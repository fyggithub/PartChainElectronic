#include "logrecord.h"
#include <QDateTime>

LogRecord::LogRecord()
{

}

LogRecord::~LogRecord()
{

}

//QString("%1").arg(a);
void LogRecord::LogTrack(const QString &str)
{
    QString getTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString timeFromat = getTime + " ";
    QString strBuff = timeFromat + " " + str + "\n";

    QFile file("Log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    file.write(strBuff.toUtf8());
    file.close();
}
