#include "networkclean.h"
#include "common.h"
#include <QProgressDialog>

QString pHostFileName,pIpTrackFileName,pFileLog;

networkclean::networkclean()
{
    flagRunning = true;
}

networkclean::~networkclean()
{

}

/**************************************
 * 判断网络通畅的线程执行函数
 * ************************************/
void networkclean::run()
{
    QString network_cmd = "ping www.baidu.com -n 2 -w 500";
    QString result;
    network_process = new QProcess();    //不要加this
    while(flagRunning)
    {
        network_process->start(network_cmd);   //调用ping 指令
        network_process->waitForFinished();    //等待指令执行完毕
        result = network_process->readAll();   //获取指令执行结果
        if(result.contains(QString("TTL=")))   //若包含TTL=字符串则认为网络在线
        {
            emit send_network_connect_state(1);  //在线
        }
        else
        {
            emit send_network_connect_state(0); //离线
        }
        sleep(1);  //加sleep降低CPU占用率
    }
}

/**************************************
 * 停止网络自检通畅问题
 * ************************************/
void networkclean::stop()
{
    flagRunning = false;
}

/**************************************
 * Host的文件获取
 * ************************************/
void networkclean::HostFile(RecordType recordType)
{
    Common pcom;
    QString filePath = pcom.FileDirPath(recordType);
    QString getTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz");
    //QString fileName = "host" + getTime + ".txt.aisino";
    QString fileName = "host" + getTime + ".aisino";
    pHostFileName = fileName;
    QString fileFullPathName = filePath + fileName;

    pcom.isDirExist(filePath);

    QString hostPath = QString("C:/Windows/System32/drivers/etc/hosts");
    bool ok = QFile::copy(hostPath, fileFullPathName);
    if (ok)
    {
        qDebug() << "host file is ok.";
    }
    else
    {
        qDebug() << "host file is fail!";
    }
}

/**************************************
 * IP追踪
 * ************************************/
void networkclean::IpTrack()
{
    qDebug() << "IpTrack.";

    /*QProcess p(0);
    p.start("cmd", QStringList()<<"/c"<<"tracert -w 300 -h 20 www.baidu.com");
    p.waitForStarted();
    p.waitForFinished();
    QString strTemp = QString::fromLocal8Bit(p.readAllStandardOutput());

    Common *pcom = NULL;
    pcom->WriteIpTrack(strTemp);

    //p.execute("taskkill", QStringList() << "-PID" << QString("%1").arg(p.processId()) << "-F" <<"-T");
    p.close();*/
    openProcess = new QProcess(this);	//新建一个process进程
    openProcess->start("cmd", QStringList()<<"/c"<<"tracert -w 300 -h 20 www.baidu.com");
    openProcess->waitForStarted();
    //openProcess->waitForFinished();
    //QString strTemp = QString::fromLocal8Bit(openProcess->readAllStandardOutput());

    //Common *pcom = NULL;
    //pcom->WriteIpTrack(strTemp);

    //绑定process进程完成信号，垃圾回收
    /*connect(openProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
           [openProcess](int exitCode, QProcess::ExitStatus exitStatus){
         Q_UNUSED(exitCode);
         Q_UNUSED(exitStatus);
         openProcess->close();
         openProcess->kill();
         openProcess->deleteLater();
     });*/
    //connect(web_forensics, SIGNAL(SigIpTrack()), this, SLOT(IpTrackFinish()));
}

void networkclean::IpTrackFinish(RecordType recordType)
{
    qDebug() << "IpTrackFinish.";
    QString strTemp = QString::fromLocal8Bit(openProcess->readAllStandardOutput());
    Common *pcom = NULL;
    pcom->WriteIpTrack(recordType, strTemp);

    openProcess->close();
    openProcess->kill();
    openProcess->deleteLater();
}

void networkclean::DialogProgressInit()
{
    //创建一个进度对话框
    progressDialog=new QProgressDialog();
    QFont font("ZYSong18030",12);
    progressDialog->setFont(font);
    //设置进度对话框采用模态方式进行，即显示进度的同时，其他窗口将不响应输入信号
    progressDialog->setWindowModality(Qt::WindowModal);
    //设置进度对话框出现需等待的时间，默认为4s
    progressDialog->setMinimumDuration(10);
    //设置进度对话框的窗体标题
    progressDialog->setWindowTitle(tr("Please Wait"));
    //设置进度对话框的显示文字信息
    progressDialog->setLabelText(tr("Copying..."));
    //设置进度对话框的“取消”按钮的显示文字
    progressDialog->setRange(0,10);
    /*progressDialog->setCancelButtonText(tr("Cancel"));
    progressDialog->setRange(0,100000); //设置进度对话框的步进范围
    for(int i=1;i<1000001;i++)
    {
        progressDialog->setValue(i);
        if(progressDialog->wasCanceled())
            return;
    }*/
}

void networkclean::DialogProgressTime()
{
    qDebug() << "hello .";
    static int num = 0;
    num++;
    qDebug() << "num:" << num;
    progressDialog->setValue(num);
}


