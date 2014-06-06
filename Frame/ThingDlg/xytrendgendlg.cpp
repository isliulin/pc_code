#include "xytrendgendlg.h"
#include "ui_xytrendgendlg.h"
extern MainWindow *pwnd;


XYTrendGenDlg::XYTrendGenDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XYTrendGenDlg)
{
    ui->setupUi(this);
    ui->comboBox_showCondition->addItem(tr("保持显示"));
    ui->comboBox_showCondition->addItem(tr("位ON时显示"));
    ui->comboBox_showCondition->addItem(tr("位OFF时显示"));
    ui->comboBox_pipeNum->addItem("0");
    setDefaultChl();
}

XYTrendGenDlg::~XYTrendGenDlg()
{
    delete ui;
}
void XYTrendGenDlg::Init(XYtrend *pItem)
{
    qDebug() << "XYTrendGenDlg::Init";
    if(pItem)
    {
        m_bIsAll        = pItem->m_bIsAll;
        chlCount        = pItem->chlCount;//通道总数
        addrLength      = pItem->addrLength;//地址长度，相当于采样点数
        m_dataType      = pItem->m_dataType;//数据类型
        m_TriggerAddr   = pItem->m_TriggerAddr;//触发地址
        m_bReset        = pItem->m_bReset;//是否自动复位

        m_bScale        = pItem->m_bScale;//是否缩放

        m_bDisplayConst  = pItem->m_bDisplayConst;
        m_DisplayMaxAddrX= pItem->m_DisplayMaxAddrX;
        m_DisplayMinAddrX= pItem->m_DisplayMinAddrX;

        m_nDisplayMinX   = pItem->m_nDisplayMinX;	//显示最小值
        m_nDisplayMaxX   = pItem->m_nDisplayMaxX;	//显示最大值
        m_bConstX        = pItem->m_bConstX;//是否常量范围
        m_SourceMaxAddrX = pItem->m_SourceMaxAddrX;//源范围最大值 地址
        m_SourceMinAddrX = pItem->m_SourceMinAddrX;//源范围最小值 地址
        m_nSourceMaxX    = pItem->m_nSourceMaxX;	//源范围最大值
        m_nSourceMinX    = pItem->m_nSourceMinX;	//源范围最小值

        m_bDisplayConstY  = pItem->m_bDisplayConstY;
        m_DisplayMaxAddrY= pItem->m_DisplayMaxAddrY;
        m_DisplayMinAddrY= pItem->m_DisplayMinAddrY;

        m_nDisplayMinY   = pItem->m_nDisplayMinY;	//显示最小值
        m_nDisplayMaxY   = pItem->m_nDisplayMaxY;	//显示最大值
        m_bConstY        = pItem->m_bConstY;//是否常量范围
        m_SourceMaxAddrY = pItem->m_SourceMaxAddrY;//源范围最大值 地址
        m_SourceMinAddrY = pItem->m_SourceMinAddrY;//源范围最小值 地址
        m_nSourceMaxY    = pItem->m_nSourceMaxY;	//源范围最大值
        m_nSourceMinY    = pItem->m_nSourceMinY;	//源范围最小值

        m_vecChannels   = pItem->m_vecChannels;//各个通道曲线外观设置

    }
    else
    {
        m_bIsAll        = false;
        chlCount        = 1;//通道总数
        addrLength      = 10;//地址长度，相当于采样点数
        m_dataType      = (DATA_TYPE)2;//数据类型
        m_TriggerAddr.sShowAddr   = "LB0";//触发地址
        m_bReset        = false;//是否自动复位

        m_bScale        = false;//是否缩放

        m_bDisplayConst  = true;
        m_DisplayMaxAddrX.sShowAddr = "LW0";
        m_DisplayMinAddrX.sShowAddr = "LW0";

        m_nDisplayMinX   = 0;	//显示最小值
        m_nDisplayMaxX   = 100;	//显示最大值
        m_bConstX        = true;//是否常量范围
        m_SourceMaxAddrX.sShowAddr = "LW0";//源范围最大值 地址
        m_SourceMinAddrX.sShowAddr = "LW0";//源范围最小值 地址
        m_nSourceMaxX    = 100;	//源范围最大值
        m_nSourceMinX    = 0;	//源范围最小值

        m_bDisplayConstY  = true;
        m_DisplayMaxAddrY.sShowAddr = "LW0";
        m_DisplayMinAddrY.sShowAddr = "LW0";
        m_nDisplayMinY   = 0;	//显示最小值
        m_nDisplayMaxY   = 100;	//显示最大值
        m_bConstY       = true;//是否常量范围
        m_SourceMaxAddrY.sShowAddr = "LW0";//源范围最大值 地址
        m_SourceMinAddrY.sShowAddr = "LW0";//源范围最小值 地址
        m_nSourceMaxY    = 100;	//源范围最大值
        m_nSourceMinY    = 0;	//源范围最小值

        m_vecChannels << m_defaultChl;

    }
    m_chlnum = 0;
    qDebug() << "m_DisplayMinAddrX:"<<m_DisplayMinAddrX.sShowAddr;
    qDebug() << "m_DisplayMaxAddrX:"<<m_DisplayMaxAddrX.sShowAddr;
    qDebug() << "m_DisplayMinAddrY:"<<m_DisplayMinAddrY.sShowAddr;
    qDebug() << "m_DisplayMaxAddrY:"<<m_DisplayMaxAddrY.sShowAddr;

    qDebug() << "XYTrendGenDlg::chlCount";
    ui->spinCount->setValue(chlCount);
    ui->spinLength->setValue(addrLength);
    ui->comboBox_dataType->setCurrentIndex(m_dataType);
    ui->lineEdit_trigAddr->setText(m_TriggerAddr.sShowAddr);
    ui->check_reset->setChecked(m_bReset);
    ui->m_DisplayBox->setCurrentIndex(!m_bDisplayConst);
    ui->m_DisplayMaxAddrX->setText(m_DisplayMaxAddrX.sShowAddr);
    ui->m_DisplayMinAddrX->setText(m_DisplayMinAddrX.sShowAddr);
    ui->m_DisplayBox_Y->setCurrentIndex(!m_bDisplayConstY);
    ui->m_DisplayMaxAddrY->setText(m_DisplayMaxAddrY.sShowAddr);
    ui->m_DisplayMinAddrY->setText(m_DisplayMinAddrY.sShowAddr);

    ui->doubleSpinBox_outputMax->setText(QString::number(m_nDisplayMaxX,'g',10));
    ui->doubleSpinBox_outputMin->setText(QString::number(m_nDisplayMinX,'g',10));
    ui->doubleSpinBox_outputMax_Y->setText(QString::number(m_nDisplayMaxY,'g',10));
    ui->doubleSpinBox_outputMin_Y->setText(QString::number(m_nDisplayMinY,'g',10));

    ui->groupBox->setChecked(m_bScale);
    ui->m_SourcecbBox->setCurrentIndex(!m_bConstX);
    ui->m_SMinspBox->setText(QString::number(m_nSourceMinX));
    ui->m_SMaxspBox->setText(QString::number(m_nSourceMaxX));
    ui->m_SMaxlineEdit->setText(m_SourceMaxAddrX.sShowAddr);
    ui->m_SMinlineEdit->setText(m_SourceMinAddrX.sShowAddr);

    ui->m_SourcecbBox_Y->setCurrentIndex(!m_bConstY);
    ui->m_SMinspBox_Y->setText(QString::number(m_nSourceMinY));
    ui->m_SMaxspBox_2->setText(QString::number(m_nSourceMaxY));
    ui->m_SMaxlineEdit_Y->setText(m_SourceMaxAddrY.sShowAddr);
    ui->m_SMinlineEdit_Y->setText(m_SourceMinAddrY.sShowAddr);

    ui->checkBox->setChecked(m_bIsAll);
    if(m_vecChannels.size() > 0)
    {
       ChannelInfo chl = m_vecChannels.first();
       ui->lineEdit_AddrX->setText(chl.m_AddrX.sShowAddr);
       ui->lineEdit_AddrY->setText(chl.m_AddrY.sShowAddr);
       ui->comboBox_showCondition->setCurrentIndex(chl.eDisplayCondition -1);
       ui->lineEdit_ctlAddr->setText(chl.KeyAddr.sShowAddr);
       ui->comboBox_lineStyle->setCurrentIndex(chl.eLineType -1);

       ui->spinBox_lineWidth->setValue(chl.nLineThickness);
       //ui->pushButton_showColor->setStyleSheet();
       ui->pushButton_showColor->setStyleSheet(
               QString("background:%1").arg(chl.nDisplayColor.name()));
       onConditionChange(chl.eDisplayCondition - 1);
       onChlCountChange(chlCount);
    }
    connect(ui->comboBox_pipeNum,SIGNAL(currentIndexChanged(int)),this,SLOT(onChlNumChange(int)));
    connect(ui->spinCount,SIGNAL(valueChanged(int)),this,SLOT(onChlCountChange(int)));
    connect(ui->comboBox_showCondition,SIGNAL(currentIndexChanged(int)),this,SLOT(onConditionChange(int)));
    connect(ui->spinBox_lineWidth,SIGNAL(valueChanged(int)),this,SLOT(setCurrentChl()));
}
void XYTrendGenDlg::setDefaultChl()
{
    m_defaultChl.m_nNumOfChannel = 0;
    m_defaultChl.eLineType = LineSolid;
    m_defaultChl.nLineThickness = 1;
    m_defaultChl.eDisplayCondition = DisplayKeep;
    m_defaultChl.nDisplayColor = QColor(192,192,192);
    m_defaultChl.m_AddrX.sShowAddr = "LW0";
    m_defaultChl.m_AddrX.nAddrType = 1;
    m_defaultChl.m_AddrY.sShowAddr = "LW0";
    m_defaultChl.m_AddrY.nAddrType = 1;

}
//当前通道号改变
void XYTrendGenDlg::onChlNumChange(int index)
{
    qDebug() << "onChlNumChange:"<< index;
    if(index < m_vecChannels.size() && index >= 0)
    {
        setChlinfoUi(m_vecChannels.at(index));
    }
}
//通道数改变
void XYTrendGenDlg::onChlCountChange(int count)
{
    qDebug() << "onChlCountChange:"<< count;
    int size = m_vecChannels.size();
    if(count > size)
    {
        ChannelInfo chl;
        if(ui->checkBox->isChecked())
        {
            chl = m_vecChannels.first();
        }
        else
            chl = m_defaultChl;

        for(int i = size; i<count; i++)
        {
            chl.m_nNumOfChannel = i;
            m_vecChannels << chl;
        }
    }
    else
    {
        m_vecChannels.resize(count);
    }
    qDebug() << "onChlCountChange: X";
    int index = ui->comboBox_pipeNum->currentIndex();
    ui->comboBox_pipeNum->clear();
    for(int i=0; i<count; i++)
    {
        ui->comboBox_pipeNum->addItem(QString::number(i));
    }
    if(index <ui->comboBox_pipeNum->count())
    {
        ui->comboBox_pipeNum->setCurrentIndex(index);
    }
    qDebug() << "onChlCountChange: Y";
}

void XYTrendGenDlg::onConditionChange(int index)
{
    ui->lineEdit_ctlAddr->setEnabled(index != 0);
    ui->pushButton_ctlAddr->setEnabled(index != 0);
    setCurrentChl();


}
void XYTrendGenDlg::setCurrentChl()
{
    if (ui->comboBox_pipeNum->currentIndex() < 0 ||
        ui->comboBox_pipeNum->currentIndex() >= m_vecChannels.size())
    {
        return;
    }
    ChannelInfo chl;
    chl.m_nNumOfChannel = ui->comboBox_pipeNum->currentIndex();
    chl.eLineType = (LineStyleType)(ui->comboBox_lineStyle->currentIndex()+1);
    chl.nLineThickness = ui->spinBox_lineWidth->value();
    chl.eDisplayCondition = (DisConType)(ui->comboBox_showCondition->currentIndex()+1);

    chl.nDisplayColor = ui->pushButton_showColor->palette().background().color();//线颜色;

    int Addr_Type = 0;
    pwnd->CheckString(chl.KeyAddr,ui->lineEdit_ctlAddr->text(),Addr_Type);
    chl.KeyAddr.nAddrType = Addr_Type; //记录字位标示
    Addr_Type = 1;
    pwnd->CheckString(chl.m_AddrX,ui->lineEdit_AddrX->text(),Addr_Type);
    chl.m_AddrX.nAddrType = Addr_Type; //记录字位标示

    pwnd->CheckString(chl.m_AddrY,ui->lineEdit_AddrY->text(),Addr_Type);
    chl.m_AddrY.nAddrType = Addr_Type; //记录字位标示
    qDebug() <<"m_nNumOfChannel" << chl.m_nNumOfChannel;

    for (int i=0; i<m_vecChannels.size(); i++)
    {
        qDebug() << "m_vecChannels[i].m_nNumOfChannel"<< m_vecChannels[i].m_nNumOfChannel;
            if(ui->checkBox->isChecked())
            {
                ChannelInfo curChl = m_vecChannels[i];
                chl.m_nNumOfChannel = curChl.m_nNumOfChannel;
                chl.m_AddrX = curChl.m_AddrX;
                chl.m_AddrY = curChl.m_AddrY;
                m_vecChannels.replace(i,chl);
            }
            else
            {
                ChannelInfo curChl = m_vecChannels[i];
                if (curChl.m_nNumOfChannel == chl.m_nNumOfChannel)
                {
                    m_vecChannels.replace(i,chl);
                    qDebug() << "chl.m_AddrX.sShowAddr"<< chl.m_AddrX.sShowAddr;
                    qDebug() << "chl.m_AddrY.sShowAddr"<< chl.m_AddrY.sShowAddr;
                    qDebug() << "chl.KeyAddr.sShowAddr"<< chl.KeyAddr.sShowAddr;
                    break;
                }
            }
    }
}

void XYTrendGenDlg::setChlinfoUi(ChannelInfo chl)
{
    ui->lineEdit_AddrX->setText(chl.m_AddrX.sShowAddr);
    ui->lineEdit_AddrY->setText(chl.m_AddrY.sShowAddr);
    ui->comboBox_showCondition->setCurrentIndex(chl.eDisplayCondition -1);
    ui->lineEdit_ctlAddr->setText(chl.KeyAddr.sShowAddr);
    ui->comboBox_lineStyle->setCurrentIndex(chl.eLineType-1);
    ui->spinBox_lineWidth->setValue(chl.nLineThickness);
    //ui->pushButton_showColor->setStyleSheet();
    ui->pushButton_showColor->setStyleSheet(
            QString("background:%1").arg(chl.nDisplayColor.name()));
}

void XYTrendGenDlg::on_pushButton_AddrX_clicked()
{
    QString str = ui->lineEdit_AddrX->text();
    Keyboard ctlAddr;
    AddressInputDialog dlg_readaddress(ctlAddr,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_AddrX->setText(ctlAddr.sShowAddr);
        setCurrentChl();
    }
}

void XYTrendGenDlg::on_pushButton_AddrY_clicked()
{
    QString str = ui->lineEdit_AddrY->text();
    Keyboard ctlAddr;
    AddressInputDialog dlg_readaddress(ctlAddr,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_AddrY->setText(ctlAddr.sShowAddr);
        setCurrentChl();
    }
}

void XYTrendGenDlg::on_pushButton_ctlAddr_clicked()
{
    QString str = ui->lineEdit_ctlAddr->text();
    Keyboard ctlAddr;
    AddressInputDialog dlg_readaddress(ctlAddr,str,0,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_ctlAddr->setText(ctlAddr.sShowAddr);
        setCurrentChl();
    }
}

void XYTrendGenDlg::on_pushButton_showColor_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->pushButton_showColor,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBtnColor(const QColor &)));

}

void XYTrendGenDlg::setBtnColor(const QColor &color)
{
    ui->pushButton_showColor->setStyleSheet(QString("background:%1").arg(color.name()));

    setCurrentChl();
}
void XYTrendGenDlg::on_checkBox_clicked(bool checked)
{
    setCurrentChl();
}

void XYTrendGenDlg::on_pushButton_trigAddr_clicked()
{
    QString str = ui->lineEdit_trigAddr->text();
    Keyboard ctlAddr;
    AddressInputDialog dlg_readaddress(ctlAddr,str,0,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_trigAddr->setText(ctlAddr.sShowAddr);
    }
}

void XYTrendGenDlg::on_m_sMaxAddress_EntryBtn_clicked()
{
    QString str = ui->m_SMaxlineEdit->text();
    Keyboard ctlAddr;
    AddressInputDialog dlg_readaddress(ctlAddr,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->m_SMaxlineEdit->setText(ctlAddr.sShowAddr);
    }
}

void XYTrendGenDlg::on_m_sMinAddress_EntryBtn_clicked()
{
    QString str = ui->m_SMinlineEdit->text();
    Keyboard ctlAddr;
    AddressInputDialog dlg_readaddress(ctlAddr,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->m_SMinlineEdit->setText(ctlAddr.sShowAddr);
    }
}

void XYTrendGenDlg::on_m_sMaxAddress_EntryBtn_Y_clicked()
{
    QString str = ui->m_SMaxlineEdit_Y->text();
    Keyboard ctlAddr;
    AddressInputDialog dlg_readaddress(ctlAddr,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->m_SMaxlineEdit_Y->setText(ctlAddr.sShowAddr);
    }
}

void XYTrendGenDlg::on_m_sMinAddress_EntryBtn_Y_clicked()
{
    QString str = ui->m_SMinlineEdit_Y->text();
    Keyboard ctlAddr;
    AddressInputDialog dlg_readaddress(ctlAddr,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->m_SMinlineEdit_Y->setText(ctlAddr.sShowAddr);
    }
}

void XYTrendGenDlg::on_m_SourcecbBox_Y_currentIndexChanged(int index)
{
    ui->m_SMinlineEdit_Y->setVisible(index != 0);
    ui->m_SMinlineEdit_Y->setVisible(index != 0);
    ui->m_sMaxAddress_EntryBtn_Y->setVisible(index != 0);
    ui->m_sMinAddress_EntryBtn_Y->setVisible(index != 0);
    ui->m_SMaxspBox_2->setVisible(index == 0);
    ui->m_SMinspBox_Y->setVisible(index == 0);

}

void XYTrendGenDlg::on_m_SourcecbBox_currentIndexChanged(int index)
{
    ui->m_SMaxlineEdit->setVisible(index != 0);
    ui->m_SMinlineEdit->setVisible(index != 0);
    ui->m_sMaxAddress_EntryBtn->setVisible(index != 0);
    ui->m_sMinAddress_EntryBtn->setVisible(index != 0);
    ui->m_SMaxspBox->setVisible(index == 0);
    ui->m_SMinspBox->setVisible(index == 0);
}

void XYTrendGenDlg::on_lineEdit_AddrX_editingFinished()
{
    qDebug() << "on_lineEdit_AddrX_editingFinished";
    QString sAddr = ui->lineEdit_AddrX->text();
    Keyboard kb;
    if(!pwnd->IsAddressCheckRight(kb, tr("X轴起始地址"), ui->lineEdit_AddrX, 1))
    {
        ui->lineEdit_AddrX->setFocus();
        qDebug() << "on_lineEdit_AddrX_editingFinished error";
        return ;
    }
    setCurrentChl();
}

void XYTrendGenDlg::on_lineEdit_AddrY_editingFinished()
{
    QString sAddr = ui->lineEdit_AddrY->text();
    Keyboard kb;
    if(!pwnd->IsAddressCheckRight(kb, tr("Y轴起始地址"), ui->lineEdit_AddrY, 1))
    {
        ui->lineEdit_AddrY->setFocus();
        return ;
    }
    setCurrentChl();
}

void XYTrendGenDlg::on_lineEdit_ctlAddr_editingFinished()
{
    QString sAddr = ui->lineEdit_ctlAddr->text();
    Keyboard kb;
    if(!pwnd->IsAddressCheckRight(kb, tr("显示条件地址"), ui->lineEdit_ctlAddr, 0))
    {
        ui->lineEdit_ctlAddr->setFocus();
        return ;
    }
    setCurrentChl();
}

bool XYTrendGenDlg::save()
{
    if(!pwnd->IsAddressCheckRight(m_TriggerAddr, tr("触发地址"), ui->lineEdit_trigAddr, 0))
    {
        ui->lineEdit_trigAddr->setFocus();
        return false;
    }
    if(ui->m_DisplayBox->currentIndex() != 0)
    {
        if(!pwnd->IsAddressCheckRight(m_DisplayMinAddrX, tr("显示范围-X轴最小值地址"), ui->m_DisplayMinAddrX, 1))
        {
            ui->m_DisplayMinAddrX->setFocus();
            return false;
        }
        if(!pwnd->IsAddressCheckRight(m_DisplayMaxAddrX, tr("显示范围-X轴最大值地址"), ui->m_DisplayMaxAddrX, 1))
        {
            ui->m_DisplayMaxAddrX->setFocus();
            return false;
        }
    }
    else
    {
        m_nDisplayMinX   = ui->doubleSpinBox_outputMin->text().toDouble();	//显示最小值
        m_nDisplayMaxX   = ui->doubleSpinBox_outputMax->text().toDouble();	//显示最大值
    }
    if(ui->m_DisplayBox_Y->currentIndex() != 0)
    {
        if(!pwnd->IsAddressCheckRight(m_DisplayMinAddrY, tr("显示范围-Y轴最小值地址"), ui->m_DisplayMinAddrY, 1))
        {
            ui->m_DisplayMinAddrY->setFocus();
            return false;
        }
        if(!pwnd->IsAddressCheckRight(m_DisplayMaxAddrY, tr("显示范围-Y轴最大值地址"), ui->m_DisplayMaxAddrY, 1))
        {
            ui->m_DisplayMaxAddrY->setFocus();
            return false;
        }
    }
    else
    {
        m_nDisplayMinY   = ui->doubleSpinBox_outputMin_Y->text().toDouble();	//显示最小值
        m_nDisplayMaxY   = ui->doubleSpinBox_outputMax_Y->text().toDouble();//显示最大值
    }

    if(ui->groupBox->isChecked())
    {
        if(ui->m_SourcecbBox->currentIndex() != 0)
        {
            if(!pwnd->IsAddressCheckRight(m_SourceMinAddrX, tr("源范围-X轴最小值地址"), ui->m_SMinlineEdit, 1))
            {
                ui->m_SMinlineEdit->setFocus();
                return false;
            }
            if(!pwnd->IsAddressCheckRight(m_SourceMaxAddrX, tr("源范围-X轴最大值地址"), ui->m_SMaxlineEdit, 1))
            {
                ui->m_SMaxlineEdit->setFocus();
                return false;
            }
        }
        else
        {
            m_nSourceMinX   = ui->m_SMinspBox->text().toDouble();	//显示最小值
            m_nSourceMaxX   = ui->m_SMaxspBox->text().toDouble();	//显示最大值
        }
        if(ui->m_SourcecbBox_Y->currentIndex() != 0)
        {
            if(!pwnd->IsAddressCheckRight(m_SourceMinAddrY, tr("源范围-Y轴最小值地址"), ui->m_SMinlineEdit_Y, 1))
            {
                ui->m_SMinlineEdit_Y->setFocus();
                return false;
            }
            if(!pwnd->IsAddressCheckRight(m_SourceMaxAddrY, tr("源范围-Y轴最大值地址"), ui->m_SMaxlineEdit_Y, 1))
            {
                ui->m_SMaxlineEdit_Y->setFocus();
                return false;
            }
        }
        else
        {
            m_nSourceMinY   = ui->m_SMinspBox_Y->text().toDouble();	//显示最小值
            m_nSourceMaxY   = ui->m_SMaxspBox_2->text().toDouble();	//显示最大值
        }
    }

    qDebug() << "m_DisplayMinAddrX:"<<m_DisplayMinAddrX.sShowAddr;
    qDebug() << "m_DisplayMaxAddrX:"<<m_DisplayMaxAddrX.sShowAddr;
    qDebug() << "m_DisplayMinAddrY:"<<m_DisplayMinAddrY.sShowAddr;
    qDebug() << "m_DisplayMaxAddrY:"<<m_DisplayMaxAddrY.sShowAddr;
    m_bIsAll        = ui->checkBox->isChecked();
    chlCount        = ui->spinCount->value();//通道总数
    addrLength      = ui->spinLength->value();//地址长度，相当于采样点数
    m_dataType      = (DATA_TYPE)ui->comboBox_dataType->currentIndex();//数据类型
    //m_TriggerAddr.sShowAddr   = "LB0";//触发地址
    m_bReset        = ui->check_reset->isChecked();//是否自动复位

    m_bScale        = ui->groupBox->isChecked();//是否缩放

    m_bDisplayConst = !(ui->m_DisplayBox->currentIndex());//是否常量范围
    m_bDisplayConstY = !(ui->m_DisplayBox_Y->currentIndex());//是否常量范围

    m_bConstX        = !(ui->m_SourcecbBox->currentIndex());//是否常量范围
    //m_SourceMaxAddrX.sShowAddr = "LW0";//源范围最大值 地址
    //m_SourceMinAddrX.sShowAddr = "LW0";//源范围最小值 地址
    qDebug() << "m_bConstX:"<< m_bConstX;
    m_nSourceMaxX    = ui->m_SMaxspBox->text().toDouble();	//源范围最大值
    m_nSourceMinX    = ui->m_SMinspBox->text().toDouble();	//源范围最小值


    m_bConstY       = !(ui->m_SourcecbBox_Y->currentIndex());//是否常量范围
    //m_SourceMaxAddrY.sShowAddr = "LW0";//源范围最大值 地址
    //m_SourceMinAddrY.sShowAddr = "LW0";//源范围最小值 地址
    qDebug() << "m_bConstY:"<< m_bConstY;
    m_nSourceMaxY    = ui->m_SMaxspBox_2->text().toDouble();;	//源范围最大值
    m_nSourceMinY    = ui->m_SMinspBox_Y->text().toDouble();;	//源范围最小值

    //m_vecChannels << m_defaultChl;
    int length = 1;
    switch(m_dataType)
    {
        case 1:
        case 3:
        case 5:
        case 6:
            length = 2;
            break;
            length = 1;
        default:
            break;
    }
    m_SourceMinAddrX.Length = length;
    m_SourceMaxAddrX.Length = length;
    m_SourceMinAddrY.Length = length;
    m_SourceMaxAddrY.Length = length;

    m_DisplayMinAddrX.Length = length;
    m_DisplayMaxAddrX.Length = length;
    m_DisplayMinAddrY.Length = length;
    m_DisplayMaxAddrY.Length = length;

    if(m_vecChannels.size() == chlCount)
    {
        for(int i=0; i< m_vecChannels.size(); i++)
        {
            m_vecChannels[i].m_AddrX.Length = length * addrLength;
            m_vecChannels[i].m_AddrY.Length = length * addrLength;
        }
    }
    else{
        return false;
    }
    return true;
}

void XYTrendGenDlg::on_comboBox_dataType_currentIndexChanged(int index)
{
    double nMax = 2147483647L;
    double nMin = -2147483648L;
    int decLen = 0;
    switch(index)
    {
    case 0://16位整数
    case 4://16位BCD码
        {
            nMax = 32767;
            nMin = -32768;
             decLen = 0;
        }
        break;
    case 1://32位整数
    case 5://32位BCD码
        {
            nMax = 2147483647L;
            nMin = -2147483648L;
             decLen = 0;
        }
        break;
    case 2://16位正整数
        {
            nMax = 65535;
            nMin = 0;
             decLen = 0;
        }
        break;
    case 3://32位正整数
        {
            nMax = 4294967295UL;
            nMin = 0;
            decLen = 0;
        }
        break;
    case 6://32位浮点数
        {
            nMax = 2147483647L;
            nMin = -2147483648L;
            decLen = 10;
        }
        break;
    }
    if (nMin>0)
    {
        nMin = nMin*-1;
    }
    DoubleValidator *validator = new DoubleValidator(nMin,nMax,decLen,this);

    ui->doubleSpinBox_outputMax->setValidator(validator);
    ui->doubleSpinBox_outputMin->setValidator(validator);

    double max = ui->doubleSpinBox_outputMax->text().toDouble();
    double min = ui->doubleSpinBox_outputMin->text().toDouble();
    double maxY = ui->doubleSpinBox_outputMax_Y->text().toDouble();
    double minY = ui->doubleSpinBox_outputMin_Y->text().toDouble();
    if(max > nMax)
        ui->doubleSpinBox_outputMax->setText(QString::number(nMax,'g',10));
    if(min < nMin)
        ui->doubleSpinBox_outputMin->setText(QString::number(nMin,'g',10));

    ui->doubleSpinBox_outputMax_Y->setValidator(validator);
    ui->doubleSpinBox_outputMin_Y->setValidator(validator);

    if(maxY > nMax)
        ui->doubleSpinBox_outputMax_Y->setText(QString::number(nMax,'g',10));
    if(minY < nMin)
        ui->doubleSpinBox_outputMin_Y->setText(QString::number(nMin,'g',10));

}

void XYTrendGenDlg::on_m_DisplayBox_currentIndexChanged(int index)
{
    ui->m_DisplayMinAddrX->setVisible(index != 0);
    ui->m_DisplayMaxAddrX->setVisible(index != 0);
    ui->m_BtnDisplayMaxAddrX->setVisible(index != 0);
    ui->m_BtnDisplayMinAddrX->setVisible(index != 0);
    ui->doubleSpinBox_outputMax->setVisible(index == 0);
    ui->doubleSpinBox_outputMin->setVisible(index == 0);
}

void XYTrendGenDlg::on_m_DisplayBox_Y_currentIndexChanged(int index)
{
    ui->m_DisplayMinAddrY->setVisible(index != 0);
    ui->m_DisplayMaxAddrY->setVisible(index != 0);
    ui->m_BtnDisplayMaxAddrY->setVisible(index != 0);
    ui->m_BtnDisplayMinAddrY->setVisible(index != 0);
    ui->doubleSpinBox_outputMax_Y->setVisible(index == 0);
    ui->doubleSpinBox_outputMin_Y->setVisible(index == 0);
}

void XYTrendGenDlg::on_m_BtnDisplayMinAddrX_clicked()
{
    QString str = ui->m_DisplayMinAddrX->text();
    Keyboard ctlAddr;
    AddressInputDialog dlg_readaddress(ctlAddr,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->m_DisplayMinAddrX->setText(ctlAddr.sShowAddr);
    }
}

void XYTrendGenDlg::on_m_BtnDisplayMaxAddrX_clicked()
{
    QString str = ui->m_DisplayMaxAddrX->text();
    Keyboard ctlAddr;
    AddressInputDialog dlg_readaddress(ctlAddr,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->m_DisplayMaxAddrX->setText(ctlAddr.sShowAddr);
    }
}

void XYTrendGenDlg::on_m_BtnDisplayMinAddrY_clicked()
{
    QString str = ui->m_DisplayMinAddrY->text();
    Keyboard ctlAddr;
    AddressInputDialog dlg_readaddress(ctlAddr,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->m_DisplayMinAddrY->setText(ctlAddr.sShowAddr);
    }
}

void XYTrendGenDlg::on_m_BtnDisplayMaxAddrY_clicked()
{
    QString str = ui->m_DisplayMaxAddrY->text();
    Keyboard ctlAddr;
    AddressInputDialog dlg_readaddress(ctlAddr,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->m_DisplayMaxAddrY->setText(ctlAddr.sShowAddr);
    }
}
