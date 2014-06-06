#include "qvaluescaledlg.h"
#include "ui_qvaluescaledlg.h"
#include "Frame/addressinputdialog.h"

QValueScaleDlg::QValueScaleDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QValueScaleDlg)
{
    ui->setupUi(this);
}

QValueScaleDlg::~QValueScaleDlg()
{
    delete ui;
}

void QValueScaleDlg::onSetRange(double dMax, double dMin, int type,int base)
{
}

void QValueScaleDlg::on_m_SourcecbBox_currentIndexChanged(int index)
{
    if(0 == index)
    {
        ui->m_SMaxlineEdit->hide();
        ui->m_SMinlineEdit->hide();
        ui->m_sMaxAddress_EntryBtn->hide();
        ui->m_sMinAddress_EntryBtn->hide();
        ui->m_SMaxspBox->show();
        ui->m_SMinspBox->show();
    }
    else
    {
        ui->m_SMaxlineEdit->show();
        ui->m_SMinlineEdit->show();
        ui->m_sMaxAddress_EntryBtn->show();
        ui->m_sMinAddress_EntryBtn->show();
        ui->m_SMaxspBox->hide();
        ui->m_SMinspBox->hide();
    }
}

void QValueScaleDlg::on_m_ShowcbBox_currentIndexChanged(int index)
{
    if(0 == index)
    {
        ui->m_ShowMaxlineEdit->hide();
        ui->m_ShowMinlineEdit->hide();
        ui->m_showMaxAddress_EntryBtn->hide();
        ui->m_showMinAddress_EntryBtn->hide();
        ui->m_ShowMaxspBox->show();
        ui->m_ShowMinspBox->show();
    }
    else
    {
        ui->m_ShowMaxlineEdit->show();
        ui->m_ShowMinlineEdit->show();
        ui->m_showMaxAddress_EntryBtn->show();
        ui->m_showMinAddress_EntryBtn->show();
        ui->m_ShowMaxspBox->hide();
        ui->m_ShowMinspBox->hide();
    }
}

void QValueScaleDlg::on_m_sMaxAddress_EntryBtn_clicked()
{
    QString addrStr = ui->m_SMaxlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(Monitor_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_SMaxlineEdit->setText(Monitor_Address_Keyboard.sShowAddr);
    }
}

void QValueScaleDlg::on_m_sMinAddress_EntryBtn_clicked()
{
    QString addrStr = ui->m_SMinlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(Monitor_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_SMinlineEdit->setText(Monitor_Address_Keyboard.sShowAddr);
    }
}
