#include "qtrendbtable.h"
#include "ui_qtrendbtable.h"
#include <math.h>
#include "Frame/mainwindow.h"
#include "qtrendbgset.h"

extern MainWindow *pwnd;

QTrendbTable::QTrendbTable(QWidget *parent):QWidget(parent),ui(new Ui::QTrendbTable)
{
    ui->setupUi(this);

	setDefaultChl();
    //�������༭��
    ui->lineEdit_pipeCount->setEnabled(false);
    //ui->lineEdit_pipeCount->setText("1");

    //������
    vecGroupNum.clear();
    int total = pwnd->m_pSamSysParame->m_loadDataSampling.size();
    for(int i = 0; i < total; i++)
    {
        if(pwnd->m_pSamSysParame->m_loadDataSampling[i].nDataSampType == 1)//ʵʱ����
        {
            vecGroupNum.push_back(i);
        }
    }
    //ui->lineEdit_pipeCount->setText(QString::number(vecGroupNum.size()));


    //�������ֵ������
    ui->doubleSpinBox_outputMin->setValue(0.00);
    ui->doubleSpinBox_outputMax->setValue(100.00);

    //��ʾ����
    ui->comboBox_showCondition->addItem(tr("������ʾ"));
    ui->comboBox_showCondition->addItem(tr("λONʱ��ʾ"));
    ui->comboBox_showCondition->addItem(tr("λOFFʱ��ʾ"));
    //��������
    connect(ui->comboBox_pipeNum,SIGNAL(currentIndexChanged(QString )),this,SLOT(channelIndexChanged(QString )));
    connect(ui->comboBox_showCondition,SIGNAL(currentIndexChanged(int )),this,SLOT(conditionChanged(int)));

    connect(ui->comboBox_lineStyle,SIGNAL(currentIndexChanged(QString )),this,SLOT(setCurrentChl()));
    connect(ui->spinBox_lineWidth,SIGNAL(valueChanged(int )),this,SLOT(setCurrentChl()));
    connect(ui->pushButton_showColor,SIGNAL(clicked( )),this,SLOT(btncolorClicked()));
    connect(ui->pushButton_ctlAddr,SIGNAL(clicked( )),this,SLOT(btnAddrClicked()));
    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(setAllChl(bool)));


    ui->comboBox_showCondition->setCurrentIndex(0);



}

QTrendbTable::~QTrendbTable()
{
    delete ui;
}

void QTrendbTable::on_comboBox_dataType_currentIndexChanged(int index)//��������
{

}

void QTrendbTable::on_doubleSpinBox_inputMin_valueChanged(double value)//Դ��Χ:��С
{

}

void QTrendbTable::on_doubleSpinBox_inputMax_valueChanged(double value)//Դ��Χ:���
{

}

void QTrendbTable::Init(QTrendDataGroupAttr *pItem)
{
    int num = vecGroupNum.size();

    if(pItem)
    {
        m_bIsAll            = pItem->m_bIsAll;              //����ȫ��
        m_sCurChnnel        = pItem->m_sCurChnnel;          //��ǰ����,������������е�����
        m_sChnnelBegin      = pItem->m_sChnnelBegin;        //��ʼ����
        m_nTotalTrendNumber = pItem->m_nTotalTrendNumber;   //����������
        m_selGroups         = pItem->m_selGroups;
        

        m_vecChannelGroups.clear();
        m_vecDisplayGroups.clear();

		m_vecChannelGroups = pItem->m_vecChannelGroups;
		ui->doubleSpinBox_outputMin->setValue(pItem->m_nDisplayMin);
		ui->doubleSpinBox_outputMax->setValue(pItem->m_nDisplayMax);
        
    }
    else
    {      
        m_bIsAll            = true;                         //����ȫ��
		if (vecGroupNum.size() >0)
		{
			m_sCurChnnel   = pwnd->m_pSamSysParame->m_vecDataSamplingStr[vecGroupNum[0]];//��ǰ����
			m_sChnnelBegin = pwnd->m_pSamSysParame->m_vecDataSamplingStr[vecGroupNum[0]];//��ʼ���
		}
		else
		{
			m_sCurChnnel = "";
			m_sChnnelBegin = "";
		}
       
        m_selGroups.append( m_sCurChnnel);
        m_nTotalTrendNumber = 1;                            //����������
        m_vecChannelGroups.clear();
        m_vecDisplayGroups.clear();


        ChannelGroupInfo info;
		info = m_defaultChl;
		info.m_sGroupName = m_sCurChnnel;
		m_vecChannelGroups.append(info);
        
    }

    //��ǰ���
    ui->comboBox_pipeNum->clear();
    for(int i = 0; i < m_selGroups.size(); i++)
    {
        ui->comboBox_pipeNum->addItem(m_selGroups.at(i));
    }
    ui->comboBox_pipeNum->setCurrentIndex(0);//��ǰͨ����

    ui->lineEdit_pipeCount->setText(QString::number(m_selGroups.size()));

	if(m_bIsAll)
	{
		ui->checkBox->setCheckState(Qt::Checked);
		ui->comboBox_pipeNum->setDisabled(true);
	}
	else{
		ui->checkBox->setCheckState(Qt::Unchecked);
		ui->comboBox_pipeNum->setDisabled(false);
	}

    int temp = 1;

	if (m_vecChannelGroups.size()>0)
	{
		temp = m_vecChannelGroups.first().eDisplayCondition;
	}
    ui->comboBox_showCondition->setCurrentIndex(temp - 1);
    if(1 == temp)
    {
        ui->lineEdit_ctlAddr->setEnabled(false);
        ui->label_showAddr->setEnabled(false);
        ui->pushButton_ctlAddr->setEnabled(false);
    }
    else
    {
        ui->lineEdit_ctlAddr->setEnabled(true);
        ui->label_showAddr->setEnabled(true);
        ui->pushButton_ctlAddr->setEnabled(true);
    }

    connect(ui->lineEdit_ctlAddr,SIGNAL(editingFinished( )),this,SLOT(setCurrentChl()));
}



void QTrendbTable::on_radioButton_all_clicked()//ȫ��
{

}

void QTrendbTable::on_radioButton_single_clicked()//����
{
}

void QTrendbTable::on_pushButton_groupSet_clicked()
{
    QTrendbgSet groupSet(m_selGroups,this);
    if(groupSet.exec() == QDialog::Accepted)
    {
        m_selGroups = groupSet.vecGroup;
        initChannelPro();//��ʼ��ͨ������UI
        //m_vecChannelGroups.clear();
        QVector<ChannelGroupInfo> newChannels;

        ui->comboBox_pipeNum->clear();
        foreach (QString groupName,m_selGroups)
        {
            ChannelGroupInfo chlPro = m_defaultChl;
            chlPro.m_sGroupName = groupName;
            foreach(ChannelGroupInfo chlInfo,m_vecChannelGroups)
            {
                if(chlInfo.m_sGroupName == chlPro.m_sGroupName)
                {
                    chlPro = chlInfo;
                    break;
                }
            }
            newChannels.push_back(chlPro);
            ui->comboBox_pipeNum->addItem(groupName);
        }
        m_vecChannelGroups.clear();
        m_vecChannelGroups = newChannels;
        ui->lineEdit_pipeCount->setText(QString::number(m_vecChannelGroups.size()));
        channelIndexChanged("");
    }
    /*
    int temp0 = ui->lineEdit_pipeCount->text().toInt();

    QTrendbgSet groupSet(vecGroupNum, temp0, begin);
    if(groupSet.exec() == QDialog::Accepted)
    {
        if(m_nTotalTrendNumber != groupSet.m_nGroupNum)
        {
            //-------------------------------------------------------
            m_nTotalTrendNumber = groupSet.m_nGroupNum;     //�ı�������ͨ����

            begin = groupSet.m_nGroupBegin;//��ʼͨ����
            m_sChnnelBegin = pwnd->m_pSamSysParame->m_vecDataSamplingStr[vecGroupNum[begin - 1]];

            ui->lineEdit_pipeCount->setText(QString::number(m_nTotalTrendNumber));

            //int num = ui->lineEdit_pipeCount->text().toInt();
            ui->comboBox_pipeNum->clear();
            for(int i = 0; i < m_nTotalTrendNumber; i++)
            {
                ui->comboBox_pipeNum->addItem(pwnd->m_pSamSysParame->m_vecDataSamplingStr[vecGroupNum[begin + i - 1]]);
            }

            int temp = 0;
            int size = 0;
            ChannelGroupInfo info;
            DisplayGroupInfo info1;
            size = m_vecChannelGroups.size();
            if(m_vecChannelGroups.size() < m_nTotalTrendNumber)//��Ҫ����m_vecChannelGroups��
            {
                temp = m_nTotalTrendNumber - m_vecChannelGroups.size();
                if(temp > 0 && m_bIsAll)//����Ϊ����ѡ��ȫ����ʱ��
                {
                    for(int i = 0; i < temp; i++)
                    {
                        info.m_eDataType    = m_vecChannelGroups.at(0).m_eDataType;     //��������
                        info.m_nNumOfChannel= vecGroupNum[begin + i];  //���
                        info.m_nSourceMin   = m_vecChannelGroups.at(0).m_nSourceMin;    //���뷶Χ��Сֵ
                        info.m_nSourceMax   = m_vecChannelGroups.at(0).m_nSourceMax;    //���뷶Χ���ֵ
                        info.m_nDisplayMin  = m_vecChannelGroups.at(0).m_nDisplayMin;   //��ʾ������Сֵ
                        info.m_nDisplayMax  = m_vecChannelGroups.at(0).m_nDisplayMax;   //��ʾ�������ֵ
                        m_vecChannelGroups.push_back(info);

                        info1.eDisplayCondition = m_vecDisplayGroups.at(0).eDisplayCondition;//��ʾ����
                        info1.KeyAddr           = m_vecDisplayGroups.at(0).KeyAddr;     //��ĵ�ַ
                        info1.nDisplayNum       = vecGroupNum[begin + i];                             //���
                        m_vecDisplayGroups.push_back(info1);
                    }
                }
                else
                {
                    for(int i = 0; i < temp; i++)
                    {
                        info.m_eDataType    = Curve16Bin;   //��������
                        info.m_nNumOfChannel= vecGroupNum[begin + i];     //ͨ����
                        info.m_nSourceMin   = 0;            //���뷶Χ��Сֵ
                        info.m_nSourceMax   = 65535;        //���뷶Χ���ֵ
                        info.m_nDisplayMin  = 0;            //��ʾ������Сֵ
                        info.m_nDisplayMax  = 100;          //��ʾ�������ֵ
                        m_vecChannelGroups.push_back(info);

                        info1.eDisplayCondition = DisplayKeep;//��ʾ����
                        info1.nDisplayNum       = vecGroupNum[begin + i];
                        m_vecDisplayGroups.push_back(info1);
                    }
                }
            }
            else if(m_vecChannelGroups.size() > m_nTotalTrendNumber)//��ҪɾȥһЩm_vecChannelGroups��
            {
                temp = m_vecChannelGroups.size() - m_nTotalTrendNumber;
                for(int i = 0; i < temp; i++)
                {
                    m_vecChannelGroups.pop_back();
                    m_vecDisplayGroups.pop_back();
                }
            }

            emit ChnnelChange(begin, m_nTotalTrendNumber);//����ͨ���ı��ź�
        }
    }
    */
}

void QTrendbTable::on_doubleSpinBox_outputMin_valueChanged(double value)
{
    m_nDisplayMax = ui->doubleSpinBox_outputMax->text().toDouble();

}

void QTrendbTable::on_doubleSpinBox_outputMax_valueChanged(double value)
{
    m_nDisplayMax = ui->doubleSpinBox_outputMin->text().toDouble();

}

void QTrendbTable::setAllChl(bool checked)
{
    m_bIsAll = checked;
    ui->comboBox_pipeNum->setDisabled(checked);
    if(checked)
    {
        for (int i=0; i<m_vecChannelGroups.size(); i++)
        {
            m_vecChannelGroups[i].eLineType = (LineStyleType)(ui->comboBox_lineStyle->currentIndex()+1);
            m_vecChannelGroups[i].nLineThickness = ui->spinBox_lineWidth->value();
            m_vecChannelGroups[i].eDisplayCondition = (DisConType)(ui->comboBox_showCondition->currentIndex()+1);


            m_vecChannelGroups[i].nDisplayColor = ui->pushButton_showColor->palette().background().color();//����ɫ;
            if (m_vecChannelGroups[i].eDisplayCondition != DisplayKeep
                && !pwnd->IsAddressCheckRight(m_vecChannelGroups[i].KeyAddr,tr("��ʾ������ַ"),ui->lineEdit_ctlAddr,0))
            {
                ui->lineEdit_ctlAddr->setFocus();
                break;
            }
        }
    }
}


void QTrendbTable::initChannelPro()
{

    ui->comboBox_showCondition->setCurrentIndex(0);
    ui->lineEdit_ctlAddr->setText("LB0");
    ui->comboBox_lineStyle->setCurrentIndex(0);
    ui->spinBox_lineWidth->setValue(1);
    ui->pushButton_showColor->setStyleSheet(QString("background:%1").arg("192,192,192"));
}

void QTrendbTable::setDefaultChl()
{
    m_defaultChl.m_nNumOfChannel = 0;
    m_defaultChl.eLineType = LineSolid;
    m_defaultChl.nLineThickness = 1;
    m_defaultChl.eDisplayCondition = DisplayKeep;
    m_defaultChl.nDisplayColor = QColor(192,192,192);

}

void QTrendbTable::setCurrentChl()
{
    if (ui->comboBox_pipeNum->currentText().isEmpty())
    {
        return;
    }
    ChannelGroupInfo chl;
    chl.m_sGroupName = ui->comboBox_pipeNum->currentText();
    chl.eLineType = (LineStyleType)(ui->comboBox_lineStyle->currentIndex()+1);
    chl.nLineThickness = ui->spinBox_lineWidth->value();
    chl.eDisplayCondition = (DisConType)(ui->comboBox_showCondition->currentIndex()+1);


    chl.nDisplayColor = ui->pushButton_showColor->palette().background().color();//����ɫ;
    /*add by wxy ����ַ���ŵ������ʱ��ȥ���������ַ������Ϣѭ����ʾ��
    if (chl.eDisplayCondition != DisplayKeep
        && !pwnd->IsAddressCheckRight(chl.KeyAddr,tr("��ʾ������ַ"),ui->lineEdit_ctlAddr,0))
    {
        ui->lineEdit_ctlAddr->setFocus();
        return;
    }
    */
    int Addr_Type = 0;
    pwnd->CheckString(chl.KeyAddr,ui->lineEdit_ctlAddr->text(),Addr_Type);
    chl.KeyAddr.nAddrType = Addr_Type; //��¼��λ��ʾ

    for (int i=0; i<m_vecChannelGroups.size(); i++)
    {
        if(m_bIsAll)
        {
            ChannelGroupInfo curChl = m_vecChannelGroups[i];
            chl.m_sGroupName = curChl.m_sGroupName;
            m_vecChannelGroups.replace(i,chl);


        }
        else
        {
            ChannelGroupInfo curChl = m_vecChannelGroups[i];
            if (curChl.m_sGroupName == chl.m_sGroupName)
            {
                m_vecChannelGroups.replace(i,chl);
                break;
            }
        }
    }
}

void QTrendbTable::channelIndexChanged(QString sNumber)
{
    if (ui->comboBox_pipeNum->currentText().isEmpty())
    {
        return;
    }
    QString groupName = ui->comboBox_pipeNum->currentText();
    for (int i=0; i<m_vecChannelGroups.size(); i++)
    {
        ChannelGroupInfo curChl = m_vecChannelGroups[i];
        if (curChl.m_sGroupName == groupName)
        {
            ui->comboBox_showCondition->setCurrentIndex(curChl.eDisplayCondition -1);

            ui->lineEdit_ctlAddr->setText(curChl.KeyAddr.sShowAddr);
            ui->comboBox_lineStyle->setCurrentIndex(curChl.eLineType-1);
            ui->spinBox_lineWidth->setValue(curChl.nLineThickness);
            ui->pushButton_showColor->setStyleSheet(
                QString("background:%1").arg(curChl.nDisplayColor.name()));
            setBtnColor(curChl.nDisplayColor);
            //conditionChanged(curChl.eDisplayCondition -1);
            break;
        }
    }

}

void QTrendbTable::btncolorClicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->pushButton_showColor,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBtnColor(const QColor &)));

}

void QTrendbTable::btnAddrClicked()
{
    pwnd->Addr_Type=0;
    Keyboard ctlAddr;
    AddressInputDialog addressintputdlg_writeaddress(ctlAddr,this);
    if(addressintputdlg_writeaddress.exec())
    {
        int chNum = ui->comboBox_pipeNum->currentText().toInt();
        m_vecChannelGroups[chNum].KeyAddr = ctlAddr;
        ui->lineEdit_ctlAddr->setText(ctlAddr.sShowAddr);
        //int nIndex = ui->comboBox_pipeNum->findText(ctlAddr.sShowAddr);
        //ui->comboBox_pipeNum->setCurrentIndex(nIndex);
        setCurrentChl();
    }

    /*QString str = ui->lineEdit_showAddr->text();
    AddressInputDialog dlg_readaddress(ctlAddr,str,0,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_showAddr->setText(ctlAddr.sShowAddr);
        setCurrentChl();
    }*/

    /*int chNum = ui->comboBox_pipeNum->currentText().toInt();
    ChannelGroupInfo curCh = m_vecChannelGroups[chNum];
    if(curCh.KeyAddr.sShowAddr == "")
    {
        ui->lineEdit_ctlAddr->setText("LB0");
    }
    else
    {
        ui->lineEdit_ctlAddr->setText(m_vecChannelGroups[chNum].KeyAddr.sShowAddr);
    }*/
}
void QTrendbTable::setBtnColor(const QColor &color)
{
    ui->pushButton_showColor->setStyleSheet(QString("background:%1").arg(color.name()));
    setCurrentChl();
}
void QTrendbTable::conditionChanged(int index)
{
	if (m_vecChannelGroups.size() == 0)
	{
		return ;
	}
    bool bValue = false;

    if (index != 0)
    {
        bValue = true;
        int chNum = ui->comboBox_pipeNum->currentText().toInt();
        ChannelGroupInfo curCh = m_vecChannelGroups[chNum];
        if(curCh.KeyAddr.sShowAddr == "")
        {
            ui->lineEdit_ctlAddr->setText("LB0");
        }
        else
        {
            ui->lineEdit_ctlAddr->setText(curCh.KeyAddr.sShowAddr);
        }
    }
    ui->lineEdit_ctlAddr->setEnabled(bValue);
    ui->label_showAddr->setEnabled(bValue);
    ui->pushButton_ctlAddr->setEnabled(bValue);

    setCurrentChl();
}
double QTrendbTable::getDisplayMax()
{
	return ui->doubleSpinBox_outputMax->value();
}
double QTrendbTable::getDisplayMin()
{
	return ui->doubleSpinBox_outputMin->value();
}

bool QTrendbTable::save()
{
    for (int i=0; i<m_vecChannelGroups.size(); i++)
    {
        ChannelGroupInfo curChl = m_vecChannelGroups[i];
        if(curChl.eDisplayCondition != DisplayKeep
           && !pwnd->IsAddressCheckRight(curChl.KeyAddr,tr("��ʾ������ַ"),ui->lineEdit_ctlAddr,0))
        {
            ui->lineEdit_ctlAddr->setFocus();
            return false;
        }
    }
    return true;
}
