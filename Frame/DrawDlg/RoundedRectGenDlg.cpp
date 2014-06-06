#include "RoundedRectGenDlg.h"
#include "ui_RoundedRectGenDlg.h"

#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

RoundedRectGenDlg::RoundedRectGenDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoundedRectGenDlg)
{
    ui->setupUi(this);

    pRoundRect = NULL;
    pRoundRectOld = NULL;
    m_iType = SAM_DRAW_OBJECT_ROUNDEDRECT_NEW;

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    bInitFlag = false;
    pwnd->OnAddPattern(ui->m_Pattern);  //º”‘ÿ—˘ Ω
    for(int i=0;i<9;i++)
    {
        ui->m_LineWidth->addItem(QString::number(i+1));
    }

    bInitFlag = true;
}

RoundedRectGenDlg::~RoundedRectGenDlg()
{
    delete ui;
}

void RoundedRectGenDlg::InitParament()
{
    ui->m_LineColorBtn ->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    ui->m_BackColorBtn->setStyleSheet( QString("background:%1").arg(QColor(255,255,255).name()));
    ui->m_FrontColorBtn->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    ui->m_LineType->setCurrentIndex(1);
    ui->m_LineWidth->setCurrentIndex(0);
    if(m_iType == SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)
    {
        pRoundRect->SetLineWidth(2);
    }
    else
    {
        pRoundRectOld->SetLineWidth(2);

    }
}


void RoundedRectGenDlg::SetLineColor(const QColor & mColor)
{
    ui-> m_LineColorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(m_iType == SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)
    {
        pRoundRect->SetLineColor(mColor);
    }
    else
    {
        pRoundRectOld->SetLineColor(mColor);
    }
}

void RoundedRectGenDlg::SetBackColor(const QColor & mColor)
{
    ui->m_BackColorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(m_iType == SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)
    {
        pRoundRect->SetBackColor(mColor);
    }
    else
    {
        pRoundRectOld->SetBackColor(mColor);
    }
}

void RoundedRectGenDlg::SetFrontColor(const QColor & mColor)
{
    ui->m_FrontColorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(m_iType == SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)
    {
        pRoundRect->SetFrontColor(mColor);
    }
    else
    {
        pRoundRectOld->SetFrontColor(mColor);
    }
}

void RoundedRectGenDlg::on_m_XR_valueChanged(int nValue)
{
    if(m_iType == SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)
    {
        pRoundRect->SetxRadius(nValue);
    }
    else
    {
        pRoundRectOld->SetxRadius(nValue);
    }
}

void RoundedRectGenDlg::on_m_YR_valueChanged(int nValue)
{
    if(m_iType == SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)
    {
        pRoundRect->SetyRadius(nValue);
    }
    else
    {
        pRoundRectOld->SetyRadius(nValue);
    }
}

void RoundedRectGenDlg::on_m_Alpha_valueChanged(int nAlpha)
{
    if(m_iType == SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)
    {
        pRoundRect->SetAlpha(nAlpha);
    }
    else
    {
        pRoundRectOld->SetAlpha(nAlpha);
    }
}

void RoundedRectGenDlg::on_m_LineType_currentIndexChanged(int index)
{
    if(m_iType == SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)
    {
        pRoundRect->SetLineType(index);
    }
    else
    {
        pRoundRectOld->SetLineType(index);
    }
}

void RoundedRectGenDlg::on_m_LineWidth_currentIndexChanged(int index)
{
    if(!bInitFlag )
        return;
    if(m_iType == SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)
    {
        pRoundRect->SetLineWidth(index+1);
    }
    else
    {
        pRoundRectOld->SetLineWidth(index+1);
    }
}

void RoundedRectGenDlg::on_m_Pattern_currentIndexChanged(int index)
{
    if(!bInitFlag )
        return;
    if(m_iType == SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)
    {
        pRoundRect->SetPattern(index);
    }
    else
    {
        pRoundRectOld->SetPattern(index);
    }
}

void RoundedRectGenDlg::DoubleClickInit(QGraphicsItem *pItem)
{
    bInitFlag = false;
    if(pItem)
    {
        QColor mColor;
        DrawItemToScene GroupFunction;
        QGraphicsItem *pRItem;
        GroupFunction.CopyItem(&pRItem,pItem);
        if(pRItem->type() == SAM_DRAW_OBJECT_ROUNDEDRECT)
        {
            pRoundRectOld = dynamic_cast<QRoundedRect *> (pRItem);
            ui->m_XR->setValue(pRoundRectOld->GetxRadius());
            ui->m_YR->setValue(pRoundRectOld->GetyRadius());
            ui->m_Alpha->setValue(pRoundRectOld->GetAlpha());
            ui->m_LineType->setCurrentIndex(pRoundRectOld->GetLineType());
            ui->m_LineWidth->setCurrentIndex(pRoundRectOld->GetLineWidth()-1);

            mColor = pRoundRectOld->GetLineColor();
            ui->m_LineColorBtn->setStyleSheet( QString("background:%1").arg(mColor.name()));
            pRoundRectOld->SetLineColor(mColor);

            ui->m_Pattern->setCurrentIndex(pRoundRectOld->GetPattern());

            mColor = pRoundRectOld->GetBackColor();
            ui->m_BackColorBtn->setStyleSheet( QString("background:%1").arg(mColor.name()));
            pRoundRectOld->SetBackColor(mColor);

            mColor = pRoundRectOld->GetFrontColor();
            ui->m_FrontColorBtn->setStyleSheet( QString("background:%1").arg(mColor.name()));
            pRoundRectOld->SetFrontColor(mColor);
            pCopyItem = pRoundRectOld;
            ui->spinbox->setValue(pRoundRectOld->id());
        }
        else
        {
            pRoundRect = dynamic_cast<QRoundedRectBasic *> (pRItem);
            ui->m_XR->setValue(pRoundRect->GetxRadius());
            ui->m_YR->setValue(pRoundRect->GetyRadius());
            ui->m_Alpha->setValue(pRoundRect->GetAlpha());
            ui->m_LineType->setCurrentIndex(pRoundRect->GetLineType());
            ui->m_LineWidth->setCurrentIndex(pRoundRect->GetLineWidth()-1);

            mColor = pRoundRect->GetLineColor();
            ui->m_LineColorBtn->setStyleSheet( QString("background:%1").arg(mColor.name()));
            pRoundRect->SetLineColor(mColor);

            ui->m_Pattern->setCurrentIndex(pRoundRect->GetPattern());

            mColor = pRoundRect->GetBackColor();
            ui->m_BackColorBtn->setStyleSheet( QString("background:%1").arg(mColor.name()));
            pRoundRect->SetBackColor(mColor);

            mColor = pRoundRect->GetFrontColor();
            ui->m_FrontColorBtn->setStyleSheet( QString("background:%1").arg(mColor.name()));
            pRoundRect->SetFrontColor(mColor);
            pCopyItem = pRoundRect;
            ui->spinbox->setValue(pRoundRect->id());
        }
    }
    bInitFlag = true;
}

void RoundedRectGenDlg::on_m_LineColorBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_LineColorBtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(SetLineColor(const QColor &)));
}

void RoundedRectGenDlg::on_m_BackColorBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_BackColorBtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(SetBackColor(const QColor &)));
}

void RoundedRectGenDlg::on_m_FrontColorBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_FrontColorBtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(SetFrontColor(const QColor &)));
}

void RoundedRectGenDlg::setItemType(int iType)
{
    m_iType = iType;
}
void RoundedRectGenDlg::saveId()
{
    SamDrawItemBase *pItem = dynamic_cast<SamDrawItemBase *> (pCopyItem);
    if(pItem)
    {
        pItem->setId(ui->spinbox->value());
    }
}
