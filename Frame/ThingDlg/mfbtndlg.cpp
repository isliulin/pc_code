#include "mfbtndlg.h"
#include "ui_mfbtndlg.h"
#include "Frame/mainwindow.h"
#include "Frame/ThingDlg/switch/exteriorwidget.h"
#include "Frame/ThingDlg/switch/securitywidget.h"
#include "Frame/ThingDlg/switch/monitorwidget.h"
#include "Macro/macroedit.h"

extern MainWindow *pwnd;
MFBtnDlg::MFBtnDlg(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MFBtnDlg)
{
    monitorwidget = NULL;

    ui->setupUi(this);
    oId = -1;
    ui->edit_const->setText("LW0");
    ui->edit_const->setVisible(false);
    ui->btn_wordAddr_const->setVisible(false);

    setWindowTitle(tr("多功能按钮"));
    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    ui->view->setScene(&scene);
    monitorwidget = new Monitorwidget(this);
    ui->tabWidget->addTab(monitorwidget, tr("指示灯设置"));
    monitorwidget->setCheckSameVisiable(false);

    exteriorwidget = new ExteriorWidget(this);
    ui->tabWidget->addTab(exteriorwidget,tr("外观设置"));

    securitywidget = new SecurityWidget(this);
    ui->tabWidget->addTab(securitywidget,tr("权限设置"));

    //connect(monitorwidget,SIGNAL(signalSetCheckSame(int )),this,SLOT(setMonitorAddr(int )));
    connect(monitorwidget,SIGNAL(StatusCountChanged(int)),exteriorwidget,SLOT(slotStatusCountChanged(int)));
    connect(monitorwidget,SIGNAL(signalBitLamp()),exteriorwidget,SLOT(slotBitLamp()));

    QPushButton *btn = ui->buttonBox->button(QDialogButtonBox::Ok);
    btn->setText(tr("确定"));

    btn = ui->buttonBox->button(QDialogButtonBox::Cancel);
    btn->setText(tr("取消"));

    btn = ui->buttonBox->button(QDialogButtonBox::Help);
    btn->setText(tr("帮助"));

    ui->label_10->setEnabled(false);
    ui->comboBox_executeType->setEnabled(false);

    //connect(ui->combo_macroIndex,SIGNAL(currentIndexChanged(QString)),this,SLOT(libraryChanged(QString)));

    foreach(Macro lib,pwnd->macros)
    {
        if (lib.type && lib.isCompiled())
        {
            ui->combo_macroIndex->addItem(lib.libName);
            //ui->combo_function->addItems(lib.functions);
        }
    }

	QGraphicsItem *m_Item = NULL;
	if(pItem && (pItem->type() == SAM_DRAW_OBJECT_GROUP))
	{
		m_Item = dynamic_cast<QItemGroup *> (pItem)->Clone();
	}
	else
		m_Item = NULL;
    Init(m_Item);
}

MFBtnDlg::~MFBtnDlg()
{
    delete ui;
}
void MFBtnDlg::Init(QGraphicsItem *pItem)
{
    item = dynamic_cast<MfBtnItem*>(pItem);
    if(item)//打开已有的item
    {
		QGroupItem groupfunction(item);
		groupfunction.SetWidth(100);
		groupfunction.SetHeigth(100);

        m_vecSwitchItem = item->m_vecSwitchItem;
        isUseScript     = item->isUseScript;
        macroName       = item->macroName;
        functionName    = item->functionName;

        scene.addItem(item);
        securitywidget->init(item);
        exteriorwidget->init(item);
        monitorwidget->init(item);
        oId = item->id();
        ui->spinBox->setValue(oId);
    }
    else//新建item
    {
        item = new MfBtnItem();
        item->SetDefault();
        item->isUseScript     = false;
        SwitchInfo info;
        info.switchType     = 1;//默认位开关
        info.addrBit.sShowAddr = "LB0";

        info.operTypeB = (BIT_OPER_TYPE)1;
        info.addrConst.sShowAddr = "LW0";
        info.bDynamicControl = false;
        info.bDown = false;
        m_vecSwitchItem.push_back(info);
        scene.addItem(item);
        exteriorwidget->init(item,1);
        securitywidget->init(0);
        monitorwidget->init(0);
        ui->spinBox->setValue(pwnd->getNewId());
    }
    foreach(SwitchInfo switchItem,m_vecSwitchItem)
    {
        switch(switchItem.switchType)
        {
        case 1:
            ui->listWidget->addItem(tr("位操作"));
            break;
        case 2:
            ui->listWidget->addItem(tr("字操作"));
            break;
        case 3:
            ui->listWidget->addItem(tr("画面切换"));
            break;
        }
    }
    if(ui->listWidget->count()>0)
        ui->listWidget->setCurrentRow(0);

    ui->group_macro->setChecked(item->isUseScript);
    if (item->isUseScript)
    {
        ui->label_5->setEnabled(true);
        ui->btn_new->setEnabled(true);
        //ui->combo_function->setEnabled(true);
        ui->combo_macroIndex->setEnabled(true);
        int macroIndex = ui->combo_macroIndex->findText(item->macroName);
        //if (macroIndex >=0)
        {
            ui->combo_macroIndex->setCurrentIndex(macroIndex);
        }
    }
}

//添加位操作
void MFBtnDlg::on_pushButton_bit_clicked()
{

    if(m_vecSwitchItem.size() >= 16)
    {
        QMessageBox::about(this, tr(""), tr("只能添加16个操作命令"));
        return;
    }
    foreach(SwitchInfo info,m_vecSwitchItem)
    {
        if(info.switchType == 3)//画面操作命令只能是最后一个命令
        {
            QMessageBox::about(this, tr(""), tr("画面操作命令只能是最后一个命令"));
            return;
        }
    }

    ui->groupBox->setEnabled(true);
    ui->groupBox_2->setEnabled(false);
    ui->groupBox_3->setEnabled(false);

    SwitchInfo info;

    info.switchType     = 1;
    //位开关属性
    info.addrBit.sShowAddr = ui->edit_operatingAddr->text();
    info.operTypeB = (BIT_OPER_TYPE)1;
    info.addrConst.sShowAddr = "LW0";
    info.bDynamicControl = false;
    info.bDown = false;
    m_vecSwitchItem.push_back(info);

    ui->listWidget->addItem(tr("位操作"));
    ui->listWidget->setCurrentRow(m_vecSwitchItem.size() - 1);

    if(m_vecSwitchItem.size() == 1)
    {
        ui->pushButton_del->setEnabled(false);
    }
    else
    {
        ui->pushButton_del->setEnabled(true);
    }
}

//添加字操作
void MFBtnDlg::on_pushButton_word_clicked()
{
    if(m_vecSwitchItem.size() >= 16)
    {
        QMessageBox::about(this, tr(""), tr("只能添加16个操作命令"));
        return;
    }
    foreach(SwitchInfo info,m_vecSwitchItem)
    {
        if(info.switchType == 3)//画面操作命令只能是最后一个命令
        {
            QMessageBox::about(this, tr(""), tr("画面操作命令只能是最后一个命令"));
            return;
        }
    }

    ui->groupBox->setEnabled(false);
    ui->groupBox_2->setEnabled(true);
    ui->groupBox_3->setEnabled(false);

    SwitchInfo info;

    info.switchType     = 2;
    //字开关属性
    Keyboard key;
    pwnd->IsAddressCheckRight(key,tr("字地址"),ui->edit_operatingAddr_2,1);
    info.addrWord = key;

    info.bDynamicControl = false;
    ui->edit_const->setText("LW0");
    Keyboard keyConst;
    pwnd->IsAddressCheckRight(keyConst,tr("字地址"),ui->edit_const,1);
    info.addrConst = keyConst;

    info.operTypeW = (WORD_OPER_TYPE)1;
    info.dataType = (DATA_TYPE)3;
    info.value = ui->edit_value->text().toDouble();
    info.bDown = false;
    m_vecSwitchItem.push_back(info);

    ui->listWidget->addItem(tr("字操作"));
    ui->listWidget->setCurrentRow(m_vecSwitchItem.size() - 1);

    if(m_vecSwitchItem.size() == 1)
    {
        ui->pushButton_del->setEnabled(false);
    }
    else
    {
        ui->pushButton_del->setEnabled(true);
    }
}

//添加画面操作
void MFBtnDlg::on_pushButton_pic_clicked()
{
    if(m_vecSwitchItem.size() >= 16)
    {
        QMessageBox::about(this, tr(""), tr("只能添加16个操作命令"));
        return;
    }
    foreach(SwitchInfo info,m_vecSwitchItem)
    {
        if(info.switchType == 3)//如果已经有画面操作，则不能继续添加
        {
            QMessageBox::about(this, tr(""), tr("只能添加一项画面操作"));
            return;
        }
    }

    ui->groupBox->setEnabled(false);
    ui->groupBox_2->setEnabled(false);
    ui->groupBox_3->setEnabled(true);

    ui->comboBox_ScreenIndex->clear();
    int screenNum = pwnd->pSceneSheet.size();//总的画面数
    QString str;
    for(int i = 0; i < screenNum; i++)
    {
        str = pwnd->pSceneSheet[i]->sNewScreenName;
        ui->comboBox_ScreenIndex->addItem(str);
    }
    ui->comboBox_ScreenIndex->setCurrentIndex(0);

    SwitchInfo info;

    info.switchType     = 3;
    //画面切换属性
    info.operType = (SCENE_OPER_TYPE)1;
    //info.nSceneType = 0;
    info.sceneName = ui->comboBox_ScreenIndex->currentText();
    info.bLogout = ui->checkBox->isChecked();        // 切换画面是否注销
    info.bDown = false;
    m_vecSwitchItem.push_back(info);

    ui->listWidget->addItem(tr("画面切换"));
    ui->listWidget->setCurrentRow(m_vecSwitchItem.size() - 1);

    if(m_vecSwitchItem.size() == 1)
    {
        ui->pushButton_del->setEnabled(false);
    }
    else
    {
        ui->pushButton_del->setEnabled(true);
    }

    ui->label_16->hide();
    ui->comboBox_ScreenIndex->hide();
}

//删除项
void MFBtnDlg::on_pushButton_del_clicked()
{
    if(m_vecSwitchItem.size() <= 1)
    {
        return;
    }

    int curRow =  ui->listWidget->currentRow();

    QListWidgetItem *item = ui->listWidget->currentItem();
    ui->listWidget->removeItemWidget(item);
    delete item;

    m_vecSwitchItem.remove(curRow);

    if(m_vecSwitchItem.size() == 1)
    {
        ui->pushButton_del->setEnabled(false);
    }
    else
    {
        ui->pushButton_del->setEnabled(true);
    }
}

//选择位地址
void MFBtnDlg::on_btn_bitAddr_clicked()
{
    int row = ui->listWidget->currentRow();
    if(m_vecSwitchItem.size() <= row)
    {
        qDebug() << "error: MFBTN on_btn_bitAddr_clicked()";
        return;
    }

    QString str = ui->edit_operatingAddr->text();
    AddressInputDialog dlg_readaddress(m_vecSwitchItem[row].addrBit,str,0,this);
    if(dlg_readaddress.exec())
    {
        ui->edit_operatingAddr->setText(m_vecSwitchItem[row].addrBit.sShowAddr);
    }
}

//选择字地址
void MFBtnDlg::on_btn_wordAddr_clicked()
{
    int row = ui->listWidget->currentRow();
    if(m_vecSwitchItem.size() <= row)
    {
        qDebug() << "error: MFBTN on_btn_wordAddr_clicked()";
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
    QString str = ui->edit_operatingAddr_2->text();
    AddressInputDialog dlg_readaddress(m_vecSwitchItem[row].addrWord,str,1,this);
    if(dlg_readaddress.exec())
    {
        m_vecSwitchItem[row].addrWord.Length = addlen;
        ui->edit_operatingAddr_2->setText(m_vecSwitchItem[row].addrWord.sShowAddr);
    }
}

//脚本组
void MFBtnDlg::on_group_macro_clicked(bool checked)
{
    ui->label_5->setEnabled(checked);
    ui->btn_new->setEnabled(checked);
    //ui->combo_function->setEnabled(checked);
    ui->combo_macroIndex->setEnabled(checked);
}

void MFBtnDlg::on_buttonBox_accepted()
{
    item->m_vecSwitchItem = m_vecSwitchItem;
    item->isUseScript     = ui->group_macro->isChecked();
    if(item->isUseScript)
    {
        item->macroName    = ui->combo_macroIndex->currentText();
        item->functionName = "MACRO_MAIN";
    }
    if(exteriorwidget && exteriorwidget->Save()/* && exteriorwidget->statusText.size()==1 */)
    {
        //item->textPros = exteriorwidget->statusText.first();
        //item->picPro   = exteriorwidget->statusPic.first();
        item->statusText  = exteriorwidget->statusText;
        item->statusPic = exteriorwidget->statusPic;
    }
    else
    {
        return;
    }
    if(securitywidget && securitywidget->Save())
    {
        item->SaveSecurityPro(&(securitywidget->sproperty));
    }
    else
    {
        return;
    }
    if(monitorwidget && monitorwidget->Save())
    {
        item->SaveMonitorPage(monitorwidget->mProperty);
    }
    else
    {
        return;
    }
    item->setId(ui->spinBox->value());
    if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox->setFocus();
        return ;
    }

    accept();
}

void MFBtnDlg::on_buttonBox_rejected()
{
    reject();
}


//帮助
void MFBtnDlg::on_buttonBox_helpRequested()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_MFBTN);
}

//当前操作改变
void MFBtnDlg::on_listWidget_currentRowChanged(int currentRow)
{
    if(m_vecSwitchItem.size() <= currentRow)
    {
        qDebug() << "error: MFBTN on_listWidget_currentRowChanged()";
        return;
    }
    SwitchInfo info = m_vecSwitchItem[currentRow];
    switch(info.switchType)
    {
    case 1://位操作
        ui->groupBox->setEnabled(true);
        ui->groupBox_2->setEnabled(false);
        ui->groupBox_3->setEnabled(false);

        ui->edit_operatingAddr->setText(info.addrBit.sShowAddr);
        ui->comboBox_operateType->setCurrentIndex((int)info.operTypeB - 1);
        break;
    case 2://字操作
        ui->groupBox->setEnabled(false);
        ui->groupBox_2->setEnabled(true);
        ui->groupBox_3->setEnabled(false);

        ui->edit_operatingAddr_2->setText(info.addrWord.sShowAddr);
        ui->comboBox_operateType_2->setCurrentIndex((int)info.operTypeW - 1);
        ui->comboBox_dataType->setCurrentIndex((int)info.dataType - 1);

        ui->edit_value->setText(QString::number(info.value,'g',10));

        ui->check_const->setChecked(info.bDynamicControl);
        ui->edit_const->setText(info.addrConst.sShowAddr);
        if(info.bDynamicControl)
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
        break;
    case 3://画面切换
        ui->groupBox->setEnabled(false);
        ui->groupBox_2->setEnabled(false);
        ui->groupBox_3->setEnabled(true);

        ui->comboBox_operType->setCurrentIndex((int)info.operType - 1);
        qDebug() << tr("画面名称: ")<< info.sceneName;
		int screenindex = ui->comboBox_ScreenIndex->findText(info.sceneName); 
		ui->comboBox_ScreenIndex->setCurrentIndex(screenindex);

        if(0 == ui->comboBox_operType->currentIndex()
            || 3 == ui->comboBox_operType->currentIndex()
            || 4 == ui->comboBox_operType->currentIndex())
        {
            ui->label_16->hide();
            ui->comboBox_ScreenIndex->hide();
        }
        else
        {
            ui->label_16->show();
            ui->comboBox_ScreenIndex->show();
        }

        ui->checkBox->setChecked(info.bLogout);
        break;
    }
}

//输入位地址
void MFBtnDlg::on_edit_operatingAddr_editingFinished()
{
    int row = ui->listWidget->currentRow();
    if(m_vecSwitchItem.size() <= row)
    {
        qDebug() << "error: MFBTN on_edit_operatingAddr_editingFinished()";
        return;
    }

    if(!pwnd->IsAddressCheckRight(m_vecSwitchItem[row].addrBit,tr("位地址"),
                                  ui->edit_operatingAddr,0))
    {
        ui->edit_operatingAddr->setText(m_vecSwitchItem[row].addrBit.sShowAddr);
    }
}

//位操作类型改变
void MFBtnDlg::on_comboBox_operateType_currentIndexChanged(int index)
{
    int row = ui->listWidget->currentRow();
    if(m_vecSwitchItem.size() <= row)
    {
        qDebug() << "error: MFBTN on_comboBox_operateType_currentIndexChanged()";
        return;
    }
    m_vecSwitchItem[row].operTypeB = (BIT_OPER_TYPE)(index + 1);

    ui->label_10->setEnabled(index == 3);
    ui->comboBox_executeType->setEnabled(index == 3);
    if(index == 3)
    {
        ui->comboBox_executeType->setCurrentIndex(m_vecSwitchItem[row].bDown);
    }
}

//位操作 点动 （按下为0或1）
void MFBtnDlg::on_comboBox_executeType_currentIndexChanged(int index)
{
    int row = ui->listWidget->currentRow();
    if(m_vecSwitchItem.size() <= row)
    {
        qDebug() << "error: MFBTN on_comboBox_executeType_currentIndexChanged()";
        return;
    }
    m_vecSwitchItem[row].bDown = index;
}

//输入字地址
void MFBtnDlg::on_edit_operatingAddr_2_editingFinished()
{
    int row = ui->listWidget->currentRow();
    if(m_vecSwitchItem.size() <= row)
    {
        qDebug() << "error: MFBTN on_edit_operatingAddr_2_editingFinished()";
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
    if(!pwnd->IsAddressCheckRight(m_vecSwitchItem[row].addrWord,tr("字地址"),
                                  ui->edit_operatingAddr_2,1))
    {
        ui->edit_operatingAddr_2->setText(m_vecSwitchItem[row].addrWord.sShowAddr);
    }
    m_vecSwitchItem[row].addrWord.Length = addlen;
}
//字操作 数据类型改变
void MFBtnDlg::on_comboBox_dataType_currentIndexChanged(int index)
{
    double  nMax   = 2147482647L;
    double  nMin   = -2147482648L;
    int     decLen = 0;
    int addlen = 1;
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
            nMax = 2147482647L;
            nMin = -2147482648L;
            decLen = 0;
            addlen = 2;
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
            addlen = 2;
        }
        break;

        case 6://32位浮点数
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

    int row = ui->listWidget->currentRow();
    if(m_vecSwitchItem.size() <= row)
    {
        qDebug() << "error: MFBTN on_comboBox_dataType_currentIndexChanged()";
        return;
    }

    m_vecSwitchItem[row].dataType = (DATA_TYPE)(index + 1);
    m_vecSwitchItem[row].addrWord.Length = addlen;
    m_vecSwitchItem[row].addrConst.Length = addlen;
}

//字操作 操作类型改变
void MFBtnDlg::on_comboBox_operateType_2_currentIndexChanged(int index)
{
    int row = ui->listWidget->currentRow();
    if(m_vecSwitchItem.size() <= row)
    {
        qDebug() << "error: MFBTN on_comboBox_operateType_2_currentIndexChanged()";
        return;
    }
    m_vecSwitchItem[row].operTypeW = (WORD_OPER_TYPE)(index + 1);
}
//字操作 输入操作值
void MFBtnDlg::on_edit_value_editingFinished()
{
    int row = ui->listWidget->currentRow();
    if(m_vecSwitchItem.size() <= row)
    {
        qDebug() << "error: MFBTN on_edit_value_editingFinished()";
        return;
    }
    m_vecSwitchItem[row].value = ui->edit_value->text().toDouble();
}
//画面操作 操作类型改变
void MFBtnDlg::on_comboBox_operType_currentIndexChanged(int index)
{
    if(0 == index || 3 == index || 4 == index)
    {
        ui->label_16->hide();
        ui->comboBox_ScreenIndex->hide();
    }
    else
    {
        ui->label_16->show();
        ui->comboBox_ScreenIndex->show();
    }

    if(0 == index || 1 == index)
    {
        ui->comboBox_ScreenIndex->clear();
        //执行这句以后跳到comboBox_ScreenIndex
        int screenNum = pwnd->pSceneSheet.size();//总的画面数
        for(int i = 0; i < screenNum; i++)
        {
            if(pwnd->pSceneSheet[i]->nIsSceneOrWindow == 0)
            {
                QString str = pwnd->pSceneSheet[i]->sNewScreenName;
                ui->comboBox_ScreenIndex->addItem(str);
            }

        }
    }
    else if(2 == index)
    {
        ui->comboBox_ScreenIndex->clear();
        int windowNum = pwnd->pSceneSheet.size();//窗口数
        for(int i = 0; i < windowNum; i++)
        {
            if(pwnd->pSceneSheet[i]->nIsSceneOrWindow == 1)
            {
                QString str = pwnd->pSceneSheet[i]->sNewScreenName;
                ui->comboBox_ScreenIndex->addItem(str);
            }
        }
    }

    int row = ui->listWidget->currentRow();
    if(m_vecSwitchItem.size() <= row)
    {
        qDebug() << "error: MFBTN on_comboBox_operType_currentIndexChanged()";
        return;
    }
    m_vecSwitchItem[row].operType = (SCENE_OPER_TYPE)(index + 1);
}
//画面操作 选择画面序号
void MFBtnDlg::on_comboBox_ScreenIndex_currentIndexChanged(int index)
{
    int row = ui->listWidget->currentRow();
    if(m_vecSwitchItem.size() <= row)
    {
        qDebug() << "error: MFBTN on_comboBox_ScreenIndex_currentIndexChanged()";
        return;
    }
    m_vecSwitchItem[row].sceneName  = ui->comboBox_ScreenIndex->currentText();
}
//画面操作 是否注销用户


void MFBtnDlg::on_checkBox_clicked(bool checked)
{
    int row = ui->listWidget->currentRow();
    if(m_vecSwitchItem.size() <= row)
    {
        qDebug() << "error: MFBTN on_checkBox_clicked()";
        return;
    }
    m_vecSwitchItem[row].bLogout = checked;
}

void MFBtnDlg::on_btn_new_clicked()
{
    Macro lib;
    AddLib addWzrd(pwnd->macros,this);
    addWzrd.setWindowTitle(tr("添加脚本"));
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
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
    }
    QString libname = ui->combo_macroIndex->currentText();
    ui->combo_macroIndex->clear();
    foreach(Macro lib,pwnd->macros) //初始化库名称
    {
        if (lib.type && lib.isCompiled())
        {
            ui->combo_macroIndex->addItem(lib.libName);
        }
    }
    int index = ui->combo_macroIndex->findText(libname);
    if(index >= 0)
    {
        ui->combo_macroIndex->setCurrentIndex(index);
    }
}

void MFBtnDlg::on_edit_const_editingFinished()
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
    if(!pwnd->IsAddressCheckRight(m_vecSwitchItem[row].addrConst,tr("字地址"),
                                  ui->edit_const,1))
    {
        ui->edit_const->setText(m_vecSwitchItem[row].addrConst.sShowAddr);
    }
    m_vecSwitchItem[row].addrConst.Length = addlen;
}

void MFBtnDlg::on_check_const_clicked(bool bCheck)
{
    bool bChecked = ui->check_const->isChecked();
    if(bChecked)
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
    m_vecSwitchItem[ui->listWidget->currentRow()].bDynamicControl = bChecked;
}

void MFBtnDlg::on_btn_wordAddr_const_clicked()
{
    int row = ui->listWidget->currentRow();
    if(m_vecSwitchItem.size() <= row)
    {
        qDebug() << "error: MFBTN on_btn_wordAddr_clicked()";
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
    QString str = ui->edit_const->text();
    AddressInputDialog dlg_readaddress(m_vecSwitchItem[row].addrConst,str,1,this);
    if(dlg_readaddress.exec())
    {
        m_vecSwitchItem[row].addrConst.Length = addlen;
        ui->edit_const->setText(m_vecSwitchItem[row].addrConst.sShowAddr);
    }
}
