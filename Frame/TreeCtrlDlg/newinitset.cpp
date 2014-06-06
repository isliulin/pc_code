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
    setWindowTitle(tr("��ʾ����"));

    int screenNum = pwnd->copyScreen_Item->childCount();//�ܵĻ�����
    QString str;

    ui->groupBox->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bUseLogo);

    int flag = -1;
    for(int i = 0; i < screenNum; i++)
    {
        //str = tr("����") + QString::number(i);
        str = pwnd->copyScreen_Item->child(i)->text(0).split(":").at(1);
        ui->comboBox_logoNum->addItem(str);
        if(str == pwnd->m_pSamSysParame->m_mixGlobalVar.m_sLogoNum)
        {
            flag = i;
        }
    }
    ui->comboBox_logoNum->setCurrentIndex(flag);

    ui->groupBox_3->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bStandby);

    ui->comboBox_standbyModel->addItem(tr("�������"));
    ui->comboBox_standbyModel->addItem(tr("���ȱ仯����"));
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
        //str = tr("����") + QString::number(i);
        str = pwnd->copyScreen_Item->child(i)->text(0).split(":").at(1);
        ui->comboBox_standbyNum->addItem(str);
        if(str == pwnd->m_pSamSysParame->m_mixGlobalVar.m_sStandbyNum)
        {
            flag = i;
        }
    }
    ui->comboBox_standbyNum->setCurrentIndex(flag);

    ui->comboBox_standbyLight->addItem(tr("û������"));
    ui->comboBox_standbyLight->addItem(tr("��С����"));
    //ui->comboBox_standbyLight->addItem(tr("��ǰ���ȵ�һ��"));
    int fuck = (int)pwnd->m_pSamSysParame->m_mixGlobalVar.m_eStandbyLight;
    ui->comboBox_standbyLight->setCurrentIndex(fuck - 1);

    ui->spinBox_standbyTime->setValue(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenTime);

    ui->checkBox_standbyLogin->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bStandbyLogin);

    //����ĳ�����Ͽ�
    flag = -1;
    for(int i = 0; i < screenNum; i++)
    {
        //str = tr("����") + QString::number(i);
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
    if(0 != GroupCount)//������һ����
    {
        if(curGroup >= GroupCount || curGroup < 0)//С��0�������û���䷽�ȱ���Ի����Ժ��ټ��䷽�򿪶Ի���
        {
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_nRecipeIndex = 0;
            curGroup = 0;
        }

        for(int i = 0; i < GroupCount; i++)
        {
            ui->comboBox_peifang->addItem(pwnd->m_pSamSysParame->m_qvcRecipe[i].sName);
        }

        ui->comboBox_peifang->setCurrentIndex(curGroup);

        int recipeNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nRecipeNum;//��ǰ�䷽��
        int CurCount = pwnd->m_pSamSysParame->m_qvcRecipe[curGroup].formula.size();//��ǰ�䷽����
        if(0 != CurCount)//������һ���䷽��
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
        if(ui->comboBox_standbyModel->currentIndex() == 0)//�������
        {
            ui->comboBox_standbyNum->setEnabled(true);
            ui->comboBox_standbyLight->setEnabled(false);
        }
        else//���ȱ仯����
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
        QMessageBox::about(this, tr("��ʾ"), tr("����logoû������"));
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
        if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bStandbyMode)//�������
        {
            QMessageBox::about(this, tr("��ʾ"), tr("�������û������"));
            return;
        }
    }
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenTime     = ui->spinBox_standbyTime->value();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_eStandbyLight   = (LightMode)(ui->comboBox_standbyLight->currentIndex() + 1);
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bStandbyLogin   = ui->checkBox_standbyLogin->isChecked();  
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_sInitNum        = ui->comboBox->currentText();
    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_sInitNum == "")
    {
        QMessageBox::about(this, tr("��ʾ"), tr("��ʼ�����û������"));
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
        if(ui->comboBox_standbyModel->currentIndex() == 0)//�������
        {
            ui->comboBox_standbyNum->setEnabled(true);
            ui->comboBox_standbyLight->setEnabled(false);

        }
        else//���ȱ仯����
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
    if(0 == index)//�������
    {
        ui->comboBox_standbyNum->setEnabled(true);
        ui->comboBox_standbyLight->setEnabled(false);
    }
    else//���ȱ仯����
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
    if(0 != recipeNum)//������һ���䷽��
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
