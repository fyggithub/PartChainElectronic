#ifndef RECORDVIDEO_H
#define RECORDVIDEO_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QWebEngineView>
#include <QWebChannel>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QMessageBox>
#include "Common/jscommunicate.h"
#include "CameraForensics/audio.h"
#include "Common/common.h"
#include "Common/networkclean.h"


namespace Ui {
class RecordVideo;
}

class RecordVideo : public QMainWindow
{
    Q_OBJECT

public:
    explicit RecordVideo(QWidget *parent = nullptr);
    ~RecordVideo();

    QWebEngineView* m_RecordWebView;
    JSCommunicate *pJsComRecord;
    void OpenRecordVideoWeb(void);
    void ShowMaximized(void);
    void RecordVideoUploadFile(QString *filename,int num);
    void DialogProgressInit();
    void DialogProgressStop();
    void DialogProgressDeal();
    void StartMplayerCompress(QString wav, QString avi, QString outName);

signals:
    void StopTimeSignal();
    void SigSendMessageToJS(QString strMain,QString type,QString str);
    void SendMsgCloseWnd(RecordType);

private slots:
    void JumpUrl(void);
    void ReloadUrl(void);
    void BackUrl(void);
    void StartButtonClicked();
    void StopButtonClicked();
    void RecordTime();
    void OnUrlChanged(QUrl url); // 测试 urlChanged信号，该信号由 load(QUrl) 触发
    void FileUpload(void);
    void replyFinished(QNetworkReply*);
    void loadError(QNetworkReply::NetworkError);
    void DialogProgressTime();
    void DisplayCurrentTime();
    void MplayerCompressFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    QTimer*    timer;
    QDateTime  m_timeStart;
    bool       m_isRun;
    void closeEvent(QCloseEvent *event);
    Audio*     m_Audio;
    QProcess* pProcess;

private:
    Ui::RecordVideo *ui;
    Common* pLog;
    QNetworkReply *reply;
    networkclean* pNetworkClean;
    QString BufferFileName[8];
    QString FileLogName;
    QString pFilePathName;
    QTimer* timerProgress;
    QTimer* pCurrentTime;
    QProgressDialog* progressDialog;
    int timecount;
    int pCloseFlag;
    QString getStrMsg;
    QString getNameMp4;
};

#endif // RECORDVIDEO_H
