#include "alarmset.h"
#include "ui_alarmset.h"
#include "Frame/mainwindow.h"
#include "Frame/TreeCtrlDlg/insertalarm.h"
extern MainWindow *pwnd;
#define MAX_ALARM_SIZE 512

AlarmSet::AlarmSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlarmSet)
{
    ui->setupUi(this);

	m_index = -1;
    bInit = false;

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    QVector<QString>language_vector;
    languageCount = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();

    for(int i=0; i<languageCount; i++)
    {
        language_vector.push_back(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
    }
    for(int i=0; i<languageCount; i++)
    {
        ui->combo_language->addItem(language_vector.at(i));
    }

    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setColumnWidth(0, ui->table->sizeHint().width()*1/6);
    ui->table->setColumnWidth(1, ui->table->sizeHint().width()*1/2);
    ui->table->setColumnWidth(2, ui->table->sizeHint().width());
    ui->table->setColumnWidth(3, ui->table->sizeHint().width()*4/3);


    ui->table->setRowCount(MAX_ALARM_SIZE);

    for(int i = 0; i < MAX_ALARM_SIZE; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(i));
        ui->table->setItem(i, 0, item);
    }

    QSize sz = size();
    setFixedSize(sz);//��ֹ�ϷŴ��ڴ�С

    setWindowTitle(tr("������¼"));
    connect(ui->combo_language,SIGNAL(currentIndexChanged(int)),this,SLOT(reloadMsgs(int)));
}

AlarmSet::~AlarmSet()
{
    delete ui;
}

//��ʼ����������
void AlarmSet::Init(ALARM_GROUP alarmGroup,int index)
{
	bInit = true;
	m_index = index;
    alarmGrp = alarmGroup;
    ui->edit_name->setText(alarmGroup.alarmName);

    foreach(stAlarm pAlarm,alarmGrp.alarms)
    {
        setTableItem(pAlarm);
    }

}
QString AlarmSet::CondString(stAlarm alarm)
{
    QString sCondtion = QString(tr("��������"));
    switch(alarm.eCondtion)
    {
    case ALARM_ON:
        sCondtion = QString(tr("λON����"));
        break;
    case ALARM_OFF:
        sCondtion = QString(tr("λOFF����"));
        break;
    case ALARM_VALUE:
        sCondtion = tr("X = ")+QString::number(alarm.rangeLow,'g',10) +tr(" ����");
        break;
    case ALARM_RANGE:
        sCondtion = tr("X < ")+QString::number(alarm.rangeHigh,'g',10)+tr(" �� ");
        sCondtion += tr("X > ")+QString::number(alarm.rangeLow,'g',10)+tr(" ����");
        break;
    case ALARM_RANGE_OUT:
        sCondtion = tr("X < ")+QString::number(alarm.rangeLow,'g',10)+tr(" �� ");
        sCondtion += tr("X > ")+QString::number(alarm.rangeHigh,'g',10)+tr(" ����");
        break;
    }
    return sCondtion;
}
//ȷ��
void AlarmSet::on_btn_ok_clicked()
{
    QString alarmName = ui->edit_name->text();
    if(alarmName.isEmpty())
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("�������Ʋ���Ϊ��"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }
    QStringList names;
    foreach(ALARM_GROUP grp,pwnd->m_pSamSysParame->m_qvcAlarm)
    {
        names << grp.alarmName;
    }
    if(!bInit && names.contains(alarmName))
    {
        QString warning;
        warning +=tr("���� ");
        warning += alarmName;
        warning +=tr(" �Ѿ�����");
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,warning,0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }

	if (bInit)
	{
		int index = names.indexOf(alarmName);
		if (index >=0 && index != m_index)
		{
			QString warning;
			warning +=tr("���� ");
			warning += alarmName;
			warning +=tr(" �Ѿ�����");
			QMessageBox box(QMessageBox::Warning,VERSION_NAME,warning,0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
			box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
			box.exec();
			return;
		}
	}
    alarmGrp.alarmName = alarmName;

    accept();
}

void AlarmSet::on_btn_cancel_clicked()
{
    reject();
}

void AlarmSet::on_table_cellDoubleClicked(int row, int column)
{
    QStringList alarmMsgs;
    for(int i=0; i<languageCount;i++)
    {
        alarmMsgs << "alarm message";
    }
    stAlarm defaultItem;
    defaultItem.index = row;
    defaultItem.addr.sShowAddr = "LB0";
    defaultItem.dataType = BIT_1;
    defaultItem.eCondtion = ALARM_ON;
    defaultItem.messages = alarmMsgs;
    defaultItem.rangeLow = 0;
	defaultItem.bOpenScene = false;
    defaultItem.bSeneMsg = false;
    defaultItem.bAddtoDB = true;
    defaultItem.bPrint = false;

    QTableWidgetItem *tableItem = ui->table->item(row,1);
    foreach(stAlarm cItem,alarmGrp.alarms)
    {
        if (cItem.index == row)
        {
            defaultItem = cItem;
            break;
        }
    }
    InsertAlarm insertDlg(defaultItem,this);
    if(insertDlg.exec() == QDialog::Accepted)
    {
        setAlarms(insertDlg.getAlarms());
    }
}
//�޸��Ժ� �����б�
void AlarmSet::setAlarms(QList<stAlarm> mAlarms)
{
    QVector<int > indexs;

    for(int i=0; i<alarmGrp.alarms.size(); i++)
    {
        if(indexs.contains(alarmGrp.alarms[i].index))
        {
            alarmGrp.alarms.remove(i);
            continue;
        }
        indexs << alarmGrp.alarms[i].index;
    }
    foreach(stAlarm cAlarm,mAlarms)
    {
        int index = indexs.indexOf(cAlarm.index);
        if(index <0)//������
        {
            alarmGrp.alarms.append(cAlarm);
        }
        else
            alarmGrp.alarms.replace(index,cAlarm);

        setTableItem(cAlarm);
    }

}

void AlarmSet::setTableItem(stAlarm cAlarm)
{
    int row = cAlarm.index;
    if( row >= 0 && row < MAX_ALARM_SIZE)
    {
        //������ַ��
        QTableWidgetItem *item = ui->table->item(row,1);
        if(item)
        {
            item->setText(cAlarm.addr.sShowAddr);

        }
        else
        {
            item = new QTableWidgetItem(cAlarm.addr.sShowAddr);
            ui->table->setItem(row,1,item);
        }
        //����������
        item = ui->table->item(row,2);
        if(item)
        {
            item->setText(CondString(cAlarm));

        }
        else
        {
            item = new QTableWidgetItem(CondString(cAlarm));
            ui->table->setItem(row,2,item);
        }
        //������Ϣ��
        item = ui->table->item(row,3);
        QString msg = "Alarm Message";
        int index = ui->combo_language->currentIndex();
        if(index>=0 && index < cAlarm.messages.size())
        {
            msg = cAlarm.messages.at(index);
        }

        if(item)
        {
            item->setText(msg);

        }
        else
        {
            item = new QTableWidgetItem(msg);
            ui->table->setItem(row,3,item);
        }
    }
}
void AlarmSet::reloadMsgs(int languageIndex)
{
    foreach(stAlarm alarm,alarmGrp.alarms)
    {
        int row = alarm.index;
        QTableWidgetItem *item = ui->table->item(row,3);
        if(alarm.messages.size()>languageIndex && item)
        {
            item->setText(alarm.messages.at(languageIndex));
        }
    }
}
//����һ��
void AlarmSet::on_btn_add_clicked()
{
    int row = ui->table->currentRow();
    QTableWidgetItem *item = ui->table->item(row,1);
    if (row>=0)
    {
        while (item && !item->text().isEmpty() && row<512)
        {
            row++;
            item = ui->table->item(row,1);
        }
        if (row <512)
        {
            on_table_cellDoubleClicked(row,0);
        }
    }
}
void AlarmSet::removeRow(int row)
{
    QTableWidgetItem *item = ui->table->item(row,1);
    if (item && !item->text().isEmpty())
    {
        item->setText("");
        ui->table->setItem(row,2,new QTableWidgetItem(""));
		
        ui->table->setItem(row,3,new QTableWidgetItem(""));
		
    }
    int index = 0;
    foreach(stAlarm alarmItem,alarmGrp.alarms)
    {
        if (alarmItem.index == row)
        {
            alarmGrp.alarms.remove(index);
			
            break;
        }
        index++;
    }
}
void AlarmSet::on_btn_delete_clicked()
{
    QList<QTableWidgetItem *> items = ui->table->selectedItems();
    QList<int> rows;
    foreach(QTableWidgetItem* item,items)
    {
        int row = item->row();
        if (!rows.contains(row))
        {
            rows << row;
        }
    }

    if(rows.size() > 0)
    {
        QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("�Ƿ�ɾ�����вɼ����ݣ�"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("��"));
        box.button(QMessageBox::No)->setText(tr("��"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::No))
        {
            return;
        }
    }

    foreach(int row,rows)
    {
        removeRow(row);
    }
}

void AlarmSet::on_btn_deleteall_clicked()
{
    if(ui->table->rowCount() > 0)
    {
        QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("�Ƿ�ɾ�����вɼ����ݣ�"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("��"));
        box.button(QMessageBox::No)->setText(tr("��"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::No))
        {
            return;
        }
    }

    for(int i=0; i<ui->table->rowCount(); i++)
    {
        for(int j=1; j<=3; j++)
        {
            QTableWidgetItem *item = ui->table->item(i,j);
            if(item)
            {
                item->setText("");
            }
        }

    }
    alarmGrp.alarms.clear();
}

void AlarmSet::on_btn_help_clicked()
{
    pwnd->loadHelpHtm(TREE_ALARMLOGIN);
}
