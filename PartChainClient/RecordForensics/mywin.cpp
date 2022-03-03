#include "mywin.h"
#include <QApplication>
#include <QScreen>
#include <QDesktopWidget>
#include <QBuffer>
#include <QFile>
#include <QDebug>
#include <windows.h>
#include <QDateTime>
#include "Common/common.h"
#include <QTextCodec>

QString pRecordVideoName;

MyWin::MyWin(std::wstring _processName, std::wstring _parentName, std::string _pathName, int _fps)
{
    m_processName = _processName;
    m_parentName  = _parentName;
    m_pathName    = _pathName;
    m_fps         = _fps;
    m_timer       = new QTimer;
    m_hwnd        = 0;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(Timer()));
}

MyWin::~MyWin()
{
    if (m_avi)
    {
        AVI_close(m_avi);
    }
}

void MyWin::Start()
{
    //get window handle.
    m_hwnd = ::FindWindowW(NULL, m_processName.c_str());

    //use system time and file name to creat file.
    Common *pcom = NULL;
    QString filePath = pcom->FileDirPath(VideoRecord);
    QString getTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz");
    QString filePathName = m_pathName.c_str() + getTime + ".avi";
    QString fileFullPathName = filePath + filePathName;

    pcom->isDirExist(filePath);
    pRecordVideoName = filePathName;

    //支持中文路径
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QByteArray fullPath = fileFullPathName.toLocal8Bit();
    m_avi = AVI_open_output_file(const_cast<char*>(fullPath.data()));
    //QByteArray fullPath = fileFullPathName.toLatin1();
    //m_avi = AVI_open_output_file(const_cast<char*>(fullPath.data()));

    //adjust the screenshot size.
    RECT rect;
    ::GetWindowRect(m_hwnd, &rect);
    QString str = "mjpg";
    AVI_set_video(m_avi, rect.right - rect.left, rect.bottom - rect.top, m_fps, str.toLatin1().data());

    //screenshot 1000/m_fps times per second.
    m_timer->start(1000 / m_fps);
    qDebug()<<"m_fps:"<<m_fps;
}

void MyWin::Stop()
{
    m_timer->stop();
    AVI_close(m_avi);
}

void MyWin::Timer()
{
    //get window wid.
    QScreen *screen = QApplication::primaryScreen();
    QPixmap map     = screen->grabWindow(WId(m_hwnd));

    //begin screenshot.
    QByteArray ba;
    QBuffer    bf(&ba);
    if (!map.save(&bf, "jpg"))
    {
        exit(0);
    }

    //write in file.
    AVI_write_frame(m_avi, ba.data(), ba.size(), 1);
}





















