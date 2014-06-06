#include "qvarnewdlg.h"
#include "qvardlg.h"
#include "ui_qvarnewdlg.h"
#include "Frame/addressinputdialog.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QVarNewdlg::QVarNewdlg(int index,int newModify,VarRecord *pRecord,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QVarNewdlg)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
    pRecordTemp = pRecord;      //保存一个备份，在对话框中将用备份操作
    pVarDlgTemp = (QVardlg*)parent;
    indextmp = index;           //新建时为-1，修改时为序号
    if (newModify == 1)         //修改
    {
        ui->m_addredit->setText(pRecord->mAddr.sShowAddr);       //地址
        ui->m_varedit->setText(pRecord->sVarName);                  //变量名
        //数据类型
        ui->combo_datatype->setCurrentIndex(pRecord->mType);
    }
    else                        //创建
    {
        ui->m_addredit->setText("LB0");
        ui->m_varedit->setText("");
    }
    this->setWindowTitle(tr("变量设定"));
}

QVarNewdlg::~QVarNewdlg()
{
    delete ui;
}

void QVarNewdlg::on_m_addrinput_clicked()
{
    Keyboard keyb;
    keyb = pRecordTemp->mAddr;
    QString str = ui->m_addredit->text();
    int addrType=ui->combo_datatype->currentIndex();
    AddressInputDialog dlg_triggered(keyb,str,addrType,this);
    if(dlg_triggered.exec())
    {
        ui->m_addredit->setText(keyb.sShowAddr);
    }


    pRecordTemp->mAddr = keyb;
}
bool QVarNewdlg::checkName(QString str)
{
    int size = pVarDlgTemp->m_qvcRecordTemp.size();
    for (int i=0;i<size;i++)
    {
        if (str == pVarDlgTemp->m_qvcRecordTemp.at(i).sVarName)         //名字重复
        {
            if (i != indextmp)
                return false;
        }
    }
    return true;
}

/*************************************************************
  点击地址输入按钮
*************************************************************/
void QVarNewdlg::on_m_ok_clicked()
{
    int bitword;
    if (ui->combo_datatype->currentIndex() == 0)
    {
        bitword = 0;
    }
    else
    {
        bitword = 1;
    }
    QMessageBox msg(QMessageBox::Warning,PRO_FULL_NAME,tr(""),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("确定"),QMessageBox::AcceptRole);

    if(! pwnd->IsAddressCheckRight(pRecordTemp->mAddr,tr("控制地址"),ui->m_addredit,bitword))
    {
  //      msg.setText(tr("地址输入错误"));
  //      msg.exec();
        return ;
    }
    if (checkName(ui->m_varedit->text()) == false)      //名字重复
    {
        msg.setText(tr("变量名重复"));
        msg.exec();
        return ;
    }
    if (ui->m_varedit->text() == "")
    {
        msg.setText(tr("变量名不能为空"));
        msg.exec();
        return ;
    }
    if (ui->m_varedit->text().size() > 128)
    {
        msg.setText(tr("变量名长度不能大于128"));
        msg.exec();
        return ;
    }
    pRecordTemp->sVarName = ui->m_varedit->text();
    pRecordTemp->mType = (DATA_TYPE)ui->combo_datatype->currentIndex();
    QDialog::accept();
}

void QVarNewdlg::on_m_cancel_clicked()
{
    QDialog::reject();
}
