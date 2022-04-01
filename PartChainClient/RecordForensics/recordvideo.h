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
    void CloseRecordWebMsg(void);
    void SimulateButtonClick(void);

signals:
    void SigSendMessageToJS(QString strMain,QString type,QString str);
    void SendMsgCloseWnd(RecordType);

private slots:
    void JumpUrl(void);
    void ReloadUrl(void);
    void BackUrl(void);
    void OnUrlChanged(QUrl url); // 测试 urlChanged信号，该信号由 load(QUrl) 触发

private:
    void closeEvent(QCloseEvent *event);

private:
    Ui::RecordVideo *ui;
};

#endif // RECORDVIDEO_H
