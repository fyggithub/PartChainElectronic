#include "inspector.h"
#include "ui_inspector.h"
#include <QPushButton>
#include <QStackedLayout>

Inspector::Inspector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inspector)
{
    ui->setupUi(this);
    //添加关闭、最大化和最小化
    Qt::WindowFlags windowFlag=Qt::Dialog;
    windowFlag |=Qt::WindowCloseButtonHint;
    windowFlag |= Qt::WindowMinimizeButtonHint;
    windowFlag |= Qt::WindowMaximizeButtonHint;
    setWindowFlags(windowFlag);

    m_webView = new QWebEngineView(this);
    QStackedLayout* layout = new QStackedLayout(ui->widget);
    ui->widget->setLayout(layout);
    layout->addWidget(m_webView);
    m_webView->load(QUrl("http://localhost:7777"));
    setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen)) | Qt::WindowMaximized);
    QDialog::show();
}

void Inspector::show()
{
    m_webView->reload();
    QDialog::show();
}

Inspector::~Inspector()
{
    delete ui;
}
