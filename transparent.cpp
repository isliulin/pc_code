#include "transparent.h"
#include <QTranslator>
extern MainWindow *pwnd;
extern QTranslator *translator;
extern bool  is_tanslator;
transparent::transparent()
{
}

void transparent::toChinese()
{

    translator->load(":/language/images/language/Ch.qm");
    translator->load(":/language/images/language/qt_zh_CN.qm");
    qApp->installTranslator(translator);
    pwnd->ui->retranslateUi(pwnd);
    translate_cn(pwnd);
    if(pwnd->newScreenDlg)
    {
        pwnd->newScreenDlg->ui->retranslateUi(pwnd->newScreenDlg);
    }

    pwnd->newWindowDlg->ui->retranslateUi(pwnd->newWindowDlg);
    pwnd->newCopyScreen->ui->retranslateUi(pwnd->newCopyScreen);
    pwnd->newCopyWindow->ui->retranslateUi(pwnd->newCopyWindow);


    //XXXXX
    /*if(pwnd->languagedlg)
    {
        pwnd->languagedlg->ui->retranslateUi(pwnd->languagedlg);
    }*/


//    if(pwnd->recipeDlg)
//    {
//        pwnd->recipeDlg->ui->retranslateUi(pwnd->recipeDlg);
//    }


    is_tanslator=0;
}

void transparent::toEnglish()
{
    translator->load(":/language/images/language/En.qm");
    qApp->installTranslator(translator);
    pwnd->ui->retranslateUi(pwnd);
    translate(pwnd);
    if(pwnd->newScreenDlg)
    {
        pwnd->newScreenDlg->ui->retranslateUi(pwnd->newScreenDlg);
    }

    pwnd->newWindowDlg->ui->retranslateUi(pwnd->newWindowDlg);
    pwnd->newCopyScreen->ui->retranslateUi(pwnd->newCopyScreen);
    pwnd->newCopyWindow->ui->retranslateUi(pwnd->newCopyWindow);


    //XXXXX
    /*if(pwnd->languagedlg)
    {
        pwnd->languagedlg->ui->retranslateUi(pwnd->languagedlg);
    }*/


//    if(pwnd->recipeDlg)
//    {
//        pwnd->recipeDlg->ui->retranslateUi(pwnd->recipeDlg);
//    }
    is_tanslator=1;
}

void transparent:: translate_cn(MainWindow *mw)
{
    mw->TreeKeyboard->setText(0,QApplication::translate("mw", "自定义键盘", 0, QApplication::CodecForTr));
    if(mw->copyUserKeyboard)
    {
       mw->copyUserKeyboard->setText(0,QApplication::translate("mw", "自定义键盘", 0, QApplication::CodecForTr));
    }
    mw->m_leftDock->setWindowTitle(QApplication::translate("mw", "窗口", 0, QApplication::CodecForTr));
    mw->m_toolDock->setWindowTitle(QApplication::translate("mw", "工具栏", 0, QApplication::CodecForTr));
    //list_style
    //mw->list_style->setItemText(0,QApplication::translate("mw", "标准列表", 0, QApplication::CodecForTr));
    //mw->list_style->setItemText(1,QApplication::translate("mw", "元件列表", 0, QApplication::CodecForTr));
    //mw->list_style->setItemText(2,QApplication::translate("mw", "预览列表", 0, QApplication::CodecForTr));
    mw->undoAction->setText(QApplication::translate("mw", "撤销", 0, QApplication::CodecForTr));
    mw->undoAction->setStatusTip(QApplication::translate("mw", "撤销所做操作", 0, QApplication::CodecForTr));
    mw->redoAction->setText(QApplication::translate("mw", "恢复", 0, QApplication::CodecForTr));
    mw->redoAction->setStatusTip(QApplication::translate("mw", "恢复撤销操作", 0, QApplication::CodecForTr));
    mw->deleteAction->setText(QApplication::translate("mw", "删除", 0, QApplication::CodecForTr));
    mw->deleteAction->setStatusTip(QApplication::translate("mw", "删除条目", 0, QApplication::CodecForTr));
    mw->lab_control_statusBar->setText(QApplication::translate("mw", "按钮名称", 0, QApplication::CodecForTr));
    mw->lab_Coordinate_statusBar->setText(QApplication::translate("mw", "控件坐标:", 0, QApplication::CodecForTr));
    mw->lab_up_statusBar->setText(QApplication::translate("mw", "上:", 0, QApplication::CodecForTr));
    mw->lab_left_statusBar->setText(QApplication::translate("mw", "左:", 0, QApplication::CodecForTr));
    mw->lab_size_statusBar->setText(QApplication::translate("mw", "控件大小:", 0, QApplication::CodecForTr));
    mw->lab_width_statusBar->setText(QApplication::translate("mw", "宽:", 0, QApplication::CodecForTr));
    mw->lab_hight_statusBar->setText(QApplication::translate("mw", "高:", 0, QApplication::CodecForTr));
#ifdef AK_SAMKOON
    mw->lab_samkoon_statusBar->setText(QApplication::translate("mw", "显控科技", 0, QApplication::CodecForTr));
#else define LA_DEBINUO
    //mw->lab_samkoon_statusBar->setText(QApplication::translate("mw", "德比诺", 0, QApplication::CodecForTr));
#endif
    //mw->lab_samkoon_statusBar->setText(QApplication::translate("mw", "显控科技", 0, QApplication::CodecForTr));
    mw->ui->statusBar->showMessage(QApplication::translate("mw", "就绪", 0, QApplication::CodecForTr) );

    mw->root->setText(0,QApplication::translate("mw", "触摸屏", 0, QApplication::CodecForTr));
    mw->root0->setText(0,QApplication::translate("mw", "窗口&画面", 0, QApplication::CodecForTr));

    mw->pMenuSpace->setTitle(QApplication::translate("mw", "间距", 0, QApplication::CodecForTr));
    QList <QAction *> actions = mw->pMenuSpace->actions();
    for(int i = 0; i < actions.size(); i++)
    {
        switch(i)
        {
        case 0:
            actions.at(0)->setText(QApplication::translate("mw", "宽度相同", 0, QApplication::CodecForTr));
            break;
        case 1:
            actions.at(1)->setText(QApplication::translate("mw", "高度相同", 0, QApplication::CodecForTr));
            break;
        case 2:
            actions.at(2)->setText(QApplication::translate("mw", "宽度高度都相同", 0, QApplication::CodecForTr));
            break;
        case 3:
            actions.at(3)->setText(QApplication::translate("mw", "水平等间距", 0, QApplication::CodecForTr));
            break;
        case 4:
            actions.at(4)->setText(QApplication::translate("mw", "垂直等间距", 0, QApplication::CodecForTr));
            break;
        default:
            break;
        }
    }

    actions.clear();
    actions = mw->pMenuAlign->actions();
    mw->pMenuAlign->setTitle(QApplication::translate("mw", "对齐", 0, QApplication::CodecForTr));
    for(int i = 0; i < actions.size(); i++)
    {
        switch(i)
        {
        case 0:
            actions.at(0)->setText(QApplication::translate("mw", "左对齐", 0, QApplication::CodecForTr));
            break;
        case 1:
            actions.at(1)->setText(QApplication::translate("mw", "右对齐", 0, QApplication::CodecForTr));
            break;
        case 2:
            actions.at(2)->setText(QApplication::translate("mw", "上对齐", 0, QApplication::CodecForTr));
            break;
        case 3:
            actions.at(3)->setText(QApplication::translate("mw", "下对齐", 0, QApplication::CodecForTr));
            break;
        case 4:
            actions.at(4)->setText(QApplication::translate("mw", "水平居中", 0, QApplication::CodecForTr));
            break;
        case 5:
            actions.at(5)->setText(QApplication::translate("mw", "垂直居中", 0, QApplication::CodecForTr));
            break;
        default:
            break;
        }
    }

    actions.clear();
    mw->pMenuZXu->setTitle(QApplication::translate("mw", "层次", 0, QApplication::CodecForTr));
    actions = mw->pMenuZXu->actions();
    for(int i = 0; i < actions.size(); i++)
    {
        switch(i)
        {
        case 0:
            actions.at(0)->setText(QApplication::translate("mw", "移到最上层", 0, QApplication::CodecForTr));
            break;
        case 1:
            actions.at(1)->setText(QApplication::translate("mw", "移到最下层", 0, QApplication::CodecForTr));
            break;
        case 2:
            actions.at(2)->setText(QApplication::translate("mw", "移到上一层", 0, QApplication::CodecForTr));
            break;
        case 3:
            actions.at(3)->setText(QApplication::translate("mw", "移到下一层", 0, QApplication::CodecForTr));
            break;
        default:
            break;
        }
    }
    //XXXXX
    //mw->link->setText(0,QApplication::translate("mw", "连接", 0, QApplication::CodecForTr));
    //XXXXX
    //mw->language->setText(0,QApplication::translate("mw", "语言", 0, QApplication::CodecForTr));

    //XXXXX
    //mw->setting->setText(0,QApplication::translate("mw", "设置", 0, QApplication::CodecForTr));
    //XXXXX
    //mw->HMIsetting->setText(0,QApplication::translate("mw", "触摸屏参数设置", 0, QApplication::CodecForTr));
    //XXXXX
    //mw->HMIstatus->setText(0,QApplication::translate("mw", "HMI状态", 0, QApplication::CodecForTr));
    //mw->PLCcontral->setText(0,QApplication::translate("mw", "PLC控制", 0, QApplication::CodecForTr));
    //mw->clock->setText(0,QApplication::translate("mw", "时钟", 0, QApplication::CodecForTr));

    //XXXXX
    //mw->filepro->setText(0,QApplication::translate("mw", "文件保护", 0, QApplication::CodecForTr));
    //XXXXX
    //mw->HMIpro->setText(0,QApplication::translate("mw", "HMI保护", 0, QApplication::CodecForTr));
    mw->screen->setText(0,QApplication::translate("mw", "画面", 0, QApplication::CodecForTr));
    mw->window->setText(0,QApplication::translate("mw", "窗口", 0, QApplication::CodecForTr));
    mw->tree_hisdatalog->setText(0,QApplication::translate("mw", "数据采集", 0, QApplication::CodecForTr));
    //XXXXX
    //mw->Varstatus->setText(0,QApplication::translate("mw", "变量表", 0, QApplication::CodecForTr));
   if(pwnd->newScreenDlg)
   {
        pwnd->newScreenDlg->ui->newscreen_style_combobox->clear();
       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/1.ico"),QApplication::translate("mw", "透明", 0, QApplication::CodecForTr));
       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/1.ico"),QApplication::translate("mw", "纯色", 0, QApplication::CodecForTr));

//       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/2.ico"),QApplication::translate("mw", "网状样式1", 0, QApplication::CodecForTr));
//       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/3.ico"),QApplication::translate("mw", "网状样式2", 0, QApplication::CodecForTr));
//       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/4.ico"),QApplication::translate("mw", "网状样式3", 0, QApplication::CodecForTr));
//       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/5.ico"),QApplication::translate("mw", "网状样式4", 0, QApplication::CodecForTr));
//       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/6.ico"),QApplication::translate("mw", "网状样式5", 0, QApplication::CodecForTr));
//       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/7.ico"),QApplication::translate("mw", "网状样式6", 0, QApplication::CodecForTr));
//       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/8.ico"),QApplication::translate("mw", "网状样式7", 0, QApplication::CodecForTr));

//       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/9.ico"),QApplication::translate("mw", "横线", 0, QApplication::CodecForTr));
//       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/10.ico"),QApplication::translate("mw", "竖线", 0, QApplication::CodecForTr));
//       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/11.ico"),QApplication::translate("mw", "方格", 0, QApplication::CodecForTr));
//       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/12.ico"),QApplication::translate("mw", "左斜线", 0, QApplication::CodecForTr));
//       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/13.ico"),QApplication::translate("mw", "右斜线", 0, QApplication::CodecForTr));
//       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/14.ico"),QApplication::translate("mw", "斜方格", 0, QApplication::CodecForTr));

       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/15.ico"),QApplication::translate("mw", "横向过度", 0, QApplication::CodecForTr));
       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/16.ico"),QApplication::translate("mw", "横向对称过度", 0, QApplication::CodecForTr));
       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/17.ico"),QApplication::translate("mw", "纵向过度", 0, QApplication::CodecForTr));
       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/18.ico"),QApplication::translate("mw", "纵向对称过度", 0, QApplication::CodecForTr));

       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/19.ico"),QApplication::translate("mw", "斜上过渡", 0, QApplication::CodecForTr));
       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/20.ico"),QApplication::translate("mw", "斜上对称过渡", 0, QApplication::CodecForTr));

       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/21.ico"),QApplication::translate("mw", "斜下过渡", 0, QApplication::CodecForTr));
       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/22.ico"),QApplication::translate("mw", "斜下对称过渡", 0, QApplication::CodecForTr));

       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/24.ico"),QApplication::translate("mw", "右上角辐射", 0, QApplication::CodecForTr));
       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/23.ico"),QApplication::translate("mw", "左上角辐射", 0, QApplication::CodecForTr));
       pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/25.ico"),QApplication::translate("mw", "中心辐射", 0, QApplication::CodecForTr));
       pwnd->newScreenDlg->ui->newscreen_style_combobox->setCurrentIndex(1); //默认选择纯色

   }


   // if(mw->com1link->text(0)=="COM1 Link")
   // {
        // mw->m_pSamSysParame->m_qvcPlcCommunicate[0].sConnectName=QApplication::translate("mw", "COM1连接", 0, QApplication::CodecForTr);
        // mw->com1link->setText(0,QApplication::translate("mw", "COM1连接", 0, QApplication::CodecForTr));
    //}
 //   if(mw->PLC_com2!=NULL)
 //   {
        //if(mw->com2link->text(0)=="COM2 Link")
        //{
            // mw->m_pSamSysParame->m_qvcPlcCommunicate[1].sConnectName=QApplication::translate("mw", "COM2连接", 0, QApplication::CodecForTr);
             //mw->com1link->setText(0,QApplication::translate("mw", "COM2连接", 0, QApplication::CodecForTr));
       // }
 //   }

//    if(mw->m_pSamSysParame->m_historyLogData.bHistoryDataExist)//历史数据
//    {
//        if(mw->hisdatalog_child->text(0)=="Historical Data Logger 0")
//         {
//             mw->m_pSamSysParame->m_historyLogData.sHistoryDataName = QApplication::translate("mw", "历史数据收集器0", 0, QApplication::CodecForTr);
//             mw->hisdatalog_child->setText(0,QApplication::translate("mw", "历史数据收集器0", 0, QApplication::CodecForTr));
//         }
//    }

    mw->alarmlog->setText(0,QApplication::translate("mw", "报警登录", 0, QApplication::CodecForTr));
    mw->recipe->setText(0,QApplication::translate("mw", "配方", 0, QApplication::CodecForTr));
    mw->datatransport->setText(0,QApplication::translate("mw", "资料传输", 0, QApplication::CodecForTr));
    mw->treeScheduler->setText(0,QApplication::translate("mw", "时间表", 0, QApplication::CodecForTr));
    //XXXXX
    //mw->datatransport->setText(0,QApplication::translate("mw", "资料传输", 0, QApplication::CodecForTr));

    mw->m_rightDock->setWindowTitle(QApplication::translate("mw", "信息输出", 0, QApplication::CodecForTr));

    mw->copyScreen_Item->setText(0,QApplication::translate("mw", "画面", 0, QApplication::CodecForTr));
    mw->copyWindow_Item->setText(0,QApplication::translate("mw", "窗口", 0, QApplication::CodecForTr));
    QString ss=QApplication::translate("mw","数位报警登录", 0, QApplication::CodecForTr);

    mw->sysSetting->setText(0,QApplication::translate("mw", "系统设置", 0, QApplication::CodecForTr));
    mw->pcCtrl->setText(0,QApplication::translate("mw", "主机管理", 0, QApplication::CodecForTr));
    mw->link->setText(0,QApplication::translate("mw", "连接设置", 0, QApplication::CodecForTr));
    mw->pcChoice->setText(0,QApplication::translate("mw", "机型选择", 0, QApplication::CodecForTr));
    mw->displaySet->setText(0,QApplication::translate("mw", "显示设置", 0, QApplication::CodecForTr));
    mw->operateSet->setText(0,QApplication::translate("mw", "操作设置", 0, QApplication::CodecForTr));
    mw->dataCtrl->setText(0,QApplication::translate("mw", "数据控制", 0, QApplication::CodecForTr));
    mw->permissionSec->setText(0,QApplication::translate("mw", "用户权限", 0, QApplication::CodecForTr));
    mw->printer->setText(0,QApplication::translate("mw", "打印机", 0, QApplication::CodecForTr));
    mw->confiWorks->setText(0,QApplication::translate("mw", "组态工程", 0, QApplication::CodecForTr));
    mw->downloadSet->setText(0,QApplication::translate("mw", "下载设置", 0, QApplication::CodecForTr));
    mw->accessEncry->setText(0,QApplication::translate("mw", "访问加密", 0, QApplication::CodecForTr));
    mw->clock->setText(0,QApplication::translate("mw", "时钟设置", 0, QApplication::CodecForTr));
    mw->productLicen->setText(0,QApplication::translate("mw", "产品授权", 0, QApplication::CodecForTr));
    mw->lanSet->setText(0,QApplication::translate("mw", "语言设置", 0, QApplication::CodecForTr));
    mw->tree_macro->setText(0,QApplication::translate("mw", "脚本", 0, QApplication::CodecForTr));
    mw->global_macro->setText(0,QApplication::translate("mw", "全局脚本", 0, QApplication::CodecForTr));
    mw->init_macro->setText(0,QApplication::translate("mw", "初始化脚本", 0, QApplication::CodecForTr));
    mw->hostPeri->setText(0,QApplication::translate("mw", "主机外设", 0, QApplication::CodecForTr));
    mw->chdItem->setText(0,QApplication::translate("mw", "掉电存储区设置", 0, QApplication::CodecForTr));
    //mw->subWidget1->setWindowTitle(QApplication::translate("mw", "系统参数", 0, QApplication::CodecForTr));
    //mw->subWidget2->setWindowTitle(QApplication::translate("mw", "窗口画面", 0, QApplication::CodecForTr));
    mw->qButtonLab->setText(QApplication::translate("mw", " 状态", 0, QApplication::CodecForTr));
    mw->qLanguageLab->setText(QApplication::translate("mw", " 语言", 0, QApplication::CodecForTr));
    if(mw->link->childCount() == 5)
    {
        QTreeWidgetItem *cItem = mw->link->child(3);
        cItem->setText(0,QApplication::translate("mw", "以太网", 0, QApplication::CodecForTr));
        cItem = mw->link->child(4);
        cItem->setText(0,QApplication::translate("mw", "CAN总线", 0, QApplication::CodecForTr));
    }
    mw->dockTabWidget->setTabText(0,QApplication::translate("mw", "系统参数", 0, QApplication::DefaultCodec));
    mw->dockTabWidget->setTabText(1,QApplication::translate("mw", "窗口画面", 0, QApplication::DefaultCodec));
    //int digitalSize = mw->m_pSamSysParame->m_qvcDigitalAlarm.size();
   // for(int i=0;i< digitalSize;i++)
   // {
       //mw->digital_treeItem[i]->setText(0,QString("%1%2").arg(ss).arg(i+1));
       //mw->m_pSamSysParame->m_qvcDigitalAlarm[i].sAlarmName =QApplication::translate("mw", "数位报警区", 0, QApplication::CodecForTr);
  //  }







    ss=QApplication::translate("mw","类比报警登录", 0, QApplication::CodecForTr);
    //int analogSize = mw->m_pSamSysParame->m_qvcAnalogAlarm.size();
//    for(int i=0;i< analogSize;i++)
//    {
//        mw->analog_treeItem[i]->setText(0,QString("%1%2").arg(ss).arg(i+1));
//    }

   // for(int i=0;i< analogSize;i++)
   // {
        //mw->m_pSamSysParame->m_qvcAnalogAlarm[i].sAlarmName = QApplication::translate("mw", "类比报警区", 0, QApplication::CodecForTr);
   // }




    QString  s_tr="";
//    for(int i=0;i<mw->m_pSamSysParame->m_qvcAnalogAlarm.size();i++)
//    {
//        if(mw->analogAlarm_vecor[i].analogAlarm_style=="Low Low")
//        {
//            mw->analogAlarm_vecor[i].analogAlarm_style=s_tr.fromLocal8Bit("低低");
//        }
//        else if(mw->analogAlarm_vecor[i].analogAlarm_style=="Low")
//        {
//            mw->analogAlarm_vecor[i].analogAlarm_style=s_tr.fromLocal8Bit("低");
//        }
//         else if(mw->analogAlarm_vecor[i].analogAlarm_style=="High High")
//        {
//            mw->analogAlarm_vecor[i].analogAlarm_style=s_tr.fromLocal8Bit("高高");
//        }
//        else if(mw->analogAlarm_vecor[i].analogAlarm_style=="High")
//        {
//            mw->analogAlarm_vecor[i].analogAlarm_style=s_tr.fromLocal8Bit("高");
//        }

//        int Row=mw->analogAlarm_vecor[i].analogAlarm_row;
//        for(int j=0;j<Row;j++)
//        {
//            if(mw->analogAlarm_vecor[i].analogAlarm_tableColumn0[j]=="Low Low")
//            {
//                mw->analogAlarm_vecor[i].analogAlarm_tableColumn0[j]=s_tr.fromLocal8Bit("低低");
//            }
//            else if(mw->analogAlarm_vecor[i].analogAlarm_tableColumn0[j]=="Low")
//            { mw->analogAlarm_vecor[i].analogAlarm_tableColumn0[j]=s_tr.fromLocal8Bit("低");
//            }
//            else if(mw->analogAlarm_vecor[i].analogAlarm_tableColumn0[j]=="High High")
//            {
//                mw->analogAlarm_vecor[i].analogAlarm_tableColumn0[j]=s_tr.fromLocal8Bit("高高");
//            }
//            else if(mw->analogAlarm_vecor[i].analogAlarm_tableColumn0[j]=="High")
//            {
//                mw->analogAlarm_vecor[i].analogAlarm_tableColumn0[j]=s_tr.fromLocal8Bit("高");
//            }
//        }
//    }

//    if(mw->recipeDlg)
//    {
//        QString m_str="";
//     //   if( mw->recipeDlg->ui->name_lineEdit->text()=="Recipe 1")
//        //{
//       //     mw->recipeDlg->ui->name_lineEdit->setText(m_str.fromLocal8Bit("配方1"));
//       // }
//       mw->recipeDlg->ui->datestyle_comboBox->clear();
//       mw->recipeDlg->ui->datestyle_comboBox->addItems(QStringList()<<m_str.fromLocal8Bit("16位正整数") <<m_str.fromLocal8Bit("32位正整数")<<m_str.fromLocal8Bit("16位整数")
//                                                       <<m_str.fromLocal8Bit("32位整数")<<m_str.fromLocal8Bit("浮点数"));
//    }

}

void  transparent::translate(MainWindow *mw)//翻译
{
    QString sTmp="";
   // mw->TreeKeyboard->setText(0,QApplication::translate("mw", "Custom Control", 0, QApplication::UnicodeUTF8));
    mw->m_leftDock->setWindowTitle(QApplication::translate("mw", "Window", 0, QApplication::DefaultCodec));
    mw->m_toolDock->setWindowTitle(QApplication::translate("mw", "ToolBar", 0, QApplication::DefaultCodec));
    //list_style
    //mw->list_style->setItemText(0,QApplication::translate("mw", "Standard List", 0, QApplication::UnicodeUTF8));
    //mw->list_style->setItemText(1,QApplication::translate("mw", "Cell List", 0, QApplication::UnicodeUTF8));
    //mw->list_style->setItemText(2,QApplication::translate("mw", "Preview List", 0, QApplication::UnicodeUTF8));
    mw->undoAction->setText(QApplication::translate("mw", "Undo", 0, QApplication::UnicodeUTF8));
    mw->undoAction->setStatusTip(QApplication::translate("mw", "Undo Ths Last Operation", 0, QApplication::UnicodeUTF8));
    mw->redoAction->setText(QApplication::translate("mw", "Redo", 0, QApplication::UnicodeUTF8));
    mw->redoAction->setStatusTip(QApplication::translate("mw", "Redo Ths Last Operation", 0, QApplication::UnicodeUTF8));
    mw->deleteAction->setText(QApplication::translate("mw", "Delete", 0, QApplication::UnicodeUTF8));
    mw->deleteAction->setStatusTip(QApplication::translate("mw", "Delete", 0, QApplication::UnicodeUTF8));
    mw->lab_control_statusBar->setText(QApplication::translate("mw", "Delete", 0, QApplication::UnicodeUTF8));
    mw->lab_Coordinate_statusBar->setText(QApplication::translate("mw", "Coordinates:", 0, QApplication::UnicodeUTF8));
    mw->lab_up_statusBar->setText(QApplication::translate("mw", "Top:", 0, QApplication::UnicodeUTF8));
    mw->lab_left_statusBar->setText(QApplication::translate("mw", "Left:", 0, QApplication::UnicodeUTF8));
    mw->lab_size_statusBar->setText(QApplication::translate("mw", "Size:", 0, QApplication::UnicodeUTF8));
    mw->lab_width_statusBar->setText(QApplication::translate("mw", "Width:", 0, QApplication::UnicodeUTF8));
    mw->lab_hight_statusBar->setText(QApplication::translate("mw", "Height:", 0, QApplication::UnicodeUTF8));
#ifdef AK_SAMKOON
    mw->lab_samkoon_statusBar->setText(QApplication::translate("mw", "Samkoon", 0, QApplication::UnicodeUTF8));
#else define LA_DEBINUO
    //mw->lab_samkoon_statusBar->setText(QApplication::translate("mw", "DeBiNuo", 0, QApplication::UnicodeUTF8));
#endif
    //mw->lab_samkoon_statusBar->setText(QApplication::translate("mw", "Samkoon", 0, QApplication::UnicodeUTF8));
    mw->ui->statusBar->showMessage(QApplication::translate("mw", "Ready", 0, QApplication::UnicodeUTF8) );

    mw->root->setText(0,QApplication::translate("mw", "HMI", 0, QApplication::UnicodeUTF8));
    mw->root0->setText(0,QApplication::translate("mw", "Window&Screen", 0, QApplication::UnicodeUTF8));

    QList <QAction *> actions = mw->pMenuSpace->actions();
    mw->pMenuSpace->setTitle(QApplication::translate("mw", "Spacing", 0, QApplication::UnicodeUTF8));
    for(int i = 0; i < actions.size(); i++)
    {
        switch(i)
        {
        case 0:
            actions.at(0)->setText(QApplication::translate("mw", "Make Same Width", 0, QApplication::UnicodeUTF8));
            break;
        case 1:
            actions.at(1)->setText(QApplication::translate("mw", "Make Same Height", 0, QApplication::UnicodeUTF8));
            break;
        case 2:
            actions.at(2)->setText(QApplication::translate("mw", "Make Same Width And Height", 0, QApplication::UnicodeUTF8));
            break;
        case 3:
            actions.at(3)->setText(QApplication::translate("mw", "Horizontal Equal Inteval", 0, QApplication::UnicodeUTF8));
            break;
        case 4:
            actions.at(4)->setText(QApplication::translate("mw", "Vertical Equal Inteval", 0, QApplication::UnicodeUTF8));
            break;
        default:
            break;
        }
    }

    actions.clear();
    actions = mw->pMenuAlign->actions();
    mw->pMenuAlign->setTitle(QApplication::translate("mw", "Align", 0, QApplication::UnicodeUTF8));
    for(int i = 0; i < actions.size(); i++)
    {
        switch(i)
        {
        case 0:
            actions.at(0)->setText(QApplication::translate("mw", "Left", 0, QApplication::UnicodeUTF8));
            break;
        case 1:
            actions.at(1)->setText(QApplication::translate("mw", "Right", 0, QApplication::UnicodeUTF8));
            break;
        case 2:
            actions.at(2)->setText(QApplication::translate("mw", "Top", 0, QApplication::UnicodeUTF8));
            break;
        case 3:
            actions.at(3)->setText(QApplication::translate("mw", "Bottom", 0, QApplication::UnicodeUTF8));
            break;
        case 4:
            actions.at(4)->setText(QApplication::translate("mw", "Horizontal Center", 0, QApplication::UnicodeUTF8));
            break;
        case 5:
            actions.at(5)->setText(QApplication::translate("mw", "Vertical Center", 0, QApplication::UnicodeUTF8));
            break;
        default:
            break;
        }
    }

    actions.clear();
    mw->pMenuZXu->setTitle(QApplication::translate("mw", "Layer", 0, QApplication::UnicodeUTF8));
    actions = mw->pMenuZXu->actions();
    for(int i = 0; i < actions.size(); i++)
    {
        switch(i)
        {
        case 0:
            actions.at(0)->setText(QApplication::translate("mw", "Moved To The Top", 0, QApplication::UnicodeUTF8));
            break;
        case 1:
            actions.at(1)->setText(QApplication::translate("mw", "Send To Bottom", 0, QApplication::UnicodeUTF8));
            break;
        case 2:
            actions.at(2)->setText(QApplication::translate("mw", "Bring Forward", 0, QApplication::UnicodeUTF8));
            break;
        case 3:
            actions.at(3)->setText(QApplication::translate("mw", "Send Behind", 0, QApplication::UnicodeUTF8));
            break;
        default:
            break;
        }
    }

    //XXXXX
    //mw->link->setText(0,QApplication::translate("mw", "Link", 0, QApplication::UnicodeUTF8));
    //mw->language->setText(0,QApplication::translate("mw", "Languege", 0, QApplication::UnicodeUTF8));
    if( mw->TreeKeyboard->text(0)==sTmp.fromLocal8Bit("自定义键盘"))
    {
        mw->TreeKeyboard->setText(0,QApplication::translate("mw", "Customize Keyboard", 0, QApplication::UnicodeUTF8));
    }
    if(mw->copyUserKeyboard)
    {
        if(mw->copyUserKeyboard->text(0)==sTmp.fromLocal8Bit("自定义键盘"))
        {
             mw->copyUserKeyboard->setText(0,QApplication::translate("mw", "Customize Keyboard", 0, QApplication::UnicodeUTF8));
        }
    }

    if(pwnd->newScreenDlg)
    {
        pwnd->newScreenDlg->ui->newscreen_style_combobox->clear();
        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/1.ico"),"Transparent");
        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/1.ico"),("Solid"));

//        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/2.ico"),("Mesh style 1"));
//        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/3.ico"),("Mesh style 2"));
//        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/4.ico"),("Mesh style 3"));
//        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/5.ico"),("Mesh style 4"));
//        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/6.ico"),("Mesh style 5"));
//        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/7.ico"),("Mesh style 6"));
//        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/8.ico"),("Mesh style 7"));

//        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/9.ico"),("Horizontal"));
//        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/10.ico"),("Vertical"));
//        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/11.ico"),("Box"));
//        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/12.ico"),("Left Slash"));
//        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/13.ico"),("Right slash"));
//        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/14.ico"),("Slope Box"));

        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/15.ico"),("Horizontal Transition"));
        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/16.ico"),("Horizontal Symmetry"));
        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/17.ico"),("Vertical Transition"));
        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/18.ico"),("Vertical Symmetry"));

        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/19.ico"),("Rap On the transition"));
        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/20.ico"),("Skew Symmetric"));

        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/21.ico"),("Rap Under the transition"));
        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/22.ico"),("Skew-Symmetric"));

        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/23.ico"),("top left-Spoke"));
        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/24.ico"),("top right-Spoke"));
        pwnd->newScreenDlg->ui->newscreen_style_combobox->addItem(QIcon(":/style/images/style/25.ico"),("Hub-Spoke"));
        pwnd->newScreenDlg->ui->newscreen_style_combobox->setCurrentIndex(1);
    }


    mw->sysSetting->setText(0,QApplication::translate("mw", "System Settings", 0, QApplication::UnicodeUTF8));
    mw->pcCtrl->setText(0,QApplication::translate("mw", "Host Management", 0, QApplication::UnicodeUTF8));
    mw->link->setText(0,QApplication::translate("mw", "Connection Settings", 0, QApplication::UnicodeUTF8));
    mw->pcChoice->setText(0,QApplication::translate("mw", "Model Selection", 0, QApplication::UnicodeUTF8));
    mw->displaySet->setText(0,QApplication::translate("mw", "Display Settings", 0, QApplication::UnicodeUTF8));
    mw->operateSet->setText(0,QApplication::translate("mw", "Operation Setting", 0, QApplication::UnicodeUTF8));
    mw->dataCtrl->setText(0,QApplication::translate("mw", "Data Control", 0, QApplication::UnicodeUTF8));
    mw->permissionSec->setText(0,QApplication::translate("mw", "User Rights", 0, QApplication::UnicodeUTF8));
    mw->printer->setText(0,QApplication::translate("mw", "Printer", 0, QApplication::UnicodeUTF8));
    mw->confiWorks->setText(0,QApplication::translate("mw", "Configuration Engineering", 0, QApplication::UnicodeUTF8));
    mw->downloadSet->setText(0,QApplication::translate("mw", "Download Settings", 0, QApplication::UnicodeUTF8));
    mw->accessEncry->setText(0,QApplication::translate("mw", "Access To Encrypted", 0, QApplication::UnicodeUTF8));
    mw->clock->setText(0,QApplication::translate("mw", "Clock Setting", 0, QApplication::UnicodeUTF8));
    mw->productLicen->setText(0,QApplication::translate("mw", "Product Licensing", 0, QApplication::UnicodeUTF8));
    mw->lanSet->setText(0,QApplication::translate("mw", "Language Settings", 0, QApplication::UnicodeUTF8));
    mw->tree_macro->setText(0,QApplication::translate("mw", "Script", 0, QApplication::UnicodeUTF8));
    mw->global_macro->setText(0,QApplication::translate("mw", "Global Script", 0, QApplication::UnicodeUTF8));
    mw->init_macro->setText(0,QApplication::translate("mw", "Initialization Script", 0, QApplication::UnicodeUTF8));
    mw->hostPeri->setText(0,QApplication::translate("mw", "Host Peripherals", 0, QApplication::UnicodeUTF8));
    mw->chdItem->setText(0,QApplication::translate("mw", "Power-down Storage Area Set", 0, QApplication::UnicodeUTF8));
    //mw->subWidget1->setWindowTitle(QApplication::translate("mw", "System Parameters", 0, QApplication::DefaultCodec));
    //mw->subWidget2->setWindowTitle(QApplication::translate("mw", "Window Screen", 0, QApplication::DefaultCodec));
    mw->qButtonLab->setText(QApplication::translate("mw", " Status", 0, QApplication::DefaultCodec));
    mw->qLanguageLab->setText(QApplication::translate("mw", " Languege", 0, QApplication::DefaultCodec));
    if(mw->link->childCount() == 5)
    {
        QTreeWidgetItem *cItem = mw->link->child(3);
        cItem->setText(0,QApplication::translate("mw", "Ethernet", 0, QApplication::UnicodeUTF8));
        cItem = mw->link->child(4);
        cItem->setText(0,QApplication::translate("mw", "CAN Bus", 0, QApplication::UnicodeUTF8));
    }

    mw->dockTabWidget->setTabText(0,QApplication::translate("mw", "System Parameters", 0, QApplication::DefaultCodec));
    mw->dockTabWidget->setTabText(1,QApplication::translate("mw", "Window Screen", 0, QApplication::DefaultCodec));

    mw->screen->setText(0,QApplication::translate("mw", "Screen", 0, QApplication::UnicodeUTF8));
    mw->window->setText(0,QApplication::translate("mw", "Window", 0, QApplication::UnicodeUTF8));
    mw->tree_hisdatalog->setText(0,QApplication::translate("mw", "Data Collection", 0, QApplication::UnicodeUTF8));


    mw->alarmlog->setText(0,QApplication::translate("mw", "Alarm Log", 0, QApplication::UnicodeUTF8));
    mw->recipe->setText(0,QApplication::translate("mw", "Recipe", 0, QApplication::UnicodeUTF8));
    mw->datatransport->setText(0,QApplication::translate("mw", "Data Transfer", 0, QApplication::UnicodeUTF8));

    mw->treeScheduler->setText(0,QApplication::translate("mw", "Time Schedule", 0, QApplication::UnicodeUTF8));
    //mw->sub_Recipe->setText(0,QApplication::translate("mw", "Recipe 1", 0, QApplication::UnicodeUTF8));
    //XXXXX
    //mw->datatransport->setText(0,QApplication::translate("mw", "Data Transport", 0, QApplication::UnicodeUTF8));
    mw->m_rightDock->setWindowTitle(QApplication::translate("mw", "Information Output", 0, QApplication::UnicodeUTF8));
    mw->copyScreen_Item->setText(0,QApplication::translate("mw", "Screen", 0, QApplication::UnicodeUTF8));
    mw->copyWindow_Item->setText(0,QApplication::translate("mw", "Window", 0, QApplication::UnicodeUTF8));



}

/*void transparent::translate_MF_toEn(QMFunctionBtnGenDlg *MF)
{
    QString sTmp="";
    int nTmp=0;
    QStringList sList;
    nTmp=MF->ui->listWidget_AddFunction->count();
    for(int i=0;i<nTmp;i++)
    {
        sTmp=MF->ui->listWidget_AddFunction->item(i)->text();
        if(sTmp.contains(QObject::tr("置位线圈")))
        {
           sList.clear();
           sList=sTmp.split(QObject::tr("置位线圈"));
           MF->ui->listWidget_AddFunction->item(i)->setText(QString("%1%2").arg("Set Coil") .arg(sList.at(1)));
        }//
        if(sTmp.contains(QObject::tr("复位线圈")))
        {
            sList.clear();
            sList=sTmp.split(QObject::tr("复位线圈"));
            MF->ui->listWidget_AddFunction->item(i)->setText(QString("%1%2").arg("Reset Coil") .arg(sList.at(1)));
        }///
        if(sTmp.contains(QObject::tr("线圈交替")))
        {
            sList.clear();
            sList=sTmp.split(QObject::tr("线圈交替"));
            MF->ui->listWidget_AddFunction->item(i)->setText(QString("%1%2").arg("Coil Turn") .arg(sList.at(1)));
        }//
        if(sTmp.contains(QObject::tr("画面跳转")))
        {
           if(sTmp.contains(QObject::tr("至起始画面")))
           {
               MF->ui->listWidget_AddFunction->item(i)->setText(QString("%1").arg("Screen Jump To the Start Screen"));
           }
           else if(sTmp.contains(QObject::tr("至前幅画面")))
           {
                MF->ui->listWidget_AddFunction->item(i)->setText(QString("%1").arg("Screen Jump To the Forward Screen"));
           }
           else
           {
               sList.clear();
               sList=sTmp.split(QObject::tr("号"));
               MF->ui->listWidget_AddFunction->item(i)->setText(QString("%1%2").arg("Screen Jump To Screen No.") .arg(sList[0].right(1)));
           }

        }
        if(sTmp.contains(QObject::tr("设置数据")))
        {
           QStringList setaddress_list=sTmp.split(":");
           QStringList setData_list=setaddress_list.at(1).split(" ");
           MF->ui->listWidget_AddFunction->item(i)->setText(QString("%1%2 %3%4").arg("Setting Data Address:").arg(setData_list.at(0)).arg("Set value:").arg(setaddress_list.last()));

        }
        if(sTmp.contains(QObject::tr("用户输入")))
        {
           sList.clear();
           sList=sTmp.split(QObject::tr("用户输入"));
           MF->ui->listWidget_AddFunction->item(i)->setText(QString("%1%2").arg("User Intput Address:").arg(sList.at(1)));

        }
        if(sTmp.contains(QObject::tr("线圈点动")))
        {
          sList.clear();
          sList=sTmp.split(QObject::tr("线圈点动"));
          MF->ui->listWidget_AddFunction->item(i)->setText(QString("%1%2").arg("Coli Inching").arg(sList.at(1)));

        }
    }
}*/
