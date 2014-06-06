#include "protocoldlg.h"
#include "ui_protocoldlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

ProtocolDlg::ProtocolDlg(stProtocol protocol,int index,bool bEthnet,int iProType,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProtocolDlg)
{
    m_Index = index;
    m_iType = iProType;
    if(index == -1)
    {
        setDefault();
    }
    else
    {
        m_Protocol = protocol;
    }
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    QSize sz = size();
    setFixedSize(sz);//禁止拖放窗口大小

    setWindowTitle(tr("协议"));

    ui->combo_manu->clear();
    QStringList manus ;
    foreach(PLC_FACTORY factory,pwnd->vPlc)
    {
        bool bShow = false;
        foreach(PLC_MODEL model,factory.models)
        {
            if(PRO_SERIAL == m_iType)
            {
                if(model.ePorttype == PORT_SERIAL || model.ePorttype == PORT_SERIAL_ETHNET)
                {
                    bShow = true;
                    break;
                }
            }
            else if(PRO_ETHNET == m_iType)
            {
                if(model.ePorttype == PORT_ETHNET || model.ePorttype == PORT_SERIAL_ETHNET)
                {
                    bShow = true;
                    break;
                }
            }
//            else if(3 == m_iType)
//            {
//                if(model.ePorttype == PORT_CAN)
//                {
//                    bShow = true;
//                    break;
//                }
//            }
        }
        if(bShow)
        {
            manus << pwnd->findFactoryFullName(factory.sFactoryName);
        }
    }


    connect(ui->combo_manu,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_combo_manu_Changed(QString)));
    connect(ui->combo_protocol,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_combo_model_Changed(QString)));
    ui->combo_manu->addItems(manus);
    updataUi();
    if (index == -1)
    {
            ui->edit_name->setText(ui->combo_protocol->currentText());
    }
    connect(ui->btn_accept,SIGNAL(clicked()),this,SLOT(on_btn_accepted()));
    connect(ui->btn_cancel,SIGNAL(clicked()),this,SLOT(reject()));
    ui->label_IP->setEnabled(bEthnet);
    ui->label_port->setEnabled(bEthnet);
    ui->edit_IP->setEnabled(bEthnet);
    ui->edit_port->setEnabled(bEthnet);
    ui->m_UdpcheckBox->setEnabled(bEthnet);
#ifdef AKPLC
    ui->combo_manu->setDisabled(true);
    ui->combo_protocol->setDisabled(true);
#endif
}

ProtocolDlg::~ProtocolDlg()
{
    delete ui;
}

//m_Protocol 设置默认值
void ProtocolDlg::setDefault()
{
    m_Protocol.sProtocolName = "";
    m_Protocol.nPlcNo = 0;
    m_Protocol.nReceiveTimeout = 0;
    m_Protocol.nMaxRWLen = 0;
    m_Protocol.nRetryTime = 0;
    m_Protocol.nIntervalTime = 0;
    m_Protocol.nCycleTime = 0;
    m_Protocol.ip = "192.168.1.100";
    m_Protocol.port = 8000;
    m_Protocol.bIsTcpProtocol = false;
}

void ProtocolDlg::updataUi()
{
    QIntValidator *validator = new QIntValidator(0,65535,this);
    ui->edit_port->setValidator(validator);

    //QRegExp regExp("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
    //QValidator *pValidator = new QRegExpValidator(regExp, this);
    //ui->edit_IP->setValidator(pValidator);
    //ui->edit_IP->setInputMask("000.000.000.000");

    int index = ui->combo_manu->findText(pwnd->findFactoryFullName(m_Protocol.sFactoryName));
    if(index != -1)
    {
        ui->combo_manu->setCurrentIndex(index);
    }
    index = ui->combo_protocol->findText(m_Protocol.sProtocolName);
    if(index != -1)
    {
        ui->combo_protocol->setCurrentIndex(index);

    }
    if (m_Index != -1)
    {
        ui->spin_stationIndex->setValue(m_Protocol.nPlcNo);
        ui->spin_time->setValue(m_Protocol.nReceiveTimeout);
        ui->spin_length->setValue(m_Protocol.nMaxRWLen);
        ui->spin_retry->setValue(m_Protocol.nRetryTime);
        ui->spin_interval->setValue(m_Protocol.nIntervalTime);
        ui->edit_name->setText(m_Protocol.sName);
        ui->spin_cycleTime->setValue(m_Protocol.nCycleTime);
        ui->edit_IP->setIp(m_Protocol.ip);
        ui->edit_port->setText(QString::number(m_Protocol.port));
        ui->m_UdpcheckBox->setChecked(m_Protocol.bIsTcpProtocol);
    }
}

void ProtocolDlg::on_btn_accepted()
{
    QString name = ui->edit_name->text();
    QString str = ui->combo_protocol->currentText();
    foreach ( stConnect con,pwnd->m_pSamSysParame->m_qvcConnect)
    {
        for(int i =0; i< con.vProtocols.size();i++)
        {
            if (i != m_Index && con.vProtocols[i].sName == name && con.vProtocols[i].sProtocolName == str)
            {
                QString msg;
                msg = tr("设备名称 \"")+name+tr("\" 已存在");
                QMessageBox box(QMessageBox::Warning,PRO_FULL_NAME,msg,0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
                box.addButton(tr("确定"),QMessageBox::AcceptRole);
                box.exec();
                return;
            }
        }
    }

    if(name.isEmpty())
    {
        QMessageBox msg(QMessageBox::Warning,PRO_FULL_NAME,tr("设备名称不能为空"),
                0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        msg.addButton(tr("确定"),QMessageBox::AcceptRole);
        msg.exec();
        return ;
    }
    m_Protocol.sFactoryName = ui->combo_manu->currentText().split("(").at(0);
    m_Protocol.sProtocolName = ui->combo_protocol->currentText();
    m_Protocol.nPlcNo = ui->spin_stationIndex->value();
    m_Protocol.nReceiveTimeout = ui->spin_time->value();
    m_Protocol.nMaxRWLen = ui->spin_length->value();
    m_Protocol.nRetryTime = ui->spin_retry->value();
    m_Protocol.nIntervalTime = ui->spin_interval->value();
    m_Protocol.sName = ui->edit_name->text();
    m_Protocol.nCycleTime = ui->spin_cycleTime->value();
    m_Protocol.ip = ui->edit_IP->GetIpAddressString();
    m_Protocol.port = ui->edit_port->text().toInt();
    m_Protocol.bIsTcpProtocol = ui->m_UdpcheckBox->isChecked();

    foreach(PLC_FACTORY factory,pwnd->vPlc)
    {
        if (pwnd->findFactoryFullName(factory.sFactoryName) == ui->combo_manu->currentText())
        {
            foreach(PLC_MODEL model,factory.models)
            {
                if (model.sModelName == ui->combo_protocol->currentText())
                {
                    m_Protocol.mPlc = model;
                }
            }
        }
    }
    accept();
}

void ProtocolDlg::on_btn_default_clicked()
{
    PLC_MODEL cModel;
    QString modelName = ui->combo_protocol->currentText();
    QString manuName = ui->combo_manu->currentText();

    bool bExist = false;
    foreach(PLC_FACTORY factory,pwnd->vPlc)
    {
        if(manuName == pwnd->findFactoryFullName(factory.sFactoryName))
        {
            foreach(PLC_MODEL model,factory.models)
            {
                if(model.sModelName == modelName)
                {
                    cModel = model;
                    bExist = true;
                    break;
                }
            }
            break;
        }
    }
    if(bExist)
    {
        ui->spin_interval->setValue(cModel.nIntervalTime);
        ui->spin_length->setValue(cModel.nMaxRWLen);
        ui->spin_retry->setValue(cModel.nRetryTime);
        ui->spin_stationIndex->setValue(cModel.nPlcNo);
        ui->spin_time->setValue(cModel.nReceiveTimeout);
        ui->spin_cycleTime->setValue(cModel.nCycleTime);
        ui->m_UdpcheckBox->setChecked(false);
    }
}

void ProtocolDlg::on_combo_manu_Changed(QString manuName)
{
    QStringList modelNames;
    foreach(PLC_FACTORY factory,pwnd->vPlc)
    {
        if(manuName == pwnd->findFactoryFullName(factory.sFactoryName))
        {
            ui->combo_protocol->clear();
            foreach(PLC_MODEL model,factory.models)
            {
                if(PRO_SERIAL == m_iType)
                {
                    if(model.ePorttype == PORT_SERIAL || model.ePorttype == PORT_SERIAL_ETHNET)
                    {
                        modelNames << model.sModelName;
                    }
                }
                else if(PRO_ETHNET == m_iType)
                {
                    if(model.ePorttype == PORT_ETHNET || model.ePorttype == PORT_SERIAL_ETHNET)
                    {
                        modelNames << model.sModelName;
                    }
                }
//                else if(3 == m_iType)
//                {
//                    if(model.ePorttype == PORT_CAN)
//                    {
//                        modelNames << model.sModelName;
//                    }
//                }
            }
            break;
        }
    }
    ui->combo_protocol->addItems(modelNames);
    if(ui->combo_protocol->count()>0)
    {
        ui->combo_protocol->setCurrentIndex(0);
    }
    ui->edit_name->setText(ui->combo_protocol->currentText());
}

void ProtocolDlg::on_combo_model_Changed(QString modelName)
{
    QStringList modelNames;
    PLC_MODEL cModel;
    QString manuName = ui->combo_manu->currentText();

    bool bExist = false;
    foreach(PLC_FACTORY factory,pwnd->vPlc)
    {
        if(manuName == pwnd->findFactoryFullName(factory.sFactoryName))
        {
            foreach(PLC_MODEL model,factory.models)
            {
                if(model.sModelName == modelName)
                {
                    cModel = model;
                    bExist = true;
                    break;
                }
            }
            break;
        }
    }
    if(bExist)
    {
        ui->spin_interval->setValue(cModel.nIntervalTime);
        ui->spin_length->setValue(cModel.nMaxRWLen);
        ui->spin_retry->setValue(cModel.nRetryTime);
        ui->spin_stationIndex->setValue(cModel.nPlcNo);
        ui->spin_time->setValue(cModel.nReceiveTimeout);
        ui->spin_cycleTime->setValue(cModel.nCycleTime);
        ui->edit_name->setText(cModel.sModelName);
    }
}

void ProtocolDlg::on_btn_help_clicked()
{
    pwnd->loadHelpHtm(TREE_COM_DEAL);
}
