#include "newlanguage.h"
#include "ui_newlanguage.h"
#include "Frame\mainwindow.h"

extern MainWindow *pwnd;

//--------语言设置--------------------------------------
//short            m_nLanNum;             //语言总数
//QVector<QString> m_vecLanguageNameList; //语言名称列表
NewLanguage::NewLanguage(QWidget *parent):QDialog(parent),ui(new Ui::NewLanguage)
{
    ui->setupUi(this);
    bInitFlag = false;
    setFixedSize(size());
    setWindowTitle(tr("语言设置"));

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    //复制过来的本来就有
    //ui->comboBox_X->addItem(tr("1"));
    //ui->comboBox_X->addItem(tr("2"));
    //ui->comboBox_X->addItem(tr("3"));
    //ui->comboBox_X->addItem(tr("4"));
    //ui->comboBox_X->addItem(tr("5"));

    int num;
    num = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum;

    if(num <= 0 || num > 5)
    {
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum = 1;
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.clear();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.push_back(QString(tr("中文")));
        num = 1;
    }
    ui->comboBox_X->setCurrentIndex(num - 1);
    QVector<QString> vLan = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList;
    ui->label_lan1->hide();
    ui->label_lan2->hide();
    ui->label_lan3->hide();
    ui->label_lan4->hide();
    ui->label_lan5->hide();
    ui->lineEdit_lan1->hide();
    ui->lineEdit_lan2->hide();
    ui->lineEdit_lan3->hide();
    ui->lineEdit_lan4->hide();
    ui->lineEdit_lan5->hide();

    switch(num)
    {
        case 1:
        {
            ui->label_lan1->show();
            ui->lineEdit_lan1->show();
            ui->lineEdit_lan1->setText(vLan.at(0));
        }
        break;

        case 2:
        {
            ui->label_lan1->show();
            ui->label_lan2->show();
            ui->lineEdit_lan1->show();
            ui->lineEdit_lan2->show();
            ui->lineEdit_lan1->setText(vLan.at(0));
            ui->lineEdit_lan2->setText(vLan.at(1));
        }
        break;

        case 3:
        {
            ui->label_lan1->show();
            ui->label_lan2->show();
            ui->label_lan3->show();
            ui->lineEdit_lan1->show();
            ui->lineEdit_lan2->show();
            ui->lineEdit_lan3->show();
            ui->lineEdit_lan1->setText(vLan.at(0));
            ui->lineEdit_lan2->setText(vLan.at(1));
            ui->lineEdit_lan3->setText(vLan.at(2));
        }
        break;

        case 4:
        {
            ui->label_lan1->show();
            ui->label_lan2->show();
            ui->label_lan3->show();
            ui->label_lan4->show();
            ui->lineEdit_lan1->show();
            ui->lineEdit_lan2->show();
            ui->lineEdit_lan3->show();
            ui->lineEdit_lan4->show();
            ui->lineEdit_lan1->setText(vLan.at(0));
            ui->lineEdit_lan2->setText(vLan.at(1));
            ui->lineEdit_lan3->setText(vLan.at(2));
            ui->lineEdit_lan4->setText(vLan.at(3));
        }
        break;

        case 5:
        {
            ui->label_lan1->show();
            ui->label_lan2->show();
            ui->label_lan3->show();
            ui->label_lan4->show();
            ui->label_lan5->show();
            ui->lineEdit_lan1->show();
            ui->lineEdit_lan2->show();
            ui->lineEdit_lan3->show();
            ui->lineEdit_lan4->show();
            ui->lineEdit_lan5->show();
            ui->lineEdit_lan1->setText(vLan.at(0));
            ui->lineEdit_lan2->setText(vLan.at(1));
            ui->lineEdit_lan3->setText(vLan.at(2));
            ui->lineEdit_lan4->setText(vLan.at(3));
            ui->lineEdit_lan5->setText(vLan.at(4));
        }
        break;

        default:
        break;
    }

    ui->spinBox->setRange(1, num);
    ui->spinBox->setValue(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nCurLan + 1);
    bInitFlag = true;
}

NewLanguage::~NewLanguage()
{
    delete ui;
}

void NewLanguage::on_pushButton_ok_clicked()
{
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum = ui->comboBox_X->currentIndex() + 1;
    int k = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum;
    QString str(tr("Language"));
    QString str0;
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.clear();

    QStringList slit;
    slit.clear();
    slit.append(ui->lineEdit_lan1->text());
    slit.append(ui->lineEdit_lan2->text());
    slit.append(ui->lineEdit_lan3->text());
    slit.append(ui->lineEdit_lan4->text());
    slit.append(ui->lineEdit_lan5->text());

    for(int i = 1; i <= k; i++)
    {
       // str0 = QString::number(i);
        //pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.push_back(str + str0);
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.append(slit.at(i-1));
    }

    pwnd->m_pSamSysParame->m_mixGlobalVar.m_nCurLan = ui->spinBox->value() - 1;

    this->accept();
}

void NewLanguage::on_pushButton_cancle_clicked()
{
    this->close();
}

void NewLanguage::on_HelpButton_clicked()
{
    pwnd->loadHelpHtm(TREE_LANGUAGE);
}

void NewLanguage::on_comboBox_X_currentIndexChanged(int index)
{
    if( !bInitFlag )
        return;
    int num = index + 1;
    ui->spinBox->setRange(1, index + 1);
    switch(num)
    {
        case 1:
        {
            ui->label_lan1->show();
            ui->lineEdit_lan1->show();
            ui->label_lan2->hide();
            ui->lineEdit_lan2->hide();
            ui->label_lan3->hide();
            ui->lineEdit_lan3->hide();
            ui->label_lan4->hide();
            ui->lineEdit_lan4->hide();
            ui->label_lan5->hide();
            ui->lineEdit_lan5->hide();
        }
        break;

        case 2:
        {
            ui->label_lan1->show();
            ui->label_lan2->show();
            ui->lineEdit_lan1->show();
            ui->lineEdit_lan2->show();
            ui->label_lan3->hide();
            ui->lineEdit_lan3->hide();
            ui->label_lan4->hide();
            ui->lineEdit_lan4->hide();
            ui->label_lan5->hide();
            ui->lineEdit_lan5->hide();
        }
        break;

        case 3:
        {
            ui->label_lan1->show();
            ui->label_lan2->show();
            ui->label_lan3->show();
            ui->lineEdit_lan1->show();
            ui->lineEdit_lan2->show();
            ui->lineEdit_lan3->show();
            ui->label_lan4->hide();
            ui->lineEdit_lan4->hide();
            ui->label_lan5->hide();
            ui->lineEdit_lan5->hide();
        }
        break;

        case 4:
        {
            ui->label_lan1->show();
            ui->label_lan2->show();
            ui->label_lan3->show();
            ui->label_lan4->show();
            ui->lineEdit_lan1->show();
            ui->lineEdit_lan2->show();
            ui->lineEdit_lan3->show();
            ui->lineEdit_lan4->show();
            ui->label_lan5->hide();
            ui->lineEdit_lan5->hide();
        }
        break;

        case 5:
        {
            ui->label_lan1->show();
            ui->label_lan2->show();
            ui->label_lan3->show();
            ui->label_lan4->show();
            ui->label_lan5->show();
            ui->lineEdit_lan1->show();
            ui->lineEdit_lan2->show();
            ui->lineEdit_lan3->show();
            ui->lineEdit_lan4->show();
            ui->lineEdit_lan5->show();
        }
        break;

        default:
        break;
    }
}

void NewLanguage::on_spinBox_valueChanged(int value)
{
    if(value > ui->comboBox_X->currentIndex() + 1)
    {
        ui->spinBox->setValue(ui->comboBox_X->currentIndex() + 1);
    }
}
