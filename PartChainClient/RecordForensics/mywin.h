#ifndef MYWIN_H
#define MYWIN_H

#include <QWidget>
#include <QTimer>
#include <Windows.h>
#include "avilib.h"

class MyWin : public QWidget
{
    Q_OBJECT
public:
    explicit MyWin(std::wstring _processName, std::wstring _parentName, std::string _pathName, int _fps);

    void Start();
    void Stop();

    ~MyWin();

private:
    std::wstring m_processName; //process Name.
    std::wstring m_parentName;  //parent process Name.
    std::string  m_pathName;    //file Name.
    int          m_fps;         //fps.
    QTimer*      m_timer;       //timer.
    avi_t*       m_avi;         //screenshot class.
    ::HWND       m_hwnd;        //window handle.

public slots:
    void Timer();

};

extern QString pRecordVideoName;

#endif // MYWIN_H
