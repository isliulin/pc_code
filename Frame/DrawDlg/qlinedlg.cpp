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
    buttonBox->addButton(tr("ȷ��"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("ȡ��"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("����"),QDialogButtonBox::HelpRole);

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
            ui->tabWidget->addTab(pSecurity, tr("Ȩ������"));
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
        ui->tabWidget->addTab(pSecurity, tr("Ȩ������"));
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
    case SAM_DRAW_OBJECT_LINE_NEW://ֱ��
        pLineItem->setLineType(ui->Line_Type->currentIndex());//������
        pLineItem->setLineWidth(ui->Line_Width->currentIndex()+1);//�߿��
        pLineItem->setLineColor(ui->Line_Color->palette().background().color());//������ɫ
        pLineItem->setAlpha(ui->Alpha->value());//͸����
        pLineItem->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//ĩ�˼�ͷ
        //pLineItem->setEndPointShape(ui->End_Cap->currentIndex());//ĩ����״
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
    case SAM_DRAW_OBJECT_FOLDLINE_NEW://������
        pFoldLineItem->setLineType(ui->Line_Type->currentIndex());//������
        pFoldLineItem->setLineWidth(ui->Line_Width->currentIndex()+1);//�߿��
        pFoldLineItem->setLineColor(ui->Line_Color->palette().background().color());//������ɫ
        pFoldLineItem->setAlpha(ui->Alpha->value());//͸����
        pFoldLineItem->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//ĩ�˼�ͷ
        //pFoldLineItem->setEndPointShape(ui->End_Cap->currentIndex());//ĩ����״
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
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW://���ߡ�Բ��
        pLineCircleItem->setLineType(ui->Line_Type->currentIndex());//������
        pLineCircleItem->setLineWidth(ui->Line_Width->currentIndex()+1);//�߿��
        pLineCircleItem->setLineColor(ui->Line_Color->palette().background().color());//������ɫ
        pLineCircleItem->setAlpha(ui->Alpha->value());//͸����
        pLineCircleItem->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//ĩ�˼�ͷ
        //pLineCircleItem->setEndPointShape(ui->End_Cap->currentIndex());//ĩ����״
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
    case SAM_DRAW_OBJECT_FREELINE_NEW://����ֱ��
        pFreeLineItem->setLineType(ui->Line_Type->currentIndex());//������
        pFreeLineItem->setLineWidth(ui->Line_Width->currentIndex()+1);//�߿��
        pFreeLineItem->setLineColor(ui->Line_Color->palette().background().color());//������ɫ
        pFreeLineItem->setAlpha(ui->Alpha->value());//͸����
        pFreeLineItem->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//ĩ�˼�ͷ
        //pFreeLineItem->setEndPointShape(ui->End_Cap->currentIndex());//ĩ����״
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
    case SAM_DRAW_OBJECT_LINE://ֱ��
        pLineItemOld->setLineType(ui->Line_Type->currentIndex());//������
        pLineItemOld->setLineWidth(ui->Line_Width->currentIndex()+1);//�߿��
        pLineItemOld->setLineColor(ui->Line_Color->palette().background().color());//������ɫ
        pLineItemOld->setAlpha(ui->Alpha->value());//͸����
        pLineItemOld->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//ĩ�˼�ͷ
        //pLineItem->setEndPointShape(ui->End_Cap->currentIndex());//ĩ����״
        pLineItemOld->setId(ui->spinbox->value());
        break;
    case SAM_DRAW_OBJECT_FOLDLINE://������
        pFoldLineItemOld->setLineType(ui->Line_Type->currentIndex());//������
        pFoldLineItemOld->setLineWidth(ui->Line_Width->currentIndex()+1);//�߿��
        pFoldLineItemOld->setLineColor(ui->Line_Color->palette().background().color());//������ɫ
        pFoldLineItemOld->setAlpha(ui->Alpha->value());//͸����
        pFoldLineItemOld->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//ĩ�˼�ͷ
        //pFoldLineItem->setEndPointShape(ui->End_Cap->currentIndex());//ĩ����״
        pFoldLineItemOld->setId(ui->spinbox->value());
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE://���ߡ�Բ��
        pLineCircleItemOld->setLineType(ui->Line_Type->currentIndex());//������
        pLineCircleItemOld->setLineWidth(ui->Line_Width->currentIndex()+1);//�߿��
        pLineCircleItemOld->setLineColor(ui->Line_Color->palette().background().color());//������ɫ
        pLineCircleItemOld->setAlpha(ui->Alpha->value());//͸����
        pLineCircleItemOld->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//ĩ�˼�ͷ
        //pLineCircleItem->setEndPointShape(ui->End_Cap->currentIndex());//ĩ����״
        pLineCircleItemOld->setId(ui->spinbox->value());
        break;
    case SAM_DRAW_OBJECT_FREELINE://����ֱ��
        pFreeLineItemOld->setLineType(ui->Line_Type->currentIndex());//������
        pFreeLineItemOld->setLineWidth(ui->Line_Width->currentIndex()+1);//�߿��
        pFreeLineItemOld->setLineColor(ui->Line_Color->palette().background().color());//������ɫ
        pFreeLineItemOld->setAlpha(ui->Alpha->value());//͸����
        pFreeLineItemOld->setLineEndArrow((LINE_END_ARROW_STYLE_E)ui->End_Arrow->currentIndex());//ĩ�˼�ͷ
        //pFreeLineItem->setEndPointShape(ui->End_Cap->currentIndex());//ĩ����״
        pFreeLineItemOld->setId(ui->spinbox->value());
        break;
/////////////////wxy add end
    default:
        break;
    }
    if(ui->spinbox->value() != oId && !pwnd->insertId(ui->spinbox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID�ظ������޸�ID��"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinbox->setFocus();
        return ;
    }

    accept();
}//
//��ʼ������
void QLineDlg::LineInit(QGraphicsItem *item)
{
  QColor tempColor;
  switch(item->type())
  {
  case SAM_DRAW_OBJECT_LINE_NEW://ֱ��
      ui->tabWidget->setTabText(0,tr("ֱ��"));
      this->setWindowTitle(tr("ֱ��"));
      pLineItem = dynamic_cast<QLineBasicItem *> (item);
      if (NULL != pLineItem)
      {
          ui->Alpha->setValue(pLineItem->getAlpha());//͸����
          ui->Line_Type->setCurrentIndex(pLineItem->getLineType());//������
          ui->Line_Width->setCurrentIndex(pLineItem->getLineWidth()-1);//�߿��
          tempColor=pLineItem->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//������ɫ
          ui->End_Arrow->setCurrentIndex(pLineItem->getEndArrow());//ĩ�˼�ͷ
          //ui->End_Cap->setCurrentIndex(pLineItem->getEndPointShape());//ĩ����״
          if(pSecurity)
          {
              pSecurity->init(pLineItem->GetSecurityPro());
          }
      }
      break;
  case SAM_DRAW_OBJECT_FOLDLINE_NEW://����
      ui->tabWidget->setTabText(0,tr("����"));
      this->setWindowTitle(tr("����"));
      pFoldLineItem = dynamic_cast<QFoldLineBasicItem *> (item);
      if (NULL != pFoldLineItem)
      {
          ui->Alpha->setValue(pFoldLineItem->getAlpha());//͸����
          ui->Line_Type->setCurrentIndex(pFoldLineItem->getLineType());//������
          ui->Line_Width->setCurrentIndex(pFoldLineItem->getLineWidth()-1);//�߿��
          tempColor=pFoldLineItem->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//������ɫ
          ui->End_Arrow->setCurrentIndex(pFoldLineItem->getEndArrow());//ĩ�˼�ͷ
          //ui->End_Cap->setCurrentIndex(pFoldLineItem->getEndPointShape());//ĩ����״
          if(pSecurity)
          {
              pSecurity->init(pFoldLineItem->GetSecurityPro());
          }
      }
      break;
  case SAM_DRAW_OBJECT_LINECIRCLE_NEW://���ߡ�Բ��
      ui->tabWidget->setTabText(0,tr("����/Բ��"));
      this->setWindowTitle(tr("����/Բ��"));
      pLineCircleItem = dynamic_cast<QLineCircleBasicItem *> (item);
      if (NULL != pLineCircleItem)
      {
          ui->Alpha->setValue(pLineCircleItem->getAlpha());//͸����
          ui->Line_Type->setCurrentIndex(pLineCircleItem->getLineType());//������
          ui->Line_Width->setCurrentIndex(pLineCircleItem->getLineWidth()-1);//�߿��
          tempColor=pLineCircleItem->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//������ɫ
          ui->End_Arrow->setCurrentIndex(pLineCircleItem->getEndArrow());//ĩ�˼�ͷ
          //ui->End_Cap->setCurrentIndex(pLineCircleItem->getEndPointShape());//ĩ����״
          if(pSecurity)
          {
              pSecurity->init(pLineCircleItem->GetSecurityPro());
          }
      }
      break;
  case SAM_DRAW_OBJECT_FREELINE_NEW://����ֱ��
      ui->tabWidget->setTabText(0,tr("����ֱ��"));
      this->setWindowTitle(tr("����ֱ��"));
      pFreeLineItem = dynamic_cast<QFreeLineBasicItem *> (item);
      if (NULL != pFreeLineItem)
      {
          ui->Alpha->setValue(pFreeLineItem->getAlpha());//͸����
          ui->Line_Type->setCurrentIndex(pFreeLineItem->getLineType());//������
          ui->Line_Width->setCurrentIndex(pFreeLineItem->getLineWidth()-1);//�߿��
          tempColor=pFreeLineItem->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//������ɫ
          ui->End_Arrow->setCurrentIndex(pFreeLineItem->getEndArrow());//ĩ�˼�ͷ
          //ui->End_Cap->setCurrentIndex(pFreeLineItem->getEndPointShape());//ĩ����״
          if(pSecurity)
          {
              pSecurity->init(pFreeLineItem->GetSecurityPro());
          }
      }
      break;
//////////////////wxy add start
  case SAM_DRAW_OBJECT_LINE://ֱ��
      ui->tabWidget->setTabText(0,tr("ֱ��"));
      this->setWindowTitle(tr("ֱ��"));
      pLineItemOld = dynamic_cast<QLineItem *> (item);
      if (NULL != pLineItemOld)
      {
          ui->Alpha->setValue(pLineItemOld->getAlpha());//͸����
          ui->Line_Type->setCurrentIndex(pLineItemOld->getLineType());//������
          ui->Line_Width->setCurrentIndex(pLineItemOld->getLineWidth()-1);//�߿��
          tempColor=pLineItemOld->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//������ɫ
          ui->End_Arrow->setCurrentIndex(pLineItemOld->getEndArrow());//ĩ�˼�ͷ
          //ui->End_Cap->setCurrentIndex(pLineItem->getEndPointShape());//ĩ����״
      }
      break;
  case SAM_DRAW_OBJECT_FOLDLINE://����
      ui->tabWidget->setTabText(0,tr("����"));
      this->setWindowTitle(tr("����"));
      pFoldLineItemOld = dynamic_cast<QFoldLineItem *> (item);
      if (NULL != pFoldLineItemOld)
      {
          ui->Alpha->setValue(pFoldLineItemOld->getAlpha());//͸����
          ui->Line_Type->setCurrentIndex(pFoldLineItemOld->getLineType());//������
          ui->Line_Width->setCurrentIndex(pFoldLineItemOld->getLineWidth()-1);//�߿��
          tempColor=pFoldLineItemOld->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//������ɫ
          ui->End_Arrow->setCurrentIndex(pFoldLineItemOld->getEndArrow());//ĩ�˼�ͷ
          //ui->End_Cap->setCurrentIndex(pFoldLineItem->getEndPointShape());//ĩ����״
      }
      break;
  case SAM_DRAW_OBJECT_LINECIRCLE://���ߡ�Բ��
      ui->tabWidget->setTabText(0,tr("����/Բ��"));
      this->setWindowTitle(tr("����/Բ��"));
      pLineCircleItemOld = dynamic_cast<QLineCircleItem *> (item);
      if (NULL != pLineCircleItemOld)
      {
          ui->Alpha->setValue(pLineCircleItemOld->getAlpha());//͸����
          ui->Line_Type->setCurrentIndex(pLineCircleItemOld->getLineType());//������
          ui->Line_Width->setCurrentIndex(pLineCircleItemOld->getLineWidth()-1);//�߿��
          tempColor=pLineCircleItemOld->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//������ɫ
          ui->End_Arrow->setCurrentIndex(pLineCircleItemOld->getEndArrow());//ĩ�˼�ͷ
          //ui->End_Cap->setCurrentIndex(pLineCircleItem->getEndPointShape());//ĩ����״
      }
      break;
  case SAM_DRAW_OBJECT_FREELINE://����ֱ��
      ui->tabWidget->setTabText(0,tr("����ֱ��"));
      this->setWindowTitle(tr("����ֱ��"));
      pFreeLineItemOld = dynamic_cast<QFreeLineItem *> (item);
      if (NULL != pFreeLineItemOld)
      {
          ui->Alpha->setValue(pFreeLineItemOld->getAlpha());//͸����
          ui->Line_Type->setCurrentIndex(pFreeLineItemOld->getLineType());//������
          ui->Line_Width->setCurrentIndex(pFreeLineItemOld->getLineWidth()-1);//�߿��
          tempColor=pFreeLineItemOld->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet( QString("background:%1").arg(tempColor.name()));//������ɫ
          ui->End_Arrow->setCurrentIndex(pFreeLineItemOld->getEndArrow());//ĩ�˼�ͷ
          //ui->End_Cap->setCurrentIndex(pFreeLineItem->getEndPointShape());//ĩ����״
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
    case SAM_DRAW_OBJECT_LINE://ֱ��
    case SAM_DRAW_OBJECT_LINE_NEW:
        pwnd->loadHelpHtm(SAM_DRAW_OBJECT_LINE);
        break;
    case SAM_DRAW_OBJECT_FOLDLINE://����
    case SAM_DRAW_OBJECT_FOLDLINE_NEW:
        pwnd->loadHelpHtm(SAM_DRAW_OBJECT_FOLDLINE);
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE://���ߡ�Բ��
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
        pwnd->loadHelpHtm(SAM_DRAW_OBJECT_ARCLINE);
        break;
     case SAM_DRAW_OBJECT_FREELINE://����ֱ��
     case SAM_DRAW_OBJECT_FREELINE_NEW:
         pwnd->loadHelpHtm(SAM_DRAW_OBJECT_FREELINE);
         break;
    }
}
