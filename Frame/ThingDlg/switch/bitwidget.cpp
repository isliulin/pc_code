#include "bitwidget.h"
#include "ui_bitwidget.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;
BitWidget::BitWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BitWidget)
{
    ui->setupUi(this);
    ui->label_3->setEnabled(false);
    ui->comboBox_executeType->setEnabled(false);

    //setStyleSheet ("background-color: rgb(255,0,0);color: rgb(255,255,255);");

}

BitWidget::~BitWidget()
{
    delete ui;
}


void BitWidget::on_comboBox_operateType_currentIndexChanged(int index)
{
	bool bValue = false;
	bool bShowCfm = true;
	switch (index)
	{
	case 0:
		bShowCfm = true;
		break;
	case 1:
		bShowCfm = true;
		break;
	case 2:
		bShowCfm = false;
        ui->groupBox->setChecked(false);
		break;
	case 3:
		bShowCfm = false;
		bValue = true;
        ui->groupBox->setChecked(false);
		break;
	}

    ui->label_3->setEnabled(bValue);
    ui->comboBox_executeType->setEnabled(bValue);
        ui->groupBox->setEnabled(bShowCfm);
   
}

QString BitWidget::getAddr()
{
    return ui->edit_operatingAddr->text();
}

void BitWidget::on_edit_operatingAddr_textChanged(QString string)
{
    emit AddrChanged(string);
}

void BitWidget::on_btn_bitAddr_clicked()
{
    QString addrStr = ui->edit_operatingAddr->text();
    AddressInputDialog addressintputdlg_writeaddress(bitAddr,addrStr,0,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->edit_operatingAddr->setText(bitAddr.sShowAddr);
    }
}
//保存属性到结构体
bool BitWidget::Save()
{
    if(! pwnd->IsAddressCheckRight(bitAddr,tr("写入地址"),ui->edit_operatingAddr,0))
    {
        ui->edit_operatingAddr->setFocus();
        return false;
    }
    bitAddr.Length = 1;
    bitproperty.addr = bitAddr;
    bitproperty.operType = (BIT_OPER_TYPE)ui->comboBox_operateType->currentIndex();
    bitproperty.bDown = ui->comboBox_executeType->currentIndex();
	bitproperty.bConfirm = ui->groupBox->isChecked();
	bitproperty.nTimeout = ui->spinBox->value();
    return true;
}

void BitWidget::InitUi(bitSwitchPro property)
{
    ui->edit_operatingAddr->setText(property.addr.sShowAddr);
    ui->comboBox_operateType->setCurrentIndex(property.operType);
	
    ui->comboBox_executeType->setCurrentIndex(property.bDown);
	ui->groupBox->setChecked(property.bConfirm);
	ui->spinBox->setValue(property.nTimeout); 
    bitAddr = property.addr;
	on_comboBox_operateType_currentIndexChanged(property.operType);
}
