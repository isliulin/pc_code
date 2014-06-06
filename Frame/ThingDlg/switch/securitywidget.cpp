#include "securitywidget.h"
// "ui_securitywidget.h"
#include "Frame/mainwindow.h"
#include "view/switchitem.h"

extern MainWindow *pwnd;
SecurityWidget::SecurityWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecurityWidget)
{
    ui->setupUi(this);
    on_combo_NoticceAddrType_currentIndexChanged(0);
    QVector<GroupPermiss> groups;
    groups = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup;


    foreach(GroupPermiss group,groups)
    {
        QString name = group.m_strName;
        if(!name.isEmpty())
        {
            QListWidgetItem *listItem = new QListWidgetItem(name,ui->listT);
            ui->listT->addItem(listItem);
            listItem->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
            listItem->setCheckState(Qt::Unchecked);

            listItem = new QListWidgetItem(name,ui->listV);
            ui->listV->addItem(listItem);
            listItem->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
            listItem->setCheckState(Qt::Unchecked);
        }
    }
    on_combo_addrTypeV_currentIndexChanged(0);
    on_combo_addrTypeT_currentIndexChanged(0);
    connect(ui->listT,SIGNAL(itemChanged(QListWidgetItem*)),this,SLOT(OnListTChanged(QListWidgetItem*)));
    connect(ui->listV,SIGNAL(itemChanged(QListWidgetItem*)),this,SLOT(OnListVChanged(QListWidgetItem*)));

}
void SecurityWidget::OnListTChanged(QListWidgetItem *listItem)
{
    QListWidgetItem *pItem = NULL;
    if(listItem == ui->listT->item(0))
    {
        if(listItem->checkState() == Qt::Checked)
        {
            for(int i =1; i<ui->listT->count();i++)
            {
                pItem = ui->listT->item(i);
                pItem->setCheckState(Qt::Unchecked);

            }
        }

    }
    else
    {
        if(listItem->checkState() == Qt::Checked && ui->listT->item(0)->checkState() == Qt::Checked)
        {
            ui->listT->item(0)->setCheckState(Qt::Unchecked);
        }
    }
}
void SecurityWidget::OnListVChanged(QListWidgetItem *listItem)
{
    QListWidgetItem *pItem = NULL;
    if(listItem == ui->listV->item(0))
    {
        if(listItem->checkState() == Qt::Checked)
        {
            for(int i =1; i<ui->listV->count();i++)
            {
                pItem = ui->listV->item(i);
                pItem->setCheckState(Qt::Unchecked);

            }
        }

    }
    else
    {
        if(listItem->checkState() == Qt::Checked && ui->listV->item(0)->checkState() == Qt::Checked)
        {
            ui->listV->item(0)->setCheckState(Qt::Unchecked);
        }
    }
}

SecurityWidget::~SecurityWidget()
{
    delete ui;
}

void SecurityWidget::setTouchDisable(bool checked)
{
    ui->groupBox_Touch->setDisabled(checked);
    ui->groupBox_Notice->setDisabled(checked);
    ui->group_press->setDisabled(checked);
}

//根据pItem属性初始化权限页面
void SecurityWidget::init(QItemGroup *pItem)
{
    //add init code here
    item = pItem;
    if(item)
    {
         QVisableItem *switchitem = dynamic_cast<QVisableItem *> (item);
         if(switchitem)
         {
            init(switchitem->sPro);
         }
    }

}

//初始化权限页面设置的属性存入pItem
bool SecurityWidget::Save()
{
    //add save code here
    if(ui->groupBox_Touch->isChecked() && ui->groupBox_TouchByBit->isChecked())
    {
        bool bType = ui->combo_addrTypeT->currentIndex();
        if(! pwnd->IsAddressCheckRight(AddrT,tr("触控控制地址"),ui->edit_ctlAddrT,bType))
        {
            ui->edit_ctlAddrT->setFocus();
            return false;
        }
    }

    if(ui->GroupV->isChecked() && ui->groupBox_ShowByBit->isChecked())
    {
        int nType = ui->combo_addrTypeV->currentIndex();
        if(! pwnd->IsAddressCheckRight(AddrV,tr("显现控制地址"),ui->edit_ctlAddrV,nType))
        {
            ui->edit_ctlAddrV->setFocus();
            return false;
        }
    }

    if(ui->groupBox_Notice->isChecked())
    {
        bool bType = ui->combo_NoticceAddrType->currentIndex();
        if(! pwnd->IsAddressCheckRight(noticeAddr,tr("解锁通知地址"),ui->edit_noticeAddr,bType))
        {
            ui->edit_noticeAddr->setFocus();
            return false;
        }

    }
    AddrT.Length = 1;
    AddrV.Length = 1;
    sproperty.enableTouch = ui->groupBox_Touch->isChecked();
    sproperty.enableVisable = ui->GroupV->isChecked();


    sproperty.byGroups_T = ui->groupBox_TouchByGroup->isChecked();
    sproperty.byGroups_V = ui->groupBox_ShowByGroup->isChecked();

    sproperty.addrType_T = ui->combo_addrTypeT->currentIndex();
    sproperty.addrType_V = ui->combo_addrTypeV->currentIndex();

    sproperty.bitIndex_T = ui->spin_bitIndexT->value();
    sproperty.bitIndex_V = ui->spin_bitIndexV->value();

    sproperty.condition_T = ui->combo_conditionT->currentIndex();
    sproperty.condition_V = ui->combo_conditionV->currentIndex();

    sproperty.address_T = AddrT;
    sproperty.address_V = AddrV;

    //还要加入用户组部分代码
	if (ui->listT->item(0)->checkState() == Qt::Checked)
	{
		foreach(GroupPermiss grp,pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup)
		{
			sproperty.groups_T << grp.m_strName;
		}
	}
	else
	{
		for(int i=0; i<ui->listT->count(); i++)
		{
			QString group = ui->listT->item(i)->text();
			if(ui->listT->item(i)->checkState() == Qt::Checked)
			{
				if(!sproperty.groups_T.contains(group))
					sproperty.groups_T << group;
			}
			else
			{
				if(sproperty.groups_T.contains(group))
                                        sproperty.groups_T.removeAll(group);
			}
		}
	}
	if (ui->listV->item(0)->checkState() == Qt::Checked)
	{
		foreach(GroupPermiss grp,pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup)
		{
			sproperty.groups_V << grp.m_strName;
		}
	}
	else 
	{
		for(int i=0; i<ui->listV->count(); i++)
		{
			QString group = ui->listV->item(i)->text();
			if(ui->listV->item(i)->checkState() == Qt::Checked)
			{
				if(!sproperty.groups_V.contains(group))
					sproperty.groups_V << group;
			}
			else
			{
				if(sproperty.groups_V.contains(group))
                                        sproperty.groups_V.removeAll(group);
			}
		}
    }
    sproperty.addrNotice = noticeAddr;
    sproperty.bDelay = ui->group_press->isChecked();
    sproperty.bNotice = ui->groupBox_Notice->isChecked();
    if(ui->combo_NoticceAddrType->currentIndex() == 0)
    {
        sproperty.datatype = 0;
        sproperty.addrNotice.Length = 1;
    }
    else
    {
        sproperty.datatype = ui->combo_NoticeType->currentIndex()+1;
        if(sproperty.datatype ==1 || sproperty.datatype == 3)
        {
            sproperty.addrNotice.Length = 1;
        }
        else
            sproperty.addrNotice.Length = 2;
    }
    sproperty.noticeValue = ui->edit_Value->text().toDouble();
    sproperty.time = ui->spin_time->value();

    return true;


}

//选择“触控受用户组权限控制”
void SecurityWidget::on_groupBox_TouchByGroup_clicked(bool value)
{
    ui->groupBox_TouchByBit->setChecked(!value);
}
//选择“触控受位控制”
void SecurityWidget::on_groupBox_TouchByBit_clicked(bool value)
{
    ui->groupBox_TouchByGroup->setChecked(!value);
}

//选择“显现受位控制”
void SecurityWidget::on_groupBox_ShowByBit_clicked(bool value)
{
    ui->groupBox_ShowByGroup->setChecked(!value);
}

//选择“显现受用户组权限控制”
void SecurityWidget::on_groupBox_ShowByGroup_clicked(bool value)
{
    ui->groupBox_ShowByBit->setChecked(!value);
}



void SecurityWidget::on_btn_ctlAddrT_clicked()
{
    int addrType=ui->combo_addrTypeT->currentIndex();
    QString addrStr = ui->edit_ctlAddrT->text();
    AddressInputDialog addressintputdlg_writeaddress(AddrT,addrStr,addrType,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->edit_ctlAddrT->setText(AddrT.sShowAddr);
    }

}

void SecurityWidget::on_btn_noticeAddr_clicked()
{
    int addrType=pwnd->Addr_Type=ui->combo_NoticceAddrType->currentIndex();
    QString addrStr = ui->edit_noticeAddr->text();
    AddressInputDialog addressintputdlg_writeaddress(noticeAddr,addrStr,addrType,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->edit_noticeAddr->setText(noticeAddr.sShowAddr);
    }
}

void SecurityWidget::on_btn_ctlAddrV_clicked()
{
    int addrType=pwnd->Addr_Type=ui->combo_addrTypeV->currentIndex();
    QString addrStr = ui->edit_ctlAddrV->text();
    AddressInputDialog addressintputdlg_writeaddress(AddrV,addrStr,addrType,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->edit_ctlAddrV->setText(AddrV.sShowAddr);
    }

}


void SecurityWidget::on_combo_NoticceAddrType_currentIndexChanged(int index)
{
    ui->label_5->setEnabled(index);
    ui->combo_NoticeType->setEnabled(index);
	if (index == 0)
	{
		QIntValidator *validator = new QIntValidator(0,1,this);
		ui->edit_Value->setValidator(validator);
	}
	else
	{
		int cIndex = ui->combo_NoticeType->currentIndex();
		on_combo_NoticeType_currentIndexChanged(cIndex);
	}
}

void SecurityWidget::setTouchGroupEnabled(bool value)
{
    if(value)
    {
		
        ui->groupBox_Touch->setEnabled(true);
        ui->groupBox_Notice->setEnabled(true);
        ui->group_press->setEnabled(true);
    }
    else
    {
		ui->groupBox_Touch->setChecked(false);
        ui->groupBox_Notice->setChecked(false);
        ui->group_press->setChecked(false);
        ui->groupBox_Touch->setEnabled(false);
        ui->groupBox_Notice->setEnabled(false);
        ui->group_press->setEnabled(false);
    }
}

void SecurityWidget::on_combo_addrTypeV_currentIndexChanged(int index)
{
    if(0 == index)
    {
        ui->spin_bitIndexV->setEnabled(false);
        ui->label_9->setEnabled(false);
    }
    else
    {
        ui->spin_bitIndexV->setEnabled(true);
        ui->label_9->setEnabled(true);
    }
}

void SecurityWidget::on_combo_addrTypeT_currentIndexChanged(int index)
{
    if(0 == index)
    {
        ui->spin_bitIndexT->setEnabled(false);
        ui->label_4->setEnabled(false);
    }
    else
    {
        ui->spin_bitIndexT->setEnabled(true);
        ui->label_4->setEnabled(true);
    }
}

void SecurityWidget::on_combo_NoticeType_currentIndexChanged(int index)
{
	if (ui->combo_NoticceAddrType->currentIndex() == 0)
	{
		QIntValidator *validator = new QIntValidator(0,1,this);
		ui->edit_Value->setValidator(validator);
	}
	else
	{
		double nMax = 2147483647L;
		double nMin = -2147483648L;
		int decLen = 0;
		switch(index)
		{
		case 0://16位整数
			{
				nMax = 32767;
				nMin = -32768;
				decLen = 0;
			}
			break;
		case 1://32位整数
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
		case 4://32位浮点数
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
		ui->edit_Value->setValidator(validator);
		double value = ui->edit_Value->text().toDouble();
		if (value > nMax || value < nMin)
		{
			ui->edit_Value->setText("0");
		}
	}
}

void SecurityWidget::setGroupVVisible(bool bShow)
{
    ui->groupBox_Touch->setVisible(bShow);
    ui->group_press->setVisible(bShow);
    ui->groupBox_TouchByBit->setVisible(bShow);
    ui->groupBox_Notice->setVisible(bShow);
}

void SecurityWidget::init(securityPro sproperty)
{
    ui->groupBox_Touch->setChecked(sproperty.enableTouch);
    ui->GroupV->setChecked(sproperty.enableVisable);

    if(sproperty.enableTouch && sproperty.byGroups_T)//触控受用户组控制
    {
        ui->groupBox_TouchByBit->setChecked(false);
        ui->groupBox_TouchByGroup->setChecked(true);
        for(int i=0; i<ui->listT->count(); i++)
        {
            QString group = ui->listT->item(i)->text();
            if(sproperty.groups_T.contains(group))
            {
                ui->listT->item(i)->setCheckState(Qt::Checked);
            }
            else
                ui->listT->item(i)->setCheckState(Qt::Unchecked);
        }
    }
    if(sproperty.enableTouch && !sproperty.byGroups_T)//触控受位控制
    {
        ui->groupBox_TouchByBit->setChecked(true);
        ui->groupBox_TouchByGroup->setChecked(false);
        ui->combo_addrTypeT->setCurrentIndex(sproperty.addrType_T);
        ui->spin_bitIndexT->setValue(sproperty.bitIndex_T);
        ui->edit_ctlAddrT->setText(sproperty.address_T.sShowAddr);
        ui->combo_conditionT->setCurrentIndex(sproperty.condition_T);
        AddrT = sproperty.address_T;
    }
    if(sproperty.enableVisable && sproperty.byGroups_V)//显现受用户组控制
    {
        ui->groupBox_ShowByBit->setChecked(false);
        ui->groupBox_ShowByGroup->setChecked(true);
        for(int i=0; i<ui->listV->count(); i++)
        {
            QString group = ui->listV->item(i)->text();
            if(sproperty.groups_V.contains(group))
            {
                ui->listV->item(i)->setCheckState(Qt::Checked);
            }
            else
                ui->listV->item(i)->setCheckState(Qt::Unchecked);
        }
    }
    if(sproperty.enableVisable && !sproperty.byGroups_V)//显现受位控制
    {
        ui->groupBox_ShowByBit->setChecked(true);
        ui->groupBox_ShowByGroup->setChecked(false);
        ui->combo_addrTypeV->setCurrentIndex(sproperty.addrType_V);
        ui->spin_bitIndexV->setValue(sproperty.bitIndex_V);
        ui->edit_ctlAddrV->setText(sproperty.address_V.sShowAddr);
        ui->combo_conditionV->setCurrentIndex(sproperty.condition_V);
        AddrV = sproperty.address_V;
    }

    ui->groupBox_Notice->setChecked(sproperty.bNotice);
    if(sproperty.bNotice)
    {
        ui->edit_noticeAddr->setText(sproperty.addrNotice.sShowAddr);
        noticeAddr = sproperty.addrNotice;
        if(sproperty.datatype >0)
        {
            ui->combo_NoticceAddrType->setCurrentIndex(1);
            ui->combo_NoticeType->setCurrentIndex(sproperty.datatype-1);
        }
        else
        {
            on_combo_NoticceAddrType_currentIndexChanged(0);
            ui->combo_NoticceAddrType->setCurrentIndex(0);
        }
        ui->edit_Value->setText(QString::number(sproperty.noticeValue));
    }
    ui->group_press->setChecked(sproperty.bDelay);
    if(sproperty.bDelay)
       ui->spin_time->setValue(sproperty.time);
}
