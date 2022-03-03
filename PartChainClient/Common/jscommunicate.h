#ifndef JSCOMMUNICATE_H
#define JSCOMMUNICATE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

class JSCommunicate : public QObject
{
    Q_OBJECT
public:
    JSCommunicate();
    ~JSCommunicate();
    //页面端调用QT公共接口，必须有Q_INVOKABLE
    //页面端调用QT变量，用Q_PROPERTY，用法与QML相同
    Q_INVOKABLE void JSSendMessage(QString strMain,QString type,QString str);

signals:
    void SigReceivedMessFromJS(QString strMain,QString type,QString str);   //Receive message from Web
    void SigSendMessageToJS(QString strMain,QString type,QString str);                  //Send message to Web

};

#endif // JSCOMMUNICATE_H
