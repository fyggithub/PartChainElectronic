#ifndef WEB_FORENSICS_H
#define WEB_FORENSICS_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QWebChannel>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include "Common/common.h"
#include "Common/networkclean.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QWebEngineUrlRequestInterceptor>
#include "weburlrequestinterceptor.h"

namespace Ui {
class web_forensics;
}

class web_forensics : public QMainWindow
        //,public QWebEngineUrlRequestInterceptor
{
    Q_OBJECT

public:
    explicit web_forensics(QWidget *parent = nullptr);
    ~web_forensics();

    QString window_title;
    QWebEngineView* m_webView;
    void ShowMaximized();
    void OpenWebForensics(void);
    void closeEvent(QCloseEvent *event);
    void WebUploadFile(QString *filename,int num);
    void DialogProgressInit();
    void DialogProgressStop();
    void DialogProgressDeal();
    virtual bool certificateError(const QWebEngineCertificateError &certificateError);


signals:
    void SigSendMessageToJS(QString strMain,QString type,QString str);
    void SendMsgClose();
    void SendMsgCloseWnd(RecordType);

public slots:
    void LoadWebOver(bool tmp);
    void JumpUrl(void);
    void ReloadUrl(void);
    void BackUrl(void);    
    void FullScreenSave();
    void OnUrlChanged(QUrl url); // 测试 urlChanged信号，该信号由 load(QUrl) 触发
    void replyFinished(QNetworkReply*);
    void loadError(QNetworkReply::NetworkError);
    void DialogProgressTime();
    void DisplayCurrentTime();
    void RecvMsgClose();
    void FullScreenShoot();

private:
    Ui::web_forensics *ui;
    Common* pLog;
    QNetworkReply *reply;
    QString BufferFileName[8];
    networkclean* pNetworkClean;
    QString FileLogName;
    QString pFilePathName;
    QTimer* timerProgress;
    QTimer* pCurrentTime;
    QProgressDialog* progressDialog;
    int timecount;
    int pCloseFlag;
    QString getStrMsg;
    QWebEngineHttpRequest httpR;
    WebUrlRequestInterceptor *wuri;
    int m_loadFinishFlag;
};

#endif // WEB_FORENSICS_H
