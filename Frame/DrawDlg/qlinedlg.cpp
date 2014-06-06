#include "qlinedlg.h"
#include "ui_qlinedlg.h"
#include "color.h"
#include "Frame/mainwindow.h"
extern  MainWindow *pwnd;
QLineDlg::QLineDlg(QGraphicsItem *item,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QLineDlg)
{
    ui->setupUi(this);
    pSecurity = NULL;
    pLineItem = NULL;
    pFoldLineItem = NULL;
    pFreeLineItem = NULL;
    pLineCircleItem = NULL;

    pLineItemOld = NULL;
    pFoldLineItemOld = NULL;
    pFreeLineItemOld = NULL;
    pLineCircleItemOld = NULL;
    oId = -1;

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
    colorPicker=NULL;
    for(int i=0;i<9;i++)
    {
        ui->Line_Width->addItem(QString::number(i+1));
    }
    ui->Line_Width->setCurrentIndex(0);

    if(item)
    {
        if(item->type() == SAM_DRAW_OBJECT_LINE
           || item->type() == SAM_DRAW_OBJECT_FOLDLINE
           || item->type() == SAM_DRAW_OBJECT_FREELINE
           || item->type() == SAM_DRAW_OBJECT_LINECIRCLE)
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
            oId = pItem->id();
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
    this->setFixedSize(340, 380);
    LineInit(item);
    pTempItem=item;
 }

QLineDlg::~QLineDlg()
{
    if(buttonBox)
    {
        delete buttonBox;
        buttonBox=NULL;
    }
//    if(colorPicker)
//    {
//        delete colorPicker;
//        colorPicker=NULL;
//    }
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
    delete ui;
}
void QLineDlg::confyButton()
{
    switch(pTempItem->type())
    {
    case SAM_DRAW_OBJECT_LINE_NEW://直线
        pLineItem->setLineType(ui->Line_Type->currentIndex());//线类型
        pLineItem->setLineWidth(ui->Line_Width->currentIndex()+1);//线宽度
        pLineItem->setLineColor(ui->Line_Color->palette().background().color());//线条颜色
        pLineItem->setAlpha(ui->Alpha->value());//透明度
        pLineItem->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//末端箭头
        //pLineItem->setEndPointShape(ui->End_Cap->currentIndex());//末端形状
        if(pSecurity->Save())
        {
            pLineItem->SaveSecurityPro(&(pSecurity->sproperty));
        }
        else
        {
            return;
        }
        pLineItem->setId(ui->spinbox->value());
        break;
    case SAM_DRAW_OBJECT_FOLDLINE_NEW://连接线
        pFoldLineItem->setLineType(ui->Line_Type->currentIndex());//线类型
        pFoldLineItem->setLineWidth(ui->Line_Width->currentIndex()+1);//线宽度
        pFoldLineItem->setLineColor(ui->Line_Color->palette().background().color());//线条颜色
        pFoldLineItem->setAlpha(ui->Alpha->value());//透明度
        pFoldLineItem->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//末端箭头
        //pFoldLineItem->setEndPointShape(ui->End_Cap->currentIndex());//末端形状
        if(pSecurity->Save())
        {
            pFoldLineItem->SaveSecurityPro(&(pSecurity->sproperty));
        }
        else
        {
            return;
        }
        pFoldLineItem->setId(ui->spinbox->value());
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW://曲线、圆弧
        pLineCircleItem->setLineType(ui->Line_Type->currentIndex());//线类型
        pLineCircleItem->setLineWidth(ui->Line_Width->currentIndex()+1);//线宽度
        pLineCircleItem->setLineColor(ui->Line_Color->palette().background().color());//线条颜色
        pLineCircleItem->setAlpha(ui->Alpha->value());//透明度
        pLineCircleItem->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//末端箭头
        //pLineCircleItem->setEndPointShape(ui->End_Cap->currentIndex());//末端形状
        if(pSecurity->Save())
        {
            pLineCircleItem->SaveSecurityPro(&(pSecurity->sproperty));
        }
        else
        {
            return;
        }
        pLineCircleItem->setId(ui->spinbox->value());
        break;
    case SAM_DRAW_OBJECT_FREELINE_NEW://自由直线
        pFreeLineItem->setLineType(ui->Line_Type->currentIndex());//线类型
        pFreeLineItem->setLineWidth(ui->Line_Width->currentIndex()+1);//线宽度
        pFreeLineItem->setLineColor(ui->Line_Color->palette().background().color());//线条颜色
        pFreeLineItem->setAlpha(ui->Alpha->value());//透明度
        pFreeLineItem->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//末端箭头
        //pFreeLineItem->setEndPointShape(ui->End_Cap->currentIndex());//末端形状
        if(pSecurity->Save())
        {
            pFreeLineItem->SaveSecurityPro(&(pSecurity->sproperty));
        }
        else
        {
            return;
        }
        pFreeLineItem->setId(ui->spinbox->value());
        break;
/////////////////wxy add start
    case SAM_DRAW_OBJECT_LINE://直线
        pLineItemOld->setLineType(ui->Line_Type->currentIndex());//线类型
        pLineItemOld->setLineWidth(ui->Line_Width->currentIndex()+1);//线宽度
        pLineItemOld->setLineColor(ui->Line_Color->palette().background().color());//线条颜色
        pLineItemOld->setAlpha(ui->Alpha->value());//透明度
        pLineItemOld->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//末端箭头
        //pLineItem->setEndPointShape(ui->End_Cap->currentIndex());//末端形状
        pLineItemOld->setId(ui->spinbox->value());
        break;
    case SAM_DRAW_OBJECT_FOLDLINE://连接线
        pFoldLineItemOld->setLineType(ui->Line_Type->currentIndex());//线类型
        pFoldLineItemOld->setLineWidth(ui->Line_Width->currentIndex()+1);//线宽度
        pFoldLineItemOld->setLineColor(ui->Line_Color->palette().background().color());//线条颜色
        pFoldLineItemOld->setAlpha(ui->Alpha->value());//透明度
        pFoldLineItemOld->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//末端箭头
        //pFoldLineItem->setEndPointShape(ui->End_Cap->currentIndex());//末端形状
        pFoldLineItemOld->setId(ui->spinbox->value());
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE://曲线、圆弧
        pLineCircleItemOld->setLineType(ui->Line_Type->currentIndex());//线类型
        pLineCircleItemOld->setLineWidth(ui->Line_Width->currentIndex()+1);//线宽度
        pLineCircleItemOld->setLineColor(ui->Line_Color->palette().background().color());//线条颜色
        pLineCircleItemOld->setAlpha(ui->Alpha->value());//透明度
        pLineCircleItemOld->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//末端箭头
        //pLineCircleItem->setEndPointShape(ui->End_Cap->currentIndex());//末端形状
        pLineCircleItemOld->setId(ui->spinbox->value());
        break;
    case SAM_DRAW_OBJECT_FREELINE://自由直线
        pFreeLineItemOld->setLineType(ui->Line_Type->currentIndex());//线类型
        pFreeLineItemOld->setLineWidth(ui->Line_Width->currentIndex()+1);//线宽度
        pFreeLineItemOld->setLineColor(ui->Line_Color->palette().background().color());//线条颜色
        pFreeLineItemOld->setAlpha(ui->Alpha->value());//透明度
        pFreeLineItemOld->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//末端箭头
        //pFreeLineItem->setEndPointShape(ui->End_Cap->currentIndex());//末端形状
        pFreeLineItemOld->setId(ui->spinbox->value());
        break;
/////////////////wxy add end
    default:
        break;
    }
    if(ui->spinbox->value() != oId && !pwnd->insertId(ui->spinbox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinbox->setFocus();
        return ;
    }

    accept();
}//
//初始化函数
void QLineDlg::LineInit(QGraphicsItem *item)
{
  QColor tempColor;
  switch(item->type())
  {
  case SAM_DRAW_OBJECT_LINE_NEW://直线
      ui->tabWidget->setTabText(0,tr("直线"));
      this->setWindowTitle(tr("直线"));
      pLineItem = dynamic_cast<QLineBasicItem *> (item);
      if (NULL != pLineItem)
      {
          ui->Alpha->setValue(pLineItem->getAlpha());//透明度
          ui->Line_Type->setCurrentIndex(pLineItem->getLineType());//线类型
          ui->Line_Width->setCurrentIndex(pLineItem->getLineWidth()-1);//线宽度
          tempColor=pLineItem->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//线条颜色
          ui->End_Arrow->setCurrentIndex(pLineItem->getEndArrow());//末端箭头
          //ui->End_Cap->setCurrentIndex(pLineItem->getEndPointShape());//末端形状
          if(pSecurity)
          {
              pSecurity->init(pLineItem->GetSecurityPro());
          }
      }
      break;
  case SAM_DRAW_OBJECT_FOLDLINE_NEW://折线
      ui->tabWidget->setTabText(0,tr("折线"));
      this->setWindowTitle(tr("折线"));
      pFoldLineItem = dynamic_cast<QFoldLineBasicItem *> (item);
      if (NULL != pFoldLineItem)
      {
          ui->Alpha->setValue(pFoldLineItem->getAlpha());//透明度
          ui->Line_Type->setCurrentIndex(pFoldLineItem->getLineType());//线类型
          ui->Line_Width->setCurrentIndex(pFoldLineItem->getLineWidth()-1);//线宽度
          tempColor=pFoldLineItem->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//线条颜色
          ui->End_Arrow->setCurrentIndex(pFoldLineItem->getEndArrow());//末端箭头
          //ui->End_Cap->setCurrentIndex(pFoldLineItem->getEndPointShape());//末端形状
          if(pSecurity)
          {
              pSecurity->init(pFoldLineItem->GetSecurityPro());
          }
      }
      break;
  case SAM_DRAW_OBJECT_LINECIRCLE_NEW://曲线、圆弧
      ui->tabWidget->setTabText(0,tr("曲线/圆弧"));
      this->setWindowTitle(tr("曲线/圆弧"));
      pLineCircleItem = dynamic_cast<QLineCircleBasicItem *> (item);
      if (NULL != pLineCircleItem)
      {
          ui->Alpha->setValue(pLineCircleItem->getAlpha());//透明度
          ui->Line_Type->setCurrentIndex(pLineCircleItem->getLineType());//线类型
          ui->Line_Width->setCurrentIndex(pLineCircleItem->getLineWidth()-1);//线宽度
          tempColor=pLineCircleItem->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//线条颜色
          ui->End_Arrow->setCurrentIndex(pLineCircleItem->getEndArrow());//末端箭头
          //ui->End_Cap->setCurrentIndex(pLineCircleItem->getEndPointShape());//末端形状
          if(pSecurity)
          {
              pSecurity->init(pLineCircleItem->GetSecurityPro());
          }
      }
      break;
  case SAM_DRAW_OBJECT_FREELINE_NEW://自由直线
      ui->tabWidget->setTabText(0,tr("自由直线"));
      this->setWindowTitle(tr("自由直线"));
      pFreeLineItem = dynamic_cast<QFreeLineBasicItem *> (item);
      if (NULL != pFreeLineItem)
      {
          ui->Alpha->setValue(pFreeLineItem->getAlpha());//透明度
          ui->Line_Type->setCurrentIndex(pFreeLineItem->getLineType());//线类型
          ui->Line_Width->setCurrentIndex(pFreeLineItem->getLineWidth()-1);//线宽度
          tempColor=pFreeLineItem->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//线条颜色
          ui->End_Arrow->setCurrentIndex(pFreeLineItem->getEndArrow());//末端箭头
          //ui->End_Cap->setCurrentIndex(pFreeLineItem->getEndPointShape());//末端形状
          if(pSecurity)
          {
              pSecurity->init(pFreeLineItem->GetSecurityPro());
          }
      }
      break;
//////////////////wxy add start
  case SAM_DRAW_OBJECT_LINE://直线
      ui->tabWidget->setTabText(0,tr("直线"));
      this->setWindowTitle(tr("直线"));
      pLineItemOld = dynamic_cast<QLineItem *> (item);
      if (NULL != pLineItemOld)
      {
          ui->Alpha->setValue(pLineItemOld->getAlpha());//透明度
          ui->Line_Type->setCurrentIndex(pLineItemOld->getLineType());//线类型
          ui->Line_Width->setCurrentIndex(pLineItemOld->getLineWidth()-1);//线宽度
          tempColor=pLineItemOld->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//线条颜色
          ui->End_Arrow->setCurrentIndex(pLineItemOld->getEndArrow());//末端箭头
          //ui->End_Cap->setCurrentIndex(pLineItem->getEndPointShape());//末端形状
      }
      break;
  case SAM_DRAW_OBJECT_FOLDLINE://折线
      ui->tabWidget->setTabText(0,tr("折线"));
      this->setWindowTitle(tr("折线"));
      pFoldLineItemOld = dynamic_cast<QFoldLineItem *> (item);
      if (NULL != pFoldLineItemOld)
      {
          ui->Alpha->setValue(pFoldLineItemOld->getAlpha());//透明度
          ui->Line_Type->setCurrentIndex(pFoldLineItemOld->getLineType());//线类型
          ui->Line_Width->setCurrentIndex(pFoldLineItemOld->getLineWidth()-1);//线宽度
          tempColor=pFoldLineItemOld->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//线条颜色
          ui->End_Arrow->setCurrentIndex(pFoldLineItemOld->getEndArrow());//末端箭头
          //ui->End_Cap->setCurrentIndex(pFoldLineItem->getEndPointShape());//末端形状
      }
      break;
  case SAM_DRAW_OBJECT_LINECIRCLE://曲线、圆弧
      ui->tabWidget->setTabText(0,tr("曲线/圆弧"));
      this->setWindowTitle(tr("曲线/圆弧"));
      pLineCircleItemOld = dynamic_cast<QLineCircleItem *> (item);
      if (NULL != pLineCircleItemOld)
      {
          ui->Alpha->setValue(pLineCircleItemOld->getAlpha());//透明度
          ui->Line_Type->setCurrentIndex(pLineCircleItemOld->getLineType());//线类型
          ui->Line_Width->setCurrentIndex(pLineCircleItemOld->getLineWidth()-1);//线宽度
          tempColor=pLineCircleItemOld->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//线条颜色
          ui->End_Arrow->setCurrentIndex(pLineCircleItemOld->getEndArrow());//末端箭头
          //ui->End_Cap->setCurrentIndex(pLineCircleItem->getEndPointShape());//末端形状
      }
      break;
  case SAM_DRAW_OBJECT_FREELINE://自由直线
      ui->tabWidget->setTabText(0,tr("自由直线"));
      this->setWindowTitle(tr("自由直线"));
      pFreeLineItemOld = dynamic_cast<QFreeLineItem *> (item);
      if (NULL != pFreeLineItemOld)
      {
          ui->Alpha->setValue(pFreeLineItemOld->getAlpha());//透明度
          ui->Line_Type->setCurrentIndex(pFreeLineItemOld->getLineType());//线类型
          ui->Line_Width->setCurrentIndex(pFreeLineItemOld->getLineWidth()-1);//线宽度
          tempColor=pFreeLineItemOld->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//线条颜色
          ui->End_Arrow->setCurrentIndex(pFreeLineItemOld->getEndArrow());//末端箭头
          //ui->End_Cap->setCurrentIndex(pFreeLineItem->getEndPointShape());//末端形状
      }
      break;
/////////////////wxy add end
  default:
      ui->tabWidget->setTabText(0,tr("error"));
      break;
  }

}

void QLineDlg::on_Line_Color_clicked()
{
    colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->Line_Color,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setCurrentLineColor(const QColor &)));
}
void QLineDlg::setCurrentLineColor(const QColor & currentColor)
{
   ui->Line_Color->setStyleSheet(QString("background:%1").arg(currentColor.name()));
}

void QLineDlg::loadHelp()
{
    switch(pTempItem->type())
    {
    case SAM_DRAW_OBJECT_LINE://直线
    case SAM_DRAW_OBJECT_LINE_NEW:
        pwnd->loadHelpHtm(SAM_DRAW_OBJECT_LINE);
        break;
    case SAM_DRAW_OBJECT_FOLDLINE://折线
    case SAM_DRAW_OBJECT_FOLDLINE_NEW:
        pwnd->loadHelpHtm(SAM_DRAW_OBJECT_FOLDLINE);
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE://曲线、圆弧
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
        pwnd->loadHelpHtm(SAM_DRAW_OBJECT_ARCLINE);
        break;
     case SAM_DRAW_OBJECT_FREELINE://自由直线
     case SAM_DRAW_OBJECT_FREELINE_NEW:
         pwnd->loadHelpHtm(SAM_DRAW_OBJECT_FREELINE);
         break;
    }
}
