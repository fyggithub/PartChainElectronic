#ifndef LOGRECORD_H
#define LOGRECORD_H

#include "common.h"

class LogRecord
{
public:
    LogRecord();
    ~LogRecord();
    void LogTrack(const QString &str);
};

#endif // LOGRECORD_H
