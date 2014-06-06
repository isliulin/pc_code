#include "expressiondlg.h"
#include "ui_expressiondlg.h"
#include "view/DataDisplayItem.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

ExpressionDlg::ExpressionDlg(int datatype,Expression exp,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpressionDlg)
{
    ui->setupUi(this);
    m_Exp = exp;



    tempAddr1 = "LW0";
    tempAddr2 = "LW0";
    tempAddr3 = "LW0";

    tempConst1 = "0";
    tempConst2 = "0";
    tempConst3 = "0";

    ui->lineEdit->setText(m_Exp.var1.sShowAddr);
    ui->comboBox->setCurrentIndex(int(m_Exp.op1));
    on_comboBox_changed(int(m_Exp.op1));
    if(m_Exp.op1 == OPR_NONE)
    {
        ui->combo_Type->setDisabled(true);
        ui->lineEdit_2->setDisabled(true);

    }
    else
    {
        ui->combo_Type->setCurrentIndex(int(m_Exp.bConstant1));
        if(m_Exp.bConstant1)
        {
            ui->lineEdit_2->setText(QString::number(m_Exp.constant1));
        }
        else
            ui->lineEdit_2->setText(m_Exp.var2.sShowAddr);
    }

    ui->comboBox_2->setCurrentIndex(int(m_Exp.op2));
    on_comboBox_2_changed(int(m_Exp.op2));
    if(m_Exp.op2 == OPR_NONE)
    {
        ui->combo_Type_2->setDisabled(true);
        ui->lineEdit_3->setDisabled(true);

    }
    else
    {
        ui->combo_Type_2->setCurrentIndex(int(m_Exp.bConstant2));
        if(m_Exp.bConstant2)
        {
            ui->lineEdit_3->setText(QString::number(m_Exp.constant2));
        }
        else
            ui->lineEdit_3->setText(m_Exp.var3.sShowAddr);
    }

    ui->comboBox_3->setCurrentIndex(int(m_Exp.op3));
    on_comboBox_3_changed(int(m_Exp.op3));

    if(m_Exp.op3 == OPR_NONE)
    {
        ui->combo_Type_3->setDisabled(true);
        ui->lineEdit_4->setDisabled(true);

    }
    else
    {
        ui->combo_Type_3->setCurrentIndex(int(m_Exp.bConstant3));
        if(m_Exp.bConstant3)
        {
            ui->lineEdit_4->setText(QString::number(m_Exp.constant3));
        }
        else
            ui->lineEdit_4->setText(m_Exp.var4.sShowAddr);
    }

    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comboBox_changed(int)));
    connect(ui->comboBox_2,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comboBox_2_changed(int)));
    connect(ui->comboBox_3,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comboBox_3_changed(int)));

}

ExpressionDlg::~ExpressionDlg()
{
    delete ui;
}

void ExpressionDlg::on_btn_ok_clicked()
{
    Expression tExp;
    if(! pwnd->IsAddressCheckRight(tExp.var1,tr("地址1"),ui->lineEdit,1))
    {
        ui->lineEdit->setFocus();
        return ;
    }
    tExp.op1 = (E_OPERATION)ui->comboBox->currentIndex();
    if(tExp.op1 != OPR_NONE)//操作1被使用
    {
        tExp.bConstant1 = (bool)ui->combo_Type->currentIndex();
        if(!tExp.bConstant1)
        {
            if(! pwnd->IsAddressCheckRight(tExp.var2,tr("地址2"),ui->lineEdit_2,1))
            {
                ui->lineEdit_2->setFocus();
                return ;
            }
        }
        else
        {
            QString sTemp = ui->lineEdit_2->text();
            if(isDouble(sTemp))
            {                
                tExp.constant1 = sTemp.toDouble();
            }
            else
            {
                QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr("常数输入有误"),
                                0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
                msg.addButton(tr("确定"),QMessageBox::AcceptRole);
                msg.exec();
                ui->lineEdit_2->setFocus();
                return;//数据格式有误
            }
        }
    }

    //操作2
    tExp.op2 = (E_OPERATION)ui->comboBox_2->currentIndex();
    if(tExp.op2 != OPR_NONE)//操作1被使用
    {
        tExp.bConstant2 = (bool)ui->combo_Type_2->currentIndex();
        if(!tExp.bConstant2)
        {
            if(! pwnd->IsAddressCheckRight(tExp.var3,tr("地址3"),ui->lineEdit_3,1))
            {
                ui->lineEdit_3->setFocus();
                return ;
            }
        }
        else
        {
            QString sTemp = ui->lineEdit_3->text();
            if(isDouble(sTemp))
            {
                tExp.constant2 = sTemp.toDouble();
            }
            else
            {
                QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr("常数输入有误"),
                                0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
                msg.addButton(tr("确定"),QMessageBox::AcceptRole);
                msg.exec();
                ui->lineEdit_3->setFocus();
                return;//数据格式有误
            }
        }
    }
    //操作3
    tExp.op3 = (E_OPERATION)ui->comboBox_3->currentIndex();
    if(tExp.op3 != OPR_NONE)//操作1被使用
    {
        tExp.bConstant3 = (bool)ui->combo_Type_3->currentIndex();

        if(!tExp.bConstant3)
        {
            if(! pwnd->IsAddressCheckRight(tExp.var4,tr("地址4"),ui->lineEdit_4,1))
            {
                ui->lineEdit_4->setFocus();
                return ;
            }
        }
        else
        {
            QString sTemp = ui->lineEdit_4->text();
            if(isDouble(sTemp))
            {
                tExp.constant3 = sTemp.toDouble();
            }
            else
            {
                QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr("常数输入有误"),
                                0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
                msg.addButton(tr("确定"),QMessageBox::AcceptRole);
                msg.exec();
                ui->lineEdit_4->setFocus();
                return;//数据格式有误
            }
        }
    }


    m_Exp = tExp;

    //qDebug() <<m_Exp.bConstant1 <<m_Exp.bConstant2 << m_Exp.bConstant3;
    //qDebug() <<m_Exp.constant1 <<m_Exp.constant2 << m_Exp.constant3;
    //qDebug() <<m_Exp.var2.sShowAddr <<m_Exp.var3.sShowAddr << m_Exp.var4.sShowAddr;

    accept();
}

void ExpressionDlg::on_btn_cancel_clicked()
{
    reject();
}
Expression ExpressionDlg::getExp()
{
    return m_Exp;
}

void ExpressionDlg::on_btn_addr_clicked()
{
    QString addrStr = ui->lineEdit->text();
    Keyboard wordAddr;
    AddressInputDialog addressintputdlg_writeaddress(wordAddr,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->lineEdit->setText(wordAddr.sShowAddr);
    }
}

void ExpressionDlg::on_btn_addr2_clicked()
{
    QString addrStr = ui->lineEdit_2->text();
    Keyboard wordAddr;
    AddressInputDialog addressintputdlg_writeaddress(wordAddr,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->lineEdit_2->setText(wordAddr.sShowAddr);
    }
}

void ExpressionDlg::on_btn_addr3_clicked()
{
    QString addrStr = ui->lineEdit_3->text();
    Keyboard wordAddr;
    AddressInputDialog addressintputdlg_writeaddress(wordAddr,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->lineEdit_3->setText(wordAddr.sShowAddr);
    }
}

void ExpressionDlg::on_btn_addr4_clicked()
{
    QString addrStr = ui->lineEdit_4->text();
    Keyboard wordAddr;
    AddressInputDialog addressintputdlg_writeaddress(wordAddr,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->lineEdit_4->setText(wordAddr.sShowAddr);
    }
}

void ExpressionDlg::on_comboBox_changed(int index)
{
    bool bValue = (E_OPERATION(index) == OPR_NONE);//无操作
    bool bConst = (ui->combo_Type->currentIndex() == 1);

    ui->combo_Type->setDisabled(bValue);

    ui->lineEdit_2->setDisabled(bValue);
    ui->btn_addr2->setDisabled(bValue || bConst);
}

void ExpressionDlg::on_comboBox_2_changed(int index)
{
    bool bValue = (E_OPERATION(index) == OPR_NONE);//无操作
    bool bConst = (ui->combo_Type_2->currentIndex() == 1);

    ui->combo_Type_2->setDisabled(bValue);

    ui->lineEdit_3->setDisabled(bValue);
    ui->btn_addr3->setDisabled(bValue || bConst);
}

void ExpressionDlg::on_comboBox_3_changed(int index)
{
    bool bValue = (E_OPERATION(index) == OPR_NONE);//无操作
    bool bConst = (ui->combo_Type_3->currentIndex() == 1);

    ui->combo_Type_3->setDisabled(bValue);

    ui->lineEdit_4->setDisabled(bValue);
    ui->btn_addr4->setDisabled(bValue || bConst);
}

bool ExpressionDlg::isDouble(QString txt)
{
    DoubleValidator *aDoubleValidator = new DoubleValidator(this,10);
    int pos = 0;
    if(aDoubleValidator->validate(txt,pos) == QValidator::Acceptable)
        return true;
    else
        return false;
}

void ExpressionDlg::on_combo_Type_currentIndexChanged(int index)
{
    ui->btn_addr2->setDisabled(index == 1);
    if(index == 1)
    {
        tempAddr1 = ui->lineEdit_2->text();
        DoubleValidator *aDoubleValidator = new DoubleValidator(this,10);
        ui->lineEdit_2->setValidator(aDoubleValidator);
        ui->lineEdit_2->setText(tempConst1);
    }
    else
    {
        tempConst1 = ui->lineEdit_2->text();
        ui->lineEdit_2->setValidator(0);
        ui->lineEdit_2->setText(tempAddr1);
    }

}

void ExpressionDlg::on_combo_Type_2_currentIndexChanged(int index)
{
    ui->btn_addr3->setDisabled(index == 1);
    if(index == 1)
    {
        tempAddr2 = ui->lineEdit_3->text();
        DoubleValidator *aDoubleValidator = new DoubleValidator(this,10);
        ui->lineEdit_3->setValidator(aDoubleValidator);
        ui->lineEdit_3->setText(tempConst2);
    }
    else
    {
        tempConst2 = ui->lineEdit_3->text();
        ui->lineEdit_3->setValidator(0);
        ui->lineEdit_3->setText(tempAddr2);
    }

}

void ExpressionDlg::on_combo_Type_3_currentIndexChanged(int index)
{
    ui->btn_addr4->setDisabled(index == 1);
    if(index == 1)
    {
        tempAddr3 = ui->lineEdit_4->text();
        DoubleValidator *aDoubleValidator = new DoubleValidator(this,10);
        ui->lineEdit_4->setValidator(aDoubleValidator);
        ui->lineEdit_4->setText(tempConst3);
    }
    else
    {
        tempConst3 = ui->lineEdit_4->text();
        ui->lineEdit_4->setValidator(0);
        ui->lineEdit_4->setText(tempAddr3);
    }

}
