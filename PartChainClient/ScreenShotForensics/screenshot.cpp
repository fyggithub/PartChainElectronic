#include "screenshot.h"
#include "ui_screenshot.h"
#include <QStackedLayout>
#include <QTimer>
#include <QScreen>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QFileDialog>
#include <QWebEngineProfile>
#include "Common/widget.h"
#include "Common/common.h"


ScreenShot::ScreenShot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScreenShot)
{
    ui->setupUi(this);
    timecount = 0;
    pCloseFlag = 0;

    ui->BtnReload->setStyleSheet("QPushButton{border-top:0px solid #e8f3f9;background:  transparent;}"
                                 "QPushButton:pressed{border:2px solid white;border-radius:10px;}"
                                 );
    ui->BtnBack->setStyleSheet("QPushButton{border-top:0px solid #e8f3f9;background:  transparent;}"
                                 "QPushButton:pressed{border:2px solid white;border-radius:10px;}"
                                 );
    ui->BtnScnSot->setStyleSheet("QPushButton{border-top:0px solid #e8f3f9;background:  transparent;}"
                                 "QPushButton:pressed{border:2px solid white;border-radius:10px;}"
                                 );
    ui->BtnUpload->setStyleSheet("QPushButton{border-top:0px solid #e8f3f9;background:  transparent;}"
                                 "QPushButton:pressed{border:2px solid white;border-radius:10px;}"
                                 );
    ui->BtnPreview->setStyleSheet("QPushButton{border-top:0px solid #e8f3f9;background:  transparent;}"
                                 "QPushButton:pressed{border:2px solid white;border-radius:10px;}"
                                 );

    ui->lineEdit->setStyleSheet("QLineEdit{border-image: url(:/new/prefix1/Icon/url.png);}");

    ui->BtnReload->setToolTip(QString::fromLocal8Bit("刷新"));
    ui->BtnBack->setToolTip(QString::fromLocal8Bit("后退"));
    ui->BtnScnSot->setToolTip(QString::fromLocal8Bit("截图"));
    ui->BtnUpload->setToolTip(QString::fromLocal8Bit("上传"));
    ui->BtnPreview->setToolTip(QString::fromLocal8Bit("预览"));
    pBtn = new BubblelTipButton(ui->BtnPreview);

    connect(ui->BtnReload,SIGNAL(clicked()),this,SLOT(ReloadUrl()));
    connect(ui->BtnBack,SIGNAL(clicked()),this,SLOT(BackUrl()));
    connect(ui->BtnScnSot,SIGNAL(clicked()),this,SLOT(GrabFullScreen()));
    connect(ui->BtnUpload,SIGNAL(clicked()),this,SLOT(FileUpload()));
    connect(ui->BtnPreview,SIGNAL(clicked()),this,SLOT(OpenPreview()));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(JumpUrl()), Qt::UniqueConnection);
}

ScreenShot::~ScreenShot()
{
    delete pBtn;
    delete pLog;
    delete m_ScnSotWebView;
    delete ui;
}


void ScreenShot::ShowMaximized(void)
{
    setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen))
                   | Qt::WindowMaximized);
    show();
}


void ScreenShot::JumpUrl(void)
{
    QUrl url = QUrl::fromUserInput(ui->lineEdit->text());
    if(url.isValid()){
        qDebug()<<"url is Valid."<<url;
    }
    else{
        qDebug()<<"url is not Valid."<<url;
    }

    if (!url.isEmpty())
    {
        m_ScnSotWebView->load(url);
        pLog->FromBaiDuJumpUrl(ScreenShotRecord, FileLogName,url.toEncoded());
    }
}

void ScreenShot::ReloadUrl(void)
{
    m_ScnSotWebView->reload();
}

void ScreenShot::BackUrl(void)
{
    m_ScnSotWebView->back();
}


void ScreenShot::OpenScreenShootWeb(void)
{
    m_ScnSotWebView = new Widget(this);
    QUrl url("http://www.baidu.com");
    m_ScnSotWebView->load(url);
    QStackedLayout* layout = new QStackedLayout(ui->scnsotwidget);
    ui->scnsotwidget->setLayout(layout);
    layout->addWidget(m_ScnSotWebView);
    ui->lineEdit->setText(url.toString());

    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString strTime = QString::fromLocal8Bit("当前时间") +  currentTime;
    ui->label_time->setText(strTime);
    ui->label_tip->setText(QString::fromLocal8Bit("提示：正在进行截图取证，请在本窗口进行取证"));
    ui->label_time->setStyleSheet("color:red;");
    ui->label_tip->setStyleSheet("color:red;");
    pCurrentTime = new QTimer(this);
    connect(pCurrentTime, SIGNAL(timeout()), this, SLOT(DisplayCurrentTime()));
    pCurrentTime->start(100);

    pLog = new Common();
    QString getTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz");
    FileLogName = "log" + getTime + ".txt";
    pLog->CreateForensicsLog(ScreenShotRecord, FileLogName);
    connect(m_ScnSotWebView, SIGNAL(urlChanged(QUrl)),this, SLOT(OnUrlChanged(QUrl)));
    m_ScnSotWebView->setContextMenuPolicy (Qt::NoContextMenu);
    /*connect(m_ScnSotWebView->page()->profile(), &QWebEngineProfile::downloadRequested, [this](QWebEngineDownloadItem *download) {
        if (download->savePageFormat() != QWebEngineDownloadItem::UnknownSaveFormat)
        {

        }

        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), download->path());//选择下载路径
        if (fileName.isEmpty())
            return;

        download->setPath(fileName);//设置文件下载路径
        qDebug() << download->path() << download->savePageFormat();
        download->accept();//接收当前下载请求，只有接收后才会开始下载
    });*/
}

void ScreenShot::DisplayCurrentTime()
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString strTime = QString::fromLocal8Bit("当前时间") +  currentTime;
    ui->label_time->setText(strTime);
    ui->label_time->setStyleSheet("color:red;");
}

void ScreenShot::OpenPreview(void)
{
    pPreviewWindow = new PreviewWindow;
    pPreviewWindow->show();
    connect(pPreviewWindow, &PreviewWindow::SendPreviewMsgCloseWnd,this, &ScreenShot::PreviewMsgCloseWnd);
}

void ScreenShot::PreviewMsgCloseWnd(void)
{
    delete pPreviewWindow;
    pBtn->setFixedSize(40, 13);
    pBtn->setMsgNumber(pMap.size());
}

void ScreenShot::FileUpload(void)
{
    if((pCloseFlag == 1) && (pMap.size() != 0))
    {
        pCloseFlag = 2;
        Common *pCommon = NULL;
        QString strDirPath = pCommon->FileDirPath(ScreenShotRecord);
        QString removeLogFile = strDirPath + FileLogName;
        pCommon->RemoveScnLogFile(removeLogFile);

        QJsonObject obj;
        obj.insert("strMain", "GetScreenshotDate");
        obj.insert("strBranch", "token");
        obj.insert("path", strDirPath);
        obj.insert("hostIp", pGetHostIp);
        obj.insert("ipAddress", pIpAddress);
        obj.insert("macAddress", pMacAddress);
        obj.insert("osVersion", pOsVersion);
        QJsonArray tokeArray;
        for(QMap<QString,QString>::ConstIterator ite=pMap.constBegin(); ite!=pMap.constEnd(); ++ite)
        {
            //qDebug()<<ite.key()<<": "<<ite.value();
            //strMsg += ite.value();
            tokeArray.append(ite.value());
        }
        obj.insert("str", tokeArray);
        QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
        QString strJson(byteArray);

        pCommon->CommunicationWriteLog("GetScreenshotDate","token",strJson);
        emit SigSendMessageToJS(strJson,"","");
        this->close();  //关闭子窗口
    }
    else
    {
        QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请先进行取证"),\
                                                       QString::fromLocal8Bit("确定"), 0);
    }

}

void ScreenShot::GrabFullScreen(void)
{
    if(pMap.size() >= 5){
        QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("最多只能截图5张！"),\
                                                       QString::fromLocal8Bit("确定"), 0);
        return;
    }

    pBtn->setFixedSize(40, 13);
    pBtn->setMsgNumber(pMap.size()+1);


    Common *pcom = NULL;
    QScreen *screen = QGuiApplication::primaryScreen();
    QString filePath = pcom->FileDirPath(ScreenShotRecord);
    QString getTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz");
    QString filePathName = "scnsot-" + getTime + ".png";
    QString fileFullPathName = filePath + filePathName;    
    pcom->isDirExist(filePath);
    pFilePathName = filePathName;

    if(!screen->grabWindow(0).save(fileFullPathName, "png"))
    {
        qDebug() << "save full screen failed";
    }

    pLog->SaveForensicsLog(ScreenShotRecord, FileLogName);
    QString strRenameFile = pcom->RenameLogFile(ScreenShotRecord, FileLogName);

    DialogProgressDeal();
    BufferFileName[0] = pFilePathName;
    //BufferFileName[1] = FileLogName;
    BufferFileName[1] = strRenameFile;
    ScnShotUploadFile(BufferFileName,2);
}

void ScreenShot::OnUrlChanged(QUrl url)
{
    pLog->WebJumpUrl(ScreenShotRecord, FileLogName,url.toEncoded());
    ui->lineEdit->setText(url.toEncoded());
}

void ScreenShot::closeEvent(QCloseEvent *event)
{
    if(pCloseFlag != 2)
    {
        int result = QMessageBox::question(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("文件还未上传，<br>是否退出当前窗口？"),\
                                           QString::fromLocal8Bit("确定"), QString::fromLocal8Bit("取消"),0);

        if (result == 0)
        {
            Common *pCommon = NULL;
            QString strDirPath = pCommon->FileDirPath(ScreenShotRecord);
            switch (pCloseFlag) {
                case 0:{                    
                    QJsonObject obj;
                    obj.insert("strMain", "GetScreenshotDate");
                    obj.insert("strBranch", "cancel");
                    obj.insert("str", "cancel");
                    obj.insert("path", strDirPath);
                    obj.insert("hostIp", pGetHostIp);
                    QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
                    QString strJson(byteArray);
                    pCommon->CommunicationWriteLog("GetWebDate","cancel","cancel");
                    emit SigSendMessageToJS(strJson,"","");
                }break;
                case 1:{
                    QString strMsg;
                    for(QMap<QString,QString>::ConstIterator ite=pMap.constBegin(); ite!=pMap.constEnd(); ++ite)
                    {
                        //qDebug()<<ite.key()<<": "<<ite.value();
                        strMsg += ite.value();
                    }
                    pCloseFlag = 0;
                    QJsonObject obj;
                    obj.insert("strMain", "GetScreenshotDate");
                    obj.insert("strBranch", "cancel");
                    obj.insert("str", strMsg);
                    obj.insert("path", strDirPath);
                    obj.insert("hostIp", pGetHostIp);
                    QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
                    QString strJson(byteArray);
                    pCommon->CommunicationWriteLog("GetWebDate","cancel",strMsg);
                    emit SigSendMessageToJS(strJson,"","");
                }break;
                default:break;
            }
            pCurrentTime->stop();//停止记录当前时间
            pMap.clear();//清空容器
            event->accept();
            pCommon->RemoveDirFile(strDirPath);//本地删除此次操作的取证文件
        }
        else if (result == 1)
        {
            event->ignore();
            return;
        }
    }
    else
    {
        pCloseFlag = 0;
        pMap.clear();//清空容器
    }
    emit SendMsgCloseWnd(ScreenShotRecord);
}

void ScreenShot::DialogProgressDeal()
{
    DialogProgressInit();
    timerProgress = new QTimer(this);
    connect(timerProgress, SIGNAL(timeout()), this, SLOT(DialogProgressTime()));
    timerProgress->start(1000);
}

void ScreenShot::DialogProgressInit()
{
    progressDialog=new QProgressDialog(this);
    progressDialog->setWindowModality(Qt::WindowModal); //设置进度对话框采用模态方式进行，即显示进度的同时，其他窗口将不响应输入信号
    progressDialog->setMinimumDuration(5);  //设置进度对话框出现需等待的时间，默认为4s
    progressDialog->setWindowTitle(QStringLiteral("请稍等"));  //设置进度对话框的窗体标题
    progressDialog->setLabelText(QStringLiteral("文件正在上传..."));  //设置进度对话框的显示文字信息
    //设置进度对话框的“取消”按钮的显示文字
    //progressDialog->setMinimum(0);  // 最小值
    //progressDialog->setMaximum(0);
    progressDialog->setRange(0,0);     //设置进度对话框的步进范围
    progressDialog->setCancelButton(0);//隐藏取消按钮
    //progressDialog->setWindowFlags(Qt::FramelessWindowHint);//无边框
    //progressDialog->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    progressDialog->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    progressDialog->show();
}

void ScreenShot::DialogProgressTime()
{
    timecount++;
    /*if(timecount < 40)
    {
        progressDialog->setValue(timecount);
    }
    else if(timecount == 40)
    {
        qDebug() << "emit SigIpTrack";
        pNetworkClean->IpTrackFinish(ScreenShotRecord);
        progressDialog->setValue(timecount);
    }
    else
    {
        DialogProgressStop();

        BufferFileName[0] = pFilePathName;
        BufferFileName[1] = pHostFileName;
        BufferFileName[2] = FileLogName;
        BufferFileName[3] = pIpTrackFileName;
        qDebug() << pFilePathName;
        qDebug() << pHostFileName;
        qDebug() << FileLogName;
        ScnShotUploadFile(BufferFileName,4);
        return;
    }*/
}

void ScreenShot::DialogProgressStop()
{
    timecount = 0;
    timerProgress->stop();
    delete progressDialog;
    return;
}


void ScreenShot::ScnShotUploadFile(QString *filename,int num)
{
    QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QString formData = "form-data; name=\"file\";filename=";

    Common *pcom = NULL;
    QString strDirPath = pcom->FileDirPath(ScreenShotRecord);
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

void ScreenShot::replyFinished(QNetworkReply*)    //删除指针，更新和关闭文件
{
    DialogProgressStop();
    if(reply->error() == QNetworkReply::NoError)
    {
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
            /*int result = QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("文件上传成功"),\
                                               QString::fromLocal8Bit("确定"), 0);
            if (result == 0)
            {
                qDebug() << "code == 0000";
                //emit SigSendMessageToJS("GetScreenshotDate","token",str);
                //pCloseFlag = 1;
                //this->close();  //关闭子窗口

                pMap.insert(pFilePathName,str);//存储到容器
            }*/
            pMap.insert(pFilePathName,str);//存储到容器
            pCloseFlag = 1;
        }
        else
        {
            //上传服务器失败
            QMessageBox::warning(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("截图上传失败，<br>请再次上传取证！"),\
                                               QString::fromLocal8Bit("确定"), 0);
        }
    }
    else
    {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("截图上传失败，<br>请再次上传取证！"),\
                                                QString::fromLocal8Bit("确定"), 0);
    }
}

void ScreenShot::loadError(QNetworkReply::NetworkError)    //传输中的错误输出
{
     qDebug()<<"Error: "<<reply->error();
}
