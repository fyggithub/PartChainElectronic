#include "recordvideo.h"
#include "ui_recordvideo.h"
#include <QStackedLayout>
#include <QTimer>
#include <QScreen>
#include <QCoreApplication>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileDialog>
#include <QWebEngineProfile>
#include "Common/common.h"
#include "Common/widget.h"
#include "head.h"
#include "mywin.h"
#include <QTextCodec>
#include "recorddialog.h"

RecordVideo::RecordVideo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RecordVideo)
{
    ui->setupUi(this);

    ui->BtnReload->setStyleSheet("QPushButton{border-top:0px solid #e8f3f9;background:  transparent;}"
                                 "QPushButton:pressed{border:2px solid white;border-radius:10px;}"
                                 );
    ui->BtnBack->setStyleSheet("QPushButton{border-top:0px solid #e8f3f9;background:  transparent;}"
                                 "QPushButton:pressed{border:2px solid white;border-radius:10px;}"
                                 );
    ui->lineEdit->setStyleSheet("QLineEdit{border-image: url(:/new/prefix1/Icon/url.png);}");

    ui->BtnReload->setToolTip(QString::fromLocal8Bit("刷新"));
    ui->BtnBack->setToolTip(QString::fromLocal8Bit("后退"));

    connect(ui->BtnReload,SIGNAL(clicked()),this,SLOT(ReloadUrl()));
    connect(ui->BtnBack,SIGNAL(clicked()),this,SLOT(BackUrl()));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(JumpUrl()), Qt::UniqueConnection);
}

RecordVideo::~RecordVideo()
{
    delete m_RecordWebView;
    delete ui;
}


void RecordVideo::JumpUrl(void)
{
    QUrl url = QUrl::fromUserInput(ui->lineEdit->text());
    if (!url.isEmpty())
    {
        m_RecordWebView->load(url);
        Common logCom;
        logCom.WebJumpUrl(VideoRecord, RecordFileLogName,url.toEncoded());
    }
}

void RecordVideo::ReloadUrl(void)
{
    m_RecordWebView->reload();
}

void RecordVideo::BackUrl(void)
{
    m_RecordWebView->back();
}

void RecordVideo::OpenRecordVideoWeb(void)
{
    m_RecordWebView = new Widget(this);
    QUrl url("http://www.baidu.com");
    m_RecordWebView->load(url);
    QStackedLayout* layout = new QStackedLayout(ui->record_widget);
    ui->record_widget->setLayout(layout);
    layout->addWidget(m_RecordWebView);
    ui->lineEdit->setText(url.toString());

    connect(m_RecordWebView, SIGNAL(urlChanged(QUrl)),this, SLOT(OnUrlChanged(QUrl)));
    m_RecordWebView->setContextMenuPolicy (Qt::NoContextMenu);
}

void RecordVideo::ShowMaximized(void)
{
//    setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen))
//                   | Qt::WindowMaximized );
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen))
                   | Qt::WindowMaximized );
    showMinimized();
}

//关闭窗口事件，关闭窗口首先需要判断定时器是否关闭了
void RecordVideo::closeEvent(QCloseEvent *event)
{
    if(pRecordDialogFlag == 1){
        pRecordDialogFlag = 0;
        event->accept();
        return;
    }
    else{
        event->ignore();
        QMessageBox::warning(this,QString::fromLocal8Bit("消息"),QString::fromLocal8Bit("请勿关闭浏览器！"),\
                                QString::fromLocal8Bit("确定"),0);
    }

    //pRecordDialogFlag = 1;
    //emit SendMsgCloseWnd(VideoRecord);
}

void RecordVideo::OnUrlChanged(QUrl url)
{
    Common logCom;
    logCom.WebJumpUrl(VideoRecord, RecordFileLogName,url.toEncoded());
    ui->lineEdit->setText(url.toEncoded());
}

void RecordVideo::CloseRecordWebMsg(void)
{
    this->close();  //关闭子窗口
}

void RecordVideo::SimulateButtonClick(void)
{
    keybd_event(VK_LWIN, 0, 0, 0);
    keybd_event(68, 0, 0, 0);
    QThread::msleep(50);
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(68, 0, KEYEVENTF_KEYUP, 0);
    QThread::msleep(100);
}

