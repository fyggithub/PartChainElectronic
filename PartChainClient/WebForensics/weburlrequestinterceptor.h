#ifndef WEBURLREQUESTINTERCEPTOR_H
#define WEBURLREQUESTINTERCEPTOR_H

#include <QDebug>
#include <QDir>
#include <QWebEngineUrlRequestInterceptor>


class WebUrlRequestInterceptor : public QWebEngineUrlRequestInterceptor
{
    Q_OBJECT
public:
    WebUrlRequestInterceptor(QObject *p = Q_NULLPTR);
    void interceptRequest(QWebEngineUrlRequestInfo &info);
};

#endif // WEBURLREQUESTINTERCEPTOR_H
