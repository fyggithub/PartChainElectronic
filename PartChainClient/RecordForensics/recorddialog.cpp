#include "recorddialog.h"
#include "ui_recorddialog.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include "Common/common.h"
#include "Common/widget.h"
#include "head.h"
#include "mywin.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QRect>

RecordDialog::RecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordDialog)
{
    ui->setupUi(this);

    pRecordDialogFlag = 0;
    timecount = 0;
    pCloseFlag = 0;
    pTimeoutFlag = 0;
    getStrMsg = "";
    getNameMp4 = "";
    m_isRun = false;
    timer   = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(RecordTime()));
    timer->start(1000);

    QDesktopWidget *desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();
    int screenWidth = screen.width();
    int screenHeight = screen.height();
    qDebug()<<"screenWidth:"<<screenWidth<<screenHeight;
    setGeometry(QRect(screenWidth-360, screenHeight-280, 260, 180));

    Qt::WindowFlags wndFlag = Qt::Dialog | Qt::FramelessWindowHint |Qt::CustomizeWindowHint | Qt::WindowShadeButtonHint | Qt::WindowStaysOnTopHint;
    setWindowFlags(wndFlag);
    ui->minBtn->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));
    ui->closeBtn->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    ui->minBtn->setFlat(true);
    ui->closeBtn->setFlat(true);
    connect(ui->minBtn, SIGNAL(clicked(bool)), this, SLOT(onMinClicked()));
    connect(ui->closeBtn, SIGNAL(clicked(bool)), this, SLOT(onCloseClicked()));

    ui->startBtn->setStyleSheet("QPushButton{border-top:0px solid #e8f3f9;background:  transparent;}"
                                 "QPushButton:pressed{border:2px solid white;border-radius:10px;}"
                                 );
    ui->stopBtn->setStyleSheet("QPushButton{border-top:0px solid #e8f3f9;background:  transparent;}"
                                 "QPushButton:pressed{border:2px solid white;border-radius:10px;}"
                                 );
    ui->uploadBtn->setStyleSheet("QPushButton{border-top:0px solid #e8f3f9;background:  transparent;}"
                                 "QPushButton:pressed{border:2px solid white;border-radius:10px;}"
                                 );
    ui->startBtn->setToolTip(QString::fromLocal8Bit("开始"));
    ui->stopBtn->setToolTip(QString::fromLocal8Bit("停止"));
    ui->uploadBtn->setToolTip(QString::fromLocal8Bit("上传"));

    ui->label_circle->setText("");
    ui->label_point->setText(QString::fromLocal8Bit("提示：1、如果有需要请使用客户端提供的浏览器\n      2、录屏取证一次最长15分钟"));
    ui->label_point->setStyleSheet("color:red;");

    QFont ft;
    ft.setPointSize(10);
    ui->label_time->setFont(ft);
    ui->label_time->setText(QString::fromLocal8Bit("录制时长：00:00:00"));
    ui->label_time->setStyleSheet("color:red;");

    connect(ui->startBtn,SIGNAL(clicked()),this,SLOT(StartButtonClicked()));
    connect(ui->stopBtn,SIGNAL(clicked()),this,SLOT(StopButtonClicked()));
    connect(ui->uploadBtn,SIGNAL(clicked()),this,SLOT(FileUpload()));
    connect(this,SIGNAL(StopTimeSignal()),this,SLOT(StopButtonClicked()));
}

RecordDialog::~RecordDialog()
{
    delete ui;
}

void RecordDialog::onMinClicked()
{
    this->showMinimized();
}

void RecordDialog::onCloseClicked()
{
    this->close();
}

void RecordDialog::StartButtonClicked()
{
    if(pCloseFlag != 1){
        m_isRun     = true;
        pCloseFlag = 1;
        m_timeStart = QDateTime::currentDateTime();

        QImage *img = new QImage; //新建一个image对象
        img->load(":/new/prefix1/Icon/circle.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
        ui->label_circle->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
        delete img;

        CameraInit();
        CameraStart();

        Common *pcom = NULL;
        QString filePath = pcom->FileDirPath(VideoRecord);
        m_Audio = new Audio();
        m_Audio->AudioInit(filePath);
        m_Audio->OnRecordStart(1);
    }
    else{
        QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请先停止取证"),\
                                                       QString::fromLocal8Bit("确定"), 0);
    }
}

void RecordDialog::StopButtonClicked()
{
    if(pCloseFlag == 1)
    {
        ui->label_circle->clear();
        m_isRun = false;
        CameraStop();
        Common *pcom = NULL;
        QString filePath = pcom->FileDirPath(VideoRecord);
        m_Audio->OnRecordSave(filePath);
        delete m_Audio;
        pCloseFlag = 2;

        QString strWav = filePath + pAudioName;
        QString strAvi = filePath + pRecordVideoName;
        QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz");
        QString nameMp4 = "mplayer" + currentTime + ".mp4";
        QString strMp4 = filePath + nameMp4;
        if(QString::compare(getNameMp4,"")) //删除多余文件
        {
            QString strDelete = filePath + getNameMp4;
            pcom->RemoveOverageFile(strDelete);
        }
        getNameMp4 = nameMp4;
        StartMplayerCompress(strWav, strAvi, strMp4);
        DialogProgressDeal();
    }
    else
    {
        QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请先点击开始按钮"),\
                                                       QString::fromLocal8Bit("确定"), 0);
    }
}

//关闭窗口事件，关闭窗口首先需要判断定时器是否关闭了
void RecordDialog::closeEvent(QCloseEvent *event)
{
    qDebug()<<"pCloseFlag:"<<pCloseFlag;
    if (pCloseFlag != 4)
    {
        int result = QMessageBox::question(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("文件还未上传，<br>是否退出当前窗口？"),\
                                           QString::fromLocal8Bit("确定"), QString::fromLocal8Bit("取消"),0);

        if (result == 0)
        {
            if(m_isRun)
            {
                QMessageBox::warning(this,QString::fromLocal8Bit("消息"),QString::fromLocal8Bit("关闭窗口前，请先停止取证！"),\
                                        QString::fromLocal8Bit("确定"),0);
                event->ignore();
                return;
            }
            pCloseFlag = 0;
            Common *pCommon = NULL;
            QString strDirPath = pCommon->FileDirPath(VideoRecord);
            QJsonObject obj;
            obj.insert("strMain", "GetRecordDate");
            obj.insert("strBranch", "cancel");
            obj.insert("str", "cancel");
            obj.insert("path", strDirPath);
            obj.insert("hostIp", pGetHostIp);
            QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
            QString strJson(byteArray);

            pCommon->CommunicationWriteLog("GetRecordDate","cancel","cancel");
            emit SigSendMessageToJS(strJson,"","");
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
        Common *pCommon = NULL;
        QString strDirPath = pCommon->FileDirPath(VideoRecord);
        QJsonObject obj;
        obj.insert("strMain", "GetRecordDate");
        obj.insert("strBranch", "token");
        obj.insert("str", getStrMsg);
        obj.insert("path", strDirPath);
        obj.insert("hostIp", pGetHostIp);
        obj.insert("ipAddress", pIpAddress);
        obj.insert("macAddress", pMacAddress);
        obj.insert("osVersion", pOsVersion);
        QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
        QString strJson(byteArray);
        pCommon->CommunicationWriteLog("GetRecordDate","token",strJson);
        emit SigSendMessageToJS(strJson,"","");
        if(m_isRun)
        {
            emit StopTimeSignal(); //关闭定时器
        }
    }
    emit SendMsgCloseWnd(VideoRecordDialog);
}

void RecordDialog::RecordTime()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    if (m_isRun)
    {
        qint64 start = m_timeStart.secsTo(currentTime);
        int hour_h = 0, hour_l = 0, minute_h = 0,minute_l = 0,second_h = 0,second_l = 0;
        second_l = start % 10;
        second_h = (start % 60) / 10;
        minute_l = (start % 600) / 60;
        minute_h = (start % 3600) / 600;
        hour_l = (start / 3600);
        hour_h = 0;
        QString display_time = QString::fromLocal8Bit("录制时长：");
        QString time_count = QString("%1%2:%3%4:%5%6").arg(hour_h).arg(hour_l).arg(minute_h).arg(minute_l).arg(second_h).arg(second_l);
        display_time = display_time + time_count;

        if((minute_h == 1) && (minute_l == 4) && (second_h == 0) && (second_l == 0)){//最后一分钟窗口弹出
            if(isMinimized()){
                qDebug()<<"is Minimized.";
                showNormal();
            }
            activateWindow();
        }

        if ((minute_h >= 1) && (minute_l >= 5) && (second_l > 0)) //如果超过15分钟，则弹框并关闭定时器
        {
            if(isMinimized()){
                qDebug()<<"is Minimized.";
                showNormal();
            }
            activateWindow();

            pTimeoutFlag = 1;
            emit StopTimeSignal(); //关闭定时器
            return;
        }
        ui->label_time->setText(display_time);
        ui->label_time->setStyleSheet("color:red;");
    }
}

void RecordDialog::StartMplayerCompress(QString wav, QString avi, QString outName)
{
    QString program = QCoreApplication::applicationDirPath() + "/ffmpeg/ffmpeg.exe";
    qDebug() << program;

    pProcess = new QProcess;
    connect(pProcess, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &RecordDialog::MplayerCompressFinished);

    QStringList arguments;
    if(!wav.isEmpty())
    {
        arguments << "-i" << wav << "-i" << avi << outName;//传递到exe的参数
    }
    else
    {
        //没有音频，只把avi转成MP4
        arguments << "-i" << avi << "-vcodec" << "mpeg4" << outName;
    }
    pProcess->start(program, arguments);
}

void RecordDialog::MplayerCompressFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if(pProcess) {
        pProcess->close();
    }
    delete pProcess;

    //上传文件服务器
    BufferFileName[0] = getNameMp4;
    RecordVideoUploadFile(BufferFileName, 1);

    Common *pcom = NULL;
    QString filePath = pcom->FileDirPath(VideoRecord);
    QString strWav = filePath + pAudioName;
    QString strAvi = filePath + pRecordVideoName;
    QString strRaw = filePath + "record.raw";
    //pcom->RemoveOverageFile(strWav);
    //pcom->RemoveOverageFile(strAvi);
    pcom->RemoveOverageFile(strRaw);
}

void RecordDialog::FileUpload(void)
{
    switch(pCloseFlag){
    case 0:{
        QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请先进行取证"),\
                                                       QString::fromLocal8Bit("确定"), 0);
    }break;
    case 1:{
        QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("正在录取视频取证，<br>请先停止取证"),\
                                                       QString::fromLocal8Bit("确定"), 0);
    }break;
    case 2:break;
    case 3:{
        pCloseFlag = 4;
        this->close();  //关闭子窗口
    }break;
    default:break;
    }
}

void RecordDialog::DialogProgressDeal()
{
    DialogProgressInit();
    timerProgress = new QTimer(this);
    connect(timerProgress, SIGNAL(timeout()), this, SLOT(DialogProgressTime()));
    timerProgress->start(1000);
}

void RecordDialog::DialogProgressInit()
{
    progressDialog=new QProgressDialog(this);
    progressDialog->setWindowModality(Qt::WindowModal); //设置进度对话框采用模态方式进行，即显示进度的同时，其他窗口将不响应输入信号
    progressDialog->setMinimumDuration(5);  //设置进度对话框出现需等待的时间，默认为4s
    progressDialog->setWindowTitle(QString::fromLocal8Bit("请稍等"));  //设置进度对话框的窗体标题
    progressDialog->setLabelText(QString::fromLocal8Bit("正在保存视频文件..."));  //设置进度对话框的显示文字信息
    progressDialog->setRange(0,0);     //设置进度对话框的步进范围
    progressDialog->setCancelButton(0);//隐藏取消按钮
    progressDialog->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    progressDialog->show();
}

void RecordDialog::DialogProgressTime()
{
    timecount++;
}

void RecordDialog::DialogProgressStop()
{
    timecount = 0;
    timerProgress->stop();
    delete progressDialog;
    return;
}

void RecordDialog::RecordVideoUploadFile(QString *filename,int num)
{
    QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QString formData = "form-data; name=\"file\";filename=";

    Common *pcom = NULL;
    QString strDirPath = pcom->FileDirPath(VideoRecord);
    for(int i = 0;i < num;i++)
    {
        QString filePath = strDirPath + filename[i];
        QFile *pfile = new QFile(filePath);
        pfile->open(QIODevice::ReadOnly);

        QHttpPart textPart;
        textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString(formData+filename[i])));
        textPart.setBodyDevice(pfile);
        pfile->setParent(multi_part);
        multi_part->append(textPart);
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

void RecordDialog::replyFinished(QNetworkReply*)    //删除指针，更新和关闭文件
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
            int result = 0;
            if(pTimeoutFlag == 1){
                pTimeoutFlag = 0;
                result = QMessageBox::warning(NULL,QString::fromLocal8Bit("消息"),QString::fromLocal8Bit("停止录屏，录制时长不能超过15分钟，<br>已为您保存录制内容。"),\
                                                    QString::fromLocal8Bit("确定"),0);
            }
            else{
                result = QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("视频文件保存成功"),\
                                                   QString::fromLocal8Bit("确定"), 0);
            }

            if (result == 0)
            {
                getStrMsg = str;
                pCloseFlag = 3;
            }
        }
        else
        {
            //上传服务器失败
            QMessageBox::warning(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("视频上传失败，<br>请再次上传取证！"),\
                                               QString::fromLocal8Bit("确定"), 0);
        }
    }
    else
    {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("视频上传失败，<br>请再次上传取证！"),\
                                                QString::fromLocal8Bit("确定"), 0);
    }
}

void RecordDialog::loadError(QNetworkReply::NetworkError)    //传输中的错误输出
{
     qDebug()<<"Error: "<<reply->error();
}


void RecordDialog::mousePressEvent(QMouseEvent *e)
{
    last=e->globalPos();
}
void RecordDialog::mouseMoveEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
        int dy = e->globalY() - last.y();
        last = e->globalPos();
        move(x()+dx, y()+dy);
}
void RecordDialog::mouseReleaseEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();
    move(x()+dx, y()+dy);
}
