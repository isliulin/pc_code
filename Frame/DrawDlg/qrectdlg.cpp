#include "qrectdlg.h"
#include "ui_qrectdlg.h"
#include "color.h"

#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QRectDlg::QRectDlg(QGraphicsItem *item,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QRectDlg)
{
    ui->setupUi(this);

    pRectItem = NULL;
    pElipseItem = NULL;
    pPolygonItem = NULL;

    pRectItemOld = NULL;
    pElipseItemOld = NULL;
    pPolygonItemOld = NULL;

    ui->nType->setEnabled(false);
    //ui->groupBox_4->setHidden(true);//种类 只有矩形用到该变量别的类型没有
    pwnd->OnAddPattern(ui->Pattern);  //加载样式
    //colorPicker=NULL;
    colorPicker2=NULL;
    colorPicker3=NULL;

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("确定"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("取消"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("帮助"),QDialogButtonBox::HelpRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(confyButton()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonBox, SIGNAL(helpRequested ()), this, SLOT(loadHelp()));
    for(int i=0;i<9;i++)
    {
        ui->Line_Width->addItem(QString::number(i+1));
    }
    ui->Line_Width->setCurrentIndex(0);

    if(item)
    {
        if(item->type() == SAM_DRAW_OBJECT_RECT
           || item->type() == SAM_DRAW_OBJECT_ELIPSE
           || item->type() == SAM_DRAW_OBJECT_POLYGON)
        {
            pSecurity = NULL;
        }
        else
        {
            pSecurity = new SecurityWidget(this);
            ui->tabWidget->addTab(pSecurity, tr("权限设置"));
            pSecurity->setGroupVVisible(false);
            pSecurity->setTouchGroupEnabled(false);
        }
        SamDrawItemBase *pItem = dynamic_cast<SamDrawItemBase *> (item);
        if(pItem)
        {
            ui->spinbox->setValue(pItem->id());
        }
    }
    else
    {
        pSecurity = new SecurityWidget(this);
        ui->tabWidget->addTab(pSecurity, tr("权限设置"));
        pSecurity->setGroupVVisible(false);
        pSecurity->setTouchGroupEnabled(false);
    }

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(ui->tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    this->setFixedSize(330, 400);
    pTempRectItem=item;
    RectInit(item);
}

QRectDlg::~QRectDlg()
{
    if(buttonBox)
    {
        delete buttonBox;
        buttonBox=NULL;
    }
    if(mainLayout)
    {
        delete mainLayout;
        mainLayout=NULL;
    }
    if(pSecurity)
    {
        delete pSecurity;
        pSecurity = NULL;
    }
//    if(colorPicker)
//    {
//        delete colorPicker;
//        colorPicker=NULL;
//    }
//    if(colorPicker2)
//    {
//        delete colorPicker2;
//        colorPicker2=NULL;
//    }
//    if(colorPicker3)
//    {
//        delete colorPicker3;
//        colorPicker3=NULL;
//    }
     delete ui;
}
void QRectDlg::confyButton()
{

    switch(pTempRectItem->type())
    {
    case SAM_DRAW_OBJECT_RECT_NEW://矩形
        pRectItem->SetLineType(ui->Line_Type->currentIndex());//线类型
        pRectItem->SetLineWidth(ui->Line_Width->currentIndex()+1);//线宽度
        pRectItem->SetLineColor(ui->Line_Color->palette().background().color());//线条颜色
        pRectItem->SetPattern(ui->Pattern->currentIndex());//样式
        pRectItem->SetBackColor(ui->Back_Color->palette().background().color());
        pRectItem->SetFrontColor(ui->Fore_Color->palette().background().color());
        pRectItem->SetAlpha(ui->Alpha->value());//透明度
        pRectItem->SetId(ui->nType->currentIndex());
        if(pSecurity->Save())
        {
            pRectItem->SaveSecurityPro(&(pSecurity->sproperty));
        }
        else
        {
            return;
        }
        pRectItem->setId(ui->spinbox->value());
        break;
    case SAM_DRAW_OBJECT_ELIPSE_NEW://椭圆
        //pElipseItem->SetLineType(ui->Line_Type->currentIndex());//线类型
        pElipseItem->SetLineWidth(ui->Line_Width->currentIndex()+1);//线宽度
        pElipseItem->SetLineColor(ui->Line_Color->palette().background().color());//线条颜色
        pElipseItem->SetPattern(ui->Pattern->currentIndex());//样式
        pElipseItem->SetBackColor(ui->Back_Color->palette().background().color());
        pElipseItem->SetFrontColor(ui->Fore_Color->palette().background().color());
        pElipseItem->SetAlpha(ui->Alpha->value());//透明度
        pElipseItem->SetLineType(ui->Line_Type->currentIndex());//线类型
        if(pSecurity->Save())
        {
            pElipseItem->SaveSecurityPro(&(pSecurity->sproperty));
        }
        else
        {
            return;
        }
        pElipseItem->setId(ui->spinbox->value());
           break;
    case SAM_DRAW_OBJECT_POLYGON_NEW://多边形
        pPolygonItem->setLineType(ui->Line_Type->currentIndex());//线类型
        pPolygonItem->setLineWidth(ui->Line_Width->currentIndex()+1);//线宽度
        pPolygonItem->setLineColor(ui->Line_Color->palette().background().color());//线条颜色
        pPolygonItem->setPattern(ui->Pattern->currentIndex());//样式
        pPolygonItem->setBackColor(ui->Back_Color->palette().background().color());
        pPolygonItem->setFrontColor(ui->Fore_Color->palette().background().color());
        pPolygonItem->setAlpha(ui->Alpha->value());//透明度
        if(pSecurity->Save())
        {
            pPolygonItem->SaveSecurityPro(&(pSecurity->sproperty));
        }
        else
        {
            return;
        }
        pPolygonItem->setId(ui->spinbox->value());
        break;
/////////////////wxy add start
    case SAM_DRAW_OBJECT_RECT://矩形
        pRectItemOld->SetLineType(ui->Line_Type->currentIndex());//线类型
        pRectItemOld->SetLineWidth(ui->Line_Width->currentIndex()+1);//线宽度
        pRectItemOld->SetLineColor(ui->Line_Color->palette().background().color());//线条颜色
        pRectItemOld->SetPattern(ui->Pattern->currentIndex());//样式
        pRectItemOld->SetBackColor(ui->Back_Color->palette().background().color());
        pRectItemOld->SetFrontColor(ui->Fore_Color->palette().background().color());
        pRectItemOld->SetAlpha(ui->Alpha->value());//透明度
        pRectItemOld->SetId(ui->nType->currentIndex());
        pRectItemOld->setId(ui->spinbox->value());
        break;
    case SAM_DRAW_OBJECT_ELIPSE://椭圆
        //pElipseItem->SetLineType(ui->Line_Type->currentIndex());//线类型
        pElipseItemOld->SetLineWidth(ui->Line_Width->currentIndex()+1);//线宽度
        pElipseItemOld->SetLineColor(ui->Line_Color->palette().background().color());//线条颜色
        pElipseItemOld->SetPattern(ui->Pattern->currentIndex());//样式
        pElipseItemOld->SetBackColor(ui->Back_Color->palette().background().color());
        pElipseItemOld->SetFrontColor(ui->Fore_Color->palette().background().color());
        pElipseItemOld->SetAlpha(ui->Alpha->value());//透明度
        pElipseItemOld->SetLineType(ui->Line_Type->currentIndex());//线类型
        pElipseItemOld->setId(ui->spinbox->value());
        break;
    case SAM_DRAW_OBJECT_POLYGON://多边形
        pPolygonItemOld->setLineType(ui->Line_Type->currentIndex());//线类型
        pPolygonItemOld->setLineWidth(ui->Line_Width->currentIndex()+1);//线宽度
        pPolygonItemOld->setLineColor(ui->Line_Color->palette().background().color());//线条颜色
        pPolygonItemOld->setPattern(ui->Pattern->currentIndex());//样式
        pPolygonItemOld->setBackColor(ui->Back_Color->palette().background().color());
        pPolygonItemOld->setFrontColor(ui->Fore_Color->palette().background().color());
        pPolygonItemOld->setAlpha(ui->Alpha->value());//透明度
        pPolygonItemOld->setId(ui->spinbox->value());
        break;
////////////////wxy add end
     default:
        break;
    }
    accept();
}//
//初始化函数
void QRectDlg::RectInit(QGraphicsItem *item)
{
    QColor tempColor;
    switch(item->type())
    {
    case SAM_DRAW_OBJECT_RECT_NEW://矩形
           ui->tabWidget->setTabText(0,tr("矩形"));
        this->setWindowTitle(tr("矩形"));
        ui->nType->setEnabled(true);
        //ui->groupBox_4->setHidden(false);//种类
        pRectItem = dynamic_cast<QRectBasicItem *> (item);
        if (NULL != pRectItem)
        {
            ui->Alpha->setValue(pRectItem->GetAlpha());//透明度
            ui->Line_Type->setCurrentIndex(pRectItem->GetLineType());//线类型
            ui->Line_Width->setCurrentIndex(pRectItem->GetLineWidth()-1);//线宽度
            tempColor=pRectItem->GetLineColor();
            tempColor.setAlpha(255);
            ui->Line_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
            ui->Pattern->setCurrentIndex(pRectItem->GetPattern());//样式
            tempColor=pRectItem->GetBackColor();
            tempColor.setAlpha(255);
            ui->Back_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
            tempColor=pRectItem->GetFrontColor();
            tempColor.setAlpha(255);
            ui->Fore_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
            ui->nType->setCurrentIndex(pRectItem->GetID());
            if(pSecurity)
            {
                pSecurity->init(pRectItem->GetSecurityPro());
            }
        }
        break;
  case SAM_DRAW_OBJECT_ELIPSE_NEW://圆/椭圆
      ui->tabWidget->setTabText(0,tr("圆/椭圆"));
      this->setWindowTitle(tr("圆/椭圆"));
      pElipseItem = dynamic_cast<QElipseBasicItem *> (item);
      if (NULL != pElipseItem)
      {

          ui->Alpha->setValue(pElipseItem->GetAlpha());//透明度
          ui->Line_Type->setCurrentIndex(pElipseItem->GetLineType());//线类型
          ui->Line_Width->setCurrentIndex(pElipseItem->GetLineWidth()-1);//线宽度
          tempColor=pElipseItem->GetLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
          ui->Pattern->setCurrentIndex(pElipseItem->GetPattern());//样式
          tempColor=pElipseItem->GetBackColor();
          tempColor.setAlpha(255);
          ui->Back_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
          tempColor=pElipseItem->GetFrontColor();
          tempColor.setAlpha(255);
          ui->Fore_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
          if(pSecurity)
          {
              pSecurity->init(pElipseItem->GetSecurityPro());
          }
      }
      break;
  case SAM_DRAW_OBJECT_POLYGON_NEW://多边形
      ui->tabWidget->setTabText(0,tr("多边形"));
      this->setWindowTitle(tr("多边形"));
      pPolygonItem = dynamic_cast<QPolygonBasicItem *> (item);
      if (NULL != pPolygonItem)
      {
          ui->Alpha->setValue(pPolygonItem->getAlpha());//透明度
          ui->Line_Type->setCurrentIndex(pPolygonItem->getLineType());//线类型
          ui->Line_Width->setCurrentIndex(pPolygonItem->getLineWidth()-1);//线宽度
          tempColor=pPolygonItem->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
          ui->Pattern->setCurrentIndex(pPolygonItem->getPattern());//样式
          tempColor=pPolygonItem->getBackColor();
          tempColor.setAlpha(255);
          ui->Back_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
          tempColor=pPolygonItem->getFrontColor();
          tempColor.setAlpha(255);
          ui->Fore_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
          if(pSecurity)
          {
              pSecurity->init(pPolygonItem->GetSecurityPro());
          }
       }
      break;
////////////////////wxy add start
    case SAM_DRAW_OBJECT_RECT://矩形
           ui->tabWidget->setTabText(0,tr("矩形"));
        this->setWindowTitle(tr("矩形"));
        ui->nType->setEnabled(true);
        //ui->groupBox_4->setHidden(false);//种类
        pRectItemOld = dynamic_cast<QRectItem *> (item);
        if (NULL != pRectItemOld)
        {
            ui->Alpha->setValue(pRectItemOld->GetAlpha());//透明度
            ui->Line_Type->setCurrentIndex(pRectItemOld->GetLineType());//线类型
            ui->Line_Width->setCurrentIndex(pRectItemOld->GetLineWidth()-1);//线宽度
            tempColor=pRectItemOld->GetLineColor();
            tempColor.setAlpha(255);
            ui->Line_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
            ui->Pattern->setCurrentIndex(pRectItemOld->GetPattern());//样式
            tempColor=pRectItemOld->GetBackColor();
            tempColor.setAlpha(255);
            ui->Back_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
            tempColor=pRectItemOld->GetFrontColor();
            tempColor.setAlpha(255);
            ui->Fore_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
            ui->nType->setCurrentIndex(pRectItemOld->GetID());
        }
        break;
  case SAM_DRAW_OBJECT_ELIPSE://圆/椭圆
      ui->tabWidget->setTabText(0,tr("圆/椭圆"));
      this->setWindowTitle(tr("圆/椭圆"));
      pElipseItemOld = dynamic_cast<QElipseItem *> (item);
      if (NULL != pElipseItemOld)
      {

          ui->Alpha->setValue(pElipseItemOld->GetAlpha());//透明度
          ui->Line_Type->setCurrentIndex(pElipseItemOld->GetLineType());//线类型
          ui->Line_Width->setCurrentIndex(pElipseItemOld->GetLineWidth()-1);//线宽度
          tempColor=pElipseItemOld->GetLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
          ui->Pattern->setCurrentIndex(pElipseItemOld->GetPattern());//样式
          tempColor=pElipseItemOld->GetBackColor();
          tempColor.setAlpha(255);
          ui->Back_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
          tempColor=pElipseItemOld->GetFrontColor();
          tempColor.setAlpha(255);
          ui->Fore_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
      }
      break;
  case SAM_DRAW_OBJECT_POLYGON://多边形
      ui->tabWidget->setTabText(0,tr("多边形"));
      this->setWindowTitle(tr("多边形"));
      pPolygonItemOld = dynamic_cast<QPolygonItem *> (item);
      if (NULL != pPolygonItemOld)
      {
          ui->Alpha->setValue(pPolygonItemOld->getAlpha());//透明度
          ui->Line_Type->setCurrentIndex(pPolygonItemOld->getLineType());//线类型
          ui->Line_Width->setCurrentIndex(pPolygonItemOld->getLineWidth()-1);//线宽度
          tempColor=pPolygonItemOld->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
          ui->Pattern->setCurrentIndex(pPolygonItemOld->getPattern());//样式
          tempColor=pPolygonItemOld->getBackColor();
          tempColor.setAlpha(255);
          ui->Back_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
          tempColor=pPolygonItemOld->getFrontColor();
          tempColor.setAlpha(255);
          ui->Fore_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//线条颜色
       }
      break;
////////////////////wxy add end
  default:
      ui->tabWidget->setTabText(0,tr("error"));
      break;
  }

}

void QRectDlg::on_Line_Color_clicked()
{
    colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->Line_Color,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setCurrentLineColor(const QColor &)));
}

void QRectDlg::on_Back_Color_clicked()
{
    colorPicker2=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->Back_Color,colorPicker2);
    connect(colorPicker2, SIGNAL(selected(const QColor &)), this, SLOT(setCurrentBKColor(const QColor &)));
}

void QRectDlg::on_Fore_Color_clicked()
{
    colorPicker3=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->Fore_Color,colorPicker3);
    connect(colorPicker3, SIGNAL(selected(const QColor &)), this, SLOT(setCurrentFrontColor(const QColor &)));
}

void QRectDlg::setCurrentLineColor(const QColor & currentColor)
{
    ui->Line_Color->setStyleSheet(QString("background:%1").arg(currentColor.name()));
}
void QRectDlg::setCurrentBKColor(const QColor & currentColor)
{
    ui->Back_Color->setStyleSheet(QString("background:%1").arg(currentColor.name()));
}
void QRectDlg::setCurrentFrontColor(const QColor & currentColor)
{
    ui->Fore_Color->setStyleSheet(QString("background:%1").arg(currentColor.name()));
}

void QRectDlg::loadHelp()
{
    switch(pTempRectItem->type())
    {
    case SAM_DRAW_OBJECT_RECT://矩形
    case SAM_DRAW_OBJECT_RECT_NEW:
        pwnd->loadHelpHtm(SAM_DRAW_OBJECT_RECT);
        break;
    case SAM_DRAW_OBJECT_ELIPSE://圆/椭圆
    case SAM_DRAW_OBJECT_ELIPSE_NEW:
        pwnd->loadHelpHtm(SAM_DRAW_OBJECT_ELIPSE);
        break;
    case SAM_DRAW_OBJECT_POLYGON://多边形
    case SAM_DRAW_OBJECT_POLYGON_NEW:
        pwnd->loadHelpHtm(SAM_DRAW_OBJECT_POLYGON);
        break;
    }
}
