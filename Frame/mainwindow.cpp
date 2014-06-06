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

#define  TOOLBAR_BASIC 1  // 基本图形
#define  TOOLBAR_CONTROL 2 //控件
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    mPicMd5.clear();
    ToolBarTabWidget = NULL;
    m_ChScreenMap.clear();
    g_Vars.clear();
    sLibraryPath.clear();
    picturePath="/home";
    sFilePath = "c:\\";//压缩解压文件路径
    //ui->setupUi(this);
    vBaseLibraryScene.clear();  //存画面的容器
    m_pSamSysParame = NULL;
    //    m_pSamSysParame = new QSamSysParame();
    qLanguagecmb = NULL;
    bToolBarCMBInit = false;
    is_Click_OpenrecentFile=false;
    is_OpenrecentFile=false;
    is_click_open=false;
    //bDrawAnimateFlag = false;  //画动画的标志
    undoStack = new QUndoStack(this);/*定义撤销堆栈*/
    nLoadShapeType = 0; //加载外形标示 0--一般外形，1--仪表外形
    nPcopyItenType = 0; //0:普通图形。1：仪表图形 add by chengzhihua
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
    bSimulator=false;//模拟是否存在
    is_ScreenProperty_Name=false;
    is_WindowProperty_Name=false;
    newScreenDlg=new QTreeCtrlNewScreenDlg(this);//新建画面
    newWindowDlg=new QNewWindowDlg(this);//新建窗口
    newCopyScreen=new QCopyScreenDlg(this);//复制画面对话框
    newCopyWindow=new QCopyWindowDlg(this);
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);//隐藏边框和标题栏
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
    is_Is=true;//是否第一次点击打开按钮

    isHave=false;
    nControlType=SAM_DRAW_INVALID; //控件类型标示
    nActiveSheetIndex=0; //当前画面序号，从0开始
    //setWindowTitle(PRO_FULL_NAME);

    /*******************************************************************/
    pwnd=this;
    newpro = NULL;
    //XXXXX
    //languagedlg = NULL;
    //initRecipeDlg();//初始化配方
    //recipeDlg = NULL;//配方对话框;
    //treectrlDlg =new QTreeCtrlDlg;//树控件里面对话框的数据封装类

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

    //   iDataTransferCount=0;//资料传输个数初始化
    //   fileprotection=new QFileProtection;
    /*******************************************************************/
    nscreen=1;//

    nCurrentDigitalAlarmIndex=0;
    nCurrentAnalog_alarmIndex=0;

    //stackeWidget=new QStackedWidget();
    m_leftDock = new myDockWidget(this);
    //wxy只允许停留在左右两侧
    m_leftDock->setAllowedAreas(Qt::LeftDockWidgetArea|/*Qt::AllDockWidgetAreas*/Qt::RightDockWidgetArea);
    m_leftDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    m_leftDock-> setWindowTitle(tr("窗口"));
    m_leftDock->setFloating(false);
    m_leftDock->setVisible(true);

    m_toolDock = new myDockWidget(this);
    m_toolDock->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea);
    m_toolDock->setFeatures(QDockWidget::DockWidgetClosable|QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
    m_toolDock->setWindowTitle(tr("工具栏"));
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
    dockTabWidget->addTab(subWidget1, tr("系统参数"));
    dockTabWidget->addTab(subWidget2, tr("窗口画面"));
    //add by wxy去掉一些组件的tabfocus属性，而不是之前的把属性设为nofocus
    dockTabWidget->setFocusPolicy(
            Qt::FocusPolicy(dockTabWidget->focusPolicy()&(~Qt::TabFocus)));


    dock_layout1 = new QVBoxLayout(subWidget1);
    dock_layout1->addWidget(tree);
    subWidget1->setLayout(dock_layout1);
    subWidget1->setStyleSheet("background: rgb(255, 255, 255);\n"
                              "font: 9pt '宋体';\n"
                              "color: rgb(8, 45, 105);\n"
                              "selection-color: rgb(8, 45, 105);\n"
                              "selection-background-color: rgb(197, 222, 255);");

    dock_layout2 = new QVBoxLayout(subWidget2);
    dock_layout2->addWidget(tree0);
    subWidget2->setLayout(dock_layout2);
    subWidget2->setStyleSheet("background: rgb(255, 255, 255);\n"
                              "font: 9pt '宋体';\n"
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

    ToolBarTabWidget->addTab(scrollAreaBasic, tr("基本图形"));
    ToolBarTabWidget->addTab(scrollAreaCtl,   tr("控件"));
    if(is_tanslator)
    {
        ToolBarTabWidget->setTabText(0, tr("Basic Graphics"));
        ToolBarTabWidget->setTabText(1, tr("Controls"));
    }
    else
    {
        ToolBarTabWidget->setTabText(0, tr("基本图形"));
        ToolBarTabWidget->setTabText(1, tr("控   件"));
    }

    //add by wxy去掉一些组件的tabfocus属性，而不是之前的把属性设为nofocus
    ToolBarTabWidget->setFocusPolicy(
                Qt::FocusPolicy(dockTabWidget->focusPolicy()&(~Qt::TabFocus)));
    ToolBarTabWidget->setCurrentIndex(1); //初始界面为控件
    ToolBarTabWidget->setStyleSheet("background: rgb(197, 222, 255);");
    m_toolDock->setWidget(ToolBarTabWidget);

    addDockWidget(Qt::RightDockWidgetArea, m_toolDock, Qt::Horizontal);
    m_toolDock->setData(TOOL_BUTTON);
    connect(m_toolDock, SIGNAL(dockWidgetClose(int)), this, SLOT(dockWidgetClose(int)));


    /***************************edit by zqh**************************/
    /***************************创建视图类*****************************/

    m_ProVersionNum = AK_CURRENT_VERSION;
    nZoomNumber=100; //缩放的初始值
    bIfSceneShowGrid = false;//是否显示网格标示
    pDrawToSceneItem = NULL;

    /*pSceneSheet[nActiveSheetIndex] = new SamDrawScene ;//samdrawscene();QGraphicsScene
    pSceneSheet[nActiveSheetIndex]->setSceneRect(QRectF(0, 0, 1000, 1000));
    QHBoxLayout *layout = new QHBoxLayout;
    pView = new QGraphicsView(pSceneSheet[nActiveSheetIndex], this);
    pView->setDragMode(QGraphicsView::RubberBandDrag);//把单选改变给拖动模式
    pView->setRenderHint(QPainter::Antialiasing, true); // 设置图形反走样
    pView->setMouseTracking(true); // 设置鼠标移动捕捉

    pView->setSceneRect(0,0,1000,1000);
    pView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    layout->addWidget(pView);
    ui->centralWidget->setLayout(layout);

    setWindowTitle(tr(VERSION_NAME));
    setUnifiedTitleAndToolBarOnMac(true);
    **************************创建视图类end*****************************/

    connect(ui->action_new_pro,SIGNAL(triggered()),this,SLOT(createprodlg()));
    connect(ui->action_open_pro,SIGNAL(triggered()),this,SLOT(createopenprodlg()));
    //connect(ui->action_new_screen,SIGNAL(triggered()),this,SLOT(createnewscreendlg()));
    connect(ui->action_save,SIGNAL(triggered()),this,SLOT(createsavedlg()));

    /******主界面物件工具栏信号与槽的连接********/	
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
    connect(ui->action_checkall,SIGNAL(triggered()),this,SLOT(SlecetALL()));//Ctrl+A全选
    connect(ui->action_Keyboard,SIGNAL(triggered()),this,SLOT(CreateKeyboardASCII()));//键盘组件
    connect(ui->action_messageboard,SIGNAL(triggered()),this,SLOT(OnCreateMessageBoard()));//留言板
    connect(ui->action_User_Keybaor,SIGNAL(triggered()),this,SLOT(tree_newuserkeyboard()));//添加用户自定义键盘
    connect(ui->action_datasamp,SIGNAL(triggered()),this,SLOT(tree_addhisdatalogger()));//添加数据采集
    connect(ui->action_waring,SIGNAL(triggered()),this,SLOT(tree_digitAlarm()));//添加报警
    connect(ui->action_rep,SIGNAL(triggered()),this,SLOT(tree_recipe()));//添加配方
    connect(ui->action_script,SIGNAL(triggered()),this,SLOT(slotOpenMacro()));//打开脚本浏览器

   // connect(ui->action_upload,SIGNAL(triggered()),this,SLOT(OnCreatUploadDlg()));//打开上载对话框

    //connect(ui->action_Pie,SIGNAL(triggered()),this,SLOT(OnCreatePie()));
    //connect(ui->action_Steping,SIGNAL(triggered()),this,SLOT(OnCreateSteping()));
    connect(ui->actionRecipeChoice,SIGNAL(triggered()),this,SLOT(ONRecipeChoice()));//配方选择器
    //connect(pPieAction,SIGNAL(triggered()),this,SLOT(OnCreatePie()));
  //  connect(ui->action_opera_record,SIGNAL(triggered()),this,SLOT(createoperadlg()));

    //绘图工具栏edit by zqh
   connect(ui->action_rect,SIGNAL(triggered()),this,SLOT(OnDrawRect())); //连接画矩形的槽和信号
   connect(ui->action_line,SIGNAL(triggered()),this,SLOT(OnDrawLine())); //连接画直线的槽和信号
   connect(ui->action_ellipse,SIGNAL(triggered()),this,SLOT(OnDrawEllipse())); //连接画圆的槽和信号
   connect(ui->action_polygon,SIGNAL(triggered()),this,SLOT(OnDrawPolygon())); //连接画多边形的槽和信号
   connect(ui->action_foldline,SIGNAL(triggered()),this,SLOT(OnDrawFoldLine())); //连接画折线的槽和信号
   connect(ui->action_freeline,SIGNAL(triggered()),this,SLOT(OnDrawFreeLine())); //连接自由直线的槽和信号
   connect(ui->action_blight_circle,SIGNAL(triggered()),this,SLOT(onDrawBlightCircle()));//连接曲线/圆弧的槽和信号
   connect(ui->action_text,SIGNAL(triggered()),this,SLOT(onDrawText()));
   connect(ui->action_RoundedRect,SIGNAL(triggered()),this,SLOT(OnCreateRoundedRect())); //圆角矩形
   connect(ui->action_ArcItem,SIGNAL(triggered()),this,SLOT(OnCreateArc())); //扇形

    //工具箱
    //绘图工具栏
    connect(ui->btn_rect,SIGNAL(clicked()),this,SLOT(OnDrawRect())); //连接画矩形的槽和信号
    connect(ui->btn_line,SIGNAL(clicked()),this,SLOT(OnDrawLine())); //连接画直线的槽和信号
    connect(ui->btn_elipse,SIGNAL(clicked()),this,SLOT(OnDrawEllipse())); //连接画圆的槽和信号
    connect(ui->btn_polygon,SIGNAL(clicked()),this,SLOT(OnDrawPolygon())); //连接画多边形的槽和信号
    connect(ui->btn_foldline,SIGNAL(clicked()),this,SLOT(OnDrawFoldLine())); //连接画折线的槽和信号
    connect(ui->btn_freeline,SIGNAL(clicked()),this,SLOT(OnDrawFreeLine())); //连接自由直线的槽和信号
    connect(ui->btn_linecycle,SIGNAL(clicked()),this,SLOT(onDrawBlightCircle()));//连接曲线/圆弧的槽和信号
    connect(ui->btn_text,SIGNAL(clicked()),this,SLOT(onDrawText()));
    connect(ui->btn_roundrect,SIGNAL(clicked()),this,SLOT(OnCreateRoundedRect())); //圆角矩形
    connect(ui->btn_arc,SIGNAL(clicked()),this,SLOT(OnCreateArc())); //扇形

    //开关等所有控件
    connect(ui->btn_switch,SIGNAL(clicked()),this,SLOT(createbitbtndlg()));//开关dataplay
    connect(ui->btn_MF,SIGNAL(clicked()),this,SLOT(createMFbtndlg()));//多功能按钮

    connect(ui->btn_dataDisplay,SIGNAL(clicked()),this,SLOT(createvalue()));//数值显示
    connect(ui->dataplay,SIGNAL(triggered()),this,SLOT(createvalue()));//数值显示

    connect(ui->btn_metre,SIGNAL(clicked()),this,SLOT(createchart()));//图表
    connect(ui->graphicsitem,SIGNAL(triggered()),this,SLOT(createchart()));//图表

    connect(ui->btn_XYtrend,SIGNAL(clicked()),this,SLOT(createXYtrend()));//图表
    connect(ui->action_X_Y,SIGNAL(triggered()),this,SLOT(createXYtrend()));//图表

    connect(ui->btn_picture,SIGNAL(clicked()),this,SLOT(createimage()));//图片显示器
    connect(ui->pictruedisplay,SIGNAL(triggered()),this,SLOT(createimage()));//图片显示器

    connect(ui->btn_trend,SIGNAL(clicked()),this,SLOT(createtrendchartdlg()));//曲线
    connect(ui->btn_datagroup,SIGNAL(clicked()),this,SLOT(on_action_DatagroupDisplay_triggered()));//数据群组
    connect(ui->btn_hisdataDisplay,SIGNAL(clicked()),this,SLOT(createhisrecord()));//历史数据显示器
    connect(ui->btn_messageDisplay,SIGNAL(clicked()),this,SLOT(createmsgdisplay()));//消息显示器
    connect(ui->btn_dyncircle,SIGNAL(clicked()),this,SLOT(createdyncricledlg()));//动态圆
    connect(ui->btn_dynrect,SIGNAL(clicked()),this,SLOT(createdynrentdlg()));//动态矩形
    connect(ui->btn_flow,SIGNAL(clicked()),this,SLOT(createflowblock()));//流动块
    connect(ui->btn_animation,SIGNAL(clicked()),this,SLOT(OnCreateAnimaDlg()));//动画
    connect(ui->btn_gif,SIGNAL(clicked()),this,SLOT(createstaticpicturedlg()));//GIF显示器
    connect(ui->btn_alarmDisplay,SIGNAL(clicked()),this,SLOT(createalarmcontroldlg()));//报警显示器
    connect(ui->btn_alarmbar,SIGNAL(clicked()),this,SLOT(createdynalarmbar()));//动态报警条
    connect(ui->btn_hisalarmDisplay,SIGNAL(clicked()),this,SLOT(createhisalarm()));//历史报警显示器
    connect(ui->btn_combox,SIGNAL(clicked()),this,SLOT(OnCreateComboBoxDlg()));//功能选择按钮
    connect(ui->pushButton_message,SIGNAL(clicked()),this,SLOT(OnCreateMessageBoard()));//留言板
    connect(ui->pushButton_Combobox,SIGNAL(clicked()),this,SLOT(OnCreateComboBox()));//combobox
    connect(ui->btn_slider,SIGNAL(clicked()),this,SLOT(OnCreateSliderDlg()));//滑动模拟量开关
    connect(ui->btn_recipeDisplay,SIGNAL(clicked()),this,SLOT(createrecipetable()));//配方显示器
    connect(ui->btn_recipeselect,SIGNAL(clicked()),this,SLOT(ONRecipeChoice()));//配方选择器

    //标准工具栏edit by zqh
    connect(ui->action_reverse_selection,SIGNAL(triggered()),this,SLOT(Reverse_selection())); //反向选择
    connect(ui->action_group,SIGNAL(triggered()),this,SLOT(OnGroupItem()));     //连接组合的槽和信号
    connect(ui->action_split,SIGNAL(triggered()),this,SLOT(OnDisGroupItem()));  //连接拆分的槽和信号
    connect(ui->action_delete,SIGNAL(triggered()),this,SLOT(OnDeleteItem())); //连接删除的槽和信号
    connect(ui->action_copy,SIGNAL(triggered()),this,SLOT(OnCopyItem()));//复制
    connect(ui->action_paste,SIGNAL(triggered()),this,SLOT(OnPasteItem()));//粘贴
    connect(ui->action_lock,SIGNAL(triggered()),this,SLOT(OnLockItem()));       //连接锁定的槽和信号
    connect(ui->action_delock,SIGNAL(triggered()),this,SLOT(OnUnLockItem()));   //连接解锁的槽和信号
    connect(ui->action_widthsame,SIGNAL(triggered()),this,SLOT(onWidthSame())); //设置选中对象等宽
    connect(ui->action_heightsame,SIGNAL(triggered()),this,SLOT(onHeightSame())); //设置选中对象等高
    connect(ui->action_widthheightsame,SIGNAL(triggered()),this,SLOT(onWidthHeightSame())); //设置选中对象等宽等高
    /**********************************************************************
    *图形的对齐方式
    *edit by zqh
    **********************************************************************/
    connect(ui->action_right,SIGNAL(triggered()),this,SLOT(OnSetRight()));  //右对齐
    connect(ui->action_left,SIGNAL(triggered()),this,SLOT(OnSetLeft()));    //左对齐
    connect(ui->action_top,SIGNAL(triggered()),this,SLOT(OnSetTop()));     //上对齐
    connect(ui->action_under,SIGNAL(triggered()),this,SLOT(OnSetButtom()));//下对齐
    connect(ui->action_hcenter,SIGNAL(triggered()),this,SLOT(OnSetHCenter()));//水平居中对齐
    connect(ui->action_vcenter,SIGNAL(triggered()),this,SLOT(OnSetVCenter()));//垂直居中对齐

    connect(ui->action_horizontal,SIGNAL(triggered()),this,SLOT(OnSetHSpacingAlign()));//水平等间距对齐
    connect(ui->action_vertcal,SIGNAL(triggered()),this,SLOT(OnSetVSpacingAlign()));//垂直等间距对齐
    connect(ui->action_new_screen,SIGNAL(triggered()),this,SLOT(OnAddNewScreen()));//新建画面
    connect(ui->action_upscreen,SIGNAL(triggered()),this,SLOT(OnSetTheFrontScreen()));//上一幅画面
    connect(ui->action_nextscreen,SIGNAL(triggered()),this,SLOT(OnSetTheNextScreen()));//下一幅画面
    connect(this,SIGNAL(InitScreenDlg()),newScreenDlg,SLOT(InitScreenDlg()));
    connect(this,SIGNAL(InitWindowDlg()),newWindowDlg,SLOT(InitWindowDlg()));
    connect(this,SIGNAL(InitScreenPropertyDlg()),newScreenDlg,SLOT(InitScreenPropertyDlg()));
    connect(this,SIGNAL(InitWindowPropertyDlg()),newWindowDlg,SLOT(InitWindowPropertyDlg()));

    connect(ui->btn_table,SIGNAL(clicked()),this,SLOT(OnCreateTable()));//表格
    connect(ui->btn_scale,SIGNAL(clicked()),this,SLOT(OnCreateScales()));//刻度
    connect(ui->action_table,SIGNAL(triggered()),this,SLOT(OnCreateTable()));//表格
    connect(ui->action_mark,SIGNAL(triggered()),this,SLOT(OnCreateScales()));//刻度

   // connect(ui->btn_library,SIGNAL(clicked()),this,SLOT(on_action_open_mapstorage_triggered()));//图库

    //connect(ui->action_stateon,SIGNAL(triggered()),this,SLOT(OnSetONState()));//设置为ON状态
    //connect(ui->action_state0,SIGNAL(triggered()),this,SLOT(OnSetOFFState()));//设置为OFF状态

    connect(ui->action_zoonbig,SIGNAL(triggered()),this,SLOT(OnSetZoomEnlarge()));//放大
    connect(ui->action_zoonfit,SIGNAL(triggered()),this,SLOT(OnSetZoomFit()));//复原
    connect(ui->action_zoonsmall,SIGNAL(triggered()),this,SLOT(OnSetZoomSmall()));//缩小
    connect(ui->action_grid,SIGNAL(triggered()),this,SLOT(OnSetSceneGrid()));//网格
    connect(ui->action_panview,SIGNAL(triggered()),this,SLOT(OnSetDagViewModel()));//平移视图
    connect(ui->action_arrow,SIGNAL(triggered()),this,SLOT(OnSetDagViewModelArrow()));//鼠标时箭头
    connect(ui->action_openpropertiset,SIGNAL(triggered()),this,SLOT(OnOpenPropertyDlg()));//打开属性对话框
    connect(ui->action_address_find,SIGNAL(triggered()),this,SLOT(OnFindAddressDlg()));//打开查找地址对话框
    connect(ui->action_address_table,SIGNAL(triggered()),this,SLOT(OnDisplayAddrUseDlg()));//打开地址使用一览表对话框
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
    connect(ui->action_close,SIGNAL(triggered()),this,SLOT(closeProject()));//关闭工程
    openInit_MenuAndTool();
    connect(this,SIGNAL(upDate_treeScreenItem()),this,SLOT(upDatetreeScreenItem()));
    connect(this,SIGNAL(reTreeScreenAndWindow()),this,SLOT(reTree_ScreenAndWindow()));
    connect(this,SIGNAL(openProreTreeCtl()),this,SLOT(openPro_reTreeCtl()));
    //connect(ui->action_singleselect,SIGNAL(triggered()),this,SLOT(OnCreateSingleSelectDlg())); //单选按钮
    connect(ui->action_ComboBox,SIGNAL(triggered()),this,SLOT(OnCreateComboBoxDlg())); //多功能选择按钮
    connect(ui->action_Slider,SIGNAL(triggered()),this,SLOT(OnCreateSliderDlg())); //滑块模拟量开关
    //connect(ui->action_compile,SIGNAL(triggered()),this,SLOT(StartCompileThread())); //编译
    connect(ui->action_Animation,SIGNAL(triggered()),this,SLOT(OnCreateAnimaDlg())); //动画
    //connect(ui->action_MsgBoard,SIGNAL(triggered()),this,SLOT(OnCreateMsgBoard())); //留言板
    //connect(ui->action_P,SIGNAL(triggered()),this,SLOT(OpenHmiSetting()));//设定-触摸屏一般参数设置
    //connect(ui->action_96,SIGNAL(triggered()),this,SLOT(OpenHmiSetting()));//设定-类比报警
    //connect(ui->action_97,SIGNAL(triggered()),this,SLOT(OpenHmiSetting()));//设定-数位报警
    //connect(ui->action_R_2,SIGNAL(triggered()),this,SLOT(OpenRecipe()));//设定-配方
    //connect(ui->action_M,SIGNAL(triggered()),this,SLOT(OpenFileProtection()));//设定-文件保护
    connect(ui->action_h,SIGNAL(triggered()),this,SLOT(OnSetHMirror())); //水平镜像
    connect(ui->action_v,SIGNAL(triggered()),this,SLOT(OnSetVMirror())); //垂直镜像
    connect(ui->action_cut,SIGNAL(triggered()),this,SLOT(OnCutItem())); //剪切
    connect(ui->action_offline_simulation,SIGNAL(triggered()),this,SLOT(ExecuteOffLineMonitor())); //离线模拟

    connect(ui->action_SamDraw3_4,SIGNAL(triggered()),this,SLOT(RunAboutDlg())); //关于对话框
    connect(ui->action_copym,SIGNAL(triggered()),this,SLOT(MultiCopyDlg())); //多重复制
    //状态栏上面的四个QLINEEDIT的改变事件
    connect(lab_left_space_statusBar,SIGNAL(editingFinished()),this,SLOT(changeItem_x()));
    connect(lab_up_space_statusBar,SIGNAL(editingFinished()),this,SLOT(changeItem_y()));
    connect(lab_width_space_statusBar,SIGNAL(editingFinished()),this,SLOT(changeItem_w()));
    connect(lab_hidth_space_statusBar,SIGNAL(editingFinished()),this,SLOT(changeItem_h()));
    connect(ui->action_english,SIGNAL(triggered()),this,SLOT(ChangetoEnglish()));
    connect(ui->action_chinese,SIGNAL(triggered()),this,SLOT(ChangetoChinese()));
    ui->action_chinese->setCheckable(true);
    ui->action_english->setCheckable(true);
    ui->action_chinese->setChecked(true);
    /*以下是宏指令编辑功能触发及其关联的槽函数*/
    //connect(ui->action_macro,SIGNAL(triggered()),this,SLOT(MarcoEdit()));
    connect(ui->action_H,SIGNAL(triggered()),this,SLOT(LoadProjectHelp()));
    loadBaseLibAndUserDefineLib(); //加载基本图库
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
    //添加 初始化协议表
    vPlc = QProtocolTool::getAllProtocols();
    m_factoryMap = QProtocolTool::getDriversConfig();
    //载入系统函数库
    loadSysLibs();
    /*ui->dockWidget->setVisible(false);
    ui->toolBox->setVisible(false);
    ui->dockWidget->setFixedSize(161,291);*/
    setToolBoxFloat();

    pwnd->setWindowTitle(PRO_FULL_NAME);
    //ui->action_SamDraw3_4->setText(tr("关于") + PRO_FULL_NAME);
    //ui->action_SamDraw3_4->setText(tr("关于"));

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

    //为连接添加3个子项，子项不能被删除
    stConnect con;
    for(int i = 0; i < 6; i++)//添加连接0，连接1，连接2,以太网
    {
        con.id = i;
        if(0 == i)
        {
            con.sConnectName = tr("Com1");//QString(tr("连接"))+QString::number(i);
        }
        else if(1 == i)
        {
            con.sConnectName = tr("Com2");//QString(tr("连接"))+QString::number(i);
        }
        else if(2 == i)
        {
            con.sConnectName = tr("Com3");//QString(tr("连接"))+QString::number(i);
        }
        else if(3 == i)
        {
            con.sConnectName = tr("网络");//QString(tr("连接"))+QString::number(i);
        }
        else if(4 == i)
        {
            con.sConnectName = tr("CAN1");//QString(tr("连接"))+QString::number(i);
        }
        else if(5 == i)
        {
            con.sConnectName = tr("CAN2");//QString(tr("连接"))+QString::number(i);
        }
        //con.sConnectName = QString(tr("连接"))+QString::number(i);
        con.eConnectPort = i;//com1
        con.bUseRelationPort = false;//默认不转发
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

        con.bMasterScreen      = 1;//主屏
        con.bConnectScreenPort = 0;//连接PLC口
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
    //ui->action_SamDraw3_4->setText(tr("关于") + PRO_FULL_NAME);
    //ui->action_SamDraw3_4->setText(tr("关于"));
    //XXXXX
    /*if(languagedlg)
    {
        delete languagedlg;
        languagedlg = NULL;
    }
    languagedlg = new  QTreeCtrlLanguageDlg(this);*/

    /*初始化宏的数据*/

    /*初始化配方对话框*/
    //initRecipeDlg();//初始化配方
    //if(recipeDlg)
    //{
    //    delete recipeDlg;
    //    recipeDlg = NULL;
    //}
    //recipeDlg=new QTreeCtrlRecipeDlg(this);//配方对话框;

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
        undoAction->setText(tr("撤销"));
        undoAction->setIconText(tr("撤销"));
        redoAction->setText(tr("恢复"));
        redoAction->setIconText(tr("恢复"));
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
*创建action
*******************************************************************/
void MainWindow::createActions()
{
    undoAction = undoStack->createUndoAction(this, tr("撤销"));
    undoAction->setStatusTip(tr("撤销所做操作"));
    undoAction->setIcon(QIcon(":/standardtool/images/standardtool/undo.ico"));
    undoAction->setObjectName(QString::fromUtf8("action_undo"));
    undoAction->setShortcuts(QKeySequence::Undo);
    undoAction->setIconText(tr("\n撤销"));

    redoAction = undoStack->createRedoAction(this, tr("恢复"));
    redoAction->setIcon(QIcon(":/standardtool/images/standardtool/redo.ico"));
    redoAction->setStatusTip(tr("恢复撤销操作"));
    redoAction->setObjectName(QString::fromUtf8("action_redo"));
    redoAction->setShortcuts(QKeySequence::Redo);
    redoAction->setIconText(tr("\n恢复"));

    if(is_tanslator == 0)
    {
        undoAction->setIconText(tr("\n撤销"));
        redoAction->setIconText(tr("\n恢复"));
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
    deleteAction->setStatusTip(tr("删除条目"));

    for (int i = 0; i < MaxRecentFiles; ++i) //4个最近打开的文档
    {
        recentFileActs[i] = new QAction(this);
        recentFileActs[i]->setVisible(false);
        connect(recentFileActs[i], SIGNAL(triggered()),this, SLOT(openRecentFile()));
    }
}

/******************************************************************
*添加菜单栏的action，该部分是由于无法用ui视图设计，采用代码添加
*******************************************************************/
void MainWindow::createMenu()
{
    ui->menu_E->addAction(ui->action_macro_find);//宏指查找
    ui->menu_E->addAction(ui->action_macro_admin);//宏指令编辑器

//    ui->menu_thing->addAction(ui->action_mfaction);//多功能键
//    ui->menu_thing->addAction(ui->action_flow_block);//流动块
//    ui->menu_thing->addAction(ui->action_his_tre_display);//历史数据显示器
//    ui->menu_thing->addAction(ui->action_timer);//定时器
//    ui->menu_thing->addAction(ui->action_Pie);//扇形
//    ui->menu_thing->addAction(ui->action_Steping);//步进
//    ui->menu_thing->addAction(ui->action_singleselect);//单选
//    ui->menu_thing->addAction(ui->action_ComboBox);//下拉
//    ui->menu_thing->addAction(ui->action_Slider);//滑动
//    ui->menu_thing->addAction(ui->action_Animation);//动画
//    ui->menu_thing->addAction(ui->action_MsgBoard);//留言板

    /*以下是添加撤销,恢复功能的菜单*/
    ui->menu_E->insertAction(ui->action_cut,undoAction);
    ui->menu_E->insertAction(ui->action_cut,redoAction);
    ui->menu_E->insertSeparator(ui->action_cut);

    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        //ui->menu_F->addAction(recentFileActs[i]);
        ui->menu_recentFile->addAction(recentFileActs[i]);
    }
    updateRecentFileActions();//更新最近打开的文档
}


/******************************************************************
*创建工具栏
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
    qButtonLab->setText(tr("状态"));;
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
    qLanguageLab->setText(tr("语言"));
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
    widgetCmb->setStyleSheet("font: 9pt '宋体';");
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
*创建状态栏
*******************************************************************/
void MainWindow::createStatusBar()
{

    lab_control_statusBar=new QLabel(tr("按钮名称"));
    lab_control_statusBar->setFrameShadow(QFrame::Sunken); //设置标签阴影
    lab_control_statusBar->setFixedWidth(100);

    lab_Coordinate_statusBar=new QLabel(tr("控件坐标"));
    lab_Coordinate_statusBar->setFrameShadow(QFrame::Sunken); //设置标签阴影
    lab_Coordinate_statusBar->setFixedWidth(80);

    lab_up_statusBar=new QLabel(tr("上:"));
    lab_up_statusBar->setFrameShadow(QFrame::Sunken);


    lab_up_space_statusBar=new QLineEdit;
    lab_up_space_statusBar->setFocusPolicy(
            Qt::FocusPolicy(lab_up_space_statusBar->focusPolicy()&(~Qt::TabFocus)));
    lab_up_space_statusBar->setFixedWidth(60);
    lab_up_space_statusBar->setEnabled(false);
    QDoubleValidator  *validator4 = new QDoubleValidator(lab_up_space_statusBar );
    validator4->setDecimals(1);
    lab_up_space_statusBar->setValidator( validator4 );

    lab_left_statusBar=new QLabel(tr("左:"));
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

    lab_size_statusBar=new QLabel(tr("控件大小"));
    lab_size_statusBar->setFrameShadow(QFrame::Sunken);

    lab_width_statusBar=new QLabel(tr("宽:"));
    lab_width_statusBar->setFrameShadow(QFrame::Sunken);

    lab_width_space_statusBar=new QLineEdit;
    lab_width_space_statusBar->setFocusPolicy(
            Qt::FocusPolicy(lab_width_space_statusBar->focusPolicy()&(~Qt::TabFocus)));
    lab_width_space_statusBar->setFixedWidth(60);
    lab_width_space_statusBar->setEnabled(false);
    QDoubleValidator  *validator2 = new QDoubleValidator(lab_width_space_statusBar );
    validator2->setDecimals(1);
    lab_width_space_statusBar->setValidator( validator2 );

    lab_hight_statusBar=new QLabel(tr("高:"));
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
    lab_samkoon_statusBar=new QLabel(tr("显控科技"));
#else define LA_DEBINUO
    //lab_samkoon_statusBar=new QLabel(tr("德比诺"));
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
    ui->statusBar->showMessage(tr("就绪") );

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
*该函数用来生成左边树形目录
************************************************************************/
void MainWindow::initLeftDocking()
{

    tree=new mytreeWidget();
    tree->setFocusPolicy(Qt::NoFocus);
    tree->setColumnCount(1);
    tree->setHeaderHidden(true);
    root = new QTreeWidgetItem(tree, QStringList(tr("触摸屏")));

    root->setIcon(0,QIcon(":/tree/images/tree/HMI.ico"));

    //+++++
    //系统设置
    link = new QTreeWidgetItem(root, QStringList(tr("连接设置")));
    root->addChild(link);
    link->setIcon(0,QIcon(":/tree/images/tree/com.ico"));
    //plcConnect = new QTreeWidgetItem(root, QStringList(tr("连接设置")));
    //root->addChild(plcConnect);

 #ifdef AKPLC
    PlcNode = new QTreeWidgetItem(root, QStringList(tr("PLC编程")));
    root->addChild(PlcNode);
    PlcNode->setIcon(0,QIcon(":/tree/images/tree/HMIsetting.ico"));
#endif

    sysSetting = new QTreeWidgetItem(root, QStringList(tr("系统设置")));
    root->addChild(sysSetting);
    sysSetting->setIcon(0,QIcon(":/tree/images/tree/HMIsetting.ico"));

    pcCtrl = new QTreeWidgetItem(sysSetting, QStringList(tr("主机管理")));
    sysSetting->addChild(pcCtrl);
    pcCtrl->setIcon(0,QIcon(":/tree/images/tree/PCManager.ico"));//用的是连接的图标

    pcChoice = new QTreeWidgetItem(pcCtrl, QStringList(tr("机型选择")));
    pcCtrl->addChild(pcChoice);
    pcChoice->setIcon(0,QIcon(":/tree/images/tree/HMISelect.ico"));

    displaySet = new QTreeWidgetItem(pcCtrl, QStringList(tr("显示设置")));
    pcCtrl->addChild(displaySet);
    displaySet->setIcon(0,QIcon(":/tree/images/tree/showseting.ico"));

    operateSet = new QTreeWidgetItem(pcCtrl, QStringList(tr("操作设置")));
    pcCtrl->addChild(operateSet);
    operateSet->setIcon(0,QIcon(":/tree/images/tree/operatorset.ico"));

    dataCtrl = new QTreeWidgetItem(pcCtrl, QStringList(tr("数据控制")));
    pcCtrl->addChild(dataCtrl);
    dataCtrl->setIcon(0,QIcon(":/tree/images/tree/datactrol.ico"));

    //timeArea = new QTreeWidgetItem(pcCtrl, QStringList(tr("时间&区域")));
    //pcCtrl->addChild(timeArea);

    permissionSec = new QTreeWidgetItem(pcCtrl, QStringList(tr("用户权限")));
    pcCtrl->addChild(permissionSec);
    permissionSec->setIcon(0,QIcon(":/tree/images/tree/User.ico"));

    hostPeri = new QTreeWidgetItem(sysSetting, QStringList(tr("主机外设")));
    sysSetting->addChild(hostPeri);
    hostPeri->setIcon(0,QIcon(":/tree/images/tree/PLCcontral.ico"));//用的是PLC控制的图标

    //plcCtrl = new QTreeWidgetItem(hostPeri, QStringList(tr("PLC控制")));
    //hostPeri->addChild(plcCtrl);
    printer = new QTreeWidgetItem(hostPeri, QStringList(tr("打印机")));
    hostPeri->addChild(printer);
    printer->setIcon(0,QIcon(":/tree/images/tree/printer.ico"));//用的是打印机的图标

    //networkAd = new QTreeWidgetItem(hostPeri, QStringList(tr("网络适配器")));
    //hostPeri->addChild(networkAd);

    confiWorks = new QTreeWidgetItem(sysSetting, QStringList(tr("组态工程")));
    sysSetting->addChild(confiWorks);
    confiWorks->setIcon(0,QIcon(":/tree/images/tree/zutaiprj.ico"));//用的是HMI保护的图标

    downloadSet = new QTreeWidgetItem(confiWorks, QStringList(tr("下载设置")));
    confiWorks->addChild(downloadSet);
    downloadSet->setIcon(0,QIcon(":/tree/images/tree/downset.ico"));

    accessEncry = new QTreeWidgetItem(confiWorks, QStringList(tr("访问加密")));
    confiWorks->addChild(accessEncry);
    accessEncry->setIcon(0,QIcon(":/tree/images/tree/prjpsw.ico"));

    //添加设置的时钟子项
    clock=new QTreeWidgetItem(confiWorks,QStringList(tr("时钟设置")));
    confiWorks->addChild(clock);
    clock->setIcon(0,QIcon(":/tree/images/tree/clock.ico"));

    productLicen = new QTreeWidgetItem(confiWorks, QStringList(tr("产品授权")));
    confiWorks->addChild(productLicen);
    productLicen->setIcon(0,QIcon(":/tree/images/tree/product.ico"));

    lanSet = new QTreeWidgetItem(confiWorks, QStringList(tr("语言设置")));
    confiWorks->addChild(lanSet);
    lanSet->setIcon(0,QIcon(":/btn/images/yuy.ico"));
    chdItem = new QTreeWidgetItem(confiWorks, QStringList(tr("掉电存储区设置")));
    confiWorks->addChild(chdItem);
    chdItem->setIcon(0,QIcon(":/standardtool/images/power.ico"));
    //xiaoqiang
    //添加画面项
    /*screen = new QTreeWidgetItem(root,QStringList(tr("画面")));
    root->addChild(screen);
    screen->setIcon(0,QIcon(":/tree/images/tree/screen.ico"));

    //添加窗口项
    window = new QTreeWidgetItem(root,QStringList(tr("窗口")));
    root->addChild(window);
    window->setIcon(0,QIcon(":/tree/images/tree/window.ico"));

    //添加自定义键盘
    TreeKeyboard=new QTreeWidgetItem(root,QStringList(tr("自定义键盘")));
    root->insertChild(0,TreeKeyboard);
    TreeKeyboard->setIcon(0,QIcon(":/tree/images/tree/keyboard.ico"));
    TreeKeyboard->setHidden(true);*/

    //添加历史数据收集器项
    tree_hisdatalog=new QTreeWidgetItem(root,QStringList(tr("数据采集")));
    root->addChild(tree_hisdatalog);
    tree_hisdatalog->setIcon(0,QIcon(":/tree/images/tree/hisdata.ico"));

    //添加报警登陆项
    alarmlog=new QTreeWidgetItem(root,QStringList(tr("报警登录")));
    root->addChild(alarmlog);
    alarmlog->setIcon(0,QIcon(":/btn/images/alarm.ico"));

    tree_macro = new QTreeWidgetItem(root,QStringList(tr("脚本")));
    root->addChild(tree_macro);
    tree_macro->setIcon(0,QIcon(":/tree/images/tree/script.ico"));

    global_macro = new QTreeWidgetItem(tree_macro,QStringList(tr("全局脚本")));
    tree_macro->addChild(global_macro);
    global_macro->setIcon(0,QIcon(":/tree/images/tree/globalScript.ico"));
    init_macro = new QTreeWidgetItem(tree_macro,QStringList(tr("初始化脚本")));
    tree_macro->addChild(init_macro);
    init_macro->setIcon(0,QIcon(":/tree/images/tree/initScrpit.ico"));

    //添加配方项
    recipe=new QTreeWidgetItem(root,QStringList(tr("配方")));
    root->addChild(recipe);
    recipe->setIcon(0,QIcon(":/tree/images/tree/recipe.ico"));
    datatransport=new QTreeWidgetItem(root,QStringList(tr("资料传输")));
    root->addChild(datatransport);
    datatransport->setIcon(0,QIcon(":/tree/images/tree/import.ico"));

    treeScheduler=new QTreeWidgetItem(root,QStringList(tr("时间表")));
    root->addChild(treeScheduler);
    treeScheduler->setIcon(0,QIcon(":/tree/images/tree/import.ico"));

    //tree_varRcd=new QTreeWidgetItem(root,QStringList(tr("变量表")));
    //root->addChild(tree_varRcd);
    //tree_varRcd->setIcon(0,QIcon(":/tree/images/tree/import.ico"));
//    sub_Recipe=new QTreeWidgetItem(recipe,QStringList(tr("配方1")));
//    recipe->addChild(sub_Recipe);
//    sub_Recipe->setIcon(0,QIcon(":/tree/images/tree/recipe.ico"));
//    sub_Recipe->setHidden(true);

    //xiaoqiang
    tree0 = new mytreeWidget();
    tree0->setFocusPolicy(Qt::NoFocus);
    tree0->setColumnCount(1);
    tree0->setHeaderHidden(true);

    root0 = new QTreeWidgetItem(tree0, QStringList(tr("窗口&画面")));
    root0->setIcon(0,QIcon(":/tree/images/tree/HMI.ico"));

    //添加画面项
    screen = new QTreeWidgetItem(root0,QStringList(tr("画面")));
    root0->addChild(screen);
    screen->setIcon(0,QIcon(":/tree/images/tree/screen.ico"));

    //添加窗口项
    window = new QTreeWidgetItem(root0,QStringList(tr("窗口")));
    root0->addChild(window);
    window->setIcon(0,QIcon(":/tree/images/tree/window.ico"));

    //添加自定义键盘
    TreeKeyboard=new QTreeWidgetItem(root0,QStringList(tr("自定义键盘")));
    root0->insertChild(0,TreeKeyboard);
    TreeKeyboard->setIcon(0,QIcon(":/tree/images/tree/keyboard.ico"));
    TreeKeyboard->setHidden(true);
    //--------------------------end--------------------------------

    //tree->expandAll();
    //为树形控件添加双击响应的槽函数
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
*实现文本输出框
***********************************************************************/
void MainWindow::initRightDocking()
{

    //textedit = new QTextEdit();
    pMainList = new QTableWidget ;
    m_rightDock = new myDockWidget(tr("信息输出"),this);
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
    pMainList->setEditTriggers(QAbstractItemView::NoEditTriggers);//List控件不可以编辑
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

    QAction *ClearAction = cmenu->addAction(tr("清除"));


    connect(ClearAction, SIGNAL(triggered(bool)), this, SLOT(clearMessage()));

    cmenu->exec(QCursor::pos());//在当前鼠标位置显示

}
void MainWindow::clearMessage()
{
    pMainList->clear();
    pMainList->setRowCount(0);
}
/***********************************************************************
*实现树形控件子目录的双击响应槽函数，关于树形控件的相关操作可以在此添加响应函数
***********************************************************************/
void MainWindow::treeItemLDclick0(QTreeWidgetItem *item,int i)
{
    QTreeWidgetItem *parentItem = tree0->currentItem()->parent();
    QString         str         = tree0->currentItem()->text(0);
    //QString         parentStr   = parentItem->text(0);

    if(isHave)
    {
        if(str==tr("窗口&画面") || str==tr("画面") || str==tr("窗口"))
        {
            return;
        }

        if(parentItem==copyScreen_Item||parentItem==screen)//当双击的是画面第2级菜单时
        {
            QStringList list=str.split(":");
            //pwnd->is_Save=false;
            //pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
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
        else if(parentItem==window||parentItem==copyWindow_Item)//当双击的是窗口第2级菜单时
        {
            QStringList list=str.split(":");
            //pwnd->is_Save=false;
            //pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
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
        else if(parentItem == TreeKeyboard||parentItem == copyUserKeyboard)//自定义菜单
        {
            QStringList list=str.split(":");
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            nActiveSheetIndex=nFindActiveSheetIndex(str);//把双击的序号赋值到当前的序号中
            pView->setScene(pSceneSheet[nActiveSheetIndex]);//设置当前场景

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
        if(str==tr("机型选择") && parentStr == tr("主机管理"))
        {
            ModelSel model_select(this);
            model_select.exec();
            //这里需要重置树形结构，确保和旧工程想兼容，因为这个时候旧工程只能看到com1，com2，以太网
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
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            return;
        }
        else if(str==tr("显示设置") && parentStr == tr("主机管理"))
        {
            NewInitSet init_set(this);
            init_set.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            return;
        }
        else if(str==tr("操作设置") && parentStr == tr("主机管理"))
        {
            operatorSet operator_set(this);
            operator_set.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            return;
        }
        else if(str==tr("数据控制") && parentStr == tr("主机管理"))
        {
            NewDataControl data_control(this);
            data_control.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            return;
        }
        else if(str==tr("用户权限") && parentStr == tr("主机管理"))
        {
            NewUserRight user_right(this);
            user_right.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            return;
        }
 //       else if(str==tr("连接设置") )
//        {
//             NewPLCCtrl plc_control(this);
//             plc_control.exec();
//             pwnd->is_Save=false;
//             pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
//             return;
//        }
        else if(str==tr("打印机") && parentStr == tr("主机外设"))
        {
            NewPrinter printer(this);
            printer.exec();
            pwnd->is_Save=false;
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            is_NeedCompiled = true;
            //QMessageBox::about(this, tr("打印机"), tr("暂时不支持打印功能"));
            return;
        }
        else if(str==tr("下载设置") && parentStr == tr("组态工程"))
        {
            NewDownload downLoad(this);
            downLoad.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            return;
        }
        else if(str==tr("时钟设置") && parentStr == tr("组态工程"))
        {
            QTreeCtrlTimeDlg timedlg(this);
            timedlg.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            return;
        }
        else if(str==tr("访问加密")&& parentStr == tr("组态工程"))
        {
            NewEncryAccess encry_access(this);
            encry_access.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            return;
        }
        else if(str==tr("掉电存储区设置")&& parentStr == tr("组态工程"))
        {
            PowerProtectDlg dlg;
            dlg.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            return;
        }
        else if(str==tr("产品授权") && parentStr == tr("组态工程"))
        {
            NewProRight product_right(this);
            product_right.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            return;
        }
        else if(str==tr("语言设置") && parentStr == tr("组态工程"))
        {
            NewLanguage language(this);
            language.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

            //在这里添加工具栏组合框语言选项
            int nLanIndex = qLanguagecmb->currentIndex(); //工具栏上当前语言下标
            if(nLanIndex < 0)
            {
                nLanIndex = 0;
            }
            int num = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();

            //刷新配方数据采集中的多语言信息，元素名称 配方名称 begin
            for(int i = 0; i < m_pSamSysParame->m_qvcRecipe.size(); i++)
            {
                for(int j = 0; j < m_pSamSysParame->m_qvcRecipe.at(i).ElmentName.size(); j++)//元素个数
                {
                    int langcout = m_pSamSysParame->m_qvcRecipe.at(i).ElmentName.at(j).size();//语言个数
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
                for(int j = 0; j < m_pSamSysParame->m_qvcRecipe.at(i).formula.size(); j++)//配方个数
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
            //刷新配方数据采集中的多语言信息，元素名称 配方名称 end

            //在这里向每个包含多语言的控件发送语言改变的消息，调用虚函数改变控件的语言数
            int count = pSceneSheet.size(); //画面总数
            QList<QGraphicsItem *> Items;
            for(int i = 0 ; i < count; i++) //扫描所有画面
            {
                Items = pSceneSheet[i]->items();   //当前页面所有的item
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
        else if(str==tr("资料传输") && parentItem == root)
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
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            return;
        }
        else if(str==tr("变量表") && parentItem == root)
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
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            return;
        }
        else if(str==tr("时间表") && parentItem == root)
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
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            return;
        }

        else if(str==tr("PLC编程") && parentItem == root)
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
                 QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("载入文件 %1 失败，请重新安装软件！").arg(PC_PLC_EXE),
                                 0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
                 box.addButton(tr("确定"),QMessageBox::AcceptRole);
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
//            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            return;
        }
        //数据采集双击事件
        if(parentItem == tree_hisdatalog)
        {            
            tree_openhisdata();
            return;
        }

        //XXXXX
        /*
        if(str==tr("触摸屏")||str==tr("连接")||str==tr("设置") ||str==tr("画面")||str==tr("窗口")||str==tr("历史数据收集器")
          ||str==tr("报警登录")||str==tr("配方"))*/
        if(str==tr("触摸屏") || str==tr("画面") || str==tr("窗口") || str==tr("数据采集")
          || str==tr("报警登录") || str==tr("配方"))
        {
            return;
        }

        /*if(parentItem==copyScreen_Item||parentItem==screen)//当双击的是画面第2级菜单时
        {
            QStringList list=str.split(":");
            pwnd->is_Save=false;
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            nActiveSheetIndex=nFindActiveSheetIndex(str);

            pView->setScene(pSceneSheet[nActiveSheetIndex]);
            pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(list.at(1)));
            return;
        }

        else if(parentItem==window||parentItem==copyWindow_Item)//当双击的是窗口第2级菜单时
        {
            QStringList list=str.split(":");
            pwnd->is_Save=false;
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            nActiveSheetIndex=nFindActiveSheetIndex(str);


            pView->setScene(pSceneSheet[nActiveSheetIndex]);
            pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(list.at(1)));
            return;
        }
        else if(parentItem == TreeKeyboard||parentItem == copyUserKeyboard)//自定义菜单
        {
            QStringList list=str.split(":");
            pwnd->is_Save=false;
            pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            nActiveSheetIndex=nFindActiveSheetIndex(str);//把双击的序号赋值到当前的序号中
            pView->setScene(pSceneSheet[nActiveSheetIndex]);//设置当前场景
            pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(list.at(1)));
        }
        else */if(parentItem == alarmlog)//双击报警登录的某一条
        {
            digitAlarm_open();
        }
//        else if(parentItem == tree_macro)//双击脚本
//        {

//        }
        else if(parentItem == link)//双击连接的某一条
        {
                openLink(str);
        }
        else if (parentItem && parentItem->parent() == link)
        {
                openProtocol(parentStr,str);
        }
        else if(str == tr("全局脚本") && parentStr == tr("脚本"))
        {
            globalScriptDlg dlg(this);
            dlg.exec();
            pwnd->is_Save=false;
            is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);
        }
        else if(str == tr("初始化脚本") && parentStr == tr("脚本"))
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
//双击打开连接设置
void MainWindow::openLink(QString name)
{
    bool bExist = false;
    int i;
    for ( i =0; i<m_pSamSysParame->m_qvcConnect.size(); i++)
    {
        if (m_pSamSysParame->m_qvcConnect[i].sConnectName == name
            || name == tr("以太网") || name == tr("网络") || name == tr("CAN总线"))//语言翻译后判断
            //|| name == tr("Ethernet") || name == tr("CAN Bus"))//语言翻译后判断
        {
            bExist = true;
            if(name == tr("以太网")|| name == tr("网络"))
            {
                i = 3;
            }
            else if(name == tr("CAN总线"))
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
        //修改PLC连接
        m_pSamSysParame->m_qvcConnect.replace(i,plc_control.m_Connect);
        tree->currentItem()->setText(0,plc_control.m_Connect.sConnectName);
        pwnd->is_Save=false;
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
    }
}

//增加协议
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
    else if(strText == tr("以太网") || strText == tr("网络"))
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
        if(1 == m_pSamSysParame->m_qvcConnect[i].vProtocols.size())//增加一个协议，且该协议是第一个
        {
            setDefaultPlc(i);
        }
    }

    pwnd->is_Save=false;
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
}

//删除协议
void MainWindow::delProtocol()
{
    QTreeWidgetItem *parentItem=tree->currentItem()->parent();
    if(!parentItem || parentItem->text(0).isEmpty())
        return;

    //QMessageBox::about(this, tr("警告"), tr("不能没有制造商"));
    //return 0;
    QMessageBox box(QMessageBox::Information,tr("提示"),tr("是否确定删除协议"),QMessageBox::Ok|QMessageBox::No,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.button(QMessageBox::Ok)->setText(tr("是"));
    box.button(QMessageBox::No)->setText(tr("否"));
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
    //删除协议
    if(bExist)
    {
        parentItem->removeChild(cItem);
        m_pSamSysParame->m_qvcConnect[i].vProtocols.remove(j);
        if(0 == j)//删除的是第一个协议，则刷新串口信息
        {
            setDefaultPlc(i);
        }
    }
}

//双击打开连接协议
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
    //修改协议
    if(bExist)
    {
        strOldProtocal = m_pSamSysParame->m_qvcConnect[i].vProtocols.at(j).sName;
        bool bEthnet   = (m_pSamSysParame->m_qvcConnect[i].eConnectPort == 3 || m_pSamSysParame->m_qvcConnect[i].eConnectPort == 4);
        int iProType = PRO_SERIAL;
        if(parentName == tr("Com1") || parentName == tr("Com2") || parentName == tr("Com3"))
        {
            iProType = PRO_SERIAL;
        }
        else if(parentName == tr("以太网") || parentName == tr("网络"))
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

            if(strNewProtocal != strOldProtocal)//需要更新所有用到这个协议的地址
            {
                pwnd->vAddrMsg.clear();
                pwnd->OnFillAddressMsgClass();//填充地址信息
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
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
}
/************************************************************************
  *Functions:添加用户自定义键盘
  ************************************************************************
  *Value：
  *无
  ************************************************************************
  *returns:
  *无
  ************************************************************************
  *Edit time：2011.6.7
  *Edit by    ：zhy
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
    msg.addButton(tr("确定"),QMessageBox::AcceptRole);
    QFile file("userkeyboard.dat");
    if(!file.open(QIODevice::ReadOnly))
    {
        msg.setText(tr("userkeyboard.dat未找到！无法载入键盘！"));
        msg.exec();
        return ;//返回参数不对，应该重新设置出错返回参数
    }

    dockTabWidget->setCurrentIndex(1);//进入画面页面

    userkeyboarddlg=new QUserKeyboard(this);
    int res=userkeyboarddlg->exec();
    delete userkeyboarddlg;
    userkeyboarddlg=NULL;
    if(res==QDialog::Accepted)
    {
        pwnd->is_Save=false;
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

        pView->setScene(pSceneSheet[nActiveSheetIndex]);
        upDatetreeScreenItem();
        sTmp=pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(1);

        updateChScreen();
        //list_style
        //if(pwnd->list_style->currentIndex()==0||pwnd->list_style->currentIndex()==1)//标准、元件列表
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
        /*else//预览列表
        {
           pwnd->tree->setCurrentItem(pwnd->newScreen[pwnd->nActiveSheetIndex],0,QItemSelectionModel::SelectCurrent);
           pwnd->tree->setFocus(Qt::MouseFocusReason);
           //PreviewWindow();
           tree->collapseAll();
           tree->expandAll();
        }*/
    }
}

//树控件的右键菜单事件
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
            if(str == tr("画面"))
            {
                showMenu();
            }

            if(parentItem == copyScreen_Item || parentItem == screen)//当点击的是画面第一级菜单时
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

            if(str == tr("窗口"))
            {
                showWindowMenu();
                pwnd->is_Save=false;
                is_NeedCompiled = true;
                pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            }

            if(parentItem == copyWindow_Item || parentItem == window)//当点击的是窗口第一级菜单时
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

            if(str == tr("自定义键盘"))
            {
                showUserKeyboardAddnew();//右键添加自定义键盘

            }

            if(parentItem==TreeKeyboard || parentItem == copyUserKeyboard)//用户自定义键盘
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
                pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
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
    //修改协议
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
        else if(parentName == tr("以太网") || parentName == tr("网络"))
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

            if(strNewProtocal != strOldProtocal)//需要更新所有用到这个协议的地址
            {
                pwnd->vAddrMsg.clear();
                pwnd->OnFillAddressMsgClass();//填充地址信息
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
    QAction *protocal_open  = menu.addAction(tr("打开"));
    connect(protocal_open,SIGNAL(triggered()),SLOT(openCurProtocol()));
#ifndef AKPLC
    QAction *protocal_delete= menu.addAction(tr("删除"));
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
        if(str == tr("触摸屏"))
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
            if(strParent == tr("Com1") || strParent == tr("Com2") || strParent == tr("Com3") || strParent == tr("以太网")|| strParent == tr("网络") || strParent == tr("CAN总线"))
            {
                showDelMenu();
            }
            /*if(str==tr("画面"))
            {
                showMenu();
            }
            if(parentItem==copyScreen_Item||parentItem==screen)//当点击的是画面第一级菜单时
            {
                nActiveSheetIndex=pwnd->nFindActiveSheetIndex(str);
                pView->setScene(pSceneSheet[nActiveSheetIndex]);
                pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                                     arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneTypeProp.sNewScreenName));
                showScreenMenu();
            }
            if(str==tr("窗口"))
            {
                showWindowMenu();
                pwnd->is_Save=false;
                pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            }
            if(parentItem==copyWindow_Item||parentItem==window)//当点击的是窗口第一级菜单时
            {
                nActiveSheetIndex=pwnd->nFindActiveSheetIndex(str);
                pView->setScene(pSceneSheet[nActiveSheetIndex]);
                pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                                     arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneTypeProp.sNewScreenName));
                showWindowSubMenu();
            }
            if(str==tr("自定义键盘"))
            {
                showUserKeyboardAddnew();//右键添加自定义键盘
                pwnd->is_Save=false;
                pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            }
            if(parentItem==TreeKeyboard||parentItem == copyUserKeyboard)//用户自定义键盘
            {
                nActiveSheetIndex=this->nFindActiveSheetIndex(str);
                pView->setScene(pSceneSheet[nActiveSheetIndex]);
                pwnd->setWindowTitle(QString(VERSION_NAME"--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                                     arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneTypeProp.sNewScreenName));
                showUserKeyboard();
                pwnd->is_Save=false;
                pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            }*/
            if(str==tr("报警登录"))
            {
                showAlarmMenu();
            }
            if(parentItem==pwnd->alarmlog) //数位报警区
            {
                qDebug() << "indexOfChild" << parentItem->indexOfChild(tree->currentItem());
                showDigitalAlarmMenu();
            }            
            if(str==tr("配方") && parentItem == root)
            {
                //if(!m_pSamSysParame->m_recipeProp.bRecipeExist)//保障配方子菜单只有一个
                {
                    showRecipeMenu();//添配方菜单
                }
//                else
//                {
//                    QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("已经存在一个配方，请删除在重新建立"),
//                                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
//                    box.addButton(tr("确定"),QMessageBox::AcceptRole);
//                    box.exec();
//                }
            }
            
            /*if(str==tr("连接设置"))
            {
                ShowComLink();
                pwnd->is_Save=false;
                pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            }*/
            if(parentItem == pwnd->link)//连接子项右键菜单
            {
                ShowlinkProperty();
                pwnd->is_Save=false;
                is_NeedCompiled = true;
                pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            }
            if(parentItem == pwnd->recipe)
            {
                showSubRecipeMenu();//添加配方1菜单
                pwnd->is_Save=false;
                is_NeedCompiled = true;
                pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            }
            if(str == tr("数据采集"))
            {
                AddHisDataMenu();
            }
            if(str == tr("脚本"))
            {
                showMacroMenu();
                return;
            }
            if (parentItem && parentItem->text(0) == tr("数据采集"))
            {
                ShowSubHisdataMenu();
            }
        }
    }
}//
/************************************************************************
  *Functions:弹出选中的连接的右键菜单如com1 com2
  ************************************************************************
  *Value：
  *无
  ************************************************************************
  *returns:
  *生成菜单：删除、打开属性两个选项
  ************************************************************************
  *Edit time：2011.7.25
  *Edit by    ：zhy
  *************************************************************************/
//XXXXX

void MainWindow::ShowlinkProperty()
{
    QMenu menu(tree);
    //QAction *tree_Deletelink= menu.addAction(tr("删除"));
    QAction *tree_linkproperty= menu.addAction(tr("打开"));

    // menu.exec(ui.treeWidget->mapToGlobal(pos));
    //connect(tree_Deletelink,SIGNAL(triggered()),SLOT(tree_deleteLink()));
    connect(tree_linkproperty,SIGNAL(triggered()),SLOT(tree_Linkproperty()));

#ifndef AKPLC
    QAction *tree_procotol= menu.addAction(tr("增加协议"));
    connect(tree_procotol,SIGNAL(triggered()),SLOT(addProtocol()));
#endif
    menu.exec(QCursor::pos());

}
void MainWindow::tree_deleteLink()//删除连接
{
//     QString sLinkName=tree->currentItem()->text(0);
//     for(int i=0;i<link->childCount();i++)//遍历连接名称 找到想对应的位置
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
//                     this->nSimulatorport.remove(i);//删除模拟运行时候记录的使用的哪个链接口
//                 }
//             }
//             break;
//         }
//     }

}
void MainWindow::tree_Linkproperty()//打开连接属性
{
    QString str = tree->currentItem()->text(0);
    openLink(str);

    pwnd->is_Save=false;
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
}

/************************************************************************
  *Functions:弹出用户自定义键盘右键菜单
  ************************************************************************
  *Value：
  *无
  ************************************************************************
  *returns:
  *生成菜单：删除、属性两个选项
  ************************************************************************
  *Edit time：2011.6.13
  *Edit by    ：zhy
  *************************************************************************/
void MainWindow::showUserKeyboard()
{
    /*QMenu menu(tree);
    QAction *tree_Deleteuserkeyboard= menu.addAction(tr("删除键盘"));
    QAction *tree_userkeyboardproperty= menu.addAction(tr("属性"));
    // menu.exec(ui.treeWidget->mapToGlobal(pos));
    connect(tree_Deleteuserkeyboard,SIGNAL(triggered()),SLOT(tree_deleteuserKeyboard()));
    connect(tree_userkeyboardproperty,SIGNAL(triggered()),SLOT(tree_UserKeyboardproperty()));
    menu.exec(QCursor::pos());*/

    QMenu menu(tree0);
    QAction *tree_Deleteuserkeyboard= menu.addAction(tr("删除(&D)"));
    QAction *tree_userkeyboardproperty= menu.addAction(tr("属性(&P)"));
    // menu.exec(ui.treeWidget->mapToGlobal(pos));
    connect(tree_Deleteuserkeyboard,SIGNAL(triggered()),SLOT(tree_deleteuserKeyboard()));
    connect(tree_userkeyboardproperty,SIGNAL(triggered()),SLOT(tree_UserKeyboardproperty()));
    menu.exec(QCursor::pos());
}
/************************************************************************
  *Functions:弹出用户自定义键盘右键新建菜单
  ************************************************************************
  *Value：
  *无
  ************************************************************************
  *returns:
  *生成菜单：新建选项
  ************************************************************************
  *Edit time：2011.6.13
  *Edit by    ：zhy
  *************************************************************************/
void MainWindow::showUserKeyboardAddnew()
{
    /*QMenu menu(tree);
    QAction *tree_newUserKeyboard= menu.addAction(tr("添加键盘"));
    connect(tree_newUserKeyboard,SIGNAL(triggered()),SLOT(tree_newuserkeyboard()));
    menu.exec(QCursor::pos());*/
    QMenu menu(tree0);
    QAction *tree_newUserKeyboard= menu.addAction(tr("添加键盘"));
    connect(tree_newUserKeyboard,SIGNAL(triggered()),SLOT(tree_newuserkeyboard()));
    menu.exec(QCursor::pos());
}

/************************************************************************
  *Functions:执行删除自定义键盘的命名
  ************************************************************************
  *Value：
  *无
  ************************************************************************
  *returns:
  *删除某个选择的键盘
  ************************************************************************
  *Edit time：2011.6.13
  *Edit by    ：zhy
  *************************************************************************/

void MainWindow::tree_deleteuserKeyboard()
{
    QMessageBox box(QMessageBox::Information,tr("提示"),tr("是否确定删除该键盘?"),QMessageBox::Ok|QMessageBox::No,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.button(QMessageBox::Ok)->setText(tr("是"));
    box.button(QMessageBox::No)->setText(tr("否"));
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

    TreeKeyboard->removeChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);//删除树控件点击的子菜单
    pwnd->pSceneSheet.remove(pwnd->nActiveSheetIndex);//删除键盘
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
                            //自定义键盘不存在
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

    int totalSceneNum = pSceneSheet.size();//取总数
    for(int i=pwnd->nActiveSheetIndex;i<totalSceneNum;i++)
    {
        pwnd->newScreen[i]=pwnd->newScreen[i+1];
        QTreeWidgetItem *parentItem=pwnd->newScreen[i+1]->parent();//取后一个父类型
        if((parentItem==pwnd->TreeKeyboard)||(parentItem==pwnd->copyUserKeyboard))
        {//若为自定义键盘的话
            stotal=pwnd->newScreen[i]->text(0).split(":").at(0);
            nTmp=stotal.toInt()-1;
            stotal=QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
            str=stotal+":"+pwnd->newScreen[i]->text(0).split(":").at(1);
            pwnd->newScreen[i]->setText(0,str);
        }
    }

    if(TreeKeyboard->childCount()<1)//当所有的用户自定义键盘都被删除时
    {
        TreeKeyboard->setHidden(true);//隐藏树形控件的自定义键盘项
    }


    //pwnd->PreviewWindow();
    if(!pwnd->label.isEmpty() && pwnd->nActiveSheetIndex < pwnd->label.size())
        pwnd->label.remove(pwnd->nActiveSheetIndex );
    if(!pwnd->titlelabel.isEmpty() && pwnd->nActiveSheetIndex < pwnd->titlelabel.size())
        pwnd->titlelabel.remove(pwnd->nActiveSheetIndex );
    if(!pwnd->priviewWidget.isEmpty() && pwnd->nActiveSheetIndex < pwnd->priviewWidget.size())
        pwnd->priviewWidget.remove(pwnd->nActiveSheetIndex );
    DealWithDeleteScreen();//处理删除画面窗口自定义键盘的时候树形控件刷新问题

    upDatetreeScreenItem();

    updateChScreen();

    undoStack->push(new DeleteKeyBoardCommand(pSceneTemp, iActiveSheetIndex, iTreeIndex, strNum));
}
/*****************************************
 *当删除自定义键盘的时候处理所有画面上的画面按钮和多功能按钮的画面跳转
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
    int    nActiveindex=newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(0).toInt();//取属性控件当前选中的
    for(int i=0;i<totalSceneNum;i++)
    {
        if(pSceneSheet[i]->nIsSceneOrWindow==2)//自定义键盘的时候
        {
            continue;
        }
        Items = pSceneSheet[i]->items();   //当前页面所有的item
        for(int j = 0; j < Items.size(); j++)
        {
            sList = Items.at(j)->data(GROUP_DATALIST_KEY).toStringList(); //取出每个item的所有数据
            if(sList.size() < 20)
                continue;//break;
            sName = sList.at(19);
            if(sName.mid(0,2) == "SB")//画面按钮
            {
                nIndex=sList.at(48).toInt();
                if(nIndex<nActiveindex)
                {
                    continue;
                }
                else if(nIndex==nActiveindex)
                {
                    sTmp.setNum(0);//逻辑地址
                    sList.replace(48,sTmp);
                    int i=pwnd->GetFristScreenID(1);
                    sList.replace(56,pwnd->pSceneSheet[i]->sNewScreenName);//更改名称
                    Items[j]->setData(GROUP_DATALIST_KEY,sList);
                }
                else if(nIndex>nActiveindex)
                {
                    sTmp.setNum(nIndex-1);
                    sList.replace(48,sTmp);
                    Items[j]->setData(GROUP_DATALIST_KEY,sList);
                }
            }
            else if(sName.mid(0,2) == "MF")//功能按钮
            {
                int nCount=sList[120].toInt();
                for(int i=0;i<nCount;i++)
                {
                    int iType = sList[80+21+2*i].toInt(); //功能标识

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
                                sList.replace(94,pwnd->pSceneSheet[i]->sNewScreenName);//更改名称

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
  *主界面树形控件的鼠标右击事件
  *************************************************************************/
void MainWindow::showMenu()//出现新建画面右键菜单
{
    /*QPoint pos;
    QMenu menu(tree);
    QAction *tree_newscreen= menu.addAction(tr("新建画面"));
    // menu.exec(ui.treeWidget->mapToGlobal(pos));
    connect(tree_newscreen,SIGNAL(triggered()),SLOT(tree_newscreen()));
    menu.exec(QCursor::pos());*/
    //QPoint pos;
    QMenu menu(tree0);
    QAction *tree_newscreen= menu.addAction(tr("新建画面"));
    //menu.exec(ui.treeWidget->mapToGlobal(pos));
    connect(tree_newscreen,SIGNAL(triggered()),SLOT(tree_newscreen()));
    menu.exec(QCursor::pos());
}//

//XXXXX

void MainWindow::ShowComLink()//出现添加连接右键菜单
{
    QPoint pos;
    QMenu menu(tree);
    QAction *tree_newLink= menu.addAction(tr("添加连接"));
    QAction *tree_deleteLink= menu.addAction(tr("删除全部链接"));
    // menu.exec(ui.treeWidget->mapToGlobal(pos));
    connect(tree_newLink,SIGNAL(triggered()),SLOT(tree_newcom()));
    connect(tree_deleteLink,SIGNAL(triggered()),SLOT(tree_deleteAllLink()));
    menu.exec(QCursor::pos());
}//
void MainWindow::tree_deleteAllLink()//删除连接操作
{
    if(m_pSamSysParame->m_qvcPlcCommunicate.size()>0)
    {
         m_pSamSysParame->m_qvcPlcCommunicate.clear();
    }
    if(pwnd->vTreeLinkType.size()>0)//删除所有连接
    {
        pwnd->vTreeLinkType.clear();
    }
    pwnd->link->takeChildren();//删除树形控件上所有链接

}
void MainWindow::tree_newcom()//添加连接操作
{
    //完成对新加的数据的初始化
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
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
    }
}

void MainWindow::showScreenMenu()//出现新建画面第二级右键菜单
{
    /*QPoint pos;
    QMenu menu(tree);
    QAction *newscreen_open= menu.addAction(tr("打开(&O)"));
    QAction *newscreen_delete= menu.addAction(tr("删除(&D)"));
    QAction *newscreen_property= menu.addAction(tr("属性(&P)"));
    QAction *newscreen_copy= menu.addAction(tr("复制(&C)"));

    connect(newscreen_open,SIGNAL(triggered()),SLOT(newscreen_open()));
    connect(newscreen_delete,SIGNAL(triggered()),SLOT(newscreen_delete()));
    connect(newscreen_property,SIGNAL(triggered()),SLOT(newscreen_property()));
    connect(newscreen_copy,SIGNAL(triggered()),SLOT(newscreen_copy()));
    menu.exec(QCursor::pos());*/
    QMenu menu(tree0);
    QAction *newscreen_open= menu.addAction(tr("打开(&O)"));
    QAction *newscreen_delete= menu.addAction(tr("删除(&D)"));
    QAction *newscreen_property= menu.addAction(tr("属性(&P)"));
    QAction *newscreen_copy= menu.addAction(tr("复制(&C)"));

    connect(newscreen_open,SIGNAL(triggered()),SLOT(newscreen_open()));
    connect(newscreen_delete,SIGNAL(triggered()),SLOT(newscreen_delete()));
    connect(newscreen_property,SIGNAL(triggered()),SLOT(newscreen_property()));
    connect(newscreen_copy,SIGNAL(triggered()),SLOT(newscreen_copy()));
    menu.exec(QCursor::pos());
}//

void MainWindow::showWindowMenu()//出现新建窗口右键菜单
{
    /*QPoint pos;
    QMenu menu(tree);
    QAction *tree_newWindow= menu.addAction(tr("新建窗口"));
    connect(tree_newWindow,SIGNAL(triggered()),SLOT(tree_newWindow()));
    menu.exec(QCursor::pos());*/
    QMenu menu(tree0);
    QAction *tree_newWindow= menu.addAction(tr("新建窗口"));
    connect(tree_newWindow,SIGNAL(triggered()),SLOT(tree_newWindow()));
    menu.exec(QCursor::pos());
}//

void MainWindow::showWindowSubMenu()//出现新建窗口右键第二级菜单
{
    /*QPoint pos;
    QMenu menu(tree);
    QAction *newswindow_open= menu.addAction(tr("打开(&O)"));
    QAction *newswindow_delete= menu.addAction(tr("删除(&D)"));
    QAction *newswindow_property= menu.addAction(tr("属性(&P)"));
    QAction *newswindow_copy= menu.addAction(tr("复制(&C)"));
    connect(newswindow_open,SIGNAL(triggered()),SLOT(newswindow_open()));
    connect(newswindow_delete,SIGNAL(triggered()),SLOT(newswindow_delete()));
    connect(newswindow_property,SIGNAL(triggered()),SLOT(newswindow_property()));
    connect(newswindow_copy,SIGNAL(triggered()),SLOT(newswindow_copy()));
    menu.exec(QCursor::pos());*/
    QMenu menu(tree0);
    QAction *newswindow_open= menu.addAction(tr("打开(&O)"));
    QAction *newswindow_delete= menu.addAction(tr("删除(&D)"));
    QAction *newswindow_property= menu.addAction(tr("属性(&P)"));
    QAction *newswindow_copy= menu.addAction(tr("复制(&C)"));
    connect(newswindow_open,SIGNAL(triggered()),SLOT(newswindow_open()));
    connect(newswindow_delete,SIGNAL(triggered()),SLOT(newswindow_delete()));
    connect(newswindow_property,SIGNAL(triggered()),SLOT(newswindow_property()));
    connect(newswindow_copy,SIGNAL(triggered()),SLOT(newswindow_copy()));
    menu.exec(QCursor::pos());
}//

void MainWindow::showMacroMenu()//宏指令菜单
{
    QPoint pos;
    QMenu menu(tree);
    QAction *openJML= menu.addAction(tr("添加脚本库"));
    QAction *openJRL= menu.addAction(tr("添加函数库"));
    QAction *openMacroExplorer= menu.addAction(tr("打开脚本浏览器"));
    //QAction *EditMacro= menu.addAction(tr("编辑库"));
    connect(openJML,SIGNAL(triggered()),SLOT(slotAddJML()));
    connect(openJRL,SIGNAL(triggered()),SLOT(slotAddJRL()));
    connect(openMacroExplorer,SIGNAL(triggered()),SLOT(slotOpenMacro()));
    //connect(EditMacro,SIGNAL(triggered()),SLOT(slotOpenMacro()));
    menu.exec(QCursor::pos());
}//

//脚本处理相关函数
void MainWindow::slotAddJML()//添加脚本库
{
    Macro lib;
    AddLib addWzrd(macros,this);
    addWzrd.setWindowTitle(tr("添加脚本"));
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
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
    }
}

void MainWindow::slotAddJRL()//添加函数库
{
    Macro lib;
    AddLib addWzrd(macros,this);
    addWzrd.setWindowTitle(tr("添加函数库"));
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
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
    }
}

void MainWindow::slotOpenMacro()//编辑脚本库
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
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
}

void MainWindow::dockWidgetClose(int iData)
{
    switch(iData)
    {
    case PROJECT_MANAGE: //工程管理器
        ui->action_42->setChecked(false);
        break;
    case INFORMATION_OUTPUT: //信息输出窗口
        ui->action_41->setChecked(false);
        break;
    case TOOL_BUTTON://工具箱
        ui->action_tool->setChecked(false);
        break;
    default:
        break;
    }
}

//czq
//历史数据收集器相关处理——//实现右键菜单
void MainWindow::AddHisDataMenu()//实现右键菜单
{
    QMenu   menu(tree);
    QAction *tree_HisDataLogger = menu.addAction(tr("添加数据采集"));

    if(m_pSamSysParame->m_loadDataSampling.size() < 64)
    {
        connect(tree_HisDataLogger,SIGNAL(triggered()),SLOT(tree_addhisdatalogger()));
        menu.exec(QCursor::pos());
    }
    else
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("数据采集已达上限"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
    }
    //----------------------------old----------------------------
    /*//QPoint pos;
    QMenu menu(tree);
    QAction *tree_HisDataLogger= menu.addAction(tr("添加历史数据收集器"));
    if(!m_pSamSysParame->m_historyLogData.bHistoryDataExist)
    {
        connect(tree_HisDataLogger,SIGNAL(triggered()),SLOT(tree_addhisdatalogger()));
        menu.exec(QCursor::pos());
    }
    else
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("历史数据收集器已经存在，请删除之后再新建！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
    }*/
}

//czq
//历史数据收集器相关处理——添加历史数据收集器
void MainWindow::tree_addhisdatalogger()//添加子项
{  
    if(isCompiled)
    {
        return;
    }
    dockTabWidget->setCurrentIndex(0);//恢复到系统参数页面

    IintHisData();//此时已经push_back

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
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

    }
    else//把push_back的吐出来
    {
        m_pSamSysParame->m_loadDataSampling.pop_back();
		m_pSamSysParame->m_vecDataSamplingStr.pop_back();
        m_curDataLog = 0;
    }

    //hisdatalog_child->setIcon(0,QIcon(":/tree/images/tree/hisdata.ico"));
    //hisdatalog_child->setHidden(true);

    //现在改成只有这个点击确定以后才能新建数据采集
    //tree_openhisdata();//打开历史数据对话框

    //----------------------------old----------------------------
    /*//hisdatalog=new QHistoryDatalogger;
    m_pSamSysParame->m_historyLogData.bHistoryDataExist = true;
    //hisdatalog_child= new QTreeWidgetItem(QStringList(tr("历史数据收集器0")));
    //tree_hisdatalog->addChild(hisdatalog_child);
    //hisdatalog_child->setIcon(0,QIcon(":/tree/images/tree/hisdata.ico"));
    IintHisData();
    hisdatalog_child->setText(0,m_pSamSysParame->m_historyLogData.sHistoryDataName);
    hisdatalog_child->setHidden(false);
    tree_openhisdata();//打开历史数据对话框
    */
}

//czq
void MainWindow::IintHisData()
{
    DATA_SAMPLING tempDataSampling;

    //tempDataSampling.m_nSampType      = 1;        //实时采集
    tempDataSampling.bContiguousAddr  = false;     //是否是连续的地址
    tempDataSampling.bFullNotic       = false;    //是否取满通知
    tempDataSampling.bAutoReset       = false;    //是否自动复位
    tempDataSampling.bSaveToFile      = false;    //是否保存文件
    tempDataSampling.bAutoSave        = false;
//    tempDataSampling.bZeroSupp        = true;     //是否零抑制
//    tempDataSampling.bZoomIn          = false;    //是否缩放
 //   tempDataSampling.bRound           = true;     //是否四舍五入
    tempDataSampling.bAddrCtlSamp     = false;    //位地址控制是否采样
    //tempDataSampling.bSampTime        = true;     //是否频率采样时间间隔为1秒
    tempDataSampling.nDataLen         = 5;        //数据位数
    tempDataSampling.nDecimalLen      = 0;        //小数长度
    tempDataSampling.nStartHour       = 0;        //开始的时（0-23）
    tempDataSampling.nStartMinute     = 0;        //开始的分（0-60）
    tempDataSampling.nEndHour         = 0;        //结束的时（0-23）
    tempDataSampling.nEndMinute       = 0;        //结束的分（0-60）
//    tempDataSampling.nSampAddrLen     = 0;        //采样总字数(字地址采样长度)
    tempDataSampling.nDigitLen        = 16;       //位长
    tempDataSampling.eSampType        = SampCycle;//采样条件
    tempDataSampling.eDealSampFull    = SFReplace;   //取满处理方式
    tempDataSampling.eSaveMedium      = SM_Udisk; //保存的媒介
    tempDataSampling.eDateShowType    = DateYMD;  //日期格式
//    tempDataSampling.eDataType        = DataInt;  //数据类型

    //tempDataSampling.nTotalSampNum    = 20;       //采样最大总数
    tempDataSampling.nSampTime        = 1;
    tempDataSampling.nSampUnit        = 3;        //采样单位为月，默认一个月

    tempDataSampling.nDataSampType    = 1;        //实时曲线

    tempDataSampling.nSampRate        = 1;        //采样的频率
    tempDataSampling.nSampRateUnit    = 1;        //默认为1秒

    tempDataSampling.nSampTimes       = 1;        //采样次数
    tempDataSampling.nSampCountUnit   = 0;        //采样次数频率。默认为分钟
	tempDataSampling.bDynSampleRate = false;		//是否动态采样频率
	tempDataSampling.bDynTimeRange = false;			//是否动态采样时间范围

//    tempDataSampling.nSourceMin       = 0;        //缩放源数据最小值
//    tempDataSampling.nSourceMax       = 65535;    //缩放源数据最大值
//    tempDataSampling.nTargeMin        = 0;        //缩放目标数据最小值
//    tempDataSampling.nTargeMax        = 65535;    //缩放目标数据最大值
    //tempDataSampling.strNoticAddrId   = initKeyboard;//地址通知的ID号
    //tempDataSampling.strCtlSampAddrId = initKeyboard;//控制采样的地址ID号
    //tempDataSampling.keyAddrBegin     = initKeyboard;//连续地址的时候的起始地址
    tempDataSampling.keyCtlSaveAddr.sShowAddr   = "LW0";//保存文件的控制地址
    tempDataSampling.m_dataTable.clear();         //数据表格

    m_pSamSysParame->m_loadDataSampling.push_back(tempDataSampling);

    //----------------------------old----------------------------
    /*m_pSamSysParame->m_historyLogData.sHistoryDataName =tr("历史数据收集器0");//历史数据名称
    m_pSamSysParame->m_historyLogData.nSampleLen =1;           //取样长度
    m_pSamSysParame->m_historyLogData.nSampleSize =1;           //取样总数
    //数据地址结构体
    m_pSamSysParame->m_historyLogData.nSampleType =0;		//取样方式
    m_pSamSysParame->m_historyLogData.nTimeInterval =1;		//计时取样时间
    m_pSamSysParame->m_historyLogData.nTriggerTime =1;		//整点取样时间
    //Keyboard addr2;                                           //触发取样结构体
    m_pSamSysParame->m_historyLogData.bFullStop =false;		//取满后是否停止
    m_pSamSysParame->m_historyLogData.bFullNotic =false;	//取满后是否通知
    //Keyboard addr3;                                           //取满后通知结构体
    m_pSamSysParame->m_historyLogData.nFullNoticPercent =90;	//通知百分比
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
//历史数据收集器相关处理——添加历史数据收集器子项的操作
void MainWindow::ShowSubHisdataMenu()
{
     QPoint pos;
     QMenu menu_subrecipe(tree);
     QAction *tree_openhisdata= menu_subrecipe.addAction(tr("打开&O"));
     QAction *tree_deletehistata=menu_subrecipe.addAction(tr("删除&D"));
     connect(tree_openhisdata,SIGNAL(triggered()),SLOT(tree_openhisdata()));
     connect(tree_deletehistata,SIGNAL(triggered()),SLOT(tree_deletehisdata()));
     menu_subrecipe.exec(QCursor::pos());
}

void MainWindow::tree_rename()
{
}

//历史数据收集器相关处理——打开历史数据收集器对话框
void MainWindow::tree_openhisdata()
{
    int m_curDataLog = getCurrentSamp();
    if (m_curDataLog < 0 || m_pSamSysParame->m_vecDataSamplingStr.size() <= m_curDataLog
		|| m_pSamSysParame->m_loadDataSampling.size() <= m_curDataLog)
    {
        return;
    }

    QString strOld  = m_pSamSysParame->m_vecDataSamplingStr[m_curDataLog];//当前打开的数据采集的名字
    QString strNew  = strOld;
    int     typeOld = m_pSamSysParame->m_loadDataSampling[m_curDataLog].nDataSampType;
    int     typeNew = typeOld;

    qdataloggerdlg hisdataloggerdialog(m_curDataLog,this);
    if(hisdataloggerdialog.exec() == QDialog::Accepted)
    {
        pwnd->is_Save=false;
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

        if((tree_hisdatalog && tree_hisdatalog->childCount() > m_curDataLog) && (m_pSamSysParame->m_vecDataSamplingStr.size() > m_curDataLog))
        {
            tree_hisdatalog->child(m_curDataLog)->setText(0,m_pSamSysParame->m_vecDataSamplingStr[m_curDataLog]);
        }

        strNew  = m_pSamSysParame->m_vecDataSamplingStr[m_curDataLog];
        typeNew = m_pSamSysParame->m_loadDataSampling[m_curDataLog].nDataSampType;
		
        int count = pSceneSheet.size(); //画面总数
		bool bUseHistory = false;
		bool bUseTrend   = false;
		bool bUseGroup   = false;
        QList<QGraphicsItem *> Items;
        for(int i = 0 ; i < count; i++) //扫描所有画面
        {
            Items = pSceneSheet[i]->items();   //当前页面所有的item
            foreach(QGraphicsItem *pItem, Items)
            {
                if(!pItem)
                {
                    continue;
                }

                if(SAM_DRAW_OBJECT_GROUP == pItem->type())
                {
                    QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
                    if(item && item->GroupType() == SAM_DRAW_GROUP_HISTORYDATE)//假如是历史数据显示器
                    {
                        QHistoryDataShowAttr* hisItem = dynamic_cast<QHistoryDataShowAttr*>(item);
						if( ((typeNew != typeOld) && (strOld == hisItem->sGroupName)) ||//类型改变
							((strOld != strNew) && (strOld == hisItem->sGroupName)) )//名字改变
						{
							bUseHistory = true;
							hisItem->sampChanged(strOld, strNew, typeNew);
						}
						//QMessageBox::about(this, tr("警告"), tr("当前数据采集有对应的历史数据显示器"));
						//hisItem->sampChanged(strOld, strNew, typeNew);
                        /*if((typeNew != typeOld) && (strOld == hisItem->sGroupName))//类型改变
                        {
                            QMessageBox::about(this, tr("警告"), tr("当前数据采集有对应的历史数据显示器"));
                        }
                        if((strOld != strNew) && (strOld == hisItem->sGroupName))//名字改变
                        {
                            hisItem->sGroupName = strNew;
                        }*/
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_TREND)//趋势图
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
                            QMessageBox::about(this, tr("警告"), tr("当前数据采集有对应的趋势图"));
							trendItem->sampChanged(strOld,strNew,typeNew);
                        }*/
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_GROUPDATA)//数据群组
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
                            QMessageBox::about(this, tr("警告"), tr("当前数据采集有对应的数据群组"));
							dataItem->sampChanged(strOld,strNew,typeNew);
                        }*/
                    }
                }
            }
        }

		if(bUseHistory)
		{
			QMessageBox::about(this, tr("警告"), tr("当前数据采集有对应的历史数据显示器"));
		}
		if(bUseTrend)
		{
			QMessageBox::about(this, tr("警告"), tr("当前数据采集有对应的趋势图"));
		}
		if(bUseGroup)
		{
			QMessageBox::about(this, tr("警告"), tr("当前数据采集有对应的数据群组"));
		}
    }
}

//czq
//历史数据收集器相关处理——删除历史数据子项
void MainWindow::tree_deletehisdata()
{
    int m_curDataLog = getCurrentSamp();//当前数据采集号
    QString str = m_pSamSysParame->m_vecDataSamplingStr[m_curDataLog];//要删除的数据采集的名字

    int count       = pSceneSheet.size(); //画面总数
    QList<QGraphicsItem *> Items;
	QList<QItemGroup *>trends;
    for(int i = 0 ; i < count; i++) //扫描所有画面
    {
        Items = pSceneSheet[i]->items();   //当前页面所有的item
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
                    if(item->GroupType() == SAM_DRAW_GROUP_HISTORYDATE)//假如是历史数据显示器
                    {
                        QHistoryDataShowAttr* hisItem = dynamic_cast<QHistoryDataShowAttr*>(item);
                        if(str == hisItem->sGroupName)
                        {
							trends << item;
                        }
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_TREND)//趋势图
                    {
                        QTrendAttr* trendItem = dynamic_cast<QTrendAttr*>(item);
                        if(str == trendItem->m_sGroupNum)
                        {
							trends << item;
                        }
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_GROUPDATA)//数据群组
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
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("当前采样已被引用，是否删除？"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("是"));
        box.button(QMessageBox::No)->setText(tr("否"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::No))
        {
            return;
        }
        else
        {
            foreach(QItemGroup *trend,trends)
            {
                trend->sampChanged(str,"",0);//删除后的刷新，最后参数没有意义
            }
            deletehisdata();
        }
    }
    else
    {
        QMessageBox box(QMessageBox::Information,tr("提示"),tr("是否确定删除该数据采集"),QMessageBox::Ok|QMessageBox::No,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("是"));
        box.button(QMessageBox::No)->setText(tr("否"));
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
  *Functions:删除历史数据的时候清空历史数据内容
  ************************************************************************
  *Value：
  *无
  ************************************************************************
 *returns:
  *无
  ************************************************************************
  *Edit time：2011.8.29
  *Edit by    ：zhy
  *************************************************************************/
void MainWindow::deletehisdata()
{
    //czq
    /*m_pSamSysParame->m_historyLogData.bHistoryDataExist=false;       //历史数据是否存在
    m_pSamSysParame->m_historyLogData.bFullStop=false;               //取满是否停止取样
    m_pSamSysParame->m_historyLogData.bFullNotic=false;              //取满是否通知
    m_pSamSysParame->m_historyLogData.nSampleLen=0;            //取样长度 0-32
    m_pSamSysParame->m_historyLogData.nSampleType=0;           //取样方式,计时，触发，整点
    m_pSamSysParame->m_historyLogData.nFullNoticPercent=0;     //取满通知的百分比 0-100，代表百分之nFullNoticPercent
    m_pSamSysParame->m_historyLogData.nTimeInterval=0;         //计时间隔  秒为单位
    m_pSamSysParame->m_historyLogData.nTriggerTime=0;          //整点触发时间 于多少分钟触发
    m_pSamSysParame->m_historyLogData.nSampleSize=0;           //取样大小
    m_pSamSysParame->m_historyLogData.sHistoryDataName.clear();      //历史数据名称
    m_pSamSysParame->m_historyLogData.mReadAddr=0;            //读取地址
    m_pSamSysParame->m_historyLogData.mTriggerAddr=0;         //触发地址
    m_pSamSysParame->m_historyLogData.mFullNoticAddr=0;       //取满通知地址
    m_pSamSysParame->m_historyLogData.mSampleList.clear();     //取样数据的列表，总大小为nSampleLen*/

    pwnd->is_Save=false;
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

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
*出现报警登陆右键菜单
******************************************************/
void MainWindow::showAlarmMenu()
{
    QPoint pos;
    QMenu menu(tree);
    QAction *alarm_action=menu.addAction(tr("新增报警登录"));

    connect(alarm_action,SIGNAL(triggered()),this,SLOT(tree_digitAlarm()));
    menu.exec(QCursor::pos());

}//

/**********************************************
*点击报警登陆的右键菜单上的新增数位报警登陆
**************************************************/
void MainWindow::tree_digitAlarm()
{
    if(isCompiled)
    {
        return;
    }
    QString str="";
    QString sTmp="";
    //添加数位报警登陆
    if(m_pSamSysParame->m_qvcAlarm.size() >= DIGIT_ALARM_NUM)
    {
        QMessageBox box(this);
        box.setText(QString(tr("报警登录最多为%1个")).arg(DIGIT_ALARM_NUM));
        box.exec();
        return;
    }

    dockTabWidget->setCurrentIndex(0);//切换到第一个页面



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
        temp=QStringList(QString("00%1:").arg(totalSize-1)+tr("数位报警登陆")+QString("%1").arg(digitalSize));;
    }
    else if(totalSize -1 >= 10 && totalSize -1 <=99)
    {
        temp=QStringList(QString("0%1:").arg(totalSize-1)+tr("数位报警登陆")+QString("%1").arg(digitalSize));;
    }
    else if(totalSize -1 >= 100)
    {
        temp=QStringList(QString("%1:").arg(totalSize-1)+tr("数位报警登陆")+QString("%1").arg(digitalSize));;
    }

    digital_treeItem[digitalSize-1]=new QTreeWidgetItem(alarmlog,QStringList(temp));
    digital_treeItem[digitalSize-1]->setIcon(0,QIcon(":/btn/images/balarm.ico"));
    alarmlog->addChild(digital_treeItem[digitalSize-1]);
    */
}//
/****************************************************************************/

/**********************************************************
  *数位报警区的右键打开和删除菜单
  **********************************************************/
void MainWindow::showDigitalAlarmMenu()
{
    QPoint pos;
    QMenu menu(tree);
    QAction *digitAlarm_open=menu.addAction(tr("打开"));
    QAction *digitAlarm_delete=menu.addAction(tr("删除"));

    connect(digitAlarm_open,SIGNAL(triggered()),this,SLOT(digitAlarm_open()));
    connect(digitAlarm_delete,SIGNAL(triggered()),this,SLOT(digitAlarm_delete()));
    menu.exec(QCursor::pos());

}//



/**************************************************
报警右键删除事件
******************************************************/
void MainWindow::digitAlarm_delete()//点击报警登陆的右键菜单上的删除
{
    QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("是否删除所选报警？"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.button(QMessageBox::Ok)->setText(tr("是"));
    box.button(QMessageBox::No)->setText(tr("否"));
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
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
}//

/**************************************************
*数位报警1-10右键打开事件
******************************************************/
void MainWindow::digitAlarm_open()//点击数位报警登陆的右键菜单上的打开
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
                pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
            }
            alarmDlg->deleteLater();
            alarmDlg = NULL;
            break;
        }
        index++;
    }

}//

void MainWindow::showRecipeMenu()//出现添加配方右键菜单
{
    QPoint pos;
    QMenu menu_recipe(tree);
    pwnd->m_pSamSysParame->m_qRecipe.formula.clear();
    pwnd->m_pSamSysParame->m_qRecipe.sName = "";
    QAction *tree_recipe= menu_recipe.addAction(tr("添加配方"));
    connect(tree_recipe,SIGNAL(triggered()),SLOT(tree_recipe()));
    menu_recipe.exec(QCursor::pos());
}//ok

void MainWindow::showSubRecipeMenu()//添加配方1的右键菜单
{
    QPoint pos;
    QMenu menu_subrecipe(tree);
    QAction *tree_openrecipe= menu_subrecipe.addAction(tr("打开&O"));
    QAction *tree_deleterecipe=menu_subrecipe.addAction(tr("删除&D"));
    connect(tree_openrecipe,SIGNAL(triggered()),SLOT(tree_openrecipe()));
    connect(tree_deleterecipe,SIGNAL(triggered()),SLOT(tree_deleterecipe()));
    menu_subrecipe.exec(QCursor::pos());
}//ok

//点击树控件上的右键菜单事件响应
void MainWindow::tree_openrecipe()//打开配方对话框
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

                //刷新配方显示器
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
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

    pwnd->m_pSamSysParame->m_qRecipe.formula.clear();
    pwnd->m_pSamSysParame->m_qRecipe.sName = "";
//    QTreeCtrlRecipeDlg recipeDlg(this);
//    recipeDlg.exec();
}//

void MainWindow::tree_deleterecipe()
{
    QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("是否删除所选配方？"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.button(QMessageBox::Ok)->setText(tr("是"));
    box.button(QMessageBox::No)->setText(tr("否"));
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


            //刷新配方显示器
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
                                    if(i == pRicipeItem->GetRicipeGroupId(i))//删除当前第I个配方组，设置于与该配方组对应的配方显示器为无效
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
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

}

void MainWindow::tree_newscreen()
{
    QString sTmp="";
    QString sNo="";
    emit InitScreenDlg();
    newScreenDlg->setWindowTitle(tr("新建画面"));

    int res=newScreenDlg->exec();
    if(res==QDialog::Accepted)
    {
        pwnd->is_Save=false;//
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
        emit  newscreen_Assign();
        upDatetreeScreenItem();//更新画面的子项
        pwnd->reScreenorwindowName(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName,newScreenDlg->ui->newscreen_name_lineedit->text());
        //若名字有更改的话刷新画面按钮的名字
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

void MainWindow::tree_newWindow()//窗口
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
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

        emit  newwindow_Assign();
        upDatetreeScreenItem();//更新画面的子项
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
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

    dockTabWidget->setCurrentIndex(0);//切换到第一个页面

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
//清除原有树形控件
void MainWindow::clearTree()
{
    //连接清空
    QList<QTreeWidgetItem *> childItems = link->takeChildren();
    childItems.clear();
    //画面清空
    QList<QTreeWidgetItem *> huamian = screen->takeChildren();
    huamian.clear();
    //配方清空
    QList<QTreeWidgetItem *> childItem = recipe->takeChildren();
    childItem.clear();
    //报警登陆
    QList<QTreeWidgetItem *> baojingItem = alarmlog->takeChildren();
    baojingItem.clear();
    //数据采集
    QList<QTreeWidgetItem *> shujucaiji = tree_hisdatalog->takeChildren();
    shujucaiji.clear();
    //清空脚本
    //librarys.clear();
}
/*************************************************************************
  *主界面标准工具栏上新建工程鼠标点击槽函数
***************************************************************************/
void MainWindow::createprodlg()
{
    if(isCompiled)
    {
        return ;
    }
    if(!isHave)
    {
        //清除原有树形控件
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
        if(!pwnd->is_Save)//有工程没保存的情况下//已经点击过新建按钮
        {
            QMessageBox box(QMessageBox::Information,tr("提示"),tr("是否保存当前工程"),QMessageBox::Ok|QMessageBox::No|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("是"));
            box.button(QMessageBox::No)->setText(tr("否"));
            box.button(QMessageBox::Cancel)->setText(tr("取消"));
            box.exec();
            if(box.clickedButton()== box.button(QMessageBox::Ok))//当点击了保存当前工程
            {
                //清除原有树形控件
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
                nActiveSheetIndex=0; //当前画面序号，从0开始
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
            else if(box.clickedButton()== box.button(QMessageBox::No))//当点击了否
            {
                //清除原有树形控件
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
            else if(box.clickedButton()== box.button(QMessageBox::Cancel))//当点击了取消
            {
                return;
            }
        }
        else//保存的前提下
        {
            //清除原有树形控件
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
        //新建工程设置默认串口参数
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
    else if(tr("以太网") == newpro->proFlag || newpro->proFlag == tr("网络"))//以太网
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
    else//CAN总线
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
        return;//18键盘 默认取第6个数字键盘， 可更改
    }

    pScene->DrawScreenSize();

    file.close();

    TreeKeyboard->setHidden(false);//显示树形控件

    pSceneSheet.push_back(pScene);//添加自定义键盘画面到容器中
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
    newScreen[nscenecount]->setText(0,stemp+":"+tr("数字键盘")+QString("%1").arg(str.mid(4,1)));
    pSceneSheet[nscenecount]->sNewScreenName=tr("数字键盘")+QString("%1").arg(str.mid(4,1));
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

    //wxy打开新工程删除掉原先的脚本编译文本，避免程序判断错误
    QFile::remove("sdmacro\\ml\\ml.jar");
    is_NeedCompiled = true;
//    mPicPath.clear();
//    mPicMd5.clear();
//    deleteDirectory(QFileInfo("resource"));
}//


/*************************************************************************
  *主界面标准工具栏上打开工程鼠标点击槽函数
***************************************************************************/
void MainWindow::createopenprodlg(QString path)
{
    QString fileName;

    if(!pwnd->is_Is)//工具栏有效的情况下
    {
        if(!pwnd->is_Save)//有工程没保存的情况下
        {
            QMessageBox box(QMessageBox::Information,tr("提示"),tr("是否保存当前工程"),QMessageBox::Ok|QMessageBox::No|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("是"));
            box.button(QMessageBox::No)->setText(tr("否"));
            box.button(QMessageBox::Cancel)->setText(tr("取消"));
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
        else//工程已经保存
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

     if(is_Click_OpenrecentFile)//当点击的是最近打开的Action时
     {
         fileName=sRecentflieName;
         is_OpenrecentFile=true;
         is_Click_OpenrecentFile=false;
     }
     else if(!path.isEmpty())//若路径为空的话 则不是双击工程打开
     {
         fileName=path;
     }
     else
     {
         fileName = QFileDialog::getOpenFileName(this,tr("打开文件"),sFilePath,SUFFIX);//,0,QFileDialog::DontUseNativeDialog);
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
        QMessageBox box(QMessageBox::Information,tr("错误"),tr("打开文件失败！"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("确定"));
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
    picturePath="/home";//图片路径清空
    QDataStream out(&file);

    /*read project version*/
	int versionNum = AK_CURRENT_VERSION;
    QString version ;
    out >> version;
	out >> versionNum;
    setProVersion(versionNum);
    sOpenFileVersion = version;                     //打开文件的版本号

    qDebug() << "project Version "<<versionNum;
	setProVersion(versionNum);
    QString versionStr = tr("AKWorkShop");//不能被改变
    versionStr += "-V1.0.2";
    if(version != versionStr  //版本不一致
		|| versionNum > AK_CURRENT_VERSION)    //当前组态是由较高版本软件创建的 
    {
        QString warning = tr("不是") + SUFFIX + tr("支持的文件格式，或者工程文件已损坏");;
        if(version == versionStr)
            warning == tr("组态是由较新版本软件生成，请升级组态软件到最新版本");
        QMessageBox box(QMessageBox::Information,tr("错误"),warning,QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("确定"));
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
    //从型号读取com口的参数
    {
        qDebug()<< "aaaaaaaaaaaaaaa  " << pwnd->newpro->newprowizard_model;
        qDebug()<< "aaaaaaaaaaaaaaa  " << pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelName;
        QFile file("modle.dat");//打开文件，该文件存储的是HMI型号的相关信息
        QString dataindex="#"+pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelName;

        QString line;//临时变量，存储从文件取出的一行数据
        QTextStream stream(&file);//定义操作文件的变量

        if (file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            while(!stream.atEnd())
            {
                line=stream.readLine();//文件第一行存储的是型号的个数
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
                if(sFactoryName == pl.sFactoryName)//厂家名称相同
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
                            else if(strConnectName == tr("以太网") || strConnectName == tr("网络"))
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
        QMessageBox::warning(this,tr("打开工程出错"),tr("请检查工程版本是否相符！"));
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
        QMessageBox::warning(this,tr("打开工程出错"),tr("请检查工程版本是否相符！"));
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
    
    //脚本
    qDebug() << "loadLibrary start" ;
    this->loadLibrary(out);//读取脚本
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
            //QMessageBox::about(this, tr("警告"), tr("输入密码错误"));
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

    //if(m_pSamSysParame->m_fileProtect.bNeedFileProtect)//文件保护输入密码 Edit zhy
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
    loadPlcPrj(akpfile,out);//载入PLC工程
#endif

    /*edit by panfacheng*/
    if (sOpenFileVersion != "AKWorkShop-V1.0.0")        //不是1.0.0版本才有这个变量表
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
        //在选中垂直模式的时候 宽度和高度都改变过 不必通过判断垂直水平模式设大小
     }

    //pView->setSceneRect(-1,-1,m_pSamSysParame->m_projectProp.nSceneWidth,m_pSamSysParame->m_projectProp.nSceneHeight+100);

    //nActiveSheetIndex = m_pSamSysParame->m_projectProp.nStartScreenIndex;

    if(pSceneSheet.isEmpty()) return ;
    nActiveSheetIndex = 0;
    pView->setSceneRect(0,0,1366,768);
    pView->setScene(pSceneSheet[nActiveSheetIndex]);

    pView->setDragMode(QGraphicsView::RubberBandDrag);//把单选改变给拖动模式
    pView->setMouseTracking(true); // 设置鼠标移动捕捉
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
    pwnd->ui->action_save->setDisabled(true);//当打开工程时改变保存按钮的颜色
    openPro_reTreeCtl();//打开工程时刷新树形控件
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
    pwnd->is_Save=true;// 画面改变 同时来改变保存按钮的颜色
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

    //遍历所有控件
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
    ui->action_41->setChecked(false); //add by wxy菜单项相应的更新
    m_toolDock->setVisible(true);
    ui->action_tool->setChecked(true);
    setProVersion(AK_CURRENT_VERSION);//打开工程后更改当前版本号

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
    //wxy打开新工程删除掉原先的脚本编译文本，避免程序判断错误
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


//保存组态数据到文件
//sFileName：要保存的文件名（包含路径）
//type：1--保存组态工程使用 0--编译使用
void MainWindow::SaveProjectToFile(QString sFileName,int type)
{
    QFile file;
    file.setFileName(sFileName);
    QString version = tr("AKWorkShop");//不能被改变
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
        QMessageBox::warning(this,tr("保存文件出错"),tr("请检查路径是否正确或者规范"));
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
        QMessageBox::warning(this,tr(""),tr("保存工程出错"));
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
    
    this->saveLibrary(in);//保存脚本

    //in << mPicPath;//存图片map
    qDebug()<< "mSceneIndex--"<<mSceneIndex;

    in << type;

    in << newpro;           //save class QNewPro data

    //int digitalSize = this->m_pSamSysParame->m_qvcAlarm.size();


    /*edit by latory*/
    in << mSceneIndex;
#ifdef AKPLC
    savePlcPrj(in);//存入PLC工程
#endif
    if(type)
    {
        is_Save=true;
        ui->action_save->setDisabled(true);
        is_SaveAS=false;
        setCurrentFile(file.fileName());//最近打开的文档
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
  *主界面标准工具栏上保存工程对话框鼠标点击槽函数
***************************************************************************/
void MainWindow::createsavedlg()
{
    /*   QMessageBox box(this);
    box.setText("sagfsdhs");
    box.exec();*/
    checkUserKeyboard();//检测是否有用到用户自定义键盘
    //CheckScreenandMFaction();//检查画面按钮 多功能按钮要跳转的画面是否正确
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

    if(pwnd->m_pSamSysParame->m_loadDataSampling.size() == 0)//没有数据采集
    {
        QMessageBox::information(this, VERSION_NAME, tr("没有建立数据采集"));
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

    //动态矩形
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
  操作记录显示器
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

    if(pwnd->m_pSamSysParame->m_loadDataSampling.size() == 0)//没有数据采集
    {
        QMessageBox::information(this, VERSION_NAME, tr("没有建立数据采集"));
        return;
    }

    //组名
    int temp = m_pSamSysParame->m_loadDataSampling.size();
    int hisSampNum = 0;
    for(int i = 0; i < temp; i++)
    {
        if(2 == m_pSamSysParame->m_loadDataSampling[i].nDataSampType)//曲线为历史数据采集
        {
            if(m_pSamSysParame->m_loadDataSampling[i].m_dataTable.size() != 0)
            {
                hisSampNum++;
            }
        }
    }
    if(0 == hisSampNum)
    {
        QMessageBox::about(this, tr("历史数据显示器"), tr("没有历史数据采集或者历史数据采集为空"));
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


void MainWindow::CreateKeyboardASCII()//键盘组件
{
    //暂时屏蔽用户自定义键盘
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

//对绘图工具栏的控件操作 edit by zqh

void MainWindow::OnDrawRect() //绘制矩形
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

void MainWindow::OnDrawLine() //绘制直线
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

void MainWindow::OnDrawEllipse() //绘制圆
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

void MainWindow::OnDrawPolygon() //绘制多边形
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

void MainWindow::OnDrawFoldLine()//绘制折线
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

void MainWindow::OnDrawFreeLine()//绘制自由直线
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

//对标准工具栏的控件操作 edit by zqh
void MainWindow::OnGroupItem()  //组合操作
{
    if(pwnd->isCompiled)
    {
        return;
    }
    //pSceneSheet[nActiveSheetIndex]->GroupItem(); //已经移到commands.cpp中（redo()）
    if(pSceneSheet[nActiveSheetIndex]->selectedItems().size() > 1)
       undoStack->push(new groupCommand(pSceneSheet[nActiveSheetIndex]));
     ui->action_copym->setDisabled(false);
}

void MainWindow::OnDisGroupItem() //拆分操作
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

void MainWindow::OnDeleteItem()  //删除操作
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

void MainWindow::OnLockItem()    //锁定操作
{
    foreach (QGraphicsItem *item, pSceneSheet[nActiveSheetIndex]->selectedItems())
        item->setFlag(QGraphicsItem::ItemIsMovable, false);
    pSceneSheet[nActiveSheetIndex]->reBondingTrackers();
}

void MainWindow::OnUnLockItem()  //解锁操作
{
    foreach (QGraphicsItem *item, pSceneSheet[nActiveSheetIndex]->selectedItems())
        item->setFlag(QGraphicsItem::ItemIsMovable, true);
    pSceneSheet[nActiveSheetIndex]->reBondingTrackers();
}

void MainWindow::OnSetLeft() //设置图形左对齐
{
	pSceneSheet[nActiveSheetIndex]->OnSetLeftAlign();
}

void MainWindow::OnSetRight() //右对齐
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

	//  pWidget->setFlag(QGraphicsItem::ItemIsMovable, true); //设置组合图形可以移动
	//  pWidget->setFlag(QGraphicsItem::ItemIsSelectable, true); //设置组合图形可选

	// movie->setPaused(false);
}

void MainWindow::OnSetTop() //上对齐
{
	pSceneSheet[nActiveSheetIndex]->OnSetTopAlign();
}

void MainWindow::OnSetButtom() //下对齐
{
	pSceneSheet[nActiveSheetIndex]->OnSetButtomAlign();
}

void MainWindow::OnSetHCenter() //水平居中对齐
{
        pSceneSheet[nActiveSheetIndex]->OnSetVCenterAlign();
}

void MainWindow::OnSetVCenter() //垂直居中对齐
{
        pSceneSheet[nActiveSheetIndex]->OnSetHCenterAlign();
}

void MainWindow::OnSetHSpacingAlign() //水平等间距对齐
{
	pSceneSheet[nActiveSheetIndex]->OnSetHSpacingAlign();
}

void MainWindow::OnSetVSpacingAlign()
{
	pSceneSheet[nActiveSheetIndex]->OnSetVSpacingAlign();
}


void MainWindow::DrawScreenSize()
{
    QString sShowModel = pwnd->newpro->newprowizard_showmodel;  //SA显示模式，是水平还是垂直显示
    QFile file("modle.dat");//打开文件，该文件存储的是HMI型号的相关信息
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString line;//临时变量，存储从文件取出的一行数据
        QString sModel;//文件变量
        QTextStream stream(&file);//定义操作文件的变量
        line=stream.readLine();//文件第一行存储的是型号的个数
        int hmimodelcount=line.toInt();//把得到的QString类型的数据转换为整型该行存储的是所有型号的个数
        for(int temp=0;temp<hmimodelcount;temp++)
        {
            sModel=stream.readLine();
            line=sModel.split("(").at(0);
            if(line==pwnd->newpro->newprowizard_model)//得到当前选择的型号位置 以便于取分辨率
            {
                break;
            }
        }
        QString sWidth ; //SA的宽度
        QString sHeight; //SA高度
        int nIndex = 0;      //左括号(‘(’)在字符串的下标位置
        int nStarIndex = 0;  //*星号在字符串中下标位置
        int nSpaceIndex = 0; //*星号后空格在字符串中下标位置
        int nWidth = 0 ;    //SA的宽度
        int nHeight = 0;    //SA高度
        int nShowModel = 0; //SA显示模式
        nIndex = sModel.indexOf("(");             //左括号(‘(’)在字符串的下标位置
        nStarIndex = sModel.indexOf("*");         //*星号在字符串中下标位置
        nSpaceIndex = sModel.indexOf(" ",nStarIndex); //*星号后空格在字符串中下标位置
        sWidth = sModel.mid(nIndex+1,nStarIndex - (nIndex+1));
        nWidth = sWidth.toInt();   //把宽度字符串转化为int
        sHeight = sModel.mid(nStarIndex+1,nSpaceIndex - (nStarIndex+1));
        nHeight = sHeight.toInt(); //把高度字符串转化为int
        if(sShowModel == tr("水平"))
        {
            nShowModel = 0;
        }
        else if(sShowModel == tr("垂直"))
        {
            nShowModel = 1;
        }
        OnNewGraphicsScene(nShowModel,nWidth,nHeight); //调用主框架中的画画面函数
        file.close();
    }
}
void MainWindow::DrawWindowSize()
{
    QString sShowModel = pwnd->newpro->newprowizard_showmodel;  //SA显示模式，是水平还是垂直显示
    int nWidth = newWindowDlg->ui->spinBox_w ->value();    //SA的宽度
    int nHeight = newWindowDlg->ui->spinBox_h->value();    //SA高度
    int nShowModel = 0; //SA显示模式
    if(sShowModel == tr("水平"))
    {
        nShowModel = 0;
    }
    else if(sShowModel == tr("垂直"))
    {
        nShowModel = 1;
    }
    OnNewGraphicsScene(nShowModel,nWidth,nHeight); //调用主框架中的画画面函数
}
/************************************************************************
  函数名称：OnDrawScreenSize(int nShowModel, int nWidth, int nHeight)
  函数功能：根据不同的型号建立不同的画面
  参数含义：
  nShowModel：显示模式，0表示水平显示，1表示垂直显示
  nWidth    ：画面的宽度
  nHeight   ：画面的高度
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
    if(nShowModel == 0) //水平显示
    {
        pScene->setSceneRect(0,0,nWidth,nHeight);
        //pView->setSceneRect(0,0,nWidth,nHeight+100);//+100不要删除edit by zqh
    }
    else if(nShowModel == 1) //垂直显示
    {
        pScene->setSceneRect(0,0,nHeight,nWidth);
        //pView->setSceneRect(0,0,nHeight,nWidth+100);
    }
    //    int nSelectType = pScene->nSelectType ; //0表示默认选择，1表示选择图片作为背景
    //    pScene->nSelectType = nSelectType;
    //    if(nSelectType == 0)
    //    {
    //        pScene->nPattern =pScene->nPattern; //样式选择
    //        pScene->m_sceneBackColor = pScene->m_sceneBackColor; //背景色
    //        pScene->m_sceneStyleColor = pScene->m_sceneStyleColor; //前景色
    //    }
    //    else if(nSelectType == 1)
    //    {
    //        pScene->m_picturePath = newpro->newscreenwizard_picturepath;  //图片路径
    //    }
    pView->setDragMode(QGraphicsView::RubberBandDrag);//把单选改变给拖动模式RubberBandDrag
    //pView->setRenderHint(QPainter::Antialiasing, true); // 设置图形反走样ScrollHandDrag
    pView->setMouseTracking(true); // 设置鼠标移动捕捉

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
    OnSetMainSceneGrid(); //是否显示网格
}

//改变层次关系
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

//弹出修改开关属性的对话框
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
    /*if(pwnd->m_pSamSysParame->m_loadDataSampling.size() == 0)//没有数据采集
    {
        return;
    }

    //组名
    int temp = m_pSamSysParame->m_loadDataSampling.size();
    int hisSampNum = 0;
    for(int i = 0; i < temp; i++)
    {
        if(2 == m_pSamSysParame->m_loadDataSampling[i].nDataSampType)//曲线为历史曲线
        {
            if(m_pSamSysParame->m_loadDataSampling[i].m_dataTable.size() != 0)
            {
                hisSampNum++;
            }
        }
    }
    if(0 == hisSampNum)
    {
        QMessageBox::about(this, tr("历史数据显示器"), tr("没有历史数据采集或者历史数据采集为空"));
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

/*void MainWindow::modifyNumEntrydlg(QGraphicsItem *item)//数值输入
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


/*void MainWindow::modifyBarGraphdlg(QGraphicsItem *item)//柱状图
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

/*void MainWindow::modifyASCIIDisplaydlg(QGraphicsItem *item)//ASCII显示
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

/*void MainWindow::modifyASCIIDEntrydlg(QGraphicsItem *item)//ASCII输入与显示
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

void MainWindow::modifyTimeDisplaydlg(QGraphicsItem *item)//时间显示
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
void MainWindow::modifyDateDisplaydlg(QGraphicsItem *item)//日期显示
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
void MainWindow::modifyDynAlarmBardlg(QGraphicsItem *item)//动态报警条
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
/*void MainWindow::modifyMeterdlg(QGraphicsItem *item)//仪表
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
void MainWindow::modifyChartdlg(QGraphicsItem *item)//图表
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
void MainWindow::modifyValuedlg(QGraphicsItem *item)//图表
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
void MainWindow::modifyImagedlg(QGraphicsItem *item)//图表
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
void MainWindow::modifyFlowBlock(QGraphicsItem *item)//流动块
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
void MainWindow::modifyAlarmControldlg(QGraphicsItem *item)//报警控件
{
    AlarmListDlg *alarmcontrol=new AlarmListDlg(item,1,this);
    if(alarmcontrol->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = alarmcontrol->item;
        OnDoubleClik(item,oldItem);
        //pSceneSheet[nActiveSheetIndex]->removeItem(item);//移除旧ITEM
    }
    alarmcontrol->deleteLater();
    alarmcontrol = NULL;
}
/***********************************************************************
  操作记录显示器修改或双击
 ***********************************************************************/
/*void MainWindow::modifyOperateDisplay(QGraphicsItem *item)//操作记录显示控件
{
    qoperatecontroldlg *operatecontrol=new qoperatecontroldlg(item,this);
    if(operatecontrol->exec() == QDialog::Accepted)
    {
        QGraphicsItem * oldItem = operatecontrol->pCopyItem;
        OnDoubleClik(item,oldItem);
        //pSceneSheet[nActiveSheetIndex]->removeItem(item);//移除旧ITEM
    }
    operatecontrol->deleteLater();
    operatecontrol = NULL;
}*/
void MainWindow::modifyHisAlarmdlg(QGraphicsItem *item)//历史报警显示器
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
void MainWindow::OnModifyLine(QGraphicsItem *item)//直线
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
void MainWindow::OnModifyRect(QGraphicsItem *item)//椭圆、矩形、多边形
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
void MainWindow::OnModfyText(QGraphicsItem *item)//文本
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

//鼠标双击一个控件的响应函数
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
           || type == SAM_DRAW_GROUP_KEY//键盘按钮
           || type == SAM_DRAW_GROUP_FLOW//流动块
           || type == SAM_DRAW_GROUP_RECIPE
           || type == SAM_DRAW_GROUP_ALARMITEM
           || type == SAM_DRAW_GROUP_HISALARMITEM
           || type == SAM_DRAW_GROUP_IMAGE
           || type == SAM_DRAW_GROUP_DYNRECT
           || type == SAM_DRAW_GROUP_DYNCIRCLE
           || type == SAM_DRAW_GROUP_STATICTEXT//静态文本

           || type == SAM_DRAW_GROUP_TABLE//表格

           || type == SAM_DRAW_GROUP_CALIBRATION//刻度
           || type == SAM_DRAW_GROUP_SLIDER//滑动块
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
            GroupTypeKey(item);//组合图形
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
    case SAM_DRAW_OBJECT_LINE://直线
    case SAM_DRAW_OBJECT_FOLDLINE://折线
    case SAM_DRAW_OBJECT_LINECIRCLE://曲线、圆弧
    case SAM_DRAW_OBJECT_FREELINE://自由直线

    case SAM_DRAW_OBJECT_LINE_NEW://直线
    case SAM_DRAW_OBJECT_FOLDLINE_NEW://折线
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW://曲线、圆弧
    case SAM_DRAW_OBJECT_FREELINE_NEW://自由直线
        OnModifyLine(item);
        break;
    case SAM_DRAW_OBJECT_RECT://矩形
    case SAM_DRAW_OBJECT_ELIPSE://椭圆
    case SAM_DRAW_OBJECT_POLYGON://多边形

    case SAM_DRAW_OBJECT_RECT_NEW://矩形
    case SAM_DRAW_OBJECT_ELIPSE_NEW://椭圆
    case SAM_DRAW_OBJECT_POLYGON_NEW://多边形
        OnModifyRect(item);
         break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT: //圆角矩形
    case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW: //圆角矩形
        OnModfyRoundedRectDlg(item);
         break;
    case SAM_DRAW_OBJECT_ARC: //基本扇形图形
    case SAM_DRAW_OBJECT_ARC_NEW: //基本扇形图形
        OnModfyArcDlg(item);
         break;
//    case SAM_DRAW_OBJECT_TEXT://静态文本
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
		
    case SAM_DRAW_GROUP_TREND://趋势图
        OnTrendChartDlg(itemGroup);
        break;

    case SAM_DRAW_GROUP_GROUPDATA://数据群组
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

    case SAM_DRAW_GROUP_FLOW://流动块
        modifyFlowBlock(itemGroup);
        break;
    case  SAM_DRAW_GROUP_KEY://键盘按钮
        modifyKeyBoardASCII(itemGroup);
        break;
    case SAM_DRAW_GROUP_ALARMBAR://动态报警条
        modifyDynAlarmBardlg(itemGroup);
        break;
    case SAM_DRAW_GROUP_STATICTEXT://静态文本
        OnModfyText(itemGroup);
        break;
    case SAM_DRAW_GROUP_CALIBRATION://刻度
        OnModifyScaleDlg(itemGroup);
        break;
    case SAM_DRAW_GROUP_SLIDER://滑动块
        OnModfySliderDlg(itemGroup);
        break;
    case SAM_DRAW_GROUP_TABLE://表格
        OnModifyTableDlg(itemGroup);
        break;
    case SAM_DRAW_GROUP_ANIMATION:
        OnModfyAnimationDlg(itemGroup);
        break;

    case SAM_DRAW_GROUP_DYNRECT://动态矩形
        modifyDynRectdlg(itemGroup);
        break;

    case SAM_DRAW_GROUP_DYNCIRCLE://动态圆
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

    case SAM_DRAW_GROUP_RECIPESHOW://配方显示器
        modifyRecipeDisplay(itemGroup);
        break;

    case SAM_DRAW_GROUP_HISTORYDATE://历史数据显示器
        OnModfyHisDataShowDlg(item);
        break;

    case SAM_DRAW_GROUP_MESSAGE://消息显示器
        OnModifyMsgDisplayDlg(item);
        break;

    case SAM_DRAW_GROUP_STATICPIC:
        OnModifyStaticPic(item);
        break;

    case SAM_DRAW_GROUP_TEXTBOARD:
        OnModifyTextBoard(item);
        break;
    case SAM_DRAW_GROUP_MFBTN://多功能按钮
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
  case GROUP_TYPE_BITBTN://是位按钮
        modifyBitBtndlg(item);
        break;
 case GROUP_TYPE_BITLAMP://是位指示灯按钮
        modifyBitLampdlg(item);
        break;
    case GROUP_TYPE_WORDBTN://是字按钮
        modifyWordBtndlg(item);
        break;
   case GROUP_TYPE_SCREENBTN://画面按钮
        modifyScreenBtndlg(item);
        break;
    case GROUP_TYPE_FUNCTIONBTN://功能按钮
        modifyFunctionBtndlg(item);
        break;
   case GROUP_TYPE_DYNCIRCLE://动态圆
        modifyDynCircledlg(item);
        break;
    case GROUP_TYPE_DYNRECT://动态矩形
        modifyDynRectdlg(item);
        break;
    case GROUP_TYPE_MFUNCTION://多功能
        modifyMfunctiondlg(item);
        break;
  case GROUP_TYPE_PICTUREDISPLAY://图片显示器
          modifyPictureDisplaydlg(item);
          break;
   case GROUP_TYPE_WEEKBTN://星期显示
        modifyWeekdlg(item);
        break;
  case  GROUP_TYPE_MULSTATELAMP://多状态指示灯
        modifyMultiLampdlg(item);
        break;
   case  GROUP_TYPE_MULSTATEBTN://多态按钮
         modifyMultiStatedlg(item);
         break;

   case  GROUP_TYPE_PICTUREMOVE://图片移动
         modifyGraphicsMovedlg(item);
         break;
    case GROUP_TYPE_NUMDISPLAY ://数值显示
        modifyNumDispaydlg(item);
        break;
    case GROUP_TYPE_NUMENTRY://数值输入
        modifyNumEntrydlg(item);
        break;
    case GROUP_TYPE_ASCIIDISPLAY://ASCII显示
        modifyASCIIDisplaydlg(item);
        break;
    case GROUP_TYPE_ASCIIENTRY://ASCII输入
        modifyASCIIDEntrydlg(item);
        break;
    case GROUP_TYPE_BARGRAPH://柱状图
        modifyBarGraphdlg(item);
        break;
    case GROUP_TYPE_TIMEDISPLAY://时间显示
        modifyTimeDisplaydlg(item);
        break;
    case GROUP_TYPE_DATEDISPLAY://日期显示
        modifyDateDisplaydlg(item);
        break;
    case GROUP_TYPE_ALARMCONTROL://报警控件
        modifyAlarmControldlg(item);
        break;
    case GROUP_TYPE_DYNALARMBAR://动态报警条
        modifyDynAlarmBardlg(item);
        break;
    case GROUP_TYPE_HISALARM://历史报警显示器
        modifyHisAlarmdlg(item);
        break;

    case GROUP_TYPE_METER://仪表
        modifyMeterdlg(item);
        break;
    case GROUP_TYPE_FLOWBLOCK://流动块
        modifyFlowBlock(item);
        break;
    case GROUP_TYPE_STATICPIC://静态图片
        OnModifyStaticPic(item);
        break;
    case GROUP_TYPE_GIFPIC://GIF图片
        OnModifyGifPic(item);
        break;
    case GROUP_TYPE_PIE:   //扇形图
        OnModifyPieDlg(item);
        break;
    case GROUP_TYPE_MSGDISPLAY:   //消息显示
        OnModifyMsgDisplayDlg(item);
        break;
    case GROUP_TYPE_TABLE: //表格
        OnModifyTableDlg(item);
        break;
    case GROUP_TYPE_SCALES: //刻度
        OnModifyScaleDlg(item);
        break;
    case GROUP_TYPE_STATICTEXT://文本
         OnModfyText(item);
         break;
    case GROUP_TYPE_TRENDCHART://趋势图
         OnTrendChartDlg(item);
         break;
    case GROUP_TYPE_XYTRENDCHART://XY趋势图
         OnXYTrendChartDlg(item);
         break;
    case GROUP_TYPE_HISTRENDCHART://历史趋势图
         OnHISTrendChartDlg(item);
          break;
    case GROUP_TYPE_STEPING: //步进按钮
        OnModfyStepingDlg(item);
         break;
    case GROUP_TYPE_SINGLESELECT://单选按钮
        OnModfySingleSelectDlg(item);
         break;
    case GROUP_TYPE_COMBOBOX: //下拉框
        OnModfyComboBoxDlg(item);
         break;
    case GROUP_TYPE_SLIDER: //滑块模拟量开关
        OnModfySliderDlg(item);
         break;
    case GROUP_TYPE_HISDATAALARM: //历史记录显示器
        OnModfyHisDataShowDlg(item);
         break;
    case GROUP_TYPE_ANIMATE: //动画
        OnModfyAnimationDlg(item);
         break;
    case GROUP_TYPE_MESSAGEBOARD: //留言板
        OnModfyMsgBoardDlg(item);
         break;
    case GROUP_TYPE_DATAGROUPDISPLAY :  //数据群组显示
        OnModfyDataGroupDisplayDlg(item);
         break;
    case GROUP_TYPE_TIMER :  //定时器
        OnModfyTimerDlg(item);
         break;
    case GROUP_TYPE_ASCII_KEYBOARD://ASCII输入
        modifyKeyBoardASCII(item);
        break;
    case GROUP_TYPE_RECIPE_CHOICE://配方选择器
        modifyRecipeChoice(item);
        break;
    case GROUP_TYPE_RECIPE_DISPLAY://配方显示器
        modifyRecipeDisplay(item);
        break;
    case GROUP_TYPE_OPERATE_RECORD://操作记录显示器
        modifyOperateDisplay(item);
    case GROUP_TYPE_CHART:          //图表
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
 *函数名称：OnAddPattern(QComboBox *pComboBox)
 *函数功能：为每个控件的一般页面添加样式
 *参数含义：pComboBox为指向组合框的指针
 *edit by zqh
 **************************************************/
void MainWindow::OnAddPattern(QComboBox *pComboBox)
{   //13个样式
    pComboBox->addItem(QIcon(":/style/images/style/1.ico"),tr("透明"));
    pComboBox->addItem(QIcon(":/style/images/style/1.ico"),tr("纯色"));
    pComboBox->addItem(QIcon(":/style/images/style/15.ico"),tr("横向过度"));
    pComboBox->addItem(QIcon(":/style/images/style/16.ico"),tr("横向对称过度"));
    pComboBox->addItem(QIcon(":/style/images/style/17.ico"),tr("纵向过度"));
    pComboBox->addItem(QIcon(":/style/images/style/18.ico"),tr("纵向对称过度"));
    pComboBox->addItem(QIcon(":/style/images/style/19.ico"),tr("斜上过渡"));
    pComboBox->addItem(QIcon(":/style/images/style/20.ico"),tr("斜上对称过渡"));
    pComboBox->addItem(QIcon(":/style/images/style/21.ico"),tr("斜下过渡"));
    pComboBox->addItem(QIcon(":/style/images/style/22.ico"),tr("斜下对称过渡"));
    pComboBox->addItem(QIcon(":/style/images/style/24.ico"),tr("右上角辐射"));
    pComboBox->addItem(QIcon(":/style/images/style/23.ico"),tr("左上角辐射"));
    pComboBox->addItem(QIcon(":/style/images/style/25.ico"),tr("中心辐射"));


    pComboBox->setCurrentIndex(1); //默认选择纯色


}

QString MainWindow::ColorTOString(QColor color) //把颜色值转换为QString类型
{
    QString sColor = "";
    int nRed = color.red();
    int nGreen = color.green();
    int nBule = color.blue();
    sColor = QString("%1+%2+%3").arg(nRed).arg(nGreen).arg(nBule);
    return sColor;
}

void MainWindow::OnAddNewScreen()  //新建画面
{
    //nSheetTotalNumber ++; //当前工程建的画面总数
    //nActiveSheetIndex ++; //当前画面序号
    //OnNewGraphicsScene(0,800,600);
    tree_newscreen();
    dockTabWidget->setCurrentIndex(1);
}

void MainWindow::OnSetTheFrontScreen() //上一幅画面
{
    int tempIndex=nActiveSheetIndex;//保存初始值
    if(nActiveSheetIndex==0)//若已经是第一个值的时候
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

void MainWindow::OnSetTheNextScreen() //下一幅画面
{
    int tempIndex=nActiveSheetIndex;//保存初始值
    int totalSceneNum = pSceneSheet.size();
    if(nActiveSheetIndex==totalSceneNum-1)//若已经是最后一个值的时候
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
    combobox->addItem(tr("16位正整数"));
    combobox->addItem(tr("32位正整数"));
    combobox->addItem(tr("16位整数"));
    combobox->addItem(tr("32位整数"));
    combobox->addItem(tr("16位BCD正整数"));
    combobox->addItem(tr("32位BCD正整数"));
    combobox->addItem(tr("32位浮点数"));
}

QString MainWindow::KeyboardToString(Keyboard keyboard)
{
    QString temp;
    temp=temp+keyboard.sShowAddr;//地址输入字符串如“X123”
    temp+='#';//分隔符

    temp+=QString::number(keyboard.nConnectType);//连接型号如内部存储区、com1等
    temp+='#';//分隔符

    temp+=QString::number(keyboard.nPlcRegTypeIndex);//PLC寄存器X、Y、T、C等的索引
    temp+='#';//分隔符

    temp+=QString::number(keyboard.nPlcStationIndex);//PLC站号
    temp+='#';//分隔符

    temp+=keyboard.sPlcAddrValue;//plc寄存器地址如“123”等
    temp+='#';//分隔符

    temp+=keyboard.sPlcRegTypeStr;//plc寄存器“X”、“Y”等
    temp+='#';//分隔符

    temp+=QString::number(keyboard.nAddrType); //字位标示
    temp+='#';//分隔符

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

void MainWindow::OnModifyStaticPic(QGraphicsItem *item) //双击打开静态图片对话框
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

    pSceneSheet[nActiveSheetIndex]->removeItem(item);//移除旧ITEM
    ModifyItemCommand * modifycommand =
            new ModifyItemCommand(item,OldItem,pSceneSheet[nActiveSheetIndex],"");
    undoStack->push(modifycommand);
    OldItem->setPos(pos);
}
QGraphicsItem * MainWindow::PasteItemToScence()//当粘贴Item到场景的时候
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
        //upDatetreeScreenItem();//更新画面的子项
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
    else//当粘贴的是多个的时候
    {

        for(int i=0;i<pSceneSheet[nActiveSheetIndex]->pasteList.size();i++)
        {
            nKey=pSceneSheet[nActiveSheetIndex]->pasteList.at(i)->data(GROUP_TYPE_KEY).toInt(); //取出key值

            pSceneSheet[nActiveSheetIndex]->setNewItem_ID(pSceneSheet[nActiveSheetIndex]->pasteList.at(i),NouseItem );
            pSceneSheet[nActiveSheetIndex]->addItem(pSceneSheet[nActiveSheetIndex]->pasteList.at(i));
            AndTreeSubItem(pSceneSheet[nActiveSheetIndex]->pasteList.at(i));
            //upDatetreeScreenItem();//更新画面的子项

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
    if(nID == LIBRARY_LIB_GROUP) ////图库组合
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
    if(oldItem)//当点击的是工具栏的Item 的时候
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
        //add by wuxiyang画面子项并没有在树上展示，没必要更新
        //且更新的话会导致树上的选中项消失
        //upDatetreeScreenItem();//更新画面的子项

        if(nID == GROUP_TYPE_TIMER) //是定时器
        {
            QItemGroup *pItemGroup = NULL;
            pItemGroup = dynamic_cast<QItemGroup *> (oldItem);
            if(pItemGroup)
                pItemGroup->setResizableOff();
        }

        undoStack->push(new addItemToScence(pSceneSheet[nActiveSheetIndex],oldItem,true));
    }

    else //当粘贴的是一个的时候
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
//       || nID == GROUP_TYPE_WEEKBTN) //位按钮 位指示灯 多态指示灯、多态按钮、图形移动 消息显示 星期显示
//    {
//        this->OnSingleClickItem();//更新工具栏上的状态组合框内容
//    }
}
void MainWindow::IsDefineGroup(QGraphicsItem * pItem)//是否是自定义组合
{
    QList<QGraphicsItem *> childItems;
    int nKey=0;
    QGraphicsItem *NouseItem = NULL;
    childItems =pItem->childItems();
    for(int i=0;i<childItems.size();i++)
    {
        nKey=childItems.at(i)->data(GROUP_TYPE_KEY).toInt(); //取出key值
        if(nKey==USER_DEFINE_GROUP)
        {
            IsDefineGroup(childItems.at(i));
        }
        else
        {
            pSceneSheet[nActiveSheetIndex]->setNewItem_ID(childItems[i],NouseItem );
            pSceneSheet[nActiveSheetIndex]->addItem(childItems[i]);
            AndTreeSubItem(childItems[i]);
            upDatetreeScreenItem();//更新画面的子项
            child_userGroupItems.push_back(childItems[i]);
        }
    }//
}
void MainWindow::OnDoubleClik(QGraphicsItem *item,QGraphicsItem *OldItem)
{
    if(NULL == OldItem)
    {
       pSceneSheet[nActiveSheetIndex]->removeItem(item);//移除旧ITEM
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
              double dW = newItem->sceneBoundingRect().width(); //新图形的宽度和高度
              double dH = newItem->sceneBoundingRect().height();
              double newH = rc.width()*dH/dW;//新图形的比例系数
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
          else if(item->type() == SAM_DRAW_OBJECT_ROUNDEDRECT)// alter by zqh 2012.9.19 圆角矩形属性改变后大小会发生改变
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
    pSceneSheet[nActiveSheetIndex]->removeItem(item);//移除旧ITEM

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
        newItem->setPos(rc.topLeft()-newItem->boundingRect().topLeft());//设置新的item的位置
    }
    else if(nKey == GROUP_TYPE_TIMER)//是定时器
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
    //newItem->setZValue(zValue); //重新设置控件按钮的层次
   //物件工具栏上的对话框在画面中点击确定按钮后改变保存按钮的颜色
 //   pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
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

QString MainWindow::GetControlNO(QString sName) //获得控件的新编号
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
    Length = sName.length();               //编号开始符长度
    int totalSceneNum = pSceneSheet.size();
    for(i = 0; i < totalSceneNum; i++) //扫描所有画面
    {
        Items = pSceneSheet[i]->items();   //当前页面所有的item
        for(j = 0; j < Items.size(); j++)
        {
            sList = Items.at(j)->topLevelItem()->data(GROUP_DATALIST_KEY).toStringList(); //取出每个item的所有数据
            if(sList.size() < 20)//if(sList.empty() && sList.size() < 20)
                continue;//break;
            str = sList.at(19);           //编号存在15位
            if(sName == str.left(str.length()-4))//if(sName == str.left(Length)) //编号开始符相同
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
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

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
    if(parentItem==copyScreen_Item||parentItem==screen)//当点击的是画面第一级菜单时
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
            QMessageBox box(QMessageBox::Information,tr("提示"),tr("最后一个画面不可以删除"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("是"));
            box.exec();
            return;
        }
    }
    pwnd->is_Save=false;//
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
    //保存画面删除时的一些信息，用做撤销、重做操作
    SamDrawScene* pSceneTemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex];
    int iActiveSheetIndex = pwnd->nActiveSheetIndex;
    int iTreeIndex = pwnd->screen->indexOfChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);
    emit deleteScreen();
    upDatetreeScreenItem();//更新画面的子项
    updateChScreen();
    undoStack->push(new DeleteSceneCommand(pSceneTemp, iActiveSheetIndex, iTreeIndex));
}

void MainWindow::newswindow_open()
{
    pwnd->is_Save=false;//
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

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
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

    SamDrawScene* pSceneTemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex];
    int iActiveSheetIndex = pwnd->nActiveSheetIndex;
    int iTreeIndex = pwnd->window->indexOfChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);
    emit deleteWindow();
    upDatetreeScreenItem();//更新画面的子项
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
    //newScreenDlg->setWindowTitle(tr("画面属性"));
    int res= newScreenDlg->exec();
    if(res==QDialog::Accepted)
    {
        pwnd->reScreenorwindowName(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName,newScreenDlg->ui->newscreen_name_lineedit->text());
        pwnd->is_Save=false;//
        is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
        //1-199  0位向导新建画面的数据
        emit screenProperty_assign();
        upDatetreeScreenItem();//更新画面的子项
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
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
        emit windowProperty_assign();
        upDatetreeScreenItem();//更新画面的子项
        PreviewWindow();
    }
    updateChScreen();
}

void MainWindow::newscreen_copy()//复制画面
{
   newCopyScreen->ui->lineEdit->setText("");
   int res=newCopyScreen->exec();
   if(res==QDialog::Accepted)
   {
       pwnd->is_Save=false;
       is_NeedCompiled = true;
       pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
       emit copyScreen();
       upDatetreeScreenItem();//更新画面的子项
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
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
        //1-199  0位向导新建画面的数据
        emit copyWindow();
        upDatetreeScreenItem();//更新画面的子项
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

void MainWindow::openInit_MenuAndTool()//点击打开按钮初始化菜单和工具栏
{
    //打开时初始化菜单和工具栏
    ///文件菜单
    ui->action_new_screen->setDisabled(is_Is);
    ui->action_close->setDisabled(is_Is);
    ui->action_save->setDisabled(is_Is);
    ui->action_save_as->setDisabled(is_Is);
    //编辑
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

    //绘图
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

    //物件
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
        pMenuSpace = new QMenu(tr("间距"), /*ui->standardToolBar*/ui->mapToolBar);
        pMenuSpace->setIcon(QIcon(":/standardtool/images/standardtool/makesamewihi.ico"));

        QAction *widthsame  = pMenuSpace->addAction(tr("宽度相同"));
        QAction *heightsame = pMenuSpace->addAction(tr("高度相同"));
        QAction *widthheight= pMenuSpace->addAction(tr("宽度高度都相同"));
        QAction *horizontal = pMenuSpace->addAction(tr("水平等间距"));
        QAction *vertical   = pMenuSpace->addAction(tr("垂直等间距"));

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
        ActionSpace->setIconText(tr("\n间距"));
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
        pMenuAlign = new QMenu(tr("对齐"), /*ui->standardToolBar*/ui->mapToolBar);
        pMenuAlign->setIcon(QIcon(":/standardtool/images/standardtool/leftalign.ico"));

        QAction *alignLeft   = pMenuAlign->addAction(tr("左对齐"));
        QAction *alignRight  = pMenuAlign->addAction(tr("右对齐"));
        QAction *alignTop    = pMenuAlign->addAction(tr("上对齐"));
        QAction *alignUnder  = pMenuAlign->addAction(tr("下对齐"));
        QAction *alignHcenter= pMenuAlign->addAction(tr("水平居中"));
        QAction *alignVcenter= pMenuAlign->addAction(tr("垂直居中"));

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
        ActionAlign->setIconText(tr("\n对齐"));
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
        pMenuZXu = new QMenu(tr("层次"), /*ui->standardToolBar*/ui->mapToolBar);
        pMenuZXu->setIcon(QIcon(":/standardtool/images/standardtool/bringtotop.ico"));

        QAction *Z_first    = pMenuZXu->addAction(tr("移到最上层"));
        QAction *Z_last     = pMenuZXu->addAction(tr("移到最下层"));
        QAction *Z_before   = pMenuZXu->addAction(tr("移到上一层"));
        QAction *Z_next     = pMenuZXu->addAction(tr("移到下一层"));

        Z_first->setIcon(QIcon(":/standardtool/images/standardtool/bringtotop.ico"));
        Z_last->setIcon(QIcon(":/standardtool/images/standardtool/sendtobottom.ico"));
        Z_before->setIcon(QIcon(":/standardtool/images/standardtool/bringforward.ico"));
        Z_next->setIcon(QIcon(":/standardtool/images/standardtool/bringbackward.ico"));

        connect(Z_first,SIGNAL(triggered()),SLOT(on_action_bringtop_triggered()));
        connect(Z_last,SIGNAL(triggered()),SLOT(on_action_sengtoback_triggered()));
        connect(Z_before,SIGNAL(triggered()),SLOT(on_action_bringforward_triggered()));
        connect(Z_next,SIGNAL(triggered()),SLOT(on_action_bringback_triggered()));

        QAction *ActionZXu = pMenuZXu->menuAction();
        ActionZXu->setIconText(tr("\n层次"));
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
    //画面

    ui->action_RoundedRect->setDisabled(is_Is);
    ui->action_ArcItem->setDisabled(is_Is);
    //设定
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
    ui->action_User_Keybaor->setDisabled(is_Is);//添加用户自定义键盘
    ui->action_datasamp->setDisabled(is_Is);//添加数据采集
    ui->action_waring->setDisabled(is_Is);//添加报警
    ui->action_rep->setDisabled(is_Is);//添加配方
    ui->action_script->setDisabled(is_Is);//打开脚本浏览器

    ui->action_reverse_selection->setDisabled(is_Is);//反向选择
    //ui->action_ComboBox->setEnabled(false);
    ui->action_split->setEnabled(false);
   // ui->action_h->setEnabled(false);
   // ui->action_v->setEnabled(false);
    //ui->dockWidget->setVisible(!is_Is);
    m_toolDock->setVisible(!is_Is);
}


//消息输出窗口的点击事件
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

//工程管理器的点击事件
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

//另外、存对话框
void MainWindow::on_action_save_as_triggered()
{
     QFileDialog saveFileDlg(this);
     QString str=saveFileDlg.getSaveFileName(
             this,
             tr("Save As"),
             tr("C:/Documents and Settings/Administrator/桌面"),
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

void MainWindow::onFrmStatecmbChange(int nIndex)//工具栏上的状态下拉框edit by zqh
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
    if(Items.size() != 1)//选择多个或者没有选择的时候返回
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
 *函数名称：SetMultiStateText
 *函数功能：设置多个状态控件的文本信息
 *参数含义：
 *pItem：需要处理的控件item
 *sList：每个控件的存储信息
 *nID：控件的key值
 *nIndex：当前状态值
 *nTotal：总的状态值
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
    QString sFont = tr("宋体");

    QString sBorderColor;
    QString sFrontColor;
    QString sBackColor;
    int nPattern = 0;

    QGroupItem *pBaseItem = new QGroupItem(pItem);
    if(nID == GROUP_TYPE_MSGDISPLAY)//消息显示
    {
        nVal = 81;

        sBorderColor = sList.at(nVal+nIndex*4);
        sFrontColor = sList.at(nVal+1+nIndex*4);
        sBackColor = sList.at(nVal+2+nIndex*4);
        nPattern = sList.at(nVal+3+nIndex*4).toInt();

        nVal = nVal+nTotal*4;  //4为一般页面的三个颜色和一个样式总和

        sColor=sList.at(nVal+nIndex*3);
        nWordInterval=0;
        nAlignment=5;

        int nLang = sList.at(79).toInt();
        nVal = nVal+nTotal*3;

        int nLanIndex = qLanguagecmb->currentIndex(); //工具栏上当前语言下标
        if(nLanIndex < 0)
          nLanIndex = 0;

        nFontSize = sList.at(nVal+nIndex*3*nLang+nLanIndex*3).toInt();
        sText = sList.at(nVal+1+nIndex*3*nLang+nLanIndex*3);
        sFont = sList.at(nVal+2+nIndex*3*nLang+nLanIndex*3);
    }
    else if(nID == GROUP_TYPE_WEEKBTN)//星期显示
    {
        sBorderColor = sList.at(190+1+nIndex*4);
        sFrontColor = sList.at(190+2+nIndex*4);
        sBackColor = sList.at(190+3+nIndex*4);
        nPattern = sList.at(190+4+nIndex*4).toInt();

        int nLanIndex = qLanguagecmb->currentIndex(); //工具栏上当前语言下标
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
    else if(nID == GROUP_TYPE_BITBTN || nID == GROUP_TYPE_BITLAMP) //位按钮 位指示灯
    {
        int nLang = qLanguagecmb->currentIndex();//sList.at(100).toInt();//当前语言
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
            || GROUP_TYPE_PICTUREMOVE)//多态指示灯
    {
        nVal = 101;
        int nLang = sList.at(99).toInt();

        sBorderColor = sList.at(nVal+nIndex*4);
        sFrontColor = sList.at(nVal+1+nIndex*4);
        sBackColor = sList.at(nVal+2+nIndex*4);
        nPattern = sList.at(nVal+3+nIndex*4).toInt();

        nVal = nVal+nTotal*4;  //4为一般页面的三个颜色和一个样式总和
        sColor = sList.at(nVal+nIndex*3);
        nWordInterval = sList.at(nVal+1+nIndex*3).toInt();
        nAlignment=sList.at(nVal+2+nIndex*3).toInt();

        nVal = nVal+nTotal*3;
        int nLanIndex = qLanguagecmb->currentIndex(); //工具栏上当前语言下标
        if(nLanIndex < 0)
         nLanIndex = 0;
        nFontSize = sList.at(nVal+nIndex*3*nLang+nLanIndex*3).toInt();
        sText = sList.at(nVal+1+nIndex*3*nLang+nLanIndex*3);
        sFont = sList.at(nVal+2+nIndex*3*nLang+nLanIndex*3);
    }

    pBaseItem->SetPropertyValue("mText.Text",QVariant(sText));       //设置文本
    pBaseItem->SetPropertyValue("mText.Font",QVariant(sFont));   //设置字体
    pBaseItem->SetPropertyValue("mText.FontSize",QVariant(nFontSize));    //设置字体大小
    pBaseItem->SetPropertyValue("mText.WordInterval",QVariant(nWordInterval));//字距
    pBaseItem->SetPropertyValue("mText.Alignment",QVariant(nAlignment));   //对齐方式
    pBaseItem->SetPropertyValue("mText.FontColor",QVariant(sColor));  //字体颜色

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
    PasteItemToScene();//粘贴ITEM到场景
}

void MainWindow::OnSingleClickItem()//单击控件槽QGraphicsItem *pItem edit by zqh
{
    //return;
    int nID = 0;
    QStringList sList;
    //int nCurrentState = 0;   //当前状态值
    //int i = 0;
    //int nTotal = 0;
    QList<QGraphicsItem *> Items;
    QGraphicsItem *pItem;

    bToolBarCMBInit = false;
    Items = pSceneSheet[nActiveSheetIndex]->selectedItems();

    ////if(qLanguagecmb->count() > 0)
    ////    qLanguagecmb->setCurrentIndex(0);

    if(Items.size() != 1) //选择多个或者没有选择的时候返回
    {
        //statusButtoncmb->clear();
        //statusButtoncmb->setEnabled(false);
        ui->action_h->setEnabled(false);
        ui->action_v->setEnabled(false);
        ui->action_split->setEnabled(false);
        pwnd->ui->action_copym->setDisabled(true);//多重复制只在场景选择单个才有效
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
    pwnd->ui->action_copym->setDisabled(false);//多重复制只在场景选择单个才有效
    lab_up_space_statusBar->setEnabled(true);
    lab_left_space_statusBar->setEnabled(true);
    lab_width_space_statusBar->setEnabled(true);
    lab_hidth_space_statusBar->setEnabled(true);

    pItem = Items.at(0);
    nID = pItem->data(GROUP_TYPE_KEY).toInt(); //取控件的Key号

    if(nID == USER_DEFINE_GROUP) //是自定义组合
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

    ToSlectTreeItem(sList);//单击场景上的Item是相应选择树形控件的项
    //setLanguageCmbEnable(pItem);
}


void MainWindow::AddCurrentItemStatusList(QGraphicsItem *pItem, int state)//对状态条增加选项
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
 *函数名称：setStatusBarCtrlName
 *函数功能：点击某个控件时，设置状态栏上对应控件名称
 *参数含义：
 *pItem：     待设置的按钮指针
 *返回值:       NULL
 *编辑作者：郑启红
 *编辑日期：2012.9.18
 **************************************************************/
void MainWindow::setStatusBarCtrlName(QGraphicsItem *pItem)
{
    QString sCtrlName = "";
    QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
    switch(item->GroupType())
    {
    case SAM_DRAW_GROUP_MESSAGE:    sCtrlName = tr("消息显示器");break;//35,消息显示器
    case SAM_DRAW_GROUP_HISTORYDATE:    sCtrlName = tr("历史数据显示器");break;//32,历史数据显示器
    case SAM_DRAW_GROUP_SWITCH: sCtrlName = tr("开关");break;//10,开关类型
    case SAM_DRAW_GROUP_CHART:  sCtrlName = tr("图表");break;//11,图表
    case SAM_DRAW_GROUP_VALUE:  sCtrlName = tr("数值显示");break;//12,数值显示
    case SAM_DRAW_GROUP_IMAGE:  sCtrlName = tr("图片显示");break;//15,图片显示
    case SAM_DRAW_GROUP_ASCII:  sCtrlName = tr("ASCII显示");break;//16,ascii显示
    case SAM_DRAW_GROUP_TIME:   sCtrlName = tr("时间显示");break;//17,时间显示
    case SAM_DRAW_GROUP_ALARMITEM:  sCtrlName = tr("报警显示器");break;//18,报警显示控件
    case SAM_DRAW_GROUP_ALARMBAR:   sCtrlName = tr("动态报警条");break;//19,动态报警条
    case SAM_DRAW_GROUP_HISALARMITEM:   sCtrlName = tr("历史报警显示器");break;//20,历史报警显示控件
    case SAM_DRAW_GROUP_FLOW:   sCtrlName = tr("流动块");break;//21,流动块
    case SAM_DRAW_GROUP_ANIMATION:  sCtrlName = tr("动画");break;//22,动画
    case SAM_DRAW_GROUP_KEY:    sCtrlName = tr("键盘组件");break;//23,键盘组件
    case SAM_DRAW_GROUP_STATICTEXT: sCtrlName = tr("静态文本");break;//28,静态文本
    case SAM_DRAW_GROUP_RECIPE: sCtrlName = tr("配方选择器");break;//29,配方选择器
    case SAM_DRAW_GROUP_RECIPESHOW: sCtrlName = tr("配方显示器");break;//30,配方显示器
    case SAM_DRAW_GROUP_CALIBRATION:    sCtrlName = tr("刻度");break;//31,刻度
    case SAM_DRAW_GROUP_SLIDER: sCtrlName = tr("滑动块");break;//33,滑动块/进度条
    case SAM_DRAW_GROUP_STATICPIC:  sCtrlName = tr("GIF显示器");break;//34,GIF显示器
    case SAM_DRAW_GROUP_TREND:  sCtrlName = tr("趋势图");break;//13,趋势图
    case SAM_DRAW_GROUP_GROUPDATA:  sCtrlName = tr("数据群组");break;//14,数据群组
    case SAM_DRAW_GROUP_DROPDOWN:   sCtrlName = tr("下拉框");break;//27,下拉框
    case SAM_DRAW_GROUP_DYNRECT:    sCtrlName = tr("动态矩形");break;//24,动态矩形
    case SAM_DRAW_GROUP_DYNCIRCLE:  sCtrlName = tr("动态圆");break;//25,动态圆
    case SAM_DRAW_GROUP_TABLE:  sCtrlName = tr("表格");break;//表格
    case SAM_DRAW_GROUP_TEXTBOARD:  sCtrlName = tr("留言板");break;//留言板
    case SAM_DRAW_GROUP_COMBOBOX: sCtrlName = tr("下拉框");break;//
    case SAM_DRAW_GROUP_XYTREND:  sCtrlName = tr("X-Y曲线");break;//X-Y曲线
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

void MainWindow::OnSetZoomEnlarge()//放大操作edit by zqh
{
    nZoomNumber+=25; //每次缩放减25
    if(nZoomNumber > 300) //缩放值大于的时候不处理
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

void MainWindow::OnSetZoomFit()//复原edit by zqh
{
    nZoomNumber = 100;
    double newScale = 100 / 100.0;
    QMatrix oldMatrix = pView->matrix();
    pView->resetMatrix();
    pView->translate(oldMatrix.dx(), oldMatrix.dy());
    pView->scale(newScale, newScale);
}

void MainWindow::OnSetZoomSmall()//缩小edit by zqh
{
    nZoomNumber-=25; //每次缩放减25
    if(nZoomNumber < 25) //缩放值小于25的时候不处理
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

void MainWindow::OnSetSceneGrid()//网格edit by zqh
{
    bIfSceneShowGrid = !bIfSceneShowGrid;
    OnSetMainSceneGrid();
}

void MainWindow::OnSetMainSceneGrid()//网格edit by zqh
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

void MainWindow::OnSetDagViewModel()//设置视图模式edit by zqh
{
    pView->setDragMode(QGraphicsView::ScrollHandDrag);
}

void MainWindow::OnSetDagViewModelArrow()//设置视图模式edit by zqh
{
    pView->setDragMode(QGraphicsView::RubberBandDrag);
}

void MainWindow::OnOpenPropertyDlg()//打开属性对话框edit by zqh
{
    QList<QGraphicsItem *> Items;

    Items = pSceneSheet[nActiveSheetIndex]->selectedItems();
    if(Items.size() == 1 ) //选择一个item时，打开控件的对话框属性
    {
        SlotItemDBClick(Items.at(0));
    }
    else if(Items.size() == 0)//没有选中item时，打开画面的属性对话框
    {
        if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nIsSceneOrWindow==2)//自定义键盘
        {
            tree_UserKeyboardproperty();//自定义键盘属性
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
    else//选中多个
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
        QString ItemID=sListpItem.at(19);//记录控件ID
        pwnd->SlotItemDBClick(pItem);

            Items = this->pSceneSheet[pwnd->nActiveSheetIndex]->selectedItems();   //当前页面所有的item
        for(int i=0;i<Items.size();i++)
        {
            sListpItem = Items.at(i)->data(GROUP_DATALIST_KEY).toStringList(); //取出每个item的所有数据
            if(sList.size()<20)
                continue;
            str=sListpItem.at(19);
                  if(str==ItemID)//对比控件ID找到对应的ID的话
            {//记录list
                    break;
            }
        }
        for(int j = 0; j < Items.size(); j++)
        {
            sList = Items.at(j)->data(GROUP_DATALIST_KEY).toStringList(); //取出每个item的所有数据
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

//                Items[j]->SetPropertyValue("mFramRect.BackColor",QVariant(sList[41]));      //调用设置属性
//                Items[j]->SetPropertyValue("mBackRect.FrontColor",QVariant(sList[42]));      //调用设置属性
//                Items[j]->SetPropertyValue("mBackRect.BackColor",QVariant(sList[43]));      //调用设置属性

                Items[j]->setData(GROUP_DATALIST_KEY,sList);
             }
        }
    }
#endif
}

void MainWindow::OnFindAddressDlg()//打开地址查找对话框 edit by zqh
{
    FindAddrDlg *pFindDlg = new FindAddrDlg(this);

    QGraphicsItem *pItem;
    QString sScreenName = "";
    QString sAddr;
    QString str = "";
    QString ss  = "";
    QRect rc    = m_rightDock->geometry();
    int nFindCount = 0; //共找到多少条信息
    int nIfFit = 0;//是否匹配
    int nRow   = 1;//列表行数
    int nIndex = 0;
    int nCount = 0;
    int i      = 0;
    int j      = 0;
    int iType = 0; //0为地址查找，1为多语言文本查找
    int iFindCount = 0;//查找条数
    int iLan = 0;//多语言下标
    QString sSta = ""; //状态
    QString sLanName = "";
    QString sNewStr = "";

    if(pFindDlg->exec() == QDialog::Accepted)
    {
        mapMsgOutPutItem.clear();
        iType = pFindDlg->iSelctType; //查找类型

        vAddrMsg.clear();
        vTextMsg.clear();
        pMainList->clear();

        sAddr  = pFindDlg->sAddress;     //查找的地址内容
        sNewStr = pFindDlg->sReplaceMsg;//新的替换内容
        if(iType == 0) //地址查找
        {
            OnFillAddressMsgClass();        //填充地址信息到vAddrMsg
        }
        else if(iType == 1 || iType == 2) //文本查找
        {
            fillTextMsgStruct();
        }

        nCount = vAddrMsg.size();       //长度

        //before find address
        if(!m_rightDock->isVisible())   //显示信息输出窗口
        {
            m_rightDock->setVisible(true);
            ui->action_41->setChecked(true);
        }
        str = tr("正在查找 '");
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
            if(iType == 0) //地址查找
            {
                iFindCount = vAddrMsg.at(i)->Address.size();
            }
            else if(iType == 1|| iType == 2) //文本查找
            {
                iFindCount = vTextMsg.at(i).vText.size();
            }

            for(j = 0; j < iFindCount; j++)//for(j = 0; j < vAddrMsg.at(i)->Address.size(); j++) //10,15
            {
                nIndex = vAddrMsg[i]->nSheetIndex;//画面序号
                if(iType == 0) //地址查找
                {
                    str    = vAddrMsg[i]->Address[j].pAddr->sShowAddr;//.sAddr;//取地址
                }
                else if(iType == 1|| iType == 2) //文本查找
                {
                    str = vTextMsg[i].vText.at(j);
                    iLan = vTextMsg[i].iLanguage.at(j); //语言下标
                    if(iLan >=0 && iLan <m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size())
                        sLanName = m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(iLan);
                    sSta = vTextMsg[i].vMsg.at(j);//QString("%1").arg(vTextMsg[i].vStatus.at(j));//状态

                    if( iType == 2)//如果是替换的话，默认是完全匹配
                    {
                        pFindDlg->bIfSame = true;
                        pFindDlg->bIfCase = true;
                    }
                }
                if(pFindDlg->bIfSame)//完全匹配
                {
                    if(pFindDlg->bIfCase)//区分大小写
                    {
                        nIfFit = sAddr.compare(str,Qt::CaseSensitive);
                    }
                    else//不区分大小写
                    {
                        nIfFit = sAddr.compare(str,Qt::CaseInsensitive);
                    }
                }
                else//模糊匹配
                {
                    QBool bFit(true);
                    if(pFindDlg->bIfCase)//区分大小写
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
                    else//不区分大小写
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

                if(nIfFit == 0)//地址匹配 str == sAddr
                {
                    if(pItem)//是控件的地址
                    {
                        sScreenName = pSceneSheet[nIndex]->sNewScreenName;//画面名称

                        if(iType == 0) //地址查找
                            ss = tr("位置: ") + sScreenName + "-" + vAddrMsg.at(i)->Address[j].str + vAddrMsg.at(i)->Address[j].pAddr->sShowAddr;//输出信息
                        else if(iType == 1) //文本查找
                            ss = tr("位置: ") + sScreenName + "-" +vTextMsg.at(i).sCtrlName+"-" +tr("语言:")+sLanName+"-"+sSta+"-"+tr("文本内容:")+str;// +tr("状态:")
                        else if(iType == 2) //替换
                        {
                            QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
                            item->replaceAllItemText(iLan,vTextMsg[i].vStatus.at(j),sNewStr); //更改内容

                            ss = tr("替换: ") + sScreenName + "-" +vTextMsg.at(i).sCtrlName+"-" +tr("语言:")+sLanName+"-"+sSta+"-"+tr("文本内容:")+str+"->"+sNewStr;
                        }
                    }
                    else//是工程管理器中地址
                    {
                        if(iType == 0) //地址查找
                            ss = tr("位置: 工程管理器 ") + "-" + vAddrMsg.at(i)->Address[j].str + vAddrMsg.at(i)->Address[j].pAddr->sShowAddr; //输出信息
                        else if(iType == 1) //文本查找
                            ss = tr("位置: 工程管理器 ") + "-" +vTextMsg.at(i).sCtrlName+"-" +tr("语言:")+sLanName+"-" +tr("文本内容:")+str;
                        else if(iType == 2) //替换
                        {
                            replaceTreeTextMsg(str,sNewStr);
                            ss = tr("替换: 工程管理器 ") + "-" +vTextMsg.at(i).sCtrlName+"-" +tr("语言:")+sLanName+"-" +tr("文本内容:")+str+"->"+sNewStr;
                        }
                    }

                    pMsgOutPut = new MsgOutPut ;//信息输出窗口双击要处理的类
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

        if(nFindCount == 0)//没有找到
        {
            ss  = "'" + sAddr + "'.";
            //str = "Cannot find the string " + ss;
            if(iType == 0)
                str = tr("没有找到地址 ") + ss;
            else
                str = tr("没有找到文本 ") + ss;
        }
        else
        {
            if(iType == 0 || iType == 1)
                str = QString("%1").arg(nFindCount) + tr(" 个结果被找到");
            else
                str = QString("%1").arg(nFindCount) + tr(" 个结果被替换");
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
    int count = pSceneSheet.size(); //画面总数
    QList<QGraphicsItem *> Items;
    for(int i = 0 ; i < count; i++) //扫描所有画面
    {
        Items = pSceneSheet[i]->items();   //当前页面所有的item
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
                        pAddrMsg->nSheetIndex = i;                      //画面序号
                        pAddrMsg->pItem       = pItem;                  //当前控件
                        vAddrMsg.append(pAddrMsg);

                        TEXTPRO txt;
                        txt = item->getAllItemText(); //获得文本信息
                        vTextMsg.append(txt);
                    }
                }
            }
        }
    }
    fillTreeTextMsg();
}

void MainWindow::fillTreeTextMsg() //工程管理器中所使用的文本内容
{
    //配方内容
    int RecipGroup = m_pSamSysParame->m_qvcRecipe.size(); //配方组
    int iRecipeCount = 0;
    int iLang = 0;
    int i,j,k;
    for( i = 0; i < RecipGroup;i++)
    {
        pAddrMsg = new AddrMsg;
        pAddrMsg->nSheetIndex = i; //标示配方组号码
        pAddrMsg->pItem = NULL;

        TEXTPRO txt;
        txt.sCtrlName = tr("配方组:")+m_pSamSysParame->m_qvcRecipe.at(i).sName; //配方组名称
        iRecipeCount = m_pSamSysParame->m_qvcRecipe[i].formula.size();//配方总数
        for( j = 0; j < iRecipeCount; j++)
        {
            iLang = m_pSamSysParame->m_qvcRecipe[i].formula.at(j).RecipeInfo.size();//语言
            for( k = 0; k < iLang; k++)
            {
                txt.iLanguage.append(k);
                txt.vStatus.append(j); //配方编号
                txt.vMsg.append(tr("配方:")+QString("%1").arg(j));
                txt.vText.append(m_pSamSysParame->m_qvcRecipe.at(i).formula.at(j).RecipeInfo.at(k).sRecipeName);
            }
        }
        vTextMsg.append(txt);
        vAddrMsg.append(pAddrMsg);
    }

    //报警
    RecipGroup = m_pSamSysParame->m_qvcAlarm.size();
    for( i = 0; i < RecipGroup;i++)
    {
        pAddrMsg = new AddrMsg;
        pAddrMsg->nSheetIndex = i; //标示配方组号码
        pAddrMsg->pItem = NULL;

        TEXTPRO txt;
        txt.sCtrlName = tr("报警:")+m_pSamSysParame->m_qvcAlarm.at(i).alarmName; //报警组名称

        iRecipeCount = m_pSamSysParame->m_qvcAlarm.at(i).alarms.size();//每组报警的报警条数
        for( j = 0; j < iRecipeCount; j++)
        {
            iLang = m_pSamSysParame->m_qvcAlarm.at(i).alarms.at(j).messages.size(); //语言
            for( k = 0; k < iLang; k++)
            {
                txt.iLanguage.append(k);
                txt.vStatus.append(j); //报警
                txt.vMsg.append(tr("报警:")+QString("%1").arg(j));
                txt.vText.append(m_pSamSysParame->m_qvcAlarm.at(i).alarms.at(j).messages.at(k));
            }
        }
        vTextMsg.append(txt);
        vAddrMsg.append(pAddrMsg);
    }
}

void MainWindow::replaceTreeTextMsg(QString sOldMsg,QString sNewMsg) //替换工程管理器中含有文本的内容
{
    int RecipGroup = m_pSamSysParame->m_qvcRecipe.size(); //配方组
    int iRecipeCount = 0;
    int iLang = 0;
    int i,j,k;
    QString str = "";
    bool bFit = false;

    for( i = 0; i < RecipGroup;i++)
    {
        iRecipeCount = m_pSamSysParame->m_qvcRecipe[i].formula.size();//配方总数
        for( j = 0; j < iRecipeCount; j++)
        {
            iLang = m_pSamSysParame->m_qvcRecipe[i].formula.at(j).RecipeInfo.size();//语言
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

    //报警
    RecipGroup = m_pSamSysParame->m_qvcAlarm.size();
    for( i = 0; i < RecipGroup;i++)
    {

        iRecipeCount = m_pSamSysParame->m_qvcAlarm.at(i).alarms.size();//每组报警的报警条数
        for( j = 0; j < iRecipeCount; j++)
        {
            iLang = m_pSamSysParame->m_qvcAlarm.at(i).alarms.at(j).messages.size(); //语言
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
 *函数名称：OnFillAddressMsgClass
 *函数功能：存储所有画面的所有控件的地址值到vAddrMsg动态数组中，用于地址
           查找，地址一览表和编译时的地址错误检查使用
 *edit by zqh
 ****************************************************************/
/*class AddrMsg //存地址信息,用于地址查找，地址一览表和编译地址错误检查使用
{
public:
    QGraphicsItem *pItem; //扫描的item
    int nSheetIndex;      //画面序号
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

    int count = pSceneSheet.size(); //画面总数
    QList<QGraphicsItem *> Items;
    for(int i = 0 ; i < count; i++) //扫描所有画面
    {
        Items = pSceneSheet[i]->items();   //当前页面所有的item
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
                        pAddrMsg->nSheetIndex = i;                      //画面序号
                        pAddrMsg->pItem       = pItem;                  //当前控件
                        pAddrMsg->Address     = item->getAllItemAddr(); //地址vector
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

    //以下是检查工程管理器模块的地址
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
 *函数名称：OnFillVisiblePage
 *函数功能：存储显现页面的地址信息
 *参数含义：
 *sList：控件的存储信息
 *sBtnName：控件的名称
 *nSheetIndex：画面序号
 *edit by zqh
 ******************************************************************/
void MainWindow::OnFillVisiblePage(QStringList sList,QString sBtnName,
                                   int nSheetIndex)
{
    
}

/*******************************************************************
 *函数名称：OnFillAdvancedPage
 *函数功能：存储高级页面的地址信息
 *参数含义：
 *sList：控件的存储信息
 *sBtnName：控件的名称
 *edit by zqh
 ******************************************************************/
void MainWindow::OnFillAdvancedPage(QStringList sList,QString sBtnName,
                                    int nSheetIndex)
{
    
}

/*******************************************************************
 *函数名称：MsgOutputListDoubleClicked
 *函数功能：双击信息输出窗口的响应函数
 *参数含义：
 *nRow：行号
 *nClomn：列号
 *edit by zqh
 ******************************************************************/
void MainWindow::MsgOutputListDoubleClicked(int nRow, int nClomn)
{
    int     nIndex = 0;
    QString str    = "";

    QTableWidgetItem *mItem;         //设置最后项为选中状态
    mItem = pMainList->item(nRow,nClomn); //0
    if(!mItem)
    {
        return;
    }
    str    = mItem->text();  //获得内容
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
        pSceneSheet[nActiveSheetIndex]->clearSelection();//清除所有选择
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

void MainWindow::OnDisplayAddrUseDlg()//打开地址使用一览表对话框
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
        QMessageBox box(QMessageBox::Information,tr("提示"),tr("编译之前要保存当前工程，是否保存？"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("是"));
        box.button(QMessageBox::Cancel)->setText(tr("取消"));
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
    if(!m_rightDock->isVisible())   //显示信息输出窗口
    {
        m_rightDock->setVisible(true);
        ui->action_41->setChecked(true);
    }
    bool bReturnFlag = true;
    pMainList->clear();
    pMainList->setRowCount(0);

    //编译时地址检查是否正确
    bReturnFlag = CheckAddressInCompile();
    if(!bReturnFlag)
    {
        return false;
    }

    //检查驱动文件
    //CheckDriver();
    //if(!this->CheckDriver())
      //  return false;
    //保存系统参数和控件数据

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
        QMessageBox box(QMessageBox::Information,tr(""),tr("有其他组态正在编译中，继续可能会造成文件冲突，是否继续"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("是"));
        box.button(QMessageBox::Cancel)->setText(tr("取消"));
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
	//开始离线模拟
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
void MainWindow::closeEvent(QCloseEvent *event)//点击关闭按钮事件
{
    //add by wuxiyang 判断是否退出，若退出保存设置
    bool is_close = true;
    if(is_Is)
   {
       event->accept();
   }

   else if(thread && thread->isRunning())
   {
       QMessageBox box(QMessageBox::Information,tr("提示"),tr("编译正在进行中，是否强制关闭"),QMessageBox::Ok|QMessageBox::No,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
       box.button(QMessageBox::Ok)->setText(tr("是"));
       box.button(QMessageBox::No)->setText(tr("否"));
       box.exec();
       if(box.clickedButton()== box.button(QMessageBox::Ok))//当点击了保存当前工程
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
       QMessageBox box(QMessageBox::Information,tr("提示"),tr("是否保存当前工程"),QMessageBox::Ok|QMessageBox::No|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
       box.button(QMessageBox::Ok)->setText(tr("是"));
       box.button(QMessageBox::No)->setText(tr("否"));
       box.button(QMessageBox::Cancel)->setText(tr("取消"));
       box.exec();
       if(box.clickedButton()== box.button(QMessageBox::Ok))//当点击了保存当前工程
       {
           createsavedlg();
           //ui->toolBox->hide();
           event->accept();
       }
       else if(box.clickedButton()== box.button(QMessageBox::No))//当点击了否
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


//退出时间
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
        QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr("名字已经存在，请重新输入"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        msg.addButton(tr("确定"),QMessageBox::AcceptRole);
        msg.exec();
        return 1;
    }
    return 0;
}//

void MainWindow::listChange(int index)
{
    return;
    /*if(index==0)//标准
    {
        if(!is_haveScreen)
        {
            return;
        }//
        for(int i=0;i<screenSubItem_vector.size();i++)
        {
            screenSubItem_vector[i]->setHidden(true);
        }//隐藏画面的子项的子项

       upDatetreeScreenItem();//更新画面的子项

    }//
    else if(index==1)//元件列表
    {
        if(!is_haveScreen)
        {
            return;
        }
            for(int i=0;i<screenSubItem_vector.size();i++)
            {
                screenSubItem_vector[i]->setHidden(false);
            }//显示画面的子项的子项
             upDatetreeScreenItem();//更新画面的子项
    }//
    else if(index==2)//预览
    {
        if(!is_haveScreen)
        {
            return;
        }

         for(int i=0;i<screenSubItem_vector.size();i++)
         {
            screenSubItem_vector[i]->setHidden(true);
        }//隐藏画面的子项的子项
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
    if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nIsSceneOrWindow==2)//自定义键盘
     {
        return;//不做操作
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
  /*if(list_style->currentIndex()==0||list_style->currentIndex()==2)//标准、预览
  {
      for(int i=0;i<screenSubItem_vector.size();i++)
      {
           screenSubItem_vector.at(i)->setHidden(true);
      }
  }
  else if(list_style->currentIndex()==1)//元件
  {
      for(int i=0;i<screenSubItem_vector.size();i++)
      {
           screenSubItem_vector.at(i)->setHidden(false);
      }
  }*/
}//

void MainWindow::PreviewWindow()
{
    updatePreviewWindow() ;//更新预览窗口
}

/*********************************************************************************
  *函数名称：updatePreviewWindow
  *函数功能：只有在工程管理器选择窗口预览的时候才处理截图
  *编辑：郑启红
  *时间：2012.02.27
  ********************************************************************************/
void MainWindow::updatePreviewWindow() //更新预览窗口
{
//list_style
    /*if(list_style->currentIndex() != 2)//不是预览窗口不作处理
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
    if(pSceneSheet[i]->m_sceneTypeProp.nIsSceneOrWindow==1)//窗口
    {
        if(pwnd->m_pSamSysParame->m_projectProp.nDisplayMode==1)//垂直
        {
           pSceneSheet[i]->render(&painter,QRectF(0,0,nHeight,nWidth),QRectF(0,0,pSceneSheet[i]->width()-50,pSceneSheet[i]->height()),Qt::IgnoreAspectRatio);
        }
        else
        {
          pSceneSheet[i]->render(&painter,QRectF(0,0,nWidth,nHeight),QRectF(0,0,pSceneSheet[i]->width(),pSceneSheet[i]->height()),Qt::IgnoreAspectRatio);
        }
    }
    else if(pSceneSheet[i]->m_sceneTypeProp.nIsSceneOrWindow==0)//画面
    {
        pSceneSheet[i]->render(&painter,QRectF(0,0,nWidth,nHeight),QRectF(0,0,pSceneSheet[i]->width(),pSceneSheet[i]->height()),Qt::IgnoreAspectRatio);
    }
    else if(pSceneSheet[i]->m_sceneTypeProp.nIsSceneOrWindow==2)//自定义键盘
    {
        pSceneSheet[i]->render(&painter,QRectF(0,0,nWidth,nHeight),QRectF(0,0,pSceneSheet[i]->width(),pSceneSheet[i]->height()),Qt::IgnoreAspectRatio);
    }
    painter.end();
    if(pixmap.isNull())
    {
        return;
    }
    pixmap.save("C:/scene.png");
    if( nActiveSheetIndex == label.size()) //是新建
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
  *函数名称：updateAllPreviewWindow
  *函数功能：只有在工程管理器选择窗口预览的时重新加载截图
  *编辑：郑启红
  *时间：2012.02.27
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
         if(pSceneSheet[i]->nIsSceneOrWindow==1)//窗口
         {
             if(pwnd->m_pSamSysParame->m_projectProp.nDisplayMode==1)//垂直
             {
                pSceneSheet[i]->render(&painter,QRectF(lab->x(),lab->y(),nHeight,nWidth),QRectF(0,0,pSceneSheet[i]->width()-50,pSceneSheet[i]->height()),Qt::IgnoreAspectRatio);
             }
             else
             {
               pSceneSheet[i]->render(&painter,QRectF(lab->x(),lab->y(),nWidth,nHeight),QRectF(0,0,pSceneSheet[i]->width(),pSceneSheet[i]->height()),Qt::IgnoreAspectRatio);
             }
         }
         else if(pSceneSheet[i]->nIsSceneOrWindow==0)//画面
         {
             pSceneSheet[i]->render(&painter,QRectF(0,0,nWidth,nHeight),QRectF(0,0,pSceneSheet[i]->width(),pSceneSheet[i]->height()),Qt::IgnoreAspectRatio);
         }
         else if(pSceneSheet[i]->nIsSceneOrWindow==2)//自定义键盘
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
    //if(list_style->currentIndex()==0)//标准
    {
        delete copyScreen_Item;
        copyScreen_Item=NULL;
        delete copyWindow_Item;
        copyWindow_Item=NULL;
        delete copyUserKeyboard;
        copyUserKeyboard=NULL;
        screen->setHidden(true);
        window->setHidden(true);
        TreeKeyboard->setHidden(true);//用户自定义键盘

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
    /*if(list_style->currentIndex()==1)//元件
    {
        delete copyScreen_Item;
        copyScreen_Item=NULL;
        delete copyWindow_Item;
        copyWindow_Item=NULL;
        delete copyUserKeyboard;//用户自定义键盘
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
    if(!pwnd->is_Save)//有工程没保存的情况下
    {
        QMessageBox box(QMessageBox::Information,tr("提示"),tr("是否保存当前工程"),QMessageBox::Ok|QMessageBox::No|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("是"));
        box.button(QMessageBox::No)->setText(tr("否"));
        box.button(QMessageBox::Cancel)->setText(tr("取消"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::Ok))//当点击了保存当前工程
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
        else if(box.clickedButton()== box.button(QMessageBox::No))//当点击了否
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
    else//当工程已经保存
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
/*返回0正确
 *返回1最小值大于最大值
 *返回2最小值超限
 *返回3最大值超限
 */
int MainWindow::CheckMinMax(QString Min, QString Max, int DataType,int CheckType)
{
    //CheckType 标示是0 最大最小值还是 ；标示是1 高限值低限值
    QString str1,str2;
    if(CheckType==0)
    {
        str1=tr("最大值");
        str2=tr("最小值");
    }
    else if(CheckType==1)
    {
        str1=tr("高限值");
        str2=tr("低限值");
    }
    QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr(""),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("确定"),QMessageBox::AcceptRole);

    QLibrary  lib("Check.dll");
    if (!lib.load())
    {
        msg.setText(tr("Check.dll未找到！"));
        msg.exec();

        return 0;//返回参数不对，应该重新设置出错返回参数
    }
    typedef int (*ADDPROC)( QString ,QString , int );
    ADDPROC CheckMinMax= (ADDPROC)lib.resolve("CheckMinMax");
    switch(CheckMinMax(Min,Max,DataType))
    {
    case 0:
        return 0;
        break;
    case 1:
        msg.setText(str2+tr("大于")+str1);
        msg.exec();
        return 1;
        break;
    case 2:
        msg.setText(str2+tr("超限!"));//最小
        msg.exec();
        return 2;
        break;
    case 3:
        msg.setText(str1+tr("超限！"));//最大
        msg.exec();
        return 3;
        break;
    case 4:
        msg.setText(str2+tr("有误！"));//最小
        msg.exec();
        return 4;
        break;
    case 5:
        msg.setText(str1+tr("有误！"));//最大
        msg.exec();
        return 5;
        break;
    default:
        msg.setText(tr("判断最大最小值返回值有误！"));
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
		value = sourceStr.mid(2,sourceStr.length()-2).toInt();//匹配LB
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
	else if (regEx_LW.exactMatch(sourceStr) || regEx_RWI.exactMatch(sourceStr))//匹配LW,RWI
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
	else if (regEx_PLC.exactMatch(sourceStr))//匹配外部地址
	{
		return CheckExternAddr(keyboard, sourceStr, Addr_Type);
	}
	else //不能识别的字符
	{
		return ADDR_OTHER_ERROR;
	}
	
	
}

//检查外部地址输入格式
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
    msg.addButton(tr("确定"),QMessageBox::AcceptRole);
    
    
	int iFlg= CheckString(keyboard,pLineEdit->text(),Addr_Type);
    switch(iFlg)
    {
    case ADDR_CORRECT://无错误
        break;
    case ADDR_STRING_NULL://数据为空
        msg.setText(WaringMsg+tr("输入地址不能为空！"));
        msg.exec();
        pLineEdit->setFocus();
        pLineEdit->selectAll();
        return 0;
	case ILLEGAL_REG://寄存器类型不匹配错误
		msg.setText(WaringMsg+tr("寄存器类型与地址要求不匹配！"));
		msg.exec();
		pLineEdit->setFocus();
		pLineEdit->selectAll();
		return 0;
	case INVALID_CONNECT://手动输入地址检查的时候没有该链接
        msg.setText(WaringMsg+tr("没有添加该协议！"));
		msg.exec();
		pLineEdit->setFocus();
		pLineEdit->selectAll();
		return 0;
	case ADDR_OUT_BOUND://数据超限 返回值为限制值 正数为最高限值 负数为最低限值
		
		msg.setText(WaringMsg+tr("地址值超出范围！"));
		msg.exec();
		pLineEdit->setFocus();
		pLineEdit->selectAll();
		return 0;
	default://输入格式错误
        msg.setText(WaringMsg+tr("输入格式错误！"));
        msg.exec();
        pLineEdit->setFocus();
        pLineEdit->selectAll();
        return 0;
    
    }
    keyboard.nAddrType = Addr_Type; //记录字位标示
    pLineEdit->setText(keyboard.sShowAddr);
    
    return 1;
	
}
int MainWindow::IsMyAddressCheckRight(Keyboard &keyboard,QString WaringMsg,QLineEdit *pLineEdit,int Addr_Type, QSpinBox *pSpinBox)
{
    QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr(""),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("确定"),QMessageBox::AcceptRole);
    QLibrary  lib("Check.dll");
    if (!lib.load())
    {
        msg.setText(tr("Check.dll未找到！"));
        msg.exec();
        return 0;//返回参数不对，应该重新设置出错返回参数
    }
    typedef int (*ADDPROC)( QString ,int , Keyboard &,QVector<plcCommunicateProp>);
    ADDPROC AddressCheck = NULL;
    AddressCheck = (ADDPROC)lib.resolve("IsAddressCheckRight");
    if (NULL == AddressCheck)
    {
        msg.setText(tr("文件损坏请重新安装应用程序！"));
        msg.exec();
        return 0;
    }
    int iFlg= AddressCheck(pLineEdit->text(),Addr_Type,keyboard,m_pSamSysParame->m_qvcPlcCommunicate);
    switch(iFlg)
    {
    case 0://无错误
        break;
    case -1://数据为空
        //msg.setText(WaringMsg+tr("输入地址不能为空！"));
        //msg.exec();
        //pLineEdit->setFocus();
        return 0;
    case 1://使用进制错误 要求为8进制数据
    case 2://使用进制错误 要求为10进制数据
    case 3://使用进制错误 要求为16进制数据
    case 4://输入格式错误
        //msg.setText(WaringMsg+tr("输入格式错误！"));
        //msg.exec();
        //pLineEdit->setFocus();
        //pSpinBox->setFocus();
        return 0;

    case 5://寄存器类型不匹配错误
        //msg.setText(WaringMsg+tr("寄存器类型与地址要求不匹配！"));
        //msg.exec();
        //pLineEdit->setFocus();
        pSpinBox->setFocus();
        return 0;

    case 6://手动输入地址检查的时候没有该链接
        //msg.setText(WaringMsg+tr("没有添加该连接口！"));
        //msg.exec();
        //pLineEdit->setFocus();
        //pSpinBox->setFocus();
        return 0;

    default://数据超限 返回值为限制值 正数为最高限值 负数为最低限值
        if(iFlg<0)
        {
            msg.setText(WaringMsg+tr("该寄存器的最小地址为：")+QString::number(0-iFlg));
        }
        else if(iFlg>0)
        {
            msg.setText(WaringMsg+tr("该寄存器的最大地址为：")+QString::number(iFlg));
        }
        //msg.exec();
        //pLineEdit->setFocus();
        //pSpinBox->setFocus();
        return 0;
    }
    keyboard.nAddrType = Addr_Type; //记录字位标示
    pLineEdit->setText(keyboard.sShowAddr);
    lib.unload();//释放dll文件
    return 1;
}

//标准工具栏上的点击事件
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

//绘图工具栏上的点击事件
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

//物件工具栏上的点击事件
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

//调试工具栏上的点击事件
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

//标准状态栏上的点击事件
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

//信息输出窗口的点击事件
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

//工程管理器的点击事件
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

//菜单上面的画面属性
/*void MainWindow::on_action_93_triggered()
{
    newscreen_property();
}*/

//菜单上面的删除画面
/*void MainWindow::on_action_94_triggered()
{
    newscreen_delete();
}*/

//显示编号对话框
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
    Items = pSceneSheet[nActiveSheetIndex]->items();    //当前页面所有的item
    for(int j = 0; j < Items.size(); j++)   //扫描当前页面的所有控件
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

QString MainWindow::remove_leftZero(QString sTmp)//移除字符串左边的0
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
    //删除自定义键盘相关信息

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
    /*this->link->takeChildren();//移除连接里面所有的子项
    pwnd->vTreeLinkType.clear();//清除链接
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

void MainWindow::openPro_reTreeCtl()//打开工程时刷新树形控件
{
    tree->expandAll();
    tree0->expandAll();

    QString temp="";
    QList<QGraphicsItem *> Items;
    //QList<QGraphicsItem *> ChildItems;
    QGraphicsItem *pItem;
    //QStringList sList;
    //QString sNo="";
    //画面清空
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
        if(pSceneSheet[i]->nIsSceneOrWindow ==0)//等于0位画面
        {
			
            newScreen[i]=new QTreeWidgetItem(screen,QStringList(temp+":"+pSceneSheet[i]->sNewScreenName));
            screen->addChild(newScreen[i]);
            Items = pSceneSheet[i]->items();    //当前页面所有的item
            index=i;
            for(int j = 0; j < Items.size(); j++)   //扫描当前页面的所有控件
            {
                pItem = Items.at(j);
                nKey=pItem->data(GROUP_TYPE_KEY).toInt(); //取出key值
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
            index=i;//当前页面所有的item
            for(int j = 0; j < Items.size(); j++)   //扫描当前页面的所有控件
            {
                pItem = Items.at(j);
                nKey=pItem->data(GROUP_TYPE_KEY).toInt(); //取出key值
                if(nKey!=USER_DEFINE_GROUP)
                {
                    UserGroup(pItem,index);
                }
            }
        }//
        else if(pSceneSheet[i]->nIsSceneOrWindow ==2)//用户自定义键盘
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

    //数位报警
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

    //连接
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
    else//旧版本
    {
        int connect = pwnd->m_pSamSysParame->m_qvcConnect.size();
        if(connect < 5)
        {
            stConnect con;
            //con.sConnectName = tr("以太网");
            //con.eConnectPort = i;//com1
            con.bUseRelationPort = false;//默认不转发
            con.eRelationPort = 0;
            con.nScreenNo = 1;
            con.nBaudRate = 9600;
            con.nDataBits = 1;
            con.nStopBit = 0;
            con.nCheckType = 0;
            con.bMasterScreen      = 1;//主屏
            con.bConnectScreenPort = 0;//连接PLC口
            con.nSlaveScreenNum    = 1;
            //con.nIntervalTime = 1;
            con.sIpAddr = QString("192.168.1.1");
            con.nNetPortNum = 12345;

            if(4 == connect)
            {
                con.sConnectName = tr("CAN总线");
                con.eConnectPort = 4;//CAN总线
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
                con.sConnectName = tr("CAN总线");
                con.eConnectPort = 4;//CAN总线
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

    //报警登陆
    QList<QTreeWidgetItem *> baojingItem = alarmlog->takeChildren();
    baojingItem.clear();

    int baojingCount=pwnd->m_pSamSysParame->m_qvcAlarm.size();
    for(int i=0;i<baojingCount;i++){
        QTreeWidgetItem *baojings=new QTreeWidgetItem(alarmlog,QStringList(pwnd->m_pSamSysParame->m_qvcAlarm[i].alarmName));
        alarmlog->addChild(baojings);
        baojings->setIcon(0,QIcon(":/btn/images/alarm.ico"));
    }


    //数据采集
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

void MainWindow::UserGroup(QGraphicsItem *pItem,int index )//打开的时候来熟悉编号（有自定义组合的空间）
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
         upDatetreeScreenItem();//更新画面的子项
    }
    /*else if(list_style->currentIndex()==1)
    {
        upDatetreeScreenItem();//更新画面的子项
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
        sList = pItem->data(GROUP_DATALIST_KEY).toStringList(); //取出每个item的所有数据
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
        //pSceneSheet[nActiveSheetIndex]->removeItem(item);//移除旧ITEM
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
        //pSceneSheet[nActiveSheetIndex]->removeItem(item);//移除旧ITEM
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
       // pSceneSheet[nActiveSheetIndex]->removeItem(item);//移除旧ITEM

    }
    XYtrendChartDlg->deleteLater();
    XYtrendChartDlg = NULL;
}

//整个编译流程：
//1，检查相关数据的正确性，如地址等
//2，编译全局参数部分：包括系统参数，报警，配方，数据采集
//3，编译画面已经item
//4，编译并提取item的图片文件
bool MainWindow::USBCompile(QSqlDatabase &db,bool bsimulator) //编译
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

    //保存上载组态

    emit SignalInformation(tr("准备组态数据..."), MSG_NORMAL);

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
    emit SignalInformation(tr("编译PLC程序..."), MSG_NORMAL);

    if(!compilePlcPrj())
    {
        emit SignalInformation(tr("编译PLC程序出错..."), MSG_ERROR);
        QFile::remove("gEKip");
        return false;
    }
#endif

    emit SignalInformation(tr("提取控件数据..."), MSG_NORMAL);
    //系统参数部分编译生成数据库文件

    //同步开始脚本打包线程
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
        macroTrd = new MacroCmptrd();//脚本打包线程
        macroTrd->startCompress(macros);
    }


    m_pSamSysParame->compile(db,counter,bsimulator);

    compileVarTable(db,counter);
    compileInitLibrary(db,counter);
    compileGlobalLibrary(db,counter);

    //收集系统参数部分的地址
    addrsInSysPrarm = addrsInScene;


    qDebug() << "addrsInScene  1"<<addrsInScene.keys();
    //场景部分的编译
    int totalNum = pSceneSheet.size();
    //int sceneId,UserKeyboardId;
    for(int i = 0,sceneId = 0,UserKeyboardId = 0; i < totalNum; i++)
    {
        int index;
        addrsInScene.clear();
        //qDebug()<<"nIsSceneOrWindow = " << pSceneSheet[i]->nIsSceneOrWindow;
        if(pSceneSheet[i]->nIsSceneOrWindow == 2)// 是自定义键盘
        {
            UserKeyboardId++;
            index = UserKeyboardId;
        }
        else                                                     //是窗口或者画面
        {
            sceneId++;
            index = sceneId;
        }
        pSceneSheet[i]->compile(db,index, counter);

		//收集场景控件部分的地址
        addrsInScene = addrsInScene+addrsInSysPrarm;
        //qDebug() << "addrsInScene  "<<addrsInScene.keys();
		compileArrangeAddr(db,index);
    }

    emit SignalInformation(tr("编译字体库..."), MSG_NORMAL);
	getAllFontNames(db);

    emit SignalInformation(tr("编译脚本库..."), MSG_NORMAL);

    if(macroTrd)
    {
        bool bResult = false;
        QString macroName;
        if(macroTrd->wait(300000))//正常结束
        {
            bResult = macroTrd->bSucess;
            macroName = macroTrd->m_strLibName;
            if(!bResult)
            {
                QString strError = QString(tr("编译脚本库:%1 出错...")).arg(macroName);
                emit SignalInformation(strError, MSG_ERROR);
            }
        }
        else//脚本打包超时
        {
            emit SignalInformation(tr("编译脚本超时"), MSG_ERROR);
        }

        if(!bResult)
        {
            QFile::remove("gEKip");
            QFile::remove("sdmacro\\ml\\ml.jar");
            emit SignalInformation(tr("编译失败..."), MSG_ERROR);
            isCompiled = false;
            return false;
        }
    }

    emit SignalInformation(tr("编译成功..."), MSG_NORMAL);
    isCompiled = false;
    return true;
}

//地址整理并编译
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
	stProtocol cModel;// 当前的设备
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

//将整理后的vector 插入数据库
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
		sqlquery.bindValue(":nSceneId",QVariant(nSceneId));// 所属画面或窗口序号
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

	stProtocol cModel;// 当前的设备
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
    case 3://以太网
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
//调用协议文件，对vector 进行地址整理并返回
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

    //插入fontmap到数据库
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
        case MSG_NORMAL://正常，白色
            {
                pTableWidgetItem->setBackground(QBrush(QColor(255,255,255)));
                break;
            }
        case MSG_WARNING://警告，黄色
            {
                pTableWidgetItem->setForeground(QBrush(QColor(170,85,0)));
                break;
            }
        case MSG_ERROR://错误，红色
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
        case MSG_NORMAL://正常，白色
            {
                pTableWidgetItem->setBackground(QBrush(QColor(255,255,255)));
                break;
            }
        case MSG_WARNING://警告，黄色
            {
                pTableWidgetItem->setForeground(QBrush(QColor(170,85,0)));
                break;
            }
        case MSG_ERROR://错误，红色
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
    OnFillAddressMsgClass();        //填充地址信息

    int nCount = vAddrMsg.size();       //长度
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
            nIndex = vAddrMsg.at(i)->nSheetIndex; //画面序号
            //sAddr = vAddrMsg.at(i)->Address[j].addr.sShowAddr;  //取地址
            //nType = vAddrMsg.at(i)->Address[j].addr.nAddrType; //地址类型
            sAddr = vAddrMsg.at(i)->Address[j].pAddr->sShowAddr;  //取地址
            nType = vAddrMsg.at(i)->Address[j].pAddr->nAddrType; //地址类型

            if(sAddr.isEmpty())
            {
                qDebug() << "sAddr.isEmpty()";
                //sAddrUse =pwnd->vAddrMsg.at(i)->Address[j].addr.sPlcRegTypeStr;    //控件使用地址名称
                sAddrUse =pwnd->vAddrMsg.at(i)->Address[j].str;    //控件使用地址名称
                QString itemName;
                QItemGroup *itemGrp = dynamic_cast<QItemGroup *> (pItem);
                if(itemGrp)
                {
                    itemName = itemGrp->getItemName();
                }
                if (pItem)//控件
                {
                    sScreenName=tr("画面 ");
                    if (pSceneSheet.size()> nIndex)
                    {
                        sScreenName = pSceneSheet[nIndex]->sNewScreenName;
                    }
                }
                else							//工程管理器
                {
                    sScreenName=tr("工程管理器 "); //输出信息
                }
                pMsgOutPut = new MsgOutPut ;//信息输出窗口双击要处理的类
                pMsgOutPut->pItem = pItem;
                pMsgOutPut->nSheetIndex = nIndex;

                str = tr("error:")+sScreenName+tr("-")+itemName+sAddrUse+tr("输入有误");
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

                nReturnFlag = IsAddressCheckRightInCompile(sAddr,nType); //检查地址是否正确
                qDebug() << "ADDR_CHECK:" << sAddr << nType << nReturnFlag;
                if(!nReturnFlag) //地址不正确
                {
                    //sAddrUse =pwnd->vAddrMsg.at(i)->Address[j].addr.sPlcRegTypeStr;    //控件使用地址名称
                    sAddrUse =pwnd->vAddrMsg.at(i)->Address[j].str;    //控件使用地址名称
                    QString itemName;
                    QItemGroup *itemGrp = dynamic_cast<QItemGroup *> (pItem);
                    if(itemGrp)
                    {
                        itemName = itemGrp->getItemName();
                    }
                    if(pItem)//是控件的地址
                    {
                        sScreenName=tr("画面 ");
                        if (pSceneSheet.size()> nIndex)
                        {
                            sScreenName = pSceneSheet[nIndex]->sNewScreenName;
                        }
                    }
                    else     //是工程管理器中地址
                    {
                        sScreenName=tr("工程管理器 "); //输出信息
                    }

                    pMsgOutPut = new MsgOutPut ;//信息输出窗口双击要处理的类
                    pMsgOutPut->pItem = pItem;
                    pMsgOutPut->nSheetIndex = nIndex;

                    str = tr("error:")+sScreenName+tr("-")+itemName+sAddrUse+tr("输入有误");
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
    /***************HMI状态*******************/
    pAddrMsg = new AddrMsg;
    pAddrMsg->nSheetIndex = 0;
    pAddrMsg->pItem = NULL;

    //时钟

    if(m_pSamSysParame->m_clockProp.bWTimeToPlc)//写时间到PLC
    {
        shareAddressCode(m_pSamSysParame->m_clockProp.mWTimeToPlc.mCtlAddr, tr("时钟写入控制地址"));
        if(m_pSamSysParame->m_clockProp.mWTimeToPlc.nStartType == 1)
        {
            shareAddressCode(m_pSamSysParame->m_clockProp.mWTimeToPlc.mTriggerAddr, tr("时钟写入触发地址"));
        }
    }
    else if(m_pSamSysParame->m_clockProp.bRTimeFromPlc)//与PLC时间相同
    {
        shareAddressCode(m_pSamSysParame->m_clockProp.mRTimeFromPlc.mCtlAddr, tr("时钟读取控制地址"));
        if(m_pSamSysParame->m_clockProp.mRTimeFromPlc.nStartType == 1)
        {
            shareAddressCode(m_pSamSysParame->m_clockProp.mRTimeFromPlc.mTriggerAddr, tr("时钟读取触发地址"));
        }
    }

    //数据控制
    //是否写当前画面编号到PLC
    if(m_pSamSysParame->m_mixGlobalVar.m_bCurScreenNum)
    {
        shareAddressCode(m_pSamSysParame->m_mixGlobalVar.m_keyCurScreen, tr("数据控制-当前画面编号 地址"));
    }
    //是否写当前配方编号到PLC
    if(m_pSamSysParame->m_mixGlobalVar.m_bCurFormulaNum)
    {
        shareAddressCode(m_pSamSysParame->m_mixGlobalVar.m_keyCurFormula, tr("数据控制-当前配方编号 地址"));
    }

    //是否写当前语言编号到PLC
    if(m_pSamSysParame->m_mixGlobalVar.m_bCurLanguageNum)
    {
        shareAddressCode(m_pSamSysParame->m_mixGlobalVar.m_keyCurLanguage, tr("数据控制-当前语言编号 地址"));
    }

    //字控制画面切换
    if(m_pSamSysParame->m_mixGlobalVar.m_bWordAddrScreenNum)
    {
        shareAddressCode(m_pSamSysParame->m_mixGlobalVar.m_keyWordAddrScreen, tr("数据控制-字地址控制画面切换"));
    }

    if(m_pSamSysParame->m_mixGlobalVar.m_bBitSenceExch)
    {
        for (int i=0; i<m_pSamSysParame->m_mixGlobalVar.m_vecBitSence.size();i++)
        {
            shareAddressCode(m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].mCtlSceneAddr,tr("数据控制-位地址控制画面切换"));
        }
    }

    //数据采集
    int samplesize = m_pSamSysParame->m_loadDataSampling.size();
    for(int i=0; i<samplesize; i++)
    {
        DATA_SAMPLING samGrp = m_pSamSysParame->m_loadDataSampling[i];
        QString samGrpName = tr("数据采样");
        if(m_pSamSysParame->m_vecDataSamplingStr.size() > i)
        {
            samGrpName = m_pSamSysParame->m_vecDataSamplingStr[i];
        }
		for (int j=0; j<m_pSamSysParame->m_loadDataSampling[i].m_dataTable.size(); j++)
		{
			shareAddressCode( m_pSamSysParame->m_loadDataSampling[i].m_dataTable[j].keyAddress,
				samGrpName+tr("采样地址"));
		}
        //取满通知地址
        if (samGrp.bFullNotic && m_pSamSysParame->m_loadDataSampling[i].nDataSampType == 2 )
        {
            shareAddressCode(m_pSamSysParame->m_loadDataSampling[i].strNoticAddrId,samGrpName+tr("取满通知地址"));
        }
        //控制采样地址
        if (samGrp.bAddrCtlSamp)
        {
            shareAddressCode(m_pSamSysParame->m_loadDataSampling[i].strCtlSampAddrId,samGrpName+tr("控制采样地址"));
        }

        //动态时间范围地址
        if (samGrp.bDynTimeRange)
        {
            shareAddressCode(m_pSamSysParame->m_loadDataSampling[i].startTimeAddr,samGrpName+tr("采样起始时间地址"));
            shareAddressCode(m_pSamSysParame->m_loadDataSampling[i].endTimeAddr,samGrpName+tr("采样结束时间地址"));
        }
        //动态频率地址
        if (samGrp.bDynSampleRate)
        {
            shareAddressCode(m_pSamSysParame->m_loadDataSampling[i].dynRateAddr,samGrpName+tr("动态频率地址"));
        }
        //控制数据保存地址
        if (samGrp.bSaveToFile&& m_pSamSysParame->m_loadDataSampling[i].nDataSampType == 2)
        {
            shareAddressCode(m_pSamSysParame->m_loadDataSampling[i].keyCtlSaveAddr,samGrpName+tr("控制数据保存地址"));
        }
    }
    //报警登录
    for (int i=0; i<m_pSamSysParame->m_qvcAlarm.size(); i++)
    {
            QString groupName = m_pSamSysParame->m_qvcAlarm.at(i).alarmName;
            for (int j=0; j<m_pSamSysParame->m_qvcAlarm.at(i).alarms.size();j++)
            {
                    shareAddressCode(m_pSamSysParame->m_qvcAlarm[i].alarms[j].addr,groupName+tr("报警监视地址"));
            }
    }

    //wxy 增加版本控制，避免打开的旧工程无法编译
    if(pwnd->getProVersion() >= 3125)
    {
        QString groupName = tr("全局变量: ");
        for(int i = 0; i < g_Vars.size(); i++)
        {
            shareAddressCode(g_Vars[i].addr, groupName+g_Vars.at(i).varName+tr(" 地址: "));
        }
    }

    //脚本

    for (int i=0; i<macros.size(); i++)
	{
        QString groupName = macros.at(i).libName;
        groupName = tr("脚本: ")+groupName+tr(" 变量: ");

        for (int j=0; j<macros[i].m_Vars.size();j++)
        {
            //QVector <VarPro> vars = macros[i].m_Vars;
            shareAddressCode(macros[i].m_Vars[j].addr,
                             groupName+macros[i].m_Vars.at(j).varName+tr(" 地址: "));
		}
	}

    //全局脚本
	for (int i=0; i<m_pSamSysParame->m_qvcGlobalMaroProp.size(); i++)
	{
		QString groupName = tr("全局脚本");
		groupName += QString::number(i);

		if (m_pSamSysParame->m_qvcGlobalMaroProp.at(i).bIfCtrl)
		{
			shareAddressCode(m_pSamSysParame->m_qvcGlobalMaroProp[i].mCtlAddr,
				groupName+tr("控制地址"));
		}

	}
    //画面脚本
	for (int i=0; i<pSceneSheet.size(); i++)
	{
		QString groupName =pSceneSheet[i]->sNewScreenName+ tr("脚本");
		for (int j=0; j<pSceneSheet[i]->listScript.size(); j++)
		{
			if (pSceneSheet[i]->listScript.at(j).scriptBShow)
			{
				groupName += QString::number(j);
				shareAddressCode(pSceneSheet[i]->listScript[j].scriptAddr,
					groupName+tr("控制地址"));
			}
		}

	}

	//资料传输
	for (int i=0; i<m_pSamSysParame->m_qvcdataTransProp.size(); i++)
	{
		QString groupName = tr("资料传输");

		if(m_pSamSysParame->m_qvcdataTransProp.at(i).nTriggerType == 2)
		{
			shareAddressCode(m_pSamSysParame->m_qvcdataTransProp[i].mTriggerAddr,
				groupName+tr("触发地址"));
		}
		shareAddressCode(m_pSamSysParame->m_qvcdataTransProp[i].mSourceAddr,
			groupName+tr("源地址"));
		shareAddressCode(m_pSamSysParame->m_qvcdataTransProp[i].mTargetAddr,
			groupName+tr("目标地址"));
	}

    /***************配方*******************/

    int Recipesize = m_pSamSysParame->m_qvcRecipe.size();
    for(int i=0; i<Recipesize; i++)
    {
        bool bContinue = false;
        QString samGrpName = tr("配方组：")+m_pSamSysParame->m_qvcRecipe[i].sName;//配方组名称
        if(m_pSamSysParame->m_qvcRecipe[i].bCtlAddr)
        {
            shareAddressCode( m_pSamSysParame->m_qvcRecipe[i].addrCtl, samGrpName+tr("控制地址"));
        }

        if(m_pSamSysParame->m_qvcRecipe[i].bCompleteNotic)
        {
            shareAddressCode( m_pSamSysParame->m_qvcRecipe[i].addrNotic, samGrpName+tr("完成通知地址"));
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
                shareAddressCode( m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].addr, samGrpName+tr("配方地址"), i+1);
            }
            else
            {
                shareAddressCode( m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].addr, samGrpName+tr("配方地址"));
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

void MainWindow::OnCreateAnimation() //动画
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
//更新最近打开的文档
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

    if(m_pSamSysParame->m_recipeProp.bRecipeExist)//保障配方子菜单自由一个
    {
        QTreeCtrlRecipeDlg recipeDlg(this);
      recipeDlg.exec();
    }
    else
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("配方尚未建立！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
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
    //return mPicPath.value(path);//wxy不进行重复的图片操作，直接读取路径
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
    if (mPicPath.contains(path))//存在该路径
    {
        QString sName = mPicPath.value(path);
//        if(!pwnd->checkMD5(mPicMd5.value(sName), sName))//wxy进行md5检测，相同不再进行操作
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
                //重新缩放后保存图片
                if(!img.isNull())
                {
                    img = img.scaled(QSize(newSize.width(),newSize.height()));
                    img.save(sName,fmt);
                }
            }
//            QByteArray md5 = pwnd->getFileMd5(sName);//wxy更新md5码
//            mPicMd5.insert(sName, md5);
//        }
        return sName;
    }
    else
    {

        QImage picture = QImage(path);
        QList <QString> list = mPicPath.values();
        if (list.contains(path))//如果当前文件已经存在
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
//            QByteArray md5 = pwnd->getFileMd5(sName);//wxy 生成md5码
//            mPicMd5.insert(newpath, md5);
            return sName;
        }
    }

}
QString MainWindow::SaveLibPath(QString path,QSizeF size)
{
    QString date = QDateTime::currentDateTime().toString("yyMMddhhmmss");
    QString newPath;

    //从图库取得libItem并按照size进行缩放
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

    //将item保存到pixmap
    QRectF rect = libItem->sceneBoundingRect();

    QPixmap pixmap(rect.width(),rect.height());
    pixmap.fill(QColor(0,0,0,0));
    QPainter painter(&pixmap);

    QRectF target = QRectF(0,0,rect.width(),rect.height());
    rect = QRectF(rect.x(),rect.y(),rect.width()+1,rect.height()+1);
    tmpScene.render(&painter,target,rect,Qt::IgnoreAspectRatio);

    //如果已经存在该item在mLibPath中，则比较大小，并判断是否需要重新保存
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
            //重新缩放后保存图片

            if(!img.isNull())
            {
                img = img.scaled(QSize(newSize.width(),newSize.height()));
                img.save(sName,fmt);
            }
        }
        return sName;
    }
    //不存在该图片，分配文件名并保存图片，将path 插入mLibPath
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

void MainWindow::OnCutItem() //剪切
{
	pSceneSheet[nActiveSheetIndex]->actionCut();
}

void MainWindow::ExecuteOffLineMonitor() //离线模拟
{
    if(QFile::exists("gEKip"))
    {
        QMessageBox box(QMessageBox::Information,tr(""),tr("有其他组态正在编译中，继续可能会造成文件冲突，是否继续"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("是"));
        box.button(QMessageBox::Cancel)->setText(tr("取消"));
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
//        QMessageBox box(QMessageBox::Warning,tr("提示"),tr("离线模拟之前请保存工程"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
//        box.button(QMessageBox::Ok)->setText(tr("是"));
//        box.exec();
        QMessageBox box(QMessageBox::Information,tr("提示"),tr("运行离线模拟之前要保存工程，是否保存？"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("是"));
        box.button(QMessageBox::Cancel)->setText(tr("取消"));
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
void MainWindow::RunAboutDlg() //关于对话框
{
    AboutDlg about(this);
    about.exec();
}
void MainWindow::MultiCopyDlg() //多重复制
{
    QMultiCopy qmulticopydlg(this);
    qmulticopydlg.exec();
}

void MainWindow::PasteItemToScene()//
{
    //粘贴Item
    QGraphicsItem *oldItem=NULL;

    if(pSceneSheet[nActiveSheetIndex]->pasteList.size()!=0
       &&!pDrawToSceneItem&&(SamDrawTool::s_eDrawActType == SAM_DRAW_ASSY_COMPONENT))//组合图形
    {
        this->OnSingClikSpare(oldItem);

    }
    else if(pSceneSheet[nActiveSheetIndex]->pasteList.size()!=0
            &&!pDrawToSceneItem&&pSceneSheet[nActiveSheetIndex]->is_paste_singleItem)//非组合图形
    {
       // this->OnSingClikSpare(oldItem);
    }
    pSceneSheet[nActiveSheetIndex]->is_paste_singleItem=false;
    pSceneSheet[nActiveSheetIndex]->pasteList.clear();
}//

void MainWindow::initRecipeDlg()//初始化配方对话框
{
    m_pSamSysParame->m_recipeProp.sRecipeName =tr("配方1"); //配方名称
    m_pSamSysParame->m_recipeProp.sDescription =""; //描述
    m_pSamSysParame->m_recipeProp.nLanIndex=0;
    m_pSamSysParame->m_recipeProp.nRecipeLen =4;//配方长度
    m_pSamSysParame->m_recipeProp.nRecipeTotalNum =1; //配方总量
    m_pSamSysParame->m_recipeProp.nDataType =0;  //数据类别
    m_pSamSysParame->m_recipeProp.bWRecipeToPlc =false;//是否写配方到PLC
    m_pSamSysParame->m_recipeProp.bRRecipeFromPlc =false; //是否从PLC读取配方
    m_pSamSysParame->m_recipeProp.bRaddrSameWaddr =true;

    m_pSamSysParame->m_recipeProp.sRowHeadName.clear();
    m_pSamSysParame->m_recipeProp.sRowHeadName.resize(1);
    m_pSamSysParame->m_recipeProp.sRowHeadName[0].push_back("");//数据项页面的配方名称
    //m_pSamSysParame->m_recipeProp.sRowHeadName.push_back("");
    //    m_pSamSysParame->m_recipeProp.sRecipeData.push_back("");//数据

    m_pSamSysParame->m_recipeProp.mWRecipeAddr.sShowAddr ="";       //写地址
    m_pSamSysParame->m_recipeProp.mRRecipeAddr.sShowAddr ="";         //读地址

    m_pSamSysParame->m_recipeProp.sRecMemAddrRange ="RW1---RW4";    //配方记忆地址范围

    m_pSamSysParame->m_recipeProp.sCurrRecAddrRange ="RWI1---RWI4";    //当前配方地址范围
    m_pSamSysParame->m_recipeProp.sRecipeRegNum ="RWI0";    //寄存器

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

    //表格的表头
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

void MainWindow::Reverse_selection()//反向选择
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

 void MainWindow:: OnAddColorDlg(QPushButton *pbtn,ColorPickerPopup *colorPicker) //每个控件添加颜色对话框
 {
     QDesktopWidget *d = QApplication::desktop();
     int width = d->width(); //屏幕的宽度
     int height = d->height(); //屏幕的高度

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

void MainWindow:: changeItem_x()//状态栏上面的编辑框的改变
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

void MainWindow::changeItem_y()//状态栏上面的编辑框的改变
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

 void MainWindow::changeItem_w()//状态栏上面的编辑框的改变
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
 void MainWindow::changeItem_h()//状态栏上面的编辑框的改变
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
    Length = sName.length();               //编号开始符长度
    int totalSceneNum = pSceneSheet.size();
    for(i = 0; i < totalSceneNum; i++) //扫描所有画面
    {
        Items = pSceneSheet[i]->items();   //当前页面所有的item
        for(j = 0; j < Items.size(); j++)
        {
            sList = Items.at(j)->data(GROUP_DATALIST_KEY).toStringList(); //取出每个item的所有数据
            if(sList.size() < 20)
                continue;//break;
            str = sList.at(19);           //编号存在15位
            if(sName == str.left(Length)) //编号开始符相同
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
 *函数名称：IsHaveLibraryItem(QGraphicsItem *pItem)
 *函数功能：用于多状态控件按钮，判断该控件中是否含有图库图形
 *参数含义：pItem表示需要判断的item
 *返回值：  返回所使用图库文件中item
 *Name：   edit by zqh
 *Date：   2011-04-07
 *****************************************************/
QGraphicsItem * MainWindow::IsHaveLibraryItem(QGraphicsItem *pItem)
{
    int nKey = 0;
    QGraphicsItem *newItem = NULL;
    QList<QGraphicsItem *> itemList = pItem->childItems();
    DrawItemToScene GroupFunction;

    int nID = pItem->data(GROUP_TYPE_KEY).toInt();
    if(nID == GROUP_TYPE_ANIMATE) //处理动画
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
        if(nKey == LIBRARY_LIB_GROUP)//图库组合
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

void MainWindow::SlecetALL()//Ctrl+A全选操作
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
 *函数名称：OpenLibraryFile(QString str)
 *函数功能：用于多状态控件按钮，如该按钮含有图库item，则根据存储
          路径打开图库文件，查找所选择的item
 *参数含义：str表示图库item的路径
          0位置标示画面序号，1位置标示第几个item，3标示该图形
          是item还是图片(0--图形，1--图片)
 *返回值：  返回所使用图库文件中item
 *Name：   edit by zqh
 *Date：   2011-04-07
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
    QVector <SamDrawScene *> vScene;  //存画面的容器
    vScene.clear();

    if(sList.size() == 4)
    {
        QFile file(sPath);
        if(!file.open(QIODevice::ReadOnly))
            {
           // QMessageBox box(QMessageBox::Warning,tr("提示"),tr("缺少UserDefineLibraryLib.sk文件!"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            //box.button(QMessageBox::Ok)->setText(tr("确定"));
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
    //QMessageBox box(QMessageBox::Warning,tr("提示"),tr("缺少LibraryLib.sk文件!"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    //box.button(QMessageBox::Ok)->setText(tr("确定"));
    //box.exec();
    return NULL;
    }

    //以下是取图库item

    //sList中0位置标示画面序号，1位置标示第几个item，3标示该图形是item还是图片(0--图形，1--图片)
    int nSheet = sList.at(0).toInt();//画面序号
    QPainterPath path;
    QStringList slist;
    QList<QGraphicsItem *> item_list;

    //扫描基本图库
    if(sList.size() == 4) //用户自定义图库
    {
        //path.addRect(0,0,vScene.at(nSheet)->width(),vScene.at(nSheet)->height());
        //vScene.at(nSheet)->setSelectionArea(path);
        //item_list=vScene.at(nSheet)->selectedItems();
        item_list=vScene.at(nSheet)->TopItems();
    }
    else if(sList.size() == 3)//基本图库
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
//字体大小初始化函数
int MainWindow::InitFontSize(QComboBox *fontsize)
{
    if(fontsize!=NULL)
    {
        fontsize->setCurrentIndex(5);
        for(int i= 5;i <= 256;i++)    //初始化字体大小选择框
        {
            fontsize->addItem(QString("%1").arg(i));
        }
        fontsize->setEditable(true);//使下拉列表框可以编辑
        fontsize->setCurrentIndex(5);
        QIntValidator *validator=new QIntValidator(this);//设置手动输入下拉列表框的范围
        validator->setRange(5,256);
        fontsize->setValidator(validator);
        return 1;
    }
    else
    {
        return 0;
    }
}

void MainWindow::on_action_DatagroupDisplay_triggered()//数据群组
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
    if(rCount == 0)//没有数据采集
    {
        QMessageBox msg(QMessageBox::Information,VERSION_NAME,tr("没有建立实时数据采集"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        msg.addButton(tr("确定"),QMessageBox::AcceptRole);
        msg.exec();
        //QMessageBox::about(this, tr(""), tr("没有建立实时数据采集"));
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

/*创建宏指令编辑列表*/
/*void MainWindow::MarcoEdit(void)
{

}*/

/*void MainWindow::on_action_init_macro_triggered()//初始化宏对话框
{

}*/

/*void MainWindow::on_action_global_macro_triggered()//全局宏对话框
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
void MainWindow::modifyKeyBoardASCII(QGraphicsItem *item)//ASCII字符输入键盘
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

    //控件的宏
    int totalSceneNum = pSceneSheet.size();
    for(i = 0; i < totalSceneNum; i++)//扫描所有页面
    {
        Items = pSceneSheet[i]->items();   //当前页面所有的item
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
                            if(sch->macroName == sLib|| sLib == tr("任意"))
                            {
                                strContent = tr("画面") + QString::number(i) + tr(" 开关");
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
                                if(valueItem->m_data.macroName == sLib || sLib == tr("任意"))
                                {
                                    strContent = tr("画面") + QString::number(i) + tr("数值显示器");
                                    strList.push_back(strContent);

                                }
                            }
                        }
                        else if(valueItem->m_etabPag == ASCIIINPUTSHOW)
                        {
                            if(valueItem->m_ascii.bIsinput && valueItem->m_ascii.bUseMacro && valueItem->m_ascii.macroName != "")
                            {
                                if(valueItem->m_ascii.macroName == sLib || sLib == tr("任意"))
                                {
                                    strContent = tr("画面") + QString::number(i) + tr("ASCII显示器");
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
                            if(dropItem->macroName == sLib || sLib == tr("任意"))
                            {
                                strContent = tr("画面") + QString::number(i) + tr("多功能选择按钮");
                                strList.push_back(strContent);

                            }
                        }
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_MFBTN)
                    {
                        MfBtnItem* mfbItem = dynamic_cast<MfBtnItem*>(item);
                        if(mfbItem->isUseScript && mfbItem->macroName != "")
                        {
                            if(mfbItem->macroName == sLib || sLib == tr("任意"))
                            {
                                strContent = tr("画面") + QString::number(i) + tr("多功能开关");
                                strList.push_back(strContent);
                            }
                        }
                    }
                    else if(item->GroupType() == SAM_DRAW_GROUP_COMBOBOX)
                    {
                        AkComboItem* mfbItem = dynamic_cast<AkComboItem*>(item);
                        if(mfbItem->dataCombo.m_bUseMacro && mfbItem->dataCombo.m_strMacroName != "")
                        {
                            if(mfbItem->dataCombo.m_strMacroName == sLib || sLib == tr("任意"))
                            {
                                strContent = tr("画面") + QString::number(i) + tr("下拉框");
                                strList.push_back(strContent);
                            }
                        }
                    }
                }
            }
        }
    }

    //全局宏
    int num = m_pSamSysParame->m_qvcGlobalMaroProp.size();
    GLOBAL_MARO_PROP prop;
    for(int i = 0; i < num; i++)
    {
        prop = m_pSamSysParame->m_qvcGlobalMaroProp[i];
        if(prop.sLibName == sLib || sLib == tr("任意"))
        {
            strContent = tr("第") + QString::number(i + 1) + tr("个全局脚本");
            strList.push_back(strContent);

        }
    }

    //初始化宏
    num = m_pSamSysParame->m_qvcInitMaroProp.size();
    INIT_MARO_PROP intProc;
    for(int i = 0; i < num; i++)
    {
        intProc = m_pSamSysParame->m_qvcInitMaroProp[i];
        if(intProc.sLibName == sLib || sLib == tr("任意"))
        {
            strContent = tr("第") + QString::number(i + 1) + tr("个初始化脚本");
            strList.push_back(strContent);
        }
    }
}

void MainWindow::findScreenAllMarco(QVector<MarcoString> &mVecStr)
{
    MarcoString marcoStr;
    int i = 0;
    QList<QGraphicsItem*> Items;

    //控件的宏
    int totalSceneNum = pSceneSheet.size();
    for(i = 0; i < totalSceneNum; i++)//扫描所有页面
    {
        Items = pSceneSheet[i]->items();   //当前页面所有的item
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
                            marcoStr.sItemName= tr("开关");
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
                                marcoStr.sItemName  = tr("数值显示");
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
                                marcoStr.sItemName  = tr("ASCII显示");
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
                            marcoStr.sItemName  = tr("多功能开关");
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
                            marcoStr.sItemName  = tr("下拉框");
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
                            marcoStr.sItemName  = tr("多功能开关");
                            marcoStr.sLibName   = mfbItem->macroName;
                            marcoStr.sFunName   = mfbItem->functionName;
                            mVecStr.push_back(marcoStr);
                        }
                    }
                }
            }
        }
    }

    //全局宏
    int num = m_pSamSysParame->m_qvcGlobalMaroProp.size();
    GLOBAL_MARO_PROP prop;
    for(int i = 0; i < num; i++)
    {
        prop = m_pSamSysParame->m_qvcGlobalMaroProp[i];
        marcoStr.sScreenName= tr("工程管理器");
        marcoStr.sItemName  = tr("全局脚本");
        marcoStr.sLibName   = prop.sLibName;
        marcoStr.sFunName   = prop.sFucName;
        mVecStr.push_back(marcoStr);
    }

    //初始化宏
    num = m_pSamSysParame->m_qvcInitMaroProp.size();
    INIT_MARO_PROP intProc;
    for(int i = 0; i < num; i++)
    {
        intProc = m_pSamSysParame->m_qvcInitMaroProp[i];
        marcoStr.sScreenName= tr("工程管理器");
        marcoStr.sItemName  = tr("初始化脚本");
        marcoStr.sLibName   = intProc.sLibName;
        marcoStr.sFunName   = intProc.sFucName;
        mVecStr.push_back(marcoStr);
    }

    //窗口画面宏
    num = pwnd->pSceneSheet.size();
    for(int i = 0; i < num; i++)
    {
        QList<SCRIPT_PROP> scripts;//所有脚本
        int scriptNum = 0;
        if((pwnd->pSceneSheet[i]->nIsSceneOrWindow == 0) && (pwnd->pSceneSheet[i]->listScript.size() != 0))//画面宏
        {
            marcoStr.sScreenName = tr("画面脚本");
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
        else if((pwnd->pSceneSheet[i]->nIsSceneOrWindow == 1) && (pwnd->pSceneSheet[i]->listScript.size() != 0))//窗口宏
        {
            marcoStr.sScreenName = tr("窗口脚本");
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
        pAddrMsg->nSheetIndex = nIndex;           //画面序号
        pAddrMsg->pItem = pItem;             //当前控件
        /*ADDRPRO temp;
        temp.addr.sShowAddr = sList.at(marcoindex);//宏名称
        temp.addr.sPlcRegTypeStr = sCtrlName;
        temp.str = QObject::tr("宏地址");
        pAddrMsg->Address.append(temp);
        vAddrMsg.append(pAddrMsg);*/
        ADDRPRO temp;
        Keyboard* kb = temp.pAddr;
        kb->sShowAddr = sList.at(marcoindex);//宏名称
        kb->sPlcRegTypeStr = sCtrlName;
        temp.str = QObject::tr("地址");
        pAddrMsg->Address.append(temp);
        vAddrMsg.append(pAddrMsg);
    }
}

void MainWindow::on_action_macro_admin_triggered()//宏指令管理器
{
    MarcoUseDisplay* pDlg = new MarcoUseDisplay(this);
    pDlg->exec();
    pwnd->is_Save = false;// 画面改变 同时来改变保存按钮的颜色
    is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pDlg->deleteLater();
    pDlg = NULL;
    //qDebug() << "on_action_macro_admin_triggered";
    //system("D:\\android\\code\\bash.bat");
}

    void MainWindow::on_action_macro_find_triggered()//宏查找
{
    MarcoFindDlg *pFindDlg = new MarcoFindDlg(this);

    if(pFindDlg->exec() == QDialog::Accepted)
    {
        pMainList->clear();

        int     nRow    = 1; //列表行数
        int     nFcount = 0;
        QString strLib  = pFindDlg->libName;//库名
        QString strFunc = pFindDlg->funcName;//函数名
        //QString str     = "Searching for the Marco:" + strLib + "(libName)...";
        QString str = tr("正在查找脚本:") +  strLib + tr("(库名)...");
        if(!m_rightDock->isVisible())   //显示信息输出窗口
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
        fillMarcoUseStruct(strLib, strFunc, lsStr);//填充地址信息
        int strNum  = lsStr.size();
        for(int i = 0; i < strNum; i++)
        {
            pMainList->insertRow(nRow);
            pMainList->setRowHeight(nRow, 20);
            pMainList->setItem(nRow, 0, new QTableWidgetItem(lsStr.at(i)));
            nRow++;
            nFcount++;
        }
        if(nFcount == 0)//没有找到
        {
            //str = "Cannot find the Marco !!!!!";
            str = tr("没有找到对应的脚本 !");
        }
        else
        {
            //str = QString("%1").arg(nFcount) + " occurrence(s) have been found.";
            str = QString("%1").arg(nFcount) + tr(" 个结果被找到.");
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
            //add by wxy增加全局变量数据库保存
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
bool MainWindow::CheckMarcoIsNullInCompile(QString& strLibName)//编译时检查宏使用是否为空
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

void MainWindow::ChangetoChinese()//工程语言改变
{
    QString sTmp=this->windowTitle();
    transparent tor;
    if(ui->action_chinese->isChecked())
    {
        ui->action_english->setChecked(false);
        tor.toChinese();
        languageChangeForRecipe(0);

        undoAction->setText(tr("撤销"));
        undoAction->setIconText(tr("撤销"));
        redoAction->setText(tr("恢复"));
        redoAction->setIconText(tr("恢复"));

        scrollAreaBasic->setWindowIconText("XXXX");
        scrollAreaBasic->setToolTip("XXXX");
        if(ToolBarTabWidget)
        {
            ToolBarTabWidget->setTabText(0, tr("基本图形"));
            ToolBarTabWidget->setTabText(1, tr("控   件"));
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

       undoAction->setText(tr("撤销"));
       undoAction->setIconText(tr("撤销"));
       redoAction->setText(tr("恢复"));
       redoAction->setIconText(tr("恢复"));
       if(ToolBarTabWidget)
       {
           ToolBarTabWidget->setTabText(0, tr("基本图形"));
           ToolBarTabWidget->setTabText(1, tr("控   件"));
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

//重新调整控件中图片的位置
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
        //调整开关图片大小
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
    msg.addButton(tr("确定"),QMessageBox::AcceptRole);
	int iFlg= CheckString(keyboard,sAddr,Addr_Type);
	switch(iFlg)
	{
	case ADDR_CORRECT://无错误
		break;
	case ADDR_STRING_NULL://数据为空
		msg.setText(WaringMsg+tr("输入地址不能为空！"));
		msg.exec();
		return 0;
	case ILLEGAL_REG://寄存器类型不匹配错误
		msg.setText(WaringMsg+tr("寄存器类型与地址要求不匹配！"));
		msg.exec();
		return 0;
	case INVALID_CONNECT://手动输入地址检查的时候没有该链接
        msg.setText(WaringMsg+tr("没有添加该协议！"));
		msg.exec();
		return 0;
	case ADDR_OUT_BOUND://数据超限 返回值为限制值 正数为最高限值 负数为最低限值

		msg.setText(WaringMsg+tr("地址值超出范围！"));
		msg.exec();
		return 0;
	default://输入格式错误
		msg.setText(WaringMsg+tr("输入格式错误！"));
		msg.exec();
		return 0;

    }
       
    keyboard.nAddrType = Addr_Type; //记录字位标示
       
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
//重新调整控件中图片的位置
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
        if(btransparent)//是否透明
        {
            QColor mColor = StringTOColor(sColor);
            QBitmap bmp=picture.createMaskFromColor(mColor,Qt::MaskInColor);
            picture.setMask(bmp); //设置创建的mask
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
    msg.addButton(tr("确定"),QMessageBox::AcceptRole);

    QLibrary  lib("GetHelpPath.dll");
    if (!lib.load())
    {
        msg.setText(tr("GetHelpPath.dll未找到！")); //调用获得帮助文档的dll文件
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

void MainWindow::on_action_online_simulation_triggered()//在线模拟
{
    if(bSimulator)
    {
        return;
    }
    if(!is_Save)
    {
        QMessageBox box(QMessageBox::Information,tr("提示"),tr("运行在线模拟之前要保存工程，是否保存？"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("是"));
        box.button(QMessageBox::Cancel)->setText(tr("取消"));
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
    QString dir = "Picture/" + newpro->newprowizard_name;//解压后图片存放的路径
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
  *Functions:弹出工程上载对话框
  ************************************************************************
  *Value：
  *无
  ************************************************************************
  *returns:
  *生成工程上载对话框
  ************************************************************************
  *Edit time：2011.7.13
  *Edit by    ：zhy
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
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("载入转化器文件失败，请重新安装文件！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
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
  *Functions:编译时检查用户自定义键盘
  ************************************************************************
  *Value：
  *该函数暂时没有用到
  ************************************************************************
  *returns:
  *检查用户自定义键盘的页面是否有其他的控件以及用户自定义键盘控件是否被其他的页面调用了
  *出错的话返回false 检查无错的话返回true
  ************************************************************************
  *Edit time：2011.7.13
  *Edit by    ：zhy
  *************************************************************************/

bool MainWindow::OnCheckUserkeyboard()
{
    int totalSceneNum = pSceneSheet.size();
    for(int i = 0; i < totalSceneNum;i++)   //扫描所有页面
    {
        if(pSceneSheet.at(i)->nIsSceneOrWindow==2)//是自定义键盘
        {

            QList<QGraphicsItem *> Items;
            QPainterPath path;
            path.addRect(0,0,pSceneSheet[i]->width(),pSceneSheet[i]->height());
            pSceneSheet[i]->setSelectionArea(path);
            Items=pSceneSheet[i]->selectedItems();
            foreach(QGraphicsItem *item,Items)
                item->setSelected(false);

            for(int j = 0; j < Items.size(); j++)   //扫描当前页面的所有控件
            {
                if(Items.at(j)->data(GROUP_TYPE_KEY)!=GROUP_TYPE_ASCII_KEYBOARD)
                {
                    QString sScreenName = pSceneSheet[i]->sNewScreenName;//画面名称
                    pMsgOutPut = new MsgOutPut ;//信息输出窗口双击要处理的类
                    pMsgOutPut->pItem = Items.at(j);

                    QString str = tr("error:")+sScreenName+tr("-")+tr("该控件不是用户自定义键盘控件，请删除！");
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
  *Functions:在载入用户自定义键盘后连接各种槽函数
  ************************************************************************
  *Value：
  *SamDrawScene *pScene 载入的用户自定义键盘
  ************************************************************************
  *returns:
  *无
  ************************************************************************
  *Edit time：2011.7.16
  *Edit by    ：zhy
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
  *Functions:在保存工程的时候检查所有页面的控件是否有用到自定义键盘
  ************************************************************************
  *Value：
  *如果用到自定义键盘的话就通过存储的名字找到其对应的用户自定义键盘的ID并记录到指定位置
  ************************************************************************
  *returns:
  *无
  ************************************************************************
  *Edit time：2011.7.19
  *Edit by    ：zhy
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
    for(i = 0; i < totalSceneNum;i++)   //扫描所有页面
    {
        Items = pwnd->pSceneSheet[i]->items();    //当前页面所有的item
        for(j = 0; j < Items.size(); j++)   //扫描当前页面的所有控件
        {
            pItem = Items.at(j);//->topLevelItem();
            KbLocation.clear();//清空keyboard列表；

            if(pItem->parentItem())
                continue;
            if(pItem->type() == SAM_DRAW_OBJECT_TRACKER
               || SAM_DRAW_OBJECT_LOCK == pItem->type())
            {
                continue;
            }
            nID = pItem->data(GROUP_TYPE_KEY).toInt(); //取控件的Key号
            sList = pItem->data(GROUP_DATALIST_KEY).toStringList(); //取出每个item的所有数据

            switch(-1)
            {
            case GROUP_TYPE_WORDBTN: //字按钮
            case GROUP_TYPE_ASCIIENTRY: //ASC字输入
            case GROUP_TYPE_MFUNCTION: //多功能按钮
            case GROUP_TYPE_MULSTATEBTN: //多状态按钮
                fillUserKeyboard(sList);//调用函数处理
                pItem->setData(GROUP_DATALIST_KEY,sList);
                break;
            case GROUP_TYPE_NUMENTRY://数值输入
                if(sList.at(130).toInt())//若是使用自定义键盘
                {
                    //以下代码为事先清空相关信息
                    //若找到相关数据的话会重新写该信息
                    sList[130]=QString::number(0);//不使用自定义键盘
                    sList[132]=QString::number(-1);

                   for(int nUserkeyboar=0;nUserkeyboar<pwnd->pSceneSheet.size();nUserkeyboar++)
                    {
                       if(pwnd->pSceneSheet.at(nUserkeyboar)->nIsSceneOrWindow==2)//自定义键盘
                       {
                           if(pwnd->pSceneSheet[nUserkeyboar]->sNewScreenName==sList.at(131))//若找到对应的键盘
                           {
                               sList[130]=QString::number(1);
                               sList[132]=QString::number(nUserkeyboar);
                               break;
                           }
                       }
                       else
                       {
                           continue;//非用户自定义键盘
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
  *Functions:给checkUserKeyboard（）函数调用 用以修改用户自定义键盘
  ************************************************************************
  *Value：
  *数值输入的自定义键盘数据存储的位置与其他的位置不同，除去数值输入之外 剩下的都在该函数
  *中执行
  ************************************************************************
  *returns:
  *无
  ************************************************************************
  *Edit time：2011.7.19
  *Edit by    ：zhy
  *************************************************************************/
void MainWindow::fillUserKeyboard(QStringList &sList)
{
    if(sList.at(24).toInt())//若是使用自定义键盘
    {
        //以下代码为事先清空相关信息
        //若找到相关数据的话会重新写该信息
        sList[24]=QString::number(0);
        sList[32]=QString::number(-1);
        for(int nUserkeyboar=0;nUserkeyboar<pwnd->pSceneSheet.size();nUserkeyboar++)
        {
            if(pwnd->pSceneSheet.at(nUserkeyboar)->nIsSceneOrWindow==2)//自定义键盘
            {
                if(pwnd->pSceneSheet[nUserkeyboar]->sNewScreenName==sList.at(25))//若找到对应的键盘
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

    //开始提取控件中的图片
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
    //保存组态到文件

    this->SaveProjectToFile(tr("compile\\prj.bin"),0);

    QFile file;
    file.setFileName(sFileName);
    file.open(QIODevice::WriteOnly);
    QByteArray data;
    QDataStream filestream(&data,QIODevice::WriteOnly);

    QStringList picList = mPicPath.values();

    //组态工程保存到目标路径文件下面
    this->SaveToStream("compile\\prj.bin","d:\\new",filestream);
    this->SavePicToFile(picList,filestream);
    //this->SaveProjProp();
    data = qCompress(data,5);
    file.write(data);
    file.close();
    emit this->SignalCompressProgress(100);

    //恢复组态中的图片路径
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
  *Functions:判断字体选择框是否为空
  ************************************************************************
  *Value：
  *QComboBox &fontcombobox 引用传递要判断的字体下拉列表框
  ************************************************************************
  *returns:
  *bool 若字体列表框选择的为空的话 返回false 不为空返回true
  ************************************************************************
  *Edit time：2011.7.22
  *Edit by    ：zhy
  *************************************************************************/

bool MainWindow::bCheckFount(QComboBox &fontcombobox)
{
    if(fontcombobox.currentText().isEmpty())
    {
        QMessageBox box(QMessageBox::Information,tr("提示"),tr("请选文本的字体！"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("确定"));
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

//保存文件到stream中
//sSourceFile -- 源文件 含路径
//sFileName   -- 存入stream中的文件名，含路径
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

//解压缩
//sSourceFile -- 压缩文件，含路径
//sSaveName   -- 压缩后组态的文件名，含路径
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
  *Functions:删除宏指令后重新整理全局宏和初始化宏
  *参数含义：sMacroName要删除的已编译成功的宏名称
  *Edit by zqh
  *Edit time：2011.8.10
  *************************************************************************/
void MainWindow::deleteMacro(QString sMacroName)
{
    //int i = 0;
   // QString sName = "";
//    for(i = 0; i < m_pSamSysParame->m_qvcGlobalMaroProp.size();i++) //处理全局宏
//    {
//        sName = m_pSamSysParame->m_qvcGlobalMaroProp.at(i).sMaroName;
//        if(sName == sMacroName)
//        {
//            m_pSamSysParame->m_qvcGlobalMaroProp.remove(i);
//            break;
//        }
//    }
//    for(i = 0; i < m_pSamSysParame->m_qvcInitMaroProp.size();i++) //处理全局宏
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
  *Functions:配方选择器槽函数
  ************************************************************************
  *Value：
  *单击槽函数
  ************************************************************************
  *returns:
  *无
  ************************************************************************
  *Edit time：2011.8.17
  *Edit by    ：zhy
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
        QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("配方尚未建立!"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
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
  *Functions:配方选择器槽函数
  ************************************************************************
  *Value：
  *双击槽函数
  ************************************************************************
  *returns:
  *无
  ************************************************************************
  *Edit time：2011.8.17
  *Edit by    ：zhy
  *Changed by zqh on 2011.8.18
  *************************************************************************/
void MainWindow::modifyRecipeChoice(QGraphicsItem *item)
{
    if( m_pSamSysParame->m_qvcRecipe.size() <= 0 )
    {
        QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("配方尚未建立,该控件无效!"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
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
  *主界面物件工具栏上位按钮鼠标点击槽函数
***************************************************************************/
void MainWindow::createrecipetable()
{
    if (SamDrawTool::s_eToolStat != SAM_DRAW_TOOL_UNLOCKED  || isCompiled)
    {
        return;
    }
    if( m_pSamSysParame->m_qvcRecipe.size() <= 0 )
    {
        QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("配方尚未建立!"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
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
        QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("配方尚未建立,该控件无效!"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
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
  *Functions:通过取树形控件的当前选择项来查找到当前页面
  ************************************************************************
  *Value：
  *QString stemp：当前树形控件的选择项 例如：“001：画面1”
  ************************************************************************
 *returns:
  *int类型，表示查找到了当前页面在容器中的位置 查找不到的话返回0
  ************************************************************************
  *Edit time：2011.8.30
  *Edit by    ：zhy
  *************************************************************************/
int MainWindow::nFindActiveSheetIndex(QString stemp)
{
    QStringList slist=stemp.split(":");
    if(slist.size()!=2)//有误
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
                //自定义图库
                pItem = OpenLibraryFile(sPath);
                if(pItem != NULL)
                {
                    this->saveItem(pItem,userlibStream);
                }

            }
            else if(sList.size() == 3)
            {
                //系统图库
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
  *Functions:根据HMI型号名称判断该型号有多少个链接口
  ************************************************************************
  *Value：
  *QString sHMIModle：HMI型号名称 如：SK-070AS
  ************************************************************************
 *returns:
  *QString类型
  * 第一位 若为 S -----只有一个串口 D-----两个串口
  *第二位 若为 E------有以太网接口 N----无以太网接口
  ************************************************************************
  *Edit time：2011.5.26
  *Edit by    ：zhy
  *************************************************************************/
QString MainWindow::GetHMIConnectInformation(QString sHMIModle)
{
    QString sVal = "SN";

    //D 有com2，S 没有com2，E 有以太网，N 没有以太网
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

//编译的时候需要添加HMI型号，显示模式，下载设置等信息在压缩文件头部
//将信息保存在10字节QByteArray中并返回
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
  *Functions:通过传入画面的索引值找到画面在容器中的名称
  ************************************************************************
  *Value：
  *int nScreenId：逻辑索引值
  ************************************************************************
 *returns:
  *画面名称，找不到的话返回空
  ************************************************************************
  *Edit time：2011.12.3
  *Edit by    ：zhy
  *************************************************************************/
QString  MainWindow::GetSCreenName(int nScreenId)
{
    QString sScreenName;
    for(int j=0, nrealadd=0;j<=nScreenId;nrealadd++)
    {//变量j是临时辅助变量  nrealadd代表页面的真实地址
        if(j>pwnd->pSceneSheet.size()-1)
        {
            sScreenName.clear();
            break;
        }
        if(pwnd->pSceneSheet.at(nrealadd)->nIsSceneOrWindow!=2)//不是自定义键盘
        {
            if(j ==nScreenId )//循环完特定的次数之后
            {//对应的循环nrealadd就是实际地址
                sScreenName=pwnd->pSceneSheet.at(nrealadd)->sNewScreenName;
                break;
            }
            j++;
        }
    }
    return sScreenName;
}
/************************************************************************
  *Functions:通过传入画面的索引值找到画面在容器中的实际索引
  ************************************************************************
  *Value：
  *int nScreenId：逻辑索引值
  ************************************************************************
 *returns:
  *返回画面在容器中的实际索引找不到的话返回0
  ************************************************************************
  *Edit time：2011.12.3
  *Edit by    ：zhy
  *************************************************************************/
int  MainWindow::GetSCreenID(int nScreenId)
{
    int sScreenID=GetFristScreenID(1);
    for(int j=0, nrealadd=0;j<=nScreenId;nrealadd++)
    {//变量j是临时辅助变量  nrealadd代表页面的真实地址
        if(j>pwnd->pSceneSheet.size()-1)
        {
            break;
        }
        if(pwnd->pSceneSheet.at(nrealadd)->nIsSceneOrWindow!=2)//不是自定义键盘
        {
            if(j ==nScreenId )//循环完特定的次数之后
            {//对应的循环nrealadd就是实际地址
                sScreenID=nrealadd;
                break;
            }
            j++;
        }
    }
    return sScreenID;
}
/************************************************************************
  *Functions:删除画面或者窗口或者自定义键盘的时候刷新树形控件上页面跳转的问题
  ************************************************************************
  *Value：
  *无
  ************************************************************************
 *returns:
  *无
  ************************************************************************
  *Edit time：2011.12.6
  *Edit by    ：zhy
  *************************************************************************/
int  MainWindow::DealWithDeleteScreen()
{
    if(pwnd->m_pSamSysParame->m_projectProp.nScreensaverIndex > pwnd->nActiveSheetIndex)
    {
        pwnd->m_pSamSysParame->m_projectProp.nScreensaverIndex--;//删除屏保画面之前的画面时 序号减1
    }
    else if(pwnd->m_pSamSysParame->m_projectProp.nScreensaverIndex == pwnd->nActiveSheetIndex)
    {
        pwnd->m_pSamSysParame->m_projectProp.nScreensaverIndex=GetFristScreenID(0);//删除当前页面序号清零
    }
    if(pwnd->m_pSamSysParame->m_projectProp.nLoadSceneIndex > pwnd->nActiveSheetIndex)
    {
        pwnd->m_pSamSysParame->m_projectProp.nLoadSceneIndex--;//删除初始化页面之前的画面时 序号减1
    }
    else if(pwnd->m_pSamSysParame->m_projectProp.nLoadSceneIndex == pwnd->nActiveSheetIndex)
    {
        pwnd->m_pSamSysParame->m_projectProp.nLoadSceneIndex=GetFristScreenID(0);//删除当前页面序号清零
    }
    if(pwnd->m_pSamSysParame->m_projectProp.nStartScreenIndex  > pwnd->nActiveSheetIndex)
    {
        pwnd->m_pSamSysParame->m_projectProp.nStartScreenIndex--;//删除启动画面之前的画面时 序号减1
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
    for(int i=0;i<pwnd->m_pSamSysParame->m_hmiProtectProp.mProtectList.size();i++)//HMI保护跳转页面
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
  *Functions:给上面DealWithDeleteScreen（）函数调用，当删掉当前选择的画面的时候
  *处理树形控件上面的画面的索引防止跳转到自定义键盘
  ************************************************************************
  *Value：
  *int nIncludeWindow 标示是否包含窗口，包含窗口的话为1 不包含为0
  ************************************************************************
 *returns:
  *int 类型返回的是第一个画面或者窗口在容器中的下标
  ************************************************************************
  *Edit time：2011.12.17
  *Edit by    ：Dylan
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
  *Functions:更改画面或者窗口名称的时候刷新画面按钮和功能按钮中画面的名称
  ************************************************************************
  *Value：
  *无
  ************************************************************************
 *returns:
  *无
  ************************************************************************
  *Edit time：2012.1.7
  *Edit by    ：Dylan
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
        if(pwnd->pSceneSheet[i]->nIsSceneOrWindow==2)//自定义键盘的时候
        {
            continue;
        }
        Items = pwnd->pSceneSheet[i]->items();   //当前页面所有的item
        for(int j = 0; j < Items.size(); j++)
        {
            sList = Items.at(j)->data(GROUP_DATALIST_KEY).toStringList(); //取出每个item的所有数据
            if(sList.size() < 20)
                continue;//break;
            sName = sList.at(19);
            if(sName.mid(0,2) == "SB")//画面按钮
            {
                sTmp.setNum(0);//清空存储的数据，若下面的for循环找不到合适的数据的话则标示选择的画面已经被删除或者不存在
                sList.replace(57,sTmp);//设置成跳转到第一个画面
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
            else if(sName.mid(0,2) == "MF")//功能按钮
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
  *Functions:在更改自定义键盘名称的时候刷新用的自定义键盘名称的控件
  ************************************************************************
  *Value：
  *
  ************************************************************************
  *returns:
  *无
  ************************************************************************
  *Edit time：2012.1.7
  *Edit by    ：Dylan
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
    for(i = 0; i < totalSceneNum;i++)   //扫描所有页面
    {
        Items = pwnd->pSceneSheet[i]->items();    //当前页面所有的item
        for(j = 0; j < Items.size(); j++)   //扫描当前页面的所有控件
        {
            pItem = Items.at(j);//->topLevelItem();
            KbLocation.clear();//清空keyboard列表；

            if(pItem->parentItem())
                continue;
            if(pItem->type() == SAM_DRAW_OBJECT_TRACKER
               || pItem->type() == SAM_DRAW_OBJECT_LOCK)
            {
                continue;
            }
            nID = pItem->data(GROUP_TYPE_KEY).toInt(); //取控件的Key号
            sList = pItem->data(GROUP_DATALIST_KEY).toStringList(); //取出每个item的所有数据

            switch(nID)
            {
            case GROUP_TYPE_WORDBTN: //字按钮
            case GROUP_TYPE_ASCIIENTRY: //ASC字输入
            case GROUP_TYPE_MFUNCTION: //多功能按钮
            case GROUP_TYPE_MULSTATEBTN: //多状态按钮
                Rename(sOldName, sNewName,sList);//调用函数处理
                pItem->setData(GROUP_DATALIST_KEY,sList);
                break;
            case GROUP_TYPE_NUMENTRY://数值输入
                if(sList.at(130).toInt())//若是使用自定义键盘
                {
                    if(sOldName==sList.at(131))//若找到对应的键盘
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
  *Functions:给checkUserKeyboard（）函数调用 用以修改用户自定义键盘
  ************************************************************************
  *Value：
  *数值输入的自定义键盘数据存储的位置与其他的位置不同，除去数值输入之外 剩下的都在该函数
  *中执行
  ************************************************************************
  *returns:
  *无
  ************************************************************************
  *Edit time：2012.1.7
  *Edit by    ：Dylan
  *************************************************************************/
void MainWindow::Rename(QString sOldName,QString sNewName,QStringList &sList)
{
    if(sList.at(24).toInt())//若是使用自定义键盘
    {
        if(sOldName==sList.at(25))//若找到对应的键盘
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
    //wxy 切换画面时将滚动条进行默认设置
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

    if(nLanIndex < 0) //只有一种语言的时候不作处理
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
    count       = pSceneSheet.size(); //画面总数
    for(int i = 0 ; i < count; i++) //扫描所有画面
    {
        Items = pSceneSheet[i]->items();   //当前页面所有的item
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
                //sList   = item->topLevelItem()->data(GROUP_DATALIST_KEY).toStringList(); //取出每个item的所有数据
                //nID     = item->data(GROUP_TYPE_KEY).toInt(); //取控件的Key号
                //alterControlLanguage(item,sList,nID,nLanIndex);
                changeItemLanguageAttr(item);
            }
        }*/
    }
    //qDebug() <<"onFrmLanguageChange:end";
}



//取Item的sceneBoundingRect，当复制静态图片的时候，需要从data区取实际的rect
//方便复制部分的操作
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
//保存脚本
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

//读取脚本
void MainWindow::loadLibrary(QDataStream &stream)
{

    if(pwnd->getProVersion() < 2781)//旧版本
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
        //读取全局变量
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
                if(pwnd->getProVersion() >= 2914)//新版本
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
 *函数名称：setToolBoxFloat
 *函数功能：设置工具箱为浮动效果
 *参数含义：NULL
 *返回值:       NULL
 *编辑作者：郑启红
 *编辑日期：2012.9.12
 **************************************************************/
void MainWindow::setToolBoxFloat()
{
    QList<QPushButton *> button = ui->m_toolwidgetBasic->findChildren<QPushButton *>();
    for(int i=0; i < button.count(); i++)//通过i的范围确定需要设置哪些button
    {
        setDynamicImage(button.at(i));
    }
    QList<QPushButton *> buttonCtl = ui->m_toolwidgetCtl->findChildren<QPushButton *>();
    for(int i=0; i < buttonCtl.count(); i++)//通过i的范围确定需要设置哪些button
    {
        setDynamicImage(buttonCtl.at(i));
    }
}

/***************************************************************
 *函数名称：setDynamicImage
 *函数功能：设置工具箱为浮动效果
 *参数含义：
 *button：     待设置的按钮指针
 *返回值:       NULL
 *编辑作者：郑启红
 *编辑日期：2012.9.12
 **************************************************************/
void MainWindow::setDynamicImage(QPushButton *button)
{
    /*定义两种状态（鼠标进入button/退出button）*/
    QState *inside = new QState;
    inside->assignProperty(button,"flat", "false");//设置button为凸起
    QState *outside = new QState;
    outside->assignProperty(button, "flat", "true");//设置button为平面

    /*把进入、退出事件与button关联*/
    QEventTransition *enterTransition = new QEventTransition(button, QEvent::Enter);
    enterTransition->setTargetState(inside);//鼠标进入button
    outside->addTransition(enterTransition);//把outside状态，连接到enterTransition变化中去

    QEventTransition *leaveTransition = new QEventTransition(button, QEvent::Leave);
    leaveTransition->setTargetState(outside);//鼠标退出button
    inside->addTransition(leaveTransition);//把inside状态，连接到leaveTransition变化中去

    /*定义状态机*/
    QStateMachine *machine = new QStateMachine(this);

    /*在状态机中添加这两种状态*/
    machine->addState(inside);
    machine->addState(outside);

    /*设置初始状态*/
    machine->setInitialState(outside);

    /*启动状态机*/
    machine->start();
}
void MainWindow::initFontMap()
{
	sysFontMap.insert(tr("宋体"),"SIMSUN.TTC");
	sysFontMap.insert(tr("新宋体"),"SIMSUN.TTC");
	sysFontMap.insert(tr("仿宋体"),"SIMFANG.TTF");
	sysFontMap.insert(tr("华文中宋"),"STZHONGS.TTF");
	sysFontMap.insert(tr("华文宋体"),"STSONG.TTF");
	sysFontMap.insert(tr("华文仿宋"),"STFANGSO.TTF");
	sysFontMap.insert(tr("华文彩云"),"STCAIYUN.TTF");
	sysFontMap.insert(tr("华文新魏"),"STXINWEI.TTF");
	sysFontMap.insert(tr("华文楷体"),"STKAITI.TTF");
	sysFontMap.insert(tr("华文琥珀"),"STHUPO.TTF");
	sysFontMap.insert(tr("华文隶书"),"STLITI.TTF");
	sysFontMap.insert(tr("华文细黑"),"STXIHEI.TTF");
	sysFontMap.insert(tr("华文行楷"),"STXINGKA.TTF");
	sysFontMap.insert(tr("黑体"),"SIMHEI.TTF");
	sysFontMap.insert(tr("楷体"),"SIMKAI.TTF");
	sysFontMap.insert(tr("楷体_GB2312"),"SIMKAI.TTF");
	sysFontMap.insert(tr("隶书"),"SIMLI.TTF");
	sysFontMap.insert(tr("微软雅黑"),"msyh.TTF");
	sysFontMap.insert(tr("幼圆"),"SIMYOU.TTF");
	sysFontMap.insert(tr("微软雅黑 Bold"),"msyhbd.TTF");
	sysFontMap.insert(tr("方正舒体"),"FZSTK.TTF");
	sysFontMap.insert(tr("方正姚体 Bold"),"FZYTK.TTF");
	
}
//检查脚本引用是否正确
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
                if(mac.isCompiled())//已经编译通过
                {
                    chkResult = 1;
                }
                else//未编译通过
                {
                    chkResult = 0;
                }
                break;
            }
        }
        if(chkResult != 1)
        {
            if(chkResult == 0)//引用了未编译通过的脚本
            {
                str = tr("error:初始化脚本引用了未编译通过的脚本 %1").arg(initMac.sLibName);
            }
            else
            {
                str = tr("error:初始化脚本引用的脚本 %1 不存在").arg(initMac.sLibName);
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
                if(mac.isCompiled())//已经编译通过
                {
                    chkResult = 1;
                }
                else//未编译通过
                {
                    chkResult = 0;
                }
                break;
            }
        }
        if(chkResult != 1)
        {
            if(chkResult == 0)//引用了未编译通过的脚本
            {
                str = tr("error:全局脚本引用了未编译通过的脚本 %1").arg(glMac.sLibName);
            }
            else
            {
                str = tr("error:全局脚本引用的脚本 %1 不存在").arg(glMac.sLibName);
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
                    if(mac.isCompiled())//已经编译通过
                    {
                        chkResult = 1;
                    }
                    else//未编译通过
                    {
                        chkResult = 0;
                    }
                    break;
                }
            }
            if(chkResult != 1)
            {
                if(chkResult == 0)//引用了未编译通过的脚本
                {
                    str = tr("error:画面 %1 引用了未编译通过的脚本 %2").arg(sScreenName).arg(script.scriptName);
                }
                else
                {
                    str = tr("error:画面 %1 引用的脚本 %2 不存在").arg(sScreenName).arg(script.scriptName);
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
                    if(chkResult == 0)//引用了未编译通过的脚本
                    {
                        str = tr("error:%1-%2引用了未编译通过的脚本%3").arg(sScreenName).arg(pItem->getItemName()).arg(msg);
                    }
                    else
                    {
                        str = tr("error:%1-%2引用的脚本不存在").arg(sScreenName).arg(pItem->getItemName());
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
//输出信息到编译输出窗口
void MainWindow::showCompileMsg(QString str,QGraphicsItem *pItem,int row,int index)
{
    pMsgOutPut = new MsgOutPut ;//信息输出窗口双击要处理的类
    pMsgOutPut->pItem = pItem;
    pMsgOutPut->nSheetIndex = index;
    //str = tr("error:")+sScreenName+tr("-")+pItem->getItemName()+tr("引用脚本有误");
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
//检查系统参数配置是否正确
bool MainWindow::checkSysParam()
{
	//检查显示设置
	QString str;
	QStringList sceneNames;//所有画面的名称
	QStringList windowNames;//所有窗口的名称
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
		&& !sceneNames.contains(m_pSamSysParame->m_mixGlobalVar.m_sLogoNum))//使用启动logo画面
	{	
            str = tr("工程管理器:显示设置 启动logo画面号错误");
            emit SignalInformation(str, MSG_ERROR);
            result = false;
	}

	if (m_pSamSysParame->m_mixGlobalVar.m_bStandby && m_pSamSysParame->m_mixGlobalVar.m_bStandbyMode 
		&& !sceneNames.contains(m_pSamSysParame->m_mixGlobalVar.m_sStandbyNum))//使用画面待机
	{
            str = tr("工程管理器:显示设置 待机画面号错误");
            emit SignalInformation(str, MSG_ERROR);
            result = false;
	}
        if(m_pSamSysParame->m_mixGlobalVar.m_sInitNum == "")
        {
            m_pSamSysParame->m_mixGlobalVar.m_sInitNum = pwnd->copyScreen_Item->child(0)->text(0).split(":").at(1);
        }
	if (!sceneNames.contains(m_pSamSysParame->m_mixGlobalVar.m_sInitNum))
	{
            str = tr("工程管理器:显示设置 初始画面号错误");
            emit SignalInformation(str, MSG_WARNING);
            //result = false;
	}

	//数据控制-位控制画面切换
    if (m_pSamSysParame->m_mixGlobalVar.m_bBitSenceExch)
	{
            foreach(BitSenceItem item,m_pSamSysParame->m_mixGlobalVar.m_vecBitSence)
            {
                if (!sceneNames.contains(item.sCtlSceneId)
                        && !windowNames.contains(item.sCtlSceneId))
                {
                    str = tr("工程管理器:数据控制 位控制画面切换错误");
                    emit SignalInformation(str, MSG_ERROR);
                    result = false;
                }
            }
     }

	//报警登录
	foreach (AlarmGroup grp,m_pSamSysParame->m_qvcAlarm)
	{
            foreach(stAlarm alarm,grp.alarms)
            {
                if (alarm.bOpenScene && !sceneNames.contains(alarm.sceneName)
                        && !windowNames.contains(alarm.sceneName))
                {
                    str = tr("工程管理器:报警登录");
                    str += grp.alarmName;
                    str += tr("报警打开画面号错误");
                    emit SignalInformation(str, MSG_ERROR);
                    result = false;
                }
            }
	}
	return result;
}

//修改多功能按钮属性
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

//添加多功能按钮
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
//上载数据
void MainWindow::on_action_upload_triggered()
{
    QStringList cmdlist;
    cmdlist.append("0");
    cmdlist.append(QString::number(is_tanslator));
    bool bReturnFlag = QProcess::startDetached(PC_AKTOOL_EXE,cmdlist);
    if(!bReturnFlag)
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("载入文件 %1 失败，请重新安装软件！").arg(PC_AKTOOL_EXE),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
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
    sBaudrate << "1200" << "2400" << "4800" << "9600" << "19200" << "34800" << "57600" << "115200";//波特率

    sDataBit << "7" << "8";//数据位

    sStopBit << "1" << "2";//停止位


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

//查看HMI序列号等信息
void MainWindow::on_action_HMI_triggered()
{
    InfoDlg dlg;
    dlg.exec();
}
//index= 0 中文,index = 1 英文
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
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("16位整数");
                    }
                    else if(tr("16-Bit Unsigned Int") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("16位正整数");
                    }
                    else if(tr("32-Bit Signed Int") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("32位整数");
                    }
                    else if(tr("32-Bit Unsigned Int") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("32位正整数");
                    }
                    else if(tr("32-Bit Float") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("32位浮点数");
                    }
                    else if(tr("16-Bit BCD") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("16位BCD码");
                    }
                    else if(tr("32-Bit BCD") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("32位BCD码");
                    }
                    else if(tr("Bit") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = tr("位");
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
                    qDebug()<<"sdatatype ====="<<tr("16位整数");
                    if(tr("16位整数") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = "16-Bit Signed Int";
                    }
                    else if(tr("16位正整数") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = "16-Bit Unsigned Int";
                    }
                    else if(tr("32位整数") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = "32-Bit Signed Int";
                    }
                    else if(tr("32位正整数") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = "32-Bit Unsigned Int";
                    }
                    else if(tr("32位浮点数") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = "32-Bit Float";
                    }
                    else if(tr("16位BCD码") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = "16-Bit BCD";
                    }
                    else if(tr("32位BCD码") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
                    {
                        m_pSamSysParame->m_qvcRecipe[i].formula[0].elment[j].sAddrType = "32-Bit BCD";
                    }
                    else if(tr("位") == m_pSamSysParame->m_qvcRecipe[i].formula[0].elment.at(j).sAddrType)
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
    return str;  //没找到返回
}
//压缩工程的时候重新获取控件图片路径
void MainWindow::loadPicPath(QItemGroup *pItemGroup,QMap<QString, QString> &mPath)
{
    if(NULL == pItemGroup)
    {
        return;
    }

    QString path;
    int nKey = pItemGroup->data(GROUP_TYPE_KEY).toInt();
    if(USER_DEFINE_GROUP == nKey)//组合图形
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

//压缩工程的时候保存控件图片路径
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
        if(USER_DEFINE_GROUP == nKey)//组合图形
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
         if(!(str == tr("画面") || str == tr("窗口")
             || str == tr("自定义键盘") || str == tr("窗口&画面")))
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
//调用PLC编程软件，编译PLC程序
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
//载入PLC程序
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
//保存PLC程序
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
        pSimDlg->setLabelText(tr("正在传输组态数据"), 66);
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

    if(bSuc)//wxy拷贝文件成功
    {
        if(pSimDlg)
        {
            pSimDlg->setLabelText(tr("传输完成，运行模拟器"), 100);
        }

        QString vdisk = QDir::currentPath();
        vdisk += vShareIni;
        vdisk.replace("\\","/");
        QSettings *readIni = new QSettings(vdisk, QSettings::IniFormat, 0);
        readIni->setValue("StartVM", "true");
        //写入APK版本号，模拟器根据此版本号决定是否更新
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
            pSimDlg->setLabelText(tr("传输失败"), 100);
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


//拷贝文件夹：
bool MainWindow::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
            if(!copyDirectoryFiles(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()),
                coverFileIfExist))
                return false;
        }
        else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
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

//将数据库语句存到vector，最后批量执行
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
    if(!bExist)//不存在改表的项则添加
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
