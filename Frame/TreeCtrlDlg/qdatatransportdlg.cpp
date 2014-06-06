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

    this->setWindowTitle(tr("���ϴ����б�"));
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
    sTemp=tr("Դ��ַ:");
    sTemp+=pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].mSourceAddr.sShowAddr;
    sTemp+=tr("-->");
    sTemp+=tr("Ŀ���ַ:");
    sTemp+=pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].mTargetAddr.sShowAddr;
    sTemp+=tr("��");
    sTemp+=tr("���䷽ʽ:");
    if(pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].nAddrType ==0)
    {
        sTemp+=tr("λ");
    }
    else if(pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].nAddrType ==1)
    {
        sTemp+=tr("��");
    }
    else if(pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].nAddrType ==2)
    {
        sTemp+=tr("˫��");
    }
    sTemp+=tr("��");
    if(pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].nTriggerType ==1)
    {
        sTemp+=tr("ʱ�䴥��:Ƶ��");
        sTemp+=QString::number(pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].nTriggerSpace);
        sTemp+=tr("s");
    }
    else if(pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].nTriggerType ==2)
    {
        sTemp+=tr("��ַ����:��ַ");
        sTemp+=pwnd->m_pSamSysParame->m_qvcdataTransProp[iDataIndex].mTriggerAddr.sShowAddr;
    }
    sTemp+=tr("���������ݴ�С=");
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
        QMessageBox box(QMessageBox::Warning,PRO_FULL_NAME,tr("���ݴ������ֻ�ܽ���64����"),
                               0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
               box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
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
        return;//�����ϴ��� ����
    }

    QMessageBox box(QMessageBox::Information,tr("��ʾ"),tr("�Ƿ�ȷ��ɾ���������ϴ��䣿"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
    box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));
    box.exec();
    if(box.clickedButton()== box.button(QMessageBox::Cancel))
    {
        return;
    }
//    for(itemp=row;itemp< dataTranSize;itemp++)
//    {
//        pwnd->m_pSamSysParame->m_qvcdataTransProp[itemp] = pwnd->m_pSamSysParame->m_qvcdataTransProp[itemp +1];
//        //��ʱ������
//        pwnd->qDataTransfer[itemp].iGroupCheckID=pwnd->qDataTransfer[itemp+1].iGroupCheckID;
//        //���
//        pwnd->qDataTransfer[itemp].iTimeInterval=pwnd->qDataTransfer[itemp+1].iTimeInterval;
//        //������ַ�����
//        pwnd->qDataTransfer[itemp].qTriggeerBitText=pwnd->qDataTransfer[itemp+1].qTriggeerBitText;
//        //����Keyboard
//        pwnd->qDataTransfer[itemp].kTriggerBit=pwnd->qDataTransfer[itemp+1].kTriggerBit;
//        //��ַ��������
//        pwnd->qDataTransfer[itemp].iAddressType=pwnd->qDataTransfer[itemp+1].iAddressType;
//        //�֡�λ��
//        pwnd->qDataTransfer[itemp].iNoWordBit=pwnd->qDataTransfer[itemp+1].iNoWordBit;
//        //Դ��ַ
//        pwnd->qDataTransfer[itemp].qSourceAddressText=pwnd->qDataTransfer[itemp+1].qSourceAddressText;
//        //Դ��ַKeyboard
//        pwnd->qDataTransfer[itemp].kSourceAddress=pwnd->qDataTransfer[itemp+1].kSourceAddress;
//        //Դ��ַ
//        pwnd->qDataTransfer[itemp].qDestinationText=pwnd->qDataTransfer[itemp+1].qDestinationText;
//        //Դ��ַKeyboard
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
