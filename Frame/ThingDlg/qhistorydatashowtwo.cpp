#include "qhistorydatashowtwo.h"
#include "ui_qhistorydatashowtwo.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

//注意，当前是哪一组就初始话哪组，选择其他组后不保留当前组的内容,下次再选这组要从新初始化
QHistoryDataShowTwo::QHistoryDataShowTwo(QWidget *parent):QWidget(parent),ui(new Ui::QHistoryDataShowTwo)
{
    bInit = false;
    ui->setupUi(this);

    pEdit = NULL;
    curSamp = -1;

    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//最后一行拉伸

    //语言选择
    int temp = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    for(int i = 0; i < temp; i++)
    {
        ui->comboBox->addItem(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList[i]);
    }

    //组名
    temp = pwnd->m_pSamSysParame->m_loadDataSampling.size();
    qDebug() << "datasample size:"<< temp;
    for(int i = 0; i < temp; i++)
    {
        if(2 == pwnd->m_pSamSysParame->m_loadDataSampling[i].nDataSampType)//曲线为历史数据采集
        {
            if(pwnd->m_pSamSysParame->m_loadDataSampling[i].m_dataTable.size() != 0)
            {
                ui->comboBox_2->addItem(pwnd->m_pSamSysParame->m_vecDataSamplingStr[i]);
            }
        }
    }

    //bInit = true;
}

QHistoryDataShowTwo::~QHistoryDataShowTwo()
{
    delete ui;
}

void QHistoryDataShowTwo::Init(QHistoryDataShowAttr* pItem)
{
    if(pItem)
    {
        sGroupName      = pItem->sGroupName;
        m_vecHisData    = pItem->m_vecHisData;

        //修正m_vecHisData？？？？？？
        int strNum = pwnd->m_pSamSysParame->m_vecDataSamplingStr.size();
        int ky = -1;
        for(int i = 0; i < strNum; i++)
        {
            if(pwnd->m_pSamSysParame->m_vecDataSamplingStr[i] == sGroupName)
            {
                ky = i;
                break;
            }
        }
        if(ky != -1)
        {
            if(2 == pwnd->m_pSamSysParame->m_loadDataSampling[ky].nDataSampType)//历史数据采集
            {
                HistoryDataInfo info;
                dataInfo        item;
                int lanNum  = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
                int itemNum = pwnd->m_pSamSysParame->m_loadDataSampling[ky].m_dataTable.size();
                if(itemNum == m_vecHisData[0].m_vecInfo.size())//个数没有改变的情况，看看是否有的地址值改变了
                {
                    QVector<HistoryDataInfo> tempHisData;
                    tempHisData = m_vecHisData;
                    m_vecHisData.clear();
                    for(int i = 0; i < lanNum; i++)
                    {
                        info.m_nLanguage = i;
                        for(int j = 0; j < itemNum; j++)
                        {
                            item.m_kb       = pwnd->m_pSamSysParame->m_loadDataSampling[ky].m_dataTable[j].keyAddress;
                            item.m_nSampNum = pwnd->m_pSamSysParame->m_loadDataSampling[ky].m_dataTable[j].nAddrNumber;
                            //item.m_bShow    = true;
                            //item.m_strName  = QString::number(pwnd->m_pSamSysParame->m_loadDataSampling[k].m_dataTable[j].nAddrNumber);
                            info.m_vecInfo.push_back(item);
                        }
                        m_vecHisData.push_back(info);
                        info.m_vecInfo.clear();
                    }

                    if(itemNum > 256)
                    {
                        for(int i = 0; i < lanNum; i++)
                        {
                            for(int j = 256; j < itemNum; j++)
                            {
                                m_vecHisData[i].m_vecInfo.pop_back();
                            }
                        }
                    }

                    //add
                    sortHisData();

                    for(int i = 0; i < lanNum; i++)
                    {
                        for(int j = 0; j < itemNum; j++)
                        {
                            m_vecHisData[i].m_vecInfo[j].m_bShow   = tempHisData[i].m_vecInfo[j].m_bShow;
                            m_vecHisData[i].m_vecInfo[j].m_strName = tempHisData[i].m_vecInfo[j].m_strName;
                        }
                    }
                }
            }
        }
        //if(sGroupName != "" && pwnd->m_pSamSysParame->m_vecDataSamplingStr.contains(sGroupName)
        //&& m_vecHisData.size() != 0 && )
    }
    else
    {
        sGroupName = "";
        m_vecHisData.clear();
    }

    if(pItem && (sGroupName == ""))//数据采集被删掉或者修改为实时的时候的处理方式
    {
        ui->checkBox_all->setEnabled(false);
        ui->comboBox->setEnabled(false);

        ui->comboBox_2->clear();
        //组名
        int temp = pwnd->m_pSamSysParame->m_loadDataSampling.size();
        for(int i = 0; i < temp; i++)
        {
            if(2 == pwnd->m_pSamSysParame->m_loadDataSampling[i].nDataSampType)//曲线为历史数据采集
            {
                if(pwnd->m_pSamSysParame->m_loadDataSampling[i].m_dataTable.size() != 0)
                {
                    ui->comboBox_2->addItem(pwnd->m_pSamSysParame->m_vecDataSamplingStr[i]);
                }
            }
        }
        ui->comboBox_2->setCurrentIndex(-1);

        ui->tableWidget->setEnabled(false);
        bInit = true;
        return;
    }

    bool SampNumCh = false;//是否再次打开的时候，选中的数据采集改变个数
    if(sGroupName != "")
    {
        int gSize = pwnd->m_pSamSysParame->m_vecDataSamplingStr.size();
        int numSize = 0;
        for(int i = 0; i < gSize; i++)
        {
            if(sGroupName == pwnd->m_pSamSysParame->m_vecDataSamplingStr[i])
            {
                numSize = pwnd->m_pSamSysParame->m_loadDataSampling[i].m_dataTable.size();
                if(numSize != m_vecHisData[0].m_vecInfo.size())
                {
                    SampNumCh = true;
                }
                break;
            }
        }
    }

    //当前语言数与上面初始化的语言数不吻合的时候
    //即已经形成了图形后改变语言数，然后再进入这里，或者初始化赋值为0肯定进这里
    //改变语言需要重新初始化，以前pItem的数据全部去掉
    //没有考虑组改变的时候的情况，组的改变需要删除这个，所以假设组是对的
    if((m_vecHisData.size() != pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size()) || (SampNumCh == true))
    {
        if(sGroupName == "")
        {
            ui->comboBox_2->setCurrentIndex(0);
            sGroupName = ui->comboBox_2->currentText();//设置当前组号为0
        }
        else
        {
            int count = ui->comboBox_2->count();
            for(int i = 0; i < count; i++)
            {
                if(sGroupName == ui->comboBox_2->itemText(i))
                {
                    ui->comboBox_2->setCurrentIndex(i);
                    break;
                }
            }
        }

        m_vecHisData.clear();
        int lanNum  = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
        int itemNum = 0;
        int sampNum = pwnd->m_pSamSysParame->m_vecDataSamplingStr.size();
        for(int i = 0; i < sampNum; i++)
        {
            if(sGroupName == pwnd->m_pSamSysParame->m_vecDataSamplingStr[i])
            {
                itemNum = pwnd->m_pSamSysParame->m_loadDataSampling[i].m_dataTable.size();
                curSamp = i;
                break;
            }
        }

        HistoryDataInfo info;
        dataInfo        item;
        for(int i = 0; i < lanNum; i++)
        {
            info.m_nLanguage = i;
            for(int j = 0; j < itemNum; j++)
            {
                item.m_kb       = pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable[j].keyAddress;
                item.m_nSampNum = pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable[j].nAddrNumber;
                item.m_bShow    = true;
                item.m_strName  = QString::number(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable[j].nAddrNumber);
                info.m_vecInfo.push_back(item);
            }
            m_vecHisData.push_back(info);
            info.m_vecInfo.clear();
        }

        //add
        sortHisData();
    }

    m_nCurLanNum = 0;
    ui->comboBox->setCurrentIndex(0);

    int k = ui->comboBox_2->count();
    for(int i = 0; i < k; i++)
    {
        if(sGroupName == ui->comboBox_2->itemText(i))
        {
            ui->comboBox_2->setCurrentIndex(i);
            break;
        }
    }

    k = pwnd->m_pSamSysParame->m_vecDataSamplingStr.size();
    int num = 0;
    for(int i = 0; i < k; i++)
    {
        if(sGroupName == pwnd->m_pSamSysParame->m_vecDataSamplingStr[i])
        {
            num = pwnd->m_pSamSysParame->m_loadDataSampling[i].m_dataTable.size();
            curSamp = i;
            break;
        }
    }
    if(num <= 0)
    {
        return;
    }
    if(-1 == curSamp)//没有数据采集相匹配
    {
        QMessageBox::about(this, tr("waring"), tr("iiiiiiiiiiiiiiii"));
        return;
    }
    ui->tableWidget->setRowCount(num);
    //sortHisData();

    bool isAllSelect = true;//全选/全不选，默认为全选
    if(pItem)
    {
        for(int i = 0; i < num; i++)
        {
            //填充编号
            //QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::number(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable[i].nAddrNumber));
            QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::number(m_vecHisData[m_nCurLanNum].m_vecInfo[i].m_nSampNum));
            ui->tableWidget->setItem(i, 0, newItem1);

            //填充地址
            //QTableWidgetItem *newItem2 = new QTableWidgetItem(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable[i].keyAddress.sShowAddr);
            QTableWidgetItem *newItem2 = new QTableWidgetItem(m_vecHisData[m_nCurLanNum].m_vecInfo[i].m_kb.sShowAddr);
            ui->tableWidget->setItem(i, 1, newItem2);

            //填充显示
            QTableWidgetItem *newItem3 = new QTableWidgetItem();
            if(m_vecHisData[m_nCurLanNum].m_vecInfo[i].m_bShow)
            {
                newItem3->setCheckState(Qt::Checked);
            }
            else
            {
                newItem3->setCheckState(Qt::Unchecked);
                isAllSelect = false;
            }
            ui->tableWidget->setItem(i, 2, newItem3);

            //填充名称
            QTableWidgetItem *newItem4 = new QTableWidgetItem(m_vecHisData[m_nCurLanNum].m_vecInfo[i].m_strName);
            ui->tableWidget->setItem(i, 3, newItem4);
        }
    }
    else
    {
        for(int i = 0; i < num; i++)
        {
            //填充编号
            //QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::number(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable[i].nAddrNumber));
            QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::number(m_vecHisData[m_nCurLanNum].m_vecInfo[i].m_nSampNum));
            ui->tableWidget->setItem(i, 0, newItem1);

            //填充地址
            //QTableWidgetItem *newItem2 = new QTableWidgetItem(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable[i].keyAddress.sShowAddr);
            QTableWidgetItem *newItem2 = new QTableWidgetItem(m_vecHisData[m_nCurLanNum].m_vecInfo[i].m_kb.sShowAddr);
            ui->tableWidget->setItem(i, 1, newItem2);

            //填充显示
            QTableWidgetItem *newItem3 = new QTableWidgetItem();
            //newItem3->setCheckState(Qt::Checked);
            if(m_vecHisData[m_nCurLanNum].m_vecInfo[i].m_bShow)
            {
                newItem3->setCheckState(Qt::Checked);
            }
            else
            {
                newItem3->setCheckState(Qt::Unchecked);
                isAllSelect = false;
            }
            ui->tableWidget->setItem(i, 2, newItem3);

            //填充名称
            //QTableWidgetItem *newItem4 = new QTableWidgetItem(QString::number(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable[i].nAddrNumber));
            QTableWidgetItem *newItem4 = new QTableWidgetItem(m_vecHisData[m_nCurLanNum].m_vecInfo[i].m_strName);
            ui->tableWidget->setItem(i, 3, newItem4);
        }
    }

    ui->checkBox_all->setChecked(isAllSelect);

    bInit = true;
}

void QHistoryDataShowTwo::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if(bInit == false)
    {
        return;
    }

    if(3 == previousColumn)//前一次点的是名称编辑
    {
        if(pEdit == NULL)
        {
            return;
        }
        m_str = pEdit->text();
        ui->tableWidget->removeCellWidget(previousRow, 3);
        delete pEdit;
        pEdit = NULL;
        if(m_str != "")
        {
            ui->tableWidget->item(previousRow, 3)->setText(m_str);
        }
        //m_vecHisData[m_nCurLanNum].m_vecInfo[previousRow].m_strName = m_str;
        emit redrawSence();
    }

    if(3 == currentColumn)//修改名称
    {
        pEdit = new QLineEdit;
        int  width      = ui->tableWidget->columnWidth(3);
        int  height     = ui->tableWidget->rowHeight(currentRow);
        pEdit->resize(width, height);
        pEdit->setText(ui->tableWidget->item(currentRow, 3)->text());
        ui->tableWidget->setCellWidget(currentRow, 3, pEdit);

        m_nCurRow = currentRow;
        connect(pEdit, SIGNAL(editingFinished()), this, SLOT(shit()));

        //m_vecHisData[m_nCurLanNum].m_vecInfo[currentRow].m_strName = pEdit->text();
    }
}

void QHistoryDataShowTwo::shit()
{
    m_vecHisData[m_nCurLanNum].m_vecInfo[m_nCurRow].m_strName = pEdit->text();
    emit redrawSence();
}

void QHistoryDataShowTwo::on_comboBox_2_currentIndexChanged(int index)//组号改变
{
    if(bInit == false)
    {
        return;
    }

    if(index >= 0)
    {
        ui->checkBox_all->setEnabled(true);
        ui->comboBox->setEnabled(true);
        ui->tableWidget->setEnabled(true);

        emit groupCh();
    }
    sGroupName = ui->comboBox_2->itemText(index);//index;
    HistoryDataInfo info;
    dataInfo        item;

    int lanNum  = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    int itemNum = 0;
    int sampNum = pwnd->m_pSamSysParame->m_vecDataSamplingStr.size();
    for(int i = 0; i < sampNum; i++)
    {
        if(sGroupName == pwnd->m_pSamSysParame->m_vecDataSamplingStr[i])
        {
            itemNum = pwnd->m_pSamSysParame->m_loadDataSampling[i].m_dataTable.size();
            curSamp = i;
            break;
        }
    }

    m_vecHisData.clear();
    for(int i = 0; i < lanNum; i++)
    {
        info.m_nLanguage = i;
        for(int j = 0; j < itemNum; j++)
        {
            item.m_kb       = pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable[j].keyAddress;
            item.m_nSampNum = pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable[j].nAddrNumber;
            item.m_bShow    = true;
            item.m_strName  = QString::number(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable[j].nAddrNumber);
            info.m_vecInfo.push_back(item);
        }
        m_vecHisData.push_back(info);
        info.m_vecInfo.clear();
    }
    sortHisData();

    m_nCurLanNum = 0;
    ui->comboBox->setCurrentIndex(0);
    //ui->comboBox_2->setCurrentIndex(sGroupName);

    int num = pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable.size();
    if(num <= 0)
    {
        return;
    }
    ui->tableWidget->setRowCount(num);

    for(int i = 0; i < num; i++)
    {
        //填充编号
        //QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::number(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable[i].nAddrNumber));
        QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::number(m_vecHisData[m_nCurLanNum].m_vecInfo[i].m_nSampNum));
        ui->tableWidget->setItem(i, 0, newItem1);

        //填充地址
        //QTableWidgetItem *newItem2 = new QTableWidgetItem(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable[i].keyAddress.sShowAddr);
        QTableWidgetItem *newItem2 = new QTableWidgetItem(m_vecHisData[m_nCurLanNum].m_vecInfo[i].m_kb.sShowAddr);
        ui->tableWidget->setItem(i, 1, newItem2);

        //填充显示
        QTableWidgetItem *newItem3 = new QTableWidgetItem();
        //newItem3->setCheckState(Qt::Checked);
        if(m_vecHisData[m_nCurLanNum].m_vecInfo[i].m_bShow)
        {
            newItem3->setCheckState(Qt::Checked);
        }
        else
        {
            newItem3->setCheckState(Qt::Unchecked);
        }
        ui->tableWidget->setItem(i, 2, newItem3);

        //填充名称
        //QTableWidgetItem *newItem4 = new QTableWidgetItem(QString::number(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable[i].nAddrNumber));
        QTableWidgetItem *newItem4 = new QTableWidgetItem(m_vecHisData[m_nCurLanNum].m_vecInfo[i].m_strName);
        ui->tableWidget->setItem(i, 3, newItem4);
    }

    emit redrawSence();
}

void QHistoryDataShowTwo::on_comboBox_currentIndexChanged(int index)//语言改变
{
    if(bInit == false)
    {
        return;
    }

    m_nCurLanNum = index;

    int k = pwnd->m_pSamSysParame->m_vecDataSamplingStr.size();
    int num = 0;
    for(int i = 0; i < k; i++)
    {
        if(sGroupName == pwnd->m_pSamSysParame->m_vecDataSamplingStr[i])
        {
            num = pwnd->m_pSamSysParame->m_loadDataSampling[i].m_dataTable.size();
            break;
        }
    }
    QString str;
    for(int i = 0; i < num; i++)
    {
        str = m_vecHisData[index].m_vecInfo[i].m_strName;
        if((ui->tableWidget->currentRow() == i) && pEdit)
        {
            pEdit->setText(str);
        }
        ui->tableWidget->item(i, 3)->setText(str);
    }

    emit redrawSence();
    emit sigLanguageCh(index);
}

void QHistoryDataShowTwo::on_tableWidget_cellClicked(int row, int column)
{
    if(2 == column)
    {
        int temp = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();

        int sampNum = pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable.size();
        int num = 0;
        for(int i = 0; i < sampNum; i++)
        {
            if(ui->tableWidget->item(i,2)->checkState() == Qt::Checked)
            //if(ui->tableWidget->item(row,2)->checkState() == true)
            {
                num++;
            }
        }
        if(num <= 0)//这里不是1是因为当前点中的那一行已经改变
        {
            ui->tableWidget->item(row,2)->setCheckState(Qt::Checked);
            return;
        }

        for(int i = 0; i < temp; i++)
        {
            m_vecHisData[i].m_vecInfo[row].m_bShow = ui->tableWidget->item(row,2)->checkState();
            /*if(Qt::Checked == ui->tableWidget->item(row,2)->checkState())
            {
                m_vecHisData[i].m_vecInfo[row].m_bShow = true;
            }
            else if(Qt::Unchecked == ui->tableWidget->item(row,2)->checkState())
            {
                m_vecHisData[i].m_vecInfo[row].m_bShow = false;
            }*/
        }
        emit redrawSence();
    }
}

void QHistoryDataShowTwo::on_checkBox_all_clicked(bool checked)
{
    int temp    = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    int sampNum = pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].m_dataTable.size();

    if(sampNum <= 0)
    {
        return;
    }

    bool isFirst = true;
    for(int i = 0; i < sampNum; i++)
    {
        if(checked)
        {
            ui->tableWidget->item(i,2)->setCheckState(Qt::Checked);
        }
        else
        {
            if(isFirst == true)
            {
                isFirst = false;
                continue;
            }
            ui->tableWidget->item(i,2)->setCheckState(Qt::Unchecked);
        }

        for(int j = 0; j < temp; j++)
        {
            m_vecHisData[j].m_vecInfo[i].m_bShow = checked;
        }
    }

    emit redrawSence();
}

void QHistoryDataShowTwo::slotLan(int lan)
{
    ui->comboBox->setCurrentIndex(lan);

    m_nCurLanNum = lan;

    int k = pwnd->m_pSamSysParame->m_vecDataSamplingStr.size();
    int num = 0;
    for(int i = 0; i < k; i++)
    {
        if(sGroupName == pwnd->m_pSamSysParame->m_vecDataSamplingStr[i])
        {
            num = pwnd->m_pSamSysParame->m_loadDataSampling[i].m_dataTable.size();
            break;
        }
    }
    QString str;
    for(int i = 0; i < num; i++)
    {
        str = m_vecHisData[lan].m_vecInfo[i].m_strName;
        ui->tableWidget->item(i, 3)->setText(str);
    }

    emit redrawSence();
}

void QHistoryDataShowTwo::sortHisData()
{
    //QVector<HistoryDataInfo> m_vecHisData;
    int nLan = m_vecHisData.size();
    int num = 0;
    dataInfo temp;
    for(int i = 0; i < nLan; i++)
    {
        num = m_vecHisData[i].m_vecInfo.size();
        if(num <= 1)
        {
            continue;
        }
        for(int j = 0; j < num - 1; j++)
        {
            for(int k = j + 1; k < num; k++)
            {
                if(m_vecHisData[i].m_vecInfo[j].m_nSampNum > m_vecHisData[i].m_vecInfo[k].m_nSampNum)
                {
                    temp = m_vecHisData[i].m_vecInfo[j];
                    m_vecHisData[i].m_vecInfo[j] = m_vecHisData[i].m_vecInfo[k];
                    m_vecHisData[i].m_vecInfo[k] = temp;
                }
            }
        }
    }
}
