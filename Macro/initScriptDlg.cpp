#include "initScriptDlg.h"
#include "ui_initScriptDlg.h"
#include  "Frame\MainWindow.h"
#include "Macro/newInitScriptDlg.h"
extern MainWindow  *pwnd;

initScriptDlg::initScriptDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initScriptDlg)
{
    ui->setupUi(this);
    this->setFixedSize(412,454);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    //��ʼ�����
    int count = pwnd->m_pSamSysParame->m_qvcInitMaroProp.size();
    for(int i = 0; i < count; i++)
    {
        insertDataToTable(i);
    }
    ui->table->horizontalHeader()->setStretchLastSection(true);//���һ������
}

initScriptDlg::~initScriptDlg()
{
    delete ui;
}

void initScriptDlg::on_newadd_clicked()
{
    newInitScriptDlg dlg(1,-1,this);
    if(dlg.exec() == QDialog::Accepted)
    {
        int cout = pwnd->m_pSamSysParame->m_qvcInitMaroProp.size();
        insertDataToTable(cout-1);
    }
}

void initScriptDlg::insertDataToTable(int iIndex)
{
    int count = ui->table->rowCount();
    QString sName = "";

    ui->table->insertRow(count);
    ui->table->setRowHeight(count,20);

    sName = pwnd->m_pSamSysParame->m_qvcInitMaroProp[iIndex].sLibName; //������
    ui->table->setItem(count ,0,new QTableWidgetItem(sName));
    sName = pwnd->m_pSamSysParame->m_qvcInitMaroProp[iIndex].sFucName; //��������
    ui->table->setItem(count ,1,new QTableWidgetItem(sName));
}

void initScriptDlg::on_deletebtn_clicked()
{
    int irow = ui->table->currentRow();
    if(irow < 0)
        return;
    ui->table->removeRow(irow);
    pwnd->m_pSamSysParame->m_qvcInitMaroProp.remove(irow);
    irow--;
    if( irow >= 0 )
    {
        ui->table->setCurrentCell(irow,0);
        QTableWidgetItem *item = ui->table->item(irow,0);
        item->setSelected(true);
    }
}

void initScriptDlg::on_alterbtn_clicked()
{
    int irow = ui->table->currentRow();
    if(irow < 0)
        return;
    int count = pwnd->m_pSamSysParame->m_qvcInitMaroProp.size();
    if(irow >= count)
        return;

    newInitScriptDlg dlg(2,irow,this);
    if(dlg.exec() == QDialog::Accepted)
    {
        alterDataToTable(irow);
    }
}

void initScriptDlg::alterDataToTable(int iIndex)
{
    QString sName = "";
    QTableWidgetItem *item = NULL;

   item = ui->table->item(iIndex,0);
   if(item)
   {
        sName = pwnd->m_pSamSysParame->m_qvcInitMaroProp[iIndex].sLibName; //������
        item->setText(sName);
   }

   item = ui->table->item(iIndex,1);
   if(item)
   {
        sName = pwnd->m_pSamSysParame->m_qvcInitMaroProp[iIndex].sFucName; //��������
        item->setText(sName);
   }
}

void initScriptDlg::on_exsitbtn_clicked()
{
    QDialog::close();
}

void initScriptDlg::on_helpbtn_clicked()
{
    pwnd->LoadProjectHelp();
}

void initScriptDlg::on_table_itemPressed(QTableWidgetItem* item)
{
    if (qApp->mouseButtons() == Qt::RightButton)          //�ж��Ƿ����Ҽ�
    {
        QMenu menu(ui->table);
        QAction *newVar= menu.addAction(tr("�½�"));
        QAction *editVar= menu.addAction(tr("�༭"));
        menu.addSeparator();
        QAction *deleteVar= menu.addAction(tr("ɾ��"));

        connect(newVar,SIGNAL(triggered()),SLOT(on_newadd_clicked()));
        connect(editVar,SIGNAL(triggered()),SLOT(on_alterbtn_clicked()));
        connect(deleteVar,SIGNAL(triggered()),SLOT(on_deletebtn_clicked()));

        menu.exec(QCursor::pos());
    }
}

void initScriptDlg::on_table_cellDoubleClicked(int row, int column)
{
    if(row < 0 || column < 0 )
        return;
    on_alterbtn_clicked();//�޸�
}
