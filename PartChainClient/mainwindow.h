#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLibrary>
#include <QMainWindow>
#include <QWebEngineView>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include "Common/jscommunicate.h"
#include "Common/networkclean.h"
#include "SM4/En_Decrypt.h"

#include "WebForensics/web_forensics.h"
#include "ScreenShotForensics/screenshot.h"
#include "RecordForensics/recordvideo.h"
#include "CameraForensics/camera.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString window_title;
    QWebEngineView* m_webView;
    JSCommunicate *pJsCommunicate;
    void ShowMaximized();
    void startweb(void);
    void NetworkTest();
    void RemoveCache();
    void SetCachePath();
    void DialogProgressInit();
    void DialogProgressStop();
    void DialogProgressStart();
    void UploadFile(QString *filename,int num);
    void SendPathMessage(QString mode);

public:
    web_forensics *pWebForensics;
    ScreenShot *pScreenShot;
    RecordVideo *pRecordVideo;
    Camera *pCamera;
    SM4Decrypt *pDecrypt;

public slots:
    void OpenWebForensics(void);
    void OpenWebScreenShoot(void);
    void OpenWebRecordVideo(void);
    void OpenWebCamera(void);
    void DialogProgressTime();
    void OnReceiveMessageFromJS(QString strMain,QString type,QString str);
    void update_network_state(int state); //更新网络状态

private slots:
    void replyFinished(QNetworkReply*);
    void loadError(QNetworkReply::NetworkError);
    void RecvMsgCloseWnd(RecordType type);
    void DownLoadFinish();

signals:
    void SigSendMessageToJS(QString strMain,QString type,QString str);

private:
    Ui::MainWindow *ui;
    QNetworkReply *reply;
    networkclean *detect_thread;
    QString pStrMain,pType,pStr;
    networkclean* pNetworkClean;
    QTimer* timerProgress;
    QProgressDialog* progressDialog;
    int timecount;
    int pProgressMaxRange;
    RecordType pRecordType;
    Common* pLog;
    QString downLoadPath;
    QString recvBuff;
    QString sendBuff;
};

#endif // MAINWINDOW_H
