#include "previewwindow.h"
#include "ui_previewwindow.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include "Common/common.h"

const int W_ICONSIZE = 384;
const int H_ICONSIZE = 216;
QMap<QString, QString> pMap;

PreviewWindow::PreviewWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PreviewWindow)
{
    ui->setupUi(this);

    m_pListWidget = ui->listWidget;
    m_pListWidget->setIconSize(QSize(W_ICONSIZE, H_ICONSIZE));
    m_pListWidget->setResizeMode(QListView::Adjust);
    m_pListWidget->setViewMode(QListView::IconMode);
    m_pListWidget->setMovement(QListView::Static);
    m_pListWidget->setSpacing(20);
    m_pListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection); //设置为可以选中多个目标
    PreviewItem();

    connect(m_pListWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(SlotItemClicked(QListWidgetItem*)));
    connect(ui->pushButton, SIGNAL(clicked(bool)),this,SLOT(DeleteClicked()));
    connect(m_pListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(SlotDoubleClicked(QListWidgetItem*)));
    setWindowTitle(QString::fromLocal8Bit("图片预览"));
}

PreviewWindow::~PreviewWindow()
{
    delete m_pListWidget;
    delete ui;
}

void PreviewWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<"PreviewWindow::closeEvent.";
    emit SendPreviewMsgCloseWnd();
}

void PreviewWindow::SlotItemClicked(QListWidgetItem* item)
{

}

void PreviewWindow::SlotDoubleClicked(QListWidgetItem* item)
{
    //qDebug() << "SlotDoubleClicked.";
    QList<QListWidgetItem*> itemsCnt = m_pListWidget->selectedItems();
    if(itemsCnt.size() == 0){
        return;
    }
    Common *pcom = NULL;
    QString filePath = pcom->FileDirPath(ScreenShotRecord);
    QString fullFile = filePath + itemsCnt[0]->text();

    pZoomPreview = new ZoomPreview;
    pZoomPreview->DisplayImage(fullFile);
    pZoomPreview->ShowMaximized();
}

void PreviewWindow::PreviewItem(void)
{
    Common *pcom = NULL;
    QString filePath = pcom->FileDirPath(ScreenShotRecord);
    QDir dir(filePath);
    if(!dir.exists()){
        return;
    }

    QStringList filters;
    filters << QString("*.png");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);  //设置类型过滤器，只为文件格式
    dir.setNameFilters(filters);                    //设置文件名称过滤器，只为filters格式
    if(dir.count() == 0){
        return;
    }

    int maxIndex = dir.count();
    for(int nIndex = 0;nIndex<maxIndex;++nIndex)
    {
        QString strPath = filePath + dir[nIndex];
        QPixmap objPixmap(strPath);

        //生成QListWidgetItem对象(注意：其Icon图像进行了伸缩[96*96])---scaled函数
        QListWidgetItem *pItem = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(W_ICONSIZE,H_ICONSIZE))),dir[nIndex]);
        m_pListWidget->addItem(pItem);

        //设置单元项的宽度和高度
        pItem->setSizeHint(QSize(W_ICONSIZE,H_ICONSIZE+32));
        m_pListWidget->insertItem(nIndex, pItem);
    }
}

void PreviewWindow::DeleteClicked()
{
    QList<QListWidgetItem*> itemsCnt = m_pListWidget->selectedItems();
    if(itemsCnt.size() == 0){
        QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请选择要删除的图片！"),\
                                                       QString::fromLocal8Bit("确定"), 0);
        return;
    }

    Common *pcom = NULL;
    QString filePath = pcom->FileDirPath(ScreenShotRecord);
    for(int i = 0;i < itemsCnt.size();i++)
    {
        qDebug() << itemsCnt[i]->text() << m_pListWidget->row(itemsCnt[i]);
        int numRow = m_pListWidget->row(itemsCnt[i]);
        m_pListWidget->takeItem(numRow);

        pMap.remove(itemsCnt[i]->text());

        QString fullFile = filePath + itemsCnt[i]->text();
        QFile fileTemp(fullFile);
        fileTemp.remove();
    }
}
