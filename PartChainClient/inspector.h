#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QDialog>
#include <QWebEngineView>

namespace Ui {
class Inspector;
}

class Inspector : public QDialog
{
    Q_OBJECT

public:
    explicit Inspector(QWidget *parent = nullptr);
    ~Inspector();
    void show();

    QWebEngineView* m_webView;

private:
    Ui::Inspector *ui;
};

#endif // INSPECTOR_H
