#include "quploaddlg.h"
#include "ui_quploaddlg.h"

QUploadDlg::QUploadDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QUploadDlg)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("���ع���"));
    ui->FilePath->setDisabled(true);
}

QUploadDlg::~QUploadDlg()
{
    delete ui;
}

void QUploadDlg::on_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("ѡ��Ҫ�洢��λ��"),
                                                     "/home",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    ui->FilePath->setText(dir);
}

void QUploadDlg::on_UploadCancel_clicked()
{
    reject();
}

void QUploadDlg::on_UploadStart_clicked()
{
    QMessageBox msg(QMessageBox::Warning, PRO_FULL_NAME, tr(""),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);

    QString dir=ui->FilePath->text();//ȡ�ļ�λ��
    if(dir.isEmpty())//����ַΪ��
    {
        msg.setText(tr("��ѡ���ļ��洢λ�ã�"));
        msg.exec();
        return;
    }
    QString filename=ui->FileName->text();//ȡ�ļ�����
    if(filename.isEmpty())
    {
        msg.setText(tr("�������ļ����ƣ�"));
        msg.exec();
        return;
    }
    QFile file(dir+"/"+filename+AK_FILE_END);
    if(file.exists())
    {//���ļ����ڵĻ���ʾ�Ƿ��滻
        msg.addButton(tr("ȡ��"),QMessageBox::RejectRole);
        msg.setText(tr("�ļ��Ѵ����Ƿ��滻��"));
        if(msg.exec()==QDialog::Accepted)//���ȷ����ť
        {
           if(!file.remove())//ɾ��֮ǰ���ļ�
            {
                msg.setText(tr("�ļ��޷�ɾ���������ļ��Ƿ���������ռ�ã�"));
                msg.exec();
                return;
           }
           else
           {
               uploadfile(file);//�����ļ�����
               accept();
           }
        }
        else//���ȡ����ť
        {
         //   return;//����
        }

    }
    else//�ļ������ڵĻ�ֱ�Ӵ���
    {
        uploadfile(file);//�����ļ�����
        accept();
    }
}
/************************************************************************
  *Functions:�������غ��������ڹ������صĲ��������ڸú�����ִ��
  ************************************************************************
  *Value��
  *QFile &file ���������ļ����β� ���ô���
  ************************************************************************
  *returns:
  *��������֮����ļ�
  ************************************************************************
  *Edit time��2011.7.13
  *Edit by    ��zhy
  *************************************************************************/
void QUploadDlg::uploadfile(QFile &file)
{
    file.open(QIODevice::WriteOnly);
    /***********************************
      *���ص���ز��������ڸò���ִ��
      **********************************/
    file.close();
}
