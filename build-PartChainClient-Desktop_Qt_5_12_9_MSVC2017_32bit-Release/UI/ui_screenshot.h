/********************************************************************************
** Form generated from reading UI file 'screenshot.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENSHOT_H
#define UI_SCREENSHOT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScreenShot
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *ctr_widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_time;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_tip;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *BtnBack;
    QPushButton *BtnReload;
    QLineEdit *lineEdit;
    QPushButton *BtnScnSot;
    QPushButton *BtnPreview;
    QPushButton *BtnUpload;
    QWidget *scnsotwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ScreenShot)
    {
        if (ScreenShot->objectName().isEmpty())
            ScreenShot->setObjectName(QString::fromUtf8("ScreenShot"));
        ScreenShot->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Icon/Titleicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ScreenShot->setWindowIcon(icon);
        centralwidget = new QWidget(ScreenShot);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        ctr_widget = new QWidget(centralwidget);
        ctr_widget->setObjectName(QString::fromUtf8("ctr_widget"));
        ctr_widget->setMaximumSize(QSize(16777215, 69));
        ctr_widget->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/Icon/top.png);"));
        verticalLayout_2 = new QVBoxLayout(ctr_widget);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 2, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_time = new QLabel(ctr_widget);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        horizontalLayout_2->addWidget(label_time);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_tip = new QLabel(ctr_widget);
        label_tip->setObjectName(QString::fromUtf8("label_tip"));

        horizontalLayout_2->addWidget(label_tip);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(2, 18);
        horizontalLayout_2->setStretch(4, 3);

        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        BtnBack = new QPushButton(ctr_widget);
        BtnBack->setObjectName(QString::fromUtf8("BtnBack"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/Icon/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        BtnBack->setIcon(icon1);
        BtnBack->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(BtnBack);

        BtnReload = new QPushButton(ctr_widget);
        BtnReload->setObjectName(QString::fromUtf8("BtnReload"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/Icon/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        BtnReload->setIcon(icon2);
        BtnReload->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(BtnReload);

        lineEdit = new QLineEdit(ctr_widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEdit);

        BtnScnSot = new QPushButton(ctr_widget);
        BtnScnSot->setObjectName(QString::fromUtf8("BtnScnSot"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/Icon/scn.png"), QSize(), QIcon::Normal, QIcon::Off);
        BtnScnSot->setIcon(icon3);
        BtnScnSot->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(BtnScnSot);

        BtnPreview = new QPushButton(ctr_widget);
        BtnPreview->setObjectName(QString::fromUtf8("BtnPreview"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix1/Icon/preview.png"), QSize(), QIcon::Normal, QIcon::Off);
        BtnPreview->setIcon(icon4);
        BtnPreview->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(BtnPreview);

        BtnUpload = new QPushButton(ctr_widget);
        BtnUpload->setObjectName(QString::fromUtf8("BtnUpload"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/prefix1/Icon/upload.png"), QSize(), QIcon::Normal, QIcon::Off);
        BtnUpload->setIcon(icon5);
        BtnUpload->setIconSize(QSize(40, 40));

        horizontalLayout->addWidget(BtnUpload);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 3);

        verticalLayout->addWidget(ctr_widget);

        scnsotwidget = new QWidget(centralwidget);
        scnsotwidget->setObjectName(QString::fromUtf8("scnsotwidget"));

        verticalLayout->addWidget(scnsotwidget);

        ScreenShot->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ScreenShot);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        ScreenShot->setMenuBar(menubar);
        statusbar = new QStatusBar(ScreenShot);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ScreenShot->setStatusBar(statusbar);

        retranslateUi(ScreenShot);

        QMetaObject::connectSlotsByName(ScreenShot);
    } // setupUi

    void retranslateUi(QMainWindow *ScreenShot)
    {
        ScreenShot->setWindowTitle(QApplication::translate("ScreenShot", "MainWindow", nullptr));
        label_time->setText(QApplication::translate("ScreenShot", "TextLabel", nullptr));
        label_tip->setText(QApplication::translate("ScreenShot", "TextLabel", nullptr));
        BtnBack->setText(QString());
        BtnReload->setText(QString());
        BtnScnSot->setText(QString());
        BtnPreview->setText(QString());
        BtnUpload->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ScreenShot: public Ui_ScreenShot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENSHOT_H
