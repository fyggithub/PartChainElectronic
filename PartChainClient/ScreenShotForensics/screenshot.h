#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QMainWindow>
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
#include "Common/common.h"
#include "Common/networkclean.h"
#include "previewwindow.h"

namespace Ui {
class ScreenShot;
}

class ScreenShot : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScreenShot(QWidget *parent = nullptr);
    ~ScreenShot();

    QWebEngineView* m_ScnSotWebView;
    JSCommunicate *pJsComScnSot;
    void ShowMaximized(void);
    void OpenScreenShootWeb(void);
private:
    void closeEvent(QCloseEvent *event);
    void ScnShotUploadFile(QString *filename,int num);
    void DialogProgressInit();
    void DialogProgressStop();
    void DialogProgressDeal();

signals:
    void SigSendMessageToJS(QString strMain,QString type,QString str);
    void SendMsgCloseWnd(RecordType);

public slots:
    void JumpUrl(void);
    void ReloadUrl(void);
    void BackUrl(void);
    void GrabFullScreen(void);
    void FileUpload(void);
    void OpenPreview(void);
    void OnUrlChanged(QUrl url); // 测试 urlChanged信号，该信号由 load(QUrl) 触发
    void replyFinished(QNetworkReply*);
    void loadError(QNetworkReply::NetworkError);
    void DialogProgressTime();
    void DisplayCurrentTime();

private:
    Ui::ScreenShot *ui;
    Common* pLog;
    QNetworkReply *reply;
    QString BufferFileName[8];
    networkclean* pNetworkClean;
    QString FileLogName;
    QString pFilePathName;
    QTimer* timerProgress;
    QTimer* pCurrentTime;
    QProgressDialog* progressDialog;
    PreviewWindow* pPreviewWindow;
    int timecount;
    int pCloseFlag;
};

#endif // SCREENSHOT_H
