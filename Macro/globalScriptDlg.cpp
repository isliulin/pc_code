#include "globalScriptDlg.h"
#include "ui_globalScriptDlg.h"
#include "Macro/newGlobalScriptDlg.h"
#include  "Frame\MainWindow.h"
#include "Macro/macroedit.h"

extern MainWindow  *pwnd;

globalScriptDlg::globalScriptDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::globalScriptDlg)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    this->setFixedSize(size());
    //��ʼ�����
    int count = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp.size();
    for(int i = 0; i < count; i++)
    {
        insertDataToTable(i);
    }
}

globalScriptDlg::~globalScriptDlg()
{
    delete ui;
}

void globalScriptDlg::on_newadd_clicked()//����
{
    newGlobalScriptDlg dlg(1,-1,this);
    if(dlg.exec() == QDialog::Accepted)
    {
        int cout = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp.size();
        insertDataToTable(cout-1);
    }
}

void globalScriptDlg::insertDataToTable(int iIndex)
{
    int count = ui->table->rowCount();
    QString sName = "";
    int val = 0;

    ui->table->insertRow(count);
    ui->table->setRowHeight(count,20);

    sName = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].sLibName; //������
    ui->table->setItem(count ,0,new QTableWidgetItem(sName));
    sName = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].sFucName; //��������
    ui->table->setItem(count ,1,new QTableWidgetItem(sName));

    val = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].iRunRate;//Ƶ��
    sName = QString("%1").arg(val * 100);
    ui->table->setItem(count ,2,new QTableWidgetItem(sName));

    val = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].iScriptCount;//wxy ִ�д���
    sName = QString("%1").arg(val);
    ui->table->setItem(count ,3,new QTableWidgetItem(sName));

    int ival = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].bIfCtrl; //�Ƿ��ܿش���
    if(ival == 1)
        sName = tr("��");
    else if(ival == 0)
        sName = tr("��");
    ui->table->setItem(count ,4,new QTableWidgetItem(sName));

    if(ival == 1)
    {
        val = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].iCtrlType;//��������
        if(val == 0)
            sName = tr("λ��ַ");
        else if(val == 1)
            sName = tr("�ֵ�ַ");
        ui->table->setItem(count ,5,new QTableWidgetItem(sName));

        sName = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].mCtlAddr.sShowAddr; //���Ƶ�ַ
        ui->table->setItem(count ,6,new QTableWidgetItem(sName));

        val = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].iValue;//ִ������
        sName = QString("%1").arg(val);
        ui->table->setItem(count ,7,new QTableWidgetItem(sName));
    }
    else
    {
        ui->table->setItem(count ,5,new QTableWidgetItem(""));
        ui->table->setItem(count ,6,new QTableWidgetItem(""));
        ui->table->setItem(count ,7,new QTableWidgetItem(""));
    }
}

void globalScriptDlg::on_deletebtn_clicked()//ɾ��
{
    int irow = ui->table->currentRow();
    if(irow < 0)
        return;
    ui->table->removeRow(irow);
    pwnd->m_pSamSysParame->m_qvcGlobalMaroProp.remove(irow);
    irow--;
    if( irow >= 0 )
    {
        ui->table->setCurrentCell(irow,0);
        QTableWidgetItem *item = ui->table->item(irow,0);
        item->setSelected(true);
    }
}

void globalScriptDlg::on_alterbtn_clicked()//�޸�
{
    int irow = ui->table->currentRow();
    if(irow < 0)
        return;
    int count = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp.size();
    if(irow >= count)
        return;

    newGlobalScriptDlg dlg(2,irow,this);
    if(dlg.exec() == QDialog::Accepted)
    {
        alterDataToTable(irow);
    }
}

void globalScriptDlg::alterDataToTable(int iIndex)
{
    QString sName = "";
    int val = 0;
   QTableWidgetItem *item = NULL;

   item = ui->table->item(iIndex,0);
   if(item)
   {
        sName = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].sLibName; //������
        item->setText(sName);
   }

   item = ui->table->item(iIndex,1);
   if(item)
   {
        sName = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].sFucName; //��������
        item->setText(sName);
   }

   item = ui->table->item(iIndex,2);
   if(item)
   {
       val = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].iRunRate;//Ƶ��
       sName = QString("%1").arg(val * 100);
        item->setText(sName);
   }

   item = ui->table->item(iIndex,3);
   if(item)
   {
       val = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].iScriptCount;//wxy ִ�д���
       sName = QString("%1").arg(val);
        item->setText(sName);
   }

   item = ui->table->item(iIndex,4);
   int ictrl = 0;
   if(item)
   {
       ictrl = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].bIfCtrl;//�Ƿ��ܿش���
       if(ictrl == 1)
           sName = tr("��");
       else if(ictrl == 0)
           sName = tr("��");
        item->setText(sName);
   }


   item = ui->table->item(iIndex,5);
   if(item)
   {
       if(ictrl == 1)
       {
           val = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].iCtrlType;//��������
           if(val == 0)
               sName = tr("λ��ַ");
           else if(val == 1)
               sName = tr("�ֵ�ַ");
       }
       else
           sName = "";
       item->setText(sName);
   }

   item = ui->table->item(iIndex,6);
   if(item)
   {
       if(ictrl == 1)
            sName = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].mCtlAddr.sShowAddr; //���Ƶ�ַ
       else
           sName = "";
       item->setText(sName);
   }

   item = ui->table->item(iIndex,7);
   if(item)
   {
       if(ictrl == 1)
       {
           val = pwnd->m_pSamSysParame->m_qvcGlobalMaroProp[iIndex].iValue;//ִ������
           sName = QString("%1").arg(val);
       }
       else
           sName = "";
       item->setText(sName);
   }
}

void globalScriptDlg::on_exsitbtn_clicked()
{
    QDialog::close();
}

void globalScriptDlg::on_helpbtn_clicked()
{
    pwnd->LoadProjectHelp();
}

void globalScriptDlg::on_table_cellDoubleClicked(int row, int column)
{
    if(row < 0 || column < 0 )
        return;
    on_alterbtn_clicked();//�޸�
}

void globalScriptDlg::on_table_itemPressed(QTableWidgetItem* item)//�Ҽ�
{
    if (qApp->mouseButtons() == Qt::RightButton)          //�ж��Ƿ����Ҽ�
    {
        QMenu menu(ui->table);
        QAction *newVar= menu.addAction(tr("�½�"));
        QAction *editVar= menu.addAction(tr("�༭"));
        menu.addSeparator();
        QAction *deleteVar= menu.addAction(tr("ɾ��"));
        menu.addSeparator();
        QAction *openScript= menu.addAction(tr("�򿪽ű���"));

        connect(newVar,SIGNAL(triggered()),SLOT(on_newadd_clicked()));
        connect(editVar,SIGNAL(triggered()),SLOT(on_alterbtn_clicked()));
        connect(deleteVar,SIGNAL(triggered()),SLOT(on_deletebtn_clicked()));
        connect(openScript,SIGNAL(triggered()),SLOT(openScriptLib()));

        menu.exec(QCursor::pos());
    }
}

void globalScriptDlg::openScriptLib()//�򿪽ű���
{
    MacroEdit dlg(QString(""),this);
    dlg.exec();
}
