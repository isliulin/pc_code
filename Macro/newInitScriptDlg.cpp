#include "newInitScriptDlg.h"
#include "ui_newInitScriptDlg.h"
#include  "Frame\MainWindow.h"
#include "Macro/macroedit.h"
extern MainWindow  *pwnd;

newInitScriptDlg::newInitScriptDlg(int Type,int iIndex,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newInitScriptDlg)
{
    ui->setupUi(this);
    setFixedSize(this->size());

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    iOpenType = Type; //1-标示新建，2-标示属性修改
    iRowIndex = iIndex; //修改属性下标，-1为新建，否则为修改下标
    initDlgParament();
}

newInitScriptDlg::~newInitScriptDlg()
{
    delete ui;
}

void newInitScriptDlg::initDlgParament()
{
    binitFlag = false; //初始化标志
    foreach(Macro lib,pwnd->macros) //初始化库名称
    {
            if (lib.type && lib.isCompiled())
            {
                    ui->libcmb->addItem(lib.libName);
            }
    }
    binitFlag = true; //初始化标志

    if(iOpenType == 1)
    {
        setWindowTitle(tr("新建初始化脚本"));
        if(ui->libcmb->count() > 0 )
        {
            ui->libcmb->setCurrentIndex(0);

        }
    }
    else if(iOpenType == 2)
    {
        setWindowTitle(tr("初始化脚本属性修改"));
        int ival = 0;
        INIT_MARO_PROP odata = pwnd->m_pSamSysParame->m_qvcInitMaroProp.at(iRowIndex);
        ival = ui->libcmb->findText(odata.sLibName);
        ui->libcmb->setCurrentIndex(ival);

    }
}


void newInitScriptDlg::on_Ok_clicked()
{
    if( !isInputRight() )
        return;

    INIT_MARO_PROP odata;
    odata.sLibName = ui->libcmb->currentText();
    if(iOpenType == 1) //新建
    {
         pwnd->m_pSamSysParame->m_qvcInitMaroProp.append(odata);
    }
    else if(iOpenType == 2)//属性修改
    {
         pwnd->m_pSamSysParame->m_qvcInitMaroProp.replace(iRowIndex,odata);
    }
    QDialog::accept();
}

bool newInitScriptDlg::isInputRight()
{
    QString sName = "";
    sName = ui->libcmb->currentText();
    QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr(""),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("确定"),QMessageBox::AcceptRole);

    if(sName.isEmpty())
    {
        msg.setText(tr("脚本库名称不能为空!"));
        msg.exec();
        return false;
    }

     return true;
}

void newInitScriptDlg::on_Cancel_clicked()
{
    QDialog::close();
}

void newInitScriptDlg::on_btn_new_clicked()
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
    QString libname = ui->libcmb->currentText();
    ui->libcmb->clear();
    foreach(Macro lib,pwnd->macros) //初始化库名称
    {
            if (lib.type && lib.isCompiled())
            {
                    ui->libcmb->addItem(lib.libName);
            }
    }
    int index = ui->libcmb->findText(libname);
    if(index >= 0)
    {
        ui->libcmb->setCurrentIndex(index);
    }
}
