#include "functionwdiget.h"
#include "ui_functionwdiget.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

FunctionWdiget::FunctionWdiget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionWdiget)
{
    ui->setupUi(this);
    foreach(SamDrawScene* pScene,pwnd->pSceneSheet)
    {
        if(pScene->nIsSceneOrWindow == 1)
        {
            ui->combo_screen->addItem(pScene->sNewScreenName);
        }
    }
    ui->combo_screen->setEnabled(false);
    ui->label_3->setEnabled(false);
    ui->label_2->setEnabled(false);
    ui->combo_Type->setEnabled(false);

    ui->checkBox_X->setEnabled(false);
    ui->checkBox_Y->setEnabled(false);
    bX = true;
    bY = false;

    FunTranslation(0);
}

FunctionWdiget::~FunctionWdiget()
{
    delete ui;
}
bool FunctionWdiget::Save()
{	
    funproperty.operType = (PECULIAR_TYPE)ui->combo_Funciton->currentIndex();
	if (funproperty.operType == OPER_WINDOW && ui->combo_screen->currentText().isEmpty())
	{
		QMessageBox::about(ui->combo_screen, tr(""), tr("δѡ��Ҫ�����Ĵ���"));
		ui->combo_screen->setFocus();
		return false;
	}
    funproperty.functionIndex = ui->combo_Type->currentIndex();
    funproperty.windowName = ui->combo_screen->currentText();
    funproperty.IsCheckX = ui->checkBox_X->isChecked();
    funproperty.IsCheckY = ui->checkBox_Y->isChecked();
    return true;
}
void FunctionWdiget::InitUi(functionSwitchPro property)
{
    ui->combo_Funciton->setCurrentIndex(property.operType);
    ui->combo_Type->setCurrentIndex(property.functionIndex);
    int index = ui->combo_screen->findText(property.windowName);
    if(index != -1)
    {
        ui->combo_screen->setCurrentIndex(index);
    }

    if(property.IsCheckX)
    {
        bX = true;
        ui->checkBox_X->setChecked(true);
    }
    else
    {
        bX = false;
        ui->checkBox_X->setChecked(false);
    }

    if(property.IsCheckY)
    {
        bY = true;
        ui->checkBox_Y->setChecked(true);
    }
    else
    {
        bY = false;
        ui->checkBox_Y->setChecked(false);
    }

    //FunTranslation(property.operType);
}

void FunctionWdiget::on_combo_Funciton_currentIndexChanged(int index)
{
    QStringList items;

    FunTranslation(index);

    switch(index)
    {
	case 8:
        {
            int languageCount = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();

            for(int i=0; i<languageCount; i++)
            {
                    items << (pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
            }
            ui->label_2->setEnabled(true);
            ui->combo_Type->setEnabled(true);
            ui->label_3->setEnabled(false);
            ui->combo_screen->setEnabled(false);
            ui->combo_Type->clear();
            ui->combo_Type->addItems(items);
            ui->combo_Type->setCurrentIndex(0);
            ui->checkBox_X->setEnabled(false);
            ui->checkBox_Y->setEnabled(false);
        }
        break;
        case 10:
        {
            items << tr("�򿪴���") << tr("�رմ���");
            ui->label_2->setEnabled(true);
            ui->combo_Type->setEnabled(true);
            ui->label_3->setEnabled(true);
            ui->combo_screen->setEnabled(true);
            ui->combo_Type->clear();
            ui->combo_Type->addItems(items);
            ui->combo_Type->setCurrentIndex(0);
            ui->checkBox_X->setEnabled(false);
            ui->checkBox_Y->setEnabled(false);
        }
        break;
        case 12:
        {
            items << tr("�༭��ǰ�䷽") << tr("�½��䷽") << tr("ɾ����ǰ�䷽") << tr("ɾ��һ���䷽")
                    << tr("��ǰ�䷽д��PLC") << tr("��PLC����ǰ�䷽") << tr("�䷽�鵼��Ϊ�ļ�")
                     << tr("���ļ������䷽��")<< tr("���浱ǰ�䷽")<< tr("����ȫ���䷽")
                     << tr("��ǰ�䷽����")<<tr("���Ƶ�ǰ�䷽")<<tr("�����䷽��");
        }
        ui->label_2->setEnabled(true);
        ui->combo_Type->setEnabled(true);
        ui->label_3->setEnabled(false);
        ui->combo_screen->setEnabled(false);
        ui->combo_Type->clear();
        ui->combo_Type->addItems(items);
        ui->combo_Type->setCurrentIndex(0);
        ui->checkBox_X->setEnabled(false);
        ui->checkBox_Y->setEnabled(false);
		break;
        case 13:
        {
            items << tr("������������") << tr("ȷ�ϱ���") << tr("�������") 
				<< tr("�����ʷ��������") << tr("������ʷ��������");
        }
        ui->label_2->setEnabled(true);
        ui->combo_Type->setEnabled(true);
        ui->label_3->setEnabled(false);
        ui->combo_screen->setEnabled(false);
        ui->combo_Type->clear();
        ui->combo_Type->addItems(items);
        ui->combo_Type->setCurrentIndex(0);
        ui->checkBox_X->setEnabled(false);
        ui->checkBox_Y->setEnabled(false);
        break;

        case 17:
        case 18:
        {
            ui->checkBox_X->setEnabled(true);
            ui->checkBox_Y->setEnabled(true);
        }
        break;

        default:
        ui->label_2->setEnabled(false);
        ui->combo_Type->setEnabled(false);
        ui->label_3->setEnabled(false);
        ui->combo_screen->setEnabled(false);
        ui->checkBox_X->setEnabled(false);
        ui->checkBox_Y->setEnabled(false);
        break;
    }
}


void FunctionWdiget::on_checkBox_X_clicked(bool checked)
{
    if(bY == true)
    {
        ui->checkBox_X->setChecked(checked);
        bX = checked;
    }
    else
    {
        ui->checkBox_X->setChecked(true);
        bX = true;
    }
}

void FunctionWdiget::on_checkBox_Y_clicked(bool checked)
{
    if(bX == true)
    {
        ui->checkBox_Y->setChecked(checked);
        bY = checked;
    }
    else
    {
        ui->checkBox_Y->setChecked(true);
        bY = true;
    }
}

void FunctionWdiget::FunTranslation(int index)
{
    switch(index)
    {
        case 0://�����ƿ���
        {
            ui->label_4->setText(tr("�����������ƿ��͹�"));
        }
        break;

        case 1://ϵͳ����
        {
            ui->label_4->setText(tr("��ϵͳ��������"));
        }
        break;

        case 2://��������ʱ��
        {
            ui->label_4->setText(tr("���ö�ý�������ʱ��"));
        }
        break;

        case 3://����ϵͳʱ��
        {
            ui->label_4->setText(tr("�޸Ļ����ĵ�ǰʱ��"));
        }
        break;

        case 4://�л���ǰ�û�
        {
            ui->label_4->setText(tr("�л��û�"));
        }
        break;

        case 5://�û�����
        {
            ui->label_4->setText(tr("�����û�����Ȩ��"));
        }
        break;

        case 6://������������
        {
            ui->label_4->setText(tr("�򿪣��رմ�������"));
        }
        break;

        case 7://�������
        {
            ui->label_4->setText(tr("��ϵͳĬ�������"));
        }
        break;

        case 8://�����л�
        {
            ui->label_4->setText(tr("ʹ�����ϵĶ����Կؼ���ʾ�趨������"));
        }
        break;

        case 9://��Ļ��ͼ
        {
            ui->label_4->setText(tr("��ȡ��ǰ��Ļ����ʾ����ΪͼƬ"));
        }
        break;

        case 10://���ڲ���
        {
            ui->label_4->setText(tr("�趨ָ�����ڴ򿪻��߹ر�"));
        }
        break;

        case 11://�����ʷ����
        {
            ui->label_4->setText(tr("�����ʷ���ݲɼ����ɼ���������"));
        }
        break;

        case 12://�䷽����
        {
            ui->label_4->setText(tr("���䷽�½���ɾ�������룬���������棬д��ȹ��ܵĿ���"));
        }
        break;

        case 13://��������
        {
            ui->label_4->setText(tr("�Ա����ĵ����������ȷ�ϣ������Ŀ���"));
        }
        break;

        case 14://�޸ĵ�ǰ�û�����
        {
            ui->label_4->setText(tr("�޸ĵ�ǰʹ���û�������"));
        }
        break;

        case 15://ע����ǰ�û�
        {
            ui->label_4->setText(tr("ע����ǰ�û�"));
        }
        break;

        case 16://�����������
        {
            ui->label_4->setText(tr("�����磬������������ݴ���"));
        }
        break;

        case 17://���߷Ŵ�
        {
            ui->label_4->setText(tr("��������X,Y�ᣬ�����߽��зŴ�"));
        }
        break;

        case 18://������С
        {
            ui->label_4->setText(tr("��������X,Y�ᣬ�����߽�����С"));
        }
        break;

        case 19://WiFi����
        {
            ui->label_4->setText(tr("��WiFi����"));
        }
        break;

        case 20://���ʼ�
        {
            ui->label_4->setText(tr("�����ʼ���ָ����ַ"));
        }
        break;

        case 21://����Զ�̷���
        {
            ui->label_4->setText(tr("����Զ�̷�����"));
        }
        break;

        case 22://�ر�Զ�̷���
        {
            ui->label_4->setText(tr("�ر�Զ�̷�����"));
        }
        break;

        case 23://��̫������
        {
            ui->label_4->setText(tr("������̫������"));
        }
        break;
        case 24://��ӡ������
        {
            ui->label_4->setText(tr("���ô�ӡ������"));
        }
        break;
        case 25://ϵͳ����
        {
            ui->label_4->setText(tr("����ϵͳ����"));
        }
        break;
        case 26://��������
        {
            ui->label_4->setText(tr("���ص�����ϵͳ��������"));
        }
        break;
        default:
        {
            ui->label_4->setText(tr("�����������ƿ��͹�"));
        }
        break;
    }
}
