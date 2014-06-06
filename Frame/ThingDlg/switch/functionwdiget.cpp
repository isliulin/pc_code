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
		QMessageBox::about(ui->combo_screen, tr(""), tr("未选择要操作的窗口"));
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
            items << tr("打开窗口") << tr("关闭窗口");
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
            items << tr("编辑当前配方") << tr("新建配方") << tr("删除当前配方") << tr("删除一组配方")
                    << tr("当前配方写入PLC") << tr("从PLC读当前配方") << tr("配方组导出为文件")
                     << tr("从文件导入配方组")<< tr("保存当前配方")<< tr("导出全部配方")
                     << tr("当前配方清零")<<tr("复制当前配方")<<tr("复制配方组");
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
            items << tr("报警声音开关") << tr("确认报警") << tr("清除报警") 
				<< tr("清除历史报警数据") << tr("导出历史报警数据");
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
        case 0://背景灯开关
        {
            ui->label_4->setText(tr("控制屏背景灯开和关"));
        }
        break;

        case 1://系统重启
        {
            ui->label_4->setText(tr("让系统重新启动"));
        }
        break;

        case 2://设置屏保时间
        {
            ui->label_4->setText(tr("设置多久进入屏保时间"));
        }
        break;

        case 3://设置系统时间
        {
            ui->label_4->setText(tr("修改机器的当前时间"));
        }
        break;

        case 4://切换当前用户
        {
            ui->label_4->setText(tr("切换用户"));
        }
        break;

        case 5://用户管理
        {
            ui->label_4->setText(tr("设置用户访问权限"));
        }
        break;

        case 6://触摸声音开关
        {
            ui->label_4->setText(tr("打开，关闭触摸声音"));
        }
        break;

        case 7://打开浏览器
        {
            ui->label_4->setText(tr("打开系统默认浏览器"));
        }
        break;

        case 8://语言切换
        {
            ui->label_4->setText(tr("使界面上的多语言控件显示设定的语言"));
        }
        break;

        case 9://屏幕截图
        {
            ui->label_4->setText(tr("截取当前屏幕的显示保存为图片"));
        }
        break;

        case 10://窗口操作
        {
            ui->label_4->setText(tr("设定指定窗口打开或者关闭"));
        }
        break;

        case 11://清除历史数据
        {
            ui->label_4->setText(tr("清除历史数据采集所采集到的数据"));
        }
        break;

        case 12://配方操作
        {
            ui->label_4->setText(tr("对配方新建，删除，导入，导出，保存，写入等功能的控制"));
        }
        break;

        case 13://报警操作
        {
            ui->label_4->setText(tr("对报警的导出，清除，确认，声音的控制"));
        }
        break;

        case 14://修改当前用户密码
        {
            ui->label_4->setText(tr("修改当前使用用户的密码"));
        }
        break;

        case 15://注销当前用户
        {
            ui->label_4->setText(tr("注销当前用户"));
        }
        break;

        case 16://启动网络服务
        {
            ui->label_4->setText(tr("打开网络，用网络进行数据传输"));
        }
        break;

        case 17://曲线放大
        {
            ui->label_4->setText(tr("设置曲线X,Y轴，对曲线进行放大"));
        }
        break;

        case 18://曲线缩小
        {
            ui->label_4->setText(tr("设置曲线X,Y轴，对曲线进行缩小"));
        }
        break;

        case 19://WiFi设置
        {
            ui->label_4->setText(tr("打开WiFi功能"));
        }
        break;

        case 20://发邮件
        {
            ui->label_4->setText(tr("发送邮件到指定地址"));
        }
        break;

        case 21://启动远程服务
        {
            ui->label_4->setText(tr("启动远程服务功能"));
        }
        break;

        case 22://关闭远程服务
        {
            ui->label_4->setText(tr("关闭远程服务功能"));
        }
        break;

        case 23://以太网设置
        {
            ui->label_4->setText(tr("启动以太网设置"));
        }
        break;
        case 24://打印机设置
        {
            ui->label_4->setText(tr("设置打印机参数"));
        }
        break;
        case 25://系统设置
        {
            ui->label_4->setText(tr("设置系统参数"));
        }
        break;
        case 26://返回桌面
        {
            ui->label_4->setText(tr("返回到操作系统的主界面"));
        }
        break;
        default:
        {
            ui->label_4->setText(tr("控制屏背景灯开和关"));
        }
        break;
    }
}
