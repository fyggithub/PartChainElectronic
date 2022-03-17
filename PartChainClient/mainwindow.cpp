#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Common/widget.h"
#include <QString>
#include <QStackedLayout>
#include <QWebEngineProfile>
#include <QWebEngineCookieStore>
#include <QWebEngineDownloadItem>
#include <QWebEngineSettings>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileDialog>
#include "SM4/sm4.h"
#include "include/JlCompress.h"
#include "Common/logrecord.h"
#include <QDesktopServices>
#include "Json/json/json.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pProgressMaxRange = 40;
    recvBuff = "";
    sendBuff = "";
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "7777");
}

MainWindow::~MainWindow()
{
    delete m_webView;
    delete ui;
}

void MainWindow::startweb(void)
{
    window_title = QString::fromLocal8Bit("信诺链电子存证平台");
    m_webView = new Widget(ui->widgetMain);
    QWebChannel *pWebChannel = new QWebChannel(m_webView->page());      //为网页视图页面创建通道channel
    pJsCommunicate = new JSCommunicate();                   //创建通道对象用于与JS交互
    pWebChannel->registerObject("interactObj", pJsCommunicate);//"interactObj"为注册名，JS调用的对象名必须和它相同
    m_webView->page()->setWebChannel(pWebChannel);

    QString filePath = QCoreApplication::applicationDirPath() + "/testHtml.html";
    QString urlPath = "file:///" + filePath;
    //m_webView->page()->load(QUrl(urlPath));
    m_webView->page()->load(QUrl("http://172.24.103.6:8016/"));
    //m_webView->page()->load(QUrl("http://172.16.5.71:8083/"));

    QStackedLayout* layout = new QStackedLayout(ui->widgetMain);
    ui->widgetMain->setLayout(layout);
    layout->addWidget(m_webView);

    SetCachePath(); //设置缓存路径
    connect(pJsCommunicate, &JSCommunicate::SigReceivedMessFromJS, this,&MainWindow::OnReceiveMessageFromJS);
    connect(this, &MainWindow::SigSendMessageToJS,pJsCommunicate, &JSCommunicate::SigSendMessageToJS);

    connect(m_webView->page()->profile(), &QWebEngineProfile::downloadRequested, [this](QWebEngineDownloadItem *download) {
        //connect(download, &QWebEngineDownloadItem::finished,this,&MainWindow::DownLoadFinish);
        LogRecord wLog;
        //if (download->savePageFormat() != QWebEngineDownloadItem::UnknownSaveFormat){
        //}
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), download->path());//选择下载路径
        if (fileName.isEmpty()){
            wLog.LogTrack("Warning:the downLoad fileName is empty.");
            return;
        }
        download->setPath(fileName);//设置文件下载路径
        downLoadPath = fileName;
        qDebug() << download->path() << download->savePageFormat();
        download->accept();//接收当前下载请求，只有接收后才会开始下载
        wLog.LogTrack("download accept ok.");
    });
    //m_webView->setContextMenuPolicy (Qt::NoContextMenu);
    //m_webView->page()->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    m_webView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_inspector = NULL;
    connect(m_webView, &QWidget::customContextMenuRequested, this, &MainWindow::MsgInspector);

    //获取本地ip及mac地址
    Common *pCommon = NULL;
    pCommon->GetIpAddress();
}

//调出控制台
void MainWindow::MsgInspector()
{
    QMenu* menu = new QMenu(this);
    QAction* action = menu->addAction("Inspect");
    connect(action, &QAction::triggered, this, [this](){
        if(m_inspector == NULL)
        {
            m_inspector = new Inspector(this);
        }
        else
        {
            m_inspector->show();
        }
    });
    menu->exec(QCursor::pos());
}

void MainWindow::DownLoadFinish()
{
    qDebug()<< "downLoadPath:" << downLoadPath;
    qDebug()<< "pDownLoadFileName:" << pDownLoadFileName;
    QString path = QString("DownLoadPath:%1").arg(downLoadPath);
    LogRecord wLog;
    wLog.LogTrack(path);
    wLog.LogTrack(QString("pBatchSingle:%1").arg(pBatchSingle));
    if(pBatchSingle != ""){
        Common *pCommon = NULL;
        pCommon->RemoveOverageFile(downLoadPath);
        std::string dir = downLoadPath.toStdString();
        int pos = dir.rfind("/");
        QString toDir = downLoadPath.left(pos+1);
        QStringList fileLists;

        for(int i = 0; i < pList.size(); ++i){
            QString getName = pList.at(i);
            qDebug() << getName;
            QString fullPath = toDir + getName;
            if(!QFile::copy(getName, fullPath))
            {
                qDebug()<< "file copy fail.";
            }
            pCommon->RemoveOverageFile(getName);
            fileLists << fullPath;
        }

        if(pBatchSingle == "batch"){//为批量就进行压缩
            std::string::size_type zipPos = dir.find(".zip");
            QString zipPath = downLoadPath;
            if(zipPos == dir.npos){
                zipPath = QString("%1.zip").arg(downLoadPath);
            }
            JlCompress::compressFiles(zipPath, fileLists);
            for(int j = 0;j < fileLists.size();++j)
            {
                pCommon->RemoveOverageFile(fileLists[j]);
            }
        }
        pBatchSingle = "";
        pList.clear();
    }
    wLog.LogTrack("downLoad over.");
    return;
}

void MainWindow::OnReceiveMessageFromJS(QString strMain,QString type,QString str)
{
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(strMain.toUtf8(), &parseJsonErr);
    if (!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug() << "Parsing failed";
    }
    QJsonObject jsonObject = document.object();
    QString forensicsType = jsonObject["type"].toString();
    qDebug() << forensicsType;
    if(forensicsType == "web_login")
    {
        pRecordType = WebRecord;
        pGetJsUrl = jsonObject["url"].toString();
    }
    else if(forensicsType == "camera_login")
    {
        pRecordType = CameraRecord;
    }
    else if(forensicsType == "record_login")
    {
        pRecordType = VideoRecord;
    }
    else if(forensicsType == "screenshot_login")
    {
        pRecordType = ScreenShotRecord;
    }
    else if(forensicsType == "sm4")
    {
        qDebug()<<"sm411111111111111111";
        static int countNum = 0;
        QString state = jsonObject["state"].toString();        
        qDebug()<<"state:"<<state;        
        if(state == "start")
        {
            QString sourceArray = jsonObject["encry"].toString();
            recvBuff.append(sourceArray);

            QJsonObject obj;
            obj.insert("strMain", "sm4");
            obj.insert("strBranch", "JsSegmentSend");
            obj.insert("str", "success");
            QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
            QString strJson(byteArray);
            SigSendMessageToJS(strJson,"","");
            return;
        }
        else if(state == "finish")
        {
            qDebug()<<"finish111111111111111111111111111";
            pDownLoadFileName = "";
            pBatchSingle = "";
            pDownLoadFileName = jsonObject["filename"].toString();
            pBatchSingle = jsonObject["batchSingle"].toString();
            qDebug()<<"pDownLoadFileName:"<<pDownLoadFileName;
            QString keyArray = jsonObject["key"].toString();
            qDebug()<<"key:"<<keyArray;
            QString sourceArray = jsonObject["encry"].toString();
            recvBuff.append(sourceArray);

            LogRecord wLog;
            wLog.LogTrack("--------------------------------------------");
            wLog.LogTrack("recv is over starting to decrypt.");
            pDecrypt = new SM4Decrypt;
            qDebug()<<"****************************recvBuff len:"<<recvBuff.length();
            sendBuff = pDecrypt->DecodeSM4_Base64(keyArray,recvBuff);
            double len = sendBuff.length();
            QString str = sendBuff.left(len/5);
            QJsonObject obj;
            obj.insert("strMain", "sm4");
            obj.insert("strBranch", "JsSegmentRecvStart");
            obj.insert("str", str);
            QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
            QString strJson(byteArray);
            SigSendMessageToJS(strJson,"","");            
            countNum = 0; //避免异常情况
            recvBuff = "";//清空缓存
            qDebug()<<"finish222222222222222222";
            qDebug()<<"len:"<<len;
            qDebug()<<str;
            wLog.LogTrack("starting to send message.");
            delete pDecrypt;
            return;
        }
        else if(state == "rstart")
        {
            countNum++;
            double len = sendBuff.length();
            QJsonObject obj;
            QString str;
            int segmentNum = len/5;
            int pos = segmentNum*countNum;
            if(countNum < 4)
            {                
                str = sendBuff.mid(pos,segmentNum);
                obj.insert("strBranch", "JsSegmentRecvStart");
            }
            else{
                int rightPos = len - pos;
                str = sendBuff.right(rightPos);
                countNum = 0;
                obj.insert("strBranch", "JsSegmentRecvFinish");
                sendBuff = "";
                LogRecord wLog;
                wLog.LogTrack("message send to finish.");

                QString downloadName = "";
                if(pBatchSingle == "batch"){
                    downloadName = QString::fromLocal8Bit("证据文件集.zip");
                }
                else{
                    downloadName = pDownLoadFileName;
                }
                downLoadPath = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("保存文件"), downloadName);//选择下载路径
                qDebug()<<"downLoadPath:"<<downLoadPath << pBatchSingle;
                DownLoadFinish();
            }
            obj.insert("strMain", "sm4");
            obj.insert("str", str);
            QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
            QString strJson(byteArray);
            SigSendMessageToJS(strJson,"","");
            return;
        }
        return;
    }
    else if(forensicsType == "forensicsPath")
    {
        QString mode = jsonObject["mode"].toString();
        SendPathMessage(mode);
        return;
    }
    else if(forensicsType == "tokenInvalidat")
    {
        QJsonObject obj;
        obj.insert("strMain", "tokenInvalidat");
        QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
        QString strJson(byteArray);
        SigSendMessageToJS(strJson,"","");
        QString msg = QString::fromLocal8Bit("登录信息已失效，<br>请关闭窗口，重新登录！");
        QMessageBox::warning(NULL, QString::fromLocal8Bit("提示"), msg, QString::fromLocal8Bit("确定"), 0);
        return;
    }
    else if(forensicsType == "openResourceManagement")
    {
        QString path = jsonObject["path"].toString();
        qDebug()<<"path:"<<path;
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
        QJsonObject obj;
        obj.insert("strMain", "openResourceManagement");
        QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
        QString strJson(byteArray);
        SigSendMessageToJS(strJson,"","");
        return;
    }
    else if(forensicsType == "GetDownLoadData")
    {
        QString downloadUrl = jsonObject["url"].toString();
        QString downloadToken = jsonObject["token"].toString();
        QJsonObject objParame = jsonObject["parame"].toObject();
        QByteArray byteArrayParame = QJsonDocument(objParame).toJson(QJsonDocument::Compact);
        QString strJsonParame(byteArrayParame);
        qDebug() << downloadUrl << downloadToken << strJsonParame;

        QJsonValue arrayValue = jsonObject.value(QStringLiteral("key"));
        if(arrayValue.isArray())
        {
            QJsonArray array = arrayValue.toArray();
            for(int i=0;i<array.size();i++)
            {
                QString kk = array.at(i).toString();
                qDebug()<<"kk:"<<kk;
                keyList << kk;
            }
        }

        QJsonValue arrayFilename = jsonObject.value(QStringLiteral("filename"));
        if(arrayFilename.isArray())
        {
            QJsonArray arrFilename = arrayFilename.toArray();
            for(int j = 0;j < arrFilename.size(); j++)
            {
                QString filename = arrFilename.at(j).toString();
                qDebug()<<"filename:"<<filename;
                fileList << filename;
            }
        }

        PostDownloadData(downloadUrl,downloadToken,byteArrayParame);

        QJsonObject obj;
        obj.insert("strMain", "GetDownLoadData");
        obj.insert("strBranch", "DownLoadFinish");
        QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
        QString strJson(byteArray);
        SigSendMessageToJS(strJson,"","");
        return;
    }

    pGetNameNoTime = jsonObject["name"].toString();
    pGetJsToken = jsonObject["token"].toString();

    QString getTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    pGetForensicsName = pGetNameNoTime + getTime;

    //RemoveCache();  //清理缓存文件
    DialogProgressStart();
    //NetworkTest();  //网络检测
    pNetworkClean = new networkclean();
    pNetworkClean->HostFile(pRecordType);
    pNetworkClean->IpTrack();
}

void MainWindow::UploadFile(QString *filename,int num)
{
    QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QString formData = "form-data; name=\"file\";filename=";

    Common *pcom = NULL;
    QString strDirPath = pcom->FileDirPath(pRecordType);
    for(int i = 0;i < num;i++)
    {
        QString filePath = strDirPath + filename[i];
        QFile *pfile = new QFile(filePath);
        pfile->open(QIODevice::ReadOnly);

        QHttpPart *textPart = new QHttpPart;
        textPart->setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString(formData+filename[i])));
        textPart->setBodyDevice(pfile);
        pfile->setParent(multi_part);
        multi_part->append(*textPart);
        delete textPart;
    }

    QUrl url("http://172.16.5.71:8080/api/file/uploadFile");
    QNetworkRequest request(url);
    QString tokenStr = pGetJsToken;
    QString tokenHeaderData = QString("Bearer ") + tokenStr;
    request.setRawHeader("Authorization", tokenHeaderData.toLatin1());

    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);    //往该目录中上传文件
    accessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    reply = accessManager->post(request, multi_part);
    multi_part->setParent(reply);

    connect(accessManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(loadError(QNetworkReply::NetworkError)));
}

void MainWindow::replyFinished(QNetworkReply*)    //删除指针，更新和关闭文件
{
    if(reply->error() == QNetworkReply::NoError)
    {
        qDebug()<<"**********************replyFinished";
        QString str = reply->readAll();
        reply->deleteLater();
        //qDebug() << str;

        QJsonParseError parseJsonErr;
        QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(), &parseJsonErr);
        if (!(parseJsonErr.error == QJsonParseError::NoError))
        {
            qDebug() << "Parsing failed";
        }
        QJsonObject jsonObject = document.object();
        QString code = jsonObject["code"].toString();
        QString msg = jsonObject["message"].toString();
        if(code == "0000")
        {
            //获取host文件和IP追踪的文件
            pGetHostIp = str;
            switch(pRecordType)
            {
                case WebRecord:     OpenWebForensics();break;
                case CameraRecord:  OpenWebCamera(); break;
                case VideoRecord:   OpenWebRecordVideo();break;
                case ScreenShotRecord:OpenWebScreenShoot();break;
                default:break;
            }
        }
        else
        {
            QJsonObject obj;
            switch(pRecordType)
            {
                case WebRecord:     obj.insert("strMain", "GetWebDate");break;
                case CameraRecord:  obj.insert("strMain", "GetCameraDate"); break;
                case VideoRecord:   obj.insert("strMain", "GetRecordDate");break;
                case ScreenShotRecord:obj.insert("strMain", "GetScreenshotDate");break;
                default:break;
            }
            obj.insert("strBranch", "cleanFail");
            QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
            QString strJson(byteArray);
            emit SigSendMessageToJS(strJson,"","");
            if(pRecordType == CameraRecord)
            {
                pCamera->ClosePhotograph();//关闭摄像头
                delete pCamera;
            }
            //上传服务器失败
            QMessageBox::warning(NULL, QString::fromLocal8Bit("提示"), msg, QString::fromLocal8Bit("确定"), 0);
        }
    }
    else
    {
        QJsonObject obj;
        switch(pRecordType)
        {
            case WebRecord:     obj.insert("strMain", "GetWebDate");break;
            case CameraRecord:  obj.insert("strMain", "GetCameraDate"); break;
            case VideoRecord:   obj.insert("strMain", "GetRecordDate");break;
            case ScreenShotRecord:obj.insert("strMain", "GetScreenshotDate");break;
            default:break;
        }
        obj.insert("strBranch", "cleanFail");
        QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
        QString strJson(byteArray);
        emit SigSendMessageToJS(strJson,"","");
        if(pRecordType == CameraRecord)
        {
            pCamera->ClosePhotograph();//关闭摄像头
            delete pCamera;
        }
        QMessageBox::critical(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("网络清洁性检测失败，<br>请重新取证！"),\
                                        QString::fromLocal8Bit("确定"), 0);
    }
}

void MainWindow::loadError(QNetworkReply::NetworkError)    //传输中的错误输出
{
     qDebug()<<"Error: "<<reply->error();
}

void MainWindow::PostDownloadData(const QString& url,const QString& token,const QByteArray& parame)
{
    QUrl getUrl(url);
    QNetworkRequest request(getUrl);
    QString tokenStr = token;
    QString tokenHeaderData = QString("Bearer ") + tokenStr;
    request.setRawHeader("Authorization", tokenHeaderData.toLatin1());
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("responseType", "blob");    
    QByteArray postData = parame;

    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);    //往该目录中上传文件
    accessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    accessManager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
    reply = accessManager->post(request, postData);

    connect(accessManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(DownReplyFinished(QNetworkReply*)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(loadError(QNetworkReply::NetworkError)));
}

void MainWindow::DownReplyFinished(QNetworkReply*)    //删除指针，更新和关闭文件
{
    qDebug()<<"-------------------**************---";
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray strJson = reply->readAll();
        reply->deleteLater();

        QJsonParseError parseJsonErr;
        QJsonDocument document = QJsonDocument::fromJson(strJson, &parseJsonErr);
        if (!(parseJsonErr.error == QJsonParseError::NoError))
        {
            qDebug() << "Parsing failed"<<parseJsonErr.error;
        }
        qDebug()<<"*************************fyg1";
        QJsonObject jsonObject = document.object();
        QString code = jsonObject["code"].toString();
        QString msg = jsonObject["message"].toString();
        qDebug()<<code<<msg;
        if(code == "0000"){
            QJsonValue arrayValue = jsonObject.value(QStringLiteral("data"));
            QString strBase64 = "";
            if(arrayValue.isArray())
            {
                qDebug()<<"isArray1";
                QJsonArray array = arrayValue.toArray();
                for(int i = 0;i < array.size();i++)
                {
                    qDebug()<<"isArray2"<<array.size();
                    QJsonValue iconArray = array.at(i);
                    qDebug()<<"isArray3";
                    QJsonObject icon = iconArray.toObject();
                    qDebug()<<"icon:";
                    strBase64 = icon["base64"].toString();
                    qDebug()<<"base64:";
                    QString strkey = keyList.at(i);
                    qDebug()<<"tmp ="<< strkey;
                    pDownLoadFileName = fileList.at(i);
                    pDecrypt = new SM4Decrypt;
                    pDecrypt->DecodeSM4_Base64(strkey,strBase64);
                    delete pDecrypt;
                }
            }
        }
        fileList.clear();
        keyList.clear();
    }
    else
    {
        qDebug() << "**********************1111111111";
    }
}

void MainWindow::NetworkTest()
{
    detect_thread = new networkclean();
    connect(detect_thread, SIGNAL(send_network_connect_state(int)), this, SLOT(update_network_state(int)));
    detect_thread->start(); //开启网络检测线程
}

void MainWindow::update_network_state(int state)
{
    if(state)
    {
        qDebug() << "NetWork is ok." << endl;
        detect_thread->stop();       
    }
    else
    {
        detect_thread->stop();
        DialogProgressStop();
        qDebug() << "NetWork is fail." << endl;
        QMessageBox::warning(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("网络异常"), QString::fromLocal8Bit("确定"), 0);
    }
    delete detect_thread;
}

void MainWindow::RecvMsgCloseWnd(RecordType type)
{
    qDebug()<<"*********************";
    switch(type)
    {
        case WebRecord:{
            delete pWebForensics;
            //删除取消的文件
            qDebug()<<pGetDirPath;
            if(pGetDirPath != "")
            {
                qDebug()<<"---------------";
                Common *pCommon = NULL;
                pCommon->RemoveDirFile(pGetDirPath);
                pGetDirPath = "";   //清空，避免异常导致错误
            }
        }break;
        case CameraRecord:  delete pCamera; break;
        case VideoRecord:   delete pRecordVideo;break;
        case ScreenShotRecord:delete pScreenShot;break;
        default:break;
    }

}

void MainWindow::OpenWebForensics(void)
{
    pWebForensics = new web_forensics;
    pWebForensics->OpenWebForensics();
    pWebForensics->setWindowTitle(QString::fromLocal8Bit("网页取证"));
    pWebForensics->ShowMaximized();
    connect(pWebForensics, &web_forensics::SigSendMessageToJS,pJsCommunicate, &JSCommunicate::SigSendMessageToJS);
    connect(pWebForensics, &web_forensics::SendMsgCloseWnd,this, &MainWindow::RecvMsgCloseWnd);
}

void MainWindow::OpenWebCamera(void)
{
    //pCamera = new Camera;
    pCamera->InitPhotographUi();
    pCamera->setWindowTitle(QString::fromLocal8Bit("拍摄取证"));
    pCamera->ShowMaximized();
    //pCamera->OpenPhotographWeb(); //窗口显示完后在打开摄像头
    connect(pCamera, &Camera::SigSendMessageToJS,pJsCommunicate, &JSCommunicate::SigSendMessageToJS);
    connect(pCamera, &Camera::SendMsgCloseWnd,this, &MainWindow::RecvMsgCloseWnd);
}

void MainWindow::OpenWebRecordVideo(void)
{
    pRecordVideo = new RecordVideo;
    pRecordVideo->OpenRecordVideoWeb();
    pRecordVideo->setWindowTitle(QString::fromLocal8Bit("录屏取证"));
    pRecordVideo->ShowMaximized();
    connect(pRecordVideo, &RecordVideo::SigSendMessageToJS,pJsCommunicate, &JSCommunicate::SigSendMessageToJS);
    connect(pRecordVideo, &RecordVideo::SendMsgCloseWnd,this, &MainWindow::RecvMsgCloseWnd);
}

void MainWindow::OpenWebScreenShoot(void)
{
    pScreenShot = new ScreenShot;
    pScreenShot->OpenScreenShootWeb();
    pScreenShot->setWindowTitle(QString::fromLocal8Bit("截图取证"));
    pScreenShot->ShowMaximized();
    connect(pScreenShot, &ScreenShot::SigSendMessageToJS,pJsCommunicate, &JSCommunicate::SigSendMessageToJS);
    connect(pScreenShot, &ScreenShot::SendMsgCloseWnd,this, &MainWindow::RecvMsgCloseWnd);
}

void MainWindow::RemoveCache()
{
    QWebEngineProfile *engineProfile = m_webView->page()->profile();
    engineProfile->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);
    engineProfile->clearHttpCache();        // 清理缓存
    engineProfile->clearAllVisitedLinks();  // 清理浏览记录
    QWebEngineCookieStore *cookie = engineProfile->cookieStore();
    cookie->deleteAllCookies();     //删除cookie
    cookie->deleteSessionCookies(); // 清理会话cookie
}
//设置缓存路径
void MainWindow::SetCachePath()
{
    QString path = QCoreApplication::applicationDirPath() + "/Cache/";
    Common *pcom = NULL;
    pcom->isDirExist(path);

    QWebEngineProfile * engineProfile = m_webView->page()->profile();
    engineProfile->setCachePath(path);//指定高速缓存路径
    engineProfile->setPersistentStoragePath(path);//指定会话和持久性Cookie路径
    engineProfile->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);//会话和持久性Cookie均保存到磁盘或从磁盘还原
    engineProfile->setHttpCacheType(QWebEngineProfile::DiskHttpCache);//使用磁盘缓存。
}

void MainWindow::DialogProgressInit()
{
    progressDialog=new QProgressDialog(this);
    progressDialog->setWindowModality(Qt::WindowModal); //设置进度对话框采用模态方式进行，即显示进度的同时，其他窗口将不响应输入信号
    progressDialog->setMinimumDuration(5);  //设置进度对话框出现需等待的时间，默认为4s
    progressDialog->setWindowTitle(QString::fromLocal8Bit("请稍等"));  //设置进度对话框的窗体标题
    progressDialog->setLabelText(QString::fromLocal8Bit("正在进行网络清洁性检测..."));  //设置进度对话框的显示文字信息
    progressDialog->setRange(0,pProgressMaxRange);     //设置进度对话框的步进范围
    progressDialog->setCancelButton(0);//隐藏取消按钮
    //progressDialog->setWindowFlags(Qt::FramelessWindowHint);//无边框
    //progressDialog->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    progressDialog->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    progressDialog->show();
}

void MainWindow::DialogProgressStart()
{
    timecount = 0;
    DialogProgressInit();
    timerProgress = new QTimer(this);
    connect(timerProgress, SIGNAL(timeout()), this, SLOT(DialogProgressTime()));
    timerProgress->start(1000);
}

void MainWindow::DialogProgressTime()
{
    timecount++;
    if(timecount < pProgressMaxRange)
    {
        progressDialog->setValue(timecount);
    }
    else if(timecount == pProgressMaxRange)
    {
        progressDialog->setValue(timecount);
        pNetworkClean->IpTrackFinish(pRecordType);
        delete pNetworkClean;
        if(pRecordType == CameraRecord)
        {
            pCamera = new Camera;
            pCamera->OpenPhotographWeb(); //窗口显示完后在打开摄像头
        }
    }
    else
    {
        DialogProgressStop();        
        QString BufferFileName[2];
        BufferFileName[0] = pHostFileName;
        BufferFileName[1] = pIpTrackFileName;
        UploadFile(BufferFileName,2);
        return;
    }
}

void MainWindow::DialogProgressStop()
{
    timecount = 0;
    timerProgress->stop();
    delete progressDialog;
    return;
}

//发送文件路径的消息
void MainWindow::SendPathMessage(QString mode)
{
    QString filePathDir,strHalfPath;
    QString getDirPath = QCoreApplication::applicationDirPath();

    QString strMode = "";
    if(mode == "web_forensics")
    {
        strMode.append(QString::fromLocal8Bit("/OutPut/网页取证"));
    }
    else if(mode == "camera_forensics")
    {
        strMode.append(QString::fromLocal8Bit("/OutPut/拍摄取证"));
    }
    else if(mode == "record_forensics")
    {
        strMode.append(QString::fromLocal8Bit("/OutPut/录屏取证"));
    }
    else if(mode == "screenshot_forensics")
    {
        strMode.append(QString::fromLocal8Bit("/OutPut/截图取证"));
    }

    QString strDirPath = getDirPath + strMode;
    QJsonObject obj;
    obj.insert("strMain", "forensicsMode");
    obj.insert("forensicsPath", strDirPath);
    QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    QString strJson(byteArray);
    emit SigSendMessageToJS(strJson,"","");
}
