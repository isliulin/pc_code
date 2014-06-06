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
    pRecordTemp = pRecord;      //����һ�����ݣ��ڶԻ����н��ñ��ݲ���
    pVarDlgTemp = (QVardlg*)parent;
    indextmp = index;           //�½�ʱΪ-1���޸�ʱΪ���
    if (newModify == 1)         //�޸�
    {
        ui->m_addredit->setText(pRecord->mAddr.sShowAddr);       //��ַ
        ui->m_varedit->setText(pRecord->sVarName);                  //������
        //��������
        ui->combo_datatype->setCurrentIndex(pRecord->mType);
    }
    else                        //����
    {
        ui->m_addredit->setText("LB0");
        ui->m_varedit->setText("");
    }
    this->setWindowTitle(tr("�����趨"));
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
        if (str == pVarDlgTemp->m_qvcRecordTemp.at(i).sVarName)         //�����ظ�
        {
            if (i != indextmp)
                return false;
        }
    }
    return true;
}

/*************************************************************
  �����ַ���밴ť
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
    msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);

    if(! pwnd->IsAddressCheckRight(pRecordTemp->mAddr,tr("���Ƶ�ַ"),ui->m_addredit,bitword))
    {
  //      msg.setText(tr("��ַ�������"));
  //      msg.exec();
        return ;
    }
    if (checkName(ui->m_varedit->text()) == false)      //�����ظ�
    {
        msg.setText(tr("�������ظ�"));
        msg.exec();
        return ;
    }
    if (ui->m_varedit->text() == "")
    {
        msg.setText(tr("����������Ϊ��"));
        msg.exec();
        return ;
    }
    if (ui->m_varedit->text().size() > 128)
    {
        msg.setText(tr("���������Ȳ��ܴ���128"));
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
