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

    //初始化表格
    int count = pwnd->m_pSamSysParame->m_qvcInitMaroProp.size();
    for(int i = 0; i < count; i++)
    {
        insertDataToTable(i);
    }
    ui->table->horizontalHeader()->setStretchLastSection(true);//最后一行拉伸
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

    sName = pwnd->m_pSamSysParame->m_qvcInitMaroProp[iIndex].sLibName; //库名称
    ui->table->setItem(count ,0,new QTableWidgetItem(sName));
    sName = pwnd->m_pSamSysParame->m_qvcInitMaroProp[iIndex].sFucName; //函数名称
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
        sName = pwnd->m_pSamSysParame->m_qvcInitMaroProp[iIndex].sLibName; //库名称
        item->setText(sName);
   }

   item = ui->table->item(iIndex,1);
   if(item)
   {
        sName = pwnd->m_pSamSysParame->m_qvcInitMaroProp[iIndex].sFucName; //函数名称
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
    if (qApp->mouseButtons() == Qt::RightButton)          //判断是否是右键
    {
        QMenu menu(ui->table);
        QAction *newVar= menu.addAction(tr("新建"));
        QAction *editVar= menu.addAction(tr("编辑"));
        menu.addSeparator();
        QAction *deleteVar= menu.addAction(tr("删除"));

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
    on_alterbtn_clicked();//修改
}
