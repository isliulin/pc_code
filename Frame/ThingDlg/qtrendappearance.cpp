#include "qtrendappearance.h"
#include "ui_qtrendappearance.h"
#include <math.h>

extern MainWindow *pwnd;

QTrendAppearance::QTrendAppearance(QWidget *parent):QWidget(parent),ui(new Ui::QTrendAppearance)
{
    ui->setupUi(this);

	setDefaultChl();
    ui->groupBox_tabType->setEnabled(false);

    //ͨ������
    ui->lineEdit_pipeCount->setEnabled(false);
    ui->lineEdit_pipeCount->setText("1");

    //���~~~
    for(int i = 1; i <= pwnd->m_pSamSysParame->m_loadDataSampling.size(); i++)
    {
        ui->comboBox_groupNum->addItem(pwnd->m_pSamSysParame->m_vecDataSamplingStr[i - 1]);
    }

	
	
    //��������
    connect(ui->comboBox_channelNum,SIGNAL(currentIndexChanged(QString )),this,SLOT(channelIndexChanged(QString )));
    connect(ui->comboBox_showCondition,SIGNAL(currentIndexChanged(int )),this,SLOT(conditionChanged(int)));
    connect(ui->lineEdit_showAddr,SIGNAL(editingFinished( )),this,SLOT(setCurrentChl()));
    connect(ui->comboBox_lineStyle,SIGNAL(currentIndexChanged(QString )),this,SLOT(setCurrentChl()));
    connect(ui->spinBox_lineWidth,SIGNAL(valueChanged(int )),this,SLOT(setCurrentChl()));
    connect(ui->pushButton_showColor,SIGNAL(clicked( )),this,SLOT(btncolorClicked()));
    connect(ui->pushButton_showAddr,SIGNAL(clicked( )),this,SLOT(btnAddrClicked()));
    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(setAllChl(bool)));

    //�������ֵ������
    ui->doubleSpinBox_outputMin->setValue(0.00);
    ui->doubleSpinBox_outputMax->setValue(100.00);
	ui->comboBox_showCondition->addItem(tr("������ʾ"));
	ui->comboBox_showCondition->addItem(tr("λONʱ��ʾ"));
	ui->comboBox_showCondition->addItem(tr("λOFFʱ��ʾ"));
        ui->label_showAddr->setEnabled(false);
        ui->lineEdit_showAddr->setEnabled(false);
        ui->pushButton_showAddr->setEnabled(false);
    ui->pushButton_showColor->setStyleSheet(QString("background:%1").arg("192,192,192"));
}

QTrendAppearance::~QTrendAppearance()
{
    delete ui;
}

void QTrendAppearance::on_pushButton_pipeSet_clicked()//ͨ������
{
    int temp        = ui->lineEdit_pipeCount->text().toInt();
    int curGroup    = ui->comboBox_groupNum->currentIndex();

    if(curGroup < 0)
    {
        return ;
    }
    QTrendaChSet chanSet(m_channels, curGroup);
    if(chanSet.exec() == QDialog::Accepted)
    {
        m_channels = chanSet.m_Channels;
		initChannelPro();//��ʼ��ͨ������UI
        //m_vecChannelGroups.clear();
        QVector<ChannelGroupInfo> newChannels;

		foreach (int chlNumber,m_channels)
		{
			ChannelGroupInfo chlPro = m_defaultChl;
			chlPro.m_nNumOfChannel = chlNumber;
            foreach(ChannelGroupInfo chlInfo,m_vecChannelGroups)
            {
                if(chlInfo.m_nNumOfChannel == chlNumber)
                {
                    chlPro = chlInfo;
                    break;
                }
            }
            newChannels.push_back(chlPro);
		}
        m_vecChannelGroups.clear();
        m_vecChannelGroups = newChannels;

		ui->comboBox_channelNum->clear();
		foreach(int chlNumber,m_channels)
		{
			ui->comboBox_channelNum->addItem(QString::number(chlNumber));
		}
        m_nTotalTrendNumber = m_vecChannelGroups.size();
		ui->lineEdit_pipeCount->setText(QString::number(m_vecChannelGroups.size()));
    }
}

void QTrendAppearance::on_comboBox_dataType_currentIndexChanged(int index)//��������
{
    
}

void QTrendAppearance::on_doubleSpinBox_inputMin_valueChanged(double value)//���뷶Χ����С
{
    
}

void QTrendAppearance::on_doubleSpinBox_inputMax_valueChanged(double value)//���뷶Χ�����
{
    
}

void QTrendAppearance::Init(QTrendAttr *pItem)
{
    if(pItem)
    {
        m_sGroupNum         = pItem->m_sGroupNum;    //����

        m_bIsAll        = pItem->m_bIsAll;
        int num = pwnd->m_pSamSysParame->m_loadDataSampling.size();
        for(int i = 0 ; i < num; i++)
        {
            if(m_sGroupNum == pwnd->m_pSamSysParame->m_vecDataSamplingStr[i])
            {
                if(1 == pwnd->m_pSamSysParame->m_loadDataSampling[0].nDataSampType)//ʵʱ����
                {
                    m_eTableType    = TypeRealTime;  //ͼ������
                }
                else
                {
                    m_eTableType    = TypeHistory;  //ͼ������
                }

                break;
            }
        }

		int num0 = pwnd->m_pSamSysParame->m_loadDataSampling.size();
		for(int i = 0; i < num0; i++)
		{
			if(pwnd->m_pSamSysParame->m_vecDataSamplingStr[i] == m_sGroupNum)
			{
				ui->comboBox_groupNum->setCurrentIndex(i);//���
			}
		}
        //
		m_vecChannelGroups = pItem->m_vecChannelGroups;
		//m_channels = pItem->m_Channels;
        m_nTotalTrendNumber = m_vecChannelGroups.size(); //ͨ������

        
		ui->doubleSpinBox_outputMin->setValue(pItem->m_nDisplayMin);
		ui->doubleSpinBox_outputMax->setValue(pItem->m_nDisplayMax);
    }
    else
    {
        m_bIsAll        = true;         //����ȫ��
        m_sGroupNum     = pwnd->m_pSamSysParame->m_vecDataSamplingStr[0];//����
        if(1 == pwnd->m_pSamSysParame->m_loadDataSampling[0].nDataSampType)//ʵʱ����
        {
            m_eTableType    = TypeRealTime;  //ͼ������
        }
        else
        {
            m_eTableType    = TypeHistory;  //ͼ������
        }
        m_nTotalTrendNumber = 1;//��������
        

        ui->doubleSpinBox_outputMin->setValue(0.00);
        ui->doubleSpinBox_outputMax->setValue(100.00);
    }

    

    if(m_eTableType == TypeHistory)//����ѡ�е�����ʷ����ͼ
    {
        emit TrendTypeChange(true);//������Ϣ
    }
    else//����ѡ�е���ʵʱ����ͼ
    {
        emit TrendTypeChange(false);//������Ϣ
    }

    ///////////////////////ui//////////////////////////////
    if(m_eTableType == TypeRealTime)
    {
        ui->radioButton_realTime->setChecked(true);
        ui->radioButton_history->setChecked(false);
    }
    else
    {
        ui->radioButton_realTime->setChecked(false);
        ui->radioButton_history->setChecked(true);
    }

    

    

	ui->comboBox_channelNum->clear();
	m_channels.clear();
	foreach(ChannelGroupInfo curChl,m_vecChannelGroups)
	{
		int chlNumber = curChl.m_nNumOfChannel;
		m_channels << chlNumber;
		ui->comboBox_channelNum->addItem(QString::number(chlNumber));
	}
    m_nTotalTrendNumber = m_vecChannelGroups.size();
	ui->lineEdit_pipeCount->setText(QString::number(m_channels.size()));//ͨ����
	if (ui->comboBox_channelNum->count()>0)
	{
		ui->comboBox_channelNum->setCurrentIndex(0);
	}
	
    if(m_bIsAll)
    {
		ui->checkBox->setCheckState(Qt::Checked);
        ui->comboBox_channelNum->setDisabled(true);
    }
	else{
		ui->checkBox->setCheckState(Qt::Unchecked);
		ui->comboBox_channelNum->setDisabled(false);
	}
}

void QTrendAppearance::on_comboBox_groupNum_currentIndexChanged(int index)//���,
{
    //m_nGroupNum = index + 1;
	m_channels.clear();
    m_sGroupNum = ui->comboBox_groupNum->currentText();

	QVector<DATA_ADDRESS_ITEM> samples = pwnd->m_pSamSysParame->m_loadDataSampling[index].m_dataTable;
	m_vecChannelGroups.clear();
    for (int i=0;i<samples.size();i++)
	{
        if(i >= 16)
        {
            break;
        }
		ChannelGroupInfo chlPro = m_defaultChl;
		chlPro.m_nNumOfChannel = samples[i].nAddrNumber;
		m_vecChannelGroups.push_back(chlPro);
		m_channels << chlPro.m_nNumOfChannel;
	}

	m_nTotalTrendNumber = m_channels.size();
	ui->lineEdit_pipeCount->setText(QString::number(m_channels.size()));//ͨ����
    ui->comboBox_channelNum->clear();
    foreach(int chlNumber,m_channels)
    {
        ui->comboBox_channelNum->addItem(QString::number(chlNumber));
    }
    if(pwnd->m_pSamSysParame->m_loadDataSampling[index].nDataSampType == 1)
    {
        m_eTableType = TypeRealTime;
        ui->radioButton_history->setChecked(false);
        ui->radioButton_realTime->setChecked(true);
        emit TrendTypeChange(false);//������Ϣ
    }
    else
    {
        m_eTableType = TypeHistory;
        ui->radioButton_history->setChecked(true);
        ui->radioButton_realTime->setChecked(false);
        emit TrendTypeChange(true);//������Ϣ
    }
}



void QTrendAppearance::on_radioButton_all_clicked()//ȫ��
{
    
}

void QTrendAppearance::on_radioButton_single_clicked()//����
{
}

void QTrendAppearance::on_doubleSpinBox_outputMin_valueChanged(double value)//��ʾ��Χ����С
{
     m_nDisplayMax = ui->doubleSpinBox_outputMax->text().toDouble();
}

void QTrendAppearance::on_doubleSpinBox_outputMax_valueChanged(double value)//��ʾ��Χ�����
{
    m_nDisplayMin = ui->doubleSpinBox_outputMin->text().toDouble();

}
double QTrendAppearance::getDisplayMax()
{
	return ui->doubleSpinBox_outputMax->value();
}
double QTrendAppearance::getDisplayMin()
{
	return ui->doubleSpinBox_outputMin->value();
}

void QTrendAppearance::initChannelPro()
{
	
	ui->comboBox_showCondition->setCurrentIndex(0);
	ui->lineEdit_showAddr->setText("LB0");
	ui->comboBox_lineStyle->setCurrentIndex(0);
	ui->spinBox_lineWidth->setValue(1);
	ui->pushButton_showColor->setStyleSheet(QString("background:%1").arg("192,192,192"));
}

void QTrendAppearance::setDefaultChl()
{
	m_defaultChl.m_nNumOfChannel = 0;
	m_defaultChl.eLineType = LineSolid;
	m_defaultChl.nLineThickness = 1;
	m_defaultChl.eDisplayCondition = DisplayKeep;
	m_defaultChl.nDisplayColor = QColor(192,192,192);

}

void QTrendAppearance::setCurrentChl()
{	
	if (ui->comboBox_channelNum->currentText().isEmpty())
	{
		return;
	}
	ChannelGroupInfo chl;
        chl.m_nNumOfChannel = ui->comboBox_channelNum->currentText().toInt();
	chl.eLineType = (LineStyleType)(ui->comboBox_lineStyle->currentIndex()+1);
	chl.nLineThickness = ui->spinBox_lineWidth->value();
	chl.eDisplayCondition = (DisConType)(ui->comboBox_showCondition->currentIndex()+1);
	
    chl.nDisplayColor = ui->pushButton_showColor->palette().background().color();//����ɫ;
    /*add by wxy ����ַ���ŵ������ʱ��ȥ���������ַ������Ϣѭ����ʾ��
	if (chl.eDisplayCondition != DisplayKeep 
		&& !pwnd->IsAddressCheckRight(chl.KeyAddr,tr("��ʾ������ַ"),ui->lineEdit_showAddr,0))
    {
            ui->lineEdit_showAddr->setFocus();
            return;
    }
    */
    int Addr_Type = 0;
    pwnd->CheckString(chl.KeyAddr,ui->lineEdit_showAddr->text(),Addr_Type);
    chl.KeyAddr.nAddrType = Addr_Type; //��¼��λ��ʾ
	for (int i=0; i<m_vecChannelGroups.size(); i++)
	{
            if(m_bIsAll)
            {
                ChannelGroupInfo curChl = m_vecChannelGroups[i];
                chl.m_nNumOfChannel = curChl.m_nNumOfChannel;
                m_vecChannelGroups.replace(i,chl);
            }
            else
            {
                ChannelGroupInfo curChl = m_vecChannelGroups[i];
                if (curChl.m_nNumOfChannel == chl.m_nNumOfChannel)
                {
                    m_vecChannelGroups.replace(i,chl);
                    break;
                }
            }
	}
}

void QTrendAppearance::btncolorClicked()
{
        ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
        pwnd->OnAddColorDlg(ui->pushButton_showColor,colorPicker);
        connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBtnColor(const QColor &)));

}

void QTrendAppearance::setBtnColor(const QColor &color)
{
        ui->pushButton_showColor->setStyleSheet(QString("background:%1").arg(color.name()));
        //cc = color;
        setCurrentChl();
}

void QTrendAppearance::channelIndexChanged(QString sNumber)
{
	if (ui->comboBox_channelNum->currentText().isEmpty())
	{
		return;
	}
	int chlNumber = ui->comboBox_channelNum->currentText().toInt();
	for (int i=0; i<m_vecChannelGroups.size(); i++)
	{
		ChannelGroupInfo curChl = m_vecChannelGroups[i];
		if (curChl.m_nNumOfChannel == chlNumber)
		{
			ui->comboBox_showCondition->setCurrentIndex(curChl.eDisplayCondition -1);
			
			ui->lineEdit_showAddr->setText(curChl.KeyAddr.sShowAddr);
			ui->comboBox_lineStyle->setCurrentIndex(curChl.eLineType-1);
			ui->spinBox_lineWidth->setValue(curChl.nLineThickness);
			ui->pushButton_showColor->setStyleSheet(QString("background:%1").arg(curChl.nDisplayColor.name()));
                        setBtnColor(curChl.nDisplayColor);
                        conditionChanged(curChl.eDisplayCondition -1);
			break;
		}
	}
	
}

void QTrendAppearance::btnAddrClicked()
{    
    QString str = ui->lineEdit_showAddr->text();
    Keyboard ctlAddr;
    AddressInputDialog dlg_readaddress(ctlAddr,str,0,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_showAddr->setText(ctlAddr.sShowAddr);
        setCurrentChl();
    }
}

void QTrendAppearance::conditionChanged(int index)
{
	bool bValue = false;
    if(m_vecChannelGroups.size() < 1)
    {
        return ;
    }
	if (index != 0)
	{
            bValue = true;
            //int chNum = ui->comboBox_channelNum->currentText().toInt();
            int chNum = ui->comboBox_channelNum->currentIndex();
            ChannelGroupInfo curCh = m_vecChannelGroups[chNum];
            if(curCh.KeyAddr.sShowAddr == "")
            {
                ui->lineEdit_showAddr->setText("LB0");
            }
            else
            {
                ui->lineEdit_showAddr->setText(curCh.KeyAddr.sShowAddr);
            }
	}
        ui->lineEdit_showAddr->setEnabled(bValue);
        ui->label_showAddr->setEnabled(bValue);
        ui->pushButton_showAddr->setEnabled(bValue);
	
	setCurrentChl();
}

void QTrendAppearance::setAllChl(bool checked)
{
    m_bIsAll = checked;
    ui->comboBox_channelNum->setDisabled(checked);
    if(checked)
    {
        for (int i=0; i<m_vecChannelGroups.size(); i++)
        {
            //m_vecChannelGroups[i].m_nNumOfChannel = ui->comboBox_channelNum->currentText().toInt();
            m_vecChannelGroups[i].eLineType = (LineStyleType)(ui->comboBox_lineStyle->currentIndex()+1);
            m_vecChannelGroups[i].nLineThickness = ui->spinBox_lineWidth->value();
            m_vecChannelGroups[i].eDisplayCondition = (DisConType)(ui->comboBox_showCondition->currentIndex()+1);


            m_vecChannelGroups[i].nDisplayColor = ui->pushButton_showColor->palette().background().color();//����ɫ;
            if (m_vecChannelGroups[i].eDisplayCondition != DisplayKeep
                && !pwnd->IsAddressCheckRight(m_vecChannelGroups[i].KeyAddr,tr("��ʾ������ַ"),ui->lineEdit_showAddr,0))
            {
                ui->lineEdit_showAddr->setFocus();
                break;
            }
        }
    }
}

bool QTrendAppearance::save()
{
    for (int i=0; i<m_vecChannelGroups.size(); i++)
    {
        ChannelGroupInfo curChl = m_vecChannelGroups[i];
        if(curChl.eDisplayCondition != DisplayKeep
           && !pwnd->IsAddressCheckRight(curChl.KeyAddr,tr("��ʾ������ַ"),ui->lineEdit_showAddr,0))
        {
            ui->lineEdit_showAddr->setFocus();
            return false;
        }
    }
    return true;
}

