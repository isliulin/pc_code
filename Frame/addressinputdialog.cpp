#include "addressinputdialog.h"
#include "Frame\structHead.h"
#include "Frame\mainwindow.h"
extern MainWindow *pwnd;


//#include "ui_bitbtndialog.h"

AddressInputDialog::AddressInputDialog(QWidget *parent,int addrType) :
    QDialog(parent),
    ui(new Ui::AddressInputDialog)
{
    m_type = pwnd->Addr_Type;
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    temp_Com="";//��ʼ��COM����Ϣ����û�õ�com2�������Ϊ��
    temp_PLC_Station="";//��ʼ��PLCվ�ţ���û�õ���չģʽ�������Ϊ��
    temp_address=new Keyboard;
    gl_lineeditintput=ui->addressinputdialog_address_lineedit;
    ui->addressinputdialog_address_lineedit->setFocus();
    ui->addressinputdialog_address_lineedit->selectAll();
    init();

}
AddressInputDialog::AddressInputDialog(Keyboard &address,QString sAddr,int addrType,QWidget *parent):
        QDialog(parent),
        ui(new Ui::AddressInputDialog)
{
	m_type = addrType;
    localkeyboard=&address;
    ui->setupUi(this);
    temp_Com="";//��ʼ��COM����Ϣ����û�õ�com2�������Ϊ��
    temp_PLC_Station="";//��ʼ��PLCվ�ţ���û�õ���չģʽ�������Ϊ��
    temp_address=new Keyboard;

    init();

    setAllparam(sAddr,addrType);
    ui->addressinputdialog_address_lineedit->setFocus();
    ui->addressinputdialog_address_lineedit->selectAll();

}
AddressInputDialog::AddressInputDialog(Keyboard &address, QWidget *parent,int addrType):
        QDialog(parent),
        ui(new Ui::AddressInputDialog)

{
    m_type = pwnd->Addr_Type;
    ui->setupUi(this);
    localkeyboard=&address;
    temp_address=new Keyboard;
    int temp_connect_type=address.nConnectType;
    int temp_plc_station=address.nPlcStationIndex;
    temp_PLC_Station = QString("%1:").arg(address.nPlcStationIndex);

    init();
    temp_connect_type = findConnect(temp_connect_type);
    ui->comboBox_storage->setCurrentIndex(temp_connect_type);//��������
    ui->comboBox_register->setCurrentIndex(ui->comboBox_register->findText(address.sPlcRegTypeStr));
    ui->addressinputdialog_address_lineedit->setText(address.sPlcAddrValue);//�������ӵĵ�ַ



    ui->pushbtnintput->setFocus();
    ui->addressinputdialog_address_lineedit->setFocus();
    ui->addressinputdialog_address_lineedit->selectAll();
}

AddressInputDialog::~AddressInputDialog()
{
    delete ui;
}
void AddressInputDialog::setAllparam(QString sAddr,int addrType)
{
    QStringList connects;
    for(int i=0; i<ui->comboBox_storage->count();i++)
    {
        connects << ui->comboBox_storage->itemText(i);
    }
	Keyboard kb = *temp_address;
    if (pwnd->m_LocalReg.contains(sAddr))
	{
		if (addrType == 0 && pwnd->m_LocalReg.value(sAddr).startsWith("LB",Qt::CaseInsensitive))
		{
			ui->comboBox_storage->setCurrentIndex(0);
			ui->comboBox_register->setCurrentIndex(ui->comboBox_register->findText(sAddr));
		}
		if (addrType == 1 && pwnd->m_LocalReg.value(sAddr).startsWith("LW",Qt::CaseInsensitive))
		{
			ui->comboBox_storage->setCurrentIndex(0);
			ui->comboBox_register->setCurrentIndex(ui->comboBox_register->findText(sAddr));
		}
	}
    else if(pwnd->CheckString(kb, sAddr, addrType) == ADDR_CORRECT)//����ĵ�ַ�Ϸ�
    {
		*temp_address = kb;
		int cmbIndex = findConnect(kb.nConnectType);
        ui->comboBox_storage->setCurrentIndex(cmbIndex);
        if(kb.nConnectType != 0)
        {
            qDebug() << kb.sPlcName;

            int protocolIndex = ui->comboBox_protocol->findText(kb.sPlcName);
            ui->comboBox_protocol->setCurrentIndex(protocolIndex);
            qDebug() <<"protocolIndex---"<< protocolIndex;
        }
        int index  = ui->comboBox_register->findText(kb.sPlcRegTypeStr);
        if(index >= 0)
        {
            ui->comboBox_register->setCurrentIndex(index);
        }
        //ui->comboBox_register->setCurrentIndex(kb.nPlcRegTypeIndex);
        ui->addressinputdialog_address_lineedit->setText(kb.sPlcAddrValue);
    }
    else
    {
        if(!addrType)
        {
            ui->comboBox_storage->setCurrentIndex(0);
            ui->comboBox_register->setCurrentIndex(0);
            ui->addressinputdialog_address_lineedit->setText("0");
        }
        else
        {
            ui->comboBox_storage->setCurrentIndex(0);
            ui->comboBox_register->setCurrentIndex(1);
            ui->addressinputdialog_address_lineedit->setText("0");
        }
    }
}

void AddressInputDialog::init()
{
    QStringList connects;
    connects << tr("�ڲ��洢��");

    foreach(stConnect cnt,pwnd->m_pSamSysParame->m_qvcConnect)
    {
        if(!cnt.sConnectName.isEmpty() && !cnt.vProtocols.isEmpty())
        {
            connects << cnt.sConnectName;
        }
    }
    ui->comboBox_storage->addItems(connects);


}
void AddressInputDialog::on_pushbtn1_clicked()
{
    ui->addressinputdialog_address_lineedit->insert(tr("1"));
}

void AddressInputDialog::on_pushbtn2_clicked()
{
    ui->addressinputdialog_address_lineedit->insert(tr("2"));
}

void AddressInputDialog::on_pushbtn3_clicked()
{
    ui->addressinputdialog_address_lineedit->insert(tr("3"));
}

void AddressInputDialog::on_pushbtn4_clicked()
{
    ui->addressinputdialog_address_lineedit->insert(tr("4"));
}

void AddressInputDialog::on_pushbtn5_clicked()
{
    ui->addressinputdialog_address_lineedit->insert(tr("5"));
}

void AddressInputDialog::on_pushbtn6_clicked()
{
     ui->addressinputdialog_address_lineedit->insert(tr("6"));
}

void AddressInputDialog::on_pushButton7_clicked()
{
     ui->addressinputdialog_address_lineedit->insert(tr("7"));
}



void AddressInputDialog::on_pushButton8_clicked()
{
     ui->addressinputdialog_address_lineedit->insert(tr("8"));
}

void AddressInputDialog::on_pushButton9_clicked()
{
     ui->addressinputdialog_address_lineedit->insert(tr("9"));
}

void AddressInputDialog::on_pushButton0_clicked()
{
     ui->addressinputdialog_address_lineedit->insert(tr("0"));
}

void AddressInputDialog::on_pushbtnclear_clicked()
{
     ui->addressinputdialog_address_lineedit->clear();
}

void AddressInputDialog::on_pushbtnback_clicked()
{
    QString str=ui->addressinputdialog_address_lineedit->text();
    int len=str.size()-1;
    str.resize(len);
    ui->addressinputdialog_address_lineedit->setText(str);
}

void AddressInputDialog::on_pushbtnquit_clicked()
{
    reject();
}

void AddressInputDialog::on_pushbtnintput_clicked()
{
    int iFlg;
    if(ui->comboBox_storage->currentIndex()==0)//�ڲ��Ĵ����Ļ�
    {
        //�ڲ��Ĵ���վ�Ŷ�Ϊ100
        temp_address->nPlcStationIndex=100;
    }
	QString header = "["+ui->comboBox_protocol->currentText()+"]";
	if (ui->comboBox_storage->currentIndex() == 0)
	{
		header = "";
	}
    temp_address->sShowAddr=header+temp_address->sPlcRegTypeStr+temp_address->sPlcAddrValue;
    iFlg=IsCorrect();
     QMessageBox msg(QMessageBox::Warning,PRO_FULL_NAME,tr("��ַ�������"),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);

	switch(iFlg)
	{
	case ADDR_CORRECT://�޴���
		break;
	case ADDR_STRING_NULL://����Ϊ��
		msg.setText(tr("�����ַ����Ϊ�գ�"));
		msg.exec();
		ui->addressinputdialog_address_lineedit->setFocus();
		ui->addressinputdialog_address_lineedit->selectAll();
		return ;
	case ILLEGAL_REG://�Ĵ������Ͳ�ƥ�����
		msg.setText(tr("�Ĵ����������ַҪ��ƥ�䣡"));
		msg.exec();
		ui->addressinputdialog_address_lineedit->setFocus();
		ui->addressinputdialog_address_lineedit->selectAll();
		return ;
	case INVALID_CONNECT://�ֶ������ַ����ʱ��û�и�����
		msg.setText(tr("û����Ӹ����ӿڣ�"));
		msg.exec();
		ui->addressinputdialog_address_lineedit->setFocus();
		ui->addressinputdialog_address_lineedit->selectAll();
		return ;
	case ADDR_OUT_BOUND://���ݳ��� ����ֵΪ����ֵ ����Ϊ�����ֵ ����Ϊ�����ֵ

		msg.setText(tr("��ֵַ������Χ��"));
		msg.exec();
		ui->addressinputdialog_address_lineedit->setFocus();
		ui->addressinputdialog_address_lineedit->selectAll();
		return;
	default://�����ʽ����
		msg.setText(tr("�����ʽ����"));
		msg.exec();
		ui->addressinputdialog_address_lineedit->setFocus();
		ui->addressinputdialog_address_lineedit->selectAll();
		return ;

	}
    
    localkeyboard->nConnectType=temp_address->nConnectType;
    localkeyboard->sShowAddr=temp_address->sShowAddr;
    localkeyboard->sPlcAddrValue=temp_address->sPlcAddrValue;
    localkeyboard->nPlcRegTypeIndex=temp_address->nPlcRegTypeIndex;
    localkeyboard->nPlcStationIndex=temp_address->nPlcStationIndex;
    localkeyboard->sPlcRegTypeStr=temp_address->sPlcRegTypeStr;
    localkeyboard->nAddrType = m_type;
	localkeyboard->sPlcName = ui->comboBox_protocol->currentText();
    accept () ;

}
int AddressInputDialog::IsCorrect()
{
    int result = ADDR_OTHER_ERROR;
	
	int connectIndex = ui->comboBox_storage->currentIndex();
	int protocolIndex = ui->comboBox_protocol->currentIndex();
	int registerIndex = ui->comboBox_register->currentIndex();
	QString sAddr = ui->addressinputdialog_address_lineedit->text();
	QString sReg = ui->comboBox_register->currentText();
	if (connectIndex == 0)//�ڲ�����
	{
		if (pwnd->m_LocalReg.keys().contains(sReg))
		{
			if (m_type == 0 && pwnd->m_LocalReg.value(sReg).startsWith("LB",Qt::CaseInsensitive))
			{
				temp_address->sShowAddr = sReg;
				return ADDR_CORRECT;
			}
			if (m_type == 1 && pwnd->m_LocalReg.value(sReg).startsWith("LW",Qt::CaseInsensitive))
			{
				temp_address->sShowAddr = sReg;
				return ADDR_CORRECT;
			}
			
		}
		if (ui->addressinputdialog_address_lineedit->text().isEmpty())
		{
			return ADDR_STRING_NULL;
		}

		if (registerIndex == 0 && m_type == 0 && NumIsDigit2(sAddr))
		{
			if (sAddr.toInt()>=0 && sAddr.toInt()<65536)
			{
				return ADDR_CORRECT;//LB ��ȷ��ַ
			}
			else
			{
				return ADDR_OUT_BOUND;//������Χ
			}
			
		}
		else if (registerIndex >0 && m_type>0 && NumIsDigit2(sAddr))
		{
			if (sAddr.toInt()>=0 && sAddr.toInt()<65536)
			{
				return ADDR_CORRECT;//LW RWI ��ȷ��ַ
			}
			else
			{
				return ADDR_OUT_BOUND;//������Χ
			}
		}
		else
			return ADDR_OTHER_ERROR;		
		
	}
	else
	{
		if (ui->addressinputdialog_address_lineedit->text().isEmpty())
		{
			return ADDR_STRING_NULL;
		}
		connectIndex = 1;
		foreach(stConnect cnt,pwnd->m_pSamSysParame->m_qvcConnect)
		{
			if(ui->comboBox_storage->currentText() == cnt.sConnectName)
			{
				break;
			}
			connectIndex++;
		}
		return checkAddrFromLib(connectIndex,protocolIndex,registerIndex);
	}
	
    return result;
}
//����ⲿ��ַ�����ʽ
int AddressInputDialog::checkAddrFromLib(int connectIndex,int protocolIndex,int registerIndex)
{
	QString sAddr = ui->addressinputdialog_address_lineedit->text();
	if (connectIndex <1 || protocolIndex <0 || registerIndex <0)//�޴����ӻ���Э�顢�Ĵ���
	{
		return INVALID_CONNECT;
	}
	QVector<stProtocol> vProtocols;
	stProtocol ptl;
	if (pwnd->m_pSamSysParame->m_qvcConnect.size()> connectIndex-1)
	{
		vProtocols = pwnd->m_pSamSysParame->m_qvcConnect[connectIndex-1].vProtocols;
		if (vProtocols.size() > protocolIndex)
		{
			ptl = vProtocols[protocolIndex];
		}		
	}
        QString sPlcName = ui->comboBox_register->currentText();
        int index = ptl.mPlc.regs.indexOf(sPlcName);
        if(index >= 0)
        {
            registerIndex = index;
        }
        else
        {
            return ADDR_OTHER_ERROR;
        }
    QString path = "Drivers/qtdll/"+ptl.sFactoryName +"/"+ptl.mPlc.sModelName+".dll";
	QLibrary lib(path);
	
	if(lib.load())
	{
		typedef ADDR_CHECK_ERROR_INFO (*ADDPROC)(ADDR_CHECK_SOURCE_PROP , ADDR_REG_TYPE );
		ADDPROC check= (ADDPROC)lib.resolve("checkAddrCorrect");
		if(check)
		{
			ADDR_CHECK_SOURCE_PROP spro;
			spro.nAddrLen = 1;
            spro.sRegName = ptl.mPlc.regs.at(registerIndex).toStdString();;
			spro.eAddrRWprop = SCENE_CONTROL_ONCE_W;
			spro.nPlcStationIndex = ptl.nPlcNo;
			spro.sAddrValue = sAddr.toStdString();


            int result = check(spro,(addrRegType)(m_type+1));
            return result;

            lib.unload();
			
		}
	}
	return INVALID_CONNECT;
}
void AddressInputDialog::on_pushbtna_clicked()
{
  ui->addressinputdialog_address_lineedit->insert(tr("A"));
}

void AddressInputDialog::on_pushbtnb_clicked()
{
    ui->addressinputdialog_address_lineedit->insert(tr("B"));
}

void AddressInputDialog::on_pushbtnc_clicked()
{
  ui->addressinputdialog_address_lineedit->insert(tr("C"));
}

void AddressInputDialog::on_pushbtnd_clicked()
{
    ui->addressinputdialog_address_lineedit->insert(tr("D"));
}

void AddressInputDialog::on_pushbtne_clicked()
{
    ui->addressinputdialog_address_lineedit->insert(tr("E"));
}

void AddressInputDialog::on_pushbtnf_clicked()
{
    ui->addressinputdialog_address_lineedit->insert(tr("F"));
}

void AddressInputDialog::on_pushbtndot_clicked()
{
    ui->addressinputdialog_address_lineedit->insert(tr("."));
}

void AddressInputDialog::on_pushbtnslash_clicked()
{
   ui->addressinputdialog_address_lineedit->insert(tr("/"));
}

void AddressInputDialog::on_pushbtncolon_clicked()
{
    ui->addressinputdialog_address_lineedit->insert(tr(":"));
}

void AddressInputDialog::on_comboBox_storage_currentIndexChanged(int index)
{
    //int flg=0;//��ʾ�Ƿ����plc�ļĴ���
    temp_Com="";
	int connectIndex = 0;
    if(index==0)
    {
        ui->comboBox_register->clear();

        ui->comboBox_register->addItem("LB");
        ui->comboBox_register->addItem("LW");
        ui->comboBox_register->addItem("RWI");
		foreach(QString variable,pwnd->m_LocalReg.keys())
		{
			if (m_type == 0 
				&& pwnd->m_LocalReg.value(variable).startsWith("LB",Qt::CaseInsensitive))
			{
				ui->comboBox_register->addItem(variable);
			}
			if (m_type == 1 
				&& pwnd->m_LocalReg.value(variable).startsWith("LW",Qt::CaseInsensitive))
			{
				ui->comboBox_register->addItem(variable);
			}
		}
        if(m_type)
        {
            ui->comboBox_register->setCurrentIndex(1);
        }
        else
        {
            ui->comboBox_register->setCurrentIndex(0);
        }
        ui->comboBox_protocol->clear();
        ui->comboBox_protocol->setVisible(false);
    }
    else
    {
        QString sPlc;
        QStringList plcs;
        QString connectName = ui->comboBox_storage->currentText();
		
        foreach(stConnect cnt,pwnd->m_pSamSysParame->m_qvcConnect)
        {
			connectIndex++;
            if(cnt.sConnectName == connectName)
            {
                foreach(stProtocol protocol,cnt.vProtocols)
                {
                    plcs << protocol.sName;
                }
				break;
            }
			
        }
        ui->comboBox_protocol->setVisible(true);
		ui->comboBox_protocol->clear();
        ui->comboBox_protocol->addItems(plcs);
    }


    temp_address->nConnectType=connectIndex;
    temp_address->sPlcRegTypeStr=ui->comboBox_register->currentText();

}

void AddressInputDialog::on_plc_station_currentIndexChanged(int index)
{

}

void AddressInputDialog::on_addressinputdialog_address_lineedit_textChanged(QString index )
{
    temp_address->sPlcAddrValue=index;
}

void AddressInputDialog::on_comboBox_register_currentIndexChanged(int index)
{
    temp_address->nPlcRegTypeIndex=index;
    temp_address->sPlcRegTypeStr=ui->comboBox_register->currentText();
    ui->addressinputdialog_address_lineedit->setFocus();
    ui->addressinputdialog_address_lineedit->selectAll();
    temp_address->sPlcName = ui->comboBox_protocol->currentText();
	if (ui->comboBox_storage->currentIndex() == 0 && ui->comboBox_register->currentIndex() >2)
	{
		ui->addressinputdialog_address_lineedit->setVisible(false);
	}
	else
		ui->addressinputdialog_address_lineedit->setVisible(true);
}
bool AddressInputDialog::NumIsDigit2(QString str)//�޷���10����
{
        if(str=="") return false;

    bool flage=false;
        int length=str.length();

        for(int i=0;i<length;i++)
                if(str[i]>='0'&&str[i]<='9') flage=true;
                else {flage=false;break;}
                return flage;
}

void AddressInputDialog::on_comboBox_protocol_currentIndexChanged(QString name)
{
	if (ui->comboBox_storage->currentIndex() == 0)
	{
		return ;
	}
    ui->comboBox_register->clear();
    bool bExist = false;
    stProtocol cModel;
    foreach(stConnect cnt,pwnd->m_pSamSysParame->m_qvcConnect)
    {
        foreach(stProtocol model,cnt.vProtocols)
        {
            if(model.sName == name)
            {
                bExist = true;
                cModel = model;
                break;
            }
        }
        if(bExist)
            break;
    }
    if(bExist)
    {
        if(0 == m_type)//λ��ַ
        {
            ui->comboBox_register->addItems(cModel.mPlc.sBitregs);
        }
        else if(1 == m_type)//�ֵ�ַ
        {
            QStringList sAddr;
            sAddr.clear();
            sAddr << cModel.mPlc.sWorldregs;
            //sAddr << cModel.mPlc.sDworldregs;
            ui->comboBox_register->addItems(sAddr);
        }
        else
        {
            return;
        }
    }

}
int AddressInputDialog::findConnect(int index)
{
	if (index == 0)//�ڲ��洢��
	{
		return 0;
	}
	int cmbIndex = -1;
	QStringList sConnects;
	for (int i=0;i<ui->comboBox_storage->count();i++)
	{
		sConnects << ui->comboBox_storage->itemText(i);
	}
	QVector<stConnect> vConnects = pwnd->m_pSamSysParame->m_qvcConnect;
	if (vConnects.size()>index-1)
	{
		QString connectName = vConnects[index-1].sConnectName;
		cmbIndex = sConnects.indexOf(connectName);
		
	}
	return cmbIndex;
}
