#include "qchartmeruler.h"
#include "ui_qchartmeruler.h"

extern MainWindow *pwnd;

QchartMeRuler::QchartMeRuler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QchartMeRuler)
{
    //nMainScale = 7;
    //nSubScale = 2;
    sCaleColor = pwnd->ColorTOString(QColor(255,0,0));
    ui->setupUi(this);
}

QchartMeRuler::~QchartMeRuler()
{
    delete ui;
}

void QchartMeRuler::on_m_mainScaleSpBox_valueChanged(int )
{
    //nMainScale = ui->m_mainScaleSpBox->value();
    //发送主刻度改变消息重绘仪表
    if(!bInitFlag)
    {
        return;
    }
    emit scalechange();
}

void QchartMeRuler::on_m_SubSgroupBox_clicked(bool checked)
{
    if (checked)
    {
        //nSubScale = ui->m_subScaleSpinBox->value();
    }
    else
    {
        //nSubScale = 0;
    }
    //发送次刻度改变消息
    if(!bInitFlag)
    {
        return;
    }
    emit scalechange();
}

void QchartMeRuler::on_m_subScaleSpinBox_valueChanged(int )
{
    //nSubScale = ui->m_subScaleSpinBox->value();
    //发送次刻度改变消息
    if(!bInitFlag)
    {
        return;
    }
    emit scalechange();
}

void QchartMeRuler::on_m_ScaleColorBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_ScaleColorBtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setScalebtnColor(const QColor &)));
}

void QchartMeRuler::setScalebtnColor(const QColor &mColor)
{
    sCaleColor = pwnd->ColorTOString(mColor);
    ui->m_ScaleColorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    //发送刻度颜色改变消息
    if(!bInitFlag)
    {
        return;
    }
    emit scalechange();
}

void QchartMeRuler::Init(ChartItem *pItem)
{
    bInitFlag = false;
    if (pItem)
    {
        ui->m_ShowScalevalueCkBox->setChecked(pItem->meter_st.bShowRuleValue);
        ui->m_mainScaleSpBox->setValue(pItem->meter_st.nMainScale);
        ui->m_subScaleSpinBox->setValue(pItem->meter_st.nSubScale);
        ui->m_ScaleColorBtn->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(pItem->meter_st.nScaleColor).name()));
        sCaleColor = pItem->meter_st.nScaleColor;
        ui->m_SubSgroupBox->setChecked(pItem->meter_st.nScaleMark);
    }
    else
    {
        ui->m_mainScaleSpBox->setValue(4);
        ui->m_subScaleSpinBox->setValue(2);
        ui->m_ScaleColorBtn->setStyleSheet(QString("background:%1").arg(QColor(255,0,0).name()));
    }
    bInitFlag = true;
}
void QchartMeRuler::MeterGenSave(struct METER_INFORMATION &meter_st)
{
    meter_st.bShowRuleValue = ui->m_ShowScalevalueCkBox->isChecked();
    meter_st.nMainScale = ui->m_mainScaleSpBox->value();
    meter_st.nSubScale = ui->m_subScaleSpinBox->value();
    meter_st.nScaleColor = pwnd->ColorTOString(ui->m_ScaleColorBtn->palette().background().color());
    meter_st.nScaleMark = ui->m_SubSgroupBox->isChecked();
}

int QchartMeRuler::onGetMainScale()
{
    return ui->m_mainScaleSpBox->value();
}

int QchartMeRuler::onGetSubScale()
{
    if(ui->m_SubSgroupBox->isChecked())
        return ui->m_subScaleSpinBox->value();
    else
        return 0;
}

QString QchartMeRuler::onGetScaleColor()
{
    return pwnd->ColorTOString(ui->m_ScaleColorBtn->palette().background().color());
}

void QchartMeRuler::on_m_ShowScalevalueCkBox_clicked(bool checked)
{
    if(!bInitFlag)
    {
        return;
    }
    emit scalechange();
}

void QchartMeRuler::onGetShowValue(bool &bShow)
{
    bShow = ui->m_ShowScalevalueCkBox->isChecked();
}
