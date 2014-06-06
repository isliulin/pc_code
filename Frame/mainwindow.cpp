#include "mainwindow.h"
#include "stdafx.h"
#include <windows.h>
#include <QtGui>

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include "view/qgroupitem.h"
//#include "Frame/ThingDlg/qpieframdlg.h"
//#include "Frame/ThingDlg/qstepingdlg.h"
#include "Frame/ThingDlg/table.h"
#include "Frame/ThingDlg/qscale.h"
#include "view/qdrawgraphics.h"
#include "Frame/ThingDlg/FindAddrDlg.h"
#include "Frame/ThingDlg/DisplayAddressUse.h"
#include <QBitmap>
#include "Frame/ThingDlg/StaticTexts.h"
#include "QLibrary"
#include "Frame/DebugDlg/DownLoadDlg.h"
#include "view/statictextitem.h"
#include "view/akcomboitem.h"
#include "Frame/ThingDlg/akcombobox.h"
//#include "Frame/ThingDlg/QSingSelectDlg.h"
//#include "Frame/ThingDlg/ComboBox.h"
#include "Frame/ThingDlg/Slider.h"
#include "Frame/ThingDlg/AnimationDlg.h"
//#include "Frame/ThingDlg/MsgBoardDlg.h"
#include "Frame/DrawDlg/RoundedRectDlg.h"
#include "Frame/DrawDlg/ArcDlg.h"
#include <QProcess>
#include "Frame/DrawDlg/OpenLibrary.h"
#include "Frame/DrawDlg/SaveToLibrary.h"
#include  "Command/unandrestack.h"
#include "Frame/DebugDlg/compilethrd.h"
#include "Frame/DebugDlg/compress.h"
#include "transparent.h"
#include "Frame/ThingDlg/qrecipetable.h"
#include "Frame/TreeCtrlDlg/qvardlg.h"
#include "Frame/TreeCtrlDlg/qdataloggerdlg.h"
#include "Frame/ThingDlg/qtrend.h"
#include "Frame/ThingDlg/qtrenddatagroup.h"

#include "Frame/TreeCtrlDlg/modelsel.h"
#include "Frame/TreeCtrlDlg/operatorset.h"
#include "Frame/TreeCtrlDlg/newdatacontrol.h"
#include "Frame/TreeCtrlDlg/newdownload.h"
#include "Frame/TreeCtrlDlg/newencryaccess.h"
#include "Frame/TreeCtrlDlg/newinitset.h"
#include "Frame/TreeCtrlDlg/newlanguage.h"
#include "Frame/TreeCtrlDlg/newplcctrl.h"
#include "Frame/TreeCtrlDlg/newprinter.h"
#include "Frame/TreeCtrlDlg/newproright.h"
#include "Frame/TreeCtrlDlg/newuserright.h"
#include "Frame/TreeCtrlDlg/protocoldlg.h"

#include "Frame/ThingDlg/qalarmcontroldlg.h"
//#include "Frame/ThingDlg/qdynalarmbardlg.h"
#include "Frame/ThingDlg/alarmbardlg.h"
//#include "Frame/ThingDlg/qhisalarmdlg.h"
#include "Frame/ThingDlg/switch/switchdlg.h"
#include "Frame/ThingDlg/alarmlistdlg.h"

#include "Frame/ThingDlg/qimageshowdlg.h"
//#include "Frame/ThingDlg/qkeyboardascii.h"
#include "Frame/ThingDlg/qkeybutton.h"
//#include "Frame/ThingDlg/qkeybuttons.h"
#include "qprotocoltool.h"
#include "Frame/ThingDlg/newdynrectdlg.h"
#include "Frame/ThingDlg/newdyncircledlg.h"
#include "view/dyncircleattr.h"
#include "view/dynrectattr.h"
#include "structHead.h"
#include "Frame/ThingDlg/qrecipechoicedlg.h"
#include "Frame/ThingDlg/qdropdownbox.h"
#include "view/qdropdownattr.h"
#include "Frame/ThingDlg/qhistorydatashow.h"
#include "view/qhistorydatashowattr.h"
#include "Frame/ThingDlg/qmessageshow.h"
#include "view/qmessageshowattr.h"
#include "Macro/macroedit.h"
#include "Macro/macro.h"

#include "TreeCtrlDlg/alarmset.h"

#include "Macro/globalScriptDlg.h"
#include "Macro/initScriptDlg.h"
#include "Frame/ThingDlg/qflowblock.h"
#include "TreeCtrlDlg/powerprotectdlg.h"
#include "Frame/ThingDlg/qmessageboard.h"
#include "view/qmessageboradattr.h"
#include "Frame/ThingDlg/mfbtndlg.h"
#include "Macro/MarcoFindDlg.h"
#include "Frame/ThingDlg/qvaluedlg.h"
#include "ThingDlg/qchartdlg.h"
#include "Frame/DebugDlg/infodlg.h"
#include "Frame/ThingDlg/xytrenddlg.h"
#include "view/xytrend.h"

#include "Frame/NewProjectWizard/qnewprodlgex.h"

#include "Frame/DebugDlg/downloadtrd.h"
#include "Frame/TreeCtrlDlg/scheduledlg.h"

#ifndef PC_COMPRESS_FILE
#define PC_COMPRESS_FILE "compile\\upLoad.akr"
#endif
#define PC_PLC_EXE "SAMSoarDeveloper.exe"
#define PC_AKTOOL_EXE "aktool.exe"
typedef int (*FunCompress)(char *, int);
extern QTranslator *translator;
extern bool  is_tanslator;

MainWindow *pwnd;
QUndoStack *undoStack;
QList <QGraphicsItem *> CopyList;

extern QLabel *labelcolor;
extern QLabel *labelRGB;
//static const float FULL_ELLIPSE_FACTOR_OF_METER = 1.04511;
//static const float SECT_ELLIPSE_FACTOR_OF_METER = 0.80405;

#define PROJECT_MANAGE 1
#define INFORMATION_OUTPUT 2
#define TOOL_BUTTON 3

#define  vShareDir "/vdisk"
#define  vShareIni "/vdisk/start.ini"

#define  TOOLBAR_BASIC 1  // ����ͼ��
#define  TOOLBAR_CONTROL 2 //�ؼ�
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    mPicMd5.clear();
    ToolBarTabWidget = NULL;
    m_ChScreenMap.clear();
    g_Vars.clear();
    sLibraryPath.clear();
    picturePath="/home";
    sFilePath = "c:\\";//ѹ����ѹ�ļ�·��
    //ui->setupUi(this);
    vBaseLibraryScene.clear();  //�滭�������
    m_pSamSysParame = NULL;
    //    m_pSamSysParame = new QSamSysParame();
    qLanguagecmb = NULL;
    bToolBarCMBInit = false;
    is_Click_OpenrecentFile=false;
    is_OpenrecentFile=false;
    is_click_open=false;
    //bDrawAnimateFlag = false;  //�������ı�־
    undoStack = new QUndoStack(this);/*���峷����ջ*/
    nLoadShapeType = 0; //�������α�ʾ 0--һ�����Σ�1--�Ǳ�����
    nPcopyItenType = 0; //0:��ͨͼ�Ρ�1���Ǳ�ͼ�� add by chengzhihua
    pView=NULL;
    m_pLayout = NULL;
    cmenu = NULL;
    //   PLC_com2=NULL;
    copyScreen_Item=new QTreeWidgetItem();
    copyWindow_Item=new QTreeWidgetItem();
    copyUserKeyboard=new QTreeWidgetItem();
    is_haveScreen=false;
    is_SaveAS=false;
    is_Save=false;
    is_NeedCompiled = true;
    isCompiled = false;
    isCheck_WindowProperty=false;
    isCheck_ScreenProperty=false;
    bSimulator=false;//ģ���Ƿ����
    is_ScreenProperty_Name=false;
    is_WindowProperty_Name=false;
    newScreenDlg=new QTreeCtrlNewScreenDlg(this);//�½�����
    newWindowDlg=new QNewWindowDlg(this);//�½�����
    newCopyScreen=new QCopyScreenDlg(this);//���ƻ���Ի���
    newCopyWindow=new QCopyWindowDlg(this);
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);//���ر߿�ͱ�����
    ui->action_36->setCheckable(true);
    ui->action_37->setCheckable(true);
    ui->action_38->setCheckable(true);
    ui->action_39->setCheckable(true);
    ui->action_40->setCheckable(true);
    ui->action_41->setCheckable(true);
    ui->action_42->setCheckable(true);
    ui->action_tool->setCheckable(true);
    ui->action_36->setChecked(true);
    ui->action_37->setChecked(true);
    ui->action_38->setChecked(true);
    ui->action_39->setChecked(true);
    ui->action_40->setChecked(true);
    ui->action_41->setChecked(true);
    ui->action_42->setChecked(true);
    ui->action_tool->setChecked(false);
    is_Is=true;//�Ƿ��һ�ε���򿪰�ť

    isHave=false;
    nControlType=SAM_DRAW_INVALID; //�ؼ����ͱ�ʾ
    nActiveSheetIndex=0; //��ǰ������ţ���0��ʼ
    //setWindowTitle(PRO_FULL_NAME);

    /*******************************************************************/
    pwnd=this;
    newpro = NULL;
    //XXXXX
    //languagedlg = NULL;
    //initRecipeDlg();//��ʼ���䷽
    //recipeDlg = NULL;//�䷽�Ի���;
    //treectrlDlg =new QTreeCtrlDlg;//���ؼ�����Ի�������ݷ�װ��

    ////////////////////////////
    pMenuSpace = NULL;
    pMenuAlign = NULL;
    pMenuZXu   = NULL;
    ////////////////////////////

    for(int i=0;i<MAX_SCRNCNT;i++)
    {
        newScreen[i]=NULL;
    }//
    for(int i=0;i<DIGIT_ALARM_NUM;i++)
    {
        digital_treeItem[i]=NULL;
    }//
    for(int i=0;i<ANALOG_ALARM_NUM;i++)
    {
        analog_treeItem[i]=NULL;
    }//

    //   iDataTransferCount=0;//���ϴ��������ʼ��
    //   fileprotection=new QFileProtection;
    /*******************************************************************/
    nscreen=1;//

    nCurrentDigitalAlarmIndex=0;
    nCurrentAnalog_alarmIndex=0;

    //stackeWidget=new QStackedWidget();
    m_leftDock = new myDockWidget(this);
    //wxyֻ����ͣ������������
    m_leftDock->setAllowedAreas(Qt::LeftDockWidgetArea|/*Qt::AllDockWidgetAreas*/Qt::RightDockWidgetArea);
    m_leftDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    m_leftDock-> setWindowTitle(tr("����"));
    m_leftDock->setFloating(false);
    m_leftDock->setVisible(true);

    m_toolDock = new myDockWidget(this);
    m_toolDock->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea);
    m_toolDock->setFeatures(QDockWidget::DockWidgetClosable|QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
    m_toolDock->setWindowTitle(tr("������"));
    m_toolDock->setFloating(false);
    m_toolDock->setVisible(true);
    m_toolDock->setStyleSheet("QDockWidget::title{\ntext-align: left;\n"
                              "background: rgb(150,179,221);\n"
                              "padding-left: 5px;\n}");
    createActions();
    createMenu();
    createToolBars();
    createStatusBar();
    initLeftDocking();
    initRightDocking();

    QFile::remove("gEKip");

    subWidget1 = new QWidget;
    subWidget2 = new QWidget;
    widget = new QFrame();
    widget->setStyleSheet("background: rgb(197, 222, 255);");

    dockTabWidget =  new QTabWidget;
    dockTabWidget->setTabPosition(QTabWidget::North);//wxy tab above the pages
    dockTabWidget->addTab(subWidget1, tr("ϵͳ����"));
    dockTabWidget->addTab(subWidget2, tr("���ڻ���"));
    //add by wxyȥ��һЩ�����tabfocus���ԣ�������֮ǰ�İ�������Ϊnofocus
    dockTabWidget->setFocusPolicy(
            Qt::FocusPolicy(dockTabWidget->focusPolicy()&(~Qt::TabFocus)));


    dock_layout1 = new QVBoxLayout(subWidget1);
    dock_layout1->addWidget(tree);
    subWidget1->setLayout(dock_layout1);
    subWidget1->setStyleSheet("background: rgb(255, 255, 255);\n"
                              "font: 9pt '����';\n"
                              "color: rgb(8, 45, 105);\n"
                              "selection-color: rgb(8, 45, 105);\n"
                              "selection-background-color: rgb(197, 222, 255);");

    dock_layout2 = new QVBoxLayout(subWidget2);
    dock_layout2->addWidget(tree0);
    subWidget2->setLayout(dock_layout2);
    subWidget2->setStyleSheet("background: rgb(255, 255, 255);\n"
                              "font: 9pt '����';\n"
                              "color: rgb(8, 45, 105);\n"
                              "selection-color: rgb(8, 45, 105);\n"
                              "selection-background-color: rgb(197, 222, 255);");

    dock_layout = new QVBoxLayout(widget);
    dock_layout->addWidget(dockTabWidget);
    widget->setLayout(dock_layout);

    m_leftDock->setWidget(widget);
    addDockWidget(Qt::LeftDockWidgetArea,m_leftDock,Qt::Horizontal);
    m_leftDock->setStyleSheet("QDockWidget::title{\ntext-align: left;\n"
                              "background: rgb(150,179,221);\n"
                              "padding-left: 5px;\n}");
    m_leftDock->setFocusPolicy(
                Qt::FocusPolicy(dockTabWidget->focusPolicy()&(~Qt::TabFocus)));
    dockTabWidget->setCurrentIndex(1);
    m_leftDock->setData(PROJECT_MANAGE);
    connect(m_leftDock, SIGNAL(dockWidgetClose(int)), this, SLOT(dockWidgetClose(int)));

    ToolBarTabWidget =  new QTabWidget;
    ToolBarTabWidget->setTabPosition(QTabWidget::North);//wxy tab above the pages

    scrollAreaBasic = new QScrollArea(m_toolDock);
    scrollAreaBasic->setFocusPolicy(
                Qt::FocusPolicy(dockTabWidget->focusPolicy()&(~Qt::TabFocus)));
    scrollAreaBasic->setStyleSheet("background: rgb(197, 222, 255);");
    scrollAreaBasic->setWidget(ui->m_toolwidgetBasic);
    ui->m_toolwidgetBasic->setMinimumSize(231,421);
    ui->m_toolwidgetBasic->setStyleSheet("background: rgb(255, 255, 255);\n"
                                         "color: rgb(8, 45, 105);");

    scrollAreaCtl = new QScrollArea(m_toolDock);
    scrollAreaCtl->setFocusPolicy(
                Qt::FocusPolicy(dockTabWidget->focusPolicy()&(~Qt::TabFocus)));
    scrollAreaCtl->setStyleSheet("background: rgb(197, 222, 255);");
    scrollAreaCtl->setWidget(ui->m_toolwidgetCtl);
    ui->m_toolwidgetCtl->setMinimumSize(231,421);
    ui->m_toolwidgetCtl->setStyleSheet("background: rgb(255, 255, 255);\n"
                                       "color: rgb(8, 45, 105);");

    ToolBarTabWidget->addTab(scrollAreaBasic, tr("����ͼ��"));
    ToolBarTabWidget->addTab(scrollAreaCtl,   tr("�ؼ�"));
    if(is_tanslator)
    {
        ToolBarTabWidget->setTabText(0, tr("Basic Graphics"));
        ToolBarTabWidget->setTabText(1, tr("Controls"));
    }
    else
    {
        ToolBarTabWidget->setTabText(0, tr("����ͼ��"));
        ToolBarTabWidget->setTabText(1, tr("��   ��"));
    }

    //add by wxyȥ��һЩ�����tabfocus���ԣ�������֮ǰ�İ�������Ϊnofocus
    ToolBarTabWidget->setFocusPolicy(
                Qt::FocusPolicy(dockTabWidget->focusPolicy()&(~Qt::TabFocus)));
    ToolBarTabWidget->setCurrentIndex(1); //��ʼ����Ϊ�ؼ�
    ToolBarTabWidget->setStyleSheet("background: rgb(197, 222, 255);");
    m_toolDock->setWidget(ToolBarTabWidget);

    addDockWidget(Qt::RightDockWidgetArea, m_toolDock, Qt::Horizontal);
    m_toolDock->setData(TOOL_BUTTON);
    connect(m_toolDock, SIGNAL(dockWidgetClose(int)), this, SLOT(dockWidgetClose(int)));


    /***************************edit by zqh**************************/
    /***************************������ͼ��*****************************/

    m_ProVersionNum = AK_CURRENT_VERSION;
    nZoomNumber=100; //���ŵĳ�ʼֵ
    bIfSceneShowGrid = false;//�Ƿ���ʾ�����ʾ
    pDrawToSceneItem = NULL;

    /*pSceneSheet[nActiveSheetIndex] = new SamDrawScene ;//samdrawscene();QGraphicsScene
    pSceneSheet[nActiveSheetIndex]->setSceneRect(QRectF(0, 0, 1000, 1000));
    QHBoxLayout *layout = new QHBoxLayout;
    pView = new QGraphicsView(pSceneSheet[nActiveSheetIndex], this);
    pView->setDragMode(QGraphicsView::RubberBandDrag);//�ѵ�ѡ�ı���϶�ģʽ
    pView->setRenderHint(QPainter::Antialiasing, true); // ����ͼ�η�����
    pView->setMouseTracking(true); // ��������ƶ���׽

    pView->setSceneRect(0,0,1000,1000);
    pView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    layout->addWidget(pView);
    ui->centralWidget->setLayout(layout);

    setWindowTitle(tr(VERSION_NAME));
    setUnifiedTitleAndToolBarOnMac(true);
    **************************������ͼ��end*****************************/

    connect(ui->action_new_pro,SIGNAL(triggered()),this,SLOT(createprodlg()));
    connect(ui->action_open_pro,SIGNAL(triggered()),this,SLOT(createopenprodlg()));
    //connect(ui->action_new_screen,SIGNAL(triggered()),this,SLOT(createnewscreendlg()));
    connect(ui->action_save,SIGNAL(triggered()),this,SLOT(createsavedlg()));

    /******����������������ź���۵�����********/	
    connect(ui->action_recipetable,SIGNAL(triggered()),this,SLOT(createrecipetable()));
    connect(ui->action_bitbutton,SIGNAL(triggered()),this,SLOT(createbitbtndlg()));
    connect(ui->action_MFbtn,SIGNAL(triggered()),this,SLOT(createMFbtndlg()));
    //connect(ui->action_picture_button,SIGNAL(triggered()),this,SLOT(createpicturebtndlg()));
    //connect(ui->action_function_button,SIGNAL(triggered()),this,SLOT(createfunctionbtndlg()));
    //connect(ui->action_bit_indicatorlight,SIGNAL(triggered()),this,SLOT(createbitindicatorlightbtndlg()));
    //connect(ui->action_multi_indicatorlight,SIGNAL(triggered()),this,SLOT(createmultiindicatorlightbtndlg()));
    //connect(ui->action_multistate,SIGNAL(triggered()),this,SLOT(createmultistatebtndlg()));
    //connect(ui->action_staticpicture,SIGNAL(triggered()),this,SLOT(createstaticpicturedlg()));
    //connect(ui->action_pictureoutput,SIGNAL(triggered()),this,SLOT(createpicturedisplaydlg()));
    connect(ui->action_GIFoutput,SIGNAL(triggered()),this,SLOT(createstaticpicturedlg()));
    connect(ui->action_trendchart,SIGNAL(triggered()),this,SLOT(createtrendchartdlg()));
    //connect(ui->action_XYtrend,SIGNAL(triggered()),this,SLOT(createxytrendchartdlg()));
    connect(ui->action_dynamiccircle,SIGNAL(triggered()),this,SLOT(createdyncricledlg()));
    connect(ui->action_dynamicrect,SIGNAL(triggered()),this,SLOT(createdynrentdlg()));
    connect(ui->action_arlamcontrol,SIGNAL(triggered()),this,SLOT(createalarmcontroldlg()));
    connect(ui->action_dynamicarlarm,SIGNAL(triggered()),this,SLOT(createdynalarmbar()));
    connect(ui->action_histotyarlarm,SIGNAL(triggered()),this,SLOT(createhisalarm()));
    //connect(ui->action_picturemove,SIGNAL(triggered()),this,SLOT(creategraphicsmove()));
    connect(ui->action_chart,SIGNAL(triggered()),this,SLOT(createchart()));
    connect(ui->action_value,SIGNAL(triggered()),this,SLOT(createvalue()));
    connect(ui->action_image,SIGNAL(triggered()),this,SLOT(createimage()));
    connect(ui->action_historyrecord,SIGNAL(triggered()),this,SLOT(createhisrecord()));
    connect(ui->action_messagedisplay,SIGNAL(triggered()),this,SLOT(createmsgdisplay()));
    //connect(ui->action_mfaction,SIGNAL(triggered()),this,SLOT(createmfunctionbuttondlg()));
    connect(ui->action_flow_block,SIGNAL(triggered()),this,SLOT(createflowblock()));
    //connect(ui->action_his_tre_display,SIGNAL(triggered()),this,SLOT(createhistrenddisplay()));
    //connect(ui->action_timer,SIGNAL(triggered()),this,SLOT(createtimer()));
    connect(ui->action_checkall,SIGNAL(triggered()),this,SLOT(SlecetALL()));//Ctrl+Aȫѡ
    connect(ui->action_Keyboard,SIGNAL(triggered()),this,SLOT(CreateKeyboardASCII()));//�������
    connect(ui->action_messageboard,SIGNAL(triggered()),this,SLOT(OnCreateMessageBoard()));//���԰�
    connect(ui->action_User_Keybaor,SIGNAL(triggered()),this,SLOT(tree_newuserkeyboard()));//����û��Զ������
    connect(ui->action_datasamp,SIGNAL(triggered()),this,SLOT(tree_addhisdatalogger()));//������ݲɼ�
    connect(ui->action_waring,SIGNAL(triggered()),this,SLOT(tree_digitAlarm()));//��ӱ���
    connect(ui->action_rep,SIGNAL(triggered()),this,SLOT(tree_recipe()));//����䷽
    connect(ui->action_script,SIGNAL(triggered()),this,SLOT(slotOpenMacro()));//�򿪽ű������

   // connect(ui->action_upload,SIGNAL(triggered()),this,SLOT(OnCreatUploadDlg()));//�����ضԻ���

    //connect(ui->action_Pie,SIGNAL(triggered()),this,SLOT(OnCreatePie()));
    //connect(ui->action_Steping,SIGNAL(triggered()),this,SLOT(OnCreateSteping()));
    connect(ui->actionRecipeChoice,SIGNAL(triggered()),this,SLOT(ONRecipeChoice()));//�䷽ѡ����
    //connect(pPieAction,SIGNAL(triggered()),this,SLOT(OnCreatePie()));
  //  connect(ui->action_opera_record,SIGNAL(triggered()),this,SLOT(createoperadlg()));

    //��ͼ������edit by zqh
   connect(ui->action_rect,SIGNAL(triggered()),this,SLOT(OnDrawRect())); //���ӻ����εĲۺ��ź�
   connect(ui->action_line,SIGNAL(triggered()),this,SLOT(OnDrawLine())); //���ӻ�ֱ�ߵĲۺ��ź�
   connect(ui->action_ellipse,SIGNAL(triggered()),this,SLOT(OnDrawEllipse())); //���ӻ�Բ�Ĳۺ��ź�
   connect(ui->action_polygon,SIGNAL(triggered()),this,SLOT(OnDrawPolygon())); //���ӻ�����εĲۺ��ź�
   connect(ui->action_foldline,SIGNAL(triggered()),this,SLOT(OnDrawFoldLine())); //���ӻ����ߵĲۺ��ź�
   connect(ui->action_freeline,SIGNAL(triggered()),this,SLOT(OnDrawFreeLine())); //��������ֱ�ߵĲۺ��ź�
   connect(ui->action_blight_circle,SIGNAL(triggered()),this,SLOT(onDrawBlightCircle()));//��������/Բ���Ĳۺ��ź�
   connect(ui->action_text,SIGNAL(triggered()),this,SLOT(onDrawText()));
   connect(ui->action_RoundedRect,SIGNAL(triggered()),this,SLOT(OnCreateRoundedRect())); //Բ�Ǿ���
   connect(ui->action_ArcItem,SIGNAL(triggered()),this,SLOT(OnCreateArc())); //����

    //������
    //��ͼ������
    connect(ui->btn_rect,SIGNAL(clicked()),this,SLOT(OnDrawRect())); //���ӻ����εĲۺ��ź�
    connect(ui->btn_line,SIGNAL(clicked()),this,SLOT(OnDrawLine())); //���ӻ�ֱ�ߵĲۺ��ź�
    connect(ui->btn_elipse,SIGNAL(clicked()),this,SLOT(OnDrawEllipse())); //���ӻ�Բ�Ĳۺ��ź�
    connect(ui->btn_polygon,SIGNAL(clicked()),this,SLOT(OnDrawPolygon())); //���ӻ�����εĲۺ��ź�
    connect(ui->btn_foldline,SIGNAL(clicked()),this,SLOT(OnDrawFoldLine())); //���ӻ����ߵĲۺ��ź�
    connect(ui->btn_freeline,SIGNAL(clicked()),this,SLOT(OnDrawFreeLine())); //��������ֱ�ߵĲۺ��ź�
    connect(ui->btn_linecycle,SIGNAL(clicked()),this,SLOT(onDrawBlightCircle()));//��������/Բ���Ĳۺ��ź�
    connect(ui->btn_text,SIGNAL(clicked()),this,SLOT(onDrawText()));
    connect(ui->btn_roundrect,SIGNAL(clicked()),this,SLOT(OnCreateRoundedRect())); //Բ�Ǿ���
    connect(ui->btn_arc,SIGNAL(clicked()),this,SLOT(OnCreateArc())); //����

    //���ص����пؼ�
    connect(ui->btn_switch,SIGNAL(clicked()),this,SLOT(createbitbtndlg()));//����dataplay
    connect(ui->btn_MF,SIGNAL(clicked()),this,SLOT(createMFbtndlg()));//�๦�ܰ�ť

    connect(ui->btn_dataDisplay,SIGNAL(clicked()),this,SLOT(createvalue()));//��ֵ��ʾ
    connect(ui->dataplay,SIGNAL(triggered()),this,SLOT(createvalue()));//��ֵ��ʾ

    connect(ui->btn_metre,SIGNAL(clicked()),this,SLOT(createchart()));//ͼ��
    connect(ui->graphicsitem,SIGNAL(triggered()),this,SLOT(createchart()));//ͼ��

    connect(ui->btn_XYtrend,SIGNAL(clicked()),this,SLOT(createXYtrend()));//ͼ��
    connect(ui->action_X_Y,SIGNAL(triggered()),this,SLOT(createXYtrend()));//ͼ��

    connect(ui->btn_picture,SIGNAL(clicked()),this,SLOT(createimage()));//ͼƬ��ʾ��
    connect(ui->pictruedisplay,SIGNAL(triggered()),this,SLOT(createimage()));//ͼƬ��ʾ��

    connect(ui->btn_trend,SIGNAL(clicked()),this,SLOT(createtrendchartdlg()));//����
    connect(ui->btn_datagroup,SIGNAL(clicked()),this,SLOT(on_action_DatagroupDisplay_triggered()));//����Ⱥ��
    connect(ui->btn_hisdataDisplay,SIGNAL(clicked()),this,SLOT(createhisrecord()));//��ʷ������ʾ��
    connect(ui->btn_messageDisplay,SIGNAL(clicked()),this,SLOT(createmsgdisplay()));//��Ϣ��ʾ��
    connect(ui->btn_dyncircle,SIGNAL(clicked()),this,SLOT(createdyncricledlg()));//��̬Բ
    connect(ui->btn_dynrect,SIGNAL(clicked()),this,SLOT(createdynrentdlg()));//��̬����
    connect(ui->btn_flow,SIGNAL(clicked()),this,SLOT(createflowblock()));//������
    connect(ui->btn_animation,SIGNAL(clicked()),this,SLOT(OnCreateAnimaDlg()));//����
    connect(ui->btn_gif,SIGNAL(clicked()),this,SLOT(createstaticpicturedlg()));//GIF��ʾ��
    connect(ui->btn_alarmDisplay,SIGNAL(clicked()),this,SLOT(createalarmcontroldlg()));//������ʾ��
    connect(ui->btn_alarmbar,SIGNAL(clicked()),this,SLOT(createdynalarmbar()));//��̬������
    connect(ui->btn_hisalarmDisplay,SIGNAL(clicked()),this,SLOT(createhisalarm()));//��ʷ������ʾ��
    connect(ui->btn_combox,SIGNAL(clicked()),this,SLOT(OnCreateComboBoxDlg()));//����ѡ��ť
    connect(ui->pushButton_message,SIGNAL(clicked()),this,SLOT(OnCreateMessageBoard()));//���԰�
    connect(ui->pushButton_Combobox,SIGNAL(clicked()),this,SLOT(OnCreateComboBox()));//combobox
    connect(ui->btn_slider,SIGNAL(clicked()),this,SLOT(OnCreateSliderDlg()));//����ģ��������
    connect(ui->btn_recipeDisplay,SIGNAL(clicked()),this,SLOT(createrecipetable()));//�䷽��ʾ��
    connect(ui->btn_recipeselect,SIGNAL(clicked()),this,SLOT(ONRecipeChoice()));//�䷽ѡ����

    //��׼������edit by zqh
    connect(ui->action_reverse_selection,SIGNAL(triggered()),this,SLOT(Reverse_selection())); //����ѡ��
    connect(ui->action_group,SIGNAL(triggered()),this,SLOT(OnGroupItem()));     //������ϵĲۺ��ź�
    connect(ui->action_split,SIGNAL(triggered()),this,SLOT(OnDisGroupItem()));  //���Ӳ�ֵĲۺ��ź�
    connect(ui->action_delete,SIGNAL(triggered()),this,SLOT(OnDeleteItem())); //����ɾ���Ĳۺ��ź�
    connect(ui->action_copy,SIGNAL(triggered()),this,SLOT(OnCopyItem()));//����
    connect(ui->action_paste,SIGNAL(triggered()),this,SLOT(OnPasteItem()));//ճ��
    connect(ui->action_lock,SIGNAL(triggered()),this,SLOT(OnLockItem()));       //���������Ĳۺ��ź�
    connect(ui->action_delock,SIGNAL(triggered()),this,SLOT(OnUnLockItem()));   //���ӽ����Ĳۺ��ź�
    connect(ui->action_widthsame,SIGNAL(triggered()),this,SLOT(onWidthSame())); //����ѡ�ж���ȿ�
    connect(ui->action_heightsame,SIGNAL(triggered()),this,SLOT(onHeightSame())); //����ѡ�ж���ȸ�
    connect(ui->action_widthheightsame,SIGNAL(triggered()),this,SLOT(onWidthHeightSame())); //����ѡ�ж���ȿ�ȸ�
    /**********************************************************************
    *ͼ�εĶ��뷽ʽ
    *edit by zqh
    **********************************************************************/
    connect(ui->action_right,SIGNAL(triggered()),this,SLOT(OnSetRight()));  //�Ҷ���
    connect(ui->action_left,SIGNAL(triggered()),this,SLOT(OnSetLeft()));    //�����
    connect(ui->action_top,SIGNAL(triggered()),this,SLOT(OnSetTop()));     //�϶���
    connect(ui->action_under,SIGNAL(triggered()),this,SLOT(OnSetButtom()));//�¶���
    connect(ui->action_hcenter,SIGNAL(triggered()),this,SLOT(OnSetHCenter()));//ˮƽ���ж���
    connect(ui->action_vcenter,SIGNAL(triggered()),this,SLOT(OnSetVCenter()));//��ֱ���ж���

    connect(ui->action_horizontal,SIGNAL(triggered()),this,SLOT(OnSetHSpacingAlign()));//ˮƽ�ȼ�����
    connect(ui->action_vertcal,SIGNAL(triggered()),this,SLOT(OnSetVSpacingAlign()));//��ֱ�ȼ�����
    connect(ui->action_new_screen,SIGNAL(triggered()),this,SLOT(OnAddNewScreen()));//�½�����
    connect(ui->action_upscreen,SIGNAL(triggered()),this,SLOT(OnSetTheFrontScreen()));//��һ������
    connect(ui->action_nextscreen,SIGNAL(triggered()),this,SLOT(OnSetTheNextScreen()));//��һ������
    connect(this,SIGNAL(InitScreenDlg()),newScreenDlg,SLOT(InitScreenDlg()));
    connect(this,SIGNAL(InitWindowDlg()),newWindowDlg,SLOT(InitWindowDlg()));
    connect(this,SIGNAL(InitScreenPropertyDlg()),newScreenDlg,SLOT(InitScreenPropertyDlg()));
    connect(this,SIGNAL(InitWindowPropertyDlg()),newWindowDlg,SLOT(InitWindowPropertyDlg()));

    connect(ui->btn_table,SIGNAL(clicked()),this,SLOT(OnCreateTable()));//���
    connect(ui->btn_scale,SIGNAL(clicked()),this,SLOT(OnCreateScales()));//�̶�
    connect(ui->action_table,SIGNAL(triggered()),this,SLOT(OnCreateTable()));//���
    connect(ui->action_mark,SIGNAL(triggered()),this,SLOT(OnCreateScales()));//�̶�

   // connect(ui->btn_library,SIGNAL(clicked()),this,SLOT(on_action_open_mapstorage_triggered()));//ͼ��

    //connect(ui->action_stateon,SIGNAL(triggered()),this,SLOT(OnSetONState()));//����ΪON״̬
    //connect(ui->action_state0,SIGNAL(triggered()),this,SLOT(OnSetOFFState()));//����ΪOFF״̬

    connect(ui->action_zoonbig,SIGNAL(triggered()),this,SLOT(OnSetZoomEnlarge()));//�Ŵ�
    connect(ui->action_zoonfit,SIGNAL(triggered()),this,SLOT(OnSetZoomFit()));//��ԭ
    connect(ui->action_zoonsmall,SIGNAL(triggered()),this,SLOT(OnSetZoomSmall()));//��С
    connect(ui->action_grid,SIGNAL(triggered()),this,SLOT(OnSetSceneGrid()));//����
    connect(ui->action_panview,SIGNAL(triggered()),this,SLOT(OnSetDagViewModel()));//ƽ����ͼ
    connect(ui->action_arrow,SIGNAL(triggered()),this,SLOT(OnSetDagViewModelArrow()));//���ʱ��ͷ
    connect(ui->action_openpropertiset,SIGNAL(triggered()),this,SLOT(OnOpenPropertyDlg()));//�����ԶԻ���
    connect(ui->action_address_find,SIGNAL(triggered()),this,SLOT(OnFindAddressDlg()));//�򿪲��ҵ�ַ�Ի���
    connect(ui->action_address_table,SIGNAL(triggered()),this,SLOT(OnDisplayAddrUseDlg()));//�򿪵�ַʹ��һ����Ի���
    connect(ui->action_USBdownload,SIGNAL(triggered()),this,SLOT(USB_DownLoad()));

    connect(this,SIGNAL(newscreen_Assign()),newScreenDlg,SLOT(newscreen_Assign()));
    connect(this,SIGNAL(newwindow_Assign()),newWindowDlg,SLOT(newwindow_Assign()));
    connect(this,SIGNAL(screenProperty_assign()),newScreenDlg,SLOT(screenProperty_assign()));
    connect(this,SIGNAL(windowProperty_assign()),newWindowDlg,SLOT(windowProperty_assign()));
    connect(this,SIGNAL(copyScreen()),newScreenDlg,SLOT(copyScreen()));
    connect(this,SIGNAL(copyWindow()),newWindowDlg,SLOT(copyWindow()));
    connect(this,SIGNAL(deleteScreen()),newScreenDlg,SLOT(deleteScreen()));
    connect(this,SIGNAL(deleteWindow()),newWindowDlg,SLOT(deleteWindow()));
    connect(this,SIGNAL(showNumDlg(QString,QTreeWidgetItem *)),this,SLOT(showNumDlg_ScreenAndWindow(QString,QTreeWidgetItem *)));
    connect(ui->action_close,SIGNAL(triggered()),this,SLOT(closeProject()));//�رչ���
    openInit_MenuAndTool();
    connect(this,SIGNAL(upDate_treeScreenItem()),this,SLOT(upDatetreeScreenItem()));
    connect(this,SIGNAL(reTreeScreenAndWindow()),this,SLOT(reTree_ScreenAndWindow()));
    connect(this,SIGNAL(openProreTreeCtl()),this,SLOT(openPro_reTreeCtl()));
    //connect(ui->action_singleselect,SIGNAL(triggered()),this,SLOT(OnCreateSingleSelectDlg())); //��ѡ��ť
    connect(ui->action_ComboBox,SIGNAL(triggered()),this,SLOT(OnCreateComboBoxDlg())); //�๦��ѡ��ť
    connect(ui->action_Slider,SIGNAL(triggered()),this,SLOT(OnCreateSliderDlg())); //����ģ��������
    //connect(ui->action_compile,SIGNAL(triggered()),this,SLOT(StartCompileThread())); //����
    connect(ui->action_Animation,SIGNAL(triggered()),this,SLOT(OnCreateAnimaDlg())); //����
    //connect(ui->action_MsgBoard,SIGNAL(triggered()),this,SLOT(OnCreateMsgBoard())); //���԰�
    //connect(ui->action_P,SIGNAL(triggered()),this,SLOT(OpenHmiSetting()));//�趨-������һ���������
    //connect(ui->action_96,SIGNAL(triggered()),this,SLOT(OpenHmiSetting()));//�趨-��ȱ���
    //connect(ui->action_97,SIGNAL(triggered()),this,SLOT(OpenHmiSetting()));//�趨-��λ����
    //connect(ui->action_R_2,SIGNAL(triggered()),this,SLOT(OpenRecipe()));//�趨-�䷽
    //connect(ui->action_M,SIGNAL(triggered()),this,SLOT(OpenFileProtection()));//�趨-�ļ�����
    connect(ui->action_h,SIGNAL(triggered()),this,SLOT(OnSetHMirror())); //ˮƽ����
    connect(ui->action_v,SIGNAL(triggered()),this,SLOT(OnSetVMirror())); //��ֱ����
    connect(ui->action_cut,SIGNAL(triggered()),this,SLOT(OnCutItem())); //����
    connect(ui->action_offline_simulation,SIGNAL(triggered()),this,SLOT(ExecuteOffLineMonitor())); //����ģ��

    connect(ui->action_SamDraw3_4,SIGNAL(triggered()),this,SLOT(RunAboutDlg())); //���ڶԻ���
    connect(ui->action_copym,SIGNAL(triggered()),this,SLOT(MultiCopyDlg())); //���ظ���
    //״̬��������ĸ�QLINEEDIT�ĸı��¼�
    connect(lab_left_space_statusBar,SIGNAL(editingFinished()),this,SLOT(changeItem_x()));
    connect(lab_up_space_statusBar,SIGNAL(editingFinished()),this,SLOT(changeItem_y()));
    connect(lab_width_space_statusBar,SIGNAL(editingFinished()),this,SLOT(changeItem_w()));
    connect(lab_hidth_space_statusBar,SIGNAL(editingFinished()),this,SLOT(changeItem_h()));
    connect(ui->action_english,SIGNAL(triggered()),this,SLOT(ChangetoEnglish()));
    connect(ui->action_chinese,SIGNAL(triggered()),this,SLOT(ChangetoChinese()));
    ui->action_chinese->setCheckable(true);
    ui->action_english->setCheckable(true);
    ui->action_chinese->setChecked(true);
    /*�����Ǻ�ָ��༭���ܴ�����������Ĳۺ���*/
    //connect(ui->action_macro,SIGNAL(triggered()),this,SLOT(MarcoEdit()));
    connect(ui->action_H,SIGNAL(triggered()),this,SLOT(LoadProjectHelp()));
    loadBaseLibAndUserDefineLib(); //���ػ���ͼ��
    thread = new CompileThrd();
    connect(thread,SIGNAL(SignalStartDownload()),this,SLOT(StartDownload()));
	connect(thread,SIGNAL(SignalStartsimulator()),this,SLOT(StartSimulator_off()));
    connect(thread,SIGNAL(message(QString, MSG_TYPE)),this,SLOT(MessageOut(QString, MSG_TYPE)));

    connect(thread,SIGNAL(SignalCompileEnd()), this, SLOT(SignalCompileEnd()));
    threadDownload = new downloadTrd();
    connect(threadDownload, SIGNAL(finished()), this, SLOT(downFinished()));

    connect(this,SIGNAL(SignalInformation(QString, MSG_TYPE)),this,SLOT(MessageOut(QString, MSG_TYPE)));

    transparent tor;
    if(is_tanslator==0 )
    {
        tor.toChinese();
        ui->action_chinese->setChecked(true);
        ui->action_english->setChecked(false);
    }
    else if( is_tanslator==1)
    {
        tor.toEnglish();
        ui->action_english->setChecked(true);
        ui->action_chinese->setChecked(false);
    }
    bCpyAndPaste = false;
    QDir compiledir = QDir("compile");
    if(!compiledir.exists())
    {
        compiledir.mkpath(compiledir.absolutePath());
    }
    pwnd->lab_control_statusBar->setEnabled(false);
    pwnd->lab_width_space_statusBar->setEnabled(false);
    pwnd->lab_hidth_space_statusBar->setEnabled(false);
    pwnd->lab_left_space_statusBar->setEnabled(false);
    pwnd->lab_up_space_statusBar->setEnabled(false);
    pwnd->lab_control_statusBar->setText("");
    pwnd->lab_width_space_statusBar->setText("");
    pwnd->lab_hidth_space_statusBar->setText("");
    pwnd->lab_left_space_statusBar->setText("");
    pwnd->lab_up_space_statusBar->setText("");
    bToolBarCMBInit = true;
    //��� ��ʼ��Э���
    vPlc = QProtocolTool::getAllProtocols();
    m_factoryMap = QProtocolTool::getDriversConfig();
    //����ϵͳ������
    loadSysLibs();
    /*ui->dockWidget->setVisible(false);
    ui->toolBox->setVisible(false);
    ui->dockWidget->setFixedSize(161,291);*/
    setToolBoxFloat();

    pwnd->setWindowTitle(PRO_FULL_NAME);
    //ui->action_SamDraw3_4->setText(tr("����") + PRO_FULL_NAME);
    //ui->action_SamDraw3_4->setText(tr("����"));

    pSimDlg = NULL;
}

void MainWindow::init()
{
    if(m_pSamSysParame)
    {
        delete m_pSamSysParame;
        m_pSamSysParame = NULL;
    }
    setProVersion(AK_CURRENT_VERSION);
    m_pSamSysParame = new QSamSysParame();
    PLC_COMMUNICATE_PROP PLC_com1 ;
    m_pSamSysParame->m_qvcPlcCommunicate.push_back(PLC_com1);

    //Ϊ�������3���������ܱ�ɾ��
    stConnect con;
    for(int i = 0; i < 6; i++)//�������0������1������2,��̫��
    {
        con.id = i;
        if(0 == i)
        {
            con.sConnectName = tr("Com1");//QString(tr("����"))+QString::number(i);
        }
        else if(1 == i)
        {
            con.sConnectName = tr("Com2");//QString(tr("����"))+QString::number(i);
        }
        else if(2 == i)
        {
            con.sConnectName = tr("Com3");//QString(tr("����"))+QString::number(i);
        }
        else if(3 == i)
        {
            con.sConnectName = tr("����");//QString(tr("����"))+QString::number(i);
        }
        else if(4 == i)
        {
            con.sConnectName = tr("CAN1");//QString(tr("����"))+QString::number(i);
        }
        else if(5 == i)
        {
            con.sConnectName = tr("CAN2");//QString(tr("����"))+QString::number(i);
        }
        //con.sConnectName = QString(tr("����"))+QString::number(i);
        con.eConnectPort = i;//com1
        con.bUseRelationPort = false;//Ĭ�ϲ�ת��
        con.eRelationPort = 0;
        con.nScreenNo = 1;
        con.nBaudRate = 9600;
        if(4==i || 5==i)
        {
            con.nBaudRate = 500;
        }
        con.nDataBits = 1;
        con.nStopBit = 0;
        con.nCheckType = 0;

        con.bMasterScreen      = 1;//����
        con.bConnectScreenPort = 0;//����PLC��
        con.nSlaveScreenNum    = 1;

        //con.nIntervalTime = 1;
        con.sIpAddr = QString("192.168.1.1");
        con.nNetPortNum = 12345;

        QTreeWidgetItem *wTemp;
        wTemp=new QTreeWidgetItem(link,QStringList(tr("")));
        pwnd->vTreeLinkType.append(wTemp);
        link->insertChild(1,vTreeLinkType.last());
        vTreeLinkType.last()->setIcon(0,QIcon(":/tree/images/tree/com.ico"));
        vTreeLinkType.last()->setText(0,con.sConnectName);
        m_pSamSysParame->m_qvcConnect.push_back(con);
    }
    pwnd->setWindowTitle(PRO_FULL_NAME);
    //ui->action_SamDraw3_4->setText(tr("����") + PRO_FULL_NAME);
    //ui->action_SamDraw3_4->setText(tr("����"));
    //XXXXX
    /*if(languagedlg)
    {
        delete languagedlg;
        languagedlg = NULL;
    }
    languagedlg = new  QTreeCtrlLanguageDlg(this);*/

    /*��ʼ���������*/

    /*��ʼ���䷽�Ի���*/
    //initRecipeDlg();//��ʼ���䷽
    //if(recipeDlg)
    //{
    //    delete recipeDlg;
    //    recipeDlg = NULL;
    //}
    //recipeDlg=new QTreeCtrlRecipeDlg(this);//�䷽�Ի���;

    if(newpro)
    {
        delete newpro;
        newpro = NULL;
    }
    newpro = new  QNewPro;
    librarys.clear();
    macros.clear();
    g_Vars.clear();//wxy
    m_Ids.clear();
}


MainWindow::~MainWindow()
{
    int i = 0;

    if(threadDownload)
    {
        threadDownload->deleteLater();
        threadDownload = NULL;
    }

    if(pMenuSpace)
    {
        delete pMenuSpace;
        pMenuSpace = NULL;
    }

    if(pMenuAlign)
    {
        delete pMenuAlign;
        pMenuAlign = NULL;
    }

    if(pMenuZXu)
    {
        delete pMenuZXu;
        pMenuZXu = NULL;
    }

    if(qLanguagecmb)
    {
        delete qLanguagecmb;
        qLanguagecmb = NULL;
    }

    if(statusButtoncmb)
    {
        delete statusButtoncmb;
        statusButtoncmb = NULL;
    }

    if(pChScreen)
    {
        delete pChScreen;
        pChScreen = NULL;
    }

    for(i = 0; i < vBaseLibraryScene.size();i++)
    {
        delete vBaseLibraryScene[i];
    }
    vBaseLibraryScene.clear();

    QProcess::execute("adb kill-server ");
    delete ui;
}

void MainWindow::HandleRedoUndo()
{
    //transparent tor;
    if(ui->action_chinese->isChecked())
    {
        undoAction->setText(tr("����"));
        undoAction->setIconText(tr("����"));
        redoAction->setText(tr("�ָ�"));
        redoAction->setIconText(tr("�ָ�"));
        //tor.toChinese();
    }
    else
    {
        undoAction->setText(tr("Undo"));
        undoAction->setIconText(tr("Undo"));
        redoAction->setText(tr("Redo"));
        redoAction->setIconText(tr("Redo"));
        //tor.toEnglish();
    }
    if(nActiveSheetIndex < pSceneSheet.size())
    {
        pSceneSheet[nActiveSheetIndex]->update();
    }
}

/******************************************************************
*����action
*******************************************************************/
void MainWindow::createActions()
{
    undoAction = undoStack->createUndoAction(this, tr("����"));
    undoAction->setStatusTip(tr("������������"));
    undoAction->setIcon(QIcon(":/standardtool/images/standardtool/undo.ico"));
    undoAction->setObjectName(QString::fromUtf8("action_undo"));
    undoAction->setShortcuts(QKeySequence::Undo);
    undoAction->setIconText(tr("\n����"));

    redoAction = undoStack->createRedoAction(this, tr("�ָ�"));
    redoAction->setIcon(QIcon(":/standardtool/images/standardtool/redo.ico"));
    redoAction->setStatusTip(tr("�ָ���������"));
    redoAction->setObjectName(QString::fromUtf8("action_redo"));
    redoAction->setShortcuts(QKeySequence::Redo);
    redoAction->setIconText(tr("\n�ָ�"));

    if(is_tanslator == 0)
    {
        undoAction->setIconText(tr("\n����"));
        redoAction->setIconText(tr("\n�ָ�"));
    }
    else if(is_tanslator == 1)
    {
        undoAction->setIconText(tr("Undo"));
        redoAction->setIconText(tr("Redo"));
    }

    connect(undoStack,SIGNAL(undoTextChanged(const QString)),this,SLOT(HandleRedoUndo()));
    connect(undoStack,SIGNAL(redoTextChanged(const QString)),this,SLOT(HandleRedoUndo()));

    //connect(undoStack,SIGNAL(canUndoChanged(bool)),this,SLOT(HandleRedoUndo()));
    //connect(undoStack,SIGNAL(canRedoChanged(bool)),this,SLOT(HandleRedoUndo()));

    deleteAction = new QAction(tr("Delete"), this);
    deleteAction->setShortcut(tr("Del"));
    deleteAction->setIcon(QIcon(":/file/images/res/delete1.bmp"));
    deleteAction->setStatusTip(tr("ɾ����Ŀ"));

    for (int i = 0; i < MaxRecentFiles; ++i) //4������򿪵��ĵ�
    {
        recentFileActs[i] = new QAction(this);
        recentFileActs[i]->setVisible(false);
        connect(recentFileActs[i], SIGNAL(triggered()),this, SLOT(openRecentFile()));
    }
}

/******************************************************************
*��Ӳ˵�����action���ò����������޷���ui��ͼ��ƣ����ô������
*******************************************************************/
void MainWindow::createMenu()
{
    ui->menu_E->addAction(ui->action_macro_find);//��ָ����
    ui->menu_E->addAction(ui->action_macro_admin);//��ָ��༭��

//    ui->menu_thing->addAction(ui->action_mfaction);//�๦�ܼ�
//    ui->menu_thing->addAction(ui->action_flow_block);//������
//    ui->menu_thing->addAction(ui->action_his_tre_display);//��ʷ������ʾ��
//    ui->menu_thing->addAction(ui->action_timer);//��ʱ��
//    ui->menu_thing->addAction(ui->action_Pie);//����
//    ui->menu_thing->addAction(ui->action_Steping);//����
//    ui->menu_thing->addAction(ui->action_singleselect);//��ѡ
//    ui->menu_thing->addAction(ui->action_ComboBox);//����
//    ui->menu_thing->addAction(ui->action_Slider);//����
//    ui->menu_thing->addAction(ui->action_Animation);//����
//    ui->menu_thing->addAction(ui->action_MsgBoard);//���԰�

    /*��������ӳ���,�ָ����ܵĲ˵�*/
    ui->menu_E->insertAction(ui->action_cut,undoAction);
    ui->menu_E->insertAction(ui->action_cut,redoAction);
    ui->menu_E->insertSeparator(ui->action_cut);

    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        //ui->menu_F->addAction(recentFileActs[i]);
        ui->menu_recentFile->addAction(recentFileActs[i]);
    }
    updateRecentFileActions();//��������򿪵��ĵ�
}


/******************************************************************
*����������
*******************************************************************/
void MainWindow::createToolBars()
{
    //addToolBar(ui->standardToolBar);
    //addToolBarBreak(Qt::TopToolBarArea);

    //addToolBar(ui->mapToolBar);
    //addToolBarBreak(Qt::TopToolBarArea);

    //addToolBar(ui->thingToolBar);
    //addToolBarBreak(Qt::TopToolBarArea);

    //addToolBarBreak(Qt::TopToolBarArea);

    QWidget* widgetCmb = new QWidget(ui->mapToolBar);
    QVBoxLayout* vBoxLayoutCmb = new QVBoxLayout;

    statusButtoncmb = new QComboBox();
    statusButtoncmb->clear();
    statusButtoncmb->setFocusPolicy(
    Qt::FocusPolicy(statusButtoncmb->focusPolicy()&(~Qt::TabFocus)));
    statusButtoncmb->setStyleSheet("background-color: rgb(255, 255, 255);");

    qButtonLab = new QLabel();
    qButtonLab->setStyleSheet("background-color: rgb(197, 222, 255);");
    qButtonLab->setText(tr("״̬"));;
    qButtonLab->setEnabled(true);
    QHBoxLayout* hBoxLayoutBtnCmb = new QHBoxLayout;
    hBoxLayoutBtnCmb->addWidget(statusButtoncmb);
    hBoxLayoutBtnCmb->addWidget(qButtonLab);
    vBoxLayoutCmb->addLayout(hBoxLayoutBtnCmb);

    qLanguagecmb=new QComboBox();
    qLanguagecmb->clear();
    qLanguagecmb->setFocusPolicy(
    Qt::FocusPolicy(qLanguagecmb->focusPolicy()&(~Qt::TabFocus)));
    qLanguagecmb->setStyleSheet("background-color: rgb(255, 255, 255);");

    qLanguageLab = new QLabel();
    qLanguageLab->setText(tr("����"));
    qLanguageLab->setStyleSheet("background-color: rgb(197, 222, 255);");
    qLanguageLab->setEnabled(true);
    QHBoxLayout* hBoxLayoutLanCmb = new QHBoxLayout;
    hBoxLayoutLanCmb->addWidget(qLanguagecmb);
    hBoxLayoutLanCmb->addWidget(qLanguageLab);
    vBoxLayoutCmb->addLayout(hBoxLayoutLanCmb);;

    pChScreen = new QComboBox();
    pChScreen->clear();
    pChScreen->setFixedWidth(/*100*/120);
    pChScreen->setFocusPolicy(Qt::FocusPolicy(pChScreen->focusPolicy()&(~Qt::TabFocus)));
    pChScreen->setStyleSheet("background-color: rgb(255, 255, 255);");
    vBoxLayoutCmb->addWidget(pChScreen);

    widgetCmb->setLayout(vBoxLayoutCmb);
    widgetCmb->setStyleSheet("font: 9pt '����';");
    ui->mapToolBar->insertWidget(ui->action_group,widgetCmb);

    ui->standardToolBar->insertAction(ui->action_cut,undoAction);
    ui->standardToolBar->insertAction(undoAction,redoAction);

    connect(statusButtoncmb,SIGNAL(currentIndexChanged(int)),this,SLOT(onFrmStatecmbChange(int)));
    connect(qLanguagecmb,SIGNAL(currentIndexChanged(int)),this,SLOT(onFrmLanguageChange(int)));
    connect(pChScreen,SIGNAL(currentIndexChanged(int)),this,SLOT(onScreenChange(int)));

    ui->standardToolBar->setMinimumSize(1,85);
    ui->mapToolBar->setMinimumSize(1,85);
}

/******************************************************************
*����״̬��
*******************************************************************/
void MainWindow::createStatusBar()
{

    lab_control_statusBar=new QLabel(tr("��ť����"));
    lab_control_statusBar->setFrameShadow(QFrame::Sunken); //���ñ�ǩ��Ӱ
    lab_control_statusBar->setFixedWidth(100);

    lab_Coordinate_statusBar=new QLabel(tr("�ؼ�����"));
    lab_Coordinate_statusBar->setFrameShadow(QFrame::Sunken); //���ñ�ǩ��Ӱ
    lab_Coordinate_statusBar->setFixedWidth(80);

    lab_up_statusBar=new QLabel(tr("��:"));
    lab_up_statusBar->setFrameShadow(QFrame::Sunken);


    lab_up_space_statusBar=new QLineEdit;
    lab_up_space_statusBar->setFocusPolicy(
            Qt::FocusPolicy(lab_up_space_statusBar->focusPolicy()&(~Qt::TabFocus)));
    lab_up_space_statusBar->setFixedWidth(60);
    lab_up_space_statusBar->setEnabled(false);
    QDoubleValidator  *validator4 = new QDoubleValidator(lab_up_space_statusBar );
    validator4->setDecimals(1);
    lab_up_space_statusBar->setValidator( validator4 );

    lab_left_statusBar=new QLabel(tr("��:"));
    lab_left_statusBar->setFrameShadow(QFrame::Sunken);

    lab_left_space_statusBar=new QLineEdit;
    lab_left_space_statusBar->setFocusPolicy(
            Qt::FocusPolicy(lab_left_space_statusBar->focusPolicy()&(~Qt::TabFocus)));
    lab_left_space_statusBar->setFixedWidth(60);
    lab_left_space_statusBar->setEnabled(false);
   // QRegExp regx1("^[0-9.]*$");
    QDoubleValidator  *validator1 = new QDoubleValidator(lab_left_space_statusBar );
    validator1->setDecimals(1);
 //   QValidator *validator1 = new QRegExpValidator(regx1, lab_left_space_statusBar );
    lab_left_space_statusBar->setValidator( validator1 );

    lab_size_statusBar=new QLabel(tr("�ؼ���С"));
    lab_size_statusBar->setFrameShadow(QFrame::Sunken);

    lab_width_statusBar=new QLabel(tr("��:"));
    lab_width_statusBar->setFrameShadow(QFrame::Sunken);

    lab_width_space_statusBar=new QLineEdit;
    lab_width_space_statusBar->setFocusPolicy(
            Qt::FocusPolicy(lab_width_space_statusBar->focusPolicy()&(~Qt::TabFocus)));
    lab_width_space_statusBar->setFixedWidth(60);
    lab_width_space_statusBar->setEnabled(false);
    QDoubleValidator  *validator2 = new QDoubleValidator(lab_width_space_statusBar );
    validator2->setDecimals(1);
    lab_width_space_statusBar->setValidator( validator2 );

    lab_hight_statusBar=new QLabel(tr("��:"));
    lab_hight_statusBar->setFrameShadow(QFrame::Sunken);

    lab_hidth_space_statusBar=new QLineEdit;
    lab_hidth_space_statusBar->setFocusPolicy(
            Qt::FocusPolicy(lab_hidth_space_statusBar->focusPolicy()&(~Qt::TabFocus)));
    lab_hidth_space_statusBar->setFixedWidth(60);
    lab_hidth_space_statusBar->setEnabled(false);
    QDoubleValidator  *validator3 = new QDoubleValidator(lab_hidth_space_statusBar );
    validator3->setDecimals(1);
    lab_hidth_space_statusBar->setValidator( validator3 );

#ifdef AK_SAMKOON
    lab_samkoon_statusBar=new QLabel(tr("�ԿؿƼ�"));
#else define LA_DEBINUO
    //lab_samkoon_statusBar=new QLabel(tr("�±�ŵ"));
    lab_samkoon_statusBar=new QLabel(tr(""));
#endif
    lab_samkoon_statusBar->setFixedWidth(200);
    lab_samkoon_statusBar->setFrameShadow(QFrame::Sunken);
    ui->statusBar->addPermanentWidget(lab_control_statusBar);
    ui->statusBar->addPermanentWidget(lab_Coordinate_statusBar);
    ui->statusBar->addPermanentWidget(lab_left_statusBar);
    ui->statusBar->addPermanentWidget(lab_left_space_statusBar);
    ui->statusBar->addPermanentWidget(lab_up_statusBar);
    ui->statusBar->addPermanentWidget(lab_up_space_statusBar);
    ui->statusBar->addPermanentWidget(lab_size_statusBar);
    ui->statusBar->addPermanentWidget(lab_width_statusBar);
    ui->statusBar->addPermanentWidget(lab_width_space_statusBar);
    ui->statusBar->addPermanentWidget(lab_hight_statusBar);
    ui->statusBar->addPermanentWidget(lab_hidth_space_statusBar);
    ui->statusBar->addPermanentWidget(lab_samkoon_statusBar);
    ui->statusBar->setSizeGripEnabled(true);
    ui->statusBar->showMessage(tr("����") );

    pwnd->lab_control_statusBar->setEnabled(false);
    pwnd->lab_width_space_statusBar->setEnabled(false);
    pwnd->lab_hidth_space_statusBar->setEnabled(false);
    pwnd->lab_left_space_statusBar->setEnabled(false);
    pwnd->lab_up_space_statusBar->setEnabled(false);

    pwnd->lab_control_statusBar->setText("");
    pwnd->lab_width_space_statusBar->setText("");
    pwnd->lab_hidth_space_statusBar->setText("");
    pwnd->lab_left_space_statusBar->setText("");
    pwnd->lab_up_space_statusBar->setText("");
}//



/************************************************************************
*�ú������������������Ŀ¼
************************************************************************/
void MainWindow::initLeftDocking()
{

    tree=new mytreeWidget();
    tree->setFocusPolicy(Qt::NoFocus);
    tree->setColumnCount(1);
    tree->setHeaderHidden(true);
    root = new QTreeWidgetItem(tree, QStringList(tr("������")));

    root->setIcon(0,QIcon(":/tree/images/tree/HMI.ico"));

    //+++++
    //ϵͳ����
    link = new QTreeWidgetItem(root, QStringList(tr("��������")));
    root->addChild(link);
    link->setIcon(0,QIcon(":/tree/images/tree/com.ico"));
    //plcConnect = new QTreeWidgetItem(root, QStringList(tr("��������")));
    //root->addChild(plcConnect);

 #ifdef AKPLC
    PlcNode = new QTreeWidgetItem(root, QStringList(tr("PLC���")));
    root->addChild(PlcNode);
    PlcNode->setIcon(0,QIcon(":/tree/images/tree/HMIsetting.ico"));
#endif

    sysSetting = new QTreeWidgetItem(root, QStringList(tr("ϵͳ����")));
    root->addChild(sysSetting);
    sysSetting->setIcon(0,QIcon(":/tree/images/tree/HMIsetting.ico"));

    pcCtrl = new QTreeWidgetItem(sysSetting, QStringList(tr("��������")));
    sysSetting->addChild(pcCtrl);
    pcCtrl->setIcon(0,QIcon(":/tree/images/tree/PCManager.ico"));//�õ������ӵ�ͼ��

    pcChoice = new QTreeWidgetItem(pcCtrl, QStringList(tr("����ѡ��")));
    pcCtrl->addChild(pcChoice);
    pcChoice->setIcon(0,QIcon(":/tree/images/tree/HMISelect.ico"));

    displaySet = new QTreeWidgetItem(pcCtrl, QStringList(tr("��ʾ����")));
    pcCtrl->addChild(displaySet);
    displaySet->setIcon(0,QIcon(":/tree/images/tree/showseting.ico"));

    operateSet = new QTreeWidgetItem(pcCtrl, QStringList(tr("��������")));
    pcCtrl->addChild(operateSet);
    operateSet->setIcon(0,QIcon(":/tree/images/tree/operatorset.ico"));

    dataCtrl = new QTreeWidgetItem(pcCtrl, QStringList(tr("���ݿ���")));
    pcCtrl->addChild(dataCtrl);
    dataCtrl->setIcon(0,QIcon(":/tree/images/tree/datactrol.ico"));

    //timeArea = new QTreeWidgetItem(pcCtrl, QStringList(tr("ʱ��&����")));
    //pcCtrl->addChild(timeArea);

    permissionSec = new QTreeWidgetItem(pcCtrl, QStringList(tr("�û�Ȩ��")));
    pcCtrl->addChild(permissionSec);
    permissionSec->setIcon(0,QIcon(":/tree/images/tree/User.ico"));

    hostPeri = new QTreeWidgetItem(sysSetting, QStringList(tr("��������")));
    sysSetting->addChild(hostPeri);
    hostPeri->setIcon(0,QIcon(":/tree/images/tree/PLCcontral.ico"));//�õ���PLC���Ƶ�ͼ��

    //plcCtrl = new QTreeWidgetItem(hostPeri, QStringList(tr("PLC����")));
    //hostPeri->addChild(plcCtrl);
    printer = new QTreeWidgetItem(hostPeri, QStringList(tr("��ӡ��")));
    hostPeri->addChild(printer);
    printer->setIcon(0,QIcon(":/tree/images/tree/printer.ico"));//�õ��Ǵ�ӡ����ͼ��

    //networkAd = new QTreeWidgetItem(hostPeri, QStringList(tr("����������")));
    //hostPeri->addChild(networkAd);

    confiWorks = new QTreeWidgetItem(sysSetting, QStringList(tr("��̬����")));
    sysSetting->addChild(confiWorks);
    confiWorks->setIcon(0,QIcon(":/tree/images/tree/zutaiprj.ico"));//�õ���HMI������ͼ��

    downloadSet = new QTreeWidgetItem(confiWorks, QStringList(tr("��������")));
    confiWorks->addChild(downloadSet);
    downloadSet->setIcon(0,QIcon(":/tree/images/tree/downset.ico"));

    accessEncry = new QTreeWidgetItem(confiWorks, QStringList(tr("���ʼ���")));
    confiWorks->addChild(accessEncry);
    accessEncry->setIcon(0,QIcon(":/tree/images/tree/prjpsw.ico"));

    //������õ�ʱ������
    clock=new QTreeWidgetItem(confiWorks,QStringList(tr("ʱ������")));
    confiWorks->addChild(clock);
    clock->setIcon(0,QIcon(":/tree/images/tree/clock.ico"));

    productLicen = new QTreeWidgetItem(confiWorks, QStringList(tr("��Ʒ��Ȩ")));
    confiWorks->addChild(productLicen);
    productLicen->setIcon(0,QIcon(":/tree/images/tree/product.ico"));

    lanSet = new QTreeWidgetItem(confiWorks, QStringList(tr("��������")));
    confiWorks->addChild(lanSet);
    lanSet->setIcon(0,QIcon(":/btn/images/yuy.ico"));
    chdItem = new QTreeWidgetItem(confiWorks, QStringList(tr("����洢������")));
    confiWorks->addChild(chdItem);
    chdItem->setIcon(0,QIcon(":/standardtool/images/power.ico"));
    //xiaoqiang
    //��ӻ�����
    /*screen = new QTreeWidgetItem(root,QStringList(tr("����")));
    root->addChild(screen);
    screen->setIcon(0,QIcon(":/tree/images/tree/screen.ico"));

    //��Ӵ�����
    window = new QTreeWidgetItem(root,QStringList(tr("����")));
    root->addChild(window);
    window->setIcon(0,QIcon(":/tree/images/tree/window.ico"));

    //����Զ������
    TreeKeyboard=new QTreeWidgetItem(root,QStringList(tr("�Զ������")));
    root->insertChild(0,TreeKeyboard);
    TreeKeyboard->setIcon(0,QIcon(":/tree/images/tree/keyboard.ico"));
    TreeKeyboard->setHidden(true);*/

    //�����ʷ�����ռ�����
    tree_hisdatalog=new QTreeWidgetItem(root,QStringList(tr("���ݲɼ�")));
    root->addChild(tree_hisdatalog);
    tree_hisdatalog->setIcon(0,QIcon(":/tree/images/tree/hisdata.ico"));

    //��ӱ�����½��
    alarmlog=new QTreeWidgetItem(root,QStringList(tr("������¼")));
    root->addChild(alarmlog);
    alarmlog->setIcon(0,QIcon(":/btn/images/alarm.ico"));

    tree_macro = new QTreeWidgetItem(root,QStringList(tr("�ű�")));
    root->addChild(tree_macro);
    tree_macro->setIcon(0,QIcon(":/tree/images/tree/script.ico"));

    global_macro = new QTreeWidgetItem(tree_macro,QStringList(tr("ȫ�ֽű�")));
    tree_macro->addChild(global_macro);
    global_macro->setIcon(0,QIcon(":/tree/images/tree/globalScript.ico"));
    init_macro = new QTreeWidgetItem(tree_macro,QStringList(tr("��ʼ���ű�")));
    tree_macro->addChild(init_macro);
    init_macro->setIcon(0,QIcon(":/tree/images/tree/initScrpit.ico"));

    //����䷽��
    recipe=new QTreeWidgetItem(root,QStringList(tr("�䷽")));
    root->addChild(recipe);
    recipe->setIcon(0,QIcon(":/tree/images/tree/recipe.ico"));
    datatransport=new QTreeWidgetItem(root,QStringList(tr("���ϴ���")));
    root->addChild(datatransport);
    datatransport->setIcon(0,QIcon(":/tree/images/tree/import.ico"));

    treeScheduler=new QTreeWidgetItem(root,QStringList(tr("ʱ���")));
    root->addChild(treeScheduler);
    treeScheduler->setIcon(0,QIcon(":/tree/images/tree/import.ico"));

    //tree_varRcd=new QTreeWidgetItem(root,QStringList(tr("������")));
    //root->addChild(tree_varRcd);
    //tree_varRcd->setIcon(0,QIcon(":/tree/images/tree/import.ico"));
//    sub_Recipe=new QTreeWidgetItem(recipe,QStringList(tr("�䷽1")));
//    recipe->addChild(sub_Recipe);
//    sub_Recipe->setIcon(0,QIcon(":/tree/images/tree/recipe.ico"));
//    sub_Recipe->setHidden(true);

    //xiaoqiang
    tree0 = new mytreeWidget();
    tree0->setFocusPolicy(Qt::NoFocus);
    tree0->setColumnCount(1);
    tree0->setHeaderHidden(true);

    root0 = new QTreeWidgetItem(tree0, QStringList(tr("����&����")));
    root0->setIcon(0,QIcon(":/tree/images/tree/HMI.ico"));

    //��ӻ�����
    screen = new QTreeWidgetItem(root0,QStringList(tr("����")));
    root0->addChild(screen);
    screen->setIcon(0,QIcon(":/tree/images/tree/screen.ico"));

    //��Ӵ�����
    window = new QTreeWidgetItem(root0,QStringList(tr("����")));
    root0->addChild(window);
    window->setIcon(0,QIcon(":/tree/images/tree/window.ico"));

    //����Զ������
    TreeKeyboard=new QTreeWidgetItem(root0,QStringList(tr("�Զ������")));
    root0->insertChild(0,TreeKeyboard);
    TreeKeyboard->setIcon(0,QIcon(":/tree/images/tree/keyboard.ico"));
    TreeKeyboard->setHidden(true);
    //--------------------------end--------------------------------

    //tree->expandAll();
    //Ϊ���οؼ����˫����Ӧ�Ĳۺ���
    connect(tree,SIGNAL(itemDoubleClicked(QTreeWidgetItem *,int)),
            this,SLOT(treeItemLDclick(QTreeWidgetItem *,int)));

    connect(tree0,SIGNAL(itemDoubleClicked(QTreeWidgetItem *,int)),
            this,SLOT(treeItemLDclick0(QTreeWidgetItem *,int)));

    connect(tree,SIGNAL(itemPressed(QTreeWidgetItem *, int)),
            this,SLOT(SlotItemClicked(QTreeWidgetItem *, int)));

    connect(tree0,SIGNAL(itemPressed(QTreeWidgetItem *, int)),
            this,SLOT(SlotItemClicked0(QTreeWidgetItem *, int)));

    tree->expandAll();
    tree0->expandAll();
}//


/***********************************************************************
*ʵ���ı������
***********************************************************************/
void MainWindow::initRightDocking()
{

    //textedit = new QTextEdit();
    pMainList = new QTableWidget ;
    m_rightDock = new myDockWidget(tr("��Ϣ���"),this);
    //m_rightDock->titleBarWidget()->setStyleSheet("background:yellow");
    m_rightDock->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::AllDockWidgetAreas);
    m_rightDock->setFeatures(QDockWidget::DockWidgetClosable |QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetVerticalTitleBar);
    m_rightDock->setFloating(false);
    m_rightDock->setVisible(true);
    m_rightDock->setWidget(pMainList);//textedit
    m_rightDock->setStyleSheet("QDockWidget::title{\ntext-align: left;\nbackground: rgb(192,192,192);\n   padding-left: 5px;\n}");
    m_rightDock->setFocusPolicy(
            Qt::FocusPolicy(m_rightDock->focusPolicy()&(~Qt::TabFocus)));
    addDockWidget(Qt::BottomDockWidgetArea,m_rightDock,Qt::Horizontal);//BottomDockWidgetArea
    pMainList->setEditTriggers(QAbstractItemView::NoEditTriggers);//List�ؼ������Ա༭
    m_rightDock->setData(INFORMATION_OUTPUT);
    connect(m_rightDock, SIGNAL(dockWidgetClose(int)), this, SLOT(dockWidgetClose(int)));

    pMainList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(pMainList, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(show_contextmenu(const QPoint&)));


    pMainList->verticalHeader()->setVisible(false);
    pMainList->horizontalHeader()->setVisible(false);
    connect(pMainList,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(MsgOutputListDoubleClicked(int,int)));
    pMainList->setFocusPolicy(
            Qt::FocusPolicy(pMainList->focusPolicy()&(~Qt::TabFocus)));
}//

void MainWindow::show_contextmenu(const QPoint& pos)
{
    if(pMainList->rowCount() <= 0)
    {
        return;
    }
    if(cmenu)
    {
        delete cmenu;
        cmenu = NULL;
    }
    cmenu = new QMenu(pMainList);

    QAction *ClearAction = cmenu->addAction(tr("���"));


    connect(ClearAction, SIGNAL(triggered(bool)), this, SLOT(clearMessage()));

    cmenu->exec(QCursor::pos());//�ڵ�ǰ���λ����ʾ

}
void MainWindow::clearMessage()
{
    pMainList->clear();
    pMainList->setRowCount(0);
}
/***********************************************************************
*ʵ�����οؼ���Ŀ¼��˫����Ӧ�ۺ������������οؼ�����ز��������ڴ������Ӧ����
***********************************************************************/
void MainWindow::treeItemLDclick0(QTreeWidgetItem *item,int i)
{
    QTreeWidgetItem *parentItem = tree0->currentItem()->parent();
    QString         str         = tree0->currentItem()->text(0);
    //QString         parentStr   = parentItem->text(0);

    if(isHave)
    {
        if(str==tr("����&����") || str==tr("����") || str==tr("����"))
        {
            return;
        }

        if(parentItem==copyScreen_Item||parentItem==screen)//��˫�����ǻ����2���˵�ʱ
        {
            QStringList list=str.split(":");
            //pwnd->is_Save=false;
            //pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            nActiveSheetIndex=nFindActiveSheetIndex(str);

            pView->setScene(pSceneSheet[nActiveSheetIndex]);

            QScrollBar *pHorizScrollBar = pView->horizontalScrollBar();
            if(pHorizScrollBar)
            {
                pHorizScrollBar->setValue(0);
            }
            QScrollBar *pVerticalScrollBar = pView->verticalScrollBar();
            if(pVerticalScrollBar)
            {
                pVerticalScrollBar->setValue(0);
            }

            QString strDest;
            QString strtemp = list.at(1);
            handleWinTitle(strDest, strtemp);
            pwnd->setWindowTitle(strDest);

            int iIndex = pChScreen->findText(pSceneSheet[nActiveSheetIndex]->sNewScreenName);
            pwnd->pChScreen->setCurrentIndex(iIndex);
            //pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(list.at(1)));
            return;
        }
        else if(parentItem==window||parentItem==copyWindow_Item)//��˫�����Ǵ��ڵ�2���˵�ʱ
        {
            QStringList list=str.split(":");
            //pwnd->is_Save=false;
            //pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            nActiveSheetIndex=nFindActiveSheetIndex(str);

            pView->setScene(pSceneSheet[nActiveSheetIndex]);

            QString strDest;
            QString strtemp = list.at(1);
            handleWinTitle(strDest, strtemp);
            pwnd->setWindowTitle(strDest);

            int iIndex = pChScreen->findText(pSceneSheet[nActiveSheetIndex]->sNewScreenName);
            pwnd->pChScreen->setCurrentIndex(iIndex);
            //pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(list.at(1)));
            return;
        }
        else if(parentItem == TreeKeyboard||parentItem == copyUserKeyboard)//�Զ���˵�
        {
            QStringList list=str.split(":");
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            nActiveSheetIndex=nFindActiveSheetIndex(str);//��˫������Ÿ�ֵ����ǰ�������
            pView->setScene(pSceneSheet[nActiveSheetIndex]);//���õ�ǰ����

            QString strDest;
            QString strtemp = list.at(1);
            handleWinTitle(strDest, strtemp);
            pwnd->setWindowTitle(strDest);

            int iIndex = pChScreen->findText(pSceneSheet[nActiveSheetIndex]->sNewScreenName);
            pwnd->pChScreen->setCurrentIndex(iIndex);
            //pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(list.at(1)));
        }     
    }
}

void MainWindow::treeItemLDclick(QTreeWidgetItem *item, int i)
{
    bool t = item->isDisabled();
    if(t == true || isCompiled)
    {
        return;
    }

    QTreeWidgetItem *parentItem=tree->currentItem()->parent();
    if (!parentItem)
    {
            return ;
    }
    QString str=tree->currentItem()->text(0);
    QString parentStr = parentItem->text(0);
    if(isHave)
    {

        //+++++
        if(str==tr("����ѡ��") && parentStr == tr("��������"))
        {
            ModelSel model_select(this);
            model_select.exec();
            //������Ҫ�������νṹ��ȷ���;ɹ�������ݣ���Ϊ���ʱ��ɹ���ֻ�ܿ���com1��com2����̫��
            //QString strT = GetHMIConnectInformation(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelName);

            if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom1.contains("com1"))
            {
                link->child(0)->setDisabled(false);
            }
            else
            {
                link->child(0)->takeChildren();
                m_pSamSysParame->m_qvcConnect[0].vProtocols.clear();
                link->child(0)->setDisabled(true);
            }
            if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom1.contains("com2"))
            {
                link->child(1)->setDisabled(false);
            }
            else
            {
                link->child(1)->takeChildren();
                m_pSamSysParame->m_qvcConnect[1].vProtocols.clear();
                link->child(1)->setDisabled(true);
            }

            if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom1.contains("com3"))
            {
                link->child(2)->setDisabled(false);
            }
            else
            {
                link->child(2)->takeChildren();
                m_pSamSysParame->m_qvcConnect[2].vProtocols.clear();
                link->child(2)->setDisabled(true);
            }

            if(!pwnd->m_pSamSysParame->m_mixGlobalVar.m_strMaxscreennumber.contains("Ethernet(NONE)"))
            {
                link->child(3)->setDisabled(false);
            }
            else
            {
                link->child(3)->takeChildren();
                m_pSamSysParame->m_qvcConnect[3].vProtocols.clear();
                link->child(3)->setDisabled(true);
            }

            if(!pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom2.contains("NONE"))
            {
                link->child(4)->setDisabled(false);
                if(link->childCount() > 5)
                    link->child(5)->setDisabled(false);
            }
            else
            {
                link->child(4)->takeChildren();
                m_pSamSysParame->m_qvcConnect[4].vProtocols.clear();
                link->child(4)->setDisabled(true);
                if(link->childCount() > 5 )
                {
                    link->child(5)->takeChildren();
                    link->child(5)->setDisabled(true);
                }
                if(m_pSamSysParame->m_qvcConnect.size() > 5)
                    m_pSamSysParame->m_qvcConnect[5].vProtocols.clear();

            }

            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            return;
        }
        else if(str==tr("��ʾ����") && parentStr == tr("��������"))
        {
            NewInitSet init_set(this);
            init_set.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            return;
        }
        else if(str==tr("��������") && parentStr == tr("��������"))
        {
            operatorSet operator_set(this);
            operator_set.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            return;
        }
        else if(str==tr("���ݿ���") && parentStr == tr("��������"))
        {
            NewDataControl data_control(this);
            data_control.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            return;
        }
        else if(str==tr("�û�Ȩ��") && parentStr == tr("��������"))
        {
            NewUserRight user_right(this);
            user_right.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            return;
        }
 //       else if(str==tr("��������") )
//        {
//             NewPLCCtrl plc_control(this);
//             plc_control.exec();
//             pwnd->is_Save=false;
//             pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
//             return;
//        }
        else if(str==tr("��ӡ��") && parentStr == tr("��������"))
        {
            NewPrinter printer(this);
            printer.exec();
            pwnd->is_Save=false;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            is_NeedCompiled = true;
            //QMessageBox::about(this, tr("��ӡ��"), tr("��ʱ��֧�ִ�ӡ����"));
            return;
        }
        else if(str==tr("��������") && parentStr == tr("��̬����"))
        {
            NewDownload downLoad(this);
            downLoad.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            return;
        }
        else if(str==tr("ʱ������") && parentStr == tr("��̬����"))
        {
            QTreeCtrlTimeDlg timedlg(this);
            timedlg.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            return;
        }
        else if(str==tr("���ʼ���")&& parentStr == tr("��̬����"))
        {
            NewEncryAccess encry_access(this);
            encry_access.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            return;
        }
        else if(str==tr("����洢������")&& parentStr == tr("��̬����"))
        {
            PowerProtectDlg dlg;
            dlg.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            return;
        }
        else if(str==tr("��Ʒ��Ȩ") && parentStr == tr("��̬����"))
        {
            NewProRight product_right(this);
            product_right.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            return;
        }
        else if(str==tr("��������") && parentStr == tr("��̬����"))
        {
            NewLanguage language(this);
            language.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ

            //��������ӹ�������Ͽ�����ѡ��
            int nLanIndex = qLanguagecmb->currentIndex(); //�������ϵ�ǰ�����±�
            if(nLanIndex < 0)
            {
                nLanIndex = 0;
            }
            int num = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();

            //ˢ���䷽���ݲɼ��еĶ�������Ϣ��Ԫ������ �䷽���� begin
            for(int i = 0; i < m_pSamSysParame->m_qvcRecipe.size(); i++)
            {
                for(int j = 0; j < m_pSamSysParame->m_qvcRecipe.at(i).ElmentName.size(); j++)//Ԫ�ظ���
                {
                    int langcout = m_pSamSysParame->m_qvcRecipe.at(i).ElmentName.at(j).size();//���Ը���
                    if(num < langcout)
                    {
                       m_pSamSysParame->m_qvcRecipe[i].ElmentName[j].resize(num);
                       m_pSamSysParame->m_qvcRecipe[i].nLanguageId = 0;
                    }
                    else
                    {
                        m_pSamSysParame->m_qvcRecipe[i].ElmentName[j].resize(num);
                        for(int k = langcout; k < num; k++)
                        {
                            m_pSamSysParame->m_qvcRecipe[i].ElmentName[j][k].sElemName = "elment" + QString("%1").arg(j);
                            m_pSamSysParame->m_qvcRecipe[i].ElmentName[j][k].nLanguageId = k;
                        }
                    }
                }
                for(int j = 0; j < m_pSamSysParame->m_qvcRecipe.at(i).formula.size(); j++)//�䷽����
                {
                   int langcout = m_pSamSysParame->m_qvcRecipe.at(i).formula.at(j).RecipeInfo.size();
                   m_pSamSysParame->m_qvcRecipe[i].formula[j].RecipeInfo.resize(num);
                   if(num > langcout)
                   {
                       m_pSamSysParame->m_qvcRecipe[i].nLanguageId = 0;
                       for(int k = langcout; k < num; k++)
                       {
                           QString str = "Recipe";
                           str = str + QString("%1").arg(j);
                           m_pSamSysParame->m_qvcRecipe[i].formula[j].RecipeInfo[k].nLanguageId = k;
                           m_pSamSysParame->m_qvcRecipe[i].formula[j].RecipeInfo[k].sRecipeDescri = "";
                           m_pSamSysParame->m_qvcRecipe[i].formula[j].RecipeInfo[k].sRecipeName = str;
                       }
                   }
                }
            }
            //ˢ���䷽���ݲɼ��еĶ�������Ϣ��Ԫ������ �䷽���� end

            //��������ÿ�����������ԵĿؼ��������Ըı����Ϣ�������麯���ı�ؼ���������
            int count = pSceneSheet.size(); //��������
            QList<QGraphicsItem *> Items;
            for(int i = 0 ; i < count; i++) //ɨ�����л���
            {
                Items = pSceneSheet[i]->items();   //��ǰҳ�����е�item
                foreach(QGraphicsItem *pItem, Items)
                {
                    if(!pItem)
                    {
                        continue;
                    }

                    if(SAM_DRAW_OBJECT_GROUP == pItem->type())
                    {
                        if(pItem->parentItem() == 0 && pItem->type() != SAM_DRAW_OBJECT_TRACKER && pItem->type() != SAM_DRAW_OBJECT_LOCK)
                        {
                            QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
                            //item->redrawForChangeLanguage(qLanguagecmb->currentIndex());
                            item->changeItemLanguageAttr(num);
                        }
                    }
                }
            }

            qLanguagecmb->clear();
            for(int i = 0; i < num; i++)
            {
                qLanguagecmb->addItem(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList[i]);
            }
            qLanguagecmb->setEnabled(true);
            if(nLanIndex >= num)
            {
                qLanguagecmb->setCurrentIndex(0);
                //pwnd->m_pSamSysParame->m_mixGlobalVar.m_nCurLan = 0;
            }
            else
            {
                qLanguagecmb->setCurrentIndex(nLanIndex);
                //pwnd->m_pSamSysParame->m_mixGlobalVar.m_nCurLan = nLanIndex;
            }
            return;
        }
        else if(str==tr("���ϴ���") && parentItem == root)
        {

            QDataTransportDlg *DataTransport;
            DataTransport=new QDataTransportDlg(this);
            DataTransport->exec();
            if(DataTransport)
            {
                delete DataTransport;
                DataTransport=NULL;
            }
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            return;
        }
        else if(str==tr("������") && parentItem == root)
        {

            QVardlg *varDlg=new QVardlg(this);
            varDlg->exec();
            if(varDlg)
            {
                delete varDlg;
                varDlg=NULL;
            }
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            return;
        }
        else if(str==tr("ʱ���") && parentItem == root)
        {

            ScheduleDlg *varDlg=new ScheduleDlg(this);
            varDlg->exec();
            if(varDlg)
            {
                delete varDlg;
                varDlg=NULL;
            }
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            return;
        }

        else if(str==tr("PLC���") && parentItem == root)
        {
             QProcess proc(this);
             QStringList args;
             args << QString::number(is_tanslator);
             QString argv = QDir::currentPath();
             argv += QString("\\temp\\"+newpro->newprowizard_name+".bin");
             argv.replace("/","\\");
             args << argv;
             bool bReturnFlag = proc.startDetached(PC_PLC_EXE,args);
             if(!bReturnFlag)
             {
                 QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("�����ļ� %1 ʧ�ܣ������°�װ�����").arg(PC_PLC_EXE),
                                 0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
                 box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
                 box.exec();
                 return ;
             }

        }
        //else if(str==pwnd->m_pSamSysParame->m_recipeProp.sRecipeName)
        if(parentItem == recipe)
        {

            tree_openrecipe();
            //pwnd->m_pSamSysParame->m_recipeProp.sRecipeName =sub_Recipe->text(0);
//            QTreeCtrlRecipeDlg recipeDlg(this);
//            //recipeDlg->initAnalogAlarmDlg();
//            recipeDlg.exec();
//            pwnd->is_Save=false;
//            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            return;
        }
        //���ݲɼ�˫���¼�
        if(parentItem == tree_hisdatalog)
        {            
            tree_openhisdata();
            return;
        }

        //XXXXX
        /*
        if(str==tr("������")||str==tr("����")||str==tr("����") ||str==tr("����")||str==tr("����")||str==tr("��ʷ�����ռ���")
          ||str==tr("������¼")||str==tr("�䷽"))*/
        if(str==tr("������") || str==tr("����") || str==tr("����") || str==tr("���ݲɼ�")
          || str==tr("������¼") || str==tr("�䷽"))
        {
            return;
        }

        /*if(parentItem==copyScreen_Item||parentItem==screen)//��˫�����ǻ����2���˵�ʱ
        {
            QStringList list=str.split(":");
            pwnd->is_Save=false;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            nActiveSheetIndex=nFindActiveSheetIndex(str);

            pView->setScene(pSceneSheet[nActiveSheetIndex]);
            pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(list.at(1)));
            return;
        }

        else if(parentItem==window||parentItem==copyWindow_Item)//��˫�����Ǵ��ڵ�2���˵�ʱ
        {
            QStringList list=str.split(":");
            pwnd->is_Save=false;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            nActiveSheetIndex=nFindActiveSheetIndex(str);


            pView->setScene(pSceneSheet[nActiveSheetIndex]);
            pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(list.at(1)));
            return;
        }
        else if(parentItem == TreeKeyboard||parentItem == copyUserKeyboard)//�Զ���˵�
        {
            QStringList list=str.split(":");
            pwnd->is_Save=false;
            pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            nActiveSheetIndex=nFindActiveSheetIndex(str);//��˫������Ÿ�ֵ����ǰ�������
            pView->setScene(pSceneSheet[nActiveSheetIndex]);//���õ�ǰ����
            pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(list.at(1)));
        }
        else */if(parentItem == alarmlog)//˫��������¼��ĳһ��
        {
            digitAlarm_open();
        }
//        else if(parentItem == tree_macro)//˫���ű�
//        {

//        }
        else if(parentItem == link)//˫�����ӵ�ĳһ��
        {
                openLink(str);
        }
        else if (parentItem && parentItem->parent() == link)
        {
                openProtocol(parentStr,str);
        }
        else if(str == tr("ȫ�ֽű�") && parentStr == tr("�ű�"))
        {
            globalScriptDlg dlg(this);
            dlg.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);
        }
        else if(str == tr("��ʼ���ű�") && parentStr == tr("�ű�"))
        {
            initScriptDlg dlg(this);
            dlg.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);
        }
       // else if(parentItem == tree_macro)
        else
        {
            tree->setFocus(Qt::ActiveWindowFocusReason);
            emit showNumDlg(str,parentItem);
            return;
        }
      }
}//
//˫������������
void MainWindow::openLink(QString name)
{
    bool bExist = false;
    int i;
    for ( i =0; i<m_pSamSysParame->m_qvcConnect.size(); i++)
    {
        if (m_pSamSysParame->m_qvcConnect[i].sConnectName == name
            || name == tr("��̫��") || name == tr("����") || name == tr("CAN����"))//���Է�����ж�
            //|| name == tr("Ethernet") || name == tr("CAN Bus"))//���Է�����ж�
        {
            bExist = true;
            if(name == tr("��̫��")|| name == tr("����"))
            {
                i = 3;
            }
            else if(name == tr("CAN����"))
            {
                i = 4;
            }
            break;
        }
    }
    if (!bExist)
    {
        return;
    }

    NewPLCCtrl plc_control(i,this);
    plc_control.setConnect(m_pSamSysParame->m_qvcConnect[i]);
    if(plc_control.exec()==QDialog::Accepted)
    {
        //�޸�PLC����
        m_pSamSysParame->m_qvcConnect.replace(i,plc_control.m_Connect);
        tree->currentItem()->setText(0,plc_control.m_Connect.sConnectName);
        pwnd->is_Save=false;
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
    }
}

//����Э��
void MainWindow::addProtocol()
{
    QTreeWidgetItem *parentItem=tree->currentItem()->parent();
    //if(!parentItem || parentItem->text(0).isEmpty())
    //    return;
    //parentStr= parentItem->text(0);
    QTreeWidgetItem *cItem=tree->currentItem();
    QString str=tree->currentItem()->text(0);
    QString parentStr;

    if(!cItem || !parentItem || str.isEmpty())
    {
        return;
    }

    bool bExist = false;
    int i;
    for ( i =0; i<m_pSamSysParame->m_qvcConnect.size(); i++)
    {
        if (m_pSamSysParame->m_qvcConnect[i].sConnectName == str)
        {
            bExist = true;
            break;
        }
    }
    if (!bExist)
    {
        return;
    }

    bool bEthnet = (m_pSamSysParame->m_qvcConnect[i].eConnectPort == 3 || m_pSamSysParame->m_qvcConnect[i].eConnectPort == 4);
    stProtocol ptcl;
    QString strText = cItem->text(0);
    int iProType = PRO_SERIAL;
    if(strText == tr("Com1") || strText == tr("Com2") || strText == tr("Com3"))
    {
        iProType = PRO_SERIAL;
    }
    else if(strText == tr("��̫��") || strText == tr("����"))
    {
        iProType = PRO_ETHNET;
    }
    ProtocolDlg protocolDlg(ptcl,-1,bEthnet,iProType,this);
    if(protocolDlg.exec()==QDialog::Accepted)
    {
        QTreeWidgetItem *wTemp;
        wTemp=new QTreeWidgetItem(cItem,QStringList(tr("")));

        cItem->insertChild(1,wTemp);
        cItem->setExpanded(true);
        wTemp->setIcon(0,QIcon(":/tree/images/tree/com.ico"));
        wTemp->setText(0,protocolDlg.m_Protocol.sName);
        m_pSamSysParame->m_qvcConnect[i].vProtocols.append(protocolDlg.m_Protocol);
        if(1 == m_pSamSysParame->m_qvcConnect[i].vProtocols.size())//����һ��Э�飬�Ҹ�Э���ǵ�һ��
        {
            setDefaultPlc(i);
        }
    }

    pwnd->is_Save=false;
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
}

//ɾ��Э��
void MainWindow::delProtocol()
{
    QTreeWidgetItem *parentItem=tree->currentItem()->parent();
    if(!parentItem || parentItem->text(0).isEmpty())
        return;

    //QMessageBox::about(this, tr("����"), tr("����û��������"));
    //return 0;
    QMessageBox box(QMessageBox::Information,tr("��ʾ"),tr("�Ƿ�ȷ��ɾ��Э��"),QMessageBox::Ok|QMessageBox::No,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.button(QMessageBox::Ok)->setText(tr("��"));
    box.button(QMessageBox::No)->setText(tr("��"));
    box.exec();
    if(box.clickedButton()== box.button(QMessageBox::No))
    {
        return;
    }
    //else if(box.clickedButton()== box.button(QMessageBox::Ok))

    QString parentStr= parentItem->text(0);

    QTreeWidgetItem *cItem=tree->currentItem();
    QString str=tree->currentItem()->text(0);

    int i;
    bool bExist = false;
    QVector<stProtocol> protocols;
    bool bValue = false;

    for (i = 0; i < m_pSamSysParame->m_qvcConnect.size(); i++)
    {
            if (m_pSamSysParame->m_qvcConnect[i].sConnectName == parentStr)
            {
                    protocols = m_pSamSysParame->m_qvcConnect[i].vProtocols;
                    bValue = true;
                    break;
            }

    }

    int j;
    for (j = 0; j < protocols.size(); j++)
    {
            if (protocols[j].sName == str)
            {
                bExist = true;
                break;
            }

    }
    bExist = bExist && bValue;
    //ɾ��Э��
    if(bExist)
    {
        parentItem->removeChild(cItem);
        m_pSamSysParame->m_qvcConnect[i].vProtocols.remove(j);
        if(0 == j)//ɾ�����ǵ�һ��Э�飬��ˢ�´�����Ϣ
        {
            setDefaultPlc(i);
        }
    }
}

//˫��������Э��
void MainWindow::openProtocol(QString parentName,QString name)
{
    int i;
    bool bExist = false;
    QVector<stProtocol> protocols;
    bool bValue = false;
    for (i =0; i<m_pSamSysParame->m_qvcConnect.size(); i++)
    {
        if (m_pSamSysParame->m_qvcConnect[i].sConnectName == parentName)
        {
            protocols = m_pSamSysParame->m_qvcConnect[i].vProtocols;
            bValue = true;
            break;
        }
    }

    int j;
    for (j=0; j<protocols.size();j++)
    {
        if (bValue && protocols[j].sName == name)
        {
            bExist = true;
            break;
        }
    }
    bExist = bExist && bValue;
    //�޸�Э��
    if(bExist)
    {
        strOldProtocal = m_pSamSysParame->m_qvcConnect[i].vProtocols.at(j).sName;
        bool bEthnet   = (m_pSamSysParame->m_qvcConnect[i].eConnectPort == 3 || m_pSamSysParame->m_qvcConnect[i].eConnectPort == 4);
        int iProType = PRO_SERIAL;
        if(parentName == tr("Com1") || parentName == tr("Com2") || parentName == tr("Com3"))
        {
            iProType = PRO_SERIAL;
        }
        else if(parentName == tr("��̫��") || parentName == tr("����"))
        {
            iProType = PRO_ETHNET;
        }
        ProtocolDlg protocolDlg(protocols[j],j,bEthnet,iProType,this);
        if(protocolDlg.exec()==QDialog::Accepted)
        {
            stProtocol      pro     = m_pSamSysParame->m_qvcConnect[i].vProtocols.at(j);
            QTreeWidgetItem *wTemp  = tree->currentItem();

            strNewProtocal = protocolDlg.m_Protocol.sName;
            wTemp->setText(0,protocolDlg.m_Protocol.sName);
            m_pSamSysParame->m_qvcConnect[i].vProtocols.replace(j,protocolDlg.m_Protocol);

            if(0 == j && ((pro.sFactoryName != protocolDlg.m_Protocol.sFactoryName) || (pro.sProtocolName != protocolDlg.m_Protocol.sProtocolName)))
            {
                setDefaultPlc(i);
            }

            if(strNewProtocal != strOldProtocal)//��Ҫ���������õ����Э��ĵ�ַ
            {
                pwnd->vAddrMsg.clear();
                pwnd->OnFillAddressMsgClass();//����ַ��Ϣ
                int msgNum = pwnd->vAddrMsg.size();
                int addrNum;
                for(int i = 0; i < msgNum; i++)
                {
                    addrNum = pwnd->vAddrMsg[i]->Address.size();
                    for(int j = 0; j < addrNum; j++)
                    {
                        if(pwnd->vAddrMsg[i]->Address.size() == 0)
                        {
                            break;
                        }
                        QString strTemp = pwnd->vAddrMsg[i]->Address[j].pAddr->sShowAddr;
                        if(strTemp.at(0) != '[')
                        {
                            continue;
                        }
                        else
                        {
                            int nEnd = strTemp.lastIndexOf(']');
                            if(nEnd > 0)
                            {
                                strTemp = strTemp.left(nEnd);
                                strTemp = strTemp.remove(0, 1);
                                if(strTemp != strOldProtocal)
                                {
                                    continue;
                                }
                                else
                                {
                                    pwnd->vAddrMsg[i]->Address[j].pAddr->sShowAddr.replace(1, nEnd - 1, strNewProtocal);
                                    pwnd->vAddrMsg[i]->Address[j].pAddr->sPlcName = strNewProtocal;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    pwnd->is_Save=false;
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
}
/************************************************************************
  *Functions:����û��Զ������
  ************************************************************************
  *Value��
  *��
  ************************************************************************
  *returns:
  *��
  ************************************************************************
  *Edit time��2011.6.7
  *Edit by    ��zhy
  *************************************************************************/
void MainWindow::tree_newuserkeyboard()
{
    if(isCompiled)
    {
        return;
    }
    QString sTmp="";
    QString sNo="";
    QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr(""),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
    QFile file("userkeyboard.dat");
    if(!file.open(QIODevice::ReadOnly))
    {
        msg.setText(tr("userkeyboard.datδ�ҵ����޷�������̣�"));
        msg.exec();
        return ;//���ز������ԣ�Ӧ���������ó����ز���
    }

    dockTabWidget->setCurrentIndex(1);//���뻭��ҳ��

    userkeyboarddlg=new QUserKeyboard(this);
    int res=userkeyboarddlg->exec();
    delete userkeyboarddlg;
    userkeyboarddlg=NULL;
    if(res==QDialog::Accepted)
    {
        pwnd->is_Save=false;
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ

        pView->setScene(pSceneSheet[nActiveSheetIndex]);
        upDatetreeScreenItem();
        sTmp=pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(1);

        updateChScreen();
        //list_style
        //if(pwnd->list_style->currentIndex()==0||pwnd->list_style->currentIndex()==1)//��׼��Ԫ���б�
        if(1)
        {
           //pwnd->tree->setCurrentItem(pwnd->copyUserKeyboard->child(pwnd->nActiveSheetIndex));
           //pwnd->tree->setFocus(Qt::MouseFocusReason);
           pwnd->tree0->setCurrentItem(pwnd->copyUserKeyboard->child(pwnd->nActiveSheetIndex));
           pwnd->tree0->setFocus(Qt::MouseFocusReason);
           for(int j=0;j<pwnd->copyUserKeyboard->childCount();j++)
           {
               sNo=pwnd->copyUserKeyboard->child(j)->text(0).split(":").at(1);
               if(sTmp==sNo)
               {
                  //pwnd->tree->setCurrentItem(pwnd->copyUserKeyboard->child(j),0,QItemSelectionModel::SelectCurrent);
                  //pwnd->tree->setFocus(Qt::ActiveWindowFocusReason);
                  pwnd->tree0->setCurrentItem(pwnd->copyUserKeyboard->child(j),0,QItemSelectionModel::SelectCurrent);
                  pwnd->tree0->setFocus(Qt::ActiveWindowFocusReason);
               }
           }//
        }
        /*else//Ԥ���б�
        {
           pwnd->tree->setCurrentItem(pwnd->newScreen[pwnd->nActiveSheetIndex],0,QItemSelectionModel::SelectCurrent);
           pwnd->tree->setFocus(Qt::MouseFocusReason);
           //PreviewWindow();
           tree->collapseAll();
           tree->expandAll();
        }*/
    }
}

//���ؼ����Ҽ��˵��¼�
void MainWindow::SlotItemClicked0(QTreeWidgetItem *item, int column)
{
    if (qApp->mouseButtons() == Qt::LeftButton || isCompiled)
    {
        return;
    }
    else if (qApp->mouseButtons() == Qt::RightButton)
    {
        QTreeWidgetItem *parentItem = tree0->currentItem()->parent();
        QString         str         = tree0->currentItem()->text(0);

        if(str.isEmpty())
        {
            return;
        }

        if(isHave)
        {
            if(str == tr("����"))
            {
                showMenu();
            }

            if(parentItem == copyScreen_Item || parentItem == screen)//��������ǻ����һ���˵�ʱ
            {
                nActiveSheetIndex=pwnd->nFindActiveSheetIndex(str);
                pView->setScene(pSceneSheet[nActiveSheetIndex]);

                QString strDest;
                QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
                handleWinTitle(strDest, strtemp);
                pwnd->setWindowTitle(strDest);
                //pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                                     //arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
                int iIndex = pChScreen->findText(pSceneSheet[nActiveSheetIndex]->sNewScreenName);
                pwnd->pChScreen->setCurrentIndex(iIndex);
                showScreenMenu();
            }

            if(str == tr("����"))
            {
                showWindowMenu();
                pwnd->is_Save=false;
                is_NeedCompiled = true;
                pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            }

            if(parentItem == copyWindow_Item || parentItem == window)//��������Ǵ��ڵ�һ���˵�ʱ
            {
                nActiveSheetIndex=pwnd->nFindActiveSheetIndex(str);
                pView->setScene(pSceneSheet[nActiveSheetIndex]);

                QString strDest;
                QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
                handleWinTitle(strDest, strtemp);
                pwnd->setWindowTitle(strDest);
                //pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                                     //arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
                int iIndex = pChScreen->findText(pSceneSheet[nActiveSheetIndex]->sNewScreenName);
                pwnd->pChScreen->setCurrentIndex(iIndex);
                showWindowSubMenu();
            }

            if(str == tr("�Զ������"))
            {
                showUserKeyboardAddnew();//�Ҽ�����Զ������

            }

            if(parentItem==TreeKeyboard || parentItem == copyUserKeyboard)//�û��Զ������
            {
                nActiveSheetIndex=this->nFindActiveSheetIndex(str);
                pView->setScene(pSceneSheet[nActiveSheetIndex]);

                QString strDest;
                QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
                handleWinTitle(strDest, strtemp);
                pwnd->setWindowTitle(strDest);
                //pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                                     //arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
                int iIndex = pChScreen->findText(pSceneSheet[nActiveSheetIndex]->sNewScreenName);
                pwnd->pChScreen->setCurrentIndex(iIndex);
                showUserKeyboard();
                pwnd->is_Save=false;
                is_NeedCompiled = true;
                pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            }
        }
    }
}

void MainWindow::openCurProtocol()
{
    int i;
    bool bExist = false;
    QVector<stProtocol> protocols;
    bool bValue = false;

    QString parentName;
    QString name;

    QTreeWidgetItem *parentItem=tree->currentItem()->parent();
    if(!parentItem || parentItem->text(0).isEmpty())
        return;
    parentName= parentItem->text(0);

    //QTreeWidgetItem *cItem=tree->currentItem();
    name=tree->currentItem()->text(0);

    for (i =0; i<m_pSamSysParame->m_qvcConnect.size(); i++)
    {
        if (m_pSamSysParame->m_qvcConnect[i].sConnectName == parentName)
        {
            protocols = m_pSamSysParame->m_qvcConnect[i].vProtocols;
            bValue = true;
            break;
        }
    }

    int j;
    for (j=0; j<protocols.size();j++)
    {
        if (bValue && protocols[j].sName == name)
        {
            bExist = true;
            break;
        }
    }
    bExist = bExist && bValue;
    //�޸�Э��
    if(bExist)
    {
        stProtocol ptcl = m_pSamSysParame->m_qvcConnect[i].vProtocols.at(j);
        strOldProtocal  = m_pSamSysParame->m_qvcConnect[i].vProtocols.at(j).sName;
        bool bEthnet    = (m_pSamSysParame->m_qvcConnect[i].eConnectPort == 3 || m_pSamSysParame->m_qvcConnect[i].eConnectPort == 4);
        int iProType = PRO_SERIAL;
        if(parentName == tr("Com1") || parentName == tr("Com2") || parentName == tr("Com3"))
        {
            iProType = PRO_SERIAL;
        }
        else if(parentName == tr("��̫��") || parentName == tr("����"))
        {
            iProType = PRO_ETHNET;
        }
        ProtocolDlg protocolDlg(protocols[j],j,bEthnet,iProType,this);
        if(protocolDlg.exec()==QDialog::Accepted)
        {
            QTreeWidgetItem *wTemp = tree->currentItem();

            strNewProtocal = protocolDlg.m_Protocol.sName;
            wTemp->setText(0,protocolDlg.m_Protocol.sName);
            m_pSamSysParame->m_qvcConnect[i].vProtocols.replace(j,protocolDlg.m_Protocol);

            if(0 == j && ((ptcl.sFactoryName != protocolDlg.m_Protocol.sFactoryName) || (ptcl.sProtocolName != protocolDlg.m_Protocol.sProtocolName)))
            {
                setDefaultPlc(i);
            }

            if(strNewProtocal != strOldProtocal)//��Ҫ���������õ����Э��ĵ�ַ
            {
                pwnd->vAddrMsg.clear();
                pwnd->OnFillAddressMsgClass();//����ַ��Ϣ
                int msgNum = pwnd->vAddrMsg.size();
                int addrNum;
                for(int i = 0; i < msgNum; i++)
                {
                    addrNum = pwnd->vAddrMsg[i]->Address.size();
                    for(int j = 0; j < addrNum; j++)
                    {
                        if(pwnd->vAddrMsg[i]->Address.size() == 0)
                        {
                            break;
                        }
                        QString strTemp = pwnd->vAddrMsg[i]->Address[j].pAddr->sShowAddr;
                        if(strTemp.at(0) != '[')
                        {
                            continue;
                        }
                        else
                        {
                            int nEnd = strTemp.lastIndexOf(']');
                            if(nEnd > 0)
                            {
                                strTemp = strTemp.left(nEnd);
                                strTemp = strTemp.remove(0, 1);
                                if(strTemp != strOldProtocal)
                                {
                                    continue;
                                }
                                else
                                {
                                    pwnd->vAddrMsg[i]->Address[j].pAddr->sShowAddr.replace(1, nEnd - 1, strNewProtocal);
                                    pwnd->vAddrMsg[i]->Address[j].pAddr->sPlcName = strNewProtocal;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::showDelMenu()
{
    QMenu menu(tree);
    QAction *protocal_open  = menu.addAction(tr("��"));
    connect(protocal_open,SIGNAL(triggered()),SLOT(openCurProtocol()));
#ifndef AKPLC
    QAction *protocal_delete= menu.addAction(tr("ɾ��"));
    connect(protocal_delete,SIGNAL(triggered()),SLOT(delProtocol()));
#endif



    menu.exec(QCursor::pos());
}

void MainWindow::SlotItemClicked(QTreeWidgetItem *item, int column)
{
    if (qApp->mouseButtons() == Qt::LeftButton || isCompiled)
    {
        return;
    }
    else if (qApp->mouseButtons() == Qt::RightButton)
    {
        QString str=tree->currentItem()->text(0);
        if(str == tr("������"))
        {
            return;
        }
        QTreeWidgetItem *parentItem=tree->currentItem()->parent();
        QString strParent = tree->currentItem()->parent()->text(0);
        if(str.isEmpty())
        {
            return;
        }
        if(isHave)
        {
            if(strParent == tr("Com1") || strParent == tr("Com2") || strParent == tr("Com3") || strParent == tr("��̫��")|| strParent == tr("����") || strParent == tr("CAN����"))
            {
                showDelMenu();
            }
            /*if(str==tr("����"))
            {
                showMenu();
            }
            if(parentItem==copyScreen_Item||parentItem==screen)//��������ǻ����һ���˵�ʱ
            {
                nActiveSheetIndex=pwnd->nFindActiveSheetIndex(str);
                pView->setScene(pSceneSheet[nActiveSheetIndex]);
                pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                                     arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneTypeProp.sNewScreenName));
                showScreenMenu();
            }
            if(str==tr("����"))
            {
                showWindowMenu();
                pwnd->is_Save=false;
                pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            }
            if(parentItem==copyWindow_Item||parentItem==window)//��������Ǵ��ڵ�һ���˵�ʱ
            {
                nActiveSheetIndex=pwnd->nFindActiveSheetIndex(str);
                pView->setScene(pSceneSheet[nActiveSheetIndex]);
                pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                                     arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneTypeProp.sNewScreenName));
                showWindowSubMenu();
            }
            if(str==tr("�Զ������"))
            {
                showUserKeyboardAddnew();//�Ҽ�����Զ������
                pwnd->is_Save=false;
                pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            }
            if(parentItem==TreeKeyboard||parentItem == copyUserKeyboard)//�û��Զ������
            {
                nActiveSheetIndex=this->nFindActiveSheetIndex(str);
                pView->setScene(pSceneSheet[nActiveSheetIndex]);
                pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                                     arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneTypeProp.sNewScreenName));
                showUserKeyboard();
                pwnd->is_Save=false;
                pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            }*/
            if(str==tr("������¼"))
            {
                showAlarmMenu();
            }
            if(parentItem==pwnd->alarmlog) //��λ������
            {
                qDebug() << "indexOfChild" << parentItem->indexOfChild(tree->currentItem());
                showDigitalAlarmMenu();
            }            
            if(str==tr("�䷽") && parentItem == root)
            {
                //if(!m_pSamSysParame->m_recipeProp.bRecipeExist)//�����䷽�Ӳ˵�ֻ��һ��
                {
                    showRecipeMenu();//���䷽�˵�
                }
//                else
//                {
//                    QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("�Ѿ�����һ���䷽����ɾ�������½���"),
//                                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
//                    box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
//                    box.exec();
//                }
            }
            
            /*if(str==tr("��������"))
            {
                ShowComLink();
                pwnd->is_Save=false;
                pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            }*/
            if(parentItem == pwnd->link)//���������Ҽ��˵�
            {
                ShowlinkProperty();
                pwnd->is_Save=false;
                is_NeedCompiled = true;
                pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            }
            if(parentItem == pwnd->recipe)
            {
                showSubRecipeMenu();//����䷽1�˵�
                pwnd->is_Save=false;
                is_NeedCompiled = true;
                pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            }
            if(str == tr("���ݲɼ�"))
            {
                AddHisDataMenu();
            }
            if(str == tr("�ű�"))
            {
                showMacroMenu();
                return;
            }
            if (parentItem && parentItem->text(0) == tr("���ݲɼ�"))
            {
                ShowSubHisdataMenu();
            }
        }
    }
}//
/************************************************************************
  *Functions:����ѡ�е����ӵ��Ҽ��˵���com1 com2
  ************************************************************************
  *Value��
  *��
  ************************************************************************
  *returns:
  *���ɲ˵���ɾ��������������ѡ��
  ************************************************************************
  *Edit time��2011.7.25
  *Edit by    ��zhy
  *************************************************************************/
//XXXXX

void MainWindow::ShowlinkProperty()
{
    QMenu menu(tree);
    //QAction *tree_Deletelink= menu.addAction(tr("ɾ��"));
    QAction *tree_linkproperty= menu.addAction(tr("��"));

    // menu.exec(ui.treeWidget->mapToGlobal(pos));
    //connect(tree_Deletelink,SIGNAL(triggered()),SLOT(tree_deleteLink()));
    connect(tree_linkproperty,SIGNAL(triggered()),SLOT(tree_Linkproperty()));

#ifndef AKPLC
    QAction *tree_procotol= menu.addAction(tr("����Э��"));
    connect(tree_procotol,SIGNAL(triggered()),SLOT(addProtocol()));
#endif
    menu.exec(QCursor::pos());

}
void MainWindow::tree_deleteLink()//ɾ������
{
//     QString sLinkName=tree->currentItem()->text(0);
//     for(int i=0;i<link->childCount();i++)//������������ �ҵ����Ӧ��λ��
//     {
//         if(link->child(i)->text(0) == sLinkName)
//         {
//             link->removeChild(pwnd->vTreeLinkType.at(i));
//             pwnd->vTreeLinkType.remove(i);
//             if(i<m_pSamSysParame->m_qvcPlcCommunicate.size())
//             {
//                 m_pSamSysParame->m_qvcPlcCommunicate.remove(i);
//                 if(i<this->nSimulatorport.size())
//                 {
//                     this->nSimulatorport.remove(i);//ɾ��ģ������ʱ���¼��ʹ�õ��ĸ����ӿ�
//                 }
//             }
//             break;
//         }
//     }

}
void MainWindow::tree_Linkproperty()//����������
{
    QString str = tree->currentItem()->text(0);
    openLink(str);

    pwnd->is_Save=false;
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
}

/************************************************************************
  *Functions:�����û��Զ�������Ҽ��˵�
  ************************************************************************
  *Value��
  *��
  ************************************************************************
  *returns:
  *���ɲ˵���ɾ������������ѡ��
  ************************************************************************
  *Edit time��2011.6.13
  *Edit by    ��zhy
  *************************************************************************/
void MainWindow::showUserKeyboard()
{
    /*QMenu menu(tree);
    QAction *tree_Deleteuserkeyboard= menu.addAction(tr("ɾ������"));
    QAction *tree_userkeyboardproperty= menu.addAction(tr("����"));
    // menu.exec(ui.treeWidget->mapToGlobal(pos));
    connect(tree_Deleteuserkeyboard,SIGNAL(triggered()),SLOT(tree_deleteuserKeyboard()));
    connect(tree_userkeyboardproperty,SIGNAL(triggered()),SLOT(tree_UserKeyboardproperty()));
    menu.exec(QCursor::pos());*/

    QMenu menu(tree0);
    QAction *tree_Deleteuserkeyboard= menu.addAction(tr("ɾ��(&D)"));
    QAction *tree_userkeyboardproperty= menu.addAction(tr("����(&P)"));
    // menu.exec(ui.treeWidget->mapToGlobal(pos));
    connect(tree_Deleteuserkeyboard,SIGNAL(triggered()),SLOT(tree_deleteuserKeyboard()));
    connect(tree_userkeyboardproperty,SIGNAL(triggered()),SLOT(tree_UserKeyboardproperty()));
    menu.exec(QCursor::pos());
}
/************************************************************************
  *Functions:�����û��Զ�������Ҽ��½��˵�
  ************************************************************************
  *Value��
  *��
  ************************************************************************
  *returns:
  *���ɲ˵����½�ѡ��
  ************************************************************************
  *Edit time��2011.6.13
  *Edit by    ��zhy
  *************************************************************************/
void MainWindow::showUserKeyboardAddnew()
{
    /*QMenu menu(tree);
    QAction *tree_newUserKeyboard= menu.addAction(tr("��Ӽ���"));
    connect(tree_newUserKeyboard,SIGNAL(triggered()),SLOT(tree_newuserkeyboard()));
    menu.exec(QCursor::pos());*/
    QMenu menu(tree0);
    QAction *tree_newUserKeyboard= menu.addAction(tr("��Ӽ���"));
    connect(tree_newUserKeyboard,SIGNAL(triggered()),SLOT(tree_newuserkeyboard()));
    menu.exec(QCursor::pos());
}

/************************************************************************
  *Functions:ִ��ɾ���Զ�����̵�����
  ************************************************************************
  *Value��
  *��
  ************************************************************************
  *returns:
  *ɾ��ĳ��ѡ��ļ���
  ************************************************************************
  *Edit time��2011.6.13
  *Edit by    ��zhy
  *************************************************************************/

void MainWindow::tree_deleteuserKeyboard()
{
    QMessageBox box(QMessageBox::Information,tr("��ʾ"),tr("�Ƿ�ȷ��ɾ���ü���?"),QMessageBox::Ok|QMessageBox::No,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.button(QMessageBox::Ok)->setText(tr("��"));
    box.button(QMessageBox::No)->setText(tr("��"));
    box.exec();
    if(box.clickedButton()== box.button(QMessageBox::No))
    {
        return;
    }

    QString str="";
    int nTmp=0;
    QString  stotal="";
    //deleteScreen_upDateIndex();
    QStringList sNamelist;
    sNamelist.clear();

    SamDrawScene* pSceneTemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex];
    int iActiveSheetIndex = pwnd->nActiveSheetIndex;
    int iTreeIndex = pwnd->TreeKeyboard->indexOfChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);
    QString strNum = pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0);
    //strNum = strNum.left(strNum.lastIndexOf(":"));

    TreeKeyboard->removeChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);//ɾ�����ؼ�������Ӳ˵�
    pwnd->pSceneSheet.remove(pwnd->nActiveSheetIndex);//ɾ������
    if(m_pSamSysParame->nUserDefKeyboardCount > 0)
        m_pSamSysParame->nUserDefKeyboardCount--;

    for(int i = 0; i< pwnd->pSceneSheet.size(); i++)
    {
        if(2 == pwnd->pSceneSheet[i]->nIsSceneOrWindow)
        {
            sNamelist.append(pwnd->pSceneSheet[i]->sNewScreenName);
        }
    }

    for(int i = 0; i < pwnd->m_pSamSysParame->m_qvcRecipe.size();i++)
    {
        if(m_pSamSysParame->m_qvcRecipe[i].nKeyMark)
        {
            QString sname = m_pSamSysParame->m_qvcRecipe[i].sKeyname;
            if(sNamelist.size() <= 0)
            {
                m_pSamSysParame->m_qvcRecipe[i].nKeyMark = false;
                m_pSamSysParame->m_qvcRecipe[i].nKeyId = 0;
                m_pSamSysParame->m_qvcRecipe[i].sKeyname = "";
            }
            else
            {
                int index = sNamelist.indexOf(sname);
                if(index >= 0)
                {
                    m_pSamSysParame->m_qvcRecipe[i].nKeyId = index;
                }
                else
                {
                    m_pSamSysParame->m_qvcRecipe[i].nKeyId = 0;
                    m_pSamSysParame->m_qvcRecipe[i].sKeyname = sNamelist.at(0);
                }
            }
        }
    }

    for(int i = 0; i< pwnd->pSceneSheet.size(); i++)
    {
        if(2 == pwnd->pSceneSheet[i]->nIsSceneOrWindow)
        {
            continue;
        }
        if(0 == pwnd->pSceneSheet[i]->nIsSceneOrWindow)
        {
            QList <QGraphicsItem *> items = pwnd->pSceneSheet[i]->TopItems();
            foreach(QGraphicsItem* pItem,items)
            {
                if(SAM_DRAW_OBJECT_GROUP == pItem->type())
                {
                    DataDisplayItem *itemgoup = dynamic_cast<DataDisplayItem *> (pItem);
                    if(!itemgoup)
                    {
                        continue;
                    }
                    if(SAM_DRAW_GROUP_VALUE  == itemgoup->GroupType()
                        || SAM_DRAW_GROUP_ASCII == itemgoup->GroupType())
                    {
                        QString sname = itemgoup->GetKeyboardName();
                        if(sNamelist.size() <= 0)
                        {
                            //�Զ�����̲�����
                            itemgoup->SetKeyBoardInfo("",-1);
                        }
                        else
                        {
                            int index = sNamelist.indexOf(sname);
                            if(index >= 0)
                            {
                                itemgoup->SetKeyBoardInfo(sname,index);
                            }
                            else
                            {
                                itemgoup->SetKeyBoardInfo(sNamelist.at(0),0);
                            }
                        }
                    }
                }

            }
        }
    }

    int totalSceneNum = pSceneSheet.size();//ȡ����
    for(int i=pwnd->nActiveSheetIndex;i<totalSceneNum;i++)
    {
        pwnd->newScreen[i]=pwnd->newScreen[i+1];
        QTreeWidgetItem *parentItem=pwnd->newScreen[i+1]->parent();//ȡ��һ��������
        if((parentItem==pwnd->TreeKeyboard)||(parentItem==pwnd->copyUserKeyboard))
        {//��Ϊ�Զ�����̵Ļ�
            stotal=pwnd->newScreen[i]->text(0).split(":").at(0);
            nTmp=stotal.toInt()-1;
            stotal=QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
            str=stotal+":"+pwnd->newScreen[i]->text(0).split(":").at(1);
            pwnd->newScreen[i]->setText(0,str);
        }
    }

    if(TreeKeyboard->childCount()<1)//�����е��û��Զ�����̶���ɾ��ʱ
    {
        TreeKeyboard->setHidden(true);//�������οؼ����Զ��������
    }


    //pwnd->PreviewWindow();
    if(!pwnd->label.isEmpty() && pwnd->nActiveSheetIndex < pwnd->label.size())
        pwnd->label.remove(pwnd->nActiveSheetIndex );
    if(!pwnd->titlelabel.isEmpty() && pwnd->nActiveSheetIndex < pwnd->titlelabel.size())
        pwnd->titlelabel.remove(pwnd->nActiveSheetIndex );
    if(!pwnd->priviewWidget.isEmpty() && pwnd->nActiveSheetIndex < pwnd->priviewWidget.size())
        pwnd->priviewWidget.remove(pwnd->nActiveSheetIndex );
    DealWithDeleteScreen();//����ɾ�����洰���Զ�����̵�ʱ�����οؼ�ˢ������

    upDatetreeScreenItem();

    updateChScreen();

    undoStack->push(new DeleteKeyBoardCommand(pSceneTemp, iActiveSheetIndex, iTreeIndex, strNum));
}
/*****************************************
 *��ɾ���Զ�����̵�ʱ�������л����ϵĻ��水ť�Ͷ๦�ܰ�ť�Ļ�����ת
 *************************************/
void  MainWindow::deleteScreen_upDateIndex()
{
    QList<QGraphicsItem *> Items;
    QStringList sList;
    QString sName="";
    int nIndex=0;
    int nTmp=0;
    QString sTmp="";
    int totalSceneNum = pSceneSheet.size();
    //  int    nActiveindex=pwnd->nActiveSheetIndex;
    int    nActiveindex=newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(0).toInt();//ȡ���Կؼ���ǰѡ�е�
    for(int i=0;i<totalSceneNum;i++)
    {
        if(pSceneSheet[i]->nIsSceneOrWindow==2)//�Զ�����̵�ʱ��
        {
            continue;
        }
        Items = pSceneSheet[i]->items();   //��ǰҳ�����е�item
        for(int j = 0; j < Items.size(); j++)
        {
            sList = Items.at(j)->data(GROUP_DATALIST_KEY).toStringList(); //ȡ��ÿ��item����������
            if(sList.size() < 20)
                continue;//break;
            sName = sList.at(19);
            if(sName.mid(0,2) == "SB")//���水ť
            {
                nIndex=sList.at(48).toInt();
                if(nIndex<nActiveindex)
                {
                    continue;
                }
                else if(nIndex==nActiveindex)
                {
                    sTmp.setNum(0);//�߼���ַ
                    sList.replace(48,sTmp);
                    int i=pwnd->GetFristScreenID(1);
                    sList.replace(56,pwnd->pSceneSheet[i]->sNewScreenName);//��������
                    Items[j]->setData(GROUP_DATALIST_KEY,sList);
                }
                else if(nIndex>nActiveindex)
                {
                    sTmp.setNum(nIndex-1);
                    sList.replace(48,sTmp);
                    Items[j]->setData(GROUP_DATALIST_KEY,sList);
                }
            }
            else if(sName.mid(0,2) == "MF")//���ܰ�ť
            {
                int nCount=sList[120].toInt();
                for(int i=0;i<nCount;i++)
                {
                    int iType = sList[80+21+2*i].toInt(); //���ܱ�ʶ

                    if(iType == 4)
                    {
                        sTmp=sList[80+22+2*i];
                        nTmp=sList[80+22+2*i].toInt();
                        if((sTmp!="f")&&(sTmp!="p"))
                        {
                            nTmp=sTmp.toInt();
                            if(nTmp<nActiveindex)
                            {
                                continue;
                            }
                            else if(nTmp==nActiveindex)
                            {
                                sList.replace(80+22+2*i,"0");
                                int i=pwnd->GetFristScreenID(1);
                                sList.replace(94,pwnd->pSceneSheet[i]->sNewScreenName);//��������

                                Items[j]->setData(GROUP_DATALIST_KEY,sList);
                            }
                            else if(nTmp>nActiveindex)
                            {
                                sTmp=QString::number(nTmp-1);
                                sList.replace(80+22+2*i,sTmp);
                                Items[j]->setData(GROUP_DATALIST_KEY,sList);
                            }
                        }
                    }
                }
            }
        }
    }
}
void MainWindow::tree_UserKeyboardproperty()
{
    userkeyboardproperty=new QUserKeyboardProperty(this);
    userkeyboardproperty->exec();

    updateChScreen();
}
/***************************************************************************
  *���������οؼ�������һ��¼�
  *************************************************************************/
void MainWindow::showMenu()//�����½������Ҽ��˵�
{
    /*QPoint pos;
    QMenu menu(tree);
    QAction *tree_newscreen= menu.addAction(tr("�½�����"));
    // menu.exec(ui.treeWidget->mapToGlobal(pos));
    connect(tree_newscreen,SIGNAL(triggered()),SLOT(tree_newscreen()));
    menu.exec(QCursor::pos());*/
    //QPoint pos;
    QMenu menu(tree0);
    QAction *tree_newscreen= menu.addAction(tr("�½�����"));
    //menu.exec(ui.treeWidget->mapToGlobal(pos));
    connect(tree_newscreen,SIGNAL(triggered()),SLOT(tree_newscreen()));
    menu.exec(QCursor::pos());
}//

//XXXXX

void MainWindow::ShowComLink()//������������Ҽ��˵�
{
    QPoint pos;
    QMenu menu(tree);
    QAction *tree_newLink= menu.addAction(tr("�������"));
    QAction *tree_deleteLink= menu.addAction(tr("ɾ��ȫ������"));
    // menu.exec(ui.treeWidget->mapToGlobal(pos));
    connect(tree_newLink,SIGNAL(triggered()),SLOT(tree_newcom()));
    connect(tree_deleteLink,SIGNAL(triggered()),SLOT(tree_deleteAllLink()));
    menu.exec(QCursor::pos());
}//
void MainWindow::tree_deleteAllLink()//ɾ�����Ӳ���
{
    if(m_pSamSysParame->m_qvcPlcCommunicate.size()>0)
    {
         m_pSamSysParame->m_qvcPlcCommunicate.clear();
    }
    if(pwnd->vTreeLinkType.size()>0)//ɾ����������
    {
        pwnd->vTreeLinkType.clear();
    }
    pwnd->link->takeChildren();//ɾ�����οؼ�����������

}
void MainWindow::tree_newcom()//������Ӳ���
{
    //��ɶ��¼ӵ����ݵĳ�ʼ��
    NewPLCCtrl plc_control(-1,this);
    stConnect con;
    if(plc_control.exec()==QDialog::Accepted)
    {
        QTreeWidgetItem *wTemp;
        wTemp=new QTreeWidgetItem(link,QStringList(tr("")));
        pwnd->vTreeLinkType.append(wTemp);
        link->insertChild(1,vTreeLinkType.last());
        vTreeLinkType.last()->setIcon(0,QIcon(":/tree/images/tree/com.ico"));
        vTreeLinkType.last()->setText(0,plc_control.m_Connect.sConnectName);
        m_pSamSysParame->m_qvcConnect.append(plc_control.m_Connect);

        pwnd->is_Save=false;
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
    }
}

void MainWindow::showScreenMenu()//�����½�����ڶ����Ҽ��˵�
{
    /*QPoint pos;
    QMenu menu(tree);
    QAction *newscreen_open= menu.addAction(tr("��(&O)"));
    QAction *newscreen_delete= menu.addAction(tr("ɾ��(&D)"));
    QAction *newscreen_property= menu.addAction(tr("����(&P)"));
    QAction *newscreen_copy= menu.addAction(tr("����(&C)"));

    connect(newscreen_open,SIGNAL(triggered()),SLOT(newscreen_open()));
    connect(newscreen_delete,SIGNAL(triggered()),SLOT(newscreen_delete()));
    connect(newscreen_property,SIGNAL(triggered()),SLOT(newscreen_property()));
    connect(newscreen_copy,SIGNAL(triggered()),SLOT(newscreen_copy()));
    menu.exec(QCursor::pos());*/
    QMenu menu(tree0);
    QAction *newscreen_open= menu.addAction(tr("��(&O)"));
    QAction *newscreen_delete= menu.addAction(tr("ɾ��(&D)"));
    QAction *newscreen_property= menu.addAction(tr("����(&P)"));
    QAction *newscreen_copy= menu.addAction(tr("����(&C)"));

    connect(newscreen_open,SIGNAL(triggered()),SLOT(newscreen_open()));
    connect(newscreen_delete,SIGNAL(triggered()),SLOT(newscreen_delete()));
    connect(newscreen_property,SIGNAL(triggered()),SLOT(newscreen_property()));
    connect(newscreen_copy,SIGNAL(triggered()),SLOT(newscreen_copy()));
    menu.exec(QCursor::pos());
}//

void MainWindow::showWindowMenu()//�����½������Ҽ��˵�
{
    /*QPoint pos;
    QMenu menu(tree);
    QAction *tree_newWindow= menu.addAction(tr("�½�����"));
    connect(tree_newWindow,SIGNAL(triggered()),SLOT(tree_newWindow()));
    menu.exec(QCursor::pos());*/
    QMenu menu(tree0);
    QAction *tree_newWindow= menu.addAction(tr("�½�����"));
    connect(tree_newWindow,SIGNAL(triggered()),SLOT(tree_newWindow()));
    menu.exec(QCursor::pos());
}//

void MainWindow::showWindowSubMenu()//�����½������Ҽ��ڶ����˵�
{
    /*QPoint pos;
    QMenu menu(tree);
    QAction *newswindow_open= menu.addAction(tr("��(&O)"));
    QAction *newswindow_delete= menu.addAction(tr("ɾ��(&D)"));
    QAction *newswindow_property= menu.addAction(tr("����(&P)"));
    QAction *newswindow_copy= menu.addAction(tr("����(&C)"));
    connect(newswindow_open,SIGNAL(triggered()),SLOT(newswindow_open()));
    connect(newswindow_delete,SIGNAL(triggered()),SLOT(newswindow_delete()));
    connect(newswindow_property,SIGNAL(triggered()),SLOT(newswindow_property()));
    connect(newswindow_copy,SIGNAL(triggered()),SLOT(newswindow_copy()));
    menu.exec(QCursor::pos());*/
    QMenu menu(tree0);
    QAction *newswindow_open= menu.addAction(tr("��(&O)"));
    QAction *newswindow_delete= menu.addAction(tr("ɾ��(&D)"));
    QAction *newswindow_property= menu.addAction(tr("����(&P)"));
    QAction *newswindow_copy= menu.addAction(tr("����(&C)"));
    connect(newswindow_open,SIGNAL(triggered()),SLOT(newswindow_open()));
    connect(newswindow_delete,SIGNAL(triggered()),SLOT(newswindow_delete()));
    connect(newswindow_property,SIGNAL(triggered()),SLOT(newswindow_property()));
    connect(newswindow_copy,SIGNAL(triggered()),SLOT(newswindow_copy()));
    menu.exec(QCursor::pos());
}//

void MainWindow::showMacroMenu()//��ָ��˵�
{
    QPoint pos;
    QMenu menu(tree);
    QAction *openJML= menu.addAction(tr("��ӽű���"));
    QAction *openJRL= menu.addAction(tr("��Ӻ�����"));
    QAction *openMacroExplorer= menu.addAction(tr("�򿪽ű������"));
    //QAction *EditMacro= menu.addAction(tr("�༭��"));
    connect(openJML,SIGNAL(triggered()),SLOT(slotAddJML()));
    connect(openJRL,SIGNAL(triggered()),SLOT(slotAddJRL()));
    connect(openMacroExplorer,SIGNAL(triggered()),SLOT(slotOpenMacro()));
    //connect(EditMacro,SIGNAL(triggered()),SLOT(slotOpenMacro()));
    menu.exec(QCursor::pos());
}//

//�ű�������غ���
void MainWindow::slotAddJML()//��ӽű���
{
    Macro lib;
    AddLib addWzrd(macros,this);
    addWzrd.setWindowTitle(tr("��ӽű�"));
    if(addWzrd.exec() == QDialog::Accepted)
    {
        qDebug() << "AddLib::accept";
        lib.libName = addWzrd.libName;
        lib.type = true;
        lib.setCompipiled(false);
        lib.setCode(SCRIPT_HEADER);
        macros.append(lib);
        MacroEdit *dlg = new MacroEdit(lib.libName,this);
        dlg->exec();
        pwnd->is_Save=false;
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
    }
}

void MainWindow::slotAddJRL()//��Ӻ�����
{
    Macro lib;
    AddLib addWzrd(macros,this);
    addWzrd.setWindowTitle(tr("��Ӻ�����"));
    if(addWzrd.exec() == QDialog::Accepted)
    {
        lib.libName = addWzrd.libName;
        lib.type = false;
        lib.setCompipiled(false);
        lib.setCode(SYS_FUNCTION_HEADER);
        macros.append(lib);
        MacroEdit *dlg = new MacroEdit(lib.libName,this);
        dlg->exec();
        pwnd->is_Save=false;
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
    }
}

void MainWindow::slotOpenMacro()//�༭�ű���
{
    if(isCompiled)
    {
        return;
    }
    dockTabWidget->setCurrentIndex(0);
    MacroEdit dlg(QString(""),this);
    dlg.exec();
    pwnd->is_Save=false;
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
}

void MainWindow::dockWidgetClose(int iData)
{
    switch(iData)
    {
    case PROJECT_MANAGE: //���̹�����
        ui->action_42->setChecked(false);
        break;
    case INFORMATION_OUTPUT: //��Ϣ�������
        ui->action_41->setChecked(false);
        break;
    case TOOL_BUTTON://������
        ui->action_tool->setChecked(false);
        break;
    default:
        break;
    }
}

//czq
//��ʷ�����ռ�����ش�����//ʵ���Ҽ��˵�
void MainWindow::AddHisDataMenu()//ʵ���Ҽ��˵�
{
    QMenu   menu(tree);
    QAction *tree_HisDataLogger = menu.addAction(tr("������ݲɼ�"));

    if(m_pSamSysParame->m_loadDataSampling.size() < 64)
    {
        connect(tree_HisDataLogger,SIGNAL(triggered()),SLOT(tree_addhisdatalogger()));
        menu.exec(QCursor::pos());
    }
    else
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("���ݲɼ��Ѵ�����"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
    }
    //----------------------------old----------------------------
    /*//QPoint pos;
    QMenu menu(tree);
    QAction *tree_HisDataLogger= menu.addAction(tr("�����ʷ�����ռ���"));
    if(!m_pSamSysParame->m_historyLogData.bHistoryDataExist)
    {
        connect(tree_HisDataLogger,SIGNAL(triggered()),SLOT(tree_addhisdatalogger()));
        menu.exec(QCursor::pos());
    }
    else
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("��ʷ�����ռ����Ѿ����ڣ���ɾ��֮�����½���"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
    }*/
}

//czq
//��ʷ�����ռ�����ش����������ʷ�����ռ���
void MainWindow::tree_addhisdatalogger()//�������
{  
    if(isCompiled)
    {
        return;
    }
    dockTabWidget->setCurrentIndex(0);//�ָ���ϵͳ����ҳ��

    IintHisData();//��ʱ�Ѿ�push_back

    int m_curDataLog = m_pSamSysParame->m_loadDataSampling.size() - 1;

    qdataloggerdlg hisdataloggerdialog(m_curDataLog,this);
    if(hisdataloggerdialog.exec() == QDialog::Accepted)
    {
        

        QTreeWidgetItem* hisdatalog_child = new QTreeWidgetItem(QStringList(m_pSamSysParame->m_vecDataSamplingStr[m_curDataLog]));
        tree_hisdatalog->addChild(hisdatalog_child);
        hisdatalog_child->setIcon(0,QIcon(":/tree/images/tree/hisdata.ico"));
        tree_hisdatalog->addChild(hisdatalog_child);

        m_vecHisdatalogChild.push_back(hisdatalog_child);

        pwnd->is_Save=false;
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ

    }
    else//��push_back���³���
    {
        m_pSamSysParame->m_loadDataSampling.pop_back();
		m_pSamSysParame->m_vecDataSamplingStr.pop_back();
        m_curDataLog = 0;
    }

    //hisdatalog_child->setIcon(0,QIcon(":/tree/images/tree/hisdata.ico"));
    //hisdatalog_child->setHidden(true);

    //���ڸĳ�ֻ��������ȷ���Ժ�����½����ݲɼ�
    //tree_openhisdata();//����ʷ���ݶԻ���

    //----------------------------old----------------------------
    /*//hisdatalog=new QHistoryDatalogger;
    m_pSamSysParame->m_historyLogData.bHistoryDataExist = true;
    //hisdatalog_child= new QTreeWidgetItem(QStringList(tr("��ʷ�����ռ���0")));
    //tree_hisdatalog->addChild(hisdatalog_child);
    //hisdatalog_child->setIcon(0,QIcon(":/tree/images/tree/hisdata.ico"));
    IintHisData();
    hisdatalog_child->setText(0,m_pSamSysParame->m_historyLogData.sHistoryDataName);
    hisdatalog_child->setHidden(false);
    tree_openhisdata();//����ʷ���ݶԻ���
    */
}

//czq
void MainWindow::IintHisData()
{
    DATA_SAMPLING tempDataSampling;

    //tempDataSampling.m_nSampType      = 1;        //ʵʱ�ɼ�
    tempDataSampling.bContiguousAddr  = false;     //�Ƿ��������ĵ�ַ
    tempDataSampling.bFullNotic       = false;    //�Ƿ�ȡ��֪ͨ
    tempDataSampling.bAutoReset       = false;    //�Ƿ��Զ���λ
    tempDataSampling.bSaveToFile      = false;    //�Ƿ񱣴��ļ�
    tempDataSampling.bAutoSave        = false;
//    tempDataSampling.bZeroSupp        = true;     //�Ƿ�������
//    tempDataSampling.bZoomIn          = false;    //�Ƿ�����
 //   tempDataSampling.bRound           = true;     //�Ƿ���������
    tempDataSampling.bAddrCtlSamp     = false;    //λ��ַ�����Ƿ����
    //tempDataSampling.bSampTime        = true;     //�Ƿ�Ƶ�ʲ���ʱ����Ϊ1��
    tempDataSampling.nDataLen         = 5;        //����λ��
    tempDataSampling.nDecimalLen      = 0;        //С������
    tempDataSampling.nStartHour       = 0;        //��ʼ��ʱ��0-23��
    tempDataSampling.nStartMinute     = 0;        //��ʼ�ķ֣�0-60��
    tempDataSampling.nEndHour         = 0;        //������ʱ��0-23��
    tempDataSampling.nEndMinute       = 0;        //�����ķ֣�0-60��
//    tempDataSampling.nSampAddrLen     = 0;        //����������(�ֵ�ַ��������)
    tempDataSampling.nDigitLen        = 16;       //λ��
    tempDataSampling.eSampType        = SampCycle;//��������
    tempDataSampling.eDealSampFull    = SFReplace;   //ȡ������ʽ
    tempDataSampling.eSaveMedium      = SM_Udisk; //�����ý��
    tempDataSampling.eDateShowType    = DateYMD;  //���ڸ�ʽ
//    tempDataSampling.eDataType        = DataInt;  //��������

    //tempDataSampling.nTotalSampNum    = 20;       //�����������
    tempDataSampling.nSampTime        = 1;
    tempDataSampling.nSampUnit        = 3;        //������λΪ�£�Ĭ��һ����

    tempDataSampling.nDataSampType    = 1;        //ʵʱ����

    tempDataSampling.nSampRate        = 1;        //������Ƶ��
    tempDataSampling.nSampRateUnit    = 1;        //Ĭ��Ϊ1��

    tempDataSampling.nSampTimes       = 1;        //��������
    tempDataSampling.nSampCountUnit   = 0;        //��������Ƶ�ʡ�Ĭ��Ϊ����
	tempDataSampling.bDynSampleRate = false;		//�Ƿ�̬����Ƶ��
	tempDataSampling.bDynTimeRange = false;			//�Ƿ�̬����ʱ�䷶Χ

//    tempDataSampling.nSourceMin       = 0;        //����Դ������Сֵ
//    tempDataSampling.nSourceMax       = 65535;    //����Դ�������ֵ
//    tempDataSampling.nTargeMin        = 0;        //����Ŀ��������Сֵ
//    tempDataSampling.nTargeMax        = 65535;    //����Ŀ���������ֵ
    //tempDataSampling.strNoticAddrId   = initKeyboard;//��ַ֪ͨ��ID��
    //tempDataSampling.strCtlSampAddrId = initKeyboard;//���Ʋ����ĵ�ַID��
    //tempDataSampling.keyAddrBegin     = initKeyboard;//������ַ��ʱ�����ʼ��ַ
    tempDataSampling.keyCtlSaveAddr.sShowAddr   = "LW0";//�����ļ��Ŀ��Ƶ�ַ
    tempDataSampling.m_dataTable.clear();         //���ݱ��

    m_pSamSysParame->m_loadDataSampling.push_back(tempDataSampling);

    //----------------------------old----------------------------
    /*m_pSamSysParame->m_historyLogData.sHistoryDataName =tr("��ʷ�����ռ���0");//��ʷ��������
    m_pSamSysParame->m_historyLogData.nSampleLen =1;           //ȡ������
    m_pSamSysParame->m_historyLogData.nSampleSize =1;           //ȡ������
    //���ݵ�ַ�ṹ��
    m_pSamSysParame->m_historyLogData.nSampleType =0;		//ȡ����ʽ
    m_pSamSysParame->m_historyLogData.nTimeInterval =1;		//��ʱȡ��ʱ��
    m_pSamSysParame->m_historyLogData.nTriggerTime =1;		//����ȡ��ʱ��
    //Keyboard addr2;                                           //����ȡ���ṹ��
    m_pSamSysParame->m_historyLogData.bFullStop =false;		//ȡ�����Ƿ�ֹͣ
    m_pSamSysParame->m_historyLogData.bFullNotic =false;	//ȡ�����Ƿ�֪ͨ
    //Keyboard addr3;                                           //ȡ����֪ͨ�ṹ��
    m_pSamSysParame->m_historyLogData.nFullNoticPercent =90;	//֪ͨ�ٷֱ�
    m_pSamSysParame->m_historyLogData.mFullNoticAddr=0;
    m_pSamSysParame->m_historyLogData.mReadAddr=0;
    m_pSamSysParame->m_historyLogData.mTriggerAddr=0;
    HISTORY_DATA_ITEM historyItem;
    historyItem.sNameList.resize(1);
    historyItem.nDataType = 0;
    historyItem.nDataShowType = 0;
    historyItem.nDataLen = 4;
    historyItem.nDataPointLen = 0;
    historyItem.bZoom = false;
    historyItem.sZoomStr = "1.0";
    historyItem.sOffsetStr = "0.0";
    m_pSamSysParame->m_historyLogData.mSampleList.clear();
    m_pSamSysParame->m_historyLogData.mSampleList.push_back(historyItem);*/
}

//czq
//��ʷ�����ռ�����ش����������ʷ�����ռ�������Ĳ���
void MainWindow::ShowSubHisdataMenu()
{
     QPoint pos;
     QMenu menu_subrecipe(tree);
     QAction *tree_openhisdata= menu_subrecipe.addAction(tr("��&O"));
     QAction *tree_deletehistata=menu_subrecipe.addAction(tr("ɾ��&D"));
     connect(tree_openhisdata,SIGNAL(triggered()),SLOT(tree_openhisdata()));
     connect(tree_deletehistata,SIGNAL(triggered()),SLOT(tree_deletehisdata()));
     menu_subrecipe.exec(QCursor::pos());
}

void MainWindow::tree_rename()
{
}

//��ʷ�����ռ�����ش���������ʷ�����ռ����Ի���
void MainWindow::tree_openhisdata()
{
    int m_curDataLog = getCurrentSamp();
    if (m_curDataLog < 0 || m_pSamSysParame->m_vecDataSamplingStr.size() <= m_curDataLog
		|| m_pSamSysParame->m_loadDataSampling.size() <= m_curDataLog)
    {
        return;
    }

    QString strOld  = m_pSamSysParame->m_vecDataSamplingStr[m_curDataLog];//��ǰ�򿪵����ݲɼ�������
    QString strNew  = strOld;
    int     typeOld = m_pSamSysParame->m_loadDataSampling[m_curDataLog].nDataSampType;
    int     typeNew = typeOld;

    qdataloggerdlg hisdataloggerdialog(m_curDataLog,this);
    if(hisdataloggerdialog.exec() == QDialog::Accepted)
    {
        pwnd->is_Save=false;
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ

        if((tree_hisdatalog && tree_hisdatalog->childCount() > m_curDataLog) && (m_pSamSysParame->m_vecDataSamplingStr.size() > m_curDataLog))
        {
            tree_hisdatalog->child(m_curDataLog)->setText(0,m_pSamSysParame->m_vecDataSamplingStr[m_curDataLog]);
        }

        strNew  = m_pSamSysParame->m_vecDataSamplingStr[m_curDataLog];
        typeNew = m_pSamSysParame->m_loadDataSampling[m_curDataLog].nDataSampType;
		
        int count = pSceneSheet.size(); //��������
		bool bUseHistory = false;
		bool bUseTrend   = false;
		bool bUseGroup   = false;
        QList<QGraphicsItem *> Items;
        for(int i = 0 ; i < count; i++) //ɨ�����л���
        {
            Items = pSceneSheet[i]->items();   //��ǰҳ�����е�item
            foreach(QGraphicsItem *pItem, Items)
            {
                if(!pItem)
                {
                    continue;
                }

                if(SAM_DRAW_OBJECT_GROUP == pItem->type())
                {
                    QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
                    if(item && item->GroupType() == SAM_DRAW_GROUP_HISTORYDATE)//��������ʷ������ʾ��
                    {
                        QHistoryDataShowAttr* hisItem = dynamic_cast<QHistoryDataShowAttr*>(item);
						if( ((typeNew != typeOld) && (strOld == hisItem->sGroupName)) ||//���͸ı�
							((strOld != strNew) && (strOld == hisItem->sGroupName)) )//���ָı�
						{
							bUseHistory = true;
							hisItem->sampChanged(strOld, strNew, typeNew);
						}
						//QMessageBox::about(this, tr("����"), tr("��ǰ���ݲɼ��ж�Ӧ����ʷ������ʾ��"));
						//hisItem->sampChanged(strOld, strNew, typeNew);
                        /*if((typeNew != typeOld) && (strOld == hisItem->sGroupName))//���͸ı�
                        {
                            QMessageBox::about(this, tr("����"), tr("��ǰ���ݲɼ��ж�Ӧ����ʷ������ʾ��"));
                        }
                        if((strOld != strNew) && (strOld == hisItem->sGroupName))//���ָı�
                        {
                            hisItem->sGroupName = strNew;
                        }*/
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_TREND)//����ͼ
                    {
                        QTrendAttr* trendItem = dynamic_cast<QTrendAttr*>(item);
						if( ((typeNew != typeOld) && (strOld == trendItem->m_sGroupNum)) ||
							((strOld != strNew) && (strOld == trendItem->m_sGroupNum)) )
						{
							bUseTrend = true;
							trendItem->sampChanged(strOld,strNew,typeNew);
						}
                        /*if(strOld == trendItem->m_sGroupNum)
                        {
                            QMessageBox::about(this, tr("����"), tr("��ǰ���ݲɼ��ж�Ӧ������ͼ"));
							trendItem->sampChanged(strOld,strNew,typeNew);
                        }*/
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_GROUPDATA)//����Ⱥ��
                    {
                        QTrendDataGroupAttr* dataItem = dynamic_cast<QTrendDataGroupAttr*>(item);
						if( ((typeNew != typeOld) && (dataItem->m_selGroups.contains(strOld))) ||
							((strOld != strNew) && (dataItem->m_selGroups.contains(strOld))) )
						{
							bUseGroup = true;
							dataItem->sampChanged(strOld,strNew,typeNew);
						}
                        /*if(dataItem->m_selGroups.contains(strOld))
                        {
                            QMessageBox::about(this, tr("����"), tr("��ǰ���ݲɼ��ж�Ӧ������Ⱥ��"));
							dataItem->sampChanged(strOld,strNew,typeNew);
                        }*/
                    }
                }
            }
        }

		if(bUseHistory)
		{
			QMessageBox::about(this, tr("����"), tr("��ǰ���ݲɼ��ж�Ӧ����ʷ������ʾ��"));
		}
		if(bUseTrend)
		{
			QMessageBox::about(this, tr("����"), tr("��ǰ���ݲɼ��ж�Ӧ������ͼ"));
		}
		if(bUseGroup)
		{
			QMessageBox::about(this, tr("����"), tr("��ǰ���ݲɼ��ж�Ӧ������Ⱥ��"));
		}
    }
}

//czq
//��ʷ�����ռ�����ش�����ɾ����ʷ��������
void MainWindow::tree_deletehisdata()
{
    int m_curDataLog = getCurrentSamp();//��ǰ���ݲɼ���
    QString str = m_pSamSysParame->m_vecDataSamplingStr[m_curDataLog];//Ҫɾ�������ݲɼ�������

    int count       = pSceneSheet.size(); //��������
    QList<QGraphicsItem *> Items;
	QList<QItemGroup *>trends;
    for(int i = 0 ; i < count; i++) //ɨ�����л���
    {
        Items = pSceneSheet[i]->items();   //��ǰҳ�����е�item
        foreach(QGraphicsItem *pItem, Items)
        {
            if(!pItem)
            {
                continue;
            }

            if(SAM_DRAW_OBJECT_GROUP == pItem->type())
            {
                if(pItem->parentItem() == 0 && pItem->type() != SAM_DRAW_OBJECT_TRACKER && pItem->type() != SAM_DRAW_OBJECT_LOCK)
                {
                    QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
                    if(item->GroupType() == SAM_DRAW_GROUP_HISTORYDATE)//��������ʷ������ʾ��
                    {
                        QHistoryDataShowAttr* hisItem = dynamic_cast<QHistoryDataShowAttr*>(item);
                        if(str == hisItem->sGroupName)
                        {
							trends << item;
                        }
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_TREND)//����ͼ
                    {
                        QTrendAttr* trendItem = dynamic_cast<QTrendAttr*>(item);
                        if(str == trendItem->m_sGroupNum)
                        {
							trends << item;
                        }
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_GROUPDATA)//����Ⱥ��
                    {
                        QTrendDataGroupAttr* dataItem = dynamic_cast<QTrendDataGroupAttr*>(item);
                        if(dataItem->m_selGroups.contains(str) )
                        {
							trends << item;
                        }
                    }
                }
            }
        }
    }

    if (trends.size() > 0)
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("��ǰ�����ѱ����ã��Ƿ�ɾ����"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("��"));
        box.button(QMessageBox::No)->setText(tr("��"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::No))
        {
            return;
        }
        else
        {
            foreach(QItemGroup *trend,trends)
            {
                trend->sampChanged(str,"",0);//ɾ�����ˢ�£�������û������
            }
            deletehisdata();
        }
    }
    else
    {
        QMessageBox box(QMessageBox::Information,tr("��ʾ"),tr("�Ƿ�ȷ��ɾ�������ݲɼ�"),QMessageBox::Ok|QMessageBox::No,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("��"));
        box.button(QMessageBox::No)->setText(tr("��"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::No))
        {
            return;
        }
        else
        {
            deletehisdata();
        }
    }
}

/************************************************************************
  *Functions:ɾ����ʷ���ݵ�ʱ�������ʷ��������
  ************************************************************************
  *Value��
  *��
  ************************************************************************
 *returns:
  *��
  ************************************************************************
  *Edit time��2011.8.29
  *Edit by    ��zhy
  *************************************************************************/
void MainWindow::deletehisdata()
{
    //czq
    /*m_pSamSysParame->m_historyLogData.bHistoryDataExist=false;       //��ʷ�����Ƿ����
    m_pSamSysParame->m_historyLogData.bFullStop=false;               //ȡ���Ƿ�ֹͣȡ��
    m_pSamSysParame->m_historyLogData.bFullNotic=false;              //ȡ���Ƿ�֪ͨ
    m_pSamSysParame->m_historyLogData.nSampleLen=0;            //ȡ������ 0-32
    m_pSamSysParame->m_historyLogData.nSampleType=0;           //ȡ����ʽ,��ʱ������������
    m_pSamSysParame->m_historyLogData.nFullNoticPercent=0;     //ȡ��֪ͨ�İٷֱ� 0-100������ٷ�֮nFullNoticPercent
    m_pSamSysParame->m_historyLogData.nTimeInterval=0;         //��ʱ���  ��Ϊ��λ
    m_pSamSysParame->m_historyLogData.nTriggerTime=0;          //���㴥��ʱ�� �ڶ��ٷ��Ӵ���
    m_pSamSysParame->m_historyLogData.nSampleSize=0;           //ȡ����С
    m_pSamSysParame->m_historyLogData.sHistoryDataName.clear();      //��ʷ��������
    m_pSamSysParame->m_historyLogData.mReadAddr=0;            //��ȡ��ַ
    m_pSamSysParame->m_historyLogData.mTriggerAddr=0;         //������ַ
    m_pSamSysParame->m_historyLogData.mFullNoticAddr=0;       //ȡ��֪ͨ��ַ
    m_pSamSysParame->m_historyLogData.mSampleList.clear();     //ȡ�����ݵ��б��ܴ�СΪnSampleLen*/

    pwnd->is_Save=false;
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ

	int m_curDataLog = getCurrentSamp();
	if (m_curDataLog >= 0)
	{
		m_pSamSysParame->m_loadDataSampling.remove(m_curDataLog);

		m_pSamSysParame->m_vecDataSamplingStr.remove(m_curDataLog);

		if (tree_hisdatalog && tree_hisdatalog->childCount() > m_curDataLog)
		{
			tree_hisdatalog->removeChild(tree_hisdatalog->child(m_curDataLog));
		}
	}
    

    m_curDataLog = 0;
}

/***************************************************
*���ֱ�����½�Ҽ��˵�
******************************************************/
void MainWindow::showAlarmMenu()
{
    QPoint pos;
    QMenu menu(tree);
    QAction *alarm_action=menu.addAction(tr("����������¼"));

    connect(alarm_action,SIGNAL(triggered()),this,SLOT(tree_digitAlarm()));
    menu.exec(QCursor::pos());

}//

/**********************************************
*���������½���Ҽ��˵��ϵ�������λ������½
**************************************************/
void MainWindow::tree_digitAlarm()
{
    if(isCompiled)
    {
        return;
    }
    QString str="";
    QString sTmp="";
    //�����λ������½
    if(m_pSamSysParame->m_qvcAlarm.size() >= DIGIT_ALARM_NUM)
    {
        QMessageBox box(this);
        box.setText(QString(tr("������¼���Ϊ%1��")).arg(DIGIT_ALARM_NUM));
        box.exec();
        return;
    }

    dockTabWidget->setCurrentIndex(0);//�л�����һ��ҳ��



    AlarmSet *alarmDlg = new AlarmSet(this);
    if(alarmDlg->exec() == QDialog::Accepted)
    {
        pwnd->is_Save=false;
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);

        QStringList alarmName;
        alarmName.append(alarmDlg->alarmGrp.alarmName);
        m_pSamSysParame->m_qvcAlarm.append(alarmDlg->alarmGrp);
        QTreeWidgetItem *treeAlarmItem = new QTreeWidgetItem(alarmlog,alarmName);
        treeAlarmItem->setIcon(0,QIcon(":/btn/images/alarm.ico"));
        alarmlog->addChild(treeAlarmItem);
    }
    /*
    DIGITAL_ALARM_PROP digitalAlarm;
    digitalalarmlogdlg->initDigitalStruct(digitalAlarm);
    m_pSamSysParame->m_qvcDigitalAlarm.push_back(digitalAlarm);//
    QStringList temp;
    int analogSize = m_pSamSysParame->m_qvcAnalogAlarm.size();
    int digitalSize = m_pSamSysParame->m_qvcDigitalAlarm.size();
    int totalSize = analogSize + digitalSize;
    if(totalSize - 1 >= 0 && totalSize -1 < 10)
    {
        temp=QStringList(QString("00%1:").arg(totalSize-1)+tr("��λ������½")+QString("%1").arg(digitalSize));;
    }
    else if(totalSize -1 >= 10 && totalSize -1 <=99)
    {
        temp=QStringList(QString("0%1:").arg(totalSize-1)+tr("��λ������½")+QString("%1").arg(digitalSize));;
    }
    else if(totalSize -1 >= 100)
    {
        temp=QStringList(QString("%1:").arg(totalSize-1)+tr("��λ������½")+QString("%1").arg(digitalSize));;
    }

    digital_treeItem[digitalSize-1]=new QTreeWidgetItem(alarmlog,QStringList(temp));
    digital_treeItem[digitalSize-1]->setIcon(0,QIcon(":/btn/images/balarm.ico"));
    alarmlog->addChild(digital_treeItem[digitalSize-1]);
    */
}//
/****************************************************************************/

/**********************************************************
  *��λ���������Ҽ��򿪺�ɾ���˵�
  **********************************************************/
void MainWindow::showDigitalAlarmMenu()
{
    QPoint pos;
    QMenu menu(tree);
    QAction *digitAlarm_open=menu.addAction(tr("��"));
    QAction *digitAlarm_delete=menu.addAction(tr("ɾ��"));

    connect(digitAlarm_open,SIGNAL(triggered()),this,SLOT(digitAlarm_open()));
    connect(digitAlarm_delete,SIGNAL(triggered()),this,SLOT(digitAlarm_delete()));
    menu.exec(QCursor::pos());

}//



/**************************************************
�����Ҽ�ɾ���¼�
******************************************************/
void MainWindow::digitAlarm_delete()//���������½���Ҽ��˵��ϵ�ɾ��
{
    QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("�Ƿ�ɾ����ѡ������"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.button(QMessageBox::Ok)->setText(tr("��"));
    box.button(QMessageBox::No)->setText(tr("��"));
    box.exec();
    if(box.clickedButton()== box.button(QMessageBox::No))
    {
        return;
    }
    QString str=tree->currentItem()->text(0);
    ALARM_GROUP alarmGrp;
    for(int i=0; i<m_pSamSysParame->m_qvcAlarm.size();i++)
    {
        alarmGrp = m_pSamSysParame->m_qvcAlarm.at(i);
        if(alarmGrp.alarmName == str)
        {
            m_pSamSysParame->m_qvcAlarm.remove(i);
        }
    }
    alarmlog->removeChild(tree->currentItem());
    pwnd->is_Save=false;//
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
}//

/**************************************************
*��λ����1-10�Ҽ����¼�
******************************************************/
void MainWindow::digitAlarm_open()//�����λ������½���Ҽ��˵��ϵĴ�
{

    QTreeWidgetItem *treeItem = tree->currentItem();
    QString str=treeItem->text(0);
    int index = 0;
    foreach(ALARM_GROUP alarmGrp,m_pSamSysParame->m_qvcAlarm)
    {

        if(alarmGrp.alarmName == str)
        {
            AlarmSet *alarmDlg = new AlarmSet(this);
            alarmDlg->Init(alarmGrp,index);
            if(alarmDlg->exec() == QDialog::Accepted)
            {
                m_pSamSysParame->m_qvcAlarm.replace(index, alarmDlg->alarmGrp);
                treeItem->setText(0,alarmDlg->alarmGrp.alarmName);
                pwnd->is_Save=false;
                is_NeedCompiled = true;
                pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
            }
            alarmDlg->deleteLater();
            alarmDlg = NULL;
            break;
        }
        index++;
    }

}//

void MainWindow::showRecipeMenu()//��������䷽�Ҽ��˵�
{
    QPoint pos;
    QMenu menu_recipe(tree);
    pwnd->m_pSamSysParame->m_qRecipe.formula.clear();
    pwnd->m_pSamSysParame->m_qRecipe.sName = "";
    QAction *tree_recipe= menu_recipe.addAction(tr("����䷽"));
    connect(tree_recipe,SIGNAL(triggered()),SLOT(tree_recipe()));
    menu_recipe.exec(QCursor::pos());
}//ok

void MainWindow::showSubRecipeMenu()//����䷽1���Ҽ��˵�
{
    QPoint pos;
    QMenu menu_subrecipe(tree);
    QAction *tree_openrecipe= menu_subrecipe.addAction(tr("��&O"));
    QAction *tree_deleterecipe=menu_subrecipe.addAction(tr("ɾ��&D"));
    connect(tree_openrecipe,SIGNAL(triggered()),SLOT(tree_openrecipe()));
    connect(tree_deleterecipe,SIGNAL(triggered()),SLOT(tree_deleterecipe()));
    menu_subrecipe.exec(QCursor::pos());
}//ok

//������ؼ��ϵ��Ҽ��˵��¼���Ӧ
void MainWindow::tree_openrecipe()//���䷽�Ի���
{
    QString str = tree->currentItem()->text(0);
    for(int i = 0; i < pwnd->m_pSamSysParame->m_qvcRecipe.size();i++)
    {
        if(str == pwnd->m_pSamSysParame->m_qvcRecipe[i].sName)
        {
            pwnd->m_pSamSysParame->m_qRecipe = pwnd->m_pSamSysParame->m_qvcRecipe[i];
            QTreeCtrlRecipeDlg *pRecipeDlg = new QTreeCtrlRecipeDlg(this,i);
            if(pRecipeDlg->exec() == QDialog::Accepted)
            {
                pwnd->m_pSamSysParame->m_qvcRecipe.replace(i,pRecipeDlg->Pro);
                tree->currentItem()->setText(0,pRecipeDlg->Pro.sName);

                //ˢ���䷽��ʾ��
                int size = pSceneSheet.size();
                for(int j = 0; j< size; j++)
                {
                    QList <QGraphicsItem *> list;
                    list = pSceneSheet.at(j)->TopItems();
                    foreach(QGraphicsItem *pItem,list)
                    {
                        if(SAM_DRAW_OBJECT_GROUP == pItem->type())
                        {
                            QItemGroup *pItemGroup = dynamic_cast<QItemGroup *> (pItem);
                            if(pItemGroup)
                            {
                                if(SAM_DRAW_GROUP_RECIPESHOW == pItemGroup->GroupType())
                                {
                                    QRecipeTableItem *pRicipeItem = dynamic_cast<QRecipeTableItem *> (pItem);
                                    if(pRicipeItem)
                                    {
                                        pRicipeItem->RefreshItem(i);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            pRecipeDlg->deleteLater();
            pRecipeDlg = NULL;
            break;
        }
    }
    pwnd->is_Save=false;
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ

    pwnd->m_pSamSysParame->m_qRecipe.formula.clear();
    pwnd->m_pSamSysParame->m_qRecipe.sName = "";
//    QTreeCtrlRecipeDlg recipeDlg(this);
//    recipeDlg.exec();
}//

void MainWindow::tree_deleterecipe()
{
    QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("�Ƿ�ɾ����ѡ�䷽��"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.button(QMessageBox::Ok)->setText(tr("��"));
    box.button(QMessageBox::No)->setText(tr("��"));
    box.exec();
    if(box.clickedButton()== box.button(QMessageBox::No))
    {
        return;
    }
    QTreeWidgetItem *pChildItem = tree->currentItem();
    for(int i = 0; i < pwnd->m_pSamSysParame->m_qvcRecipe.size();i++)
    {
        if(pChildItem->text(0) == pwnd->m_pSamSysParame->m_qvcRecipe[i].sName)
        {
            recipe->removeChild(pChildItem);
            delete pChildItem;
            pChildItem = NULL;
            pwnd->m_pSamSysParame->m_qvcRecipe.remove(i);


            //ˢ���䷽��ʾ��
            int size = pSceneSheet.size();
            for(int j = 0; j< size; j++)
            {
                QList <QGraphicsItem *> list;
                list = pSceneSheet.at(j)->TopItems();
                foreach(QGraphicsItem *pItem,list)
                {
                    if(SAM_DRAW_OBJECT_GROUP == pItem->type())
                    {
                        QItemGroup *pItemGroup = dynamic_cast<QItemGroup *> (pItem);
                        if(pItemGroup)
                        {
                            if(SAM_DRAW_GROUP_RECIPESHOW == pItemGroup->GroupType())
                            {
                                QRecipeTableItem *pRicipeItem = dynamic_cast<QRecipeTableItem *> (pItem);
                                if(pRicipeItem)
                                {
                                    if(i == pRicipeItem->GetRicipeGroupId(i))//ɾ����ǰ��I���䷽�飬����������䷽���Ӧ���䷽��ʾ��Ϊ��Ч
                                        pRicipeItem->setInvalid();
                                        //pSceneSheet.at(j)->removeItem(pItem);
                                }
                            }
                            else if(SAM_DRAW_GROUP_RECIPE == pItemGroup->GroupType())
                            {
                                QRcipeItem *pRicipeItem = dynamic_cast<QRcipeItem *> (pItem);
                                if(pRicipeItem)
                                {
                                    if(i == pRicipeItem->GetRicipeGroupId(i))
                                        pRicipeItem->setInvalid();
                                        //pSceneSheet.at(j)->removeItem(pItem);
                                }
                            }
                        }
                    }
                }
            }
            break;
        }
    }
    pwnd->is_Save=false;
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ

}

void MainWindow::tree_newscreen()
{
    QString sTmp="";
    QString sNo="";
    emit InitScreenDlg();
    newScreenDlg->setWindowTitle(tr("�½�����"));

    int res=newScreenDlg->exec();
    if(res==QDialog::Accepted)
    {
        pwnd->is_Save=false;//
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
        emit  newscreen_Assign();
        upDatetreeScreenItem();//���»��������
        pwnd->reScreenorwindowName(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName,newScreenDlg->ui->newscreen_name_lineedit->text());
        //�������и��ĵĻ�ˢ�»��水ť������
        sTmp=pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(1);

        updateChScreen();

        //list_style
        //if(pwnd->list_style->currentIndex()==0||pwnd->list_style->currentIndex()==1)
        if(1)
        {
            //pwnd->tree->setCurrentItem(pwnd->copyScreen_Item->child(pwnd->nActiveSheetIndex));
            //pwnd->tree->setFocus(Qt::MouseFocusReason);
            pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(pwnd->nActiveSheetIndex));
            pwnd->tree0->setFocus(Qt::MouseFocusReason);
            for(int j=0;j<pwnd->copyScreen_Item->childCount();j++)
            {
                sNo=pwnd->copyScreen_Item->child(j)->text(0).split(":").at(1);
                if(sTmp==sNo)
                {
                    //pwnd->tree->setCurrentItem(pwnd->copyScreen_Item->child(j),0,QItemSelectionModel::SelectCurrent);
                    //pwnd->tree->setFocus(Qt::ActiveWindowFocusReason);
                    pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(j),0,QItemSelectionModel::SelectCurrent);
                    pwnd->tree0->setFocus(Qt::ActiveWindowFocusReason);
                }
            }//
        }
        /*else
        {
            pwnd->tree->setCurrentItem(pwnd->newScreen[pwnd->nActiveSheetIndex],0,QItemSelectionModel::SelectCurrent);
            pwnd->tree->setFocus(Qt::MouseFocusReason);
            PreviewWindow();
            tree->collapseAll();
            tree->expandAll();
        }*/
        SamDrawScene* pSceneTemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex];
        int iActiveSheetIndex = pwnd->nActiveSheetIndex;
        int iTreeIndex = pwnd->screen->indexOfChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);
        undoStack->push(new AddSceneCommand(pSceneTemp, iActiveSheetIndex, iTreeIndex));
    }
}//

void MainWindow::tree_newWindow()//����
{
    QString sTmp="";
    QString sNo="";
    newWindowDlg->ui->spinBox_w->setRange(0,m_pSamSysParame->m_projectProp.nSceneWidth);
    newWindowDlg->ui->spinBox_h->setRange(0,m_pSamSysParame->m_projectProp.nSceneHeight);
    emit InitWindowDlg();
    int res=newWindowDlg->exec();
    if(res==QDialog::Accepted)
    {
        pwnd->is_Save=false;//
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ

        emit  newwindow_Assign();
        upDatetreeScreenItem();//���»��������
        sTmp=pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(1);

        updateChScreen();
        //list_style
        //if(pwnd->list_style->currentIndex()==0||pwnd->list_style->currentIndex()==1)
        if(1)
        {
             //pwnd->tree->setCurrentItem(pwnd->copyWindow_Item->child(pwnd->nActiveSheetIndex));
             //pwnd->tree->setFocus(Qt::MouseFocusReason);
             pwnd->tree0->setCurrentItem(pwnd->copyWindow_Item->child(pwnd->nActiveSheetIndex));
             pwnd->tree0->setFocus(Qt::MouseFocusReason);
             for(int j=0;j<pwnd->copyWindow_Item->childCount();j++)
             {
                 sNo=pwnd->copyWindow_Item->child(j)->text(0).split(":").at(1);
                 if(sTmp==sNo)
                 {
                    //pwnd->tree->setCurrentItem(pwnd->copyWindow_Item->child(j),0,QItemSelectionModel::SelectCurrent);
                    //pwnd->tree->setFocus(Qt::ActiveWindowFocusReason);
                    pwnd->tree0->setCurrentItem(pwnd->copyWindow_Item->child(j),0,QItemSelectionModel::SelectCurrent);
                    pwnd->tree0->setFocus(Qt::ActiveWindowFocusReason);
                 }
             }//
        }
        /*else
        {
             pwnd->tree->setCurrentItem(pwnd->newScreen[pwnd->nActiveSheetIndex],0,QItemSelectionModel::SelectCurrent);
             pwnd->tree->setFocus(Qt::MouseFocusReason);
             PreviewWindow();
             tree->collapseAll();
             tree->expandAll();
        }*/
        SamDrawScene* pSceneTemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex];
        int iActiveSheetIndex = pwnd->nActiveSheetIndex;
        int iTreeIndex = pwnd->window->indexOfChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);
        undoStack->push(new AddWindowCommand(pSceneTemp, iActiveSheetIndex, iTreeIndex));
    }
}//

void MainWindow::tree_recipe()
{
    if(isCompiled)
    {
        return;
    }
    pwnd->is_Save=false;
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ

    dockTabWidget->setCurrentIndex(0);//�л�����һ��ҳ��

    QTreeCtrlRecipeDlg *pRecipeDlg = new QTreeCtrlRecipeDlg(this);
    if(pRecipeDlg->exec() == QDialog::Accepted)
    {
        pwnd->m_pSamSysParame->m_qvcRecipe.append(pRecipeDlg->Pro);
        QTreeWidgetItem *pSubTreeWidgetItem = new QTreeWidgetItem(recipe);
        pSubTreeWidgetItem->setIcon(0,QIcon(":/tree/images/tree/recipe.ico"));
        pSubTreeWidgetItem->setText(0,pRecipeDlg->Pro.sName);
    }
    pRecipeDlg->deleteLater();
    pRecipeDlg = NULL;
  }
//���ԭ�����οؼ�
void MainWindow::clearTree()
{
    //�������
    QList<QTreeWidgetItem *> childItems = link->takeChildren();
    childItems.clear();
    //�������
    QList<QTreeWidgetItem *> huamian = screen->takeChildren();
    huamian.clear();
    //�䷽���
    QList<QTreeWidgetItem *> childItem = recipe->takeChildren();
    childItem.clear();
    //������½
    QList<QTreeWidgetItem *> baojingItem = alarmlog->takeChildren();
    baojingItem.clear();
    //���ݲɼ�
    QList<QTreeWidgetItem *> shujucaiji = tree_hisdatalog->takeChildren();
    shujucaiji.clear();
    //��սű�
    //librarys.clear();
}
/*************************************************************************
  *�������׼���������½�����������ۺ���
***************************************************************************/
void MainWindow::createprodlg()
{
    if(isCompiled)
    {
        return ;
    }
    if(!isHave)
    {
        //���ԭ�����οؼ�
        clearTree();
        /*init all need new data*/
        init();
        qLanguagecmb->clear();
        for(int i=0;i<m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();i++)
        {
            qLanguagecmb->addItem(m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
        }
        qLanguagecmb->setEnabled(true);
        qLanguagecmb->setCurrentIndex(0);
        //m_pSamSysParame->m_mixGlobalVar.m_nCurLan = 0;

        isHave=true;
        //QNewProDlg *newprodlg=new QNewProDlg(this);
        qNewProDlgEx *newprodlg=new qNewProDlgEx(this);
        if(newprodlg->exec() != QDialog::Accepted)
        {
            link->takeChildren();
            return;
        }
    }
    else
    {
        if(!pwnd->is_Save)//�й���û����������//�Ѿ�������½���ť
        {
            QMessageBox box(QMessageBox::Information,tr("��ʾ"),tr("�Ƿ񱣴浱ǰ����"),QMessageBox::Ok|QMessageBox::No|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("��"));
            box.button(QMessageBox::No)->setText(tr("��"));
            box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));
            box.exec();
            if(box.clickedButton()== box.button(QMessageBox::Ok))//������˱��浱ǰ����
            {
                //���ԭ�����οؼ�
                clearTree();
                createsavedlg();
                is_Is=true;
                isHave=false;
                is_OpenrecentFile=false;
                is_click_open=false;
                openInit_MenuAndTool();

                reTree_ScreenAndWindow();

                pMainList->clear();
                pMainList->setRowCount(0);
                nActiveSheetIndex=0; //��ǰ������ţ���0��ʼ
                pwnd->setWindowTitle(QString(VERSION_NAME));

                /*init all need new data*/
                init();
                qLanguagecmb->clear();
                for(int i=0;i<m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();i++)
                {
                    qLanguagecmb->addItem(m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
                }
                qLanguagecmb->setEnabled(true);
                qLanguagecmb->setCurrentIndex(0);
                //m_pSamSysParame->m_mixGlobalVar.m_nCurLan = 0;

                //QNewProDlg *newprodlg=new QNewProDlg(this);
                qNewProDlgEx *newprodlg=new qNewProDlgEx(this);
                if(newprodlg->exec() != QDialog::Accepted)
                {
                    link->takeChildren();
                    return;
                }
            }
            else if(box.clickedButton()== box.button(QMessageBox::No))//������˷�
            {
                //���ԭ�����οؼ�
                clearTree();
                is_Is=true;
                isHave=false;
                is_OpenrecentFile=false;
                is_click_open=false;
                openInit_MenuAndTool();
                reTree_ScreenAndWindow();

                pMainList->clear();
                pMainList->setRowCount(0);
                pwnd->setWindowTitle(QString(VERSION_NAME));

                /*init all need new data*/
                init();
                qLanguagecmb->clear();
                for(int i=0;i<m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();i++)
                {
                    qLanguagecmb->addItem(m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
                }
                qLanguagecmb->setEnabled(true);
                qLanguagecmb->setCurrentIndex(0);
                //m_pSamSysParame->m_mixGlobalVar.m_nCurLan = 0;

                //QNewProDlg *newprodlg=new QNewProDlg(this);
                qNewProDlgEx *newprodlg=new qNewProDlgEx(this);
                if(newprodlg->exec() != QDialog::Accepted)
                {
                    link->takeChildren();
                    return;
                }
            }
            else if(box.clickedButton()== box.button(QMessageBox::Cancel))//�������ȡ��
            {
                return;
            }
        }
        else//�����ǰ����
        {
            //���ԭ�����οؼ�
            clearTree();
            is_Is=true;
            isHave=false;
            is_OpenrecentFile=false;
            is_click_open=false;
            openInit_MenuAndTool();
            reTree_ScreenAndWindow();

            pMainList->clear();
            pMainList->setRowCount(0);
            pwnd->setWindowTitle(QString(VERSION_NAME));

            /*init all need new data*/
            init();
            qLanguagecmb->clear();
            for(int i=0;i<m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();i++)
            {
                qLanguagecmb->addItem(m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
            }
            qLanguagecmb->setEnabled(true);
            qLanguagecmb->setCurrentIndex(0);
            //m_pSamSysParame->m_mixGlobalVar.m_nCurLan = 0;

            //QNewProDlg *newprodlg=new QNewProDlg(this);
            qNewProDlgEx *newprodlg=new qNewProDlgEx(this);
            if(newprodlg->exec() != QDialog::Accepted)
            {
                link->takeChildren();
                return;
            }
        }
    }

    stProtocol pro;
    pro.nPlcNo          = 1;
    pro.nReceiveTimeout = 1000;
    pro.nMaxRWLen       = 32;
    pro.nRetryTime      = 3;
    pro.nIntervalTime   = 10;
    pro.nCycleTime      = 1;
    pro.ip              = "192.168.1.100";
    pro.port            = 12345;
    pro.sName           = newpro->sName;
    pro.sFactoryName    = newpro->sFactoryName.left(newpro->sFactoryName.lastIndexOf("("));
    pro.sProtocolName   = newpro->sProtocolName;
    pro.bIsTcpProtocol = false;
    bool bExist = false;
    foreach(PLC_FACTORY factory, vPlc)
    {
        if (factory.sFactoryName == pro.sFactoryName)
        {
            foreach(PLC_MODEL model,factory.models)
            {
                if (model.sModelName == pro.sProtocolName)
                {
                    pro.mPlc = model;
                    bExist = true;
                    break;
                }
            }
            break;
        }
    }
    if(bExist)
    {
        pro.nIntervalTime   = pro.mPlc.nIntervalTime;
        pro.nMaxRWLen       = pro.mPlc.nMaxRWLen;
        pro.nRetryTime      = pro.mPlc.nRetryTime;
        pro.nPlcNo          = pro.mPlc.nPlcNo;
        pro.nReceiveTimeout = pro.mPlc.nReceiveTimeout;
        pro.nCycleTime      = pro.mPlc.nCycleTime;
    }

    QTreeWidgetItem *cItem;
    QTreeWidgetItem *wTemp;
    if("COM1" == newpro->proFlag)//com1
    {
        cItem = link->child(0);
        QString str = cItem->text(0);
        wTemp = new QTreeWidgetItem(cItem,QStringList(tr("")));

        cItem->insertChild(1,wTemp);
        cItem->setExpanded(true);
        wTemp->setIcon(0,QIcon(":/tree/images/tree/com.ico"));
        wTemp->setText(0,pro.sName);
        m_pSamSysParame->m_qvcConnect[0].vProtocols.append(pro);
        //�½���������Ĭ�ϴ��ڲ���
        setDefaultPlc(0);
    }
    else if("COM2" == newpro->proFlag)//com2
    {
        cItem = link->child(1);
        QString str = cItem->text(0);
        wTemp = new QTreeWidgetItem(cItem,QStringList(tr("")));

        cItem->insertChild(1,wTemp);
        cItem->setExpanded(true);
        wTemp->setIcon(0,QIcon(":/tree/images/tree/com.ico"));
        wTemp->setText(0,pro.sName);
        m_pSamSysParame->m_qvcConnect[1].vProtocols.append(pro);
        setDefaultPlc(1);
    }
    else if("COM3" == newpro->proFlag)//com3
    {
        cItem = link->child(2);
        QString str = cItem->text(0);
        wTemp = new QTreeWidgetItem(cItem,QStringList(tr("")));

        cItem->insertChild(1,wTemp);
        cItem->setExpanded(true);
        wTemp->setIcon(0,QIcon(":/tree/images/tree/com.ico"));
        wTemp->setText(0,pro.sName);
        m_pSamSysParame->m_qvcConnect[2].vProtocols.append(pro);
        setDefaultPlc(1);
    }
    else if(tr("��̫��") == newpro->proFlag || newpro->proFlag == tr("����"))//��̫��
    {
        cItem = link->child(3);
        QString str = cItem->text(0);
        wTemp = new QTreeWidgetItem(cItem,QStringList(tr("")));

        cItem->insertChild(1,wTemp);
        cItem->setExpanded(true);
        wTemp->setIcon(0,QIcon(":/tree/images/tree/com.ico"));
        wTemp->setText(0,pro.sName);
        m_pSamSysParame->m_qvcConnect[3].vProtocols.append(pro);
    }
    else//CAN����
    {
        cItem = link->child(4);
        QString str = cItem->text(0);
        wTemp = new QTreeWidgetItem(cItem,QStringList(tr("")));

        cItem->insertChild(1,wTemp);
        cItem->setExpanded(true);
        wTemp->setIcon(0,QIcon(":/tree/images/tree/com.ico"));
        wTemp->setText(0,pro.sName);
        m_pSamSysParame->m_qvcConnect[4].vProtocols.append(pro);
    }

    //QString strT = GetHMIConnectInformation(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelName);
    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom1.contains("com1"))
    {
        link->child(0)->setDisabled(false);
    }
    else
    {
        link->child(0)->setDisabled(true);
    }
    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom1.contains("com2"))
    {
        link->child(1)->setDisabled(false);
    }
    else
    {
        link->child(1)->setDisabled(true);
    }

    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom1.contains("com3"))
    {
        link->child(2)->setDisabled(false);
    }
    else
    {
        link->child(2)->setDisabled(true);
    }

    if(!pwnd->m_pSamSysParame->m_mixGlobalVar.m_strMaxscreennumber.contains("Ethernet(NONE)"))
    {
        link->child(3)->setDisabled(false);
    }
    else
    {
        link->child(3)->setDisabled(true);
    }

    if(!pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom2.contains("NONE"))
    {
        link->child(4)->setDisabled(false);
        if(link->childCount() > 5)
            link->child(5)->setDisabled(false);
    }
    else
    {
        link->child(4)->setDisabled(true);
        if(link->childCount() > 5)
            link->child(5)->setDisabled(true);
    }

    QFile file("userkeyboard.dat");
    if(!file.open(QIODevice::ReadOnly))
    {
        return ;
    }
    QDataStream out(&file);
    SamDrawScene *pScene = NULL;

    int num  = 0;
    for(num = 0; !out.atEnd(); num++)
    {
        pScene = new SamDrawScene;
        //out >> pScene;
        pScene->load(out,pScene);
        if(num < 6)
        {
            delete pScene;
            pScene = NULL;
        }
        else if(num == 6)
        {
            break;
        }
   }

    if(num != 6)
    {
        file.close();
        return;//18���� Ĭ��ȡ��6�����ּ��̣� �ɸ���
    }

    pScene->DrawScreenSize();

    file.close();

    TreeKeyboard->setHidden(false);//��ʾ���οؼ�

    pSceneSheet.push_back(pScene);//����Զ�����̻��浽������
    pSceneSheet[pSceneSheet.size() - 1]->nIsSceneOrWindow = 2;
    connect(pSceneSheet[pSceneSheet.size()-1],SIGNAL(DoubleClickItem(QGraphicsItem *)),this,SLOT(SlotItemDBClick(QGraphicsItem *)));
    connect(pSceneSheet[pSceneSheet.size()-1],SIGNAL(SingleClickItem()),this,SLOT(OnSingleClickItem()));
    connect(pSceneSheet[pSceneSheet.size()-1],SIGNAL(SingleClickItem()),this,SLOT(AddItemToScene()));
    connect(pSceneSheet[pSceneSheet.size()-1], SIGNAL(itemsMoved(SamDrawScene*,QList<QGraphicsItem*>,QList<QPointF>)),
            this, SLOT(itemsMoved(SamDrawScene *,QList <QGraphicsItem *>,QList <QPointF >)));
    connect(pSceneSheet[pSceneSheet.size()-1], SIGNAL(Messageout(QString, MSG_TYPE, MsgOutPut*)), this, SLOT(MessageOutEx(QString, MSG_TYPE, MsgOutPut*)));

    int nscenecount=pSceneSheet.size()-1;
    QString stemp;
    unsigned ntemp = TreeKeyboard->childCount();
    newScreen[nscenecount]=new QTreeWidgetItem(TreeKeyboard,QStringList(tr("")));
    stemp=QString("%1%2%3").arg(ntemp/100).arg((ntemp/10)%10).arg(ntemp%10);

    QString str=pSceneSheet[nscenecount]->sNewScreenName;
    newScreen[nscenecount]->setText(0,stemp+":"+tr("���ּ���")+QString("%1").arg(str.mid(4,1)));
    pSceneSheet[nscenecount]->sNewScreenName=tr("���ּ���")+QString("%1").arg(str.mid(4,1));
    TreeKeyboard->addChild(newScreen[nscenecount]);
    pSceneSheet[nscenecount]->sNewScreenName = newScreen[nscenecount]->text(0).split(":").last();
    m_pSamSysParame->nUserDefKeyboardCount++;

    updateChScreen();

    if(pView)
    {
        QScrollBar *pHorizScrollBar = pView->horizontalScrollBar();
        if(pHorizScrollBar)
        {
            pHorizScrollBar->setValue(1);
        }
        QScrollBar *pVerticalScrollBar = pView->verticalScrollBar();
        if(pVerticalScrollBar)
        {
            pVerticalScrollBar->setValue(1);
        }
    }

    //wxy���¹���ɾ����ԭ�ȵĽű������ı�����������жϴ���
    QFile::remove("sdmacro\\ml\\ml.jar");
    is_NeedCompiled = true;
//    mPicPath.clear();
//    mPicMd5.clear();
//    deleteDirectory(QFileInfo("resource"));
}//


/*************************************************************************
  *�������׼�������ϴ򿪹���������ۺ���
***************************************************************************/
void MainWindow::createopenprodlg(QString path)
{
    QString fileName;

    if(!pwnd->is_Is)//��������Ч�������
    {
        if(!pwnd->is_Save)//�й���û����������
        {
            QMessageBox box(QMessageBox::Information,tr("��ʾ"),tr("�Ƿ񱣴浱ǰ����"),QMessageBox::Ok|QMessageBox::No|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("��"));
            box.button(QMessageBox::No)->setText(tr("��"));
            box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));
            box.exec();
            if(box.clickedButton()== box.button(QMessageBox::Ok))
            {
                createsavedlg();
                reTree_ScreenAndWindow();

                is_Is=true;
                isHave=false;
                is_OpenrecentFile=false;
                is_click_open=false;
                openInit_MenuAndTool();
                qLanguagecmb->clear();
                //AAAAAA
                link->takeChildren();
                if(tree_hisdatalog->childCount() > 0)
                {
                    tree_hisdatalog->takeChildren();
                }
                if(recipe->childCount() > 0)
                {
                    recipe->takeChildren();
                }
                if(alarmlog->childCount() > 0)
                {
                    alarmlog->takeChildren();
                }
            }
            if(box.clickedButton()== box.button(QMessageBox::No))
            {
                reTree_ScreenAndWindow();

                is_Is=true;
                isHave=false;
                is_OpenrecentFile=false;
                is_click_open=false;
                openInit_MenuAndTool();
                qLanguagecmb->clear();
                //AAAAAA
                link->takeChildren();
                if(tree_hisdatalog->childCount() > 0)
                {
                    tree_hisdatalog->takeChildren();
                }
                if(recipe->childCount() > 0)
                {
                    recipe->takeChildren();
                }
                if(alarmlog->childCount() > 0)
                {
                    alarmlog->takeChildren();
                }
            }
            else if(box.clickedButton()== box.button(QMessageBox::Cancel))
            {
                return;
            }
        }
        else//�����Ѿ�����
        {
            is_Is=true;
            isHave=false;
            is_OpenrecentFile=false;
            is_click_open=false;
            openInit_MenuAndTool();

            reTree_ScreenAndWindow();
            qLanguagecmb->clear();

            //AAAAAA
            link->takeChildren();
            if(tree_hisdatalog->childCount() > 0)
            {
                tree_hisdatalog->takeChildren();
            }
            if(recipe->childCount() > 0)
            {
                recipe->takeChildren();
            }
            if(alarmlog->childCount() > 0)
            {
                alarmlog->takeChildren();
            }
        }
    }
    else
    {
        //AAAAAA
        link->takeChildren();
        if(tree_hisdatalog->childCount() > 0)
        {
            tree_hisdatalog->takeChildren();
        }
        if(recipe->childCount() > 0)
        {
            recipe->takeChildren();
        }
        if(alarmlog->childCount() > 0)
        {
            alarmlog->takeChildren();
        }
    }

     /*init all need new data*/
     QString proName = "resource";
     QDir dir = QDir(proName);
     if(dir.exists())
     {
         QStringList fileList = dir.entryList();
         foreach(QString sTmp,fileList)
         {
             dir.remove(sTmp);
         }
     }

     init();
     setWindowTitle(QString(VERSION_NAME));
     pMainList->clear();
     pMainList->setRowCount(0);

     if(is_Click_OpenrecentFile)//�������������򿪵�Actionʱ
     {
         fileName=sRecentflieName;
         is_OpenrecentFile=true;
         is_Click_OpenrecentFile=false;
     }
     else if(!path.isEmpty())//��·��Ϊ�յĻ� ����˫�����̴�
     {
         fileName=path;
     }
     else
     {
         fileName = QFileDialog::getOpenFileName(this,tr("���ļ�"),sFilePath,SUFFIX);//,0,QFileDialog::DontUseNativeDialog);
         if("" != fileName)
         {
             QString sTemp = fileName;
             QString str = sTemp.section("/",-1);
             sFilePath = sTemp.remove(str);
         }
         is_click_open=true;
         sOpenflieName=fileName;
         if(fileName.isEmpty())
         {
             is_click_open=false;
              return ;
         }
     }

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox box(QMessageBox::Information,tr("����"),tr("���ļ�ʧ�ܣ�"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
        box.exec();
        file.close();
        //AAAAAA
        link->takeChildren();
        if(tree_hisdatalog->childCount() > 0)
        {
            tree_hisdatalog->takeChildren();
        }
        if(recipe->childCount() > 0)
        {
            recipe->takeChildren();
        }
        if(alarmlog->childCount() > 0)
        {
            alarmlog->takeChildren();
        }
        return ;
    }
   // emit reTreeScreenAndWindow();
    picturePath="/home";//ͼƬ·�����
    QDataStream out(&file);

    /*read project version*/
	int versionNum = AK_CURRENT_VERSION;
    QString version ;
    out >> version;
	out >> versionNum;
    setProVersion(versionNum);
    sOpenFileVersion = version;                     //���ļ��İ汾��

    qDebug() << "project Version "<<versionNum;
	setProVersion(versionNum);
    QString versionStr = tr("AKWorkShop");//���ܱ��ı�
    versionStr += "-V1.0.2";
    if(version != versionStr  //�汾��һ��
		|| versionNum > AK_CURRENT_VERSION)    //��ǰ��̬���ɽϸ߰汾��������� 
    {
        QString warning = tr("����") + SUFFIX + tr("֧�ֵ��ļ���ʽ�����߹����ļ�����");;
        if(version == versionStr)
            warning == tr("��̬���ɽ��°汾������ɣ���������̬��������°汾");
        QMessageBox box(QMessageBox::Information,tr("����"),warning,QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
        box.exec();
        file.close();
        //AAAAAA
        link->takeChildren();
        if(tree_hisdatalog->childCount() > 0)
        {
            tree_hisdatalog->takeChildren();
        }
        if(recipe->childCount() > 0)
        {
            recipe->takeChildren();
        }
        if(alarmlog->childCount() > 0)
        {
            alarmlog->takeChildren();
        }
        return ;
    }

    /*read project model */
    QString sModel;
    out >> sModel;
    out >> m_pSamSysParame;
    //���ͺŶ�ȡcom�ڵĲ���
    {
        qDebug()<< "aaaaaaaaaaaaaaa  " << pwnd->newpro->newprowizard_model;
        qDebug()<< "aaaaaaaaaaaaaaa  " << pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelName;
        QFile file("modle.dat");//���ļ������ļ��洢����HMI�ͺŵ������Ϣ
        QString dataindex="#"+pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelName;

        QString line;//��ʱ�������洢���ļ�ȡ����һ������
        QTextStream stream(&file);//��������ļ��ı���

        if (file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            while(!stream.atEnd())
            {
                line=stream.readLine();//�ļ���һ�д洢�����ͺŵĸ���
                if(line==dataindex)
                {
                    break;
                 }
            }
        }

        line=stream.readLine();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelSize = line;
        line=stream.readLine();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strResolution = line;
        line=stream.readLine();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strColor = line;
        line=stream.readLine();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strUsermemory = line;
        line=stream.readLine();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strNandFlash = line;
        line=stream.readLine();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strPowersupply = line;
        line=stream.readLine();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom1 = line;
        line=stream.readLine();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom2 = line;
        line=stream.readLine();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strUsb = line;
        line=stream.readLine();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strMaxscreennumber = line;
        file.close();
    }

    QVector<int> vDel;
    for(int i = 0; i < pwnd->m_pSamSysParame->m_qvcConnect.size(); i++)
    {
        vDel.clear();
        for(int j = 0; j < pwnd->m_pSamSysParame->m_qvcConnect[i].vProtocols.size(); j++)
        {
            stProtocol model = pwnd->m_pSamSysParame->m_qvcConnect[i].vProtocols.at(j);
            QString sFactoryName = model.sFactoryName;
            QString sProtocolName = model.sProtocolName;
            QString strConnectName = pwnd->m_pSamSysParame->m_qvcConnect[i].sConnectName;
            foreach(PLC_FACTORY pl,vPlc)
            {
                if(sFactoryName == pl.sFactoryName)//����������ͬ
                {
                    foreach(PLC_MODEL pLcmodel,pl.models)
                    {
                        if(sProtocolName == pLcmodel.sModelName)
                        {
                            m_pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.regs = pLcmodel.regs;
                            m_pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.sBitregs = pLcmodel.sBitregs;
                            m_pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.sWorldregs = pLcmodel.sWorldregs;
                            m_pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.sDworldregs = pLcmodel.sDworldregs;
                            m_pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.ePorttype = pLcmodel.ePorttype;
                            if(strConnectName == tr("Com1") || strConnectName == tr("Com2") || strConnectName == tr("Com3"))
                            {
                                if(pLcmodel.ePorttype == PORT_ETHNET)
                                {
                                    vDel.push_front(j);;
                                }
                            }
                            else if(strConnectName == tr("��̫��") || strConnectName == tr("����"))
                            {
                                if(pLcmodel.ePorttype == PORT_SERIAL)
                                {
                                    vDel.push_front(j);;
                                }
                            }
                        }
                    }
                }
            }

        }
        for(int k = 0; k < vDel.size(); k++)
        {
            pwnd->m_pSamSysParame->m_qvcConnect[i].vProtocols.remove(vDel.at(k));
        }
    }

    qDebug() << "load m_pSamSysParame end" ;
    /*read all scene and windown scene properties*/
    int totalSceneNum = 0;
    out >> totalSceneNum;
    pSceneSheet.clear();
    SamDrawScene *pScene = NULL;
    if(totalSceneNum <= 0)
    {
        QMessageBox::warning(this,tr("�򿪹��̳���"),tr("���鹤�̰汾�Ƿ������"));
        file.close();
        //AAAAAA
        link->takeChildren();
        if(tree_hisdatalog->childCount() > 0)
        {
            tree_hisdatalog->takeChildren();
        }
        if(recipe->childCount() > 0)
        {
            recipe->takeChildren();
        }
        if(alarmlog->childCount() > 0)
        {
            alarmlog->takeChildren();
        }
        return ;
    }
    if(totalSceneNum > MAX_SCRNCNT)
    {
        QMessageBox::warning(this,tr("�򿪹��̳���"),tr("���鹤�̰汾�Ƿ������"));
        file.close();
        //AAAAAA
        link->takeChildren();
        if(tree_hisdatalog->childCount() > 0)
        {
            tree_hisdatalog->takeChildren();
        }
        if(recipe->childCount() > 0)
        {
            recipe->takeChildren();
        }
        if(alarmlog->childCount() > 0)
        {
            alarmlog->takeChildren();
        }
        return ;
    }

    for(int num = 0; num < totalSceneNum; num++)
    {
        pScene = new SamDrawScene;
        out >> pScene;
        qreal z = 0;
        QList<QGraphicsItem *> items = pScene->TopItems();
        if(items.size()>0)
        {
            z = items.first()->zValue();
        }
        pScene->setTopOrder(z);
        pSceneSheet.push_back(pScene);

        connect(pSceneSheet[num],SIGNAL(DoubleClickItem(QGraphicsItem *)),this,SLOT(SlotItemDBClick(QGraphicsItem *)));
        connect(pSceneSheet[num],SIGNAL(SingleClickItem()),this,SLOT(OnSingleClickItem()));
        connect(pSceneSheet[num],SIGNAL(SingleClickItem()),this,SLOT(AddItemToScene()));
        connect(pSceneSheet[num], SIGNAL(itemsMoved(SamDrawScene*,QList<QGraphicsItem*>,QList<QPointF>)),
                this, SLOT(itemsMoved(SamDrawScene *,QList <QGraphicsItem *>,QList <QPointF >)));
        connect(pSceneSheet[num], SIGNAL(itemResize(SamDrawScene*,QGraphicsItem*,QSizeF,QPointF)),
                this, SLOT(itemResize(SamDrawScene *,QGraphicsItem*,QSizeF,QPointF)));
        connect(pSceneSheet[num], SIGNAL(lineItemDrag(SamDrawScene *,QGraphicsItem * ,QPainterPath ,QPainterPath )),
                this, SLOT(lineItemchanged(SamDrawScene *,QGraphicsItem * ,QPainterPath ,QPainterPath )));
        connect(pSceneSheet[num], SIGNAL(polygonDrag(SamDrawScene*,QGraphicsItem*,QPolygonF,QPolygonF)),
                this, SLOT(polygonchanged(SamDrawScene *,QGraphicsItem*,QPolygonF,QPolygonF)));
        connect(pSceneSheet[num], SIGNAL(Messageout(QString, MSG_TYPE, MsgOutPut*)), this, SLOT(MessageOutEx(QString, MSG_TYPE, MsgOutPut*)));
    }
    
    //�ű�
    qDebug() << "loadLibrary start" ;
    this->loadLibrary(out);//��ȡ�ű�
    //out>>mPicPath;
    qDebug()<< "out mPicPath--"<<mPicPath;
    proName = "resource";
    dir = QDir(proName);
    if(!dir.exists())
    {
        dir.mkpath(dir.absolutePath());
    }
    int type = 0;
    out >> type;
    if(type)
    {
        //this->LoadPicFromFile(out);
    }
    totalSceneNum = pSceneSheet.size();

    /*init*/
    if(newpro == NULL)
    {
        newpro = new QNewPro();
    }
    out >> newpro;           //read class QNewPro data

    /*The following storage may not use for Lower code*/
    if(m_pSamSysParame->m_mixGlobalVar.m_bEncryAccess)
    {
        QFilePassWordDlg *dlg = new QFilePassWordDlg(m_pSamSysParame->m_mixGlobalVar.m_strAccessPassword,this);
        if(dlg->exec() != QDialog::Accepted)
        {
            file.close();
            //QMessageBox::about(this, tr("����"), tr("�����������"));
            //AAAAAA
            link->takeChildren();
            if(tree_hisdatalog->childCount() > 0)
            {
                tree_hisdatalog->takeChildren();
            }
            if(recipe->childCount() > 0)
            {
                recipe->takeChildren();
            }
            if(alarmlog->childCount() > 0)
            {
                alarmlog->takeChildren();
            }
            return;
        }
    }

    //QString strT = GetHMIConnectInformation(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelName);
    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom1.contains("com1"))
    {
        link->child(0)->setDisabled(false);
    }
    else
    {
        link->child(0)->setDisabled(true);
    }
    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom1.contains("com2"))
    {
        link->child(1)->setDisabled(false);
    }
    else
    {
        link->child(1)->setDisabled(true);
    }

    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom1.contains("com3"))
    {
        link->child(2)->setDisabled(false);
    }
    else
    {
        link->child(2)->setDisabled(true);
    }

    if(!pwnd->m_pSamSysParame->m_mixGlobalVar.m_strMaxscreennumber.contains("Ethernet(NONE)"))
    {
        link->child(3)->setDisabled(false);
    }
    else
    {
        link->child(3)->setDisabled(true);
    }

    if(!pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom2.contains("NONE"))
    {
        link->child(4)->setDisabled(false);
        if(link->childCount() > 5)
            link->child(5)->setDisabled(false);
    }
    else
    {
        link->child(4)->setDisabled(true);
        if(link->childCount() > 5)
            link->child(5)->setDisabled(false);
    }

    //if(m_pSamSysParame->m_fileProtect.bNeedFileProtect)//�ļ������������� Edit zhy
    //{
    //    QFilePassWordDlg *filepassworddlg=new QFilePassWordDlg(m_pSamSysParame->m_fileProtect.sProtectPWD,this);
    //    if(filepassworddlg->exec()!=QDialog::Accepted)
    //    {
    //        file.close();
    //        return;
    //    }
    //}

    //int digitalSize = this->m_pSamSysParame->m_qvcAlarm.size();
    //int analogSize = this->m_pSamSysParame->m_qvcAlarm.size();
    /*add alarm data is show */
    //QString ss = "" ;
    //alarm_name.clear();
//    for(int i = 0; i < digitalSize + analogSize; i++)
//    {
//        out >> ss;
//        alarm_name.push_back(ss);
//    }
    /*alarmlog  Style*/
    //int nSyle=0;
//    alarm_style.clear();
//    for(int i = 0; i < digitalSize + analogSize; i++)
//    {
//        out >> nSyle;
//        alarm_style.push_back(nSyle);
//    }

    /*edit by latory*/
    QMap<int,int> mSceneIndex;
    out >> mSceneIndex;
#ifdef AKPLC
    QString akpfile = fileName.replace("/","\\");
    akpfile = akpfile.section("\\",-1);
    akpfile.remove(AK_FILE_END);
    loadPlcPrj(akpfile,out);//����PLC����
#endif

    /*edit by panfacheng*/
    if (sOpenFileVersion != "AKWorkShop-V1.0.0")        //����1.0.0�汾�������������
    {
        int nVectorSize;
        out >> nVectorSize;
        if(nVectorSize > 1000)
        {
            nVectorSize = 1000;
        }
        m_pSamSysParame->m_qvcVarRecord.clear();
        m_pSamSysParame->m_qvcVarRecord.resize(nVectorSize);
        for(int i = 0; i < nVectorSize; i++)
        {
            out >> m_pSamSysParame->m_qvcVarRecord[i].ibitWord;
            out >> m_pSamSysParame->m_qvcVarRecord[i].mCtlAddr;
            out >> m_pSamSysParame->m_qvcVarRecord[i].SVarName;
        }
    }

    file.close();

    if(pView == NULL)
    {
        pView =new myGraphicsView();
        //edit zhy 2011.8.3
        //��ѡ�д�ֱģʽ��ʱ�� ��Ⱥ͸߶ȶ��ı�� ����ͨ���жϴ�ֱˮƽģʽ���С
     }

    //pView->setSceneRect(-1,-1,m_pSamSysParame->m_projectProp.nSceneWidth,m_pSamSysParame->m_projectProp.nSceneHeight+100);

    //nActiveSheetIndex = m_pSamSysParame->m_projectProp.nStartScreenIndex;

    if(pSceneSheet.isEmpty()) return ;
    nActiveSheetIndex = 0;
    pView->setSceneRect(0,0,1366,768);
    pView->setScene(pSceneSheet[nActiveSheetIndex]);

    pView->setDragMode(QGraphicsView::RubberBandDrag);//�ѵ�ѡ�ı���϶�ģʽ
    pView->setMouseTracking(true); // ��������ƶ���׽
    pView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    if(m_pLayout==NULL)
    {
        m_pLayout = new QHBoxLayout;
    }
    m_pLayout->addWidget(pView);
    ui->centralWidget->setLayout(m_pLayout);
    QScrollBar *pVbar = pView->verticalScrollBar();
    pVbar->installEventFilter(this);

    setUnifiedTitleAndToolBarOnMac(true);

    undoStack->clear();
    is_Is=false;
    openInit_MenuAndTool();
    isHave=true;
    is_haveScreen=true;
    pwnd->is_Save=true;
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(true);//���򿪹���ʱ�ı䱣�水ť����ɫ
    openPro_reTreeCtl();//�򿪹���ʱˢ�����οؼ�
    fileName.replace("/","\\");
    QStringList pathList = fileName.split("\\");
    QString sname = pathList.back();
    QString spath;
    sname.remove(AK_FILE_END);
    pathList.pop_back();
    int size = pathList.size();
    for(int i = 0; i < size; i++)
    {
        spath += pathList.at(i);
        spath += "\\";
    }
    newpro->newprowizard_path = spath;
    newpro->newprowizard_name = sname;
    //  pwnd->setWindowTitle(QString(VERSION_NAME + "--%1").arg(fileName));
    /*QString strDest;
    QString strtemp = pSceneSheet[nActiveSheetIndex]->sNewScreenName;
    handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);*/
    pwnd->setWindowTitle(QString(VERSION_NAME"--%1--%2").arg(fileName).
                         arg(pSceneSheet[nActiveSheetIndex]->sNewScreenName));

    //XXXXX
    /*if(languagedlg==NULL)
    {
        languagedlg=new  QTreeCtrlLanguageDlg(this);
    }
    languagedlg->initDlg();
    listChange(list_style->currentIndex());
    pwnd->is_Save=true;// ����ı� ͬʱ���ı䱣�水ť����ɫ
    pwnd->ui->action_save->setDisabled(true);*/

    //new add by zqh on 2012-2-7
    qLanguagecmb->clear();
    for(int i=0;i<m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();i++)
    {
        qLanguagecmb->addItem(m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
    }
    qDebug() <<"open:start";
    qLanguagecmb->setEnabled(true);
    qLanguagecmb->setCurrentIndex(0);
    //m_pSamSysParame->m_mixGlobalVar.m_nCurLan = 0;

    updateChScreen();

    int totalNum = pSceneSheet.size();
    QList <QGraphicsItem *> itemLIst;

    //�������пؼ�
    for(int num = 0; num < totalNum; num++)
    {

        itemLIst = pSceneSheet[num]->items();
        foreach(QGraphicsItem *pItem,itemLIst)
        {
            int type = pItem->data(GROUP_TYPE_KEY).toInt();
            switch(type)
            {
            case GROUP_TYPE_STATICPIC:
                if(pItem->sceneBoundingRect().size() == QSizeF(0,0))
                {
                    qDebug() << "error static picture!"<<endl;
                    pSceneSheet[num]->removeItem(pItem);
                }
                break;
            default:
                break;
            }
            if(pItem->parentItem() == 0 && pItem->type() != SAM_DRAW_OBJECT_TRACKER
               && pItem->type() != SAM_DRAW_OBJECT_LOCK)
            {
                SamDrawItemBase *baseitem = dynamic_cast<SamDrawItemBase *>(pItem);
                if(baseitem)
                {
                    //int nId = getNewId();
                   // baseitem->setId(nId);
                    insertId(baseitem->id());
                }
            }
        }
    }
    /*ui->toolBox->setVisible(true);
    ui->dockWidget->setVisible(true);

    ui->dockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
    ui->dockWidget->setFloating(true);
    QRect  rcdock =  geometry();
    ui->dockWidget->setGeometry(rcdock.right()-181,120,161,291);
    ui->dockWidget->setFixedSize(161,291);*/

    m_rightDock->setVisible(false);
    ui->action_41->setChecked(false); //add by wxy�˵�����Ӧ�ĸ���
    m_toolDock->setVisible(true);
    ui->action_tool->setChecked(true);
    setProVersion(AK_CURRENT_VERSION);//�򿪹��̺���ĵ�ǰ�汾��

    qDebug() << m_Ids;
    if(pView)
    {
        QScrollBar *pHorizScrollBar = pView->horizontalScrollBar();
        if(pHorizScrollBar)
        {
            pHorizScrollBar->setValue(1);
        }
        QScrollBar *pVerticalScrollBar = pView->verticalScrollBar();
        if(pVerticalScrollBar)
        {
            pVerticalScrollBar->setValue(1);
        }
    }
    //wxy���¹���ɾ����ԭ�ȵĽű������ı�����������жϴ���
    QFile::remove("sdmacro\\ml\\ml.jar");
//    mPicPath.clear();
//    mPicMd5.clear();
//    deleteDirectory(QFileInfo("resource"));
    qDebug() <<"open:end";
}
/*void MainWindow::createnewscreendlg()
{
}*/
void MainWindow::createopenprodlg()
{
    if(isCompiled)
    {
        return ;
    }
    QString path;
    path.clear();
    createopenprodlg(path);
}


//������̬���ݵ��ļ�
//sFileName��Ҫ������ļ���������·����
//type��1--������̬����ʹ�� 0--����ʹ��
void MainWindow::SaveProjectToFile(QString sFileName,int type)
{
    QFile file;
    file.setFileName(sFileName);
    QString version = tr("AKWorkShop");//���ܱ��ı�
    version += VERSION_NUM;
    QVector<int> VScenePosInFile;
    QMap<int,int> mSceneIndex;
    QVector<Keyboard> vKeyboard;
    QVector<int> vType;

    QFileInfo fileInfo(sFileName);
    QDir filedir = fileInfo.dir();
    if(!filedir.exists())
    {
        filedir.mkdir(filedir.absolutePath());
        qDebug() << "fileInfo.filePath "<< fileInfo.filePath();
    }
    bool bOpenSuccess = file.open(QIODevice::WriteOnly);
    if(!bOpenSuccess)
    {
        qDebug() << "save file error !";
        QMessageBox::warning(this,tr("�����ļ�����"),tr("����·���Ƿ���ȷ���߹淶"));
        file.close();
        return;
    }
    QDataStream in(&file);

    /*save project version*/
    in << version;
	int versionNum = AK_CURRENT_VERSION;
	in << versionNum;

    QString imodel = m_pSamSysParame->m_projectProp.sPjtModel;
    int index;
    for(index=0;index<imodel.length();index++)
    {
        if(imodel.at(index) == '(')
            break;
    }
    imodel = imodel.left(index);

    /*save model*/
    in << imodel;

	in << m_pSamSysParame;
    /*save all scene and windown scene properties*/
    int totalNum = pSceneSheet.size();
    in << totalNum;
    if(totalNum > MAX_SCRNCNT)
    {
        qDebug() << "save file error !";
        QMessageBox::warning(this,tr(""),tr("���湤�̳���"));
        file.close();
        return ;
    }
    index = 0 ;
    int len = 1;
    for(int num = 0; num < totalNum; num++)
    {
        VScenePosInFile << file.size();
        int nSceneType = pSceneSheet[num]->nIsSceneOrWindow;
        if(nSceneType == 0 || nSceneType == 1)
        {
            mSceneIndex.insert(index,num);
            index++;
        }
        in << pSceneSheet[num];
    }
    VScenePosInFile << file.size();
    
    this->saveLibrary(in);//����ű�

    //in << mPicPath;//��ͼƬmap
    qDebug()<< "mSceneIndex--"<<mSceneIndex;

    in << type;

    in << newpro;           //save class QNewPro data

    //int digitalSize = this->m_pSamSysParame->m_qvcAlarm.size();


    /*edit by latory*/
    in << mSceneIndex;
#ifdef AKPLC
    savePlcPrj(in);//����PLC����
#endif
    if(type)
    {
        is_Save=true;
        ui->action_save->setDisabled(true);
        is_SaveAS=false;
        setCurrentFile(file.fileName());//����򿪵��ĵ�
    }
    file.close();
}

void MainWindow::handleWinTitle(QString &strTitle, QString str0)
{
    QString str = pwnd->windowTitle().split(AK_FILE_END).at(0);
    str = str + AK_FILE_END + "--" + str0;
    strTitle = str;
    return;
}
/*************************************************************************
  *�������׼�������ϱ��湤�̶Ի���������ۺ���
***************************************************************************/
void MainWindow::createsavedlg()
{
    /*   QMessageBox box(this);
    box.setText("sagfsdhs");
    box.exec();*/
    checkUserKeyboard();//����Ƿ����õ��û��Զ������
    //CheckScreenandMFaction();//��黭�水ť �๦�ܰ�ťҪ��ת�Ļ����Ƿ���ȷ
    // deleteScreen_upDateIndex();
    if(!newpro)
    {
        return ;
    }
    QString filename;
    if(is_SaveAS)
    {
        if(!saveAs_Name.endsWith(QString(AK_FILE_END)),Qt::CaseInsensitive)
            filename = saveAs_Name+ AK_FILE_END;
        else
            filename = saveAs_Name;
        pwnd->setWindowTitle(QString(VERSION_NAME"--%1").arg(filename.replace("/","\\")));
        //saveAs_Name = "";
    }
    else
    {
        if(newpro->newprowizard_path.right(1) != "\\")
            newpro->newprowizard_path += "\\";
        QString filePath;
        if(saveAs_Name=="")
        {
            filePath= newpro->newprowizard_path + newpro->newprowizard_name;
            filename = filePath + AK_FILE_END;
        }
        else
        {
            if(!saveAs_Name.endsWith(QString(AK_FILE_END)),Qt::CaseInsensitive)
                filename = saveAs_Name+ AK_FILE_END;
            else
                filename = saveAs_Name;
            //filename = saveAs_Name+ AK_FILE_END;
        }

    }

    SaveProjectToFile(filename,1);

}



void MainWindow::createbitbtndlg()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED
        || isCompiled)
    {
        return;
    }

    SwitchDlg *switchdlg=new SwitchDlg(0,this);
    if(switchdlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = switchdlg->item;


        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        qDebug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~"<<pDrawToSceneItem->childItems().size();

        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    switchdlg->deleteLater();
    switchdlg = NULL;
}




void MainWindow::createtimedisplaydlg()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    QTimeDisplayDlg  *timedisplaydlg=new QTimeDisplayDlg(0,this);
    if(timedisplaydlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = timedisplaydlg->pTimeDisplayGen->pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        //OnSingClikSpare(oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    timedisplaydlg->deleteLater();
    timedisplaydlg = NULL;
}




void MainWindow::createdatedisplaydlg()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    QDateDisplayDlg  *datedisplaydlg=new QDateDisplayDlg(0,this);
    if( datedisplaydlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = datedisplaydlg->pDateDisplayGen->pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        //OnSingClikSpare(oldItem);

        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    datedisplaydlg->deleteLater();
    datedisplaydlg = NULL;
 }
void MainWindow::createweekdisplaydlg()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    QWeekDisplayDlg *weekdisplaydlg=new QWeekDisplayDlg(0,this);
    if(weekdisplaydlg->exec()== QDialog::Accepted)
    {
        QGraphicsItem * oldItem = weekdisplaydlg->pGeneralDlg->pOldItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        //OnSingClikSpare(oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    weekdisplaydlg->deleteLater();
    weekdisplaydlg = NULL;
}
void MainWindow::createstaticpicturedlg()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    QStaticPictureDlg *staticpicturedlg=new QStaticPictureDlg(0,this);
    if(staticpicturedlg->exec()== QDialog::Accepted)
    {
        QGraphicsItem * oldItem = staticpicturedlg->pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    staticpicturedlg->deleteLater();
    staticpicturedlg = NULL;
}



void MainWindow::createtrendchartdlg()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    if(pwnd->m_pSamSysParame->m_loadDataSampling.size() == 0)//û�����ݲɼ�
    {
        QMessageBox::information(this, VERSION_NAME, tr("û�н������ݲɼ�"));
        return;
    }

    //QTrendChartDlg *trendchart=new QTrendChartDlg(0,this);
    QTrend *trendchart = new QTrend(0,this);
    if( trendchart->exec() == QDialog::Accepted)
    {
        //QGraphicsItem * oldItem = trendchart->pCopyItem;
        QGraphicsItem * oldItem = trendchart->m_pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    trendchart->deleteLater();
    trendchart = NULL;
}

void MainWindow::createdyncricledlg()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    newDynCircleDlg *dyncricle = new newDynCircleDlg(0,this);
    //QDynCricleDlg *dyncricle=new QDynCricleDlg(0,this);
    if(dyncricle->exec()== QDialog::Accepted)
    {
        QGraphicsItem * oldItem = dyncricle->m_pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    dyncricle->deleteLater();
    dyncricle = NULL;
}
void MainWindow::createdynrentdlg()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    //��̬����
    newDynRectDlg *dynrect = new newDynRectDlg(0, this);
    //QDynRectDlg *dynrect=new QDynRectDlg(0,this);
    if(dynrect->exec()== QDialog::Accepted)
    {
        QGraphicsItem * oldItem = dynrect->m_pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    dynrect->deleteLater();
    dynrect = NULL;
}

void MainWindow::createalarmcontroldlg()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    AlarmListDlg *alarmcontrol=new AlarmListDlg(0,1,this);
    if(alarmcontrol->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = alarmcontrol->item;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);

        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    alarmcontrol->deleteLater();
    alarmcontrol = NULL;
}
/*****************************************************
  ������¼��ʾ��
 ****************************************************/
/*void MainWindow::createoperadlg()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED)
    {
        return;
    }

    qoperatecontroldlg *operatecontrol=new qoperatecontroldlg(0,this);
    if(operatecontrol->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = operatecontrol->pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);

        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    operatecontrol->deleteLater();
    operatecontrol = NULL;
}*/

void MainWindow::createdynalarmbar()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    AlarmbarDlg *dynalarmbar=new AlarmbarDlg(0,this);
    if( dynalarmbar->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = dynalarmbar->pDynAlarmBarGen->pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        //OnSingClikSpare(oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    dynalarmbar->deleteLater();
    dynalarmbar = NULL;
}

void MainWindow::createhisalarm()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    AlarmListDlg *hisalarm=new AlarmListDlg(0,2,this);
    if(hisalarm->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = hisalarm->item;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);

        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    hisalarm->deleteLater();
    hisalarm = NULL;
}



void MainWindow::createchart()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    QChartDlg *chart=new QChartDlg(0,this);
    if( chart->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = chart->pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        //OnSingClikSpare(oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    chart->deleteLater();
    chart = NULL;
}

void MainWindow::createXYtrend()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    XYTrendDlg *chart=new XYTrendDlg(0,this);
    if( chart->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = chart->m_pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        //OnSingClikSpare(oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    chart->deleteLater();
    chart = NULL;
}

void MainWindow::createvalue()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    QValueDlg *pValue=new QValueDlg(0,this);
    if( pValue->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pValue->pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        //OnSingClikSpare(oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    pValue->deleteLater();
    pValue = NULL;
}

void MainWindow::createimage()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    QImageShowDlg *pImage=new QImageShowDlg(0,this);
    if( pImage->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pImage->pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        //OnSingClikSpare(oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    pImage->deleteLater();
    pImage = NULL;
}
void MainWindow::createhisrecord()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    if(pwnd->m_pSamSysParame->m_loadDataSampling.size() == 0)//û�����ݲɼ�
    {
        QMessageBox::information(this, VERSION_NAME, tr("û�н������ݲɼ�"));
        return;
    }

    //����
    int temp = m_pSamSysParame->m_loadDataSampling.size();
    int hisSampNum = 0;
    for(int i = 0; i < temp; i++)
    {
        if(2 == m_pSamSysParame->m_loadDataSampling[i].nDataSampType)//����Ϊ��ʷ���ݲɼ�
        {
            if(m_pSamSysParame->m_loadDataSampling[i].m_dataTable.size() != 0)
            {
                hisSampNum++;
            }
        }
    }
    if(0 == hisSampNum)
    {
        QMessageBox::about(this, tr("��ʷ������ʾ��"), tr("û����ʷ���ݲɼ�������ʷ���ݲɼ�Ϊ��"));
        return;
    }

    //QHisRecordDisplayDlg *hisrecorddisplay=new QHisRecordDisplayDlg(0,this);
    QHistoryDataShow* hisrecorddisplay = new QHistoryDataShow(0,this);
    if(hisrecorddisplay->exec() == QDialog::Accepted)
    {
        QGraphicsItem *oldItem = hisrecorddisplay->m_pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }
}

void MainWindow::createmsgdisplay()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    //QMsgDisplayDlg *msgdisplay=new QMsgDisplayDlg(0,this);
    qMessageShow *msgdisplay = new qMessageShow(0,this);
    if(msgdisplay->exec()== QDialog::Accepted)
    {
        QGraphicsItem *oldItem = msgdisplay->m_pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    msgdisplay->deleteLater();
    msgdisplay = NULL;
}


void MainWindow::CreateKeyboardASCII()//�������
{
    //��ʱ�����û��Զ������
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

        qkeybutton *keydlg=new qkeybutton(0 ,this);
    if(keydlg->exec()== QDialog::Accepted)
    {
        QGraphicsItem * oldItem =keydlg->pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        //OnSingClikSpare(oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    keydlg->deleteLater();
    keydlg = NULL;
}
void MainWindow::createflowblock()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    qFlowBlock *flowblock=new qFlowBlock(0,this);
    if( flowblock->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = flowblock->pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        //OnSingClikSpare(oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    flowblock->deleteLater();
    flowblock = NULL;

}


void MainWindow::OnCreateTable()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    Table *pTable = new Table(0,this);

    if( pTable->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pTable->pGeneralDlg->pOldItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        //OnSingClikSpare(oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    pTable->deleteLater();
    pTable = NULL;
}

void MainWindow::OnCreateMessageBoard()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    qMessageBoard *pMessageBoard = new qMessageBoard(0, this);

    if(pMessageBoard->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pMessageBoard->m_pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    pMessageBoard->deleteLater();
    pMessageBoard = NULL;
}

void MainWindow::OnCreateComboBox()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }
    AkComboBox *pAkComboBox = new AkComboBox(0, this);
    if(pAkComboBox->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pAkComboBox->m_pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }
    pAkComboBox->deleteLater();
    pAkComboBox = NULL;
}

void MainWindow::OnCreateScales()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    qScale *pScales = new qScale(0,this);

    if( pScales->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pScales->pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        //OnSingClikSpare(oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    pScales->deleteLater();
    pScales = NULL;
}



void MainWindow::OnCreateComboBoxDlg()
{
    if(SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    //ComboBox *pComboBoxDlg = new ComboBox(0,this);
    qDropDownBox *pComboBoxDlg = new qDropDownBox(0,this);
    if(pComboBoxDlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pComboBoxDlg->m_pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    pComboBoxDlg->deleteLater();
    pComboBoxDlg = NULL;
}

void MainWindow::OnCreateSliderDlg()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED|| isCompiled)
    {
        return;
    }

    Slider *pSliderDlg = new Slider(0,this);

    if( pSliderDlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pSliderDlg->pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    pSliderDlg->deleteLater();
    pSliderDlg = NULL;
}

//void MainWindow::on_action_triggered()
//{
//    QTranslator * translator = new QTranslator();
//    translator->load("Language_Chn.qm");
//    QApplication::instance()->installTranslator(translator);

//}

//�Ի�ͼ�������Ŀؼ����� edit by zqh

void MainWindow::OnDrawRect() //���ƾ���
{
    if(isCompiled)
    {
        return;
    }
    if (SamDrawTool::s_eToolStat == SAM_DRAW_TOOL_UNLOCKED)
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_RECT;
    }
	QApplication::setActiveWindow(pView);
}

void MainWindow::OnDrawLine() //����ֱ��
{
    if(isCompiled)
    {
        return;
    }
    if (SamDrawTool::s_eToolStat == SAM_DRAW_TOOL_UNLOCKED)
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_LINE;
    }
	QApplication::setActiveWindow(pView);
}

void MainWindow::OnDrawEllipse() //����Բ
{
    if(isCompiled)
    {
        return;
    }
    if (SamDrawTool::s_eToolStat == SAM_DRAW_TOOL_UNLOCKED)
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_ELLIPSE;
    }
	QApplication::setActiveWindow(pView);
}

void MainWindow::OnDrawPolygon() //���ƶ����
{
    if(isCompiled)
    {
        return;
    }
    if (SamDrawTool::s_eToolStat == SAM_DRAW_TOOL_UNLOCKED)
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_POLYGON;
    }
	QApplication::setActiveWindow(pView);
}

void MainWindow::OnDrawFoldLine()//��������
{
    if(isCompiled)
    {
        return;
    }
    if (SamDrawTool::s_eToolStat == SAM_DRAW_TOOL_UNLOCKED)
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_FOLDLINE;
    }
	QApplication::setActiveWindow(pView);
}

void MainWindow::OnDrawFreeLine()//��������ֱ��
{
    if(isCompiled)
    {
        return;
    }
    if (SamDrawTool::s_eToolStat == SAM_DRAW_TOOL_UNLOCKED)
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_FREELINE;
    }
	QApplication::setActiveWindow(pView);
}

void MainWindow::onDrawBlightCircle()
{
    if(isCompiled)
    {
        return;
    }
    if (SamDrawTool::s_eToolStat == SAM_DRAW_TOOL_UNLOCKED)
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_LINE_CIRCLE;
    }
	QApplication::setActiveWindow(pView);
}

void MainWindow::onDrawText()
{
    if(isCompiled)
    {
        return;
    }
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED)
    {
        return;
    }

    StaticTexts *pText = new StaticTexts(0,this);
    if( pText->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pText->pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    pText->deleteLater();
    pText = NULL;
	QApplication::setActiveWindow(pView);
}

//�Ա�׼�������Ŀؼ����� edit by zqh
void MainWindow::OnGroupItem()  //��ϲ���
{
    if(pwnd->isCompiled)
    {
        return;
    }
    //pSceneSheet[nActiveSheetIndex]->GroupItem(); //�Ѿ��Ƶ�commands.cpp�У�redo()��
    if(pSceneSheet[nActiveSheetIndex]->selectedItems().size() > 1)
       undoStack->push(new groupCommand(pSceneSheet[nActiveSheetIndex]));
     ui->action_copym->setDisabled(false);
}

void MainWindow::OnDisGroupItem() //��ֲ���
{
    if(pwnd->isCompiled)
    {
        return;
    }
    QList<QGraphicsItem *> selList =pSceneSheet[nActiveSheetIndex]->selectedItems();
    if(selList.size() != 1)
    {
        return ;
    }
    if(selList.first()->data(GROUP_TYPE_KEY).toInt() != USER_DEFINE_GROUP)
        return;
    undoStack->push(new disgroupCommand(pSceneSheet[nActiveSheetIndex]));
    ui->action_copym->setDisabled(true);
}

void MainWindow::OnDeleteItem()  //ɾ������
{
    if(isCompiled)
    {
        return;
    }
    if (pSceneSheet[nActiveSheetIndex]->selectedItems().isEmpty())
        return;

    QUndoCommand *deleteCommand = new DeleteCommand(pSceneSheet[nActiveSheetIndex]);
    undoStack->push(deleteCommand);

}

void MainWindow::OnLockItem()    //��������
{
    foreach (QGraphicsItem *item, pSceneSheet[nActiveSheetIndex]->selectedItems())
        item->setFlag(QGraphicsItem::ItemIsMovable, false);
    pSceneSheet[nActiveSheetIndex]->reBondingTrackers();
}

void MainWindow::OnUnLockItem()  //��������
{
    foreach (QGraphicsItem *item, pSceneSheet[nActiveSheetIndex]->selectedItems())
        item->setFlag(QGraphicsItem::ItemIsMovable, true);
    pSceneSheet[nActiveSheetIndex]->reBondingTrackers();
}

void MainWindow::OnSetLeft() //����ͼ�������
{
	pSceneSheet[nActiveSheetIndex]->OnSetLeftAlign();
}

void MainWindow::OnSetRight() //�Ҷ���
{
        pSceneSheet[nActiveSheetIndex]->OnSetRightAlign();

	// QMovie   *movie;
	/*  lab_close_clicked   =   new   QLabel( "hello ");
	lab_close_clicked-> setGeometry(   QRect(10,0,300,300));

	QFile *file = new QFile("D:\\qq.gif"); //:/Gif/Skater.gif
	file->open(QIODevice::ReadOnly);


	movie=   new   QMovie( file);
	lab_close_clicked-> setMovie(movie);
	movie-> start();

	QGraphicsProxyWidget *pWidget = pSceneSheet[nActiveSheetIndex]->addWidget(lab_close_clicked);
	pSceneSheet[nActiveSheetIndex]->addItem(pWidget);
	pWidget->setPos(100,100);
	*/

	//  pWidget->setFlag(QGraphicsItem::ItemIsMovable, true); //�������ͼ�ο����ƶ�
	//  pWidget->setFlag(QGraphicsItem::ItemIsSelectable, true); //�������ͼ�ο�ѡ

	// movie->setPaused(false);
}

void MainWindow::OnSetTop() //�϶���
{
	pSceneSheet[nActiveSheetIndex]->OnSetTopAlign();
}

void MainWindow::OnSetButtom() //�¶���
{
	pSceneSheet[nActiveSheetIndex]->OnSetButtomAlign();
}

void MainWindow::OnSetHCenter() //ˮƽ���ж���
{
        pSceneSheet[nActiveSheetIndex]->OnSetVCenterAlign();
}

void MainWindow::OnSetVCenter() //��ֱ���ж���
{
        pSceneSheet[nActiveSheetIndex]->OnSetHCenterAlign();
}

void MainWindow::OnSetHSpacingAlign() //ˮƽ�ȼ�����
{
	pSceneSheet[nActiveSheetIndex]->OnSetHSpacingAlign();
}

void MainWindow::OnSetVSpacingAlign()
{
	pSceneSheet[nActiveSheetIndex]->OnSetVSpacingAlign();
}


void MainWindow::DrawScreenSize()
{
    QString sShowModel = pwnd->newpro->newprowizard_showmodel;  //SA��ʾģʽ����ˮƽ���Ǵ�ֱ��ʾ
    QFile file("modle.dat");//���ļ������ļ��洢����HMI�ͺŵ������Ϣ
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString line;//��ʱ�������洢���ļ�ȡ����һ������
        QString sModel;//�ļ�����
        QTextStream stream(&file);//��������ļ��ı���
        line=stream.readLine();//�ļ���һ�д洢�����ͺŵĸ���
        int hmimodelcount=line.toInt();//�ѵõ���QString���͵�����ת��Ϊ���͸��д洢���������ͺŵĸ���
        for(int temp=0;temp<hmimodelcount;temp++)
        {
            sModel=stream.readLine();
            line=sModel.split("(").at(0);
            if(line==pwnd->newpro->newprowizard_model)//�õ���ǰѡ����ͺ�λ�� �Ա���ȡ�ֱ���
            {
                break;
            }
        }
        QString sWidth ; //SA�Ŀ��
        QString sHeight; //SA�߶�
        int nIndex = 0;      //������(��(��)���ַ������±�λ��
        int nStarIndex = 0;  //*�Ǻ����ַ������±�λ��
        int nSpaceIndex = 0; //*�Ǻź�ո����ַ������±�λ��
        int nWidth = 0 ;    //SA�Ŀ��
        int nHeight = 0;    //SA�߶�
        int nShowModel = 0; //SA��ʾģʽ
        nIndex = sModel.indexOf("(");             //������(��(��)���ַ������±�λ��
        nStarIndex = sModel.indexOf("*");         //*�Ǻ����ַ������±�λ��
        nSpaceIndex = sModel.indexOf(" ",nStarIndex); //*�Ǻź�ո����ַ������±�λ��
        sWidth = sModel.mid(nIndex+1,nStarIndex - (nIndex+1));
        nWidth = sWidth.toInt();   //�ѿ���ַ���ת��Ϊint
        sHeight = sModel.mid(nStarIndex+1,nSpaceIndex - (nStarIndex+1));
        nHeight = sHeight.toInt(); //�Ѹ߶��ַ���ת��Ϊint
        if(sShowModel == tr("ˮƽ"))
        {
            nShowModel = 0;
        }
        else if(sShowModel == tr("��ֱ"))
        {
            nShowModel = 1;
        }
        OnNewGraphicsScene(nShowModel,nWidth,nHeight); //����������еĻ����溯��
        file.close();
    }
}
void MainWindow::DrawWindowSize()
{
    QString sShowModel = pwnd->newpro->newprowizard_showmodel;  //SA��ʾģʽ����ˮƽ���Ǵ�ֱ��ʾ
    int nWidth = newWindowDlg->ui->spinBox_w ->value();    //SA�Ŀ��
    int nHeight = newWindowDlg->ui->spinBox_h->value();    //SA�߶�
    int nShowModel = 0; //SA��ʾģʽ
    if(sShowModel == tr("ˮƽ"))
    {
        nShowModel = 0;
    }
    else if(sShowModel == tr("��ֱ"))
    {
        nShowModel = 1;
    }
    OnNewGraphicsScene(nShowModel,nWidth,nHeight); //����������еĻ����溯��
}
/************************************************************************
  �������ƣ�OnDrawScreenSize(int nShowModel, int nWidth, int nHeight)
  �������ܣ����ݲ�ͬ���ͺŽ�����ͬ�Ļ���
  �������壺
  nShowModel����ʾģʽ��0��ʾˮƽ��ʾ��1��ʾ��ֱ��ʾ
  nWidth    ������Ŀ��
  nHeight   ������ĸ߶�
  edit by zqh
************************************************************************/
//void MainWindow::OnDrawScreenSize(int nShowModel, int nWidth, int nHeight)
void MainWindow::OnNewGraphicsScene(int nShowModel, int nWidth, int nHeight)
{
    SamDrawScene *pScene = NULL;

    pScene=new  SamDrawScene;
    pSceneSheet.push_back(pScene);

    if(!pScene) return ;
    if(!m_pLayout)
    {
        m_pLayout = new QHBoxLayout;
    }
    if(!pView)
    {
        pView =new myGraphicsView();
    }
    pView->setSceneRect(0,0,1366,768);
    pView->setScene(pScene);
    if(nShowModel == 0) //ˮƽ��ʾ
    {
        pScene->setSceneRect(0,0,nWidth,nHeight);
        //pView->setSceneRect(0,0,nWidth,nHeight+100);//+100��Ҫɾ��edit by zqh
    }
    else if(nShowModel == 1) //��ֱ��ʾ
    {
        pScene->setSceneRect(0,0,nHeight,nWidth);
        //pView->setSceneRect(0,0,nHeight,nWidth+100);
    }
    //    int nSelectType = pScene->nSelectType ; //0��ʾĬ��ѡ��1��ʾѡ��ͼƬ��Ϊ����
    //    pScene->nSelectType = nSelectType;
    //    if(nSelectType == 0)
    //    {
    //        pScene->nPattern =pScene->nPattern; //��ʽѡ��
    //        pScene->m_sceneBackColor = pScene->m_sceneBackColor; //����ɫ
    //        pScene->m_sceneStyleColor = pScene->m_sceneStyleColor; //ǰ��ɫ
    //    }
    //    else if(nSelectType == 1)
    //    {
    //        pScene->m_picturePath = newpro->newscreenwizard_picturepath;  //ͼƬ·��
    //    }
    pView->setDragMode(QGraphicsView::RubberBandDrag);//�ѵ�ѡ�ı���϶�ģʽRubberBandDrag
    //pView->setRenderHint(QPainter::Antialiasing, true); // ����ͼ�η�����ScrollHandDrag
    pView->setMouseTracking(true); // ��������ƶ���׽

    pView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    //m_widgetToolbar->show();
    m_pLayout->addWidget(pView);
    //m_pLayout->addWidget(m_widgetToolbar);

    ui->centralWidget->setLayout(m_pLayout);
    QScrollBar *pVbar = pView->verticalScrollBar();
    pVbar->installEventFilter(this);

    connect(pScene,SIGNAL(DoubleClickItem(QGraphicsItem *)),this,SLOT(SlotItemDBClick(QGraphicsItem *)));
    connect(pScene,SIGNAL(SingleClickItem()),this,SLOT(OnSingleClickItem()));
    connect(pScene,SIGNAL(SingleClickItem()),this,SLOT(AddItemToScene()));
    connect(pScene, SIGNAL(itemResize(SamDrawScene*,QGraphicsItem*,QSizeF,QPointF)),
            this, SLOT(itemResize(SamDrawScene *,QGraphicsItem*,QSizeF,QPointF)));
    connect(pScene, SIGNAL(Messageout(QString, MSG_TYPE, MsgOutPut*)), this, SLOT(MessageOutEx(QString, MSG_TYPE, MsgOutPut*)));
    setUnifiedTitleAndToolBarOnMac(true);

    connect(pScene, SIGNAL(itemsMoved(SamDrawScene*,QList<QGraphicsItem*>,QList<QPointF>)),
            this, SLOT(itemsMoved(SamDrawScene *,QList <QGraphicsItem *>,QList <QPointF >)));

    isCheck_ScreenProperty=false;
    OnSetMainSceneGrid(); //�Ƿ���ʾ����
}

//�ı��ι�ϵ
void MainWindow::on_action_bringforward_triggered()
{
   // pSceneSheet[nActiveSheetIndex]->OnOderUp();
    undoStack->push(new zValueUpChangeCommand(pSceneSheet[nActiveSheetIndex]));
}

void MainWindow::on_action_bringback_triggered()
{
   // pSceneSheet[nActiveSheetIndex]->OnOderDown();
    undoStack->push(new zValueDownChangeCommand(pSceneSheet[nActiveSheetIndex]));
}

void MainWindow::on_action_bringtop_triggered()
{
    //pSceneSheet[nActiveSheetIndex]->OnOderTop();
     undoStack->push(new bringtopCommand(pSceneSheet[nActiveSheetIndex]));
}

void MainWindow::on_action_sengtoback_triggered()
{
    //pSceneSheet[nActiveSheetIndex]->OnOderBotton();
    undoStack->push(new bringBottomCommand(pSceneSheet[nActiveSheetIndex]));
}

//�����޸Ŀ������ԵĶԻ���
void MainWindow::modifyBitBtndlg(QGraphicsItem *item)
{
    SwitchDlg *switchDlg=new SwitchDlg(item,this);
    if(switchDlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = switchDlg->item;
        OnDoubleClik(item,oldItem);
    }

    switchDlg->deleteLater();
    switchDlg = NULL;
}//



void MainWindow::modifyDynCircledlg(QGraphicsItem *item)
{
    newDynCircleDlg *dyncricle = new newDynCircleDlg((DynCircleAttr*)item,this);
    //QDynCricleDlg *dyncricle=new QDynCricleDlg(item,this);

    if(dyncricle->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = dyncricle->m_pCopyItem;
        OnDoubleClik(item,oldItem);
    }

    dyncricle->deleteLater();
    dyncricle = NULL;
}

void MainWindow::modifyDynRectdlg(QGraphicsItem *item)
{
    newDynRectDlg *dynrect = new newDynRectDlg((DynRectAttr *)item, this);
    //QDynRectDlg *dynrect=new QDynRectDlg(item,this);

    if(dynrect->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = dynrect->m_pCopyItem;
        OnDoubleClik(item,oldItem);
    }

    dynrect->deleteLater();
    dynrect = NULL;
}//

/*void MainWindow::modifyMfunctiondlg(QGraphicsItem *item)
{
    QMFunctionBtnDlg *mfunctionbtn=new QMFunctionBtnDlg(item,this);
    if(mfunctionbtn->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = mfunctionbtn->ptab1->pOldItem;
        OnDoubleClik(item,oldItem);
    }
    mfunctionbtn->deleteLater();
    mfunctionbtn = NULL;
}/*/

void MainWindow::modifyWeekdlg(QGraphicsItem *item)
{
    QWeekDisplayDlg *weekdisplaydlg=new QWeekDisplayDlg(item,this);

    if(weekdisplaydlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = weekdisplaydlg->pGeneralDlg->pOldItem;
        OnDoubleClik(item,oldItem);
    }
    weekdisplaydlg->deleteLater();
    weekdisplaydlg = NULL;
}//

/*void MainWindow::modifyWordBtndlg(QGraphicsItem *item)
{
    QWordBtnDlg *wordbtndlg=new  QWordBtnDlg(item,this);
    if(wordbtndlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = wordbtndlg->pGeneral->pOldItem;
        OnDoubleClik(item,oldItem);
    }
    wordbtndlg->deleteLater();
    wordbtndlg = NULL;
}/*/

void MainWindow::modifyBitLampdlg(QGraphicsItem *item)
{

}//

void MainWindow::OnModifyMsgDisplayDlg(QGraphicsItem *item)
{
    //QMsgDisplayDlg *msgdisplay=new QMsgDisplayDlg(item,this);
    qMessageShow *msgdisplay = new qMessageShow((QMessageShowAttr *)item,this);
    if(msgdisplay->exec() == QDialog::Accepted)
    {
        QGraphicsItem *oldItem = msgdisplay->m_pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    msgdisplay->deleteLater();
    msgdisplay = NULL;
}

void MainWindow::OnModifyTableDlg(QGraphicsItem *item)
{
    Table *table=new Table(item,this);
    if(table->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = table->pGeneralDlg->pOldItem;
        OnDoubleClik(item,oldItem);
    }
    table->deleteLater();
    table = NULL;
}

void MainWindow::OnModifyScaleDlg(QGraphicsItem *item)
{
    qScale *pScales = new qScale(item,this);
    if(pScales->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pScales->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    pScales->deleteLater();
    pScales = NULL;
}

/*void MainWindow::modifyMultiLampdlg(QGraphicsItem *item)
{
    QMultiStateLampDlg *multistatelampdlg=new QMultiStateLampDlg(item,this);
    if(multistatelampdlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = multistatelampdlg->pGeneralDlg->pOldItem;
        OnDoubleClik(item,oldItem);
    }
    multistatelampdlg->deleteLater();
    multistatelampdlg = NULL;

}*/

/*void MainWindow::modifyPictureDisplaydlg(QGraphicsItem *item)
{
    QPictureDisplayDlg *picturedisplaydlg=new QPictureDisplayDlg(item,this);
    if(picturedisplaydlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = picturedisplaydlg->pGeneralDlg->pOldItem;
        OnDoubleClik(item,oldItem);
    }
    picturedisplaydlg->deleteLater();
    picturedisplaydlg = NULL;

}/*/

/*void MainWindow::OnModfyStepingDlg(QGraphicsItem *item)
{
    QStepingDlg *Steppingdlg=new QStepingDlg (item,this);
    if(Steppingdlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = Steppingdlg->pGeneralDlg->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    Steppingdlg->deleteLater();
    Steppingdlg = NULL;
}*/

/*void MainWindow::OnModfySingleSelectDlg(QGraphicsItem *item)
{
    QSingSelectDlg *SingleSelectDlg=new QSingSelectDlg (item,this);
    if(SingleSelectDlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = SingleSelectDlg->pGeneralDlg->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    SingleSelectDlg->deleteLater();
    SingleSelectDlg = NULL;
}*/

void MainWindow::OnModfyComboBoxDlg(QGraphicsItem *item)
{
    //ComboBox *ComboBoxDlg=new ComboBox (item,this);
    qDropDownBox *ComboBoxDlg = new qDropDownBox((QDropdownAttr *)item, this);
    if(ComboBoxDlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = ComboBoxDlg->m_pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    ComboBoxDlg->deleteLater();
    ComboBoxDlg = NULL;
}

void MainWindow::OnModfySliderDlg(QGraphicsItem *item)
{
    Slider * slider=new Slider(item,this);
    if(slider->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = slider->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    slider->deleteLater();
    slider = NULL;
}

void MainWindow::OnModfyHisDataShowDlg(QGraphicsItem *item)
{
    //czq
    /*if(pwnd->m_pSamSysParame->m_loadDataSampling.size() == 0)//û�����ݲɼ�
    {
        return;
    }

    //����
    int temp = m_pSamSysParame->m_loadDataSampling.size();
    int hisSampNum = 0;
    for(int i = 0; i < temp; i++)
    {
        if(2 == m_pSamSysParame->m_loadDataSampling[i].nDataSampType)//����Ϊ��ʷ����
        {
            if(m_pSamSysParame->m_loadDataSampling[i].m_dataTable.size() != 0)
            {
                hisSampNum++;
            }
        }
    }
    if(0 == hisSampNum)
    {
        QMessageBox::about(this, tr("��ʷ������ʾ��"), tr("û����ʷ���ݲɼ�������ʷ���ݲɼ�Ϊ��"));
        return;
    }*/

    //QHisRecordDisplayDlg *HisShow=new QHisRecordDisplayDlg (item,this);
    QHistoryDataShow *HisShow=new QHistoryDataShow((QHistoryDataShowAttr*)item,this);
    if(HisShow->exec() == QDialog::Accepted)
    {
        QGraphicsItem *oldItem = HisShow->m_pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    HisShow->deleteLater();
    HisShow = NULL;
}

/*void MainWindow::modifyMultiStatedlg(QGraphicsItem *item)
{
    QMultiStateBtnDlg  *multistatebtndlg=new QMultiStateBtnDlg (item,this);
    if(multistatebtndlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = multistatebtndlg->pGeneralDlg->pOldItem;
        OnDoubleClik(item,oldItem);
    }
    multistatebtndlg->deleteLater();
    multistatebtndlg = NULL;
}/*/

/*void MainWindow::modifyGraphicsMovedlg(QGraphicsItem *item)
{
    QGraphicsMoveDlg *graphicsmove=new QGraphicsMoveDlg(item,this);
    if(graphicsmove->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = graphicsmove->pGeneralDlg->pOldItem;
        OnDoubleClik(item,oldItem);
    }
    graphicsmove->deleteLater();
    graphicsmove = NULL;
}/*/

/*void MainWindow::modifyNumDispaydlg(QGraphicsItem *item)
{
    QNumDisplayDlg  *numdisplaydlg=new QNumDisplayDlg (item,this);
    if( numdisplaydlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = numdisplaydlg->pNumDisplayGen->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    numdisplaydlg->deleteLater();
    numdisplaydlg = NULL;
}/*/

/*void MainWindow::modifyNumEntrydlg(QGraphicsItem *item)//��ֵ����
{
    QNumEntryDlg  *numentrydlg=new QNumEntryDlg(item,this);
    if( numentrydlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = numentrydlg->pNumEentryGen->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    numentrydlg->deleteLater();
    numentrydlg = NULL;
}/*/


/*void MainWindow::modifyBarGraphdlg(QGraphicsItem *item)//��״ͼ
{
    QBarGraghDlg *bargraph=new QBarGraghDlg(item,this);
    if(bargraph->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = bargraph->pBarGraphGen->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    bargraph->deleteLater();
    bargraph = NULL;
}*/

/*void MainWindow::modifyASCIIDisplaydlg(QGraphicsItem *item)//ASCII��ʾ
{
    QAscIIDisplayDlg *pAsciidisplay=new QAscIIDisplayDlg(item,this);
    if(pAsciidisplay->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pAsciidisplay->pASCIIDisplayGenDlg->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    pAsciidisplay->deleteLater();
    pAsciidisplay = NULL;
}*/

/*void MainWindow::modifyASCIIDEntrydlg(QGraphicsItem *item)//ASCII��������ʾ
{
    QAscIIInputDlg *pAsciiInput=new QAscIIInputDlg(item,this);
    if(pAsciiInput->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pAsciiInput->pASCIIInputGen->pCopyItem;
        OnDoubleClik(item,oldItem);
    }

    pAsciiInput->deleteLater();
    pAsciiInput = NULL;
}*/

void MainWindow::modifyTimeDisplaydlg(QGraphicsItem *item)//ʱ����ʾ
{
    QTimeDisplayDlg  *timedisplaydlg=new QTimeDisplayDlg(item,this);
    if(timedisplaydlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = timedisplaydlg->pTimeDisplayGen->pCopyItem;
        OnDoubleClik(item,oldItem);
    }

    timedisplaydlg->deleteLater();
    timedisplaydlg = NULL;
}
void MainWindow::modifyDateDisplaydlg(QGraphicsItem *item)//������ʾ
{
    QDateDisplayDlg  *datedisplaydlg=new QDateDisplayDlg(item,this);
    if(datedisplaydlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = datedisplaydlg->pDateDisplayGen->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    datedisplaydlg->deleteLater();
    datedisplaydlg = NULL;
}
void MainWindow::modifyDynAlarmBardlg(QGraphicsItem *item)//��̬������
{
    AlarmbarDlg *dynalarmbar=new AlarmbarDlg(item,this);
    if( dynalarmbar->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = dynalarmbar->pDynAlarmBarGen->pCopyItem;
        OnDoubleClik(item,oldItem);
    }

    dynalarmbar->deleteLater();
    dynalarmbar = NULL;
}
/*void MainWindow::modifyMeterdlg(QGraphicsItem *item)//�Ǳ�
{
    QMeterDlg *meter=new QMeterDlg(item,this);
    if(meter->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = meter->pQMeterGen->pCopyItem;
        OnDoubleClik(item,oldItem);
    }

    meter->deleteLater();
    meter = NULL;
}*/
void MainWindow::modifyChartdlg(QGraphicsItem *item)//ͼ��
{
    QChartDlg *chart=new QChartDlg(item,this);
    if(chart->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = chart->pCopyItem;
        OnDoubleClik(item,oldItem);
    }

    chart->deleteLater();
    chart = NULL;
}
void MainWindow::modifyValuedlg(QGraphicsItem *item)//ͼ��
{
    QValueDlg *qValue=new QValueDlg(item,this);
    if(qValue->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = qValue->pCopyItem;
        OnDoubleClik(item,oldItem);
    }

    qValue->deleteLater();
    qValue = NULL;
}
void MainWindow::modifyImagedlg(QGraphicsItem *item)//ͼ��
{
    QImageShowDlg *qImage=new QImageShowDlg(item,this);
    if(qImage->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = qImage->pCopyItem;
        OnDoubleClik(item,oldItem);
    }

    qImage->deleteLater();
    qImage = NULL;
}
void MainWindow::modifyFlowBlock(QGraphicsItem *item)//������
{
    qFlowBlock *flowblock=new qFlowBlock(item,this);
    if(flowblock->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = flowblock->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    flowblock->deleteLater();
    flowblock = NULL;
}
void MainWindow::modifyAlarmControldlg(QGraphicsItem *item)//�����ؼ�
{
    AlarmListDlg *alarmcontrol=new AlarmListDlg(item,1,this);
    if(alarmcontrol->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = alarmcontrol->item;
        OnDoubleClik(item,oldItem);
        //pSceneSheet[nActiveSheetIndex]->removeItem(item);//�Ƴ���ITEM
    }
    alarmcontrol->deleteLater();
    alarmcontrol = NULL;
}
/***********************************************************************
  ������¼��ʾ���޸Ļ�˫��
 ***********************************************************************/
/*void MainWindow::modifyOperateDisplay(QGraphicsItem *item)//������¼��ʾ�ؼ�
{
    qoperatecontroldlg *operatecontrol=new qoperatecontroldlg(item,this);
    if(operatecontrol->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = operatecontrol->pCopyItem;
        OnDoubleClik(item,oldItem);
        //pSceneSheet[nActiveSheetIndex]->removeItem(item);//�Ƴ���ITEM
    }
    operatecontrol->deleteLater();
    operatecontrol = NULL;
}*/
void MainWindow::modifyHisAlarmdlg(QGraphicsItem *item)//��ʷ������ʾ��
{
    AlarmListDlg *hisalarm=new AlarmListDlg(item,2,this);
    if(hisalarm->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = hisalarm->item;
        OnDoubleClik(item,oldItem);
    }
    hisalarm->deleteLater();
    hisalarm = NULL;
}
void MainWindow::OnModifyLine(QGraphicsItem *item)//ֱ��
{
    DrawItemToScene dfun;
    QGraphicsItem *newItem;
    dfun.CopyItem(&newItem,item);
    QLineDlg *straight=new QLineDlg(newItem,this);
    if(straight->exec() == QDialog::Accepted)
    {
        undoStack->push(new ModifyBaseItemCommand(pSceneSheet[nActiveSheetIndex],item,newItem));
    }
    if(straight)
    {
        delete straight;
        straight=NULL;
    }
}
void MainWindow::OnModifyRect(QGraphicsItem *item)//��Բ�����Ρ������
{
    DrawItemToScene dfun;
    QGraphicsItem *newItem;
    dfun.CopyItem(&newItem,item);
    QRectDlg *rectdlg=new QRectDlg(newItem,this);
    if(rectdlg->exec() == QDialog::Accepted)
    {
        undoStack->push(new ModifyBaseItemCommand(pSceneSheet[nActiveSheetIndex],item,newItem));
    }
    if(rectdlg)
    {
        delete rectdlg;
        rectdlg=NULL;
    }
}
void MainWindow::OnModfyText(QGraphicsItem *item)//�ı�
{
    StaticTexts *pText=new StaticTexts(item,this);
    if(pText->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pText->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    pText->deleteLater();
    pText = NULL;
}

//���˫��һ���ؼ�����Ӧ����
void MainWindow::SlotItemDBClick(QGraphicsItem *item)
{
    if(isCompiled)
    {
        return;
    }
    int value = 0;
    QItemGroup *itemGroup = dynamic_cast<QItemGroup *>(item);

    if(itemGroup)
    {
        int type = itemGroup->GroupType();
        if(type == SAM_DRAW_GROUP_SWITCH
           || type == SAM_DRAW_GROUP_TREND
           || type == SAM_DRAW_GROUP_GROUPDATA
           || type == SAM_DRAW_GROUP_CHART
           || type == SAM_DRAW_GROUP_VALUE
           || type == SAM_DRAW_GROUP_TIME
           || type == SAM_DRAW_GROUP_ASCII
           || type == SAM_DRAW_GROUP_ALARMBAR
           || type == SAM_DRAW_GROUP_ANIMATION
           || type == SAM_DRAW_GROUP_KEY//���̰�ť
           || type == SAM_DRAW_GROUP_FLOW//������
           || type == SAM_DRAW_GROUP_RECIPE
           || type == SAM_DRAW_GROUP_ALARMITEM
           || type == SAM_DRAW_GROUP_HISALARMITEM
           || type == SAM_DRAW_GROUP_IMAGE
           || type == SAM_DRAW_GROUP_DYNRECT
           || type == SAM_DRAW_GROUP_DYNCIRCLE
           || type == SAM_DRAW_GROUP_STATICTEXT//��̬�ı�

           || type == SAM_DRAW_GROUP_TABLE//���

           || type == SAM_DRAW_GROUP_CALIBRATION//�̶�
           || type == SAM_DRAW_GROUP_SLIDER//������
           || type == SAM_DRAW_GROUP_RECIPESHOW
           || value == GROUP_TYPE_DYNCIRCLE
           || value == GROUP_TYPE_DYNRECT
           || value == GROUP_TYPE_MESSAGEBOARD
           || type == SAM_DRAW_GROUP_DROPDOWN
           || type == SAM_DRAW_GROUP_HISTORYDATE
           || type == SAM_DRAW_GROUP_STATICPIC
           || type == SAM_DRAW_GROUP_MESSAGE
           || type == SAM_DRAW_GROUP_TEXTBOARD
           || type == SAM_DRAW_GROUP_MFBTN
           || type == SAM_DRAW_GROUP_COMBOBOX
           || type == SAM_DRAW_GROUP_XYTREND)
        {
            GroupTypeKey(item);//���ͼ��
        }
    }
    else
    {
        BasicGraphicsItem(item);
    }
}
void MainWindow::BasicGraphicsItem(QGraphicsItem *item)
{
    switch(item->type())
    {
    case SAM_DRAW_OBJECT_LINE://ֱ��
    case SAM_DRAW_OBJECT_FOLDLINE://����
    case SAM_DRAW_OBJECT_LINECIRCLE://���ߡ�Բ��
    case SAM_DRAW_OBJECT_FREELINE://����ֱ��

    case SAM_DRAW_OBJECT_LINE_NEW://ֱ��
    case SAM_DRAW_OBJECT_FOLDLINE_NEW://����
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW://���ߡ�Բ��
    case SAM_DRAW_OBJECT_FREELINE_NEW://����ֱ��
        OnModifyLine(item);
        break;
    case SAM_DRAW_OBJECT_RECT://����
    case SAM_DRAW_OBJECT_ELIPSE://��Բ
    case SAM_DRAW_OBJECT_POLYGON://�����

    case SAM_DRAW_OBJECT_RECT_NEW://����
    case SAM_DRAW_OBJECT_ELIPSE_NEW://��Բ
    case SAM_DRAW_OBJECT_POLYGON_NEW://�����
        OnModifyRect(item);
         break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT: //Բ�Ǿ���
    case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW: //Բ�Ǿ���
        OnModfyRoundedRectDlg(item);
         break;
    case SAM_DRAW_OBJECT_ARC: //��������ͼ��
    case SAM_DRAW_OBJECT_ARC_NEW: //��������ͼ��
        OnModfyArcDlg(item);
         break;
//    case SAM_DRAW_OBJECT_TEXT://��̬�ı�
//        OnModfyText(item);
//        break;
    default:
         GroupTypeKey(item);
        break;

    }
}

void MainWindow::GroupTypeKey(QGraphicsItem *item)
{

    QVariant value;

    QItemGroup *itemGroup = dynamic_cast<QItemGroup *>(item);

    if(!itemGroup)
    {
        return ;
    }

    switch(itemGroup->GroupType())
    {
    case SAM_DRAW_GROUP_SWITCH:
        modifyBitBtndlg(itemGroup);
        break;

    case SAM_DRAW_GROUP_CHART:
        modifyChartdlg(itemGroup);
        break;
		
    case SAM_DRAW_GROUP_TREND://����ͼ
        OnTrendChartDlg(itemGroup);
        break;

    case SAM_DRAW_GROUP_GROUPDATA://����Ⱥ��
        OnModfyDataGroupDisplayDlg(itemGroup);
        break;

    case SAM_DRAW_GROUP_VALUE:
    case SAM_DRAW_GROUP_TIME:
    case SAM_DRAW_GROUP_ASCII:
        modifyValuedlg(itemGroup);
        break;

    case SAM_DRAW_GROUP_IMAGE:
        modifyImagedlg(itemGroup);
        break;

    case SAM_DRAW_GROUP_FLOW://������
        modifyFlowBlock(itemGroup);
        break;
    case  SAM_DRAW_GROUP_KEY://���̰�ť
        modifyKeyBoardASCII(itemGroup);
        break;
    case SAM_DRAW_GROUP_ALARMBAR://��̬������
        modifyDynAlarmBardlg(itemGroup);
        break;
    case SAM_DRAW_GROUP_STATICTEXT://��̬�ı�
        OnModfyText(itemGroup);
        break;
    case SAM_DRAW_GROUP_CALIBRATION://�̶�
        OnModifyScaleDlg(itemGroup);
        break;
    case SAM_DRAW_GROUP_SLIDER://������
        OnModfySliderDlg(itemGroup);
        break;
    case SAM_DRAW_GROUP_TABLE://���
        OnModifyTableDlg(itemGroup);
        break;
    case SAM_DRAW_GROUP_ANIMATION:
        OnModfyAnimationDlg(itemGroup);
        break;

    case SAM_DRAW_GROUP_DYNRECT://��̬����
        modifyDynRectdlg(itemGroup);
        break;

    case SAM_DRAW_GROUP_DYNCIRCLE://��̬Բ
        modifyDynCircledlg(itemGroup);
        break;

    case SAM_DRAW_GROUP_RECIPE:
        modifyRecipeChoice(itemGroup);
        break;

    case SAM_DRAW_GROUP_ALARMITEM:
        modifyAlarmControldlg(itemGroup);
        break;

    case SAM_DRAW_GROUP_HISALARMITEM:
        modifyHisAlarmdlg(itemGroup);
        break;

    case SAM_DRAW_GROUP_DROPDOWN:
        OnModfyComboBoxDlg(itemGroup);
        break;

    case SAM_DRAW_GROUP_RECIPESHOW://�䷽��ʾ��
        modifyRecipeDisplay(itemGroup);
        break;

    case SAM_DRAW_GROUP_HISTORYDATE://��ʷ������ʾ��
        OnModfyHisDataShowDlg(item);
        break;

    case SAM_DRAW_GROUP_MESSAGE://��Ϣ��ʾ��
        OnModifyMsgDisplayDlg(item);
        break;

    case SAM_DRAW_GROUP_STATICPIC:
        OnModifyStaticPic(item);
        break;

    case SAM_DRAW_GROUP_TEXTBOARD:
        OnModifyTextBoard(item);
        break;
    case SAM_DRAW_GROUP_MFBTN://�๦�ܰ�ť
        modifyMFbtndlg(item);
        break;

    case SAM_DRAW_GROUP_COMBOBOX:
        OnModifyComboBox(item);
        break;
    case SAM_DRAW_GROUP_XYTREND:
        OnXYTrendChartDlg(item);
    }
    /*
    value = item->data(GROUP_TYPE_KEY);
    switch(value.toInt())
    {
  case GROUP_TYPE_BITBTN://��λ��ť
        modifyBitBtndlg(item);
        break;
 case GROUP_TYPE_BITLAMP://��λָʾ�ư�ť
        modifyBitLampdlg(item);
        break;
    case GROUP_TYPE_WORDBTN://���ְ�ť
        modifyWordBtndlg(item);
        break;
   case GROUP_TYPE_SCREENBTN://���水ť
        modifyScreenBtndlg(item);
        break;
    case GROUP_TYPE_FUNCTIONBTN://���ܰ�ť
        modifyFunctionBtndlg(item);
        break;
   case GROUP_TYPE_DYNCIRCLE://��̬Բ
        modifyDynCircledlg(item);
        break;
    case GROUP_TYPE_DYNRECT://��̬����
        modifyDynRectdlg(item);
        break;
    case GROUP_TYPE_MFUNCTION://�๦��
        modifyMfunctiondlg(item);
        break;
  case GROUP_TYPE_PICTUREDISPLAY://ͼƬ��ʾ��
          modifyPictureDisplaydlg(item);
          break;
   case GROUP_TYPE_WEEKBTN://������ʾ
        modifyWeekdlg(item);
        break;
  case  GROUP_TYPE_MULSTATELAMP://��״ָ̬ʾ��
        modifyMultiLampdlg(item);
        break;
   case  GROUP_TYPE_MULSTATEBTN://��̬��ť
         modifyMultiStatedlg(item);
         break;

   case  GROUP_TYPE_PICTUREMOVE://ͼƬ�ƶ�
         modifyGraphicsMovedlg(item);
         break;
    case GROUP_TYPE_NUMDISPLAY ://��ֵ��ʾ
        modifyNumDispaydlg(item);
        break;
    case GROUP_TYPE_NUMENTRY://��ֵ����
        modifyNumEntrydlg(item);
        break;
    case GROUP_TYPE_ASCIIDISPLAY://ASCII��ʾ
        modifyASCIIDisplaydlg(item);
        break;
    case GROUP_TYPE_ASCIIENTRY://ASCII����
        modifyASCIIDEntrydlg(item);
        break;
    case GROUP_TYPE_BARGRAPH://��״ͼ
        modifyBarGraphdlg(item);
        break;
    case GROUP_TYPE_TIMEDISPLAY://ʱ����ʾ
        modifyTimeDisplaydlg(item);
        break;
    case GROUP_TYPE_DATEDISPLAY://������ʾ
        modifyDateDisplaydlg(item);
        break;
    case GROUP_TYPE_ALARMCONTROL://�����ؼ�
        modifyAlarmControldlg(item);
        break;
    case GROUP_TYPE_DYNALARMBAR://��̬������
        modifyDynAlarmBardlg(item);
        break;
    case GROUP_TYPE_HISALARM://��ʷ������ʾ��
        modifyHisAlarmdlg(item);
        break;

    case GROUP_TYPE_METER://�Ǳ�
        modifyMeterdlg(item);
        break;
    case GROUP_TYPE_FLOWBLOCK://������
        modifyFlowBlock(item);
        break;
    case GROUP_TYPE_STATICPIC://��̬ͼƬ
        OnModifyStaticPic(item);
        break;
    case GROUP_TYPE_GIFPIC://GIFͼƬ
        OnModifyGifPic(item);
        break;
    case GROUP_TYPE_PIE:   //����ͼ
        OnModifyPieDlg(item);
        break;
    case GROUP_TYPE_MSGDISPLAY:   //��Ϣ��ʾ
        OnModifyMsgDisplayDlg(item);
        break;
    case GROUP_TYPE_TABLE: //���
        OnModifyTableDlg(item);
        break;
    case GROUP_TYPE_SCALES: //�̶�
        OnModifyScaleDlg(item);
        break;
    case GROUP_TYPE_STATICTEXT://�ı�
         OnModfyText(item);
         break;
    case GROUP_TYPE_TRENDCHART://����ͼ
         OnTrendChartDlg(item);
         break;
    case GROUP_TYPE_XYTRENDCHART://XY����ͼ
         OnXYTrendChartDlg(item);
         break;
    case GROUP_TYPE_HISTRENDCHART://��ʷ����ͼ
         OnHISTrendChartDlg(item);
          break;
    case GROUP_TYPE_STEPING: //������ť
        OnModfyStepingDlg(item);
         break;
    case GROUP_TYPE_SINGLESELECT://��ѡ��ť
        OnModfySingleSelectDlg(item);
         break;
    case GROUP_TYPE_COMBOBOX: //������
        OnModfyComboBoxDlg(item);
         break;
    case GROUP_TYPE_SLIDER: //����ģ��������
        OnModfySliderDlg(item);
         break;
    case GROUP_TYPE_HISDATAALARM: //��ʷ��¼��ʾ��
        OnModfyHisDataShowDlg(item);
         break;
    case GROUP_TYPE_ANIMATE: //����
        OnModfyAnimationDlg(item);
         break;
    case GROUP_TYPE_MESSAGEBOARD: //���԰�
        OnModfyMsgBoardDlg(item);
         break;
    case GROUP_TYPE_DATAGROUPDISPLAY :  //����Ⱥ����ʾ
        OnModfyDataGroupDisplayDlg(item);
         break;
    case GROUP_TYPE_TIMER :  //��ʱ��
        OnModfyTimerDlg(item);
         break;
    case GROUP_TYPE_ASCII_KEYBOARD://ASCII����
        modifyKeyBoardASCII(item);
        break;
    case GROUP_TYPE_RECIPE_CHOICE://�䷽ѡ����
        modifyRecipeChoice(item);
        break;
    case GROUP_TYPE_RECIPE_DISPLAY://�䷽��ʾ��
        modifyRecipeDisplay(item);
        break;
    case GROUP_TYPE_OPERATE_RECORD://������¼��ʾ��
        modifyOperateDisplay(item);
    case GROUP_TYPE_CHART:          //ͼ��
        modifyChartdlg(item);
        break;
    case GROUP_TYPE_VALUE:
        modifyValuedlg(item);
    default:
        break;
    }
    */
}

void MainWindow::itemsMoved(SamDrawScene *scene,QList <QGraphicsItem *> movingItems,QList <QPointF >oldPoss)
{
    undoStack->push(new MovesCommand(scene,movingItems, oldPoss));
}
void MainWindow::itemResize(SamDrawScene *scene,QGraphicsItem *resizeItem,QSizeF oldSize,QPointF oldPos)
{
    undoStack->push(new SizeCommand(scene,resizeItem, oldSize,oldPos));
}
/*
void MainWindow::deleteItem()
{
    if (scene[nActiveSheetIndex]->selectedItems().isEmpty())
        return;

    QUndoCommand *deleteCommand = new DeleteCommand(scene[nActiveSheetIndex]);
    undoStack->push(deleteCommand);
}
*/
void MainWindow::onWidthSame()
{
    if(pSceneSheet[nActiveSheetIndex]->selectedItems().size()>1)
    {
        QList <QGraphicsItem *> list =
                pSceneSheet[nActiveSheetIndex]->selectedItems();

        QList <QPointF > posList;
        QList <QSizeF > sizeList;

        foreach(QGraphicsItem *pItem,list)
        {
            posList << pItem->sceneBoundingRect().topLeft();
            sizeList << pItem->sceneBoundingRect().size();
        }

        pSceneSheet[nActiveSheetIndex]->setWidthSame();

        QUndoCommand * algincommand = new AlignCommand(
                pSceneSheet[nActiveSheetIndex],list,sizeList,posList);
        undoStack->push(algincommand);
    }
}

void MainWindow::onHeightSame()
{
    if(pSceneSheet[nActiveSheetIndex]->selectedItems().size()>1)
    {
        QList <QGraphicsItem *> list =
                pSceneSheet[nActiveSheetIndex]->selectedItems();

        QList <QPointF > posList;
        QList <QSizeF > sizeList;

        foreach(QGraphicsItem *pItem,list)
        {
            posList << pItem->sceneBoundingRect().topLeft();
            sizeList << pItem->sceneBoundingRect().size();
        }
        pSceneSheet[nActiveSheetIndex]->setHeightSame();
        QUndoCommand * algincommand = new AlignCommand(
                pSceneSheet[nActiveSheetIndex],list,sizeList,posList);
        undoStack->push(algincommand);
    }

}

void MainWindow::onWidthHeightSame()
{
    if(pSceneSheet[nActiveSheetIndex]->selectedItems().size()>1)
    {
        QList <QGraphicsItem *> list =
                pSceneSheet[nActiveSheetIndex]->selectedItems();

        QList <QPointF > posList;
        QList <QSizeF > sizeList;

        foreach(QGraphicsItem *pItem,list)
        {
            posList << pItem->sceneBoundingRect().topLeft();
            sizeList << pItem->sceneBoundingRect().size();
        }
        pSceneSheet[nActiveSheetIndex]->setWidthHeightSame();
        QUndoCommand * algincommand = new AlignCommand(
                pSceneSheet[nActiveSheetIndex],list,sizeList,posList);
        undoStack->push(algincommand);
    }

}

/***************************************************
 *�������ƣ�OnAddPattern(QComboBox *pComboBox)
 *�������ܣ�Ϊÿ���ؼ���һ��ҳ�������ʽ
 *�������壺pComboBoxΪָ����Ͽ��ָ��
 *edit by zqh
 **************************************************/
void MainWindow::OnAddPattern(QComboBox *pComboBox)
{   //13����ʽ
    pComboBox->addItem(QIcon(":/style/images/style/1.ico"),tr("͸��"));
    pComboBox->addItem(QIcon(":/style/images/style/1.ico"),tr("��ɫ"));
    pComboBox->addItem(QIcon(":/style/images/style/15.ico"),tr("�������"));
    pComboBox->addItem(QIcon(":/style/images/style/16.ico"),tr("����Գƹ���"));
    pComboBox->addItem(QIcon(":/style/images/style/17.ico"),tr("�������"));
    pComboBox->addItem(QIcon(":/style/images/style/18.ico"),tr("����Գƹ���"));
    pComboBox->addItem(QIcon(":/style/images/style/19.ico"),tr("б�Ϲ���"));
    pComboBox->addItem(QIcon(":/style/images/style/20.ico"),tr("б�϶Գƹ���"));
    pComboBox->addItem(QIcon(":/style/images/style/21.ico"),tr("б�¹���"));
    pComboBox->addItem(QIcon(":/style/images/style/22.ico"),tr("б�¶Գƹ���"));
    pComboBox->addItem(QIcon(":/style/images/style/24.ico"),tr("���ϽǷ���"));
    pComboBox->addItem(QIcon(":/style/images/style/23.ico"),tr("���ϽǷ���"));
    pComboBox->addItem(QIcon(":/style/images/style/25.ico"),tr("���ķ���"));


    pComboBox->setCurrentIndex(1); //Ĭ��ѡ��ɫ


}

QString MainWindow::ColorTOString(QColor color) //����ɫֵת��ΪQString����
{
    QString sColor = "";
    int nRed = color.red();
    int nGreen = color.green();
    int nBule = color.blue();
    sColor = QString("%1+%2+%3").arg(nRed).arg(nGreen).arg(nBule);
    return sColor;
}

void MainWindow::OnAddNewScreen()  //�½�����
{
    //nSheetTotalNumber ++; //��ǰ���̽��Ļ�������
    //nActiveSheetIndex ++; //��ǰ�������
    //OnNewGraphicsScene(0,800,600);
    tree_newscreen();
    dockTabWidget->setCurrentIndex(1);
}

void MainWindow::OnSetTheFrontScreen() //��һ������
{
    int tempIndex=nActiveSheetIndex;//�����ʼֵ
    if(nActiveSheetIndex==0)//���Ѿ��ǵ�һ��ֵ��ʱ��
    {
        return;
    }
    for(nActiveSheetIndex--;nActiveSheetIndex>=0;nActiveSheetIndex--)
    {
        if(pSceneSheet[nActiveSheetIndex]->nIsSceneOrWindow!=2)
        {
            break;
        }
    }
    if(nActiveSheetIndex<0)
    {
        nActiveSheetIndex=tempIndex;
    }
    pView->setScene(pSceneSheet[nActiveSheetIndex]);

    QString strDest;
    QString strtemp = pwnd->pSceneSheet[nActiveSheetIndex]->sNewScreenName;
    handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);
    //pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(pwnd->pSceneSheet[nActiveSheetIndex]->sNewScreenName));

}

void MainWindow::OnSetTheNextScreen() //��һ������
{
    int tempIndex=nActiveSheetIndex;//�����ʼֵ
    int totalSceneNum = pSceneSheet.size();
    if(nActiveSheetIndex==totalSceneNum-1)//���Ѿ������һ��ֵ��ʱ��
    {
        return;
    }

    for(nActiveSheetIndex++;nActiveSheetIndex<totalSceneNum;nActiveSheetIndex++)
    {
        if((pSceneSheet[nActiveSheetIndex]->nIsSceneOrWindow!=2))
        {
            break;
        }
    }
    if(nActiveSheetIndex>=totalSceneNum)
    {
        nActiveSheetIndex=tempIndex;
    }
    pView->setScene(pSceneSheet[nActiveSheetIndex]);

    QString strDest;
    QString strtemp = pwnd->pSceneSheet[nActiveSheetIndex]->sNewScreenName;
    handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);
    pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2"AK_FILE_END"--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(pwnd->pSceneSheet[nActiveSheetIndex]->sNewScreenName));
}

QColor MainWindow::StringTOColor(QString sColor)
{
    QColor color;
    QStringList sList = sColor.split("+", QString::SkipEmptyParts);
    if(3 > sList.size())
        return QColor(0,0,0);
    color.setRed(sList.at(0).toInt());
    color.setGreen(sList.at(1).toInt());
    color.setBlue(sList.at(2).toInt());
    return color;
}//
void MainWindow::InitDateType(QComboBox *combobox)
{
    combobox->addItem(tr("16λ������"));
    combobox->addItem(tr("32λ������"));
    combobox->addItem(tr("16λ����"));
    combobox->addItem(tr("32λ����"));
    combobox->addItem(tr("16λBCD������"));
    combobox->addItem(tr("32λBCD������"));
    combobox->addItem(tr("32λ������"));
}

QString MainWindow::KeyboardToString(Keyboard keyboard)
{
    QString temp;
    temp=temp+keyboard.sShowAddr;//��ַ�����ַ����硰X123��
    temp+='#';//�ָ���

    temp+=QString::number(keyboard.nConnectType);//�����ͺ����ڲ��洢����com1��
    temp+='#';//�ָ���

    temp+=QString::number(keyboard.nPlcRegTypeIndex);//PLC�Ĵ���X��Y��T��C�ȵ�����
    temp+='#';//�ָ���

    temp+=QString::number(keyboard.nPlcStationIndex);//PLCվ��
    temp+='#';//�ָ���

    temp+=keyboard.sPlcAddrValue;//plc�Ĵ�����ַ�硰123����
    temp+='#';//�ָ���

    temp+=keyboard.sPlcRegTypeStr;//plc�Ĵ�����X������Y����
    temp+='#';//�ָ���

    temp+=QString::number(keyboard.nAddrType); //��λ��ʾ
    temp+='#';//�ָ���

    return temp;
}
void MainWindow::StringToKeyboard(Keyboard &keyboard,QString sKeyboard)
{
    QStringList sList = sKeyboard.split('#'); //QString::SkipEmptyParts

    if(sList.size()<7)
        return;

    QString temp;
    keyboard.sShowAddr = sList.at(0);

    temp =sList.at(1);
    keyboard.nConnectType = temp.toInt();

    temp =sList.at(2);
    keyboard.nPlcRegTypeIndex =temp.toInt();


    temp =sList.at(3);
    keyboard.nPlcStationIndex = temp.toInt();

    keyboard.sPlcAddrValue =sList.at(4);

    keyboard.sPlcRegTypeStr =sList.at(5);

    temp =sList.at(6);
    keyboard.nAddrType = temp.toInt();

}

void MainWindow::OnModifyStaticPic(QGraphicsItem *item) //˫���򿪾�̬ͼƬ�Ի���
{
    QStaticPictureDlg *staticpicturedlg=new QStaticPictureDlg(item,this);

    if(staticpicturedlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = staticpicturedlg->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
}

void MainWindow::OnModifyTextBoard(QGraphicsItem *item)
{
    qMessageBoard *pMessageBoardDlg = new qMessageBoard((qMessageBoradAttr *)item,this);

    if(pMessageBoardDlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pMessageBoardDlg->m_pCopyItem;
        OnDoubleClik(item,oldItem);
    }

    pMessageBoardDlg->deleteLater();
    pMessageBoardDlg = NULL;
}

void MainWindow::OnModifyComboBox(QGraphicsItem *item)
{
    AkComboBox *pAkComboBox = new AkComboBox((AkComboItem *)item,this);

    if(pAkComboBox->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pAkComboBox->m_pCopyItem;
        OnDoubleClik(item,oldItem);
    }

    pAkComboBox->deleteLater();
    pAkComboBox = NULL;
}

/*void MainWindow::OnModifyGifPic(QGraphicsItem *item)
{
    QGIFDisplayDlg *gifdisplaydlg=new QGIFDisplayDlg(item,this);
    if(gifdisplaydlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = gifdisplaydlg->pGeneralDlg->pOldItem;
        //OnDoubleClikSpare(item,oldItem);
        OnDoubleClik(item,oldItem);
    }
}*/

void MainWindow::OnDoubleClikSpare(QGraphicsItem *item, QGraphicsItem *OldItem)
{
    QPointF pos = item->pos();

    pSceneSheet[nActiveSheetIndex]->removeItem(item);//�Ƴ���ITEM
    ModifyItemCommand * modifycommand =
            new ModifyItemCommand(item,OldItem,pSceneSheet[nActiveSheetIndex],"");
    undoStack->push(modifycommand);
    OldItem->setPos(pos);
}
QGraphicsItem * MainWindow::PasteItemToScence()//��ճ��Item��������ʱ��
{
    QGraphicsItem *NouseItem = NULL;
    QGraphicsItem *oldItem = NULL;
    QGraphicsItem *pTmp = NULL;
    int nKey=0;
    if(pSceneSheet[nActiveSheetIndex]->pasteList.size()==1)
    {
        pSceneSheet[nActiveSheetIndex]->setNewItem_ID(pSceneSheet[nActiveSheetIndex]->pasteList.at(0),NouseItem );
        pSceneSheet[nActiveSheetIndex]->addItem(pSceneSheet[nActiveSheetIndex]->pasteList.at(0));
        AndTreeSubItem(pSceneSheet[nActiveSheetIndex]->pasteList.at(0));
        //upDatetreeScreenItem();//���»��������
        oldItem=pSceneSheet[nActiveSheetIndex]->pasteList.at(0);


        oldItem->setPos(pSceneSheet[nActiveSheetIndex]->MousePressPos.x()-oldItem->boundingRect().left()
                        ,pSceneSheet[nActiveSheetIndex]->MousePressPos.y()-oldItem->boundingRect().top());

        //oldItem = ReloadPic(oldItem,pSceneSheet[nActiveSheetIndex]);
        oldItem->setSelected(true);
        QList <QGraphicsItem *> lst;
        lst.append(oldItem);
        pasteCommand *pCommandp=new pasteCommand(pSceneSheet[nActiveSheetIndex],lst,true);
        undoStack->push(pCommandp);
        return oldItem;
    }
    else//��ճ�����Ƕ����ʱ��
    {

        for(int i=0;i<pSceneSheet[nActiveSheetIndex]->pasteList.size();i++)
        {
            nKey=pSceneSheet[nActiveSheetIndex]->pasteList.at(i)->data(GROUP_TYPE_KEY).toInt(); //ȡ��keyֵ

            pSceneSheet[nActiveSheetIndex]->setNewItem_ID(pSceneSheet[nActiveSheetIndex]->pasteList.at(i),NouseItem );
            pSceneSheet[nActiveSheetIndex]->addItem(pSceneSheet[nActiveSheetIndex]->pasteList.at(i));
            AndTreeSubItem(pSceneSheet[nActiveSheetIndex]->pasteList.at(i));
            //upDatetreeScreenItem();//���»��������

        }
        int nLeftMostIndex = 0;
        int nTopMostIndex = 0;
        qreal rLeftMost,rTopMost;
        for(int i=0;i<pSceneSheet[nActiveSheetIndex]->parentItem_list.size();i++)
        {
            rLeftMost = GetItemRect(pSceneSheet[nActiveSheetIndex]->parentItem_list.at(nLeftMostIndex)).left();
            rTopMost = GetItemRect(pSceneSheet[nActiveSheetIndex]->parentItem_list.at(nTopMostIndex)).top();
            pTmp = pSceneSheet[nActiveSheetIndex]->parentItem_list.at(i);
            if(rLeftMost >GetItemRect(pTmp).left())
            {
                nLeftMostIndex = i;
            }

            if(rTopMost >GetItemRect(pTmp).top())
            {
                nTopMostIndex = i;
            }
        }
        QList <QGraphicsItem *> lst;

        for(int i=0;i<pSceneSheet[nActiveSheetIndex]->pasteList.size();i++)
        {
            QGraphicsItem* ptr = pSceneSheet[nActiveSheetIndex]->pasteList.at(i);
            int type = ptr->data(GROUP_RECT_KEY).toInt();
            if(type == GROUP_TYPE_STATICPIC || type == GROUP_TYPE_STATICPIC)
            {
                QPointF pos,ps;
                QRectF rect,rect1;
                rect = GetItemRect(ptr);
                rect = QRectF(QPointF(pSceneSheet[nActiveSheetIndex]->MousePressPos.x()
                              +GetItemRect(pSceneSheet[nActiveSheetIndex]->parentItem_list.at(i)).left()
                              -GetItemRect(pSceneSheet[nActiveSheetIndex]->parentItem_list.at(nLeftMostIndex)).left()
                              -pSceneSheet[nActiveSheetIndex]->pasteList.at(i)->boundingRect().left()
                              ,pSceneSheet[nActiveSheetIndex]->MousePressPos.y()
                              +GetItemRect(pSceneSheet[nActiveSheetIndex]->parentItem_list.at(i)).top()
                              -GetItemRect(pSceneSheet[nActiveSheetIndex]->parentItem_list.at(nLeftMostIndex)).top()
                              -pSceneSheet[nActiveSheetIndex]->pasteList.at(i)->boundingRect().top())
                              ,rect.size());
            }
            pSceneSheet[nActiveSheetIndex]->pasteList.at(i)->setPos(pSceneSheet[nActiveSheetIndex]->MousePressPos.x()
                                                                    +GetItemRect(pSceneSheet[nActiveSheetIndex]->parentItem_list.at(i)).left()
                                                                    -GetItemRect(pSceneSheet[nActiveSheetIndex]->parentItem_list.at(nLeftMostIndex)).left()
                                                                    -pSceneSheet[nActiveSheetIndex]->pasteList.at(i)->boundingRect().left()
                                                                    ,pSceneSheet[nActiveSheetIndex]->MousePressPos.y()
                                                                    +GetItemRect(pSceneSheet[nActiveSheetIndex]->parentItem_list.at(i)).top()
                                                                    -GetItemRect(pSceneSheet[nActiveSheetIndex]->parentItem_list.at(nLeftMostIndex)).top()
                                                                    -pSceneSheet[nActiveSheetIndex]->pasteList.at(i)->boundingRect().top()
                                                                    );

             pSceneSheet[nActiveSheetIndex]->pasteList.at(i)->setSelected(true);

             lst << ReloadPic(pSceneSheet[nActiveSheetIndex]->pasteList.at(i),
                             pSceneSheet[nActiveSheetIndex]);

        }
        pasteCommand *pCommandp=new pasteCommand(pSceneSheet[nActiveSheetIndex],lst,true);
        undoStack->push(pCommandp);
        return NULL;
    }
}
void MainWindow::OnSingClikSpare(QGraphicsItem *oldItem)
{
   int nID = 0;
   qreal dWsize = 1.0;
   qreal dHsize = 1.0;
   qreal dDelta = 1.0;
   qreal dMin   = 10.0;
   QPointF newpos(0,0);

   dWsize = abs(pSceneSheet[nActiveSheetIndex]->MouseReleasePos.x() - pSceneSheet[nActiveSheetIndex]->prMousePoint.x());
   dHsize = abs(pSceneSheet[nActiveSheetIndex]->MouseReleasePos.y() - pSceneSheet[nActiveSheetIndex]->prMousePoint.y());

   newpos.setX(pSceneSheet[nActiveSheetIndex]->MouseReleasePos.x() < pSceneSheet[nActiveSheetIndex]->prMousePoint.x()? pSceneSheet[nActiveSheetIndex]->MouseReleasePos.x():pSceneSheet[nActiveSheetIndex]->prMousePoint.x());
   newpos.setY(pSceneSheet[nActiveSheetIndex]->MouseReleasePos.y() < pSceneSheet[nActiveSheetIndex]->prMousePoint.y()? pSceneSheet[nActiveSheetIndex]->MouseReleasePos.y():pSceneSheet[nActiveSheetIndex]->prMousePoint.y());

   if(dWsize < dMin && dHsize < dMin)
   {
       dWsize = 40.0;
       dHsize = 40.0;
   }
    pSceneSheet[nActiveSheetIndex]->clearSelection();
    if(oldItem)
    nID = oldItem->data(GROUP_TYPE_KEY).toInt();
    if(nID == LIBRARY_LIB_GROUP) ////ͼ�����
    {
        QGroupItem pGroupItem(oldItem);
        pGroupItem.SetWidth(dWsize);
        pGroupItem.SetHeigth(dHsize);
        pSceneSheet[nActiveSheetIndex]->addItem(oldItem);
        oldItem->setPos(pSceneSheet[nActiveSheetIndex]->MousePressPos-oldItem->boundingRect().topLeft());
        oldItem->setFlag(QGraphicsItemGroup::ItemIsMovable, true);
        oldItem->setFlag(QGraphicsItemGroup::ItemIsSelectable, true);
        oldItem->setSelected(true);

        pDrawToSceneItem = NULL;
        undoStack->push(new addItemToScence(pSceneSheet[nActiveSheetIndex],oldItem,true));
        return;
    }
    if(oldItem)//��������ǹ�������Item ��ʱ��
    {
        if(SAM_DRAW_OBJECT_GROUP == oldItem->type())
        {
            QItemGroup *pItem = dynamic_cast<QItemGroup *> (oldItem);
            if(SAM_DRAW_GROUP_CHART == pItem->GroupType())
            {
                ChartItem *pChartItem = dynamic_cast<ChartItem *> (oldItem);
                if(ENCOMMON_TYPE == pChartItem->m_eGraphType)
                {
                    if(CIRCLE == pChartItem->common_st.eShapeType
                       || SECTOR == pChartItem->common_st.eShapeType)
                    {
                        dDelta = pChartItem->boundingRect().width()/pChartItem->boundingRect().height();
                        if(abs(dWsize) > abs(dHsize))
                        {
                            if(dHsize >= 0)
                            {
                                dHsize = abs(dWsize / dDelta);
                            }
                            else
                            {
                                dHsize = -1 * (abs(dWsize / dDelta));
                            }
                        }
                        else
                        {
                            if(dWsize >= 0)
                            {
                                dWsize = abs(dHsize * dDelta);
                            }
                            else
                            {
                                dWsize = -1 * abs(dHsize * dDelta);
                            }
                        }
                    }
                }
                else if(ENMETER_TYPE == pChartItem->m_eGraphType)
                {
                    dDelta = pChartItem->boundingRect().width()/pChartItem->boundingRect().height();
                    if(abs(dWsize) > abs(dHsize))
                    {
                        if(dHsize >= 0)
                        {
                            dHsize = abs(dWsize / dDelta);
                        }
                        else
                        {
                            dHsize = -1 * (abs(dWsize / dDelta));
                        }
                    }
                    else
                    {
                        if(dWsize >= 0)
                        {
                            dWsize = abs(dHsize * dDelta);
                        }
                        else
                        {
                            dWsize = -1 * abs(dHsize * dDelta);
                        }
                    }
                }
            }
            QGroupItem pGroupItem(oldItem);
            pGroupItem.SetWidth(dWsize);
            pGroupItem.SetHeigth(dHsize);
        }
        pSceneSheet[nActiveSheetIndex]->addItem(oldItem);
        oldItem->setPos(newpos - oldItem->boundingRect().topLeft());
        AndTreeSubItem(oldItem);
        //add by wuxiyang�������û��������չʾ��û��Ҫ����
        //�Ҹ��µĻ��ᵼ�����ϵ�ѡ������ʧ
        //upDatetreeScreenItem();//���»��������

        if(nID == GROUP_TYPE_TIMER) //�Ƕ�ʱ��
        {
            QItemGroup *pItemGroup = NULL;
            pItemGroup = dynamic_cast<QItemGroup *> (oldItem);
            if(pItemGroup)
                pItemGroup->setResizableOff();
        }

        undoStack->push(new addItemToScence(pSceneSheet[nActiveSheetIndex],oldItem,true));
    }

    else //��ճ������һ����ʱ��
    {
        oldItem=PasteItemToScence();



        if(!oldItem)
        {
            return;
        }
    }
    oldItem->setFlag(QGraphicsItemGroup::ItemIsMovable, true);
    oldItem->setFlag(QGraphicsItemGroup::ItemIsSelectable, true);
    oldItem->setSelected(true);

    pDrawToSceneItem = NULL;

//    nID = oldItem->data(GROUP_TYPE_KEY).toInt();
//    if(nID == GROUP_TYPE_BITBTN || nID == GROUP_TYPE_BITLAMP
//       || nID == GROUP_TYPE_MULSTATELAMP || nID == GROUP_TYPE_MULSTATEBTN
//       || GROUP_TYPE_PICTUREMOVE || nID == GROUP_TYPE_MSGDISPLAY
//       || nID == GROUP_TYPE_WEEKBTN) //λ��ť λָʾ�� ��ָ̬ʾ�ơ���̬��ť��ͼ���ƶ� ��Ϣ��ʾ ������ʾ
//    {
//        this->OnSingleClickItem();//���¹������ϵ�״̬��Ͽ�����
//    }
}
void MainWindow::IsDefineGroup(QGraphicsItem * pItem)//�Ƿ����Զ������
{
    QList<QGraphicsItem *> childItems;
    int nKey=0;
    QGraphicsItem *NouseItem = NULL;
    childItems =pItem->childItems();
    for(int i=0;i<childItems.size();i++)
    {
        nKey=childItems.at(i)->data(GROUP_TYPE_KEY).toInt(); //ȡ��keyֵ
        if(nKey==USER_DEFINE_GROUP)
        {
            IsDefineGroup(childItems.at(i));
        }
        else
        {
            pSceneSheet[nActiveSheetIndex]->setNewItem_ID(childItems[i],NouseItem );
            pSceneSheet[nActiveSheetIndex]->addItem(childItems[i]);
            AndTreeSubItem(childItems[i]);
            upDatetreeScreenItem();//���»��������
            child_userGroupItems.push_back(childItems[i]);
        }
    }//
}
void MainWindow::OnDoubleClik(QGraphicsItem *item,QGraphicsItem *OldItem)
{
    if(NULL == OldItem)
    {
       pSceneSheet[nActiveSheetIndex]->removeItem(item);//�Ƴ���ITEM
       return;
    }
    int nKey = 0;
    int nType = 0;
    QGraphicsItem * newItem;
    QRectF rc = item->sceneBoundingRect();

    DrawItemToScene FunClass;
    FunClass.CopyItem(&newItem,OldItem);

     nKey =item->data(GROUP_TYPE_KEY).toInt(); //get key
     QItemGroup *itemGroup = dynamic_cast<QItemGroup *>(item);
	 if (itemGroup)
	 {
		 nType = itemGroup->GroupType();
	 }

     QGroupItem *pBaseItem = new QGroupItem(newItem);
     if(nKey == GROUP_TYPE_TIMER)
     {
         pBaseItem->SetWidth(39);
         pBaseItem->SetHeigth(39);
     }
      else if(nKey != GROUP_TYPE_ANIMATE)
      {
          if (nKey == GROUP_TYPE_METER || nKey == GROUP_TYPE_PIE)
          {
              double dW = newItem->sceneBoundingRect().width(); //��ͼ�εĿ�Ⱥ͸߶�
              double dH = newItem->sceneBoundingRect().height();
              double newH = rc.width()*dH/dW;//��ͼ�εı���ϵ��
              pBaseItem->SetWidth(rc.width());
              pBaseItem->SetHeigth(newH);
          }
          else if(SAM_DRAW_GROUP_CHART == nType)
          {
              qreal dWsize = rc.width();
              qreal dHsize = rc.height();
              qreal dDelta = 1.0;
              ChartItem *pChartItem = dynamic_cast<ChartItem *> (newItem);
              if(ENCOMMON_TYPE == pChartItem->m_eGraphType)
              {
                  if(CIRCLE == pChartItem->common_st.eShapeType
                     || SECTOR == pChartItem->common_st.eShapeType)
                  {
                      dDelta = pChartItem->boundingRect().width()/pChartItem->boundingRect().height();
                      if(abs(dWsize) > abs(dHsize))
                      {
                          dHsize = abs(dWsize / dDelta);
                      }
                      else
                      {
                          dWsize = abs(dHsize * dDelta);
                      }
                  }
              }
              else if(ENMETER_TYPE == pChartItem->m_eGraphType)
              {
                  dDelta = pChartItem->boundingRect().width()/pChartItem->boundingRect().height();
                  if(abs(dWsize) > abs(dHsize))
                  {
                      dHsize = abs(dWsize / dDelta);
                  }
                  else
                  {
                      dWsize = abs(dHsize * dDelta);
                  }
              }
              pBaseItem->SetWidth(dWsize);
              pBaseItem->SetHeigth(dHsize);
          }
          else if(item->type() == SAM_DRAW_OBJECT_ROUNDEDRECT)// alter by zqh 2012.9.19 Բ�Ǿ������Ըı���С�ᷢ���ı�
           {
               QRoundedRect *pRoundRect = dynamic_cast<QRoundedRect *> (item);
               int aa = pRoundRect->GetWidth();
               int bb  = pRoundRect->GetHeight();
               pRoundRect->SetWidth(aa);
               pRoundRect->SetHeight(bb);
           }
          else
          {
              pBaseItem->SetWidth(rc.width());
              pBaseItem->SetHeigth(rc.height());
          }

      }
    //int zValue = item->zValue();

   if(item->type() == SAM_DRAW_OBJECT_TEXT || nKey == GROUP_TYPE_STATICTEXT|| item->type() == SAM_DRAW_OBJECT_ARC)
            item->setVisible(false);

   if(!(item->flags() & QGraphicsItem::ItemIsMovable))
   {
       newItem->setFlag(QGraphicsItemGroup::ItemIsMovable, false);
   }
   else
   {
       newItem->setFlag(QGraphicsItemGroup::ItemIsMovable, true);
   }
    pSceneSheet[nActiveSheetIndex]->removeItem(item);//�Ƴ���ITEM

    //pSceneSheet[nActiveSheetIndex]->addItem(newItem,zValue);
    newItem->setFlag(QGraphicsItemGroup::ItemIsSelectable, true);


    if( nKey == GROUP_TYPE_ALARMCONTROL || nKey == GROUP_TYPE_HISALARM
       || nKey == GROUP_TYPE_HISDATAALARM || nKey == GROUP_TYPE_TRENDCHART
       || nKey == GROUP_TYPE_XYTRENDCHART || nKey == GROUP_TYPE_HISTRENDCHART
       || nKey == GROUP_TYPE_SLIDER || nKey == GROUP_TYPE_DYNRECT
       || nKey == GROUP_TYPE_DYNCIRCLE || nKey == GROUP_TYPE_FLOWBLOCK
       || nKey == GROUP_TYPE_PIE || nKey == GROUP_TYPE_METER
       || nKey == GROUP_TYPE_STEPING || nKey == GROUP_TYPE_SINGLESELECT
       || nKey == GROUP_TYPE_TABLE || nKey == GROUP_TYPE_SCALES
       || item->type() == SAM_DRAW_OBJECT_ROUNDEDRECT || item->type() == SAM_DRAW_OBJECT_ARC
       || nKey == GROUP_TYPE_STATICPIC || nKey == GROUP_TYPE_GIFPIC
       || nKey == GROUP_TYPE_MESSAGEBOARD || nKey == GROUP_TYPE_TABLE
       || item->type() == SAM_DRAW_OBJECT_TEXT || nKey == GROUP_TYPE_DATAGROUPDISPLAY
       || nKey == GROUP_TYPE_RECIPE_CHOICE || nKey == GROUP_TYPE_RECIPE_DISPLAY
       || nKey == GROUP_TYPE_OPERATE_RECORD || nType == SAM_DRAW_GROUP_CHART
       || nType == SAM_DRAW_GROUP_IMAGE || nType == SAM_DRAW_GROUP_VALUE
       || nType == SAM_DRAW_GROUP_ASCII || nType == SAM_DRAW_GROUP_TIME
       || nType == SAM_DRAW_GROUP_TREND || nType == SAM_DRAW_GROUP_DYNRECT
       || nType == SAM_DRAW_GROUP_DYNCIRCLE || nType == SAM_DRAW_GROUP_RECIPE
       || nType == SAM_DRAW_GROUP_GROUPDATA || nType == SAM_DRAW_GROUP_RECIPESHOW
       || nType == SAM_DRAW_GROUP_ALARMITEM || nType == SAM_DRAW_GROUP_HISALARMITEM
       || nType == SAM_DRAW_GROUP_DROPDOWN || nType == SAM_DRAW_GROUP_HISTORYDATE
       || nType == SAM_DRAW_GROUP_STATICPIC || nType == SAM_DRAW_GROUP_STATICTEXT
       || nType == SAM_DRAW_GROUP_SLIDER || nType == SAM_DRAW_GROUP_FLOW
       || nType == SAM_DRAW_GROUP_CALIBRATION || nType == SAM_DRAW_GROUP_MESSAGE
       || nType == SAM_DRAW_GROUP_TABLE || nType == SAM_DRAW_GROUP_TEXTBOARD
       || nType == SAM_DRAW_GROUP_COMBOBOX || nType == SAM_DRAW_GROUP_XYTREND)
    {
        newItem->setPos(rc.topLeft()-newItem->boundingRect().topLeft());//�����µ�item��λ��
    }
    else if(nKey == GROUP_TYPE_TIMER)//�Ƕ�ʱ��
    {
            QItemGroup *pItemGroup = NULL;
            pItemGroup = dynamic_cast<QItemGroup *> (newItem);
            if(pItemGroup)
                pItemGroup->setResizableOff();
    }


    newItem->setSelected(true);
    ModifyItemCommand * modifycommand =
            new ModifyItemCommand(item,newItem,pSceneSheet[nActiveSheetIndex],"");
    undoStack->push(modifycommand);
    this->ResetPic(newItem);
    //newItem->setZValue(zValue); //�������ÿؼ���ť�Ĳ��
   //����������ϵĶԻ����ڻ����е��ȷ����ť��ı䱣�水ť����ɫ
 //   pwnd->is_Save=false;// ����ı� ͬʱ���ı䱣�水ť����ɫ
 //   pwnd->ui->action_save->setDisabled(false);
}

/*void MainWindow::OnModifyPieDlg(QGraphicsItem *item)
{
    QPieFramDlg *pPie=new QPieFramDlg(item,this);
    if(pPie->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pPie->pGeneralDlg->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    pPie->deleteLater();
    pPie = NULL;
}*/

QString MainWindow::GetControlNO(QString sName) //��ÿؼ����±��
{
    int i = 0;
    int j = 0;
    QList<QGraphicsItem *> Items;
    QStringList sList;
    QVector <int>ID;
    int nVal = 0;
    QString str = "";
    int Length = 0;

    sList.clear();
    Length = sName.length();               //��ſ�ʼ������
    int totalSceneNum = pSceneSheet.size();
    for(i = 0; i < totalSceneNum; i++) //ɨ�����л���
    {
        Items = pSceneSheet[i]->items();   //��ǰҳ�����е�item
        for(j = 0; j < Items.size(); j++)
        {
            sList = Items.at(j)->topLevelItem()->data(GROUP_DATALIST_KEY).toStringList(); //ȡ��ÿ��item����������
            if(sList.size() < 20)//if(sList.empty() && sList.size() < 20)
                continue;//break;
            str = sList.at(19);           //��Ŵ���15λ
            if(sName == str.left(str.length()-4))//if(sName == str.left(Length)) //��ſ�ʼ����ͬ
            {
                nVal = str.right(str.length() - Length).toInt();
                ID.append(nVal);
            }
        }
    }

    nVal = 0;
    for(i = 0; i < ID.size();)
    {
        if(nVal == ID.at(i))
        {
            nVal++;
            i = 0;
        }
        else
            i++;
    }

    str = QString("%1").arg(nVal);
    while(str.length() < 4)
    {
        str = tr("0")+str;
    }
    sName = sName+str;
    return sName;
}
void MainWindow::newscreen_open()
{
    pwnd->is_Save=false;//
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ

    pView->setScene(pSceneSheet[nActiveSheetIndex]);

    QString strDest;
    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);
    /*pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).
                         arg(pwnd->newpro->newprowizard_name).
                         arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));*/

}//

void MainWindow::newscreen_delete()
{
    //QTreeWidgetItem *parentItem=tree->currentItem()->parent();
    QTreeWidgetItem *parentItem=tree0->currentItem()->parent();
    if(parentItem==copyScreen_Item||parentItem==screen)//��������ǻ����һ���˵�ʱ
    {
        QString selectNum = tree0->currentItem()->text(0);
        //int selectNum = tree0->currentItem()->parent()->indexOfChild(tree0->currentItem());
        if(selectNum.split(":").at(1) == m_pSamSysParame->m_mixGlobalVar.m_sInitNum)
        {
            //m_pSamSysParame->m_mixGlobalVar.m_nInitNum = -1;
            m_pSamSysParame->m_mixGlobalVar.m_sInitNum = "";
        }
        //else if(selectNum < m_pSamSysParame->m_mixGlobalVar.m_nInitNum)
        //{
        //    m_pSamSysParame->m_mixGlobalVar.m_nInitNum -= 1;
        //}

        if(parentItem->childCount()==1)
        {
            QMessageBox box(QMessageBox::Information,tr("��ʾ"),tr("���һ�����治����ɾ��"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("��"));
            box.exec();
            return;
        }
    }
    pwnd->is_Save=false;//
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
    //���滭��ɾ��ʱ��һЩ��Ϣ��������������������
    SamDrawScene* pSceneTemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex];
    int iActiveSheetIndex = pwnd->nActiveSheetIndex;
    int iTreeIndex = pwnd->screen->indexOfChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);
    emit deleteScreen();
    upDatetreeScreenItem();//���»��������
    updateChScreen();
    undoStack->push(new DeleteSceneCommand(pSceneTemp, iActiveSheetIndex, iTreeIndex));
}

void MainWindow::newswindow_open()
{
    pwnd->is_Save=false;//
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ

    pView->setScene(pSceneSheet[nActiveSheetIndex]);
    QString strDest;
    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);
    /*pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                         arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));*/
}//

void MainWindow::newswindow_delete()//
{
    pwnd->is_Save=false;//
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ

    SamDrawScene* pSceneTemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex];
    int iActiveSheetIndex = pwnd->nActiveSheetIndex;
    int iTreeIndex = pwnd->window->indexOfChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);
    emit deleteWindow();
    upDatetreeScreenItem();//���»��������
    updateChScreen();
    undoStack->push(new DeleteWindowCommand(pSceneTemp, iActiveSheetIndex, iTreeIndex));
}

void MainWindow::newscreen_property()
{
    QString strDest;
    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);
    //pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                         //arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
    emit InitScreenPropertyDlg();
    is_ScreenProperty_Name=true;
    //newScreenDlg->setWindowTitle(tr("��������"));
    int res= newScreenDlg->exec();
    if(res==QDialog::Accepted)
    {
        pwnd->reScreenorwindowName(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName,newScreenDlg->ui->newscreen_name_lineedit->text());
        pwnd->is_Save=false;//
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
        //1-199  0λ���½����������
        emit screenProperty_assign();
        upDatetreeScreenItem();//���»��������
        PreviewWindow();
    }

    updateChScreen();
}//

void MainWindow::newswindow_property()
{
    QString strDest;
    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);
    //pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                         //arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
    newWindowDlg->ui->spinBox_w->setRange(0,m_pSamSysParame->m_projectProp.nSceneWidth);
    newWindowDlg->ui->spinBox_h->setRange(0,m_pSamSysParame->m_projectProp.nSceneHeight);
    emit InitWindowPropertyDlg();
    is_WindowProperty_Name=true;
    int res=newWindowDlg->exec();
    if(res==QDialog::Accepted)
    {
        pwnd->reScreenorwindowName(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName,newWindowDlg->ui->lineEdit_name->text());
        pwnd->is_Save=false;
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
        emit windowProperty_assign();
        upDatetreeScreenItem();//���»��������
        PreviewWindow();
    }
    updateChScreen();
}

void MainWindow::newscreen_copy()//���ƻ���
{
   newCopyScreen->ui->lineEdit->setText("");
   int res=newCopyScreen->exec();
   if(res==QDialog::Accepted)
   {
       pwnd->is_Save=false;
       is_NeedCompiled = true;
       pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
       emit copyScreen();
       upDatetreeScreenItem();//���»��������
       PreviewWindow();

       //tree->collapseAll();
       //tree->expandAll();
       tree0->collapseAll();
       tree0->expandAll();

       QString sTmp=pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(1);
       updateChScreen();

       //list_style
       //if(pwnd->list_style->currentIndex()==0||pwnd->list_style->currentIndex()==1)
       if(1)
       {
           pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(pwnd->nActiveSheetIndex));
           pwnd->tree0->setFocus(Qt::MouseFocusReason);
           for(int j=0;j<pwnd->copyScreen_Item->childCount();j++)
           {
               QString sNo=pwnd->copyScreen_Item->child(j)->text(0).split(":").at(1);
               if(sTmp==sNo)
               {
                   pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(j),0,QItemSelectionModel::SelectCurrent);
                   pwnd->tree0->setFocus(Qt::ActiveWindowFocusReason);
               }
           }//
       }
       /*else
       {
           pwnd->tree->setCurrentItem(pwnd->newScreen[pwnd->nActiveSheetIndex]);
           pwnd->tree->setFocus(Qt::MouseFocusReason);

           pwnd->tree->setCurrentItem(pwnd->newScreen[pwnd->nActiveSheetIndex],0,QItemSelectionModel::SelectCurrent);
           pwnd->tree->setFocus(Qt::ActiveWindowFocusReason);
       }*/
       SamDrawScene* pSceneTemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex];
       int iActiveSheetIndex = pwnd->nActiveSheetIndex;
       int iTreeIndex = pwnd->screen->indexOfChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);
       undoStack->push(new AddSceneCommand(pSceneTemp, iActiveSheetIndex, iTreeIndex));
     }
}

void MainWindow::newswindow_copy()
{
    newCopyWindow->ui->lineEdit->setText("");
    newCopyWindow->ui->lineEdit->setFocus(Qt::ActiveWindowFocusReason);
    int res=newCopyWindow->exec();
    if(res==QDialog::Accepted)
    {
        pwnd->is_Save=false;//
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//���򿪹���ʱ�ı䱣�水ť����ɫ
        //1-199  0λ���½����������
        emit copyWindow();
        upDatetreeScreenItem();//���»��������
        PreviewWindow();
        QString sTmp=pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(1);
        updateChScreen();

        //list_style
        if(1)
        //if(pwnd->list_style->currentIndex()==0||pwnd->list_style->currentIndex()==1)
        {
           //pwnd->tree->setCurrentItem(pwnd->copyWindow_Item->child(pwnd->nActiveSheetIndex));
           //pwnd->tree->setFocus(Qt::MouseFocusReason);
           pwnd->tree0->setCurrentItem(pwnd->copyWindow_Item->child(pwnd->nActiveSheetIndex));
           pwnd->tree0->setFocus(Qt::MouseFocusReason);
           for(int j=0;j<pwnd->copyWindow_Item->childCount();j++)
           {
                QString  sNo=pwnd->copyWindow_Item->child(j)->text(0).split(":").at(1);
                if(sTmp==sNo)
                {
                    //pwnd->tree->setCurrentItem(pwnd->copyWindow_Item->child(j),0,QItemSelectionModel::SelectCurrent);
                    //pwnd->tree->setFocus(Qt::ActiveWindowFocusReason);
                    pwnd->tree0->setCurrentItem(pwnd->copyWindow_Item->child(j),0,QItemSelectionModel::SelectCurrent);
                    pwnd->tree0->setFocus(Qt::ActiveWindowFocusReason);
                }
           }//
        }
        /*else
        {
           pwnd->tree->setCurrentItem(pwnd->newScreen[pwnd->nActiveSheetIndex]);
           pwnd->tree->setFocus(Qt::MouseFocusReason);

           pwnd->tree->setCurrentItem(pwnd->newScreen[pwnd->nActiveSheetIndex],0,QItemSelectionModel::SelectCurrent);
           pwnd->tree->setFocus(Qt::ActiveWindowFocusReason);
        }*/
        //list_style
        //pwnd->listChange(pwnd->list_style->currentIndex());
        SamDrawScene* pSceneTemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex];
        int iActiveSheetIndex = pwnd->nActiveSheetIndex;
        int iTreeIndex = pwnd->window->indexOfChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);
        undoStack->push(new AddWindowCommand(pSceneTemp, iActiveSheetIndex, iTreeIndex));
     }
}

void MainWindow::openInit_MenuAndTool()//����򿪰�ť��ʼ���˵��͹�����
{
    //��ʱ��ʼ���˵��͹�����
    ///�ļ��˵�
    ui->action_new_screen->setDisabled(is_Is);
    ui->action_close->setDisabled(is_Is);
    ui->action_save->setDisabled(is_Is);
    ui->action_save_as->setDisabled(is_Is);
    //�༭
    ui->action_cut->setDisabled(is_Is);
    ui->action_copy->setDisabled(is_Is);
    ui->action_copym->setDisabled(is_Is);
    ui->action_paste->setDisabled(is_Is);
    ui->action_delete->setDisabled(is_Is);
    ui->action_checkall->setDisabled(is_Is);
    ui->action_panview->setDisabled(is_Is);
    ui->action_grid->setDisabled(is_Is);
    ui->action_frame_mark->setDisabled(is_Is);
    ui->action_upscreen->setDisabled(is_Is);
    ui->action_nextscreen->setDisabled(is_Is);
    ui->action_open_proprerty->setDisabled(is_Is);
    //ui->action_addresslookup->setDisabled(is_Is);
    //ui->action_address_preview->setDisabled(is_Is);
    ui->action_macro_find->setDisabled(is_Is);
    ui->action_macro_admin->setDisabled(is_Is);

    //��ͼ
    ui->action_line->setDisabled(is_Is);
    ui->action_foldline->setDisabled(is_Is);
    ui->action_blight_circle->setDisabled(is_Is);
    ui->action_freeline->setDisabled(is_Is);
    ui->action_line_link->setDisabled(is_Is);
    ui->action_blight_link->setDisabled(is_Is);
    ui->action_rect->setDisabled(is_Is);
    ui->action_ellipse->setDisabled(is_Is);
    ui->action_polygon->setDisabled(is_Is);
    ui->action_text->setDisabled(is_Is);
   // ui->action_open_mapstorage->setDisabled(is_Is);
   // ui->action_create_map_storage->setDisabled(is_Is);
    //ui->action_stateon->setDisabled(is_Is);
    //ui->action_state0->setDisabled(is_Is);
    ui->action_table->setDisabled(is_Is);
    ui->action_mark->setDisabled(is_Is);

    //=========================
    ui->action_tool->setDisabled(is_Is);

    //���
    //ui->action_opera_record->setDisabled(is_Is);
    ui->action_bitbutton->setDisabled(is_Is);
    ui->action_MFbtn->setDisabled(is_Is);
    //ui->action_word_button->setDisabled(is_Is);
    //ui->action_picture_button->setDisabled(is_Is);
    //ui->action_function_button->setDisabled(is_Is);
    //ui->action_bit_indicatorlight->setDisabled(is_Is);
    //ui->action_multi_indicatorlight->setDisabled(is_Is);
    //ui->action_staticpicture->setDisabled(is_Is);
    //ui->action_pictureoutput->setDisabled(is_Is);
    ui->action_GIFoutput->setDisabled(is_Is);
    ui->action_trendchart->setDisabled(is_Is);
    //ui->action_XYtrend->setDisabled(is_Is);
    ui->action_dynamiccircle->setDisabled(is_Is);
    ui->action_dynamicrect->setDisabled(is_Is);
    ui->action_arlamcontrol->setDisabled(is_Is);
    ui->action_dynamicarlarm->setDisabled(is_Is);
    ui->action_histotyarlarm->setDisabled(is_Is);
    //ui->action_picturemove->setDisabled(is_Is);
    ui->action_chart->setDisabled(is_Is);//add by czh for chart
    ui->action_value->setDisabled(is_Is);//add by czh for chart
    ui->action_image->setDisabled(is_Is);
    //ui->action_multistate->setDisabled(is_Is);
    ui->action_historyrecord->setDisabled(is_Is);
    ui->action_messagedisplay->setDisabled(is_Is);
    //ui->action_mfaction->setDisabled(is_Is);
    ui->action_flow_block->setDisabled(is_Is);
    //ui->action_his_tre_display->setDisabled(is_Is);
    //ui->action_timer->setDisabled(is_Is);
    //ui->action_Pie->setDisabled(is_Is);
    //ui->action_Steping->setDisabled(is_Is);
    ui->dataplay->setDisabled(is_Is);
    ui->pictruedisplay->setDisabled(is_Is);
    ui->graphicsitem->setDisabled(is_Is);

    //---------ui->action_space->setDisabled(is_Is);
    if(pMenuSpace == NULL)
    {
        pMenuSpace = new QMenu(tr("���"), /*ui->standardToolBar*/ui->mapToolBar);
        pMenuSpace->setIcon(QIcon(":/standardtool/images/standardtool/makesamewihi.ico"));

        QAction *widthsame  = pMenuSpace->addAction(tr("�����ͬ"));
        QAction *heightsame = pMenuSpace->addAction(tr("�߶���ͬ"));
        QAction *widthheight= pMenuSpace->addAction(tr("��ȸ߶ȶ���ͬ"));
        QAction *horizontal = pMenuSpace->addAction(tr("ˮƽ�ȼ��"));
        QAction *vertical   = pMenuSpace->addAction(tr("��ֱ�ȼ��"));

        widthsame->setIcon(QIcon(":/standardtool/images/standardtool/makesamewidth.ico"));
        heightsame->setIcon(QIcon(":/standardtool/images/standardtool/makesameheight.ico"));
        widthheight->setIcon(QIcon(":/standardtool/images/standardtool/makesamewihi.ico"));
        horizontal->setIcon(QIcon(":/standardtool/images/standardtool/horizontal.ico"));
        vertical->setIcon(QIcon(":/standardtool/images/standardtool/vertical.ico"));

        connect(widthsame,SIGNAL(triggered()),SLOT(onWidthSame()));
        connect(heightsame,SIGNAL(triggered()),SLOT(onHeightSame()));
        connect(widthheight,SIGNAL(triggered()),SLOT(onWidthHeightSame()));
        connect(horizontal,SIGNAL(triggered()),SLOT(OnSetHSpacingAlign()));
        connect(vertical,SIGNAL(triggered()),SLOT(OnSetVSpacingAlign()));

        QAction *ActionSpace = pMenuSpace->menuAction();
        ActionSpace->setIconText(tr("\n���"));
        connect(ActionSpace,SIGNAL(triggered()),SLOT(onWidthHeightSame()));

        pMenuSpace->setDisabled(is_Is);

        //menu.exec(QCursor::pos());
        //ui->standardToolBar->addAction(pMenuSpace->menuAction());
        /*ui->standardToolBar*/ui->mapToolBar->insertAction(ui->action_v, pMenuSpace->menuAction());
        //ui->standardToolBar->insertSeparator(ui->action_v);
    }
    else
    {
        pMenuSpace->setDisabled(is_Is);
    }
    ui->action_horizontal->setDisabled(is_Is);
    ui->action_vertcal->setDisabled(is_Is);
    ui->action_widthsame->setDisabled(is_Is);
    ui->action_heightsame->setDisabled(is_Is);
    ui->action_widthheightsame->setDisabled(is_Is);

    //-----ui->action_Align->setDisabled(is_Is);
    if(pMenuAlign == NULL)
    {
        pMenuAlign = new QMenu(tr("����"), /*ui->standardToolBar*/ui->mapToolBar);
        pMenuAlign->setIcon(QIcon(":/standardtool/images/standardtool/leftalign.ico"));

        QAction *alignLeft   = pMenuAlign->addAction(tr("�����"));
        QAction *alignRight  = pMenuAlign->addAction(tr("�Ҷ���"));
        QAction *alignTop    = pMenuAlign->addAction(tr("�϶���"));
        QAction *alignUnder  = pMenuAlign->addAction(tr("�¶���"));
        QAction *alignHcenter= pMenuAlign->addAction(tr("ˮƽ����"));
        QAction *alignVcenter= pMenuAlign->addAction(tr("��ֱ����"));

        alignLeft->setIcon(QIcon(":/standardtool/images/standardtool/leftalign.ico"));
        alignRight->setIcon(QIcon(":/standardtool/images/standardtool/rightalign.ico"));
        alignTop->setIcon(QIcon(":/standardtool/images/standardtool/topalign.ico"));
        alignUnder->setIcon(QIcon(":/standardtool/images/standardtool/bottomalign.ico"));
        alignHcenter->setIcon(QIcon(":/standardtool/images/standardtool/horcenalign.ico"));
        alignVcenter->setIcon(QIcon(":/standardtool/images/standardtool/vercenalign.ico"));

        connect(alignLeft,SIGNAL(triggered()),SLOT(OnSetLeft()));
        connect(alignRight,SIGNAL(triggered()),SLOT(OnSetRight()));
        connect(alignTop,SIGNAL(triggered()),SLOT(OnSetTop()));
        connect(alignUnder,SIGNAL(triggered()),SLOT(OnSetButtom()));
        connect(alignHcenter,SIGNAL(triggered()),SLOT(OnSetHCenter()));
        connect(alignVcenter,SIGNAL(triggered()),SLOT(OnSetVCenter()));

        QAction *ActionAlign = pMenuAlign->menuAction();
        ActionAlign->setIconText(tr("\n����"));
        connect(ActionAlign,SIGNAL(triggered()),SLOT(OnSetLeft()));

        pMenuAlign->setDisabled(is_Is);

        /*ui->standardToolBar*/ui->mapToolBar->insertAction(pMenuSpace->menuAction(), pMenuAlign->menuAction());
        //ui->standardToolBar->insertSeparator(pMenuSpace->menuAction());
        //connect(pMenuAlign,SIGNAL(triggered(QAction *)),alignLeft,SIGNAL(triggered()));
        //pMenuAlign->setActiveAction(alignLeft);
    }
    else
    {
        pMenuAlign->setDisabled(is_Is);
    }
    ui->action_top->setDisabled(is_Is);
    ui->action_under->setDisabled(is_Is);
    ui->action_vcenter->setDisabled(is_Is);
    ui->action_left->setDisabled(is_Is);
    ui->action_right->setDisabled(is_Is);
    ui->action_hcenter->setDisabled(is_Is);

    //--------ui->action_ZXu->setDisabled(is_Is);
    if(pMenuZXu == NULL)
    {
        pMenuZXu = new QMenu(tr("���"), /*ui->standardToolBar*/ui->mapToolBar);
        pMenuZXu->setIcon(QIcon(":/standardtool/images/standardtool/bringtotop.ico"));

        QAction *Z_first    = pMenuZXu->addAction(tr("�Ƶ����ϲ�"));
        QAction *Z_last     = pMenuZXu->addAction(tr("�Ƶ����²�"));
        QAction *Z_before   = pMenuZXu->addAction(tr("�Ƶ���һ��"));
        QAction *Z_next     = pMenuZXu->addAction(tr("�Ƶ���һ��"));

        Z_first->setIcon(QIcon(":/standardtool/images/standardtool/bringtotop.ico"));
        Z_last->setIcon(QIcon(":/standardtool/images/standardtool/sendtobottom.ico"));
        Z_before->setIcon(QIcon(":/standardtool/images/standardtool/bringforward.ico"));
        Z_next->setIcon(QIcon(":/standardtool/images/standardtool/bringbackward.ico"));

        connect(Z_first,SIGNAL(triggered()),SLOT(on_action_bringtop_triggered()));
        connect(Z_last,SIGNAL(triggered()),SLOT(on_action_sengtoback_triggered()));
        connect(Z_before,SIGNAL(triggered()),SLOT(on_action_bringforward_triggered()));
        connect(Z_next,SIGNAL(triggered()),SLOT(on_action_bringback_triggered()));

        QAction *ActionZXu = pMenuZXu->menuAction();
        ActionZXu->setIconText(tr("\n���"));
        connect(ActionZXu,SIGNAL(triggered()),SLOT(on_action_bringtop_triggered()));

        pMenuZXu->setDisabled(is_Is);

        //menu.exec(QCursor::pos());
        /*ui->standardToolBar*/ui->mapToolBar->insertAction(ui->action_v, pMenuZXu->menuAction());
        //ui->standardToolBar->insertSeparator(ui->action_group);
    }
    else
    {
        pMenuZXu->setDisabled(is_Is);
    }
    ui->action_bringtop->setDisabled(is_Is);
    ui->action_bringforward->setDisabled(is_Is);
    ui->action_sengtoback->setDisabled(is_Is);
    ui->action_bringback->setDisabled(is_Is);

    //ui->action_free->setDisabled(is_Is);
    ui->action_group->setDisabled(is_Is);
    ui->action_split->setDisabled(is_Is);
    ui->action_zoonbig->setDisabled(is_Is);
    ui->action_zoonfit->setDisabled(is_Is);
    ui->action_zoonsmall->setDisabled(is_Is);
    ui->action_h->setDisabled(is_Is);
    ui->action_v->setDisabled(is_Is);
    ui->action_lock->setDisabled(is_Is);
    ui->action_delock->setDisabled(is_Is);
    ui->action_address_find->setDisabled(is_Is);
    ui->action_address_table->setDisabled(is_Is);
    ui->action_openpropertiset->setDisabled(is_Is);
    statusButtoncmb->setDisabled(is_Is);
    pChScreen->setDisabled(is_Is);
    qLanguagecmb->setDisabled(is_Is);

    ui->action_Animation->setDisabled(is_Is);
    //ui->action_MsgBoard->setDisabled(is_Is);
    ui->action_Keyboard->setDisabled(is_Is);
    ui->action_messageboard->setDisabled(is_Is);
    ui->actionRecipeChoice->setDisabled(is_Is);
    ui->action_recipetable->setDisabled(is_Is);
    //����

    ui->action_RoundedRect->setDisabled(is_Is);
    ui->action_ArcItem->setDisabled(is_Is);
    //�趨
    ui->action_P->setDisabled(is_Is);
    ui->action_R_2->setDisabled(is_Is);
    ui->action_M->setDisabled(is_Is);

    ui->action_offline_simulation->setDisabled(is_Is);
    //ui->action_online_simulation->setDisabled(is_Is);
    ui->action_USBdownload->setDisabled(is_Is);
    ui->action_compile->setDisabled(is_Is);
    ui->action_USBdownload->setDisabled(is_Is);
    ui->action_compile_download->setDisabled(is_Is);

    ui->action_arrow->setDisabled(is_Is);
    //ui->action_singleselect->setDisabled(is_Is);
    ui->action_ComboBox->setDisabled(is_Is);
    ui->action_Slider->setDisabled(is_Is);
    ui->action_DatagroupDisplay->setDisabled(is_Is);
    //tree->collapseAll();
    ui->action_User_Keybaor->setDisabled(is_Is);//����û��Զ������
    ui->action_datasamp->setDisabled(is_Is);//������ݲɼ�
    ui->action_waring->setDisabled(is_Is);//��ӱ���
    ui->action_rep->setDisabled(is_Is);//����䷽
    ui->action_script->setDisabled(is_Is);//�򿪽ű������

    ui->action_reverse_selection->setDisabled(is_Is);//����ѡ��
    //ui->action_ComboBox->setEnabled(false);
    ui->action_split->setEnabled(false);
   // ui->action_h->setEnabled(false);
   // ui->action_v->setEnabled(false);
    //ui->dockWidget->setVisible(!is_Is);
    m_toolDock->setVisible(!is_Is);
}


//��Ϣ������ڵĵ���¼�
void MainWindow::on_action_information_output_triggered()
{
 if(m_rightDock->isVisible())
 {
     m_rightDock->hide();
 }
 else
 {
     m_rightDock->setVisible(true);
 }
}

//���̹������ĵ���¼�
void MainWindow::on_action_project_manager_triggered()
{
    if(m_leftDock->isVisible())
    {
        m_leftDock->hide();
    }
    else
    {
        m_leftDock->setVisible(true);
    }
}

//���⡢��Ի���
void MainWindow::on_action_save_as_triggered()
{
     QFileDialog saveFileDlg(this);
     QString str=saveFileDlg.getSaveFileName(
             this,
             tr("Save As"),
             tr("C:/Documents and Settings/Administrator/����"),
             tr(VERSION_NAME" "AK_FILE_END),
             0,
             0//QFileDialog::DontUseNativeDialog | QFileDialog::DontResolveSymlinks | QFileDialog::DontUseSheet
             );
     /*ShowDirsOnly          = 0x00000001,
     DontResolveSymlinks   = 0x00000002,
     DontConfirmOverwrite  = 0x00000004,
     DontUseSheet          = 0x00000008,
     DontUseNativeDialog   = 0x00000010,
     ReadOnly              = 0x00000020,
     HideNameFilterDetails = 0x00000040*/
        saveAs_Name=str;
        if(saveAs_Name=="")
        {
            return;
        }
        else
        {
            is_SaveAS=true;
            is_OpenrecentFile=false;
            is_click_open=false;
            createsavedlg();
        }
}//

void MainWindow::onFrmStatecmbChange(int nIndex)//�������ϵ�״̬������edit by zqh
{
    int state = nIndex;

    if(nIndex < 0)
    {
        statusButtoncmb->clear();
        //statusButtoncmb->setEnabled(false);
        return;
    }

    QList<QGraphicsItem *> Items;
    Items = pSceneSheet[nActiveSheetIndex]->items();
    int sz = Items.size();
    if(Items.size() == 0)
    {
        return;
    }
    int statuNum = statusButtoncmb->count();
    if(statuNum <= state)
    {
        state = 0;
    }
    statusButtoncmb->setCurrentIndex(state);

    QGraphicsItem* pItem;
    QItemGroup* item;
    for(int i = 0; i < sz; i++)
    {
        pItem = Items.at(i);
        if(!pItem)
        {
            continue;
        }

        if(SAM_DRAW_OBJECT_GROUP == pItem->type())
        {
            if(pItem->parentItem() == 0 && pItem->type() != SAM_DRAW_OBJECT_TRACKER && pItem->type() != SAM_DRAW_OBJECT_LOCK)
            {
                item  = dynamic_cast<QItemGroup*>(pItem);
                item->redrawForChangeStatus(state, qLanguagecmb->currentIndex());
            }
        }
    }
    pSceneSheet[nActiveSheetIndex]->update();

    /*QList<QGraphicsItem *> Items;
    Items = pSceneSheet[nActiveSheetIndex]->selectedItems();
    if(Items.size() != 1)//ѡ��������û��ѡ���ʱ�򷵻�
    {
        statusButtoncmb->clear();
        statusButtoncmb->setEnabled(false);
        return;
    }

    QGraphicsItem* pItem = Items.at(0);
    QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
    qDebug() << "XXXXXXXXXXXXX" << item->GroupType();

    int statuNum = statusButtoncmb->count();
    //if(state < 0)
    //{
    //    state = item->getCurrentState();
    //}
    if(statuNum <= state)
    {
        state = 0;
    }
    statusButtoncmb->setCurrentIndex(state);

    item->redrawForChangeStatus(state, qLanguagecmb->currentIndex());*/
}

/***********************************************************************
 *�������ƣ�SetMultiStateText
 *�������ܣ����ö��״̬�ؼ����ı���Ϣ
 *�������壺
 *pItem����Ҫ����Ŀؼ�item
 *sList��ÿ���ؼ��Ĵ洢��Ϣ
 *nID���ؼ���keyֵ
 *nIndex����ǰ״ֵ̬
 *nTotal���ܵ�״ֵ̬
 *edit by zqh
 **********************************************************************/
void MainWindow::SetMultiStateText(QGraphicsItem *pItem,QStringList sList,int nID,
                                   int nIndex,int nTotal)
{
    QString sText = "";
    int nVal = 0;
    int nFontSize = 0;
    int nWordInterval = 0;
    int nAlignment = 0;
    QString sColor;
    QString sFont = tr("����");

    QString sBorderColor;
    QString sFrontColor;
    QString sBackColor;
    int nPattern = 0;

    QGroupItem *pBaseItem = new QGroupItem(pItem);
    if(nID == GROUP_TYPE_MSGDISPLAY)//��Ϣ��ʾ
    {
        nVal = 81;

        sBorderColor = sList.at(nVal+nIndex*4);
        sFrontColor = sList.at(nVal+1+nIndex*4);
        sBackColor = sList.at(nVal+2+nIndex*4);
        nPattern = sList.at(nVal+3+nIndex*4).toInt();

        nVal = nVal+nTotal*4;  //4Ϊһ��ҳ���������ɫ��һ����ʽ�ܺ�

        sColor=sList.at(nVal+nIndex*3);
        nWordInterval=0;
        nAlignment=5;

        int nLang = sList.at(79).toInt();
        nVal = nVal+nTotal*3;

        int nLanIndex = qLanguagecmb->currentIndex(); //�������ϵ�ǰ�����±�
        if(nLanIndex < 0)
          nLanIndex = 0;

        nFontSize = sList.at(nVal+nIndex*3*nLang+nLanIndex*3).toInt();
        sText = sList.at(nVal+1+nIndex*3*nLang+nLanIndex*3);
        sFont = sList.at(nVal+2+nIndex*3*nLang+nLanIndex*3);
    }
    else if(nID == GROUP_TYPE_WEEKBTN)//������ʾ
    {
        sBorderColor = sList.at(190+1+nIndex*4);
        sFrontColor = sList.at(190+2+nIndex*4);
        sBackColor = sList.at(190+3+nIndex*4);
        nPattern = sList.at(190+4+nIndex*4).toInt();

        int nLanIndex = qLanguagecmb->currentIndex(); //�������ϵ�ǰ�����±�
        if(nLanIndex < 0)
          nLanIndex = 0;
        nVal = 49+nIndex*15+nLanIndex*3;
        sText = sList.at(nVal);

        nVal = 48+nIndex*15+nLanIndex*3;
        nFontSize = sList.at(nVal).toInt();

        nVal = 50+nIndex*15+nLanIndex*3;
        sFont = sList.at(nVal);

        sColor=sList.at(20+nIndex*4);
        nWordInterval=sList.at(20+1+nIndex*4).toInt();
        nAlignment=sList.at(20+2+nIndex*4).toInt();
    }
    else if(nID == GROUP_TYPE_BITBTN || nID == GROUP_TYPE_BITLAMP) //λ��ť λָʾ��
    {
        int nLang = qLanguagecmb->currentIndex();//sList.at(100).toInt();//��ǰ����
        if(nLang < 0)
         nLang = 0;
        bool bBold,bUnderline,bItalic;
        if(nIndex == 0)
        {
            sText = sList.at(117+nLang);
            sFont = sList.at(127+nLang);
            nFontSize = sList.at(137+nLang).toInt();
            sBorderColor = sList.at(58);
            sFrontColor = sList.at(62);
            sBackColor = sList.at(60);
            nPattern = sList.at(64).toInt();
            sColor = sList.at(101);
            nWordInterval = sList.at(102).toInt();
            nAlignment=sList.at(108).toInt();
            bBold = sList.at(105).toInt();
            bItalic = sList.at(106).toInt();
            bUnderline = sList.at(107).toInt();

        }
        else if(nIndex == 1)
        {
            sText = sList.at(122+nLang);
            sFont = sList.at(132+nLang);
            nFontSize = sList.at(142+nLang).toInt();
            sBorderColor = sList.at(59);
            sFrontColor = sList.at(63);
            sBackColor = sList.at(61);
            nPattern = sList.at(65).toInt();
            sColor = sList.at(109);
            nWordInterval = sList.at(111).toInt();
            nAlignment=sList.at(116).toInt();
            bBold = sList.at(113).toInt();
            bItalic = sList.at(114).toInt();
            bUnderline = sList.at(115).toInt();
        }
        pBaseItem->SetPropertyValue("mText.fontbold",QVariant(bBold));
        pBaseItem->SetPropertyValue("mText.fontitalic",QVariant(bItalic));
        pBaseItem->SetPropertyValue("mText.underline",QVariant(bUnderline));
    }
    else if(nID == GROUP_TYPE_MULSTATELAMP || nID == GROUP_TYPE_MULSTATEBTN
            || GROUP_TYPE_PICTUREMOVE)//��ָ̬ʾ��
    {
        nVal = 101;
        int nLang = sList.at(99).toInt();

        sBorderColor = sList.at(nVal+nIndex*4);
        sFrontColor = sList.at(nVal+1+nIndex*4);
        sBackColor = sList.at(nVal+2+nIndex*4);
        nPattern = sList.at(nVal+3+nIndex*4).toInt();

        nVal = nVal+nTotal*4;  //4Ϊһ��ҳ���������ɫ��һ����ʽ�ܺ�
        sColor = sList.at(nVal+nIndex*3);
        nWordInterval = sList.at(nVal+1+nIndex*3).toInt();
        nAlignment=sList.at(nVal+2+nIndex*3).toInt();

        nVal = nVal+nTotal*3;
        int nLanIndex = qLanguagecmb->currentIndex(); //�������ϵ�ǰ�����±�
        if(nLanIndex < 0)
         nLanIndex = 0;
        nFontSize = sList.at(nVal+nIndex*3*nLang+nLanIndex*3).toInt();
        sText = sList.at(nVal+1+nIndex*3*nLang+nLanIndex*3);
        sFont = sList.at(nVal+2+nIndex*3*nLang+nLanIndex*3);
    }

    pBaseItem->SetPropertyValue("mText.Text",QVariant(sText));       //�����ı�
    pBaseItem->SetPropertyValue("mText.Font",QVariant(sFont));   //��������
    pBaseItem->SetPropertyValue("mText.FontSize",QVariant(nFontSize));    //���������С
    pBaseItem->SetPropertyValue("mText.WordInterval",QVariant(nWordInterval));//�־�
    pBaseItem->SetPropertyValue("mText.Alignment",QVariant(nAlignment));   //���뷽ʽ
    pBaseItem->SetPropertyValue("mText.FontColor",QVariant(sColor));  //������ɫ

    pBaseItem->SetPropertyValue("mFramRect.BackColor",QVariant(sBorderColor));
    pBaseItem->SetPropertyValue("mBackRect.FrontColor",QVariant(sFrontColor));
    pBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(sBackColor));
    pBaseItem->SetPropertyValue("mBackRect.Pattern",QVariant(nPattern));
    if(nPattern == 0)
    {
        pBaseItem->SetPropertyValue("mFramRect.Pattern",QVariant(0));
        pBaseItem->setItemPattern(0);
    }
    else
    {
        pBaseItem->SetPropertyValue("mFramRect.Pattern",QVariant(1));
        pBaseItem->setItemPattern(1);
    }
}

void MainWindow::AddItemToScene()
{
    if (pDrawToSceneItem&&(SamDrawTool::s_eDrawActType == SAM_DRAW_ASSY_COMPONENT))
    {
        this->OnSingClikSpare(pDrawToSceneItem);
    }
    PasteItemToScene();//ճ��ITEM������
}

void MainWindow::OnSingleClickItem()//�����ؼ���QGraphicsItem *pItem edit by zqh
{
    //return;
    int nID = 0;
    QStringList sList;
    //int nCurrentState = 0;   //��ǰ״ֵ̬
    //int i = 0;
    //int nTotal = 0;
    QList<QGraphicsItem *> Items;
    QGraphicsItem *pItem;

    bToolBarCMBInit = false;
    Items = pSceneSheet[nActiveSheetIndex]->selectedItems();

    ////if(qLanguagecmb->count() > 0)
    ////    qLanguagecmb->setCurrentIndex(0);

    if(Items.size() != 1) //ѡ��������û��ѡ���ʱ�򷵻�
    {
        //statusButtoncmb->clear();
        //statusButtoncmb->setEnabled(false);
        ui->action_h->setEnabled(false);
        ui->action_v->setEnabled(false);
        ui->action_split->setEnabled(false);
        pwnd->ui->action_copym->setDisabled(true);//���ظ���ֻ�ڳ���ѡ�񵥸�����Ч
        lab_up_space_statusBar->setEnabled(false);
        lab_left_space_statusBar->setEnabled(false);
        lab_width_space_statusBar->setEnabled(false);
        lab_hidth_space_statusBar->setEnabled(false);
        lab_up_space_statusBar->setText("");
        lab_left_space_statusBar->setText("");
        lab_width_space_statusBar->setText("");
        lab_hidth_space_statusBar->setText("");
        bToolBarCMBInit = true;
        return;
    }
    pwnd->ui->action_copym->setDisabled(false);//���ظ���ֻ�ڳ���ѡ�񵥸�����Ч
    lab_up_space_statusBar->setEnabled(true);
    lab_left_space_statusBar->setEnabled(true);
    lab_width_space_statusBar->setEnabled(true);
    lab_hidth_space_statusBar->setEnabled(true);

    pItem = Items.at(0);
    nID = pItem->data(GROUP_TYPE_KEY).toInt(); //ȡ�ؼ���Key��

    if(nID == USER_DEFINE_GROUP) //���Զ������
    {
        ui->action_split->setEnabled(true);
    }
    else
    {
        ui->action_split->setEnabled(false);
    }

    int nType = pItem->type();
    if(nType == SAM_DRAW_OBJECT_LINE_NEW || nType == SAM_DRAW_OBJECT_FOLDLINE_NEW
       || nType == SAM_DRAW_OBJECT_LINECIRCLE_NEW || nType == SAM_DRAW_OBJECT_FREELINE_NEW
       || nType == SAM_DRAW_OBJECT_RECT_NEW || nType == SAM_DRAW_OBJECT_ELIPSE_NEW
       || nType == SAM_DRAW_OBJECT_POLYGON_NEW || nType == SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)
    {

        ui->action_h->setEnabled(true);
        ui->action_v->setEnabled(true);
    }
    else
    {
        ui->action_h->setEnabled(false);
        ui->action_v->setEnabled(false);
    }

    bToolBarCMBInit = true;

    ToSlectTreeItem(sList);//���������ϵ�Item����Ӧѡ�����οؼ�����
    //setLanguageCmbEnable(pItem);
}


void MainWindow::AddCurrentItemStatusList(QGraphicsItem *pItem, int state)//��״̬������ѡ��
{
    QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);

    if(!pItem)
    {
        return;
    }
    setStatusBarCtrlName(pItem);

    if(pItem->parentItem() == 0 && pItem->type() != SAM_DRAW_OBJECT_TRACKER && pItem->type() != SAM_DRAW_OBJECT_LOCK)
    {
        QStringList list = item->getItemStates();
        if(list.size() == 0)
        {
            return;
        }
        else
        {
            disconnect(statusButtoncmb,SIGNAL(currentIndexChanged(int)),this,SLOT(onFrmStatecmbChange(int)));
            statusButtoncmb->setEnabled(true);
            statusButtoncmb->addItems(list);
            connect(statusButtoncmb,SIGNAL(currentIndexChanged(int)),this,SLOT(onFrmStatecmbChange(int)));

            statusButtoncmb->setCurrentIndex(state);
        }
    }
}

/***************************************************************
 *�������ƣ�setStatusBarCtrlName
 *�������ܣ����ĳ���ؼ�ʱ������״̬���϶�Ӧ�ؼ�����
 *�������壺
 *pItem��     �����õİ�ťָ��
 *����ֵ:       NULL
 *�༭���ߣ�֣����
 *�༭���ڣ�2012.9.18
 **************************************************************/
void MainWindow::setStatusBarCtrlName(QGraphicsItem *pItem)
{
    QString sCtrlName = "";
    QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
    switch(item->GroupType())
    {
    case SAM_DRAW_GROUP_MESSAGE:    sCtrlName = tr("��Ϣ��ʾ��");break;//35,��Ϣ��ʾ��
    case SAM_DRAW_GROUP_HISTORYDATE:    sCtrlName = tr("��ʷ������ʾ��");break;//32,��ʷ������ʾ��
    case SAM_DRAW_GROUP_SWITCH: sCtrlName = tr("����");break;//10,��������
    case SAM_DRAW_GROUP_CHART:  sCtrlName = tr("ͼ��");break;//11,ͼ��
    case SAM_DRAW_GROUP_VALUE:  sCtrlName = tr("��ֵ��ʾ");break;//12,��ֵ��ʾ
    case SAM_DRAW_GROUP_IMAGE:  sCtrlName = tr("ͼƬ��ʾ");break;//15,ͼƬ��ʾ
    case SAM_DRAW_GROUP_ASCII:  sCtrlName = tr("ASCII��ʾ");break;//16,ascii��ʾ
    case SAM_DRAW_GROUP_TIME:   sCtrlName = tr("ʱ����ʾ");break;//17,ʱ����ʾ
    case SAM_DRAW_GROUP_ALARMITEM:  sCtrlName = tr("������ʾ��");break;//18,������ʾ�ؼ�
    case SAM_DRAW_GROUP_ALARMBAR:   sCtrlName = tr("��̬������");break;//19,��̬������
    case SAM_DRAW_GROUP_HISALARMITEM:   sCtrlName = tr("��ʷ������ʾ��");break;//20,��ʷ������ʾ�ؼ�
    case SAM_DRAW_GROUP_FLOW:   sCtrlName = tr("������");break;//21,������
    case SAM_DRAW_GROUP_ANIMATION:  sCtrlName = tr("����");break;//22,����
    case SAM_DRAW_GROUP_KEY:    sCtrlName = tr("�������");break;//23,�������
    case SAM_DRAW_GROUP_STATICTEXT: sCtrlName = tr("��̬�ı�");break;//28,��̬�ı�
    case SAM_DRAW_GROUP_RECIPE: sCtrlName = tr("�䷽ѡ����");break;//29,�䷽ѡ����
    case SAM_DRAW_GROUP_RECIPESHOW: sCtrlName = tr("�䷽��ʾ��");break;//30,�䷽��ʾ��
    case SAM_DRAW_GROUP_CALIBRATION:    sCtrlName = tr("�̶�");break;//31,�̶�
    case SAM_DRAW_GROUP_SLIDER: sCtrlName = tr("������");break;//33,������/������
    case SAM_DRAW_GROUP_STATICPIC:  sCtrlName = tr("GIF��ʾ��");break;//34,GIF��ʾ��
    case SAM_DRAW_GROUP_TREND:  sCtrlName = tr("����ͼ");break;//13,����ͼ
    case SAM_DRAW_GROUP_GROUPDATA:  sCtrlName = tr("����Ⱥ��");break;//14,����Ⱥ��
    case SAM_DRAW_GROUP_DROPDOWN:   sCtrlName = tr("������");break;//27,������
    case SAM_DRAW_GROUP_DYNRECT:    sCtrlName = tr("��̬����");break;//24,��̬����
    case SAM_DRAW_GROUP_DYNCIRCLE:  sCtrlName = tr("��̬Բ");break;//25,��̬Բ
    case SAM_DRAW_GROUP_TABLE:  sCtrlName = tr("���");break;//���
    case SAM_DRAW_GROUP_TEXTBOARD:  sCtrlName = tr("���԰�");break;//���԰�
    case SAM_DRAW_GROUP_COMBOBOX: sCtrlName = tr("������");break;//
    case SAM_DRAW_GROUP_XYTREND:  sCtrlName = tr("X-Y����");break;//X-Y����
    default:sCtrlName = tr("");break;
    }
   pwnd->lab_control_statusBar->setText(sCtrlName);
}

void MainWindow::ToSlectTreeItem(QStringList sList)
 {
    QString sTmp="";
    QString sNo="";

    return;

    /*if(sList.size() > 20)//if(!sList.isEmpty())
    {
         sTmp = sList.at(19);
         for(int j=0;j<copyScreen_Item->childCount();j++)
         {
             for(int i=0;i<copyScreen_Item->child(j)->childCount();i++)
             {
                 sNo=copyScreen_Item->child(j)->child(i)->text(0);
                 if(sTmp==sNo)
                 {
                     //list_style
                     tree->setCurrentItem(copyScreen_Item->child(j),0,QItemSelectionModel::SelectCurrent);
                     //if(pwnd->list_style->currentIndex()==0)
                     //{
                     //    tree->setCurrentItem(copyScreen_Item->child(j),0,QItemSelectionModel::SelectCurrent);
                     //}
                     //else  if(pwnd->list_style->currentIndex()==1)
                     //{
                     //    tree->setCurrentItem(copyScreen_Item->child(j)->child(i),0,QItemSelectionModel::SelectCurrent);
                     //}
                 }
             }
         }//
         for(int j=0;j<copyWindow_Item->childCount();j++)
         {
             for(int i=0;i<copyWindow_Item->child(j)->childCount();i++)
             {
                 sNo=copyWindow_Item->child(j)->child(i)->text(0);
                 if(sTmp==sNo)
                 {
                     //list_style
                     tree->setCurrentItem(copyWindow_Item->child(j),0,QItemSelectionModel::SelectCurrent);
                      //if(pwnd->list_style->currentIndex()==0)
                      //{
                      //    tree->setCurrentItem(copyWindow_Item->child(j),0,QItemSelectionModel::SelectCurrent);
                      //}
                      //else  if(pwnd->list_style->currentIndex()==1)
                      //{
                      //         tree->setCurrentItem(copyWindow_Item->child(j)->child(i),0,QItemSelectionModel::SelectCurrent);
                      //}
                }
            }
        }//
        for(int j=0;j<copyUserKeyboard->childCount();j++)
        {
            for(int i=0;i<copyUserKeyboard->child(j)->childCount();i++)
            {
                sNo=copyUserKeyboard->child(j)->child(i)->text(0);
                if(sTmp==sNo)
                {
                    tree->setCurrentItem(copyUserKeyboard->child(j)->child(i),0,QItemSelectionModel::SelectCurrent);
                    // tree->setFocus(Qt::ActiveWindowFocusReason);
                }
            }
        }//
    }*/
 }

void MainWindow::OnSetZoomEnlarge()//�Ŵ����edit by zqh
{
    nZoomNumber+=25; //ÿ�����ż�25
    if(nZoomNumber > 300) //����ֵ���ڵ�ʱ�򲻴���
    {
        nZoomNumber = 300;
        return;
    }

    double newScale = nZoomNumber / 100.0;
    QMatrix oldMatrix = pView->matrix();
    pView->resetMatrix();
    pView->translate(oldMatrix.dx(), oldMatrix.dy());
    pView->scale(newScale, newScale);
}

void MainWindow::OnSetZoomFit()//��ԭedit by zqh
{
    nZoomNumber = 100;
    double newScale = 100 / 100.0;
    QMatrix oldMatrix = pView->matrix();
    pView->resetMatrix();
    pView->translate(oldMatrix.dx(), oldMatrix.dy());
    pView->scale(newScale, newScale);
}

void MainWindow::OnSetZoomSmall()//��Сedit by zqh
{
    nZoomNumber-=25; //ÿ�����ż�25
    if(nZoomNumber < 25) //����ֵС��25��ʱ�򲻴���
    {
        nZoomNumber = 25;
        return;
    }

    double newScale = nZoomNumber / 100.0;
    QMatrix oldMatrix = pView->matrix();
    pView->resetMatrix();
    pView->translate(oldMatrix.dx(), oldMatrix.dy());
    pView->scale(newScale, newScale);
}

void MainWindow::OnSetSceneGrid()//����edit by zqh
{
    bIfSceneShowGrid = !bIfSceneShowGrid;
    OnSetMainSceneGrid();
}

void MainWindow::OnSetMainSceneGrid()//����edit by zqh
{
    QBrush br;
    int totalSceneNum = pSceneSheet.size();
    for(int i = 0; i < totalSceneNum;i++)
    {
        br = pSceneSheet[i]->backgroundBrush();
        if(bIfSceneShowGrid)
        {
            br.setStyle(Qt::Dense7Pattern);
        }
        else
        {
            br.setStyle(Qt::NoBrush);
        }
        this->pSceneSheet[i]->setBackgroundBrush(br);
    }
}

void MainWindow::OnSetDagViewModel()//������ͼģʽedit by zqh
{
    pView->setDragMode(QGraphicsView::ScrollHandDrag);
}

void MainWindow::OnSetDagViewModelArrow()//������ͼģʽedit by zqh
{
    pView->setDragMode(QGraphicsView::RubberBandDrag);
}

void MainWindow::OnOpenPropertyDlg()//�����ԶԻ���edit by zqh
{
    QList<QGraphicsItem *> Items;

    Items = pSceneSheet[nActiveSheetIndex]->selectedItems();
    if(Items.size() == 1 ) //ѡ��һ��itemʱ���򿪿ؼ��ĶԻ�������
    {
        SlotItemDBClick(Items.at(0));
    }
    else if(Items.size() == 0)//û��ѡ��itemʱ���򿪻�������ԶԻ���
    {
        if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nIsSceneOrWindow==2)//�Զ������
        {
            tree_UserKeyboardproperty();//�Զ����������
        }
        else if(0 == pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nIsSceneOrWindow)
        {
            newscreen_property();
        }
        else if(1 == pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nIsSceneOrWindow)
        {
            newswindow_property();
        }
    }
#if 0
    //add by Dylan 2011-11-14
    else//ѡ�ж��
    {
        QGraphicsItem *pItem;
        QList<QGraphicsItem *> Items;
        QStringList sList,sListpItem;
        QString str;
        pItem= this->pSceneSheet[pwnd->nActiveSheetIndex]->selectedItems().at(0);
        sListpItem=pItem->data(GROUP_DATALIST_KEY).toStringList();
        if(sListpItem.size()<20)
        {
            return;
        }
        QString ItemID=sListpItem.at(19);//��¼�ؼ�ID
        pwnd->SlotItemDBClick(pItem);

            Items = this->pSceneSheet[pwnd->nActiveSheetIndex]->selectedItems();   //��ǰҳ�����е�item
        for(int i=0;i<Items.size();i++)
        {
            sListpItem = Items.at(i)->data(GROUP_DATALIST_KEY).toStringList(); //ȡ��ÿ��item����������
            if(sList.size()<20)
                continue;
            str=sListpItem.at(19);
                  if(str==ItemID)//�Աȿؼ�ID�ҵ���Ӧ��ID�Ļ�
            {//��¼list
                    break;
            }
        }
        for(int j = 0; j < Items.size(); j++)
        {
            sList = Items.at(j)->data(GROUP_DATALIST_KEY).toStringList(); //ȡ��ÿ��item����������
           if(sList.size()<20)
               continue;
            str=sList.at(19);
            if(str.left(2)=="KB")
            {
                sList[41]=sListpItem[41];
                sList[42]=sListpItem[42];
                sList[43]=sListpItem[43];
                sList[45]=sListpItem[45];
                sList[48]=sListpItem[48];
                sList[49]=sListpItem[49];
                sList[50]=sListpItem[50];
                sList[51]=sListpItem[51];
                sList[140]=sListpItem[140];
//                Items[j]->SetPropertyValue("mBackRect.Pattern",QVariant(sList[51].toInt()));

//                Items[j]->SetPropertyValue("mFramRect.BackColor",QVariant(sList[41]));      //������������
//                Items[j]->SetPropertyValue("mBackRect.FrontColor",QVariant(sList[42]));      //������������
//                Items[j]->SetPropertyValue("mBackRect.BackColor",QVariant(sList[43]));      //������������

                Items[j]->setData(GROUP_DATALIST_KEY,sList);
             }
        }
    }
#endif
}

void MainWindow::OnFindAddressDlg()//�򿪵�ַ���ҶԻ��� edit by zqh
{
    FindAddrDlg *pFindDlg = new FindAddrDlg(this);

    QGraphicsItem *pItem;
    QString sScreenName = "";
    QString sAddr;
    QString str = "";
    QString ss  = "";
    QRect rc    = m_rightDock->geometry();
    int nFindCount = 0; //���ҵ���������Ϣ
    int nIfFit = 0;//�Ƿ�ƥ��
    int nRow   = 1;//�б�����
    int nIndex = 0;
    int nCount = 0;
    int i      = 0;
    int j      = 0;
    int iType = 0; //0Ϊ��ַ���ң�1Ϊ�������ı�����
    int iFindCount = 0;//��������
    int iLan = 0;//�������±�
    QString sSta = ""; //״̬
    QString sLanName = "";
    QString sNewStr = "";

    if(pFindDlg->exec() == QDialog::Accepted)
    {
        mapMsgOutPutItem.clear();
        iType = pFindDlg->iSelctType; //��������

        vAddrMsg.clear();
        vTextMsg.clear();
        pMainList->clear();

        sAddr  = pFindDlg->sAddress;     //���ҵĵ�ַ����
        sNewStr = pFindDlg->sReplaceMsg;//�µ��滻����
        if(iType == 0) //��ַ����
        {
            OnFillAddressMsgClass();        //����ַ��Ϣ��vAddrMsg
        }
        else if(iType == 1 || iType == 2) //�ı�����
        {
            fillTextMsgStruct();
        }

        nCount = vAddrMsg.size();       //����

        //before find address
        if(!m_rightDock->isVisible())   //��ʾ��Ϣ�������
        {
            m_rightDock->setVisible(true);
            ui->action_41->setChecked(true);
        }
        str = tr("���ڲ��� '");
        str = str + sAddr + "'...";

        pMainList->setRowCount(nRow);
        pMainList->setColumnCount(1);
        //pMainList->setColumnWidth(0, rc.width());
        pMainList->setColumnWidth(0, 2000);
        pMainList->setRowHeight(0, 20);
        pMainList->setItem(0, 0, new QTableWidgetItem(str));

        for(i = 0;i < nCount; i++)
        {
            pItem = vAddrMsg.at(i)->pItem;
            if(iType == 0) //��ַ����
            {
                iFindCount = vAddrMsg.at(i)->Address.size();
            }
            else if(iType == 1|| iType == 2) //�ı�����
            {
                iFindCount = vTextMsg.at(i).vText.size();
            }

            for(j = 0; j < iFindCount; j++)//for(j = 0; j < vAddrMsg.at(i)->Address.size(); j++) //10,15
            {
                nIndex = vAddrMsg[i]->nSheetIndex;//�������
                if(iType == 0) //��ַ����
                {
                    str    = vAddrMsg[i]->Address[j].pAddr->sShowAddr;//.sAddr;//ȡ��ַ
                }
                else if(iType == 1|| iType == 2) //�ı�����
                {
                    str = vTextMsg[i].vText.at(j);
                    iLan = vTextMsg[i].iLanguage.at(j); //�����±�
                    if(iLan >=0 && iLan <m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size())
                        sLanName = m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(iLan);
                    sSta = vTextMsg[i].vMsg.at(j);//QString("%1").arg(vTextMsg[i].vStatus.at(j));//״̬

                    if( iType == 2)//������滻�Ļ���Ĭ������ȫƥ��
                    {
                        pFindDlg->bIfSame = true;
                        pFindDlg->bIfCase = true;
                    }
                }
                if(pFindDlg->bIfSame)//��ȫƥ��
                {
                    if(pFindDlg->bIfCase)//���ִ�Сд
                    {
                        nIfFit = sAddr.compare(str,Qt::CaseSensitive);
                    }
                    else//�����ִ�Сд
                    {
                        nIfFit = sAddr.compare(str,Qt::CaseInsensitive);
                    }
                }
                else//ģ��ƥ��
                {
                    QBool bFit(true);
                    if(pFindDlg->bIfCase)//���ִ�Сд
                    {
                        bFit = str.contains(sAddr, Qt::CaseSensitive);
                        if(bFit == true)
                        {
                            nIfFit = 0;
                        }
                        else
                        {
                            nIfFit = 1;
                        }
                    }
                    else//�����ִ�Сд
                    {
                        bFit = str.contains(sAddr,Qt::CaseInsensitive);
                        if(bFit == true)
                        {
                            nIfFit = 0;
                        }
                        else
                        {
                            nIfFit = 1;
                        }
                    }
                }

                if(nIfFit == 0)//��ַƥ�� str == sAddr
                {
                    if(pItem)//�ǿؼ��ĵ�ַ
                    {
                        sScreenName = pSceneSheet[nIndex]->sNewScreenName;//��������

                        if(iType == 0) //��ַ����
                            ss = tr("λ��: ") + sScreenName + "-" + vAddrMsg.at(i)->Address[j].str + vAddrMsg.at(i)->Address[j].pAddr->sShowAddr;//�����Ϣ
                        else if(iType == 1) //�ı�����
                            ss = tr("λ��: ") + sScreenName + "-" +vTextMsg.at(i).sCtrlName+"-" +tr("����:")+sLanName+"-"+sSta+"-"+tr("�ı�����:")+str;// +tr("״̬:")
                        else if(iType == 2) //�滻
                        {
                            QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
                            item->replaceAllItemText(iLan,vTextMsg[i].vStatus.at(j),sNewStr); //��������

                            ss = tr("�滻: ") + sScreenName + "-" +vTextMsg.at(i).sCtrlName+"-" +tr("����:")+sLanName+"-"+sSta+"-"+tr("�ı�����:")+str+"->"+sNewStr;
                        }
                    }
                    else//�ǹ��̹������е�ַ
                    {
                        if(iType == 0) //��ַ����
                            ss = tr("λ��: ���̹����� ") + "-" + vAddrMsg.at(i)->Address[j].str + vAddrMsg.at(i)->Address[j].pAddr->sShowAddr; //�����Ϣ
                        else if(iType == 1) //�ı�����
                            ss = tr("λ��: ���̹����� ") + "-" +vTextMsg.at(i).sCtrlName+"-" +tr("����:")+sLanName+"-" +tr("�ı�����:")+str;
                        else if(iType == 2) //�滻
                        {
                            replaceTreeTextMsg(str,sNewStr);
                            ss = tr("�滻: ���̹����� ") + "-" +vTextMsg.at(i).sCtrlName+"-" +tr("����:")+sLanName+"-" +tr("�ı�����:")+str+"->"+sNewStr;
                        }
                    }

                    pMsgOutPut = new MsgOutPut ;//��Ϣ�������˫��Ҫ�������
                    pMsgOutPut->pItem = pItem;
                    pMsgOutPut->nSheetIndex = nIndex;

                    pMainList->insertRow(nRow);
                    pMainList->setRowHeight(nRow,20);
                    pMainList->setColumnWidth(0, 2000);
                    pMainList->setItem(nRow,0,new QTableWidgetItem(ss));

                    mapMsgOutPutItem.insert(nRow, pMsgOutPut);
                    nRow++;
                    nFindCount++;
                }//end if
            } //end  the second for
        } //end  the first for

        if(nFindCount == 0)//û���ҵ�
        {
            ss  = "'" + sAddr + "'.";
            //str = "Cannot find the string " + ss;
            if(iType == 0)
                str = tr("û���ҵ���ַ ") + ss;
            else
                str = tr("û���ҵ��ı� ") + ss;
        }
        else
        {
            if(iType == 0 || iType == 1)
                str = QString("%1").arg(nFindCount) + tr(" ��������ҵ�");
            else
                str = QString("%1").arg(nFindCount) + tr(" ��������滻");
        }

        pMainList->insertRow(nRow);
        pMainList->setRowHeight(nRow, 20);
        pMainList->setColumnWidth(nRow, 2000);
        pMainList->setItem(nRow, 0, new QTableWidgetItem(str));
        pMainList->setCurrentCell(nRow, 0);
    }//end if

    pFindDlg->deleteLater();
    pFindDlg = NULL;
}

void MainWindow::fillTextMsgStruct()
{
    int count = pSceneSheet.size(); //��������
    QList<QGraphicsItem *> Items;
    for(int i = 0 ; i < count; i++) //ɨ�����л���
    {
        Items = pSceneSheet[i]->items();   //��ǰҳ�����е�item
        foreach(QGraphicsItem *pItem, Items)
        {
            if(!pItem)
            {
                continue;
            }

            if(SAM_DRAW_OBJECT_GROUP == pItem->type())
            {
                if(pItem->parentItem() == 0 && pItem->type() != SAM_DRAW_OBJECT_TRACKER && pItem->type() != SAM_DRAW_OBJECT_LOCK)
                {
                    QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
                    {
                        pAddrMsg = new AddrMsg;
                        pAddrMsg->nSheetIndex = i;                      //�������
                        pAddrMsg->pItem       = pItem;                  //��ǰ�ؼ�
                        vAddrMsg.append(pAddrMsg);

                        TEXTPRO txt;
                        txt = item->getAllItemText(); //����ı���Ϣ
                        vTextMsg.append(txt);
                    }
                }
            }
        }
    }
    fillTreeTextMsg();
}

void MainWindow::fillTreeTextMsg() //���̹���������ʹ�õ��ı�����
{
    //�䷽����
    int RecipGroup = m_pSamSysParame->m_qvcRecipe.size(); //�䷽��
    int iRecipeCount = 0;
    int iLang = 0;
    int i,j,k;
    for( i = 0; i < RecipGroup;i++)
    {
        pAddrMsg = new AddrMsg;
        pAddrMsg->nSheetIndex = i; //��ʾ�䷽�����
        pAddrMsg->pItem = NULL;

        TEXTPRO txt;
        txt.sCtrlName = tr("�䷽��:")+m_pSamSysParame->m_qvcRecipe.at(i).sName; //�䷽������
        iRecipeCount = m_pSamSysParame->m_qvcRecipe[i].formula.size();//�䷽����
        for( j = 0; j < iRecipeCount; j++)
        {
            iLang = m_pSamSysParame->m_qvcRecipe[i].formula.at(j).RecipeInfo.size();//����
            for( k = 0; k < iLang; k++)
            {
                txt.iLanguage.append(k);
                txt.vStatus.append(j); //�䷽���
                txt.vMsg.append(tr("�䷽:")+QString("%1").arg(j));
                txt.vText.append(m_pSamSysParame->m_qvcRecipe.at(i).formula.at(j).RecipeInfo.at(k).sRecipeName);
            }
        }
        vTextMsg.append(txt);
        vAddrMsg.append(pAddrMsg);
    }

    //����
    RecipGroup = m_pSamSysParame->m_qvcAlarm.size();
    for( i = 0; i < RecipGroup;i++)
    {
        pAddrMsg = new AddrMsg;
        pAddrMsg->nSheetIndex = i; //��ʾ�䷽�����
        pAddrMsg->pItem = NULL;

        TEXTPRO txt;
        txt.sCtrlName = tr("����:")+m_pSamSysParame->m_qvcAlarm.at(i).alarmName; //����������

        iRecipeCount = m_pSamSysParame->m_qvcAlarm.at(i).alarms.size();//ÿ�鱨���ı�������
        for( j = 0; j < iRecipeCount; j++)
        {
            iLang = m_pSamSysParame->m_qvcAlarm.at(i).alarms.at(j).messages.size(); //����
            for( k = 0; k < iLang; k++)
            {
                txt.iLanguage.append(k);
                txt.vStatus.append(j); //����
                txt.vMsg.append(tr("����:")+QString("%1").arg(j));
                txt.vText.append(m_pSamSysParame->m_qvcAlarm.at(i).alarms.at(j).messages.at(k));
            }
        }
        vTextMsg.append(txt);
        vAddrMsg.append(pAddrMsg);
    }
}

void MainWindow::replaceTreeTextMsg(QString sOldMsg,QString sNewMsg) //�滻���̹������к����ı�������
{
    int RecipGroup = m_pSamSysParame->m_qvcRecipe.size(); //�䷽��
    int iRecipeCount = 0;
    int iLang = 0;
    int i,j,k;
    QString str = "";
    bool bFit = false;

    for( i = 0; i < RecipGroup;i++)
    {
        iRecipeCount = m_pSamSysParame->m_qvcRecipe[i].formula.size();//�䷽����
        for( j = 0; j < iRecipeCount; j++)
        {
            iLang = m_pSamSysParame->m_qvcRecipe[i].formula.at(j).RecipeInfo.size();//����
            for( k = 0; k < iLang; k++)
            {
                str = m_pSamSysParame->m_qvcRecipe.at(i).formula.at(j).RecipeInfo.at(k).sRecipeName;
                bFit = str.contains(sOldMsg, Qt::CaseSensitive);
                if(bFit)
                {
                    m_pSamSysParame->m_qvcRecipe[i].formula[j].RecipeInfo[k].sRecipeName = sNewMsg;
                }
            }
        }
    }

    //����
    RecipGroup = m_pSamSysParame->m_qvcAlarm.size();
    for( i = 0; i < RecipGroup;i++)
    {

        iRecipeCount = m_pSamSysParame->m_qvcAlarm.at(i).alarms.size();//ÿ�鱨���ı�������
        for( j = 0; j < iRecipeCount; j++)
        {
            iLang = m_pSamSysParame->m_qvcAlarm.at(i).alarms.at(j).messages.size(); //����
            for( k = 0; k < iLang; k++)
            {
                str = m_pSamSysParame->m_qvcAlarm.at(i).alarms.at(j).messages.at(k);
                bFit = str.contains(sOldMsg, Qt::CaseSensitive);
                if(bFit)
                {
                    m_pSamSysParame->m_qvcAlarm[i].alarms[j].messages[k] = sNewMsg;
                }
            }
        }
    }
}

/*****************************************************************
 *�������ƣ�OnFillAddressMsgClass
 *�������ܣ��洢���л�������пؼ��ĵ�ֵַ��vAddrMsg��̬�����У����ڵ�ַ
           ���ң���ַһ����ͱ���ʱ�ĵ�ַ������ʹ��
 *edit by zqh
 ****************************************************************/
/*class AddrMsg //���ַ��Ϣ,���ڵ�ַ���ң���ַһ����ͱ����ַ������ʹ��
{
public:
    QGraphicsItem *pItem; //ɨ���item
    int nSheetIndex;      //�������
    QVector<Keyboard> Address;
};*/
void MainWindow::OnFillAddressMsgClass()
{
    //QList<QGraphicsItem *> Items;
    /*QGraphicsItem *pItem;
    QStringList sList;
    int nValue = 0;
    int nID = 0;
    int i   = 0;
    int j   = 0;
    int k   = 0;*/

    int count = pSceneSheet.size(); //��������
    QList<QGraphicsItem *> Items;
    for(int i = 0 ; i < count; i++) //ɨ�����л���
    {
        Items = pSceneSheet[i]->items();   //��ǰҳ�����е�item
        foreach(QGraphicsItem *pItem, Items)
        {
            if(!pItem)
            {
                continue;
            }

            if(SAM_DRAW_OBJECT_GROUP == pItem->type())
            {
                if(pItem->parentItem() == 0 && pItem->type() != SAM_DRAW_OBJECT_TRACKER && pItem->type() != SAM_DRAW_OBJECT_LOCK)
                {
                    QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
                    {
                        pAddrMsg = new AddrMsg;
                        pAddrMsg->nSheetIndex = i;                      //�������
                        pAddrMsg->pItem       = pItem;                  //��ǰ�ؼ�
                        pAddrMsg->Address     = item->getAllItemAddr(); //��ַvector
                        if(pAddrMsg->Address.size() > 0)
                        {
                            vAddrMsg.append(pAddrMsg);
                        }

                        //delete pAddrMsg;
                        //pAddrMsg = NULL;
                    }
                }
            }
        }
    }

    //�����Ǽ�鹤�̹�����ģ��ĵ�ַ
    FillTreeAddress();
}

//


void MainWindow::shareAddressCode(Keyboard &TreeAddr, QString sName, int recipeNum)
{
    /*ADDRPRO temp;
    temp.addr = TreeAddr;
    temp.addr.sPlcRegTypeStr = sName;
    temp.str = QObject::tr("shareAddressCode");
    pAddrMsg->Address.append(temp);*/
    ADDRPRO temp;
    //Keyboard* kb = temp.pAddr;
    temp.pAddr = &TreeAddr;
    //temp.pAddr->sPlcRegTypeStr = sName;
    temp.str   = sName;//QObject::tr("shareAddressCode");
    temp.type  = TreeAddr.nAddrType;
    temp.nRecipe = recipeNum;
    pAddrMsg->Address.append(temp);
}

/*******************************************************************
 *�������ƣ�OnFillVisiblePage
 *�������ܣ��洢����ҳ��ĵ�ַ��Ϣ
 *�������壺
 *sList���ؼ��Ĵ洢��Ϣ
 *sBtnName���ؼ�������
 *nSheetIndex���������
 *edit by zqh
 ******************************************************************/
void MainWindow::OnFillVisiblePage(QStringList sList,QString sBtnName,
                                   int nSheetIndex)
{
    
}

/*******************************************************************
 *�������ƣ�OnFillAdvancedPage
 *�������ܣ��洢�߼�ҳ��ĵ�ַ��Ϣ
 *�������壺
 *sList���ؼ��Ĵ洢��Ϣ
 *sBtnName���ؼ�������
 *edit by zqh
 ******************************************************************/
void MainWindow::OnFillAdvancedPage(QStringList sList,QString sBtnName,
                                    int nSheetIndex)
{
    
}

/*******************************************************************
 *�������ƣ�MsgOutputListDoubleClicked
 *�������ܣ�˫����Ϣ������ڵ���Ӧ����
 *�������壺
 *nRow���к�
 *nClomn���к�
 *edit by zqh
 ******************************************************************/
void MainWindow::MsgOutputListDoubleClicked(int nRow, int nClomn)
{
    int     nIndex = 0;
    QString str    = "";

    QTableWidgetItem *mItem;         //���������Ϊѡ��״̬
    mItem = pMainList->item(nRow,nClomn); //0
    if(!mItem)
    {
        return;
    }
    str    = mItem->text();  //�������
    //nIndex = str.indexOf("error");
    nIndex = pMainList->rowCount();
    QMap<int, MsgOutPut*>::const_iterator itor = mapMsgOutPutItem.find(nRow);
    if(itor != mapMsgOutPutItem.end() && itor.value()->pItem)
    {
        if (pSceneSheet.size() <= itor.value()->nSheetIndex)
        {
            return;
        }
        nActiveSheetIndex = itor.value()->nSheetIndex;
        this->pView->setScene(pSceneSheet[nActiveSheetIndex]);
        pSceneSheet[nActiveSheetIndex]->clearSelection();//�������ѡ��
        itor.value()->pItem->setSelected(true);
        pSceneSheet[nActiveSheetIndex]->update();
    }
    pView->setScene(pSceneSheet[nActiveSheetIndex]);
    if(pwnd->pSceneSheet[nActiveSheetIndex]->nIsSceneOrWindow == 1)
    {
        setWindowTitle(QString(VERSION_NAME"--%1\%2"AK_FILE_END"--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                       arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
    }
    else if(pwnd->pSceneSheet[nActiveSheetIndex]->nIsSceneOrWindow ==0)
    {
        setWindowTitle(QString(VERSION_NAME"--%1\%2"AK_FILE_END"--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                       arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
    }
}

void MainWindow::OnDisplayAddrUseDlg()//�򿪵�ַʹ��һ����Ի���
{
    DisplayAddressUse *pAddressUse = new DisplayAddressUse(this);
    pAddressUse->exec();
    pAddressUse->deleteLater();
    pAddressUse = NULL;
}//

bool MainWindow::StartCompileThread()
{
    if(!this->is_Save)
    {
        QMessageBox box(QMessageBox::Information,tr("��ʾ"),tr("����֮ǰҪ���浱ǰ���̣��Ƿ񱣴棿"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("��"));
        box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::Ok))
        {
            createsavedlg();
        }
        else
        {
           return false;
        }
    }
    if(thread->isRunning())
    {
        qDebug() <<"thread->isRunning()";
        return false;
    }
    isCompiled = true;
    if(!m_rightDock->isVisible())   //��ʾ��Ϣ�������
    {
        m_rightDock->setVisible(true);
        ui->action_41->setChecked(true);
    }
    bool bReturnFlag = true;
    pMainList->clear();
    pMainList->setRowCount(0);

    //����ʱ��ַ����Ƿ���ȷ
    bReturnFlag = CheckAddressInCompile();
    if(!bReturnFlag)
    {
        return false;
    }

    //��������ļ�
    //CheckDriver();
    //if(!this->CheckDriver())
      //  return false;
    //����ϵͳ�����Ϳؼ�����

    deleteDirectory(QFileInfo("compile"));
    deleteDirectory(QFileInfo("Fonts"));
    deleteDirectory(QFileInfo("resource"));

    thread->start();
    //thread->wait();
    return true;
}

void MainWindow::USB_DownLoad()
{
    if(QFile::exists("gEKip"))
    {
        QMessageBox box(QMessageBox::Information,tr(""),tr("��������̬���ڱ����У��������ܻ�����ļ���ͻ���Ƿ����"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("��"));
        box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::Cancel))
        {
            return;
        }
    }
    else
    {
        QFile file("gEKip");
        file.open(QIODevice::WriteOnly);
        file.close();
    }
    if(is_NeedCompiled == true)
    {
        thread->SetDownload(DOWNLOAD);
        if(!StartCompileThread())
        {
            QFile::remove("gEKip");
            isCompiled = false;
        }
    }
    else
    {
        StartDownload();
    }
}

void MainWindow::StartSimulator_off()
{
	//��ʼ����ģ��
    //SimulatorDlg *simDlg = new SimulatorDlg(this);
    //simDlg->exec();
    if(pSimDlg == NULL)
    {
      pSimDlg = new SimulatorDlg(this);
    }
    if(pSimDlg)
    {
      if(pSimDlg->exec() == QDialog::Accepted)
      {
          pSimDlg = NULL;
      }
    }
}
void MainWindow::StartSimulator_on()
{
	DownLoadDlg *pDownLoadDlg = new DownLoadDlg(this);
	pDownLoadDlg->exec();
    pDownLoadDlg->deleteLater();
}
void MainWindow::StartDownload()
{
	DownLoadDlg *pDownLoadDlg = new DownLoadDlg(this);
	pDownLoadDlg->exec();
    pDownLoadDlg->deleteLater();
}
void MainWindow::closeEvent(QCloseEvent *event)//����رհ�ť�¼�
{
    //add by wuxiyang �ж��Ƿ��˳������˳���������
    bool is_close = true;
    if(is_Is)
   {
       event->accept();
   }

   else if(thread && thread->isRunning())
   {
       QMessageBox box(QMessageBox::Information,tr("��ʾ"),tr("�������ڽ����У��Ƿ�ǿ�ƹر�"),QMessageBox::Ok|QMessageBox::No,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
       box.button(QMessageBox::Ok)->setText(tr("��"));
       box.button(QMessageBox::No)->setText(tr("��"));
       box.exec();
       if(box.clickedButton()== box.button(QMessageBox::Ok))//������˱��浱ǰ����
       {
           thread->terminate();
           //ui->toolBox->hide();
           event->accept();
       }
       else
       {
          event->ignore();
          is_close = false;
       }
   }
   else if(!pwnd->is_Save)
   {
       QMessageBox box(QMessageBox::Information,tr("��ʾ"),tr("�Ƿ񱣴浱ǰ����"),QMessageBox::Ok|QMessageBox::No|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
       box.button(QMessageBox::Ok)->setText(tr("��"));
       box.button(QMessageBox::No)->setText(tr("��"));
       box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));
       box.exec();
       if(box.clickedButton()== box.button(QMessageBox::Ok))//������˱��浱ǰ����
       {
           createsavedlg();
           //ui->toolBox->hide();
           event->accept();
       }
       else if(box.clickedButton()== box.button(QMessageBox::No))//������˷�
       {
           //ui->toolBox->hide();
           event->accept();
       }
       else
       {
          event->ignore();
          is_close = false;
       }
   }

   if(is_close)
   {
        QSettings *readIni = new QSettings("language.ini", QSettings::IniFormat, 0);
        if(ui->action_chinese->isChecked())
        {
            readIni->setValue("language/language", "chinese");
        }
        else
        {
            readIni->setValue("language/language", "english");
        }
   }
}


//�˳�ʱ��
void MainWindow::on_action_quit_triggered()
{
   close();
}

bool MainWindow::review_ScreenAndWindow_Name(QString str)
{
    int nCount_Screen=screen->childCount();
    int nCount_Window=window->childCount();
    int nCount_TreeKeyboard=TreeKeyboard->childCount();

    QVector<QString> name_vector;
    QString item_name="";
    for(int i=0;i<nCount_Screen;i++)
    {
        item_name=screen->child(i)->text(0).split(":").at(1);
        name_vector.push_back(item_name);
    }
    if(window->childCount()>=1)
    {
        for(int i=0;i<nCount_Window;i++)
        {
            item_name=window->child(i)->text(0).split(":").at(1);
            name_vector.push_back(item_name);
        }
    }
    if(TreeKeyboard->childCount()>=1)
    {
        for(int i=0;i<nCount_TreeKeyboard;i++)
        {
            item_name=TreeKeyboard->child(i)->text(0).split(":").at(1);
            name_vector.push_back(item_name);
        }
    }
    if(name_vector.contains(str))
    {
        QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr("�����Ѿ����ڣ�����������"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        msg.exec();
        return 1;
    }
    return 0;
}//

void MainWindow::listChange(int index)
{
    return;
    /*if(index==0)//��׼
    {
        if(!is_haveScreen)
        {
            return;
        }//
        for(int i=0;i<screenSubItem_vector.size();i++)
        {
            screenSubItem_vector[i]->setHidden(true);
        }//���ػ�������������

       upDatetreeScreenItem();//���»��������

    }//
    else if(index==1)//Ԫ���б�
    {
        if(!is_haveScreen)
        {
            return;
        }
            for(int i=0;i<screenSubItem_vector.size();i++)
            {
                screenSubItem_vector[i]->setHidden(false);
            }//��ʾ��������������
             upDatetreeScreenItem();//���»��������
    }//
    else if(index==2)//Ԥ��
    {
        if(!is_haveScreen)
        {
            return;
        }

         for(int i=0;i<screenSubItem_vector.size();i++)
         {
            screenSubItem_vector[i]->setHidden(true);
        }//���ػ�������������
        copyScreen_Item->setHidden(true);
        copyWindow_Item->setHidden(true);
        copyUserKeyboard->setHidden(true);

        if(TreeKeyboard->childCount()>0)
        {
            TreeKeyboard->setHidden(false);
        }
        else
        {
            TreeKeyboard->setHidden(true);
        }
        screen->setHidden(false);
        window->setHidden(false);
        tree0->expandAll();
        updateAllPreviewWindow();
        //pwnd->PreviewWindow();
    }/*/
}
void MainWindow::AndTreeSubItem(QGraphicsItem * newItem)
{
    if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nIsSceneOrWindow==2)//�Զ������
     {
        return;//��������
    }
  QStringList datalist;
  datalist= qVariantValue<QStringList>(newItem->data(GROUP_DATALIST_KEY));

  if(datalist.size() < 20)//if(datalist.isEmpty())
  {
      return;
  }

  QString sTmp=datalist.at(19);

  if(sTmp.isEmpty())
  {
      return;
  }

  screenSubItem_vector.push_back(new QTreeWidgetItem(newScreen[pwnd->nActiveSheetIndex],QStringList(sTmp)));;
  newScreen[pwnd->nActiveSheetIndex]->addChild(screenSubItem_vector.at(screenSubItem_vector.size()-1));

  //list_style
  for(int i=0;i<screenSubItem_vector.size();i++)
  {
       screenSubItem_vector.at(i)->setHidden(true);
  }
  /*if(list_style->currentIndex()==0||list_style->currentIndex()==2)//��׼��Ԥ��
  {
      for(int i=0;i<screenSubItem_vector.size();i++)
      {
           screenSubItem_vector.at(i)->setHidden(true);
      }
  }
  else if(list_style->currentIndex()==1)//Ԫ��
  {
      for(int i=0;i<screenSubItem_vector.size();i++)
      {
           screenSubItem_vector.at(i)->setHidden(false);
      }
  }*/
}//

void MainWindow::PreviewWindow()
{
    updatePreviewWindow() ;//����Ԥ������
}

/*********************************************************************************
  *�������ƣ�updatePreviewWindow
  *�������ܣ�ֻ���ڹ��̹�����ѡ�񴰿�Ԥ����ʱ��Ŵ����ͼ
  *�༭��֣����
  *ʱ�䣺2012.02.27
  ********************************************************************************/
void MainWindow::updatePreviewWindow() //����Ԥ������
{
//list_style
    /*if(list_style->currentIndex() != 2)//����Ԥ�����ڲ�������
        return;
    if(!is_haveScreen)
    {
        return;
    }
    int i = nActiveSheetIndex;
    int nWidth=80;
    int nHeight=60;

    QPixmap pixmap(nWidth,nHeight);
    QPainter painter(&pixmap);
    if(pSceneSheet[i]->m_sceneTypeProp.nIsSceneOrWindow==1)//����
    {
        if(pwnd->m_pSamSysParame->m_projectProp.nDisplayMode==1)//��ֱ
        {
           pSceneSheet[i]->render(&painter,QRectF(0,0,nHeight,nWidth),QRectF(0,0,pSceneSheet[i]->width()-50,pSceneSheet[i]->height()),Qt::IgnoreAspectRatio);
        }
        else
        {
          pSceneSheet[i]->render(&painter,QRectF(0,0,nWidth,nHeight),QRectF(0,0,pSceneSheet[i]->width(),pSceneSheet[i]->height()),Qt::IgnoreAspectRatio);
        }
    }
    else if(pSceneSheet[i]->m_sceneTypeProp.nIsSceneOrWindow==0)//����
    {
        pSceneSheet[i]->render(&painter,QRectF(0,0,nWidth,nHeight),QRectF(0,0,pSceneSheet[i]->width(),pSceneSheet[i]->height()),Qt::IgnoreAspectRatio);
    }
    else if(pSceneSheet[i]->m_sceneTypeProp.nIsSceneOrWindow==2)//�Զ������
    {
        pSceneSheet[i]->render(&painter,QRectF(0,0,nWidth,nHeight),QRectF(0,0,pSceneSheet[i]->width(),pSceneSheet[i]->height()),Qt::IgnoreAspectRatio);
    }
    painter.end();
    if(pixmap.isNull())
    {
        return;
    }
    pixmap.save("C:/scene.png");
    if( nActiveSheetIndex == label.size()) //���½�
    {
        QLabel  *lab=new QLabel(tree);
        QLabel  * tit=new QLabel(tree);
        tit->setAlignment(Qt::AlignHCenter);

        QVBoxLayout *preview_layout=new QVBoxLayout(tree);
        preview_layout->setSpacing(0);
        label.push_back(lab);
        titlelabel.push_back(tit);
        preview_layout->addWidget(label.last());
        preview_layout->addWidget(titlelabel.last());
        QWidget  *pri=new QWidget(tree);
        priviewWidget.push_back(pri);
        priviewWidget.last()->setLayout(preview_layout);
        tree->setItemWidget(newScreen[i],0,priviewWidget.last()) ;
        tree->expandAll();
    }
    label[i]->setPixmap(pixmap);
    newScreen[i]->setTextAlignment(0,Qt::AlignBottom);
    tree->expandAll();*/
}

/*********************************************************************************
  *�������ƣ�updateAllPreviewWindow
  *�������ܣ�ֻ���ڹ��̹�����ѡ�񴰿�Ԥ����ʱ���¼��ؽ�ͼ
  *�༭��֣����
  *ʱ�䣺2012.02.27
  ********************************************************************************/
void MainWindow::updateAllPreviewWindow()
{
    if(!is_haveScreen)
    {
        return;
    }
    int totalSceneNum = pSceneSheet.size();
    int nWidth=80;
    int nHeight=60;

    for(int i=0;i<label.size();i++)
    {
        if(label[i])
        {
            delete  label[i];
            label[i]=NULL;
        }
    }
    label.clear();
    for(int i=0;i<label.size();i++)
    {
        if(label[i])
        {
            delete  label[i];
            label[i]=NULL;
        }
    }
    label.clear();
    for(int i=0;i<titlelabel.size();i++)
    {
        if(titlelabel[i])
        {
            delete titlelabel[i];
            titlelabel[i]=NULL;
        }
    }
    titlelabel.clear();
    for(int i=0;i<priviewWidget.size();i++)
    {
        if(priviewWidget[i])
        {
            delete  priviewWidget[i];
            priviewWidget[i]=NULL;
        }
    }
    priviewWidget.clear();


    for(int i=0;i<totalSceneNum;i++)
    {
        if(!pSceneSheet[i])
        {
            return;
        }
        QLabel  *lab=new QLabel(tree);
        QLabel  * tit=new QLabel(tree);
        tit->setAlignment(Qt::AlignHCenter);

        QVBoxLayout *preview_layout=new QVBoxLayout(tree);
        preview_layout->setSpacing(0);
        label.push_back(lab);
        titlelabel.push_back(tit);
        preview_layout->addWidget(label.last());
        preview_layout->addWidget(titlelabel.last());
        QWidget  *pri=new QWidget(tree);
        priviewWidget.push_back(pri);
        priviewWidget.last()->setLayout(preview_layout);

        QPixmap pixmap(nWidth,nHeight);
        QPainter painter(&pixmap);
         if(pSceneSheet[i]->nIsSceneOrWindow==1)//����
         {
             if(pwnd->m_pSamSysParame->m_projectProp.nDisplayMode==1)//��ֱ
             {
                pSceneSheet[i]->render(&painter,QRectF(lab->x(),lab->y(),nHeight,nWidth),QRectF(0,0,pSceneSheet[i]->width()-50,pSceneSheet[i]->height()),Qt::IgnoreAspectRatio);
             }
             else
             {
               pSceneSheet[i]->render(&painter,QRectF(lab->x(),lab->y(),nWidth,nHeight),QRectF(0,0,pSceneSheet[i]->width(),pSceneSheet[i]->height()),Qt::IgnoreAspectRatio);
             }
         }
         else if(pSceneSheet[i]->nIsSceneOrWindow==0)//����
         {
             pSceneSheet[i]->render(&painter,QRectF(0,0,nWidth,nHeight),QRectF(0,0,pSceneSheet[i]->width(),pSceneSheet[i]->height()),Qt::IgnoreAspectRatio);
         }
         else if(pSceneSheet[i]->nIsSceneOrWindow==2)//�Զ������
         {
             pSceneSheet[i]->render(&painter,QRectF(lab->x(),lab->y(),nWidth,nHeight),QRectF(0,0,pSceneSheet[i]->width(),pSceneSheet[i]->height()),Qt::IgnoreAspectRatio);
         }
         painter.end();
         pixmap.save("C:/scene.png");
         if(pixmap.isNull())
         {
             return;
         }

         label.last()->setPixmap(pixmap);
         newScreen[i]->setTextAlignment(0,Qt::AlignBottom);
         tree->setItemWidget(newScreen[i],0,priviewWidget.last()) ;
         tree->expandAll();
    }
    tree->expandAll();
}

void MainWindow::upDatetreeScreenItem()
{
    //list_style
    //if(list_style->currentIndex()==0)//��׼
    {
        delete copyScreen_Item;
        copyScreen_Item=NULL;
        delete copyWindow_Item;
        copyWindow_Item=NULL;
        delete copyUserKeyboard;
        copyUserKeyboard=NULL;
        screen->setHidden(true);
        window->setHidden(true);
        TreeKeyboard->setHidden(true);//�û��Զ������

        copyUserKeyboard=pwnd->TreeKeyboard->clone();
        copyScreen_Item=screen->clone();
        copyWindow_Item=window->clone();
        copyScreen_Item->setHidden(false);
        copyWindow_Item->setHidden(false);
        root0->insertChild(1,copyScreen_Item);
        root0->insertChild(2,copyWindow_Item);
        //root->insertChild(3,copyScreen_Item);
        //root->insertChild(4,copyWindow_Item);
        if(copyUserKeyboard->childCount()>0)
        {
            copyUserKeyboard->setHidden(false);
            //root->insertChild(5,copyUserKeyboard);
            root0->insertChild(3,copyUserKeyboard);
        }
        else
        {
            copyUserKeyboard->setHidden(true);
        }
        for(int j=0;j<copyScreen_Item->childCount();j++)
        {
            for(int i=0;i<copyScreen_Item->child(j)->childCount();i++)
            {
                copyScreen_Item->child(j)->child(i)->setHidden(true);
            }
        }//
        for(int j=0;j<copyWindow_Item->childCount();j++)
        {
            for(int i=0;i<copyWindow_Item->child(j)->childCount();i++)
            {
                copyWindow_Item->child(j)->child(i)->setHidden(true);
            }
        }
        for(int j=0;j<copyUserKeyboard->childCount();j++)
        {
            for(int i=0;i<copyUserKeyboard->child(j)->childCount();i++)
            {
                copyUserKeyboard->child(j)->child(i)->setHidden(true);
            }
        }
        tree0->expandAll();
    }
    /*if(list_style->currentIndex()==1)//Ԫ��
    {
        delete copyScreen_Item;
        copyScreen_Item=NULL;
        delete copyWindow_Item;
        copyWindow_Item=NULL;
        delete copyUserKeyboard;//�û��Զ������
       copyUserKeyboard=NULL;
        screen->setHidden(true);
        window->setHidden(true);
        TreeKeyboard->setHidden(true);

        copyScreen_Item=screen->clone();
        copyWindow_Item=window->clone();
        copyUserKeyboard=TreeKeyboard->clone();

        copyScreen_Item->setHidden(false);
        copyWindow_Item->setHidden(false);
         root->insertChild(3,copyScreen_Item);
        root->insertChild(4,copyWindow_Item);
        root->insertChild(5,copyUserKeyboard);
        if(copyUserKeyboard->childCount()>0)
        {
            copyUserKeyboard->setHidden(false);
        }
        else
        {
            copyUserKeyboard->setHidden(true);
        }
        for(int j=0;j<copyScreen_Item->childCount();j++)
        {
            for(int i=0;i<copyScreen_Item->child(j)->childCount();i++)
            {
                copyScreen_Item->child(j)->child(i)->setHidden(false);
            }
        }//
        for(int j=0;j<copyWindow_Item->childCount();j++)
        {
            for(int i=0;i<copyWindow_Item->child(j)->childCount();i++)
            {
                copyWindow_Item->child(j)->child(i)->setHidden(false);
            }
        }
        for(int j=0;j<copyUserKeyboard->childCount();j++)
        {
            for(int i=0;i<copyUserKeyboard->child(j)->childCount();i++)
            {
                copyUserKeyboard->child(j)->child(i)->setHidden(false);
            }
        }
        tree->expandAll();
    }*/
}
void MainWindow::closeProject()
{
    if(isCompiled)
    {
        return;
    }
    if(!pwnd->is_Save)//�й���û����������
    {
        QMessageBox box(QMessageBox::Information,tr("��ʾ"),tr("�Ƿ񱣴浱ǰ����"),QMessageBox::Ok|QMessageBox::No|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("��"));
        box.button(QMessageBox::No)->setText(tr("��"));
        box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::Ok))//������˱��浱ǰ����
        {
            createsavedlg();
            is_Is=true;
            isHave=false;
            openInit_MenuAndTool();
            is_haveScreen=false;
            is_OpenrecentFile=false;
            is_click_open=false;

            qLanguagecmb->clear();//
            qLanguagecmb->setEnabled(false);
            reTree_ScreenAndWindow();
        }
        else if(box.clickedButton()== box.button(QMessageBox::No))//������˷�
        {
            is_Is=true;
            openInit_MenuAndTool();
            isHave=false;
            is_haveScreen=false;
            is_OpenrecentFile=false;
            is_click_open=false;

            qLanguagecmb->clear();//
            qLanguagecmb->setEnabled(false);
            reTree_ScreenAndWindow();
        }
        else
        {
            return;
        }
    }
    else//�������Ѿ�����
    {
        is_Is=true;
        openInit_MenuAndTool();
        isHave=false;
        is_haveScreen=false;
        is_OpenrecentFile=false;
        is_click_open=false;

        qLanguagecmb->clear();//
        qLanguagecmb->setEnabled(false);
        reTree_ScreenAndWindow();
        pwnd->is_Save=false;
        is_NeedCompiled = true;
        if(pView!=NULL)
        {
            delete pView;
            pView=NULL;
        }
    }

    ui->action_tool->setChecked(false);

    pMainList->clear();
    pMainList->setRowCount(0);
    setWindowTitle(tr(VERSION_NAME));

    link->takeChildren();
    tree_hisdatalog->takeChildren();
    alarmlog->takeChildren();
    recipe->takeChildren();

    root->setExpanded(false);
}
/*����0��ȷ
 *����1��Сֵ�������ֵ
 *����2��Сֵ����
 *����3���ֵ����
 */
int MainWindow::CheckMinMax(QString Min, QString Max, int DataType,int CheckType)
{
    //CheckType ��ʾ��0 �����Сֵ���� ����ʾ��1 ����ֵ����ֵ
    QString str1,str2;
    if(CheckType==0)
    {
        str1=tr("���ֵ");
        str2=tr("��Сֵ");
    }
    else if(CheckType==1)
    {
        str1=tr("����ֵ");
        str2=tr("����ֵ");
    }
    QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr(""),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);

    QLibrary  lib("Check.dll");
    if (!lib.load())
    {
        msg.setText(tr("Check.dllδ�ҵ���"));
        msg.exec();

        return 0;//���ز������ԣ�Ӧ���������ó����ز���
    }
    typedef int (*ADDPROC)( QString ,QString , int );
    ADDPROC CheckMinMax= (ADDPROC)lib.resolve("CheckMinMax");
    switch(CheckMinMax(Min,Max,DataType))
    {
    case 0:
        return 0;
        break;
    case 1:
        msg.setText(str2+tr("����")+str1);
        msg.exec();
        return 1;
        break;
    case 2:
        msg.setText(str2+tr("����!"));//��С
        msg.exec();
        return 2;
        break;
    case 3:
        msg.setText(str1+tr("���ޣ�"));//���
        msg.exec();
        return 3;
        break;
    case 4:
        msg.setText(str2+tr("����"));//��С
        msg.exec();
        return 4;
        break;
    case 5:
        msg.setText(str1+tr("����"));//���
        msg.exec();
        return 5;
        break;
    default:
        msg.setText(tr("�ж������Сֵ����ֵ����"));
        msg.exec();
    }
    lib.unload();
    return 6;
}
int MainWindow::CheckString(Keyboard &keyboard,QString sourceStr,int Addr_Type)
{
	QRegExp regEx_LB = QRegExp("^lb([0-9]*[0-9][0-9]*)$");
	regEx_LB.setCaseSensitivity(Qt::CaseInsensitive);
	QRegExp regEx_LW = QRegExp("^lw([0-9]*[0-9][0-9]*)$");
	regEx_LW.setCaseSensitivity(Qt::CaseInsensitive);
	QRegExp regEx_RWI = QRegExp("^rwi([0-9]*[0-9][0-9]*)$");
	regEx_RWI.setCaseSensitivity(Qt::CaseInsensitive);
	//QRegExp regEx_LS = QRegExp("^ls([0-9]*[0-9][0-9]*)$");
	//regEx_LS.setCaseSensitivity(Qt::CaseInsensitive);
	QRegExp regEx_PLC = QRegExp("^\\[\\S{1,255}\\]\\S{1,255}$");
	regEx_PLC.setCaseSensitivity(Qt::CaseInsensitive);

	int value = 0;
	int index = 0;
	QStringList regs = m_LocalReg.keys();

	if (regs.contains(sourceStr,Qt::CaseInsensitive))
    {
        QString regStr;
        foreach(QString sReg,regs)
        {
            if(sReg.compare(sourceStr,Qt::CaseInsensitive) == 0)
            {
                regStr = sReg;
                break;
            }
        }
        if (Addr_Type == 0 && m_LocalReg.value(regStr).startsWith("LB",Qt::CaseInsensitive))
		{
			keyboard.sPlcAddrValue = "0";
			keyboard.nConnectType = 0;
			keyboard.nPlcRegTypeIndex = 0;
			keyboard.nAddrType = 0;
			keyboard.sShowAddr = sourceStr;
			keyboard.sPlcRegTypeStr = sourceStr;
			keyboard.sPlcName = "";
			keyboard.Length = 1;
			return ADDR_CORRECT;
		}
		if (Addr_Type == 1 && m_LocalReg.value(sourceStr).startsWith("LW",Qt::CaseInsensitive))
		{
			keyboard.sPlcAddrValue = "0";
			keyboard.nConnectType = 0;
			keyboard.nPlcRegTypeIndex = 0;
			keyboard.nAddrType = 0;
			keyboard.sShowAddr = sourceStr;
			keyboard.sPlcRegTypeStr = sourceStr;
			keyboard.sPlcName = "";
			keyboard.Length = 1;
			return ADDR_CORRECT;
		}
	}
	if (regEx_LB.exactMatch(sourceStr))
	{
		value = sourceStr.mid(2,sourceStr.length()-2).toInt();//ƥ��LB
		if (Addr_Type != 0)
		{
			return ILLEGAL_REG;
		} 
		if (value <0 || value >65535)
		{
			return ADDR_OUT_BOUND;
		}
		else{
			keyboard.sPlcAddrValue = sourceStr.mid(2,sourceStr.length()-2);
			keyboard.nConnectType = 0;
			keyboard.nPlcRegTypeIndex = 0;
			keyboard.nAddrType = 0;
			keyboard.sShowAddr = sourceStr;
			keyboard.sPlcRegTypeStr = "LB";
			keyboard.sPlcName = "";
			keyboard.Length = 1;
			return ADDR_CORRECT;
		}
		
	} 
	else if (regEx_LW.exactMatch(sourceStr) || regEx_RWI.exactMatch(sourceStr))//ƥ��LW,RWI
	{
		if (Addr_Type != 1)
		{
			return ILLEGAL_REG;
		} 
		if (regEx_LW.exactMatch(sourceStr))
		{
			index = 2;
		} 
		else
		{
			index = 3;
		}
		value = sourceStr.mid(index,sourceStr.length()-index).toInt();
		if (value <0 || value >65535)
		{
			return ADDR_OUT_BOUND;
		}
		else{
			keyboard.sPlcAddrValue = sourceStr.mid(index,sourceStr.length()-index);
			keyboard.nConnectType = 0;
			keyboard.nPlcRegTypeIndex = index-1;
			
			keyboard.nAddrType = 1;
			keyboard.sShowAddr = sourceStr;
			keyboard.sPlcRegTypeStr = sourceStr.mid(0,index);
			keyboard.sPlcName = "";
			keyboard.Length = 1;
			return ADDR_CORRECT;
		}
		
	} 
	else if (regEx_PLC.exactMatch(sourceStr))//ƥ���ⲿ��ַ
	{
		return CheckExternAddr(keyboard, sourceStr, Addr_Type);
	}
	else //����ʶ����ַ�
	{
		return ADDR_OTHER_ERROR;
	}
	
	
}

//����ⲿ��ַ�����ʽ
int MainWindow::CheckExternAddr(Keyboard &keyboard,QString sourceStr,int Addr_Type)
{
	QStringList lst = sourceStr.split("]");
	if (lst.size() != 2)
	{
		return ADDR_OTHER_ERROR;
	}
	QString sName = lst[0].remove("[");
	//QString sProtocol = lst[1].remove("[");
	QString sAddr = lst[1];

    QString path = "drivers/qtdll/";
	int nConnect = 1;
	int nProtocol  = 0;
	PLC_MODEL cModel;
	bool bExist = false;
	foreach(stConnect cnt,m_pSamSysParame->m_qvcConnect)
	{		
		
		nProtocol = 0;
		foreach(stProtocol ptl,cnt.vProtocols)
		{
			if (ptl.sName == sName)
			{
				cModel = ptl.mPlc;
                path += ptl.sFactoryName +"/"+ptl.mPlc.sModelName+".dll";
				bExist = true;
				break;
			}
			nProtocol++;
		}
		if (bExist)
		{
			break;
		}
		nConnect++;
	}
	QLibrary lib(path);
	if (bExist && lib.load())
	{
        typedef ADDR_CHECK_ERROR_INFO (*ADDPROC)(std::string , int , ADDR_CHECK_SOURCE_PROP &);
		ADDPROC check= (ADDPROC)lib.resolve("checkStrAddr");
		if(check)
		{
            ADDR_CHECK_SOURCE_PROP spro;
			
			QString sReg;
			ADDR_CHECK_ERROR_INFO result = ADDR_CORRECT;
			result = check(sAddr.toStdString(),Addr_Type+1,spro);
			if(result == ADDR_CORRECT)
			{
                sReg = QString::fromStdString(spro.sRegName);
				keyboard.sPlcAddrValue = QString::fromStdString(spro.sAddrValue);
				keyboard.nConnectType = nConnect;
                keyboard.nPlcRegTypeIndex = cModel.regs.indexOf(sReg);
				
				keyboard.nAddrType = Addr_Type;
				keyboard.sShowAddr = sourceStr;
				keyboard.sPlcRegTypeStr = sReg;
				keyboard.sPlcName = sName;
				keyboard.Length = 1;
				
			}
			lib.unload();
			return result;
		}
		else{
			lib.unload();
			return INVALID_CONNECT;
		}
	}
	else
	{
		return INVALID_CONNECT;
	}
	
}

int MainWindow::IsAddressCheckRight(Keyboard &keyboard,QString WaringMsg,QLineEdit *pLineEdit,int Addr_Type)
{	
    QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr(""),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
    
    
	int iFlg= CheckString(keyboard,pLineEdit->text(),Addr_Type);
    switch(iFlg)
    {
    case ADDR_CORRECT://�޴���
        break;
    case ADDR_STRING_NULL://����Ϊ��
        msg.setText(WaringMsg+tr("�����ַ����Ϊ�գ�"));
        msg.exec();
        pLineEdit->setFocus();
        pLineEdit->selectAll();
        return 0;
	case ILLEGAL_REG://�Ĵ������Ͳ�ƥ�����
		msg.setText(WaringMsg+tr("�Ĵ����������ַҪ��ƥ�䣡"));
		msg.exec();
		pLineEdit->setFocus();
		pLineEdit->selectAll();
		return 0;
	case INVALID_CONNECT://�ֶ������ַ����ʱ��û�и�����
        msg.setText(WaringMsg+tr("û����Ӹ�Э�飡"));
		msg.exec();
		pLineEdit->setFocus();
		pLineEdit->selectAll();
		return 0;
	case ADDR_OUT_BOUND://���ݳ��� ����ֵΪ����ֵ ����Ϊ�����ֵ ����Ϊ�����ֵ
		
		msg.setText(WaringMsg+tr("��ֵַ������Χ��"));
		msg.exec();
		pLineEdit->setFocus();
		pLineEdit->selectAll();
		return 0;
	default://�����ʽ����
        msg.setText(WaringMsg+tr("�����ʽ����"));
        msg.exec();
        pLineEdit->setFocus();
        pLineEdit->selectAll();
        return 0;
    
    }
    keyboard.nAddrType = Addr_Type; //��¼��λ��ʾ
    pLineEdit->setText(keyboard.sShowAddr);
    
    return 1;
	
}
int MainWindow::IsMyAddressCheckRight(Keyboard &keyboard,QString WaringMsg,QLineEdit *pLineEdit,int Addr_Type, QSpinBox *pSpinBox)
{
    QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr(""),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
    QLibrary  lib("Check.dll");
    if (!lib.load())
    {
        msg.setText(tr("Check.dllδ�ҵ���"));
        msg.exec();
        return 0;//���ز������ԣ�Ӧ���������ó����ز���
    }
    typedef int (*ADDPROC)( QString ,int , Keyboard &,QVector<plcCommunicateProp>);
    ADDPROC AddressCheck = NULL;
    AddressCheck = (ADDPROC)lib.resolve("IsAddressCheckRight");
    if (NULL == AddressCheck)
    {
        msg.setText(tr("�ļ��������°�װӦ�ó���"));
        msg.exec();
        return 0;
    }
    int iFlg= AddressCheck(pLineEdit->text(),Addr_Type,keyboard,m_pSamSysParame->m_qvcPlcCommunicate);
    switch(iFlg)
    {
    case 0://�޴���
        break;
    case -1://����Ϊ��
        //msg.setText(WaringMsg+tr("�����ַ����Ϊ�գ�"));
        //msg.exec();
        //pLineEdit->setFocus();
        return 0;
    case 1://ʹ�ý��ƴ��� Ҫ��Ϊ8��������
    case 2://ʹ�ý��ƴ��� Ҫ��Ϊ10��������
    case 3://ʹ�ý��ƴ��� Ҫ��Ϊ16��������
    case 4://�����ʽ����
        //msg.setText(WaringMsg+tr("�����ʽ����"));
        //msg.exec();
        //pLineEdit->setFocus();
        //pSpinBox->setFocus();
        return 0;

    case 5://�Ĵ������Ͳ�ƥ�����
        //msg.setText(WaringMsg+tr("�Ĵ����������ַҪ��ƥ�䣡"));
        //msg.exec();
        //pLineEdit->setFocus();
        pSpinBox->setFocus();
        return 0;

    case 6://�ֶ������ַ����ʱ��û�и�����
        //msg.setText(WaringMsg+tr("û����Ӹ����ӿڣ�"));
        //msg.exec();
        //pLineEdit->setFocus();
        //pSpinBox->setFocus();
        return 0;

    default://���ݳ��� ����ֵΪ����ֵ ����Ϊ�����ֵ ����Ϊ�����ֵ
        if(iFlg<0)
        {
            msg.setText(WaringMsg+tr("�üĴ�������С��ַΪ��")+QString::number(0-iFlg));
        }
        else if(iFlg>0)
        {
            msg.setText(WaringMsg+tr("�üĴ���������ַΪ��")+QString::number(iFlg));
        }
        //msg.exec();
        //pLineEdit->setFocus();
        //pSpinBox->setFocus();
        return 0;
    }
    keyboard.nAddrType = Addr_Type; //��¼��λ��ʾ
    pLineEdit->setText(keyboard.sShowAddr);
    lib.unload();//�ͷ�dll�ļ�
    return 1;
}

//��׼�������ϵĵ���¼�
void MainWindow::on_action_36_triggered()
{
    if(!ui->action_36->isChecked())
    {
        ui->standardToolBar->setVisible(false);
    }
    else
    {
        ui->standardToolBar->setVisible(true);
    }
}

//��ͼ�������ϵĵ���¼�
void MainWindow::on_action_37_triggered()
{
    if(!ui->action_37->isChecked())
    {
        ui->mapToolBar->setVisible(false);
    }
    else
    {
        ui->mapToolBar->setVisible(true);
    }
}

//����������ϵĵ���¼�
void MainWindow::on_action_38_triggered()
{
    if(!ui->action_38->isChecked())
    {
        //ui->thingToolBar->setVisible(false);
    }
    else
    {
      //  ui->thingToolBar->setVisible(true);
    }
}

//���Թ������ϵĵ���¼�
void MainWindow::on_action_39_triggered()
{
    /*
	if(!ui->action_39->isChecked())
	{
        ui->dockWidget->setVisible(false);
	}
	else
	{
		ui->dockWidget->setVisible(true);
        ui->dockWidget->setFloating(true);
        QRect  rcdock =  geometry();
        ui->dockWidget->setGeometry(rcdock.right()-181,120,161,291);
        ui->dockWidget->setFixedSize(161,291);
	}
    */
}

//��׼״̬���ϵĵ���¼�
void MainWindow::on_action_40_triggered()
{
    if(!ui->action_40->isChecked())
    {
        ui->statusBar->setVisible(false);
    }
    else
    {
        ui->statusBar->setVisible(true);
    }
}

//��Ϣ������ڵĵ���¼�
void MainWindow::on_action_41_triggered()
{
    if(!ui->action_41->isChecked())
    {
       m_rightDock->setVisible(false);
    }
    else
    {
        m_rightDock->setVisible(true);
    }
}

//���̹������ĵ���¼�
void MainWindow::on_action_42_triggered()
{
    if(!ui->action_42->isChecked())
    {
        m_leftDock->setVisible(false);
    }
    else
    {
        m_leftDock->setVisible(true);
    }
}

void MainWindow::on_action_tool_triggered()
{
    if(!ui->action_tool->isChecked())
    {
        m_toolDock->setVisible(false);
    }
    else
    {
        m_toolDock->setVisible(true);
    }
}

//�˵�����Ļ�������
/*void MainWindow::on_action_93_triggered()
{
    newscreen_property();
}*/

//�˵������ɾ������
/*void MainWindow::on_action_94_triggered()
{
    newscreen_delete();
}*/

//��ʾ��ŶԻ���
void MainWindow::showNumDlg_ScreenAndWindow(QString str,QTreeWidgetItem *parentItem)
{
//   QString sTmp= parentItem->text(0).split(":").at(0);
//   int nTmp=0;
//   QString ss="";
//   if(sTmp=="000")
//   {
//      nTmp=0;
//   }
//   else
//   {
//      ss=remove_leftZero(sTmp);
//      nTmp=ss.toInt(0,10);
  //
    nActiveSheetIndex=this->nFindActiveSheetIndex(parentItem->text(0));
    QList<QGraphicsItem *> Items;
    QGraphicsItem *pItem;
    QStringList sList;
    Items = pSceneSheet[nActiveSheetIndex]->items();    //��ǰҳ�����е�item
    for(int j = 0; j < Items.size(); j++)   //ɨ�赱ǰҳ������пؼ�
    {
        pItem = Items.at(j);
        if(pItem->parentItem())
            continue;

        sList = pItem->data(GROUP_DATALIST_KEY).toStringList();
        if(sList.size() > 20)//if(!sList.isEmpty())
        {
            QString sNo = sList.at(19);
            if(sNo == str)
            {
                if(pwnd->pSceneSheet[nActiveSheetIndex]->nIsSceneOrWindow ==0)
                {
                    /*QString strDest;
                    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
                    handleWinTitle(strDest, strtemp);
                    pwnd->setWindowTitle(strDest);*/
                    pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2"AK_FILE_END"--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                                         arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
                }
                else  if(pwnd->pSceneSheet[nActiveSheetIndex]->nIsSceneOrWindow ==1)
                {
                    /*QString strDest;
                    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
                    handleWinTitle(strDest, strtemp);
                    pwnd->setWindowTitle(strDest);*/
                    pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2"AK_FILE_END"--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                                         arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
                }

                pView->setScene(pSceneSheet[nActiveSheetIndex]);
                pSceneSheet[nActiveSheetIndex]->clearSelection();
                pItem->setSelected(true);
                this->SlotItemDBClick(pItem);
            }
        }
    }
}//

QString MainWindow::remove_leftZero(QString sTmp)//�Ƴ��ַ�����ߵ�0
{
    QString str = sTmp;
    if(str.left(1)=="0")
    {
        str=str.right(str.length()-1);
        remove_leftZero(str);
    }
    else
    {
       return str;
    }
  //  return str;
}
void MainWindow::OnCopyItem()
{
	pSceneSheet[nActiveSheetIndex]->actionCopy();
}
void MainWindow::OnPasteItem()
{
	pSceneSheet[nActiveSheetIndex]->actionPaste();
}

void MainWindow::reTree_ScreenAndWindow()
{
    for(int i=0;i<label.size();i++)
    {
        if(label[i])
        {
            delete  label[i];
            label[i]=NULL;
        }

    }
    label.clear();
    for(int i=0;i<titlelabel.size();i++)
    {
        if(titlelabel[i])
        {
            delete titlelabel[i];
            titlelabel[i]=NULL;
        }

    }
    titlelabel.clear();
    for(int i=0;i<priviewWidget.size();i++)
    {
        if(priviewWidget[i])
        {
            delete  priviewWidget[i];
            priviewWidget[i]=NULL;
        }

    }
    priviewWidget.clear();

    delete  copyScreen_Item;
    copyScreen_Item=NULL;
    delete  copyWindow_Item;
    copyWindow_Item=NULL;

    copyScreen_Item=new QTreeWidgetItem() ;
    copyWindow_Item=new QTreeWidgetItem() ;
    screen->setHidden(false);
    window->setHidden(false);
    //ɾ���Զ�����������Ϣ

    if(copyUserKeyboard)
    {
        delete copyUserKeyboard;
        copyUserKeyboard=NULL;
    }
    copyUserKeyboard=new QTreeWidgetItem() ;
    pwnd->TreeKeyboard->takeChildren();
    TreeKeyboard->setHidden(true);

	int totalSceneNum = pSceneSheet.size();
	for(int i=0;i<totalSceneNum;i++)
	{
        if(newScreen[i])
        {
            delete newScreen[i];
            newScreen[i]=NULL;
        }
	}
    //czq
    //pwnd->hisdatalog_child->setHidden(true);
    //XXXXX
    /*this->link->takeChildren();//�Ƴ������������е�����
    pwnd->vTreeLinkType.clear();//�������
       for(int i=0;i<screenSubItem_vector.size();i++)
    {
        delete screenSubItem_vector[i];
        screenSubItem_vector[i]=NULL;
    }
    screenSubItem_vector.clear();*/

    //tree->collapseAll();
    tree0->collapseAll();

    int digitSize = m_pSamSysParame->m_qvcAlarm.size();
    for(int i = 0; i < digitSize; i++)
    {
        if(digital_treeItem[i])
        {
            delete digital_treeItem[i];
            digital_treeItem[i] = NULL;
        }
    }
    m_pSamSysParame->m_qvcAlarm.clear();

    int analogSize = m_pSamSysParame->m_qvcAlarm.size();
    for(int i = 0; i < analogSize; i++)
    {
        if(analog_treeItem[i])
        {
            delete analog_treeItem[i];
            analog_treeItem[i] = NULL;
        }
    }
    m_pSamSysParame->m_qvcAlarm.clear();

    nCurrentDigitalAlarmIndex=0;
    nCurrentAnalog_alarmIndex=0;

    m_pSamSysParame->m_qvcRecipe.clear();

    for(int i=0;i<pSceneSheet.size();i++)
    {
        delete pSceneSheet[i];
        pSceneSheet[i]=NULL;
    }
	pSceneSheet.clear();
    //XXXXX
    //languagedlg->deleteLater();
    //languagedlg=NULL;

    undoStack->clear();
    pwnd->lab_control_statusBar->setText("");
    pwnd->lab_width_space_statusBar->setText("");
    pwnd->lab_hidth_space_statusBar->setText("");
    pwnd->lab_left_space_statusBar->setText("");
    pwnd->lab_up_space_statusBar->setText("");

    pwnd->lab_control_statusBar->setEnabled(false);
    pwnd->lab_width_space_statusBar->setEnabled(false);
    pwnd->lab_hidth_space_statusBar->setEnabled(false);
    pwnd->lab_left_space_statusBar->setEnabled(false);
    pwnd->lab_up_space_statusBar->setEnabled(false);
}//

void MainWindow::openPro_reTreeCtl()//�򿪹���ʱˢ�����οؼ�
{
    tree->expandAll();
    tree0->expandAll();

    QString temp="";
    QList<QGraphicsItem *> Items;
    //QList<QGraphicsItem *> ChildItems;
    QGraphicsItem *pItem;
    //QStringList sList;
    //QString sNo="";
    //�������
    QList<QTreeWidgetItem *> huamian = screen->takeChildren();
    huamian.clear();

    int nKey=0;
    int index=0;
    int totalSceneNum = pSceneSheet.size();
    for(int i=0;i<totalSceneNum;i++)
    {
        //int ntemp=screen->childCount()+window->childCount();
		temp = pSceneSheet[i]->sNumberName;
        //temp=QString("%1%2%3").arg((ntemp)/100).arg(((ntemp)%100)/10).arg((ntemp)%10);
        if(pSceneSheet[i]->nIsSceneOrWindow ==0)//����0λ����
        {
			
            newScreen[i]=new QTreeWidgetItem(screen,QStringList(temp+":"+pSceneSheet[i]->sNewScreenName));
            screen->addChild(newScreen[i]);
            Items = pSceneSheet[i]->items();    //��ǰҳ�����е�item
            index=i;
            for(int j = 0; j < Items.size(); j++)   //ɨ�赱ǰҳ������пؼ�
            {
                pItem = Items.at(j);
                nKey=pItem->data(GROUP_TYPE_KEY).toInt(); //ȡ��keyֵ
                if(nKey!=USER_DEFINE_GROUP)
                {
                    UserGroup(pItem,index);
                }
            }//
        }
        else if(pSceneSheet[i]->nIsSceneOrWindow ==1)
        {
            newScreen[i]=new QTreeWidgetItem(window,QStringList(temp+":"+pSceneSheet[i]->sNewScreenName));
            screen->addChild(newScreen[i]);
            Items = pSceneSheet[i]->items();
            index=i;//��ǰҳ�����е�item
            for(int j = 0; j < Items.size(); j++)   //ɨ�赱ǰҳ������пؼ�
            {
                pItem = Items.at(j);
                nKey=pItem->data(GROUP_TYPE_KEY).toInt(); //ȡ��keyֵ
                if(nKey!=USER_DEFINE_GROUP)
                {
                    UserGroup(pItem,index);
                }
            }
        }//
        else if(pSceneSheet[i]->nIsSceneOrWindow ==2)//�û��Զ������
        {
            int nkeyboard=TreeKeyboard->childCount();
            temp=QString("%1%2%3").arg((nkeyboard)/100).arg(((nkeyboard)%100)/10).arg((nkeyboard)%10);
            newScreen[i]=new QTreeWidgetItem(TreeKeyboard,QStringList(temp+":"+pSceneSheet[i]->sNewScreenName));
            TreeKeyboard->addChild(newScreen[i]);
        }

        //list_style
        for(int i=0;i<screenSubItem_vector.size();i++)
        {
            screenSubItem_vector.at(i)->setHidden(true);
        }
        /*if(list_style->currentIndex()==0||list_style->currentIndex()==2)
        {
            for(int i=0;i<screenSubItem_vector.size();i++)
            {
                screenSubItem_vector.at(i)->setHidden(true);
            }
        }
        else if(list_style->currentIndex()==1)
        {
            for(int i=0;i<screenSubItem_vector.size();i++)
            {
                screenSubItem_vector.at(i)->setHidden(true);
            }
        }*/
    }

    pwnd->reOpenPro();

    //��λ����
    int ndigital=0;
    int nanalog=0;
    QString sTmp="";
    for(int i=0;i<alarm_name.size();i++)
    {
        if(alarm_style.at(i)==0)
        {
            //sTmp=alarm_name.at(i).split(":").at(0);
            //nTmp=sTmp.toInt();
            digital_treeItem[ndigital]=new QTreeWidgetItem(alarmlog,QStringList(alarm_name.at(i)));
            digital_treeItem[ndigital]->setIcon(0,QIcon(":/btn/images/balarm.ico"));
            alarmlog->addChild(digital_treeItem[ndigital]);
            ndigital++;
        }
        else if(alarm_style.at(i)==1)
        {
            //sTmp=alarm_name.at(i).split(":").at(0);
            //nTmp=sTmp.toInt();
            analog_treeItem[nanalog]=new QTreeWidgetItem(alarmlog,QStringList(alarm_name.at(i)));
            analog_treeItem[nanalog]->setIcon(0,QIcon(":/btn/images/walarm.ico"));
            alarmlog->addChild(analog_treeItem[nanalog]);
            nanalog++;
        }
    }

    QList<QTreeWidgetItem *> childItem = recipe->takeChildren();
    childItem.clear();

    if(pwnd->m_pSamSysParame->m_qvcRecipe.size() > 0)
    {
        for(int i = 0; i < pwnd->m_pSamSysParame->m_qvcRecipe.size(); i++)
        {
            QTreeWidgetItem *pRecipe=new QTreeWidgetItem(recipe,QStringList(pwnd->m_pSamSysParame->m_qvcRecipe[i].sName));
            recipe->addChild(pRecipe);
            pRecipe->setIcon(0,QIcon(":/tree/images/tree/recipe.ico"));
        }
    }

    //����
    QList<QTreeWidgetItem *> childItems = link->takeChildren();
    childItems.clear();

    //int connect = 0;
    if(pwnd->getProVersion() >= 2727)
    {
        int connect=pwnd->m_pSamSysParame->m_qvcConnect.size();
        for(int i=0;i<connect;i++)
        {
            QTreeWidgetItem *links=new QTreeWidgetItem(link,QStringList(pwnd->m_pSamSysParame->m_qvcConnect[i].sConnectName));
            link->addChild(links);
            links->setIcon(0,QIcon(":/tree/images/tree/com.ico"));

            int xieyi=pwnd->m_pSamSysParame->m_qvcConnect[i].vProtocols.size();
            for(int j=0;j<xieyi;j++){
                QTreeWidgetItem *xieyis=new QTreeWidgetItem(link->child(i),QStringList(pwnd->m_pSamSysParame->m_qvcConnect[i].vProtocols[j].sName));
                link->child(i)->addChild(xieyis);
                xieyis->setIcon(0,QIcon(":/tree/images/tree/com.ico"));
            }
        }

        if(!m_pSamSysParame->m_mixGlobalVar.m_strCom1.contains(tr("com1")))
        {
            link->child(0)->setDisabled(true);
        }
        if(!m_pSamSysParame->m_mixGlobalVar.m_strCom1.contains(tr("com2")))
        {
            link->child(1)->setDisabled(true);
        }
        if(!m_pSamSysParame->m_mixGlobalVar.m_strCom1.contains(tr("com3")))
        {
            link->child(2)->setDisabled(true);
        }
        if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strMaxscreennumber.contains("Ethernet(NONE)"))
        {
            link->child(3)->setDisabled(true);
        }
        if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom2.contains("NONE"))
        {
            link->child(4)->setDisabled(true);
            if(link->childCount() > 5)
                link->child(5)->setDisabled(true);
        }
    }
    else//�ɰ汾
    {
        int connect = pwnd->m_pSamSysParame->m_qvcConnect.size();
        if(connect < 5)
        {
            stConnect con;
            //con.sConnectName = tr("��̫��");
            //con.eConnectPort = i;//com1
            con.bUseRelationPort = false;//Ĭ�ϲ�ת��
            con.eRelationPort = 0;
            con.nScreenNo = 1;
            con.nBaudRate = 9600;
            con.nDataBits = 1;
            con.nStopBit = 0;
            con.nCheckType = 0;
            con.bMasterScreen      = 1;//����
            con.bConnectScreenPort = 0;//����PLC��
            con.nSlaveScreenNum    = 1;
            //con.nIntervalTime = 1;
            con.sIpAddr = QString("192.168.1.1");
            con.nNetPortNum = 12345;

            if(4 == connect)
            {
                con.sConnectName = tr("CAN����");
                con.eConnectPort = 4;//CAN����
                pwnd->m_pSamSysParame->m_qvcConnect.push_back(con);
            }
            else if(3 == connect)
            {
                QVector<stConnect > VecConnect = pwnd->m_pSamSysParame->m_qvcConnect;
                con.sConnectName = tr("Com3");
                con.eConnectPort = 2;
                pwnd->m_pSamSysParame->m_qvcConnect.pop_back();
                pwnd->m_pSamSysParame->m_qvcConnect.push_back(con);
                //con.sConnectName = tr("Com3");
                con.eConnectPort = 3;
                pwnd->m_pSamSysParame->m_qvcConnect.push_back(VecConnect.at(2));
                con.sConnectName = tr("CAN����");
                con.eConnectPort = 4;//CAN����
                pwnd->m_pSamSysParame->m_qvcConnect.push_back(con);
            }

            connect = 5;
        }

        for(int i = 0; i < connect; i++)
        {
            QTreeWidgetItem *links=new QTreeWidgetItem(link,QStringList(pwnd->m_pSamSysParame->m_qvcConnect[i].sConnectName));
            link->addChild(links);
            links->setIcon(0,QIcon(":/tree/images/tree/com.ico"));

            int xieyi=pwnd->m_pSamSysParame->m_qvcConnect[i].vProtocols.size();
            for(int j=0;j<xieyi;j++){
                QTreeWidgetItem *xieyis=new QTreeWidgetItem(link->child(i),QStringList(pwnd->m_pSamSysParame->m_qvcConnect[i].vProtocols[j].sName));
                link->child(i)->addChild(xieyis);
                xieyis->setIcon(0,QIcon(":/tree/images/tree/com.ico"));
            }
        }

        if(!m_pSamSysParame->m_mixGlobalVar.m_strCom1.contains(tr("com1")))
        {
            link->child(0)->setDisabled(true);
        }
        if(!m_pSamSysParame->m_mixGlobalVar.m_strCom1.contains(tr("com2")))
        {
            link->child(1)->setDisabled(true);
        }
        if(!m_pSamSysParame->m_mixGlobalVar.m_strCom1.contains(tr("com3")))
        {
            link->child(2)->setDisabled(true);
        }
        if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strMaxscreennumber.contains("Ethernet(NONE)"))
        {
            link->child(3)->setDisabled(true);
        }
        if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom2.contains("NONE"))
        {
            link->child(4)->setDisabled(true);
            if(link->childCount() > 5)
                link->child(5)->setDisabled(true);
        }
    }

    //������½
    QList<QTreeWidgetItem *> baojingItem = alarmlog->takeChildren();
    baojingItem.clear();

    int baojingCount=pwnd->m_pSamSysParame->m_qvcAlarm.size();
    for(int i=0;i<baojingCount;i++){
        QTreeWidgetItem *baojings=new QTreeWidgetItem(alarmlog,QStringList(pwnd->m_pSamSysParame->m_qvcAlarm[i].alarmName));
        alarmlog->addChild(baojings);
        baojings->setIcon(0,QIcon(":/btn/images/alarm.ico"));
    }


    //���ݲɼ�
    QList<QTreeWidgetItem *> shujucaiji = tree_hisdatalog->takeChildren();
    shujucaiji.clear();
    int caijiCount=pwnd->m_pSamSysParame->m_vecDataSamplingStr.size();
    for(int i=0;i<caijiCount;i++){
        QTreeWidgetItem *caijis=new QTreeWidgetItem(tree_hisdatalog,QStringList(pwnd->m_pSamSysParame->m_vecDataSamplingStr[i]));
        tree_hisdatalog->addChild(caijis);
        m_vecHisdatalogChild.push_back(caijis);
        caijis->setIcon(0,QIcon(":/tree/images/tree/hisdata.ico"));
    }

}//

void MainWindow::UserGroup(QGraphicsItem *pItem,int index )//�򿪵�ʱ������Ϥ��ţ����Զ�����ϵĿռ䣩
{
    QStringList sList;
    QString sNo="";
    sList = pItem->data(GROUP_DATALIST_KEY).toStringList();
    if(sList.size() > 20)//if(!sList.isEmpty())
    {
         sNo = sList.at(19);
         if(sNo!="")
         {
             screenSubItem_vector.push_back(new QTreeWidgetItem(newScreen[index],QStringList(sNo)));;
             newScreen[index]->addChild(screenSubItem_vector.at(screenSubItem_vector.size()-1));
         }

     }
}
void MainWindow::reOpenPro()
{
    //list_style
    //if(list_style->currentIndex()==0)
    {
         upDatetreeScreenItem();//���»��������
    }
    /*else if(list_style->currentIndex()==1)
    {
        upDatetreeScreenItem();//���»��������
    }
    else
    {
        updateAllPreviewWindow();// PreviewWindow();
    }*/
}//
void MainWindow::deleteItem_undefineGroup(QGraphicsItem * pItem)
{
     int id=0;
     QStringList sList;
     QString sNo="";
     QString sTmp="";
     QList<QGraphicsItem *> childItems;
     id=pItem->data(GROUP_TYPE_KEY).toInt();
     if(id==USER_DEFINE_GROUP)
     {
        childItems=pItem->childItems();
        for(int i=0;i<childItems.size();i++)
        {
            deleteItem_undefineGroup(childItems.at(i));
        }
    }
    else
    {
        sList = pItem->data(GROUP_DATALIST_KEY).toStringList(); //ȡ��ÿ��item����������
        if(sList.size() > 20)//if(!sList.isEmpty())
        {
            sTmp=sList.at(19);
            for(int i=0;i<screenSubItem_vector.size();i++)
            {
                sNo=screenSubItem_vector.at(i)->text(0);
                if(sNo==sTmp)
                {
                    screenSubItem_vector.remove(i);
                }
            }//
            int totalSceneNum = pSceneSheet.size();
            for(int j=0;j<totalSceneNum;j++)
            {
                for(int i=0;i<newScreen[j]->childCount();i++)
                {
                    sNo= newScreen[j]->child(i)->text(0);
                    if(sNo==sTmp)
                    {
                        delete newScreen[j]->child(i);
                        //newScreen[j]->child(i)=NULL;
                    }
                }
            }//

            for(int j=0;j<copyScreen_Item->childCount();j++)
            {
                for(int i=0;i<copyScreen_Item->child(j)->childCount();i++)
                {
                    sNo=copyScreen_Item->child(j)->child(i)->text(0);
                    if(sTmp==sNo)
                    {
                        copyScreen_Item->child(j)->removeChild(copyScreen_Item->child(j)->child(i));
                    }
                }
            }//
            for(int j=0;j<copyWindow_Item->childCount();j++)
            {
                for(int i=0;i<copyWindow_Item->child(j)->childCount();i++)
                {
                    sNo=copyWindow_Item->child(j)->child(i)->text(0);
                    if(sTmp==sNo)
                    {
                        copyWindow_Item->child(j)->removeChild(copyWindow_Item->child(j)->child(i));
                    }
                }
            }//
        }//
    }
}
void MainWindow::deleteItem_upDateTreeContrl(QList<QGraphicsItem *> list)
{
    QGraphicsItem *pItem;
    for(int i=0;i<list.size();i++)
    {
        pItem=list.at(i);
        deleteItem_undefineGroup(pItem);
     }
}//

/*void MainWindow::OnTrendChartDlg(QGraphicsItem *item)
{
    QTrendChartDlg *trendChartDlg=new QTrendChartDlg(item,this);
    if(trendChartDlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = trendChartDlg->pCopyItem;
        OnDoubleClik(item,oldItem);
        //pSceneSheet[nActiveSheetIndex]->removeItem(item);//�Ƴ���ITEM
    }
    trendChartDlg->deleteLater();
    trendChartDlg = NULL;
}*/
/*void MainWindow::createtrendchartdlg()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED)
    {
        return;
    }

    //QTrendChartDlg *trendchart=new QTrendChartDlg(0,this);
    QTrend *trendchart = new QTrend(0,this);
    if( trendchart->exec() == QDialog::Accepted)
    {
        //QGraphicsItem * oldItem = trendchart->pCopyItem;
        QGraphicsItem * oldItem = trendchart->m_pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    trendchart->deleteLater();
    trendchart = NULL;
}*/
void MainWindow::OnTrendChartDlg(QGraphicsItem *item)
{
    //QTrendChartDlg *trendChartDlg = new QTrendChartDlg(item,this);
    QTrend *trendchart = new QTrend((QTrendAttr *)item,this);

    if(trendchart->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = trendchart->m_pCopyItem;
        OnDoubleClik(item,oldItem);
        //pSceneSheet[nActiveSheetIndex]->removeItem(item);//�Ƴ���ITEM
    }

    trendchart->deleteLater();
    trendchart = NULL;
}

void MainWindow::OnXYTrendChartDlg(QGraphicsItem *item)
{
    XYTrendDlg *XYtrendChartDlg=new XYTrendDlg(dynamic_cast<XYtrend *>(item),this);
    if(XYtrendChartDlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = XYtrendChartDlg->m_pCopyItem;
        OnDoubleClik(item,oldItem);
       // pSceneSheet[nActiveSheetIndex]->removeItem(item);//�Ƴ���ITEM

    }
    XYtrendChartDlg->deleteLater();
    XYtrendChartDlg = NULL;
}

//�����������̣�
//1�����������ݵ���ȷ�ԣ����ַ��
//2������ȫ�ֲ������֣�����ϵͳ�������������䷽�����ݲɼ�
//3�����뻭���Ѿ�item
//4�����벢��ȡitem��ͼƬ�ļ�
bool MainWindow::USBCompile(QSqlDatabase &db,bool bsimulator) //����
{
    int counter = 0;
    QDir compiledir = QDir("compile");
    if(!compiledir.exists())
    {
        compiledir.mkpath(compiledir.absolutePath());
    }

    mPicPath.clear();
    mLibPathInfo.mLibPath.clear();
    mLibPathInfo.mLibSize.clear();
    addrsInScene.clear();
    vAllDbQuery.clear();

    //����������̬

    emit SignalInformation(tr("׼����̬����..."), MSG_NORMAL);

    if(m_pSamSysParame->m_mixGlobalVar.m_bUpLoad)
    {
        qDebug() << "compile\\upLoad.akr";
        compressFile("compile\\upLoad.akr");
    }



    deleteDirectory(QFileInfo("resource"));
    mPicPath.clear();
    deleteDirectory(QFileInfo("sdmacro\\jsrc\\jml"));
    deleteDirectory(QFileInfo("sdmacro\\jsrc\\jrl"));
    QFile::remove("sdmacro\\ml\\ml.jar");


#ifdef AKPLC
    emit SignalInformation(tr("����PLC����..."), MSG_NORMAL);

    if(!compilePlcPrj())
    {
        emit SignalInformation(tr("����PLC�������..."), MSG_ERROR);
        QFile::remove("gEKip");
        return false;
    }
#endif

    emit SignalInformation(tr("��ȡ�ؼ�����..."), MSG_NORMAL);
    //ϵͳ�������ֱ����������ݿ��ļ�

    //ͬ����ʼ�ű�����߳�
    MacroCmptrd *macroTrd = NULL;
    bool needCmpMacro = false;
    foreach(Macro lib, macros)
    {
        if(lib.isCompiled())
        {
            needCmpMacro = true;
            break;
        }
    }
    if(needCmpMacro)
    {
        qDebug() << "start compress librarys";
        macroTrd = new MacroCmptrd();//�ű�����߳�
        macroTrd->startCompress(macros);
    }


    m_pSamSysParame->compile(db,counter,bsimulator);

    compileVarTable(db,counter);
    compileInitLibrary(db,counter);
    compileGlobalLibrary(db,counter);

    //�ռ�ϵͳ�������ֵĵ�ַ
    addrsInSysPrarm = addrsInScene;


    qDebug() << "addrsInScene  1"<<addrsInScene.keys();
    //�������ֵı���
    int totalNum = pSceneSheet.size();
    //int sceneId,UserKeyboardId;
    for(int i = 0,sceneId = 0,UserKeyboardId = 0; i < totalNum; i++)
    {
        int index;
        addrsInScene.clear();
        //qDebug()<<"nIsSceneOrWindow = " << pSceneSheet[i]->nIsSceneOrWindow;
        if(pSceneSheet[i]->nIsSceneOrWindow == 2)// ���Զ������
        {
            UserKeyboardId++;
            index = UserKeyboardId;
        }
        else                                                     //�Ǵ��ڻ��߻���
        {
            sceneId++;
            index = sceneId;
        }
        pSceneSheet[i]->compile(db,index, counter);

		//�ռ������ؼ����ֵĵ�ַ
        addrsInScene = addrsInScene+addrsInSysPrarm;
        //qDebug() << "addrsInScene  "<<addrsInScene.keys();
		compileArrangeAddr(db,index);
    }

    emit SignalInformation(tr("���������..."), MSG_NORMAL);
	getAllFontNames(db);

    emit SignalInformation(tr("����ű���..."), MSG_NORMAL);

    if(macroTrd)
    {
        bool bResult = false;
        QString macroName;
        if(macroTrd->wait(300000))//��������
        {
            bResult = macroTrd->bSucess;
            macroName = macroTrd->m_strLibName;
            if(!bResult)
            {
                QString strError = QString(tr("����ű���:%1 ����...")).arg(macroName);
                emit SignalInformation(strError, MSG_ERROR);
            }
        }
        else//�ű������ʱ
        {
            emit SignalInformation(tr("����ű���ʱ"), MSG_ERROR);
        }

        if(!bResult)
        {
            QFile::remove("gEKip");
            QFile::remove("sdmacro\\ml\\ml.jar");
            emit SignalInformation(tr("����ʧ��..."), MSG_ERROR);
            isCompiled = false;
            return false;
        }
    }

    emit SignalInformation(tr("����ɹ�..."), MSG_NORMAL);
    isCompiled = false;
    return true;
}

//��ַ��������
void MainWindow::compileArrangeAddr(QSqlDatabase &db,int nSceneId)
{
	QList <QString> plcNames = addrsInScene.keys();

	QList<addrTargetProp> addPrarms;

	QVector<QString> vNames;
	foreach(QString key,plcNames)
	{
        //qDebug() << "PLC names "<< key;
		if (!vNames.contains(key))
		{
			vNames << key;
		}
	}
	std::vector<addrTargetProp> arrandgedAddrs;
	stProtocol cModel;// ��ǰ���豸
	int connectType = -1;
	foreach(QString plcName,vNames)
	{
		addPrarms = addrsInScene.values(plcName);
		cModel = getPlcModel(plcName,connectType);
		if (cModel.sName.isEmpty())
		{
			continue;
		}
		arrandgedAddrs = getArrangedAddrs(cModel,addPrarms.toVector().toStdVector());
		complieArranged(db, nSceneId,connectType,cModel,arrandgedAddrs);
	}
}
void MainWindow::OnHISTrendChartDlg(QGraphicsItem *item)
{

}

//��������vector �������ݿ�
void MainWindow::complieArranged(QSqlDatabase &db,int nSceneId,int nConnectType,
					 stProtocol cModel,std::vector<addrTargetProp>addrs)
{
	QSqlQuery sqlquery(db);
    sqlquery.prepare("INSERT INTO arrangeAddr(nSceneId ,eItemType,eConnectType ,nUserPlcId ,sPlcProtocol ,"
		"nPlcStationIndex ,nPlcRegIndex ,nPlcStartAddr ,nAddrLen ,eRwLevel)"
		"VALUES (:nSceneId ,:eItemType, :eConnectType ,:nUserPlcId,:sPlcProtocol ,:nPlcStationIndex ,"
		":nPlcRegIndex ,:nPlcStartAddr ,:nAddrLen ,:eRwLevel)");
	bool result = false;
	foreach(addrTargetProp addrprop,addrs)
	{
		sqlquery.bindValue(":nSceneId",QVariant(nSceneId));// ��������򴰿����
        sqlquery.bindValue(":eItemType",QVariant(OBJ_ITEM));
        sqlquery.bindValue(":eConnectType",QVariant(nConnectType));
        sqlquery.bindValue(":nUserPlcId",QVariant(addrprop.nUserPlcId));
		sqlquery.bindValue(":sPlcProtocol",QVariant(cModel.sProtocolName));
		sqlquery.bindValue(":nPlcStationIndex",QVariant(addrprop.nPlcStationIndex));
		sqlquery.bindValue(":nPlcRegIndex",QVariant(addrprop.nRegIndex));
		sqlquery.bindValue(":nPlcStartAddr",QVariant(addrprop.nAddrValue));
		sqlquery.bindValue(":nAddrLen",QVariant(addrprop.nAddrLen));
		sqlquery.bindValue(":eRwLevel",QVariant(addrprop.eAddrRWprop));

		
		result = sqlquery.exec();
		qDebug() << "insert arrangeAddr table :" << result << endl;
	}
	
	
}
stProtocol MainWindow::getPlcModel(QString name,int &connectType)
{
	bool bExist = false;

	stProtocol cModel;// ��ǰ���豸
	foreach (stConnect cnt,m_pSamSysParame->m_qvcConnect)
	{
		foreach(stProtocol ptl,cnt.vProtocols)
		{
			if (ptl.sName.compare(name,Qt::CaseInsensitive) == 0)
			{
				bExist = true;
				cModel = ptl;
				break;
			}
		}
		if (bExist)
		{
			connectType = cnt.eConnectPort;
			break;
		}
	}
	switch (connectType)
	{
	case 0:
#ifdef AKPLC
        connectType = 4;
#else
        connectType = 3;
#endif
		break;
	case 1:
		connectType = 4;
		break;
    case 2://COM3
        connectType = 5;
		break;
    case 3://��̫��
        connectType = 8;
        break;
    case 4://CAN1
        connectType = 14;
        break;
    case 5://CAN2
        connectType = 15;
        break;
	default:
		break;
	}
	return cModel;
}
//����Э���ļ�����vector ���е�ַ��������
std::vector<addrTargetProp> MainWindow::getArrangedAddrs(stProtocol cModel,
										std::vector<addrTargetProp> addrs)
{	  
	int nMaxRWlen = cModel.nMaxRWLen;
	std::vector<addrTargetProp> tgAddrs;
    QString path = "Drivers/qtdll/"+cModel.sFactoryName +"/"+cModel.sProtocolName+".dll";
	QLibrary lib(path);


	if(lib.load())
	{
        typedef bool (*ADDPROC)(std::vector<addrTargetProp> , std::vector<addrTargetProp> &,int,bool);
		ADDPROC getAddrs= (ADDPROC)lib.resolve("sortOutAddrList");
		if(getAddrs)
		{
            getAddrs(addrs,tgAddrs,nMaxRWlen,false);
		}
		lib.unload();
	}
	return tgAddrs;
}

void MainWindow::getAllFontNames(QSqlDatabase &db)
{
    QStringList  fontNames;
    int totalNum = pSceneSheet.size();

    m_fontMap.clear();
    for(int i = 0; i < totalNum; i++)
    {
        QList<QGraphicsItem *>itemList = pSceneSheet[i]->TopItems();
        foreach(QGraphicsItem* pItem,itemList)
        {
            int type = pItem->type();
            if (type == SAM_DRAW_OBJECT_GROUP)
            {
                QItemGroup* pGroup = dynamic_cast<QItemGroup *>(pItem);
                if (pGroup)
                {
                    fontNames << pGroup->getAllFonts();
                    //qDebug() << pSceneSheet[i]->sNewScreenName;
                    //qDebug() << pGroup->getItemName()<< pGroup->getAllFonts();
                }
            }
        }
    }

    fontNames.removeDuplicates();
    foreach(QString sFont,fontNames)
    {
        if(sFont == tr("Droid Sans Fallback"))
        {
            continue;
        }
        QString fontfile = GetFontFile(sFont);
        if (fontfile.isEmpty())
        {
            initFontMap();
            fontfile = sysFontMap.value(sFont);
            //qDebug() << sysFontMap;
        }
        if (!fontfile.isEmpty() && !m_fontMap.contains(sFont))
        {
            m_fontMap.insert(sFont,fontfile);
        }
    }

    //����fontmap�����ݿ�
    QSqlQuery sqlquery(db);
    sqlquery.prepare("INSERT INTO fontmap(sFontType ,sFileName )"
            "VALUES (:sFontType,:sFileName)");
    bool result = false;
    QMap<QString,QString>::const_iterator i = m_fontMap.constBegin();
    while(i != m_fontMap.constEnd())
    {
        sqlquery.bindValue(":sFontType",QVariant(i.key()));
        sqlquery.bindValue(":sFileName",QVariant(i.value()));
        ++i;
        result = sqlquery.exec();
        qDebug() << "insert fontmap table :" << result << endl;
    }
}

bool MainWindow::SaveMacro(QString sDir,QDataStream &stream)
{

    return true;
}
QString MainWindow::GetFontFile(QString sFontType)
{

    QString sFont;
    QString sTmp;
    QString fileName ="";
    QStringList list;


    QVariant v;
    QString path = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts";
    QSettings *reg = new QSettings(path,QSettings::NativeFormat);
    QStringList keys = reg->allKeys();
    foreach(QString key,keys)
    {
        list = key.split("&");
        if(list.size()>1)
        {
            fileName = "";
        }
        foreach(QString sKey,list)
        {
            sTmp = sKey.left(sKey.indexOf("("));
            sTmp = sTmp.trimmed();
            sFont = sFontType.left(sFontType.indexOf("("));
            if(sFont.contains("_GB2312"))
            {
                sFont.remove("_GB2312",Qt::CaseInsensitive);
            }
            if(sFont == sTmp)
            {
                v = reg->value(key);
                fileName =v.toString();
                return fileName;
            }
        }
    }
    return fileName;
}


void MainWindow::MessageOutEx(QString str, MSG_TYPE eType, MsgOutPut* pOutPut)
{
	int count = pMainList->rowCount();
	pMainList->insertRow(count);
    pMainList->setRowHeight(count,20);
    QTableWidgetItem * pTableWidgetItem = new QTableWidgetItem(str);
    if(pTableWidgetItem)
    {
        switch(eType)
        {
        case MSG_NORMAL://��������ɫ
            {
                pTableWidgetItem->setBackground(QBrush(QColor(255,255,255)));
                break;
            }
        case MSG_WARNING://���棬��ɫ
            {
                pTableWidgetItem->setForeground(QBrush(QColor(170,85,0)));
                break;
            }
        case MSG_ERROR://���󣬺�ɫ
            {
                pTableWidgetItem->setForeground(QBrush(QColor(255,0,0)));
                break;
            }
        default:
            {
                pTableWidgetItem->setBackground(QBrush(QColor(255,255,255)));
                break;
            }
        }
        pMainList->setItem(count,0,pTableWidgetItem);
        pMainList->setCurrentCell(count,0);

        pwnd->mapMsgOutPutItem.insert(count, pOutPut);
    }
}

void MainWindow::MessageOut(QString str, MSG_TYPE eType)
{
	int count = pMainList->rowCount();
	pMainList->insertRow(count);
    pMainList->setRowHeight(count,20);
    QTableWidgetItem * pTableWidgetItem = new QTableWidgetItem(str);
    if(pTableWidgetItem)
    {
        switch(eType)
        {
        case MSG_NORMAL://��������ɫ
            {
                pTableWidgetItem->setBackground(QBrush(QColor(255,255,255)));
                break;
            }
        case MSG_WARNING://���棬��ɫ
            {
                pTableWidgetItem->setForeground(QBrush(QColor(170,85,0)));
                break;
            }
        case MSG_ERROR://���󣬺�ɫ
            {
                pTableWidgetItem->setForeground(QBrush(QColor(255,0,0)));
                break;
            }
        default:
            {
                pTableWidgetItem->setBackground(QBrush(QColor(255,255,255)));
                break;
            }
        }
        pMainList->setItem(count,0,pTableWidgetItem);
        pMainList->setCurrentCell(count,0);
    }
}

bool MainWindow::CheckAddressInCompile()
{
    vAddrMsg.clear();
    mapMsgOutPutItem.clear();
    pMainList->clear();
    OnFillAddressMsgClass();        //����ַ��Ϣ

    int nCount = vAddrMsg.size();       //����
    QGraphicsItem *pItem;
    int i = 0;
    int j = 0;
    bool nFlag = true;
    int nIndex = 0;
    QString sAddr = "";
    QString sScreenName = "";
    QString sAddrUse = "";
    QString str = "";
    QRect rc = m_rightDock->geometry();

    int nReturnFlag = 1;
    int nType = 0;
    int nRow = 0;
    bool bReturnFlag = true;

	
	
    pMainList->setColumnCount(1);
    pMainList->setColumnWidth(0,rc.width());

	if (!checkSysParam())
	{
		return false;
	}
    if (!checkMacroName())
    {
        return false;
    }
    for(i = 0;i < nCount;i++)
    {
        pItem = vAddrMsg.at(i)->pItem;
        for(j = 0; j < vAddrMsg.at(i)->Address.size(); j++) //10
        {
            nIndex = vAddrMsg.at(i)->nSheetIndex; //�������
            //sAddr = vAddrMsg.at(i)->Address[j].addr.sShowAddr;  //ȡ��ַ
            //nType = vAddrMsg.at(i)->Address[j].addr.nAddrType; //��ַ����
            sAddr = vAddrMsg.at(i)->Address[j].pAddr->sShowAddr;  //ȡ��ַ
            nType = vAddrMsg.at(i)->Address[j].pAddr->nAddrType; //��ַ����

            if(sAddr.isEmpty())
            {
                qDebug() << "sAddr.isEmpty()";
                //sAddrUse =pwnd->vAddrMsg.at(i)->Address[j].addr.sPlcRegTypeStr;    //�ؼ�ʹ�õ�ַ����
                sAddrUse =pwnd->vAddrMsg.at(i)->Address[j].str;    //�ؼ�ʹ�õ�ַ����
                QString itemName;
                QItemGroup *itemGrp = dynamic_cast<QItemGroup *> (pItem);
                if(itemGrp)
                {
                    itemName = itemGrp->getItemName();
                }
                if (pItem)//�ؼ�
                {
                    sScreenName=tr("���� ");
                    if (pSceneSheet.size()> nIndex)
                    {
                        sScreenName = pSceneSheet[nIndex]->sNewScreenName;
                    }
                }
                else							//���̹�����
                {
                    sScreenName=tr("���̹����� "); //�����Ϣ
                }
                pMsgOutPut = new MsgOutPut ;//��Ϣ�������˫��Ҫ�������
                pMsgOutPut->pItem = pItem;
                pMsgOutPut->nSheetIndex = nIndex;

                str = tr("error:")+sScreenName+tr("-")+itemName+sAddrUse+tr("��������");
                pMainList->insertRow(nRow);
                pMainList->setRowHeight(nRow,20);
                QTableWidgetItem* pTable = new QTableWidgetItem(str);
                if(pTable)
                {
                    pTable->setBackground(QBrush(QColor(255,0,0)));
                    pMainList->setItem(nRow,0,pTable);
                }
                pMainList->setCurrentCell(nRow,0);
                mapMsgOutPutItem.insert(nRow, pMsgOutPut);
                nRow++;
                bReturnFlag = false;
                nFlag = false;
            }
            else
                nFlag = true;

            if(nFlag) //!sAddr.isEmpty()
            {

                nReturnFlag = IsAddressCheckRightInCompile(sAddr,nType); //����ַ�Ƿ���ȷ
                qDebug() << "ADDR_CHECK:" << sAddr << nType << nReturnFlag;
                if(!nReturnFlag) //��ַ����ȷ
                {
                    //sAddrUse =pwnd->vAddrMsg.at(i)->Address[j].addr.sPlcRegTypeStr;    //�ؼ�ʹ�õ�ַ����
                    sAddrUse =pwnd->vAddrMsg.at(i)->Address[j].str;    //�ؼ�ʹ�õ�ַ����
                    QString itemName;
                    QItemGroup *itemGrp = dynamic_cast<QItemGroup *> (pItem);
                    if(itemGrp)
                    {
                        itemName = itemGrp->getItemName();
                    }
                    if(pItem)//�ǿؼ��ĵ�ַ
                    {
                        sScreenName=tr("���� ");
                        if (pSceneSheet.size()> nIndex)
                        {
                            sScreenName = pSceneSheet[nIndex]->sNewScreenName;
                        }
                    }
                    else     //�ǹ��̹������е�ַ
                    {
                        sScreenName=tr("���̹����� "); //�����Ϣ
                    }

                    pMsgOutPut = new MsgOutPut ;//��Ϣ�������˫��Ҫ�������
                    pMsgOutPut->pItem = pItem;
                    pMsgOutPut->nSheetIndex = nIndex;

                    str = tr("error:")+sScreenName+tr("-")+itemName+sAddrUse+tr("��������");
                    pMainList->insertRow(nRow);
                    pMainList->setRowHeight(nRow,20);
                    QTableWidgetItem* pTable = new QTableWidgetItem(str);
                    if(pTable)
                    {
                        pTable->setBackground(QBrush(QColor(255,0,0)));
                        pMainList->setItem(nRow,0,pTable);
                    }
                    //pMainList->setItem(nRow,0,new QTableWidgetItem(str));
                    pMainList->setCurrentCell(nRow,0);
                    mapMsgOutPutItem.insert(nRow, pMsgOutPut);
                    nRow++;
                    //nFlag = false;//Flag = false;
                    bReturnFlag = false;
                }
            }
        } //end  the second for
    } //end  the first for
    return bReturnFlag ;//nFlag;
}

int MainWindow::IsAddressCheckRightInCompile(QString sAddr, int Type)
{
	int result = 0;
    Keyboard kb;
	if (CheckString(kb,sAddr,Type) == ADDR_CORRECT)
	{
		result = 1;
	}
	return result;
}

void MainWindow::FillTreeAddress()
{
    /***************HMI״̬*******************/
    pAddrMsg = new AddrMsg;
    pAddrMsg->nSheetIndex = 0;
    pAddrMsg->pItem = NULL;

    //ʱ��

    if(m_pSamSysParame->m_clockProp.bWTimeToPlc)//дʱ�䵽PLC
    {
        shareAddressCode(m_pSamSysParame->m_clockProp.mWTimeToPlc.mCtlAddr, tr("ʱ��д����Ƶ�ַ"));
        if(m_pSamSysParame->m_clockProp.mWTimeToPlc.nStartType == 1)
        {
            shareAddressCode(m_pSamSysParame->m_clockProp.mWTimeToPlc.mTriggerAddr, tr("ʱ��д�봥����ַ"));
        }
    }
    else if(m_pSamSysParame->m_clockProp.bRTimeFromPlc)//��PLCʱ����ͬ
    {
        shareAddressCode(m_pSamSysParame->m_clockProp.mRTimeFromPlc.mCtlAddr, tr("ʱ�Ӷ�ȡ���Ƶ�ַ"));
        if(m_pSamSysParame->m_clockProp.mRTimeFromPlc.nStartType == 1)
        {
            shareAddressCode(m_pSamSysParame->m_clockProp.mRTimeFromPlc.mTriggerAddr, tr("ʱ�Ӷ�ȡ������ַ"));
        }
    }

    //���ݿ���
    //�Ƿ�д��ǰ�����ŵ�PLC
    if(m_pSamSysParame->m_mixGlobalVar.m_bCurScreenNum)
    {
        shareAddressCode(m_pSamSysParame->m_mixGlobalVar.m_keyCurScreen, tr("���ݿ���-��ǰ������ ��ַ"));
    }
    //�Ƿ�д��ǰ�䷽��ŵ�PLC
    if(m_pSamSysParame->m_mixGlobalVar.m_bCurFormulaNum)
    {
        shareAddressCode(m_pSamSysParame->m_mixGlobalVar.m_keyCurFormula, tr("���ݿ���-��ǰ�䷽��� ��ַ"));
    }

    //�Ƿ�д��ǰ���Ա�ŵ�PLC
    if(m_pSamSysParame->m_mixGlobalVar.m_bCurLanguageNum)
    {
        shareAddressCode(m_pSamSysParame->m_mixGlobalVar.m_keyCurLanguage, tr("���ݿ���-��ǰ���Ա�� ��ַ"));
    }

    //�ֿ��ƻ����л�
    if(m_pSamSysParame->m_mixGlobalVar.m_bWordAddrScreenNum)
    {
        shareAddressCode(m_pSamSysParame->m_mixGlobalVar.m_keyWordAddrScreen, tr("���ݿ���-�ֵ�ַ���ƻ����л�"));
    }

    if(m_pSamSysParame->m_mixGlobalVar.m_bBitSenceExch)
    {
        for (int i=0; i<m_pSamSysParame->m_mixGlobalVar.m_vecBitSence.size();i++)
        {
            shareAddressCode(m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].mCtlSceneAddr,tr("���ݿ���-λ��ַ���ƻ����л�"));
        }
    }

    //���ݲɼ�
    int samplesize = m_pSamSysParame->m_loadDataSampling.size();
    for(int i=0; i<samplesize; i++)
    {
        DATA_SAMPLING samGrp = m_pSamSysParame->m_loadDataSampling[i];
        QString samGrpName = tr("���ݲ���");
        if(m_pSamSysParame->m_vecDataSamplingStr.size() > i)
        {
            samGrpName = m_pSamSysParame->m_vecDataSamplingStr[i];
        }
		for (int j=0; j<m_pSamSysParame->m_loadDataSampling[i].m_dataTable.size(); j++)
		{
			shareAddressCode( m_pSamSysParame->m_loadDataSampling[i].m_dataTable[j].keyAddress,
				samGrpName+tr("������ַ"));
		}
        //ȡ��֪ͨ��ַ
        if (samGrp.bFullNotic && m_pSamSysParame->m_loadDataSampling[i].nDataSampType == 2 )
        {
            shareAddressCode(m_pSamSysParame->m_loadDataSampling[i].strNoticAddrId,samGrpName+tr("ȡ��֪ͨ��ַ"));
        }
        //���Ʋ�����ַ
        if (samGrp.bAddrCtlSamp)
        {
            shareAddressCode(m_pSamSysParame->m_loadDataSampling[i].strCtlSampAddrId,samGrpName+tr("���Ʋ�����ַ"));
        }

        //��̬ʱ�䷶Χ��ַ
        if (samGrp.bDynTimeRange)
        {
            shareAddressCode(m_pSamSysParame->m_loadDataSampling[i].startTimeAddr,samGrpName+tr("������ʼʱ���ַ"));
            shareAddressCode(m_pSamSysParame->m_loadDataSampling[i].endTimeAddr,samGrpName+tr("��������ʱ���ַ"));
        }
        //��̬Ƶ�ʵ�ַ
        if (samGrp.bDynSampleRate)
        {
            shareAddressCode(m_pSamSysParame->m_loadDataSampling[i].dynRateAddr,samGrpName+tr("��̬Ƶ�ʵ�ַ"));
        }
        //�������ݱ����ַ
        if (samGrp.bSaveToFile&& m_pSamSysParame->m_loadDataSampling[i].nDataSampType == 2)
        {
            shareAddressCode(m_pSamSysParame->m_loadDataSampling[i].keyCtlSaveAddr,samGrpName+tr("�������ݱ����ַ"));
        }
    }
    //������¼
    for (int i=0; i<m_pSamSysParame->m_qvcAlarm.size(); i++)
    {
            QString groupName = m_pSamSysParame->m_qvcAlarm.at(i).alarmName;
            for (int j=0; j<m_pSamSysParame->m_qvcAlarm.at(i).alarms.size();j++)
            {
                    shareAddressCode(m_pSamSysParame->m_qvcAlarm[i].alarms[j].addr,groupName+tr("�������ӵ�ַ"));
            }
    }

    //wxy ���Ӱ汾���ƣ�����򿪵ľɹ����޷�����
    if(pwnd->getProVersion() >= 3125)
    {
        QString groupName = tr("ȫ�ֱ���: ");
        for(int i = 0; i < g_Vars.size(); i++)
        {
            shareAddressCode(g_Vars[i].addr, groupName+g_Vars.at(i).varName+tr(" ��ַ: "));
        }
    }

    //�ű�

    for (int i=0; i<macros.size(); i++)
	{
        QString groupName = macros.at(i).libName;
        groupName = tr("�ű�: ")+groupName+tr(" ����: ");

        for (int j=0; j<macros[i].m_Vars.size();j++)
        {
            //QVector <VarPro> vars = macros[i].m_Vars;
            shareAddressCode(macros[i].m_Vars[j].addr,
                             groupName+macros[i].m_Vars.at(j).varName+tr(" ��ַ: "));
		}
	}

    //ȫ�ֽű�
	for (int i=0; i<m_pSamSysParame->m_qvcGlobalMaroProp.size(); i++)
	{
		QString groupName = tr("ȫ�ֽű�");
		groupName += QString::number(i);

		if (m_pSamSysParame->m_qvcGlobalMaroProp.at(i).bIfCtrl)
		{
			shareAddressCode(m_pSamSysParame->m_qvcGlobalMaroProp[i].mCtlAddr,
				groupName+tr("���Ƶ�ַ"));
		}

	}
    //����ű�
	for (int i=0; i<pSceneSheet.size(); i++)
	{
		QString groupName =pSceneSheet[i]->sNewScreenName+ tr("�ű�");
		for (int j=0; j<pSceneSheet[i]->listScript.size(); j++)
		{
			if (pSceneSheet[i]->listScript.at(j).scriptBShow)
			{
				groupName += QString::number(j);
				shareAddressCode(pSceneSheet[i]->listScript[j].scriptAddr,
					groupName+tr("���Ƶ�ַ"));
			}
		}

	}

	//���ϴ���
	for (int i=0; i<m_pSamSysParame->m_qvcdataTransProp.size(); i++)
	{
		QString groupName = tr("���ϴ���");

		if(m_pSamSysParame->m_qvcdataTransProp.at(i).nTriggerType == 2)
		{
			shareAddressCode(m_pSamSysParame->m_qvcdataTransProp[i].mTriggerAddr,
				groupName+tr("������ַ"));
		}
		shareAddressCode(m_pSamSysParame->m_qvcdataTransProp[i].mSourceAddr,
			groupName+tr("Դ��ַ"));
		shareAddressCode(m_pSamSysParame->m_qvcdataTransProp[i].mTargetAddr,
			groupName+tr("Ŀ���ַ"));
	}

    /***************�䷽*******************/

    int Recipesize = m_pSamSysParame->m_qvcRecipe.size();
    for(int i=0; i<Recipesize; i++)
    {
        bool bContinue = false;
        QString samGrpName = tr("�䷽�飺")+m_pSamSysParame->m_qvcRecipe[i].sName;//�䷽������
        if(m_pSamSysParame->m_qvcRecipe[i].bCtlAddr)
        {
            shareAddressCode( m_pSamSysParame->m_qvcRecipe[i].addrCtl, samGrpName+tr("���Ƶ�ַ"));
        }

        if(m_pSamSysParame->m_qvcRecipe[i].bCompleteNotic)
        {
            shareAddressCode( m_pSamSysParame->m_qvcRecipe[i].addrNotic, samGrpName+tr("���֪ͨ��ַ"));
        }

        if(m_pSamSysParame->m_qvcRecipe[i].formula.size() <= 0)
        {
            continue;
        }

        if(m_pSamSysParame->m_qvcRecipe[i].bContniu != false)
        {
            bContinue = true;
        }

        for(int j  = 0; j < m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.size();j++)
        {
            if(bContinue)
            {
                shareAddressCode( m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].addr, samGrpName+tr("�䷽��ַ"), i+1);
            }
            else
            {
                shareAddressCode( m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].addr, samGrpName+tr("�䷽��ַ"));
            }
        }
    }

    if(pAddrMsg->Address.size() > 0)
    {
        vAddrMsg.append(pAddrMsg);
    }

    //delete pAddrMsg;
    //pAddrMsg = NULL;
}

void MainWindow::OnModfyAnimationDlg(QGraphicsItem *item)
{
    AnimationDlg *pAnimate=new AnimationDlg (item,this);
    if(pAnimate->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pAnimate->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    pAnimate->deleteLater();
    pAnimate = NULL;
}

/*void MainWindow::OnModfyMsgBoardDlg(QGraphicsItem *item)
{
    MsgBoardDlg *pMsg=new MsgBoardDlg (item,this);
    if(pMsg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pMsg->pGeneralDlg->pOldItem;
        OnDoubleClik(item,oldItem);
    }
    pMsg->deleteLater();
    pMsg = NULL;
}*/

void MainWindow::OnCreateAnimation() //����
{
    if (SamDrawTool::s_eToolStat == SAM_DRAW_TOOL_UNLOCKED)
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_ANIMATION;
    }
}

void MainWindow::OnCreateAnimaDlg()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED || isCompiled)
    {
        return;
    }

    AnimationDlg *pAnimat=new AnimationDlg(0,this);
    if( pAnimat->exec() == QDialog::Accepted)
    {
//        QGraphicsItem * oldItem = pAnimat->pCopyItem;
//        DrawItemToScene FunClass;
//        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
//        //OnSingClikSpare(oldItem);
//        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    pAnimat->deleteLater();
    pAnimat = NULL;
}

/*void MainWindow::OnCreateMsgBoard()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED)
    {
        return;
    }

    MsgBoardDlg *MsgDlg=new MsgBoardDlg(0,this);
    if(MsgDlg->exec()== QDialog::Accepted)
    {
        QGraphicsItem * oldItem = MsgDlg->pGeneralDlg->pOldItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    MsgDlg->deleteLater();
    MsgDlg = NULL;

}*/
//��������򿪵��ĵ�
void MainWindow::updateRecentFileActions()
{
    QSettings settings;
    settings.allKeys();
    QStringList filesAll = settings.value("recentFileList").toStringList();
    QStringList files;
    QString str="";
    for(int i=0;i<filesAll.size();i++)
    {
        str=filesAll.at(i);
        if(str.right(3)==QString(AK_FILE_END))
        {
            files.push_back(filesAll.at(i));
        }
    }

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);
    if(0 == numRecentFiles)
    {
        ui->menu_recentFile->setEnabled(false);
    }
    else
    {
        ui->menu_recentFile->setEnabled(true);
        for (int i = 0; i < numRecentFiles; ++i)
        {
            QString text = tr("&%1 %2").arg(i + 1).arg(files[i]);
            text.replace(QString("/"),QString("\\"));
            recentFileActs[i]->setText(text);
            recentFileActs[i]->setData(files[i]);
            recentFileActs[i]->setVisible(true);
        }
        for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
            recentFileActs[j]->setVisible(false);
    }
}//



void MainWindow::setCurrentFile(const QString &fileName)
{
    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > MaxRecentFiles)
        files.removeLast();

    settings.setValue("recentFileList", files);
    updateRecentFileActions();

}//

void MainWindow::openRecentFile()
{
    if(isCompiled)
    {
        return ;
    }
    is_Click_OpenrecentFile=true;
    is_OpenrecentFile=true;
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
       sRecentflieName=action->data().toString();
    createopenprodlg();
}
/*void MainWindow::OpenRecipe()
{

    if(m_pSamSysParame->m_recipeProp.bRecipeExist)//�����䷽�Ӳ˵�����һ��
    {
        QTreeCtrlRecipeDlg recipeDlg(this);
      recipeDlg.exec();
    }
    else
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("�䷽��δ������"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
    }

    return;
}*/

QString MainWindow::SavePath(QString path,QSizeF size,bool bLib)
{
    if(bLib)
    {
        return SaveLibPath(path,size);
    }
    else
    {
        return SavePicPath(path,size);
    }
    //return mPicPath.value(path);//wxy�������ظ���ͼƬ������ֱ�Ӷ�ȡ·��
}

QString MainWindow::SavePicPath(QString path,QSizeF size)
{
    bool bSave = false;
    QString date = QDateTime::currentDateTime().toString("yyMMddhhmmss");
    QString newPath;
    QFile fp;
    if (!fp.exists(path))
    {
        return newPath;
    }
    if (mPicPath.contains(path))//���ڸ�·��
    {
        QString sName = mPicPath.value(path);
//        if(!pwnd->checkMD5(mPicMd5.value(sName), sName))//wxy����md5��⣬��ͬ���ٽ��в���
//        {
            QString format = sName.section(".",-1);
            QByteArray ba = format.toLatin1();
            const char *fmt = ba.data();

            QImage picture = QImage(sName);
            QSizeF sizeO;
            if(!picture.isNull())
            {
                sizeO = picture.size();
            }
            QImage img = QImage(path);
            QSizeF newSize = ScalePicture(sizeO,size,img.size());
            if(sizeO != newSize)
            {
                //�������ź󱣴�ͼƬ
                if(!img.isNull())
                {
                    img = img.scaled(QSize(newSize.width(),newSize.height()));
                    img.save(sName,fmt);
                }
            }
//            QByteArray md5 = pwnd->getFileMd5(sName);//wxy����md5��
//            mPicMd5.insert(sName, md5);
//        }
        return sName;
    }
    else
    {

        QImage picture = QImage(path);
        QList <QString> list = mPicPath.values();
        if (list.contains(path))//�����ǰ�ļ��Ѿ�����
        {

            return path;
        }
        else
        {
            QString newpath;
            QStringList list;
            int count;
            list<<"*.JPEG";
            list<<"*.gif";
            list<<"*.png";
            list<<"*.bmp";
            list<<"*.jpg";
            QString proName = "resource";
            QDir dir = QDir(proName);
            QString sName;
            if(!dir.exists())
            {
                dir.mkpath(dir.absolutePath());
            }
            count = dir.entryList(list).count();
            newpath = newpath.number(count);
            newpath = date+"_"+newpath;
            QString sTmp;
            sTmp = path.section(".",-1);
            if(sTmp.toUpper() == "GIF")
            {
                sName = newpath+".gif";
                newpath = proName+"/" +newpath+".gif";
                QFile file(path);
                bSave = file.copy(newpath);
                if(!bSave)
                {
                    return "";
                }
            }
            else
            {
                //if(isCompiled && m_pSamSysParame->m_projectProp.nDownLoadPicCheck)
                {
                   // sName = newpath+".JPEG";
                   // newpath = proName+"/" +newpath+".JPEG";
                }
                //else
                {
                    sName = newpath+"."+"PNG";
                    newpath = proName+"/" +newpath+"."+"PNG";
                }
                long lWidth,lHeight;
                double dW,dH;
                double dScale = 1;
                lWidth = picture.width();
                dW = (double)lWidth/size.width();
                lHeight = picture.height();
                dH = (double)lHeight/size.height();
                dScale = dH>dW ? dH:dW;
                if (dScale>1)
                {
                        picture = picture.scaled(lWidth/dScale,lHeight/dScale);
                }
                bSave = picture.save(newpath,"PNG");
                if(!bSave)
                {
                    qDebug()<<"save pictrue error..";
                    return "";
                }
            }
            mPicPath.insert(path,newpath);
            sName = newpath;
//            QByteArray md5 = pwnd->getFileMd5(sName);//wxy ����md5��
//            mPicMd5.insert(newpath, md5);
            return sName;
        }
    }

}
QString MainWindow::SaveLibPath(QString path,QSizeF size)
{
    QString date = QDateTime::currentDateTime().toString("yyMMddhhmmss");
    QString newPath;

    //��ͼ��ȡ��libItem������size��������
    QGraphicsScene tmpScene;
	QGraphicsItem *libItem = onGetItemFromFile(path);
    if(!libItem)
    {
        qDebug() << "lib item not exist!: " << path;
        return path;
    }

    tmpScene.addItem(libItem);
    QGroupItem gfun(libItem);
    gfun.SetWidth(size.width());
    gfun.SetHeigth(size.height());

    //��item���浽pixmap
    QRectF rect = libItem->sceneBoundingRect();

    QPixmap pixmap(rect.width(),rect.height());
    pixmap.fill(QColor(0,0,0,0));
    QPainter painter(&pixmap);

    QRectF target = QRectF(0,0,rect.width(),rect.height());
    rect = QRectF(rect.x(),rect.y(),rect.width()+1,rect.height()+1);
    tmpScene.render(&painter,target,rect,Qt::IgnoreAspectRatio);

    //����Ѿ����ڸ�item��mLibPath�У���Ƚϴ�С�����ж��Ƿ���Ҫ���±���
    if(mLibPathInfo.mLibPath.contains(path))
    {
        QString sName = mLibPathInfo.mLibPath.value(path);
        QString format = sName.section(".",-1);
        QByteArray ba = format.toLatin1();
        const char *fmt = ba.data();

        QSizeF sizeO = mLibPathInfo.mLibSize.value(path);
        QImage img = pixmap.toImage();
        QSizeF newSize = ScalePicture(sizeO,size,img.size());
        if(sizeO != newSize)
        {
            //�������ź󱣴�ͼƬ

            if(!img.isNull())
            {
                img = img.scaled(QSize(newSize.width(),newSize.height()));
                img.save(sName,fmt);
            }
        }
        return sName;
    }
    //�����ڸ�ͼƬ�������ļ���������ͼƬ����path ����mLibPath
    else
    {
        QImage picture = pixmap.toImage();
        QString newpath;
        QStringList list;
        int count;
        list<<"*.JPEG";
        list<<"*.gif";
        list<<"*.png";
        list<<"*.bmp";
        list<<"*.jpg";
        QString proName = "resource";
        QDir dir = QDir(proName);
        QString sName;
        if(!dir.exists())
        {
            dir.mkpath(dir.absolutePath());
        }
        count = dir.entryList(list).count();
        newpath = newpath.number(count);
        newpath = date+"_"+newpath;
        QString sTmp;
        sTmp = path.section(".",-1);


        //if(isCompiled && m_pSamSysParame->m_projectProp.nDownLoadPicCheck)
        {
           // sName = newpath+".JPEG";
           // newpath = proName+"/" +newpath+".JPEG";
        }
        //else
        {
            sName = newpath+"."+"PNG";
            newpath = proName+"/" +newpath+"."+"PNG";
        }
        long lWidth,lHeight;
        double dW,dH;
        double dScale = 1;
        lWidth = picture.width();
        dW = (double)lWidth/size.width();
        lHeight = picture.height();
        dH = (double)lHeight/size.height();
        dScale = dH>dW ? dH:dW;
        if (dScale>1)
        {
                picture = picture.scaled(lWidth/dScale,lHeight/dScale);
        }
        picture.save(newpath,"PNG");


        mLibPathInfo.mLibSize.insert(path,rect.size());
        mLibPathInfo.mLibPath.insert(path,newpath);
        sName = newpath;
        return sName;
    }

}

void MainWindow::OnSetHMirror()
{
    pSceneSheet[nActiveSheetIndex]->SetBaseItemMirror(1);
}

void MainWindow::OnSetVMirror()
{
    pSceneSheet[nActiveSheetIndex]->SetBaseItemMirror(2);
}

void MainWindow::OnCutItem() //����
{
	pSceneSheet[nActiveSheetIndex]->actionCut();
}

void MainWindow::ExecuteOffLineMonitor() //����ģ��
{
    if(QFile::exists("gEKip"))
    {
        QMessageBox box(QMessageBox::Information,tr(""),tr("��������̬���ڱ����У��������ܻ�����ļ���ͻ���Ƿ����"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("��"));
        box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::Cancel))
        {
            return;
        }
    }
    else
    {
        QFile file("gEKip");
        file.open(QIODevice::WriteOnly);
        file.close();
    }
    if(!is_Save)
    {
//        QMessageBox box(QMessageBox::Warning,tr("��ʾ"),tr("����ģ��֮ǰ�뱣�湤��"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
//        box.button(QMessageBox::Ok)->setText(tr("��"));
//        box.exec();
        QMessageBox box(QMessageBox::Information,tr("��ʾ"),tr("��������ģ��֮ǰҪ���湤�̣��Ƿ񱣴棿"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("��"));
        box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::Ok))
        {
            createsavedlg();
        }
        else
        {
           return ;
        }
		
   }
    QFile::remove("vdisk/prepare_OK.ini");
    QFile::remove("vdisk/prepare.ini");

    thread->SetDownload(SIMULATOR_OFF);
    if(!StartCompileThread())
    {
        QFile::remove("gEKip");
        isCompiled = false;
    }
}
void MainWindow::RunAboutDlg() //���ڶԻ���
{
    AboutDlg about(this);
    about.exec();
}
void MainWindow::MultiCopyDlg() //���ظ���
{
    QMultiCopy qmulticopydlg(this);
    qmulticopydlg.exec();
}

void MainWindow::PasteItemToScene()//
{
    //ճ��Item
    QGraphicsItem *oldItem=NULL;

    if(pSceneSheet[nActiveSheetIndex]->pasteList.size()!=0
       &&!pDrawToSceneItem&&(SamDrawTool::s_eDrawActType == SAM_DRAW_ASSY_COMPONENT))//���ͼ��
    {
        this->OnSingClikSpare(oldItem);

    }
    else if(pSceneSheet[nActiveSheetIndex]->pasteList.size()!=0
            &&!pDrawToSceneItem&&pSceneSheet[nActiveSheetIndex]->is_paste_singleItem)//�����ͼ��
    {
       // this->OnSingClikSpare(oldItem);
    }
    pSceneSheet[nActiveSheetIndex]->is_paste_singleItem=false;
    pSceneSheet[nActiveSheetIndex]->pasteList.clear();
}//

void MainWindow::initRecipeDlg()//��ʼ���䷽�Ի���
{
    m_pSamSysParame->m_recipeProp.sRecipeName =tr("�䷽1"); //�䷽����
    m_pSamSysParame->m_recipeProp.sDescription =""; //����
    m_pSamSysParame->m_recipeProp.nLanIndex=0;
    m_pSamSysParame->m_recipeProp.nRecipeLen =4;//�䷽����
    m_pSamSysParame->m_recipeProp.nRecipeTotalNum =1; //�䷽����
    m_pSamSysParame->m_recipeProp.nDataType =0;  //�������
    m_pSamSysParame->m_recipeProp.bWRecipeToPlc =false;//�Ƿ�д�䷽��PLC
    m_pSamSysParame->m_recipeProp.bRRecipeFromPlc =false; //�Ƿ��PLC��ȡ�䷽
    m_pSamSysParame->m_recipeProp.bRaddrSameWaddr =true;

    m_pSamSysParame->m_recipeProp.sRowHeadName.clear();
    m_pSamSysParame->m_recipeProp.sRowHeadName.resize(1);
    m_pSamSysParame->m_recipeProp.sRowHeadName[0].push_back("");//������ҳ����䷽����
    //m_pSamSysParame->m_recipeProp.sRowHeadName.push_back("");
    //    m_pSamSysParame->m_recipeProp.sRecipeData.push_back("");//����

    m_pSamSysParame->m_recipeProp.mWRecipeAddr.sShowAddr ="";       //д��ַ
    m_pSamSysParame->m_recipeProp.mRRecipeAddr.sShowAddr ="";         //����ַ

    m_pSamSysParame->m_recipeProp.sRecMemAddrRange ="RW1---RW4";    //�䷽�����ַ��Χ

    m_pSamSysParame->m_recipeProp.sCurrRecAddrRange ="RWI1---RWI4";    //��ǰ�䷽��ַ��Χ
    m_pSamSysParame->m_recipeProp.sRecipeRegNum ="RWI0";    //�Ĵ���

    int row= 4;
    int column=1;
    //    treectrlDlg->data.clear();
    //    treectrlDlg->PFheadername.clear();
   m_pSamSysParame->m_recipeProp.sRecipeData.clear();
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<column;j++)
        {
            m_pSamSysParame->m_recipeProp.sRecipeData.push_back("0");
        }
    }

    //���ı�ͷ
    m_pSamSysParame->m_recipeProp.sRowHeadName[0].clear();
    for(int j=0;j<column;j++)
    {
        m_pSamSysParame->m_recipeProp.sRowHeadName[0].push_back("RECIPE1");
    }

}//

void MainWindow::OnCreateRoundedRect()
{
//    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED)
//    {
//        return;
//    }

    if (SamDrawTool::s_eToolStat == SAM_DRAW_TOOL_UNLOCKED)
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_ROUNDED_RECT;
    }

//    RoundedRectDlg *RoundRectDlg=new RoundedRectDlg(0,this);
//    if(RoundRectDlg->exec() == QDialog::Accepted)
//    {
//        QGraphicsItem * oldItem = RoundRectDlg->pGeneralDlg->pCopyItem;
//        DrawItemToScene FunClass;
//        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
//        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
//    }
//    RoundRectDlg->deleteLater();
//    RoundRectDlg = NULL;
}

void MainWindow::OnCreateArc()
{
    if (SamDrawTool::s_eToolStat == SAM_DRAW_TOOL_UNLOCKED)
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_ARC;
    }

//    ArcDlg *pArcDlg=new ArcDlg(0,this);
//    if(pArcDlg->exec() == QDialog::Accepted)
//    {
//        QGraphicsItem * oldItem = pArcDlg->pGeneralDlg->pCopyItem;
//        DrawItemToScene FunClass;
//        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
//        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
//    }
//    pArcDlg->deleteLater();
//    pArcDlg = NULL;

}

void MainWindow::OnModfyRoundedRectDlg(QGraphicsItem *item)
{
    RoundedRectDlg *RoundRectDlg=new RoundedRectDlg(item,this);
    if(RoundRectDlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = RoundRectDlg->pGeneralDlg->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    RoundRectDlg->deleteLater();
    RoundRectDlg = NULL;
}

void MainWindow::OnModfyArcDlg(QGraphicsItem *item)
{
    ArcDlg *pArcDlg=new ArcDlg(item,this);
    if(pArcDlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = pArcDlg->pGeneralDlg->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    pArcDlg->deleteLater();
    pArcDlg = NULL;
}
bool MainWindow::eventFilter ( QObject * watched, QEvent * event )
{
    if (pView && watched == pView->verticalScrollBar())
    {
        if (event->type() == QEvent::Wheel)
        {
            QWheelEvent *wheelEvent = dynamic_cast<QWheelEvent*>(event);
            qDebug() << "Wheel Ate key press" << wheelEvent->modifiers();
            if(wheelEvent->modifiers() == Qt::ControlModifier)
            {
                qDebug() << "wheelEvent->modifiers() == Qt::ControlModifier";
                return true;
            }
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::Reverse_selection()//����ѡ��
{
    QPainterPath path;
    QList<QGraphicsItem *> item_list=pSceneSheet[nActiveSheetIndex]->selectedItems();
    for(int i=0;i<item_list.size();i++)
    {
        item_list.at(i)->setFlag(QGraphicsItem::ItemIsSelectable,false);
    }
    path.addRect(0,0,pSceneSheet[nActiveSheetIndex]->width(),pSceneSheet[nActiveSheetIndex]->height());
    pSceneSheet[nActiveSheetIndex]->setSelectionArea(path);
    for(int i=0;i<item_list.size();i++)
    {
        item_list.at(i)->setFlag(QGraphicsItem::ItemIsSelectable,true);
    }
}

 void MainWindow:: OnAddColorDlg(QPushButton *pbtn,ColorPickerPopup *colorPicker) //ÿ���ؼ������ɫ�Ի���
 {
     QDesktopWidget *d = QApplication::desktop();
     int width = d->width(); //��Ļ�Ŀ��
     int height = d->height(); //��Ļ�ĸ߶�

     QRect rect=pbtn->geometry();
     QPoint pos1(rect.left(),rect.bottom());
     QPoint pos=pbtn->parentWidget()->mapToGlobal(pos1);

     labelcolor->setStyleSheet(QString("background:%1").arg(pbtn->palette().background().color().name()));
     labelRGB->setText(pbtn->palette().background().color().name());
     colorPicker->setGeometry(pos.x(),pos.y(),20,30);
     colorPicker->show();
     QSize sz = colorPicker->size();
     QPointF ps(pos.x(),pos.y());
     if(pos.y() +sz.height() > height)
     {
         ps.setY(pos.y()-sz.height()-rect.height());
         //colorPicker->setGeometry(pos.x(),pos.y()-sz.height()-rect.height(),sz.width(),sz.height());
     }
     if(pos.x()+sz.width() > width)
     {
         ps.setX(pos.x()-sz.width()+rect.width());

     }
     colorPicker->setGeometry(ps.x(),ps.y(),sz.width(),sz.height());
 }//

void MainWindow:: changeItem_x()//״̬������ı༭��ĸı�
{
     QString  ss;
     ss = lab_left_space_statusBar->text();
    qreal nTmp=0.0f;
    QList <QGraphicsItem *>Items;
    QList <QPointF >oldPoss;
    QGraphicsItem *pItem=NULL;
    QList<QGraphicsItem *> itemList=pSceneSheet[nActiveSheetIndex]->selectedItems();
    if(itemList.size()==1)
    {
        pItem=itemList.at(0);
        nTmp=ss.toDouble();

        oldPoss += pItem->pos();
        Items.append(pItem);

        if(nTmp>pSceneSheet[nActiveSheetIndex]->width())
        {
            nTmp = pSceneSheet[nActiveSheetIndex]->width()- pItem->boundingRect().width();
        }
        else if(nTmp < 0)
        {
           nTmp = 0;
        }
        if(pItem->type()== SAM_DRAW_OBJECT_ROUNDEDRECT)
        {

            QRoundedRect *pRoundedRect = dynamic_cast<QRoundedRect *> (pItem);
            if(pRoundedRect)
            {
                pRoundedRect->setX(nTmp+pRoundedRect->GetLineWidth()/1.958);
                pSceneSheet[nActiveSheetIndex]->reBondingTrackers();
            }
        }
        else
        {
            pItem->setX(nTmp-pItem->boundingRect().left());
            pSceneSheet[nActiveSheetIndex]->reBondingTrackers(true);
        }

        if(pItem->pos() != oldPoss.first())
        {
            undoStack->push(new MovesCommand(pSceneSheet[nActiveSheetIndex],Items, oldPoss));
        }
    }
}

void MainWindow::changeItem_y()//״̬������ı༭��ĸı�
{
    QString  ss;
    ss = lab_up_space_statusBar->text();
    qreal nTmp=0.0f;
    QList <QGraphicsItem *>Items;
    QList <QPointF >oldPoss;
    QGraphicsItem *pItem=NULL;
    QList<QGraphicsItem *> itemList=pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->selectedItems();
    if(itemList.size()==1)
    {
        pItem=itemList.at(0);
        nTmp=ss.toDouble();

        oldPoss += pItem->pos();
        Items.append(pItem);

        if(nTmp>pSceneSheet[nActiveSheetIndex]->height())
        {
            nTmp = pSceneSheet[nActiveSheetIndex]->height()- pItem->boundingRect().height();
        }
        else if(nTmp < 0)
        {
           nTmp = 0;
        }
        if(pItem->type()== SAM_DRAW_OBJECT_ROUNDEDRECT)
        {
            QRoundedRect *pRoundedRect = dynamic_cast<QRoundedRect *> (pItem);
            if(pRoundedRect)
            {
                pRoundedRect->setY(nTmp+pRoundedRect->GetLineWidth()/1.98);
                pSceneSheet[nActiveSheetIndex]->reBondingTrackers();
            }
        }
        else
        {
            pItem->setY(nTmp-pItem->boundingRect().top());
            pSceneSheet[nActiveSheetIndex]->reBondingTrackers(true);
        }
        if(pItem->pos() != oldPoss.first())
        {
            undoStack->push(new MovesCommand(pSceneSheet[nActiveSheetIndex],Items, oldPoss));
        }
    }
}

 void MainWindow::changeItem_w()//״̬������ı༭��ĸı�
 {
     QString  ss;
     ss = lab_width_space_statusBar->text();
     qreal nTmp=0.0f;
     QGraphicsItem *pItem=NULL;
     QSizeF size;
     QPointF pt;
     QGroupItem * group;
     QList<QGraphicsItem *> itemList=pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->selectedItems();
     if(itemList.size()==1)
     {
         pItem=itemList.at(0);
         nTmp=ss.toDouble();
         size = pItem->boundingRect().size();
         pt = pItem->sceneBoundingRect().topLeft();
         double maxsize = pSceneSheet[nActiveSheetIndex]->width()-pItem->sceneBoundingRect().left();
         nTmp = (nTmp < maxsize) ? nTmp:maxsize;

         //nTmp=pItem->sceneBoundingRect().width();
         group=new QGroupItem(pItem);
         group->SetWidth(nTmp);
         pSceneSheet[nActiveSheetIndex]->reBondingTrackers(true);

         if(pItem->boundingRect().size() != size)
         {
             undoStack->push(new SizeCommand(pSceneSheet[nActiveSheetIndex],pItem, size,pt));
         }

     }
 }
 void MainWindow::changeItem_h()//״̬������ı༭��ĸı�
 {
     QString  ss;
     ss = lab_hidth_space_statusBar->text();
     qreal nTmp=0.0f;
     QGraphicsItem *pItem=NULL;
     QSizeF size;
     QPointF pt;
     QGroupItem * group;
     QList<QGraphicsItem *> itemList=pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->selectedItems();
     if(itemList.size()==1)
     {
         pItem=itemList.at(0);
         nTmp=ss.toDouble();
         pt = pItem->sceneBoundingRect().topLeft();
         size = pItem->boundingRect().size();
         double maxsize = pSceneSheet[nActiveSheetIndex]->height()-pItem->sceneBoundingRect().top();
         nTmp = (nTmp < maxsize) ? nTmp:maxsize;

         //nTmp=pItem->sceneBoundingRect().height();
         group=new QGroupItem(pItem);
         group->SetHeigth(nTmp);
         pSceneSheet[nActiveSheetIndex]->reBondingTrackers(true);

         if(pItem->boundingRect().size() != size)
         {
             undoStack->push(new SizeCommand(pSceneSheet[nActiveSheetIndex],pItem, size,pt));
         }
     }
 }

 QString MainWindow::ControlNO(QString sName)
 {
     int i = 0;
     int j = 0;
     QList<QGraphicsItem *> Items;
     QStringList sList;
     QVector<int> ID;
     int nVal = 0;
     QString str = "";
     int Length = 0;

    sList.clear();
    Length = sName.length();               //��ſ�ʼ������
    int totalSceneNum = pSceneSheet.size();
    for(i = 0; i < totalSceneNum; i++) //ɨ�����л���
    {
        Items = pSceneSheet[i]->items();   //��ǰҳ�����е�item
        for(j = 0; j < Items.size(); j++)
        {
            sList = Items.at(j)->data(GROUP_DATALIST_KEY).toStringList(); //ȡ��ÿ��item����������
            if(sList.size() < 20)
                continue;//break;
            str = sList.at(19);           //��Ŵ���15λ
            if(sName == str.left(Length)) //��ſ�ʼ����ͬ
            {
                nVal = str.right(str.length() - Length).toInt();
                ID.append(nVal);
            }
        }
    }

     nVal = 0;
     for(i = 0; i < ID.size(); )
     {
         if(nVal == ID.at(i))
         {
             nVal++;
             i = 0;
             continue;
         }
         i++;
     }

     str = QString("%1").arg(nVal);
     while(str.length() < 4)
     {
         str = tr("0")+str;
     }
     sName = sName+str;
     return sName;
 }


/******************************************************
 *�������ƣ�IsHaveLibraryItem(QGraphicsItem *pItem)
 *�������ܣ����ڶ�״̬�ؼ���ť���жϸÿؼ����Ƿ���ͼ��ͼ��
 *�������壺pItem��ʾ��Ҫ�жϵ�item
 *����ֵ��  ������ʹ��ͼ���ļ���item
 *Name��   edit by zqh
 *Date��   2011-04-07
 *****************************************************/
QGraphicsItem * MainWindow::IsHaveLibraryItem(QGraphicsItem *pItem)
{
    int nKey = 0;
    QGraphicsItem *newItem = NULL;
    QList<QGraphicsItem *> itemList = pItem->childItems();
    DrawItemToScene GroupFunction;

    int nID = pItem->data(GROUP_TYPE_KEY).toInt();
    if(nID == GROUP_TYPE_ANIMATE) //������
    {
        QString sName = "";
        foreach(QGraphicsItem *item,itemList)
        {
            sName = item->data(GROUP_NAME_KEY).toString();
            if(sName == tr("mMain"))
            {
                itemList.clear();
                itemList = item->childItems();
                break;
            }
        }
    }

    foreach(QGraphicsItem *item,itemList)
    {
        nKey = item->data(GROUP_TYPE_KEY).toInt();
        if(nKey == LIBRARY_LIB_GROUP)//ͼ�����
        {
            GroupFunction.CopyItem(&newItem,item);
            break;
        }
        else if(item->type() == SAM_DRAW_OBJECT_PIXMAP)
        {
            GroupFunction.CopyItem(&newItem,item);
            break;
        }
    }
    return newItem;
}

void MainWindow::SlecetALL()//Ctrl+Aȫѡ����
{
    QList <QGraphicsItem *> selList;
    selList=pwnd->pSceneSheet[nActiveSheetIndex]->items();
    QPainterPath path;
    path.addRect(0,0,pSceneSheet[nActiveSheetIndex]->width(),pSceneSheet[nActiveSheetIndex]->height());
    pSceneSheet[nActiveSheetIndex]->setSelectionArea(path);
    selList=pSceneSheet[nActiveSheetIndex]->selectedItems();
    foreach(QGraphicsItem *item,selList)
        item->setSelected(true);
}


/******************************************************
 *�������ƣ�OpenLibraryFile(QString str)
 *�������ܣ����ڶ�״̬�ؼ���ť����ð�ť����ͼ��item������ݴ洢
          ·����ͼ���ļ���������ѡ���item
 *�������壺str��ʾͼ��item��·��
          0λ�ñ�ʾ������ţ�1λ�ñ�ʾ�ڼ���item��3��ʾ��ͼ��
          ��item����ͼƬ(0--ͼ�Σ�1--ͼƬ)
 *����ֵ��  ������ʹ��ͼ���ļ���item
 *Name��   edit by zqh
 *Date��   2011-04-07
 *****************************************************/
QGraphicsItem * MainWindow::OpenLibraryFile(QString str)
{
    QStringList sList = str.split("-", QString::SkipEmptyParts);
    QString sPath = "";
    QGraphicsItem * pItem = NULL;


    if(sList.size() == 4)
    {
        sPath = tr("UserDefineLibraryLib.sk");
    }
    else if(sList.size() == 3)
    {}
    else
        return pItem;


    SamDrawScene *pSvene = NULL;
    int sceneSize = 0;
    QVector <SamDrawScene *> vScene;  //�滭�������
    vScene.clear();

    if(sList.size() == 4)
    {
        QFile file(sPath);
        if(!file.open(QIODevice::ReadOnly))
            {
           // QMessageBox box(QMessageBox::Warning,tr("��ʾ"),tr("ȱ��UserDefineLibraryLib.sk�ļ�!"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            //box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
            //box.exec();
            return NULL;
        }
        QDataStream openData(&file);

        openData >> sceneSize;

        for(int i =0; i< sceneSize; i++)
        {
            pSvene = new SamDrawScene();
            openData >> pSvene;
            vScene.push_back(pSvene);
        }
        file.close();
    }

if(vBaseLibraryScene.isEmpty())
    {
    //QMessageBox box(QMessageBox::Warning,tr("��ʾ"),tr("ȱ��LibraryLib.sk�ļ�!"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    //box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
    //box.exec();
    return NULL;
    }

    //������ȡͼ��item

    //sList��0λ�ñ�ʾ������ţ�1λ�ñ�ʾ�ڼ���item��3��ʾ��ͼ����item����ͼƬ(0--ͼ�Σ�1--ͼƬ)
    int nSheet = sList.at(0).toInt();//�������
    QPainterPath path;
    QStringList slist;
    QList<QGraphicsItem *> item_list;

    //ɨ�����ͼ��
    if(sList.size() == 4) //�û��Զ���ͼ��
    {
        //path.addRect(0,0,vScene.at(nSheet)->width(),vScene.at(nSheet)->height());
        //vScene.at(nSheet)->setSelectionArea(path);
        //item_list=vScene.at(nSheet)->selectedItems();
        item_list=vScene.at(nSheet)->TopItems();
    }
    else if(sList.size() == 3)//����ͼ��
    {
        //path.addRect(0,0,vBaseLibraryScene.at(nSheet)->width(),vBaseLibraryScene.at(nSheet)->height());
        //vBaseLibraryScene.at(nSheet)->setSelectionArea(path);
        item_list=vBaseLibraryScene.at(nSheet)->TopItems();
    }

    foreach (QGraphicsItem * tmpItem, item_list)
    {
        QString sname = pItem->data(GROUP_NAME_KEY).toString();
        if (str == sname)
        {
            DrawItemToScene GroupFunction;
            GroupFunction.CopyItem(&pItem,tmpItem);
            break;
        }
    }


    for(int i = 0;i < vScene.size();i++)
        delete vScene[i];
    vScene.clear();
    return pItem;
}
//�����С��ʼ������
int MainWindow::InitFontSize(QComboBox *fontsize)
{
    if(fontsize!=NULL)
    {
        fontsize->setCurrentIndex(5);
        for(int i= 5;i <= 256;i++)    //��ʼ�������Сѡ���
        {
            fontsize->addItem(QString("%1").arg(i));
        }
        fontsize->setEditable(true);//ʹ�����б����Ա༭
        fontsize->setCurrentIndex(5);
        QIntValidator *validator=new QIntValidator(this);//�����ֶ����������б��ķ�Χ
        validator->setRange(5,256);
        fontsize->setValidator(validator);
        return 1;
    }
    else
    {
        return 0;
    }
}

void MainWindow::on_action_DatagroupDisplay_triggered()//����Ⱥ��
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED  || isCompiled)
    {
        return;
    }

	int rCount = 0;
	foreach (DATA_SAMPLING datasample,pwnd->m_pSamSysParame->m_loadDataSampling)
	{
		if (datasample.nDataSampType == 1)
		{
			rCount++;
		}
	}
    if(rCount == 0)//û�����ݲɼ�
    {
        QMessageBox msg(QMessageBox::Information,VERSION_NAME,tr("û�н���ʵʱ���ݲɼ�"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        msg.exec();
        //QMessageBox::about(this, tr(""), tr("û�н���ʵʱ���ݲɼ�"));
        return;
    }

    //DataGroupDisplayDlg *trendchart=new DataGroupDisplayDlg(0,this);
    QTrendDataGroup *trendchart = new QTrendDataGroup(0,this);
    if( trendchart->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = trendchart->m_pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    trendchart->deleteLater();
    trendchart = NULL;
}

/*
void MainWindow::OnModfyDataGroupDisplayDlg(QGraphicsItem *item)
{
    DataGroupDisplayDlg *trendChartDlg=new DataGroupDisplayDlg(item,this);
    //QTrendDataGroup *trendChartDlg=new QTrendDataGroup(item,this);
    if(trendChartDlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = trendChartDlg->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    trendChartDlg->deleteLater();
    trendChartDlg = NULL;
}*/
void MainWindow::OnModfyDataGroupDisplayDlg(QGraphicsItem *item)
{
    //DataGroupDisplayDlg *trendChartDlg=new DataGroupDisplayDlg(item,this);
    QTrendDataGroup *trendChartDlg=new QTrendDataGroup((QTrendDataGroupAttr *)item,this);
    if(trendChartDlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = trendChartDlg->m_pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    trendChartDlg->deleteLater();
    trendChartDlg = NULL;
}

/*������ָ��༭�б�*/
/*void MainWindow::MarcoEdit(void)
{

}*/

/*void MainWindow::on_action_init_macro_triggered()//��ʼ����Ի���
{

}*/

/*void MainWindow::on_action_global_macro_triggered()//ȫ�ֺ�Ի���
{

}*/

void MainWindow::OnModfyTimerDlg(QGraphicsItem *item)
{
    QTimerDlg *Timerdlg=new QTimerDlg(item,this);
    if(Timerdlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = Timerdlg->pGeneralDlg->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    Timerdlg->deleteLater();
    Timerdlg = NULL;
}
void MainWindow::modifyKeyBoardASCII(QGraphicsItem *item)//ASCII�ַ��������
{
    qkeybutton *KeyboardASCII=new qkeybutton(item,this);
    if(KeyboardASCII->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = KeyboardASCII->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    KeyboardASCII->deleteLater();
    KeyboardASCII = NULL;
}

void MainWindow::fillMarcoUseStruct(QString sLib, QString sFunc, QStringList& strList)
{
    int i = 0;
    QList<QGraphicsItem*> Items;
    QString strContent;

    //�ؼ��ĺ�
    int totalSceneNum = pSceneSheet.size();
    for(i = 0; i < totalSceneNum; i++)//ɨ������ҳ��
    {
        Items = pSceneSheet[i]->items();   //��ǰҳ�����е�item
        foreach(QGraphicsItem *pItem, Items)
        {
            if(!pItem)
            {
                continue;
            }

            if(SAM_DRAW_OBJECT_GROUP == pItem->type())
            {
                if(pItem->parentItem() == 0 && pItem->type() != SAM_DRAW_OBJECT_TRACKER && pItem->type() != SAM_DRAW_OBJECT_LOCK)
                {
                    QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
                    if(item->GroupType() == SAM_DRAW_GROUP_SWITCH)
                    {
                        SwitchItem* sch = dynamic_cast<SwitchItem*>(item);
                        if(sch->bMacro && sch->macroName!= "")
                        {
                            if(sch->macroName == sLib|| sLib == tr("����"))
                            {
                                strContent = tr("����") + QString::number(i) + tr(" ����");
                                strList.push_back(strContent);
                            }
                        }
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_VALUE || item->GroupType() == SAM_DRAW_GROUP_ASCII)
                    {
                        DataDisplayItem* valueItem = dynamic_cast<DataDisplayItem*>(item);
                        if(valueItem->m_etabPag == DATAINPUTSHOW)
                        {
                            if(valueItem->m_data.bIsInput && valueItem->m_data.bUseMacro && valueItem->m_data.macroName != "")
                            {
                                if(valueItem->m_data.macroName == sLib || sLib == tr("����"))
                                {
                                    strContent = tr("����") + QString::number(i) + tr("��ֵ��ʾ��");
                                    strList.push_back(strContent);

                                }
                            }
                        }
                        else if(valueItem->m_etabPag == ASCIIINPUTSHOW)
                        {
                            if(valueItem->m_ascii.bIsinput && valueItem->m_ascii.bUseMacro && valueItem->m_ascii.macroName != "")
                            {
                                if(valueItem->m_ascii.macroName == sLib || sLib == tr("����"))
                                {
                                    strContent = tr("����") + QString::number(i) + tr("ASCII��ʾ��");
                                    strList.push_back(strContent);
                                }
                            }
                        }
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_DROPDOWN)
                    {
                        QDropdownAttr* dropItem = dynamic_cast<QDropdownAttr*>(item);
                        if(dropItem->isUseScript && dropItem->macroName != "")
                        {
                            if(dropItem->macroName == sLib || sLib == tr("����"))
                            {
                                strContent = tr("����") + QString::number(i) + tr("�๦��ѡ��ť");
                                strList.push_back(strContent);

                            }
                        }
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_MFBTN)
                    {
                        MfBtnItem* mfbItem = dynamic_cast<MfBtnItem*>(item);
                        if(mfbItem->isUseScript && mfbItem->macroName != "")
                        {
                            if(mfbItem->macroName == sLib || sLib == tr("����"))
                            {
                                strContent = tr("����") + QString::number(i) + tr("�๦�ܿ���");
                                strList.push_back(strContent);
                            }
                        }
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_COMBOBOX)
                    {
                        AkComboItem* mfbItem = dynamic_cast<AkComboItem*>(item);
                        if(mfbItem->dataCombo.m_bUseMacro && mfbItem->dataCombo.m_strMacroName != "")
                        {
                            if(mfbItem->dataCombo.m_strMacroName == sLib || sLib == tr("����"))
                            {
                                strContent = tr("����") + QString::number(i) + tr("������");
                                strList.push_back(strContent);
                            }
                        }
                    }
                }
            }
        }
    }

    //ȫ�ֺ�
    int num = m_pSamSysParame->m_qvcGlobalMaroProp.size();
    GLOBAL_MARO_PROP prop;
    for(int i = 0; i < num; i++)
    {
        prop = m_pSamSysParame->m_qvcGlobalMaroProp[i];
        if(prop.sLibName == sLib || sLib == tr("����"))
        {
            strContent = tr("��") + QString::number(i + 1) + tr("��ȫ�ֽű�");
            strList.push_back(strContent);

        }
    }

    //��ʼ����
    num = m_pSamSysParame->m_qvcInitMaroProp.size();
    INIT_MARO_PROP intProc;
    for(int i = 0; i < num; i++)
    {
        intProc = m_pSamSysParame->m_qvcInitMaroProp[i];
        if(intProc.sLibName == sLib || sLib == tr("����"))
        {
            strContent = tr("��") + QString::number(i + 1) + tr("����ʼ���ű�");
            strList.push_back(strContent);
        }
    }
}

void MainWindow::findScreenAllMarco(QVector<MarcoString> &mVecStr)
{
    MarcoString marcoStr;
    int i = 0;
    QList<QGraphicsItem*> Items;

    //�ؼ��ĺ�
    int totalSceneNum = pSceneSheet.size();
    for(i = 0; i < totalSceneNum; i++)//ɨ������ҳ��
    {
        Items = pSceneSheet[i]->items();   //��ǰҳ�����е�item
        foreach(QGraphicsItem *pItem, Items)
        {
            if(!pItem)
            {
                continue;
            }

            if(SAM_DRAW_OBJECT_GROUP == pItem->type())
            {
                if(pItem->parentItem() == 0 && pItem->type() != SAM_DRAW_OBJECT_TRACKER && pItem->type() != SAM_DRAW_OBJECT_LOCK)
                {
                    QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
                    if(item->GroupType() == SAM_DRAW_GROUP_SWITCH)
                    {
                        SwitchItem* sch = dynamic_cast<SwitchItem*>(item);
                        if(sch->bMacro && sch->macroName != "")
                        {
                            marcoStr.sScreenName = pSceneSheet[i]->sNewScreenName;
                            marcoStr.sItemName= tr("����");
                            marcoStr.sLibName = sch->macroName;
                            marcoStr.sFunName = sch->functionName;
                            mVecStr.push_back(marcoStr);
                        }
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_VALUE || item->GroupType() == SAM_DRAW_GROUP_ASCII)
                    {
                        DataDisplayItem* valueItem = dynamic_cast<DataDisplayItem*>(item);
                        if(valueItem->m_etabPag == DATAINPUTSHOW)
                        {
                            if(valueItem->m_data.bIsInput && valueItem->m_data.bUseMacro && valueItem->m_data.macroName != "")
                            {
                                marcoStr.sScreenName= pSceneSheet[i]->sNewScreenName;
                                marcoStr.sItemName  = tr("��ֵ��ʾ");
                                marcoStr.sLibName   = valueItem->m_data.macroName;
                                marcoStr.sFunName   = valueItem->m_data.functionName;
                                mVecStr.push_back(marcoStr);
                            }
                        }
                        else if(valueItem->m_etabPag == ASCIIINPUTSHOW)
                        {
                            if(valueItem->m_ascii.bIsinput && valueItem->m_ascii.bUseMacro && valueItem->m_ascii.macroName!= "")
                            {
                                marcoStr.sScreenName= pSceneSheet[i]->sNewScreenName;
                                marcoStr.sItemName  = tr("ASCII��ʾ");
                                marcoStr.sLibName   = valueItem->m_ascii.macroName;
                                marcoStr.sFunName   = valueItem->m_ascii.functionName;
                                mVecStr.push_back(marcoStr);
                            }
                        }
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_DROPDOWN)
                    {
                        QDropdownAttr* dropItem = dynamic_cast<QDropdownAttr*>(item);
                        if(dropItem->isUseScript && dropItem->macroName != "")
                        {
                            marcoStr.sScreenName= pSceneSheet[i]->sNewScreenName;
                            marcoStr.sItemName  = tr("�๦�ܿ���");
                            marcoStr.sLibName   = dropItem->macroName;
                            marcoStr.sFunName   = dropItem->functionName;
                            mVecStr.push_back(marcoStr);
                        }
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_COMBOBOX)
                    {
                        AkComboItem* dropItem = dynamic_cast<AkComboItem*>(item);
                        if(dropItem->dataCombo.m_bUseMacro && dropItem->dataCombo.m_strMacroName != "")
                        {
                            marcoStr.sScreenName= pSceneSheet[i]->sNewScreenName;
                            marcoStr.sItemName  = tr("������");
                            marcoStr.sLibName   = dropItem->dataCombo.m_strMacroName;
                            marcoStr.sFunName   = "";
                            mVecStr.push_back(marcoStr);
                        }
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_MFBTN)
                    {
                        MfBtnItem* mfbItem = dynamic_cast<MfBtnItem*>(item);
                        if(mfbItem->isUseScript && mfbItem->macroName != "")
                        {
                            marcoStr.sScreenName= pSceneSheet[i]->sNewScreenName;
                            marcoStr.sItemName  = tr("�๦�ܿ���");
                            marcoStr.sLibName   = mfbItem->macroName;
                            marcoStr.sFunName   = mfbItem->functionName;
                            mVecStr.push_back(marcoStr);
                        }
                    }
                }
            }
        }
    }

    //ȫ�ֺ�
    int num = m_pSamSysParame->m_qvcGlobalMaroProp.size();
    GLOBAL_MARO_PROP prop;
    for(int i = 0; i < num; i++)
    {
        prop = m_pSamSysParame->m_qvcGlobalMaroProp[i];
        marcoStr.sScreenName= tr("���̹�����");
        marcoStr.sItemName  = tr("ȫ�ֽű�");
        marcoStr.sLibName   = prop.sLibName;
        marcoStr.sFunName   = prop.sFucName;
        mVecStr.push_back(marcoStr);
    }

    //��ʼ����
    num = m_pSamSysParame->m_qvcInitMaroProp.size();
    INIT_MARO_PROP intProc;
    for(int i = 0; i < num; i++)
    {
        intProc = m_pSamSysParame->m_qvcInitMaroProp[i];
        marcoStr.sScreenName= tr("���̹�����");
        marcoStr.sItemName  = tr("��ʼ���ű�");
        marcoStr.sLibName   = intProc.sLibName;
        marcoStr.sFunName   = intProc.sFucName;
        mVecStr.push_back(marcoStr);
    }

    //���ڻ����
    num = pwnd->pSceneSheet.size();
    for(int i = 0; i < num; i++)
    {
        QList<SCRIPT_PROP> scripts;//���нű�
        int scriptNum = 0;
        if((pwnd->pSceneSheet[i]->nIsSceneOrWindow == 0) && (pwnd->pSceneSheet[i]->listScript.size() != 0))//�����
        {
            marcoStr.sScreenName = tr("����ű�");
            marcoStr.sItemName   = pwnd->pSceneSheet[i]->sNewScreenName;
            scripts = pwnd->pSceneSheet[i]->listScript;
            scriptNum = scripts.size();
            for(int j = 0; j < scriptNum; j++)
            {
                marcoStr.sLibName   = scripts[j].scriptName;
                marcoStr.sFunName   = scripts[j].scriptFuncName;
                mVecStr.push_back(marcoStr);
            }
        }
        else if((pwnd->pSceneSheet[i]->nIsSceneOrWindow == 1) && (pwnd->pSceneSheet[i]->listScript.size() != 0))//���ں�
        {
            marcoStr.sScreenName = tr("���ڽű�");
            marcoStr.sItemName   = pwnd->pSceneSheet[i]->sNewScreenName;
            scripts   = pwnd->pSceneSheet[i]->listScript;
            scriptNum = scripts.size();
            for(int j = 0; j < scriptNum; j++)
            {
                marcoStr.sLibName   = scripts[j].scriptName;
                marcoStr.sFunName   = scripts[j].scriptFuncName;
                mVecStr.push_back(marcoStr);
            }
        }
    }
}

void MainWindow::fillMarcoName(int ifuse, int marcoindex, int nIndex,
                 QGraphicsItem *pItem, QString sCtrlName,QStringList sList)
{
    if(sList.at(ifuse) == "1")
    {
        pAddrMsg = new AddrMsg;
        pAddrMsg->nSheetIndex = nIndex;           //�������
        pAddrMsg->pItem = pItem;             //��ǰ�ؼ�
        /*ADDRPRO temp;
        temp.addr.sShowAddr = sList.at(marcoindex);//������
        temp.addr.sPlcRegTypeStr = sCtrlName;
        temp.str = QObject::tr("���ַ");
        pAddrMsg->Address.append(temp);
        vAddrMsg.append(pAddrMsg);*/
        ADDRPRO temp;
        Keyboard* kb = temp.pAddr;
        kb->sShowAddr = sList.at(marcoindex);//������
        kb->sPlcRegTypeStr = sCtrlName;
        temp.str = QObject::tr("��ַ");
        pAddrMsg->Address.append(temp);
        vAddrMsg.append(pAddrMsg);
    }
}

void MainWindow::on_action_macro_admin_triggered()//��ָ�������
{
    MarcoUseDisplay* pDlg = new MarcoUseDisplay(this);
    pDlg->exec();
    pwnd->is_Save = false;// ����ı� ͬʱ���ı䱣�水ť����ɫ
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pDlg->deleteLater();
    pDlg = NULL;
    //qDebug() << "on_action_macro_admin_triggered";
    //system("D:\\android\\code\\bash.bat");
}

    void MainWindow::on_action_macro_find_triggered()//�����
{
    MarcoFindDlg *pFindDlg = new MarcoFindDlg(this);

    if(pFindDlg->exec() == QDialog::Accepted)
    {
        pMainList->clear();

        int     nRow    = 1; //�б�����
        int     nFcount = 0;
        QString strLib  = pFindDlg->libName;//����
        QString strFunc = pFindDlg->funcName;//������
        //QString str     = "Searching for the Marco:" + strLib + "(libName)...";
        QString str = tr("���ڲ��ҽű�:") +  strLib + tr("(����)...");
        if(!m_rightDock->isVisible())   //��ʾ��Ϣ�������
        {
            m_rightDock->setVisible(true);
            ui->action_41->setChecked(true);
        }
        pMainList->setRowCount(nRow);
        pMainList->setColumnCount(1);
        pMainList->setColumnWidth(0, 2000);
        pMainList->setRowHeight(0, 20);
        pMainList->setItem(0, 0, new QTableWidgetItem(str));

        //QStringList lsStr;
        lsStr.clear();
        fillMarcoUseStruct(strLib, strFunc, lsStr);//����ַ��Ϣ
        int strNum  = lsStr.size();
        for(int i = 0; i < strNum; i++)
        {
            pMainList->insertRow(nRow);
            pMainList->setRowHeight(nRow, 20);
            pMainList->setItem(nRow, 0, new QTableWidgetItem(lsStr.at(i)));
            nRow++;
            nFcount++;
        }
        if(nFcount == 0)//û���ҵ�
        {
            //str = "Cannot find the Marco !!!!!";
            str = tr("û���ҵ���Ӧ�Ľű� !");
        }
        else
        {
            //str = QString("%1").arg(nFcount) + " occurrence(s) have been found.";
            str = QString("%1").arg(nFcount) + tr(" ��������ҵ�.");
        }
        pMainList->insertRow(nRow);
        pMainList->setRowHeight(nRow, 20);
        pMainList->setItem(nRow, 0, new QTableWidgetItem(str));
        pMainList->setCurrentCell(nRow, 0);
    }
    pFindDlg->deleteLater();
    pFindDlg = NULL;
}

void MainWindow::compileVarTable(QSqlDatabase &db,int &count)
{
    QSqlQuery sqlquery(db);

    sqlquery.prepare("INSERT INTO macroProp(sName , nDatatype , nAddrValue ,bOffset ,nOffsetAddr ,sMacroLibName , nRWPerm ,nElemNum,nCodetype) "
                     "VALUES (:sName , :nDatatype , :nAddrValue ,:bOffset ,:nOffsetAddr ,:sMacroLibName , :nRWPerm ,:nElemNum,:nCodetype)");
    int i=0;
    int j=0;
    bool result = false;
    int dataType = 0;
    int codetype = 0;
    foreach(Macro lib,macros)
    {
        if (lib.type && lib.isCompiled())
        {
            i++;
            j=0;
            foreach(VarPro var,lib.vars())
            {
                j++;
                switch(var.dataType)
                {
                case 0://bool
                    dataType = 1;
                    break;
                case 1://short
                    dataType = 3;
                    break;
                case 2://ushort
                    dataType = 13;
                    break;
                case 3://int
                    dataType = 5;
                    break;
                case 4://uint
                    dataType = 11;
                    break;
                case 5://bool[]
                    dataType = 2;
                    break;
                case 6://short[]
                    dataType = 4;
                    break;
                case 7://ushort[]
                    dataType = 14;
                    break;
				case 8://int[]
					dataType = 6;
					break;
				case 9://uint[]
					dataType = 12;
					break;
				case 10://float
					dataType = 7;
					break;
				case 11://float[]
					dataType = 8;
					break;
                case 12://BCD16
                    dataType = 15;
                    break;
                case 13://BCD16[]
                    dataType = 16;
                    break;
                case 14://BCD32
                    dataType = 17;
                    break;
                case 15://BCD32[]
                    dataType = 18;
                    break;
                case 16://string
                    dataType = 9;
                    codetype = 1;
                    break;
                case 17://string
                    dataType = 9;
                    codetype = 0;

                    break;
                }
                sqlquery.bindValue(":sName",QVariant(var.varName));
                sqlquery.bindValue(":nDatatype",QVariant(dataType));
                count++;
                ADDR_PARAMENTS stParams;
                stParams.id = count;
                stParams.itemId = i;
                stParams.eType = OBJ_MACRO;
                stParams.addrNum = j;
                stParams.eRWtype = MACRO_LOOP_R;
                if(var.RWPerm == 1)
                {
                    stParams.eRWtype = MACRO_LOOP_W;
                }
                var.addr.compile(db,stParams);

                sqlquery.bindValue(":nAddrValue",QVariant(count));
                sqlquery.bindValue(":bOffset",QVariant(var.bOffset));
                if(var.bOffset)
                {
                    count++;
                    ADDR_PARAMENTS stParams;
                    stParams.id = count;
                    stParams.itemId = i;
                    stParams.eType = OBJ_MACRO;
                    stParams.addrNum = j;
                    stParams.eRWtype = MACRO_ONCE_R;

                    var.offsetAddr.compile(db,stParams);
                    sqlquery.bindValue(":nOffsetAddr",QVariant(count));
                }
                sqlquery.bindValue(":sMacroLibName",QVariant(lib.libName));
                sqlquery.bindValue(":nRWPerm",QVariant(var.RWPerm));
                sqlquery.bindValue(":nElemNum",QVariant(var.count));
                sqlquery.bindValue(":nCodetype",QVariant(codetype));

                result = sqlquery.exec();
                qDebug() << "insert macroProp table :"<<result;
            }
            //add by wxy����ȫ�ֱ������ݿⱣ��
            if(getProVersion() >= 3125)
            {
                foreach(VarPro var,getGlobalVars())
                {
                    j++;
                    switch(var.dataType)
                    {
                    case 0://bool
                        dataType = 1;
                        break;
                    case 1://short
                        dataType = 3;
                        break;
                    case 2://ushort
                        dataType = 13;
                        break;
                    case 3://int
                        dataType = 5;
                        break;
                    case 4://uint
                        dataType = 11;
                        break;
                    case 5://bool[]
                        dataType = 2;
                        break;
                    case 6://short[]
                        dataType = 4;
                        break;
                    case 7://ushort[]
                        dataType = 14;
                        break;
                    case 8://int[]
                        dataType = 6;
                        break;
                    case 9://uint[]
                        dataType = 12;
                        break;
                    case 10://float
                        dataType = 7;
                        break;
                    case 11://float[]
                        dataType = 8;
                        break;
                    case 12://BCD16
                        dataType = 15;
                        break;
                    case 13://BCD16[]
                        dataType = 16;
                        break;
                    case 14://BCD32
                        dataType = 17;
                        break;
                    case 15://BCD32[]
                        dataType = 18;
                        break;
                    case 16://string
                        dataType = 9;
                        codetype = 1;
                        break;
                    case 17://string
                        dataType = 9;
                        codetype = 0;
                        break;
                    }
                    sqlquery.bindValue(":sName",QVariant(var.varName));
                    sqlquery.bindValue(":nDatatype",QVariant(dataType));
                    count++;
                    ADDR_PARAMENTS stParams;
                    stParams.id = count;
                    stParams.itemId = i;
                    stParams.eType = OBJ_MACRO;
                    stParams.addrNum = j;
                    stParams.eRWtype = MACRO_LOOP_R;
                    if(var.RWPerm == 1)
                    {
                        stParams.eRWtype = MACRO_LOOP_W;
                    }
                    var.addr.compile(db,stParams);

                    sqlquery.bindValue(":nAddrValue",QVariant(count));
                    sqlquery.bindValue(":bOffset",QVariant(var.bOffset));
                    if(var.bOffset)
                    {
                        count++;
                        ADDR_PARAMENTS stParams;
                        stParams.id = count;
                        stParams.itemId = i;
                        stParams.eType = OBJ_MACRO;
                        stParams.addrNum = j;
                        stParams.eRWtype = MACRO_ONCE_R;

                        var.offsetAddr.compile(db,stParams);
                        sqlquery.bindValue(":nOffsetAddr",QVariant(count));
                    }
                    sqlquery.bindValue(":sMacroLibName",QVariant(lib.libName));
                    sqlquery.bindValue(":nRWPerm",QVariant(var.RWPerm));
                    sqlquery.bindValue(":nElemNum",QVariant(var.count));
                    sqlquery.bindValue(":nCodetype",QVariant(codetype));

                    result = sqlquery.exec();
                }
            }
        }
    }
}

void MainWindow::compileInitLibrary(QSqlDatabase &db,int &count)
{}
void MainWindow::compileGlobalLibrary(QSqlDatabase &db,int &count)
{}
bool MainWindow::CheckMarcoIsNullInCompile(QString& strLibName)//����ʱ����ʹ���Ƿ�Ϊ��
{
    //deleteDirectory(QFileInfo("sdmacro\\ml\\\class\\jml"));
    //deleteDirectory(QFileInfo("sdmacro\\ml\\\class\\jrl"));
	deleteDirectory(QFileInfo("sdmacro\\jsrc\\jml"));
	deleteDirectory(QFileInfo("sdmacro\\jsrc\\jrl"));
    QFile::remove("sdmacro\\ml\\ml.jar");
    MacroCmptrd *macroTrd = new MacroCmptrd();
    return macroTrd->compressJar(macros, strLibName);
    return true;
}

void MainWindow::ChangetoChinese()//�������Ըı�
{
    QString sTmp=this->windowTitle();
    transparent tor;
    if(ui->action_chinese->isChecked())
    {
        ui->action_english->setChecked(false);
        tor.toChinese();
        languageChangeForRecipe(0);

        undoAction->setText(tr("����"));
        undoAction->setIconText(tr("����"));
        redoAction->setText(tr("�ָ�"));
        redoAction->setIconText(tr("�ָ�"));

        scrollAreaBasic->setWindowIconText("XXXX");
        scrollAreaBasic->setToolTip("XXXX");
        if(ToolBarTabWidget)
        {
            ToolBarTabWidget->setTabText(0, tr("����ͼ��"));
            ToolBarTabWidget->setTabText(1, tr("��   ��"));
        }
    }
    else
    {
       ui->action_english->setChecked(true);
       languageChangeForRecipe(1);
       tor.toEnglish();

       undoAction->setText(tr("Undo"));
       undoAction->setIconText(tr("Undo"));
       redoAction->setText(tr("Redo"));
       redoAction->setIconText(tr("Redo"));
       if(ToolBarTabWidget)
       {
           ToolBarTabWidget->setTabText(0, "Basic Graphics");
           ToolBarTabWidget->setTabText(1, "Controls");
       }
    }
    this->setWindowTitle(sTmp);

    if(!pSceneSheet.empty())
    {
        pSceneSheet[nActiveSheetIndex]->selItemsChanged();
    }
}

void MainWindow::ChangetoEnglish()
{
    QString sTmp=this->windowTitle();
    transparent tor;
    if(ui->action_english->isChecked())
    {
        qDebug() <<"ChangetoEnglish:1" ;
        ui->action_chinese->setChecked(false);
        languageChangeForRecipe(1);
        qDebug() <<"ChangetoEnglish:2" ;
        tor.toEnglish();
        qDebug() <<"ChangetoEnglish:3" ;

        undoAction->setText(tr("Undo"));
        undoAction->setIconText(tr("Undo"));
        redoAction->setText(tr("Redo"));
        redoAction->setIconText(tr("Redo"));
        if(ToolBarTabWidget)
        {
            ToolBarTabWidget->setTabText(0, "Basic Graphics");
            ToolBarTabWidget->setTabText(1, "Controls");
        }
    }
    else
    {
        qDebug() <<"ChangetoEnglish:4" ;
       ui->action_chinese->setChecked(true);
       tor.toChinese();
       qDebug() <<"ChangetoEnglish:5" ;
       languageChangeForRecipe(0);
       qDebug() <<"ChangetoEnglish:6" ;

       undoAction->setText(tr("����"));
       undoAction->setIconText(tr("����"));
       redoAction->setText(tr("�ָ�"));
       redoAction->setIconText(tr("�ָ�"));
       if(ToolBarTabWidget)
       {
           ToolBarTabWidget->setTabText(0, tr("����ͼ��"));
           ToolBarTabWidget->setTabText(1, tr("��   ��"));
       }
    }
    this->setWindowTitle(sTmp);

    if(!pSceneSheet.empty())
    {
        pSceneSheet[nActiveSheetIndex]->selItemsChanged();
    }
}

void MainWindow::loadBaseLibAndUserDefineLib()
{
    if(vBaseLibraryScene.size() > 0)
        return;

    QFile file("android_new.sk");
    if(!file.open(QIODevice::ReadOnly))
        return ;

    QDataStream openData(&file);
    SamDrawScene *pSvene = NULL;
    vBaseLibraryScene.clear();
    int sceneSize = 0;
    openData >> sceneSize;

    for(int i =0; i< sceneSize; i++)
    {
        pSvene = new SamDrawScene();
        //openData >> pSvene;
        pSvene->load(openData,pSvene);
        pSvene->bIsLibrary = false;
        pSvene->setSceneRect(0,0,621-3,1000);
        vBaseLibraryScene.push_back(pSvene);
        lockCurrentSheetItem(i);
    }
    file.close();
}

void MainWindow::lockCurrentSheetItem(int nSheetIndex)
{
    QPainterPath path;
    QList<QGraphicsItem *> item_list;
    item_list.clear();

    path.addRect(0,0,vBaseLibraryScene.at(nSheetIndex)->width(),vBaseLibraryScene.at(nSheetIndex)->height());
    vBaseLibraryScene.at(nSheetIndex)->setSelectionArea(path);
    item_list=vBaseLibraryScene.at(nSheetIndex)->selectedItems();

    if(!item_list.isEmpty())
    {
        foreach (QGraphicsItem *item, item_list)
        {
            item->setFlag(QGraphicsItem::ItemIsMovable, false);
            item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item->setSelected(false);
            switch(item->type())
            {
            case SAM_DRAW_OBJECT_RECT:              //15
                {
                    QRectItem *rectItem = dynamic_cast<QRectItem *>(item);
                    if(rectItem)
                        rectItem->setLockVisiable(false);
                    break;
                }
            case SAM_DRAW_OBJECT_ELIPSE:              //16
                {
                    QElipseItem *elipseItem = dynamic_cast<QElipseItem *>(item);
                    if(elipseItem)
                       elipseItem->setLockVisiable(false);
                    break;
                }
            case SAM_DRAW_OBJECT_LINE:                 //17
                {
                    QLineItem *lineItem = dynamic_cast<QLineItem *>(item);
                    if(lineItem)
                        lineItem->setLockVisiable(false);
                    break;
                }
            case SAM_DRAW_OBJECT_POLYGON:              //18
                {
                    QPolygonItem *polygonItem = dynamic_cast<QPolygonItem *>(item);
                    if(polygonItem)
                        polygonItem->setLockVisiable(false);
                    break;
                }
            case SAM_DRAW_OBJECT_FOLDLINE:             //19
                {
                    QFoldLineItem *foldLineItem = dynamic_cast<QFoldLineItem *>(item);
                    if(foldLineItem)
                        foldLineItem->setLockVisiable(false);
                    break;
                }
            case SAM_DRAW_OBJECT_FREELINE:             //20
                {
                    QFreeLineItem *freeLineItem = dynamic_cast<QFreeLineItem *>(item);
                    if(freeLineItem)
                        freeLineItem->setLockVisiable(false);
                    break;
                }
            case SAM_DRAW_OBJECT_TEXT:                 //22
                {
                    QSimpleTextItem *textItem = dynamic_cast<QSimpleTextItem *>(item);
                    if(textItem)
                        textItem->setLockVisiable(false);
                    break;
                }
            case SAM_DRAW_OBJECT_LINECIRCLE:           //25
                {
                    QLineCircleItem *lineCircleItem = dynamic_cast<QLineCircleItem *>(item);
                    if(lineCircleItem)
                        lineCircleItem->setLockVisiable(false);
                    break;
                }
            case SAM_DRAW_OBJECT_ROUNDEDRECT:
                {
                    QRoundedRect *pRoundItem = dynamic_cast<QRoundedRect *>(item);
                    if(pRoundItem)
                        pRoundItem->setLockVisiable(false);
                    break;
                }
            case SAM_DRAW_OBJECT_ARC:
                {
                    QArcItem *pArcItem = dynamic_cast<QArcItem *>(item);
                    if(pArcItem)
                        pArcItem->setLockVisiable(false);
                    break;
                }
            case SAM_DRAW_OBJECT_GROUP:                //23
                {
                    QItemGroup *groupItem = dynamic_cast<QItemGroup *>(item);
                    if(groupItem)
                        groupItem->setLockVisiable(false);

                    break;
                }
            default:
                break;
            }
        }
    }
}

//���µ����ؼ���ͼƬ��λ��
void MainWindow::ResetPic(QGraphicsItem *pItem)
{
    if(!pItem)
    {
        return;
    }
    QRectF rect = pItem->sceneBoundingRect();
    if(SAM_DRAW_OBJECT_GROUP == pItem->type())
    {
        QItemGroup *itemGroup = dynamic_cast<QItemGroup *>(pItem);
        if(!itemGroup)
        {
            return;
        }
        //��������ͼƬ��С
        if (SAM_DRAW_GROUP_SWITCH == itemGroup->GroupType())
        {
            SwitchItem *pSwitchItem = dynamic_cast<SwitchItem *>(pItem);
            if(!pSwitchItem)
            {
                return;
            }
            if(pSwitchItem->curSta >= pSwitchItem->statusPic.size()
                || pSwitchItem->curSta < 0)
                {
                return;
            }
            if(LIBRARY != pSwitchItem->statusPic[pSwitchItem->curSta].bLib)
            {
                if(pSwitchItem->backItem)
                {
                    QPixmapItem *pPix = dynamic_cast<QPixmapItem *> (pSwitchItem->backItem);
                    if (pPix)
                    {
                        //QRectF rc = pAniMageItam->sceneBoundingRect();
                        //pPix->updateSize(rc);
                        //rc = QRectF(rc.top(),rc.left(),rc.width(),nHeight);
                        pPix->updatePic(rect);
                        pPix->updateSize(rect);
                    }
                    //QGroupItem *pBaseItem = new QGroupItem(pSwitchItem->backItem);
                    //pBaseItem->SetWidth(rect.width());
                    //pBaseItem->SetHeigth(rect.height());
                }
            }
        }
        else if(SAM_DRAW_GROUP_STATICPIC == itemGroup->GroupType())
        {
            foreach(QGraphicsItem *item,itemGroup->childItems())
            {
                if(item->type() == 65536 + 24)
                {
                    QPixmapItem *pPix = dynamic_cast<QPixmapItem *> (item);
                    if(pPix)
                    {
                        pPix->updatePic(rect);
                        pPix->updateSize(rect);
                    }
                    break;
                }
            }
        }
    }
    return;
}

void MainWindow::ResetItem(PicPosInfo posinfo,QGraphicsItem *pItem)
{
    QRectF rect;
    QPointF pos;
    foreach(QGraphicsItem *pTmp,pItem->childItems())
    {
        if (pTmp->data(GROUP_NAME_KEY).toString() == "mBackRect")
        {
            rect = pTmp->sceneBoundingRect();
            break;
        }
    }
    DrawItemToScene drawFun;
    rect = drawFun.TransPicPos(posinfo,rect);
    QPixmapItem *pixmapItem = NULL;
    foreach(QGraphicsItem *pTmp,pItem->childItems())
    {
        if( (pTmp->data(GROUP_NAME_KEY).toString() == "mLibrary")
            &&(pTmp->type() == SAM_DRAW_OBJECT_PIXMAP))
        {
            pixmapItem = dynamic_cast<QPixmapItem *>(pTmp);
            if(pixmapItem)
            {
                pos = pixmapItem->mapFromScene(rect.topLeft());
                //rect.setTopLeft(pos);
                rect = QRectF(pos.x(),pos.y(),rect.width(),rect.height());
                pixmapItem->updateSize(rect);
            }
            break;
        }
    }
}

int MainWindow::IsCheckAddressRight(Keyboard &keyboard, QString WaringMsg, QLineEdit *pLineEdit, int Addr_Type,
                                     QString sAddr)
{
    QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr(""),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
	int iFlg= CheckString(keyboard,sAddr,Addr_Type);
	switch(iFlg)
	{
	case ADDR_CORRECT://�޴���
		break;
	case ADDR_STRING_NULL://����Ϊ��
		msg.setText(WaringMsg+tr("�����ַ����Ϊ�գ�"));
		msg.exec();
		return 0;
	case ILLEGAL_REG://�Ĵ������Ͳ�ƥ�����
		msg.setText(WaringMsg+tr("�Ĵ����������ַҪ��ƥ�䣡"));
		msg.exec();
		return 0;
	case INVALID_CONNECT://�ֶ������ַ����ʱ��û�и�����
        msg.setText(WaringMsg+tr("û����Ӹ�Э�飡"));
		msg.exec();
		return 0;
	case ADDR_OUT_BOUND://���ݳ��� ����ֵΪ����ֵ ����Ϊ�����ֵ ����Ϊ�����ֵ

		msg.setText(WaringMsg+tr("��ֵַ������Χ��"));
		msg.exec();
		return 0;
	default://�����ʽ����
		msg.setText(WaringMsg+tr("�����ʽ����"));
		msg.exec();
		return 0;

    }
       
    keyboard.nAddrType = Addr_Type; //��¼��λ��ʾ
       
    return 1;
}
bool MainWindow::FocusInStatusbar()


{
    return (
            lab_left_space_statusBar->hasFocus()
            || lab_up_space_statusBar->hasFocus()
            || lab_width_space_statusBar->hasFocus()
            || lab_hidth_space_statusBar->hasFocus()
            );
}
//���µ����ؼ���ͼƬ��λ��
QGraphicsItem * MainWindow::ReloadPic(QGraphicsItem *pItem,SamDrawScene *scene,int flag)
{
    return pItem;

}
QGraphicsItem * MainWindow::ReloadItem(QGraphicsItem *pItem,bool btransparent,QString sColor,
                                       PicPosInfo posinfo,QString sPath)
{
    QGraphicsItem *pLibItem = NULL;
    QGraphicsItem *pNewItem = NULL;
    QDrawGraphics *pDraw = new QDrawGraphics;
    QPixmap picture = QPixmap(sPath);
    if(picture.isNull())
    {
        pLibItem = NULL;
        pNewItem = pDraw->AlterGraphics(pItem,NULL,pLibItem,posinfo.btnIndex,posinfo.space,
                                        posinfo.fixrect);
    }
    else
    {
        if(btransparent)//�Ƿ�͸��
        {
            QColor mColor = StringTOColor(sColor);
            QBitmap bmp=picture.createMaskFromColor(mColor,Qt::MaskInColor);
            picture.setMask(bmp); //���ô�����mask
        }
        QPixmapItem *PicItem = new QPixmapItem(picture,picture.size());
        pLibItem = PicItem;
        pNewItem = pDraw->AlterGraphics(pItem,&picture,pLibItem,posinfo.btnIndex,posinfo.space,
                                        posinfo.fixrect);
    }
    delete pDraw;
    return pNewItem;
}

/************************************************************************
 *                        SAMKOON TECHNOLOGY CORP.
 *                          COPYRIGHT (C) 2011
 *
 * Description: Load help.
 *
 * Functions: load help by different btuuon
 *
 * Modification Log:
 * Date             Name             Description Of Change
 * 2011-7-6       zqh               Creation.
 ***********************************************************************/
void MainWindow::loadHelpHtm(int nKey)
{
    QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr(""),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);

    QLibrary  lib("GetHelpPath.dll");
    if (!lib.load())
    {
        msg.setText(tr("GetHelpPath.dllδ�ҵ���")); //���û�ð����ĵ���dll�ļ�
        msg.exec();
        return ;
    }
    typedef QString (*ADDPROC)( int );
    ADDPROC getHlepPath = (ADDPROC)lib.resolve("getHelpPath");

    if(getHlepPath)
    {
        QProcess mp_helpProcess(this);
        QString str = getHlepPath(nKey);
        mp_helpProcess.startDetached(str);
    }
}

void MainWindow::on_action_online_simulation_triggered()//����ģ��
{
    if(bSimulator)
    {
        return;
    }
    if(!is_Save)
    {
        QMessageBox box(QMessageBox::Information,tr("��ʾ"),tr("��������ģ��֮ǰҪ���湤�̣��Ƿ񱣴棿"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("��"));
        box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::Ok))
        {
            createsavedlg();
        }
        else
        {
           return ;
        }

   }

}

void MainWindow::LoadProjectHelp()
{
    loadHelpHtm(GLOBAL_HELP_KEY);
}
void MainWindow::SavePicToFile(QStringList pathList,QDataStream &stream)
{
    QString dir = "Picture/" + newpro->newprowizard_name;//��ѹ��ͼƬ��ŵ�·��
    stream << dir;
    stream <<pathList.size();
    foreach(QString path,pathList)
    {
        QString name;
        name = path.section("/",-1);
        path = "resource/"+name;
        QFile f( path );
        if(f.open( QIODevice::ReadOnly ))
        {
            QByteArray s = f.readAll();
            stream << path;
            stream << s;
            f.close();
        }
        else
        {
            path = "";
            stream <<path;
        }
        int nValue = 0;
        emit this->SignalGetvalue(nValue);
        if(nValue >= 99)
        {
            nValue = 99;
        }
        else nValue = -1;
        emit this->SignalCompressProgress(nValue);
    }

}
void MainWindow::LoadPicFromFile(QDataStream &stream)
{
    int size = 0;
    QString path;
    QString picPath;
    stream >> picPath;
    QDir dir = QDir(picPath);
    if(!dir.exists())
    {
        dir.mkpath(dir.absolutePath());
    }
    stream >> size;
    if(size > 5000)
    {
        size = 5000;
    }
    float nprogress = 0;
    if(size != 0)
    {
       nprogress = 90/size;
    }

    for(int i = 0; i<size; i++)
    {
        stream >> path;
        if(path != "")
        {
            path.replace("\\","/");
            path = path.section("/",-1);
            path = picPath+"/"+path;
            QFile f(path);
            QByteArray fstream;
            stream>> fstream;
            if(f.open(QIODevice::WriteOnly))
            {
                f.write(fstream);
                f.close();
            }

        }
        emit this->SignalCompressProgress(int(nprogress*i));
    }
}
/************************************************************************
  *Functions:�����������ضԻ���
  ************************************************************************
  *Value��
  *��
  ************************************************************************
  *returns:
  *���ɹ������ضԻ���
  ************************************************************************
  *Edit time��2011.7.13
  *Edit by    ��zhy
  *Change by zqh
  *2011-07-28
  *************************************************************************/

/*void MainWindow::OnCreatUploadDlg()
{
    QString sPath;
    QProcess mProcess;
    QStringList cmdlist;

    cmdlist.clear();
    const char license_[] ="SamkoonConverter.exe";
    sPath = QString::fromLocal8Bit(license_);
   cmdlist.append(QString("%1").arg(is_tanslator));
    bool bReturnFlag = mProcess.startDetached(sPath,cmdlist);
    if(!bReturnFlag)
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("����ת�����ļ�ʧ�ܣ������°�װ�ļ���"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        return ;
    }
    //QUploadDlg uploaddlg;
   // if(uploaddlg.exec() == QDialog::Accepted)
   // {

   // }
}
*/
/************************************************************************
  *Functions:����ʱ����û��Զ������
  ************************************************************************
  *Value��
  *�ú�����ʱû���õ�
  ************************************************************************
  *returns:
  *����û��Զ�����̵�ҳ���Ƿ��������Ŀؼ��Լ��û��Զ�����̿ؼ��Ƿ�������ҳ�������
  *����Ļ�����false ����޴�Ļ�����true
  ************************************************************************
  *Edit time��2011.7.13
  *Edit by    ��zhy
  *************************************************************************/

bool MainWindow::OnCheckUserkeyboard()
{
    int totalSceneNum = pSceneSheet.size();
    for(int i = 0; i < totalSceneNum;i++)   //ɨ������ҳ��
    {
        if(pSceneSheet.at(i)->nIsSceneOrWindow==2)//���Զ������
        {

            QList<QGraphicsItem *> Items;
            QPainterPath path;
            path.addRect(0,0,pSceneSheet[i]->width(),pSceneSheet[i]->height());
            pSceneSheet[i]->setSelectionArea(path);
            Items=pSceneSheet[i]->selectedItems();
            foreach(QGraphicsItem *item,Items)
                item->setSelected(false);

            for(int j = 0; j < Items.size(); j++)   //ɨ�赱ǰҳ������пؼ�
            {
                if(Items.at(j)->data(GROUP_TYPE_KEY)!=GROUP_TYPE_ASCII_KEYBOARD)
                {
                    QString sScreenName = pSceneSheet[i]->sNewScreenName;//��������
                    pMsgOutPut = new MsgOutPut ;//��Ϣ�������˫��Ҫ�������
                    pMsgOutPut->pItem = Items.at(j);

                    QString str = tr("error:")+sScreenName+tr("-")+tr("�ÿؼ������û��Զ�����̿ؼ�����ɾ����");
                    int nRow=0;
                    pMainList->insertRow(nRow);
                    pMainList->setRowHeight(nRow,20);
                    QTableWidgetItem* pTable = new QTableWidgetItem(str);
                    if(pTable)
                    {
                        pTable->setBackground(QBrush(QColor(255,0,0)));
                        pMainList->setItem(nRow,0,pTable);
                    }
                    //pMainList->setItem(nRow,0,new QTableWidgetItem(str));
                    pMainList->setCurrentCell(nRow,0);
                    mapMsgOutPutItem.insert(nRow, pMsgOutPut);
                    nRow++;
                }
            }
        }
    }
return false;
}
/************************************************************************
  *Functions:�������û��Զ�����̺����Ӹ��ֲۺ���
  ************************************************************************
  *Value��
  *SamDrawScene *pScene ������û��Զ������
  ************************************************************************
  *returns:
  *��
  ************************************************************************
  *Edit time��2011.7.16
  *Edit by    ��zhy
  *************************************************************************/

//void MainWindow::RefurbishConnect(SamDrawScene *pScene)
//{
//    connect(pScene,SIGNAL(DoubleClickItem(QGraphicsItem *)),this,SLOT(SlotItemDBClick(QGraphicsItem *)));
//    connect(pScene,SIGNAL(SingleClickItem()),this,SLOT(OnSingleClickItem()));
//    connect(pScene,SIGNAL(SingleClickItem()),this,SLOT(AddItemToScene()));
//    pwnd->setUnifiedTitleAndToolBarOnMac(true);
//    connect(pScene, SIGNAL(itemsMoved(SamDrawScene*,QList<QGraphicsItem*>,QList<QPointF>)),
//            this, SLOT(itemsMoved(SamDrawScene *,QList <QGraphicsItem *>,QList <QPointF >)));
//}
/************************************************************************
  *Functions:�ڱ��湤�̵�ʱ��������ҳ��Ŀؼ��Ƿ����õ��Զ������
  ************************************************************************
  *Value��
  *����õ��Զ�����̵Ļ���ͨ���洢�������ҵ����Ӧ���û��Զ�����̵�ID����¼��ָ��λ��
  ************************************************************************
  *returns:
  *��
  ************************************************************************
  *Edit time��2011.7.19
  *Edit by    ��zhy
  *************************************************************************/
void MainWindow::checkUserKeyboard()
{
    QList<QGraphicsItem *> Items;
    QGraphicsItem *pItem;
    QStringList sList;
    QStringList KbLocation;
    int nID = 0;
    int  i = 0;
    int j = 0;

    int totalSceneNum = pwnd->pSceneSheet.size();
    for(i = 0; i < totalSceneNum;i++)   //ɨ������ҳ��
    {
        Items = pwnd->pSceneSheet[i]->items();    //��ǰҳ�����е�item
        for(j = 0; j < Items.size(); j++)   //ɨ�赱ǰҳ������пؼ�
        {
            pItem = Items.at(j);//->topLevelItem();
            KbLocation.clear();//���keyboard�б�

            if(pItem->parentItem())
                continue;
            if(pItem->type() == SAM_DRAW_OBJECT_TRACKER
               || SAM_DRAW_OBJECT_LOCK == pItem->type())
            {
                continue;
            }
            nID = pItem->data(GROUP_TYPE_KEY).toInt(); //ȡ�ؼ���Key��
            sList = pItem->data(GROUP_DATALIST_KEY).toStringList(); //ȡ��ÿ��item����������

            switch(-1)
            {
            case GROUP_TYPE_WORDBTN: //�ְ�ť
            case GROUP_TYPE_ASCIIENTRY: //ASC������
            case GROUP_TYPE_MFUNCTION: //�๦�ܰ�ť
            case GROUP_TYPE_MULSTATEBTN: //��״̬��ť
                fillUserKeyboard(sList);//���ú�������
                pItem->setData(GROUP_DATALIST_KEY,sList);
                break;
            case GROUP_TYPE_NUMENTRY://��ֵ����
                if(sList.at(130).toInt())//����ʹ���Զ������
                {
                    //���´���Ϊ������������Ϣ
                    //���ҵ�������ݵĻ�������д����Ϣ
                    sList[130]=QString::number(0);//��ʹ���Զ������
                    sList[132]=QString::number(-1);

                   for(int nUserkeyboar=0;nUserkeyboar<pwnd->pSceneSheet.size();nUserkeyboar++)
                    {
                       if(pwnd->pSceneSheet.at(nUserkeyboar)->nIsSceneOrWindow==2)//�Զ������
                       {
                           if(pwnd->pSceneSheet[nUserkeyboar]->sNewScreenName==sList.at(131))//���ҵ���Ӧ�ļ���
                           {
                               sList[130]=QString::number(1);
                               sList[132]=QString::number(nUserkeyboar);
                               break;
                           }
                       }
                       else
                       {
                           continue;//���û��Զ������
                       }
                   }
               }
               else
               {
                   sList[132]=QString::number(-1);
               }
               pItem->setData(GROUP_DATALIST_KEY,sList);
                break;
             } //end switch
        } //end the second for
    } //end the first for

}
/************************************************************************
  *Functions:��checkUserKeyboard������������ �����޸��û��Զ������
  ************************************************************************
  *Value��
  *��ֵ������Զ���������ݴ洢��λ����������λ�ò�ͬ����ȥ��ֵ����֮�� ʣ�µĶ��ڸú���
  *��ִ��
  ************************************************************************
  *returns:
  *��
  ************************************************************************
  *Edit time��2011.7.19
  *Edit by    ��zhy
  *************************************************************************/
void MainWindow::fillUserKeyboard(QStringList &sList)
{
    if(sList.at(24).toInt())//����ʹ���Զ������
    {
        //���´���Ϊ������������Ϣ
        //���ҵ�������ݵĻ�������д����Ϣ
        sList[24]=QString::number(0);
        sList[32]=QString::number(-1);
        for(int nUserkeyboar=0;nUserkeyboar<pwnd->pSceneSheet.size();nUserkeyboar++)
        {
            if(pwnd->pSceneSheet.at(nUserkeyboar)->nIsSceneOrWindow==2)//�Զ������
            {
                if(pwnd->pSceneSheet[nUserkeyboar]->sNewScreenName==sList.at(25))//���ҵ���Ӧ�ļ���
                {
                    sList[24]=QString::number(1);
                    sList[32]=QString::number(nUserkeyboar);
                    break;
                }
             }
            else
            {
                continue;
            }
        }
    }
   else
   {
       sList[32]=QString::number(-1);
   }

}


void MainWindow::compressFile(QString sFileName)
{
    emit this->SignalCompressProgress(0);
    int size = pSceneSheet.size();
    //int type = 0;
    QString path;
    QString newPath;
    QStringList datalist;
    QMap<QString, QString> mPath;

    //int j;
    mPicPath.clear();
    mPath.clear();

    if(m_pSamSysParame->m_projectProp.bTouchInvalidPic)
    {
        for(int i=0; i<m_pSamSysParame->m_projectProp.sTIPicPathList.size(); i++)
        {
            path = m_pSamSysParame->m_projectProp.sTIPicPathList.at(i);
            newPath = pwnd->SavePicPath(path,QSizeF(m_pSamSysParame->m_projectProp.nSceneWidth,m_pSamSysParame->m_projectProp.nSceneHeight));

            if("" != newPath)
            {
                QString str = newPath;
                str = newPath.section("/",-1);
                newPath = PICTURE_PATH + newpro->newprowizard_name;
                newPath = newPath + "/";
                newPath = newPath + str;
            }
            else
            {
                continue;
            }
            mPath.insert(newPath,path);
            qDebug() << "ffffff===   "<<m_pSamSysParame->m_projectProp.sTIPicPathList;
            m_pSamSysParame->m_projectProp.sTIPicPathList.replace(i,newPath);
            qDebug() << "ffffff===   "<<m_pSamSysParame->m_projectProp.sTIPicPathList;
        }
    }

    //��ʼ��ȡ�ؼ��е�ͼƬ
    for(int i=0; i<size; i++)
    {
        path = pSceneSheet[i]->m_picturePath;
        newPath = pwnd->SavePicPath(path,pSceneSheet[i]->sceneRect().size());
        if("" != newPath)
        {
            QString str = newPath;
            str = newPath.section("/",-1);
            newPath = PICTURE_PATH + newpro->newprowizard_name;
            newPath = newPath + "/";
            newPath = newPath + str;

            if(!mPath.contains(newPath))
            {
                mPath.insert(newPath,path);
            }
            pSceneSheet[i]->m_picturePath = newPath;
            pSceneSheet[i]->m_bChangePicPath = true;
        }

        QList<QGraphicsItem *> tmpList;
        QVector<QGraphicsItem *> itemList;
        tmpList.clear();
        itemList.clear();
        tmpList = pSceneSheet[i]->items();
        int tmpSize = tmpList.size();
        for(int i=0;i < tmpSize;i++)
        {
            QGraphicsItem *pItem = tmpList.at(i);
            if(!pItem) continue;
            QGraphicsItem *pParentItem= pItem->parentItem();
            if(pParentItem != 0)
                continue;
            if(pItem->type() == SAM_DRAW_OBJECT_TRACKER
               || pItem->type() == SAM_DRAW_OBJECT_LOCK)
                continue;
            itemList.push_back(pItem);
        }
        int sceneItemsize = itemList.size();
        for(int i = 0; i < sceneItemsize; i++)
        {
            QGraphicsItem *pItem = itemList.at(i);
            if(SAM_DRAW_OBJECT_GROUP == pItem->type())
            {
                QItemGroup *pItemGroup = dynamic_cast<QItemGroup *> (pItem);
                savePicPath(pItemGroup,mPath);
            }
            int nValue = 0;
            emit this->SignalGetvalue(nValue);
            if(nValue >= 99)
            {
                nValue = 99;
            }
            else nValue = -1;
            emit this->SignalCompressProgress(nValue);
        }
    }
    //������̬���ļ�

    this->SaveProjectToFile(tr("compile\\prj.bin"),0);

    QFile file;
    file.setFileName(sFileName);
    file.open(QIODevice::WriteOnly);
    QByteArray data;
    QDataStream filestream(&data,QIODevice::WriteOnly);

    QStringList picList = mPicPath.values();

    //��̬���̱��浽Ŀ��·���ļ�����
    this->SaveToStream("compile\\prj.bin","d:\\new",filestream);
    this->SavePicToFile(picList,filestream);
    //this->SaveProjProp();
    data = qCompress(data,5);
    file.write(data);
    file.close();
    emit this->SignalCompressProgress(100);

    //�ָ���̬�е�ͼƬ·��
    if(m_pSamSysParame->m_projectProp.bTouchInvalidPic)
    {
        for(int i=0; i<m_pSamSysParame->m_projectProp.sTIPicPathList.size(); i++)
        {
            path = m_pSamSysParame->m_projectProp.sTIPicPathList.at(i);
            if(mPath.contains(path))
            {
                path = mPath.value(path);
                m_pSamSysParame->m_projectProp.sTIPicPathList.replace(i,path);
                 qDebug() << "ffffff===   "<<m_pSamSysParame->m_projectProp.sTIPicPathList;
            }
        }
    }
    for(int i=0; i<size; i++)
    {
        path = pSceneSheet[i]->m_picturePath;
        if(mPath.contains(path))
        {
            path = mPath.value(path);
            pSceneSheet[i]->m_picturePath = path;
            pSceneSheet[i]->m_bChangePicPath = true;
        }

        QList<QGraphicsItem *> tmpList;
        QVector<QGraphicsItem *> itemList;
        tmpList.clear();
        itemList.clear();
        tmpList = pSceneSheet[i]->items();
        int tmpSize = tmpList.size();
        for(int i=0;i < tmpSize;i++)
        {
            QGraphicsItem *pItem = tmpList.at(i);
            if(!pItem) continue;
            QGraphicsItem *pParentItem= pItem->parentItem();
            if(pParentItem != 0)
                continue;
            if(pItem->type() == SAM_DRAW_OBJECT_TRACKER
               || pItem->type() == SAM_DRAW_OBJECT_LOCK)
                continue;
            itemList.push_back(pItem);
        }

        int sceneItemsize = itemList.size();

        for(int i = 0; i < sceneItemsize; i++)
        {
            QGraphicsItem *pItem = itemList.at(i);
            if(SAM_DRAW_OBJECT_GROUP == pItem->type())
            {
                QItemGroup *pItemGroup = dynamic_cast<QItemGroup *> (pItem);
                loadPicPath(pItemGroup,mPath);
            }

        }
    }
}
void MainWindow::SetCurrentPath(QString path)
{
    exePath = path;
    exePath.replace("\\","/");
}

QString MainWindow::currentPath()
{
    return exePath;
}

/************************************************************************
  *Functions:�ж�����ѡ����Ƿ�Ϊ��
  ************************************************************************
  *Value��
  *QComboBox &fontcombobox ���ô���Ҫ�жϵ����������б��
  ************************************************************************
  *returns:
  *bool �������б��ѡ���Ϊ�յĻ� ����false ��Ϊ�շ���true
  ************************************************************************
  *Edit time��2011.7.22
  *Edit by    ��zhy
  *************************************************************************/

bool MainWindow::bCheckFount(QComboBox &fontcombobox)
{
    if(fontcombobox.currentText().isEmpty())
    {
        QMessageBox box(QMessageBox::Information,tr("��ʾ"),tr("��ѡ�ı������壡"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
        box.exec();
        fontcombobox.setFocus();
        return false;
    }
    else
    {
        return true;
    }
}

//void MainWindow::on_actionCompress_triggered()
//{
//    Compress dlg(this);
//    dlg.DisableCompress(this->is_Is);
//    dlg.exec();
//}

//�����ļ���stream��
//sSourceFile -- Դ�ļ� ��·��
//sFileName   -- ����stream�е��ļ�������·��
void MainWindow::SaveToStream(QString sSourceFile,QString sFileName,QDataStream &stream)
{
    QString path;
    QFile f( sSourceFile );
    QString sname = "begin save project";
    if(f.open( QIODevice::ReadOnly ))
    {
        QByteArray s = f.readAll();
        stream << sname;
        stream << s;
        f.close();
    }
    else
    {
        path = "";
        stream <<path;
    }
    sname = "end save project";
    stream << sname;
    emit this->SignalCompressProgress(-1);
}

void MainWindow::LoadFromStream(QString sFileName,QDataStream &stream)
{
    QString path;
    stream >> path;
    if(path != "")
    {
        QFile f(sFileName);
        QByteArray fstream;
        stream>> fstream;
        if(f.open(QIODevice::WriteOnly))
        {
            f.write(fstream);
            f.close();
        }
        emit this->SignalCompressProgress(10);
    }
    stream >> path;
}

//��ѹ��
//sSourceFile -- ѹ���ļ�����·��
//sSaveName   -- ѹ������̬���ļ�������·��
void MainWindow::uncompressFile(QString sSourceName,QString sSaveName)
{
    emit this->SignalCompressProgress(0);
    QFile file(sSourceName);
    if(file.open(QIODevice::ReadWrite))
    {
        int size;
        size = file.size();
        QByteArray data;
        data = file.readAll();
        file.close();
        size = data.size();
        data = qUncompress(data);
        size = data.size();
        //QFile tmpFile;
        //tmpFile.open(QIODevice::ReadWrite);

        //tmpFile.write(data);
       // size = file.size();

        QDataStream stream(&data,QIODevice::ReadOnly);

        LoadFromStream(sSaveName,stream);

        LoadPicFromFile(stream);
        //file.close();
    }
}

/************************************************************************
  *Functions:ɾ����ָ�����������ȫ�ֺ�ͳ�ʼ����
  *�������壺sMacroNameҪɾ�����ѱ���ɹ��ĺ�����
  *Edit by zqh
  *Edit time��2011.8.10
  *************************************************************************/
void MainWindow::deleteMacro(QString sMacroName)
{
    //int i = 0;
   // QString sName = "";
//    for(i = 0; i < m_pSamSysParame->m_qvcGlobalMaroProp.size();i++) //����ȫ�ֺ�
//    {
//        sName = m_pSamSysParame->m_qvcGlobalMaroProp.at(i).sMaroName;
//        if(sName == sMacroName)
//        {
//            m_pSamSysParame->m_qvcGlobalMaroProp.remove(i);
//            break;
//        }
//    }
//    for(i = 0; i < m_pSamSysParame->m_qvcInitMaroProp.size();i++) //����ȫ�ֺ�
//    {
//        sName = m_pSamSysParame->m_qvcInitMaroProp.at(i).sMaroName;
//        if(sName == sMacroName)
//        {
//            m_pSamSysParame->m_qvcInitMaroProp.remove(i);
//            break;
//        }
//    }
}
/************************************************************************
  *Functions:�䷽ѡ�����ۺ���
  ************************************************************************
  *Value��
  *�����ۺ���
  ************************************************************************
  *returns:
  *��
  ************************************************************************
  *Edit time��2011.8.17
  *Edit by    ��zhy
  *Changed by zqh on 2011.8.18
  *************************************************************************/
void MainWindow::ONRecipeChoice()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED  || isCompiled)
    {
        return;
    }

    if( m_pSamSysParame->m_qvcRecipe.size() <= 0 )
    {
        QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("�䷽��δ����!"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }

    QRecipeChoiceDlg  *recipechoice=new QRecipeChoiceDlg(0,this);
    if( recipechoice->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = recipechoice->pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    recipechoice->deleteLater();
    recipechoice = NULL;
}
/************************************************************************
  *Functions:�䷽ѡ�����ۺ���
  ************************************************************************
  *Value��
  *˫���ۺ���
  ************************************************************************
  *returns:
  *��
  ************************************************************************
  *Edit time��2011.8.17
  *Edit by    ��zhy
  *Changed by zqh on 2011.8.18
  *************************************************************************/
void MainWindow::modifyRecipeChoice(QGraphicsItem *item)
{
    if( m_pSamSysParame->m_qvcRecipe.size() <= 0 )
    {
        QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("�䷽��δ����,�ÿؼ���Ч!"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }

    QRecipeChoiceDlg *recipechoice=new QRecipeChoiceDlg(item,this);
    if(recipechoice->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = recipechoice->pCopyItem;
        OnDoubleClik(item,oldItem);
    }
    recipechoice->deleteLater();
    recipechoice = NULL;
}

/*************************************************************************
  *�����������������λ��ť������ۺ���
***************************************************************************/
void MainWindow::createrecipetable()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED  || isCompiled)
    {
        return;
    }
    if( m_pSamSysParame->m_qvcRecipe.size() <= 0 )
    {
        QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("�䷽��δ����!"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }

    Qrecipetable *recipetabledlg=new Qrecipetable(0,this);
    if(recipetabledlg->exec()==QDialog::Accepted)
    {
        QGraphicsItem * oldItem = recipetabledlg->pCopyItem;
        DrawItemToScene FunClass;
        FunClass.CopyItem(&pDrawToSceneItem,oldItem);
        SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    recipetabledlg->deleteLater();
    recipetabledlg = NULL;
}

void MainWindow::modifyRecipeDisplay(QGraphicsItem *item)
{
    if( m_pSamSysParame->m_qvcRecipe.size() <= 0 )
    {
        QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("�䷽��δ����,�ÿؼ���Ч!"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }

    Qrecipetable *recipedisplay=new Qrecipetable(item,this);
    if(recipedisplay->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = recipedisplay->pCopyItem;
       OnDoubleClik(item,oldItem);
    }
    recipedisplay->deleteLater();
    recipedisplay = NULL;
}
/************************************************************************
  *Functions:ͨ��ȡ���οؼ��ĵ�ǰѡ���������ҵ���ǰҳ��
  ************************************************************************
  *Value��
  *QString stemp����ǰ���οؼ���ѡ���� ���磺��001������1��
  ************************************************************************
 *returns:
  *int���ͣ���ʾ���ҵ��˵�ǰҳ���������е�λ�� ���Ҳ����Ļ�����0
  ************************************************************************
  *Edit time��2011.8.30
  *Edit by    ��zhy
  *************************************************************************/
int MainWindow::nFindActiveSheetIndex(QString stemp)
{
    QStringList slist=stemp.split(":");
    if(slist.size()!=2)//����
    {
        return 0;
    }
    for(int i=0;i<pwnd->pSceneSheet.size();i++)
    {
        if(slist.at(1)==pwnd->pSceneSheet.at(i)->sNewScreenName)
        {
            return i;
        }
    }
    return 0;
}
void MainWindow::lineItemchanged(SamDrawScene *scene,QGraphicsItem *item,
                                 QPainterPath oldPath,QPainterPath newPath)
{
    undoStack->push(new LineItemCommand(scene,item, oldPath,newPath));
}
void MainWindow::polygonchanged(SamDrawScene *scene,QGraphicsItem *item,
                                QPolygonF oldPolygon,QPolygonF newPolygon)
{
    undoStack->push(new PolygonItemCommand(scene,item, oldPolygon,newPolygon));
}
void MainWindow::deleteDirectory(QFileInfo fileList)
{
    if(fileList.isDir())
    {
        int childCount =0;
        QString dir = fileList.filePath();
        QDir thisDir(dir);
        childCount = thisDir.entryInfoList().count();
        QFileInfoList newFileList = thisDir.entryInfoList();
        if(childCount>2)
        {
            for(int i=0;i<childCount;i++)
            {
                if(newFileList.at(i).fileName().operator ==(".")
                    |newFileList.at(i).fileName().operator ==(".."))
                {
                    continue;
                }
                deleteDirectory(newFileList.at(i));
            }
        }
        //fileList.absoluteDir().rmpath(fileList.fileName());
    }
    else if(fileList.isFile()){
        fileList.absoluteDir().remove(fileList.fileName());
    }
}
void MainWindow::SaveFontDir(QStringList list,QDataStream &stream)
{
    QFile file("Fonts/fontdir");
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream txtstream(&file);
        foreach(QString sFont,list)
        {
            QString sFileName = sFont +tr(".ttf");
            QString line = sFont +tr(" ")+sFileName+tr(" FT n 50 0 su\n");
            txtstream << line;
        }
        file.close();
    }
    this->SaveToStream("Fonts/fontdir",
                       "/usr/local/qte/lib/fonts/fontdir",stream);
}


void MainWindow::SaveLibraryFile()
{
    QFile systemlibFile("compile/Library.sk");
    QFile userlibFile("compile/userLibrary.sk");

    if(systemlibFile.open(QIODevice::WriteOnly)
        && userlibFile.open(QIODevice::WriteOnly))
    {
        QDataStream libStream(&systemlibFile);
        QDataStream userlibStream(&userlibFile);
        QGraphicsItem *pItem = NULL;
        foreach(QString sPath,lLibPaths)
        {
            QStringList sList = sPath.split("-", QString::SkipEmptyParts);

            if(sList.size() == 4)
            {
                //�Զ���ͼ��
                pItem = OpenLibraryFile(sPath);
                if(pItem != NULL)
                {
                    this->saveItem(pItem,userlibStream);
                }

            }
            else if(sList.size() == 3)
            {
                //ϵͳͼ��
                pItem = OpenLibraryFile(sPath);
                if(pItem != NULL)
                {
                    this->saveItem(pItem,libStream);
                }
            }
        }
    }
    if(systemlibFile.isOpen())
        systemlibFile.close();

    if(userlibFile.isOpen())
        userlibFile.close();
}
void MainWindow::saveItem(QGraphicsItem *pItem,QDataStream &stream)//save
{

    switch(pItem->type())
    {
    case SAM_DRAW_OBJECT_RECT:              //15
        {
            stream << QRectItem::Type;
            QRectItem *pRectItem = dynamic_cast<QRectItem *>(pItem);
            stream << pRectItem;
            break;
        }
    case SAM_DRAW_OBJECT_ELIPSE:              //16
        {
            stream << QElipseItem::Type;
            QElipseItem *pElipseItem = dynamic_cast<QElipseItem *>(pItem);
            stream << pElipseItem;
            break;
        }
    case SAM_DRAW_OBJECT_LINE:                 //17
        {
            stream << QLineItem::Type;
            QLineItem *pLineItem = dynamic_cast<QLineItem *>(pItem);
            stream << pLineItem;
            break;
        }
    case SAM_DRAW_OBJECT_POLYGON:              //18
        {
            stream << QPolygonItem::Type;
            QPolygonItem *pPolygonItem = dynamic_cast<QPolygonItem *>(pItem);
            stream << pPolygonItem;
            break;
        }
    case SAM_DRAW_OBJECT_FOLDLINE:             //19
        {
            stream << QFoldLineItem::Type;
            QFoldLineItem *pFoldLineItem = dynamic_cast<QFoldLineItem *>(pItem);
            stream << pFoldLineItem;
            break;
        }
    case SAM_DRAW_OBJECT_FREELINE:             //20
        {
            stream << QFreeLineItem::Type;
            QFreeLineItem *pFreeLineItem = dynamic_cast<QFreeLineItem *>(pItem);
            stream << pFreeLineItem;
            break;
        }
    case SAM_DRAW_OBJECT_TEXT:                 //22
        {
            stream << QSimpleTextItem::Type;
            QSimpleTextItem *pTextItem = dynamic_cast<QSimpleTextItem *>(pItem);
            stream << pTextItem;
            break;
        }
    case SAM_DRAW_OBJECT_PIXMAP:
        {
            stream << QPixmapItem::Type;
            QPixmapItem *pPixmap = dynamic_cast<QPixmapItem *>(pItem);
            stream << pPixmap;
            break;
        }
    case SAM_DRAW_OBJECT_LINECIRCLE:           //25
        {
            stream << QLineCircleItem::Type;
            QLineCircleItem *pLineCircleItem = dynamic_cast<QLineCircleItem *>(pItem);
            stream << pLineCircleItem;
            break;
        }
    case SAM_DRAW_OBJECT_ROUNDEDRECT:
        {
            stream << QRoundedRect::Type;
            QRoundedRect *pRoundRect = dynamic_cast<QRoundedRect *>(pItem);
            stream << pRoundRect;
            break;
        }
    case SAM_DRAW_OBJECT_ARC:
        {
            stream << QArcItem::Type;
            QArcItem *pArcItem = dynamic_cast<QArcItem *>(pItem);
            stream << pArcItem;
            break;
        }
    case SAM_DRAW_OBJECT_GROUP:                //23
        {
            stream << QItemGroup::Type;
            QItemGroup *pItemGroup = dynamic_cast<QItemGroup *>(pItem);
            stream << pItemGroup;
            break;
        }
    default:
        break;
    }

}
/************************************************************************
  *Functions:����HMI�ͺ������жϸ��ͺ��ж��ٸ����ӿ�
  ************************************************************************
  *Value��
  *QString sHMIModle��HMI�ͺ����� �磺SK-070AS
  ************************************************************************
 *returns:
  *QString����
  * ��һλ ��Ϊ S -----ֻ��һ������ D-----��������
  *�ڶ�λ ��Ϊ E------����̫���ӿ� N----����̫���ӿ�
  ************************************************************************
  *Edit time��2011.5.26
  *Edit by    ��zhy
  *************************************************************************/
QString MainWindow::GetHMIConnectInformation(QString sHMIModle)
{
    QString sVal = "SN";

    //D ��com2��S û��com2��E ����̫����N û����̫��
    /*if(sHMIModle == "AK-043AE")
    {
        sVal="SN";
    }
    else if(sHMIModle == "AK-043AC")
    {
        sVal="SN";
    }
    else if(sHMIModle == "AK-050AS")
    {
        sVal="SE";
    }
    else if(sHMIModle == "AK-050AE")
    {
        sVal="SN";
    }
    else if(sHMIModle == "AK-070AS")
    {
        sVal="DE";
    }
	else if(sHMIModle == "AK-070AE")
    {
        sVal="DN";
    }
	else if(sHMIModle == "AK-102AS")
    {
        sVal="DE";
    }
	else if(sHMIModle == "AK-102AE")
    {
        sVal="DN";
    }*/

    return sVal;
}

//�����ʱ����Ҫ���HMI�ͺţ���ʾģʽ���������õ���Ϣ��ѹ���ļ�ͷ��
//����Ϣ������10�ֽ�QByteArray�в�����
QByteArray MainWindow::FileHeader()
{
    QByteArray header;
    header.resize(10);
    header.fill(0);

    QString sDeviceModel = m_pSamSysParame->m_projectProp.sPjtModel;
    int nDisplayMode = m_pSamSysParame->m_projectProp.nDisplayMode;


    QByteArray displayMode;

    displayMode.setNum(nDisplayMode);
    header.replace(0,8,sDeviceModel.left(8).toAscii());
    header.replace(8,1,displayMode);

    char Status;
    bool bHistorydata = m_pSamSysParame->m_projectProp.bClearHisData;
    bool bAlarm = m_pSamSysParame->m_projectProp.bClearHisAlarm;
    bool brecip = m_pSamSysParame->m_projectProp.bDownLoadRecipe;
    bool bRestart = m_pSamSysParame->m_projectProp.bStratScreen;
    bool bHideMouse = m_pSamSysParame->m_projectProp.bHideMouse;
    bool bMouse = false;
    QStringList lst = m_pSamSysParame->m_projectProp.sBackupForNewVer;
    if(!lst.isEmpty())
    {
        bMouse = lst.at(0).toInt();
    }
    Status = (bAlarm << 1)|(bHistorydata << 2)|(brecip << 3)
             | (bHideMouse << 4)| (bMouse << 5)|bRestart;

    header[9] = Status;

    return header;
}
void MainWindow::information(QString str, MSG_TYPE eType)
{
    emit this->SignalInformation(str, eType);
}

QMap<QString,QString> MainWindow::getFontMap()
{
	return m_fontMap;
}
/************************************************************************
  *Functions:ͨ�����뻭�������ֵ�ҵ������������е�����
  ************************************************************************
  *Value��
  *int nScreenId���߼�����ֵ
  ************************************************************************
 *returns:
  *�������ƣ��Ҳ����Ļ����ؿ�
  ************************************************************************
  *Edit time��2011.12.3
  *Edit by    ��zhy
  *************************************************************************/
QString  MainWindow::GetSCreenName(int nScreenId)
{
    QString sScreenName;
    for(int j=0, nrealadd=0;j<=nScreenId;nrealadd++)
    {//����j����ʱ��������  nrealadd����ҳ�����ʵ��ַ
        if(j>pwnd->pSceneSheet.size()-1)
        {
            sScreenName.clear();
            break;
        }
        if(pwnd->pSceneSheet.at(nrealadd)->nIsSceneOrWindow!=2)//�����Զ������
        {
            if(j ==nScreenId )//ѭ�����ض��Ĵ���֮��
            {//��Ӧ��ѭ��nrealadd����ʵ�ʵ�ַ
                sScreenName=pwnd->pSceneSheet.at(nrealadd)->sNewScreenName;
                break;
            }
            j++;
        }
    }
    return sScreenName;
}
/************************************************************************
  *Functions:ͨ�����뻭�������ֵ�ҵ������������е�ʵ������
  ************************************************************************
  *Value��
  *int nScreenId���߼�����ֵ
  ************************************************************************
 *returns:
  *���ػ����������е�ʵ�������Ҳ����Ļ�����0
  ************************************************************************
  *Edit time��2011.12.3
  *Edit by    ��zhy
  *************************************************************************/
int  MainWindow::GetSCreenID(int nScreenId)
{
    int sScreenID=GetFristScreenID(1);
    for(int j=0, nrealadd=0;j<=nScreenId;nrealadd++)
    {//����j����ʱ��������  nrealadd����ҳ�����ʵ��ַ
        if(j>pwnd->pSceneSheet.size()-1)
        {
            break;
        }
        if(pwnd->pSceneSheet.at(nrealadd)->nIsSceneOrWindow!=2)//�����Զ������
        {
            if(j ==nScreenId )//ѭ�����ض��Ĵ���֮��
            {//��Ӧ��ѭ��nrealadd����ʵ�ʵ�ַ
                sScreenID=nrealadd;
                break;
            }
            j++;
        }
    }
    return sScreenID;
}
/************************************************************************
  *Functions:ɾ��������ߴ��ڻ����Զ�����̵�ʱ��ˢ�����οؼ���ҳ����ת������
  ************************************************************************
  *Value��
  *��
  ************************************************************************
 *returns:
  *��
  ************************************************************************
  *Edit time��2011.12.6
  *Edit by    ��zhy
  *************************************************************************/
int  MainWindow::DealWithDeleteScreen()
{
    if(pwnd->m_pSamSysParame->m_projectProp.nScreensaverIndex > pwnd->nActiveSheetIndex)
    {
        pwnd->m_pSamSysParame->m_projectProp.nScreensaverIndex--;//ɾ����������֮ǰ�Ļ���ʱ ��ż�1
    }
    else if(pwnd->m_pSamSysParame->m_projectProp.nScreensaverIndex == pwnd->nActiveSheetIndex)
    {
        pwnd->m_pSamSysParame->m_projectProp.nScreensaverIndex=GetFristScreenID(0);//ɾ����ǰҳ���������
    }
    if(pwnd->m_pSamSysParame->m_projectProp.nLoadSceneIndex > pwnd->nActiveSheetIndex)
    {
        pwnd->m_pSamSysParame->m_projectProp.nLoadSceneIndex--;//ɾ����ʼ��ҳ��֮ǰ�Ļ���ʱ ��ż�1
    }
    else if(pwnd->m_pSamSysParame->m_projectProp.nLoadSceneIndex == pwnd->nActiveSheetIndex)
    {
        pwnd->m_pSamSysParame->m_projectProp.nLoadSceneIndex=GetFristScreenID(0);//ɾ����ǰҳ���������
    }
    if(pwnd->m_pSamSysParame->m_projectProp.nStartScreenIndex  > pwnd->nActiveSheetIndex)
    {
        pwnd->m_pSamSysParame->m_projectProp.nStartScreenIndex--;//ɾ����������֮ǰ�Ļ���ʱ ��ż�1
    }
    else if(pwnd->m_pSamSysParame->m_projectProp.nStartScreenIndex  == pwnd->nActiveSheetIndex)
    {
        pwnd->m_pSamSysParame->m_projectProp.nStartScreenIndex=GetFristScreenID(0);
    }
    for(int i=0;i<pwnd->m_pSamSysParame->m_ctlByPlc.mSceneCtlByBitList.size();i++)
    {
        if(pwnd->m_pSamSysParame->m_ctlByPlc.mSceneCtlByBitList.at(i).nCtlSceneId>pwnd->nActiveSheetIndex)
        {
            pwnd->m_pSamSysParame->m_ctlByPlc.mSceneCtlByBitList[i].nCtlSceneId--;
        }
        else if(pwnd->m_pSamSysParame->m_ctlByPlc.mSceneCtlByBitList.at(i).nCtlSceneId == pwnd->nActiveSheetIndex)
        {
            pwnd->m_pSamSysParame->m_ctlByPlc.mSceneCtlByBitList[i].nCtlSceneId=GetFristScreenID(1);
        }
    }
    for(int i=0;i<pwnd->m_pSamSysParame->m_hmiProtectProp.mProtectList.size();i++)//HMI������תҳ��
    {
        if(pwnd->m_pSamSysParame->m_hmiProtectProp.mProtectList.at(i).nProtectSceneId>pwnd->nActiveSheetIndex)
        {
            pwnd->m_pSamSysParame->m_hmiProtectProp.mProtectList[i].nProtectSceneId--;
        }
        else if(pwnd->m_pSamSysParame->m_hmiProtectProp.mProtectList.at(i).nProtectSceneId == pwnd->nActiveSheetIndex)
        {
            pwnd->m_pSamSysParame->m_hmiProtectProp.mProtectList[i].nProtectSceneId=GetFristScreenID(1);
        }
    }
    if(pwnd->nActiveSheetIndex==pwnd->pSceneSheet.size())
    {
        pwnd->nActiveSheetIndex--;
    }
    pwnd->pView->setScene(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]);
	return 0;
}
/************************************************************************
  *Functions:������DealWithDeleteScreen�����������ã���ɾ����ǰѡ��Ļ����ʱ��
  *�������οؼ�����Ļ����������ֹ��ת���Զ������
  ************************************************************************
  *Value��
  *int nIncludeWindow ��ʾ�Ƿ�������ڣ��������ڵĻ�Ϊ1 ������Ϊ0
  ************************************************************************
 *returns:
  *int ���ͷ��ص��ǵ�һ��������ߴ����������е��±�
  ************************************************************************
  *Edit time��2011.12.17
  *Edit by    ��Dylan
  *************************************************************************/
int  MainWindow::GetFristScreenID(int nIncludeWindow)
{
        for(int i=0;i<pwnd->pSceneSheet.size();i++)
    {
            if(pwnd->pSceneSheet.at(i)->nIsSceneOrWindow==0
               ||pwnd->pSceneSheet.at(i)->nIsSceneOrWindow==nIncludeWindow)
            {
                return i;
            }
        }
}

/************************************************************************
  *Functions:���Ļ�����ߴ������Ƶ�ʱ��ˢ�»��水ť�͹��ܰ�ť�л��������
  ************************************************************************
  *Value��
  *��
  ************************************************************************
 *returns:
  *��
  ************************************************************************
  *Edit time��2012.1.7
  *Edit by    ��Dylan
  *************************************************************************/
void  MainWindow::reScreenorwindowName(QString sOldname,QString sNewname)
{
    QList<QGraphicsItem *> Items;
    QStringList sList;
    QString sName="";
    QString sTmp="";
    int totalSceneNum = pwnd->pSceneSheet.size();
    for(int i=0;i<totalSceneNum;i++)
    {
        if(pwnd->pSceneSheet[i]->nIsSceneOrWindow==2)//�Զ�����̵�ʱ��
        {
            continue;
        }
        Items = pwnd->pSceneSheet[i]->items();   //��ǰҳ�����е�item
        for(int j = 0; j < Items.size(); j++)
        {
            sList = Items.at(j)->data(GROUP_DATALIST_KEY).toStringList(); //ȡ��ÿ��item����������
            if(sList.size() < 20)
                continue;//break;
            sName = sList.at(19);
            if(sName.mid(0,2) == "SB")//���水ť
            {
                sTmp.setNum(0);//��մ洢�����ݣ��������forѭ���Ҳ������ʵ����ݵĻ����ʾѡ��Ļ����Ѿ���ɾ�����߲�����
                sList.replace(57,sTmp);//���ó���ת����һ������
                Items[j]->setData(GROUP_DATALIST_KEY,sList);
                QString screenName=sList.at(56);
//                for(int nIndex=0;nIndex<totalSceneNum;nIndex++)
//                {
                    if(sOldname==screenName)
                    {
                        sList.replace(56,sNewname);
                        Items[j]->setData(GROUP_DATALIST_KEY,sList);
                        break;
               //     }
                }
            }
            else if(sName.mid(0,2) == "MF")//���ܰ�ť
            {
                sTmp.setNum(0);
                sList.replace(93,sTmp);
                Items[j]->setData(GROUP_DATALIST_KEY,sList);
                QString screenName=sList.at(94);
//                for(int nIndex=0;nIndex<totalSceneNum;nIndex++)
//                {
                    if(sOldname==screenName)
                    {
                        sList.replace(94,sNewname);
                        Items[j]->setData(GROUP_DATALIST_KEY,sList);
                        break;
                    }
              //  }
            }
        }
    }
}
/************************************************************************
  *Functions:�ڸ����Զ���������Ƶ�ʱ��ˢ���õ��Զ���������ƵĿؼ�
  ************************************************************************
  *Value��
  *
  ************************************************************************
  *returns:
  *��
  ************************************************************************
  *Edit time��2012.1.7
  *Edit by    ��Dylan
  *************************************************************************/
void MainWindow::reUserkeyboardname(QString sOldName,QString sNewName)
{
    QList<QGraphicsItem *> Items;
    QGraphicsItem *pItem;
    QStringList sList;
    QStringList KbLocation;
    int nID = 0;
    int  i = 0;
    int j = 0;

    int totalSceneNum = pwnd->pSceneSheet.size();
    for(i = 0; i < totalSceneNum;i++)   //ɨ������ҳ��
    {
        Items = pwnd->pSceneSheet[i]->items();    //��ǰҳ�����е�item
        for(j = 0; j < Items.size(); j++)   //ɨ�赱ǰҳ������пؼ�
        {
            pItem = Items.at(j);//->topLevelItem();
            KbLocation.clear();//���keyboard�б�

            if(pItem->parentItem())
                continue;
            if(pItem->type() == SAM_DRAW_OBJECT_TRACKER
               || pItem->type() == SAM_DRAW_OBJECT_LOCK)
            {
                continue;
            }
            nID = pItem->data(GROUP_TYPE_KEY).toInt(); //ȡ�ؼ���Key��
            sList = pItem->data(GROUP_DATALIST_KEY).toStringList(); //ȡ��ÿ��item����������

            switch(nID)
            {
            case GROUP_TYPE_WORDBTN: //�ְ�ť
            case GROUP_TYPE_ASCIIENTRY: //ASC������
            case GROUP_TYPE_MFUNCTION: //�๦�ܰ�ť
            case GROUP_TYPE_MULSTATEBTN: //��״̬��ť
                Rename(sOldName, sNewName,sList);//���ú�������
                pItem->setData(GROUP_DATALIST_KEY,sList);
                break;
            case GROUP_TYPE_NUMENTRY://��ֵ����
                if(sList.at(130).toInt())//����ʹ���Զ������
                {
                    if(sOldName==sList.at(131))//���ҵ���Ӧ�ļ���
                    {
                        sList.replace(131,sNewName);
                    }
                }

            }
            pItem->setData(GROUP_DATALIST_KEY,sList);
        }
    } //end switch
}
/************************************************************************
  *Functions:��checkUserKeyboard������������ �����޸��û��Զ������
  ************************************************************************
  *Value��
  *��ֵ������Զ���������ݴ洢��λ����������λ�ò�ͬ����ȥ��ֵ����֮�� ʣ�µĶ��ڸú���
  *��ִ��
  ************************************************************************
  *returns:
  *��
  ************************************************************************
  *Edit time��2012.1.7
  *Edit by    ��Dylan
  *************************************************************************/
void MainWindow::Rename(QString sOldName,QString sNewName,QStringList &sList)
{
    if(sList.at(24).toInt())//����ʹ���Զ������
    {
        if(sOldName==sList.at(25))//���ҵ���Ӧ�ļ���
        {
            sList.replace(25,sNewName);
        }
    }
}

void MainWindow::onScreenChange(int nStr)
{
    if(nStr < 0)
    {
        return;
    }

    QString strCombox = pChScreen->itemText(nStr);
    nActiveSheetIndex = m_ChScreenMap.find(strCombox).value();
    pView->setScene(pSceneSheet[nActiveSheetIndex]);
    //wxy �л�����ʱ������������Ĭ������
    QScrollBar *pHorizScrollBar = pView->horizontalScrollBar();
    if(pHorizScrollBar)
    {
        pHorizScrollBar->setValue(0);
    }
    QScrollBar *pVerticalScrollBar = pView->verticalScrollBar();
    if(pVerticalScrollBar)
    {
        pVerticalScrollBar->setValue(0);
    }

    QString strDest;
    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);
}

void MainWindow::onFrmLanguageChange(int nLanIndex) //Alter toolbar Language combobox
{
    //return;
    //qDebug() <<"onFrmLanguageChange:start";
    if(!bToolBarCMBInit)
    {
        return;
    }

    if(nLanIndex < 0) //ֻ��һ�����Ե�ʱ��������
    {
        return;
    }

    if(this->qLanguagecmb->count() <= 0)
    {
        return;
    }

    QList<QGraphicsItem *> Items;
    //QStringList sList;
    int count   = 0;
    //int nID     = 0;
    //m_pSamSysParame->m_mixGlobalVar.m_nCurLan = nLanIndex;
    count       = pSceneSheet.size(); //��������
    for(int i = 0 ; i < count; i++) //ɨ�����л���
    {
        Items = pSceneSheet[i]->items();   //��ǰҳ�����е�item
        foreach(QGraphicsItem *pItem, Items)
        {
            if(!pItem)
            {
                continue;
            }

            if(SAM_DRAW_OBJECT_GROUP == pItem->type())
            {
                if(pItem->parentItem() == 0 && pItem->type() != SAM_DRAW_OBJECT_TRACKER && pItem->type() != SAM_DRAW_OBJECT_LOCK)
                {
                    //changeItemLanguageAttr(pItem);
                    QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
                    //qDebug() <<"onFrmLanguageChange:"<< item->GroupType();
                    item->redrawForChangeLanguage(qLanguagecmb->currentIndex());
                }
            }
        }
        /*foreach(QGraphicsItem *item,Items)
        {
            if(!item)
            {
                continue;
            }
            if(!item->parentItem())
            {
                //sList   = item->topLevelItem()->data(GROUP_DATALIST_KEY).toStringList(); //ȡ��ÿ��item����������
                //nID     = item->data(GROUP_TYPE_KEY).toInt(); //ȡ�ؼ���Key��
                //alterControlLanguage(item,sList,nID,nLanIndex);
                changeItemLanguageAttr(item);
            }
        }*/
    }
    //qDebug() <<"onFrmLanguageChange:end";
}



//ȡItem��sceneBoundingRect�������ƾ�̬ͼƬ��ʱ����Ҫ��data��ȡʵ�ʵ�rect
//���㸴�Ʋ��ֵĲ���
QRectF MainWindow::GetItemRect(QGraphicsItem *item)
{
    int type;
    type = item->data(GROUP_TYPE_KEY).toInt();
    QRectF rect;

    if(type == GROUP_TYPE_STATICPIC || type == GROUP_TYPE_STATICPIC)
    {
        rect = item->data(GROUP_RECT_KEY).toRectF();
    }
    else
        rect = item->sceneBoundingRect();

    return rect;
}
QSizeF MainWindow::ScalePicture(QSizeF size1,QSizeF size2,QSizeF oldSize)
{
    double lWidth,lHeight;
    double dW,dH;
    double dScale = 1;
    double d1,d2 = 1;
    lWidth = size1.width();
    dW = (double)lWidth/oldSize.width();
    lHeight = size1.height();
    dH = (double)lHeight/oldSize.height();
    d1 = dH>dW ? dH:dW;


    lWidth = size2.width();
    dW = (double)lWidth/oldSize.width();
    lHeight = size2.height();
    dH = (double)lHeight/oldSize.height();
    d2 = dH>dW ? dH:dW;

    dScale = d1 > d2 ? d1:d2;
    return QSizeF(oldSize*dScale);

}
QGraphicsItem * MainWindow::onGetItemFromFile(QString sPath)
{
	QGraphicsItem *tmpItem = NULL;
	QList <QGraphicsItem*> listItem;
	QStringList str = sPath.split('-');
	if(str.isEmpty())
	{
		return NULL;
	}
	int nLoadPag = str.at(0).toInt();

	
	if(pwnd->vBaseLibraryScene.isEmpty() &&pwnd->vBaseLibraryScene.size()<= nLoadPag )
	{
		return NULL;
	}
	listItem = pwnd->vBaseLibraryScene.at(nLoadPag)->TopItems();
	foreach (QGraphicsItem * pItem, listItem)
	{
		QString sname = pItem->data(GROUP_NAME_KEY).toString();
		if (sPath == sname)
		{
			DrawItemToScene dfun;
			dfun.CopyItem(&tmpItem,pItem);
			break;
		}
	}
	
	return tmpItem;
}
//����ű�
void MainWindow::saveLibrary(QDataStream &stream)
{
    int libraryList=macros.size();
    stream << libraryList;
    for(int i=0;i<libraryList;i++)
    {
        macros[i].save(stream);
    }
    if(pwnd->getProVersion() >= 3125)
    {
        int variantList=g_Vars.size();
        stream << variantList;
        for(int j=0;j<variantList;j++)
        {
            stream << g_Vars[j].addr;
            stream << g_Vars[j].dataType;
            stream << g_Vars[j].RWPerm;
            stream << g_Vars[j].varName;
            stream << g_Vars[j].count;
            stream << g_Vars[j].bOffset;
            if(g_Vars[j].bOffset)
            {
                stream << g_Vars[j].offsetAddr;
            }
        }
    }
}

//��ȡ�ű�
void MainWindow::loadLibrary(QDataStream &stream)
{

    if(pwnd->getProVersion() < 2781)//�ɰ汾
    {
        int libraryList=0;
        stream >> libraryList;
        librarys.clear();
        macros.clear();
        librarys.resize(libraryList);
        macros.resize(libraryList);
        for(int i=0;i<libraryList;i++){
            stream >> librarys[i].code;
            stream >> librarys[i].functions;
            stream >> librarys[i].isCompiled;
            stream >> librarys[i].libName;
            stream >> librarys[i].type;

            macros[i].setCode(librarys[i].code);
            macros[i].setCompipiled(librarys[i].isCompiled);
            if(!librarys[i].type)
            {
                macros[i].functions = librarys[i].functions;
            }
            macros[i].libName = librarys[i].libName;
            macros[i].type = librarys[i].type;
            macros[i].setMD5(QByteArray());

            int variantList=0;
            stream >> variantList;
            librarys[i].variants.resize(variantList);
            for(int j=0;j<variantList;j++){
                stream >> librarys[i].variants[j].addr;
                stream >> librarys[i].variants[j].dataType;
                stream >> librarys[i].variants[j].RWPerm;
                stream >> librarys[i].variants[j].varName;
                stream >> librarys[i].variants[j].count;
            }
            macros[i].setVar(librarys[i].variants);
        }
    }
    else
    {
        int libraryList=0;
        stream >> libraryList;
        macros.clear();
        macros.resize(libraryList);
        for(int i=0;i<libraryList;i++)
        {
            macros[i].load(stream);
        }
        //��ȡȫ�ֱ���
        if(pwnd->getProVersion() >= 3125)
        {
            g_Vars.clear();
            int variantList=0;
            stream >> variantList;
            g_Vars.resize(variantList);
            for(int j=0;j<variantList;j++)
            {
                stream >> g_Vars[j].addr;
                stream >> g_Vars[j].dataType;
                stream >> g_Vars[j].RWPerm;
                stream >> g_Vars[j].varName;
                stream >> g_Vars[j].count;
                if(pwnd->getProVersion() >= 2914)//�°汾
                {
                    stream >> g_Vars[j].bOffset;
                    if(g_Vars[j].bOffset)
                    {
                        stream >> g_Vars[j].offsetAddr;
                    }
                }
                else
                {
                    g_Vars[j].bOffset = false;
                }
            }
        }
        else
        {
            g_Vars.clear();
        }
    }
}



void MainWindow::loadSysLibs()
{
    QLibrary lib("scriptLib.dll");
    typedef QVector<stScriptLib> (*GETPRO)( );
    if(lib.load())
    {
        qDebug() << "load scriptLib.dll sucessful";
        GETPRO loadLibs= (GETPRO)lib.resolve("getSysLibs");
        if(loadLibs)
        {
            sysLibs = loadLibs();
            qDebug() << sysLibs.size();
            qDebug() << "load scriptLib.dll:loadLibs sucessful";
        }
		lib.unload();
    }
    else
        qDebug() << "load scriptLib.dll faild";

	QLibrary libA("LclPara.dll");
	typedef QMap<QString,QString> (*GETPROA)( );
	if(libA.load())
	{
		GETPROA loadLibs= (GETPROA)libA.resolve("sysPrarms");
		if(loadLibs)
		{
			m_LocalReg = loadLibs();
			qDebug() << m_LocalReg.size();
		}
		libA.unload();
	}
	else
		qDebug() << "load LclPara.dll faild";

}
int MainWindow::getCurrentSamp()
{
	int currentIndex = -1;
	QTreeWidgetItem *tree_samp = tree->currentItem();
	if (tree_hisdatalog && tree_samp && tree_samp->parent() == tree_hisdatalog)
	{
		currentIndex = tree_hisdatalog->indexOfChild(tree_samp);
	}
	return currentIndex;
}
/***************************************************************
 *�������ƣ�setToolBoxFloat
 *�������ܣ����ù�����Ϊ����Ч��
 *�������壺NULL
 *����ֵ:       NULL
 *�༭���ߣ�֣����
 *�༭���ڣ�2012.9.12
 **************************************************************/
void MainWindow::setToolBoxFloat()
{
    QList<QPushButton *> button = ui->m_toolwidgetBasic->findChildren<QPushButton *>();
    for(int i=0; i < button.count(); i++)//ͨ��i�ķ�Χȷ����Ҫ������Щbutton
    {
        setDynamicImage(button.at(i));
    }
    QList<QPushButton *> buttonCtl = ui->m_toolwidgetCtl->findChildren<QPushButton *>();
    for(int i=0; i < buttonCtl.count(); i++)//ͨ��i�ķ�Χȷ����Ҫ������Щbutton
    {
        setDynamicImage(buttonCtl.at(i));
    }
}

/***************************************************************
 *�������ƣ�setDynamicImage
 *�������ܣ����ù�����Ϊ����Ч��
 *�������壺
 *button��     �����õİ�ťָ��
 *����ֵ:       NULL
 *�༭���ߣ�֣����
 *�༭���ڣ�2012.9.12
 **************************************************************/
void MainWindow::setDynamicImage(QPushButton *button)
{
    /*��������״̬��������button/�˳�button��*/
    QState *inside = new QState;
    inside->assignProperty(button,"flat", "false");//����buttonΪ͹��
    QState *outside = new QState;
    outside->assignProperty(button, "flat", "true");//����buttonΪƽ��

    /*�ѽ��롢�˳��¼���button����*/
    QEventTransition *enterTransition = new QEventTransition(button, QEvent::Enter);
    enterTransition->setTargetState(inside);//������button
    outside->addTransition(enterTransition);//��outside״̬�����ӵ�enterTransition�仯��ȥ

    QEventTransition *leaveTransition = new QEventTransition(button, QEvent::Leave);
    leaveTransition->setTargetState(outside);//����˳�button
    inside->addTransition(leaveTransition);//��inside״̬�����ӵ�leaveTransition�仯��ȥ

    /*����״̬��*/
    QStateMachine *machine = new QStateMachine(this);

    /*��״̬�������������״̬*/
    machine->addState(inside);
    machine->addState(outside);

    /*���ó�ʼ״̬*/
    machine->setInitialState(outside);

    /*����״̬��*/
    machine->start();
}
void MainWindow::initFontMap()
{
	sysFontMap.insert(tr("����"),"SIMSUN.TTC");
	sysFontMap.insert(tr("������"),"SIMSUN.TTC");
	sysFontMap.insert(tr("������"),"SIMFANG.TTF");
	sysFontMap.insert(tr("��������"),"STZHONGS.TTF");
	sysFontMap.insert(tr("��������"),"STSONG.TTF");
	sysFontMap.insert(tr("���ķ���"),"STFANGSO.TTF");
	sysFontMap.insert(tr("���Ĳ���"),"STCAIYUN.TTF");
	sysFontMap.insert(tr("������κ"),"STXINWEI.TTF");
	sysFontMap.insert(tr("���Ŀ���"),"STKAITI.TTF");
	sysFontMap.insert(tr("��������"),"STHUPO.TTF");
	sysFontMap.insert(tr("��������"),"STLITI.TTF");
	sysFontMap.insert(tr("����ϸ��"),"STXIHEI.TTF");
	sysFontMap.insert(tr("�����п�"),"STXINGKA.TTF");
	sysFontMap.insert(tr("����"),"SIMHEI.TTF");
	sysFontMap.insert(tr("����"),"SIMKAI.TTF");
	sysFontMap.insert(tr("����_GB2312"),"SIMKAI.TTF");
	sysFontMap.insert(tr("����"),"SIMLI.TTF");
	sysFontMap.insert(tr("΢���ź�"),"msyh.TTF");
	sysFontMap.insert(tr("��Բ"),"SIMYOU.TTF");
	sysFontMap.insert(tr("΢���ź� Bold"),"msyhbd.TTF");
	sysFontMap.insert(tr("��������"),"FZSTK.TTF");
	sysFontMap.insert(tr("����Ҧ�� Bold"),"FZYTK.TTF");
	
}
//���ű������Ƿ���ȷ
bool MainWindow::checkMacroName()
{
    int nIndex = 0;
    int nRow = 0;
    QString sScreenName;
    QString msg ;
    QString str;
    int result = true;
    int chkResult = 1;
    foreach(INIT_MARO_PROP initMac,m_pSamSysParame->m_qvcInitMaroProp)
    {
        foreach(Macro mac,macros)
        {
            if(mac.libName == initMac.sLibName)
            {
                if(mac.isCompiled())//�Ѿ�����ͨ��
                {
                    chkResult = 1;
                }
                else//δ����ͨ��
                {
                    chkResult = 0;
                }
                break;
            }
        }
        if(chkResult != 1)
        {
            if(chkResult == 0)//������δ����ͨ���Ľű�
            {
                str = tr("error:��ʼ���ű�������δ����ͨ���Ľű� %1").arg(initMac.sLibName);
            }
            else
            {
                str = tr("error:��ʼ���ű����õĽű� %1 ������").arg(initMac.sLibName);
            }
            showCompileMsg(str,0,nRow,nIndex);
            nRow++;
            result = false;
        }
    }
    foreach(GLOBAL_MARO_PROP glMac,m_pSamSysParame->m_qvcGlobalMaroProp)
    {
        foreach(Macro mac,macros)
        {
            if(mac.libName == glMac.sLibName)
            {
                if(mac.isCompiled())//�Ѿ�����ͨ��
                {
                    chkResult = 1;
                }
                else//δ����ͨ��
                {
                    chkResult = 0;
                }
                break;
            }
        }
        if(chkResult != 1)
        {
            if(chkResult == 0)//������δ����ͨ���Ľű�
            {
                str = tr("error:ȫ�ֽű�������δ����ͨ���Ľű� %1").arg(glMac.sLibName);
            }
            else
            {
                str = tr("error:ȫ�ֽű����õĽű� %1 ������").arg(glMac.sLibName);
            }
            showCompileMsg(str,0,nRow,nIndex);
            nRow++;
            result = false;
        }
    }

    foreach(SamDrawScene* cScene,pSceneSheet)
    {
        sScreenName = cScene->sNewScreenName;
        foreach(SCRIPT_PROP script,cScene->listScript)
        {
            foreach(Macro mac,macros)
            {
                if(mac.libName == script.scriptName)
                {
                    if(mac.isCompiled())//�Ѿ�����ͨ��
                    {
                        chkResult = 1;
                    }
                    else//δ����ͨ��
                    {
                        chkResult = 0;
                    }
                    break;
                }
            }
            if(chkResult != 1)
            {
                if(chkResult == 0)//������δ����ͨ���Ľű�
                {
                    str = tr("error:���� %1 ������δ����ͨ���Ľű� %2").arg(sScreenName).arg(script.scriptName);
                }
                else
                {
                    str = tr("error:���� %1 ���õĽű� %2 ������").arg(sScreenName).arg(script.scriptName);
                }
                showCompileMsg(str,0,nRow,nIndex);
                nRow++;
                result = false;
            }
        }
        QList<QGraphicsItem *>items = cScene->TopItems();
        foreach(QGraphicsItem *cItem,items)
        {
            QItemGroup *pItem = dynamic_cast<QItemGroup *>(cItem);
            if(pItem)
            {
                int chkResult = pItem->checkMacroName(msg);

                if(chkResult != 1)
                {
                    if(chkResult == 0)//������δ����ͨ���Ľű�
                    {
                        str = tr("error:%1-%2������δ����ͨ���Ľű�%3").arg(sScreenName).arg(pItem->getItemName()).arg(msg);
                    }
                    else
                    {
                        str = tr("error:%1-%2���õĽű�������").arg(sScreenName).arg(pItem->getItemName());
                    }
                    showCompileMsg(str,pItem,nRow,nIndex);
                    nRow++;
                    result = false;
                }
            }
        }
        nIndex++;
    }
    return result;
}
//�����Ϣ�������������
void MainWindow::showCompileMsg(QString str,QGraphicsItem *pItem,int row,int index)
{
    pMsgOutPut = new MsgOutPut ;//��Ϣ�������˫��Ҫ�������
    pMsgOutPut->pItem = pItem;
    pMsgOutPut->nSheetIndex = index;
    //str = tr("error:")+sScreenName+tr("-")+pItem->getItemName()+tr("���ýű�����");
    pMainList->insertRow(row);
    pMainList->setRowHeight(row,20);
    QTableWidgetItem* pTable = new QTableWidgetItem(str);
    if(pTable)
    {
        pTable->setForeground(QBrush(QColor(255,0,0)));
        pMainList->setItem(row,0,pTable);
    }
    pMainList->setCurrentCell(row,0);
    mapMsgOutPutItem.insert(row, pMsgOutPut);
}
//���ϵͳ���������Ƿ���ȷ
bool MainWindow::checkSysParam()
{
	//�����ʾ����
	QString str;
	QStringList sceneNames;//���л��������
	QStringList windowNames;//���д��ڵ�����
	bool result = true;
	foreach(SamDrawScene* cScene,pSceneSheet)
	{
            if (cScene->nIsSceneOrWindow == 0)
            {
                sceneNames << cScene->sNewScreenName;
            }
            if (cScene->nIsSceneOrWindow == 1)
            {
                windowNames << cScene->sNewScreenName;
            }
	}
	if (m_pSamSysParame->m_mixGlobalVar.m_bUseLogo 
		&& !sceneNames.contains(m_pSamSysParame->m_mixGlobalVar.m_sLogoNum))//ʹ������logo����
	{	
            str = tr("���̹�����:��ʾ���� ����logo����Ŵ���");
            emit SignalInformation(str, MSG_ERROR);
            result = false;
	}

	if (m_pSamSysParame->m_mixGlobalVar.m_bStandby && m_pSamSysParame->m_mixGlobalVar.m_bStandbyMode 
		&& !sceneNames.contains(m_pSamSysParame->m_mixGlobalVar.m_sStandbyNum))//ʹ�û������
	{
            str = tr("���̹�����:��ʾ���� ��������Ŵ���");
            emit SignalInformation(str, MSG_ERROR);
            result = false;
	}
        if(m_pSamSysParame->m_mixGlobalVar.m_sInitNum == "")
        {
            m_pSamSysParame->m_mixGlobalVar.m_sInitNum = pwnd->copyScreen_Item->child(0)->text(0).split(":").at(1);
        }
	if (!sceneNames.contains(m_pSamSysParame->m_mixGlobalVar.m_sInitNum))
	{
            str = tr("���̹�����:��ʾ���� ��ʼ����Ŵ���");
            emit SignalInformation(str, MSG_WARNING);
            //result = false;
	}

	//���ݿ���-λ���ƻ����л�
    if (m_pSamSysParame->m_mixGlobalVar.m_bBitSenceExch)
	{
            foreach(BitSenceItem item,m_pSamSysParame->m_mixGlobalVar.m_vecBitSence)
            {
                if (!sceneNames.contains(item.sCtlSceneId)
                        && !windowNames.contains(item.sCtlSceneId))
                {
                    str = tr("���̹�����:���ݿ��� λ���ƻ����л�����");
                    emit SignalInformation(str, MSG_ERROR);
                    result = false;
                }
            }
     }

	//������¼
	foreach (AlarmGroup grp,m_pSamSysParame->m_qvcAlarm)
	{
            foreach(stAlarm alarm,grp.alarms)
            {
                if (alarm.bOpenScene && !sceneNames.contains(alarm.sceneName)
                        && !windowNames.contains(alarm.sceneName))
                {
                    str = tr("���̹�����:������¼");
                    str += grp.alarmName;
                    str += tr("�����򿪻���Ŵ���");
                    emit SignalInformation(str, MSG_ERROR);
                    result = false;
                }
            }
	}
	return result;
}

//�޸Ķ๦�ܰ�ť����
void MainWindow::modifyMFbtndlg(QGraphicsItem *item)
{
    MFBtnDlg *mfdlg=new MFBtnDlg(item,this);
    if(mfdlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = mfdlg->item;
        OnDoubleClik(item,oldItem);
    }

    mfdlg->deleteLater();
    mfdlg = NULL;
}

//��Ӷ๦�ܰ�ť
void MainWindow::createMFbtndlg()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED  || isCompiled)
    {
        return;
    }

    MFBtnDlg *mfdlg=new MFBtnDlg(0,this);
    if(mfdlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = mfdlg->item;

        if(oldItem)
        {
            DrawItemToScene FunClass;
            FunClass.CopyItem(&pDrawToSceneItem,oldItem);

            SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;
        }
        else
            SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;

    }
    else
    {
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
    }

    mfdlg->deleteLater();
    mfdlg = NULL;
}

void MainWindow::on_actionCompress_triggered()
{
    Compress dlg(this);
    dlg.DisableCompress(this->is_Is);
    dlg.exec();
}
//��������
void MainWindow::on_action_upload_triggered()
{
    QStringList cmdlist;
    cmdlist.append("0");
    cmdlist.append(QString::number(is_tanslator));
    bool bReturnFlag = QProcess::startDetached(PC_AKTOOL_EXE,cmdlist);
    if(!bReturnFlag)
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("�����ļ� %1 ʧ�ܣ������°�װ�����").arg(PC_AKTOOL_EXE),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        return ;
    }
}

void MainWindow::setDefaultPlc(int nArray)
{
    QStringList sBaudrate;
    QStringList sDataBit;
    QStringList sStopBit;
    sDataBit.clear();
    sBaudrate.clear();
    sStopBit.clear();
    sBaudrate << "1200" << "2400" << "4800" << "9600" << "19200" << "34800" << "57600" << "115200";//������

    sDataBit << "7" << "8";//����λ

    sStopBit << "1" << "2";//ֹͣλ


    if(nArray >2 || nArray < 0 || nArray >= m_pSamSysParame->m_qvcConnect.size())
    {
        return;
    }

    if(m_pSamSysParame->m_qvcConnect[nArray].vProtocols.size() > 0)
    {
        stConnect con = m_pSamSysParame->m_qvcConnect[nArray];
        //int index = sBaudrate.indexOf(QString::number(con.vProtocols.at(0).mPlc.mPort.BAUD_RATE));
        //if(index >= 0)
        {
            m_pSamSysParame->m_qvcConnect[nArray].nBaudRate = con.vProtocols.at(0).mPlc.mPort.BAUD_RATE ;
        }

        int index = sDataBit.indexOf(QString::number(con.vProtocols.at(0).mPlc.mPort.DATA_BIT));
        if(index >= 0)
        {
            m_pSamSysParame->m_qvcConnect[nArray].nDataBits = index ;
        }

        index = con.vProtocols.at(0).mPlc.mPort.PARITY_TYPE - 1;
        if(index >= 0 && index <= 2)
            m_pSamSysParame->m_qvcConnect[nArray].nCheckType = index;

        index = sStopBit.indexOf(QString::number(con.vProtocols.at(0).mPlc.mPort.STOP_BIT));
        if(index >= 0)
        {
            m_pSamSysParame->m_qvcConnect[nArray].nStopBit = index ;
        }
    }
}

void MainWindow::setActiveScreenIndex(QGraphicsScene *pScene)
{
    SamDrawScene *pDrawScene = dynamic_cast<SamDrawScene *>(pScene);
    if(pDrawScene)
    {
        QString sName = pDrawScene->sNewScreenName;
        for(int i = 0; i < pSceneSheet.size(); i++)
        {
            if(sName == pSceneSheet[i]->sNewScreenName)
            {
                nActiveSheetIndex = i;
                break;
            }
        }
        for(int i=0;i<screen->childCount();i++)
        {
            QString item_name=screen->child(i)->text(0).split(":").at(1);
            if(item_name == sName)
            {
                screen->child(i)->setSelected(true);
                break;
            }
        }
        pDrawScene->selItemsChanged();
    }
}

//�鿴HMI���кŵ���Ϣ
void MainWindow::on_action_HMI_triggered()
{
    InfoDlg dlg;
    dlg.exec();
}
//index= 0 ����,index = 1 Ӣ��
void MainWindow::languageChangeForRecipe(int nIndex)
{
    qDebug() << "languageChangeForRecipe "<<is_Is;
    if(is_Is)
    {
        return;
    }
    if(0 == nIndex)
    {
        for(int i = 0; i < m_pSamSysParame->m_qvcRecipe.size(); i++)
        {
            if(m_pSamSysParame->m_qvcRecipe[i].formula.size() >0
               && m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.size() > 0)
            {
                for(int j = 0; j < m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.size(); j++)
                {
                    qDebug()<<"sdatatype =11===="<<tr("16-Bit Signed Int");
                    if(tr("16-Bit Signed Int") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("16λ����");
                    }
                    else if(tr("16-Bit Unsigned Int") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("16λ������");
                    }
                    else if(tr("32-Bit Signed Int") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("32λ����");
                    }
                    else if(tr("32-Bit Unsigned Int") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("32λ������");
                    }
                    else if(tr("32-Bit Float") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("32λ������");
                    }
                    else if(tr("16-Bit BCD") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("16λBCD��");
                    }
                    else if(tr("32-Bit BCD") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("32λBCD��");
                    }
                    else if(tr("Bit") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("λ");
                    }
                }
            }
        }
    }
    else if(1 == nIndex)
    {
        for(int i = 0; i < m_pSamSysParame->m_qvcRecipe.size(); i++)
        {
            if(m_pSamSysParame->m_qvcRecipe[i].formula.size() >0
               && m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.size() > 0)
            {
                for(int j = 0; j < m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.size(); j++)
                {
                    qDebug()<<"sdatatype ====="<<tr("16λ����");
                    if(tr("16λ����") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = "16-Bit Signed Int";
                    }
                    else if(tr("16λ������") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = "16-Bit Unsigned Int";
                    }
                    else if(tr("32λ����") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = "32-Bit Signed Int";
                    }
                    else if(tr("32λ������") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = "32-Bit Unsigned Int";
                    }
                    else if(tr("32λ������") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = "32-Bit Float";
                    }
                    else if(tr("16λBCD��") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = "16-Bit BCD";
                    }
                    else if(tr("32λBCD��") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = "32-Bit BCD";
                    }
                    else if(tr("λ") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = "Bit";
                    }
                }
            }
        }
    }
}

QString MainWindow::findFactoryFullName(QString str)
{
    if(0 == is_tanslator)
    {
        QMap<QString,QString>::const_iterator itor = m_factoryMap.find(str);
        if(itor != m_factoryMap.end())
        {
            return itor.value();
        }
    }
    return str;  //û�ҵ�����
}
//ѹ�����̵�ʱ�����»�ȡ�ؼ�ͼƬ·��
void MainWindow::loadPicPath(QItemGroup *pItemGroup,QMap<QString, QString> &mPath)
{
    if(NULL == pItemGroup)
    {
        return;
    }

    QString path;
    int nKey = pItemGroup->data(GROUP_TYPE_KEY).toInt();
    if(USER_DEFINE_GROUP == nKey)//���ͼ��
    {
        foreach(QGraphicsItem *pItem, pItemGroup->childItems())
        {
            if(SAM_DRAW_OBJECT_GROUP == pItem->type())
            {
                QItemGroup *pGroup = dynamic_cast<QItemGroup *> (pItem);
                loadPicPath(pGroup,mPath);
            }
        }
    }
    else
    {
        int type =  pItemGroup->GroupType();
        switch(type)
        {
        case SAM_DRAW_GROUP_IMAGE:
            {
                ImageItem *pPicItem = dynamic_cast<ImageItem *> (pItemGroup);
                if(pPicItem)
                {
                    for(int i = 0; i < pPicItem->m_PicInfo.size(); i++)
                    {
                        if(PIC == pPicItem->m_PicInfo[i].bIspic)
                        {
                            path = pPicItem->m_PicInfo[i].path;
                            if(mPath.contains(path))
                            {
                                path = mPath.value(path);
                                pPicItem->m_PicInfo[i].path = path;
                            }
                        }
                    }
                }
            }
            break;
        case SAM_DRAW_GROUP_SWITCH:
            {
                SwitchItem *pPicItem = dynamic_cast<SwitchItem *> (pItemGroup);
                if(pPicItem)
                {
                    for(int i = 0; i < pPicItem->statusPic.size(); i++)
                    {
                        if(PIC == pPicItem->statusPic[i].bLib
                           || USERDEFINE == pPicItem->statusPic[i].bLib)
                        {
                            path = pPicItem->statusPic[i].path;
                            if(mPath.contains(path))
                            {
                                path = mPath.value(path);
                                pPicItem->statusPic[i].path = path;
                            }
                        }
                    }
                }
            }
            break;
        case SAM_DRAW_GROUP_MFBTN:
            {
                MfBtnItem *pPicItem = dynamic_cast<MfBtnItem *> (pItemGroup);
                if(pPicItem)
                {
                    /*if(PIC == pPicItem->picPro.bLib
                       || USERDEFINE == pPicItem->picPro.bLib)
                    {
                        path = pPicItem->picPro.path;
                        if(mPath.contains(path))
                        {
                            path = mPath.value(path);
                            pPicItem->picPro.path = path;
                        }
                    }*/
                    for(int i = 0; i < pPicItem->statusPic.size(); i++)
                    {
                        if(PIC == pPicItem->statusPic[i].bLib
                           || USERDEFINE == pPicItem->statusPic[i].bLib)
                        {
                            path = pPicItem->statusPic[i].path;
                            if(mPath.contains(path))
                            {
                                path = mPath.value(path);
                                pPicItem->statusPic[i].path = path;
                            }
                        }
                    }
                }
            }
            break;
        case SAM_DRAW_GROUP_KEY:
            {
                KeyBoardItem *pKeyItem = dynamic_cast<KeyBoardItem *> (pItemGroup);
                if(pKeyItem)
                {
                    if(pKeyItem->m_key.bisPic && "" != pKeyItem->m_key.sPath)
                    {
                        path = pKeyItem->m_key.sPath;
                        if(mPath.contains(path))
                        {
                            path = mPath.value(path);
                            pKeyItem->m_key.sPath = path;
                        }
                    }
                }
            }
            break;
        case SAM_DRAW_GROUP_ANIMATION:
            {
                AnimationItem *pPicItem = dynamic_cast<AnimationItem *> (pItemGroup);
                if(pPicItem)
                {
                    for(int i = 0; i < pPicItem->m_AnimatInfo.PicInfo.size(); i++)
                    {
                        if(PIC == pPicItem->m_AnimatInfo.PicInfo[i].bIspic
                           || USERDEFINE == pPicItem->m_AnimatInfo.PicInfo[i].bIspic)
                        {
                            path = pPicItem->m_AnimatInfo.PicInfo[i].sPath;
                            if(mPath.contains(path))
                            {
                                path = mPath.value(path);
                                pPicItem->m_AnimatInfo.PicInfo[i].sPath = path;
                            }
                        }
                    }
                }
            }
            break;
        case SAM_DRAW_GROUP_STATICPIC:
            {
                QStaticPictureItem *pPicItem = dynamic_cast<QStaticPictureItem *> (pItemGroup);
                if(pPicItem)
                {
                    if("" != pPicItem->m_PicInfo.sPicPath)
                    {
                        path = pPicItem->m_PicInfo.sPicPath;
                        if(mPath.contains(path))
                        {
                            path = mPath.value(path);
                            pPicItem->m_PicInfo.sPicPath = path;
                        }
                    }
                }
            }
            break;
        case SAM_DRAW_GROUP_VALUE:
        case SAM_DRAW_GROUP_ASCII:
        case SAM_DRAW_GROUP_TIME:
            {
                DataDisplayItem *pPicItem = dynamic_cast<DataDisplayItem *> (pItemGroup);
                if(pPicItem)
                {
                    if(DATAINPUTSHOW == pPicItem->m_etabPag)
                    {
                        if("" != pPicItem->m_data.nShapId)
                        {
                            if(PIC == pPicItem->m_eIspic
                               || USERDEFINE == pPicItem->m_eIspic)
                            {
                                if(PIC == pPicItem->m_eIspic
                                   || USERDEFINE == pPicItem->m_eIspic)
                                {
                                    path = pPicItem->m_data.nShapId;
                                    if(mPath.contains(path))
                                    {
                                        path = mPath.value(path);
                                        pPicItem->m_data.nShapId = path;
                                    }
                                }
                            }
                        }
                    }
                    else if(ASCIIINPUTSHOW == pPicItem->m_etabPag)
                    {
                        if("" != pPicItem->m_ascii.nShapId)
                        {
                            if(PIC == pPicItem->m_eIspic
                               || USERDEFINE == pPicItem->m_eIspic)
                            {
                                if(PIC == pPicItem->m_eIspic
                                   || USERDEFINE == pPicItem->m_eIspic)
                                {
                                    path = pPicItem->m_ascii.nShapId;
                                    if(mPath.contains(path))
                                    {
                                        path = mPath.value(path);
                                        pPicItem->m_ascii.nShapId = path;
                                    }
                                }
                            }
                        }
                    }
                    else if(DATETIMEINPUT == pPicItem->m_etabPag)
                    {
                        if("" != pPicItem->m_time.nShapId)
                        {
                            if(PIC == pPicItem->m_eIspic
                               || USERDEFINE == pPicItem->m_eIspic)
                            {
                                path = pPicItem->m_time.nShapId;
                                if(mPath.contains(path))
                                {
                                    path = mPath.value(path);
                                    pPicItem->m_time.nShapId = path;
                                }
                            }
                        }
                    }
                }
            }
            break;
        case SAM_DRAW_GROUP_COMBOBOX:
            {
                AkComboItem *pPicItem = dynamic_cast<AkComboItem *>(pItemGroup);
                if(pPicItem)
                {
                    if("" != pPicItem->dataCombo.m_strPath)
                    {
                        path = pPicItem->dataCombo.m_strPath;
                        if(mPath.contains(path))
                        {
                            path = mPath.value(path);
                            pPicItem->dataCombo.m_strPath = path;
                        }
                    }
                }
            }
            break;
        case SAM_DRAW_GROUP_DROPDOWN:
            {
                QDropdownAttr *pPicItem = dynamic_cast<QDropdownAttr *> (pItemGroup);
                if(pPicItem)
                {
                    for(int i = 0; i < pPicItem->m_vecSwitchItem.size(); i++)
                    {
                        if(PIC == pPicItem->m_vecSwitchItem[i].bLib
                           || USERDEFINE == pPicItem->m_vecSwitchItem[i].bLib)
                        {
                            path = pPicItem->m_vecSwitchItem[i].sPath;
                            if(mPath.contains(path))
                            {
                                path = mPath.value(path);
                                pPicItem->m_vecSwitchItem[i].sPath = path;
                            }
                        }
                    }
                }
            }
            break;
        default:
            break;
        }
    }
}

//ѹ�����̵�ʱ�򱣴�ؼ�ͼƬ·��
void MainWindow::savePicPath(QItemGroup *pItemGroup,QMap<QString, QString> &mPath)
{
    if(NULL == pItemGroup)
    {
        return;
    }
    QString path;
    QString newPath;

    if(pItemGroup)
    {
        int nKey = pItemGroup->data(GROUP_TYPE_KEY).toInt();
        if(USER_DEFINE_GROUP == nKey)//���ͼ��
        {
            foreach(QGraphicsItem *pItem, pItemGroup->childItems())
            {
                if(SAM_DRAW_OBJECT_GROUP == pItem->type())
                {
                    QItemGroup *pGroup = dynamic_cast<QItemGroup *> (pItem);
                    savePicPath(pGroup,mPath);
                }
            }
        }
        else
        {
            int type =  pItemGroup->GroupType();
            switch(type)
            {
            case SAM_DRAW_GROUP_IMAGE:
                {
                    ImageItem *pPicItem = dynamic_cast<ImageItem *> (pItemGroup);
                    if(pPicItem)
                    {
                        for(int i = 0; i < pPicItem->m_PicInfo.size(); i++)
                        {
                            if(PIC == pPicItem->m_PicInfo[i].bIspic)
                            {
                                QSizeF picSize = pPicItem->sceneBoundingRect().size();
                                path = pPicItem->m_PicInfo[i].path;
                                newPath = pwnd->SavePicPath(path,picSize);
                                if("" != newPath)
                                {
                                    QString str = newPath;
                                    str = newPath.section("/",-1);
                                    newPath = PICTURE_PATH + newpro->newprowizard_name;
                                    newPath = newPath + "/";
                                    newPath = newPath + str;
                                }
                                else
                                {
                                    return;
                                }
                                pPicItem->m_PicInfo[i].path = newPath;
                                if(!mPath.contains(newPath))
                                {
                                    mPath.insert(newPath,path);
                                }
                            }
                        }
                    }
                }
                break;
            case SAM_DRAW_GROUP_SWITCH:
                {
                    SwitchItem *pPicItem = dynamic_cast<SwitchItem *> (pItemGroup);
                    if(pPicItem)
                    {
                        for(int i = 0; i < pPicItem->statusPic.size(); i++)
                        {
                            if(PIC == pPicItem->statusPic[i].bLib
                               || USERDEFINE == pPicItem->statusPic[i].bLib)
                            {
                                QSizeF picSize = pPicItem->sceneBoundingRect().size();
                                path = pPicItem->statusPic[i].path;
                                newPath = pwnd->SavePicPath(path,picSize);
                                if("" != newPath)
                                {
                                    QString str = newPath;
                                    str = newPath.section("/",-1);
                                    newPath = PICTURE_PATH + newpro->newprowizard_name;
                                    newPath = newPath + "/";
                                    newPath = newPath + str;
                                }
                                else
                                {
                                    return;
                                }
                                pPicItem->statusPic[i].path = newPath;
                                if(!mPath.contains(newPath))
                                {
                                    mPath.insert(newPath,path);
                                }
                            }
                        }
                    }
                }
                break;
            case SAM_DRAW_GROUP_MFBTN:
                {
                    MfBtnItem *pPicItem = dynamic_cast<MfBtnItem *> (pItemGroup);
                    if(pPicItem)
                    {
                        /*if(PIC == pPicItem->picPro.bLib
                           || USERDEFINE == pPicItem->picPro.bLib)
                        {
                            QSizeF picSize = pPicItem->sceneBoundingRect().size();
                            path = pPicItem->picPro.path;
                            newPath = pwnd->SavePicPath(path,picSize);
                            if("" != newPath)
                            {
                                QString str = newPath;
                                str = newPath.section("/",-1);
                                newPath = PICTURE_PATH + newpro->newprowizard_name;
                                newPath = newPath + "/";
                                newPath = newPath + str;
                            }
                            else
                            {
                                return;
                            }
                            pPicItem->picPro.path = newPath;
                            if(!mPath.contains(newPath))
                            {
                                mPath.insert(newPath,path);
                            }
                        }*/
                        for(int i = 0; i < pPicItem->statusPic.size(); i++)
                        {
                            if(PIC == pPicItem->statusPic[i].bLib
                               || USERDEFINE == pPicItem->statusPic[i].bLib)
                            {
                                QSizeF picSize = pPicItem->sceneBoundingRect().size();
                                path = pPicItem->statusPic[i].path;
                                newPath = pwnd->SavePicPath(path,picSize);
                                if("" != newPath)
                                {
                                    QString str = newPath;
                                    str = newPath.section("/",-1);
                                    newPath = PICTURE_PATH + newpro->newprowizard_name;
                                    newPath = newPath + "/";
                                    newPath = newPath + str;
                                }
                                else
                                {
                                    return;
                                }
                                pPicItem->statusPic[i].path = newPath;
                                if(!mPath.contains(newPath))
                                {
                                    mPath.insert(newPath,path);
                                }
                            }
                        }
                    }
                }
                break;
            case SAM_DRAW_GROUP_KEY:
                {
                    KeyBoardItem *pKeyItem = dynamic_cast<KeyBoardItem *> (pItemGroup);
                    if(pKeyItem)
                    {
                        if(pKeyItem->m_key.bisPic && "" != pKeyItem->m_key.sPath)
                        {
                            if(pKeyItem->textItem)
                            {
                                QSizeF picSize = pKeyItem->textItem->sceneBoundingRect().size();
                                path = pKeyItem->m_key.sPath;
                                newPath = pwnd->SavePicPath(path,picSize);
                                if("" != newPath)
                                {
                                    QString str = newPath;
                                    str = newPath.section("/",-1);
                                    newPath = PICTURE_PATH + newpro->newprowizard_name;
                                    newPath = newPath + "/";
                                    newPath = newPath + str;
                                }
                                else
                                {
                                    return;
                                }
                                pKeyItem->m_key.sPath = newPath;
                                if(!mPath.contains(newPath))
                                {
                                    mPath.insert(newPath,path);
                                }
                            }
                        }
                    }
                }
                break;
            case SAM_DRAW_GROUP_ANIMATION:
                {
                    AnimationItem *pPicItem = dynamic_cast<AnimationItem *> (pItemGroup);
                    if(pPicItem)
                    {
                        for(int i = 0; i < pPicItem->m_AnimatInfo.PicInfo.size(); i++)
                        {
                            if(PIC == pPicItem->m_AnimatInfo.PicInfo[i].bIspic
                               || USERDEFINE == pPicItem->m_AnimatInfo.PicInfo[i].bIspic)
                            {
                                QSizeF picSize = pPicItem->sceneBoundingRect().size();
                                path = pPicItem->m_AnimatInfo.PicInfo[i].sPath;
                                newPath = pwnd->SavePicPath(path,picSize);
                                if("" != newPath)
                                {
                                    QString str = newPath;
                                    str = newPath.section("/",-1);
                                    newPath = PICTURE_PATH + newpro->newprowizard_name;
                                    newPath = newPath + "/";
                                    newPath = newPath + str;
                                }
                                else
                                {
                                    return;
                                }
                                pPicItem->m_AnimatInfo.PicInfo[i].sPath = newPath;
                                if(!mPath.contains(newPath))
                                {
                                    mPath.insert(newPath,path);
                                }
                            }
                        }
                    }
                }
                break;
            case SAM_DRAW_GROUP_STATICPIC:
                {
                    QStaticPictureItem *pPicItem = dynamic_cast<QStaticPictureItem *> (pItemGroup);
                    if(pPicItem)
                    {
                        if("" != pPicItem->m_PicInfo.sPicPath)
                        {
                            QSizeF picSize = pPicItem->sceneBoundingRect().size();
                            path = pPicItem->m_PicInfo.sPicPath;
                            newPath = pwnd->SavePicPath(path,picSize);
                            if("" != newPath)
                            {
                                QString str = newPath;
                                str = newPath.section("/",-1);
                                newPath = PICTURE_PATH + newpro->newprowizard_name;
                                newPath = newPath + "/";
                                newPath = newPath + str;
                            }
                            else
                            {
                                return;
                            }
                            pPicItem->m_PicInfo.sPicPath = newPath;
                            if(!mPath.contains(newPath))
                            {
                                mPath.insert(newPath,path);
                            }
                        }
                    }
                }
                break;
            case SAM_DRAW_GROUP_VALUE:
            case SAM_DRAW_GROUP_ASCII:
            case SAM_DRAW_GROUP_TIME:
                {
                    DataDisplayItem *pPicItem = dynamic_cast<DataDisplayItem *> (pItemGroup);
                    if(pPicItem)
                    {
                        if(DATAINPUTSHOW == pPicItem->m_etabPag)
                        {
                            if("" != pPicItem->m_data.nShapId)
                            {
                                if(PIC == pPicItem->m_eIspic
                                   || USERDEFINE == pPicItem->m_eIspic)
                                {
                                    QSizeF picSize = pPicItem->sceneBoundingRect().size();
                                    path = pPicItem->m_data.nShapId;
                                    newPath = pwnd->SavePicPath(path,picSize);
                                    if("" != newPath)
                                    {
                                        QString str = newPath;
                                        str = newPath.section("/",-1);
                                        newPath = PICTURE_PATH + newpro->newprowizard_name;
                                        newPath = newPath + "/";
                                        newPath = newPath + str;
                                    }
                                    else
                                    {
                                        return;
                                    }
                                    pPicItem->m_data.nShapId = newPath;
                                    if(!mPath.contains(newPath))
                                    {
                                        mPath.insert(newPath,path);
                                    }
                                }
                            }
                        }
                        else if(ASCIIINPUTSHOW == pPicItem->m_etabPag)
                        {
                            if("" != pPicItem->m_ascii.nShapId)
                            {
                                if(PIC == pPicItem->m_eIspic
                                   || USERDEFINE == pPicItem->m_eIspic)
                                {
                                    QSizeF picSize = pPicItem->sceneBoundingRect().size();
                                    path = pPicItem->m_ascii.nShapId;
                                    newPath = pwnd->SavePicPath(path,picSize);
                                    if("" != newPath)
                                    {
                                        QString str = newPath;
                                        str = newPath.section("/",-1);
                                        newPath = PICTURE_PATH + newpro->newprowizard_name;
                                        newPath = newPath + "/";
                                        newPath = newPath + str;
                                    }
                                    else
                                    {
                                        return;
                                    }
                                    pPicItem->m_ascii.nShapId = newPath;
                                    if(!mPath.contains(newPath))
                                    {
                                        mPath.insert(newPath,path);
                                    }
                                }
                            }
                        }
                        else if(DATETIMEINPUT == pPicItem->m_etabPag)
                        {
                            if("" != pPicItem->m_time.nShapId)
                            {
                                if(PIC == pPicItem->m_eIspic
                                   || USERDEFINE == pPicItem->m_eIspic)
                                {
                                    QSizeF picSize = pPicItem->sceneBoundingRect().size();
                                    path = pPicItem->m_time.nShapId;
                                    newPath = pwnd->SavePicPath(path,picSize);
                                    if("" != newPath)
                                    {
                                        QString str = newPath;
                                        str = newPath.section("/",-1);
                                        newPath = PICTURE_PATH + newpro->newprowizard_name;
                                        newPath = newPath + "/";
                                        newPath = newPath + str;
                                    }
                                    else
                                    {
                                        return;
                                    }
                                    pPicItem->m_time.nShapId = newPath;
                                    if(!mPath.contains(newPath))
                                    {
                                        mPath.insert(newPath,path);
                                    }
                                }
                            }
                        }
                    }
                }
                break;
            case SAM_DRAW_GROUP_DROPDOWN:
                {
                    QDropdownAttr *pdropItem = dynamic_cast<QDropdownAttr *> (pItemGroup);
                    if(pdropItem)
                    {
                        for(int i = 0; i < pdropItem->m_vecSwitchItem.size(); i++)
                        {
                            if(PIC == pdropItem->m_vecSwitchItem[i].bLib
                               || USERDEFINE == pdropItem->m_vecSwitchItem[i].bLib)
                            {
                                QSizeF picSize = pdropItem->sceneBoundingRect().size();
                                path = pdropItem->m_vecSwitchItem[i].sPath;
                                newPath = pwnd->SavePicPath(path,picSize);
                                if("" != newPath)
                                {
                                    QString str = newPath;
                                    str = newPath.section("/",-1);
                                    newPath = PICTURE_PATH + newpro->newprowizard_name;
                                    newPath = newPath + "/";
                                    newPath = newPath + str;
                                }
                                else
                                {
                                    return;
                                }
                                pdropItem->m_vecSwitchItem[i].sPath = newPath;
                                if(!mPath.contains(newPath))
                                {
                                    mPath.insert(newPath,path);
                                }
                            }
                        }
                    }
                }
                break;

            case SAM_DRAW_GROUP_COMBOBOX:
                {
                    AkComboItem *pPicItem = dynamic_cast<AkComboItem *> (pItemGroup);
                    if(pPicItem)
                    {
                        if("" != pPicItem->dataCombo.m_strPath)
                        {
                            QSizeF picSize = pPicItem->sceneBoundingRect().size();
                            path = pPicItem->dataCombo.m_strPath;
                            newPath = pwnd->SavePicPath(path,picSize);
                            if("" != newPath)
                            {
                                QString str = newPath;
                                str = newPath.section("/",-1);
                                newPath = PICTURE_PATH + newpro->newprowizard_name;
                                newPath = newPath + "/";
                                newPath = newPath + str;
                            }
                            else
                            {
                                return;
                            }
                            pPicItem->dataCombo.m_strPath = newPath;
                            if(!mPath.contains(newPath))
                            {
                                mPath.insert(newPath,path);
                            }
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
    }
}


QVector <VarPro> MainWindow::getGlobalVars()
{
    return g_Vars;
}

bool MainWindow::appendGlobalVar(VarPro variant)
{
    foreach(VarPro var,g_Vars)
    {
        if(var.varName == variant.varName)
        {
            return false;
        }
    }
    g_Vars.append(variant);
    return true;
}

void MainWindow::setGlobalVar(QVector <VarPro> variants)
{
    g_Vars = variants;
}

void MainWindow::updateChScreen()
{
    int iActiveSheetTemp = nActiveSheetIndex;
    m_ChScreenMap.clear();
    pChScreen->clear();
    QTreeWidgetItemIterator itor(tree0);
    while(*itor)
    {
         QString str = (*itor)->text(0);
         if(!(str == tr("����") || str == tr("����")
             || str == tr("�Զ������") || str == tr("����&����")))
         {
             str = str.right(str.length()-str.lastIndexOf(":")-1);
             for(int i = 0; i < pSceneSheet.size(); i++)
             {
                 if(str == pSceneSheet[i]->sNewScreenName)
                 {
                     QMap<QString, int>::const_iterator it = m_ChScreenMap.find(pSceneSheet[i]->sNewScreenName);
                     if(it == m_ChScreenMap.end() && it.value() != i)
                     {
                         m_ChScreenMap.insert(pSceneSheet[i]->sNewScreenName, i);
                         pChScreen->addItem(pSceneSheet[i]->sNewScreenName);
                     }
                 }
             }
         }
         ++itor;
    }
    nActiveSheetIndex = iActiveSheetTemp;
    int iIndex = pChScreen->findText(pSceneSheet[nActiveSheetIndex]->sNewScreenName);
    pChScreen->setCurrentIndex(iIndex);
}
//����PLC������������PLC����
bool MainWindow::compilePlcPrj()
{
    QProcess proc(this);
    QStringList args ;
    QString argv;
    QDir outDir("temp\\soar");
    if(!outDir.exists())
    {
        outDir.mkpath(outDir.absolutePath());
    }
    deleteDirectory(QFileInfo("temp\\soar"));

    argv = QDir::currentPath();
    argv += QString("\\temp\\"+newpro->newprowizard_name+".bin");
    argv.replace("/","\\");
    args << QString::number(is_tanslator);
    args << argv;
    argv = QDir::currentPath()+"\\temp\\soar";
    argv.replace("/","\\");
    args << argv;
    bool bReturnFlag = proc.execute(PC_PLC_EXE,args);

    bReturnFlag = QFile::exists("temp\\soar\\codefile.dat");
    bReturnFlag == bReturnFlag && QFile::exists("temp\\soar\\commfile.dat");
    bReturnFlag == bReturnFlag && QFile::exists("temp\\soar\\elemInitfile.dat");
    bReturnFlag == bReturnFlag && QFile::exists("temp\\soar\\modbusfile.dat");
    bReturnFlag == bReturnFlag && QFile::exists("temp\\soar\\settingfile.dat");

    return bReturnFlag;

}
//����PLC����
void MainWindow::loadPlcPrj(QString filename,QDataStream &stream)
{
    //QString filename = newpro->newprowizard_name+".bin";
    filename = "temp\\"+filename+".bin";
    QFile plcFile(filename);
    QByteArray plcStream;
    if(plcFile.open(QIODevice::WriteOnly))
    {
        stream >> plcStream;
        plcFile.write(plcStream);
        plcFile.close();
    }
}
//����PLC����
void MainWindow::savePlcPrj(QDataStream &stream)
{
    QString filename = newpro->newprowizard_name+".bin";
    filename = "temp\\"+filename;
    QFile plcFile(filename);
    if(plcFile.open(QIODevice::ReadOnly))
    {
        int size = plcFile.size();
        if(size > 0)
        {
            stream << plcFile.readAll();
        }
        plcFile.close();
    }
}

void MainWindow::SignalCompileEnd()
{
    if(pSimDlg)
    {
        pSimDlg->setLabelText(tr("���ڴ�����̬����"), 66);
    }
    if(threadDownload && !threadDownload->isRunning())
    {
        QString vdisk = QDir::currentPath();
        vdisk += vShareDir;
        vdisk.replace("\\","/");
        threadDownload->setprarm(2,vdisk,true);
        threadDownload->start();
    }
}

void MainWindow::downFinished()
{
    QFile::remove("gEKip");

    QString sourceDir = QDir::currentPath() + "/compile";
    QString toDir = QDir::currentPath() + "/vdisk";
    bool coverFileIfExist = true;
    bool bSuc = copyDirectoryFiles(sourceDir, toDir, coverFileIfExist);

    if(bSuc)//wxy�����ļ��ɹ�
    {
        if(pSimDlg)
        {
            pSimDlg->setLabelText(tr("������ɣ�����ģ����"), 100);
        }

        QString vdisk = QDir::currentPath();
        vdisk += vShareIni;
        vdisk.replace("\\","/");
        QSettings *readIni = new QSettings(vdisk, QSettings::IniFormat, 0);
        readIni->setValue("StartVM", "true");
        //д��APK�汾�ţ�ģ�������ݴ˰汾�ž����Ƿ����
        readIni->setValue("updateVer", QVariant(APK_VERSION_CODE));
        delete readIni;
        setWindowFirst();
        if(pSimDlg)
        {
            pSimDlg->accept();
            pSimDlg = NULL;
        }
    }
    else
    {
        if(pSimDlg)
        {
            pSimDlg->setLabelText(tr("����ʧ��"), 100);
            pSimDlg->accept();
            pSimDlg = NULL;
        }
    }
}

void MainWindow::setWindowFirst()
{
    wchar_t strTitle[20];
    HWND hwnd=NULL;
    HWND AfterHwnd = NULL;
    while(true)
    {
        hwnd=::FindWindowEx(NULL,AfterHwnd,NULL,NULL);
        if(!hwnd)
        {
            break;
        }
        else
        {
            if(::GetWindowText(hwnd,strTitle,20))
            {
                qDebug() << strTitle;
                QString str;
                str = str.fromWCharArray(strTitle);
                if(strstr(str.toLatin1(),"AKEmu")!=0)
                {
                    qDebug() << "before set SetWindowPos";
                    ::SetForegroundWindow(hwnd);
                    ::ShowWindow(hwnd, SW_RESTORE);
                    //::SetWindowPos(hwnd,HWND_TOP ,0,0,600,400,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
                    break;
                }
            }
        }
        AfterHwnd = hwnd;
    }
}


//�����ļ��У�
bool MainWindow::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    /**< ���Ŀ��Ŀ¼�����ڣ�����д��� */
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    /**< ��ΪĿ¼ʱ���ݹ�Ľ���copy */
            if(!copyDirectoryFiles(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()),
                coverFileIfExist))
                return false;
        }
        else{            /**< �������ǲ���ʱ�������ļ�����ɾ������ */
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            /// �����ļ�copy
            if(!QFile::copy(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()))){
                    return false;
            }
        }
    }
    return true;
}

QByteArray MainWindow::getFileMd5(QString filePath)
{
     QFile localFile(filePath);

     if (!localFile.open(QFile::ReadOnly))
     {
         qDebug() <<filePath <<"file open error.";
         return 0;
     }
     QCryptographicHash ch(QCryptographicHash::Md5);

     quint64 totalBytes = 0;
     quint64 bytesWritten = 0;
     quint64 bytesToWrite = 0;
     quint64 loadSize = 1024 * 4;
     QByteArray buf;

     totalBytes = localFile.size();
     bytesToWrite = totalBytes;
     while (1)
     {
         if(bytesToWrite > 0)
         {
             buf = localFile.read(qMin(bytesToWrite, loadSize));
             ch.addData(buf);
             bytesWritten += buf.length();
             bytesToWrite -= buf.length();
             buf.resize(0);
         }
         else
         {
             break;
         }

         if(bytesWritten == totalBytes)
         {
             break;
         }
     }
     localFile.close();
     QByteArray md5 = ch.result();
     return md5;
}

bool MainWindow::checkMD5(QByteArray md5, QString filePath)
{
    if(md5.isEmpty())
    {
        return false;
    }
    QByteArray nmd;
    nmd = getFileMd5(filePath);
    if(nmd.isEmpty())
    {
        return false;
    }
    return (md5 == nmd);
}

//�����ݿ����浽vector���������ִ��
void MainWindow::inSertDbQuery(QString tableName,QMap<QString,QVariant> mapDbquery)
{
    bool bExist = false;
    for(int i=0; i<vAllDbQuery.size();i++)
    {
        if(vAllDbQuery[i].tableName == tableName)
        {
            vAllDbQuery[i].vDbQuery.append(mapDbquery);
            bExist = true;
            break;
        }
    }
    if(!bExist)//�����ڸı���������
    {
        DBQuery dbquery;
        dbquery.tableName = tableName;
        dbquery.vDbQuery.append(mapDbquery);
        vAllDbQuery.append(dbquery);
    }
}
int MainWindow::getNewId()
{
    int nMax = -1;
    m_Ids.clear();
    foreach(SamDrawScene *pscene,pSceneSheet)
    {
        foreach(QGraphicsItem* pItem,pscene->TopItems())
        {
            SamDrawItemBase *baseitem = dynamic_cast<SamDrawItemBase *> (pItem);
            if(baseitem)
            {
                int id = baseitem->id();
                m_Ids << id;
                nMax = nMax > id? nMax:id;
            }
        }
    }

    int newId = nMax +1;
    //m_Ids << newId;
    return newId;
}

bool MainWindow::insertId(int nId)
{
    bool result = false;

    m_Ids.clear();
    foreach(SamDrawScene *pscene,pSceneSheet)
    {
        foreach(QGraphicsItem* pItem,pscene->TopItems())
        {
            SamDrawItemBase *baseitem = dynamic_cast<SamDrawItemBase *> (pItem);
            if(baseitem)
            {
                int id = baseitem->id();
                m_Ids << id;
            }
        }
    }

    if(!m_Ids.contains(nId))
    {
        m_Ids << nId;
        result = true;
    }
    else
    {
        if(nId == -1)
        {
            result = true;
        }
    }
    return result;
}
