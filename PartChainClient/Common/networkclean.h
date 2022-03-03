#ifndef NETWORKCLEAN_H
#define NETWORKCLEAN_H

#include <QProcess>
#include <QThread>
#include <QDebug>
#include <QDir>
#include <QTimer>
#include <QDateTime>
#include <QCoreApplication>
#include <QProgressDialog>
#include "common.h"

class networkclean : public QThread
{
    Q_OBJECT
public:
    networkclean();
    ~networkclean();

    virtual void run();
    void stop();
    void HostFile(RecordType recordType);
    void IpTrack();    
    void DialogProgressInit();
    void IpTrackFinish(RecordType recordType);

signals:
    void send_network_connect_state(int state);
    //void SigIpTrack();

private slots:
    void DialogProgressTime();


private:
    bool flagRunning;   //线程运行标志
    QProcess *network_process;
    QTimer* timer;
    QProgressDialog* progressDialog;
    QProcess *openProcess;
};

extern QString pHostFileName,pIpTrackFileName,pFileLog;

#endif // NETWORKCLEAN_H
