#include "wordwidget.h"
#include "ui_wordwidget.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;
WordWidget::WordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WordWidget)
{
    ui->setupUi(this);
    ui->check_cycle->setVisible(false);
    ui->comboBox_dataType->setCurrentIndex(2);
    on_comboBox_dataType_currentIndexChanged(2);

    ui->edit_const->setText("LW0");
    ui->edit_const->setEnabled(false);
    ui->btn_wordAddr_const->setEnabled(false);
}

WordWidget::~WordWidget()
{
    delete ui;
}
QString WordWidget::getAddr()
{
    return ui->edit_operatingAddr->text();
}

void WordWidget::on_edit_operatingAddr_textChanged(QString string)
{
    emit AddrChanged(string);
}

void WordWidget::on_btn_wordAddr_clicked()
{
	QString addrStr = ui->edit_operatingAddr->text();
	AddressInputDialog addressintputdlg_writeaddress(wordAddr,addrStr,1,this);
	if(addressintputdlg_writeaddress.exec())
	{
		ui->edit_operatingAddr->setText(wordAddr.sShowAddr);
	}
}

bool WordWidget::Save()
{
    if(! pwnd->IsAddressCheckRight(wordAddr,tr("写入地址"),ui->edit_operatingAddr,1))
    {
        ui->edit_operatingAddr->setFocus();
        return false;
    }
    else if((ui->check_const->isChecked())&&(! pwnd->IsAddressCheckRight(wordAddrConst, tr("写入地址"), ui->edit_const,1)))
    {
        ui->edit_const->setFocus();
        return false;
    }
    else
    {
        switch(ui->comboBox_dataType->currentIndex())
        {
        case 1:
        case 3:
        case 5:
        case 6:
            wordAddr.Length = 2;
            wordAddrConst.Length = 2;
            break;
        default:
            wordAddr.Length = 1;
            wordAddrConst.Length = 1;
        }
        wordproperty.addr = wordAddr;
        wordproperty.operType = (WORD_OPER_TYPE)ui->comboBox_operateType->currentIndex();
        wordproperty.dataType = (DATA_TYPE)ui->comboBox_dataType->currentIndex();
        wordproperty.value = ui->edit_value->text().toDouble();
        wordproperty.bCycle = ui->check_cycle->isChecked();
        wordproperty.nMax = ui->edit_max->text().toDouble();
        wordproperty.nMin = ui->edit_min->text().toDouble();

        wordproperty.bDynamicControl = ui->check_const->isChecked();
        wordproperty.addrConst = wordAddrConst;
        return true;
    }
}

void WordWidget::InitUi(wordSwitchPro property)
{
    ui->edit_operatingAddr->setText(property.addr.sShowAddr);
    ui->comboBox_dataType->setCurrentIndex(property.dataType);

    ui->comboBox_operateType->setCurrentIndex(property.operType);

    ui->edit_value->setText(QString::number(property.value,'g',10));
    ui->check_cycle->setChecked(property.bCycle);
    ui->edit_max->setText(QString::number(property.nMax,'g',10));
    ui->edit_min->setText(QString::number(property.nMin,'g',10));
    wordAddr = property.addr;
    on_comboBox_operateType_currentIndexChanged(property.operType);

    wordAddrConst = property.addrConst;
    ui->check_const->setChecked(property.bDynamicControl);
    if(property.bDynamicControl)
    {
        ui->edit_const->setText(property.addrConst.sShowAddr);
        ui->edit_const->setEnabled(true);
        ui->btn_wordAddr_const->setEnabled(true);
        ui->edit_value->setEnabled(false);
    }
    else
    {
        ui->edit_const->setText("LW0");
        ui->edit_const->setEnabled(false);
        ui->btn_wordAddr_const->setEnabled(false);
        ui->edit_value->setEnabled(true);
    }
}

void WordWidget::on_comboBox_dataType_currentIndexChanged(int index)
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
	ui->edit_value->setValidator(validator);
    ui->edit_max->setValidator(validator);
    ui->edit_min->setValidator(validator);

    ui->edit_max->setText(QString::number(nMax,'g',10));
    ui->edit_min->setText(QString::number(nMin,'g',10));

	double value = ui->edit_value->text().toDouble();
	if (value > nMax || value < nMin)
	{
		ui->edit_value->setText("0");
	}
}

void WordWidget::on_comboBox_operateType_currentIndexChanged(int index)
{
    if(index == 1 || index == 2 || index == 3 || index == 4)
    {
        ui->check_cycle->setVisible(true);
    }
    else
        ui->check_cycle->setVisible(false);
}

void WordWidget::on_check_const_clicked(bool bChecked)
{
    if(ui->check_const->isChecked())
    {
      ui->edit_const->setEnabled(true);
      ui->btn_wordAddr_const->setEnabled(true);
      ui->edit_value->setEnabled(false);
    }
    else
    {
        ui->edit_const->setEnabled(false);
        ui->btn_wordAddr_const->setEnabled(false);
        ui->edit_value->setEnabled(true);
    }
    wordproperty.bDynamicControl = ui->check_const->isChecked();
}

void WordWidget::on_btn_wordAddr_const_clicked()
{
    QString addrConstStr = ui->edit_const->text();
    AddressInputDialog addressintpudlg(wordAddrConst, addrConstStr, 1, this);
    if(addressintpudlg.exec())
    {
        ui->edit_const->setText(wordAddrConst.sShowAddr);
    }
}
