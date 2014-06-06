#include "monitorwidget.h"
#include "ui_monitorwidget.h"
#include "Frame/ThingDlg/qmultistategenelcunstomdlg.h"

#include "Frame/mainwindow.h"
#include "view/switchitem.h"
#include "view/mfbtnitem.h"

extern MainWindow *pwnd;

Monitorwidget::Monitorwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Monitorwidget)
{
    ui->setupUi(this);
    ui->btn_customValue->setEnabled(false);
    functionType = 0;
        ui->label_2->setEnabled(false);
    ui->spinBox_bitIndex->setEnabled(false);
    ui->edit_bitAddr->setText("LB0");
    ui->groupBox->setChecked(false);
    bMonitor = true;
}

Monitorwidget::~Monitorwidget()
{
    delete ui;
}

void Monitorwidget::init(QItemGroup *pItem)
{
    item = pItem;
    if(item)
    {
        if(item->GroupType() == SAM_DRAW_GROUP_SWITCH)
        {
            SwitchItem *switchitem = dynamic_cast<SwitchItem *> (item);
            if(switchitem)
            {
                mProperty = switchitem->mPro;
            }
        }
        else if(item->GroupType() == SAM_DRAW_GROUP_MFBTN)
        {
            MfBtnItem *mbftnItem = dynamic_cast<MfBtnItem *>(item);
            if(mbftnItem)
            {
                mProperty = mbftnItem->mPro;
            }
        }

        switch(mProperty.monitorType)
        {
        case NONE:
            ui->groupBox->setChecked(false);
            on_groupBox_clicked(false);
            ui->group_bit->setDisabled(true);
            ui->group_word->setDisabled(true);
            break;
        case BIT_MONITOR:
            {
                ui->groupBox->setChecked(true);
                ui->group_bit->setChecked(true);

                ui->comboBox_bitAddr->setCurrentIndex(mProperty.bBitAddr);
                ui->edit_bitAddr->setText(mProperty.addr.sShowAddr);
                ui->spinBox_bitIndex->setValue(mProperty.bitIndex);
                ui->check_sameBit->setChecked(mProperty.bSameAddr);
                //this->on_group_bit_clicked(true);
                monitorAddr = mProperty.addr;
            }
            break;
        case POLY:
            {
                ui->groupBox->setChecked(true);
                ui->group_word->setChecked(true);

                ui->edit_wordAddr->setText(mProperty.addr.sShowAddr);
                ui->combo_dataType->setCurrentIndex(mProperty.dataType);
                ui->check_sameWord->setChecked(mProperty.bSameAddr);
                ui->spin_statusCount->setValue(mProperty.count);

                ui->combo_condition->setCurrentIndex(mProperty.valueType);
                values = mProperty.values;
                this->on_group_word_clicked(true);
                monitorAddr = mProperty.addr;
            }
            break;
        default:
            break;
        }
    }
}
//选择双态监视
void Monitorwidget::on_group_bit_clicked(bool checked)
{
    ui->group_word->setChecked(!checked);
    if(functionType <2 && checked)
    {
        ui->check_sameBit->setDisabled(false);
    }
    else
        ui->check_sameBit->setDisabled(true);
    if(checked)
    {
        emit signalBitLamp();
    }
    else
    {
        int count = ui->spin_statusCount->value();
        emit StatusCountChanged(count);
    }
}

//选择多态监视
void Monitorwidget::on_group_word_clicked(bool checked)
{
    ui->group_bit->setChecked(!checked);
    if(functionType <2 && checked)
    {
        ui->check_sameWord->setDisabled(false);
    }
    else
        ui->check_sameWord->setDisabled(true);

    if(!checked)
    {
        emit signalBitLamp();
    }
    else
    {
        int count = ui->spin_statusCount->value();
        emit StatusCountChanged(count);
    }
}

//选择自定义状态值
void Monitorwidget::on_btn_customValue_clicked()
{
    QMultiStateGenelCunstomDlg *customDlg=new QMultiStateGenelCunstomDlg(this);

    customDlg->setRange(ui->combo_dataType->currentIndex());
    customDlg->setAllData(values,false);
    if(customDlg->exec() == QDialog::Accepted)
    {
        values = customDlg->getValues();
    }
}

//状态切换条件 更改
void Monitorwidget::on_combo_condition_currentIndexChanged(int index)
{
    if(index == 2)//选择自定义状态
    {
        ui->btn_customValue->setEnabled(true);
        int statusCount = ui->spin_statusCount->value();
        values.resize(statusCount);
        for (int i = 0; i < values.size(); ++i)
        {
            values[i] = i;
        }
    }
    else               //隐藏自定义状态设定按钮
    {
        ui->btn_customValue->setEnabled(false);
    }
}


//总状态数改变的响应函数
void Monitorwidget::on_spin_statusCount_valueChanged(int count)
{
    int size = values.size();
    if(size < count)
    {
        for(int i = size; i < count; i++)
        {
            values << i;
        }
    }
    else
    {
        for(int i = size; i > count; i--)
        {
            values.remove(i-1);
        }
    }
    emit StatusCountChanged(count);
}



void Monitorwidget::changeAddr(QString string)
{
    if(ui->check_sameBit->isChecked())
    {
        ui->edit_bitAddr->setText(string);
    }
    if(ui->check_sameWord->isChecked())
    {
        ui->edit_wordAddr->setText(string);
    }
}

//禁用或启用 “跟操作地址相同”
//无操作地址的时候，禁用 “跟操作地址相同”
void Monitorwidget::SetCheckDisabled(bool checked)
{
    if(checked)
    {
        ui->check_sameBit->setDisabled(true);
        ui->check_sameWord->setDisabled(true);

        if(ui->group_bit->isChecked())
            ui->check_sameBit->setDisabled(true);
        if(ui->group_word->isChecked())
            ui->check_sameWord->setDisabled(true);
		ui->check_sameBit->setChecked(false);
		ui->check_sameWord->setChecked(false);
    }
    else
    {
        if(ui->group_bit->isChecked())
            ui->check_sameBit->setDisabled(false);
        if(ui->group_word->isChecked())
            ui->check_sameWord->setDisabled(false);
		
    }

}

//选择与操作地址相同
void Monitorwidget::on_check_sameBit_stateChanged(int checked)
{
    if(checked)
    {
        emit signalSetCheckSame(0);

    }
	ui->comboBox_bitAddr->setDisabled(checked);
    ui->edit_bitAddr->setDisabled(checked);
    ui->btn_bitAddr->setDisabled(checked);
}

//选择与操作地址相同
void Monitorwidget::on_check_sameWord_stateChanged(int checked)
{
    if(checked)
    {
        emit signalSetCheckSame(0);

    }
    ui->edit_wordAddr->setDisabled(checked);
    ui->btn_wordAddr->setDisabled(checked);
}

void Monitorwidget::on_comboBox_bitAddr_currentIndexChanged(int index)
{
    if(index == 0)
    {
                ui->label_2->setEnabled(false);
        ui->spinBox_bitIndex->setEnabled(false);
    }
	else
	{
                ui->label_2->setEnabled(true);
                ui->spinBox_bitIndex->setEnabled(true);
	}
        
}

void Monitorwidget::on_btn_bitAddr_clicked()
{
    QString addrStr = ui->edit_bitAddr->text();
	int type = ui->comboBox_bitAddr->currentIndex();
    AddressInputDialog addressintputdlg_writeaddress(monitorAddr,addrStr,type,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->edit_bitAddr->setText(monitorAddr.sShowAddr);
    }


}

void Monitorwidget::setAddrType(int type)
{
	if (ui->check_sameBit->isChecked() 
		&& ui->comboBox_bitAddr->count()>type )
	{
		ui->comboBox_bitAddr->setCurrentIndex(type);
	}
	
}
void Monitorwidget::on_btn_wordAddr_clicked()
{
    QString addrStr = ui->edit_wordAddr->text();
    AddressInputDialog addressintputdlg_writeaddress(monitorAddr,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->edit_wordAddr->setText(monitorAddr.sShowAddr);
    }

}

//保存属性到item
bool Monitorwidget::Save()
{
    if((bMonitor && !ui->groupBox->isCheckable())
		|| ui->groupBox->isChecked() )
    {
        if(ui->group_bit->isChecked())
        {
			int addType = 0;
			if (ui->comboBox_bitAddr->currentIndex()>0)
			{
				addType = 1;
			}
            if(! pwnd->IsAddressCheckRight(monitorAddr,tr("监视地址"),ui->edit_bitAddr,addType))
            {
                ui->edit_bitAddr->setFocus();
                return false;
            }
            monitorAddr.Length = 1;
            mProperty.monitorType = BIT_MONITOR;
            mProperty.addr = monitorAddr;
            mProperty.count = 2;
            mProperty.bSameAddr = ui->check_sameBit->isChecked();
            mProperty.bBitAddr = ui->comboBox_bitAddr->currentIndex();
            mProperty.bitIndex = ui->spinBox_bitIndex->value();
        }
        else
        {
            if(! pwnd->IsAddressCheckRight(monitorAddr,tr("监视地址"),ui->edit_wordAddr,1))
            {
                ui->edit_wordAddr->setFocus();
                return false;
            }
            if(ui->combo_dataType->currentIndex() == 0)
            {
                monitorAddr.Length = 1;
            }
            else
            {
                monitorAddr.Length = 2;
            }

            mProperty.monitorType = POLY;
            mProperty.addr = monitorAddr;
            mProperty.bSameAddr = ui->check_sameWord->isChecked();
            mProperty.dataType = (DATA_TYPE)ui->combo_dataType->currentIndex();
            mProperty.valueType = ui->combo_condition->currentIndex();
            mProperty.count = ui->spin_statusCount->value();
            mProperty.values = values;
        }
    }
    else
    {
        mProperty.monitorType = NONE;
        mProperty.count = 1;
    }

    qDebug() <<"mProperty.count ===="<< mProperty.count;
    return true;
}

void Monitorwidget::on_groupBox_clicked(bool checked)
{
    if(!checked)
    {
        emit StatusCountChanged(1);
    }
    else
    {
        ui->group_bit->setDisabled(false);
        ui->group_word->setDisabled(false);
        if(ui->group_bit->isChecked())
        {
            ui->group_bit->setChecked(true);
			on_group_bit_clicked(true);
            //emit StatusCountChanged(2);
        }
        else
        {
            ui->group_word->setChecked(true);

            int count = ui->spin_statusCount->value();
            emit StatusCountChanged(count);
        }
    }
}
void Monitorwidget::setFuncType(int type)
{
	functionType = type;
	if (type == 4)
	{
		ui->groupBox->setChecked(true);
		//ui->group_bit->setChecked(true);
		on_groupBox_clicked( true);
		//on_group_bit_clicked(true);
		ui->groupBox->setCheckable(false);
	}
	else{
		if (!ui->groupBox->isCheckable() && bMonitor)
		{
			ui->groupBox->setCheckable(true);
		}
		
	}
}
void Monitorwidget::setSlid(bool checked)
{
	bMonitor = checked;
	ui->groupBox->setCheckable(checked);
	ui->groupBox->setChecked(false);
    on_groupBox_clicked( false);
    
    ui->groupBox->setDisabled(!checked);
}

void Monitorwidget::setCheckSameVisiable(bool bVisiable)
{
    ui->check_sameBit->setVisible(bVisiable);
    ui->check_sameWord->setVisible(bVisiable);
}
