/********************************************************************************
** Form generated from reading UI file 'web_forensics.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEB_FORENSICS_H
#define UI_WEB_FORENSICS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_web_forensics
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *webwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *web_forensics)
    {
        if (web_forensics->objectName().isEmpty())
            web_forensics->setObjectName(QString::fromUtf8("web_forensics"));
        web_forensics->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Icon/Titleicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        web_forensics->setWindowIcon(icon);
        centralwidget = new QWidget(web_forensics);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        webwidget = new QWidget(centralwidget);
        webwidget->setObjectName(QString::fromUtf8("webwidget"));
        webwidget->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(webwidget);

        web_forensics->setCentralWidget(centralwidget);
        menubar = new QMenuBar(web_forensics);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        web_forensics->setMenuBar(menubar);
        statusbar = new QStatusBar(web_forensics);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        web_forensics->setStatusBar(statusbar);

        retranslateUi(web_forensics);

        QMetaObject::connectSlotsByName(web_forensics);
    } // setupUi

    void retranslateUi(QMainWindow *web_forensics)
    {
        web_forensics->setWindowTitle(QApplication::translate("web_forensics", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class web_forensics: public Ui_web_forensics {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEB_FORENSICS_H
