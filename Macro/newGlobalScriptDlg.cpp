#include "newGlobalScriptDlg.h"
#include "ui_newGlobalScriptDlg.h"
#include  "Frame\MainWindow.h"
#include "Macro/macroedit.h"
extern MainWindow  *pwnd;

newGlobalScriptDlg::newGlobalScriptDlg(int Type,int iIndex,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newGlobalScriptDlg)
{
    ui->setupUi(this);
    this->setFixedSize(334,301);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    iOpenType = Type; //1-��ʾ�½���2-��ʾ�����޸�
    iRowIndex = iIndex; //�޸������±꣬-1Ϊ�½�������Ϊ�޸��±�

    //add by wxy
    ui->comboBox_condition->addItem(tr("0(off)"));
    ui->comboBox_condition->addItem(tr("1(on)"));
    ui->comboBox_condition->addItem(tr("2(��off��on)"));
    ui->comboBox_condition->addItem(tr("3(��on��off)"));
    ui->comboBox_condition->addItem(tr("4(λ�ı�)"));

    initDlgParament();
}

newGlobalScriptDlg::~newGlobalScriptDlg()
{
    delete ui;
}

void newGlobalScriptDlg::initDlgParament()
{
    binitFlag = false; //��ʼ����־
    foreach(Macro lib,pwnd->macros) //��ʼ��������
    {
            if (lib.type && lib.isCompiled())
            {
                    ui->libcmb->addItem(lib.libName);
            }
    }
    binitFlag = true; //��ʼ����־

    if(iOpenType == 1)
    {
        setWindowTitle(tr("�½�ȫ�ֽű�"));
        if(ui->libcmb->count() > 0 )
        {
            ui->libcmb->setCurrentIndex(0);
        }
        CtrlAddr.sShowAddr = "LB0";
        CtrlAddr.sPlcAddrValue = "0";
        CtrlAddr.sPlcRegTypeStr = "LB";
        CtrlAddr.nConnectType = 0;
        CtrlAddr.nAddrType = 0;
        CtrlAddr.nPlcRegTypeIndex = 0;
        CtrlAddr.nPlcStationIndex = 100;

        on_bctrlcheck_clicked(false);
        ui->m_ScriptCount->setValue(0);
    }
    else if(iOpenType == 2)
    {
        setWindowTitle(tr("ȫ�ֽű������޸�"));
        //QString sName = "";
        int ival = 0;
        GLOBAL_MARO_PROP odata = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp.at(iRowIndex);
        ival = ui->libcmb->findText(odata.sLibName);
        ui->libcmb->setCurrentIndex(ival);

        ui->bctrlcheck->setChecked(odata.bIfCtrl);
        on_bctrlcheck_clicked(odata.bIfCtrl);

        CtrlAddr = odata.mCtlAddr;
        ui->ratespin->setValue(odata.iRunRate);
        ui->typecmb->setCurrentIndex(odata.iCtrlType);
        ui->m_ScriptCount->setValue(odata.iScriptCount);

        ui->addredit->setText(CtrlAddr.sShowAddr);
        //sName = QString("%1").arg(odata.iValue);
        //ui->valueedit->setText(sName);
        ui->comboBox_condition->setCurrentIndex(odata.iValue);
    }
}



void newGlobalScriptDlg::on_addrbtn_clicked()//�ܿص�ַ
{
    QString addrStr = ui->addredit->text();
    AddressInputDialog addressintputdlg_writeaddress(CtrlAddr,addrStr,0,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->addredit->setText(CtrlAddr.sShowAddr);
    }

}

void newGlobalScriptDlg::on_Ok_clicked()
{
    if( !isInputRight() )
        return;

    /*if(ui->bctrlcheck->isChecked())
    {
        QString str0 = ui->valueedit->text();
        if(str0 != "0" && str0 != "1")
        {
            QMessageBox::about(this, tr("����"), tr("ִ������ֻ����0����1"));
            return;
        }
    }*/

    GLOBAL_MARO_PROP odata;
    odata.sLibName = ui->libcmb->currentText();
    odata.sFucName = "MACRO_MAIN";
    odata.iRunRate = ui->ratespin->value();
    odata.iScriptCount = ui->m_ScriptCount->value();
    odata.iCtrlType = ui->typecmb->currentIndex();
    //odata.mCtlAddr = CtrlAddr;
    //odata.iValue = ui->valueedit->text().toInt();
    odata.bIfCtrl = ui->bctrlcheck->isChecked();

    if(odata.bIfCtrl)
    {
        odata.mCtlAddr = CtrlAddr;
        //odata.iValue = ui->valueedit->text().toInt();
        odata.iValue = ui->comboBox_condition->currentIndex();
    }
    /*if(odata.iValue != 0 && odata.iValue != 1)
    {
        odata.iValue = 0;
    }*/

    if(iOpenType == 1) //�½�
    {
         pwnd->m_pSamSysParame->m_qvcGlobalMaroProp.append(odata);
    }
    else if(iOpenType == 2)//�����޸�
    {
         pwnd->m_pSamSysParame->m_qvcGlobalMaroProp.replace(iRowIndex,odata);
    }

    QDialog::accept();
}

bool newGlobalScriptDlg::isInputRight() //�����ж�
{
    QString sName = "";
    int val =-1;
    sName = ui->libcmb->currentText();
    QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr(""),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);

    if(sName.isEmpty())
    {
        msg.setText(tr("�ű������Ʋ���Ϊ��!"));
        msg.exec();
        return false;
    }

     //�����ж��Ƿ��ܿش���
     if(ui->bctrlcheck->isChecked())
     {
         if(! pwnd->IsAddressCheckRight(CtrlAddr,tr("�ܿص�ַ"),ui->addredit,0))
         {
             ui->addredit->setFocus();
             return false;
         }

         /*sName = ui->valueedit->text();
         val = sName.toInt();
         if(val !=0 && val != 1 && ui->typecmb->currentIndex() == 0)
         {
             msg.setText(tr("λ��ַ�ؼ����ܿ���������Ϊ0����1!"));
             msg.exec();
             return false;
         }*/
     }
    return true;
}

void newGlobalScriptDlg::on_Cancel_clicked()
{
    QDialog::close();
}

void newGlobalScriptDlg::on_bctrlcheck_clicked(bool checked)//�Ƿ��ܿش���
{
    ui->ctrlgroupBox->setEnabled(checked);
}

void newGlobalScriptDlg::on_btn_new_clicked()
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
        pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
    }
    QString libname = ui->libcmb->currentText();
    ui->libcmb->clear();
    foreach(Macro lib,pwnd->macros) //��ʼ��������
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
