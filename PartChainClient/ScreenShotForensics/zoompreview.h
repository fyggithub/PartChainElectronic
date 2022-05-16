#ifndef ZOOMPREVIEW_H
#define ZOOMPREVIEW_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class ZoomPreview;
}

class ZoomPreview : public QWidget
{
    Q_OBJECT

public:
    explicit ZoomPreview(QWidget *parent = nullptr);
    ~ZoomPreview();
    QString imagePath;
    void DisplayImage(QString path);
    void ShowMaximized();
private:
    void closeEvent(QCloseEvent *event);
signals:
    void SendZoomPreviewMsgCloseWnd();
private:
    Ui::ZoomPreview *ui;
};

#endif // ZOOMPREVIEW_H
