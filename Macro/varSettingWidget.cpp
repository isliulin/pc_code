
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

    varNameLabel = new QLabel(tr("变量名称:"));
    nameLineEdit = new QLineEdit;
    varNameLabel->setBuddy(nameLineEdit);

    QRegExp regExp("[A-Za-z_][0-9a-zA-Z_]{1,20}");

    QValidator *validator = new QRegExpValidator(regExp,this);
    nameLineEdit->setValidator(validator);
    nameLineEdit->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));

    dataTypeLabel = new QLabel(tr("数据类别:"));
    dataTypeLineEdit = new QComboBox;
    dataTypeLabel->setBuddy(dataTypeLineEdit);
    dataTypeLineEdit->addItem(tr("bool值"));
    dataTypeLineEdit->addItem(tr("16位整数"));
	dataTypeLineEdit->addItem(tr("16位正整数"));
    dataTypeLineEdit->addItem(tr("32位整数"));
	dataTypeLineEdit->addItem(tr("32位正整数"));
	dataTypeLineEdit->addItem(tr("批量bool值"));
    dataTypeLineEdit->addItem(tr("批量16位整数"));
	dataTypeLineEdit->addItem(tr("批量16位正整数"));
    dataTypeLineEdit->addItem(tr("批量32位整数"));
	dataTypeLineEdit->addItem(tr("批量32位正整数"));
    dataTypeLineEdit->addItem(tr("32位浮点数"));
    dataTypeLineEdit->addItem(tr("批量32位浮点数"));
    dataTypeLineEdit->addItem(tr("16位BCD码"));
    dataTypeLineEdit->addItem(tr("批量16位BCD码"));
    dataTypeLineEdit->addItem(tr("32位BCD码"));
    dataTypeLineEdit->addItem(tr("批量32位BCD码"));
    dataTypeLineEdit->addItem(tr("ASCII字符串"));
    dataTypeLineEdit->addItem(tr("UNICODE字符串"));
    connect(dataTypeLineEdit,SIGNAL(currentIndexChanged(int)),this,SLOT(setDataTypeIndex(int)));

    lengthLabel = new QLabel(tr("长    度:"));
    lengthLineEdit = new QLineEdit;
    lengthLabel->setBuddy(lengthLineEdit);
    lengthLineEdit->setEnabled(false);
    QIntValidator *intValidator = new QIntValidator(2,1024,this);
	lengthLineEdit->setValidator(intValidator);

    rwLabel = new QLabel(tr("读 /  写:"));
    rwLineEdit = new QComboBox;
    rwLabel->setBuddy(rwLineEdit);
    rwLineEdit->addItem(tr("读"));
    rwLineEdit->addItem(tr("写"));
    rwLineEdit->addItem(tr("读写"));
    rwLineEdit->setCurrentIndex(2);
    connect(rwLineEdit,SIGNAL(currentIndexChanged(int)),this,SLOT(setRWIndex(int)));

    addressLabel = new QLabel(tr("地    址:"),this);
    addressLineEdit = new QLineEdit(this);
    addressLabel->setBuddy(addressLineEdit);

    offsetAddrLabel = new QLabel(tr("偏移地址:"), this);
    offsetAddrEdit = new QLineEdit(this);
    offsetAddrLabel->setBuddy(offsetAddrEdit);

    countLabel = new QLabel(tr("个数:"));
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

    okButton = new QPushButton(tr("确定"));
    cancelButton = new QPushButton(tr("取消"));

    groupBoxOffset = new QGroupBox(tr("偏移地址"), this);
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


    //偏移地址
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

    setWindowTitle(tr("变量设定"));
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
 *函数功能:实现变量设定对话框,确定按钮执行相关保存

 ********************************************************/
void varSettingWidget::saveVarInfo(void)
{
	//检查输入
	//判断名称是否合法
    if (nameLineEdit->text().isEmpty())
    {
        nameLineEdit->setFocus();
        return ;
    }
    QString strLength = lengthLineEdit->text();
    if (strLength.isEmpty())
	{
		lengthLineEdit->setFocus();
        QMessageBox::warning(lengthLineEdit,tr(""),tr("批量地址的个数范围为：1-1024"));
		return ;
	}
    else if(strLength.toInt() < 2 || strLength.toInt() > 1024)
    {
        int iType = dataTypeLineEdit->currentIndex();
        switch(iType)
        {
        case 5: //批量bool值
        case 6: //批量16位整数
        case 7: //批量16位正整数
        case 8: //批量32位整数
        case 9: //批量32位正整数
        case 11: //批量32位浮点数
        case 13: //批量16位BCD码
        case 15: //批量32位BCD码
            {
                lengthLineEdit->setFocus();
                QMessageBox::warning(lengthLineEdit,tr(""),tr("批量地址的个数范围为：2-1024"));
                return ;
            }
            break;
        default:
            break;
        }
    }

	//判断地址和数据类型是否合法
	int addrtype = 0;
	int datatype = dataTypeLineEdit->currentIndex();
	if (datatype == 0 || datatype == 5)
	{
		addrtype=0;
	}
	else{
		addrtype=1;
	}

	if(! pwnd->IsAddressCheckRight(addr,tr("写入地址"),addressLineEdit,addrtype))
	{
		addressLineEdit->setFocus();
		return ;
	}

    if(groupBoxOffset->isChecked() && ! pwnd->IsAddressCheckRight(offsetAddr,tr("写入地址"),offsetAddrEdit,1))
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
	//保存所有属性到VarPro

	saveVar.varName = nameLineEdit->text();
	saveVar.dataType = dataTypeLineEdit->currentIndex();
    saveVar.RWPerm = rwLineEdit->currentIndex();

    if ((saveVar.varName != initVar.varName)
        && varNames.contains(saveVar.varName))
    {
        nameLineEdit->setFocus();
        QMessageBox::warning(nameLineEdit,tr(""),
                             QString(tr("%1 已存在")).arg(saveVar.varName));
        return ;
    }
    saveVar.bOffset = groupBoxOffset->isChecked();

    if(isMulti)//建多个变量
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

                if (varNames.contains(saveVars[i].varName))//名字重复
                {
                    nameLineEdit->setFocus();
                    QMessageBox::warning(nameLineEdit,tr(""),
                                         QString(tr("%1 已存在")).arg(saveVars[i].varName));
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
    /*偏移地址只能是字地址
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
      case 1: //16位整数
             iLength = index;
             strDataLength = "1";
             break;
      case 2: //16位正整数
             iLength = index;
             strDataLength = "1";
             break;
	  case 3: //32位整数
		  iLength = index;
		  strDataLength = "1";
		  break;
	  case 4: //32位正整数
		  iLength = index;
		  strDataLength = "1";
		  break;	  
      case 5: //批量bool值
             iLength = index;
             strDataLength = "2";
			 bSeq = true;
             break;
      case 6: //批量16位整数
             iLength = index;
             strDataLength = "2";
			 bSeq = true;
             break;
	  case 7: //批量16位正整数
		  iLength = index;
          strDataLength = "2";
		  bSeq = true;
		  break;
	  case 8: //批量32位整数
		  iLength = index;
          strDataLength = "2";
		  bSeq = true;
		  break;
	  case 9: //批量32位正整数
		  iLength = index;
          strDataLength = "2";
		  bSeq = true;
		  break;
	  case 10: //32位浮点数
		  iLength = index;
		  strDataLength = "1";
		  
		  break;
	  case 11: //批量32位浮点数
		  iLength = index;
          strDataLength = "2";
		  bSeq = true;
		  break;
      case 12: //16位BCD码
          iLength = index;
          strDataLength = "1";
          break;
      case 13: //批量16位BCD码
          iLength = index;
          strDataLength = "2";
          bSeq = true;
          break;

      case 14: //32位BCD码
          iLength = index;
          strDataLength = "1";
          break;
      case 15: //批量32位BCD码
          iLength = index;
          strDataLength = "2";
          bSeq = true;
          break;
    case 16: //字符串
        iLength = index;
        strDataLength = "1";
        bSeq = true;
        break;
    case 17: //字符串
        iLength = index;
        strDataLength = "1";
        bSeq = true;
        break;
      
    }

	lengthLineEdit->setDisabled(!bSeq);
    lengthLineEdit->setText(strDataLength);

//	if (!bSeq)//批量
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
*功能:实现变量设定连接名称改变时更新变量设定
*     各变量的对应的连接名称
*参数说明:int index ,QString strConName
*       int index:为连接的ID（对应第几个连接）
*QString strConName 对应index的连接名
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
        //offsetAddr = Keyboard(); //置零
        saveVar.bOffset = false;
    }
}
