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

#include "inspector.h"
#include "RecordForensics/recorddialog.h"
#include <QMap>

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
    void PostDownloadData(const QString& url,const QString& token,const QByteArray& parame);

public:
    web_forensics *pWebForensics;
    ScreenShot *pScreenShot;
    RecordVideo *pRecordVideo;
    Camera *pCamera;
    SM4Decrypt *pDecrypt;
    Inspector* m_inspector;
    RecordDialog *m_record;

public slots:
    void OpenWebForensics(void);
    void OpenWebScreenShoot(void);
    void OpenWebRecordVideo(void);
    void OpenWebRecordDialog(void);
    void OpenWebCamera(void);
    void DialogProgressTime();
    void OnReceiveMessageFromJS(QString strMain,QString type,QString str);
    void update_network_state(int state); //更新网络状态

private slots:
    void replyFinished(QNetworkReply*);
    void DownReplyFinished(QNetworkReply*);
    void DownReplyFinishedTest(QNetworkReply *strReply);
    void loadError(QNetworkReply::NetworkError);
    void RecvMsgCloseWnd(RecordType type);
    void MsgInspector();
    void MsgOperation();
    void MsgCopy();
    void MsgPaste();
    void WriteToFile();
private:
    void DownLoadFinish();
signals:
    void SigSendMessageToJS(QString strMain,QString type,QString str);

private:
    Ui::MainWindow *ui;
    QNetworkReply *reply;
    QNetworkAccessManager *mAccessManager;
    //QHttpMultiPart *multi_part;
    FILE *mFile;
    networkclean *detect_thread;
    QString pStrMain,pType,pStr;
    networkclean* pNetworkClean;
    QFile *pfile0;
    QFile *pfile1;
    QTimer* timerProgress;
    QProgressDialog* progressDialog;
    int timecount;
    int pProgressMaxRange;
    RecordType pRecordType;
    Common* pLog;
    QString downLoadPath;
    QByteArray recvBuff;
    QString sendBuff;
    QStringList keyList;
    QStringList fileList;
    QString mSingleType;
    int fileSum;
    int countBuff;
};

#endif // MAINWINDOW_H
