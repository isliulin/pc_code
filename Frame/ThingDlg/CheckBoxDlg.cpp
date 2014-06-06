#include "CheckBoxDlg.h"
#include "view/CheckBoxItem.h"
#include "ui_CheckBoxDlg.h"

CheckBoxDlg::CheckBoxDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckBoxDlg)
{
    ui->setupUi(this);
}

void CheckBoxDlg::initUiDlg()
{
    this->setWindowTitle(tr("¸´Ñ¡¿ò"));

    connect(ui->btnAccept, SIGNAL(clicked()),this, SLOT(onTabWightSwitch(int));
    connect(ui->btnCancel, SIGNAL(clicked()),this, SLOT(onTabWightSwitch(int));
    connect(ui->btnHelp, SIGNAL(clicked()),this, SLOT(onTabWightSwitch(int));
}

CheckBoxDlg::~CheckBoxDlg()
{
    delete ui;
}
