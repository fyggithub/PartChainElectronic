#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "zoompreview.h"

class QListWidget;
class QListWidgetItem;
class QPaintEvent;

namespace Ui {
class PreviewWindow;
}

class PreviewWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PreviewWindow(QWidget *parent = nullptr);
    ~PreviewWindow();

private:
    void PreviewItem(void);
    void closeEvent(QCloseEvent *event);
signals:
    void SendPreviewMsgCloseWnd();
private slots:
    void SlotItemClicked(QListWidgetItem * item);
    void SlotDoubleClicked(QListWidgetItem* item);
    void DeleteClicked();
    void GetZoomPreviewMsgCloseWnd();

private:
    Ui::PreviewWindow *ui;
    QListWidget *m_pListWidget;
    ZoomPreview* pZoomPreview;
};

extern QMap<QString, QString> pMap;

#endif // PREVIEWWINDOW_H
