#include "screenwidget.h"
#include "ui_screenwidget.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;
ScreenWidget::ScreenWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenWidget)
{
    ui->setupUi(this);
    QString stotal="";
    int nTmp=0;
    QString sTmp="";
	foreach(SamDrawScene* pScene,pwnd->pSceneSheet)
	{
		if(pScene->nIsSceneOrWindow == 0)
		{
			ui->comboBox_ScreenIndex->addItem(pScene->sNewScreenName);
		}
	}
    
	on_comboBox_operType_currentIndexChanged(0);
}

ScreenWidget::~ScreenWidget()
{
    delete ui;
}
bool ScreenWidget::Save()
{
    sceneproperty.operType = (SCENE_OPER_TYPE)ui->comboBox_operType->currentIndex();
    sceneproperty.sceneName = ui->comboBox_ScreenIndex->currentText();
    sceneproperty.nSlideStyle = ui->comboBox_effect->currentIndex();
    sceneproperty.bLogout = ui->checkBox->isChecked();

    return true;
}
void ScreenWidget::InitUi(sceneSwitchPro property)
{
    ui->comboBox_operType->setCurrentIndex(property.operType);
	
    int index =ui->comboBox_ScreenIndex->findText(property.sceneName) ;
    if(index != -1)
        ui->comboBox_ScreenIndex->setCurrentIndex(index);
    ui->comboBox_effect->setCurrentIndex(property.nSlideStyle);
    ui->checkBox->setChecked(property.bLogout);
}

void ScreenWidget::on_comboBox_operType_currentIndexChanged(int index)
{
    bool bValue = true;
	switch (index)
	{
	case 0:
    case 4:
		bValue = false;
		break;
	case 1:
		ui->label_4->setText(tr("画面名称："));
		ui->comboBox_ScreenIndex->clear();
		foreach(SamDrawScene* pScene,pwnd->pSceneSheet)
		{
			if(pScene->nIsSceneOrWindow == 0)
			{
				ui->comboBox_ScreenIndex->addItem(pScene->sNewScreenName);
			}
		}
		break;
	case 2:
		ui->label_4->setText(tr("窗口名称："));
		ui->comboBox_ScreenIndex->clear();
		foreach(SamDrawScene* pScene,pwnd->pSceneSheet)
		{
			if(pScene->nIsSceneOrWindow == 1)
			{
				ui->comboBox_ScreenIndex->addItem(pScene->sNewScreenName);
			}
		}
		break;
	case 3:
		bValue = false;
		break;
    }
    ui->label_4->setEnabled(bValue);
    ui->comboBox_ScreenIndex->setEnabled(bValue);
}
