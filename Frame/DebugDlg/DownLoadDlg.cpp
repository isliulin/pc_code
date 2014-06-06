#include "DownLoadDlg.h"
#include "ui_DownLoadDlg.h"

#include "Frame\mainwindow.h"
#include <QRegExp>
#include "downloadtrd.h"
#include "connecttrd.h"
#include <QNetworkInterface>
//#include <QDateTime>
//#include "DownT.h"


extern MainWindow *pwnd;
DownLoadDlg * model;
DownLoadDlg::DownLoadDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownLoadDlg)
{
    model = this;
    ui->setupUi(this);
    isLocked = false;
    this->setWindowTitle(tr("下载"));

    QSize sz = size();
    setFixedSize(sz);

    ui->m_progress->setMaximum(100);
    ui->m_progress->setMinimum(0);
    ui->m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);//List控件不可以编辑
    ui->m_table->verticalHeader()->setVisible(false);
    ui->m_table->horizontalHeader()->setVisible(false);

    QRegExp rx("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");

    QValidator* inputValueValidator = new QRegExpValidator(rx, this);


    ui->IpEdit->setIp(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp1
                ,pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp2
                ,pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp3
                ,pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp4);
    ui->buttonGroup->setId(ui->radioUSB,0);
    ui->buttonGroup->setId(ui->radioUDP,1);
    ui->buttonGroup->setId(ui->radioUdisk,2);

    connect(ui->buttonGroup,SIGNAL(buttonClicked(int )),this,SLOT(ShowIpEdit(int )));
    ui->radioUSB->setChecked(true);

    ui->IpEdit->setVisible(false);
    ui->Iplabel->setVisible(false);

    ui->m_stopbtn->setVisible(false);

    timer = new QTimer(this);
    timer->start(200);
    connect(timer,SIGNAL(timeout()),this,SLOT(TimeOut()));
    thread = new downloadTrd();
    connect(thread,SIGNAL(information(QString)),this,SLOT(information(QString)));

    cTrd = new ConnectTrd();
    connect(cTrd,SIGNAL(ConnectTo(QString,QString)),this,SLOT(onConnect(QString,QString)));
    //process = new QProcess();
    //connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(showBatMsg()));


    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_eDownload == NetDownload)
    {
        ui->radioUDP->setChecked(true);
        ShowIpEdit(1);
    }
    else
    {
        ui->radioUSB->setChecked(true);
        this->ShowIpEdit(0);
    }
    

}

DownLoadDlg::~DownLoadDlg()
{
    delete ui;

    thread->deleteLater();
    if(timer)
    {
        timer->deleteLater();
    }
    if(cTrd)
    {
        qDebug() << "terminate connectting thread";
        cTrd->terminate();
        delete cTrd;
    }
}

void DownLoadDlg::ShowIpEdit(int id)
{
    switch(id)
    {
    case 0:
        ui->IpEdit->setVisible(false);
        ui->Iplabel->setVisible(false);
        ui->edit_path->setVisible(false);
        ui->btn_destDir->setVisible(false);
        ui->checkBox->setVisible(false);
        on_checkBox_clicked(false);
        break;
    case 1:
        ui->IpEdit->setVisible(true);
        ui->Iplabel->setVisible(true);
        ui->edit_path->setVisible(false);
        ui->btn_destDir->setVisible(false);
        ui->checkBox->setVisible(true);
        if(ui->checkBox->isChecked())
        {
            on_checkBox_clicked(true);
        }
        break;
    case 2:
        ui->IpEdit->setVisible(false);
        ui->Iplabel->setVisible(false);
        ui->edit_path->setVisible(true);
        ui->btn_destDir->setVisible(true);
        ui->checkBox->setVisible(false);
        on_checkBox_clicked(false);

        break;
    }
}
void DownLoadDlg::detectDevices()
{
    //process->start("ADB devices");
    //process->waitForFinished();
    //information("end detectDevices");
}
void DownLoadDlg::on_m_downloadbtn_clicked() //下载按钮
{
    if(!thread->isRunning())
    {
        //BeforeDownload();
        if(ui->radioUDP->isChecked())
        {
            if(ui->checkBox->isChecked())//多机下载
            {
                startMultiHost();
            }
            else
            {
                BeforeDownload();
                thread->setprarm(0,ui->IpEdit->GetIpAddressString(),
                                 false,ui->checkBox_2->isChecked());
                thread->start();
            }

        }
        else if(ui->radioUdisk->isChecked())//下载到U盘
        {
            startUdisk();
        }
        else
        {
            BeforeDownload();
            thread->setprarm(1,QString(""),false,ui->checkBox_2->isChecked());

            thread->start();
        }

        return;
    }

}
void DownLoadDlg::BeforeDownload()
{


    QRect rc = ui->m_table->geometry();
    //DisableUI(true);
    ui->m_table->clear();
    ui->m_table->setRowCount(0);
    ui->m_table->setColumnCount(1);
    ui->m_table->setColumnWidth(0,rc.width());
    ui->m_table->setRowHeight(0,20);
    information(tr("下载组态工程"));
    ui->m_progress->setValue(0);

}


void DownLoadDlg::on_m_stopbtn_clicked()  //停止按钮
{

}

void DownLoadDlg::on_m_closebtn_clicked()  //关闭按钮
{
    QDialog::close();
}

void DownLoadDlg::SetProgress(int size)
{    
    this->ui->m_progress->setValue(size);

}
void DownLoadDlg::DisableUI(bool bValue)
{
	ui->m_downloadbtn->setDisabled(bValue);
	ui->m_closebtn->setDisabled(bValue);

}
void DownLoadDlg::information(QString str,bool status )
{
    int count = ui->m_table->rowCount();
    ui->m_table->insertRow(count);
    ui->m_table->setAutoScroll(true);
    ui->m_table->setRowHeight(count,20);
    ui->m_table->setItem(count,0,new QTableWidgetItem(str));
    ui->m_table->setCurrentCell(count,0);
    if(!status)
    {
        QBrush brush(0xff0000);
        ui->m_table->currentItem()->setBackground(brush);
        ui->m_table->currentItem()->setSelected(false);
    }
}
void DownLoadDlg::closeEvent ( QCloseEvent * cEvent )   
{   
    qDebug() << "remove gEKip" ;
    QFile::remove("gEKip");
    if(thread->isRunning())
    {
        QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("下载中，是否强制结束？"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("是"));
        box.button(QMessageBox::No)->setText(tr("否"));
        if(box.exec())
        {
            if(box.clickedButton()== box.button(QMessageBox::No))
             {
                 cEvent->ignore();
                 return ;
             }
            else
            {
                thread->terminate();

            }
        }

    }
    cTrd->terminate();
} 
void DownLoadDlg::reject()
{
    qDebug() << "remove gEKip" ;
    QFile::remove("gEKip");
    if(thread->isRunning())
    {
        QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("下载中，是否强制结束？"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("是"));
        box.button(QMessageBox::No)->setText(tr("否"));
        if(box.exec() &&
           box.clickedButton()== box.button(QMessageBox::No))
        {
            return;
        }
        thread->terminate();

    }
    cTrd->terminate();
    QDialog::reject();
}
int DownLoadDlg::GetPort()
{
    int nPort = 5555;
   // nPort = this->ui->PortEdit->text().toInt();
    return nPort;
}

void DownLoadDlg::startUdisk()
{
    QString path = ui->edit_path->text();

    if(path.isEmpty())
    {
        return;
    }
    BeforeDownload();
    QDir destDir(path);
    if(!destDir.exists())
    {
        information(tr("路径有误，请输入正确的路径"));
    }
    path.replace("/","\\");
    if(!path.endsWith("\\"))
    {
        path.append("\\");
    }
    path += PC_AKZ_FIRE;
    if(QFile::exists(path))
    {
        QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("文件已存在，是否覆盖"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("是"));
        box.button(QMessageBox::No)->setText(tr("否"));
        if(box.exec() &&
           box.clickedButton()== box.button(QMessageBox::No))
        {
            return;
        }
    }

    thread->setprarm(2,path);
    thread->start();
}

void DownLoadDlg::TimeOut()
{
    if(thread && thread->isTransmitting())
    {
        int value = ui->m_progress->value();
        value+= 2;
        if(value >100)
        {
            value = 0;
        }
        ui->m_progress->setValue(value);
        DisableUI(true);
    }
    else
    {
        DisableUI(false);
        ui->m_progress->setValue(0);
    }

}
void DownLoadDlg::slotError(int code)
{
    switch(code)
    {
    case 0:
        information(tr("更新成功！"));
        break;
    case -1:
        information(tr("触摸屏未连接!"),0);
        break;
    case 1:
        information(tr("触摸屏与当前组态不一致!"),0);
        break;
    case 2:
        information(tr("文件错误!"),0);
        break;
    case 3:
        information(tr("触摸屏初始化失败!"),0);
        break;
    case 4:
        information(tr("数据校验错误!"),0);
        break;
    case 5:
        information(tr("上传失败!"),0);
        break;
    case 6:
        information(tr("不允许上载!"),0);
        break;
    case 7:
        information(tr("密码错误!"),0);
        break;
    case 8:
        information(tr("已取消"));
        break;
    default:
        break;
    }
}
void DownLoadDlg::showBatMsg()
{
    qDebug() << "showBatMsg";
    //QString text = process->readAllStandardOutput();

   // QStringList lst = text.split("\r\n");
   // for(int i=0; i<lst.size();i++)
   // {
//        information(lst.at(i));
//    }
}
//启动扫描线程，搜索网段内的主机
void DownLoadDlg::connecttoHost(QString ip)
{
    cTrd->terminate();
    if(!cTrd->isRunning())
    {
        //qDebug() << "start connect thread";
        cTrd->setIp(ip);
        cTrd->start();
    }

}
void DownLoadDlg::onConnect(QString ip,QString name)
{
    qDebug() << "connect to host: " << ip << "sucessful";
    if(ui->checkBox->isChecked())
    {
        if(mHosts.contains(ip))
        {
            QString oname = mHosts.value(ip);
            mHosts.remove(ip);
            mHosts.insert(ip,name);
            for(int i=0; i<ui->listWidget->count(); i++)
            {
                QString txt = ui->listWidget->item(i)->text();
                txt = txt.section("(",-1);
                txt.remove(")");
                if(txt == ip)
                {
                    ui->listWidget->item(i)->setText(QString("%1(%2)").arg(name).arg(ip));
                }
            }
        }
        else
        {
            mHosts.insert(ip,name);
            QListWidgetItem *listItem = new QListWidgetItem(QString("%1(%2)").arg(name).arg(ip));
            listItem->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
            ui->listWidget->addItem(listItem);
            listItem->setCheckState(Qt::Unchecked);
        }


    }
}
void DownLoadDlg::slotRestart()
{
    bChange = false;

    QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("已完成，点确定重新启动HMI"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.button(QMessageBox::Ok)->setText(tr("确定"));
    box.exec();
    /*
    QMessageBox dlg(this);
    dlg.setWindowTitle(tr("提示"));
    dlg.setWindowFlags(dlg.windowFlags()&~Qt::WindowContextHelpButtonHint);
    dlg.setWindowIcon(QIcon("samkoon.ico"));
    dlg.setText(tr("点击确定重启"));
    QPushButton *connectButton = dlg.addButton(tr("确定"), QMessageBox::AcceptRole);
    dlg.exec();
    */
    bChange = true;
}

/********************************************************************
 * Function: checksum check, add all bytes by unsigned short
 *******************************************************************/
static unsigned long samkoon_checksum(const unsigned short *pBuffer, const int iSize, const bool bComplete)
{
    unsigned long ulCksum = 0;
    int iLen = iSize;

    /*Add every 2bytes as a unsigned short*/
    while (iLen > 1)
    {
        ulCksum += *pBuffer++;
        iLen -= sizeof(unsigned short);
    }

    if (iLen == 1)
    {
        ulCksum += *(unsigned char*)pBuffer;
    }

    if (FALSE == bComplete)
    {
        return ulCksum;
    }

    /*upper 2 bytes + lower 2 bytes*/
    ulCksum = (ulCksum >> 16) + (ulCksum & 0xffff);

    /*add the part overflow 2 bytes*/
    ulCksum += (ulCksum >> 16);

    return (unsigned short)(~ulCksum);
}
//选择存储的路径
void DownLoadDlg::on_btn_destDir_clicked()
{
    QString selectedFilter;
    QString cPath = ui->edit_path->text();
    QDir dir(cPath);
    if(!dir.exists())
    {
        cPath = "/home";
    }
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString path = QFileDialog::getExistingDirectory(this,
                                               tr("选择要存储的位置"),
                                                ui->edit_path->text(),
                                                options);
    if(!path.isEmpty())
    {
        path.replace("/","\\");
        ui->edit_path->setText(path);
    }
}

void DownLoadDlg::startMultiHost()//多机下载
{
    QStringList hostIps;
    for(int i=0; i<ui->listWidget->count(); i++)
    {
        if(ui->listWidget->item(i)->checkState() == Qt::Unchecked)
        {
            continue;
        }
        QString txt = ui->listWidget->item(i)->text();
        txt = txt.section("(",-1);
        txt.remove(")");
        if(!hostIps.contains(txt))
        {
            hostIps << txt;
        }
    }
    qDebug() << "host Ip:"<< hostIps;
    if(hostIps.size() > 0)
    {
        BeforeDownload();
        thread->setHostIps(hostIps,ui->checkBox_2->isChecked());
        thread->start();
    }
}
void DownLoadDlg::on_checkBox_clicked(bool checked)
{
    ui->listWidget->setVisible(checked);
    ui->listWidget->clear();
    mHosts.clear();
    if(checked)
    {
        ui->Iplabel->setDisabled(true);
        ui->IpEdit->setDisabled(true);
        QString str;

          QList<QHostAddress> NetList = QNetworkInterface::allAddresses(); //取得全部信息

          for(int Neti = 0;Neti < NetList.count(); Neti++)
          {
           str = NetList.at(Neti).toString();
           qDebug()<<"local Ip :"<<str;
           if(str != "127.0.0.1")
            break;
          }

        connecttoHost(str);
    }
    else
    {
        ui->Iplabel->setDisabled(false);
        ui->IpEdit->setDisabled(false);
        if(cTrd && cTrd->isRunning())
        {
            cTrd->terminate();
        }
    }
}
