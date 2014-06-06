#include "MarcoUseDisplay.h"
#include "ui_MarcoUseDisplay.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

MarcoUseDisplay::MarcoUseDisplay(QWidget *parent):QDialog(parent),ui(new Ui::MarcoUseDisplay)
{
    ui->setupUi(this);

    setFixedSize(size());

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    QString str = "";
    ui->m_radio1->setChecked(true);
    ui->m_sheetcmb->setVisible(false);
    int totalSceneNum = pwnd->pSceneSheet.size();
    for(int i = 0; i < totalSceneNum;i++)
    {
        str = pwnd->pSceneSheet[i]->sNewScreenName ;//画面名称
        ui->m_sheetcmb->addItem(str);
    }
    ui->m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);//List控件不可以编辑

    pwnd->findScreenAllMarco(mVecStr);//填充地址信息
    nSelctType = 0;
    InitTable();
}

MarcoUseDisplay::~MarcoUseDisplay()
{
    delete ui;
}

void MarcoUseDisplay::InitTable()
{
    QGraphicsItem *pItem;
    int     nCount = 0;
    int     nRow   = 0;
    bool    nFlag  = true;
    QString str    = "";
    int     nIndex = 0;

    ui->m_table->setColumnCount(3);
    ui->m_table->setRowCount(0);
    ui->m_table->setColumnWidth(0,230);
    ui->m_table->setColumnWidth(1,200);
    ui->m_table->setColumnWidth(2,200);
    pwnd->mapMsgOutPutItem.clear();
    nCount = mVecStr.size();//长度
    ui->m_table->clear();

    QStringList header;
    header.append(tr("画面名称"));
    header.append(tr("控件名称"));
    header.append(tr("脚本名称"));
    ui->m_table->setHorizontalHeaderLabels(header);

    for(int i = 0; i < nCount; i++)
    {
        if(nSelctType == 1) //显示指定画面
        {
            str = ui->m_sheetcmb->currentText();//获得画面名称
            if(str != mVecStr[i].sScreenName)
            {
                nFlag = false;
            }
        }

        if(nFlag)
        {
            ui->m_table->insertRow(nRow);
            ui->m_table->setRowHeight(nRow,20);
            ui->m_table->setItem(nRow, 0, new QTableWidgetItem(mVecStr[i].sScreenName + mVecStr[i].sItemName));//画面名称
            ui->m_table->setItem(nRow, 1, new QTableWidgetItem(mVecStr[i].sLibName));   //控件名称
            ui->m_table->setItem(nRow, 2, new QTableWidgetItem(mVecStr[i].sFunName));      //使用宏名称

            pwnd->pMsgOutPut = new MsgOutPut ;//信息输出窗口双击要处理的类
            pwnd->pMsgOutPut->pItem = pItem;
            pwnd->pMsgOutPut->nSheetIndex = nIndex;
            pwnd->mapMsgOutPutItem.insert(nRow, pwnd->pMsgOutPut);
            nRow++;
        }

        nFlag = true;
    }
}

void MarcoUseDisplay::on_m_radio1_clicked()
{
    nSelctType = 0;
    InitTable();
    ui->m_sheetcmb->setVisible(false);
}

void MarcoUseDisplay::on_m_radio2_clicked()
{
    nSelctType = 1;
    InitTable();
    ui->m_sheetcmb->setVisible(true);
}

void MarcoUseDisplay::on_m_sheetcmb_currentIndexChanged(QString )
{
    nSelctType = 1;
    InitTable();
}

void MarcoUseDisplay::on_m_table_cellDoubleClicked(int row, int column)
{
    /*QTableWidgetItem *mItem;         //设置最后项为选中状态
    mItem = ui->m_table->item(row,column); //0

    if(mItem) //!str.isEmpty()
    {
        if(pwnd->vMsgOutPutItem.at(row)->pItem)
        {
            pwnd->nActiveSheetIndex = pwnd->vMsgOutPutItem.at(row)->nSheetIndex;
            pwnd->pView->setScene(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]);
            pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->clearSelection();//清除所有选择
            pwnd->vMsgOutPutItem.at(row)->pItem->setSelected(true);
        }
    }*/
}
