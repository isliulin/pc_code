#include "quserkeyboardselect.h"

QUserkeyboardselect::QUserkeyboardselect(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::QUserkeyboardselect)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
    on_CNumberKeyboard_clicked();
}

QUserkeyboardselect::~QUserkeyboardselect()
{
    delete ui;
}

void QUserkeyboardselect::on_CNumberKeyboard_clicked()
{
    ui->numberpic->setHidden(false);
    ui->asciipic->setHidden(true);
 }

void QUserkeyboardselect::on_CASCIIKeyboard_clicked(bool checked)
{
    ui->numberpic->setHidden(true);
    ui->asciipic->setHidden(false);
}
