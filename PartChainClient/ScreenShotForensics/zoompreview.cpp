#include "zoompreview.h"
#include "ui_zoompreview.h"

ZoomPreview::ZoomPreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZoomPreview)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromLocal8Bit("图片预览"));
}

ZoomPreview::~ZoomPreview()
{
    delete ui;
}

void ZoomPreview::ShowMaximized()
{
    setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen))
                   | Qt::WindowMaximized);
    show();
}

void ZoomPreview::DisplayImage(QString path)
{
    /*QPixmap pixmap(path);
    qDebug() << path;
    ui->label->setPixmap(pixmap);
    ui->label->show();*/


    QImage* img=new QImage;
    if(!(img->load(path) ) ) //加载图像
    {
        delete img;
        return;
    }
    ui->label->setPixmap(QPixmap::fromImage(*img));
}
