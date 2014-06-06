#include "newplcctrl.h"
#include "ui_newplcctrl.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

NewPLCCtrl::NewPLCCtrl(int index,QWidget *parent):QDialog(parent),ui(new Ui::NewPLCCtrl)
{
    m_Index = index;
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    setFixedSize(size());
    setWindowTitle(tr("连接设置"));
    ui->combo_databits->setCurrentIndex(1);
    setConnect(m_Connect,true);
    ui->combo_serialport->setDisabled(true);
    //ui->combo_transmit->hide();
    ui->label_kp->setEnabled(false);
    if(index == 4 || index == 5)
    {
        ui->combo_baudrate->clear();
        QStringList bauds;
        bauds << "1" <<"2"<< "5" <<"10"<< "20" <<"40"<< "50" <<"80"<< "100" <<"150"<< "200" <<"250"<< "300" <<"400"
                << "500" <<"600" <<"800"<< "1000";
        ui->combo_baudrate->addItems(bauds);
        ui->label_kp->setEnabled(true);
        //ui->combo_baudrate->setCurrentIndex(13);
    }
}

NewPLCCtrl::~NewPLCCtrl()
{
    delete ui;
}

void NewPLCCtrl::setConnect(stConnect con,bool bInit)
{
    if (bInit)
    {
        /*QStringList names;
        names << tr("Com1") << tr("Com2") << tr("以太网");
        if( m_Index< names.size())
        {
            m_Connect.sConnectName = names.at(m_Index);
        }*/
        //ui->combo_serialport->setCurrentIndex(m_Index);
        //QString str = ui->combo_serialport->currentText();
        m_Connect.sConnectName      = ui->edit_name->text();
        //m_Connect.sConnectName      = ui->combo_serialport->currentText();

        m_Connect.eConnectPort      = m_Index;
        m_Connect.bUseRelationPort  = false;//默认不转发
        m_Connect.eRelationPort     = 0;
        m_Connect.nScreenNo         = 1;
        m_Connect.nBaudRate         = 9600;
        if(m_Index == 4 || m_Index == 5)
        {
            m_Connect.nBaudRate         = 500;
        }
        m_Connect.nDataBits         = 1;
        m_Connect.nStopBit          = 0;
        m_Connect.nCheckType        = 0;

        m_Connect.bMasterScreen      = 1;//主屏
        m_Connect.bConnectScreenPort = 0;//连接PLC口
        m_Connect.nSlaveScreenNum    = 1;
    }
    else
    {
        m_Connect = con;
    }

    refreshUi();
}

void NewPLCCtrl::refreshUi()
{
    ui->edit_number->setText(QString::number(m_Connect.id));
    ui->edit_name->setText(m_Connect.sConnectName);
    ui->combo_serialport->setCurrentIndex(m_Connect.eConnectPort);
    ui->spin_HMInumber->setValue(m_Connect.nScreenNo);
    ui->combo_baudrate->setCurrentIndex(ui->combo_baudrate->findText(QString::number(m_Connect.nBaudRate)));
    ui->combo_checkType->setCurrentIndex(m_Connect.nCheckType);
    ui->combo_databits->setCurrentIndex(m_Connect.nDataBits);
    ui->stopbits->setCurrentIndex(m_Connect.nStopBit);
    //ui->spin_interval->setValue(m_Connect.nIntervalTime);
    //ui->edit_IP->setText(m_Connect.sIpAddr);
    //ui->edit_port->setText(QString::number(m_Connect.nNetPortNum));
    ui->check_transmit->setChecked(m_Connect.bUseRelationPort);
//    if (ui->check_transmit->isChecked())
//    {
//        ui->combo_transmit->setEnabled(true);
//        if (m_Connect.eRelationPort>=0)
//        {
//            ui->combo_transmit->setCurrentIndex(m_Connect.eRelationPort);
//        }
//    }
//    else
//    {
//        ui->combo_transmit->setEnabled(false);
//    }
    if (ui->combo_serialport->currentIndex() == 3)
    {
        showIpLabel(true);
    }
    else
    {
        showIpLabel(false);
    }
    if(ui->combo_serialport->currentIndex() >= 4)//CAN
    {
        ui->check_transmit->setEnabled(false);
    }
    else{
        ui->check_transmit->setEnabled(true);
    }

    if(1 == m_Connect.bMasterScreen)
    {
        ui->m_MainScreenradioBtn->setChecked(true);
    }
    else
    {
        ui->m_FromScreenradioBtn->setChecked(true);
    }

    if(m_Connect.bConnectScreenPort == 0)//连接PLC口
    {
        ui->m_LinkFromScreenradioBtn->setChecked(false);
    }
    else
    {
        ui->m_LinkFromScreenradioBtn->setChecked(true);
    }

    ui->m_FromScreenspinBox->setValue(m_Connect.nSlaveScreenNum);

//    if (m_Connect.eRelationPort>=0)
//    {
//        ui->combo_transmit->setCurrentIndex(m_Connect.eRelationPort);
//    }
    on_check_transmit_clicked(ui->check_transmit->isChecked());
}

void NewPLCCtrl::on_pushButton_sure_clicked()
{
    //bool bExist = false;
    if(ui->edit_name->text() == "")
    {
        QString msg;
        msg = tr("连接名称不能为空");
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,msg,0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        ui->edit_name->setFocus();
        return;
    }
    int i;
    for ( i =0; i<pwnd->m_pSamSysParame->m_qvcConnect.size(); i++)
    {
        if (i != m_Index && pwnd->m_pSamSysParame->m_qvcConnect[i].sConnectName == ui->edit_name->text() )
        {
            QString msg;
            msg = tr("连接名称 \"")+ui->edit_name->text()+tr("\" 已存在");
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,msg,0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("确定"),QMessageBox::AcceptRole);
            box.exec();
            return;
        }
        if(i != m_Index && pwnd->m_pSamSysParame->m_qvcConnect[i].eConnectPort == ui->combo_serialport->currentIndex())
        {
            QString msg;
            msg = tr("连接端口")+ui->combo_serialport->currentText()+tr("已被使用");
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,msg,0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("确定"),QMessageBox::AcceptRole);
            box.exec();
            return;
        }
    }

//    if(ui->check_transmit->isChecked() &&
//       ui->combo_transmit->currentText() == ui->combo_serialport->currentText())
//    {
//        QString msg;
//        msg = tr("转发端口不能和连接端口相同");
//        QMessageBox box(QMessageBox::Warning,VERSION_NAME,msg,0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
//        box.addButton(tr("确定"),QMessageBox::AcceptRole);
//        box.exec();
//        return;
//    }
    m_Connect.id = ui->edit_number->text().toInt();
    m_Connect.sConnectName = ui->edit_name->text();
    m_Connect.eConnectPort = ui->combo_serialport->currentIndex();
    m_Connect.nScreenNo = ui->spin_HMInumber->value();
    m_Connect.nBaudRate = ui->combo_baudrate->currentText().toInt();
    m_Connect.nCheckType = ui->combo_checkType->currentIndex();
    m_Connect.nDataBits = ui->combo_databits->currentIndex();
    m_Connect.nStopBit = ui->stopbits->currentIndex();

    if(ui->m_MainScreenradioBtn->isChecked())
    {
        m_Connect.bMasterScreen = 1;
    }
    else
    {
        m_Connect.bMasterScreen = 0;
    }

    if(ui->m_LinkFromScreenradioBtn->isChecked())
    {
        m_Connect.bConnectScreenPort = 1;
    }
    else
    {
        m_Connect.bConnectScreenPort = 0;
    }

    m_Connect.nSlaveScreenNum = ui->m_FromScreenspinBox->value();

    qDebug()<<"save nSlaveScreenNum========="<<m_Connect.nSlaveScreenNum;
    //m_Connect.nIntervalTime = ui->spin_interval->value();
    //m_Connect.sIpAddr = ui->edit_IP->text();
    //m_Connect.nNetPortNum = ui->edit_port->text().toInt();
    m_Connect.bUseRelationPort = ui->check_transmit->isChecked();
    //m_Connect.eRelationPort = ui->combo_transmit->currentIndex();
    accept();
}

void NewPLCCtrl::on_pushButton_cancel_clicked()
{
    close();
}

void NewPLCCtrl::on_DefaultSet_clicked()
{
    setConnect(m_Connect,true);
}

void NewPLCCtrl::on_check_transmit_stateChanged(int checked)
{
    //if(checked)
    {
        //ui->combo_transmit->setEnabled(checked);
    }
}

void NewPLCCtrl::on_combo_serialport_currentIndexChanged(int index)
{
    if(index == 2)
    {
        showIpLabel(true);
    }
    else
    {
        showIpLabel(false);
    }
}

void NewPLCCtrl::showIpLabel(bool checked)
{
    ui->combo_baudrate->setEnabled(!checked);
    ui->combo_checkType->setEnabled(!checked);
    ui->combo_databits->setEnabled(!checked);
    ui->stopbits->setEnabled(!checked);
    //ui->spin_interval->setEnabled(!checked);
    ui->label_baudrate->setEnabled(!checked);
    ui->label_check->setEnabled(!checked);
    ui->label_bit->setEnabled(!checked);
    ui->label_stopbit->setEnabled(!checked);
    //ui->label_interval->setEnabled(!checked);
}
//帮助
void NewPLCCtrl::on_pushButton_sure_2_clicked()
{
    pwnd->loadHelpHtm(TREE_COM_LINK);
}

void NewPLCCtrl::on_check_transmit_clicked(bool checked)
{
    if(checked)
    {
        ui->m_MainScreenradioBtn->setEnabled(true);
        ui->m_FromScreenradioBtn->setEnabled(true);
        if(ui->m_MainScreenradioBtn->isChecked())
        {
            ui->m_LinkFromScreenradioBtn->setEnabled(true);
            ui->m_LinkPLCradioBtn->setEnabled(true);
            //ui->combo_transmit->setEnabled(true);
            if(ui->m_LinkFromScreenradioBtn->isChecked())
            {
                ui->label->setEnabled(true);
                ui->m_FromScreenspinBox->setEnabled(true);
            }
            else
            {
                ui->label->setEnabled(false);
                ui->m_FromScreenspinBox->setEnabled(false);
            }
        }
        else
        {
            ui->m_LinkFromScreenradioBtn->setEnabled(false);
            ui->m_LinkPLCradioBtn->setEnabled(false);
            //ui->combo_transmit->setEnabled(false);
            ui->label->setEnabled(false);
            ui->m_FromScreenspinBox->setEnabled(false);
        }
    }
    else
    {
        ui->m_MainScreenradioBtn->setEnabled(false);
        ui->m_FromScreenradioBtn->setEnabled(false);
        ui->m_LinkFromScreenradioBtn->setEnabled(false);
        ui->m_LinkPLCradioBtn->setEnabled(false);
        //ui->combo_transmit->setEnabled(false);
        ui->label->setEnabled(false);
        ui->m_FromScreenspinBox->setEnabled(false);
    }
}

void NewPLCCtrl::on_m_MainScreenradioBtn_clicked(bool checked)
{
    bool bChecked = ui->check_transmit->isChecked();
    on_check_transmit_clicked(bChecked);
}

void NewPLCCtrl::on_m_FromScreenradioBtn_clicked(bool checked)
{
    bool bChecked = ui->check_transmit->isChecked();
    on_check_transmit_clicked(bChecked);
}

void NewPLCCtrl::on_m_LinkPLCradioBtn_clicked(bool checked)
{
    bool bChecked = ui->check_transmit->isChecked();
    on_check_transmit_clicked(bChecked);
}

void NewPLCCtrl::on_m_LinkFromScreenradioBtn_clicked(bool checked)
{
    bool bChecked = ui->check_transmit->isChecked();
    on_check_transmit_clicked(bChecked);
}
