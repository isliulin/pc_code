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

    iOpenType = Type; //1-��ʾ�½���2-��ʾ�����޸�
    iRowIndex = iIndex; //�޸������±꣬-1Ϊ�½�������Ϊ�޸��±�
    initDlgParament();
}

newInitScriptDlg::~newInitScriptDlg()
{
    delete ui;
}

void newInitScriptDlg::initDlgParament()
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
        setWindowTitle(tr("�½���ʼ���ű�"));
        if(ui->libcmb->count() > 0 )
        {
            ui->libcmb->setCurrentIndex(0);

        }
    }
    else if(iOpenType == 2)
    {
        setWindowTitle(tr("��ʼ���ű������޸�"));
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
    if(iOpenType == 1) //�½�
    {
         pwnd->m_pSamSysParame->m_qvcInitMaroProp.append(odata);
    }
    else if(iOpenType == 2)//�����޸�
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
    msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);

    if(sName.isEmpty())
    {
        msg.setText(tr("�ű������Ʋ���Ϊ��!"));
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
