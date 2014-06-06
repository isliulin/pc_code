#include "qnewprodlgex.h"
#include "ui_qnewprodlgex.h"

#include  "Frame\mainwindow.h"
extern MainWindow *pwnd;

qNewProDlgEx::qNewProDlgEx(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qNewProDlgEx)
{
    ui->setupUi(this);
    newprowizard = new QNewProjectWizard(this);
    newlinkwizard = new QNewLinkWizard(this);
    newprowizard->setVisible(true);
    newlinkwizard->setVisible(false);
    this->setWindowTitle(tr("新项目"));
    ui->pushButton_Pre->setVisible(false);
    ui->pushButton_Done->setVisible(false);
    //ui->pushButton_Next->setFocus();
    ui->pushButton_Next->setDefault(true);
    newprowizard->ui->newprojectwizard_name->setFocus();
#ifdef AKPLC//是一体机
    ui->pushButton_Next->setText(tr("完成"));
#endif
}

qNewProDlgEx::~qNewProDlgEx()
{
    delete ui;
}
void qNewProDlgEx::on_pushButton_Cancel_clicked()
{
    pwnd->isHave=false;
    pwnd->is_Save=true;
    QDialog::reject();
}

void qNewProDlgEx::closeEvent(QCloseEvent * event)
{
    pwnd->isHave=false;
    pwnd->is_Save=true;
}

void qNewProDlgEx::on_pushButton_Done_clicked()
{
    initTreeHMIUserPage();
    initHMIPrinter();
    initCom();

    if(newlinkwizard->ui->newlinkwizard_linkport_combobox_2->currentText() == "")
    {
        QMessageBox::about(this, tr("警告"), tr("不能没有制造商"));
        return;
    }

    if(newlinkwizard->ui->newlinkwizard_linkport_lineEdit->text() == "")
    {
        QMessageBox::about(this, tr("警告"), tr("请填写一个名称"));
        newlinkwizard->ui->newlinkwizard_linkport_lineEdit->setFocus();
        return;
    }

    pwnd->newpro->newlinkwizard_connection=newlinkwizard->ui->newlinkwizard_linknum_label->text();
    pwnd->newpro->newlinkwizard_linkname=newlinkwizard->ui->newlinkwizard_linkname_lineedit->text();
    pwnd->newpro->newlinkwizard_linkdevice= "";
    pwnd->newpro->newlinkwizard_linkserver=newlinkwizard->ui->newlinkwizard_server_combobox->currentText();
    pwnd->newpro->newlinkwizard_plcaddress=newlinkwizard->ui->newlinkwizard_plcaddress_combobox->currentText();
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nConnectPort=newlinkwizard->ui->newlinkwizard_linkport_combobox->currentIndex();
    ////新建工程的时候初始化com2的相关信息 edit zhy
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sDiviceType= "";
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sDiviceModel= "";

    //第三个页面的初始化
    pwnd->newpro->newscreenwizard_name = tr("画面1");
    pwnd->newpro->newscreenwizard_bk = QColor(192,192,192);
    pwnd->newpro->newscreenwizard_frontcolor = QColor(192,192,192);
    pwnd->newpro->newscreenwizard_style=1;
    pwnd->newpro->newscreenwizard_picturepath=tr("");
    pwnd->newpro->ischeck_slience=true;
    pwnd->newpro->ischeck_picture=false;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nPlcAddrInterval=newlinkwizard->ui->newlinkwizard_plcaddress_combobox->currentText().toInt();
    pwnd-> initRecipeDlg();//初始化配方对话框
    pwnd->isHave=true;
    pwnd->is_Is=false;
    pwnd->is_Save=false;
    pwnd->is_NeedCompiled = true;
    pwnd->openInit_MenuAndTool();
    pwnd->ui->action_copym->setDisabled(true);//多重复制只在场景选择单个才有效
    pwnd->tree0->expandAll();

    pwnd->nActiveSheetIndex=0; //当前画面序号，从0开始
    QString temp = QString("%1%2%3").arg(0/100).arg((0%100)/10).arg(0%10);
    pwnd->newScreen[0]=new QTreeWidgetItem(pwnd->screen,QStringList(temp+":"+pwnd->newpro->newscreenwizard_name));
    pwnd->screen->addChild(pwnd->newScreen[0]);
    pwnd->DrawScreenSize(); //绘制场景
    pwnd->pSceneSheet[0]->sNewScreenName    = tr("画面1");
    pwnd->pSceneSheet[0]->sNumberName       = tr("000");
    pwnd->pSceneSheet[0]->m_sceneBackColor  = pwnd->newpro->newscreenwizard_bk;
    pwnd->pSceneSheet[0]->m_sceneStyleColor = pwnd->newpro->newscreenwizard_frontcolor;
    pwnd->pSceneSheet[0]->nPattern          = 0;
    pwnd->pSceneSheet[0]->m_picturePath     = tr("");
    pwnd->pSceneSheet[0]->m_bChangePicPath  = true;
    pwnd->pSceneSheet[0]->nIsSceneOrWindow  = 0;
    pwnd->pSceneSheet[0]->nSelectType       = 0;
    pwnd->pSceneSheet[0]->bIsAddMenu        = true;
    pwnd->pSceneSheet[0]->bSlide            = true;
    pwnd->pSceneSheet[0]->nTowardLeftId     = 1;
    pwnd->pSceneSheet[0]->nTowardRIghtId    = 1;
    pwnd->pSceneSheet[0]->nSlideStyle       = 1;
    pwnd->pSceneSheet[0]->listScript.clear();

    pwnd->is_haveScreen=true;
    pwnd->reOpenPro();

    pwnd->m_pSamSysParame->m_qvcInitMaroProp.clear();//清空初始化宏
    pwnd->m_pSamSysParame->m_qvcGlobalMaroProp.clear();//清空初始化宏

    /*//对工具箱的操作
    pwnd->ui->toolBox->setVisible(true);
    pwnd->ui->dockWidget->setVisible(true);

    pwnd->ui->dockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
    pwnd->ui->dockWidget->setFloating(true);
    QRect  rcdock =  pwnd->geometry();
    pwnd->ui->dockWidget->setGeometry(rcdock.right()-181,120,161,291);
    pwnd->ui->dockWidget->setFixedSize(161,291);*/

    pwnd->m_rightDock->setVisible(false);
    pwnd->ui->action_41->setChecked(false);
    pwnd->m_toolDock->setVisible(true);
    pwnd->ui->action_tool->setChecked(true);

    pwnd->newpro->proFlag = newlinkwizard->ui->newlinkwizard_linkport_combobox->currentText();
    pwnd->newpro->sName = newlinkwizard->ui->newlinkwizard_linkport_lineEdit->text();
    pwnd->newpro->sFactoryName = newlinkwizard->ui->newlinkwizard_linkport_combobox_2->currentText();
    pwnd->newpro->sProtocolName = newlinkwizard->ui->newlinkwizard_linkport_combobox_3->currentText();

    QDialog::accept();
}

void qNewProDlgEx::on_pushButton_Next_clicked()
{
    initTreeHMIUserPage();
    initHMIPrinter();
    initCom();

    if(newprowizard->ui->newprojectwizard_name->text()=="")
    {
        QMessageBox box(QMessageBox::Warning,tr("警告"),tr("请输入工程的名字"),QMessageBox::NoButton,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        newprowizard->ui->newprojectwizard_name->setFocus();
        return;
    }
    if(newprowizard->ui->HMImodel->currentText()=="")
    {
        QMessageBox box(QMessageBox::Warning,tr("警告"),tr("请输入型号"),QMessageBox::NoButton,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }
    //wxy 判断工程路径是否正确，避免做好工程无法保存的问题
    QString file_Text= QString("%1\%2a."LOWER_CASE_PRO_NAME).arg(newprowizard->ui->newpro_label_pos->text()).arg(newprowizard->ui->newprojectwizard_name->text());
    QFile fileTemp(file_Text);
    bool bOpenSuccess = fileTemp.open(QIODevice::WriteOnly);
    if(!bOpenSuccess)
    {
        QMessageBox::warning(this,tr("创建文件出错"),tr("请检查路径是否正确或者规范"));
        fileTemp.close();
        newprowizard->ui->newprojectwizard_name->setFocus();
        return;
    }
    else
    {
        fileTemp.close();
        QFile::remove(file_Text);
    }

    QString file_name=QString("%1\%2."LOWER_CASE_PRO_NAME).arg(newprowizard->ui->newpro_label_pos->text()).arg(newprowizard->ui->newprojectwizard_name->text());
    QFile file(file_name);
    if(file.exists())
    {
        QMessageBox box(QMessageBox::Warning,tr("警告"),tr("文件已经存在，是否覆盖？"),QMessageBox::Ok|QMessageBox::No,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("是"));
        box.button(QMessageBox::No)->setText(tr("否"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::No))
        {
            return;
        }
    }
    pwnd->newpro->newprowizard_name= newprowizard->ui->newprojectwizard_name->text();
    pwnd->newpro->newprowizard_path= newprowizard->ui->newpro_label_pos->text();
    pwnd->newpro->newprowizard_model=newprowizard->ui->HMImodel->currentText();
    pwnd->newpro->HMI_Name         = newprowizard->ui->HMI_Name->text();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelName = pwnd->newpro->newprowizard_model;
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strHmiName   = pwnd->newpro->HMI_Name;
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom1 = newprowizard->ui->com1->text();//com口
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom2 = newprowizard->ui->com2->text();//CAN总线
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strMaxscreennumber = newprowizard->ui->maxscreennumber->text();//以太网

    //根据型号赋值屏的宽，高resolution
    QString strwh = newprowizard->ui->resolution->text();
    QString strW  = strwh.split("x").at(0);
    strwh = strwh.split("x").at(1);
    QString strH  = strwh.split(" ").at(0);
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth = strW.toInt();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight = strH.toInt();

    pwnd->newpro->newprowizard_showmodel=newprowizard->ui->showmodel->currentText();
    pwnd->newpro->newprowizard_showmodel_maxscreennum=newprowizard->ui->maxscreennumber->text();
    pwnd->m_pSamSysParame->m_projectProp.nDisplayMode=newprowizard->ui->showmodel->currentIndex();//显示模式
    newlinkwizard->ui->newlinkwizard_linkport_combobox->clear();
    int comNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom1.count("com");
    for(int i = 0; i < comNum; i++)
    {
        newlinkwizard->ui->newlinkwizard_linkport_combobox->addItem("COM" + QString::number(i + 1));
    }
    if(!pwnd->m_pSamSysParame->m_mixGlobalVar.m_strMaxscreennumber.contains("Ethernet(NONE)"))
    {
        newlinkwizard->ui->newlinkwizard_linkport_combobox->addItem(tr("以太网"));
    }
    if(!pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom2.contains("NONE"))//CAN总线
    {
        newlinkwizard->ui->newlinkwizard_linkport_combobox->addItem(tr("CAN总线"));
    }
#ifndef AKPLC
    setWindowTitle(tr("通信连接"));
    newprowizard->setVisible(false);
    newlinkwizard->setVisible(true);
    ui->pushButton_Next->setVisible(false);
    ui->pushButton_Pre->setVisible(true);
    ui->pushButton_Done->setVisible(true);

    //ui->pushButton_Done->setFocus();
    ui->pushButton_Done->setDefault(true);
    newlinkwizard->ui->newlinkwizard_linkport_lineEdit->setFocus();
#else
    pwnd->newpro->newlinkwizard_connection="1";//newlinkwizard->ui->newlinkwizard_linknum_label->text();
    pwnd->newpro->newlinkwizard_linkname="";//newlinkwizard->ui->newlinkwizard_linkname_lineedit->text();
    pwnd->newpro->newlinkwizard_linkdevice= "";//newlinkwizard->ui->newlinkwizard_device_combobox->currentText();
    pwnd->newpro->newlinkwizard_linkserver="";//newlinkwizard->ui->newlinkwizard_server_combobox->currentText();
    pwnd->newpro->newlinkwizard_plcaddress="32";//newlinkwizard->ui->newlinkwizard_plcaddress_combobox->currentText();
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nConnectPort=6;//newlinkwizard->ui->newlinkwizard_linkport_combobox->currentIndex();
    ////新建工程的时候初始化com2的相关信息 edit zhy
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sDiviceType= "";
         //newlinkwizard->ui->newlinkwizard_device_combobox->currentText();
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sDiviceModel= "";

    //第三个页面的初始化
    pwnd->newpro->newscreenwizard_name = tr("画面1");
    pwnd->newpro->newscreenwizard_bk = QColor(192,192,192);
    pwnd->newpro->newscreenwizard_frontcolor = QColor(192,192,192);
    pwnd->newpro->newscreenwizard_style=1;
    pwnd->newpro->newscreenwizard_picturepath=tr("");
    //

    pwnd->newpro->ischeck_slience=true;
    pwnd->newpro->ischeck_picture=false;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nPlcAddrInterval=32;
    pwnd->initRecipeDlg();//初始化配方对话框
    pwnd->isHave=true;
    pwnd->is_Is=false;
    pwnd->is_Save=false;
    pwnd->openInit_MenuAndTool();
    pwnd->ui->action_copym->setDisabled(true);//多重复制只在场景选择单个才有效
    pwnd->tree0->expandAll();

    pwnd->nActiveSheetIndex=0; //当前画面序号，从0开始
    QString temp = QString("%1%2%3").arg(0/100).arg((0%100)/10).arg(0%10);
    pwnd->newScreen[0]=new QTreeWidgetItem(pwnd->screen,QStringList(temp+":"+pwnd->newpro->newscreenwizard_name));
    pwnd->screen->addChild(pwnd->newScreen[0]);
    pwnd->DrawScreenSize(); //绘制场景
    pwnd->pSceneSheet[0]->sNewScreenName    = tr("画面1");
    pwnd->pSceneSheet[0]->sNumberName       = tr("000");
    pwnd->pSceneSheet[0]->m_sceneBackColor  = pwnd->newpro->newscreenwizard_bk;
    pwnd->pSceneSheet[0]->m_sceneStyleColor = pwnd->newpro->newscreenwizard_frontcolor;
    pwnd->pSceneSheet[0]->nPattern          = 0;
    pwnd->pSceneSheet[0]->m_picturePath     = tr("");
    pwnd->pSceneSheet[0]->m_bChangePicPath  = true;
    pwnd->pSceneSheet[0]->nIsSceneOrWindow  = 0;
    pwnd->pSceneSheet[0]->nSelectType       = 0;
    pwnd->pSceneSheet[0]->bIsAddMenu        = true;
    pwnd->pSceneSheet[0]->bSlide            = true;
    pwnd->pSceneSheet[0]->nTowardLeftId     = 1;
    pwnd->pSceneSheet[0]->nTowardRIghtId    = 1;
    pwnd->pSceneSheet[0]->nSlideStyle       = 1;
    pwnd->pSceneSheet[0]->listScript.clear();

    pwnd->is_haveScreen=true;
    pwnd->reOpenPro();

    pwnd->m_pSamSysParame->m_qvcInitMaroProp.clear();//清空初始化宏
    pwnd->m_pSamSysParame->m_qvcGlobalMaroProp.clear();//清空初始化宏

    pwnd->m_rightDock->setVisible(false);
    pwnd->ui->action_41->setChecked(false);
    pwnd->m_toolDock->setVisible(true);
    pwnd->ui->action_tool->setChecked(true);

    pwnd->newpro->proFlag = "COM1";//newlinkwizard->ui->newlinkwizard_linkport_combobox->currentText();
    pwnd->newpro->sName = "samkoon";//newlinkwizard->ui->newlinkwizard_linkport_lineEdit->text();
    pwnd->newpro->sFactoryName = "samkoon";//newlinkwizard->ui->newlinkwizard_linkport_combobox_2->currentText();
    pwnd->newpro->sProtocolName = "samkoon_fgs_32mr";//newlinkwizard->ui->newlinkwizard_linkport_combobox_3->currentText();

    QDialog::accept();
#endif
}

void qNewProDlgEx::on_pushButton_Pre_clicked()
{
    setWindowTitle(tr("新项目"));
    newprowizard->setVisible(true);
    newlinkwizard->setVisible(false);
    ui->pushButton_Next->setVisible(true);
    //ui->pushButton_Next->setFocus();
    ui->pushButton_Next->setDefault(true);
    ui->pushButton_Pre->setVisible(false);
    ui->pushButton_Done->setVisible(false);
    newprowizard->ui->newprojectwizard_name->setFocus();
}

/*********************************************************
*初始化触摸屏参数设置-用户页面设置
**********************************************************/
void qNewProDlgEx::initTreeHMIUserPage()
{//用户界面

    pwnd->m_pSamSysParame->m_projectProp.nSetFloatType =1;
    pwnd->m_pSamSysParame->m_projectProp.nSetFloatProp =1;
    pwnd->m_pSamSysParame->m_projectProp.nNoDataCharFlag =0;
    pwnd->m_pSamSysParame->m_projectProp.nNoDataValueFlag =0;
    pwnd->m_pSamSysParame->m_projectProp.bTIPicTransparent =false;
    pwnd->m_pSamSysParame->m_projectProp.mTIPicColor = QColor(0,0,0);
    if(pwnd->m_pSamSysParame->m_projectProp.sBackupForNewVer.size()>7)
    {
        pwnd->m_pSamSysParame->m_projectProp.sBackupForNewVer[3] = tr("宋体");
    }//初始化触摸屏一般设置里面系统报警文字字体
}
/*********************************************************
*初始化触摸屏参数设置-打印机设置
**********************************************************/
void qNewProDlgEx::initHMIPrinter()
{
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bUsePrinter =0;//开启打印功能
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.nPrinterType =0;//打印机型号
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintNo =0;//打印序号
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintTime =0;//打印时间
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintTimeEx =0;//打印扩展时间(D:H:M)
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintStandTime =0;//打印标准时间(H:M:S)
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintPricesTime =0;//打印精确时间(H:M:S:MS)
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintDate =0;//打印日期
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintDateEx =0;//打印扩展日期(YYYY-MM-DD)
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintCheckError =0;//检查窗口错误
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintCharModel =0;//字符模式打印
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.nPrintPort =0;//打印机端口
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.nPrintBaud =0;//波特率
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.nDataBit =0;//数据位
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.nStopBit =0;//停止位
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.nCheckOe =0;//奇偶校验
}
/*********************************************************
*初始化树控件文件保护对话框
**********************************************************/
void qNewProDlgEx::initTreeFileProtectDlg()
{
    pwnd->m_pSamSysParame->m_fileProtect.bNeedFileProtect =false;
    pwnd->m_pSamSysParame->m_fileProtect.sProtectPWD ="";

}//

//初始化树控件语言对话框
void qNewProDlgEx::initTreeLanguageDlg()
{
    //语言总量
   pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum=0;
   pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.clear();
   pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.push_back(tr("中文"));

   pwnd->qLanguagecmb->clear();
   pwnd->qLanguagecmb->addItem(tr("中文")); //new add by zqh on 2012-02-7
   pwnd->qLanguagecmb->setEnabled(false);
}//
//初始化COM1信息
void qNewProDlgEx::initCom()
{
    //完成对com1数据的初始化
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nCommunicateTime=20;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nRetryTime=3;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nPlcAddrInterval=6;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nAddrType=0;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sDiviceType="";//newlinkwizard->ui->newlinkwizard_device_combobox->currentText();
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sDiviceModel=newlinkwizard->ui->newlinkwizard_server_combobox->currentText();
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sConnectName=newlinkwizard->ui->newlinkwizard_linkname_lineedit->text();
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nHmiLocation=0;//0-本机 1-远端
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nFwConnectType=0;//穿透应用中的连接方式 0为直连串口 1为以太网 其他备用
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nFwFromStationId=1;  //穿透应用中的从站ID
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sInternetIpAddr="0.0.0.0";//选择用以太网连接时候的IP地址;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sInternetPort="8000";     //选择用以太网连接时候的端口号=0;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sFwIpAddr="0.0.0.0";      //穿透应用中用以太网连接时候的IP地址=0;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sFwPort="8000";           //穿透应用中用以太网连接时候的端口号=0;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nTimeout1=1000;           //超时时间1;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nTimeout2=5;           //超时时间2;
    for(int i=0;i<4;i++)
    {
        pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sDataBakeup.append("0");//初始化默认参数0
    }

  }
