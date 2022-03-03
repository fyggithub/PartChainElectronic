#include "jscommunicate.h"
#include <QDebug>

JSCommunicate::JSCommunicate()
{

}

JSCommunicate::~JSCommunicate()
{
}

/**************************************************
 * 说明：此函数是接受JS传过来的数据
 * 参数：strMain:  "web_login";    "camera_login"
 *                "record_login"; "screenshot_login"
 *      type:   "replay";   "token"
 *      str:    最终需要传输的字符串
 * *************************************************/
void JSCommunicate::JSSendMessage(QString strMain,QString type,QString str)
{
    //qDebug() << strMain;
    emit SigReceivedMessFromJS(strMain,type,str);
}
