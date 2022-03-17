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
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_time;
    QSpacerItem *horizontalSpacer_2;
    QWidget *btnWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *startBtn;
    QPushButton *stopBtn;
    QPushButton *uploadBtn;
    QWidget *pointWidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_point;

    void setupUi(QDialog *RecordDialog)
    {
        if (RecordDialog->objectName().isEmpty())
            RecordDialog->setObjectName(QString::fromUtf8("RecordDialog"));
        RecordDialog->resize(220, 160);
        verticalLayout = new QVBoxLayout(RecordDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        timeWidget = new QWidget(RecordDialog);
        timeWidget->setObjectName(QString::fromUtf8("timeWidget"));
        timeWidget->setMaximumSize(QSize(16777215, 48));
        verticalLayout_5 = new QVBoxLayout(timeWidget);
        verticalLayout_5->setSpacing(2);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_time = new QLabel(timeWidget);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        horizontalLayout->addWidget(label_time);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout);


        verticalLayout->addWidget(timeWidget);

        btnWidget = new QWidget(RecordDialog);
        btnWidget->setObjectName(QString::fromUtf8("btnWidget"));
        verticalLayout_4 = new QVBoxLayout(btnWidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        startBtn = new QPushButton(btnWidget);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));
        startBtn->setMaximumSize(QSize(16777215, 16777215));
        startBtn->setLayoutDirection(Qt::LeftToRight);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Icon/startRecord.png"), QSize(), QIcon::Normal, QIcon::Off);
        startBtn->setIcon(icon);
        startBtn->setIconSize(QSize(40, 40));

        horizontalLayout_2->addWidget(startBtn);

        stopBtn = new QPushButton(btnWidget);
        stopBtn->setObjectName(QString::fromUtf8("stopBtn"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/Icon/stopRecord.png"), QSize(), QIcon::Normal, QIcon::Off);
        stopBtn->setIcon(icon1);
        stopBtn->setIconSize(QSize(40, 40));

        horizontalLayout_2->addWidget(stopBtn);

        uploadBtn = new QPushButton(btnWidget);
        uploadBtn->setObjectName(QString::fromUtf8("uploadBtn"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/Icon/upload.png"), QSize(), QIcon::Normal, QIcon::Off);
        uploadBtn->setIcon(icon2);
        uploadBtn->setIconSize(QSize(40, 40));

        horizontalLayout_2->addWidget(uploadBtn);


        verticalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(btnWidget);

        pointWidget = new QWidget(RecordDialog);
        pointWidget->setObjectName(QString::fromUtf8("pointWidget"));
        pointWidget->setMaximumSize(QSize(16777215, 48));
        verticalLayout_3 = new QVBoxLayout(pointWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(7);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_point = new QLabel(pointWidget);
        label_point->setObjectName(QString::fromUtf8("label_point"));

        verticalLayout_2->addWidget(label_point);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout->addWidget(pointWidget);


        retranslateUi(RecordDialog);

        QMetaObject::connectSlotsByName(RecordDialog);
    } // setupUi

    void retranslateUi(QDialog *RecordDialog)
    {
        RecordDialog->setWindowTitle(QApplication::translate("RecordDialog", "\345\275\225\345\261\217\345\217\226\350\257\201", nullptr));
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
