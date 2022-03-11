#include "camera.h"
#include "ui_camera.h"
#include "Common/common.h"
#include "Common/networkclean.h"
#include <QUrl>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include "opencv2/opencv.hpp"
#include "Common/logrecord.h"

Camera::Camera(QWidget *parent) :
    QMainWindow(parent),    
    ui(new Ui::Camera)
{
    ui->setupUi(this);

}

Camera::~Camera()
{
    delete capture;
    delete ui;
}

void Camera::InitPhotographUi()
{
    m_isRun = false;
    timecount = 0;
    pCloseFlag = 0;
    pStopFlag = 0;
    pTimeoutFlag = 0;

    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString strTime = QString::fromLocal8Bit("当前时间") +  currentTime;
    ui->label_currenttime->setText(strTime);
    ui->label_tip->setText(QString::fromLocal8Bit("提示：正在进行拍摄取证，请在本窗口进行取证"));
    ui->label->setText(QString::fromLocal8Bit("待取证"));
    ui->label_point->setText(QString::fromLocal8Bit("提示：一次录制时长最多10分钟"));

    ui->label_currenttime->setStyleSheet("color:red;");
    ui->label_tip->setStyleSheet("color:red;");
    ui->label->setStyleSheet("color:red;");
    ui->label_display->setText("");

    pCurrentTime = new QTimer(this);
    connect(pCurrentTime, SIGNAL(timeout()), this, SLOT(DisplayCurrentTime()));
    pCurrentTime->start(100);

    connect(ui->BtnStart, SIGNAL(clicked()), this, SLOT(StartRecordVideo()));
    connect(ui->BtnReload, SIGNAL(clicked()), this, SLOT(ReloadRecordVideo()));
    connect(ui->BtnUpload, SIGNAL(clicked()), this, SLOT(UploadRecordVideo()));
    connect(this,SIGNAL(StopRecordVideoSignal()),this,SLOT(StopRecordVideo()));

//    connect(ui->BtnStart, SIGNAL(clicked()), this, SLOT(StartRecordVideo1()));
//    connect(ui->BtnReload, SIGNAL(clicked()), this, SLOT(StopRecordVideo1()));
}

void Camera::StartRecordVideo1(void)
{
    qDebug() << "StartRecordVideo.";
    capture = new VideoCapture(0);
    //capture->set(CAP_PROP_FOURCC,cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
    //判断是否出错
    if (!capture->isOpened()){return;}
    double  frameHeight = capture->get(CAP_PROP_FRAME_HEIGHT);
    double frameWidth = capture->get(CAP_PROP_FRAME_WIDTH);

    double fps = capture->get(CAP_PROP_FPS);
    int fourcc = capture->get(CAP_PROP_FOURCC);
    qDebug()<<"fps:"<<fps<<"fourcc:"<<fourcc;

    //定义writer对象
    outputVideo = new VideoWriter;
    int failFps = 30;
    outputVideo->open("TestVideo.avi", outputVideo->fourcc('M', 'J', 'P', 'G'), failFps, Size(frameWidth, frameHeight), true);
    //outputVideo->open("TestVideo.avi", outputVideo->fourcc('U', '2', '6', '3'), fps, Size(frameWidth, frameHeight), true);

    //判断open writer对象是否出错
    if (!outputVideo->isOpened()){return;}

    m_isRun     = true;
    InitTimeTasks();

    timer = new QTimer();
    timer->setInterval(8);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(RecordTime1()));
}

void Camera::RecordTime1(void)
{
    frameImg = new Mat;
    capture->read(*frameImg);
    //判断是否读完
    if (!frameImg->empty())
    {
        QImage image = cvMat2QImage(*frameImg);
        ui->label_display->setPixmap(QPixmap::fromImage(image));

        outputVideo->write(*frameImg);
    }
    delete frameImg;
    return;
}

void Camera::StopRecordVideo1(void)
{
    qDebug() << "StopRecordVideo.";
    count_timer->stop();
    timer->stop();
    capture->release();
    outputVideo->release();
    delete outputVideo;
    delete timer;
}

void Camera::DisplayCurrentTime()
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString strTime = QString::fromLocal8Bit("当前时间") +  currentTime;
    ui->label_currenttime->setText(strTime);
    ui->label_currenttime->setStyleSheet("color:red;");
}

void Camera::OpenPhotographWeb(void)
{
    OpenVideo();    //打开摄像头
}

void Camera::ClosePhotograph(void)
{
    capture->release();
}

void Camera::ShowMaximized(void)
{
    setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen))
                   | Qt::WindowMaximized);
    show();
}

void Camera::StartRecordVideo(void)
{
    if(pStopFlag == 0)
    {
        if (!m_isRun)
        {
            //删除刚录取的视频和音频文件
            RemoveFile(FileVideoName);
            RemoveFile(pAudioName);

            ui->BtnStart->setText(QString::fromLocal8Bit("停止取证"));
            ui->BtnReload->setEnabled(false);
            ui->BtnUpload->setEnabled(false);
            ui->BtnReload->setStyleSheet("QPushButton{background-image: url(:/new/prefix1/Icon/button_gray.png);border-style: none;padding-left: 8px;padding-top: 8px;padding-right: 8px;padding-bottom: 8px;color:white;}");
            ui->BtnUpload->setStyleSheet("QPushButton{background-image: url(:/new/prefix1/Icon/button_gray.png);border-style: none;padding-left: 8px;padding-top: 8px;padding-right: 8px;padding-bottom: 8px;color:white;}");
            //生成视频文件
            m_isRun     = true;
            pCloseFlag = 1;
            InitTimeTasks();

            Common *pcom = NULL;
            QString filePath = pcom->FileDirPath(CameraRecord);
            //开始录取音屏
            m_Audio = new Audio();
            m_Audio->AudioInit(filePath);
            m_Audio->OnRecordStart(2);
            WriteToVideo();
        }
        else
        {
            emit StopRecordVideoSignal();
        }
    }
}

void Camera::StopRecordVideo(void)
{
    qDebug() << "StopRecordVideo.";
    m_isRun = false;
    pCloseFlag = 2;
    pStopFlag = 1;
    timer->stop();
    count_timer->stop();
    outputVideo->release();
    delete outputVideo;
    delete timer;
    //关闭音屏
    Common *pcom = NULL;
    QString filePath = pcom->FileDirPath(CameraRecord);
    m_Audio->OnRecordSave(filePath);
    delete m_Audio;

    QString strWav = filePath + pAudioName;
    QString strAvi = filePath + FileVideoName;
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

    ui->BtnStart->setEnabled(false);
    ui->BtnReload->setEnabled(true);
    ui->BtnUpload->setEnabled(true);
    ui->BtnStart->setStyleSheet("QPushButton{background-image: url(:/new/prefix1/Icon/button_gray.png);border-style: none;padding-left: 8px;padding-top: 8px;padding-right: 8px;padding-bottom: 8px;color:white;}");
    ui->BtnReload->setStyleSheet("QPushButton{background-image: url(:/new/prefix1/Icon/button.png);border-style: none;padding-left: 8px;padding-top: 8px;padding-right: 8px;padding-bottom: 8px;color:white;}");
    ui->BtnUpload->setStyleSheet("QPushButton{background-image: url(:/new/prefix1/Icon/button.png);border-style: none;padding-left: 8px;padding-top: 8px;padding-right: 8px;padding-bottom: 8px;color:white;}");
}

void Camera::StartMplayerCompress(QString wav, QString avi, QString outName)
{
    QString program = QCoreApplication::applicationDirPath() + "/ffmpeg/ffmpeg.exe";
    pProcess = new QProcess;
    connect(pProcess, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &Camera::MplayerCompressFinished);

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

void Camera::MplayerCompressFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if(pProcess) {
        pProcess->close();
    }
    delete pProcess;

    //上传文件服务器
    BufferFileName[0] = getNameMp4;
    CameraUploadFile(BufferFileName,1);
    Common *pcom = NULL;
    QString filePath = pcom->FileDirPath(CameraRecord);
    QString strWav = filePath + pAudioName;
    QString strAvi = filePath + FileVideoName;
    QString strRaw = filePath + "record.raw";
    pcom->RemoveOverageFile(strWav);
    pcom->RemoveOverageFile(strAvi);
    pcom->RemoveOverageFile(strRaw);
}

//上传取证
void Camera::UploadRecordVideo(void)
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

//重新取证
void Camera::ReloadRecordVideo(void)
{
    Common *pcom = NULL;
    QString filePath = pcom->FileDirPath(CameraRecord);
    if (m_isRun)        //如果是正在录取状态
    {
        ui->BtnStart->setText(QString::fromLocal8Bit("开始取证"));
        emit StopRecordVideoSignal(); //关闭定时器
        QString strRaw = filePath + "record.raw";
        pcom->RemoveOverageFile(strRaw);
    }

    //删除刚录取的视频和音频文件
    if(QString::compare(getNameMp4,"")) //删除多余文件
    {
        QString strDelete = filePath + getNameMp4;
        pcom->RemoveOverageFile(strDelete);
    }
    pcom->RemoveOverageFile(pAudioName);
    pcom->RemoveOverageFile(FileVideoName);

    m_isRun     = true;
    pCloseFlag = 1;
    pStopFlag = 0;
    WriteToVideo();
    InitTimeTasks();
    ui->BtnStart->setText(QString::fromLocal8Bit("停止取证"));

    //开始录取音屏
    m_Audio = new Audio();
    m_Audio->AudioInit(filePath);
    m_Audio->OnRecordStart(2);

    ui->BtnStart->setEnabled(true);
    ui->BtnReload->setEnabled(false);
    ui->BtnUpload->setEnabled(false);
    ui->BtnStart->setStyleSheet("QPushButton{background-image: url(:/new/prefix1/Icon/button.png);border-style: none;padding-left: 8px;padding-top: 8px;padding-right: 8px;padding-bottom: 8px;color:white;}");
    ui->BtnReload->setStyleSheet("QPushButton{background-image: url(:/new/prefix1/Icon/button_gray.png);border-style: none;padding-left: 8px;padding-top: 8px;padding-right: 8px;padding-bottom: 8px;color:white;}");
    ui->BtnUpload->setStyleSheet("QPushButton{background-image: url(:/new/prefix1/Icon/button_gray.png);border-style: none;padding-left: 8px;padding-top: 8px;padding-right: 8px;padding-bottom: 8px;color:white;}");
}

//关闭窗口事件，关闭窗口首先需要判断定时器是否关闭了
void Camera::closeEvent(QCloseEvent *event)
{
    if (pCloseFlag != 4)
    {
        int result = QMessageBox::question(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("文件还未上传，<br>是否退出当前窗口？"),\
                                           QString::fromLocal8Bit("确定"), QString::fromLocal8Bit("取消"),0);

        if (result == 0)
        {
            if(m_isRun)
            {
                QMessageBox::warning(this,QString::fromLocal8Bit("消息"),QString::fromLocal8Bit("关闭窗口前，请先停止取证！"),QString::fromLocal8Bit("确定"));
                event->ignore();
                return;
            }
            pCurrentTime->stop();
            delete pCurrentTime;
            pCloseFlag = 0;
            Common *pCommon = NULL;
            QString strDirPath = pCommon->FileDirPath(CameraRecord);
            QJsonObject obj;
            obj.insert("strMain", "GetCameraDate");
            obj.insert("strBranch", "cancel");
            obj.insert("str", "cancel");
            obj.insert("path", strDirPath);
            obj.insert("hostIp", pGetHostIp);
            QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
            QString strJson(byteArray);

            pCommon->CommunicationWriteLog("GetCameraDate","cancel","cancel");
            emit SigSendMessageToJS(strJson,"","");
            capture->release();
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
        pCurrentTime->stop();
        pCloseFlag = 0;
        Common *pCommon = NULL;
        QString strDirPath = pCommon->FileDirPath(CameraRecord);
        QJsonObject obj;
        obj.insert("strMain", "GetCameraDate");
        obj.insert("strBranch", "token");
        obj.insert("str", getStrMsg);
        obj.insert("path", strDirPath);
        obj.insert("hostIp", pGetHostIp);
        obj.insert("ipAddress", pIpAddress);
        obj.insert("macAddress", pMacAddress);
        obj.insert("osVersion", pOsVersion);
        QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
        QString strJson(byteArray);
        pCommon->CommunicationWriteLog("GetCameraDate","token",strJson);
        emit SigSendMessageToJS(strJson,"","");
        capture->release();
    }
    emit SendMsgCloseWnd(CameraRecord);
}


void Camera::DialogProgressDeal()
{
    DialogProgressInit();
    timerProgress = new QTimer(this);
    connect(timerProgress, SIGNAL(timeout()), this, SLOT(DialogProgressTime()));
    timerProgress->start(1000);
}

void Camera::DialogProgressInit()
{
    progressDialog=new QProgressDialog(this);
    progressDialog->setWindowModality(Qt::WindowModal); //设置进度对话框采用模态方式进行，即显示进度的同时，其他窗口将不响应输入信号
    progressDialog->setMinimumDuration(5);  //设置进度对话框出现需等待的时间，默认为4s
    progressDialog->setWindowTitle(QStringLiteral("请稍等"));  //设置进度对话框的窗体标题
    progressDialog->setLabelText(QStringLiteral("正在保存视频文件..."));  //设置进度对话框的显示文字信息
    //设置进度对话框的“取消”按钮的显示文字
    progressDialog->setRange(0,0);     //设置进度对话框的步进范围
    progressDialog->setCancelButton(0);//隐藏取消按钮
    progressDialog->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    progressDialog->show();
}

void Camera::DialogProgressTime()
{
    timecount++;
}

void Camera::DialogProgressStop()
{
    timecount = 0;
    timerProgress->stop();
    delete progressDialog;
    return;
}

void Camera::CameraUploadFile(QString *filename,int num)
{
    QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QString formData = "form-data; name=\"file\";filename=";

    Common *pcom = NULL;
    QString strDirPath = pcom->FileDirPath(CameraRecord);
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

void Camera::replyFinished(QNetworkReply*)    //删除指针，更新和关闭文件
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
                result = QMessageBox::warning(NULL,QString::fromLocal8Bit("消息"),QString::fromLocal8Bit("停止拍摄，录制时长不能超过10分钟，<br>已为您保存录制内容。"),\
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

void Camera::loadError(QNetworkReply::NetworkError)    //传输中的错误输出
{
     qDebug()<<"Error: "<<reply->error();
}

void Camera::InitTimeTasks(void)
{
    count_timer = new QTimer();
    connect(count_timer, SIGNAL(timeout()), this, SLOT(DisplayTime()));
    count_timer->start(1000);
    pCountTime = 0;
}

void Camera::DisplayTime(void)
{
    if (m_isRun)
    {
        pCountTime++;
        int hour_h = 0, hour_l = 0, minute_h = 0,minute_l = 0,second_h = 0,second_l = 0;
        if(pCountTime < 10 && pCountTime > 0)
        {
            second_l = pCountTime % 10;
        }
        else if(pCountTime < 60 && pCountTime >= 10)
        {
            second_l = pCountTime % 10;
            second_h = (pCountTime % 60) / 10;
        }
        else if(pCountTime < 600 && pCountTime >= 60)
        {
            second_l = pCountTime % 10;
            second_h = (pCountTime % 60) / 10;
            minute_l = (pCountTime % 600) / 60;
        }
        else if(pCountTime < 3600 && pCountTime >= 600)
        {
            second_l = pCountTime % 10;
            second_h = (pCountTime % 60) / 10;
            minute_l = (pCountTime % 600) / 60;
            minute_h = (pCountTime % 3600) / 600;
        }
        else if(pCountTime >= 3600)
        {
            hour_l = 1;
        }
        hour_h = 0;

        QString display_time = QString::fromLocal8Bit("取证时长：");
        QString time_count = QString("%1%2:%3%4:%5%6").arg(hour_h).arg(hour_l).arg(minute_h).arg(minute_l).arg(second_h).arg(second_l);
        display_time = display_time + time_count;
        ui->label->setText(display_time);

        if ((minute_h >= 1) && (minute_l >= 0)) //如果超过10分钟，则弹框并关闭定时器
        {
            pTimeoutFlag = 1;
            emit StopRecordVideoSignal(); //关闭定时器
        }
    }
}

void Camera::RemoveFile(QString fileName)
{
    Common *pcom = NULL;
    QString getPath = pcom->FileDirPath(CameraRecord);
    QString filePath = getPath + fileName;
    qDebug() << filePath;
    //判断路径是否存在
    QFileInfo fileInfo(filePath);
    if(!fileInfo.exists()){
        qDebug() << "it is not exists.";
        return;
    }

    QFile fileTemp(filePath);
    fileTemp.remove();
}

void Camera::OpenVideo(void)
{
    //打开本地摄像头
    capture = new VideoCapture(0,CAP_DSHOW);
    //设置的值如果大于编辑框大小，录取的视频就会变快
    capture->set(CAP_PROP_FRAME_WIDTH, 800);  //max:960; normal:640
    capture->set(CAP_PROP_FRAME_HEIGHT, 450);  //max:540; normal:480
    if (!capture->isOpened()){
        QMessageBox::warning(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("摄像头打开失败！"),QString::fromLocal8Bit("确定"),0);
        return;
    }
}

void Camera::WriteToVideo(void)
{
    //判断是否出错
    if (!capture->isOpened()){return;}
    double  frameHeight = capture->get(CAP_PROP_FRAME_HEIGHT);
    double frameWidth = capture->get(CAP_PROP_FRAME_WIDTH);
    qDebug() << "frameHeight : " << frameHeight;
    qDebug() << "frameWidth : " << frameWidth;
    qDebug() << "frameHeight1 : " << ui->label_display->size().height();
    qDebug() << "frameWidth2 : " << ui->label_display->size().width();

    Common *pcom = NULL;
    QString filePath = pcom->FileDirPath(CameraRecord);
    QString getTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz");
    QString filePathName = "Video-" + getTime + ".avi";
    FileVideoName = filePathName;
    QString fileFullPathName = filePath + filePathName;
    pcom->isDirExist(filePath);

    double fps = capture->get(CAP_PROP_FPS);//默认是30fps
    qDebug()<<"fps:"<<fps;
    outputVideo = new VideoWriter;
    //间隔33ms
    //outputVideo->open(fileFullPathName.toLocal8Bit().toStdString(), outputVideo->fourcc('M', 'J', 'P', 'G'), 18, Size(frameWidth, frameHeight), true);
    outputVideo->open(fileFullPathName.toLocal8Bit().toStdString(), outputVideo->fourcc('M', 'J', 'P', 'G'), 30, Size(frameWidth, frameHeight), true);

    //判断open writer对象是否出错
    if (!outputVideo->isOpened()){return;}
    int rate = 1000/fps;
    qDebug()<<"rate:"<<rate;
    QString strRate = QString("fps:%1").arg(rate);
    LogRecord wLog;
    wLog.LogTrack(strRate);

    timer = new QTimer();
    //timer->setInterval(6);
    //timer->setInterval(8);
    timer->setInterval(8);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(RecordTime()));
}

void Camera::RecordTime(void)
{
    frameImg = new Mat;
    capture->read(*frameImg);

    //判断是否读完
    if (!frameImg->empty())
    {
        QImage image = cvMat2QImage(*frameImg);
        image.scaled(ui->label_display->size(), Qt::KeepAspectRatio);//图片自适应
        ui->label_display->setScaledContents(true);
        ui->label_display->setPixmap(QPixmap::fromImage(image));
        outputVideo->write(*frameImg);
    }

    delete frameImg;
    return;
}

void Camera::ImageVideo(void)
{
    cv::Mat mat = cv::imread("F:\\QT\\code\\build-opecvmingw-Desktop_Qt_5_9_9_MinGW_32bit-Release\\release\\IMG_00000003.jpg", cv::IMREAD_UNCHANGED);
    cv::cvtColor(mat, mat, COLOR_BGR5652RGB);
    QImage image = cvMat2QImage(mat);
    namedWindow("hello", WINDOW_AUTOSIZE);
    imshow("cvMat2QImage gray", mat);
    QLabel label;
    label.setPixmap(QPixmap::fromImage(image));
    //cv::waitKey(10000);
}

QImage Camera::cvMat2QImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        qDebug() << "CV_8UC1";
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

cv::Mat Camera::QImage2cvMat(QImage image)
{
    cv::Mat mat;
    //qDebug() << image.format();
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, COLOR_BGR2HSV);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    return mat;
}

