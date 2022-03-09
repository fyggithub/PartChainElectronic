/********************************************************************************
** Form generated from reading UI file 'camera.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERA_H
#define UI_CAMERA_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Camera
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *display_widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_currenttime;
    QSpacerItem *horizontalSpacer_14;
    QLabel *label;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label_tip;
    QSpacerItem *horizontalSpacer_2;
    QWidget *photo_widget;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_display;
    QSpacerItem *horizontalSpacer_12;
    QWidget *option_widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *BtnStart;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *BtnUpload;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *BtnReload;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_8;
    QWidget *point_widget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_point;
    QSpacerItem *horizontalSpacer_10;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Camera)
    {
        if (Camera->objectName().isEmpty())
            Camera->setObjectName(QString::fromUtf8("Camera"));
        Camera->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Icon/Titleicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Camera->setWindowIcon(icon);
        centralwidget = new QWidget(Camera);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        display_widget = new QWidget(centralwidget);
        display_widget->setObjectName(QString::fromUtf8("display_widget"));
        display_widget->setMaximumSize(QSize(16777215, 43));
        display_widget->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/Icon/cameraTop.png);"));
        horizontalLayout = new QHBoxLayout(display_widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_currenttime = new QLabel(display_widget);
        label_currenttime->setObjectName(QString::fromUtf8("label_currenttime"));

        horizontalLayout->addWidget(label_currenttime);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_14);

        label = new QLabel(display_widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_13);

        label_tip = new QLabel(display_widget);
        label_tip->setObjectName(QString::fromUtf8("label_tip"));

        horizontalLayout->addWidget(label_tip);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(display_widget);

        photo_widget = new QWidget(centralwidget);
        photo_widget->setObjectName(QString::fromUtf8("photo_widget"));
        photo_widget->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_4 = new QHBoxLayout(photo_widget);
        horizontalLayout_4->setSpacing(7);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_11);

        label_display = new QLabel(photo_widget);
        label_display->setObjectName(QString::fromUtf8("label_display"));
        label_display->setMaximumSize(QSize(16777215, 16777215));
        label_display->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/Icon/camera.png);"));

        horizontalLayout_4->addWidget(label_display);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_12);


        verticalLayout->addWidget(photo_widget);

        option_widget = new QWidget(centralwidget);
        option_widget->setObjectName(QString::fromUtf8("option_widget"));
        option_widget->setMaximumSize(QSize(16777215, 60));
        verticalLayout_2 = new QVBoxLayout(option_widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        BtnStart = new QPushButton(option_widget);
        BtnStart->setObjectName(QString::fromUtf8("BtnStart"));
        BtnStart->setMaximumSize(QSize(75, 36));
        BtnStart->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/Icon/button.png);\n"
"border-style: none;\n"
"padding-left: 8px;\n"
"padding-top: 8px;\n"
"padding-right: 8px;\n"
"padding-bottom: 8px;\n"
"color:white;"));

        horizontalLayout_2->addWidget(BtnStart);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        BtnUpload = new QPushButton(option_widget);
        BtnUpload->setObjectName(QString::fromUtf8("BtnUpload"));
        BtnUpload->setMaximumSize(QSize(75, 36));
        BtnUpload->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/Icon/button.png);\n"
"border-style: none;\n"
"padding-left: 8px;\n"
"padding-top: 8px;\n"
"padding-right: 8px;\n"
"padding-bottom: 8px;\n"
"color:white;"));

        horizontalLayout_2->addWidget(BtnUpload);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        BtnReload = new QPushButton(option_widget);
        BtnReload->setObjectName(QString::fromUtf8("BtnReload"));
        BtnReload->setMaximumSize(QSize(75, 36));
        BtnReload->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/Icon/button.png);\n"
"border-style: none;\n"
"padding-left: 8px;\n"
"padding-top: 8px;\n"
"padding-right: 8px;\n"
"padding-bottom: 8px;\n"
"color:white;"));

        horizontalLayout_2->addWidget(BtnReload);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(option_widget);

        point_widget = new QWidget(centralwidget);
        point_widget->setObjectName(QString::fromUtf8("point_widget"));
        point_widget->setMaximumSize(QSize(16777215, 48));
        horizontalLayout_3 = new QHBoxLayout(point_widget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        label_point = new QLabel(point_widget);
        label_point->setObjectName(QString::fromUtf8("label_point"));

        horizontalLayout_3->addWidget(label_point);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_10);


        verticalLayout->addWidget(point_widget);

        Camera->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Camera);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        Camera->setMenuBar(menubar);
        statusbar = new QStatusBar(Camera);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Camera->setStatusBar(statusbar);

        retranslateUi(Camera);

        QMetaObject::connectSlotsByName(Camera);
    } // setupUi

    void retranslateUi(QMainWindow *Camera)
    {
        Camera->setWindowTitle(QApplication::translate("Camera", "MainWindow", nullptr));
        label_currenttime->setText(QApplication::translate("Camera", "TextLabel", nullptr));
        label->setText(QApplication::translate("Camera", "TextLabel", nullptr));
        label_tip->setText(QApplication::translate("Camera", "TextLabel", nullptr));
        label_display->setText(QApplication::translate("Camera", "TextLabel", nullptr));
        BtnStart->setText(QApplication::translate("Camera", "\345\274\200\345\247\213\345\217\226\350\257\201", nullptr));
        BtnUpload->setText(QApplication::translate("Camera", "\344\270\212\344\274\240\345\217\226\350\257\201", nullptr));
        BtnReload->setText(QApplication::translate("Camera", "\351\207\215\346\226\260\345\217\226\350\257\201", nullptr));
        label_point->setText(QApplication::translate("Camera", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Camera: public Ui_Camera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_H
