#include "qscreendialog.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QScreenDialog::QScreenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QScreenDialog)
{
    ui->setupUi(this);

    btn=new QButtonGroup(this);
    btn->addButton(ui->radioButton,1);
    btn->addButton(ui->radioButton_2,2);
    btn->addButton(ui->radioButton_3,3);

    btn->button(3)->setChecked(true);
    QString stotal="";
    int nTmp=0;
    int totalSceneNum = pwnd->pSceneSheet.size();
    for(int i=0;i<totalSceneNum;i++)
    {
        if(pwnd->newScreen[i]->parent()==pwnd->TreeKeyboard||pwnd->newScreen[i]->parent() == pwnd->copyUserKeyboard)
            continue;
        stotal=pwnd->newScreen[i]->text(0).split(":").at(0);
        nTmp=stotal.toInt();
        ui->comboBox->addItem(QString("%1").arg(nTmp));
   }//
    connect(btn,SIGNAL(buttonClicked(int)),this,SLOT(BtnSelect(int)));
    ui->comboBox->setEnabled(true);
}

void QScreenDialog::BtnSelect(int id)
{
    if(id==1)
    {
        ui->comboBox->setEnabled(false);
    }
   else  if(id==2)
    {
        ui->comboBox->setEnabled(false);
    }
    else if(id==3)
    {
        ui->comboBox->setEnabled(true);
    }
}
QScreenDialog::~QScreenDialog()
{
    delete ui;
}

void QScreenDialog::on_pushButton_clicked()
{
    accept();
}

void QScreenDialog::on_pushButton_2_clicked()
{
    reject();
}
