#include "qnewlinkwizard.h"
#include "Frame\mainwindow.h"
extern MainWindow *pwnd;

QNewLinkWizard::QNewLinkWizard(QWidget *parent):QWizardPage(parent),ui(new Ui::QNewLinkWizard)
{
    ui->setupUi(this);
    /***********初始化控件**************/
    ui->newlinkwizard_linkname_lineedit->setText(tr("连接1"));
    for(int i=1;i<=256;i++)
    {
        ui->newlinkwizard_plcaddress_combobox->addItem(QString().setNum(i));
    }
    ui->newlinkwizard_plcaddress_combobox->setCurrentIndex(ui->newlinkwizard_plcaddress_combobox->findText("32"));

    ui->label_5->hide();
    ui->newlinkwizard_device_combobox->hide();
    ui->newlinkwizard_server_combobox->hide();
    ui->label_7->hide();
    ui->newlinkwizard_plcaddress_combobox->hide();

    /***********************读文件*************************/
    /*QFile  file("device.bin");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox box(this);
        box.setText(tr("文件被损坏，请重新安装软件！"));
        box.exec();
        return;
    }
    else
    {
        QTextStream in(&file);
        QString line = in.readLine();//读取一行数据
        QString qtemp_index;
        QString qtemp_hmimodel;
        QString temp;//辅助函数，辅助处理从文件读出的一行数据
        int times=0;
        int i=0;
        while(1)
        {
            for(int j=i;line[j]!=',';j++,i++)
            {
                temp=temp+line[j];
            }
            if(times==0)//去分隔符‘,’的次数，第一次是取的PLC的索引
            {
                qtemp_index=temp;
                times++;
                temp.clear();
                i+=1;
                continue;
            }
            if(times==1)
            {
                times++;
                temp.clear();
                i+=1;
                continue;
            }
            if(times==2)
            {
                ui->newlinkwizard_device_combobox->addItem(temp);
                qtemp_hmimodel=temp;
                break;
            }
        }
        while (!in.atEnd())
        {

            if(line=="end")
            {
                break;
            }
            i=0;
            times=0;
            while(1)
            {
                for(int j=i;line[j]!=',';j++,i++)
                {
                    temp=temp+line[j];
                }
                if(times==0)//去分隔符‘,’的次数，第一次是取的PLC的索引
                {
                    qtemp_index=temp;
                    times++;
                    temp.clear();
                    i+=1;
                    continue;
                }
                if(times==1)
                {
                    times++;
                    temp.clear();
                    i+=1;
                    continue;
                }
                if(times==2)
                {
                    if(qtemp_hmimodel==temp)
                    {
                        break;
                    }
                    ui->newlinkwizard_device_combobox->addItem(temp);
                    qtemp_hmimodel=temp;
                    break;
                }
            }
            line = in.readLine();
            //  ui->newlinkwizard_device_combobox->addItem(line);
        }
    }
    file.close();*/
    //ui->newlinkwizard_device_combobox->setCurrentIndex(ui->newlinkwizard_device_combobox->findText("Modbus"));

    //add by czq
    ui->newlinkwizard_linkport_combobox_2->clear();
    QStringList manus;
    foreach(PLC_FACTORY factory,pwnd->vPlc)
    {
        bool bShow = false;
        foreach(PLC_MODEL model,factory.models)
        {
            if(PRO_SERIAL == getProtocolType())
            {
                if(model.ePorttype == PORT_SERIAL || model.ePorttype == PORT_SERIAL_ETHNET)
                {
                    bShow = true;
                    break;
                }
            }
            else if(PRO_ETHNET == getProtocolType())
            {
                if(model.ePorttype == PORT_ETHNET || model.ePorttype == PORT_SERIAL_ETHNET)
                {
                    bShow = true;
                    break;
                }
            }
//            else if(2 == getProtocolType())
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
    //connect(ui->combo_manu,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_combo_manu_Changed(QString)));
    //connect(ui->combo_protocol,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_combo_model_Changed(QString)));
    ui->newlinkwizard_linkport_combobox_2->addItems(manus);

    ui->label->hide();
    ui->newlinkwizard_linknum_label->hide();
    ui->label_3->hide();
    ui->newlinkwizard_linkname_lineedit->hide();
}

QNewLinkWizard::~QNewLinkWizard()
{
    delete ui;
}

/**************************连接页面的设备combobox的槽函数来改变服务combobox的值****************************************/
void QNewLinkWizard::on_newlinkwizard_device_combobox_currentIndexChanged(int index)
{
    /*QFile  file("device.bin");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;

    }
    else
    {
        ui->newlinkwizard_server_combobox->clear();
        QString qtemp_index=QString::number(index);

        QTextStream in(&file);
        QString line = in.readLine();//读取一行数据

        QString temp;//辅助函数，辅助处理从文件读出的一行数据
        int times=0;
        int i=0;
        while (!in.atEnd())
        {
            if(line=="end")
            {
                break;
            }

            while(1)
            {
                for(int j=i;line[j]!=',';j++,i++)
                {
                    temp=temp+line[j];
                }
                if(times==0)//去分隔符‘,’的次数，第一次是取的PLC的索引
                {
                    if(qtemp_index!=temp)
                    {
                        temp.clear();
                        i=0;
                        times=0;
                        break;
                    }
                    times++;
                    temp.clear();
                    i+=1;
                    continue;
                }
                else if(times==1||times==2)
                {
                    times++;
                    temp.clear();
                    i+=1;
                    continue;
                }
                else if(times==3)
                {
                    ui->newlinkwizard_server_combobox->addItem(temp);
                    temp.clear();
                    i=0;
                    times=0;
                    break;
                }
            }
            line = in.readLine();
        }
    }*/
}

/******当选择不同的PLC时根据从文件中读出的PLC信息来初始化com1和com2结构体的数据*********/
void QNewLinkWizard::on_newlinkwizard_server_combobox_currentIndexChanged(QString index)
{
    /*QString device=ui->newlinkwizard_device_combobox->currentText();
    QFile  file("device.bin");//定义文件指针
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))//打开文件
    {
        return;
    }
    else
    {
        QTextStream in(&file);
        QString line = in.readLine();//读取一行数据
        while (!in.atEnd())
        {
            if(line=="end")
            {
                break;
            }
            QStringList list=line.split(",");
            if(list.size()<10)
            {
                QMessageBox box(QMessageBox::Warning,PRO_FULL_NAME,tr("device.bin已损坏，请重新安装应用软件！"),
                                0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
                box.addButton(tr("确定"),QMessageBox::AcceptRole);
                box.exec();
                break;
            }
            if(device!=list.at(2))//PLC的厂家不对的话
            {
                line = in.readLine();//取下一行数据
                continue;//重新循环
            }
            if(index!=list.at(3))//PLC的型号不对
            {
                line = in.readLine();//取下一行数据
                continue;//重新循环
            }
            if(1)//比特率
            {
                QString temp=list.at(4);
                int itmpindex=0;
                if(temp=="1200")
                {
                    itmpindex=0;
                }
                else if(temp=="2400")
                {
                    itmpindex=1;
                }
                else if(temp=="4800")
                {
                    itmpindex=2;
                }
                else if(temp=="9600")
                {
                    itmpindex=3;
                }
                else if(temp=="19200")
                {
                    itmpindex=4;
                }
                else if(temp=="38400")
                {
                    itmpindex=5;
                }
                else if(temp=="57600")
                {
                    itmpindex=6;
                }
                else if(temp=="115200")
                {
                    itmpindex=7;
                }
                else if(temp=="187500")
                {
                    itmpindex=8;
                }
                pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nBandRade=itmpindex;
            }
            if(1)//数据位
            {
                QString temp=list.at(5);
                int itmpindex=0;
                if(temp=="7")
                {
                    itmpindex=0;
                }
                else if(temp=="8")
                {
                    itmpindex=1;
                }
                pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nDataBits=itmpindex;

            }
            if(1)//校验码
            {
                QString temp=list.at(6);
                int itmpindex=0;
                if(temp=="N")
                {
                    itmpindex=0;
                }
                else if(temp=="E")
                {
                    itmpindex=1;
                }
                else if(temp=="O")
                {
                    itmpindex=2;
                }
                pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nCheckType=itmpindex;
            }
            if(1)//停止位
            {
            QString temp=list.at(7);
            int itmpindex=0;
            if(temp=="1")
            {
                itmpindex=0;
            }
            else if(temp=="2")
            {
                itmpindex=1;
            }
            pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nStopBit=itmpindex;

        }
            pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nTouchScreenAddr=list.at(8).toInt();
            pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nPlcAddr=list.at(9).toInt();
            ui->newlinkwizard_plcaddress_combobox->setCurrentIndex(list.last().toInt()-1);
            break;
        }
    }
    file.close();*/
}

void QNewLinkWizard::on_newlinkwizard_linkport_combobox_2_currentIndexChanged(QString str)
{
    QStringList modelNames;
    foreach(PLC_FACTORY factory,pwnd->vPlc)
    {
        if(str == pwnd->findFactoryFullName(factory.sFactoryName))
        {
            ui->newlinkwizard_linkport_combobox_3->clear();
            foreach(PLC_MODEL model,factory.models)
            {
                if(PRO_SERIAL == getProtocolType())
                {
                    if(model.ePorttype == PORT_SERIAL || model.ePorttype == PORT_SERIAL_ETHNET)
                    {
                        modelNames << model.sModelName;
                    }
                }
                else if(PRO_ETHNET == getProtocolType())
                {
                    if(model.ePorttype == PORT_ETHNET || model.ePorttype == PORT_SERIAL_ETHNET)
                    {
                        modelNames << model.sModelName;
                    }
                }
//                else if(2 == getProtocolType())
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

    ui->newlinkwizard_linkport_combobox_3->addItems(modelNames);
    if(ui->newlinkwizard_linkport_combobox_3->count()>0)
    {
        ui->newlinkwizard_linkport_combobox_3->setCurrentIndex(0);
    }

    ui->newlinkwizard_linkport_lineEdit->setText(ui->newlinkwizard_linkport_combobox_3->currentText());
}

void QNewLinkWizard::on_newlinkwizard_linkport_combobox_3_currentIndexChanged(QString str)
{
    ui->newlinkwizard_linkport_lineEdit->setText(ui->newlinkwizard_linkport_combobox_3->currentText());
    ui->newlinkwizard_linkport_lineEdit->setText(str);
}

int QNewLinkWizard::getProtocolType()
{
    QString strTemp = ui->newlinkwizard_linkport_combobox->currentText();
    if(strTemp == tr("以太网") || strTemp == tr("网络"))
    {
        return PRO_ETHNET;
    }
    else if(strTemp == tr("CAN总线"))
    {
        return PRO_CAN;
    }
    else if(strTemp.contains("COM"))
    {
        return PRO_SERIAL;
    }
    else
    {
        return PRO_SERIAL;
    }
}

void QNewLinkWizard::on_newlinkwizard_linkport_combobox_currentIndexChanged(QString str)
{
    ui->newlinkwizard_linkport_combobox_2->clear();
    QStringList manus;
    foreach(PLC_FACTORY factory,pwnd->vPlc)
    {
        bool bShow = false;
        foreach(PLC_MODEL model,factory.models)
        {
            if(PRO_SERIAL == getProtocolType())
            {
                if(model.ePorttype == PORT_SERIAL || model.ePorttype == PORT_SERIAL_ETHNET)
                {
                    bShow = true;
                    break;
                }
            }
            else if(PRO_ETHNET == getProtocolType())
            {
                if(model.ePorttype == PORT_ETHNET || model.ePorttype == PORT_SERIAL_ETHNET)
                {
                    bShow = true;
                    break;
                }
            }
//            else if(2 == getProtocolType())
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
    ui->newlinkwizard_linkport_combobox_2->addItems(manus);
    if(ui->newlinkwizard_linkport_combobox_2->count()>0)
    {
        ui->newlinkwizard_linkport_combobox_2->setCurrentIndex(0);
    }
}
