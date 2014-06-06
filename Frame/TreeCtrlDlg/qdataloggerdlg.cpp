#include "qdataloggerdlg.h"
#include "ui_qdataloggerdlg.h"
#include "Frame\mainwindow.h"
#include "insertdatasample.h"

extern MainWindow *pwnd;
#define  MAX_DATASAMPLE_LENGTH 256
//////////////////////////////QMyWidget自定义的类/////////////////////////////////
Keyboard QMyWidget::curAddr;

QMyWidget::QMyWidget(int width, int height, QWidget* parent) : QWidget(parent)
{
    bUpdate = false;

    pEdit  = new QLineEdit(this);
    pBtn   = new QPushButton(this);

    //curAddr.sPlcAddrValue = "0";
    //curAddr.sShowAddr = curAddr.sPlcRegTypeStr + curAddr.sPlcAddrValue;

    pEdit->resize(width * 4 / 5, height);
    pBtn->move(width * 4 / 5, 0);
    pBtn->resize(width / 5, height);

    connect(pBtn, SIGNAL(clicked()), this, SLOT(getBtnAddress()));
    connect(pEdit, SIGNAL(editingFinished()), this, SLOT(getEditAddress()));
}

QMyWidget::~QMyWidget()
{
    delete pEdit;
    delete pBtn;
}

void QMyWidget::getBtnAddress()
{
    //czq
    //pwnd->Addr_Type = 0;
    pwnd->Addr_Type = 1;
    AddressInputDialog dlg_readaddress(curAddr, this);
    dlg_readaddress.exec();

    if(curAddr.sShowAddr == "")
    {
        curAddr.sPlcAddrValue = "0";
        curAddr.sShowAddr = curAddr.sPlcRegTypeStr + curAddr.sPlcAddrValue;
    }
    else
    {
        pEdit->setText(curAddr.sShowAddr);
    }

    bUpdate = true;
}

void QMyWidget::getEditAddress()
{
    //czq
    //if(!pwnd->IsAddressCheckRight(curAddr, tr("单元格地址"), pEdit, 0))
    if(!pwnd->IsAddressCheckRight(curAddr, tr("单元格地址"), pEdit, 1))
    {
        //QMessageBox::about(this, tr("2"),tr("2"));
    }

    if(curAddr.sShowAddr == "")
    {
        curAddr.sPlcAddrValue = "0";
        curAddr.sShowAddr = curAddr.sPlcRegTypeStr + curAddr.sPlcAddrValue;
    }
    else
    {
        pEdit->setText(curAddr.sShowAddr);
    }

    bUpdate = true;
}

////////////////////////////qdataloggerdlg累构造析构函数///////////////////////////
qdataloggerdlg::qdataloggerdlg(int index,QWidget *parent):QDialog(parent),ui(new Ui::qdataloggerdlg)
{
    //////////////////////////////////////初始化前/////////////////////////////////////    
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    setFixedSize(size());
    this->setWindowTitle(tr("数据采集"));

    bInitFinish         = false;    //初始化还没完成
    bFlush              = true;
    m_pMyWidgetCur      = NULL;

    m_curSamp = index;
    int curSamp = m_curSamp;
    //从pwnd拷贝历史数据到临时变量m_dataSampling，复制全部数据
    m_dataSampling      = pwnd->m_pSamSysParame->m_loadDataSampling[curSamp];

    //////////////////////////////////地址页/////////////////////////////////////////
    //连续地址禁止编辑地址表
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnWidth(0, ui->tableWidget->sizeHint().width() / 4);
    ui->tableWidget->setColumnWidth(1, ui->tableWidget->sizeHint().width() *2/ 5);//设置第一列的宽度为总宽度的1/4
    ui->tableWidget->setColumnWidth(2, ui->tableWidget->sizeHint().width() * 3 / 5);//设置第一列的宽度为总宽度的3/4
    ui->tableWidget->setColumnWidth(3, ui->tableWidget->sizeHint().width() * 3 / 5);//设置第一列的宽度为总宽度的3/4
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//最后一行拉伸

    if(pwnd->m_pSamSysParame->m_vecDataSamplingStr.size() <= m_curSamp)//新建的时候
    {
        QString str;
        QString temp;
        int i;
        int j;
        bool HaveThisStr;
        int count = pwnd->m_pSamSysParame->m_vecDataSamplingStr.size();
        for(i = 0; i < count; i++)
        {
            temp = QString(tr("数据采集")) + QString::number(i);
            HaveThisStr = false;

            for(j = 0; j < count; j++)
            {
                if(pwnd->m_pSamSysParame->m_vecDataSamplingStr.at(j) == temp)
                {
                    HaveThisStr = true;
                    break;
                }
            }

            if(HaveThisStr == false)//当前temp字符串没有被用的时候
            {
                str = temp;
                break;
            }
        }
        if(i == count)
        {
            str = QString(tr("数据采集")) + QString::number(count);
        }

        pwnd->m_pSamSysParame->m_vecDataSamplingStr.push_back(str);
    }
    ui->lineEdit_name->setText(pwnd->m_pSamSysParame->m_vecDataSamplingStr.at(curSamp));



    //这里对表进行操作
    ui->tableWidget->verticalHeader()->hide();//隐藏表头
	show_table_srand_addr();
    

    //////////////////////////////////模式页/////////////////////////////////////////
    

    ui->comboBox_timeFreqUint->addItem(tr("200毫秒"));
    ui->comboBox_timeFreqUint->addItem(tr("秒"));
    ui->comboBox_timeFreqUint->addItem(tr("分钟"));
    ui->comboBox_timeFreqUint->addItem(tr("小时"));
    ui->comboBox_timeFreqUint->addItem(tr("天"));

    ui->comboBox_cycFreqUnit->addItem(tr("200毫秒"));
    ui->comboBox_cycFreqUnit->addItem(tr("秒"));
    ui->comboBox_cycFreqUnit->addItem(tr("分钟"));
    ui->comboBox_cycFreqUnit->addItem(tr("小时"));
    ui->comboBox_cycFreqUnit->addItem(tr("天"));


    if(1 == pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].nDataSampType)//实时采集
    {
        ui->radioButton->setChecked(true);
        ui->radioButton_2->setChecked(false);

        ui->groupBox_full->setEnabled(false);
        ui->groupBox_other->setEnabled(false);

        ui->groupBox_2->setEnabled(false);
    }
    else
    {
        ui->radioButton->setChecked(false);
        ui->radioButton_2->setChecked(true);

        ui->groupBox_full->setEnabled(true);
        ui->groupBox_other->setEnabled(true);

        ui->groupBox_2->setEnabled(true);
    }

    if(SampTime == pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].eSampType)//采样方式的选择
    {
		bool bValue = false;
		bValue = pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].bDynTimeRange;
		if (bValue)
		{
			ui->edit_starttimeAddr->setText(
				pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].startTimeAddr.sShowAddr);
			ui->edit_endtimeAddr->setText(
				pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].endTimeAddr.sShowAddr);
		}
        ui->radioButton_styTime->setChecked(true);

		setDynTimeUi(bValue);
		bValue = pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].bDynSampleRate;
		if (bValue)
		{
			ui->edit_rateAddr->setText(
				pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].dynRateAddr.sShowAddr);
			
		}

		setDynRateUi(bValue);
		setDynRateUi_cycle(false);
		
		
		
    }
    else if(SampCycle == pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].eSampType)
    {
		bool bValue = false;
		bValue = pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].bDynSampleRate;
		if (bValue)
		{
			ui->edit_rateAddr_2->setText(
				pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].dynRateAddr.sShowAddr);

		}
        ui->radioButton_styCycle->setChecked(true);
		setDynRateUi_cycle(bValue);
		setDynTimeUi(false);
		setDynRateUi(false);
    }
    else
    {
        ui->radioButton_styControl->setChecked(true);
		setDynTimeUi(false);
		setDynRateUi(false);
		setDynRateUi_cycle(false);
    }

    if(SFStop == pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].eDealSampFull)//取满处理方式
    {
        ui->radioButton_stop->setChecked(true);
    }
    else if(SFClear == pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].eDealSampFull)
    {
        ui->radioButton_begin->setChecked(true);
    }
    else
    {
        ui->radioButton_replace->setChecked(true);
    }

    ui->checkBox_timeAddrCtl->setChecked(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].bAddrCtlSamp);//时间采样位地址控制
    ui->checkBox_cycAddrCtl->setChecked(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].bAddrCtlSamp);//周期采样位地址控制

    ui->lineEdit_timeAddr->setText(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].strCtlSampAddrId.sShowAddr);//时间采样地址值
    ui->lineEdit_cycAddr->setText(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].strCtlSampAddrId.sShowAddr);//周期采样地址值
    ui->lineEdit_ctlAddr->setText(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].strCtlSampAddrId.sShowAddr);//位ON控制采样地址值

    ui->spinBox_timeFreq->setValue(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].nSampRate);//时间采样频率值
    ui->comboBox_timeFreqUint->setCurrentIndex(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].nSampRateUnit);
    ui->spinBox_cycFreq->setValue(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].nSampRate);//周期采样频率值
    ui->comboBox_cycFreqUnit->setCurrentIndex(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].nSampRateUnit);

  
    ui->checkBox_cycReset->setVisible(false);
    //ui->checkBox_cycReset->setChecked(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].bAutoReset);//周期采样是否自动复位
    ui->checkBox_ctlReset->setChecked(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].bAutoReset);//控制采样是否自动复位

    ui->spinBox_beginHour->setValue(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].nStartHour);//时间采样的起止时间设置
    ui->spinBox_beginMinute->setValue(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].nStartMinute);
    ui->spinBox_endHour->setValue(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].nEndHour);
    ui->spinBox_endMinute->setValue(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].nEndMinute);

    
    ui->checkBox_notify->setChecked(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].bFullNotic);//是否取满通知
    ui->lineEdit_notify->setText(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].strNoticAddrId.sShowAddr);//取满通知地址

    if(ui->checkBox_cycAddrCtl->isChecked())
    {
        
        ui->lineEdit_cycAddr->setEnabled(true);
        ui->pushButton_cycAddr->setEnabled(true);

        //ui->checkBox_cycReset->show();
    }
    else
    {
        
        ui->lineEdit_cycAddr->setEnabled(false);
        ui->pushButton_cycAddr->setEnabled(false);

        //ui->checkBox_cycReset->hide();
    }
    //////////////////////////////////保存输出页/////////////////////////////////////////
    //日期格式
    ui->comboBox_dateFormat->addItem(tr("YYYY/MM/DD"));
    ui->comboBox_dateFormat->addItem(tr("YYYY.MM.DD"));
    ui->comboBox_dateFormat->addItem(tr("YYYY-MM-DD"));
    ui->comboBox_dateFormat->addItem(tr("MM/DD/YYYY"));
    ui->comboBox_dateFormat->addItem(tr("MM.DD.YYYY"));
    ui->comboBox_dateFormat->addItem(tr("MM-DD-YYYY"));
    ui->comboBox_dateFormat->addItem(tr("DD/MM/YYYY"));
    ui->comboBox_dateFormat->addItem(tr("DD.MM.YYYY"));
    ui->comboBox_dateFormat->addItem(tr("DD-MM-YYYY"));

    //ui->spinBox_decimalDigit->hide();
    //ui->label_15->hide();

    ui->checkBox_saveFile->setChecked(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].bSaveToFile);//是否保存文件
    ui->lineEdit_ctlWordAddr->setText(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].keyCtlSaveAddr.sShowAddr);//保存文件的控制地址

    ui->check_autosave->setChecked(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].bAutoSave);//是否保存文件

    //ui->radioButton_CFcard->hide();
    if(SM_Udisk == pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].eSaveMedium)//保存位置
    {
        ui->radioButton_Udisk->setChecked(true);
    }
    else if(SM_CFcard == pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].eSaveMedium)
    {
        //ui->radioButton_CFcard->setChecked(true);
    }
    else
    {
        ui->radioButton_SDcard->setChecked(true);
    }

    model.setColumnCount(8);
    model.setRowCount(2);
    ui->tableView->setModel(&model);
    //禁止编辑数据表
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    model.setData(model.index(0, 0, QModelIndex()), QVariant(tr("")));
    model.setData(model.index(0, 1, QModelIndex()), QVariant(tr("项目名称")));
    model.setData(model.index(0, 2, QModelIndex()), QVariant(tr("日期")));
    model.setData(model.index(0, 3, QModelIndex()), QVariant(tr("时间")));
    model.setData(model.index(0, 4, QModelIndex()), QVariant(tr("LB0")));
    model.setData(model.index(0, 5, QModelIndex()), QVariant(tr("LB1")));
    model.setData(model.index(0, 6, QModelIndex()), QVariant(tr("LB2")));
    model.setData(model.index(0, 7, QModelIndex()), QVariant(tr("....")));

    model.setData(model.index(1, 0, QModelIndex()), QVariant(tr("显示数据")));
    model.setData(model.index(1, 1, QModelIndex()), QVariant(tr("")));
    model.setData(model.index(1, 2, QModelIndex()), QVariant(ui->comboBox_dateFormat->currentText()));
    model.setData(model.index(1, 3, QModelIndex()), QVariant(tr("hh:mm:ss")));
    model.setData(model.index(1, 4, QModelIndex()), QVariant(tr("xxxx")));
    model.setData(model.index(1, 5, QModelIndex()), QVariant(tr("xxxx")));
    model.setData(model.index(1, 6, QModelIndex()), QVariant(tr("xxxx")));
    model.setData(model.index(1, 7, QModelIndex()), QVariant(tr("....")));

    ui->tableView->show();

    ////////////////////////////////界面相关控件的隐藏//////////////////////////////////
    if(!ui->checkBox_timeAddrCtl->isChecked())//隐藏固定时间采样组框中的地址栏
    {
        ui->lineEdit_timeAddr->setEnabled(false);
        ui->pushButton_timeAddr->setEnabled(false);
    }

    if(!ui->checkBox_cycAddrCtl->isChecked())//隐藏恒定周期采样组框中的地址栏
    {
        ui->lineEdit_cycAddr->setEnabled(false);
        ui->pushButton_cycAddr->setEnabled(false);

        //ui->checkBox_cycReset->hide();
    }

    if(!ui->checkBox_notify->isChecked())//隐藏是否取满通知的通知地址栏
    {
        ui->label_11->setEnabled(false);
        ui->lineEdit_notify->setEnabled(false);
        ui->pushButton_notify->setEnabled(false);
    }

    if(!ui->radioButton_styTime->isChecked())//如果没有选中固定时间采样，隐藏他下面的组框
    {
        //ui->groupBox_time->hide();
        ui->groupBox_time->setDisabled(true);
    }

    if(!ui->radioButton_styCycle->isChecked())//如果没有选中恒定周期采样，隐藏他下面的组框
    {
        //ui->groupBox_cycle->hide();
        ui->groupBox_cycle->setDisabled(true);
    }

    if(!ui->radioButton_styControl->isChecked())//如果没有选中位ON时控制采样，隐藏他下面的组框
    {
        //ui->groupBox_control->hide();
        ui->groupBox_control->setDisabled(true);
    }



    if(!ui->checkBox_saveFile->isChecked())
    {
        //ui->groupBox_baseDataSet->setEnabled(false);
        //ui->groupBox_zoom->setEnabled(false);

        ui->label_22->setEnabled(false);
        ui->lineEdit_ctlWordAddr->setEnabled(false);
        ui->pushButton_ctlWordAddr->setEnabled(false);
    }
    else
    {
        //ui->groupBox_baseDataSet->setEnabled(true);

		

        ui->label_22->setEnabled(true);
        ui->lineEdit_ctlWordAddr->setEnabled(true);
        ui->pushButton_ctlWordAddr->setEnabled(true);

        ui->lineEdit_ctlWordAddr->setText(m_dataSampling.keyCtlSaveAddr.sShowAddr);
        if(m_dataSampling.keyCtlSaveAddr.sShowAddr == "")
        {
            ui->lineEdit_ctlWordAddr->setText(tr("LW0"));
            pwnd->IsAddressCheckRight(m_dataSampling.keyCtlSaveAddr, tr("控制字地址"), ui->lineEdit_ctlWordAddr, 1);
        }
    }

    if(ui->check_autosave->isChecked())
    {
        ui->label_28->setEnabled(true);
        ui->label_29->setEnabled(true);
        ui->spin_hour->setEnabled(true);
        ui->spin_hour->setValue(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].nSaveHour);//保存文件的控制地址

    }
    else
    {
        ui->label_28->setEnabled(false);
        ui->label_29->setEnabled(false);
        ui->spin_hour->setEnabled(false);
    }
    ui->check_Print->setChecked(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].bPrint);
    ui->check_Date->setChecked(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].bPrintDate);
    ui->check_Time->setChecked(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].bPrintTime);
    on_check_Print_clicked(pwnd->m_pSamSysParame->m_loadDataSampling[curSamp].bPrint);

	ui->groupBox_baseDataSet->setDisabled(!ui->checkBox_saveFile->isChecked() && !ui->check_autosave->isChecked());
    ///////////////////////////////初始化结束////////////////////////////////
    bInitFinish = true;

    ui->tableWidget->setCurrentCell(0,0);
	connect(ui->btn_add,SIGNAL(clicked()),this,SLOT(on_add()));
	connect(ui->btn_delete,SIGNAL(clicked()),this,SLOT(on_delete()));
	connect(ui->check_dynamicTime,SIGNAL(clicked(bool)),this,SLOT(setDynTimeUi(bool)));
	connect(ui->check_dynaminRate,SIGNAL(clicked(bool)),this,SLOT(setDynRateUi(bool)));
	connect(ui->check_dynaminRate_2,SIGNAL(clicked(bool)),this,SLOT(setDynRateUi_cycle(bool)));
	connect(ui->btn_startAddr,SIGNAL(clicked()),this,SLOT(on_btn_startAddr()));
	connect(ui->btn_endAddr,SIGNAL(clicked()),this,SLOT(on_btn_endAddr()));
	connect(ui->btn_rateAddr,SIGNAL(clicked()),this,SLOT(on_btn_rateAddr()));
	connect(ui->btn_rateAddr_2,SIGNAL(clicked()),this,SLOT(on_btn_rateAddr_2()));
	
}

qdataloggerdlg::~qdataloggerdlg()
{
    delete ui;
}

///////////////////////////////////地址属性页slot///////////////////////////////
void qdataloggerdlg::on_radioButton_addrConti_clicked(bool checked)//选中连续地址
{
    m_dataSampling.bContiguousAddr = true;

//     if(checked)
//     {
//         ui->label_12->show();
//         ui->lineEdit_addrBegin->show();
//         ui->pushButton_addrBegin->show();
// 
//         ui->spinBox_allWords->setValue(m_dataSampling.nSampAddrLen);
//         ui->spinBox_allWords->show();
// 
//         ui->label_13->hide();
// 
//         show_table_continous_addr();
//     }
}

void qdataloggerdlg::on_radioButton_addrRand_clicked(bool checked)//选中随机地址
{
    m_dataSampling.bContiguousAddr = false;

//     if(checked)
//     {
//         //重新计算随机地址，并保存在m_dataSampling
//         ui->label_12->hide();
//         ui->lineEdit_addrBegin->hide();
//         ui->pushButton_addrBegin->hide();
// 
//         ui->spinBox_allWords->hide();
// 
//         ui->label_13->setText(QString::number(m_dataSampling.nSampAddrLen));
//         ui->label_13->show();
// 
//         show_table_srand_addr();
//     }
}

void qdataloggerdlg::on_radioButton_16bit_clicked(bool checked)//位长16位被选中
{
    m_dataSampling.nDigitLen = 16;

    if(checked)
    {
        if(true == m_dataSampling.bContiguousAddr)//假如是连续地址
        {
            show_table_continous_addr();
        }
        else
        {
            show_table_srand_addr();
        }
    }
}

void qdataloggerdlg::on_radioButton_32bit_clicked(bool checked)//位长32位被选中
{
    m_dataSampling.nDigitLen = 32;

    if(checked)
    {
        if(true == m_dataSampling.bContiguousAddr)//假如是连续地址
        {
            show_table_continous_addr();
        }
        else
        {
            show_table_srand_addr();
        }
    }
}

void qdataloggerdlg::on_spinBox_allWords_valueChanged(int num)//采样总字数改变,此时只可能是连续地址
{
    show_table_continous_addr();
}

void qdataloggerdlg::on_pushButton_addrBegin_clicked()//采样地址编辑按钮被点击
{
}

//双击tablewidget中的一项
void qdataloggerdlg::on_TableDClick(int row, int colum)
{
    int curRow;
    DATA_ADDRESS_ITEM item;
    item.keyAddress.sShowAddr = "LW0";
    item.nAddrNumber = row;
    item.dataType = DATA_TYPE(2);
    item.bZoom = false;
    item.decLen = 0;
    item.name = "Data" + QString::number(row);

    bool isHave = false;
    QTableWidgetItem *tableItem = ui->tableWidget->item(row,1);
    foreach(DATA_ADDRESS_ITEM cItem,m_dataSampling.m_dataTable)
    {
        if (cItem.nAddrNumber == row)
        {
            item = cItem;
            isHave = true;
            break;
        }
    }

    InsertDataSample insertDlg(item,this);
    if (insertDlg.exec() == QDialog::Accepted)
    {
        item = insertDlg.m_Item;
        QVector<Keyboard>addrs = insertDlg.getAddrs();
        for (curRow=row; curRow<addrs.size()+row; curRow++)
        {
            bool bExist = false;
            int index = 0;
            if(!isHave)
            {
                //item.name = "Data" + QString::number(curRow);
            }
            item.nAddrNumber = curRow;
            item.keyAddress = addrs.at(curRow-row);

            QTableWidgetItem *numberItem = ui->tableWidget->item(curRow,0);
            if (numberItem && !numberItem->text().isEmpty())
            {
                foreach(DATA_ADDRESS_ITEM cItem,m_dataSampling.m_dataTable)
                {
                    if (cItem.nAddrNumber == curRow)
                    {
                        bExist = true;
                        break;
                    }
                    index++;
                }
            }

            if (bExist)
            {
                m_dataSampling.m_dataTable.replace(index,item);
            }
            else
            {
                m_dataSampling.m_dataTable << item;
            }

            ui->tableWidget->setItem(curRow,1,new QTableWidgetItem(item.name));
            QTableWidgetItem * tableItem = new QTableWidgetItem(item.keyAddress.sShowAddr);
            ui->tableWidget->setItem(curRow,2,tableItem);
            ui->tableWidget->setItem(curRow,3,new QTableWidgetItem(insertDlg.getDatatypeStr()));
            QString sExchanged = tr("无");
            if(item.bZoom)
            {
                sExchanged = tr("采集范围");
                sExchanged += QString("(%1,%2)")
                              .arg(QString::number(item.inputMin)).arg(QString::number(item.inputMax));
                sExchanged += tr(" 输出范围");
                sExchanged += QString("(%1,%2)")
                              .arg(QString::number(item.outputMin)).arg(QString::number(item.outputMax));
            }
            ui->tableWidget->setItem(curRow,4,new QTableWidgetItem(sExchanged));
            ui->tableWidget->setCurrentItem(tableItem);
        }
    }
}

///////////////////////////////////模式属性页slot///////////////////////////////
///////----------------时间采样部分---------------------
void qdataloggerdlg::on_radioButton_styTime_clicked(bool checked)//点击固定时间采样
{
    if(checked)
    {
        //组框设置有效或者无效
        ui->groupBox_time->setEnabled(true);
        ui->groupBox_cycle->setEnabled(false);
        ui->groupBox_control->setEnabled(false);

        //组框设置是否选中
        ui->radioButton_styTime->setChecked(true);
        ui->radioButton_styCycle->setChecked(false);
        ui->radioButton_styControl->setChecked(false);

        m_dataSampling.eSampType = SampTime;

        //假如地址控制是要显示的，因为3个部分公用变量，其他部分可能改变这个值
        if(m_dataSampling.bAddrCtlSamp == true)
        {
            ui->lineEdit_timeAddr->setEnabled(true);
            ui->pushButton_timeAddr->setEnabled(true);

            ui->lineEdit_timeAddr->setText(m_dataSampling.strCtlSampAddrId.sShowAddr);
        }
        else
        {
            ui->lineEdit_timeAddr->setEnabled(false);
            ui->pushButton_timeAddr->setEnabled(false);
        }
        ui->checkBox_timeAddrCtl->setChecked(m_dataSampling.bAddrCtlSamp);

        ui->spinBox_timeFreq->setValue(m_dataSampling.nSampRate);
        ui->comboBox_timeFreqUint->setCurrentIndex(m_dataSampling.nSampRateUnit);

        return;
    }

    ui->radioButton_styTime->setChecked(true);
}

void qdataloggerdlg::on_checkBox_timeAddrCtl_clicked(bool checked)//时间采样的位地址控制
{
    if(checked)
    {
        ui->lineEdit_timeAddr->setEnabled(true);
        ui->pushButton_timeAddr->setEnabled(true);

        if(m_dataSampling.strCtlSampAddrId.sShowAddr == "")//显示默认的地址或者已经存在的地址
        {
            m_dataSampling.strCtlSampAddrId.sPlcAddrValue = "0";

            m_dataSampling.strCtlSampAddrId.sShowAddr =
                m_dataSampling.strCtlSampAddrId.sPlcRegTypeStr +
                m_dataSampling.strCtlSampAddrId.sPlcAddrValue;
        }
        ui->lineEdit_timeAddr->setText(m_dataSampling.strCtlSampAddrId.sShowAddr);
    }
    else
    {
        ui->lineEdit_timeAddr->setEnabled(false);
        ui->pushButton_timeAddr->setEnabled(false);
    }

    m_dataSampling.bAddrCtlSamp = checked;
}

void qdataloggerdlg::on_spinBox_beginHour_valueChanged(int value)//开始时间，小时
{
    //ui->spinBox_beginHour->setValue(value);
    //ui->spinBox_beginHour->clearFocus();

    m_dataSampling.nStartHour = value;
}

void qdataloggerdlg::on_spinBox_beginMinute_valueChanged(int value)//开始时间，分钟
{
    //ui->spinBox_beginMinute->setValue(value);
    //ui->spinBox_beginMinute->clearFocus();

    m_dataSampling.nStartMinute = value;
}

void qdataloggerdlg::on_spinBox_endHour_valueChanged(int value)//结束时间，小时
{
    //ui->spinBox_endHour->setValue(value);
    //ui->spinBox_endHour->clearFocus();

    m_dataSampling.nEndHour = value;
}

void qdataloggerdlg::on_spinBox_endMinute_valueChanged(int value)//结束时间，分钟
{
    //ui->spinBox_endMinute->setValue(value);
    //ui->spinBox_endMinute->clearFocus();

    m_dataSampling.nEndMinute = value;
}

void qdataloggerdlg::on_spinBox_timeFreq_valueChanged(int value)//时间采样的频率
{
    //ui->spinBox_timeFreq->setValue(value);
    //ui->spinBox_timeFreq->clearFocus();

    m_dataSampling.nSampRate = value;
}

void qdataloggerdlg::on_pushButton_timeAddr_clicked()//时间采样地址按钮被点击
{
    pwnd->Addr_Type = 0;
    AddressInputDialog dlg_readaddress(m_dataSampling.strCtlSampAddrId,this);
    dlg_readaddress.exec();

    ui->lineEdit_timeAddr->setText(m_dataSampling.strCtlSampAddrId.sShowAddr);
}

void qdataloggerdlg::on_lineEdit_timeAddr_editingFinished()
{
    //czq
    if(!pwnd->IsAddressCheckRight(m_dataSampling.strCtlSampAddrId, tr("位控制地址"), ui->lineEdit_timeAddr, 0))
    //if(!pwnd->IsMyAddressCheckRight(m_dataSampling.strCtlSampAddrId, tr("位控制地址"), ui->lineEdit_timeAddr, 0, NULL))
    {
        QMessageBox::about(ui->lineEdit_timeAddr, tr("warning"), tr("位控制地址错误"));
        ui->lineEdit_timeAddr->setText(m_dataSampling.strCtlSampAddrId.sShowAddr);
    }
}

///////----------------周期采样部分---------------------
void qdataloggerdlg::on_radioButton_styCycle_clicked(bool checked)//点击恒定周期采样
{
    if(checked)
    {
        ui->groupBox_time->setEnabled(false);
        ui->groupBox_cycle->setEnabled(true);
        ui->groupBox_control->setEnabled(false);

        ui->radioButton_styTime->setChecked(false);
        ui->radioButton_styCycle->setChecked(true);
        ui->radioButton_styControl->setChecked(false);

        m_dataSampling.eSampType = SampCycle;

        ui->spinBox_cycFreq->setValue(m_dataSampling.nSampRate);//采样频率
        ui->comboBox_cycFreqUnit->setCurrentIndex(m_dataSampling.nSampRateUnit);

        //ui->spinBox_cycCount->setValue(m_dataSampling.nSampTimes);//采样字数
        //ui->comboBox_cycCountUnit->setCurrentIndex(m_dataSampling.nSampCountUnit);

        if(m_dataSampling.bAutoReset == true)
        {
            //ui->checkBox_cycReset->setChecked(true);
        }
        else
        {
            //ui->checkBox_cycReset->setChecked(false);
        }

        if(m_dataSampling.bAddrCtlSamp == true)
        {
            ui->lineEdit_cycAddr->setEnabled(true);
            ui->pushButton_cycAddr->setEnabled(true);

            //ui->checkBox_cycReset->setEnabled(true);

            ui->lineEdit_cycAddr->setText(m_dataSampling.strCtlSampAddrId.sShowAddr);
        }
        else
        {
            ui->lineEdit_cycAddr->setEnabled(false);
            ui->pushButton_cycAddr->setEnabled(false);

            //ui->checkBox_cycReset->hide();
        }
        ui->checkBox_cycAddrCtl->setChecked(m_dataSampling.bAddrCtlSamp);

        return;
    }

    ui->radioButton_styCycle->setChecked(true);
}

void qdataloggerdlg::on_checkBox_cycAddrCtl_clicked(bool checked)//周期采样的位地址控制
{
    if(checked)
    {
        ui->lineEdit_cycAddr->setEnabled(true);
        ui->pushButton_cycAddr->setEnabled(true);

        //ui->checkBox_cycReset->show();

        if(m_dataSampling.strCtlSampAddrId.sShowAddr == "")//显示默认的地址或者已经存在的地址
        {
            m_dataSampling.strCtlSampAddrId.sPlcAddrValue = "0";

            m_dataSampling.strCtlSampAddrId.sShowAddr =
                m_dataSampling.strCtlSampAddrId.sPlcRegTypeStr +
                m_dataSampling.strCtlSampAddrId.sPlcAddrValue;
        }
        ui->lineEdit_cycAddr->setText(m_dataSampling.strCtlSampAddrId.sShowAddr);
    }
    else
    {
        ui->lineEdit_cycAddr->setEnabled(false);
        ui->pushButton_cycAddr->setEnabled(false);
        //ui->checkBox_cycReset->hide();
    }

    m_dataSampling.bAddrCtlSamp = checked;
}

void qdataloggerdlg::on_spinBox_cycFreq_valueChanged(int value)
{
    //ui->spinBox_cycFreq->setValue(value);
    //ui->spinBox_cycFreq->clearFocus();

    m_dataSampling.nSampRate = value;
}

/*void qdataloggerdlg::on_radioButton_second_clicked()
{
    m_dataSampling.bSampTime = true;
}

void qdataloggerdlg::on_radioButton_milsecond_clicked()
{
    m_dataSampling.bSampTime = false;
}*/

void qdataloggerdlg::on_lineEdit_cycAddr_editingFinished()
{
    
}

void qdataloggerdlg::on_pushButton_cycAddr_clicked()
{
    //czq
    //pwnd->Addr_Type = 0;
    pwnd->Addr_Type = 0;
    AddressInputDialog dlg_readaddress(m_dataSampling.strCtlSampAddrId,this);
    dlg_readaddress.exec();

    ui->lineEdit_cycAddr->setText(m_dataSampling.strCtlSampAddrId.sShowAddr);
}

void qdataloggerdlg::on_spinBox_cycCount_valueChanged(int value)
{
    //ui->spinBox_cycCount->setValue(value);
    //ui->spinBox_cycCount->clearFocus();

    m_dataSampling.nSampTimes = value;
}

void qdataloggerdlg::on_checkBox_cycReset_clicked(bool checked)
{
    m_dataSampling.bAutoReset = checked;
}

///////----------------位ON时控制采样部分---------------------
void qdataloggerdlg::on_radioButton_styControl_clicked(bool checked)//点击位ON时控制采样
{
    if(checked)
    {
        ui->groupBox_time->setEnabled(false);
        ui->groupBox_cycle->setEnabled(false);
        ui->groupBox_control->setEnabled(true);

        ui->radioButton_styTime->setChecked(false);
        ui->radioButton_styCycle->setChecked(false);
        ui->radioButton_styControl->setChecked(true);

        m_dataSampling.eSampType = SampControl;

        //ui->spinBox_ctlCount->setValue(m_dataSampling.nSampTimes);//采样次数
        //ui->comboBox_ctlCountUnit->setCurrentIndex(m_dataSampling.nSampCountUnit);

        ui->lineEdit_ctlAddr->setText(m_dataSampling.strCtlSampAddrId.sShowAddr);

        if(m_dataSampling.bAutoReset == true)
        {
            ui->checkBox_ctlReset->setChecked(true);
        }
        else
        {
            ui->checkBox_ctlReset->setChecked(false);
        }

        return;
    }

    ui->radioButton_styControl->setChecked(true);
}

void qdataloggerdlg::on_spinBox_ctlCount_valueChanged(int value)
{
    //ui->spinBox_ctlCount->setValue(value);
    //ui->spinBox_ctlCount->clearFocus();

    m_dataSampling.nSampTimes = value;
}

void qdataloggerdlg::on_lineEdit_ctlAddr_editingFinished()
{
    
}

void qdataloggerdlg::on_pushButton_ctlAddr_clicked()
{
    //czq
    //pwnd->Addr_Type = 0;
    pwnd->Addr_Type = 0;
    AddressInputDialog dlg_readaddress(m_dataSampling.strCtlSampAddrId,this);
    dlg_readaddress.exec();

    ui->lineEdit_ctlAddr->setText(m_dataSampling.strCtlSampAddrId.sShowAddr);
}

void qdataloggerdlg::on_checkBox_ctlReset_clicked(bool checked)
{
    m_dataSampling.bAutoReset = checked;
}

///////----------------其他部分---------------------
void qdataloggerdlg::on_radioButton_stop_clicked(bool checked)
{
    if(checked)
    {
        m_dataSampling.eDealSampFull = SFStop;
    }
}

void qdataloggerdlg::on_radioButton_begin_clicked(bool checked)
{
    if(checked)
    {
        m_dataSampling.eDealSampFull = SFClear;
    }
}

void qdataloggerdlg::on_radioButton_replace_clicked(bool checked)
{
    if(checked)
    {
        m_dataSampling.eDealSampFull = SFReplace;
    }
}

void qdataloggerdlg::on_spinBox_maxNum_valueChanged(int value)
{
    //ui->spinBox_maxNum->setValue(value);
    //ui->spinBox_maxNum->clearFocus();

    //m_dataSampling.nTotalSampNum = value;
    m_dataSampling.nSampTime =  value;
}

void qdataloggerdlg::on_checkBox_notify_clicked(bool checked)//取满是否通知
{
    if(checked)
    {
        ui->label_11->setEnabled(true);
        ui->lineEdit_notify->setEnabled(true);
        ui->pushButton_notify->setEnabled(true);

        if(m_dataSampling.strNoticAddrId.sShowAddr == "")
        {
            ui->lineEdit_notify->setText(tr("LB0"));
            pwnd->IsAddressCheckRight(m_dataSampling.strNoticAddrId, tr("通知地址"), ui->lineEdit_notify, 0);
        }
    }
    else
    {
        ui->label_11->setEnabled(false);
        ui->lineEdit_notify->setEnabled(false);
        ui->pushButton_notify->setEnabled(false);
    }

    m_dataSampling.bFullNotic = checked;
}

void qdataloggerdlg::on_lineEdit_notify_editingFinished()
{
    //czq
    if(!pwnd->IsAddressCheckRight(m_dataSampling.strNoticAddrId, tr("取满通知地址"), ui->lineEdit_notify, 0))
    //if(!pwnd->IsMyAddressCheckRight(m_dataSampling.strNoticAddrId, tr("取满通知地址"), ui->lineEdit_notify, 1, NULL))
    {
        QMessageBox::about(ui->lineEdit_notify, tr("warning"), tr("取满通知地址错误"));
        ui->lineEdit_notify->setText(m_dataSampling.strNoticAddrId.sShowAddr);
    }
}

void qdataloggerdlg::on_pushButton_notify_clicked()
{
    //czq
    pwnd->Addr_Type = 0;
    //pwnd->Addr_Type = 1;
    AddressInputDialog dlg_readaddress(m_dataSampling.strNoticAddrId, this);
    dlg_readaddress.exec();

    ui->lineEdit_notify->setText(m_dataSampling.strNoticAddrId.sShowAddr);
}

///////////////////////////////////保存输出属性页slot///////////////////////////
void qdataloggerdlg::on_checkBox_saveFile_clicked(bool checked)//是否保存位CSV文件
{
    m_dataSampling.bSaveToFile = checked;

    if(checked)
    {
        ui->groupBox_baseDataSet->setEnabled(true);

        

        ui->label_22->setEnabled(true);
        ui->lineEdit_ctlWordAddr->setEnabled(true);
        ui->pushButton_ctlWordAddr->setEnabled(true);

        ui->lineEdit_ctlWordAddr->setText(m_dataSampling.keyCtlSaveAddr.sShowAddr);
        if(m_dataSampling.keyCtlSaveAddr.sShowAddr == "")
        {
            ui->lineEdit_ctlWordAddr->setText(tr("LW0"));
            pwnd->IsAddressCheckRight(m_dataSampling.keyCtlSaveAddr, tr("控制字地址"), ui->lineEdit_ctlWordAddr, 1);
        }
    }
    else
    {
        if(!ui->check_autosave->isChecked())
            ui->groupBox_baseDataSet->setEnabled(false);
        //ui->groupBox_zoom->setEnabled(false);

        ui->label_22->setEnabled(false);
        ui->lineEdit_ctlWordAddr->setEnabled(false);
        ui->pushButton_ctlWordAddr->setEnabled(false);
    }
}

void qdataloggerdlg::on_lineEdit_ctlWordAddr_editingFinished()//控制字地址编辑框
{
    //czq

}

void qdataloggerdlg::on_pushButton_ctlWordAddr_clicked()//控制字地址按钮
{
    //czq
    //pwnd->Addr_Type = 0;
    pwnd->Addr_Type = 1;
    AddressInputDialog dlg_readaddress(m_dataSampling.keyCtlSaveAddr, this);
    dlg_readaddress.exec();

    ui->lineEdit_ctlWordAddr->setText(m_dataSampling.keyCtlSaveAddr.sShowAddr);
}

void qdataloggerdlg::on_radioButton_Udisk_clicked()//存储在U盘
{
    m_dataSampling.eSaveMedium = SM_Udisk;
}

void qdataloggerdlg::on_radioButton_CFcard_clicked()//存储在CF卡
{
    m_dataSampling.eSaveMedium = SM_CFcard;
}

void qdataloggerdlg::on_radioButton_SDcard_clicked()//存储在SD卡
{
    m_dataSampling.eSaveMedium = SM_SDcard;
}

void qdataloggerdlg::on_checkBox_zoom_clicked(bool checked)//是否缩放
{
    
}

void qdataloggerdlg::on_checkBox_suppression_clicked(bool checked)//是否0抑制
{
}

void qdataloggerdlg::on_spinBox_totalDigit_valueChanged(int value)//总位数
{
    m_dataSampling.nDataLen = value;
    //ui->spinBox_totalDigit->setValue(value);
    //ui->spinBox_totalDigit->clearFocus();
}

void qdataloggerdlg::on_spinBox_decimalDigit_valueChanged(int value)//小数位数
{
    if(value < m_dataSampling.nDataLen)//小数位数要小于总位数
    {
        m_dataSampling.nDecimalLen = value;
        //ui->spinBox_decimalDigit->setValue(value);

    }
    else
    {
        m_dataSampling.nDecimalLen = 0;
        //ui->spinBox_decimalDigit->setValue(0);
        //QMessageBox::about(ui->spinBox_decimalDigit, tr("warning"), tr("小数位数要比总位数小"));
    }
    //ui->spinBox_decimalDigit->clearFocus();
}

void qdataloggerdlg::on_comboBox_dataFormat_currentIndexChanged(int index)//数据格式
{
}

void qdataloggerdlg::on_comboBox_dateFormat_currentIndexChanged(int index)//日期格式
{
    m_dataSampling.eDateShowType = (SaveDateType)(index + 1);
    //ui->comboBox_dateFormat->setCurrentIndex(index);
    model.setData(model.index(1, 2, QModelIndex()), QVariant(ui->comboBox_dateFormat->currentText()));
}

void qdataloggerdlg::on_doubleSpinBox_desMax_valueChanged(double value)//目标最大值
{
    
}

void qdataloggerdlg::on_doubleSpinBox_desMin_valueChanged(double value)//目标最小值
{
    
}

void qdataloggerdlg::on_doubleSpinBox_srcMax_valueChanged(double value)//源最大值
{
}

void qdataloggerdlg::on_doubleSpinBox_srcMin_valueChanged(double value)//源最小值
{
}

void qdataloggerdlg::on_checkBox_rounding_clicked(bool checked)//是否四舍五入
{
}

///////////////////////////////////确定，取消，帮助slot//////////////////////////
void qdataloggerdlg::on_cancel_clicked()//取消
{
    this->close();
}

void qdataloggerdlg::on_help_clicked()//帮助
{
    pwnd->loadHelpHtm(TREE_HISDATA_RECORD);
}

void qdataloggerdlg::on_accept_clicked()//确定
{
	if(m_dataSampling.eSampType == SampTime)
	{
		bool bType = 1;
		m_dataSampling.bDynTimeRange = ui->check_dynamicTime->isChecked();
		m_dataSampling.bDynSampleRate = ui->check_dynaminRate->isChecked();
		if(ui->check_dynamicTime->isChecked() && 
			! pwnd->IsAddressCheckRight(m_dataSampling.startTimeAddr,tr("开始时间地址"),ui->edit_starttimeAddr,bType))
		{
			ui->edit_starttimeAddr->setFocus();
			return ;
		}
		if(ui->check_dynamicTime->isChecked() && 
			! pwnd->IsAddressCheckRight(m_dataSampling.endTimeAddr,tr("结束时间地址"),ui->edit_endtimeAddr,bType))
		{
			ui->edit_endtimeAddr->setFocus();
			return ;
		}
		if(ui->check_dynaminRate->isChecked() && 
			! pwnd->IsAddressCheckRight(m_dataSampling.dynRateAddr,tr("采样频率地址"),ui->edit_rateAddr,bType))
		{
			ui->edit_rateAddr->setFocus();
			return ;
		}
		if(ui->checkBox_timeAddrCtl->isChecked() && 
			!pwnd->IsAddressCheckRight(m_dataSampling.strCtlSampAddrId, tr("位控制地址"), ui->lineEdit_timeAddr, 0))
		{
			ui->lineEdit_timeAddr->setFocus();
			return;
		}
		
	}
	else if (m_dataSampling.eSampType == SampCycle)
	{
		if(ui->check_dynaminRate_2->isChecked() &&
			! pwnd->IsAddressCheckRight(m_dataSampling.dynRateAddr,tr("开始时间地址"),ui->edit_rateAddr_2,1))
		{
			ui->edit_rateAddr_2->setFocus();
			return ;
		}
		if(ui->checkBox_cycAddrCtl->isChecked() &&
			!pwnd->IsAddressCheckRight(m_dataSampling.strCtlSampAddrId, tr("位控制地址"), ui->lineEdit_cycAddr, 0))
		{
			ui->lineEdit_cycAddr->setFocus();
			return;
		}
		m_dataSampling.bDynTimeRange = false;
		m_dataSampling.bDynSampleRate = ui->check_dynaminRate_2->isChecked();
	}
	else{
		if(!pwnd->IsAddressCheckRight(m_dataSampling.strCtlSampAddrId, tr("位控制地址"), ui->lineEdit_ctlAddr, 0))
		{
			ui->lineEdit_ctlAddr->setFocus();
			return;
		}
		m_dataSampling.bAddrCtlSamp = true;
		m_dataSampling.bDynTimeRange = false;
		m_dataSampling.bDynSampleRate = false;
	}

	if(m_dataSampling.nDataSampType == 2 && ui->checkBox_saveFile->isChecked() &&
		!pwnd->IsAddressCheckRight(m_dataSampling.keyCtlSaveAddr, tr("控制字地址"), ui->lineEdit_ctlWordAddr, 1))
	{
		ui->pushButton_ctlWordAddr->setFocus();
		return;
	}
    m_dataSampling.keyCtlSaveAddr.Length = 8;
    if(m_dataSampling.nDataSampType == 2)
    {
        m_dataSampling.bAutoSave = ui->check_autosave->isChecked();
        m_dataSampling.nSaveHour = ui->spin_hour->value();
    }
    m_dataSampling.bPrint = ui->check_Print->isChecked();
    m_dataSampling.bPrintDate = ui->check_Date->isChecked();
    m_dataSampling.bPrintTime = ui->check_Time->isChecked();
	

    int count = pwnd->m_pSamSysParame->m_vecDataSamplingStr.size();
    QString strName = ui->lineEdit_name->text().simplified();
    if(strName.isEmpty())
    {// 名字为纯空字符的书记采集不能保存
        QMessageBox::about(this, tr("警告"), tr("数据采集命名不能为空字符"));
        return;
    }
    bool IsRename = false;
    for(int i = 0; i < count; i++)
    {
        if(i == m_curSamp)
        {
            continue;
        }

        if(pwnd->m_pSamSysParame->m_vecDataSamplingStr[i] == strName)
        {
            QMessageBox::about(this, tr("警告"), tr("数据采集重名,更名无效"));
            IsRename = true;
			return;
        }
    }
	pwnd->m_pSamSysParame->m_loadDataSampling[m_curSamp] = m_dataSampling;
    if(IsRename ==  false)
    {
        pwnd->m_pSamSysParame->m_vecDataSamplingStr[m_curSamp] = strName;
    }


    RedrawAllScene();

    accept();
}

/////////////////////////////////////类成员函数，辅助函数/////////////////////////
void qdataloggerdlg::temp_storage_addr()//重新计算地址并存储在m_dataSampling
{
    /*if(m_dataSampling.m_dataTable.isEmpty())
    {
        return;
    }*/

    
    {
        if(32 == m_dataSampling.nDigitLen)
        {
            for(int j = 0; j < m_dataSampling.m_dataTable.size(); j++)//过滤掉256以上的地址
            {
                if(m_dataSampling.m_dataTable[j].nAddrNumber > 256)
                {
                    m_dataSampling.m_dataTable.remove(j);
                    j--;
                }
            }

            //m_dataSampling.nSampAddrLen = m_dataSampling.m_dataTable.size();
        }
    }
}

void qdataloggerdlg::show_table_continous_addr()//连续地址的刷新(16位,32位)
{
    int      countWords; //显示的总字个数

    temp_storage_addr();//先刷新数据表的内容

    countWords  = m_dataSampling.m_dataTable.size();

    while(ui->tableWidget->rowCount() > 0)//清空表格显示的数据
    {
        ui->tableWidget->removeRow(0);
    }

    for(int i = 0; i < countWords; i++)
    {
        ui->tableWidget->insertRow(i);//插入一行

        QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::number(m_dataSampling.m_dataTable[i].nAddrNumber));//填充编号
        ui->tableWidget->setItem(i, 0, newItem1);
        //ui->tableWidget->item(i, 0)->setSizeHint(m_leftSize);

        QTableWidgetItem *newItem2 = new QTableWidgetItem(m_dataSampling.m_dataTable[i].keyAddress.sShowAddr);//填充地址
        ui->tableWidget->setItem(i, 1, newItem2);
        //ui->tableWidget->item(i, 1)->setSizeHint(m_rightSize);
    }
}

void qdataloggerdlg::show_table_srand_addr()//随机地址的刷新(16位,32位)
{
    int     countWords;     //显示的总字个数
    int     tableNum = 0;   //表的项数

    QStringList datatypes;
	datatypes << tr("16位整数") << tr("32位整数") << tr("16位正整数") << tr("32位正整数") << tr("16位BCD码") 
        << tr("32位BCD码") << tr("32位浮点数") << tr("ASCII字符串")<<tr("UNICODE字符串") ;

    countWords  = m_dataSampling.m_dataTable.size();

    //初始化tablewidget
    while(ui->tableWidget->rowCount() > 0)//清空表格显示的数据
    {
        ui->tableWidget->removeRow(0);
    }

    tableNum = MAX_DATASAMPLE_LENGTH;

    ui->tableWidget->setRowCount(tableNum);

    for(int i = 0; i < tableNum; i++)
    {
        QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::number(i));  //填充编号
        //newItem1->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);         //设置item属性不能编辑，能选中
        ui->tableWidget->setItem(i, 0, newItem1);
    }

    for(int i = 0; i < countWords; i++)
    {
        DATA_ADDRESS_ITEM item = m_dataSampling.m_dataTable[i];
        ui->tableWidget->setItem(item.nAddrNumber, 1, new QTableWidgetItem(item.name));
        QTableWidgetItem *newItem = new QTableWidgetItem(item.keyAddress.sShowAddr);//填充地址
        ui->tableWidget->setItem(item.nAddrNumber, 2, newItem);

        if(item.dataType == UNICODE_STRING)
        {
            newItem = new QTableWidgetItem(datatypes.value(8));
        }
        else
        {
            int index = item.dataType;
            if (index >=2 && index < (datatypes.size()+2))
            {
                newItem = new QTableWidgetItem(datatypes.value(index-2));//数据类型
            }
        }
		
        ui->tableWidget->setItem(item.nAddrNumber, 3, newItem);
        QString sExchanged = tr("无");
        if(item.bZoom)
        {
            sExchanged = tr("采集范围");
            sExchanged += QString("(%1,%2)")
                          .arg(QString::number(item.inputMin)).arg(QString::number(item.inputMax));
            sExchanged += tr(" 输出范围");
            sExchanged += QString("(%1,%2)")
                          .arg(QString::number(item.outputMin)).arg(QString::number(item.outputMax));
        }
        ui->tableWidget->setItem(item.nAddrNumber,4,new QTableWidgetItem(sExchanged));

    }
	connect(ui->tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(on_TableDClick(int,int)));
}

void qdataloggerdlg::RedrawAllScene()//扫描场景并根据设置更新
{

}

//add
void qdataloggerdlg::on_comboBox_maxNum_currentIndexChanged(int index)
{
    m_dataSampling.nSampUnit = index;
}

void qdataloggerdlg::on_radioButton_clicked()
{
    m_dataSampling.nDataSampType = 1;

    ui->groupBox_full->setEnabled(false);
    ui->groupBox_other->setEnabled(false);

    ui->groupBox_2->setEnabled(false);
}

void qdataloggerdlg::on_radioButton_2_clicked()
{
    m_dataSampling.nDataSampType = 2;

    ui->groupBox_full->setEnabled(true);
    ui->groupBox_other->setEnabled(true);

    ui->groupBox_2->setEnabled(true);
}

void qdataloggerdlg::on_comboBox_timeFreqUint_currentIndexChanged(int index)
{
    m_dataSampling.nSampRateUnit = index;
}

void qdataloggerdlg::on_comboBox_cycFreqUnit_currentIndexChanged(int index)
{
    m_dataSampling.nSampRateUnit = index;
}

void qdataloggerdlg::on_comboBox_cycCountUnit_currentIndexChanged(int index)
{
    m_dataSampling.nSampCountUnit = index;
}

void qdataloggerdlg::on_comboBox_ctlCountUnit_currentIndexChanged(int index)
{
    m_dataSampling.nSampCountUnit = index;
}

//增加
void qdataloggerdlg::on_add()
{
    int row = ui->tableWidget->currentRow();
    QTableWidgetItem *item = ui->tableWidget->item(row,1);
    if (row>=0)
    {
        while (item && !item->text().isEmpty() && row<MAX_DATASAMPLE_LENGTH)
        {
            row++;
            item = ui->tableWidget->item(row,1);
        }
        if (row <MAX_DATASAMPLE_LENGTH)
        {
            on_TableDClick(row,0);
        }
    }
}

//删除
void qdataloggerdlg::on_delete()
{
    QList<QTableWidgetItem *>selItems = ui->tableWidget->selectedItems();
    QList<int >rows;
    foreach(QTableWidgetItem *pItem,selItems)
    {
        int row = pItem->row();
        if (!rows.contains(row))
        {
            rows << row;
        }
    }

    if(rows.size() > 0)//有要删掉的行，弹出提示
    {
        QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("是否删除所选采集数据？"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("是"));
        box.button(QMessageBox::No)->setText(tr("否"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::No))
        {
            return;
        }
    }

    foreach(int row,rows)
    {
        QTableWidgetItem *item = ui->tableWidget->item(row,1);
        if (item && !item->text().isEmpty())
        {
            item->setText("");
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(""));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(""));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(""));
        }
        int index = 0;
        foreach(DATA_ADDRESS_ITEM datasampleItem,m_dataSampling.m_dataTable)
        {
            if (datasampleItem.nAddrNumber == row)
            {
                m_dataSampling.m_dataTable.remove(index);
                break;
            }
            index++;
        }
    }

    int row = ui->tableWidget->currentRow();
    row ++;
    if (row <0 || row >511)
    {
        row = 0;
    }
    ui->tableWidget->clearSelection();
    QTableWidgetItem *cItem = ui->tableWidget->item(row,1);
    if (cItem)
    {
        cItem->setSelected(true);
        ui->tableWidget->setCurrentItem(cItem);
    }
}

void qdataloggerdlg::setDynTimeUi(bool checked)
{
	ui->check_dynamicTime->setChecked(checked);
	ui->edit_starttimeAddr->setVisible(checked);
	ui->edit_endtimeAddr->setVisible(checked);
	ui->btn_startAddr->setVisible(checked);
	ui->btn_endAddr->setVisible(checked);

	ui->spinBox_beginHour->setVisible(!checked);
	ui->label_23->setVisible(!checked);
	ui->spinBox_beginMinute->setVisible(!checked);
	ui->label_25->setVisible(!checked);
	ui->spinBox_endHour->setVisible(!checked);
	ui->spinBox_endMinute->setVisible(!checked);
	ui->label_24->setVisible(!checked);
	ui->label_26->setVisible(!checked);
}

void qdataloggerdlg::setDynRateUi(bool checked)
{
	ui->check_dynaminRate->setChecked(checked);
	ui->edit_rateAddr->setVisible(checked);
	ui->btn_rateAddr->setVisible(checked);
	ui->spinBox_timeFreq->setVisible(!checked);
	ui->comboBox_timeFreqUint->setVisible(!checked);
}

void qdataloggerdlg::setDynRateUi_cycle(bool checked)
{
	ui->check_dynaminRate_2->setChecked(checked);
	ui->edit_rateAddr_2->setVisible(checked);
	ui->btn_rateAddr_2->setVisible(checked);
	ui->spinBox_cycFreq->setVisible(!checked);
	ui->comboBox_cycFreqUnit->setVisible(!checked);
}
//地址 选择采样开始时间
void qdataloggerdlg::on_btn_startAddr()
{
	pwnd->Addr_Type = 1;
	AddressInputDialog dlg_readaddress(m_dataSampling.startTimeAddr, this);
	dlg_readaddress.exec();

	ui->edit_starttimeAddr->setText(m_dataSampling.startTimeAddr.sShowAddr);
}

//地址 选择采样结束时间
void qdataloggerdlg::on_btn_endAddr()
{
	pwnd->Addr_Type = 1;
	AddressInputDialog dlg_readaddress(m_dataSampling.endTimeAddr, this);
	dlg_readaddress.exec();

	ui->edit_endtimeAddr->setText(m_dataSampling.endTimeAddr.sShowAddr);
}

//地址 时间范围 选择采样频率
void qdataloggerdlg::on_btn_rateAddr()
{
	pwnd->Addr_Type = 1;
	AddressInputDialog dlg_readaddress(m_dataSampling.dynRateAddr, this);
	dlg_readaddress.exec();

	ui->edit_rateAddr->setText(m_dataSampling.dynRateAddr.sShowAddr);
}

//地址 固定周期 选择采样频率
void qdataloggerdlg::on_btn_rateAddr_2()
{
	pwnd->Addr_Type = 1;
	AddressInputDialog dlg_readaddress(m_dataSampling.dynRateAddr, this);
	dlg_readaddress.exec();

	ui->edit_rateAddr_2->setText(m_dataSampling.dynRateAddr.sShowAddr);
}

void qdataloggerdlg::on_btn_deleteall_clicked()
{
    if(ui->tableWidget->rowCount() > 0)
    {
        QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("是否删除所有采集数据？"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("是"));
        box.button(QMessageBox::No)->setText(tr("否"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::No))
        {
            return;
        }
    }

    for(int i=0; i<ui->tableWidget->rowCount(); i++)
    {
        for(int j=1; j<=4; j++)
        {
            QTableWidgetItem *item = ui->tableWidget->item(i,j);
            if(item)
            {
                 item->setText("");
            }
        }
    }
    m_dataSampling.m_dataTable.clear();
}

void qdataloggerdlg::on_check_autosave_clicked(bool checked)
{
    ui->label_28->setEnabled(checked);
    ui->label_29->setEnabled(checked);
    ui->spin_hour->setEnabled(checked);
    if(checked)
    {
        ui->groupBox_baseDataSet->setEnabled(true);
    }
    else if(!ui->checkBox_saveFile->isChecked())
    {
        ui->groupBox_baseDataSet->setEnabled(false);
    }
}

void qdataloggerdlg::on_check_Print_clicked(bool checked)
{
    ui->check_Date->setVisible(checked);
    ui->check_Time->setVisible(checked);
}
