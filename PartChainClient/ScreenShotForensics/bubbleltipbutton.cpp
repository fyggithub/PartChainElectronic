#include <QPainter>

#include "bubbleltipbutton.h"
#include <QDebug>

BubblelTipButton::BubblelTipButton(QWidget *parent)
    : QPushButton(parent)
    , bubbleWidth(13)
    , m_msgNumber(0)
{
}

BubblelTipButton::~BubblelTipButton()
{
}

void BubblelTipButton::setMsgNumber(int number)
{
    m_msgNumber = number;
}

void BubblelTipButton::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

//    QPoint pointMsg(6, 6);
//    QPixmap pixmapMsg(":/new/prefix1/Icon/preview.png");
//    painter.drawPixmap(pointMsg, pixmapMsg);

    if (m_msgNumber > 0)
    {
        if (m_msgNumber > 9)
        {
            bubbleWidth = 23;
        }
        if (m_msgNumber > 99)
        {
            bubbleWidth = 27;
        }
        QRect rt = rect();
//        QRect rt1 = QRect(rt.right() - bubbleWidth, rt.top(), bubbleWidth, bubbleWidth);
//        painter.setPen(Qt::red);
//        painter.setBrush(QBrush(Qt::red));
//        painter.drawEllipse(rt1);

//        painter.setPen(Qt::white);
//        painter.drawText(rt1, Qt::AlignCenter, QString::number(m_msgNumber));

        qDebug()<<"rt:"<<rt<<"bubbleWidth:"<<bubbleWidth << this->height() << this->width();
        //QRect rt1 = QRect(this->width() - bubbleWidth, rt.top(), bubbleWidth, bubbleWidth);
        QRect rt1 = QRect(this->width() - bubbleWidth, rt.top(), bubbleWidth, bubbleWidth);
        painter.setPen(Qt::red);
        painter.setBrush(QBrush(Qt::red));
        painter.drawEllipse(rt1);
        painter.setPen(Qt::white);
        painter.drawText(rt1, Qt::AlignCenter, QString::number(m_msgNumber));
    }
}
