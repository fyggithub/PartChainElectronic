/********************************************************************************
** Form generated from reading UI file 'zoompreview.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZOOMPREVIEW_H
#define UI_ZOOMPREVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ZoomPreview
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;

    void setupUi(QWidget *ZoomPreview)
    {
        if (ZoomPreview->objectName().isEmpty())
            ZoomPreview->setObjectName(QString::fromUtf8("ZoomPreview"));
        ZoomPreview->resize(960, 540);
        ZoomPreview->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Icon/Titleicon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ZoomPreview->setWindowIcon(icon);
        verticalLayout_2 = new QVBoxLayout(ZoomPreview);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(ZoomPreview);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ZoomPreview);

        QMetaObject::connectSlotsByName(ZoomPreview);
    } // setupUi

    void retranslateUi(QWidget *ZoomPreview)
    {
        ZoomPreview->setWindowTitle(QApplication::translate("ZoomPreview", "Form", nullptr));
        label->setText(QApplication::translate("ZoomPreview", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ZoomPreview: public Ui_ZoomPreview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZOOMPREVIEW_H
