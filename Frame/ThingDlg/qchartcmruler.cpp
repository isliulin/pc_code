#include "qchartcmruler.h"
#include "ui_qchartcmruler.h"

extern MainWindow *pwnd;

QChartCMRuler::QChartCMRuler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QChartCMRuler)
{
    sCaleColor = pwnd->ColorTOString(QColor(255,0,0));
    ui->setupUi(this);
}

QChartCMRuler::~QChartCMRuler()
{
    delete ui;
}

void QChartCMRuler::on_m_mainScaleSpBox_valueChanged(int )
{
    nMainScale = ui->m_mainScaleSpBox->value();
    //发送刻度改变消息
    if(bInitFlag)
    {
        emit scalechange();
    }
}

void QChartCMRuler::on_m_SubSgroupBox_clicked(bool checked)
{
    if (checked)
    {
        nSubScale = ui->m_subScaleSpinBox->value();
    }
    else
    {
        nSubScale = 1;
    }
    //发送次刻度改变消息
    if(bInitFlag)
    {
        emit scalechange();
    }
}

void QChartCMRuler::on_m_ScaleColorBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_ScaleColorBtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setScalebtnColor(const QColor &)));
}

void QChartCMRuler::setScalebtnColor(const QColor &mColor)
{
    sCaleColor = pwnd->ColorTOString(mColor);
    ui->m_ScaleColorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    //发送刻度颜色改变消息
    if(bInitFlag)
    {
        emit scalechange();
    }
}

void QChartCMRuler::Init(ChartItem *pItem)
{
    bInitFlag = false;
    if (pItem)
    {
        ui->m_mainScaleSpBox->setValue(pItem->common_st.nMainScale);
        ui->m_subScaleSpinBox->setValue(pItem->common_st.nSubScale);
        ui->m_SubSgroupBox->setChecked(pItem->common_st.nScaleMark);
        ui->m_ScaleColorBtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->common_st.nRulingColor).name()));
        if(pItem->common_st.nScaleMark)
        {
           nSubScale =  pItem->common_st.nSubScale;
        }
        else
        {
            nSubScale = 1;
        }
        nMainScale = pItem->common_st.nMainScale;
        sCaleColor = pItem->common_st.nRulingColor;
        ui->m_ShowScalevalueCkBox->setChecked(pItem->common_st.bShowRuleValue);;
    }
    else
    {
        ui->m_mainScaleSpBox->setValue(4);
        ui->m_subScaleSpinBox->setValue(2);
        ui->m_SubSgroupBox->setChecked(false);
        ui->m_ScaleColorBtn->setStyleSheet(QString("background:%1").arg(QColor(255,0,0).name()));

        nMainScale = 4;
        nSubScale = 1;
    }
    bInitFlag = true;
}

void QChartCMRuler::on_m_subScaleSpinBox_valueChanged(int )
{
    nSubScale = ui->m_subScaleSpinBox->value();
    //发送次刻度改变消息
    if(bInitFlag)
    {
        emit scalechange();
    }
}
void QChartCMRuler::CommonGenSave(struct COMMON_INFORMATION &common_st)
{
    common_st.nMainScale = ui->m_mainScaleSpBox->value();
    common_st.nSubScale = ui->m_subScaleSpinBox->value();
    common_st.nScaleMark = ui->m_SubSgroupBox->isChecked();
    common_st.bShowRuleValue = ui->m_ShowScalevalueCkBox->isChecked();
    common_st.nRulingColor = pwnd->ColorTOString(ui->m_ScaleColorBtn->palette().background().color());
}

int QChartCMRuler::onGetMainScale()
{
    return 0;
}


int QChartCMRuler::onGetSubScale()
{
    return 0;
}

void QChartCMRuler::onGetShowValue(bool &bShow)//获取是否显示刻度值
{
    bShow = ui->m_ShowScalevalueCkBox->isChecked();
}

void QChartCMRuler::on_m_ShowScalevalueCkBox_clicked(bool checked)
{
    if(bInitFlag)
    {
        emit scalechange();
    }
}
