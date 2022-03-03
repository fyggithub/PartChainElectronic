#include "web_forensics.h"
#include "ui_web_forensics.h"
#include <QStackedLayout>
#include <QGuiApplication>
#include <QScreen>
#include <QWebEngineProfile>
#include <QFileDialog>
#include <QWebEngineSettings>
#include <QTimer>
#include <QFile>
#include <QPixmap>
#include <QClipboard>
#include <QThread>
#include <QMessageBox>
#include <QProgressDialog>
#include <QProgressBar>
#include <QWebEngineCookieStore>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include "Common/widget.h"
#include "Common/common.h"
#include "Common/networkclean.h"
#include <QTextCodec>

web_forensics::web_forensics(QWidget *parent) :
    QMainWindow(parent)
    ,ui(new Ui::web_forensics)
{
    ui->setupUi(this);

    timecount = 0;
    pCloseFlag = 0;
    pFilePathName = "";

//    ui->BtnReload->setStyleSheet("QPushButton{border-top:0px solid #e8f3f9;background:  transparent;}"
//                                 "QPushButton:pressed{border:2px solid white;border-radius:10px;}"
//                                 );
//    ui->BtnShoot->setStyleSheet("QPushButton{border-top:0px solid #e8f3f9;background:  transparent;}"
//                                 "QPushButton:pressed{border:2px solid white;border-radius:10px;}"
//                                 );
//    ui->BtnUpload->setStyleSheet("QPushButton{border-top:0px solid #e8f3f9;background:  transparent;}"
//                                 "QPushButton:pressed{border:2px solid white;border-radius:10px;}"
//                                 );
//    ui->lineEdit->setStyleSheet("QLineEdit{border-image: url(:/new/prefix1/Icon/url.png);}");
//    ui->lineEdit->setEnabled(false);
//    ui->BtnReload->setToolTip(QString::fromLocal8Bit("刷新"));
//    ui->BtnShoot->setToolTip(QString::fromLocal8Bit("网页截图"));
//    ui->BtnUpload->setToolTip(QString::fromLocal8Bit("上传"));

//    connect(ui->BtnReload,SIGNAL(clicked()),this,SLOT(ReloadUrl()));
//    connect(ui->BtnUpload,SIGNAL(clicked()),this,SLOT(FileUpload()));
    connect(this, SIGNAL(SendMsgClose()),this, SLOT(RecvMsgClose()));
}

web_forensics::~web_forensics()
{
    delete pLog;
    delete m_webView;
    delete ui;
}

void web_forensics::ShowMaximized()
{
    setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen)) | Qt::WindowMaximized);
    show();
}

void web_forensics::OpenWebForensics(void)
{
    m_webView = new Widget(this);
    QUrl url1 = QUrl::fromUserInput(pGetJsUrl);
    m_webView->page()->load(url1);
    QStackedLayout* layout = new QStackedLayout(ui->webwidget);
    ui->webwidget->setLayout(layout);
    layout->addWidget(m_webView);
    //ui->lineEdit->setText(pGetJsUrl);

//    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
//    QString strTime = QString::fromLocal8Bit("当前时间") +  currentTime;
//    ui->label_time->setText(strTime);
//    ui->label_tip->setText(QString::fromLocal8Bit("提示：正在进行网页取证，请在本窗口进行取证"));
//    ui->label_time->setStyleSheet("color:red;");
//    ui->label_tip->setStyleSheet("color:red;");
//    pCurrentTime = new QTimer(this);
//    connect(pCurrentTime, SIGNAL(timeout()), this, SLOT(DisplayCurrentTime()));
//    pCurrentTime->start(100);

    pLog = new Common();
    QString getTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz");
    FileLogName = "log" + getTime + ".txt";
    pLog->CreateForensicsLog(WebRecord, FileLogName);
    connect(m_webView, SIGNAL(urlChanged(QUrl)),this, SLOT(OnUrlChanged(QUrl)));
    m_webView->setContextMenuPolicy (Qt::NoContextMenu);
    /*connect(m_webView->page()->profile(), &QWebEngineProfile::downloadRequested, [this](QWebEngineDownloadItem *download) {
        if (download->savePageFormat() != QWebEngineDownloadItem::UnknownSaveFormat){}
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), download->path());//选择下载路径
        if (fileName.isEmpty())
            return;

        download->setPath(fileName);//设置文件下载路径
        qDebug() << download->path() << download->savePageFormat();
        download->accept();//接收当前下载请求，只有接收后才会开始下载
    });*/
    connect(m_webView,SIGNAL(loadFinished(bool)),this,SLOT(LoadWebOver(bool)));

    //判断输入的网址是否有效
    if(!QUrl(pGetJsUrl).isValid()){
        qDebug() << "is not valid.";
        QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("输入的网址无效！"),\
                                                       QString::fromLocal8Bit("确定"), 0);
    }
}

void web_forensics::DisplayCurrentTime()
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString strTime = QString::fromLocal8Bit("当前时间") +  currentTime;
    //ui->label_time->setText(strTime);
    //ui->label_time->setStyleSheet("color:red;");
}

void web_forensics::JumpUrl(void)
{
//    QUrl url = ui->lineEdit->text();
//    if (!url.isEmpty())
//    {
//        m_webView->load(url);
//        pLog->FromBaiDuJumpUrl(WebRecord, FileLogName,url.toEncoded());
//    }
}

void web_forensics::ReloadUrl(void)
{
    m_webView->reload();
}

void web_forensics::BackUrl(void)
{
    m_webView->back();
}

void web_forensics::LoadWebOver(bool tmp)
{
    qDebug()<<"bool:"<<tmp;
    if(tmp == true)
    {
        FullScreenShoot();
    }
}

void web_forensics::FileUpload()
{
//    if(pCloseFlag == 1)
//    {
//        pCloseFlag = 2;
//        this->close();  //关闭子窗口
//    }
//    else
//    {
//        QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请先进行取证"),\
//                                                       QString::fromLocal8Bit("确定"), 0);
//    }

}

void web_forensics::FullScreenShoot()
{
    DialogProgressDeal();
    m_webView->setAttribute(Qt::WA_DontShowOnScreen);

    //注意：Q5.10以上版本才引入QWebEngineSettings::ShowScrollBars
    m_webView->page()->settings()->setAttribute(QWebEngineSettings::ShowScrollBars, false);
    m_webView->show();

    QSize size = m_webView->page()->contentsSize().toSize();
    m_webView->resize(size);
    QTimer::singleShot(1200, this, SLOT(FullScreenSave()));
}

void web_forensics::FullScreenSave()
{
    QString filePath = pLog->FileDirPath(WebRecord);

//    if(!pFilePathName.isNull()) //删除多余文件
//    {
//        QString strFileName = filePath + pFilePathName;
//        pcom->RemoveOverageFile(strFileName);
//    }

    QString getTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz");
    QString filePathName = "web-" + getTime + ".png";
    QString fileFullPathName = filePath + filePathName;   
    pLog->isDirExist(filePath);
    m_webView->grab().save(fileFullPathName, "PNG");
    pLog->SaveForensicsLog(WebRecord,FileLogName);

    pFilePathName = filePathName;
    QString strRenameFile = pLog->RenameLogFile(WebRecord,FileLogName);
    pLog->RemoveWebLogFile(WebRecord,FileLogName);
    BufferFileName[0] = pFilePathName;
    BufferFileName[1] = strRenameFile;
    WebUploadFile(BufferFileName,2);
}

void web_forensics::OnUrlChanged(QUrl url)
{
    pLog->WebJumpUrl(WebRecord, FileLogName,url.toEncoded());
    //ui->lineEdit->setText(url.toEncoded());
}

void web_forensics::RecvMsgClose()
{
    qDebug()<<"RecvMsgClose";
    this->close();//关闭窗口界面
}

void web_forensics::closeEvent(QCloseEvent *event)
{
    QString strDirPath = pLog->FileDirPath(WebRecord);
    QJsonObject obj;
    switch(pCloseFlag)
    {
        case 1:obj.insert("strBranch", "token");break;
        case 2:obj.insert("strBranch", "cancel");break;
        default:obj.insert("strBranch", "unknow");break;
    }
    obj.insert("strMain", "GetWebDate");
    obj.insert("str", getStrMsg);
    obj.insert("path", strDirPath);
    obj.insert("hostIp", pGetHostIp);
    obj.insert("ipAddress", pIpAddress);
    obj.insert("macAddress", pMacAddress);
    obj.insert("osVersion", pOsVersion);
    QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    QString strJson(byteArray);
    emit SigSendMessageToJS(strJson,"","");
    switch(pCloseFlag)
    {
        case 1:pGetDirPath = "";pLog->CommunicationWriteLog("GetWebDate","token",strJson);break;
        case 2:{
            pLog->CommunicationWriteLog("GetWebDate","cancel",getStrMsg);
            pLog->RemoveDirFile(strDirPath);
            pGetDirPath = strDirPath;
        }break;
        default:break;
    }
    pCloseFlag = 0;
    event->accept();
    emit SendMsgCloseWnd(WebRecord);
}

void web_forensics::DialogProgressDeal()
{
    DialogProgressInit();
    timerProgress = new QTimer(this);
    connect(timerProgress, SIGNAL(timeout()), this, SLOT(DialogProgressTime()));
    timerProgress->start(1000);
}

void web_forensics::DialogProgressInit()
{
    progressDialog=new QProgressDialog(this);   
    progressDialog->setWindowModality(Qt::WindowModal); //设置进度对话框采用模态方式进行，即显示进度的同时，其他窗口将不响应输入信号
    progressDialog->setMinimumDuration(5);  //设置进度对话框出现需等待的时间，默认为4s
    progressDialog->setWindowTitle(QStringLiteral("请稍等"));  //设置进度对话框的窗体标题
    progressDialog->setLabelText(QStringLiteral("正在保存网页..."));  //设置进度对话框的显示文字信息
    //设置进度对话框的“取消”按钮的显示文字
    progressDialog->setRange(0,0);     //设置进度对话框的步进范围
    progressDialog->setCancelButton(0);//隐藏取消按钮
    progressDialog->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    progressDialog->show();
}

void web_forensics::DialogProgressTime()
{
    timecount++;
}

void web_forensics::DialogProgressStop()
{
    timecount = 0;
    timerProgress->stop();
    delete progressDialog;
    return;
}

void web_forensics::WebUploadFile(QString *filename,int num)
{
    QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QString formData = "form-data; name=\"file\";filename=";

    Common *pcom = NULL;
    QString strDirPath = pcom->FileDirPath(WebRecord);
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

void web_forensics::replyFinished(QNetworkReply*)    //删除指针，更新和关闭文件
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
            int result = QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("网页取证成功，立即上链？"),\
                                               QString::fromLocal8Bit("确定"), QString::fromLocal8Bit("取消"));
            if (result == 0)
            {
                getStrMsg = str;
                pCloseFlag = 1;
            }
            else
            {
                pCloseFlag = 2;
            }
        }
        else
        {
            //上传服务器失败
            QMessageBox::warning(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("网页上传失败，请重新取证！"),\
                                               QString::fromLocal8Bit("确定"), 0);
        }
    }
    else
    {
        QMessageBox::warning(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("网页上传失败，请重新取证！"),\
                                           QString::fromLocal8Bit("确定"), 0);
    }
    emit SendMsgClose();
}

void web_forensics::loadError(QNetworkReply::NetworkError)    //传输中的错误输出
{
     qDebug()<<"Error: "<<reply->error();
}
