/********************************************************************************
** Form generated from reading UI file 'recorddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDDIALOG_H
#define UI_RECORDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecordDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *timeWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_circle;
    QLabel *label_time;
    QSpacerItem *horizontalSpacer_3;
    QWidget *btnWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *startBtn;
    QPushButton *stopBtn;
    QPushButton *uploadBtn;
    QWidget *widget_2;
    QWidget *pointWidget;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_point;

    void setupUi(QDialog *RecordDialog)
    {
        if (RecordDialog->objectName().isEmpty())
            RecordDialog->setObjectName(QString::fromUtf8("RecordDialog"));
        RecordDialog->resize(300, 90);
        RecordDialog->setMaximumSize(QSize(600, 200));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Icon/Titleicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        RecordDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(RecordDialog);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 6);
        timeWidget = new QWidget(RecordDialog);
        timeWidget->setObjectName(QString::fromUtf8("timeWidget"));
        timeWidget->setMaximumSize(QSize(16777215, 32));
        verticalLayout_2 = new QVBoxLayout(timeWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        label_circle = new QLabel(timeWidget);
        label_circle->setObjectName(QString::fromUtf8("label_circle"));
        label_circle->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_3->addWidget(label_circle);

        label_time = new QLabel(timeWidget);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        horizontalLayout_3->addWidget(label_time);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(timeWidget);

        btnWidget = new QWidget(RecordDialog);
        btnWidget->setObjectName(QString::fromUtf8("btnWidget"));
        btnWidget->setMaximumSize(QSize(16777215, 32));
        verticalLayout_3 = new QVBoxLayout(btnWidget);
        verticalLayout_3->setSpacing(7);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 0, -1, 4);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        startBtn = new QPushButton(btnWidget);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/Icon/startRecord.png"), QSize(), QIcon::Normal, QIcon::Off);
        startBtn->setIcon(icon1);
        startBtn->setIconSize(QSize(40, 40));

        horizontalLayout_4->addWidget(startBtn);

        stopBtn = new QPushButton(btnWidget);
        stopBtn->setObjectName(QString::fromUtf8("stopBtn"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/Icon/stopRecord.png"), QSize(), QIcon::Normal, QIcon::Off);
        stopBtn->setIcon(icon2);
        stopBtn->setIconSize(QSize(40, 40));

        horizontalLayout_4->addWidget(stopBtn);

        uploadBtn = new QPushButton(btnWidget);
        uploadBtn->setObjectName(QString::fromUtf8("uploadBtn"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/Icon/upload.png"), QSize(), QIcon::Normal, QIcon::Off);
        uploadBtn->setIcon(icon3);
        uploadBtn->setIconSize(QSize(40, 40));

        horizontalLayout_4->addWidget(uploadBtn);


        verticalLayout_3->addLayout(horizontalLayout_4);


        verticalLayout->addWidget(btnWidget);

        widget_2 = new QWidget(RecordDialog);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMaximumSize(QSize(16777215, 1));
        widget_2->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/Icon/line.png);"));

        verticalLayout->addWidget(widget_2);

        pointWidget = new QWidget(RecordDialog);
        pointWidget->setObjectName(QString::fromUtf8("pointWidget"));
        pointWidget->setMaximumSize(QSize(16777215, 32));
        verticalLayout_5 = new QVBoxLayout(pointWidget);
        verticalLayout_5->setSpacing(2);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(11, 0, -1, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_point = new QLabel(pointWidget);
        label_point->setObjectName(QString::fromUtf8("label_point"));

        verticalLayout_4->addWidget(label_point);


        verticalLayout_5->addLayout(verticalLayout_4);


        verticalLayout->addWidget(pointWidget);


        retranslateUi(RecordDialog);

        QMetaObject::connectSlotsByName(RecordDialog);
    } // setupUi

    void retranslateUi(QDialog *RecordDialog)
    {
        RecordDialog->setWindowTitle(QApplication::translate("RecordDialog", "\346\265\256\347\252\227 ", nullptr));
        label_circle->setText(QApplication::translate("RecordDialog", "TextLabel", nullptr));
        label_time->setText(QApplication::translate("RecordDialog", "TextLabel", nullptr));
        startBtn->setText(QString());
        stopBtn->setText(QString());
        uploadBtn->setText(QString());
        label_point->setText(QApplication::translate("RecordDialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RecordDialog: public Ui_RecordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDDIALOG_H
