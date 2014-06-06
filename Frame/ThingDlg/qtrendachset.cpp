#include "qtrendachset.h"
#include "ui_qtrendachset.h"
#include <vector>
#include <iostream>

extern MainWindow *pwnd;

QTrendaChSet::QTrendaChSet(QList<int >channels, int curGroup, QWidget *parent):QDialog(parent),ui(new Ui::QTrendaChSet)
{
    ui->setupUi(this);

    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    setWindowTitle(tr("通道设置"));
	m_Channels = channels;
    m_nCurGroup = curGroup;
    m_nMaxNum   = pwnd->m_pSamSysParame->m_loadDataSampling[curGroup].m_dataTable.size();

	mapChls.clear();
	
	foreach (DATA_ADDRESS_ITEM item,pwnd->m_pSamSysParame->m_loadDataSampling[curGroup].m_dataTable)
	{
		mapChls.insert(item.nAddrNumber,item);
	}

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑

	ui->tableWidget->setColumnWidth(0, ui->tableWidget->sizeHint().width()*1/3);
    ui->tableWidget->setColumnWidth(1, ui->tableWidget->sizeHint().width()*2/3);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//最后一行拉伸

	int curRow = 1;
	int count = 0;
	foreach (DATA_ADDRESS_ITEM item,mapChls)
	{
		
		curRow = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(curRow);
		QTableWidgetItem * tabItem = new QTableWidgetItem(QString::number(item.nAddrNumber));
		
		ui->tableWidget->setItem(curRow,0,tabItem);
		tabItem = new QTableWidgetItem(item.keyAddress.sShowAddr);
		ui->tableWidget->setItem(curRow,1,tabItem);
		tabItem = new QTableWidgetItem();
		
		tabItem->setCheckState(Qt::Unchecked);

		ui->tableWidget->setItem(curRow,2,tabItem);
		
		count++;

	}
	connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(chlSelected(int,int)));
	for (int i=1; i<ui->tableWidget->rowCount(); i++)
	{
		QTableWidgetItem *cItem = ui->tableWidget->item(i,0);
		if (m_Channels.contains(cItem->text().toInt()))
		{
			ui->tableWidget->item(i,2)->setCheckState(Qt::Checked);
		}
	}
 
}

QTrendaChSet::~QTrendaChSet()
{
    delete ui;
}

void QTrendaChSet::on_pushButton_sure_clicked()
{
    m_nChNum    = 0;
	m_Channels.clear();
	for (int i=1; i<ui->tableWidget->rowCount(); i++)
	{
		QTableWidgetItem *cItem = ui->tableWidget->item(i,2);
		QTableWidgetItem *numberItem = ui->tableWidget->item(i,0);
		if (numberItem && cItem && cItem->checkState() == Qt::Checked)
		{
			m_Channels << numberItem->text().toInt();
			m_nChNum++;
		}
	}

	if (m_nChNum == 0)
	{
		QMessageBox::about(ui->spinBox_chNum, tr("warning"), tr("未选择通道号"));
		return;
	}
    accept();
}

void QTrendaChSet::on_pushButton_cancel_clicked()
{
    close();
}

void QTrendaChSet::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    
}

void QTrendaChSet::on_spinBox_chNum_valueChanged(int value)
{
    
}

//重新更新表项,内部函数，非信号槽函数
void QTrendaChSet::refrushTable(int count)
{
}

void QTrendaChSet::on_spinBox_beginCh_valueChanged(int value)
{
    
}

void QTrendaChSet::chlSelected(int row,int col)
{
	QTableWidgetItem *item = ui->tableWidget->item(row,2);
	if (col != 2 || !item)
	{
		return;
	}
	
	if (row == 0)
	{
		if (item->checkState() == Qt::Checked)
		{
			for(int i=1; i<ui->tableWidget->rowCount()&& i<=16; i++)
			{
				ui->tableWidget->item(i,2)->setCheckState(Qt::Checked);
			}
		}
		else{
			for(int i=1; i<ui->tableWidget->rowCount(); i++)
			{
				ui->tableWidget->item(i,2)->setCheckState(Qt::Unchecked);
			}
		}
    }
	int chlCount = 0;
	for (int i=1; i<ui->tableWidget->rowCount(); i++)
	{
		QTableWidgetItem *cItem = ui->tableWidget->item(i,2);
		if (cItem && cItem->checkState() == Qt::Checked)
		{
			chlCount++;
		}
	}
    if(chlCount >16 )
    {
        chlCount--;
        item->setCheckState(Qt::Unchecked);
    }
	ui->spinBox_chNum->setValue(chlCount);
}
