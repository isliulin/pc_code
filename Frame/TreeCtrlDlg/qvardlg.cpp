/************************************************************************
 *                        SAMKOON TECHNOLOGY CORP.
 *                          COPYRIGHT (C) 2012
 *
 * Description: ������
 *
 *
 *
 * Functions: ʵ�ֱ����Ķ��幦��.
 *
 * Modification Log:
 * Date             Name             Description Of Change
 * 2012-04-6       Pan facheng      Creation.
 ***********************************************************************/
#include "qvardlg.h"
#include "qvarnewdlg.h"
#include "Frame/mainwindow.h"
#include "Frame/addressinputdialog.h"
extern MainWindow *pwnd;

QVardlg::QVardlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QVardlg)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
    init();
    this->setWindowTitle(tr("�������趨"));
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnWidth(0,40);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,100);
}

QVardlg::~QVardlg()
{
    delete ui;
}
/*****************************************************************
  ��ʼ�����
*****************************************************************/
void QVardlg::init()
{
    int size;
    size = pwnd->m_pSamSysParame->m_VarRecord.size();
    ui->tableWidget->setRowCount(size);
    for (int i=0;i<size;i++)
    {
        settableview(pwnd->m_pSamSysParame->m_VarRecord.at(i),i);
    }
    m_qvcRecordTemp = pwnd->m_pSamSysParame->m_VarRecord;
}
/*********************************************************************
  ��������Ż����������
*********************************************************************/
QString QVardlg::connectTypeToStr(int type)
{
    QString str;
    int size;
    if (type == 0)
    {
        str = tr("�ڲ��洢��");
        return str;
    }
    size = pwnd->m_pSamSysParame->m_qvcPlcCommunicate.size();
    if (type > size)
    {
        return "";
    }
    str = pwnd->m_pSamSysParame->m_qvcPlcCommunicate.at(type - 1).sConnectName;
    return str;
}

/*********************************************************************
  �趨���ÿһ����ʾ������
*********************************************************************/
void QVardlg::settableview(VarRecord record, int rows)
{
    QString str;
    for (int j=0;j<4;j++)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem;
        switch(j)
        {
        case 0:
            newItem->setText(QString::number(rows+1));
            ui->tableWidget->setItem(rows,j,newItem);
            break;
        case 1:
            newItem->setText(record.sVarName);
            ui->tableWidget->setItem(rows,j,newItem);
            break;
        case 2:
            str = connectTypeToStr(record.mAddr.nConnectType);
            newItem->setText(str);
            ui->tableWidget->setItem(rows,j,newItem);
            break;
        case 3:
            str = record.mAddr.sShowAddr;
            newItem->setText(str);
            ui->tableWidget->setItem(rows,j,newItem);
            break;
        }
    }
}
/*****************************************************************
  �����µı���
*****************************************************************/
void QVardlg::on_m_create_new_clicked()
{
    VarRecord m_newVar;
    QVarNewdlg dlg(-1,0,&m_newVar,this);
    if (dlg.exec() == QDialog::Accepted)
    {
        if (m_newVar.mAddr.sShowAddr != "")
        {
            //����һ���µı���
            m_qvcRecordTemp.append(m_newVar);
            //�޸�tableview
            ui->tableWidget->setRowCount(m_qvcRecordTemp.size());
            int counts = ui->tableWidget->rowCount();
            settableview(m_newVar,counts - 1);
        }
    }
}
/*****************************************************************
  ɾ��ѡ���ı���
*****************************************************************/
void QVardlg::on_m_delete_clicked()
{
    int idel = ui->tableWidget->currentRow();
    if (idel == -1)
    {
        return;
    }
    m_qvcRecordTemp.remove(idel);
    //����ˢ�±��
    int size;
    size = m_qvcRecordTemp.size();
    ui->tableWidget->reset();
    ui->tableWidget->setRowCount(size);
    for (int i=0;i<size;i++)
    {
        settableview(m_qvcRecordTemp.at(i),i);
    }
}
/*****************************************************************
  �޸�ѡ���ı���
*****************************************************************/
void QVardlg::on_m_modify_clicked()
{
    int imdy = ui->tableWidget->currentRow();
    if (imdy == -1)
    {
        return;
    }
    VarRecord m_newVar;
    m_newVar = m_qvcRecordTemp.at(imdy);
    QVarNewdlg dlg(imdy,1,&m_newVar,this);
    if (dlg.exec() == QDialog::Accepted)
    {
        if (m_newVar.mAddr.sShowAddr != "")
        {
            //�޸ı���
            m_qvcRecordTemp[imdy] = m_newVar;
            //�޸�tableview
            settableview(m_newVar,imdy);
        }
    }
}
/*****************************************************************
  ɾ��ȫ������
*****************************************************************/
void QVardlg::on_m_del_all_clicked()
{
    m_qvcRecordTemp.clear();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void QVardlg::on_tableWidget_itemDoubleClicked(QTableWidgetItem* item)
{
    int imdy = ui->tableWidget->currentRow();
    if (imdy == -1)
    {
        return;
    }
    VarRecord m_newVar;
    m_newVar = m_qvcRecordTemp.at(imdy);
    QVarNewdlg dlg(imdy,1,&m_newVar,this);
    if (dlg.exec() == QDialog::Accepted)
    {
        if (m_newVar.mAddr.sShowAddr != "")
        {
            //�޸ı���
            m_qvcRecordTemp[imdy] = m_newVar;
            //�޸�tableview
            settableview(m_newVar,imdy);
        }
    }
}
/*****************************************************************
  ȷ����ť
*****************************************************************/
void QVardlg::on_pushButton_clicked()
{
    pwnd->m_pSamSysParame->m_VarRecord = m_qvcRecordTemp;
    QDialog::accept();
}
/*****************************************************************
  ȡ����ť
*****************************************************************/
void QVardlg::on_pushButton_2_clicked()
{
      QDialog::reject();
}
/*****************************************************************
  ������ť
*****************************************************************/
void QVardlg::on_pushButton_3_clicked()
{
    pwnd->loadHelpHtm(GROUP_TYPE_VARIBLE);
}
