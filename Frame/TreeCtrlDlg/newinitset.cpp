#include "newinitset.h"
#include "ui_newinitset.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

NewInitSet::NewInitSet(QWidget *parent):QDialog(parent),ui(new Ui::NewInitSet)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    setFixedSize(size());
    setWindowTitle(tr("显示设置"));

    int screenNum = pwnd->copyScreen_Item->childCount();//总的画面数
    QString str;

    ui->groupBox->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bUseLogo);

    int flag = -1;
    for(int i = 0; i < screenNum; i++)
    {
        //str = tr("画面") + QString::number(i);
        str = pwnd->copyScreen_Item->child(i)->text(0).split(":").at(1);
        ui->comboBox_logoNum->addItem(str);
        if(str == pwnd->m_pSamSysParame->m_mixGlobalVar.m_sLogoNum)
        {
            flag = i;
        }
    }
    ui->comboBox_logoNum->setCurrentIndex(flag);

    ui->groupBox_3->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bStandby);

    ui->comboBox_standbyModel->addItem(tr("画面待机"));
    ui->comboBox_standbyModel->addItem(tr("亮度变化待机"));
    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bStandbyMode == true)
    {
        ui->comboBox_standbyModel->setCurrentIndex(0);
    }
    else
    {
        ui->comboBox_standbyModel->setCurrentIndex(1);
    }

    //ui->lineEdit_standbyNum->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strStandbyNum);
    flag = -1;
    for(int i = 0; i < screenNum; i++)
    {
        //str = tr("画面") + QString::number(i);
        str = pwnd->copyScreen_Item->child(i)->text(0).split(":").at(1);
        ui->comboBox_standbyNum->addItem(str);
        if(str == pwnd->m_pSamSysParame->m_mixGlobalVar.m_sStandbyNum)
        {
            flag = i;
        }
    }
    ui->comboBox_standbyNum->setCurrentIndex(flag);

    ui->comboBox_standbyLight->addItem(tr("没有亮度"));
    ui->comboBox_standbyLight->addItem(tr("最小亮度"));
    //ui->comboBox_standbyLight->addItem(tr("当前亮度的一半"));
    int fuck = (int)pwnd->m_pSamSysParame->m_mixGlobalVar.m_eStandbyLight;
    ui->comboBox_standbyLight->setCurrentIndex(fuck - 1);

    ui->spinBox_standbyTime->setValue(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenTime);

    ui->checkBox_standbyLogin->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bStandbyLogin);

    //这个改成了组合框
    flag = -1;
    for(int i = 0; i < screenNum; i++)
    {
        //str = tr("画面") + QString::number(i);
        str = pwnd->copyScreen_Item->child(i)->text(0).split(":").at(1);
        ui->comboBox->addItem(str);
        if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_sInitNum == str)
        {
            flag = i;
        }
    }
    if(-1 == flag)
    {
        ui->comboBox->setCurrentIndex(0);
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_sInitNum = ui->comboBox->currentText();
    }
    else
    {
        ui->comboBox->setCurrentIndex(flag);
    }

    int GroupCount = pwnd->m_pSamSysParame->m_qvcRecipe.size();
    int curGroup = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nRecipeIndex;
    if(0 != GroupCount)//至少有一个组
    {
        if(curGroup >= GroupCount || curGroup < 0)//小于0的情况是没有配方先保存对话框以后再加配方打开对话框
        {
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_nRecipeIndex = 0;
            curGroup = 0;
        }

        for(int i = 0; i < GroupCount; i++)
        {
            ui->comboBox_peifang->addItem(pwnd->m_pSamSysParame->m_qvcRecipe[i].sName);
        }

        ui->comboBox_peifang->setCurrentIndex(curGroup);

        int recipeNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nRecipeNum;//当前配方号
        int CurCount = pwnd->m_pSamSysParame->m_qvcRecipe[curGroup].formula.size();//当前配方个数
        if(0 != CurCount)//至少有一个配方号
        {
            if(CurCount <= recipeNum)
            {
                pwnd->m_pSamSysParame->m_mixGlobalVar.m_nRecipeNum = 0;
                recipeNum = 0;
            }

            ui->comboBox_peifang_2->clear();
            for(int i = 0; i < CurCount; i++)
            {
                ui->comboBox_peifang_2->addItem(pwnd->m_pSamSysParame->m_qvcRecipe[curGroup].formula[i].sFormulaName);
            }
            if(recipeNum < 0)
            {
                recipeNum = 0;
            }
            ui->comboBox_peifang_2->setCurrentIndex(recipeNum);
        }
    }

    ui->checkBox->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bLockIcon);

    //ui->spinBox_freq->setValue(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nFlickRate);

    if(!ui->groupBox->isChecked())
    {
        ui->comboBox_logoNum->setEnabled(false);
    }
    else
    {
        ui->comboBox_logoNum->setEnabled(true);
    }

    if(!ui->groupBox_3->isChecked())
    {
        ui->comboBox_standbyModel->setEnabled(false);
        ui->comboBox_standbyNum->setEnabled(false);
        ui->comboBox_standbyLight->setEnabled(false);
        ui->spinBox_standbyTime->setEnabled(false);
        ui->checkBox_standbyLogin->setEnabled(false);
    }
    else
    {
        ui->comboBox_standbyModel->setEnabled(true);
        if(ui->comboBox_standbyModel->currentIndex() == 0)//画面待机
        {
            ui->comboBox_standbyNum->setEnabled(true);
            ui->comboBox_standbyLight->setEnabled(false);
        }
        else//亮度变化待机
        {
            ui->comboBox_standbyNum->setEnabled(false);
            ui->comboBox_standbyLight->setEnabled(true);
        }
        ui->spinBox_standbyTime->setEnabled(true);
        ui->checkBox_standbyLogin->setEnabled(true);
    }

    //ui->label_11->hide();
    //ui->spinBox_freq->hide();
}

NewInitSet::~NewInitSet()
{
    delete ui;
}

void NewInitSet::on_pushButton_sure_clicked()
{
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bUseLogo        = ui->groupBox->isChecked();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_sLogoNum        = ui->comboBox_logoNum->currentText();
    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bUseLogo && pwnd->m_pSamSysParame->m_mixGlobalVar.m_sLogoNum == "")
    {
        QMessageBox::about(this, tr("提示"), tr("启动logo没有设置"));
        return;
    }
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bStandby        = ui->groupBox_3->isChecked();
    if(ui->comboBox_standbyModel->currentIndex() == 0)
    {
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_bStandbyMode = true;
    }
    else
    {
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_bStandbyMode = false;
    }
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_sStandbyNum     = ui->comboBox_standbyNum->currentText();
    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bStandby && pwnd->m_pSamSysParame->m_mixGlobalVar.m_sStandbyNum == "")
    {
        if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bStandbyMode)//画面待机
        {
            QMessageBox::about(this, tr("提示"), tr("画面待机没有设置"));
            return;
        }
    }
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenTime     = ui->spinBox_standbyTime->value();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_eStandbyLight   = (LightMode)(ui->comboBox_standbyLight->currentIndex() + 1);
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bStandbyLogin   = ui->checkBox_standbyLogin->isChecked();  
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_sInitNum        = ui->comboBox->currentText();
    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_sInitNum == "")
    {
        QMessageBox::about(this, tr("提示"), tr("初始画面号没有设置"));
        return;
    }
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_nRecipeIndex    = ui->comboBox_peifang->currentIndex();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_nRecipeNum      = ui->comboBox_peifang_2->currentIndex();
    //pwnd->m_pSamSysParame->m_mixGlobalVar.m_nFlickRate      = ui->spinBox_freq->value();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bLockIcon       = ui->checkBox->isChecked();

    this->accept();
}

void NewInitSet::on_pushButton_cancel_clicked()
{
    this->close();
}

void NewInitSet::on_groupBox_clicked(bool checked)
{
    if(!checked)
    {
        ui->comboBox_logoNum->setEnabled(false);
    }
    else
    {
        ui->comboBox_logoNum->setEnabled(true);
    }
}

void NewInitSet::on_groupBox_3_clicked(bool checked)
{
    if(!checked)
    {
        ui->comboBox_standbyModel->setEnabled(false);
        ui->comboBox_standbyNum->setEnabled(false);
        ui->comboBox_standbyLight->setEnabled(false);
        ui->spinBox_standbyTime->setEnabled(false);
        ui->checkBox_standbyLogin->setEnabled(false);
    }
    else
    {
        ui->comboBox_standbyModel->setEnabled(true);
        if(ui->comboBox_standbyModel->currentIndex() == 0)//画面待机
        {
            ui->comboBox_standbyNum->setEnabled(true);
            ui->comboBox_standbyLight->setEnabled(false);

        }
        else//亮度变化待机
        {
            ui->comboBox_standbyNum->setEnabled(false);
            ui->comboBox_standbyLight->setEnabled(true);
        }
        ui->spinBox_standbyTime->setEnabled(true);
        ui->checkBox_standbyLogin->setEnabled(true);
    }
}


void NewInitSet::on_comboBox_standbyModel_currentIndexChanged(int index)
{
    if(0 == index)//画面待机
    {
        ui->comboBox_standbyNum->setEnabled(true);
        ui->comboBox_standbyLight->setEnabled(false);
    }
    else//亮度变化待机
    {
        ui->comboBox_standbyNum->setEnabled(false);
        ui->comboBox_standbyLight->setEnabled(true);
    }
}

void NewInitSet::on_comboBox_peifang_2_currentIndexChanged(int index)
{

}

void NewInitSet::on_comboBox_peifang_currentIndexChanged(int index)
{
    if(index < 0 || index >= pwnd->m_pSamSysParame->m_qvcRecipe.size())
    {
        return;
    }
    ui->comboBox_peifang_2->clear();

    int recipeNum = pwnd->m_pSamSysParame->m_qvcRecipe[index].formula.size();
    int CurCount = 0;
    if(0 != recipeNum)//至少有一个配方号
    {
        if(CurCount > recipeNum)
        {
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_nRecipeNum = 0;
            CurCount = 0;
        }

        for(int i = 0; i < recipeNum; i++)
        {
            ui->comboBox_peifang_2->addItem(pwnd->m_pSamSysParame->m_qvcRecipe[index].formula[i].sFormulaName);
        }
        ui->comboBox_peifang_2->setCurrentIndex(CurCount);
    }
}

void NewInitSet::on_helpbtn_clicked()
{
    pwnd->loadHelpHtm(TREE_SHOWSET);
}
