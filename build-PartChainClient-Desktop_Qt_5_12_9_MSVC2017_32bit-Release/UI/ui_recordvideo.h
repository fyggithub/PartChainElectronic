/********************************************************************************
** Form generated from reading UI file 'recordvideo.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDVIDEO_H
#define UI_RECORDVIDEO_H

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

class Ui_RecordVideo
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *ctr_widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_currenttime;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_time;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_tip;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *BtnBack;
    QPushButton *BtnReload;
    QLineEdit *lineEdit;
    QPushButton *BtnStart;
    QPushButton *BtnStop;
    QPushButton *BtnUpload;
    QWidget *record_widget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *RecordVideo)
    {
        if (RecordVideo->objectName().isEmpty())
            RecordVideo->setObjectName(QString::fromUtf8("RecordVideo"));
        RecordVideo->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Icon/Titleicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        RecordVideo->setWindowIcon(icon);
        centralwidget = new QWidget(RecordVideo);
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
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_currenttime = new QLabel(ctr_widget);
        label_currenttime->setObjectName(QString::fromUtf8("label_currenttime"));

        horizontalLayout->addWidget(label_currenttime);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        label_time = new QLabel(ctr_widget);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        horizontalLayout->addWidget(label_time);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_tip = new QLabel(ctr_widget);
        label_tip->setObjectName(QString::fromUtf8("label_tip"));

        horizontalLayout->addWidget(label_tip);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(2, 8);
        horizontalLayout->setStretch(4, 8);
        horizontalLayout->setStretch(6, 3);

        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        BtnBack = new QPushButton(ctr_widget);
        BtnBack->setObjectName(QString::fromUtf8("BtnBack"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/Icon/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        BtnBack->setIcon(icon1);
        BtnBack->setIconSize(QSize(40, 40));

        horizontalLayout_2->addWidget(BtnBack);

        BtnReload = new QPushButton(ctr_widget);
        BtnReload->setObjectName(QString::fromUtf8("BtnReload"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/Icon/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        BtnReload->setIcon(icon2);
        BtnReload->setIconSize(QSize(40, 40));

        horizontalLayout_2->addWidget(BtnReload);

        lineEdit = new QLineEdit(ctr_widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lineEdit);

        BtnStart = new QPushButton(ctr_widget);
        BtnStart->setObjectName(QString::fromUtf8("BtnStart"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/Icon/startRecord.png"), QSize(), QIcon::Normal, QIcon::Off);
        BtnStart->setIcon(icon3);
        BtnStart->setIconSize(QSize(40, 40));

        horizontalLayout_2->addWidget(BtnStart);

        BtnStop = new QPushButton(ctr_widget);
        BtnStop->setObjectName(QString::fromUtf8("BtnStop"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix1/Icon/stopRecord.png"), QSize(), QIcon::Normal, QIcon::Off);
        BtnStop->setIcon(icon4);
        BtnStop->setIconSize(QSize(40, 40));

        horizontalLayout_2->addWidget(BtnStop);

        BtnUpload = new QPushButton(ctr_widget);
        BtnUpload->setObjectName(QString::fromUtf8("BtnUpload"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/prefix1/Icon/upload.png"), QSize(), QIcon::Normal, QIcon::Off);
        BtnUpload->setIcon(icon5);
        BtnUpload->setIconSize(QSize(40, 40));

        horizontalLayout_2->addWidget(BtnUpload);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 3);

        verticalLayout->addWidget(ctr_widget);

        record_widget = new QWidget(centralwidget);
        record_widget->setObjectName(QString::fromUtf8("record_widget"));

        verticalLayout->addWidget(record_widget);

        RecordVideo->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RecordVideo);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        RecordVideo->setMenuBar(menubar);
        statusbar = new QStatusBar(RecordVideo);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        RecordVideo->setStatusBar(statusbar);

        retranslateUi(RecordVideo);

        QMetaObject::connectSlotsByName(RecordVideo);
    } // setupUi

    void retranslateUi(QMainWindow *RecordVideo)
    {
        RecordVideo->setWindowTitle(QApplication::translate("RecordVideo", "MainWindow", nullptr));
        label_currenttime->setText(QApplication::translate("RecordVideo", "TextLabel", nullptr));
        label_time->setText(QApplication::translate("RecordVideo", "TextLabel", nullptr));
        label_tip->setText(QApplication::translate("RecordVideo", "TextLabel", nullptr));
        BtnBack->setText(QString());
        BtnReload->setText(QString());
        BtnStart->setText(QString());
        BtnStop->setText(QString());
        BtnUpload->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RecordVideo: public Ui_RecordVideo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDVIDEO_H
