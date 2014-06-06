#include "qdatatransportdlg.h"
#include "ui_qdatatransportdlg.h"
#include "qnewdatatransfer.h"
#include "Frame\mainwindow.h"
#include <QListWidgetItem>
extern MainWindow *pwnd;


QDataTransportDlg::QDataTransportDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDataTransportDlg)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    this->setWindowTitle(tr("资料传输列表"));
    int dataTranSize = pwnd->m_pSamSysParame->m_qvcdataTransProp.size();
    for(int i=0;i< dataTranSize;i++)
    {
        if(pwnd->m_pSamSysParame->m_qvcdataTransProp[i].mSourceAddr.sShowAddr !="")
        {
            QString sTemp=CheckToStr(i);
            QListWidgetItem *listWidget;

            listWidget=new QListWidgetItem(sTemp);
            ui->listWidget->addItem(listWidget);

        }
    }
}

QDataTransportDlg::~QDataTransportDlg()
{

     delete ui;
}
QString QDataTransportDlg::CheckToStr(int iDataIndex)
{
    if(iDataIndex < 0 || iDataIndex >= pwnd->m_pSamSysParame->m_qvcdataTransProp.size()) return QString();
    QString sTemp;
    sTemp=tr("源地址:");
    sTemp+=pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].mSourceAddr.sShowAddr;
    sTemp+=tr("-->");
    sTemp+=tr("目标地址:");
    sTemp+=pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].mTargetAddr.sShowAddr;
    sTemp+=tr("，");
    sTemp+=tr("传输方式:");
    if(pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].nAddrType ==0)
    {
        sTemp+=tr("位");
    }
    else if(pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].nAddrType ==1)
    {
        sTemp+=tr("字");
    }
    else if(pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].nAddrType ==2)
    {
        sTemp+=tr("双字");
    }
    sTemp+=tr("，");
    if(pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].nTriggerType ==1)
    {
        sTemp+=tr("时间触发:频率");
        sTemp+=QString::number(pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].nTriggerSpace);
        sTemp+=tr("s");
    }
    else if(pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].nTriggerType ==2)
    {
        sTemp+=tr("地址触发:地址");
        sTemp+=pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].mTriggerAddr.sShowAddr;
    }
    sTemp+=tr("，传输数据大小=");
    sTemp+=QString::number(pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].nWordBitPos);
    return sTemp;
}

void QDataTransportDlg::on_New_clicked()
{
    int dataTranSize = pwnd->m_pSamSysParame->m_qvcdataTransProp.size();
    if(dataTranSize < 64)
    {
        QNewDataTransfer *NewDataTransfer;
        NewDataTransfer=new QNewDataTransfer(this);
        if(NewDataTransfer->exec()==QDialog::Accepted)
        {
         //   pwnd->iDataTransferCount++;
            dataTranSize = pwnd->m_pSamSysParame->m_qvcdataTransProp.size();
            QString sTemp;
            sTemp=CheckToStr(dataTranSize-1);
            QListWidgetItem *listWidget;
            listWidget=new QListWidgetItem(sTemp);
            ui->listWidget->addItem(listWidget);
        }
        delete NewDataTransfer;
        NewDataTransfer=NULL;
    }
    else
    {
        QMessageBox box(QMessageBox::Warning,PRO_FULL_NAME,tr("数据传输最多只能建立64条！"),
                               0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
               box.addButton(tr("确定"),QMessageBox::AcceptRole);
               box.exec();
    }
}

void QDataTransportDlg::on_Delete_clicked()
{
    int itemp;
    int row=ui->listWidget->currentRow();
    int dataTranSize = pwnd->m_pSamSysParame->m_qvcdataTransProp.size();
    if(row == -1 || row >= dataTranSize)
    {
        return;//无资料传输 返回
    }

    QMessageBox box(QMessageBox::Information,tr("提示"),tr("是否确定删除此项资料传输？"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.button(QMessageBox::Ok)->setText(tr("确定"));
    box.button(QMessageBox::Cancel)->setText(tr("取消"));
    box.exec();
    if(box.clickedButton()== box.button(QMessageBox::Cancel))
    {
        return;
    }
//    for(itemp=row;itemp< dataTranSize;itemp++)
//    {
//        pwnd->m_pSamSysParame->m_qvcdataTransProp[itemp] = pwnd->m_pSamSysParame->m_qvcdataTransProp[itemp +1];
//        //计时、触发
//        pwnd->qDataTransfer[itemp].iGroupCheckID=pwnd->qDataTransfer[itemp+1].iGroupCheckID;
//        //间隔
//        pwnd->qDataTransfer[itemp].iTimeInterval=pwnd->qDataTransfer[itemp+1].iTimeInterval;
//        //触发地址输入框
//        pwnd->qDataTransfer[itemp].qTriggeerBitText=pwnd->qDataTransfer[itemp+1].qTriggeerBitText;
//        //触发Keyboard
//        pwnd->qDataTransfer[itemp].kTriggerBit=pwnd->qDataTransfer[itemp+1].kTriggerBit;
//        //地址类型索引
//        pwnd->qDataTransfer[itemp].iAddressType=pwnd->qDataTransfer[itemp+1].iAddressType;
//        //字、位数
//        pwnd->qDataTransfer[itemp].iNoWordBit=pwnd->qDataTransfer[itemp+1].iNoWordBit;
//        //源地址
//        pwnd->qDataTransfer[itemp].qSourceAddressText=pwnd->qDataTransfer[itemp+1].qSourceAddressText;
//        //源地址Keyboard
//        pwnd->qDataTransfer[itemp].kSourceAddress=pwnd->qDataTransfer[itemp+1].kSourceAddress;
//        //源地址
//        pwnd->qDataTransfer[itemp].qDestinationText=pwnd->qDataTransfer[itemp+1].qDestinationText;
//        //源地址Keyboard
//        pwnd->qDataTransfer[itemp].kDestinationAddress=pwnd->qDataTransfer[itemp+1].kDestinationAddress;
//    }
    ui->listWidget->clear();
    pwnd->m_pSamSysParame->m_qvcdataTransProp.remove(row);
//    pwnd->iDataTransferCount--;

    dataTranSize = pwnd->m_pSamSysParame->m_qvcdataTransProp.size();
    for(itemp=0;itemp< dataTranSize;itemp++)
    {
        QString sTemp;
        sTemp=CheckToStr(itemp);
        QListWidgetItem *listWidget;
        listWidget=new QListWidgetItem(sTemp);
        ui->listWidget->addItem(listWidget);
     }
    ui->listWidget->setCurrentRow(row);
}

void QDataTransportDlg::on_Alter_clicked()
{
    int row=ui->listWidget->currentRow();
    if(row==-1)
    {
        return;
    }
    int itemp;
    QNewDataTransfer *NewDataTransfer;
    NewDataTransfer=new QNewDataTransfer(row,this);
    if(NewDataTransfer->exec()==QDialog::Accepted)
    {
        ui->listWidget->clear();
        int dataTranSize = pwnd->m_pSamSysParame->m_qvcdataTransProp.size();
        for(itemp=0;itemp< dataTranSize;itemp++)
        {
            QString sTemp;
            sTemp=CheckToStr(itemp);
            QListWidgetItem *listWidget;
            listWidget=new QListWidgetItem(sTemp);
            ui->listWidget->addItem(listWidget);

        }
        delete NewDataTransfer;
        NewDataTransfer=NULL;
      }
    return;
}

void QDataTransportDlg::on_listWidget_doubleClicked(QModelIndex index)
{
    on_Alter_clicked();
}

void QDataTransportDlg::on_Close_clicked()
{
    this->close();
}

void QDataTransportDlg::on_HelpButton_clicked()
{
    pwnd->loadHelpHtm(TREE_DATA_TRANSFORM);
}
