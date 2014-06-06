#include "switchdlg.h"
#include "ui_switchdlg.h"
#include <QTableWidget>
#include "view/switchitem.h"
#include "view/qgroupitem.h"
#include "Frame/mainwindow.h"
#include "Macro/macroedit.h"
extern MainWindow *pwnd;

SwitchDlg::SwitchDlg(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SwitchDlg)
{
    ui->setupUi(this);
    this->setFixedSize(783,513);
    setWindowTitle(tr("开关"));
    oId = -1;
    //ui->edit_id->setValidator(new QIntValidator(-1, 100000, this));

    ui->View->setScene(&scene);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    DrawItemToScene cpyfunction;
    //cpyfunction.CopyItem(&item,pItem);
    QPushButton *btn = ui->buttonBox->button(QDialogButtonBox::Ok);
    btn->setText(tr("确定"));
    btn->setDefault(true);
    btn->setFocus();

    btn = ui->buttonBox->button(QDialogButtonBox::Cancel);
    btn->setText(tr("取消"));

    btn = ui->buttonBox->button(QDialogButtonBox::Help);
    btn->setText(tr("帮助"));

    bitwidget = NULL;
    wordwidget = NULL;
    screenwidget = NULL;
    exteriorwidget = NULL;
    securitywidget = NULL;
    monitorwidget = NULL;
    funwidget = NULL;

    if(pItem && (pItem->type() == SAM_DRAW_OBJECT_GROUP))
    {
        item = dynamic_cast<QItemGroup *> (pItem)->Clone();
    }
    else
        item = NULL;

    bitwidget = new  BitWidget(this);
    ui->vLayout_function->addWidget(bitwidget);
    cWidget = bitwidget;

    monitorwidget = new Monitorwidget(this);
    ui->tabWidget->addTab(monitorwidget,tr("指示灯设置"));

    exteriorwidget = new ExteriorWidget(this);
    ui->tabWidget->addTab(exteriorwidget,tr("外观设置"));

    securitywidget = new SecurityWidget(this);
    ui->tabWidget->addTab(securitywidget,tr("权限设置"));

    foreach(Macro lib,pwnd->macros)
    {
        if (lib.type && lib.isCompiled())
        {
            ui->comboBox_macroIndex->addItem(lib.libName);
            ui->comboBox_macroIndex_up->addItem(lib.libName);
            //ui->comboBox_function->addItems(lib.functions);
        }
    }
    setBtnGroup();
    ui->radio_bit->setDisabled(true);
    connect(bitwidget,SIGNAL(AddrChanged(QString)),this,SLOT(changeAddr(QString)));
    connect(monitorwidget,SIGNAL(signalSetCheckSame(int )),this,SLOT(setMonitorAddr(int )));
    connect(monitorwidget,SIGNAL(StatusCountChanged(int)),exteriorwidget,SLOT(slotStatusCountChanged(int)));
	connect(monitorwidget,SIGNAL(signalBitLamp()),exteriorwidget,SLOT(slotBitLamp()));
    connect(ui->btn_new,SIGNAL(clicked()),this,SLOT(on_add_macro()));
    init();
}

SwitchDlg::~SwitchDlg()
{
    delete ui;
}

//将radiobutton添加到group并设置ID，连接信号槽
void SwitchDlg::setBtnGroup()
{
    ui->buttonGroup->setId(ui->radio_bit,0);
    ui->buttonGroup->setId(ui->radio_word,1);
    ui->buttonGroup->setId(ui->radio_scene,2);
    ui->buttonGroup->setId(ui->radio_function,3);
	ui->buttonGroup->setId(ui->radio_indicator,4);

    connect(ui->buttonGroup,SIGNAL(buttonClicked(int)),this,SLOT(functionChanged(int )));
}

void SwitchDlg::functionChanged(int type)
{
	for (int i=0; i<5; i++)
	{
		QAbstractButton *btn = ui->buttonGroup->button(i);
		if (i == type && btn)
		{
			btn->setEnabled(false);
			btn->setChecked(true);
		}
		else
			btn->setEnabled(true);
	}
    switch(type)
    {
    case 0:          //选择位开关
        {
            ui->check_slid->setEnabled(true);
            if(cWidget && cWidget == bitwidget)
            {
                return;
            }
            if(cWidget)
            {
                ui->vLayout_function->removeWidget(cWidget);
                cWidget->hide();
                cWidget->deleteLater();
                cWidget = NULL;
            }

            bitwidget = new BitWidget(this);
            ui->vLayout_function->addWidget(bitwidget);

            cWidget = bitwidget;

            connect(bitwidget,SIGNAL(AddrChanged(QString)),this,SLOT(changeAddr(QString)));
            //sSwitchAddr =  bitwidget->getAddr();//保存操作地址到sSwitchAddr
            changeAddr(bitwidget->getAddr());
			ui->label_type->setText(tr("开关:位开关"));
			if (securitywidget)
			{
				securitywidget->setTouchGroupEnabled(true);
			}
            ui->groupBox_macro->setDisabled(false);
        }
        break;
    case 1:          //选择字开关
        {
            ui->check_slid->setEnabled(true);
            if(cWidget && cWidget == wordwidget)
            {
                return;
            }
            if(cWidget)
            {
                ui->vLayout_function->removeWidget(cWidget);
                cWidget->hide();
                cWidget->deleteLater();
                cWidget = NULL;
            }

            wordwidget = new WordWidget(this);
            ui->vLayout_function->addWidget(wordwidget);

            cWidget = wordwidget;
            connect(wordwidget,SIGNAL(AddrChanged(QString)),this,SLOT(changeAddr(QString)));
            changeAddr(wordwidget->getAddr());
			ui->label_type->setText(tr("开关:字开关"));
			if (securitywidget)
			{
				securitywidget->setTouchGroupEnabled(true);
			}
			ui->groupBox_macro->setDisabled(false);
        }
        break;
    case 2:          //选择画面开关
        {
            ui->check_slid->setEnabled(true);
            if(cWidget && cWidget == screenwidget)
            {
                return;
            }
            if(cWidget)
            {
                ui->vLayout_function->removeWidget(cWidget);
                cWidget->hide();
                cWidget->deleteLater();
                cWidget = NULL;
            }

            screenwidget = new ScreenWidget(this);
            ui->vLayout_function->addWidget(screenwidget);

            cWidget = screenwidget;

            sSwitchAddr = "";
            if(monitorwidget)
            {
                monitorwidget->SetCheckDisabled(true);
            }
			ui->label_type->setText(tr("开关:画面开关"));
			if (securitywidget)
			{
				securitywidget->setTouchGroupEnabled(true);
			}
			ui->groupBox_macro->setDisabled(false);
        }
        break;
    case 3:          //选择功能开关
        {
            ui->check_slid->setEnabled(true);
            if(cWidget && cWidget == funwidget)
            {
                return;
            }
            if(cWidget)
            {
                ui->vLayout_function->removeWidget(cWidget);
                cWidget->hide();
                cWidget->deleteLater();                
                cWidget = NULL;
            }

            funwidget = new FunctionWdiget(this);
            ui->vLayout_function->addWidget(funwidget);

            cWidget = funwidget;

            sSwitchAddr = "";

            if(monitorwidget)
            {
                monitorwidget->SetCheckDisabled(true);
            }
            ui->label_type->setText(tr("开关:特殊功能开关"));
            if (securitywidget)
            {
                    securitywidget->setTouchGroupEnabled(true);
            }
            ui->groupBox_macro->setDisabled(false);
        }
        break;
	case 4:
		{
            if(ui->check_slid->isChecked())
            {
                ui->check_slid->setChecked(false);

                on_check_slid_clicked(false);
            }

            ui->check_slid->setEnabled(false);

			if(cWidget)
			{
				ui->vLayout_function->removeWidget(cWidget);
				cWidget->hide();
				cWidget->deleteLater();                
				cWidget = NULL;
			}
			if(monitorwidget)
			{
				monitorwidget->SetCheckDisabled(true);
				ui->tabWidget->setCurrentWidget(monitorwidget);
			}
			ui->label_type->setText(tr("指示灯"));
			if (securitywidget)
			{
				securitywidget->setTouchGroupEnabled(false);
			}
			ui->groupBox_macro->setChecked(false);
			ui->groupBox_macro->setDisabled(true);
			
		}
		break;
    default:
        break;
    }
    if(monitorwidget)
    {
        monitorwidget->setFuncType(type);
    }
}

void SwitchDlg::init()
{
    if(item == NULL)//新建一个位开关
    {
        SwitchItem *switchitem = new SwitchItem();
        switchitem->SetDefault();
        switchitem->setFlag(QGraphicsItem::ItemIsMovable, false);
        switchitem->setFlag(QGraphicsItem::ItemIsSelectable, false);

        scene.addItem(switchitem);
        item = switchitem;
        sSwitchAddr = "LB0";
        monitorwidget->init(0);
        exteriorwidget->init(switchitem,1);
        securitywidget->init(0);
        ui->spinBox->setValue(pwnd->getNewId());

    }
    else//通过双击打开场景中的开关
    {
        QGroupItem groupfunction(item);
        groupfunction.SetWidth(100);
        groupfunction.SetHeigth(100);

        scene.addItem(item);
        SwitchItem *switchitem = dynamic_cast<SwitchItem *> (item);

        InitUi();

        monitorwidget->init(switchitem);
        exteriorwidget->init(switchitem);
        securitywidget->init(switchitem);
    }

}
void SwitchDlg::InitUi()
{
    SwitchItem *switchitem = dynamic_cast<SwitchItem *> (item);

    qDebug() << "switchitem statuscount == "<< switchitem->mPro.count;
    bool bSlid = switchitem->bSlid;
    ui->check_slid->setChecked(bSlid);
    on_check_slid_clicked(bSlid);

    int id = switchitem->switchType;
    QAbstractButton *btn = ui->buttonGroup->button(id);
    if(btn)
        btn->setChecked(true);
    functionChanged(id);

    switch(id)
    {
    case BIT_SWITCH:
        {
            bitwidget->InitUi(switchitem->bitPro);
            sSwitchAddr = switchitem->bitPro.addr.sShowAddr;
        }
        break;
    case WORD_SWITCH:
        wordwidget->InitUi(switchitem->wordPro);
        sSwitchAddr = switchitem->wordPro.addr.sShowAddr;
        break;
    case SCENE_SWITCH:
        screenwidget->InitUi(switchitem->scenePro);
        break;
    case PECULIAR_SWITCH:
        funwidget->InitUi(switchitem->funPro);
        break;
    default:
        break;
    }
    //设置脚本部分
    ui->check_macro_down->setChecked(switchitem->bMacro);
    if (switchitem->bMacro)
    {
		ui->btn_new->setEnabled(true);
        ui->comboBox_macroIndex->setEnabled(true);
        int macroIndex = ui->comboBox_macroIndex->findText(switchitem->macroName);
        //if (macroIndex >=0)
        {
            ui->comboBox_macroIndex->setCurrentIndex(macroIndex);
        }
        
    }
    ui->check_macro_up->setChecked(switchitem->bMacroUp);
    if (switchitem->bMacroUp)
    {
        ui->btn_new_up->setEnabled(true);
        ui->comboBox_macroIndex_up->setEnabled(true);
        int macroIndex = ui->comboBox_macroIndex_up->findText(switchitem->macroNameUp);
        //if (macroIndex >=0)
        {
            ui->comboBox_macroIndex_up->setCurrentIndex(macroIndex);
        }

    }

    oId = switchitem->id();
    ui->spinBox->setValue(oId);
}

//点击确定 保存所有属性到item
void SwitchDlg::accept()
{
    SwitchItem *switchitem = dynamic_cast<SwitchItem *> (item);
    if(switchitem)
    {
        switch(ui->buttonGroup->checkedId())
        {
        case 0:
            {
                if(bitwidget && bitwidget->Save())
                    switchitem->SaveBitPro(bitwidget->bitproperty);
                else
                    return;
            }
            break;
        case 1:
            {
                if(wordwidget && wordwidget->Save())
                    switchitem->SaveWordPro(wordwidget->wordproperty);
                else
                    return;
            }
            break;
        case 2:
            {
                if(screenwidget && screenwidget->Save())
                    switchitem->SaveScenePro(screenwidget->sceneproperty);
                else
                    return;
            }
            break;
        case 3:
            {
                if(funwidget && funwidget->Save())
                    switchitem->SaveFunctionPro(funwidget->funproperty);
                else
                    return;
            }
            break;
        case 4:
            {
                switchitem->SaveIndicatorPro();
                break;
            }
        }
    }
    switchitem->bSlid  = ui->check_slid->isChecked();
    switchitem->bMacro = ui->check_macro_down->isChecked();
    if(switchitem->bMacro)
    {
        switchitem->macroName = ui->comboBox_macroIndex->currentText();
        switchitem->functionName = "MACRO_MAIN";
    }
    switchitem->bMacroUp = ui->check_macro_up->isChecked();
    if(switchitem->bMacroUp)
    {
        switchitem->macroNameUp = ui->comboBox_macroIndex_up->currentText();
        //switchitem->functionName = "MACRO_MAIN";
    }

    if(monitorwidget && monitorwidget->Save())
    {
        switchitem->SaveMonitorPage(monitorwidget->mProperty);
    }
    else
    {
        return;
    }

    if(exteriorwidget && exteriorwidget->Save())
    {
        switchitem->SaveExteriorPage(switchitem->mPro.count,
                                     exteriorwidget->statusText,exteriorwidget->statusPic);
		switchitem->curSta = exteriorwidget->currentState();
    }
    else
    {
        return;
    }
    if(securitywidget && securitywidget->Save())
    {
        switchitem->SaveSecurityPro(&(securitywidget->sproperty));
    }
    else
    {
        return;
    }
    switchitem->setId(ui->spinBox->value());
    if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox->setFocus();
        return ;
    }

    QDialog::accept();
}

void SwitchDlg::changeAddr(QString string)
{
    sSwitchAddr = string;
    if(monitorwidget)
    {
		int id = ui->buttonGroup->checkedId();
		if (id <= 1)
		{
			monitorwidget->setAddrType(id);
		}
        monitorwidget->changeAddr(string);
        monitorwidget->SetCheckDisabled(false);
    }
}
void SwitchDlg::setMonitorAddr(int index)
{

	
    if(monitorwidget)
    {
		int id = ui->buttonGroup->checkedId();
		if (id <= 1)
		{
			monitorwidget->setAddrType(id);
		}
		
        monitorwidget->changeAddr(sSwitchAddr);
    }
}


void SwitchDlg::on_buttonBox_helpRequested()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_SWITCH);
}

void SwitchDlg::on_check_slid_clicked(bool checked)
{
    if(monitorwidget)
    {
        monitorwidget->setSlid(!checked);
    }
}
void SwitchDlg::on_add_macro()
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
	QString libname = ui->comboBox_macroIndex->currentText();
	ui->comboBox_macroIndex->clear();
	foreach(Macro lib,pwnd->macros) //初始化库名称
	{
		if (lib.type && lib.isCompiled())
		{
			ui->comboBox_macroIndex->addItem(lib.libName);
		}
	}
	int index = ui->comboBox_macroIndex->findText(libname);
	if(index >= 0)
	{
		ui->comboBox_macroIndex->setCurrentIndex(index);
	}
}

void SwitchDlg::on_btn_new_up_clicked()
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
    QString libname = ui->comboBox_macroIndex_up->currentText();
    ui->comboBox_macroIndex_up->clear();
    foreach(Macro lib,pwnd->macros) //初始化库名称
    {
        if (lib.type && lib.isCompiled())
        {
            ui->comboBox_macroIndex_up->addItem(lib.libName);
        }
    }
    int index = ui->comboBox_macroIndex_up->findText(libname);
    if(index >= 0)
    {
        ui->comboBox_macroIndex_up->setCurrentIndex(index);
    }
}

void SwitchDlg::on_check_macro_down_clicked(bool checked)
{
    ui->btn_new->setEnabled(checked);
    ui->comboBox_macroIndex->setEnabled(checked);
}

void SwitchDlg::on_check_macro_up_clicked(bool checked)
{
    ui->btn_new_up->setEnabled(checked);
    ui->comboBox_macroIndex_up->setEnabled(checked);
}
