#include "qhisddataloggerdialog.h"
#include "ui_qhisddataloggerdialog.h"
#include "Frame\mainwindow.h"
extern MainWindow *pwnd;
//#include "headfile/global_types.h"

QHisdDataLoggerDialog::QHisdDataLoggerDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::QHisdDataLoggerDialog)
{
    bInitFinish=false;
    ui->setupUi(this);
    tablerow=0;//初始化第零行

    /**************以下是把历史数据类里面存储的信息赋值到临时变量当中************************/
    qhistabledata = pwnd->m_pSamSysParame->m_historyLogData;
    for(int i=0;i< pwnd->m_pSamSysParame->m_languageProp.sLanguageNameList.size();i++)//初始化语言选项列表框
    {
        ui->Language->addItem(pwnd->m_pSamSysParame->m_languageProp.sLanguageNameList[i]);
    }
    ui->Language->setCurrentIndex(0);//设置默认语言为第一种
    QString trmpstr;//辅助变量
    ui->name->setText(pwnd->m_pSamSysParame->m_historyLogData.sHistoryDataName);//历史数据名称
    ui->sample_length->setValue(pwnd->m_pSamSysParame->m_historyLogData.nSampleLen);//取样长度
    ui->number_sampling->setValue(pwnd->m_pSamSysParame->m_historyLogData.nSampleSize);//取样大小
    /******************以下是计算内存所需数******************************************/
    ui->hisdata_read_address->setText(pwnd->m_pSamSysParame->m_historyLogData.mReadAddr.sShowAddr);//读取地址
    if(pwnd->m_pSamSysParame->m_historyLogData.nSampleType ==0)//取样方式-计时取样
    {
        ui->timed->setChecked(true);
    }
    else if(pwnd->m_pSamSysParame->m_historyLogData.nSampleType ==1)//取样方式-触发取样
    {
        ui->triggered->setChecked(true);
        ui->bAutoOff->setChecked(pwnd->m_pSamSysParame->m_historyLogData.bAutoOff);
    }
    else if(pwnd->m_pSamSysParame->m_historyLogData.nSampleType ==2)//取样方式-整点取样
    {
        ui->clocked->setChecked(true);
    }
    ui->timed_choice->setValue(pwnd->m_pSamSysParame->m_historyLogData.nTimeInterval);//计时取样时间
    ui->clockedchoice->setValue(pwnd->m_pSamSysParame->m_historyLogData.nTriggerTime);//整点取样时间
    ui->triggerdchoice->setText(pwnd->m_pSamSysParame->m_historyLogData.mTriggerAddr.sShowAddr);//触发取样地址
    ui->stopsampling->setChecked(pwnd->m_pSamSysParame->m_historyLogData.bFullStop);//取满后是否停止
    ui->notiy->setChecked(pwnd->m_pSamSysParame->m_historyLogData.bFullNotic);//取满后是否通知
    ui->notiy_address->setText(pwnd->m_pSamSysParame->m_historyLogData.mFullNoticAddr.sShowAddr);//取满后通知结构体的地址
    ui->fulllimit->setValue(pwnd->m_pSamSysParame->m_historyLogData.nFullNoticPercent);//通知百分比
    ui->data_item_address->setText("LH0");//初始化地址，采用第一个单元格的数据
    if(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().sNameList.size() < 1)
    {
        pwnd->m_pSamSysParame->m_historyLogData.mSampleList[0].sNameList.resize(1);
    }
    ui->data_item_name->setText(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().sNameList.first());//初始化名称
    pwnd->InitDateType(ui->data_item_datatype);//初始化数据类别
    ui->data_item_datatype->addItem(tr("ASCII字符串"));
    ui->data_item_datatype->setCurrentIndex(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().nDataType);//设置数据类别
    ui->data_item_displaytype->setCurrentIndex(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().nDataShowType);//设置显示类别
    ui->data_item_totaldigits->setValue(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().nDataLen);//设置总位数
    ui->data_item_fractionaldigits->setValue(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().nDataPointLen);//设置小数位数
    ui->scaling->setChecked(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().bZoom);//是否缩放
    trmpstr= pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().sZoomStr;
    ui->gain->setText(trmpstr);
    trmpstr= pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().sOffsetStr;
    ui->offset->setText(trmpstr);
    ui->hisdatatable->verticalHeader()->hide();//隐藏表头
    /***************************************************************
   *以下是对界面的操作，隐藏和现实一些相关控件
   ****************************************************************/
    if(!ui->timed->isChecked())//取样方式-计时
    {
        ui->timed_choice->hide();
        ui->label_8->hide();
        ui->label_11->hide();
    }
    if(!ui->clocked->isChecked())//取样方式-整点
    {
        ui->clockedchoice->hide();
        ui->label_10->hide();
        ui->label_13->hide();
    }
    if(!ui->triggered->isChecked())//取样方式-触发
    {
    ui->triggerdchoice->hide();
    ui->triggeredbitchoice->hide();
    ui->label_9->hide();
    ui->bAutoOff->hide();
}
    if(!ui->notiy->isChecked())
    {
        ui->notiy_address->hide();
        ui->notiy_address_check->hide();
        ui->fulllimit->hide();
        ui->label_12->hide();
        ui->label_14->hide();
    }
    if(!ui->scaling->isChecked())
    {
        ui->gain->hide();
        ui->offset->hide();
        ui->label_21->hide();
        ui->label_22->hide();
    }
    QDoubleValidator *validator=new QDoubleValidator(this);//设置手动输入下拉列表框的范围
    ui->offset->setValidator(validator);
    ui->gain->setValidator(validator);
    ui->accept->setFocus();
    ui->memory_required->setDisabled(true);
    bInitFinish=true;//初始化完成标志
  //  on_sample_length_valueChanged(pwnd->m_pSamSysParame->m_historyLogData.nSampleLen);//
   on_tabWidget_currentChanged(1);
    on_data_item_name_textChanged(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().sNameList.first());
    on_data_item_datatype_currentIndexChanged(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().nDataType);
}

QHisdDataLoggerDialog::~QHisdDataLoggerDialog()
{
    delete ui;
}
/***********界面相关操作-设置计时取样************************/
void QHisdDataLoggerDialog::on_timed_clicked(bool checked)
{
    if(checked)
    {
        ui->timed_choice->show();
        ui->label_8->show();
        ui->label_11->show();

        ui->triggerdchoice->hide();
        ui->triggeredbitchoice->hide();
        ui->label_9->hide();
        ui->bAutoOff->hide();

        ui->clockedchoice->hide();
        ui->label_10->hide();
        ui->label_13->hide();

    }
}
/***********界面相关操作-设置触发取样************************/
void QHisdDataLoggerDialog::on_triggered_clicked(bool checked)
{

    if(checked)
    {
        ui->triggerdchoice->show();
        ui->triggeredbitchoice->show();
        ui->label_9->show();
        ui->bAutoOff->show();

        ui->timed_choice->hide();
        ui->label_8->hide();
        ui->label_11->hide();

        ui->clockedchoice->hide();
        ui->label_10->hide();
        ui->label_13->hide();


    }
}
/***********界面相关操作-设置整点取样************************/
void QHisdDataLoggerDialog::on_clocked_clicked(bool checked)
{
    if(checked)
    {
        ui->clockedchoice->show();
        ui->label_10->show();
        ui->label_13->show();

        ui->triggerdchoice->hide();
        ui->triggeredbitchoice->hide();
        ui->label_9->hide();
        ui->bAutoOff->hide();

        ui->timed_choice->hide();
        ui->label_8->hide();
        ui->label_11->hide();

    }
}
/***********界面相关操作-是否点击通知************************/

void QHisdDataLoggerDialog::on_notiy_clicked(bool checked)
{
    if(checked)
    {
        ui->notiy_address->show();
        ui->notiy_address_check->show();
        ui->fulllimit->show();
        ui->label_12->show();
        ui->label_14->show();
    }
    else
    {
        ui->notiy_address->hide();
        ui->notiy_address_check->hide();
        ui->fulllimit->hide();
        ui->label_12->hide();
        ui->label_14->hide();
    }
}
/***********界面相关操作-缩放选项************************/

void QHisdDataLoggerDialog::on_scaling_clicked(bool checked)
{
    if(checked)
    {
        qhistabledata.mSampleList[tablerow].bZoom =1;//存储是否缩放 tablerow中存储的是当前选中的单元格的行数
        ui->gain->show();
        ui->offset->show();
        ui->label_21->show();
        ui->label_22->show();
    }
    else
    {
        qhistabledata.mSampleList[tablerow].bZoom =0;
        ui->gain->hide();
        ui->offset->hide();
        ui->label_21->hide();
        ui->label_22->hide();

    }
}

/**********************根据长度的不同更新内存数和数据表的长度******************************/
void QHisdDataLoggerDialog::on_sample_length_valueChanged(int index)
{
    int memoryused=0;
    int lengthcount=20;
    QString temp;
    for(int i=0;i<ui->sample_length->value();i++)
    {
        int dataType=0;
        if(qhistabledata.mSampleList.size()-1>i)
        {
             dataType = qhistabledata.mSampleList.at(i).nDataType;
        }
        if((dataType == 0)||(dataType == 2))
        {
            lengthcount+=2;
        }
        else if(dataType==7)
        {
            lengthcount+=qhistabledata.mSampleList[i].nDataLen;
        }
        else
        {
            lengthcount+=4;
        }
    }
    int totalno=ui->number_sampling->value();//取样总数
    memoryused=lengthcount*totalno;//计算内存所需数
    temp=QString("%1").arg(memoryused);
    ui->memory_required->setText(temp);

}
/**********************根据取样总数更新内存所需数*****************************/
void QHisdDataLoggerDialog::on_number_sampling_valueChanged(int index)
{
//    if(!bInitFinish)
//    {
//        return;
//    }
//    ReMemoryCount(index);
    int memoryused=0;
    int lengthcount=20;
    QString temp;
    for(int i=0;i<ui->sample_length->value();i++)
    {
        int dataType=0;
        if(qhistabledata.mSampleList.size()-1>i)
        {
             dataType = qhistabledata.mSampleList.at(i).nDataType;
        }
        if((dataType == 0)||(dataType == 2))
        {
            lengthcount+=2;
        }
        else if(dataType==7)
        {
            lengthcount+=qhistabledata.mSampleList[i].nDataLen;
        }
        else
        {
            lengthcount+=4;
        }
    }
    memoryused=lengthcount*index;//计算内存所需数
    temp=QString("%1").arg(memoryused);
    ui->memory_required->setText(temp);
}
/**********************根据点击的单元格设置页面控件相关信息*****************************/
void QHisdDataLoggerDialog::on_hisdatatable_cellClicked(int row, int column)
{
    if(row >= qhistabledata.mSampleList.size() || row < 0) return ;
    if(qhistabledata.mSampleList.isEmpty()) return ;

    int iLanguage=ui->Language->currentIndex();
    tablerow=row;//tablerow中存储的是当前选中的单元格的行数
    tablecolumn=column;//column中存储的是当前选中的单元格的列数
    QString trmpstr;
    ui->data_item_address->setText(ui->hisdatatable->item(row,0)->text());
    if(qhistabledata.mSampleList.at(row).sNameList.size() <= iLanguage)
    {
        while(qhistabledata.mSampleList.at(row).sNameList.size() < iLanguage)
        {
            qhistabledata.mSampleList[row].sNameList.push_back("");
        }
    }
    ui->data_item_name->setText(qhistabledata.mSampleList.at(row).sNameList.at(iLanguage));

    int tempdisplaytype=qhistabledata.mSampleList.at(row).nDataShowType;
    ui->data_item_datatype->setCurrentIndex(qhistabledata.mSampleList.at(row).nDataType);
    ui->label_21->setHidden(false);
    ui->gain->setHidden(false);
    ui->label_22->setHidden(false);
    ui->offset->setHidden(false);
    ReDataDisplaytype(qhistabledata.mSampleList.at(row).nDataType);//刷新数据的显示类别
    qhistabledata.mSampleList[row].nDataShowType = tempdisplaytype;
    ui->data_item_totaldigits->setValue(qhistabledata.mSampleList.at(row).nDataLen);
    ui->data_item_fractionaldigits->setValue(qhistabledata.mSampleList.at(row).nDataPointLen);
    ui->scaling->setChecked(qhistabledata.mSampleList.at(row).bZoom);//是否缩放
    on_scaling_clicked(qhistabledata.mSampleList.at(row).bZoom);
    trmpstr= qhistabledata.mSampleList.at(row).sZoomStr;
    ui->gain->setText(trmpstr);
    trmpstr=qhistabledata.mSampleList.at(row).sOffsetStr;
    ui->offset->setText(trmpstr);
    ui->data_item_name->setFocus(Qt::MouseFocusReason);
    ui->data_item_displaytype->setCurrentIndex(qhistabledata.mSampleList.at(row).nDataShowType);
}
/**********************取名称编辑框中的字符更新表格中的数据*****************************/
void QHisdDataLoggerDialog::on_data_item_name_textChanged(QString name)
{
    if(!bInitFinish)
    {
        return;//初始化未完成时 返回
    }
    int iLanguage=ui->Language->currentIndex();
    QTableWidgetItem * item=new QTableWidgetItem;
    ui->hisdatatable->setItem(tablerow,1,item);
    ui->hisdatatable->item(tablerow,1)->setText(name);
    int size = qhistabledata.mSampleList.size();
    for(int i =0; i < size; i++)
    {
        int lanSize = qhistabledata.mSampleList.at(i).sNameList.size();
        if(lanSize < iLanguage)
        {
            qhistabledata.mSampleList[i].sNameList.push_back("");
        }
    }

    qhistabledata.mSampleList[tablerow].sNameList[iLanguage] = name;
}
/**********************数据类别改变后更改显示类别的相关信息*****************************/
void QHisdDataLoggerDialog::on_data_item_datatype_currentIndexChanged(int index)
{
    if(!bInitFinish)
    {
        return;//初始化未完成时 返回
    }

    if(tablerow >= qhistabledata.mSampleList.size()) return ;

    qhistabledata.mSampleList[tablerow].nDataType = index;// 把类型信息存储到临时变量中
    ReDataDisplaytype(index);//刷新数据的显示类别

   // on_sample_length_valueChanged(ui->sample_length->value());
    on_tabWidget_currentChanged(1);
    ui->data_item_displaytype->setCurrentIndex(qhistabledata.mSampleList.at(tablerow).nDataShowType);
    //以下是进行内存所需数的计算
ReMemoryCount(ui->number_sampling->value());
}
/**********************显示类别*****************************/
void QHisdDataLoggerDialog::on_data_item_displaytype_currentIndexChanged(int index)
{
    if(!bInitFinish)
    {
        return;//初始化未完成时 返回
    }

    if(tablerow < qhistabledata.mSampleList.size())
        qhistabledata.mSampleList[tablerow].nDataShowType =index;
}
/**********************总位数*****************************/
void QHisdDataLoggerDialog::on_data_item_totaldigits_valueChanged(int index)
{
    if(!bInitFinish)
    {
        return;//初始化未完成时 返回
    }

    if(tablerow < qhistabledata.mSampleList.size())
    {
        qhistabledata.mSampleList[tablerow].nDataLen = index;//总位数改变之后存储新的总位数
    }
    if(qhistabledata.mSampleList[tablerow].nDataType==7)//ascii码的时候长度改变要重新刷新数据长度
    {
        ReMemoryCount(ui->number_sampling->value());
        ReHisTable(ui->sample_length->value());
    }
}
/**********************小数位数*****************************/
void QHisdDataLoggerDialog::on_data_item_fractionaldigits_valueChanged(int index)
{
    if(!bInitFinish)
    {
        return;//初始化未完成时 返回
    }

    if(index>ui->data_item_totaldigits->value())
    {
        ui->data_item_fractionaldigits->setValue(ui->data_item_totaldigits->value());
        return;
    }
    if(tablerow < qhistabledata.mSampleList.size())
        qhistabledata.mSampleList[tablerow].nDataPointLen = index;
}
/**********************增益*****************************/

void QHisdDataLoggerDialog::on_gain_textEdited(QString data)
{
    if(tablerow < qhistabledata.mSampleList.size())
    {
        qhistabledata.mSampleList[tablerow].sZoomStr = data;
    }
}
/**********************偏移量*****************************/
void QHisdDataLoggerDialog::on_offset_textEdited(QString data)
{
    if(tablerow < qhistabledata.mSampleList.size())
    {
        qhistabledata.mSampleList[tablerow].sOffsetStr = data;
    }
}

void QHisdDataLoggerDialog::on_pushButton_readaddress_clicked()
{
    pwnd->Addr_Type=1;
    AddressInputDialog dlg_readaddress(pwnd->m_pSamSysParame->m_historyLogData.mReadAddr,this);
    dlg_readaddress.exec();
    ui->hisdata_read_address->setText(pwnd->m_pSamSysParame->m_historyLogData.mReadAddr.sShowAddr);

}//

void QHisdDataLoggerDialog::on_triggeredbitchoice_clicked()
{
    pwnd->Addr_Type=0;
    AddressInputDialog  dlg_triggered(pwnd->m_pSamSysParame->m_historyLogData.mTriggerAddr,this);
    dlg_triggered.exec();
    ui->triggerdchoice->setText(pwnd->m_pSamSysParame->m_historyLogData.mTriggerAddr.sShowAddr);
}//

void QHisdDataLoggerDialog::on_notiy_address_check_clicked()
{
    pwnd->Addr_Type=0;
    AddressInputDialog dlg_notiy_address(pwnd->m_pSamSysParame->m_historyLogData.mFullNoticAddr,this);
    dlg_notiy_address.exec();
    ui->notiy_address->setText(pwnd->m_pSamSysParame->m_historyLogData.mFullNoticAddr.sShowAddr);
}//
///*********************对话框数据保存函数，把对话框中的信息保存到历史数据类中********************/

void QHisdDataLoggerDialog::on_accept_clicked()
{
    if(! pwnd->IsAddressCheckRight(pwnd->m_pSamSysParame->m_historyLogData.mReadAddr,tr("读取地址"),ui->hisdata_read_address,1))
    {
        return;
    }
    if(ui->triggered->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(pwnd->m_pSamSysParame->m_historyLogData.mTriggerAddr,tr("触发位"),ui->triggerdchoice,0))
        {
            return;
        }
    }
    if(ui->notiy->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(pwnd->m_pSamSysParame->m_historyLogData.mFullNoticAddr,tr("通知位"),ui->notiy_address,0))
        {
            return;
        }
    }
    pwnd->m_pSamSysParame->m_historyLogData.sHistoryDataName =ui->name->text();//历史数据名称
    pwnd->m_pSamSysParame->m_historyLogData.nSampleLen =ui->sample_length->value(); //取样长度
    pwnd->m_pSamSysParame->m_historyLogData.nSampleSize =ui->number_sampling->value();//取样大小
    pwnd->m_pSamSysParame->m_historyLogData.mReadAddr.sShowAddr=ui->hisdata_read_address->text();
    if(ui->timed->isChecked())//取样方式
    {
        pwnd->m_pSamSysParame->m_historyLogData.nSampleType =0;//计时
    }
    else if(ui->triggered->isChecked())
    {
        pwnd->m_pSamSysParame->m_historyLogData.nSampleType =1;//触发
    }
    else if(ui->clocked->isChecked())
    {
        pwnd->m_pSamSysParame->m_historyLogData.nSampleType =2;//整点
    }
    pwnd->m_pSamSysParame->m_historyLogData.bAutoOff=ui->bAutoOff->isChecked();
    pwnd->m_pSamSysParame->m_historyLogData.nTimeInterval =ui->timed_choice->value();//计时取样时间
    pwnd->m_pSamSysParame->m_historyLogData.nTriggerTime =ui->clockedchoice->value();//整点取样时间
  //  pwnd->m_pSamSysParame->m_historyLogData.mReadAddr.sShowAddr= ui->triggerdchoice->text();//触发取样地址
    pwnd->m_pSamSysParame->m_historyLogData.bFullStop =ui->stopsampling->isChecked();//取满后是否停止
    pwnd->m_pSamSysParame->m_historyLogData.bFullNotic = ui->notiy->isChecked();//取满后是否通知
  //  pwnd->m_pSamSysParame->m_historyLogData.mFullNoticAddr.sShowAddr=ui->notiy_address->text();//取满后通知结构体的地址
    pwnd->m_pSamSysParame->m_historyLogData.nFullNoticPercent =ui->fulllimit->value();//通知百分比
    //表格存储的信息
    on_tabWidget_currentChanged(1);//刷新历史数据容器
    pwnd->m_pSamSysParame->m_historyLogData.mSampleList = qhistabledata.mSampleList;
    if(pwnd->m_pSamSysParame->m_historyLogData.sBackupForNewVer.size()<1)
    {
        pwnd->m_pSamSysParame->m_historyLogData.sBackupForNewVer.append(ui->memory_required->text());
    }
    else
    {
        pwnd->m_pSamSysParame->m_historyLogData.sBackupForNewVer[0]=ui->memory_required->text();
    }
    reDrawHisDataDisplay();
    accept();
}

void QHisdDataLoggerDialog::on_cancel_clicked()
{
    this->close();
}

void QHisdDataLoggerDialog::on_Language_currentIndexChanged(int index)//语言切换
{
    if(!bInitFinish)
    {
        return;//初始化未完成时 返回
    }
   // on_sample_length_valueChanged(ui->sample_length->value());//调用改变长度切换刷新表的函数
    on_tabWidget_currentChanged(1);
    if(tablerow < qhistabledata.mSampleList.size() && !qhistabledata.mSampleList.isEmpty() )
    {
        if(qhistabledata.mSampleList.at(tablerow).sNameList.size() > index)
            ui->data_item_name->setText(qhistabledata.mSampleList.at(tablerow).sNameList.at(index));
    }
}
void QHisdDataLoggerDialog::on_help_clicked()
{
    pwnd->loadHelpHtm(TREE_HISDATA_RECORD);
}
/************************************************************************
  *Functions:刷新历史数据表格
  ************************************************************************
  *Value：
  *nTablelength 数据长度 也就是表格的行数
  ************************************************************************
 *returns:
 *无
 ***********************************************************************
  *Edit time：2011.7.29
  *Edit by    ：zhy
  *************************************************************************/
void QHisdDataLoggerDialog::ReHisTable(int nTablelength)
{
    QString temp;
    int datatypecount=0;
    int iLanguage=ui->Language->currentIndex();
    while(ui->hisdatatable->rowCount()>0)//清空表格原有的数据
    {
        ui->hisdatatable->removeRow(0);
    }
    for(int icountrow=0;icountrow<nTablelength;icountrow++)
    {
        ui->hisdatatable->insertRow(icountrow);//插入一行数据
        temp=QString("LH%1").arg(datatypecount);//更新地址
        QTableWidgetItem *newItem = new QTableWidgetItem(temp);
        ui->hisdatatable->setItem(icountrow,0,newItem);//添加到表格中
        ///更新名称
        QTableWidgetItem * item = NULL;
        item=new QTableWidgetItem(qhistabledata.mSampleList.at(icountrow).sNameList.at(iLanguage));
        ui->hisdatatable->setItem(icountrow,1,item);
        //32位数据的时候
        int dataType = qhistabledata.mSampleList.at(icountrow).nDataType;
        if(dataType == 1 || dataType == 3 || dataType ==5 || dataType ==6)
        {
            datatypecount+=2;
        }
        //16位数据的时候
        else if(dataType == 0 || dataType == 2 || dataType == 4)
        {
            datatypecount+=1;
        }
        //ASCII数据的时候
        else if(dataType == 7)
        {
            datatypecount+=qhistabledata.mSampleList.at(icountrow).nDataLen/2+qhistabledata.mSampleList.at(icountrow).nDataLen%2;
        }
    }
}
/************************************************************************
  *Functions:重新计算内存所需数并填写到控件中
  ************************************************************************
  *Value：
  *index 取样总数
  ************************************************************************
 *returns:
 *在改变数据长度，取样总数、更改数据类别的时候刷新内存所需数
 ***********************************************************************
  *Edit time：2011.7.29
  *Edit by    ：zhy
  *************************************************************************/
void QHisdDataLoggerDialog::ReMemoryCount(int index)
{
    int memoryused=0;
    int lengthcount=20;
    QString temp;
    for(int i=0;i<ui->sample_length->value();i++)
    {
        int dataType = qhistabledata.mSampleList.at(i).nDataType;
        if((dataType == 0)||(dataType == 2))
        {
            lengthcount+=2;
        }
        else if(dataType==7)
        {
            lengthcount+=qhistabledata.mSampleList[i].nDataLen;
        }
        else
        {
            lengthcount+=4;
        }
    }
    memoryused=lengthcount*index;//计算内存所需数
    temp=QString("%1").arg(memoryused);
    ui->memory_required->setText(temp);
}
/************************************************************************
  *Functions:刷新显示类别的类型数据
  ************************************************************************
  *Value：
  *index 数据类型
  ************************************************************************
 *returns:
 *无
 ***********************************************************************
  *Edit time：2011.7.29
  *Edit by    ：zhy
  *************************************************************************/
void QHisdDataLoggerDialog::ReDataDisplaytype(int index)
{
    ui->label_19->setHidden(false);
    ui->data_item_totaldigits->setHidden(false);
    ui->lable_1->setHidden(false);
    ui->data_item_fractionaldigits->setHidden(false);
    ui->scaling->setHidden(false);
    ui->data_item_displaytype->clear();//清除显示类别中的数据

    if(index==0)
    {//为显示类别添加数据
        ui->data_item_displaytype->setDisabled(false);
        ui->data_item_displaytype->addItem(tr("16位十进制正整数"));
        ui->data_item_displaytype->addItem(tr("16位十六进制数"));
        ui->data_item_displaytype->addItem(tr("16位八进制数"));
        ui->data_item_totaldigits->setRange(0,5);
        //        if(ui->Total_Digits->value()>5)
//        {
//            ui->Total_Digits->setValue(5);
//        }
    }
    else if(index==1)
    {
        ui->data_item_displaytype->setDisabled(false);
        ui->data_item_displaytype->addItem(tr("32位十进制正整数"));
        ui->data_item_displaytype->addItem(tr("32位十六进制数"));
        ui->data_item_displaytype->addItem(tr("32位八进制数"));
        ui->data_item_totaldigits->setRange(0,10);
    }
    else if(index==2)
    {
        ui->data_item_displaytype->addItem(tr("16位十进制正整数"));
        ui->data_item_displaytype->setDisabled(true);
        ui->data_item_totaldigits->setRange(0,5);
    }
    else if(index==3)
    {
        ui->data_item_displaytype->addItem(tr("32位十进制正整数"));
        ui->data_item_displaytype->setDisabled(true);
        ui->data_item_totaldigits->setRange(0,10);
    }
    else if(index==4)
    {
        ui->data_item_displaytype->setDisabled(false);
        ui->data_item_displaytype->addItem(tr("16位十进制正整数"));
        ui->data_item_totaldigits->setRange(0,5);
    }
    else if(index==5)
    {
        ui->data_item_displaytype->setDisabled(false);
        ui->data_item_displaytype->addItem(tr("32位十进制正整数"));
        ui->data_item_totaldigits->setRange(0,10);
    }
    else if(index==6)
    {
        ui->data_item_displaytype->setDisabled(false);
        ui->data_item_displaytype->addItem(tr("32位浮点数"));
        ui->data_item_totaldigits->setRange(0,10);
    }
    else if(index==7)
    {
        ui->data_item_displaytype->setDisabled(false);
        ui->data_item_displaytype->addItem(tr("ASCII字符串"));
        ui->lable_1->setHidden(true);
        ui->data_item_fractionaldigits->setHidden(true);
        ui->scaling->setHidden(true);
        ui->label_21->setHidden(true);
        ui->gain->setHidden(true);
        ui->label_22->setHidden(true);
        ui->offset->setHidden(true);
        ui->data_item_totaldigits->setRange(0,128);
    }
}

/*****************************************************************
 *函数名称：reDrawHisDataDisplay
 *函数功能：当历史数据收集器的长度发生变化的时候，点击确定按钮后重绘场景中的
 *                    历史数据显示器控件
 *edit by zqh
 *2011-9-27
 ****************************************************************/
void QHisdDataLoggerDialog::reDrawHisDataDisplay()
{
    int totalSceneNum = pwnd->pSceneSheet.size();
    QList<QGraphicsItem *> Items;
    QGraphicsItem *pItem = NULL;
    QGraphicsItem *pNewItem = NULL;
    int nID = 0;
    int  i = 0;
    int j = 0;
    int k = 0;
    int nsheet = pwnd->nActiveSheetIndex;
    int nOldNum = 0; //原历史数据收集器取样长度
    int nNewNum = pwnd->m_pSamSysParame->m_historyLogData.nSampleLen;//历史数据收集器取样长度
    QStringList *sList = new QStringList();
    QStringList slist;
    Items.clear();

    for(i = 0; i < totalSceneNum;i++)   //扫描所有页面
    {
        pwnd->nActiveSheetIndex = i;
        pwnd->pView->setScene(pwnd->pSceneSheet[i]);
        QPainterPath path;
        path.addRect(0,0,pwnd->pSceneSheet[i]->width(),pwnd->pSceneSheet[i]->height());
        pwnd->pSceneSheet[i]->setSelectionArea(path);
        Items = pwnd->pSceneSheet[i]->selectedItems();
        foreach(QGraphicsItem *item,Items)
            item->setSelected(false);

        for(j = 0; j < Items.size(); j++)   //扫描当前页面的所有控件
        {
            pItem = Items.at(j);//->topLevelItem();
            nID = pItem->data(GROUP_TYPE_KEY).toInt(); //取控件的Key号
            sList->clear();
            slist.clear();
            switch(nID)
            {
                case GROUP_TYPE_HISDATAALARM: //历史数据显示器
                    {
                        slist = pItem->data(GROUP_DATALIST_KEY).toStringList(); //取出每个item的所有数据
                        for(k = 0; k < slist.size();k++)
                            sList->append(slist.at(k));

                        nOldNum = sList->at(99).toInt(); //37
                      //  if(nNewNum != nOldNum)//长度没有改变的时候也要刷新 因为名称会改变
                        //Change by Dylan 2012-3-13
                        {
                            sList->replace(99,QString("%1").arg(nNewNum)); //37
                            int val = nNewNum - nOldNum;
                            if(val < 0) //配方数减少
                            {
                                for(k = 0; k < -val;k++)
                                    sList->removeLast();
                            }
                            else if(val > 0) //配方数增加
                            {
                                for(k = 0; k < val;k++)
                                    sList->append("1");
                            }
                            QDrawGraphics *pDraw = new QDrawGraphics;
                            pNewItem = pDraw->drawHistroyDataDisplayItem(sList);  //重绘配方显示器
                            pNewItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_HISDATAALARM));
                            pNewItem->setData(GROUP_DATALIST_KEY,*sList);
                            if(pDraw)
                            {
                                delete pDraw;
                                pDraw = NULL;
                            }
                            pwnd->OnDoubleClik(pItem,pNewItem);
                        } //end if
                    } //end case
                    break;
            } //end switch
        } //end second for
    } //end first for
     pwnd->nActiveSheetIndex = nsheet ; //reset active sheet page
     pwnd->pView->setScene(pwnd->pSceneSheet[nsheet]);
}
/************************************************************************
  *Functions:在页面切换到“数据”的时候再进行刷新历史数据的容器
  ************************************************************************
  *Value：
  *int x：页面的索引 从0开始
  ************************************************************************
 *returns:
  *无
  ************************************************************************
  *Edit time：2012.3.13
  *Edit by    ：Dylan
  *************************************************************************/
void QHisdDataLoggerDialog::on_tabWidget_currentChanged(int x)
{
    if(x==0)//若切换到第一个page，不刷新容器中的数据
    {
        return;
    }
    if(!bInitFinish)
    {
        return;
    }
    int index=ui->sample_length->value();
    int LanguageNum = pwnd->m_pSamSysParame->m_languageProp.nTotalNum+1;
    int mSampleSize = qhistabledata.mSampleList.size();
    if(mSampleSize < index)
    {
        while(mSampleSize < index)
        {
            HISTORY_DATA_ITEM tempData;  //初始化历史数据的相关属性
            tempData.bZoom = false;      //缩放
            tempData.nDataLen = 4;       //总位数
            tempData.nDataPointLen = 0;
            tempData.nDataShowType = 0;
            tempData.nDataType = 0;
            tempData.sAddrName = "";
            tempData.sNameList.clear();
            for(int i = 0; i < LanguageNum; i++)
            {
                tempData.sNameList.push_back("");
            }
            tempData.sOffsetStr = "0.0";
            tempData.sZoomStr = "1.0";
            qhistabledata.mSampleList.push_back(tempData);
            mSampleSize = qhistabledata.mSampleList.size();
        }
    }
    else if(mSampleSize > index)//若改变长度之后比容器里面的少
    {
        qhistabledata.mSampleList.resize(index);//清楚容器中多余的数据
    }
    mSampleSize = qhistabledata.mSampleList.size();
    qhistabledata.nSampleLen = index;//存储长度
    for(int i = 0; i < mSampleSize; i++)
    {
        int size = qhistabledata.mSampleList.at(i).sNameList.size();
        while(size < LanguageNum)//如果长度比语言总数少的话
        {
            qhistabledata.mSampleList[i].sNameList.push_back("");//添加变量
            size++;
        }
    }
    ReMemoryCount(ui->number_sampling->value());

    ReHisTable(index);//根据相关数据刷新表格
    //设置表格禁止修改
    ui->hisdatatable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
