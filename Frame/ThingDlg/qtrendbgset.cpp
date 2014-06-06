#include "qtrendbgset.h"
#include "ui_qtrendbgset.h"
#include <qtablewidget.h>
#include "Frame/ThingDlg/qtrendbtable.h"

extern MainWindow *pwnd;

QTrendbgSet::QTrendbgSet(QVector<QString > groups, QWidget *parent):QDialog(parent),ui(new Ui::QTrendbgSet)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowTitle(tr("组设置"));
    ui->lineEdit->setEnabled(false);
    m_nMaxNum = groups.size();//实时曲线的总数
    vecGroup = groups;

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//最后一行拉伸

    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(groupSelected(int,int)));
    int total = pwnd->m_pSamSysParame->m_loadDataSampling.size();
    for(int i = 0; i < total; i++)
    {
        if(pwnd->m_pSamSysParame->m_loadDataSampling[i].nDataSampType == 1)//实时曲线
        {
            QString groupName;
            if(pwnd->m_pSamSysParame->m_vecDataSamplingStr.size() <= i)
            {
                break;
            }
            int curRow = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(curRow);

            groupName = pwnd->m_pSamSysParame->m_vecDataSamplingStr.at(i);

            QTableWidgetItem * tabItem = new QTableWidgetItem(groupName);
            ui->tableWidget->setItem(curRow,0,tabItem);
            tabItem = new QTableWidgetItem();
            ui->tableWidget->setItem(curRow,1,tabItem);
            if(vecGroup.contains(groupName))
            {
                tabItem->setCheckState(Qt::Checked);
            }
            else
            {
                tabItem->setCheckState(Qt::Unchecked);
            }
        }
    }
}

QTrendbgSet::~QTrendbgSet()
{
    delete ui;
}



void QTrendbgSet::on_pushButton_sure_clicked()
{
    int count =0;
    vecGroup.clear();
    for (int i=1; i<ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem *cItem = ui->tableWidget->item(i,1);
        QTableWidgetItem *numberItem = ui->tableWidget->item(i,0);
        if (numberItem && cItem && cItem->checkState() == Qt::Checked)
        {
            vecGroup << numberItem->text();
            count++;
        }
    }

    if (count == 0)
    {
        QMessageBox::about(ui->lineEdit, tr(""), tr("未选择采集组"));
        return;
    }
    accept();
}

void QTrendbgSet::on_pushButton_cancel_clicked()
{
    this->close();
}

void QTrendbgSet::groupSelected(int row,int col)
{
    QTableWidgetItem *item = ui->tableWidget->item(row,1);
    if (col != 1 || !item)
    {
        return;
    }

    if (row == 0)
    {
        if (item->checkState() == Qt::Checked)
        {
            for(int i=1; i<ui->tableWidget->rowCount() && i<16; i++)
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
    int chlCount = 0;
    for (int i=1; i<ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem *cItem = ui->tableWidget->item(i,1);
        if (cItem && cItem->checkState() == Qt::Checked)
        {
            chlCount++;
        }
    }
    if(chlCount >= 16)
    {
        chlCount--;
        item->setCheckState(Qt::Unchecked);
    }
    ui->lineEdit->setText(QString::number(chlCount));
}


