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
    tablerow=0;//��ʼ��������

    /**************�����ǰ���ʷ����������洢����Ϣ��ֵ����ʱ��������************************/
    qhistabledata = pwnd->m_pSamSysParame->m_historyLogData;
    for(int i=0;i< pwnd->m_pSamSysParame->m_languageProp.sLanguageNameList.size();i++)//��ʼ������ѡ���б��
    {
        ui->Language->addItem(pwnd->m_pSamSysParame->m_languageProp.sLanguageNameList[i]);
    }
    ui->Language->setCurrentIndex(0);//����Ĭ������Ϊ��һ��
    QString trmpstr;//��������
    ui->name->setText(pwnd->m_pSamSysParame->m_historyLogData.sHistoryDataName);//��ʷ��������
    ui->sample_length->setValue(pwnd->m_pSamSysParame->m_historyLogData.nSampleLen);//ȡ������
    ui->number_sampling->setValue(pwnd->m_pSamSysParame->m_historyLogData.nSampleSize);//ȡ����С
    /******************�����Ǽ����ڴ�������******************************************/
    ui->hisdata_read_address->setText(pwnd->m_pSamSysParame->m_historyLogData.mReadAddr.sShowAddr);//��ȡ��ַ
    if(pwnd->m_pSamSysParame->m_historyLogData.nSampleType ==0)//ȡ����ʽ-��ʱȡ��
    {
        ui->timed->setChecked(true);
    }
    else if(pwnd->m_pSamSysParame->m_historyLogData.nSampleType ==1)//ȡ����ʽ-����ȡ��
    {
        ui->triggered->setChecked(true);
        ui->bAutoOff->setChecked(pwnd->m_pSamSysParame->m_historyLogData.bAutoOff);
    }
    else if(pwnd->m_pSamSysParame->m_historyLogData.nSampleType ==2)//ȡ����ʽ-����ȡ��
    {
        ui->clocked->setChecked(true);
    }
    ui->timed_choice->setValue(pwnd->m_pSamSysParame->m_historyLogData.nTimeInterval);//��ʱȡ��ʱ��
    ui->clockedchoice->setValue(pwnd->m_pSamSysParame->m_historyLogData.nTriggerTime);//����ȡ��ʱ��
    ui->triggerdchoice->setText(pwnd->m_pSamSysParame->m_historyLogData.mTriggerAddr.sShowAddr);//����ȡ����ַ
    ui->stopsampling->setChecked(pwnd->m_pSamSysParame->m_historyLogData.bFullStop);//ȡ�����Ƿ�ֹͣ
    ui->notiy->setChecked(pwnd->m_pSamSysParame->m_historyLogData.bFullNotic);//ȡ�����Ƿ�֪ͨ
    ui->notiy_address->setText(pwnd->m_pSamSysParame->m_historyLogData.mFullNoticAddr.sShowAddr);//ȡ����֪ͨ�ṹ��ĵ�ַ
    ui->fulllimit->setValue(pwnd->m_pSamSysParame->m_historyLogData.nFullNoticPercent);//֪ͨ�ٷֱ�
    ui->data_item_address->setText("LH0");//��ʼ����ַ�����õ�һ����Ԫ�������
    if(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().sNameList.size() < 1)
    {
        pwnd->m_pSamSysParame->m_historyLogData.mSampleList[0].sNameList.resize(1);
    }
    ui->data_item_name->setText(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().sNameList.first());//��ʼ������
    pwnd->InitDateType(ui->data_item_datatype);//��ʼ���������
    ui->data_item_datatype->addItem(tr("ASCII�ַ���"));
    ui->data_item_datatype->setCurrentIndex(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().nDataType);//�����������
    ui->data_item_displaytype->setCurrentIndex(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().nDataShowType);//������ʾ���
    ui->data_item_totaldigits->setValue(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().nDataLen);//������λ��
    ui->data_item_fractionaldigits->setValue(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().nDataPointLen);//����С��λ��
    ui->scaling->setChecked(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().bZoom);//�Ƿ�����
    trmpstr= pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().sZoomStr;
    ui->gain->setText(trmpstr);
    trmpstr= pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().sOffsetStr;
    ui->offset->setText(trmpstr);
    ui->hisdatatable->verticalHeader()->hide();//���ر�ͷ
    /***************************************************************
   *�����ǶԽ���Ĳ��������غ���ʵһЩ��ؿؼ�
   ****************************************************************/
    if(!ui->timed->isChecked())//ȡ����ʽ-��ʱ
    {
        ui->timed_choice->hide();
        ui->label_8->hide();
        ui->label_11->hide();
    }
    if(!ui->clocked->isChecked())//ȡ����ʽ-����
    {
        ui->clockedchoice->hide();
        ui->label_10->hide();
        ui->label_13->hide();
    }
    if(!ui->triggered->isChecked())//ȡ����ʽ-����
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
    QDoubleValidator *validator=new QDoubleValidator(this);//�����ֶ����������б��ķ�Χ
    ui->offset->setValidator(validator);
    ui->gain->setValidator(validator);
    ui->accept->setFocus();
    ui->memory_required->setDisabled(true);
    bInitFinish=true;//��ʼ����ɱ�־
  //  on_sample_length_valueChanged(pwnd->m_pSamSysParame->m_historyLogData.nSampleLen);//
   on_tabWidget_currentChanged(1);
    on_data_item_name_textChanged(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().sNameList.first());
    on_data_item_datatype_currentIndexChanged(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.first().nDataType);
}

QHisdDataLoggerDialog::~QHisdDataLoggerDialog()
{
    delete ui;
}
/***********������ز���-���ü�ʱȡ��************************/
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
/***********������ز���-���ô���ȡ��************************/
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
/***********������ز���-��������ȡ��************************/
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
/***********������ز���-�Ƿ���֪ͨ************************/

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
/***********������ز���-����ѡ��************************/

void QHisdDataLoggerDialog::on_scaling_clicked(bool checked)
{
    if(checked)
    {
        qhistabledata.mSampleList[tablerow].bZoom =1;//�洢�Ƿ����� tablerow�д洢���ǵ�ǰѡ�еĵ�Ԫ�������
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

/**********************���ݳ��ȵĲ�ͬ�����ڴ��������ݱ�ĳ���******************************/
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
    int totalno=ui->number_sampling->value();//ȡ������
    memoryused=lengthcount*totalno;//�����ڴ�������
    temp=QString("%1").arg(memoryused);
    ui->memory_required->setText(temp);

}
/**********************����ȡ�����������ڴ�������*****************************/
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
    memoryused=lengthcount*index;//�����ڴ�������
    temp=QString("%1").arg(memoryused);
    ui->memory_required->setText(temp);
}
/**********************���ݵ���ĵ�Ԫ������ҳ��ؼ������Ϣ*****************************/
void QHisdDataLoggerDialog::on_hisdatatable_cellClicked(int row, int column)
{
    if(row >= qhistabledata.mSampleList.size() || row < 0) return ;
    if(qhistabledata.mSampleList.isEmpty()) return ;

    int iLanguage=ui->Language->currentIndex();
    tablerow=row;//tablerow�д洢���ǵ�ǰѡ�еĵ�Ԫ�������
    tablecolumn=column;//column�д洢���ǵ�ǰѡ�еĵ�Ԫ�������
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
    ReDataDisplaytype(qhistabledata.mSampleList.at(row).nDataType);//ˢ�����ݵ���ʾ���
    qhistabledata.mSampleList[row].nDataShowType = tempdisplaytype;
    ui->data_item_totaldigits->setValue(qhistabledata.mSampleList.at(row).nDataLen);
    ui->data_item_fractionaldigits->setValue(qhistabledata.mSampleList.at(row).nDataPointLen);
    ui->scaling->setChecked(qhistabledata.mSampleList.at(row).bZoom);//�Ƿ�����
    on_scaling_clicked(qhistabledata.mSampleList.at(row).bZoom);
    trmpstr= qhistabledata.mSampleList.at(row).sZoomStr;
    ui->gain->setText(trmpstr);
    trmpstr=qhistabledata.mSampleList.at(row).sOffsetStr;
    ui->offset->setText(trmpstr);
    ui->data_item_name->setFocus(Qt::MouseFocusReason);
    ui->data_item_displaytype->setCurrentIndex(qhistabledata.mSampleList.at(row).nDataShowType);
}
/**********************ȡ���Ʊ༭���е��ַ����±���е�����*****************************/
void QHisdDataLoggerDialog::on_data_item_name_textChanged(QString name)
{
    if(!bInitFinish)
    {
        return;//��ʼ��δ���ʱ ����
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
/**********************�������ı�������ʾ���������Ϣ*****************************/
void QHisdDataLoggerDialog::on_data_item_datatype_currentIndexChanged(int index)
{
    if(!bInitFinish)
    {
        return;//��ʼ��δ���ʱ ����
    }

    if(tablerow >= qhistabledata.mSampleList.size()) return ;

    qhistabledata.mSampleList[tablerow].nDataType = index;// ��������Ϣ�洢����ʱ������
    ReDataDisplaytype(index);//ˢ�����ݵ���ʾ���

   // on_sample_length_valueChanged(ui->sample_length->value());
    on_tabWidget_currentChanged(1);
    ui->data_item_displaytype->setCurrentIndex(qhistabledata.mSampleList.at(tablerow).nDataShowType);
    //�����ǽ����ڴ��������ļ���
ReMemoryCount(ui->number_sampling->value());
}
/**********************��ʾ���*****************************/
void QHisdDataLoggerDialog::on_data_item_displaytype_currentIndexChanged(int index)
{
    if(!bInitFinish)
    {
        return;//��ʼ��δ���ʱ ����
    }

    if(tablerow < qhistabledata.mSampleList.size())
        qhistabledata.mSampleList[tablerow].nDataShowType =index;
}
/**********************��λ��*****************************/
void QHisdDataLoggerDialog::on_data_item_totaldigits_valueChanged(int index)
{
    if(!bInitFinish)
    {
        return;//��ʼ��δ���ʱ ����
    }

    if(tablerow < qhistabledata.mSampleList.size())
    {
        qhistabledata.mSampleList[tablerow].nDataLen = index;//��λ���ı�֮��洢�µ���λ��
    }
    if(qhistabledata.mSampleList[tablerow].nDataType==7)//ascii���ʱ�򳤶ȸı�Ҫ����ˢ�����ݳ���
    {
        ReMemoryCount(ui->number_sampling->value());
        ReHisTable(ui->sample_length->value());
    }
}
/**********************С��λ��*****************************/
void QHisdDataLoggerDialog::on_data_item_fractionaldigits_valueChanged(int index)
{
    if(!bInitFinish)
    {
        return;//��ʼ��δ���ʱ ����
    }

    if(index>ui->data_item_totaldigits->value())
    {
        ui->data_item_fractionaldigits->setValue(ui->data_item_totaldigits->value());
        return;
    }
    if(tablerow < qhistabledata.mSampleList.size())
        qhistabledata.mSampleList[tablerow].nDataPointLen = index;
}
/**********************����*****************************/

void QHisdDataLoggerDialog::on_gain_textEdited(QString data)
{
    if(tablerow < qhistabledata.mSampleList.size())
    {
        qhistabledata.mSampleList[tablerow].sZoomStr = data;
    }
}
/**********************ƫ����*****************************/
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
///*********************�Ի������ݱ��溯�����ѶԻ����е���Ϣ���浽��ʷ��������********************/

void QHisdDataLoggerDialog::on_accept_clicked()
{
    if(! pwnd->IsAddressCheckRight(pwnd->m_pSamSysParame->m_historyLogData.mReadAddr,tr("��ȡ��ַ"),ui->hisdata_read_address,1))
    {
        return;
    }
    if(ui->triggered->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(pwnd->m_pSamSysParame->m_historyLogData.mTriggerAddr,tr("����λ"),ui->triggerdchoice,0))
        {
            return;
        }
    }
    if(ui->notiy->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(pwnd->m_pSamSysParame->m_historyLogData.mFullNoticAddr,tr("֪ͨλ"),ui->notiy_address,0))
        {
            return;
        }
    }
    pwnd->m_pSamSysParame->m_historyLogData.sHistoryDataName =ui->name->text();//��ʷ��������
    pwnd->m_pSamSysParame->m_historyLogData.nSampleLen =ui->sample_length->value(); //ȡ������
    pwnd->m_pSamSysParame->m_historyLogData.nSampleSize =ui->number_sampling->value();//ȡ����С
    pwnd->m_pSamSysParame->m_historyLogData.mReadAddr.sShowAddr=ui->hisdata_read_address->text();
    if(ui->timed->isChecked())//ȡ����ʽ
    {
        pwnd->m_pSamSysParame->m_historyLogData.nSampleType =0;//��ʱ
    }
    else if(ui->triggered->isChecked())
    {
        pwnd->m_pSamSysParame->m_historyLogData.nSampleType =1;//����
    }
    else if(ui->clocked->isChecked())
    {
        pwnd->m_pSamSysParame->m_historyLogData.nSampleType =2;//����
    }
    pwnd->m_pSamSysParame->m_historyLogData.bAutoOff=ui->bAutoOff->isChecked();
    pwnd->m_pSamSysParame->m_historyLogData.nTimeInterval =ui->timed_choice->value();//��ʱȡ��ʱ��
    pwnd->m_pSamSysParame->m_historyLogData.nTriggerTime =ui->clockedchoice->value();//����ȡ��ʱ��
  //  pwnd->m_pSamSysParame->m_historyLogData.mReadAddr.sShowAddr= ui->triggerdchoice->text();//����ȡ����ַ
    pwnd->m_pSamSysParame->m_historyLogData.bFullStop =ui->stopsampling->isChecked();//ȡ�����Ƿ�ֹͣ
    pwnd->m_pSamSysParame->m_historyLogData.bFullNotic = ui->notiy->isChecked();//ȡ�����Ƿ�֪ͨ
  //  pwnd->m_pSamSysParame->m_historyLogData.mFullNoticAddr.sShowAddr=ui->notiy_address->text();//ȡ����֪ͨ�ṹ��ĵ�ַ
    pwnd->m_pSamSysParame->m_historyLogData.nFullNoticPercent =ui->fulllimit->value();//֪ͨ�ٷֱ�
    //���洢����Ϣ
    on_tabWidget_currentChanged(1);//ˢ����ʷ��������
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

void QHisdDataLoggerDialog::on_Language_currentIndexChanged(int index)//�����л�
{
    if(!bInitFinish)
    {
        return;//��ʼ��δ���ʱ ����
    }
   // on_sample_length_valueChanged(ui->sample_length->value());//���øı䳤���л�ˢ�±�ĺ���
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
  *Functions:ˢ����ʷ���ݱ��
  ************************************************************************
  *Value��
  *nTablelength ���ݳ��� Ҳ���Ǳ�������
  ************************************************************************
 *returns:
 *��
 ***********************************************************************
  *Edit time��2011.7.29
  *Edit by    ��zhy
  *************************************************************************/
void QHisdDataLoggerDialog::ReHisTable(int nTablelength)
{
    QString temp;
    int datatypecount=0;
    int iLanguage=ui->Language->currentIndex();
    while(ui->hisdatatable->rowCount()>0)//��ձ��ԭ�е�����
    {
        ui->hisdatatable->removeRow(0);
    }
    for(int icountrow=0;icountrow<nTablelength;icountrow++)
    {
        ui->hisdatatable->insertRow(icountrow);//����һ������
        temp=QString("LH%1").arg(datatypecount);//���µ�ַ
        QTableWidgetItem *newItem = new QTableWidgetItem(temp);
        ui->hisdatatable->setItem(icountrow,0,newItem);//��ӵ������
        ///��������
        QTableWidgetItem * item = NULL;
        item=new QTableWidgetItem(qhistabledata.mSampleList.at(icountrow).sNameList.at(iLanguage));
        ui->hisdatatable->setItem(icountrow,1,item);
        //32λ���ݵ�ʱ��
        int dataType = qhistabledata.mSampleList.at(icountrow).nDataType;
        if(dataType == 1 || dataType == 3 || dataType ==5 || dataType ==6)
        {
            datatypecount+=2;
        }
        //16λ���ݵ�ʱ��
        else if(dataType == 0 || dataType == 2 || dataType == 4)
        {
            datatypecount+=1;
        }
        //ASCII���ݵ�ʱ��
        else if(dataType == 7)
        {
            datatypecount+=qhistabledata.mSampleList.at(icountrow).nDataLen/2+qhistabledata.mSampleList.at(icountrow).nDataLen%2;
        }
    }
}
/************************************************************************
  *Functions:���¼����ڴ�����������д���ؼ���
  ************************************************************************
  *Value��
  *index ȡ������
  ************************************************************************
 *returns:
 *�ڸı����ݳ��ȣ�ȡ��������������������ʱ��ˢ���ڴ�������
 ***********************************************************************
  *Edit time��2011.7.29
  *Edit by    ��zhy
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
    memoryused=lengthcount*index;//�����ڴ�������
    temp=QString("%1").arg(memoryused);
    ui->memory_required->setText(temp);
}
/************************************************************************
  *Functions:ˢ����ʾ������������
  ************************************************************************
  *Value��
  *index ��������
  ************************************************************************
 *returns:
 *��
 ***********************************************************************
  *Edit time��2011.7.29
  *Edit by    ��zhy
  *************************************************************************/
void QHisdDataLoggerDialog::ReDataDisplaytype(int index)
{
    ui->label_19->setHidden(false);
    ui->data_item_totaldigits->setHidden(false);
    ui->lable_1->setHidden(false);
    ui->data_item_fractionaldigits->setHidden(false);
    ui->scaling->setHidden(false);
    ui->data_item_displaytype->clear();//�����ʾ����е�����

    if(index==0)
    {//Ϊ��ʾ����������
        ui->data_item_displaytype->setDisabled(false);
        ui->data_item_displaytype->addItem(tr("16λʮ����������"));
        ui->data_item_displaytype->addItem(tr("16λʮ��������"));
        ui->data_item_displaytype->addItem(tr("16λ�˽�����"));
        ui->data_item_totaldigits->setRange(0,5);
        //        if(ui->Total_Digits->value()>5)
//        {
//            ui->Total_Digits->setValue(5);
//        }
    }
    else if(index==1)
    {
        ui->data_item_displaytype->setDisabled(false);
        ui->data_item_displaytype->addItem(tr("32λʮ����������"));
        ui->data_item_displaytype->addItem(tr("32λʮ��������"));
        ui->data_item_displaytype->addItem(tr("32λ�˽�����"));
        ui->data_item_totaldigits->setRange(0,10);
    }
    else if(index==2)
    {
        ui->data_item_displaytype->addItem(tr("16λʮ����������"));
        ui->data_item_displaytype->setDisabled(true);
        ui->data_item_totaldigits->setRange(0,5);
    }
    else if(index==3)
    {
        ui->data_item_displaytype->addItem(tr("32λʮ����������"));
        ui->data_item_displaytype->setDisabled(true);
        ui->data_item_totaldigits->setRange(0,10);
    }
    else if(index==4)
    {
        ui->data_item_displaytype->setDisabled(false);
        ui->data_item_displaytype->addItem(tr("16λʮ����������"));
        ui->data_item_totaldigits->setRange(0,5);
    }
    else if(index==5)
    {
        ui->data_item_displaytype->setDisabled(false);
        ui->data_item_displaytype->addItem(tr("32λʮ����������"));
        ui->data_item_totaldigits->setRange(0,10);
    }
    else if(index==6)
    {
        ui->data_item_displaytype->setDisabled(false);
        ui->data_item_displaytype->addItem(tr("32λ������"));
        ui->data_item_totaldigits->setRange(0,10);
    }
    else if(index==7)
    {
        ui->data_item_displaytype->setDisabled(false);
        ui->data_item_displaytype->addItem(tr("ASCII�ַ���"));
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
 *�������ƣ�reDrawHisDataDisplay
 *�������ܣ�����ʷ�����ռ����ĳ��ȷ����仯��ʱ�򣬵��ȷ����ť���ػ泡���е�
 *                    ��ʷ������ʾ���ؼ�
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
    int nOldNum = 0; //ԭ��ʷ�����ռ���ȡ������
    int nNewNum = pwnd->m_pSamSysParame->m_historyLogData.nSampleLen;//��ʷ�����ռ���ȡ������
    QStringList *sList = new QStringList();
    QStringList slist;
    Items.clear();

    for(i = 0; i < totalSceneNum;i++)   //ɨ������ҳ��
    {
        pwnd->nActiveSheetIndex = i;
        pwnd->pView->setScene(pwnd->pSceneSheet[i]);
        QPainterPath path;
        path.addRect(0,0,pwnd->pSceneSheet[i]->width(),pwnd->pSceneSheet[i]->height());
        pwnd->pSceneSheet[i]->setSelectionArea(path);
        Items = pwnd->pSceneSheet[i]->selectedItems();
        foreach(QGraphicsItem *item,Items)
            item->setSelected(false);

        for(j = 0; j < Items.size(); j++)   //ɨ�赱ǰҳ������пؼ�
        {
            pItem = Items.at(j);//->topLevelItem();
            nID = pItem->data(GROUP_TYPE_KEY).toInt(); //ȡ�ؼ���Key��
            sList->clear();
            slist.clear();
            switch(nID)
            {
                case GROUP_TYPE_HISDATAALARM: //��ʷ������ʾ��
                    {
                        slist = pItem->data(GROUP_DATALIST_KEY).toStringList(); //ȡ��ÿ��item����������
                        for(k = 0; k < slist.size();k++)
                            sList->append(slist.at(k));

                        nOldNum = sList->at(99).toInt(); //37
                      //  if(nNewNum != nOldNum)//����û�иı��ʱ��ҲҪˢ�� ��Ϊ���ƻ�ı�
                        //Change by Dylan 2012-3-13
                        {
                            sList->replace(99,QString("%1").arg(nNewNum)); //37
                            int val = nNewNum - nOldNum;
                            if(val < 0) //�䷽������
                            {
                                for(k = 0; k < -val;k++)
                                    sList->removeLast();
                            }
                            else if(val > 0) //�䷽������
                            {
                                for(k = 0; k < val;k++)
                                    sList->append("1");
                            }
                            QDrawGraphics *pDraw = new QDrawGraphics;
                            pNewItem = pDraw->drawHistroyDataDisplayItem(sList);  //�ػ��䷽��ʾ��
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
  *Functions:��ҳ���л��������ݡ���ʱ���ٽ���ˢ����ʷ���ݵ�����
  ************************************************************************
  *Value��
  *int x��ҳ������� ��0��ʼ
  ************************************************************************
 *returns:
  *��
  ************************************************************************
  *Edit time��2012.3.13
  *Edit by    ��Dylan
  *************************************************************************/
void QHisdDataLoggerDialog::on_tabWidget_currentChanged(int x)
{
    if(x==0)//���л�����һ��page����ˢ�������е�����
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
            HISTORY_DATA_ITEM tempData;  //��ʼ����ʷ���ݵ��������
            tempData.bZoom = false;      //����
            tempData.nDataLen = 4;       //��λ��
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
    else if(mSampleSize > index)//���ı䳤��֮��������������
    {
        qhistabledata.mSampleList.resize(index);//��������ж��������
    }
    mSampleSize = qhistabledata.mSampleList.size();
    qhistabledata.nSampleLen = index;//�洢����
    for(int i = 0; i < mSampleSize; i++)
    {
        int size = qhistabledata.mSampleList.at(i).sNameList.size();
        while(size < LanguageNum)//������ȱ����������ٵĻ�
        {
            qhistabledata.mSampleList[i].sNameList.push_back("");//��ӱ���
            size++;
        }
    }
    ReMemoryCount(ui->number_sampling->value());

    ReHisTable(index);//�����������ˢ�±��
    //���ñ���ֹ�޸�
    ui->hisdatatable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
