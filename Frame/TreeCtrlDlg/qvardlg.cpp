/************************************************************************
 *                        SAMKOON TECHNOLOGY CORP.
 *                          COPYRIGHT (C) 2012
 *
 * Description: 变量表
 *
 *
 *
 * Functions: 实现变量的定义功能.
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
    this->setWindowTitle(tr("变量表设定"));
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
  初始化表格
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
  由连接序号获得连接名称
*********************************************************************/
QString QVardlg::connectTypeToStr(int type)
{
    QString str;
    int size;
    if (type == 0)
    {
        str = tr("内部存储区");
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
  设定表格每一行显示的内容
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
  创建新的变量
*****************************************************************/
void QVardlg::on_m_create_new_clicked()
{
    VarRecord m_newVar;
    QVarNewdlg dlg(-1,0,&m_newVar,this);
    if (dlg.exec() == QDialog::Accepted)
    {
        if (m_newVar.mAddr.sShowAddr != "")
        {
            //增加一个新的变量
            m_qvcRecordTemp.append(m_newVar);
            //修改tableview
            ui->tableWidget->setRowCount(m_qvcRecordTemp.size());
            int counts = ui->tableWidget->rowCount();
            settableview(m_newVar,counts - 1);
        }
    }
}
/*****************************************************************
  删除选定的变量
*****************************************************************/
void QVardlg::on_m_delete_clicked()
{
    int idel = ui->tableWidget->currentRow();
    if (idel == -1)
    {
        return;
    }
    m_qvcRecordTemp.remove(idel);
    //重新刷新表格
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
  修改选定的变量
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
            //修改变量
            m_qvcRecordTemp[imdy] = m_newVar;
            //修改tableview
            settableview(m_newVar,imdy);
        }
    }
}
/*****************************************************************
  删除全部变量
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
            //修改变量
            m_qvcRecordTemp[imdy] = m_newVar;
            //修改tableview
            settableview(m_newVar,imdy);
        }
    }
}
/*****************************************************************
  确定按钮
*****************************************************************/
void QVardlg::on_pushButton_clicked()
{
    pwnd->m_pSamSysParame->m_VarRecord = m_qvcRecordTemp;
    QDialog::accept();
}
/*****************************************************************
  取消按钮
*****************************************************************/
void QVardlg::on_pushButton_2_clicked()
{
      QDialog::reject();
}
/*****************************************************************
  帮助按钮
*****************************************************************/
void QVardlg::on_pushButton_3_clicked()
{
    pwnd->loadHelpHtm(GROUP_TYPE_VARIBLE);
}
