#include "scheduledlg.h"
#include "ui_scheduledlg.h"
#include "schedulers.h"
#include <QTableView>
#include <QLayout>
#include "addcmddlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
#define MAX_SIZE 64

ScheduleDlg::ScheduleDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScheduleDlg)
{
    ui->setupUi(this);
    currentWidget = NULL;
    schedulers = pwnd->m_pSamSysParame->schedulers;
    model = new StableModel(schedulers);

    views.append(ui->viewSunday);
    views.append(ui->viewMonday);
    views.append(ui->viewTuesday);
    views.append(ui->viewWednesday);
    views.append(ui->viewThursday);
    views.append(ui->viewFriday);
    views.append(ui->viewSaturday);
    currentView = ui->viewSunday;
    weekday = SUN;

    ui->tabWidget->setCurrentWidget(ui->Sunday);
    on_tabWidget_currentChanged(weekday);

    foreach(QTableView *view,views)
    {

        connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_itemDoubleClick(QModelIndex)));
    }
    //QHBoxLayout *layout = new QHBoxLayout;
    //currentWidget->setLayout(layout);
    //currentView = new QTableView(currentWidget);

    //layout->addWidget(currentView);
    //currentView->setModel(model);
}

ScheduleDlg::~ScheduleDlg()
{
    delete ui;
}

void ScheduleDlg::on_itemDoubleClick(QModelIndex index)
{
    ScheItem item;
    item = model->itemAt(index.row(),weekday);
    qDebug() <<"weekday: " <<item.eWeek;
    if(item.eWeek != WEEKDAYERROR)
    {
        AddCmdDLg cmddlg(item.eWeek,&item,this);
        if(cmddlg.exec() == QDialog::Accepted)
        {
            model->removeItem(index.row(),weekday);
            foreach(ScheItem citem,cmddlg.m_items)
            {
                model->insert(citem);
            }

        }
    }
}

void ScheduleDlg::on_tabWidget_currentChanged(int index)
{
    if(index >= 0 && index < 7)
    {
        currentView = views.at(index);
        weekday = (E_WEEKDAY)index;
        model->setWeekday((E_WEEKDAY)index);
        currentView->setModel(model);
    }

}

void ScheduleDlg::on_btn_Add_clicked()
{
    //ScheItem item;
    AddCmdDLg cmddlg(weekday,0,this);
    if(cmddlg.exec() == QDialog::Accepted)
    {
        foreach(ScheItem item,cmddlg.m_items)
        {
            if(model->count() >= MAX_SIZE)
            {
                QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("ÿ����������64�����"),QMessageBox::Ok,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
                box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
                box.exec();
                continue;
            }
            model->insert(item);
        }


    }

}

void ScheduleDlg::on_btn_Del_clicked()
{
    QItemSelectionModel *selections = views[weekday]->selectionModel();
    QModelIndexList selItems = selections->selectedIndexes();

    //QModelIndexList selItems = views[weekday]->selectedIndexes();
    QList<int >rows;
    foreach(QModelIndex  index,selItems)
    {
        int row = index.row();
        if (!rows.contains(row))
        {
            rows << row;
        }
    }

    if(rows.size() > 0)//��Ҫɾ�����У�������ʾ
    {
        QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("�Ƿ�ɾ����ѡ��Ŀ��"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("��"));
        box.button(QMessageBox::No)->setText(tr("��"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::No))
        {
            return;
        }
    }
    model->removeitems(rows,weekday);
}

void ScheduleDlg::on_btn_continue_clicked()
{
    reject();
}

void ScheduleDlg::on_btn_AddMulti_clicked()
{
    AddCmdDLg cmddlg(WEEKDAYERROR,0,this);
    if(cmddlg.exec() == QDialog::Accepted)
    {
        foreach(ScheItem item,cmddlg.m_items)
        {
            if(model->count(item.eWeek) >= MAX_SIZE)
            {
                QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("ÿ����������64�����"),QMessageBox::Ok,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
                box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
                box.exec();
                continue;
            }
            model->insert(item);
        }


    }
}
