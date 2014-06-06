#include "groupseldlg.h"
#include "ui_groupseldlg.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;
GroupSelDlg::GroupSelDlg(QStringList names,bool bSelectAll,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupSelDlg)
{
    ui->setupUi(this);
    setWindowTitle(tr("选择报警组"));
    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(chlSelected(int,int)));
    initTable(names,bSelectAll);

}

GroupSelDlg::~GroupSelDlg()
{
    delete ui;
}

void GroupSelDlg::on_btn_ok_clicked()
{
    accept();
}

void GroupSelDlg::on_btn_cancel_clicked()
{
    reject();
}

QStringList GroupSelDlg::getNames(bool &isAll)
{
    QStringList names;
    QTableWidgetItem *firstItem = ui->tableWidget->item(0,1);
    bool bAll = (firstItem->checkState() == Qt::Checked);

    for(int i=1; i<ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i,1);
        QTableWidgetItem *nameItem = ui->tableWidget->item(i,0);
        bAll = bAll && (item->checkState() == Qt::Checked);
        if(item->checkState() == Qt::Checked)
        {
            names << nameItem->text();
        }
    }
    isAll = bAll;
    return names;
}

void GroupSelDlg::chlSelected(int row,int col)
{
    QTableWidgetItem *item = ui->tableWidget->item(row,1);
    if (col != 1 || !item)
    {
        return;
    }

    if(row == 0)
    {

        if (item->checkState() == Qt::Checked)
        {
            for(int i=1; i<ui->tableWidget->rowCount(); i++)
            {
                ui->tableWidget->item(i,1)->setCheckState(Qt::Checked);
            }
        }
        else{
            for(int i=1; i<ui->tableWidget->rowCount(); i++)
            {
                ui->tableWidget->item(i,1)->setCheckState(Qt::Unchecked);
            }
        }
    }
}

void GroupSelDlg::initTable(QStringList names,bool bSelectAll)
{
    QStringList groups;

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑

    ui->tableWidget->setColumnWidth(0, ui->tableWidget->sizeHint().width()*2/3);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//最后一行拉伸

    int curRow = 1;
    int count = 0;
    foreach(ALARM_GROUP alarmGrp,pwnd->m_pSamSysParame->m_qvcAlarm)
    {
        groups << alarmGrp.alarmName;

        curRow = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(curRow);
        QTableWidgetItem * tabItem = new QTableWidgetItem(alarmGrp.alarmName);

        ui->tableWidget->setItem(curRow,0,tabItem);
        tabItem = new QTableWidgetItem();

        if(names.contains(alarmGrp.alarmName))
            tabItem->setCheckState(Qt::Checked);
        else
            tabItem->setCheckState(Qt::Unchecked);

        ui->tableWidget->setItem(curRow,1,tabItem);

        count++;

    }
    if(bSelectAll)
    {
        ui->tableWidget->item(0,1)->setCheckState(Qt::Checked);
    }
}
