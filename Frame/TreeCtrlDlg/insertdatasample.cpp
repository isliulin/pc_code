#include "insertdatasample.h"
#include "ui_insertdatasample.h"
#include "Frame/addressinputdialog.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

InsertDataSample::InsertDataSample(DATA_ADDRESS_ITEM item,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertDataSample)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    setFixedSize(size());
    setWindowTitle(tr("采集设定"));
	ui->edit_addr->setText(item.keyAddress.sShowAddr);
	//ui->spin_length->setValue(item.nAddrNumber);
    ui->groupBox->setChecked(item.bZoom);
    qDebug() << item.bRound;
    ui->checkBox->setChecked(item.bRound);

    if(item.dataType == UNICODE_STRING)
    {
        ui->combo_datatype->setCurrentIndex(8);
        on_combo_datatype_currentIndexChanged(8);
    }
    else
    {
        ui->combo_datatype->setCurrentIndex(item.dataType-2);
        on_combo_datatype_currentIndexChanged(item.dataType-2);
    }
    ui->spin_decLen->setValue(item.decLen);
	row = item.nAddrNumber;
    if(row <256)
    {
        ui->spin_length->setMaximum(256-row);
    }
    on_groupBox_clicked(item.bZoom);
	if (item.bZoom)
	{
		ui->inputMax->setText(QString::number(item.inputMax));
		ui->inputMin->setText(QString::number(item.inputMin));
		ui->outputMax->setText(QString::number(item.outputMax));
		ui->outputMin->setText(QString::number(item.outputMin));
	}
    ui->edit_name->setText(item.name);
}

InsertDataSample::~InsertDataSample()
{
    delete ui;
}

void InsertDataSample::on_btn_ok_clicked()
{
    QString sAddr = ui->edit_addr->text();
	Keyboard addr;
    if(sAddr.isEmpty())
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("数据采集地址不能为空"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }
    if(!pwnd->IsAddressCheckRight(addr,tr("数据采集地址"),ui->edit_addr,1))
    {
        return;
    }

    switch(ui->combo_datatype->currentIndex())
    {
    case 1:
    case 3:
    case 5:
    case 6:
        addr.Length = 2;
        break;
    case 7:
    case 8:
        addr.Length = ui->spin_decLen->value();
        break;
    default:
        addr.Length = 1;
    }

    m_Item.bZoom = ui->groupBox->isChecked();
    if(m_Item.bZoom)
    {
        m_Item.inputMax = ui->inputMax->text().toDouble();
        m_Item.inputMin = ui->inputMin->text().toDouble();
        m_Item.outputMax = ui->outputMax->text().toDouble();
        m_Item.outputMin = ui->outputMin->text().toDouble();
        if( (m_Item.inputMax< m_Item.inputMin)  || (m_Item.outputMax<m_Item.outputMin))
        {
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("数据处理范围有误"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("确定"),QMessageBox::AcceptRole);
            box.exec();
            return;
        }
    }

    m_Item.decLen = ui->spin_decLen->value();
    m_Item.bRound = ui->checkBox->isChecked();
    if(ui->combo_datatype->currentIndex() == 8)
    {
        m_Item.dataType = (DATA_TYPE)(UNICODE_STRING);
    }
    else
    {
        m_Item.dataType = (DATA_TYPE)(ui->combo_datatype->currentIndex()+2);
    }
    m_Item.nAddrNumber = row;
	m_Item.keyAddress = addr;
    m_Item.name = ui->edit_name->text();

    accept();
}

void InsertDataSample::on_btn_cancel_clicked()
{
    reject();
}

void InsertDataSample::on_btn_addr_clicked()
{
    Keyboard addr;

    QString addrStr = ui->edit_addr->text();
    AddressInputDialog addressintputdlg_writeaddress(addr,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->edit_addr->setText(addr.sShowAddr);
    }

}

QString InsertDataSample::getDatatypeStr()
{
	return ui->combo_datatype->currentText();
}


QVector <Keyboard> InsertDataSample::getAddrs()
{
	Keyboard kb = m_Item.keyAddress;
	QVector <Keyboard> Vaddrs;
    Vaddrs << kb;
	int count = ui->spin_length->value();
	int nIntervl = 1;
	switch (ui->combo_datatype->currentIndex())
	{
	case 1:
	case 3:
	case 5:
	case 6:
		nIntervl = 2;
		break;
    case 7:
    case 8:
        nIntervl = ui->spin_decLen->value();
        break;
	default:
		break;
	}
	 
    QVector<ADDR_CHECK_SOURCE_PROP> multiAddrs = kb.getMultiAddrs(nIntervl,count-1);
	foreach(ADDR_CHECK_SOURCE_PROP addrPro,multiAddrs)
	{
		kb.sPlcAddrValue = QString::fromStdString(addrPro.sAddrValue);
		kb.refreshShowAddr();
		Vaddrs<< kb;
	}
	return Vaddrs;
}
void InsertDataSample::on_groupBox_clicked(bool checked)
{
    ui->label_4->setEnabled(checked);
    ui->label_5->setEnabled(checked);
    ui->label_6->setEnabled(checked);
    ui->label_8->setEnabled(checked);
    ui->inputMax->setEnabled(checked);
    ui->inputMin->setEnabled(checked);
    ui->outputMax->setEnabled(checked);
    ui->outputMin->setEnabled(checked);
}
int InsertDataSample::sampleCount()
{
	return ui->spin_length->value();
}

void InsertDataSample::on_combo_datatype_currentIndexChanged(int index)
{
    DoubleValidator *validator = new DoubleValidator(-32768,32767,5,this);
    switch(index)
    {
    case 0://16位整数
        {
            validator = new DoubleValidator(-32768,32767,5,this);

        }
        break;
    case 1://32位整数
        {
            double dMax=2147483648L;
            double dMin=-2147483647L;
            validator = new DoubleValidator(dMin,dMax,5,this);

        }
        break;
    case 2://16位正整数
        {
            validator = new DoubleValidator(0,65535,5,this);

        }
        break;
    case 3://32位正整数
        {
            double dMax=4294967295L;
            double dMin=0;
            validator = new DoubleValidator(dMin,dMax,5,this);

        }
        break;
    case 4://16位BCD码
        {
            validator = new DoubleValidator(0,9999,4,this);

        }
        break;
    case 5://32位BCD码
        {
            validator = new DoubleValidator(0,99999999,8,this);

        }
        break;
    case 6://32位浮点数
        {
            double dMax=2147483648L;
            double dMin=-2147483647L;
            validator = new DoubleValidator(dMin,dMax,5,this);

        }
        break;
    }
    ui->inputMax->setValidator(validator);
    ui->inputMin->setValidator(validator);
    ui->outputMax->setValidator(validator);
    ui->outputMin->setValidator(validator);
    ui->checkBox->setVisible(index == 6);
    if(index == 7)//字符串
    {
        ui->groupBox->setDisabled(true);
        ui->label_7->setText(tr("字符串长度"));
        ui->spin_decLen->setRange(1,256);
        qDebug() << "index == 7";
    }
    else if(index == 8)
    {
        ui->groupBox->setDisabled(true);
        ui->label_7->setText(tr("字符串长度"));
        ui->spin_decLen->setRange(1,128);
        qDebug() << "index == 8";
    }
    else
    {
        ui->groupBox->setDisabled(false);
        ui->label_7->setText(tr("小数位数"));
        ui->spin_decLen->setRange(0,4);
        ui->spin_decLen->setValue(0);
        qDebug() << "index != 7";
    }
}
