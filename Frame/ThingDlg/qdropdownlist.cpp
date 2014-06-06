#include "qdropdownlist.h"
#include "ui_qdropdownlist.h"
#include "../mainwindow.h"
#include "Macro/macroedit.h"

extern MainWindow *pwnd;

qDropDownList::qDropDownList(QWidget *parent):QWidget(parent),ui(new Ui::qDropDownList)
{
    isInit = false;
    ui->setupUi(this);
    ui->edit_const->setText("LW0");

    //ui->comboBox_executeType->hide();
    //ui->label_5->hide();

    ui->comboBox_operType->clear();
    ui->comboBox_operType->addItem(tr("��ת����һ������"));
    ui->comboBox_operType->addItem(tr("��ת��ָ������"));
    ui->comboBox_operType->addItem(tr("�򿪴���"));
    ui->comboBox_operType->addItem(tr("�رմ���"));
    ui->comboBox_operType->addItem(tr("������һ������"));

    //ui->comboBox_operateType->removeItem(3);

    /*ui->comboBox_ScreenIndex->clear();
    screenNum = pwnd->copyScreen_Item->childCount();//�ܵĻ�����
    QString str;
    for(int i = 0; i < screenNum; i++)
    {
        str = pwnd->copyScreen_Item->child(i)->text(0);
        ui->comboBox_ScreenIndex->addItem(str);
    }

    int windowNum = pwnd->copyWindow_Item->childCount();//������
    for(int i = 0; i < windowNum; i++)
    {
        str = pwnd->copyWindow_Item->child(i)->text(0);
        ui->comboBox_ScreenIndex->addItem(str);
    }*/

    //ui->label->hide();
    ui->spinBox->hide();

    ui->comboBox_curLan->clear();
    int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    for(int i = 0; i < lanNum; i++)
    {
        ui->comboBox_curLan->addItem(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
    }

    foreach(Macro lib, pwnd->macros)
    {
        if (lib.type && lib.isCompiled())
        {
            ui->comboBox_script->addItem(lib.libName);
            //ui->comboBox_function->addItems(lib.functions);
        }
    }

    //ui->spin_Value->hide();
}

qDropDownList::~qDropDownList()
{
    delete ui;
}

void qDropDownList::Init(QDropdownAttr *pItem)
{
    int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();

    if(pItem)
    {
        m_nShowNumber   = pItem->m_nShowNumber;
        isUseScript     = pItem->isUseScript;
        macroName       = pItem->macroName;
        functionName    = pItem->functionName;
        m_vecSwitchItem = pItem->m_vecSwitchItem;

        ui->check_pic->setChecked(pItem->m_bUsePic);
        int subNum;
        int switchNum = m_vecSwitchItem.size();
        if(m_vecSwitchItem[0].vecSwitchFunName.size() > lanNum)
        {
            subNum = m_vecSwitchItem[0].vecSwitchFunName.size() - lanNum;
            for(int i = 0; i < switchNum; i++)
            {
                for(int j = 0; j < subNum; j++)
                {
                    m_vecSwitchItem[i].vecSwitchFunName.remove(lanNum);
                }
            }
        }
        else if(m_vecSwitchItem[0].vecSwitchFunName.size() < lanNum)
        {
            subNum = lanNum - m_vecSwitchItem[0].vecSwitchFunName.size();
            for(int i = 0; i < switchNum; i++)
            {
                for(int j = 0; j < subNum; j++)
                {
                    QString str = tr("����1");
                    m_vecSwitchItem[i].vecSwitchFunName.push_back(str);
                }
            }
        }
    }
    else
    {
        m_nShowNumber       = 1;//��СΪ1�������б�Ӧ�����ٷ�һ��λ����
        isUseScript         = false;
        macroName           = "";
        functionName        = "";
        m_vecSwitchItem.clear();
        SwitchInfo info;

        QString strTemp = tr("λ����");
        for(int i = 0; i < lanNum; i++)
        {
            info.vecSwitchFunName.push_back(strTemp);
        }
        //info.switchFunName  = tr("����1");
        info.switchType     = 1;//Ĭ��λ����
        info.addrBit.sShowAddr = ui->edit_operatingAddr->text();
        //info.operTypeB = (BIT_OPER_TYPE)(ui->comboBox_operateType->currentIndex() + 1);
        info.operTypeB = (BIT_OPER_TYPE)1;

        info.addrConst.sShowAddr = "LW0";
        info.bDynamicControl = false;
        m_vecSwitchItem.push_back(info);
    }

    int num = m_vecSwitchItem.size();
    for(int i = 0; i < num; i++)
    {
        if(1 == m_vecSwitchItem[i].switchType)
        {
            ui->listWidget->addItem(tr("λ����"));
        }
        else if(2 == m_vecSwitchItem[i].switchType)
        {
            ui->listWidget->addItem(tr("�ֲ���"));
        }
        else if(3 == m_vecSwitchItem[i].switchType)
        {
            ui->listWidget->addItem(tr("�����л�"));
        }
        QString sFunname;
        int index = ui->comboBox_curLan->currentIndex();
        if(index < 0)
        {
            index = 0;
        }
        if(m_vecSwitchItem[i].vecSwitchFunName.size() > 0)
        {
            sFunname = m_vecSwitchItem[i].vecSwitchFunName[index];
        }
        emit this->addFun(sFunname,m_vecSwitchItem[i].sPath);
    }

    ui->listWidget->setCurrentRow(0);
    if(1 == m_vecSwitchItem[0].switchType)
    {
        ui->groupBox->setEnabled(true);
        ui->groupBox_2->setEnabled(false);
        ui->groupBox_3->setEnabled(false);

        ui->edit_operatingAddr->setText(m_vecSwitchItem[0].addrBit.sShowAddr);
        ui->comboBox_operateType->setCurrentIndex((int)m_vecSwitchItem[0].operTypeB - 1);
    }
    else if(2 == m_vecSwitchItem[0].switchType)
    {
        ui->groupBox->setEnabled(false);
        ui->groupBox_2->setEnabled(true);
        ui->groupBox_3->setEnabled(false);

        on_comboBox_dataType_currentIndexChanged((int)m_vecSwitchItem[0].dataType - 1);

        ui->edit_operatingAddr_2->setText(m_vecSwitchItem[0].addrWord.sShowAddr);
        ui->comboBox_dataType->setCurrentIndex((int)m_vecSwitchItem[0].dataType - 1);
        ui->comboBox_operateType_2->setCurrentIndex((int)m_vecSwitchItem[0].operTypeW - 1);

        ui->check_const->setChecked(m_vecSwitchItem[0].bDynamicControl);
        if(m_vecSwitchItem[0].bDynamicControl)
        {
            ui->edit_const->setVisible(true);
            ui->btn_wordAddr_const->setVisible(true);
            ui->edit_value->setVisible(false);
        }
        else
        {
            ui->edit_const->setVisible(false);
            ui->btn_wordAddr_const->setVisible(false);
            ui->edit_value->setVisible(true);
        }
        ui->edit_const->setText(m_vecSwitchItem[0].addrConst.sShowAddr);
        ui->edit_value->setText(QString::number(m_vecSwitchItem[0].value));
    }
    else if(3 == m_vecSwitchItem[0].switchType)
    {
        ui->groupBox->setEnabled(false);
        ui->groupBox_2->setEnabled(false);
        ui->groupBox_3->setEnabled(true);

        int type = (int)m_vecSwitchItem[0].operType;
        ui->comboBox_operType->setCurrentIndex(type - 1);

        if(1 == type || 4 == type || 5 == type )
        {
            ui->label_10->hide();
            ui->comboBox_ScreenIndex->hide();
        }
        else
        {
            ui->label_10->show();
            ui->comboBox_ScreenIndex->show();
        }

        if(1 == type || 2 == type)//Ҫ��ʾ���滹�Ǵ���
        {
            ui->comboBox_ScreenIndex->clear();
            screenNum = pwnd->copyScreen_Item->childCount();//�ܵĻ�����
            for(int i = 0; i < screenNum; i++)
            {
                QString str = pwnd->copyScreen_Item->child(i)->text(0).split(":").at(1);
                ui->comboBox_ScreenIndex->addItem(str);
            }
        }
        else//3,4
        {
            ui->comboBox_ScreenIndex->clear();
            int windowNum = pwnd->copyWindow_Item->childCount();//������
            for(int i = 0; i < windowNum; i++)
            {
                QString str = pwnd->copyWindow_Item->child(i)->text(0).split(":").at(1);
                ui->comboBox_ScreenIndex->addItem(str);
            }
        }

        ui->checkBox->setChecked(m_vecSwitchItem[0].bLogout);

        int countS = ui->comboBox_ScreenIndex->count();
        bool tt = false;
        for(int i = 0; i < countS; i++)
        {
            if(ui->comboBox_ScreenIndex->itemText(i) == m_vecSwitchItem[0].sceneName)
            {
                ui->comboBox_ScreenIndex->setCurrentIndex(i);
                tt = true;
            }
        }

        if(tt == false)
        {
            ui->comboBox_ScreenIndex->setCurrentIndex(0);
            m_vecSwitchItem[0].sceneName = ui->comboBox_ScreenIndex->currentText();
        }
    }

    //on_comboBox_dataType_currentIndexChanged(0);
    ui->spinBox->setValue(m_nShowNumber);
    //ui->lineEdit_name->setText(m_vecSwitchItem[0].switchFunName);


    //���ýű�����
    ui->groupBox_4->setChecked(isUseScript);
    if(isUseScript)
    {
        if(macroName == "")
        {
            //macroName = ui->comboBox_script->itemText(0);
            //ui->comboBox_script->setCurrentIndex(0);
        }
        else
        {
            int macroIndex = ui->comboBox_script->findText(macroName);
            //if (macroIndex >=0)
            {
                ui->comboBox_script->setCurrentIndex(macroIndex);
            }
        }


    }

    if(m_vecSwitchItem.size() == 1)//����ɾ��
    {
        ui->pushButton_del->setEnabled(false);
    }
    else
    {
        ui->pushButton_del->setEnabled(true);
    }

    ui->comboBox_curLan->setCurrentIndex(0);
    //ui->listWidget->setCurrentRow(0);//���������д��
    ui->lineEdit_name->setText(m_vecSwitchItem[0].vecSwitchFunName[0]);

    isInit = true;

    //on_comboBox_dataType_currentIndexChanged(0);
}

void qDropDownList::on_spinBox_valueChanged(int value)
{
    m_nShowNumber = value;
}

void qDropDownList::on_pushButton_bit_clicked()
{
    int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();

    if(m_nShowNumber >= 16)
    {
        return;
    }

    m_nShowNumber++;

    ui->groupBox->setEnabled(true);
    ui->groupBox_2->setEnabled(false);
    ui->groupBox_3->setEnabled(false);

    SwitchInfo info;
    QString strTemp = tr("λ����");
    for(int i = 0; i < lanNum; i++)
    {
        info.vecSwitchFunName.push_back(strTemp);
    }
    //info.switchFunName  = tr("����1");
    info.switchType     = 1;
    //λ��������
    info.addrBit.sShowAddr = ui->edit_operatingAddr->text();
    //info.operTypeB = (BIT_OPER_TYPE)(ui->comboBox_operateType->currentIndex() + 1);
    info.operTypeB = (BIT_OPER_TYPE)1;
    info.addrConst.sShowAddr = "LW0";
    info.bDynamicControl = false;
    m_vecSwitchItem.push_back(info);

    ui->listWidget->addItem(tr("λ����"));
    ui->listWidget->setCurrentRow(m_vecSwitchItem.size() - 1);

    emit addFun(strTemp,QString(""));

    if(m_vecSwitchItem.size() == 1)//����ɾ��
    {
        ui->pushButton_del->setEnabled(false);
    }
    else
    {
        ui->pushButton_del->setEnabled(true);
    }
}

void qDropDownList::on_pushButton_word_clicked()
{
    int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();

    if(m_nShowNumber >= 16)
    {
        return;
    }

    m_nShowNumber++;

    ui->groupBox->setEnabled(false);
    ui->groupBox_2->setEnabled(true);
    ui->groupBox_3->setEnabled(false);

    SwitchInfo info;
    QString strTemp = tr("�ֲ���");
    for(int i = 0; i < lanNum; i++)
    {
        info.vecSwitchFunName.push_back(strTemp);
    }
    //info.switchFunName  = tr("����1");
    info.switchType     = 2;
    //�ֿ�������
    Keyboard key;
    pwnd->IsAddressCheckRight(key,tr("�ֵ�ַ"),ui->edit_operatingAddr_2,1);//�ⲽ�������
    info.addrWord = key;
    //info.addrWord.sShowAddr = ui->edit_operatingAddr_2->text();
    //info.operTypeW = (WORD_OPER_TYPE)(ui->comboBox_operateType_2->currentIndex() + 1);
    //info.dataType = (DATA_TYPE)(ui->comboBox_dataType->currentIndex() + 1);
    info.operTypeW = (WORD_OPER_TYPE)1;
    info.dataType = (DATA_TYPE)3;
    //info.value = ui->spin_Value->value();          //
    info.bDynamicControl = false;
    ui->edit_const->setText("LW0");
    Keyboard keyConst;
    pwnd->IsAddressCheckRight(keyConst,tr("�ֵ�ַ"),ui->edit_const,1);//�ⲽ�������
    info.addrConst = keyConst;

    info.value = ui->edit_value->text().toDouble();
    m_vecSwitchItem.push_back(info);

    ui->listWidget->addItem(tr("�ֲ���"));
    ui->listWidget->setCurrentRow(m_vecSwitchItem.size() - 1);

    emit addFun(strTemp,QString(""));

    if(m_vecSwitchItem.size() == 1)//����ɾ��
    {
        ui->pushButton_del->setEnabled(false);
    }
    else
    {
        ui->pushButton_del->setEnabled(true);
    }
}

void qDropDownList::on_pushButton_pic_clicked()
{
    int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();

    if(m_nShowNumber >= 16)
    {
        return;
    }

    m_nShowNumber++;

    ui->groupBox->setEnabled(false);
    ui->groupBox_2->setEnabled(false);
    ui->groupBox_3->setEnabled(true);

    ui->comboBox_ScreenIndex->clear();
    screenNum = pwnd->copyScreen_Item->childCount();//�ܵĻ�����
    QString str;
    for(int i = 0; i < screenNum; i++)
    {
        str = pwnd->copyScreen_Item->child(i)->text(0).split(":").at(1);
        ui->comboBox_ScreenIndex->addItem(str);
    }
    ui->comboBox_ScreenIndex->setCurrentIndex(0);

    SwitchInfo info;
    QString strTemp = tr("�����л�");
    for(int i = 0; i < lanNum; i++)
    {
        info.vecSwitchFunName.push_back(strTemp);
    }
    //info.switchFunName  = tr("����1");
    info.switchType     = 3;
    //�����л�����
    //info.operType = (SCENE_OPER_TYPE)(ui->comboBox_operType->currentIndex() + 1);
    info.operType = (SCENE_OPER_TYPE)1;
    //info.nSceneType = 0;
    info.sceneName = ui->comboBox_ScreenIndex->currentText();
    info.bLogout = ui->checkBox->isChecked();        // �л������Ƿ�ע��
    m_vecSwitchItem.push_back(info);

    ui->listWidget->addItem(tr("�����л�"));
    ui->listWidget->setCurrentRow(m_vecSwitchItem.size() - 1);

    emit addFun(strTemp,QString(""));

    if(m_vecSwitchItem.size() == 1)//����ɾ��
    {
        ui->pushButton_del->setEnabled(false);
    }
    else
    {
        ui->pushButton_del->setEnabled(true);
    }

    ui->label_10->hide();
    ui->comboBox_ScreenIndex->hide();
}

void qDropDownList::on_pushButton_del_clicked()
{
    if(m_vecSwitchItem.size() <= 1)
    {
        //ֻ��һ����ʱ����ɾ��������һ��
        return;
    }

    if(m_nShowNumber <= 1)
    {
        return;
    }

    m_nShowNumber--;
    int curRow =  ui->listWidget->currentRow();   

    QListWidgetItem *item = ui->listWidget->currentItem();
    ui->listWidget->removeItemWidget(item);
    delete item;

    m_vecSwitchItem.remove(curRow);

    emit deleteFun("","");

    if(m_vecSwitchItem.size() == 1)//����ɾ��
    {
        ui->pushButton_del->setEnabled(false);
    }
    else
    {
        ui->pushButton_del->setEnabled(true);
    }
}

void qDropDownList::on_btn_bitAddr_clicked()
{
    QString str = ui->edit_operatingAddr->text();
    AddressInputDialog dlg_readaddress(m_vecSwitchItem[ui->listWidget->currentRow()].addrBit,str,0,this);
    if(dlg_readaddress.exec())
    {
        ui->edit_operatingAddr->setText(m_vecSwitchItem[ui->listWidget->currentRow()].addrBit.sShowAddr);
    }
}

void qDropDownList::on_edit_operatingAddr_editingFinished()
{
    if(!pwnd->IsAddressCheckRight(m_vecSwitchItem[ui->listWidget->currentRow()].addrBit,tr("λ��ַ"),ui->edit_operatingAddr,0))
    {
        //QMessageBox::about(this, tr("warning"), tr("λ��ַ����"));
        ui->edit_operatingAddr->setText(m_vecSwitchItem[ui->listWidget->currentRow()].addrBit.sShowAddr);
    }
}

void qDropDownList::on_btn_wordAddr_clicked()
{
    QString str = ui->edit_operatingAddr_2->text();
    AddressInputDialog dlg_readaddress(m_vecSwitchItem[ui->listWidget->currentRow()].addrWord,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->edit_operatingAddr_2->setText(m_vecSwitchItem[ui->listWidget->currentRow()].addrWord.sShowAddr);
    }
}

void qDropDownList::on_edit_operatingAddr_2_editingFinished()
{
    int addlen = 1;
    switch(ui->comboBox_dataType->currentIndex())
    {
        case 1:
        case 3:
        case 5:
        case 6:
        {
            addlen = 2;
        }
        break;
    }
    if(!pwnd->IsAddressCheckRight(m_vecSwitchItem[ui->listWidget->currentRow()].addrWord,tr("�ֵ�ַ"),ui->edit_operatingAddr_2,1))
    {
        //QMessageBox::about(this, tr("warning"), tr("�ֵ�ַ����"));
        ui->edit_operatingAddr_2->setText(m_vecSwitchItem[ui->listWidget->currentRow()].addrWord.sShowAddr);
    }
    m_vecSwitchItem[ui->listWidget->currentRow()].addrWord.Length = addlen;
}

void qDropDownList::on_listWidget_currentRowChanged(int currentRow)
{
    if(!isInit)
    {
        return;
    }

    if(1 == m_vecSwitchItem[currentRow].switchType)
    {
        ui->groupBox->setEnabled(true);
        ui->groupBox_2->setEnabled(false);
        ui->groupBox_3->setEnabled(false);

        ui->edit_operatingAddr->setText(m_vecSwitchItem[currentRow].addrBit.sShowAddr);
        ui->comboBox_operateType->setCurrentIndex((int)m_vecSwitchItem[currentRow].operTypeB - 1);
    }
    else if(2 == m_vecSwitchItem[currentRow].switchType)
    {
        ui->groupBox->setEnabled(false);
        ui->groupBox_2->setEnabled(true);
        ui->groupBox_3->setEnabled(false);

        double valueTemp = m_vecSwitchItem[currentRow].value;
        ui->edit_operatingAddr_2->setText(m_vecSwitchItem[currentRow].addrWord.sShowAddr);
        ui->comboBox_operateType_2->setCurrentIndex((int)m_vecSwitchItem[currentRow].operTypeW - 1);
        ui->comboBox_dataType->setCurrentIndex((int)m_vecSwitchItem[currentRow].dataType - 1);
        //ui->spin_Value->setValue(m_vecSwitchItem[currentRow].value);

        ui->check_const->setChecked(m_vecSwitchItem[currentRow].bDynamicControl);
        if(m_vecSwitchItem[currentRow].bDynamicControl)
        {
            ui->edit_const->setVisible(true);
            ui->btn_wordAddr_const->setVisible(true);
            ui->edit_value->setVisible(false);
        }
        else
        {
            ui->edit_const->setVisible(false);
            ui->btn_wordAddr_const->setVisible(false);
            ui->edit_value->setVisible(true);
        }
        ui->edit_const->setText(m_vecSwitchItem[currentRow].addrConst.sShowAddr);
        ui->edit_value->setText(QString::number(valueTemp,'g',10));
        m_vecSwitchItem[currentRow].value = valueTemp;
    }
    else if(3 == m_vecSwitchItem[currentRow].switchType)
    {
        ui->groupBox->setEnabled(false);
        ui->groupBox_2->setEnabled(false);
        ui->groupBox_3->setEnabled(true);

        //info.sceneName = ui->comboBox_ScreenIndex->currentText();
        QString strName = m_vecSwitchItem[currentRow].sceneName;
        ui->comboBox_operType->setCurrentIndex((int)m_vecSwitchItem[currentRow].operType - 1);
        //ִ����һ���Ժ�����뵽comboBox_operType�����У�����������ִ��,��ı�m_vecSwitchItem[currentRow].sceneName
        if(0 == ui->comboBox_operType->currentIndex() || 3 == ui->comboBox_operType->currentIndex()
            || 4 == ui->comboBox_operType->currentIndex())
        {
            ui->label_10->hide();
            ui->comboBox_ScreenIndex->hide();
        }
        else
        {
            ui->label_10->show();
            ui->comboBox_ScreenIndex->show();
        }

        //ui->comboBox_ScreenIndex->setCurrentIndex(m_vecSwitchItem[currentRow].nSceneType);
        int k = ui->comboBox_ScreenIndex->count();
        for(int i = 0; i < k; i++)
        {
            QString strTemp = ui->comboBox_ScreenIndex->itemText(i);
            if(strTemp == strName)
            {
                ui->comboBox_ScreenIndex->setCurrentIndex(i);
            }
        }
        ui->checkBox->setChecked(m_vecSwitchItem[currentRow].bLogout);
    }

    //ui->lineEdit_name->setText(m_vecSwitchItem[currentRow].switchFunName);
    ui->lineEdit_name->setText(m_vecSwitchItem[currentRow].vecSwitchFunName[ui->comboBox_curLan->currentIndex()]);
}

void qDropDownList::on_lineEdit_name_editingFinished()
{
    if(!isInit)
    {
        return;
    }

    //m_vecSwitchItem[ui->listWidget->currentRow()].switchFunName = ui->lineEdit_name->text();
    m_vecSwitchItem[ui->listWidget->currentRow()].vecSwitchFunName[ui->comboBox_curLan->currentIndex()] = ui->lineEdit_name->text();
}

void qDropDownList::on_comboBox_operateType_currentIndexChanged(int index)
{
    m_vecSwitchItem[ui->listWidget->currentRow()].operTypeB = (BIT_OPER_TYPE)(index + 1);
}

void qDropDownList::on_comboBox_dataType_currentIndexChanged(int index)
{
    if(!isInit)
    {
        return;
    }
    int addlen = 1;
    double  nMax   = 2147482647L;
    double  nMin   = -2147482648L;
    int     decLen = 0;
    switch(index)
    {
        case 0://16λ����
        case 4://16λBCD��
        {
            nMax = 32767;
            nMin = -32768;
            decLen = 0;
        }
        break;

        case 1://32λ����
        case 5://32λBCD��
        {
            nMax = 2147482647L;
            nMin = -2147482648L;
            decLen = 0;
            addlen = 2;
        }
        break;

        case 2://16λ������
        {
            nMax = 65535;
            nMin = 0;
            decLen = 0;
        }
        break;

        case 3://32λ������
        {
            nMax = 4294967295UL;
            nMin = 0;
            decLen = 0;
            addlen = 2;
        }
        break;

        case 6://32λ������
        {
            nMax = 2147482647L;
            nMin = -2147482648L;
            decLen = 10;
            addlen = 2;
        }
        break;
    }

    if (nMin>0)
    {
        nMin = nMin*-1;
    }
    DoubleValidator *validator = new DoubleValidator(nMin,nMax,decLen,this);
    ui->edit_value->setValidator(validator);

    m_vecSwitchItem[ui->listWidget->currentRow()].dataType = (DATA_TYPE)(index + 1);
    m_vecSwitchItem[ui->listWidget->currentRow()].value    = 1;
    m_vecSwitchItem[ui->listWidget->currentRow()].addrWord.Length = addlen;
    m_vecSwitchItem[ui->listWidget->currentRow()].addrConst.Length = addlen;
    ui->edit_value->setText(QString::number(1));
}

void qDropDownList::on_comboBox_operateType_2_currentIndexChanged(int index)
{
    m_vecSwitchItem[ui->listWidget->currentRow()].operTypeW = (WORD_OPER_TYPE)(index + 1);
}

void qDropDownList::on_spin_Value_valueChanged(int value)
{
    m_vecSwitchItem[ui->listWidget->currentRow()].value = value;
}

void qDropDownList::on_comboBox_operType_currentIndexChanged(int index)
{
    if(!isInit)
    {
        return;
    }

    if(0 == index || 3 == index || 4 == index)
    {
        ui->label_10->hide();
        ui->comboBox_ScreenIndex->hide();
    }
    else
    {
        ui->label_10->show();
        ui->comboBox_ScreenIndex->show();
    }

    if(0 == index || 1 == index)
    {
        ui->comboBox_ScreenIndex->clear();
        //ִ������Ժ�����comboBox_ScreenIndex
        screenNum = pwnd->copyScreen_Item->childCount();//�ܵĻ�����
        for(int i = 0; i < screenNum; i++)
        {
            QString str = pwnd->copyScreen_Item->child(i)->text(0).split(":").at(1);
            ui->comboBox_ScreenIndex->addItem(str);
        }
    }
    else if(2 == index)
    {
        ui->comboBox_ScreenIndex->clear();
        int windowNum = pwnd->copyWindow_Item->childCount();//������
        for(int i = 0; i < windowNum; i++)
        {
            QString str = pwnd->copyWindow_Item->child(i)->text(0).split(":").at(1);
            ui->comboBox_ScreenIndex->addItem(str);
        }
    }

    m_vecSwitchItem[ui->listWidget->currentRow()].operType = (SCENE_OPER_TYPE)(index + 1);
}

void qDropDownList::on_comboBox_ScreenIndex_currentIndexChanged(int index)
{
    if(!isInit)
    {
        return;
    }

    if(-1 == index)
    {
        return;
    }

    //m_vecSwitchItem[ui->listWidget->currentRow()].nSceneType = index;
    m_vecSwitchItem[ui->listWidget->currentRow()].sceneName  = ui->comboBox_ScreenIndex->currentText();
}

void qDropDownList::on_checkBox_clicked(bool checked)
{
    m_vecSwitchItem[ui->listWidget->currentRow()].bLogout = checked;
}

void qDropDownList::on_groupBox_4_clicked(bool checked)
{
    ui->label_13->setEnabled(checked);
    ui->btn_new->setEnabled(checked);
    ui->comboBox_script->setEnabled(checked);

    macroName    = ui->comboBox_script->currentText();

    isUseScript = checked;
}


void qDropDownList::on_comboBox_script_currentIndexChanged(int index)
{
    macroName = ui->comboBox_script->currentText();
    qDebug() << "on_comboBox_script_currentIndexChanged:" << macroName;
}

void qDropDownList::on_comboBox_curLan_currentIndexChanged(int index)
{
    if(!isInit)
    {
        return;
    }
    ui->lineEdit_name->setText(m_vecSwitchItem[ui->listWidget->currentRow()].vecSwitchFunName[index]);
}

void qDropDownList::on_edit_value_editingFinished()
{
    m_vecSwitchItem[ui->listWidget->currentRow()].value = ui->edit_value->text().toDouble();
}

void qDropDownList::on_btn_new_clicked()
{
    Macro lib;
    AddLib addWzrd(pwnd->macros,this);
    addWzrd.setWindowTitle(tr("��ӽű�"));
    if(addWzrd.exec() == QDialog::Accepted)
    {
        lib.libName = addWzrd.libName;
        lib.type = true;
        lib.setCompipiled(false);
        lib.setCode(SCRIPT_HEADER);
        pwnd->macros.append(lib);
        MacroEdit *dlg = new MacroEdit(lib.libName,this);
        dlg->exec();
        pwnd->is_Save=false;
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
    }
    QString libname = ui->comboBox_script->currentText();
    ui->comboBox_script->clear();
    foreach(Macro lib,pwnd->macros) //��ʼ��������
    {
        if (lib.type && lib.isCompiled())
        {
            ui->comboBox_script->addItem(lib.libName);
        }
    }
    int index = ui->comboBox_script->findText(libname);
    if(index >= 0)
    {
        ui->comboBox_script->setCurrentIndex(index);
    }
}

void qDropDownList::on_edit_const_editingFinished()
{
    int row = ui->listWidget->currentRow();
    if(m_vecSwitchItem.size() <= row)
    {
        qDebug() << "error: MFBTN on_edit_operatingAddr_editingFinished()";
        return;
    }
    int addlen = 1;
    switch(ui->comboBox_dataType->currentIndex())
    {
        case 1:
        case 3:
        case 5:
        case 6:
        {
            addlen = 2;
        }
        break;
    }
    if(!pwnd->IsAddressCheckRight(m_vecSwitchItem[row].addrConst,tr("�ֵ�ַ"),
                                  ui->edit_const,1))
    {
        ui->edit_const->setText(m_vecSwitchItem[row].addrConst.sShowAddr);
    }
    m_vecSwitchItem[row].addrConst.Length = addlen;
}

void qDropDownList::on_check_const_clicked(bool bCheck)
{
    bool bChecked = ui->check_const->isChecked();
    if(bChecked)
    {
        ui->btn_wordAddr_const->setVisible(true);
        ui->edit_const->setVisible(true);
        ui->edit_value->setVisible(false);
    }
    else
    {
        ui->btn_wordAddr_const->setVisible(false);
        ui->edit_const->setVisible(false);
        ui->edit_value->setVisible(true);
    }
    m_vecSwitchItem[ui->listWidget->currentRow()].bDynamicControl = bChecked;
}

void qDropDownList::on_btn_wordAddr_const_clicked()
{
    QString str = ui->edit_const->text();
    AddressInputDialog dlg_readaddress(m_vecSwitchItem[ui->listWidget->currentRow()].addrConst,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->edit_const->setText(m_vecSwitchItem[ui->listWidget->currentRow()].addrConst.sShowAddr);
    }
}

void qDropDownList::on_sel_pic(int index,EITEM_TYPE bLib,QString path)
{
    if(index <m_vecSwitchItem.size())
    {
        m_vecSwitchItem[index].bLib = bLib;
        m_vecSwitchItem[index].sPath = path;
    }
}
bool qDropDownList::getPicCheck()
{
    return ui->check_pic->isChecked();
}
void qDropDownList::on_check_pic_clicked(bool checked)
{
    emit picturechecked(checked);
}
