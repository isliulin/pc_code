#include "qchartmecolor.h"
#include "ui_qchartmecolor.h"
#include "Frame/addressinputdialog.h"

extern MainWindow *pwnd;
QChartMeColor::QChartMeColor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QChartMeColor)
{
    ui->setupUi(this);
}

QChartMeColor::~QChartMeColor()
{
    delete ui;
}

void QChartMeColor::Init(ChartItem *pItem)
{
    bInitFlag = false;
    if(pItem)
    {
        shapename = pItem->data(GROUP_NAME_KEY).toString();//图形ID名称
        ui->m_alarmckBox->setChecked(pItem->meter_st.sAlarm.bAlarm);
        if(pItem->meter_st.sAlarm.bAlarm)
        {
            ui->m_AlarmgroupBox->setEnabled(true);
        }
        else
        {
            ui->m_AlarmgroupBox->setEnabled(false);
        }
        ui->m_AlarmcbBox->setCurrentIndex(pItem->meter_st.sAlarm.nType);
        if(0 == pItem->meter_st.sAlarm.nType)
        {
            ui->m_AlarmMinspBox->show();
            ui->m_AlarmMaxspBox->show();
            ui->m_AddressMinlineEdit->hide();
            ui->m_AddressMaxlineEdit->hide();
            ui->m_AddressMin_EntryBtn->hide();
            ui->m_AddressMax_EntryBtn->hide();
            ui->m_AlarmMinspBox->setText(pItem->meter_st.sAlarm.nMin);
            ui->m_AlarmMaxspBox->setText(pItem->meter_st.sAlarm.nMax);
        }
        else
        {
            ui->m_AlarmMinspBox->hide();
            ui->m_AlarmMaxspBox->hide();
            ui->m_AddressMinlineEdit->show();
            ui->m_AddressMaxlineEdit->show();
            ui->m_AddressMin_EntryBtn->show();
            ui->m_AddressMax_EntryBtn->show();
            ui->m_AddressMinlineEdit->setText(pItem->meter_st.sAlarm.nMin);
            ui->m_AddressMaxlineEdit->setText(pItem->meter_st.sAlarm.nMax);
            ui->m_AlarmMinspBox->setText("0");
            ui->m_AlarmMaxspBox->setText("100");
        }
        ui->m_Alarmshowcolorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->meter_st.sAlarm.nTextColor).name()));
        ui->m_Alarmshapecolorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->meter_st.sAlarm.nDesignColor).name()));

        ui->m_showcolorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->meter_st.nTextColor).name()));
        ui->m_backcolorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->meter_st.nDesignColor).name()));
        nBackColor = pItem->meter_st.nDesignColor;
        nPointColor = pItem->meter_st.nTextColor;
        ui->m_alarmckBox->setChecked(pItem->meter_st.bAlarm);
        ui->m_PointTypecbBox->setCurrentIndex(pItem->meter_st.nPointType);
    }
    else
    {
        shapename = "001";
        ui->m_alarmckBox->setChecked(false);
        ui->m_AlarmgroupBox->setEnabled(false);
        ui->m_AlarmMinspBox->show();
        ui->m_AlarmMaxspBox->show();
        ui->m_AddressMinlineEdit->hide();
        ui->m_AddressMaxlineEdit->hide();
        ui->m_AddressMin_EntryBtn->hide();
        ui->m_AddressMax_EntryBtn->hide();
        ui->m_AlarmMinspBox->setText("0");
        ui->m_AlarmMaxspBox->setText("100");
        ui->m_Alarmshowcolorbtn->setStyleSheet(QString("background:%1").arg(QColor(166,166,255).name()));
        ui->m_Alarmshapecolorbtn->setStyleSheet(QString("background:%1").arg(QColor(255,255,255).name()));

        nPointColor = pwnd->ColorTOString(QColor(255,0,0));
        nBackColor = pwnd->ColorTOString(QColor(0,255,255));
        ui->m_showcolorbtn->setStyleSheet(QString("background:%1").arg(QColor(255,0,0).name()));
        ui->m_backcolorbtn->setStyleSheet(QString("background:%1").arg(QColor(0,255,255).name()));
    }
    bInitFlag = true;
}

void QChartMeColor::on_m_showcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_showcolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setshowcolorbtnColor(const QColor &)));
}

void QChartMeColor::setshowcolorbtnColor(const QColor &mColor)
{
    nPointColor = pwnd->ColorTOString(mColor);
    ui->m_showcolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(bInitFlag)
    {
        emit SetMeterPointColor();
    }
}

void QChartMeColor::setbackcolorbtnColor(const QColor &mColor)
{
    nBackColor = pwnd->ColorTOString(mColor);
    ui->m_backcolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(bInitFlag)
    {
        emit SetMeterBackColor();
    }
}

void QChartMeColor::on_m_backcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_backcolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setbackcolorbtnColor(const QColor &)));
}

bool QChartMeColor::MeterColorSave(struct METER_INFORMATION &meter_st)
{
    QString sTmp;
    int nState;
    sTmp = pwnd->ColorTOString(ui->m_showcolorbtn->palette().background().color());//指针颜色
    meter_st.nTextColor = sTmp;

    sTmp.clear();
    sTmp = pwnd->ColorTOString(ui->m_backcolorbtn->palette().background().color());//背景颜色
    meter_st.nDesignColor = sTmp;

    sTmp.clear();
    meter_st.bAlarm = ui->m_alarmckBox->isChecked();          //報警設置

    meter_st.sAlarm.bAlarm = ui->m_alarmckBox->isChecked();
    meter_st.sAlarm.nType = ui->m_AlarmcbBox->currentIndex();

    if(0 == ui->m_AlarmcbBox->currentIndex())
    {
        meter_st.sAlarm.nMin = ui->m_AlarmMinspBox->text();
        meter_st.sAlarm.nMax = ui->m_AlarmMaxspBox->text();
    }
    else
    {
        if(! pwnd->IsAddressCheckRight(AlarmMax_Address_Keyboard,tr("上限地址"),ui->m_AddressMaxlineEdit,1))
        {
            ui->m_AddressMaxlineEdit->setFocus();
            return false;
        }
        meter_st.sAlarm.nMaxaddr = AlarmMax_Address_Keyboard;

        if(! pwnd->IsAddressCheckRight(AlarmMin_Address_Keyboard,tr("下限地址"),ui->m_AddressMinlineEdit,1))
        {
            ui->m_AddressMinlineEdit->setFocus();
            return false;
        }
        meter_st.sAlarm.nMinaddr = AlarmMin_Address_Keyboard;

        meter_st.sAlarm.nMin = ui->m_AddressMinlineEdit->text();
        meter_st.sAlarm.nMax = ui->m_AddressMaxlineEdit->text();
    }

    meter_st.sAlarm.nTextColor = pwnd->ColorTOString(ui->m_Alarmshowcolorbtn->palette().background().color());
    meter_st.sAlarm.nDesignColor = pwnd->ColorTOString(ui->m_Alarmshapecolorbtn->palette().background().color());
    meter_st.nPointType = ui->m_PointTypecbBox->currentIndex();
    return true;
}

void QChartMeColor::on_load_shapeBtn_clicked()
{
    pwnd->nLoadShapeFlag = 1;//加载图表的图形文件
    pwnd->nLoadShapeType = 4;//仪表形状选择
    LoadShape *pShapeDlg = new LoadShape(this);
    if(pShapeDlg->exec() == QDialog::Accepted)
    {
        nMeterType = pShapeDlg->pCopyItem->data(GROUP_TYPE_KEY).toInt();
        shapename = pShapeDlg->pCopyItem->data(GROUP_NAME_KEY).toString();
        emit reDrawMeter();
        setbackcolorbtnColor(ui->m_backcolorbtn->palette().background().color());
        setshowcolorbtnColor(ui->m_showcolorbtn->palette().background().color());
      }
    pwnd->nLoadShapeType = 0;
    pwnd->nLoadShapeFlag = 0;
    pShapeDlg->deleteLater();
    pShapeDlg = NULL;
}

void QChartMeColor::on_m_alarmckBox_clicked()
{
    if(ui->m_alarmckBox->isChecked())
    {
        ui->m_AlarmgroupBox->setEnabled(true);
    }
    else
    {
        ui->m_AlarmgroupBox->setEnabled(false);
    }
}

void QChartMeColor::on_m_AlarmcbBox_currentIndexChanged(int index)
{
    if(0 == index)
    {
        ui->m_AlarmMinspBox->show();
        ui->m_AlarmMaxspBox->show();
        ui->m_AddressMinlineEdit->hide();
        ui->m_AddressMaxlineEdit->hide();
        ui->m_AddressMin_EntryBtn->hide();
        ui->m_AddressMax_EntryBtn->hide();
        //地址隐藏
    }
    else
    {
        ui->m_AlarmMinspBox->hide();
        ui->m_AlarmMaxspBox->hide();
        ui->m_AddressMinlineEdit->show();
        ui->m_AddressMaxlineEdit->show();
        ui->m_AddressMin_EntryBtn->show();
        ui->m_AddressMax_EntryBtn->show();
    }
}

void QChartMeColor::on_m_Alarmshowcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_Alarmshowcolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setAlarmShowBtnColor(const QColor &)));
}

void QChartMeColor::on_m_Alarmshapecolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_Alarmshapecolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setAlarmShapeBtnColor(const QColor &)));
}

void QChartMeColor::setAlarmShowBtnColor(const QColor &mColor)//设置报警显示颜色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_Alarmshowcolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
void QChartMeColor::setAlarmShapeBtnColor(const QColor &mColor)//设置报警图案颜色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_Alarmshapecolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QChartMeColor::on_m_AddressMin_EntryBtn_clicked()
{
    QString addrStr = ui->m_AddressMinlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(AlarmMin_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_AddressMinlineEdit->setText(AlarmMin_Address_Keyboard.sShowAddr);
    }
}

void QChartMeColor::on_m_AddressMax_EntryBtn_clicked()
{
    QString addrStr = ui->m_AddressMaxlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(AlarmMax_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_AddressMaxlineEdit->setText(AlarmMax_Address_Keyboard.sShowAddr);
    }
}

QString QChartMeColor::onGetShapeName()
{
    return shapename;
}

void QChartMeColor::setdataRange(double dMax, double dMin,int type)
{
    //QIntValidator* aIntValidator = new QIntValidator(this);
    DoubleValidator *aDoubleValidator = new DoubleValidator(this);
    aDoubleValidator->setNotation(QDoubleValidator::StandardNotation);

    if(0 == type)
    {
        aDoubleValidator->setRange(dMin,dMax,4);
        ui->m_AlarmMinspBox->setValidator(aDoubleValidator);
        ui->m_AlarmMaxspBox->setValidator(aDoubleValidator);
    }
    else
    {
        aDoubleValidator->setRange(dMin, dMax,0);
        ui->m_AlarmMinspBox->setValidator(aDoubleValidator);
        ui->m_AlarmMaxspBox->setValidator(aDoubleValidator);
    }

    if(ui->m_AlarmMaxspBox->text().isEmpty()
        || ui->m_AlarmMaxspBox->text().toDouble() > dMax
                || ui->m_AlarmMaxspBox->text().toDouble() < dMin)
    {
       ui->m_AlarmMaxspBox->setText(QString::number(dMax,'g',10));
    }
    if(ui->m_AlarmMinspBox->text().isEmpty()
        || ui->m_AlarmMinspBox->text().toDouble() > dMax
                || ui->m_AlarmMinspBox->text().toDouble() < dMin)
    {
        ui->m_AlarmMinspBox->setText(QString::number(dMin,'g',10));
    }
}

void QChartMeColor::on_m_PointTypecbBox_currentIndexChanged(int index)
{
    if(bInitFlag)
    {
        emit SetMeterPointColor();
    }
}

void QChartMeColor::onGetPointType(int &nType)
{
    nType = ui->m_PointTypecbBox->currentIndex();
}
