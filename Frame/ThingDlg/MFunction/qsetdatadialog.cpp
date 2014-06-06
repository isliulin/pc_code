#include "qsetdatadialog.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QSetDataDialog::QSetDataDialog(int iType,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSetDataDialog)
{
    ui->setupUi(this);

    ui->comboBox_datastyle->addItem(tr("16λ������"));
    ui->comboBox_datastyle->addItem(tr("32λ������"));
    ui->comboBox_datastyle->addItem(tr("16λ����"));
    ui->comboBox_datastyle->addItem(tr("32λ����"));
    ui->comboBox_datastyle->addItem(tr("16λBCD������"));
    ui->comboBox_datastyle->addItem(tr("32λBCD������"));
    ui->comboBox_datastyle->addItem(tr("32λ������"));
    QRegExp regx1("^[0-9.-]*$");
    QValidator *validator1 = new QRegExpValidator(regx1, ui->lineEdit_2 );
    ui->lineEdit_2->setValidator( validator1 );

    QString str = tr("����-");
    QString sFunName = "";
    switch(iType)
    {
         case 4:
             sFunName = tr("��������");
             break;
         case 5:
             sFunName = tr("�û�����");
             ui->label_3->setVisible(false);
             ui->lineEdit_2->setVisible(false);
             break;
         default:
             sFunName = tr("��������");
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
    if(! pwnd->IsAddressCheckRight(setData_address,tr("���õ�ַ"),ui->lineEdit,1))
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
            box.setText(tr("��������ȷ������"));
            QPushButton  *btn=new QPushButton(tr("ȷ��"),this);
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
            box.setText(tr("��������ȷ������"));
            QPushButton  *btn=new QPushButton(tr("ȷ��"),this);
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
