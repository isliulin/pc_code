#include "scriptfun.h"
#include "ui_scriptfun.h"
#include  "Frame\MainWindow.h"
#include "Macro\macroedit.h"

extern MainWindow  *pwnd;

scriptFun::scriptFun(int type, int index, bool bNewScreen, QWidget *parent) :QDialog(parent),ui(new Ui::scriptFun)
{
    bInit = false;
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    setFixedSize(size());
    openType  = type;//0,打开已经有的属性，1，新建属性
    iRowIndex = index;//打开第几行的

    //ui->lineEdit_condition->setText("0");

    //add by wxy
    ui->comboBox_condition->addItem(tr("0(off)"));
    ui->comboBox_condition->addItem(tr("1(on)"));
    ui->comboBox_condition->addItem(tr("2(由off到on)"));
    ui->comboBox_condition->addItem(tr("3(由on到off)"));
    ui->comboBox_condition->addItem(tr("4(位改变)"));


    ui->comboBox_type->addItem(tr("位地址"));

    ui->spinBox_count->setValue(0);

    foreach(Macro lib,pwnd->macros) //初始化库名称
    {
        if (lib.type && lib.isCompiled())
        {
            ui->comboBox_name->addItem(lib.libName);
        }
    }

    if(openType == 1)
    {
        setWindowTitle(tr("新建脚本"));

        if(ui->comboBox_name->count() > 0)
        {
            ui->comboBox_name->setCurrentIndex(0);

            
        }

        bCheckType = true;
    }
    else if(openType == 0)
    {
        int     ival  = 0;

        setWindowTitle(tr("修改脚本属性"));

        SCRIPT_PROP script = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iRowIndex);
        ival = ui->comboBox_name->findText(script.scriptName);
        ui->comboBox_name->setCurrentIndex(ival);
        

        CtrlAddr = script.scriptAddr;
        ui->spinBox_freq->setValue(script.scriptFreq);
        ui->spinBox_count->setValue(script.scriptCount);
        ui->comboBox_type->setCurrentIndex(script.scriptType);
        bCheckType = script.scriptBShow;
        ui->checkBox_type->setChecked(bCheckType);
        ui->lineEdit_addr->setText(CtrlAddr.sShowAddr);
        //ui->lineEdit_condition->setText(QString("%1").arg(script.scriptCondition));

        ui->comboBox_condition->setCurrentIndex(script.scriptCondition);
    }

    if(!ui->checkBox_type->isChecked())
    {
        ui->label_5->setEnabled(false);
        ui->lineEdit_addr->setEnabled(false);
        ui->pushButton_addr->setEnabled(false);
        ui->label_6->setEnabled(false);
        //ui->lineEdit_condition->hide();

        ui->comboBox_type->setEnabled(false);

        ui->comboBox_condition->setEnabled(false);
    }
    else
    {
        ui->label_5->setEnabled(true);
        ui->lineEdit_addr->setEnabled(true);
        ui->pushButton_addr->setEnabled(true);
        ui->label_6->setEnabled(true);
        //ui->lineEdit_condition->show();

        ui->comboBox_type->setEnabled(true);
        ui->comboBox_condition->setEnabled(true);
    }

	connect(ui->btn_new,SIGNAL(clicked()),this,SLOT(on_add_macro()));
}

scriptFun::~scriptFun()
{
    delete ui;
}

void scriptFun::on_pushButton_cancel_clicked()
{
    QDialog::close();
}

void scriptFun::on_pushButton_sure_clicked()
{
    if(!isInputRight()) return;

    //SCRIPT_PROP script;
    script.scriptName       = ui->comboBox_name->currentText();
    script.scriptFuncName   = "MACRO_MAIN";
    script.scriptFreq       = ui->spinBox_freq->value();
    script.scriptCount      = ui->spinBox_count->value();
    script.scriptBShow      = ui->checkBox_type->isChecked();
    script.scriptType       = ui->comboBox_type->currentIndex();
    if(script.scriptBShow)
    {
        script.scriptAddr       = CtrlAddr;
        //script.scriptCondition  = ui->lineEdit_condition->text().toInt();
        script.scriptCondition = ui->comboBox_condition->currentIndex();
    }

    if(1 == openType)//新建
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.append(script);
    else if(0 == openType)//属性修改
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.replace(iRowIndex, script);

    QDialog::accept();
}

void scriptFun::on_checkBox_type_clicked(bool checked)
{
    bCheckType = checked;

    if(!bCheckType)
    {
        ui->label_5->setEnabled(false);
        ui->lineEdit_addr->setEnabled(false);
        ui->pushButton_addr->setEnabled(false);
        ui->label_6->setEnabled(false);
        //ui->lineEdit_condition->hide();
        ui->comboBox_condition->setEnabled(false);
        ui->comboBox_type->setEnabled(false);
    }
    else
    {
        ui->label_5->setEnabled(true);
        ui->lineEdit_addr->setEnabled(true);
        ui->pushButton_addr->setEnabled(true);
        ui->label_6->setEnabled(true);
        //ui->lineEdit_condition->show();
        ui->comboBox_condition->setEnabled(true);
        ui->comboBox_type->setEnabled(true);
    }
}

void scriptFun::on_pushButton_addr_clicked()
{
    QString addrStr = ui->lineEdit_addr->text();
    AddressInputDialog addressintputdlg_writeaddress(CtrlAddr,addrStr,0,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->lineEdit_addr->setText(CtrlAddr.sShowAddr);
    }
}

bool scriptFun::isInputRight()
{
    QString sName = "";
    int     val   = -1;

    sName = ui->comboBox_name->currentText();
    QMessageBox msg(QMessageBox::Warning, VERSION_NAME, tr(""), 0, this, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("确定"), QMessageBox::AcceptRole);

    if(sName.isEmpty())
    {
        msg.setText(tr("脚本库名称不能为空!"));
        msg.exec();
        return false;
    }

    

    if(ui->checkBox_type->isChecked())//如果显示条件为真
    {
        if(!pwnd->IsAddressCheckRight(CtrlAddr, tr("受控地址"), ui->lineEdit_addr, 0))
        {
            ui->lineEdit_addr->setFocus();
            return false;
        }

        /*sName = ui->lineEdit_condition->text();
        val   = sName.toInt();
        if(val != 0 && val != 1 && ui->comboBox_type->currentIndex() == 0)
        {
            msg.setText(tr("位地址控件的受控条件必须为0或者1!"));
            msg.exec();
            return false;
        }*/
    }

    return true;
}
void scriptFun::on_add_macro()
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
		pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
	}
	QString libname = ui->comboBox_name->currentText();
	ui->comboBox_name->clear();
	foreach(Macro lib,pwnd->macros) //初始化库名称
	{
		if (lib.type && lib.isCompiled())
		{
			ui->comboBox_name->addItem(lib.libName);
		}
	}
	int index = ui->comboBox_name->findText(libname);
	if(index >= 0)
	{
		ui->comboBox_name->setCurrentIndex(index);
	}
}
