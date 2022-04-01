#ifndef BUBBLELTIPBUTTON_H
#define BUBBLELTIPBUTTON_H

#include <QPushButton>

class BubblelTipButton : public QPushButton
{
    Q_OBJECT

public:
    BubblelTipButton(QWidget *parent);
    ~BubblelTipButton();

    void setMsgNumber(int number);

protected:
    virtual void paintEvent(QPaintEvent * event);

private:
    int bubbleWidth;
    int m_msgNumber;

};

#endif // BUBBLELTIPBUTTON_H
