#include "newproright.h"
#include "ui_newproright.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

NewProRight::NewProRight(QWidget *parent):QDialog(parent),ui(new Ui::NewProRight)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    setFixedSize(size());
    setWindowTitle(tr("产品授权"));

    bFirst = true;

    ui->dateTimeEdit_1->setDisplayFormat("yyyy-MM-dd hh:mm");
    ui->dateTimeEdit_2->setDisplayFormat("yyyy-MM-dd hh:mm");
    ui->dateTimeEdit_3->setDisplayFormat("yyyy-MM-dd hh:mm");
    ui->dateTimeEdit_4->setDisplayFormat("yyyy-MM-dd hh:mm");
    ui->dateTimeEdit_5->setDisplayFormat("yyyy-MM-dd hh:mm");

    ui->comboBox_proRight->addItem(tr("永久授权"));
    ui->comboBox_proRight->addItem(tr("时效授权"));

    ui->comboBox_aging->addItem(tr("按使用时间计算"));
    ui->comboBox_aging->addItem(tr("按截止日期计算"));

    QRegExp regExp("[0-9A-Za-z_]*");
    QValidator *validator = new QRegExpValidator(regExp, this);
    ui->lineEdit_password_1->setValidator(validator);
    ui->lineEdit_password_1->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));
    ui->lineEdit_password_2->setValidator(validator);
    ui->lineEdit_password_2->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));
    ui->lineEdit_password_3->setValidator(validator);
    ui->lineEdit_password_3->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));
    ui->lineEdit_password_4->setValidator(validator);
    ui->lineEdit_password_4->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));
    ui->lineEdit_password_5->setValidator(validator);
    ui->lineEdit_password_5->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));

    ui->lineEdit_str1->setValidator(validator);
    ui->lineEdit_str1->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));
    ui->lineEdit_str2->setValidator(validator);
    ui->lineEdit_str2->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));
    ui->lineEdit_str3->setValidator(validator);
    ui->lineEdit_str3->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));
    ui->lineEdit_str4->setValidator(validator);
    ui->lineEdit_str4->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));
    ui->lineEdit_str5->setValidator(validator);
    ui->lineEdit_str5->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));


    ui->checkBox_dayX1->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDay[0]);
    ui->lineEdit_warningX1->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDay[0]);
    ui->spinBox_time1->setValue(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nUseDay[0]);
    ui->lineEdit_password_1->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_sUseDayPassword[0]);
    ui->checkBox_dayX2->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDay[1]);
    ui->lineEdit_warningX2->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDay[1]);
    ui->spinBox_time2->setValue(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nUseDay[1]);
    ui->lineEdit_password_2->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_sUseDayPassword[1]);
    ui->checkBox_dayX3->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDay[2]);
    ui->lineEdit_warningX3->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDay[2]);
    ui->spinBox_time3->setValue(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nUseDay[2]);
    ui->lineEdit_password_3->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_sUseDayPassword[2]);
    ui->checkBox_dayX4->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDay[3]);
    ui->lineEdit_warningX4->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDay[3]);
    ui->spinBox_time4->setValue(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nUseDay[3]);
    ui->lineEdit_password_4->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_sUseDayPassword[3]);
    ui->checkBox_dayX5->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDay[4]);
    ui->lineEdit_warningX5->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDay[4]);
    ui->spinBox_time5->setValue(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nUseDay[4]);
    ui->lineEdit_password_5->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_sUseDayPassword[4]);

    ui->checkBox_dateY1->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDate[0]);
    ui->dateTimeEdit_1->setDateTime(pwnd->m_pSamSysParame->m_mixGlobalVar.m_gDateTime[0]);
    ui->lineEdit_str1->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strDate[0]);
    ui->lineEdit_warningY1->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDate[0]);
    ui->checkBox_dateY2->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDate[1]);
    ui->dateTimeEdit_2->setDateTime(pwnd->m_pSamSysParame->m_mixGlobalVar.m_gDateTime[1]);
    ui->lineEdit_str2->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strDate[1]);
    ui->lineEdit_warningY2->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDate[1]);
    ui->checkBox_dateY3->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDate[2]);
    ui->dateTimeEdit_3->setDateTime(pwnd->m_pSamSysParame->m_mixGlobalVar.m_gDateTime[2]);
    ui->lineEdit_str3->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strDate[2]);
    ui->lineEdit_warningY3->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDate[2]);
    ui->checkBox_dateY4->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDate[3]);
    ui->dateTimeEdit_4->setDateTime(pwnd->m_pSamSysParame->m_mixGlobalVar.m_gDateTime[3]);
    ui->lineEdit_str4->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strDate[3]);
    ui->lineEdit_warningY4->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDate[3]);
    ui->checkBox_dateY5->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDate[4]);
    ui->dateTimeEdit_5->setDateTime(pwnd->m_pSamSysParame->m_mixGlobalVar.m_gDateTime[4]);
    ui->lineEdit_str5->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strDate[4]);
    ui->lineEdit_warningY5->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDate[4]);

    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_eAuthMode == AuthForever)//永久授权
    {
        ui->comboBox_proRight->setCurrentIndex(0);
        ui->groupBox->setEnabled(false);
        setGroupBox2Enabled(false);
        setGroupBox3Enabled(false);
    }
    else
    {
        ui->comboBox_proRight->setCurrentIndex(1);
        ui->groupBox->setEnabled(true);

        if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_eTimeStyle == AUseTime)//按使用时间计算时
        {
            ui->comboBox_aging->setCurrentIndex(0);
            setGroupBox2Enabled(true);
            setGroupBox3Enabled(false);
        }
        else
        {
            ui->comboBox_aging->setCurrentIndex(1);
            setGroupBox2Enabled(false);
            setGroupBox3Enabled(true);
        }
    }

    bFirst = false;
}

NewProRight::~NewProRight()
{
    delete ui;
}

void NewProRight::on_pushButton_sure_clicked()
{
    int model;
    int style;

    model = ui->comboBox_proRight->currentIndex() + 1;
    style = ui->comboBox_aging->currentIndex() + 1;

    if(model == 2 && style == 1)//
    {
        QVector<int> vecDay;
        QVector<int> vecNumber;
        if(ui->checkBox_dayX1->isChecked())
        {
            vecDay.push_back(ui->spinBox_time1->value());
            vecNumber.push_back(1);
        }
        if(ui->checkBox_dayX2->isChecked())
        {
            vecDay.push_back(ui->spinBox_time2->value());
            vecNumber.push_back(2);
        }
        if(ui->checkBox_dayX3->isChecked())
        {
            vecDay.push_back(ui->spinBox_time3->value());
            vecNumber.push_back(3);
        }
        if(ui->checkBox_dayX4->isChecked())
        {
            vecDay.push_back(ui->spinBox_time4->value());
            vecNumber.push_back(4);
        }
        if(ui->checkBox_dayX5->isChecked())
        {
            vecDay.push_back(ui->spinBox_time5->value());
            vecNumber.push_back(5);
        }
/*
        int dayNum = vecDay.size();
        for(int i = 1; i < dayNum; i++)
        {
            if(vecDay[i] <= vecDay[i - 1])
            {

                QMessageBox::about(this, tr("警告"), tr("使用天数输入不正确"));
                if(2 == vecNumber[i])
                {
                    ui->spinBox_time2->setFocus();
                }
                else if(3 == vecNumber[i])
                {
                    ui->spinBox_time3->setFocus();
                }
                else if(4 == vecNumber[i])
                {
                    ui->spinBox_time4->setFocus();
                }
                else if(5 == vecNumber[i])
                {
                    ui->spinBox_time5->setFocus();
                }

                return;
            }
        }*/
    }

    if(model == 2 && style == 2)
    {
        QVector<QDateTime> vecDateTime;
        QVector<int> vecNumber;
        if(ui->checkBox_dateY1->isChecked())
        {
            vecDateTime.push_back(ui->dateTimeEdit_1->dateTime());
            vecNumber.push_back(1);
        }
        if(ui->checkBox_dateY2->isChecked())
        {
            vecDateTime.push_back(ui->dateTimeEdit_2->dateTime());
            vecNumber.push_back(2);
        }
        if(ui->checkBox_dateY3->isChecked())
        {
            vecDateTime.push_back(ui->dateTimeEdit_3->dateTime());
            vecNumber.push_back(3);
        }
        if(ui->checkBox_dateY4->isChecked())
        {
            vecDateTime.push_back(ui->dateTimeEdit_4->dateTime());
            vecNumber.push_back(4);
        }
        if(ui->checkBox_dateY5->isChecked())
        {
            vecDateTime.push_back(ui->dateTimeEdit_5->dateTime());
            vecNumber.push_back(5);
        }

        int dtNum = vecDateTime.size();
        for(int i = 1; i < dtNum; i++)
        {
            if(vecDateTime[i] <= vecDateTime[i - 1])
            {
                QMessageBox::about(this, tr("警告"), tr("起始日期前一个不能比后一个晚"));
                if(2 == vecNumber[i])
                {
                    ui->dateTimeEdit_2->setFocus();
                }
                else if(3 == vecNumber[i])
                {
                    ui->dateTimeEdit_3->setFocus();
                }
                else if(4 == vecNumber[i])
                {
                    ui->dateTimeEdit_4->setFocus();
                }
                else if(5 == vecNumber[i])
                {
                    ui->dateTimeEdit_5->setFocus();
                }

                return;
            }
        }
    }

    pwnd->m_pSamSysParame->m_mixGlobalVar.m_eAuthMode   = (AuthorizeMode)model;
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_eTimeStyle  = (AuthTimeSet)style;

    if(model == 2 && style == 1)
    {
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDay[0]        = ui->checkBox_dayX1->isChecked();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDay[0]    = ui->lineEdit_warningX1->text();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nUseDay[0]          = ui->spinBox_time1->value();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_sUseDayPassword[0]  = ui->lineEdit_password_1->text();

        pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDay[1]        = ui->checkBox_dayX2->isChecked();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDay[1]    = ui->lineEdit_warningX2->text();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nUseDay[1]          = ui->spinBox_time2->value();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_sUseDayPassword[1]  = ui->lineEdit_password_2->text();

        pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDay[2]        = ui->checkBox_dayX3->isChecked();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDay[2]    = ui->lineEdit_warningX3->text();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nUseDay[2]          = ui->spinBox_time3->value();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_sUseDayPassword[2]  = ui->lineEdit_password_3->text();

        pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDay[3]        = ui->checkBox_dayX4->isChecked();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDay[3]    = ui->lineEdit_warningX4->text();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nUseDay[3]          = ui->spinBox_time4->value();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_sUseDayPassword[3]  = ui->lineEdit_password_4->text();

        pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDay[4]        = ui->checkBox_dayX5->isChecked();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDay[4]    = ui->lineEdit_warningX5->text();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nUseDay[4]          = ui->spinBox_time5->value();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_sUseDayPassword[4]  = ui->lineEdit_password_5->text();
    }
    else if(model == 2 && style == 2)
    {
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDate[0]       = ui->checkBox_dateY1->isChecked();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_gDateTime[0]        = ui->dateTimeEdit_1->dateTime();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strDate[0]          = ui->lineEdit_str1->text();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDate[0]   = ui->lineEdit_warningY1->text();

        pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDate[1]       = ui->checkBox_dateY2->isChecked();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_gDateTime[1]        = ui->dateTimeEdit_2->dateTime();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strDate[1]          = ui->lineEdit_str2->text();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDate[1]   = ui->lineEdit_warningY2->text();

        pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDate[2]       = ui->checkBox_dateY3->isChecked();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_gDateTime[2]        = ui->dateTimeEdit_3->dateTime();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strDate[2]          = ui->lineEdit_str3->text();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDate[2]   = ui->lineEdit_warningY3->text();

        pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDate[3]       = ui->checkBox_dateY4->isChecked();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_gDateTime[3]        = ui->dateTimeEdit_4->dateTime();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strDate[3]          = ui->lineEdit_str4->text();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDate[3]   = ui->lineEdit_warningY4->text();

        pwnd->m_pSamSysParame->m_mixGlobalVar.m_bIsUseDate[4]       = ui->checkBox_dateY5->isChecked();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_gDateTime[4]        = ui->dateTimeEdit_5->dateTime();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strDate[4]          = ui->lineEdit_str5->text();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strTimeoutDate[4]   = ui->lineEdit_warningY5->text();
    }

    this->accept();
}

void NewProRight::on_pushButton_cancel_clicked()
{
    this->close();
}

void NewProRight::on_comboBox_proRight_currentIndexChanged(int index)//改变授权方式
{
    if(bFirst == true)
    {
        return;
    }

    if(0 == index)
    {
        ui->groupBox->setEnabled(false);
        setGroupBox2Enabled(false);
        setGroupBox3Enabled(false);
        setGroupBox2Checked(false);
        setGroupBox3Checked(false);
    }
    else
    {
        ui->groupBox->setEnabled(true);
        if(ui->comboBox_aging->currentIndex() == 0)
        {
            setGroupBox2Enabled(true);
            setGroupBox3Enabled(false);
            setGroupBox3Checked(false);
        }
        else
        {
            setGroupBox2Enabled(false);
            setGroupBox3Enabled(true);
            setGroupBox2Checked(false);
        }
    }
}

void NewProRight::on_comboBox_aging_currentIndexChanged(int index)
{
    if(0 == index)
    {
        setGroupBox2Enabled(true);
        setGroupBox3Enabled(false);
        setGroupBox3Checked(false);
    }
    else//按使用时间计算时
    {
        setGroupBox2Enabled(false);
        setGroupBox2Checked(false);
        setGroupBox3Enabled(true);
    }
}

void NewProRight::on_helpbtn_clicked()
{
    pwnd->loadHelpHtm(TREE_IMPOWER);
}

void NewProRight::on_checkBox_dayX1_clicked(bool checked)
{
    ui->lineEdit_warningX1->setEnabled(checked);
    ui->spinBox_time1->setEnabled(checked);
    ui->lineEdit_password_1->setEnabled(checked);
}

void NewProRight::on_checkBox_dayX2_clicked(bool checked)
{
    ui->lineEdit_warningX2->setEnabled(checked);
    ui->spinBox_time2->setEnabled(checked);
    ui->lineEdit_password_2->setEnabled(checked);
}

void NewProRight::on_checkBox_dayX3_clicked(bool checked)
{
    ui->lineEdit_warningX3->setEnabled(checked);
    ui->spinBox_time3->setEnabled(checked);
    ui->lineEdit_password_3->setEnabled(checked);
}

void NewProRight::on_checkBox_dayX4_clicked(bool checked)
{
    ui->lineEdit_warningX4->setEnabled(checked);
    ui->spinBox_time4->setEnabled(checked);
    ui->lineEdit_password_4->setEnabled(checked);
}

void NewProRight::on_checkBox_dayX5_clicked(bool checked)
{
    ui->lineEdit_warningX5->setEnabled(checked);
    ui->spinBox_time5->setEnabled(checked);
    ui->lineEdit_password_5->setEnabled(checked);
}

void NewProRight::on_checkBox_dateY1_clicked(bool checked)
{
    ui->dateTimeEdit_1->setEnabled(checked);
    ui->lineEdit_str1->setEnabled(checked);
    ui->lineEdit_warningY1->setEnabled(checked);
}

void NewProRight::on_checkBox_dateY2_clicked(bool checked)
{
    ui->dateTimeEdit_2->setEnabled(checked);
    ui->lineEdit_str2->setEnabled(checked);
    ui->lineEdit_warningY2->setEnabled(checked);
}

void NewProRight::on_checkBox_dateY3_clicked(bool checked)
{
    ui->dateTimeEdit_3->setEnabled(checked);
    ui->lineEdit_str3->setEnabled(checked);
    ui->lineEdit_warningY3->setEnabled(checked);
}

void NewProRight::on_checkBox_dateY4_clicked(bool checked)
{
    ui->dateTimeEdit_4->setEnabled(checked);
    ui->lineEdit_str4->setEnabled(checked);
    ui->lineEdit_warningY4->setEnabled(checked);
}

void NewProRight::on_checkBox_dateY5_clicked(bool checked)
{
    ui->dateTimeEdit_5->setEnabled(checked);
    ui->lineEdit_str5->setEnabled(checked);
    ui->lineEdit_warningY5->setEnabled(checked);
}

void NewProRight::setGroupBox2Checked(bool bChecked)
{
    ui->checkBox_dayX1->setChecked(bChecked);
    ui->checkBox_dayX2->setChecked(bChecked);
    ui->checkBox_dayX3->setChecked(bChecked);
    ui->checkBox_dayX4->setChecked(bChecked);
    ui->checkBox_dayX5->setChecked(bChecked);
}

void NewProRight::setGroupBox3Checked(bool bChecked)
{
    ui->checkBox_dateY1->setChecked(bChecked);
    ui->checkBox_dateY2->setChecked(bChecked);
    ui->checkBox_dateY3->setChecked(bChecked);
    ui->checkBox_dateY4->setChecked(bChecked);
    ui->checkBox_dateY5->setChecked(bChecked);
}


void NewProRight::setGroupBox2Enabled(bool bFlag/*= true*/)
{
    if(ui->checkBox_dayX1->isChecked())//1
    {
        ui->checkBox_dayX1->setEnabled(bFlag);
        ui->lineEdit_warningX1->setEnabled(bFlag);
        ui->spinBox_time1->setEnabled(bFlag);
        ui->lineEdit_password_1->setEnabled(bFlag);
    }
    else
    {
        ui->checkBox_dayX1->setEnabled(bFlag);
        ui->lineEdit_warningX1->setEnabled(false);
        ui->spinBox_time1->setEnabled(false);
        ui->lineEdit_password_1->setEnabled(false);
    }

    if(ui->checkBox_dayX2->isChecked())//2
    {
        ui->checkBox_dayX2->setEnabled(bFlag);
        ui->lineEdit_warningX2->setEnabled(bFlag);
        ui->spinBox_time2->setEnabled(bFlag);
        ui->lineEdit_password_2->setEnabled(bFlag);
    }
    else
    {
        ui->checkBox_dayX2->setEnabled(bFlag);
        ui->lineEdit_warningX2->setEnabled(false);
        ui->spinBox_time2->setEnabled(false);
        ui->lineEdit_password_2->setEnabled(false);
    }

    if(ui->checkBox_dayX3->isChecked())//3
    {
        ui->checkBox_dayX3->setEnabled(bFlag);
        ui->lineEdit_warningX3->setEnabled(bFlag);
        ui->spinBox_time3->setEnabled(bFlag);
        ui->lineEdit_password_3->setEnabled(bFlag);
    }
    else
    {
        ui->checkBox_dayX3->setEnabled(bFlag);
        ui->lineEdit_warningX3->setEnabled(false);
        ui->spinBox_time3->setEnabled(false);
        ui->lineEdit_password_3->setEnabled(false);
    }

    if(ui->checkBox_dayX4->isChecked())//4
    {
        ui->checkBox_dayX4->setEnabled(bFlag);
        ui->lineEdit_warningX4->setEnabled(bFlag);
        ui->spinBox_time4->setEnabled(bFlag);
        ui->lineEdit_password_4->setEnabled(bFlag);
    }
    else
    {
        ui->checkBox_dayX4->setEnabled(bFlag);
        ui->lineEdit_warningX4->setEnabled(false);
        ui->spinBox_time4->setEnabled(false);
        ui->lineEdit_password_4->setEnabled(false);
    }

    if(ui->checkBox_dayX5->isChecked())//5
    {
        ui->checkBox_dayX5->setEnabled(bFlag);
        ui->lineEdit_warningX5->setEnabled(bFlag);
        ui->spinBox_time5->setEnabled(bFlag);
        ui->lineEdit_password_5->setEnabled(bFlag);
    }
    else
    {
        ui->checkBox_dayX5->setEnabled(bFlag);
        ui->lineEdit_warningX5->setEnabled(false);
        ui->spinBox_time5->setEnabled(false);
        ui->lineEdit_password_5->setEnabled(false);
    }
}


void NewProRight::setGroupBox3Enabled(bool bFlag/*= true*/)
{
    if(ui->checkBox_dateY1->isChecked())//1
    {
        ui->checkBox_dateY1->setEnabled(bFlag);
        ui->dateTimeEdit_1->setEnabled(bFlag);
        ui->lineEdit_str1->setEnabled(bFlag);
        ui->lineEdit_warningY1->setEnabled(bFlag);
    }
    else
    {
        ui->checkBox_dateY1->setEnabled(bFlag);
        ui->dateTimeEdit_1->setEnabled(false);
        ui->lineEdit_str1->setEnabled(false);
        ui->lineEdit_warningY1->setEnabled(false);
    }

    if(ui->checkBox_dateY2->isChecked())//2
    {
        ui->checkBox_dateY2->setEnabled(bFlag);
        ui->dateTimeEdit_2->setEnabled(bFlag);
        ui->lineEdit_str2->setEnabled(bFlag);
        ui->lineEdit_warningY2->setEnabled(bFlag);
    }
    else
    {
        ui->checkBox_dateY2->setEnabled(bFlag);
        ui->dateTimeEdit_2->setEnabled(false);
        ui->lineEdit_str2->setEnabled(false);
        ui->lineEdit_warningY2->setEnabled(false);
    }

    if(ui->checkBox_dateY3->isChecked())//3
    {
        ui->checkBox_dateY3->setEnabled(bFlag);
        ui->dateTimeEdit_3->setEnabled(bFlag);
        ui->lineEdit_str3->setEnabled(bFlag);
        ui->lineEdit_warningY3->setEnabled(bFlag);
    }
    else
    {
        ui->checkBox_dateY3->setEnabled(bFlag);
        ui->dateTimeEdit_3->setEnabled(false);
        ui->lineEdit_str3->setEnabled(false);
        ui->lineEdit_warningY3->setEnabled(false);
    }

    if(ui->checkBox_dateY4->isChecked())//4
    {
        ui->checkBox_dateY4->setEnabled(bFlag);
        ui->dateTimeEdit_4->setEnabled(bFlag);
        ui->lineEdit_str4->setEnabled(bFlag);
        ui->lineEdit_warningY4->setEnabled(bFlag);
    }
    else
    {
        ui->checkBox_dateY4->setEnabled(bFlag);
        ui->dateTimeEdit_4->setEnabled(false);
        ui->lineEdit_str4->setEnabled(false);
        ui->lineEdit_warningY4->setEnabled(false);
    }

    if(ui->checkBox_dateY5->isChecked())//5
    {
        ui->checkBox_dateY5->setEnabled(bFlag);
        ui->dateTimeEdit_5->setEnabled(bFlag);
        ui->lineEdit_str5->setEnabled(bFlag);
        ui->lineEdit_warningY5->setEnabled(bFlag);
    }
    else
    {
        ui->checkBox_dateY5->setEnabled(bFlag);
        ui->dateTimeEdit_5->setEnabled(false);
        ui->lineEdit_str5->setEnabled(false);
        ui->lineEdit_warningY5->setEnabled(false);
    }
}
