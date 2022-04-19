#ifndef RECORDDIALOG_H
#define RECORDDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDateTime>
#include <QMouseEvent>
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
class RecordDialog;
}

class RecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecordDialog(QWidget *parent = nullptr);
    ~RecordDialog();

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
    void StartButtonClicked();
    void StopButtonClicked();
    void RecordTime();
    void FileUpload(void);
    void replyFinished(QNetworkReply*);
    void loadError(QNetworkReply::NetworkError);
    void DialogProgressTime();
    void MplayerCompressFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onMinClicked();
    void onCloseClicked();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QPoint last;

private:
    QTimer*    timer;
    QDateTime  m_timeStart;
    bool       m_isRun;
    void closeEvent(QCloseEvent *event);
    Audio*     m_Audio;
    QProcess* pProcess;
    QPushButton *m_pMinimizeButton; //最小化按钮
    QPushButton *m_pCloseButton; //关闭按钮

private:
    Ui::RecordDialog *ui;
    QNetworkReply *reply;
    networkclean* pNetworkClean;
    QString BufferFileName[8];    
    QString pFilePathName;
    QTimer* timerProgress;
    QProgressDialog* progressDialog;
    int timecount;
    int pCloseFlag;
    int pTimeoutFlag;
    QString getStrMsg;
    QString getNameMp4;
};

extern QString RecordFileLogName;

#endif // RECORDDIALOG_H
