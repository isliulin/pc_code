#include "quploaddlg.h"
#include "ui_quploaddlg.h"

QUploadDlg::QUploadDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QUploadDlg)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("上载工程"));
    ui->FilePath->setDisabled(true);
}

QUploadDlg::~QUploadDlg()
{
    delete ui;
}

void QUploadDlg::on_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("选择要存储的位置"),
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
    msg.addButton(tr("确定"),QMessageBox::AcceptRole);

    QString dir=ui->FilePath->text();//取文件位置
    if(dir.isEmpty())//若地址为空
    {
        msg.setText(tr("请选择文件存储位置！"));
        msg.exec();
        return;
    }
    QString filename=ui->FileName->text();//取文件名称
    if(filename.isEmpty())
    {
        msg.setText(tr("请输入文件名称！"));
        msg.exec();
        return;
    }
    QFile file(dir+"/"+filename+AK_FILE_END);
    if(file.exists())
    {//若文件存在的话提示是否替换
        msg.addButton(tr("取消"),QMessageBox::RejectRole);
        msg.setText(tr("文件已存在是否替换？"));
        if(msg.exec()==QDialog::Accepted)//点击确定按钮
        {
           if(!file.remove())//删除之前的文件
            {
                msg.setText(tr("文件无法删除，请检查文件是否被其他程序占用！"));
                msg.exec();
                return;
           }
           else
           {
               uploadfile(file);//上载文件函数
               accept();
           }
        }
        else//点击取消按钮
        {
         //   return;//返回
        }

    }
    else//文件不存在的话直接创建
    {
        uploadfile(file);//上载文件函数
        accept();
    }
}
/************************************************************************
  *Functions:工程上载函数，关于工程上载的操作可以在该函数内执行
  ************************************************************************
  *Value：
  *QFile &file 生成上载文件的形参 引用传递
  ************************************************************************
  *returns:
  *生成上载之后的文件
  ************************************************************************
  *Edit time：2011.7.13
  *Edit by    ：zhy
  *************************************************************************/
void QUploadDlg::uploadfile(QFile &file)
{
    file.open(QIODevice::WriteOnly);
    /***********************************
      *上载的相关操作可以在该部分执行
      **********************************/
    file.close();
}
