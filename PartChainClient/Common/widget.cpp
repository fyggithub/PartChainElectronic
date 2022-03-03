#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWebEngineView(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    /*detect_thread = new networkclean();
    detect_thread->HostFile();
    detect_thread->IpTrack();
    detect_thread->stop();*/

    //判断网络是否通畅
    //NetworkTest();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::NetworkTest()
{
    detect_thread = new networkclean();
    connect(detect_thread, SIGNAL(send_network_connect_state(int)), this, SLOT(update_network_state(int)));
    detect_thread->start(); //开启网络检测线程
}

void Widget::update_network_state(int state)
{
    if(state)
    {
        //qDebug() << "NetWork is ok." << endl;
    }
    else
    {
        //qDebug() << "NetWork is fail." << endl;
        //QMessageBox::warning(NULL, "", "Network Error!",QMessageBox::Yes, QMessageBox::Yes);
    }
}

QWebEngineView* Widget::createWindow(QWebEnginePage::WebWindowType type)
{
    Q_UNUSED(type);
    //qDebug() << "Widget createWindow." << endl;
    QWebEngineView* newview = new Widget(this);

    connect(newview, SIGNAL(urlChanged(QUrl)), this, SLOT(onUrlChanged(QUrl)));
    return newview;
}

void Widget::onUrlChanged(QUrl url)
{
    qDebug() << "Widget onUrlChanged." << endl;
    setUrl(url);
}
