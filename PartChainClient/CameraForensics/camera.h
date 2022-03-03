#ifndef CAMERA_H
#define CAMERA_H

#include <QMainWindow>

#include <QImage>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QCloseEvent>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QPixmap>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QMessageBox>

#include "audio.h"
#include "Common/common.h"
#include "Common/networkclean.h"

using namespace cv;

namespace Ui {
class Camera;
}

class Camera : public QMainWindow
{
    Q_OBJECT

public:
    explicit Camera(QWidget *parent = nullptr);
    ~Camera();

    void ShowMaximized(void);
    void InitCamera(void);
    void CameraUploadFile(QString *filename,int num);
    void OpenPhotographWeb(void);

    void ImageVideo(void);
    QImage cvMat2QImage(const cv::Mat& mat);
    cv::Mat QImage2cvMat(QImage image);

private:
    void OpenVideo(void);
    void WriteToVideo(void);
    void InitTimeTasks(void);
    void closeEvent(QCloseEvent *event);
    void DialogProgressInit();
    void DialogProgressStop();
    void DialogProgressDeal();
    void RemoveFile(QString fileName);
    void StartMplayerCompress(QString wav, QString avi, QString outName);

private slots:
    void StartRecordVideo1(void);
    void StopRecordVideo1(void);
    void RecordTime1(void);

    void StartRecordVideo(void);
    void StopRecordVideo(void);
    void ReloadRecordVideo(void);
    void UploadRecordVideo(void);
    void RecordTime(void);
    void DisplayTime(void);
    void replyFinished(QNetworkReply*);
    void loadError(QNetworkReply::NetworkError);
    void DialogProgressTime();
    void DisplayCurrentTime();
    void MplayerCompressFinished(int exitCode, QProcess::ExitStatus exitStatus);


signals:
    void StopRecordVideoSignal(void);
    void SigSendMessageToJS(QString strMain,QString type,QString str);
    void SendMsgCloseWnd(RecordType);

private:
    Ui::Camera *ui;
    VideoCapture *capture;
    Mat *frameImg;
    VideoWriter *outputVideo;
    QTimer *timer, *count_timer;
    QDateTime  m_timeStart;
    bool       m_isRun;
    Audio*     m_Audio;
    QNetworkReply *reply;
    QString BufferFileName[8];
    networkclean* pNetworkClean;
    QString FileVideoName;
    QString pFilePathName;
    QTimer* timerProgress;
    QTimer* pCurrentTime;
    QProgressDialog* progressDialog;
    int timecount;
    int pCountTime;
    int pCloseFlag;
    int pStopFlag;
    int pTimeoutFlag;
    QString getStrMsg;
    QProcess* pProcess;
    QString getNameMp4;
};

#endif // CAMERA_H
