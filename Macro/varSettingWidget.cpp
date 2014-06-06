
#include <QtGui>
#include <QComboBox>
#include "varSettingWidget.h"
#include "Frame/mainwindow.h"
#include "Macro/macro.h"
extern MainWindow *pwnd;

varSettingWidget::varSettingWidget(QTableWidget *parent,bool bMulti,bool bGlobal)
    : QDialog(parent)
{
    m_bGlobal = bGlobal;
    isMulti = bMulti;
    pTableWidget = new QTableWidget;
    pTableWidget =  parent;

    varNameLabel = new QLabel(tr("��������:"));
    nameLineEdit = new QLineEdit;
    varNameLabel->setBuddy(nameLineEdit);

    QRegExp regExp("[A-Za-z_][0-9a-zA-Z_]{1,20}");

    QValidator *validator = new QRegExpValidator(regExp,this);
    nameLineEdit->setValidator(validator);
    nameLineEdit->setToolTip(tr("��Ч�ַ�:A-Z,a-z,0-9,_"));

    dataTypeLabel = new QLabel(tr("�������:"));
    dataTypeLineEdit = new QComboBox;
    dataTypeLabel->setBuddy(dataTypeLineEdit);
    dataTypeLineEdit->addItem(tr("boolֵ"));
    dataTypeLineEdit->addItem(tr("16λ����"));
	dataTypeLineEdit->addItem(tr("16λ������"));
    dataTypeLineEdit->addItem(tr("32λ����"));
	dataTypeLineEdit->addItem(tr("32λ������"));
	dataTypeLineEdit->addItem(tr("����boolֵ"));
    dataTypeLineEdit->addItem(tr("����16λ����"));
	dataTypeLineEdit->addItem(tr("����16λ������"));
    dataTypeLineEdit->addItem(tr("����32λ����"));
	dataTypeLineEdit->addItem(tr("����32λ������"));
    dataTypeLineEdit->addItem(tr("32λ������"));
    dataTypeLineEdit->addItem(tr("����32λ������"));
    dataTypeLineEdit->addItem(tr("16λBCD��"));
    dataTypeLineEdit->addItem(tr("����16λBCD��"));
    dataTypeLineEdit->addItem(tr("32λBCD��"));
    dataTypeLineEdit->addItem(tr("����32λBCD��"));
    dataTypeLineEdit->addItem(tr("ASCII�ַ���"));
    dataTypeLineEdit->addItem(tr("UNICODE�ַ���"));
    connect(dataTypeLineEdit,SIGNAL(currentIndexChanged(int)),this,SLOT(setDataTypeIndex(int)));

    lengthLabel = new QLabel(tr("��    ��:"));
    lengthLineEdit = new QLineEdit;
    lengthLabel->setBuddy(lengthLineEdit);
    lengthLineEdit->setEnabled(false);
    QIntValidator *intValidator = new QIntValidator(2,1024,this);
	lengthLineEdit->setValidator(intValidator);

    rwLabel = new QLabel(tr("�� /  д:"));
    rwLineEdit = new QComboBox;
    rwLabel->setBuddy(rwLineEdit);
    rwLineEdit->addItem(tr("��"));
    rwLineEdit->addItem(tr("д"));
    rwLineEdit->addItem(tr("��д"));
    rwLineEdit->setCurrentIndex(2);
    connect(rwLineEdit,SIGNAL(currentIndexChanged(int)),this,SLOT(setRWIndex(int)));

    addressLabel = new QLabel(tr("��    ַ:"),this);
    addressLineEdit = new QLineEdit(this);
    addressLabel->setBuddy(addressLineEdit);

    offsetAddrLabel = new QLabel(tr("ƫ�Ƶ�ַ:"), this);
    offsetAddrEdit = new QLineEdit(this);
    offsetAddrLabel->setBuddy(offsetAddrEdit);

    countLabel = new QLabel(tr("����:"));
    countSpin = new QSpinBox;
    countLabel->setBuddy(countSpin);
    countSpin->setValue(1);
    countSpin->setRange(1,100);

    addressButton = new QPushButton;
    addressButton->setIcon(QIcon(":/standardtool/images/address.bmp"));
    addressButton->setFlat(true);

    offsetButton = new QPushButton;
    offsetButton->setIcon(QIcon(":/standardtool/images/address.bmp"));
    offsetButton->setFlat(true);

    okButton = new QPushButton(tr("ȷ��"));
    cancelButton = new QPushButton(tr("ȡ��"));

    groupBoxOffset = new QGroupBox(tr("ƫ�Ƶ�ַ"), this);
    groupBoxOffset->setCheckable(true);
    groupBoxOffset->setChecked(false);

    initMem();

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(varNameLabel);
    topLeftLayout->addWidget(nameLineEdit);

    QHBoxLayout *bottomLeftLayout = new QHBoxLayout;
    bottomLeftLayout->addWidget(lengthLabel);
    bottomLeftLayout->addWidget(lengthLineEdit);

    QHBoxLayout *topRightLayout = new QHBoxLayout;
    topRightLayout->addWidget(dataTypeLabel);
    topRightLayout->addWidget(dataTypeLineEdit);
    topRightLayout->addStretch(1);

    QHBoxLayout *bottomRightLayout = new QHBoxLayout;
    bottomRightLayout->addWidget(rwLabel);
    bottomRightLayout->addWidget(rwLineEdit);
    bottomRightLayout->addStretch(1);


    QHBoxLayout *addressLayout = new QHBoxLayout;
    addressLayout->addWidget(addressLabel);
    addressLayout->addWidget(addressLineEdit);
    addressLayout->addWidget(addressButton);
    addressLayout->addWidget(countLabel);
    addressLayout->addWidget(countSpin);
    //addressLayout->addStretch(1);
    addressLayout->setStretch(4,2);


    //ƫ�Ƶ�ַ
    QHBoxLayout *offsetAddrLayout = new QHBoxLayout;
    offsetAddrLayout->addWidget(offsetAddrLabel);
    offsetAddrLayout->addWidget(offsetAddrEdit);
    offsetAddrLayout->addWidget(offsetButton);
    groupBoxOffset->setLayout(offsetAddrLayout);

    QHBoxLayout *groupBoxLayout = new QHBoxLayout;
    groupBoxLayout->addWidget(groupBoxOffset);
    //offsetAddrLayout->setStretch(4,2);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(okButton);
    bottomLayout->addStretch();
    bottomLayout->addWidget(cancelButton);
    bottomLayout->addStretch();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addLayout(topLeftLayout,0,0,1,1);
    mainLayout->addLayout(topRightLayout,0,1,1,2);
    mainLayout->addLayout(bottomLeftLayout,2,0,1,1);
    mainLayout->addLayout(bottomRightLayout,2,1,1,2);
    mainLayout->addLayout(addressLayout,4,0,2,2);
    if(bMulti)
    {
        mainLayout->addLayout(bottomLayout,6,0,2,2);
        offsetButton->setVisible(false);
        groupBoxOffset->setVisible(false);
        offsetAddrLabel->setVisible(false);
    }
    else
    {
        mainLayout->addLayout(groupBoxLayout,6,0,2,4);
        mainLayout->addLayout(bottomLayout,10,0,2,2);
    }
    mainLayout->setRowStretch(1, 1);
    mainLayout->setRowStretch(2, 1);
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 1);

    setLayout(mainLayout);

    setWindowTitle(tr("�����趨"));
    setFixedHeight(sizeHint().height());

    connect(cancelButton,SIGNAL(clicked()),this,SLOT(noSaveRecord()));
    connect(okButton,SIGNAL(clicked()),this,SLOT(saveVarInfo()));
    nameLineEdit->setFocus();
    okButton->setDefault(true);
    connect(addressButton,SIGNAL(clicked()),this,SLOT(addrInput()));

    connect(offsetButton, SIGNAL(clicked()), this, SLOT(offsetInput()));
    connect(groupBoxOffset, SIGNAL(toggled(bool)), this, SLOT(groupBoxOffsetChanged(bool)));
    setModal(true);

    qDebug() << bMulti;
    countSpin->setVisible(bMulti);
    countLabel->setVisible(bMulti);
}

void varSettingWidget::setDefault(QVector<VarPro> vars,VarPro var)
{
    varNames.clear();
    if(m_bGlobal)
    {
        foreach(VarPro cVar,vars)
        {
            varNames << cVar.varName;
        }
        for(int i = 0; i < pwnd->macros.size(); i++)
        {
            foreach(VarPro cVar, pwnd->macros[i].vars())
            {
               varNames << cVar.varName;
            }
        }
    }
    else
    {
        foreach(VarPro cVar,vars)
        {
            varNames << cVar.varName;
        }
        foreach(VarPro cVar, pwnd->getGlobalVars())
        {
            varNames << cVar.varName;
        }
    }

    initVar = var;
    saveVar = var;
	nameLineEdit->setText(var.varName);
	dataTypeLineEdit->setCurrentIndex(var.dataType);
	addressLineEdit->setText(var.addr.sShowAddr);
    rwLineEdit->setCurrentIndex(var.RWPerm);
	lengthLineEdit->setText(QString::number(var.count));
    if(var.bOffset)
    {
        offsetAddrEdit->setText(var.offsetAddr.sShowAddr);
        groupBoxOffset->setChecked(true);
    }
}
/*********************************************************
 *��������:ʵ�ֱ����趨�Ի���,ȷ����ťִ����ر���

 ********************************************************/
void varSettingWidget::saveVarInfo(void)
{
	//�������
	//�ж������Ƿ�Ϸ�
    if (nameLineEdit->text().isEmpty())
    {
        nameLineEdit->setFocus();
        return ;
    }
    QString strLength = lengthLineEdit->text();
    if (strLength.isEmpty())
	{
		lengthLineEdit->setFocus();
        QMessageBox::warning(lengthLineEdit,tr(""),tr("������ַ�ĸ�����ΧΪ��1-1024"));
		return ;
	}
    else if(strLength.toInt() < 2 || strLength.toInt() > 1024)
    {
        int iType = dataTypeLineEdit->currentIndex();
        switch(iType)
        {
        case 5: //����boolֵ
        case 6: //����16λ����
        case 7: //����16λ������
        case 8: //����32λ����
        case 9: //����32λ������
        case 11: //����32λ������
        case 13: //����16λBCD��
        case 15: //����32λBCD��
            {
                lengthLineEdit->setFocus();
                QMessageBox::warning(lengthLineEdit,tr(""),tr("������ַ�ĸ�����ΧΪ��2-1024"));
                return ;
            }
            break;
        default:
            break;
        }
    }

	//�жϵ�ַ�����������Ƿ�Ϸ�
	int addrtype = 0;
	int datatype = dataTypeLineEdit->currentIndex();
	if (datatype == 0 || datatype == 5)
	{
		addrtype=0;
	}
	else{
		addrtype=1;
	}

	if(! pwnd->IsAddressCheckRight(addr,tr("д���ַ"),addressLineEdit,addrtype))
	{
		addressLineEdit->setFocus();
		return ;
	}

    if(groupBoxOffset->isChecked() && ! pwnd->IsAddressCheckRight(offsetAddr,tr("д���ַ"),offsetAddrEdit,1))
    {
         offsetAddrEdit->setFocus();
         return ;
    }

	saveVar.count = lengthLineEdit->text().toInt();
	if (datatype == 0 || datatype == 1 || datatype == 2 
        || datatype == 5|| datatype == 6 || datatype == 7
        || datatype == 12 || datatype == 13 || datatype == 16)
	{
		addr.Length = 1*saveVar.count;
	}
	else{
		addr.Length = 2*saveVar.count;
	}
	saveVar.addr = addr;

    saveVar.offsetAddr = offsetAddr;
	//�����������Ե�VarPro

	saveVar.varName = nameLineEdit->text();
	saveVar.dataType = dataTypeLineEdit->currentIndex();
    saveVar.RWPerm = rwLineEdit->currentIndex();

    if ((saveVar.varName != initVar.varName)
        && varNames.contains(saveVar.varName))
    {
        nameLineEdit->setFocus();
        QMessageBox::warning(nameLineEdit,tr(""),
                             QString(tr("%1 �Ѵ���")).arg(saveVar.varName));
        return ;
    }
    saveVar.bOffset = groupBoxOffset->isChecked();

    if(isMulti)//���������
    {
        int num = countSpin->value();
        saveVars << saveVar;
        if(num > 1)
        {
            saveVars.clear();
            saveVars.fill(saveVar,num);
            QVector<Keyboard> addrs = getAddrs(saveVar.addr);
            for(int i=1; i<saveVars.size(); i++)
            {
                saveVars[i].offsetAddr = offsetAddr;
                saveVars[i].addr = addrs[i];
                //qDebug()<<"before appendNumTail"<<saveVars[i].varName;
                saveVars[i].varName = appendNumTail(saveVars[i].varName,i);
                //qDebug()<<"appendNumTail"<<saveVars[i].varName;

                if (varNames.contains(saveVars[i].varName))//�����ظ�
                {
                    nameLineEdit->setFocus();
                    QMessageBox::warning(nameLineEdit,tr(""),
                                         QString(tr("%1 �Ѵ���")).arg(saveVars[i].varName));
                    return ;
                }
                saveVar.bOffset = groupBoxOffset->isChecked();
            }
        }
    }

    accept();
}

void varSettingWidget::addrInput()
{
    int addrType = 0;
	int datatype = dataTypeLineEdit->currentIndex();
	if (datatype == 0 || datatype == 5)
	{
        addrType=0;
	}
	else{
        addrType=1;
	}
	
    QString addrStr = addressLineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(addr,addrStr,addrType,this);
    if(addressintputdlg_writeaddress.exec())
    {
        addressLineEdit->setText(addr.sShowAddr);
        okButton->setFocus();
    }

}

void varSettingWidget::offsetInput()
{
    /*ƫ�Ƶ�ַֻ�����ֵ�ַ
    int addrType = 0;
        int datatype = dataTypeLineEdit->currentIndex();
        if (datatype == 0 || datatype == 5)
        {
        addrType=0;
        }
        else{
        addrType=1;
        }
     */
    int addrType = 1;
    QString addrStr = offsetAddrEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(offsetAddr,addrStr,addrType,this);
    if(addressintputdlg_writeaddress.exec())
    {
        offsetAddrEdit->setText(offsetAddr.sShowAddr);
        okButton->setFocus();
    }
}

void varSettingWidget::initMem()
{
    iDataTypeIndex = 0;
    iRWIndex =0;
    iLength = 1;
    quit = 0;

    strVarName = "";
    strDataType = dataTypeLineEdit->itemText(iDataTypeIndex);
    strDataLength = "1";
    strRW = rwLineEdit->itemText(iRWIndex);

    strAddress = "";

    lengthLineEdit->setText(strDataLength);

}

void varSettingWidget::setDataTypeIndex(int index)
{
    iDataTypeIndex = index;

	bool bSeq = false;
    switch(index)
    {
      case 0: //bit
             iLength = index;
             strDataLength = "1";
			 
             break;
      case 1: //16λ����
             iLength = index;
             strDataLength = "1";
             break;
      case 2: //16λ������
             iLength = index;
             strDataLength = "1";
             break;
	  case 3: //32λ����
		  iLength = index;
		  strDataLength = "1";
		  break;
	  case 4: //32λ������
		  iLength = index;
		  strDataLength = "1";
		  break;	  
      case 5: //����boolֵ
             iLength = index;
             strDataLength = "2";
			 bSeq = true;
             break;
      case 6: //����16λ����
             iLength = index;
             strDataLength = "2";
			 bSeq = true;
             break;
	  case 7: //����16λ������
		  iLength = index;
          strDataLength = "2";
		  bSeq = true;
		  break;
	  case 8: //����32λ����
		  iLength = index;
          strDataLength = "2";
		  bSeq = true;
		  break;
	  case 9: //����32λ������
		  iLength = index;
          strDataLength = "2";
		  bSeq = true;
		  break;
	  case 10: //32λ������
		  iLength = index;
		  strDataLength = "1";
		  
		  break;
	  case 11: //����32λ������
		  iLength = index;
          strDataLength = "2";
		  bSeq = true;
		  break;
      case 12: //16λBCD��
          iLength = index;
          strDataLength = "1";
          break;
      case 13: //����16λBCD��
          iLength = index;
          strDataLength = "2";
          bSeq = true;
          break;

      case 14: //32λBCD��
          iLength = index;
          strDataLength = "1";
          break;
      case 15: //����32λBCD��
          iLength = index;
          strDataLength = "2";
          bSeq = true;
          break;
    case 16: //�ַ���
        iLength = index;
        strDataLength = "1";
        bSeq = true;
        break;
    case 17: //�ַ���
        iLength = index;
        strDataLength = "1";
        bSeq = true;
        break;
      
    }

	lengthLineEdit->setDisabled(!bSeq);
    lengthLineEdit->setText(strDataLength);

//	if (!bSeq)//����
//	{
//		lengthLineEdit->setText(strDataLength);
//	}

}

void varSettingWidget::setRWIndex(int index)
{
   iRWIndex = index;
   strRW = rwLineEdit->itemText(iRWIndex);
}

QVector <Keyboard> varSettingWidget::getAddrs(Keyboard kb)
{
    QVector <Keyboard> Vaddrs;
    Vaddrs << kb;

    int count = countSpin->value();
    int nIntervl = 1;
    int length = lengthLineEdit->text().toInt();

    int dataType = this->dataTypeLineEdit->currentIndex();

    switch(dataType)
    {
    case 3:
    case 4:
    case 8:
    case 9:
    case 10:
    case 11:
    case 14:
    case 15:
        nIntervl = 2;
        break;
    case 16:
        nIntervl = length;
        break;
    case 17:
        nIntervl = length *2;
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


void varSettingWidget::noSaveRecord()
{
   quit = 1;
   close();
}
/**********************************************
*����:ʵ�ֱ����趨�������Ƹı�ʱ���±����趨
*     �������Ķ�Ӧ����������
*����˵��:int index ,QString strConName
*       int index:Ϊ���ӵ�ID����Ӧ�ڼ������ӣ�
*QString strConName ��Ӧindex��������
*********************************************/
int varSettingWidget::updateVarSettingConTable(int index, QString strConName)
{

    return 0;
}


/************************************************************************
 
  *************************************************************************/
QString varSettingWidget::GetPLCStation(int index)
{
	return QString("");
}

QString varSettingWidget::appendNumTail(QString varName,int index)
{

    if(index == 0)
    {
        return varName;
    }
    QString sVarName,leftRef,rightRef;
    int i = 0;
    int size = varName.size();
    for(i=0; i<size; i++)
    {
        //qDebug() <<"varName " << size-i-1 <<":"<< varName[size-i-1];
        if(varName[size-i-1] <= '0' || varName[size-i-1] >= '9')
        {
            //qDebug() << "varName is not digit";
            break;
        }
    }
    rightRef = varName.right(i);
    leftRef = varName.left(size-i);
    //qDebug() << "leftRef"<<leftRef;
    //qDebug() << "rightRef"<<rightRef;
    return leftRef+QString::number(rightRef.toInt()+index);
}
void varSettingWidget::groupBoxOffsetChanged(bool is_checked)
{
    if(!is_checked)
    {
        //offsetAddr = Keyboard(); //����
        saveVar.bOffset = false;
    }
}
