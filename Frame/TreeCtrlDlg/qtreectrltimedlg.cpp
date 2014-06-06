#include "qtreectrltimedlg.h"
#include "ui_qtreectrltimedlg.h"
#include  "Frame\mainwindow.h"
extern MainWindow  *pwnd;

QTreeCtrlTimeDlg::QTreeCtrlTimeDlg(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::QTreeCtrlTimeDlg)
{
    ui->setupUi(this);
    this->setFixedHeight(580);
    initDlg();

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    ui->timetoplc_datastyle_lineedit->addItem(tr("16位BCD"));
    ui->sametimewithPLC_datastyle_comboBox->addItem(tr("16位BCD"));
    ui->timetoplc_size_lineedit->addItem("7");
    ui->sametimewithPLC_size_comboBox->addItem("7");
    ui->timetoplc_interval_spinBox->setRange(1,255);
    ui->sametimewithPLC_interval_spinBox->setRange(1,255);


    buttonbox=new QDialogButtonBox;
    buttonbox->addButton(tr("确定"),QDialogButtonBox::AcceptRole);
    buttonbox->addButton(tr("取消"),QDialogButtonBox::RejectRole);
    buttonbox->addButton(tr("帮助"),QDialogButtonBox::HelpRole);
    QVBoxLayout *vbox=new  QVBoxLayout;
    vbox->addWidget(ui->tabWidget);
    vbox->addWidget(buttonbox);
    setLayout(vbox);
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(confyButton()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonbox, SIGNAL(helpRequested()), this, SLOT(helpButton()));
}//ok

QTreeCtrlTimeDlg::~QTreeCtrlTimeDlg()
{
    delete ui;
}

void QTreeCtrlTimeDlg::on_timetoplc_timed_radiobutton_clicked()
{
    if(ui->timetoplc_timed_radiobutton->isChecked())
    {
        ui->timetoplc_interval_spinBox->setEnabled(true);
        ui->label_s->setVisible(true);
        ui->timetoplc_interval_label->setEnabled(true);

        ui->timetoplc_trigered_lineEdit->setEnabled(false);
        ui->timetoplc_trigered_pushButton->setEnabled(false);
        ui->checkBox_3->setEnabled(false);
    }
}//ok

void QTreeCtrlTimeDlg::on_timetoplc_trigerred_radiobutton_clicked()
{
    if(ui->timetoplc_trigerred_radiobutton->isChecked())
    {
        ui->timetoplc_trigered_lineEdit->setEnabled(true);
        ui->timetoplc_trigered_pushButton->setEnabled(true);
        ui->checkBox_3->setEnabled(true);
        ui->timetoplc_interval_spinBox->setEnabled(false);
        ui->label_s->setEnabled(false);
        ui->timetoplc_interval_label->setEnabled(false);
    }
}//ok

void QTreeCtrlTimeDlg::on_sametimewithPLC_timed_radioButton_clicked()
{
    if(ui->sametimewithPLC_timed_radioButton->isChecked())
    {
        ui->sametimewithPLC_interval_label->setEnabled(true);
        ui->sametimewithPLC_interval_spinBox->setEnabled(true);
        ui->label_14->setEnabled(true);

        ui->sametimewithPLC_trigered_lineEdit->setEnabled(false);
        ui->sametimewithPLC_trigered_pushButton->setEnabled(false);
        ui->checkBox_2->setEnabled(false);
    }
}

void QTreeCtrlTimeDlg::on_sametimewithPLC_trigered_radioButton_clicked()
{
    if(ui->sametimewithPLC_trigered_radioButton->isChecked())
    {
        ui->sametimewithPLC_trigered_lineEdit->setEnabled(true);
        ui->sametimewithPLC_trigered_pushButton->setEnabled(true);
        ui->checkBox_2->setEnabled(true);

        ui->sametimewithPLC_interval_label->setEnabled(false);
        ui->sametimewithPLC_interval_spinBox->setEnabled(false);
        ui->label_14->setEnabled(false);
    }
}//ok


void QTreeCtrlTimeDlg::on_timetoplc_writeaddress_pushButton_clicked()
{
    QString addrStr = ui->timetoplc_writeaddress_lineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(kWriteTimeToPLC,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->timetoplc_writeaddress_lineEdit->setText(kWriteTimeToPLC.sShowAddr);
    }

}//ok

void QTreeCtrlTimeDlg::on_timetoplc_trigered_pushButton_clicked()
{
    QString addrStr = ui->timetoplc_trigered_lineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(kWriteTriggered,addrStr,0,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->timetoplc_trigered_lineEdit->setText(kWriteTriggered.sShowAddr);
    }

}//ok

void QTreeCtrlTimeDlg::on_sametimewithPLC_readaddress_pushButton_clicked()
{
    QString addrStr = ui->sametimewithPLC_readaddress_lineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(kReadAddress,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->sametimewithPLC_readaddress_lineEdit->setText(kReadAddress.sShowAddr);
    }

}//ok


void QTreeCtrlTimeDlg::on_sametimewithPLC_trigered_pushButton_clicked()
{
    QString addrStr = ui->sametimewithPLC_trigered_lineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(kReadTriggered,addrStr,0,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->sametimewithPLC_trigered_lineEdit->setText(kReadTriggered.sShowAddr);
    }

}//ok

void QTreeCtrlTimeDlg::confyButton()
{

    if(ui->treectrltimedlg_timetoHMI_groupbox->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(kWriteTimeToPLC,tr("写入地址"),ui->timetoplc_writeaddress_lineEdit,1))
        {
            return;
        }

        if(ui->timetoplc_trigerred_radiobutton->isChecked())
        {
            if(! pwnd->IsAddressCheckRight(kWriteTriggered,tr("触发位"),ui->timetoplc_trigered_lineEdit,0))
            {
                return;
            }

        }
    }
    if(ui->treectrltimedlg_sametimewithPLC_groupbox->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(kReadAddress,tr("读取地址"),ui->sametimewithPLC_readaddress_lineEdit,1))
        {
            return;
        }

        if(ui->sametimewithPLC_trigered_radioButton->isChecked())
        {
            if(! pwnd->IsAddressCheckRight(kReadTriggered,tr("触发位"),ui->sametimewithPLC_trigered_lineEdit,0))
            {
                return;
            }

        }
    }

    pwnd->is_Save=false;//
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

    pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.mCtlAddr = kWriteTimeToPLC;
    pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.mTriggerAddr = kWriteTriggered;
    pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.mCtlAddr = kReadAddress;
    pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.mTriggerAddr = kReadTriggered;

    pwnd->m_pSamSysParame->m_clockProp.bDownLoadTime= ui->checkBox->isChecked();//是否选择系统时间到PLC
    pwnd->m_pSamSysParame->m_clockProp.bWTimeToPlc=ui->treectrltimedlg_timetoHMI_groupbox->isChecked(); //是否选择写时间到PLC
    pwnd->m_pSamSysParame->m_clockProp.bRTimeFromPlc=ui->treectrltimedlg_sametimewithPLC_groupbox->isChecked();//是否选择月PLC同步
    pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.nDataType = ui->timetoplc_datastyle_lineedit->currentIndex();  //写时间到PLC的数据类型
    pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.nDataType=ui->sametimewithPLC_datastyle_comboBox->currentIndex(); //与PLC时间同步的数据类型
    pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.nAddrLen=ui->timetoplc_size_lineedit->currentIndex(); //写时间到PLC的长度
    pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.nAddrLen=ui->sametimewithPLC_size_comboBox->currentIndex();//与PLC时间同步的长度


    /*写时间到PLC的计时选择状态*/
    if(ui->timetoplc_timed_radiobutton->isChecked())
    {
        pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.nStartType = 0;
    }
    else if(ui->timetoplc_trigerred_radiobutton->isChecked())
    {
        pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.nStartType = 1;
    }
    else
    {
        pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.nStartType = 199;
    }
    /*与PLC时间同步的计时选择状态*/
    if(ui->sametimewithPLC_timed_radioButton->isChecked())
    {
        pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.nStartType = 0;
    }
    else if(ui->sametimewithPLC_trigered_radioButton->isChecked())
    {
        pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.nStartType = 1;
    }
    else
    {
        pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.nStartType = 199;
    }

    pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.nTimeInterval=ui->timetoplc_interval_spinBox->value(); //写时间到PLC的间隔时间
    pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.nTimeInterval=ui->sametimewithPLC_interval_spinBox->value();//与PLC时间同步的间隔时间
    pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.bReset=ui->checkBox_3->isChecked();
    pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.bReset=ui->checkBox_2->isChecked();
    accept();

}//ok


void QTreeCtrlTimeDlg::helpButton()
{
    pwnd->loadHelpHtm(TREE_CLOCK);
}//ok

void  QTreeCtrlTimeDlg::initDlg()
{
    ui->checkBox->setChecked(pwnd->m_pSamSysParame->m_clockProp.bDownLoadTime);//是否选择系统时间到PLC
    ui->treectrltimedlg_timetoHMI_groupbox->setChecked(pwnd->m_pSamSysParame->m_clockProp.bWTimeToPlc);//是否选择写时间到PLC
    ui->treectrltimedlg_sametimewithPLC_groupbox->setChecked(pwnd->m_pSamSysParame->m_clockProp.bRTimeFromPlc);//是否选择月PLC同步
    ui->timetoplc_datastyle_lineedit->setCurrentIndex(pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.nDataType);//写时间到PLC的数据类型
    ui->sametimewithPLC_datastyle_comboBox->setCurrentIndex(pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.nDataType);//与PLC时间同步的数据类型
    ui->timetoplc_size_lineedit->setCurrentIndex(pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.nAddrLen); //写时间到PLC的长度
    ui->sametimewithPLC_size_comboBox->setCurrentIndex(pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.nAddrLen);//与PLC时间同步的长度
    ui->timetoplc_writeaddress_lineEdit->setText(pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.mCtlAddr.sShowAddr );//写入地址
    ui->sametimewithPLC_readaddress_lineEdit->setText(pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.mCtlAddr.sShowAddr);//读取地址
    if(pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.nStartType == 0)
    {
        ui->timetoplc_timed_radiobutton->setChecked(true); //写时间到PLC的计时选择状态
        ui->timetoplc_trigerred_radiobutton->setChecked(false); //写时间到PLC的触发状态
    }
    else if(pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.nStartType == 1)
    {
        ui->timetoplc_timed_radiobutton->setChecked(false); //写时间到PLC的计时选择状态
        ui->timetoplc_trigerred_radiobutton->setChecked(true); //写时间到PLC的触发状态
    }
    if(pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.nStartType == 0)
    {
        ui->sametimewithPLC_timed_radioButton->setChecked(true);//与PLC时间同步的计时选择状态
        ui->sametimewithPLC_trigered_radioButton->setChecked(false);//与PLC时间同步的触发状态
    }
    else if(pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.nStartType == 1)
    {
        ui->sametimewithPLC_timed_radioButton->setChecked(false);//与PLC时间同步的计时选择状态
        ui->sametimewithPLC_trigered_radioButton->setChecked(true);//与PLC时间同步的触发状态
    }

    ui->timetoplc_interval_spinBox->setValue( pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.nTimeInterval);//写时间到PLC的间隔时间
    ui->sametimewithPLC_interval_spinBox->setValue( pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.nTimeInterval);//与PLC时间同步的间隔时间
    ui->timetoplc_trigered_lineEdit->setText(pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.mTriggerAddr.sShowAddr );//写时间到PLC的触发位
    ui->sametimewithPLC_trigered_lineEdit->setText(pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.mTriggerAddr.sShowAddr); //与PLC时间同步的触发位
    ui->checkBox_2->setChecked(pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.bReset);
    ui->checkBox_3->setChecked(pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.bReset);
        kWriteTimeToPLC = pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.mCtlAddr;
        kWriteTriggered = pwnd->m_pSamSysParame->m_clockProp.mWTimeToPlc.mTriggerAddr;
        kReadAddress = pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.mCtlAddr;
        kReadTriggered = pwnd->m_pSamSysParame->m_clockProp.mRTimeFromPlc.mTriggerAddr;


    if(ui->timetoplc_trigerred_radiobutton->isChecked())
    {
        ui->timetoplc_trigered_lineEdit->setEnabled(true);
        ui->timetoplc_trigered_pushButton->setEnabled(true);
        ui->checkBox_3->setEnabled(true);
    }
    else
    {
        ui->timetoplc_trigered_lineEdit->setEnabled(false);
        ui->timetoplc_trigered_pushButton->setEnabled(false);
        ui->checkBox_3->setEnabled(false);
    }

    if(ui->sametimewithPLC_trigered_radioButton->isChecked())
    {
        ui->sametimewithPLC_trigered_lineEdit->setEnabled(true);
        ui->sametimewithPLC_trigered_pushButton->setEnabled(true);
        ui->checkBox_2->setEnabled(true);
    }
    else
    {
        ui->sametimewithPLC_trigered_lineEdit->setEnabled(false);
        ui->sametimewithPLC_trigered_pushButton->setEnabled(false);
        ui->checkBox_2->setEnabled(false);
    }

    if(ui->timetoplc_timed_radiobutton->isChecked())
    {
        ui->timetoplc_interval_label->setEnabled(true);
        ui->timetoplc_interval_spinBox->setEnabled(true);
        ui->label_s->setEnabled(true);
    }
    else
    {
        ui->timetoplc_interval_label->setEnabled(false);
        ui->timetoplc_interval_spinBox->setEnabled(false);
        ui->label_s->setEnabled(false);
    }//

    if(ui->sametimewithPLC_timed_radioButton->isChecked())
    {
        ui->sametimewithPLC_interval_label->setEnabled(true);
        ui->sametimewithPLC_interval_spinBox->setEnabled(true);
        ui->label_14->setEnabled(true);
    }
    else
    {
        ui->sametimewithPLC_interval_label->setEnabled(false);
        ui->sametimewithPLC_interval_spinBox->setEnabled(false);
        ui->label_14->setEnabled(false);
    }
}

void QTreeCtrlTimeDlg::on_treectrltimedlg_timetoHMI_groupbox_toggled(bool ischecked)
{
    if(ischecked)
    {
        ui->treectrltimedlg_sametimewithPLC_groupbox->setChecked(false);
        on_treectrltimedlg_sametimewithPLC_groupbox_toggled(false);
        ui->timetoplc_datastyle_label->setEnabled(true);
        ui->timetoplc_datastyle_lineedit->setEnabled(true);
        ui->timetoplc_size_label->setEnabled(true);
        ui->timetoplc_size_lineedit->setEnabled(true);
        ui->timetoplc_writeaddress_label->setEnabled(true);
        ui->timetoplc_writeaddress_lineEdit->setEnabled(true);
        ui->timetoplc_writeaddress_pushButton->setEnabled(true);
        ui->timetoplc_startstyle_groupbox->setEnabled(true);
        ui->timetoplc_timed_radiobutton->setEnabled(true);
        ui->timetoplc_timed_radiobutton->setEnabled(true);
        ui->timetoplc_interval_label->setEnabled(true);
        ui->timetoplc_interval_spinBox->setEnabled(true);
        ui->label_s->setEnabled(true);
        ui->timetoplc_trigerred_radiobutton->setEnabled(true);
        ui->timetoplc_trigered_lineEdit->setEnabled(false);
        ui->checkBox_3->setEnabled(false);
        ui->timetoplc_trigered_pushButton->setEnabled(false);
    }
    else
    {
        ui->timetoplc_datastyle_label->setEnabled(false);
        ui->timetoplc_datastyle_lineedit->setEnabled(false);
        ui->timetoplc_size_label->setEnabled(false);
        ui->timetoplc_size_lineedit->setEnabled(false);
        ui->timetoplc_writeaddress_label->setEnabled(false);
        ui->timetoplc_writeaddress_lineEdit->setEnabled(false);
        ui->timetoplc_writeaddress_pushButton->setEnabled(false);
        ui->timetoplc_startstyle_groupbox->setEnabled(false);
        ui->timetoplc_timed_radiobutton->setEnabled(false);
        ui->timetoplc_interval_label->setEnabled(false);
        ui->timetoplc_interval_spinBox->setEnabled(false);
        ui->label_s->setEnabled(false);
        ui->timetoplc_trigerred_radiobutton->setEnabled(false);
        ui->timetoplc_trigered_lineEdit->setEnabled(false);
        ui->checkBox_3->setEnabled(false);
        ui->timetoplc_trigered_pushButton->setEnabled(false);
    }

}

void QTreeCtrlTimeDlg::on_treectrltimedlg_sametimewithPLC_groupbox_toggled(bool ischecked )
{
    if(ischecked)
    {
        ui->treectrltimedlg_timetoHMI_groupbox->setChecked(false);
        on_treectrltimedlg_timetoHMI_groupbox_toggled(false);

        ui->sametimewithPLC_datastyle_label->setEnabled(true);
        ui->sametimewithPLC_datastyle_comboBox->setEnabled(true);
        ui->sametimewithPLC_size_label->setEnabled(true);
        ui->sametimewithPLC_size_comboBox->setEnabled(true);
        ui->sametimewithPLC_readaddress_label->setEnabled(true);
        ui->sametimewithPLC_readaddress_lineEdit->setEnabled(true);
        ui->sametimewithPLC_readaddress_pushButton->setEnabled(true);
        ui->sametimewithPLC_startstyle_groupBox->setEnabled(true);
        ui->sametimewithPLC_timed_radioButton->setEnabled(true);
        ui->sametimewithPLC_timed_radioButton->setChecked(true);
        ui->sametimewithPLC_interval_label->setEnabled(true);
        ui->sametimewithPLC_interval_spinBox->setEnabled(true);
        ui->label_14->setEnabled(true);
        ui->sametimewithPLC_trigered_radioButton->setEnabled(true);
        ui->sametimewithPLC_trigered_lineEdit->setEnabled(false);
        ui->sametimewithPLC_trigered_pushButton->setEnabled(false);
        ui->checkBox_2->setEnabled(false);
    }
    else
    {
        ui->sametimewithPLC_datastyle_label->setEnabled(false);
        ui->sametimewithPLC_datastyle_comboBox->setEnabled(false);
        ui->sametimewithPLC_size_label->setEnabled(false);
        ui->sametimewithPLC_size_comboBox->setEnabled(false);
        ui->sametimewithPLC_readaddress_label->setEnabled(false);
        ui->sametimewithPLC_readaddress_lineEdit->setEnabled(false);
        ui->sametimewithPLC_readaddress_pushButton->setEnabled(false);
        ui->sametimewithPLC_startstyle_groupBox->setEnabled(false);
        ui->sametimewithPLC_timed_radioButton->setEnabled(false);
        ui->sametimewithPLC_interval_label->setEnabled(false);
        ui->sametimewithPLC_interval_spinBox->setEnabled(false);
        ui->label_14->setEnabled(false);
        ui->sametimewithPLC_trigered_radioButton->setEnabled(false);
        ui->sametimewithPLC_trigered_lineEdit->setEnabled(false);
        ui->sametimewithPLC_trigered_pushButton->setEnabled(false);
        ui->checkBox_2->setEnabled(false);
    }
}
