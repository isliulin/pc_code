#include "FindAddrDlg.h"
#include "ui_FindAddrDlg.h"

FindAddrDlg::FindAddrDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindAddrDlg)
{
    ui->setupUi(this);

    setFixedSize(size());
    this->setWindowTitle(tr("查找"));
    iSelctType = 0;

    ui->radioButton_1->setChecked(true);

    Type_Group = new QButtonGroup(this);
    Type_Group->addButton(ui->radioButton_1,0);
    Type_Group->addButton(ui->radioButton_2,1);
    Type_Group->addButton(ui->radioButton_3,2);
    connect(Type_Group,SIGNAL(buttonClicked(int)),this,SLOT(selectType(int)));
    selectType(0);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

   // ui->m_nocasecheck->setChecked(true);
    ui->m_addrinputedit->setFocus();
}

FindAddrDlg::~FindAddrDlg()
{
    if(Type_Group)
    {
        delete Type_Group;
        Type_Group = NULL;
    }

    delete ui;
}

void FindAddrDlg::selectType(int iCheckId)
{
    if(iCheckId == 0 || iCheckId == 1)
    {
        ui->replacelabel->setVisible(false);
        ui->replaceEdit->setVisible(false);
        ui->m_ok->setText(tr("查找"));
        ui->m_nocasecheck->setVisible(true);
        ui->checkBox_same->setVisible(true);
    }
    else if(iCheckId == 2)
    {
        ui->replacelabel->setVisible(true);
        ui->replaceEdit->setVisible(true);
        ui->m_ok->setText(tr("替换"));

        ui->m_nocasecheck->setVisible(false);
        ui->checkBox_same->setVisible(false);
    }
}

void FindAddrDlg::on_m_ok_clicked()
{
    sAddress = ui->m_addrinputedit->text();//获得要查找的地址的内容
    bIfCase  = ui->m_nocasecheck->isChecked();
    bIfSame  = ui->checkBox_same->isChecked();
    iSelctType = Type_Group->checkedId(); //查找类型
    sReplaceMsg = ui->replaceEdit->text();
    QDialog::accept();
}

void FindAddrDlg::on_m_cancel_clicked()
{
    QDialog::close();
}
