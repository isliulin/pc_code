#include "ArcGenDlg.h"
#include "ui_ArcGenDlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

ArcGenDlg::ArcGenDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArcGenDlg)
{
    ui->setupUi(this);
    ui->spinbox->setValue(pwnd->getNewId());
    m_iType = SAM_DRAW_OBJECT_ARC_NEW;
    bInitFlag = false;
    pwnd->OnAddPattern(ui->m_Pattern);  //º”‘ÿ—˘ Ω
    for(int i=0;i<9;i++)
    {
        ui->m_LineWidth->addItem(QString::number(i+1));
    }

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    bInitFlag = true;
    pArc = NULL;
    pArcOld = NULL;
}

ArcGenDlg::~ArcGenDlg()
{
    delete ui;
}

void ArcGenDlg::InitParament()
{
    ui->m_LineColorBtn ->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    ui->m_BackColorBtn->setStyleSheet( QString("background:%1").arg(QColor(255,0,0).name()));
    ui->m_FrontColorBtn->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name())); 
    if(m_iType == SAM_DRAW_OBJECT_ARC_NEW)
    {
        pArc->SetBackColor(QColor(255,0,0));
    }
    else
    {
        pArcOld->SetBackColor(QColor(255,0,0));
    }
}


void ArcGenDlg::SetLineColor(const QColor & mColor)
{
    ui-> m_LineColorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(m_iType == SAM_DRAW_OBJECT_ARC_NEW)
    {
        pArc->SetLineColor(mColor);
    }
    else
    {
        pArcOld->SetLineColor(mColor);
    }
}

void ArcGenDlg::SetBackColor(const QColor & mColor)
{
    ui->m_BackColorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(m_iType == SAM_DRAW_OBJECT_ARC_NEW)
    {
        pArc->SetBackColor(mColor);
    }
    else
    {
        pArcOld->SetBackColor(mColor);
    }
}

void ArcGenDlg::SetFrontColor(const QColor & mColor)
{
    ui->m_FrontColorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(m_iType == SAM_DRAW_OBJECT_ARC_NEW)
    {
        pArc->SetFrontColor(mColor);
    }
    else
    {
        pArcOld->SetFrontColor(mColor);
    }
}

void ArcGenDlg::DoubleClickInit(QGraphicsItem *pItem)
{
    bInitFlag = false;
    if(pItem)
    {
       // QStringList sList;
        QColor mColor;

        DrawItemToScene GroupFunction;
        QGraphicsItem *pArcItem;
        GroupFunction.CopyItem(&pArcItem,pItem);
        if(pArcItem->type() == SAM_DRAW_OBJECT_ARC_NEW)
        {
            pArc = dynamic_cast<QArcBasicItem *> (pArcItem);
            ui->m_Alpha->setValue(pArc->GetAlpha());
            ui->m_LineType->setCurrentIndex(pArc->GetLineType());
            ui->m_LineWidth->setCurrentIndex(pArc->GetLineWidth()-1);

            mColor = pArc->GetLineColor();
            ui->m_LineColorBtn->setStyleSheet( QString("background:%1").arg(mColor.name()));
            pArc->SetLineColor(mColor);

            ui->m_Pattern->setCurrentIndex(pArc->GetPattern());

            mColor = pArc->GetBackColor();
            ui->m_BackColorBtn->setStyleSheet( QString("background:%1").arg(mColor.name()));
            pArc->SetBackColor(mColor);

            mColor = pArc->GetFrontColor();
            ui->m_FrontColorBtn->setStyleSheet( QString("background:%1").arg(mColor.name()));
            pArc->SetFrontColor(mColor);
            pCopyItem = pArc;
        }
        else
        {
            pArcOld = dynamic_cast<QArcItem *> (pArcItem);
            ui->m_Alpha->setValue(pArcOld->GetAlpha());
            ui->m_LineType->setCurrentIndex(pArcOld->GetLineType());
            ui->m_LineWidth->setCurrentIndex(pArcOld->GetLineWidth()-1);

            mColor = pArcOld->GetLineColor();
            ui->m_LineColorBtn->setStyleSheet( QString("background:%1").arg(mColor.name()));
            pArcOld->SetLineColor(mColor);

            ui->m_Pattern->setCurrentIndex(pArcOld->GetPattern());

            mColor = pArcOld->GetBackColor();
            ui->m_BackColorBtn->setStyleSheet( QString("background:%1").arg(mColor.name()));
            pArcOld->SetBackColor(mColor);

            mColor = pArcOld->GetFrontColor();
            ui->m_FrontColorBtn->setStyleSheet( QString("background:%1").arg(mColor.name()));
            pArcOld->SetFrontColor(mColor);
            pCopyItem = pArcOld;
        }
        SamDrawItemBase *samItem = dynamic_cast<SamDrawItemBase *> (pItem);
        if(samItem)
        {
            ui->spinbox->setValue(samItem->id());
        }

    }
    bInitFlag = true;
}

void ArcGenDlg::on_m_Alpha_valueChanged(int nAlpha)
{
    if(m_iType == SAM_DRAW_OBJECT_ARC_NEW)
    {
        pArc->SetAlpha(nAlpha);
    }
    else
    {
        pArcOld->SetAlpha(nAlpha);
    }
}

void ArcGenDlg::on_m_LineType_currentIndexChanged(int index)
{
    if(m_iType == SAM_DRAW_OBJECT_ARC_NEW)
    {
        pArc->SetLineType(index);
    }
    else
    {
        pArcOld->SetLineType(index);
    }
}

void ArcGenDlg::on_m_LineWidth_currentIndexChanged(int index)
{
    if(!bInitFlag )
        return;
    if(m_iType == SAM_DRAW_OBJECT_ARC_NEW)
    {
        pArc->SetLineWidth(index+1);
    }
    else
    {
        pArcOld->SetLineWidth(index+1);
    }
}

void ArcGenDlg::on_m_Pattern_currentIndexChanged(int index)
{
    if(!bInitFlag )
        return;
    if(m_iType == SAM_DRAW_OBJECT_ARC_NEW)
    {
        pArc->SetPattern(index);
    }
    else
    {
        pArcOld->SetPattern(index);
    }
}

void ArcGenDlg::on_m_LineColorBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_LineColorBtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(SetLineColor(const QColor &)));
}

void ArcGenDlg::on_m_BackColorBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_BackColorBtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(SetBackColor(const QColor &)));
}

void ArcGenDlg::on_m_FrontColorBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_FrontColorBtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(SetFrontColor(const QColor &)));
}

void ArcGenDlg::setItemType(int iType)
{
    m_iType = iType;
}
void ArcGenDlg::saveId()
{
    SamDrawItemBase *pItem = dynamic_cast<SamDrawItemBase *> (pCopyItem);
    if(pItem)
    {
        pItem->setId(ui->spinbox->value());
    }
}
int ArcGenDlg::getId()
{
    int id = -1;
    SamDrawItemBase *pItem = dynamic_cast<SamDrawItemBase *> (pCopyItem);
    if(pItem)
    {
        id = pItem->id();
    }
    return id;
}
