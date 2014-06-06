#include "qnewprodlg.h"
#include  "Frame\mainwindow.h"
extern MainWindow *pwnd;

QNewProDlg::QNewProDlg(QWidget *parent) :
    QWizard(parent)
{
   /**********�������ҳ��***********/
    newprowizard=new QNewProjectWizard(this);
    newlinkwizard=new QNewLinkWizard(this);
    //newscreenwizard=new QNewScreenWizard(this);
    setPage(Page_NewProWizard, newprowizard);
    setPage(Page_NewLinkWizard, newlinkwizard);
    //setPage(Page_NewScreenWizard, newscreenwizard);
    //this->setStyleSheet(QString("background:#d4d0c8"));
    resize(450,450);
    //resize(630,600);

    setOption(QWizard::NoBackButtonOnStartPage, true);
    setWindowTitle(tr("����Ŀ"));
	setFixedSize(size());
    setButtonText(QWizard::NextButton,tr("��һ��"));
    setButtonText(QWizard::BackButton,tr("��һ��"));
    setButtonText(QWizard::CancelButton,tr("ȡ��"));
    setButtonText(QWizard::FinishButton,tr("���"));
    QFont font;
    font = this->font();
    font.setPointSizeF(8.5);
    switch(QSysInfo::windowsVersion())
    {
    case QSysInfo::WV_WINDOWS7://����win7ĳЩ����������ʾ��ȫ
        {
            setWizardStyle(QWizard::AeroStyle);
            setFont(font);
        }
        break;
    default:
        break;
    }
    connect(this,SIGNAL(currentIdChanged(int)),SLOT(setSubTitle(int)));

  }

/*****************����ҳ���򵼵ı���******************/
void QNewProDlg::setSubTitle(int id)
{
    if(currentId()==Page_NewLinkWizard)
    {
        setWindowTitle(tr("ͨ������"));
    }
    else if(currentId() == Page_NewProWizard)
    {
        setWindowTitle(tr("����Ŀ"));
    }
    //else if(currentId()==Page_NewScreenWizard)
    //{
    //    setWindowTitle(tr("�½�����"));
    //}
}

void QNewProDlg::cleanupPage(int id)
{
    pwnd->isHave=false;
    pwnd->is_Save=true;
}

/*****************�������ɰ�ťʱ�����½����������******************/
bool QNewProDlg::validateCurrentPage()
{
    initTreeHMIUserPage();
    initHMIPrinter();
    initCom();//��ʼ��com1����
/*********���½���Ŀ�򵼵�һ��ҳ������ݱ���*********/
    if(currentId()==Page_NewProWizard)
    {
        if(newprowizard->ui->newprojectwizard_name->text()=="")
        {
            QMessageBox box(QMessageBox::Warning,tr("����"),tr("�����빤�̵�����"),QMessageBox::NoButton,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
            box.exec();
            return 0;
        }
        if(newprowizard->ui->HMImodel->currentText()=="")
        {
            QMessageBox box(QMessageBox::Warning,tr("����"),tr("�������ͺ�"),QMessageBox::NoButton,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
            box.exec();
            return 0;
        }
        QString file_name=QString("%1\%2."LOWER_CASE_PRO_NAME).arg(newprowizard->ui->newpro_label_pos->text()).arg(newprowizard->ui->newprojectwizard_name->text());
        QFile file(file_name);
        if(file.exists())
        {
            /*QMessageBox box(QMessageBox::Warning,tr("����"),tr("�ļ��Ѿ����ڣ�"),QMessageBox::NoButton, this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
            box.exec();
            return 0;*/
            QMessageBox box(QMessageBox::Warning,tr("����"),tr("�ļ��Ѿ����ڣ��Ƿ񸲸ǣ�"),QMessageBox::Ok|QMessageBox::No,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("��"));
            box.button(QMessageBox::No)->setText(tr("��"));
            box.exec();
            if(box.clickedButton()== box.button(QMessageBox::No))
            {
                return 0;
            }
        }
        pwnd->newpro->newprowizard_name= newprowizard->ui->newprojectwizard_name->text();
        pwnd->newpro->newprowizard_path= newprowizard->ui->newpro_label_pos->text();
        pwnd->newpro->newprowizard_model=newprowizard->ui->HMImodel->currentText();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelName = pwnd->newpro->newprowizard_model;
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom1 = newprowizard->ui->com1->text();//com��
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom2 = newprowizard->ui->com2->text();//CAN����
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strMaxscreennumber = newprowizard->ui->maxscreennumber->text();//��̫��

        //�����ͺŸ�ֵ���Ŀ���resolution
        QString strwh = newprowizard->ui->resolution->text();
        QString strW  = strwh.split("x").at(0);
        strwh = strwh.split("x").at(1);
        QString strH  = strwh.split(" ").at(0);
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth = strW.toInt();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight = strH.toInt();

        pwnd->newpro->newprowizard_showmodel=newprowizard->ui->showmodel->currentText();
        pwnd->newpro->newprowizard_showmodel_maxscreennum=newprowizard->ui->maxscreennumber->text();
        pwnd->m_pSamSysParame->m_projectProp.nDisplayMode=newprowizard->ui->showmodel->currentIndex();//��ʾģʽ
        //QString model=pwnd->GetHMIConnectInformation(pwnd->newpro->newprowizard_model);
        newlinkwizard->ui->newlinkwizard_linkport_combobox->clear();
        int comNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom1.count("com");
        for(int i = 0; i < comNum; i++)
        {
            newlinkwizard->ui->newlinkwizard_linkport_combobox->addItem("COM" + QString::number(i + 1));
        }
        if(!pwnd->m_pSamSysParame->m_mixGlobalVar.m_strMaxscreennumber.contains("Ethernet(NONE)"))
        {
            newlinkwizard->ui->newlinkwizard_linkport_combobox->addItem(tr("��̫��"));
        }
        if(!pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom2.contains("NONE"))//CAN����
        {
            newlinkwizard->ui->newlinkwizard_linkport_combobox->addItem(tr("CAN����"));
        }

        return  1;
    }

    /*********���½������򵼵�2��ҳ������ݱ���*********/
    else if(currentId()==Page_NewLinkWizard)
    {
        if(newlinkwizard->ui->newlinkwizard_linkport_combobox_2->currentText() == "")
        {
            QMessageBox::about(this, tr("����"), tr("����û��������"));
            return 0;
        }

        if(newlinkwizard->ui->newlinkwizard_linkport_lineEdit->text() == "")
        {
            QMessageBox::about(this, tr("����"), tr("����дһ������"));
            return 0;
        }

        pwnd->newpro->newlinkwizard_connection=newlinkwizard->ui->newlinkwizard_linknum_label->text();
        pwnd->newpro->newlinkwizard_linkname=newlinkwizard->ui->newlinkwizard_linkname_lineedit->text();
        pwnd->newpro->newlinkwizard_linkdevice= "";//newlinkwizard->ui->newlinkwizard_device_combobox->currentText();
        pwnd->newpro->newlinkwizard_linkserver=newlinkwizard->ui->newlinkwizard_server_combobox->currentText();
        pwnd->newpro->newlinkwizard_plcaddress=newlinkwizard->ui->newlinkwizard_plcaddress_combobox->currentText();
        pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nConnectPort=newlinkwizard->ui->newlinkwizard_linkport_combobox->currentIndex();
        ////�½����̵�ʱ���ʼ��com2�������Ϣ edit zhy
        pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sDiviceType= "";
             //newlinkwizard->ui->newlinkwizard_device_combobox->currentText();
        pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sDiviceModel= "";
             //newlinkwizard->ui->newlinkwizard_server_combobox->currentText();
        /*if(newlinkwizard->ui->newlinkwizard_device_combobox->currentText()=="")
        {
            QMessageBox box(QMessageBox::Warning,tr("����"),tr("�������豸����"),QMessageBox::NoButton,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
            box.exec();
            return 0;
        }*/

        //������ҳ��ĳ�ʼ��
        pwnd->newpro->newscreenwizard_name = tr("����1");
        pwnd->newpro->newscreenwizard_bk = QColor(192,192,192);
        pwnd->newpro->newscreenwizard_frontcolor = QColor(192,192,192);
        pwnd->newpro->newscreenwizard_style=1;
        pwnd->newpro->newscreenwizard_picturepath=tr("");
        pwnd->newpro->ischeck_slience=true;
        pwnd->newpro->ischeck_picture=false;
        pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nPlcAddrInterval=newlinkwizard->ui->newlinkwizard_plcaddress_combobox->currentText().toInt();
        pwnd-> initRecipeDlg();//��ʼ���䷽�Ի���
        pwnd->isHave=true;
        pwnd->is_Is=false;
        pwnd->is_Save=false;
        pwnd->openInit_MenuAndTool();
        pwnd->ui->action_copym->setDisabled(true);//���ظ���ֻ�ڳ���ѡ�񵥸�����Ч
        //pwnd->tree->expandAll();
        pwnd->tree0->expandAll();

        pwnd->nActiveSheetIndex=0; //��ǰ������ţ���0��ʼ
        QString temp = QString("%1%2%3").arg(0/100).arg((0%100)/10).arg(0%10);
        pwnd->newScreen[0]=new QTreeWidgetItem(pwnd->screen,QStringList(temp+":"+pwnd->newpro->newscreenwizard_name));
        pwnd->screen->addChild(pwnd->newScreen[0]);
        pwnd->DrawScreenSize(); //���Ƴ���
        pwnd->pSceneSheet[0]->sNewScreenName    = tr("����1");
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

        //changed by zqh on 2011.8.10
        //QString sss = VERSION_NAME+QString("--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(pwnd->newpro->newscreenwizard_name);
        //pwnd->setWindowTitle(sss);
        pwnd->m_pSamSysParame->m_qvcInitMaroProp.clear();//��ճ�ʼ����
        pwnd->m_pSamSysParame->m_qvcGlobalMaroProp.clear();//��ճ�ʼ����

        /*//�Թ�����Ĳ���
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

        return  1;
     }

    /*********���½������򵼵�3��ҳ������ݱ���*********/
    /*else if(currentId()==Page_NewScreenWizard)
    {
        if(newscreenwizard->ui->newscreen_name_lineedit->text()=="")
        {
            QMessageBox box(QMessageBox::Warning,tr("����"),tr("�����뻭�������"),QMessageBox::NoButton,
                            this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
            box.exec();
            return 0;
        }
        if(newscreenwizard->ui->newscreen_picture_radiobutton->isChecked())
        {
            if(newscreenwizard->ui->newscreen_picture_lineedit->text()=="")
            {
                QMessageBox box(this);
                box.setText(tr("��ѡ��һ��ͼƬ��"));
                QPushButton *button = new QPushButton(tr("ȷ��"),this);
                box.addButton(button,QMessageBox::AcceptRole);
                box.exec();
                return 0;
            }
        }
        pwnd->newpro->newscreenwizard_name=newscreenwizard->ui->newscreen_name_lineedit->text();
        QPalette  pal=newscreenwizard->ui->newscreen_pushButton_bk->palette();
        QColor col=pal.color(QPalette::Button);
        pwnd->newpro->newscreenwizard_bk=col;

        QPalette  pal2=newscreenwizard->ui->newscreen_pushButton_frontcolor->palette();
        QColor col2=pal2.color(QPalette::Button);
        pwnd->newpro->newscreenwizard_frontcolor=col2;

        pwnd->newpro->newscreenwizard_style=newscreenwizard->ui->newscreen_style_combobox->currentIndex();
        pwnd->newpro->newscreenwizard_picturepath=newscreenwizard->ui->newscreen_picture_lineedit->text();
        pwnd->newpro->ischeck_slience=newscreenwizard->ui->newscreen_silence_radiobutton->isChecked();
        pwnd->newpro->ischeck_picture=newscreenwizard->ui->newscreen_picture_radiobutton->isChecked();*/

        //pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nPlcAddrInterval=newlinkwizard->ui->newlinkwizard_plcaddress_combobox->currentText().toInt();

        /*pwnd-> initRecipeDlg();//��ʼ���䷽�Ի���
        pwnd->isHave=true;
        pwnd->is_Is=false;
        pwnd->is_Save=false;
        pwnd->openInit_MenuAndTool();
        pwnd->ui->action_copym->setDisabled(true);//���ظ���ֻ�ڳ���ѡ�񵥸�����Ч
        pwnd->tree->expandAll();

        //�½����ؼ�����ڶ����˵���һ���½�����
        pwnd->nActiveSheetIndex=0; //��ǰ������ţ���0��ʼ
        QString temp=QString("%1%2%3").arg(0/100).arg((0%100)/10).arg(0%10);
        pwnd->newScreen[0]=new QTreeWidgetItem(pwnd->screen,QStringList(temp+":"+pwnd->newpro->newscreenwizard_name));
        pwnd->screen->addChild(pwnd->newScreen[0]);
        pwnd->DrawScreenSize(); //���Ƴ���
        pwnd->pSceneSheet[0]->m_sceneTypeProp.sNewScreenName = newscreenwizard->ui->newscreen_name_lineedit->text();
        pwnd->pSceneSheet[0]->m_sceneBackColor = newscreenwizard->ui->newscreen_pushButton_bk->palette().color(QPalette::Background);
        pwnd->pSceneSheet[0]->m_sceneStyleColor = newscreenwizard->ui->newscreen_pushButton_frontcolor->palette().color(QPalette::Background);
        pwnd->pSceneSheet[0]->nPattern = newscreenwizard->ui->newscreen_style_combobox->currentIndex();
        pwnd->pSceneSheet[0]->m_picturePath=newscreenwizard->ui->newscreen_picture_lineedit->text();
        pwnd->pSceneSheet[0]->m_bChangePicPath = true;
        pwnd->pSceneSheet[0]->m_sceneTypeProp.nIsSceneOrWindow = 0;
        if(newscreenwizard->ui->newscreen_silence_radiobutton->isChecked())
        {
            pwnd->pSceneSheet[0]->nSelectType = 0;
        }
        else if(newscreenwizard->ui->newscreen_picture_radiobutton->isChecked())
        {
            pwnd->pSceneSheet[0]->nSelectType = 1;
        }

        pwnd->is_haveScreen=true;
        pwnd->reOpenPro();

        //changed by zqh on 2011.8.10
        QString sss = VERSION_NAME+QString("--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(pwnd->newpro->newscreenwizard_name);
        pwnd->setWindowTitle(sss);

        pwnd->m_pSamSysParame->m_qvcInitMaroProp.clear();//��ճ�ʼ����

        pwnd->m_pSamSysParame->m_qvcGlobalMaroProp.clear();//��ճ�ʼ����

        return 1;

    }*/
   return 0;
}
/*********************************************************
*��ʼ����������������-�û�ҳ������
**********************************************************/
void QNewProDlg::initTreeHMIUserPage()
{//�û�����

    pwnd->m_pSamSysParame->m_projectProp.nSetFloatType =1;
    pwnd->m_pSamSysParame->m_projectProp.nSetFloatProp =1;
    pwnd->m_pSamSysParame->m_projectProp.nNoDataCharFlag =0;
    pwnd->m_pSamSysParame->m_projectProp.nNoDataValueFlag =0;
    pwnd->m_pSamSysParame->m_projectProp.bTIPicTransparent =false;
    pwnd->m_pSamSysParame->m_projectProp.mTIPicColor = QColor(0,0,0);
    if(pwnd->m_pSamSysParame->m_projectProp.sBackupForNewVer.size()>7)
    {
        pwnd->m_pSamSysParame->m_projectProp.sBackupForNewVer[3] = tr("����");
    }//��ʼ��������һ����������ϵͳ������������
}
/*********************************************************
*��ʼ����������������-��ӡ������
**********************************************************/
void QNewProDlg::initHMIPrinter()
{
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bUsePrinter =0;//������ӡ����
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.nPrinterType =0;//��ӡ���ͺ�
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintNo =0;//��ӡ���
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintTime =0;//��ӡʱ��
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintTimeEx =0;//��ӡ��չʱ��(D:H:M)
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintStandTime =0;//��ӡ��׼ʱ��(H:M:S)
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintPricesTime =0;//��ӡ��ȷʱ��(H:M:S:MS)
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintDate =0;//��ӡ����
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintDateEx =0;//��ӡ��չ����(YYYY-MM-DD)
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintCheckError =0;//��鴰�ڴ���
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.bPrintCharModel =0;//�ַ�ģʽ��ӡ
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.nPrintPort =0;//��ӡ���˿�
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.nPrintBaud =0;//������
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.nDataBit =0;//����λ
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.nStopBit =0;//ֹͣλ
    pwnd->m_pSamSysParame->m_projectProp.mPrinterProp.nCheckOe =0;//��żУ��
}
/*********************************************************
*��ʼ�����ؼ��ļ������Ի���
**********************************************************/
void QNewProDlg::initTreeFileProtectDlg()
{
    pwnd->m_pSamSysParame->m_fileProtect.bNeedFileProtect =false;
    pwnd->m_pSamSysParame->m_fileProtect.sProtectPWD ="";

}//

//��ʼ�����ؼ����ԶԻ���
void QNewProDlg::initTreeLanguageDlg()
{
    //��������
   pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum=0;
   pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.clear();
   pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.push_back(tr("����"));

   pwnd->qLanguagecmb->clear();
   pwnd->qLanguagecmb->addItem(tr("����")); //new add by zqh on 2012-02-7
   pwnd->qLanguagecmb->setEnabled(false);
}//
//��ʼ��COM1��Ϣ
void QNewProDlg::initCom()
{
    //��ɶ�com1���ݵĳ�ʼ��
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nCommunicateTime=20;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nRetryTime=3;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nPlcAddrInterval=6;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nAddrType=0;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sDiviceType="";//newlinkwizard->ui->newlinkwizard_device_combobox->currentText();
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sDiviceModel=newlinkwizard->ui->newlinkwizard_server_combobox->currentText();
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sConnectName=newlinkwizard->ui->newlinkwizard_linkname_lineedit->text();
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nHmiLocation=0;//0-���� 1-Զ��
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nFwConnectType=0;//��͸Ӧ���е����ӷ�ʽ 0Ϊֱ������ 1Ϊ��̫�� ��������
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nFwFromStationId=1;  //��͸Ӧ���еĴ�վID
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sInternetIpAddr="0.0.0.0";//ѡ������̫������ʱ���IP��ַ;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sInternetPort="8000";     //ѡ������̫������ʱ��Ķ˿ں�=0;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sFwIpAddr="0.0.0.0";      //��͸Ӧ��������̫������ʱ���IP��ַ=0;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sFwPort="8000";           //��͸Ӧ��������̫������ʱ��Ķ˿ں�=0;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nTimeout1=1000;           //��ʱʱ��1;
    pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].nTimeout2=5;           //��ʱʱ��2;
    for(int i=0;i<4;i++)
    {
        pwnd->m_pSamSysParame->m_qvcPlcCommunicate[0].sDataBakeup.append("0");//��ʼ��Ĭ�ϲ���0
    }

  }
