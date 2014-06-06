#include "qchartcommon.h"
#include "ui_qchartcommon.h"
#include "Frame/addressinputdialog.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

QChartCommon::QChartCommon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QChartCommon)
{
    nShapeType = 0;

    bValueChange = true;
    bInitFlag = false;
    ui->setupUi(this);
    ui->Monitor_Address->setText("LW0");
    ui->m_CommonButton_2->setEnabled(false);
}

QChartCommon::~QChartCommon()
{
    delete ui;
}
void QChartCommon::Init(ChartItem *pItem)
{
    if(pItem)
    {
        ui->Monitor_Address->setText(pItem->common_st.addr.sShowAddr);//监控字地址

        ui->Date_type->setCurrentIndex(pItem->common_st.eDataType);//数据类型

        //源范围
        ui->range_Combox->setCurrentIndex(pItem->common_st.nSourceRang);//指定源范围

        //ui->symbol_Combox->setCurrentIndex(pItem->common_st.bSourceMark);//符号+/-

        on_range_Combox_currentIndexChanged(pItem->common_st.nSourceRang);
        if(0 == pItem->common_st.nSourceRang)
        {
           ui->min_Spinbox->setText(pItem->common_st.eSourceMin);        //源范围最小
           ui->max_Spinbox->setText(pItem->common_st.eSourceMax);      //源范围最大
        }
        else
        {
            ui->min_Spinbox->setText("0");
            ui->max_Spinbox->setText("100");
            ui->m_sMinlineEdit->setText(pItem->common_st.addrSourceMin.sShowAddr);
            ui->m_sMaxlineEdit->setText(pItem->common_st.addrSourceMax.sShowAddr);
        }

        //显示范围                         //显示符号 +/-
        //ui->symbol_checkBox->setChecked(pItem->common_st.bShowMark);

        ui->min_numEdit->setText(QString::number(pItem->common_st.eShowMin,'g',10));//显示最小值

        ui->max_numEdit->setText(QString::number(pItem->common_st.eShowMax,'g',10));  //显示最大值

                               //图表形状
        if(pItem->common_st.eShapeType == PILLA)
        {
            ui->type_Combobox->setCurrentIndex(0);
        }
        else if(pItem->common_st.eShapeType == CIRCLE)
        {
            ui->type_Combobox->setCurrentIndex(1);
        }
        else if(pItem->common_st.eShapeType == SECTOR)
        {
            ui->type_Combobox->setCurrentIndex(2);
        }
        else if(pItem->common_st.eShapeType == GROOVE)
        {
            ui->type_Combobox->setCurrentIndex(3);
        }

        on_type_Combobox_currentIndexChanged(int(pItem->common_st.eShapeType));
        //显示方向
        if(pItem->common_st.eDirection == TOWARD_TOP)
        {
            ui->direct_Combobox->setCurrentIndex(0);
        }
        else if(pItem->common_st.eDirection == TOWARD_BOTTOM)
        {
            ui->direct_Combobox->setCurrentIndex(1);
        }
        else if(pItem->common_st.eDirection == TOWARD_LEFT)
        {
            ui->direct_Combobox->setCurrentIndex(2);
        }
        else if(pItem->common_st.eDirection == TOWARD_RIGHT)
        {
            ui->direct_Combobox->setCurrentIndex(3);
        }

        ui->m_StartAngleSpBox->setValue(pItem->common_st.nStartAngle);
        ui->m_SpanAngleSpBox->setValue(pItem->common_st.nSpanAngle);
        ui->hole_Checkbox->setChecked(pItem->common_st.bHole);       //孔

        ui->radiu_Spinbox->setValue(pItem->common_st.nRadius);//孔半径

        ui->filling_Checkbox->setChecked(pItem->common_st.bFill);         //显示填充
        on_filling_Checkbox_clicked(pItem->common_st.bFill);

        ui->start_Checkbox->setChecked(pItem->common_st.bStart);       //显示开始点

        ui->m_TransparentspBox->setValue(pItem->common_st.nTransparent);
        ui->m_checkBox_showFrame->setChecked(pItem->common_st.bShowFrame);
    }
    else
    {
        on_type_Combobox_currentIndexChanged(ui->type_Combobox->currentIndex());
        on_range_Combox_currentIndexChanged(0);
        ui->min_Spinbox->setText("0");
        ui->max_Spinbox->setText("100");
        ui->max_numEdit->setText("100");
        ui->min_numEdit->setText("0");
        ui->Date_type->setCurrentIndex(1);//数据类型
    }
    bInitFlag = true;
    on_Date_type_currentIndexChanged(ui->Date_type->currentIndex());
}

void QChartCommon::on_m_MeterButton_2_clicked()
{
    emit meterclick();
}

void QChartCommon::on_m_CommonButton_2_clicked()
{

}

void QChartCommon::on_Monitor_Address_EntryBtn_clicked()
{
    QString addrStr = ui->Monitor_Address->text();
    AddressInputDialog addressintputdlg_writeaddress(Monitor_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->Monitor_Address->setText(Monitor_Address_Keyboard.sShowAddr);
    }
}

void QChartCommon::on_comboBox_currentIndexChanged(int index)
{

}

//设置最小显示范围为-100
void QChartCommon::on_symbol_checkBox_clicked()
{
}

bool QChartCommon::CommonGenSave(struct COMMON_INFORMATION &common_st)
{
    QString sTmp;
    int nState;

    if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("监控字地址"),ui->Monitor_Address,1))
    {
        ui->Monitor_Address->setFocus();
        return false;
    }
    common_st.addr = Monitor_Address_Keyboard;

    if(1 == ui->range_Combox->currentIndex())
    {
        if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("最小值地址"),ui->m_sMinlineEdit,1))
        {
            ui->m_sMinlineEdit->setFocus();
            return false;
        }
        common_st.addrSourceMin = Monitor_Address_Keyboard;

        if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("最大值地址"),ui->m_sMaxlineEdit,1))
        {
            ui->m_sMaxlineEdit->setFocus();
            return false;
        }
        common_st.addrSourceMax = Monitor_Address_Keyboard;
    }

    common_st.mAddress = ui->Monitor_Address->text();//监控字地址

    common_st.eDataType = ui->Date_type->currentIndex();//数据类型

    //源范围
    common_st.nSourceRang = ui->range_Combox->currentIndex();//指定源范围

    //common_st.bSourceMark = ui->symbol_Combox->currentIndex();//符号+/-

    if(0 == ui->range_Combox->currentIndex())
    {
        common_st.eSourceMin = ui->min_Spinbox->text();  //源范围最小                 //源范围最小
        common_st.eSourceMax = ui->max_Spinbox->text();//源范围最大
    }
    else
    {
        common_st.eSourceMin = ui->m_sMinlineEdit->text();  //源范围最小                 //源范围最小
        common_st.eSourceMax = ui->m_sMaxlineEdit->text();//源范围最大
    }

    //显示范围                         //显示符号 +/-
    //common_st.bShowMark = ui->symbol_checkBox->isChecked();

    sTmp.clear();                          //显示最小值
    sTmp = ui->min_numEdit->text();
    common_st.eShowMin = sTmp.toDouble();

    sTmp.clear();                          //显示最大值
    sTmp = ui->max_numEdit->text();
    common_st.eShowMax = sTmp.toDouble();

                           //图表形状
    nState = ui->type_Combobox->currentIndex();
    if(0 == nState)
    {
        common_st.eShapeType = PILLA;
    }
    else if(1 == nState)
    {
        common_st.eShapeType = CIRCLE;
    }
    else if(2 == nState)
    {
        common_st.eShapeType = SECTOR;
    }
    else if(3 == nState)
    {
        common_st.eShapeType = GROOVE;
    }

    nState = ui->direct_Combobox->currentIndex(); //显示方向
    if(0 == nState)
    {
        common_st.eDirection = TOWARD_TOP;
    }
    else if(1 == nState)
    {
        common_st.eDirection = TOWARD_BOTTOM;
    }
    else if(2 == nState)
    {
        common_st.eDirection = TOWARD_LEFT;
    }
    else if(3 == nState)
    {
        common_st.eDirection = TOWARD_RIGHT;
    }

    common_st.bHole = ui->hole_Checkbox->isChecked();       //孔

    sTmp.clear();
    sTmp = ui->radiu_Spinbox->text();//孔半径
    common_st.nRadius = sTmp.toInt();

    common_st.bFill = ui->filling_Checkbox->isChecked();         //显示填充

    common_st.bStart = ui->start_Checkbox->isChecked();       //显示开始点
    common_st.nStartAngle = ui->m_StartAngleSpBox->value();
    common_st.nSpanAngle = ui->m_SpanAngleSpBox->value();

    common_st.nTransparent = ui->m_TransparentspBox->value();
    common_st.bShowFrame = ui->m_checkBox_showFrame->isChecked();
    return true;
}



void QChartCommon::on_type_Combobox_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
    case 3:
        ui->m_StartAnglelabel->setEnabled(false);
        ui->m_StartAngleSpBox->setEnabled(false);
        ui->m_SpanAnglelabel->setEnabled(false);
        ui->m_SpanAngleSpBox->setEnabled(false);

        ui->m_Transparentlabel->setEnabled(false);
        ui->m_TransparentspBox->setEnabled(false);
        ui->m_checkBox_showFrame->setEnabled(false);

        ui->direct_Combobox->setEnabled(true);
        ui->label_34->show();
        if (ui->hole_Checkbox->isChecked())
        {
            //this->holecheck = ui->hole_Checkbox->isChecked();
            ui->hole_Checkbox->setChecked(false);
        }
        ui->hole_Checkbox->setEnabled(false);
        ui->radiu_Spinbox->setEnabled(false);

        ui->hole_Checkbox->setEnabled(false);
        ui->radiu_Spinbox->setEnabled(false);
        ui->filling_Checkbox->setEnabled(false);
        ui->start_Checkbox->setEnabled(false);
        break;
    case 1:
    case 2:
        if(2 == index)
        {
            ui->m_StartAnglelabel->setEnabled(false);
            ui->m_StartAngleSpBox->setEnabled(false);
            ui->m_SpanAnglelabel->setEnabled(false);
            ui->m_SpanAngleSpBox->setEnabled(false);

            ui->m_Transparentlabel->setEnabled(false);
            ui->m_TransparentspBox->setEnabled(false);
            ui->m_checkBox_showFrame->setEnabled(false);
        }
        else if(1 == index)
        {
            ui->m_SpanAnglelabel->setEnabled(true);
            ui->m_SpanAngleSpBox->setEnabled(true);
            ui->m_StartAnglelabel->setEnabled(true);
            ui->m_StartAngleSpBox->setEnabled(true);

            ui->m_Transparentlabel->setEnabled(true);
            ui->m_TransparentspBox->setEnabled(true);
            ui->m_checkBox_showFrame->setEnabled(true);
        }

        ui->direct_Combobox->setEnabled(false);
        ui->label_34->setEnabled(false);
        //if(this->holecheck)
        //{
            //ui->hole_Checkbox->setChecked(true);
        //}
        ui->hole_Checkbox->setEnabled(true);
        ui->radiu_Spinbox->setEnabled(true);

        ui->hole_Checkbox->setEnabled(true);
        ui->radiu_Spinbox->setEnabled(true);
        if(2 == index)
        {
            ui->filling_Checkbox->setEnabled(false);
            ui->start_Checkbox->setEnabled(false);
        }
        else
        {
            ui->filling_Checkbox->setEnabled(true);
            ui->start_Checkbox->setEnabled(true);
        }
        break;
    default:
        break;
    }
    nShapeType = index;
    ui->direct_Combobox->setCurrentIndex(0);
    if(bInitFlag)
    {
        emit setCommonShapeType();
    }
}

void QChartCommon::on_direct_Combobox_currentIndexChanged(int index)
{
    if(!bInitFlag)
    {
        return;
    }
    ndirection = ui->direct_Combobox->currentIndex();
    emit directionchange();
}

void QChartCommon::on_range_Combox_currentIndexChanged(int index)
{
    if(0 == ui->range_Combox->currentIndex())
    {
        ui->m_sMinlineEdit->setEnabled(false);
        ui->m_sMaxlineEdit->setEnabled(false);
        ui->m_maxAddress_EntryBtn->setEnabled(false);
        ui->m_minAddress_EntryBtn->setEnabled(false);
        ui->min_Spinbox->setEnabled(true);
        ui->max_Spinbox->setEnabled(true);
    }
    else if(1 == ui->range_Combox->currentIndex())
    {
        ui->m_sMinlineEdit->setEnabled(true);
        ui->m_sMaxlineEdit->setEnabled(true);
        ui->m_maxAddress_EntryBtn->setEnabled(true);
        ui->m_minAddress_EntryBtn->setEnabled(true);
        ui->min_Spinbox->setEnabled(false);
        ui->max_Spinbox->setEnabled(false);
    }
}

void QChartCommon::on_m_minAddress_EntryBtn_clicked()
{
    QString addrStr = ui->m_sMinlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(m_minAddress_EntryBtn,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_sMinlineEdit->setText(m_minAddress_EntryBtn.sShowAddr);
    }
}

void QChartCommon::on_m_maxAddress_EntryBtn_clicked()
{ 
    QString addrStr = ui->m_sMaxlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(m_maxAddress_EntryBtn,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_sMaxlineEdit->setText(m_maxAddress_EntryBtn.sShowAddr);
    }
}

void QChartCommon::on_filling_Checkbox_clicked(bool checked)
{
    if(checked)
    {
        ui->start_Checkbox->setChecked(false);
        emit enablePointType(false);
    }
    else
    {
        ui->start_Checkbox->setChecked(true);
        emit enablePointType(true);
    }
    emit reDrawBar();
}

void QChartCommon::on_radiu_Spinbox_valueChanged(int )
{
    int nRadiu = ui->radiu_Spinbox->value();
    bool checked = ui->hole_Checkbox->isChecked();
    if(!checked || !bValueChange)
    {
        return;
    }
    emit drawCenterCircle(checked, nRadiu);
}

void QChartCommon::on_hole_Checkbox_clicked(bool checked)
{
    int nRadiu = ui->radiu_Spinbox->value();
    emit drawCenterCircle(checked, nRadiu);
}

void QChartCommon::onGetDirection(int &nIndex)
{
    nIndex = ui->direct_Combobox->currentIndex();
}

void QChartCommon::setdataRange(double dMax, double dMin,int type)
{
    //QIntValidator* aIntValidator = new QIntValidator(this);
    DoubleValidator *aDoubleValidator = new DoubleValidator(this);
    aDoubleValidator->setNotation(QDoubleValidator::StandardNotation);

    if(0 == type)
    {
        aDoubleValidator->setRange(dMin,dMax,4);
        ui->min_Spinbox->setValidator(aDoubleValidator);
        ui->max_Spinbox->setValidator(aDoubleValidator);
        ui->min_numEdit->setValidator(aDoubleValidator);
        ui->max_numEdit->setValidator(aDoubleValidator);
    }
    else
    {
        aDoubleValidator->setRange(dMin, dMax,0);
        ui->min_Spinbox->setValidator(aDoubleValidator);
        ui->max_Spinbox->setValidator(aDoubleValidator);
        ui->min_numEdit->setValidator(aDoubleValidator);
        ui->max_numEdit->setValidator(aDoubleValidator);
    }

    if(ui->max_Spinbox->text().isEmpty()
        || ui->max_Spinbox->text().toDouble() > dMax
                || ui->max_Spinbox->text().toDouble() < dMin)
    {
       ui->max_Spinbox->setText(QString::number(dMax,'g',10));
    }
    if(ui->min_Spinbox->text().isEmpty()
        || ui->min_Spinbox->text().toDouble() > dMax
                || ui->min_Spinbox->text().toDouble() < dMin)
    {
        ui->min_Spinbox->setText(QString::number(dMin,'g',10));
    }

    if(ui->max_numEdit->text().isEmpty()
        || ui->max_numEdit->text().toDouble() > dMax
                || ui->max_numEdit->text().toDouble() < dMin)
    {
       ui->max_numEdit->setText(QString::number(dMax,'g',10));
    }
    if(ui->min_numEdit->text().isEmpty()
        || ui->min_numEdit->text().toDouble() > dMax
                || ui->min_numEdit->text().toDouble() < dMin)
    {
        ui->min_numEdit->setText(QString::number(dMin,'g',10));
    }
}

void QChartCommon::on_Date_type_currentIndexChanged(int index)
{
    if(!bInitFlag)
    {
        return;
    }
    double nMax = 100;
    double nMin = 0;
    int type  = 1;
    switch(index)
    {
    case 0://16位整数
        {
            nMin = -32768;
            nMax = 32767;
            break;
        }
        break;
    case 1://16位正整数
        {
            nMin = 0;
            nMax = 65535;
        }
        break;
    case 2://32位整数
        nMin = -2147483648L;
        nMax = 2147483647L;
        break;
    case 3://32位正整数
        nMin = 0;
        nMax = 4294967295UL;
        break;
    case 4://32位浮点数
        nMin = -2147483648L;
        nMax = 2147483647L;
        type = 0;
        break;
    default:
        return;
    }

    if(nMin > 0) nMin = -1*nMin;
    setdataRange(nMax, nMin,type);
    emit setRange(nMax, nMin, type);
}

void QChartCommon::onGetroleCheck(bool &bCheck, int &nRadius)
{
    if(bCheck)
    {
        bValueChange = false;
        ui->hole_Checkbox->setChecked(true);
        ui->radiu_Spinbox->setValue(nRadius);
        bValueChange = true;
    }
    else
    {
        bCheck = ui->hole_Checkbox->isChecked();
        nRadius = ui->radiu_Spinbox->value();
    }
}

void QChartCommon::on_start_Checkbox_clicked(bool checked)
{
    if(checked)
    {
        ui->filling_Checkbox->setChecked(false);
        emit enablePointType(true);
    }
    else
    {
        ui->filling_Checkbox->setChecked(true);
        emit enablePointType(false);
    }
    emit reDrawBar();
}

void QChartCommon::onGetdataRange(double &dMin, double &dMax)//获取最大最小值
{
    dMin = ui->min_numEdit->text().toDouble();
    dMax = ui->max_numEdit->text().toDouble();
}

void QChartCommon::on_min_numEdit_textChanged(QString )
{
    if(bInitFlag)
    {
        if(ui->max_numEdit->text().toDouble() < ui->min_numEdit->text().toDouble())
        {
            return;
        }
        emit reDrawBar();
    }
}

void QChartCommon::on_max_numEdit_textChanged(QString )
{
    if(bInitFlag)
    {
        if(ui->max_numEdit->text().toDouble() < ui->min_numEdit->text().toDouble())
        {
            return;
        }
        emit reDrawBar();
    }
}

void QChartCommon::onGetPointType(int &nType)//获取圆是否画指针，0：显示填充，1：显示指针
{
    if(ui->filling_Checkbox->isChecked())
    {
        nType = 0;
    }
    else
    {
        nType = 1;
    }
}

void QChartCommon::onGetStartAngle(short &nStart,short &nSpan)
{
    nStart = ui->m_StartAngleSpBox->value();
    nSpan = ui->m_SpanAngleSpBox->value();
}


void QChartCommon::on_m_StartAngleSpBox_valueChanged(int )
{
    if(bInitFlag)
    {
        emit reDrawBar();
    }
}

void QChartCommon::on_m_SpanAngleSpBox_valueChanged(int )
{
    if(bInitFlag)
    {
        emit reDrawBar();
    }
}

void QChartCommon::onGetCircleAlpha(short &nAlpha)
{
    nAlpha = ui->m_TransparentspBox->value();
}

void QChartCommon::on_m_TransparentspBox_valueChanged(int )
{
    if(bInitFlag)
    {
        emit reDrawBar();
    }
}

void QChartCommon::onGetShowFrame(bool &bShowFrame)
{
    bShowFrame = ui->m_checkBox_showFrame->isChecked();
}

void QChartCommon::on_m_checkBox_showFrame_clicked(bool checked)
{
    if(bInitFlag)
    {
        emit reDrawBar();
    }
}



