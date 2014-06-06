#include "newprinter.h"
#include "ui_newprinter.h"
#include "Frame/mainwindow.h"

extern MainWindow * pwnd;

NewPrinter::NewPrinter(QWidget *parent):QDialog(parent),ui(new Ui::NewPrinter)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
    ui->comboBox->addItem(tr("WH-E19(ì¿»Í)"));
    ui->comboBox->addItem(tr("WH-A5(ì¿»Í)"));
    ui->comboBox->setCurrentIndex((short)pwnd->m_pSamSysParame->m_mixGlobalVar.m_ePrinter-1);
    setWindowTitle(tr("´òÓ¡»ú"));
}

NewPrinter::~NewPrinter()
{
    delete ui;
}

void NewPrinter::on_pushButton_sure_clicked()
{
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_ePrinter = (PrinterType)(ui->comboBox->currentIndex()+1);
    this->accept();
}

void NewPrinter::on_pushButton_cancel_clicked()
{
    this->close();
}
