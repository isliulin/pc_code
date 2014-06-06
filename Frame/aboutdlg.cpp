#include "aboutdlg.h"
#include "ui_aboutdlg.h"
#include "headfile/global_types.h"

AboutDlg::AboutDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDlg)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    this->setWindowTitle(tr("关于 ") + PRO_FULL_NAME);
    ui->label->setText(PRO_FULL_NAME" V2.0.3");

#ifdef AK_SAMKOON
    //
#else define LA_DEBINUO
    ui->label_2->setText(tr("版权所有"));
#endif
}

AboutDlg::~AboutDlg()
{
    delete ui;
}

void AboutDlg::on_OKBtn_clicked()
{
    this->close();
}
