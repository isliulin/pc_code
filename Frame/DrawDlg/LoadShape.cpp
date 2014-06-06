#include "LoadShape.h"
#include "ui_LoadShape.h"
#include <QFile>
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
#include <QScrollBar>

LoadShape::LoadShape(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadShape)
{
    ui->setupUi(this);

    m_pLayout = NULL;
    pView = NULL;

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    this->setWindowTitle(tr("外形"));
    m_pLayout = new QHBoxLayout;
  //  pView =new QGraphicsView();
  //  pView->setDragMode(QGraphicsView::RubberBandDrag);//把单选改变给拖动模式
  //  pView->setMouseTracking(true);                     // 设置鼠标移动捕捉
  //  //pView->setSceneRect(0,0,200,200);
 //   pView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
//    m_pLayout->addWidget(pView);
//   this->setLayout(m_pLayout);

  //  ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);//把单选改变给拖动模式
  //  ui->graphicsView->setMouseTracking(true);                     // 设置鼠标移动捕捉
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    if (1 == pwnd->nLoadShapeFlag)//add by chengzhihua for chart
    {
        LoadScene("android.sk");
    }
    else
    {
        LoadScene("shape.sk");
    }
}

LoadShape::~LoadShape()
{
    for(int i = 0;i < vScene.size();i++)
        delete vScene[i];
    vScene.clear();

    delete ui;
}

void LoadShape::LoadScene(QString sPath)
{
    QFile file(sPath);
    if(!file.open(QIODevice::ReadOnly))
        return ;
    QDataStream openData(&file);
    SamDrawScene *pSvene = NULL;
    vScene.clear();
    int sceneSize = 0;
    openData >> sceneSize;
    for(int i =0; i< sceneSize; i++)
    {
        pSvene = new SamDrawScene();
       // openData >> pSvene;
        pSvene->load(openData,pSvene);
        vScene.push_back(pSvene);
        connect(pSvene,SIGNAL(SingleClickItem()),this,SLOT(onSelectSingleItem()));
    }
    file.close();
    if(ui->graphicsView && !vScene.isEmpty())
    {
        ui->graphicsView->setScene(vScene.first());
    }
    nActiveIndex = 0;

    nActiveIndex = pwnd->nLoadShapeType;

    ui->graphicsView->setScene(vScene.at(nActiveIndex));
  QScrollBar *bar = ui->graphicsView->verticalScrollBar();
 int val = bar->pageStep();
  bar->setMinimum(val);

}

void LoadShape::onSelectSingleItem()
{
    QList<QGraphicsItem *> Items;
    Items = vScene.at(nActiveIndex)->selectedItems();
    if(Items.size() != 1 ) //选择多个或者没有选择的时候返回
        return;
    DrawItemToScene FunClass;
    FunClass.CopyItem(&pCopyItem,Items.at(0));
    QDialog::accept();
}
