#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QWebEngineView>
#include <QWebChannel>

#include <QTabWidget>
#include <QList>
#include "networkclean.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWebEngineView
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void NetworkTest();

private:
    Ui::Widget *ui;
    networkclean *detect_thread;

protected:
    QWebEngineView* createWindow(QWebEnginePage::WebWindowType type);

private slots:
    void onUrlChanged(QUrl url);
    void update_network_state(int state); //更新网络状态
};

#endif // WIDGET_H
