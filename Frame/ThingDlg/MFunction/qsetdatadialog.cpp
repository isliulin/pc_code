#include "qsetdatadialog.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QSetDataDialog::QSetDataDialog(int iType,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSetDataDialog)
{
    ui->setupUi(this);

    ui->comboBox_datastyle->addItem(tr("16位正整数"));
    ui->comboBox_datastyle->addItem(tr("32位正整数"));
    ui->comboBox_datastyle->addItem(tr("16位整数"));
    ui->comboBox_datastyle->addItem(tr("32位整数"));
    ui->comboBox_datastyle->addItem(tr("16位BCD正整数"));
    ui->comboBox_datastyle->addItem(tr("32位BCD正整数"));
    ui->comboBox_datastyle->addItem(tr("32位浮点数"));
    QRegExp regx1("^[0-9.-]*$");
    QValidator *validator1 = new QRegExpValidator(regx1, ui->lineEdit_2 );
    ui->lineEdit_2->setValidator( validator1 );

    QString str = tr("功能-");
    QString sFunName = "";
    switch(iType)
    {
         case 4:
             sFunName = tr("设置数据");
             break;
         case 5:
             sFunName = tr("用户输入");
             ui->label_3->setVisible(false);
             ui->lineEdit_2->setVisible(false);
             break;
         default:
             sFunName = tr("设置数据");
             break;
    }
     this->setWindowTitle(str+sFunName);
}

QSetDataDialog::~QSetDataDialog()
{
    delete ui;
}

void QSetDataDialog::on_pushButton_2_clicked()
{
    QString ss;
    if(! pwnd->IsAddressCheckRight(setData_address,tr("设置地址"),ui->lineEdit,1))
     {
         return;
     }
    if(ui->comboBox_datastyle->currentIndex()==0||ui->comboBox_datastyle->currentIndex()==1
       ||ui->comboBox_datastyle->currentIndex()==4||ui->comboBox_datastyle->currentIndex()==5)
    {
        ss=ui->lineEdit_2->text();
        if(ss.contains(".")||ss.contains("-"))
        {
            QMessageBox box(this);
            box.setText(tr("请输入正确的数！"));
            QPushButton  *btn=new QPushButton(tr("确定"),this);
            box.addButton(btn,QMessageBox::AcceptRole);
            box.exec();
            return;
        }



    }
    else if(ui->comboBox_datastyle->currentIndex()==2||ui->comboBox_datastyle->currentIndex()==3)
    {
        if(ss.contains("."))
        {
            QMessageBox box(this);
            box.setText(tr("请输入正确的数！"));
            QPushButton  *btn=new QPushButton(tr("确定"),this);
            box.addButton(btn,QMessageBox::AcceptRole);
            box.exec();
            return;
        }
    }
    accept();
}

void QSetDataDialog::on_pushButton_3_clicked()
{
    reject();
}

void QSetDataDialog::on_pushButton_clicked()
{
    pwnd->Addr_Type=1;
    AddressInputDialog addressintputdlg_writeaddress(setData_address,this);
    QString sTmp=ui->lineEdit->text();
    int res=addressintputdlg_writeaddress.exec();
    if(res==QDialog::Accepted)
    {
           ui->lineEdit->setText(setData_address.sShowAddr);

    }
    else
    {
        ui->lineEdit->setText(sTmp);
    }
}
