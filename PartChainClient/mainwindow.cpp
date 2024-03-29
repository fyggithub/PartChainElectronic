﻿#include "mainwindow.h"
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
#include <fstream>
#include <string.h>
#include "config.h"
#include <QClipboard>

#define MAXBUFFSIZE (100*1024*1024)
char BuffData[MAXBUFFSIZE] = {0};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pProgressMaxRange = 40;
    countBuff = 0;
    recvBuff = "";
    sendBuff = "";
    mSingleType = "";
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "7777");
    LogRecord mlog;
    mlog.LogTrack("**************************************************");
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

    Config pConfig("");
    QString urlIni = pConfig.Get("URL","url").toString();
    QUrl getLoginUrl = QUrl::fromUserInput(urlIni);
    QString filePath = QCoreApplication::applicationDirPath() + "/testHtml.html";
    QString urlPath = "file:///" + filePath;
    //m_webView->page()->load(QUrl(urlPath));
    //m_webView->page()->load(QUrl("http://172.24.103.6:8016/"));
    //m_webView->page()->load(QUrl("http://172.16.5.71:8083/"));
    m_webView->page()->load(getLoginUrl);
    QString logmsg = QString("Start load url : %1").arg(urlIni);
    LogRecord mlog;
    mlog.LogTrack(logmsg);

    QStackedLayout* layout = new QStackedLayout(ui->widgetMain);
    ui->widgetMain->setLayout(layout);
    layout->addWidget(m_webView);

    SetCachePath(); //设置缓存路径
    connect(pJsCommunicate, &JSCommunicate::SigReceivedMessFromJS, this,&MainWindow::OnReceiveMessageFromJS);
    connect(this, &MainWindow::SigSendMessageToJS,pJsCommunicate, &JSCommunicate::SigSendMessageToJS);

    connect(m_webView->page()->profile(), &QWebEngineProfile::downloadRequested, [this](QWebEngineDownloadItem *download) {
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
    m_webView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_inspector = NULL;
    connect(m_webView, &QWidget::customContextMenuRequested, this, &MainWindow::MsgOperation);

    //获取本地ip及mac地址
    Common *pCommon = NULL;
    pCommon->GetIpAddress();
}

void MainWindow::MsgOperation()
{
    QMenu* menu = new QMenu(this);
    QAction* actionCopy = menu->addAction(QString::fromLocal8Bit("复制"));
    QAction* actionPaste = menu->addAction(QString::fromLocal8Bit("粘贴"));
    QAction* actionInspector = menu->addAction(QString::fromLocal8Bit("控制台"));
    connect(actionCopy,SIGNAL(triggered()), this,SLOT(MsgCopy()));
    connect(actionPaste,SIGNAL(triggered()), this,SLOT(MsgPaste()));    
    connect(actionInspector, &QAction::triggered, this, [this](){
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

void MainWindow::MsgCopy()
{
    m_webView->triggerPageAction(QWebEnginePage::Copy);
}

void MainWindow::MsgPaste()
{
    m_webView->triggerPageAction(QWebEnginePage::Paste);
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
        LogRecord mLog;
        mLog.LogTrack(QString("Send js data : %1").arg(strJson));
        return;
    }
    else if(forensicsType == "openResourceManagement")
    {
        LogRecord mLog;
        QString path = jsonObject["path"].toString();
        qDebug()<<"path:"<<path;
        QDir dir(path);
        if(dir.exists())
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(path));
        }
        else{
            qDebug() << "file is not exists.";
            mLog.LogTrack(QString("File path is not exists : %1").arg(path));
            QMessageBox::warning(NULL, QString::fromLocal8Bit("查看文件"), QString::fromLocal8Bit("本地文件已删除，无法查看"),\
                                            QString::fromLocal8Bit("确定"), 0);
        }

        QJsonObject obj;
        obj.insert("strMain", "openResourceManagement");
        QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
        QString strJson(byteArray);
        SigSendMessageToJS(strJson,"","");        
        mLog.LogTrack(QString("Send js data : %1").arg(strJson));
        return;
    }
    else if(forensicsType == "GetDownLoadData")
    {
        pBatchSingle = jsonObject["batchSingle"].toString();
        mSingleType = jsonObject["SingleType"].toString();
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
                QString key = array.at(i).toString();
                qDebug()<<"key:"<<key;
                keyList << key;
            }
        }

        QJsonValue arrayFileId = objParame.value(QStringLiteral("fileInfoVos"));
        if(arrayFileId.isArray())
        {
            QJsonArray arrFileId = arrayFileId.toArray();
            for(int m = 0;m < arrFileId.size(); m++)
            {
                QJsonValue idArray = arrFileId.at(m);
                QJsonObject idObject = idArray.toObject();
                QString fileId = idObject["file_id"].toString();

                qDebug()<<"fileId:"<<fileId;
                keyMap.insert(fileId,keyList.at(m));
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
                LogRecord wLog;
                wLog.LogTrack(QString("filename : %1").arg(filename));
                if(filename.isEmpty()){
                    wLog.LogTrack(QString("Warning:: filename is empty!"));
                    keyList.clear();
                    keyMap.clear();

                    QJsonObject obj;
                    obj.insert("strMain", "GetDownLoadData");
                    obj.insert("strBranch", "DownLoadFail");
                    QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
                    QString strJson(byteArray);
                    SigSendMessageToJS(strJson,"","");
                    QMessageBox::warning(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("下载文件名不能为空！"), QString::fromLocal8Bit("确定"), 0);
                    return;
                }

                fileList << filename;
            }
        }

        PostDownloadData(downloadUrl,downloadToken,byteArrayParame);
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
    qDebug()<<"**********************UploadFile";
    Common *pcom = NULL;
    QString strDirPath = pcom->FileDirPath(pRecordType);
//    for(int i = 0;i < num;i++)
//    {
//        QString filePath = strDirPath + filename[i];
//        QFile *pfile = new QFile(filePath);
//        pfile->open(QIODevice::ReadOnly);

//        QHttpPart *textPart = new QHttpPart;
//        textPart->setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString(formData+filename[i])));
//        textPart->setBodyDevice(pfile);
//        pfile->setParent(multi_part);
//        multi_part->append(*textPart);
//        delete textPart;
//        //pfile->close();
//    }
    QString filePath0 = strDirPath + filename[0];
    pfile0 = new QFile(filePath0);
    pfile0->open(QIODevice::ReadOnly);
    QHttpPart *textPart0 = new QHttpPart;
    textPart0->setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString(formData+filename[0])));
    textPart0->setBodyDevice(pfile0);
    pfile0->setParent(multi_part);
    multi_part->append(*textPart0);
    delete textPart0;

    QString filePath1 = strDirPath + filename[1];
    pfile1 = new QFile(filePath1);
    pfile1->open(QIODevice::ReadOnly);
    QHttpPart *textPart1 = new QHttpPart;
    textPart1->setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString(formData+filename[1])));
    textPart1->setBodyDevice(pfile1);
    pfile1->setParent(multi_part);
    multi_part->append(*textPart1);
    delete textPart1;

    QUrl url = pcom->GetUploadUrl();
    //QUrl url("http://172.16.5.71:8080/api/file/uploadFile");
    //QUrl url("http://172.16.5.71:21417/api/file/uploadFile");
    QNetworkRequest request(url);
    QString tokenStr = pGetJsToken;
    QString tokenHeaderData = QString("Bearer ") + tokenStr;
    request.setRawHeader("Authorization", tokenHeaderData.toLatin1());

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    reply = manager->post(request, multi_part);
    multi_part->setParent(reply);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(loadError(QNetworkReply::NetworkError)));
}

void MainWindow::replyFinished(QNetworkReply*)    //删除指针，更新和关闭文件
{
    pfile0->close();
    pfile1->close();
    delete pfile0;
    delete pfile1;

    if(reply->error() == QNetworkReply::NoError)
    {
        qDebug()<<"**********************replyFinished";
        QString str = reply->readAll();        
        reply->deleteLater();
        QApplication::processEvents();
        qDebug()<<"**********************reply delete over.";

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
                case WebRecord:{
                    //OpenWebForensics();
                    pWebForensics->ShowMaximized();
                }break;
                case CameraRecord:  OpenWebCamera(); break;
                case VideoRecord:   {
                    OpenWebRecordVideo();
                    OpenWebRecordDialog();
                }break;
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
            else if(pRecordType ==  WebRecord)
            {
                delete pWebForensics;
            }

            pLog = new Common();
            pLog->RemoveFailFiles(pRecordType);
            delete pLog;
            //上传服务器失败
            QMessageBox::warning(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("网络清洁性检测失败，<br>请重新取证！"),\
                                            QString::fromLocal8Bit("确定"), 0);
        }
    }
    else
    {
        QJsonObject obj;
        switch(pRecordType)
        {
            case WebRecord: obj.insert("strMain", "GetWebDate");break;
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
        else if(pRecordType ==  WebRecord)
        {
            delete pWebForensics;
        }

        QMessageBox::critical(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("网络清洁性检测失败，<br>请重新取证！"),\
                                        QString::fromLocal8Bit("确定"), 0);
        pLog = new Common();
        pLog->RemoveFailFiles(pRecordType);
        delete pLog;
    }
}

void MainWindow::loadError(QNetworkReply::NetworkError)    //传输中的错误输出
{
     qDebug()<<"Error: "<<reply->error();
}

void MainWindow::PostDownloadData(const QString& url,const QString& token,const QByteArray& parame)
{
    mAccessManager = new QNetworkAccessManager(this);
    if((pBatchSingle == "single") && (mSingleType == "certificate")){
        QJsonParseError parseJsonErr;
        QJsonDocument document = QJsonDocument::fromJson(parame, &parseJsonErr);
        QJsonObject jsonObject = document.object();
        QString strEvidenceId = jsonObject["evidenceId"].toString();
        QString strFullUrl = QString("%1?%2=%3").arg(url).arg("evidenceId").arg(strEvidenceId);

        QNetworkRequest request;
        QString tokenStr = token;
        QString tokenHeaderData = QString("Bearer ") + tokenStr;
        request.setRawHeader("Authorization", tokenHeaderData.toLatin1());
        request.setUrl(QUrl(strFullUrl));
        //mAccessManager = new QNetworkAccessManager(this);
        mAccessManager->get(request);
        mFile = fopen(TEMPFILENAME,"wb+");
        connect(mAccessManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(DownReplyFinishedTest(QNetworkReply*)));
    }
    else{
        QUrl getUrl(url);
        qDebug()<<"url:"<<url;
        QNetworkRequest request(getUrl);
        QString tokenStr = token;
        QString tokenHeaderData = QString("Bearer ") + tokenStr;
        request.setRawHeader("Authorization", tokenHeaderData.toLatin1());
        request.setRawHeader("Content-Type", "application/json");
        QByteArray postData = parame;
        qDebug()<<"parame:"<<parame;

        //QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);    //往该目录中上传文件
        //mAccessManager = new QNetworkAccessManager(this);
        mAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
        mAccessManager->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);
        reply = mAccessManager->post(request, postData);

        LogRecord wLog;
        wLog.LogTrack("------------------------------------------");
        wLog.LogTrack("start post download.");
        QString strParame = parame;
        wLog.LogTrack(QString("parame : %1").arg(strParame));

        mFile = fopen(TEMPFILEZIPNAME,"wb+");

        connect(mAccessManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(DownReplyFinishedTest(QNetworkReply*)));
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(loadError(QNetworkReply::NetworkError)));
        connect( reply, SIGNAL( readyRead() ), this, SLOT( WriteToFile() ) );
    }
}

void MainWindow::WriteToFile()
{
    if (reply->bytesAvailable()>100000)
    {
        QByteArray tempArry = reply->readAll();
        fwrite(tempArry.data(), 1, tempArry.length(), mFile);
    }
}

void MainWindow::DownReplyFinishedTest(QNetworkReply *strReply)
{
    qDebug()<<"-------------------DownReplyFinishedTest";
    LogRecord wLog;
    wLog.LogTrack("start recv download data.");
    if(strReply->error() == QNetworkReply::NoError){
        qDebug()<<"reply->readAll1.";
        wLog.LogTrack("start read download data.");
        QByteArray strData = strReply->readAll();
        wLog.LogTrack("start read download data1.");
        strReply->close();
        strReply->deleteLater();
        if(pBatchSingle != "single"){
            reply->deleteLater();
        }
        mAccessManager->deleteLater();
        wLog.LogTrack("read download file over.");

        fwrite(strData.data(), 1, strData.length(), mFile);
        fclose(mFile);
        mFile = NULL;
        qDebug()<<"strData.length():"<<strData.length();
        qDebug()<<"*****************recv:"<<strData;

        QJsonParseError parseJsonErr;
        QJsonDocument document = QJsonDocument::fromJson(strData, &parseJsonErr);
        if (parseJsonErr.error == QJsonParseError::NoError)
        {
            QJsonObject jsonObject = document.object();
            QString mes = jsonObject["message"].toString();
            qDebug()<<"mes:"<<mes;

            //获取的数据为json，则返回错误代码
            qDebug() << "Service abnormal,file download failed!";
            wLog.LogTrack("Service abnormal,file download failed!");
            QJsonObject obj;
            obj.insert("strMain", "GetDownLoadData");
            obj.insert("strBranch", "DownLoadFail");
            QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
            QString strJson(byteArray);
            SigSendMessageToJS(strJson,"","");
            //QMessageBox::warning(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("文件下载失败，服务器异常！"), QString::fromLocal8Bit("确定"), 0);
            QMessageBox::warning(NULL, QString::fromLocal8Bit("提示"), mes, QString::fromLocal8Bit("确定"), 0);
            return;
        }

        pDecrypt = new SM4Decrypt;
        if((pBatchSingle == "single") && (mSingleType == "certificate")){
            pDecrypt->DecodeSM4_CertificateStreamTest(keyList,fileList);
        }
        else if((pBatchSingle == "single") && (mSingleType == "detail")){
            pDecrypt->DecodeSM4_DetailStreamTest(keyList,fileList);
        }
        else{
            pDecrypt->DecodeSM4_StreamTest(keyList,fileList,strData.data(),strData.length());
        }
        delete pDecrypt;
        fileList.clear();
        keyList.clear();
        wLog.LogTrack("DecodeSM4 over.");

        QString downloadName = "";
        QString appPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/";
        qDebug()<< "appPath:"<<appPath;
        if(pBatchSingle == "batch"){            
            downloadName = appPath + QString::fromLocal8Bit("证据文件集.rar");
        }
        else{
            downloadName = appPath + pDownLoadFileName;
        }
        downLoadPath = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("保存文件"), downloadName);//选择下载路径
        if(downLoadPath == ""){
            wLog.LogTrack("warning : download cancel!");
            Common *pCommon = NULL;
            pCommon->RemoveOverageFile(pDownLoadFileName);

            QJsonObject obj;
            obj.insert("strMain", "GetDownLoadData");
            obj.insert("strBranch", "DownLoadFail");
            QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
            QString strJson(byteArray);
            SigSendMessageToJS(strJson,"","");
            return;
        }
        qDebug()<<"downLoadPath:"<<downLoadPath << pBatchSingle;
        QString getPath = QString("downLoadPath:%1").arg(downLoadPath);
        QString getBatchSingle = QString("pBatchSingle:%1").arg(pBatchSingle);
        wLog.LogTrack(getPath);
        wLog.LogTrack(getBatchSingle);
        if(pBatchSingle == "batch"){
            std::string dir = downLoadPath.toStdString();
            std::string::size_type zipPos = dir.find(".rar");
            QString zipPath = downLoadPath;
            if(zipPos == dir.npos){
                downLoadPath = QString("%1.rar").arg(downLoadPath);
            }
        }

        QFile fileTemp(downLoadPath);
        if(fileTemp.exists())//解决下载文件直接替换相同名的问题
        {
            qDebug()<<"file exists.";
            wLog.LogTrack("file download exists.");
            if(fileTemp.remove()){
                wLog.LogTrack("exists file remove success.");
            }
            else{
                wLog.LogTrack("exists file remove fail.");
            }
        }

        if(!QFile::copy(pDownLoadFileName, downLoadPath))
        {
            wLog.LogTrack("file download copy fail!");
            qDebug()<< "file copy fail.";
            Common *pCommon = NULL;
            pCommon->RemoveOverageFile(pDownLoadFileName);

            QMessageBox::warning(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("文件被占用！"), QString::fromLocal8Bit("确定"), 0);
            QJsonObject obj;
            obj.insert("strMain", "GetDownLoadData");
            obj.insert("strBranch", "DownLoadFail");
            QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
            QString strJson(byteArray);
            SigSendMessageToJS(strJson,"","");
            return;
        }
        else{
            Common *pCommon = NULL;
            pCommon->RemoveOverageFile(pDownLoadFileName);
        }

        //mSingleType = "";
        pBatchSingle = "";
        wLog.LogTrack("file download over.");
        QJsonObject obj;
        obj.insert("strMain", "GetDownLoadData");
        obj.insert("strBranch", "DownLoadSuccess");
        QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
        QString strJson(byteArray);
        SigSendMessageToJS(strJson,"","");
        wLog.LogTrack(QString("Send js data : %1").arg(strJson));
    }
    else{
        qDebug() << "QNetworkReply Error.";
        QJsonObject obj;
        obj.insert("strMain", "GetDownLoadData");
        obj.insert("strBranch", "DownLoadFail");
        QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
        QString strJson(byteArray);
        SigSendMessageToJS(strJson,"","");
        wLog.LogTrack(QString("Send js data : %1").arg(strJson));
        QMessageBox::warning(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("文件下载失败，服务器异常！"), QString::fromLocal8Bit("确定"), 0);
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
        case VideoRecord:{
        }break;
        case VideoRecordDialog: {
            delete m_record;
            pRecordDialogFlag = 1;
            pRecordVideo->CloseRecordWebMsg();
            delete pRecordVideo;
        }break;
        case ScreenShotRecord:delete pScreenShot;break;
        default:break;
    }

}

void MainWindow::OpenWebForensics(void)
{
    pWebForensics = new web_forensics;
    pWebForensics->OpenWebForensics();
    pWebForensics->setWindowTitle(QString::fromLocal8Bit("网页取证"));
    //pWebForensics->ShowMaximized();
    pWebForensics->hide();
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
    pRecordVideo->setWindowTitle(QString::fromLocal8Bit("录屏取证浏览器"));
    pRecordVideo->ShowMaximized();
    pRecordVideo->SimulateButtonClick();
    connect(pRecordVideo, &RecordVideo::SigSendMessageToJS,pJsCommunicate, &JSCommunicate::SigSendMessageToJS);
    connect(pRecordVideo, &RecordVideo::SendMsgCloseWnd,this, &MainWindow::RecvMsgCloseWnd);
}

void MainWindow::OpenWebRecordDialog(void)
{
    m_record = new RecordDialog();
    m_record->show();
    connect(m_record, &RecordDialog::SigSendMessageToJS,pJsCommunicate, &JSCommunicate::SigSendMessageToJS);
    connect(m_record, &RecordDialog::SendMsgCloseWnd,this, &MainWindow::RecvMsgCloseWnd);
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
        if(timecount == 2)
        {
            if(pRecordType == WebRecord){
                OpenWebForensics();
            }
        }
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
    obj.insert("IpAddress", pIpAddress);
    obj.insert("MacAddress", pMacAddress);
    obj.insert("OsVersion", pOsVersion);
    QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    QString strJson(byteArray);
    emit SigSendMessageToJS(strJson,"","");
    LogRecord mLog;
    mLog.LogTrack(QString("Send js data : %1").arg(strJson));
}
