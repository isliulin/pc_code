#include "quserkeyboardwelcome.h"
#include "ui_quserkeyboardwelcome.h"

QUserkeyboardwelcome::QUserkeyboardwelcome(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::QUserkeyboardwelcome)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
}

QUserkeyboardwelcome::~QUserkeyboardwelcome()
{
    delete ui;
}
