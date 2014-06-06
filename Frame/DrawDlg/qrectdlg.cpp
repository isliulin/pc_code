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
    //ui->groupBox_4->setHidden(true);//���� ֻ�о����õ��ñ����������û��
    pwnd->OnAddPattern(ui->Pattern);  //������ʽ
    //colorPicker=NULL;
    colorPicker2=NULL;
    colorPicker3=NULL;

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
            ui->tabWidget->addTab(pSecurity, tr("Ȩ������"));
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
        ui->tabWidget->addTab(pSecurity, tr("Ȩ������"));
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
    case SAM_DRAW_OBJECT_RECT_NEW://����
        pRectItem->SetLineType(ui->Line_Type->currentIndex());//������
        pRectItem->SetLineWidth(ui->Line_Width->currentIndex()+1);//�߿��
        pRectItem->SetLineColor(ui->Line_Color->palette().background().color());//������ɫ
        pRectItem->SetPattern(ui->Pattern->currentIndex());//��ʽ
        pRectItem->SetBackColor(ui->Back_Color->palette().background().color());
        pRectItem->SetFrontColor(ui->Fore_Color->palette().background().color());
        pRectItem->SetAlpha(ui->Alpha->value());//͸����
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
    case SAM_DRAW_OBJECT_ELIPSE_NEW://��Բ
        //pElipseItem->SetLineType(ui->Line_Type->currentIndex());//������
        pElipseItem->SetLineWidth(ui->Line_Width->currentIndex()+1);//�߿��
        pElipseItem->SetLineColor(ui->Line_Color->palette().background().color());//������ɫ
        pElipseItem->SetPattern(ui->Pattern->currentIndex());//��ʽ
        pElipseItem->SetBackColor(ui->Back_Color->palette().background().color());
        pElipseItem->SetFrontColor(ui->Fore_Color->palette().background().color());
        pElipseItem->SetAlpha(ui->Alpha->value());//͸����
        pElipseItem->SetLineType(ui->Line_Type->currentIndex());//������
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
    case SAM_DRAW_OBJECT_POLYGON_NEW://�����
        pPolygonItem->setLineType(ui->Line_Type->currentIndex());//������
        pPolygonItem->setLineWidth(ui->Line_Width->currentIndex()+1);//�߿��
        pPolygonItem->setLineColor(ui->Line_Color->palette().background().color());//������ɫ
        pPolygonItem->setPattern(ui->Pattern->currentIndex());//��ʽ
        pPolygonItem->setBackColor(ui->Back_Color->palette().background().color());
        pPolygonItem->setFrontColor(ui->Fore_Color->palette().background().color());
        pPolygonItem->setAlpha(ui->Alpha->value());//͸����
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
    case SAM_DRAW_OBJECT_RECT://����
        pRectItemOld->SetLineType(ui->Line_Type->currentIndex());//������
        pRectItemOld->SetLineWidth(ui->Line_Width->currentIndex()+1);//�߿��
        pRectItemOld->SetLineColor(ui->Line_Color->palette().background().color());//������ɫ
        pRectItemOld->SetPattern(ui->Pattern->currentIndex());//��ʽ
        pRectItemOld->SetBackColor(ui->Back_Color->palette().background().color());
        pRectItemOld->SetFrontColor(ui->Fore_Color->palette().background().color());
        pRectItemOld->SetAlpha(ui->Alpha->value());//͸����
        pRectItemOld->SetId(ui->nType->currentIndex());
        pRectItemOld->setId(ui->spinbox->value());
        break;
    case SAM_DRAW_OBJECT_ELIPSE://��Բ
        //pElipseItem->SetLineType(ui->Line_Type->currentIndex());//������
        pElipseItemOld->SetLineWidth(ui->Line_Width->currentIndex()+1);//�߿��
        pElipseItemOld->SetLineColor(ui->Line_Color->palette().background().color());//������ɫ
        pElipseItemOld->SetPattern(ui->Pattern->currentIndex());//��ʽ
        pElipseItemOld->SetBackColor(ui->Back_Color->palette().background().color());
        pElipseItemOld->SetFrontColor(ui->Fore_Color->palette().background().color());
        pElipseItemOld->SetAlpha(ui->Alpha->value());//͸����
        pElipseItemOld->SetLineType(ui->Line_Type->currentIndex());//������
        pElipseItemOld->setId(ui->spinbox->value());
        break;
    case SAM_DRAW_OBJECT_POLYGON://�����
        pPolygonItemOld->setLineType(ui->Line_Type->currentIndex());//������
        pPolygonItemOld->setLineWidth(ui->Line_Width->currentIndex()+1);//�߿��
        pPolygonItemOld->setLineColor(ui->Line_Color->palette().background().color());//������ɫ
        pPolygonItemOld->setPattern(ui->Pattern->currentIndex());//��ʽ
        pPolygonItemOld->setBackColor(ui->Back_Color->palette().background().color());
        pPolygonItemOld->setFrontColor(ui->Fore_Color->palette().background().color());
        pPolygonItemOld->setAlpha(ui->Alpha->value());//͸����
        pPolygonItemOld->setId(ui->spinbox->value());
        break;
////////////////wxy add end
     default:
        break;
    }
    accept();
}//
//��ʼ������
void QRectDlg::RectInit(QGraphicsItem *item)
{
    QColor tempColor;
    switch(item->type())
    {
    case SAM_DRAW_OBJECT_RECT_NEW://����
           ui->tabWidget->setTabText(0,tr("����"));
        this->setWindowTitle(tr("����"));
        ui->nType->setEnabled(true);
        //ui->groupBox_4->setHidden(false);//����
        pRectItem = dynamic_cast<QRectBasicItem *> (item);
        if (NULL != pRectItem)
        {
            ui->Alpha->setValue(pRectItem->GetAlpha());//͸����
            ui->Line_Type->setCurrentIndex(pRectItem->GetLineType());//������
            ui->Line_Width->setCurrentIndex(pRectItem->GetLineWidth()-1);//�߿��
            tempColor=pRectItem->GetLineColor();
            tempColor.setAlpha(255);
            ui->Line_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
            ui->Pattern->setCurrentIndex(pRectItem->GetPattern());//��ʽ
            tempColor=pRectItem->GetBackColor();
            tempColor.setAlpha(255);
            ui->Back_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
            tempColor=pRectItem->GetFrontColor();
            tempColor.setAlpha(255);
            ui->Fore_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
            ui->nType->setCurrentIndex(pRectItem->GetID());
            if(pSecurity)
            {
                pSecurity->init(pRectItem->GetSecurityPro());
            }
        }
        break;
  case SAM_DRAW_OBJECT_ELIPSE_NEW://Բ/��Բ
      ui->tabWidget->setTabText(0,tr("Բ/��Բ"));
      this->setWindowTitle(tr("Բ/��Բ"));
      pElipseItem = dynamic_cast<QElipseBasicItem *> (item);
      if (NULL != pElipseItem)
      {

          ui->Alpha->setValue(pElipseItem->GetAlpha());//͸����
          ui->Line_Type->setCurrentIndex(pElipseItem->GetLineType());//������
          ui->Line_Width->setCurrentIndex(pElipseItem->GetLineWidth()-1);//�߿��
          tempColor=pElipseItem->GetLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
          ui->Pattern->setCurrentIndex(pElipseItem->GetPattern());//��ʽ
          tempColor=pElipseItem->GetBackColor();
          tempColor.setAlpha(255);
          ui->Back_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
          tempColor=pElipseItem->GetFrontColor();
          tempColor.setAlpha(255);
          ui->Fore_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
          if(pSecurity)
          {
              pSecurity->init(pElipseItem->GetSecurityPro());
          }
      }
      break;
  case SAM_DRAW_OBJECT_POLYGON_NEW://�����
      ui->tabWidget->setTabText(0,tr("�����"));
      this->setWindowTitle(tr("�����"));
      pPolygonItem = dynamic_cast<QPolygonBasicItem *> (item);
      if (NULL != pPolygonItem)
      {
          ui->Alpha->setValue(pPolygonItem->getAlpha());//͸����
          ui->Line_Type->setCurrentIndex(pPolygonItem->getLineType());//������
          ui->Line_Width->setCurrentIndex(pPolygonItem->getLineWidth()-1);//�߿��
          tempColor=pPolygonItem->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
          ui->Pattern->setCurrentIndex(pPolygonItem->getPattern());//��ʽ
          tempColor=pPolygonItem->getBackColor();
          tempColor.setAlpha(255);
          ui->Back_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
          tempColor=pPolygonItem->getFrontColor();
          tempColor.setAlpha(255);
          ui->Fore_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
          if(pSecurity)
          {
              pSecurity->init(pPolygonItem->GetSecurityPro());
          }
       }
      break;
////////////////////wxy add start
    case SAM_DRAW_OBJECT_RECT://����
           ui->tabWidget->setTabText(0,tr("����"));
        this->setWindowTitle(tr("����"));
        ui->nType->setEnabled(true);
        //ui->groupBox_4->setHidden(false);//����
        pRectItemOld = dynamic_cast<QRectItem *> (item);
        if (NULL != pRectItemOld)
        {
            ui->Alpha->setValue(pRectItemOld->GetAlpha());//͸����
            ui->Line_Type->setCurrentIndex(pRectItemOld->GetLineType());//������
            ui->Line_Width->setCurrentIndex(pRectItemOld->GetLineWidth()-1);//�߿��
            tempColor=pRectItemOld->GetLineColor();
            tempColor.setAlpha(255);
            ui->Line_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
            ui->Pattern->setCurrentIndex(pRectItemOld->GetPattern());//��ʽ
            tempColor=pRectItemOld->GetBackColor();
            tempColor.setAlpha(255);
            ui->Back_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
            tempColor=pRectItemOld->GetFrontColor();
            tempColor.setAlpha(255);
            ui->Fore_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
            ui->nType->setCurrentIndex(pRectItemOld->GetID());
        }
        break;
  case SAM_DRAW_OBJECT_ELIPSE://Բ/��Բ
      ui->tabWidget->setTabText(0,tr("Բ/��Բ"));
      this->setWindowTitle(tr("Բ/��Բ"));
      pElipseItemOld = dynamic_cast<QElipseItem *> (item);
      if (NULL != pElipseItemOld)
      {

          ui->Alpha->setValue(pElipseItemOld->GetAlpha());//͸����
          ui->Line_Type->setCurrentIndex(pElipseItemOld->GetLineType());//������
          ui->Line_Width->setCurrentIndex(pElipseItemOld->GetLineWidth()-1);//�߿��
          tempColor=pElipseItemOld->GetLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
          ui->Pattern->setCurrentIndex(pElipseItemOld->GetPattern());//��ʽ
          tempColor=pElipseItemOld->GetBackColor();
          tempColor.setAlpha(255);
          ui->Back_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
          tempColor=pElipseItemOld->GetFrontColor();
          tempColor.setAlpha(255);
          ui->Fore_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
      }
      break;
  case SAM_DRAW_OBJECT_POLYGON://�����
      ui->tabWidget->setTabText(0,tr("�����"));
      this->setWindowTitle(tr("�����"));
      pPolygonItemOld = dynamic_cast<QPolygonItem *> (item);
      if (NULL != pPolygonItemOld)
      {
          ui->Alpha->setValue(pPolygonItemOld->getAlpha());//͸����
          ui->Line_Type->setCurrentIndex(pPolygonItemOld->getLineType());//������
          ui->Line_Width->setCurrentIndex(pPolygonItemOld->getLineWidth()-1);//�߿��
          tempColor=pPolygonItemOld->getLineColor();
          tempColor.setAlpha(255);
          ui->Line_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
          ui->Pattern->setCurrentIndex(pPolygonItemOld->getPattern());//��ʽ
          tempColor=pPolygonItemOld->getBackColor();
          tempColor.setAlpha(255);
          ui->Back_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
          tempColor=pPolygonItemOld->getFrontColor();
          tempColor.setAlpha(255);
          ui->Fore_Color->setStyleSheet(QString("background:%1").arg(tempColor.name()));//������ɫ
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
    case SAM_DRAW_OBJECT_RECT://����
    case SAM_DRAW_OBJECT_RECT_NEW:
        pwnd->loadHelpHtm(SAM_DRAW_OBJECT_RECT);
        break;
    case SAM_DRAW_OBJECT_ELIPSE://Բ/��Բ
    case SAM_DRAW_OBJECT_ELIPSE_NEW:
        pwnd->loadHelpHtm(SAM_DRAW_OBJECT_ELIPSE);
        break;
    case SAM_DRAW_OBJECT_POLYGON://�����
    case SAM_DRAW_OBJECT_POLYGON_NEW:
        pwnd->loadHelpHtm(SAM_DRAW_OBJECT_POLYGON);
        break;
    }
}
