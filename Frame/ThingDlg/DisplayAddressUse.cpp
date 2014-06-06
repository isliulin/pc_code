#include "DisplayAddressUse.h"
#include "ui_DisplayAddressUse.h"
#include "addrchangedlg.h"

#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

DisplayAddressUse::DisplayAddressUse(QWidget *parent) :QDialog(parent),ui(new Ui::DisplayAddressUse)
{
    ui->setupUi(this);
    QString str = "";

    //setFixedSize(size());
    this->setWindowTitle(tr("地址使用一览表"));

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    pwnd->vAddrMsg.clear();
    pwnd->OnFillAddressMsgClass();        //填充地址信息

    ui->m_radio1->setChecked(true);
    ui->m_sheetcmb->setVisible(false);
    int totalSceneNum = pwnd->pSceneSheet.size();
    for(int i = 0; i < totalSceneNum;i++)
    {
        str = pwnd->pSceneSheet[i]->sNewScreenName;//画面名称
        ui->m_sheetcmb->addItem(str);
    }
    ui->m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);//List控件不可以编辑


    nSelctType = 0;

    InitTable();

    qDebug() << "fourth\n";
}

DisplayAddressUse::~DisplayAddressUse()
{
    delete ui;
}

void DisplayAddressUse::InitTable()
{
    QGraphicsItem *pItem;
    int nCount = 0;
    int i = 0;
    int j = 0;
    int nIndex = 0;
    QString sAddr = "";
    QString sScreenName = "";
    QString sAddrUse = "";
    int nRow = 0;
    QString str = "";
    //bool nFlag = true;
    int temp;
    int addrCount = 0;

    ui->m_table->setColumnCount(3);
    ui->m_table->setRowCount(0);
    ui->m_table->setColumnWidth(0,180);
    ui->m_table->setColumnWidth(1,270);
    ui->m_table->setColumnWidth(2,180);
    pwnd->mapMsgOutPutItem.clear();
    nCount = pwnd->vAddrMsg.size();//长度
    ui->m_table->clear();
    QStringList header;
    header.append(tr("画面名称"));
    header.append(tr("控件名称"));
    header.append(tr("所用地址"));
    ui->m_table->setHorizontalHeaderLabels(header);

    if(1 == nSelctType)
    {
        str = ui->m_sheetcmb->currentText();  //获得画面名称
    }

    qDebug() << "first\n";
    for(int m = 0; m < nCount; m++)
    {
        pItem       = pwnd->vAddrMsg.at(m)->pItem;
        temp        = pwnd->vAddrMsg.at(m)->Address.size();
        sScreenName = "";
        if(pItem)//控件地址
        {
            nIndex      = pwnd->vAddrMsg.at(m)->nSheetIndex;//画面序号
            sScreenName = pwnd->pSceneSheet[nIndex]->sNewScreenName;//画面名称
        }

        switch(nSelctType)
        {
            case 0:
            {
                addrCount += temp;
            }
            break;

            case 1:
            {
                if(str == sScreenName)
                {
                    addrCount += temp;
                }
            }
            break;

            default:
            QMessageBox::about(this, tr("waring"), tr("error"));
            break;
        }
    }
    ui->m_table->setRowCount(addrCount);

    qDebug() << "second\n";
    for(i = 0; i < nCount; i++)
    {
        pItem       = pwnd->vAddrMsg.at(i)->pItem;
        temp        = pwnd->vAddrMsg.at(i)->Address.size();
        if(pItem)//控件地址
        {
            nIndex      = pwnd->vAddrMsg.at(i)->nSheetIndex; //画面序号
            sScreenName = pwnd->pSceneSheet[nIndex]->sNewScreenName;//画面名称
        }
        else
        {
            sScreenName = tr("工程管理器 ");
        }

        switch(nSelctType)
        {
            case 0:
            {
                for(j = 0; j < temp; j++)
                {
                    sAddrUse = pwnd->vAddrMsg.at(i)->Address[j].str;
                    sAddr    = pwnd->vAddrMsg.at(i)->Address[j].pAddr->sShowAddr;//取地址
                    ui->m_table->setItem(nRow,0,new QTableWidgetItem(sScreenName)); //画面名称
                    ui->m_table->setItem(nRow,1,new QTableWidgetItem(sAddrUse)); //控件名称
                    ui->m_table->setItem(nRow,2,new QTableWidgetItem(sAddr)); //地址

                    pwnd->pMsgOutPut = new MsgOutPut ;//信息输出窗口双击要处理的类
                    pwnd->pMsgOutPut->pItem = pItem;
                    pwnd->pMsgOutPut->nSheetIndex = nIndex;
                    pwnd->mapMsgOutPutItem.insert(nRow,pwnd->pMsgOutPut);

                    nRow++;
                }
            }
            break;

            case 1:
            {
                if(str == sScreenName)
                {
                    for(j = 0; j < temp; j++)
                    {
                        sAddrUse = pwnd->vAddrMsg.at(i)->Address[j].str;
                        sAddr    = pwnd->vAddrMsg.at(i)->Address[j].pAddr->sShowAddr;//取地址
                        //ui->m_table->setRowHeight(nRow,20);
                        ui->m_table->setItem(nRow,0,new QTableWidgetItem(sScreenName)); //画面名称
                        ui->m_table->setItem(nRow,1,new QTableWidgetItem(sAddrUse)); //控件名称
                        ui->m_table->setItem(nRow,2,new QTableWidgetItem(sAddr)); //地址

                        pwnd->pMsgOutPut = new MsgOutPut ;//信息输出窗口双击要处理的类
                        pwnd->pMsgOutPut->pItem = pItem;
                        pwnd->pMsgOutPut->nSheetIndex = nIndex;
                        pwnd->mapMsgOutPutItem.insert(nRow, pwnd->pMsgOutPut);
                        nRow++;
                    }
                }
            }
            break;

            default:
            QMessageBox::about(this, tr("waring"), tr("error"));
            break;
        }
    }
    qDebug() << "third\n";
    /*for(i = 0; i < nCount; i++)
    {
        pItem = pwnd->vAddrMsg.at(i)->pItem;

        temp = pwnd->vAddrMsg.at(i)->Address.size();
        for(j = 0; j < temp; j++)
        {
            nIndex = pwnd->vAddrMsg.at(i)->nSheetIndex; //画面序号
            sAddr = pwnd->vAddrMsg.at(i)->Address[j].pAddr->sShowAddr;//取地址

            if(nSelctType == 0) //显示全部画面
            {
                if(sAddr.isEmpty())
                {
                    nFlag = false;
                }
                else
                {
                    nFlag = true;
                }
            }
            else if(nSelctType == 1)//显示指定画面
            {
                str = ui->m_sheetcmb->currentText();  //获得画面名称
                sScreenName = pwnd->pSceneSheet[nIndex]->sNewScreenName;//画面名称
                if(str == sScreenName && !sAddr.isEmpty())
                {
                    nFlag = true;
                }
                else
                {
                    nFlag = false;
                }
            }
            if(nFlag)//!sAddr.isEmpty()
            {
                sAddrUse = pwnd->vAddrMsg.at(i)->Address[j].str;//.sAddrName;
                if(pItem)//是控件的地址
                {
                    sScreenName = pwnd->pSceneSheet[nIndex]->sNewScreenName;//画面名称
                }
                else     //是工程管理器中地址
                {
                    sScreenName=tr("工程管理器 "); //输出信息
                }

                //ui->m_table->insertRow(nRow);
                ui->m_table->setRowHeight(nRow,20);
                ui->m_table->setItem(nRow,0,new QTableWidgetItem(sScreenName)); //画面名称
                ui->m_table->setItem(nRow,1,new QTableWidgetItem(sAddrUse)); //画面名称
                ui->m_table->setItem(nRow,2,new QTableWidgetItem(sAddr)); //画面名称
                nRow++;

                pwnd->pMsgOutPut = new MsgOutPut ;//信息输出窗口双击要处理的类
                pwnd->pMsgOutPut->pItem = pItem;
                pwnd->pMsgOutPut->nSheetIndex = nIndex;
                pwnd->vMsgOutPutItem.append(pwnd->pMsgOutPut);
            }
        }//end  the second for
    }//end  the first for*/
}

void DisplayAddressUse::on_m_radio1_clicked()
{
    nSelctType = 0;
    InitTable();
    ui->m_sheetcmb->setVisible(false);
}

void DisplayAddressUse::on_m_radio2_clicked()//显示指定画面
{
    nSelctType = 1;
    InitTable();
    ui->m_sheetcmb->setVisible(true);
}

void DisplayAddressUse::on_m_sheetcmb_currentIndexChanged(QString )
{
    nSelctType = 1;
    InitTable();
}

void DisplayAddressUse::on_m_table_cellDoubleClicked(int row, int column)
{
    QTableWidgetItem *mItem;         //设置最后项为选中状态
    mItem = ui->m_table->item(row,column); //0

    if(mItem) //!str.isEmpty()
    {
        QMap<int, MsgOutPut*>::const_iterator itor = pwnd->mapMsgOutPutItem.find(row);
        if(itor != pwnd->mapMsgOutPutItem.end() && itor.value()->pItem)
        {
            pwnd->nActiveSheetIndex = itor.value()->nSheetIndex;
            pwnd->pView->setScene(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]);
            pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->clearSelection();//清除所有选择
            itor.value()->pItem->setSelected(true);
        }
    }

    //int num = totalAddrCount();
    //if(row >= num)
    //{
    //    return;//error
    //}

    int numItem = pwnd->vAddrMsg.size();
    int curNum  = 0;
    AddrMsg* pAMsg;
    ADDRPRO  pro;
    int      temp;

    if(1 == nSelctType)
    {
        QGraphicsItem *pItem;
        int nIndex = 0;
        QMap<int,MsgOutPut*>::const_iterator itor = pwnd->mapMsgOutPutItem.find(row);
        if(itor != pwnd->mapMsgOutPutItem.end() && itor.value()->pItem)
        {
            pItem  = itor.value()->pItem;
            nIndex = itor.value()->nSheetIndex;//画面序号
        }
        for(int i = 0; i < numItem; i++)
        {
            if(nIndex == pwnd->vAddrMsg[i]->nSheetIndex)
            {
                temp = curNum;
                curNum += pwnd->vAddrMsg[i]->Address.size();
                if(row < curNum)
                {
                    pAMsg = pwnd->vAddrMsg[i];
                    pro   = pwnd->vAddrMsg[i]->Address[row - temp];
                    break;
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < numItem; i++)
        {
            temp = curNum;
            curNum += pwnd->vAddrMsg[i]->Address.size();
            if(row < curNum)
            {
                pAMsg = pwnd->vAddrMsg[i];
                pro   = pwnd->vAddrMsg[i]->Address[row - temp];
                break;
            }
        }
    }

    addrChangeDlg dlg(pAMsg, row - temp);
    //假如点击确定，修改地址和显示表的地址
    short    replaceType;//那种方式替换
    short    type;       //要替换的类型
    QString  replaceAddr;//替换地址
    QString  oldAddr = pAMsg->Address[row - temp].pAddr->sShowAddr;//老地址字符串
    Keyboard key;
    int      screenId = pAMsg->nSheetIndex;//画面序号
    if(dlg.exec() == QDialog::Accepted)
    {
        replaceType = dlg.replaceType;
        type        = dlg.type;
        replaceAddr = dlg.replaceAddr;
        key         = dlg.key;

        if(oldAddr == replaceAddr)//地址没有变更
        {
            return;
        }

        if(0 == replaceType)
        {
            *(pAMsg->Address[row - temp].pAddr) = key;
            if(pAMsg->Address[row - temp].nRecipe > 0)
            {
                int k = pAMsg->Address[row - temp].nRecipe;
                if(k <= pwnd->m_pSamSysParame->m_qvcRecipe.size())
                {
                     pwnd->m_pSamSysParame->m_qvcRecipe[k-1].bContniu = false;//改为不连续
                }
            }
        }
        else if(1 == replaceType)
        {
            for(int i = temp; i < curNum; i++)
            {
                if(oldAddr == pAMsg->Address[i - temp].pAddr->sShowAddr && type == pAMsg->Address[i - temp].pAddr->nAddrType)
                {
                    *(pAMsg->Address[i - temp].pAddr) = key;
                    if(pAMsg->Address[i - temp].nRecipe > 0)
                    {
                        int k = pAMsg->Address[i - temp].nRecipe;
                        if(k <= pwnd->m_pSamSysParame->m_qvcRecipe.size())
                        {
                             pwnd->m_pSamSysParame->m_qvcRecipe[k-1].bContniu = false;//改为不连续
                        }
                    }
                }
            }
        }
        else if(2 == replaceType)//整个画面
        {
            int itemNum = pwnd->vAddrMsg.size();
            for(int i = 0; i < itemNum; i++)
            {
                int addrNum = pwnd->vAddrMsg[i]->Address.size();
                if(screenId == pwnd->vAddrMsg[i]->nSheetIndex)
                {
                    for(int j = 0; j < addrNum; j++)
                    {
                        if((oldAddr == pwnd->vAddrMsg[i]->Address[j].pAddr->sShowAddr) && (type == pwnd->vAddrMsg[i]->Address[j].pAddr->nAddrType))
                        {
                            *(pwnd->vAddrMsg[i]->Address[j].pAddr) = key;
                            if(pwnd->vAddrMsg[i]->Address[j].nRecipe > 0)
                            {
                                int k = pwnd->vAddrMsg[i]->Address[j].nRecipe;
                                if(k <= pwnd->m_pSamSysParame->m_qvcRecipe.size())
                                {
                                     pwnd->m_pSamSysParame->m_qvcRecipe[k-1].bContniu = false;//改为不连续
                                }
                            }
                        }
                    }
                }
            }
        }
        else if(3 == replaceType)//整个工程
        {
            int itemNum = pwnd->vAddrMsg.size();
            for(int i = 0; i < itemNum; i++)
            {
                int addrNum = pwnd->vAddrMsg[i]->Address.size();
                for(int j = 0; j < addrNum; j++)
                {
                    if(oldAddr == pwnd->vAddrMsg[i]->Address[j].pAddr->sShowAddr && type == pwnd->vAddrMsg[i]->Address[j].pAddr->nAddrType)
                    {
                        *(pwnd->vAddrMsg[i]->Address[j].pAddr) = key;
                        if(pwnd->vAddrMsg[i]->Address[j].nRecipe > 0)
                        {
                            int k = pwnd->vAddrMsg[i]->Address[j].nRecipe;
                            if(k <= pwnd->m_pSamSysParame->m_qvcRecipe.size())
                            {
                                 pwnd->m_pSamSysParame->m_qvcRecipe[k-1].bContniu = false;//改为不连续
                            }
                        }
                    }
                }
            }
        }

        InitTable();
    }
}

int DisplayAddressUse::totalAddrCount()
{
    int numItem = pwnd->vAddrMsg.size();
    int total = 0;

    for(int i = 0; i < numItem; i++)
    {
        total += pwnd->vAddrMsg[i]->Address.size();
    }

    return total;
}
