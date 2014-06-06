#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include <QSettings>
#include <QMainWindow>
#include <QToolBar>
#include <QCloseEvent>
#include <QStackedWidget>
#include <QGraphicsView>
#include <QHBoxLayout>
#include "view/samdrawscene.h"
#include <QFontDatabase>
//#include <QVariant>
#include "headfile/global_types.h"  //宏定义头文件
#include "Frame\TreeCtrlDlg\qtreectrlnewscreendlg.h"
#include "NewProjectWizard\qnewprodlg.h"//新建工程对话框头文件
#include "qprogectmanager.h"
#include "Frame\TreeCtrlDlg\qtreectrltimedlg.h"
#include "Frame\TreeCtrlDlg\qtreectrlrecipedlg.h"//配方
#include "Frame/TreeCtrlDlg/qdatatransportdlg.h"//资料传输
/**********主框架物件工具栏各对话框*************/
#include "ThingDlg\qtimedisplaydlg.h"
#include "ThingDlg\qdatedisplaydlg.h"
#include "ThingDlg\qweekdisplaydlg.h"
#include "ThingDlg\qstaticpicturedlg.h"

#include "ThingDlg\qtimerdlg.h"
#include "Frame\ThingDlg\qnewwindowdlg.h"
#include "Frame\TreeCtrlDlg\qcopyscreendlg.h"
#include "Frame\TreeCtrlDlg\qcopywindowdlg.h"
#include "Frame/TreeCtrlDlg/quserkeyboard.h"

#include "Frame/ThingDlg/qkeybutton.h"
#include "Frame/TreeCtrlDlg/quserkeyboardproperty.h"
#include "Frame/DebugDlg/quploaddlg.h"
#include "Frame/ThingDlg/qrecipechoice.h"
/**********绘图工具栏各对话框*************/
#include "Frame/DrawDlg/qlinedlg.h"
#include "Frame/DrawDlg/qrectdlg.h"
//#include "Frame/DrawDlg/qtextdlg.h"
#include "Frame/aboutdlg.h"//关于对话框
#include "Frame/qmulticopy.h"//多重复值
#include "Frame/TreeCtrlDlg/qfilepassworddlg.h"
#include "stdafx.h"
#include "color.h"
#include "Frame/DebugDlg/compilethrd.h"
#include "Macro/MarcoUseDisplay.h"
#include "Frame/simulatordlg.h"


QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QTreeWidget;
class QTextEdit;
class QDockWidget;
class QTreeWidgetItem;
class QHorizontal;
class MacroCmptrd;
class Macro;
class downloadTrd;
QT_END_NAMESPACE
namespace Ui {
    class MainWindow;
    class mytreeWidget;
}
typedef struct stDBQuery
{
    QString tableName;
    QVector<QMap<QString,QVariant> > vDbQuery;
}DBQuery;
/*******设置树形浮动窗口的初始大小**************/
class mytreeWidget : public QTreeWidget
{
public:
    QSize sizeHint() const
    {
        return QSize(200, 900); /* 在这里定义dock的初始大小 */
    }
};

//add by wuxiyang
//增加tab按键的转发
class myGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    myGraphicsView(QWidget *parent = 0) :
            QGraphicsView(parent)
    {
    }
protected:
    bool event(QEvent *event)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent* ke = dynamic_cast<QKeyEvent*>(event);
            if(ke->key() == Qt::Key_Tab)
            {
                if(this->scene())
                {
                    SamDrawScene* pScene = dynamic_cast<SamDrawScene*>(this->scene());
                    pScene->keyPressEvent(ke);
                }
                return true;
            }
        }
        return QGraphicsView::event(event);
    }
};

//add by wuxiyang
//增加关闭信号
class myDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    myDockWidget(QWidget *parent = 0) :
            QDockWidget(parent)
    {
        m_iData = 0;
    }

    myDockWidget(const QString& title, QWidget *parent = 0) :
            QDockWidget(title,parent)
    {
        m_iData = 0;
    }
signals:
    void dockWidgetClose(int iData);
protected:
    void closeEvent(QCloseEvent *event)
    {
        emit dockWidgetClose(m_iData);
    }
private:
    int m_iData;
public:
    void setData(int iData)
    {
        m_iData = iData;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //add by chengzhihua
    QStringList sLibraryPath;//保存图库当前打开的路径，下次打开图库选定到当前路径
    /*add by tang haiguo */
    QSamSysParame *m_pSamSysParame;
    QVector<MacroLibrary > librarys; //脚本库 也就是宏指令
    QVector<Macro> macros; //脚本库 也就是宏指令
    void saveLibrary(QDataStream &stream);//保存脚本
    void loadLibrary(QDataStream &stream);//读取脚本
    void init();
    //czq
    //unsigned int m_curDataLog;//当前操作的是第几个数据采集变量,0代表当前没有数据采集

    void SetCurrentPath(QString path);
    QString currentPath();
    QString exePath;
    QString picturePath;
    QMenu *cmenu;
    MacroCmptrd *macroTrd;

    ///////////////////////////////////
    QMenu* pMenuSpace;
    QMenu* pMenuAlign;
    QMenu* pMenuZXu;

    QComboBox* pChScreen;        //屏幕列表下拉框

    QString strOldProtocal;
    QString strNewProtocal;
    //////////////////////////////////

    QVector <PLC_FACTORY> vPlc;
    QVector<stScriptLib> sysLibs;
    void closeEvent(QCloseEvent *event);
    QVector<QString>screenItem_vector;
    QVector<QLabel *> label;
    QVector<QLabel *> titlelabel;
    QVector<QWidget *> priviewWidget;
    bool is_haveScreen;//是否存在场景
    bool is_SaveAS;//是否另存为
    bool is_Save;//是否保存
    bool is_NeedCompiled;//wxy 用来标识是否需要重新编译
    QString sOpenFileVersion;
    bool bCpyAndPaste;
    QString saveAs_Name;//另存为名字
    bool   isHave;//当点击新建工程的确定按钮时树控件鼠标点击才有效
    bool    is_Is;
    bool  isCompiled;
    CompileThrd *thread;
    downloadTrd *threadDownload;
    QColor StringTOColor(QString sColor);
    //int  nScreen_Width;//屏幕 的宽度
    //int  nScreen_Height;//屏幕的高度
    bool isCheck_ScreenProperty;//是否选择画面的属性菜单
    bool isCheck_WindowProperty;//是否选择窗口的属性菜单
    bool is_ScreenProperty_Name;//点击画面属性时来判断名字
    bool is_WindowProperty_Name;//点击窗口属性时来判断名字
    QTreeWidgetItem *screen;//树控件第一级画面
    QTreeWidgetItem *window;////树控件第一级窗口
    QTreeWidgetItem *tree_macro;////树控件第一级宏指令
    QTreeWidgetItem *global_macro;
    QTreeWidgetItem *init_macro;
    QNewWindowDlg  *newWindowDlg;//右键点击树控件上第一级画面菜单生成的新建窗口对话框
    QTreeCtrlNewScreenDlg  *newScreenDlg;//右键点击树控件上第一级画面菜单生成的新建画面对话框
    QCopyScreenDlg           *newCopyScreen;//右键点击树控件上第2级画面菜单生成的新建复制画面对话框
    QCopyWindowDlg             *newCopyWindow;//右键点击树控件上第2级画面菜单生成的新建复制画面对话框
    QTreeWidgetItem *newScreen[MAX_SCRNCNT]; //树控件上第2级画面菜单的的个数
    QTreeWidgetItem *TreeuserKeyboard[30];//树形控件用户自定义键盘
    //QVector<SamDrawScene *> pUserKeyboard_vector;//用户自定义键盘容器

    QVector<QTreeWidgetItem *>screenSubItem_vector;

    QTreeWidgetItem *alarmlog;//第一级报警登陆
    QVector<QString> alarm_name;//保存报警的各个名称
    QVector<int> alarm_style;//保存报警style 0-digital
    QTreeWidgetItem *recipe;//树控件第一级配方
    QTreeWidgetItem *datatransport;//资料传输
    QTreeWidgetItem *treeScheduler;
    QTreeWidgetItem *sub_Recipe;//树控件第2级配方"配方1"
    int nscreen;//画面子级的个数
    //bool isHave_Recipe;//是否存在配方
    //int ifhisdataexist;//历史数据是否存在
    bool bSimulator;
    QUserKeyboard *userkeyboarddlg;//用户自定义键盘对话框
    QTreeWidgetItem *TreeKeyboard;//自定义键盘
    QUserKeyboardProperty *userkeyboardproperty;//用户自定义键盘属性对话框
    void showUserKeyboard();//用户自定义键盘右键属性菜单
    void showUserKeyboardAddnew();//用户自定义键盘右键新建菜单
    bool OnCheckUserkeyboard();//编译时检查用户自定义键盘函数
    void checkUserKeyboard();//保存的时候检测是否用到用户自定义键盘

    int nFindActiveSheetIndex(QString stemp);//查找函数用于查找当前选中的页面在容器中的具体位置
    void fillUserKeyboard(QStringList &sList);//辅助以上函数进行地址处理
    void deletehisdata();//删除历史数据的时候清空历史数据内容
    QString GetHMIConnectInformation(QString sHMIModle);//根据HMI型号确定链接口
    //XXXXX

    int                   nCurrentDigitalAlarmIndex;//当前的数据报警
    int                   nCurrentAnalog_alarmIndex;
    int                   m_digitalAlarm;    //树控件上数位报警登陆右边的尾数
    //int                   nanalogAlarm;       //类比报警登陆的个数
    int                   m_analogAlarm;       //树控件上类比报警登陆右边的尾数
    QTreeWidgetItem *digital_treeItem[DIGIT_ALARM_NUM];//添加数位报警登陆
    QTreeWidgetItem *analog_treeItem[ANALOG_ALARM_NUM];//添加类比报警登陆
    QVector<QTreeWidgetItem *> digital_alarmlogItem_Vector;//
    QVector<QTreeWidgetItem *> analog_alarmlogItem_Vector;
    /******************数据的封装******************************************/
    QNewPro  *newpro;
    //edit zhy
    int  GetFristScreenID(int nIncludeWindow);//得到第一个画面在容器中的位置
    void reUserkeyboardname(QString sOldName,QString sNewName);//更改自定义键盘名称的时候刷新用到的自定义键盘的控件
    void Rename(QString sOldName,QString sNewName,QStringList &sList);//上面那个函数的辅助函数
    bool bCheckFount(QComboBox &fontcombobox);
    //XXXXX
    void ShowlinkProperty();//连接右键菜单
    QString  GetSCreenName(int nScreenId);//通过 逻辑索引找到对应的实际名称
    int GetSCreenID(int nScreenId);//通过逻辑索引找到对应画面的实际索引
    QVector<int> nSimulatorport;//存储模拟时候的选中的当前的链接口
    void  reScreenorwindowName(QString sOldname,QString sNewname);//名字更改之后刷新控件中的名称
    QString KeyboardToString(Keyboard keyboard);//地址转换为字符串函数
    void StringToKeyboard(Keyboard &keyboard,QString sKeyboard);//字符串转换为地址函数
    void GroupTypeKey(QGraphicsItem *item);//双击打开对话框函数中的判断组合图形的函数
    void BasicGraphicsItem(QGraphicsItem *item);//基本图形的函数
    int Addr_Type;//标示是字还是位
    int DataType;//存储数据类别
    int CheckMinMax(QString Min, QString Max, int DataType,int CheckType);
    int IsAddressCheckRight(Keyboard &keyboard,QString WaringMsg,QLineEdit *pLineEdit,int Addr_Type);
    int IsMyAddressCheckRight(Keyboard &keyboard,QString WaringMsg,QLineEdit *pLineEdit,int Addr_Type, QSpinBox *pSpinBox);
    int CheckString(Keyboard &keyboard,QString sourceStr,int Addr_Type);
    int CheckExternAddr(Keyboard &keyboard,QString sourceStr,int Addr_Type);
        int getCurrentSamp();
        void languageChangeForRecipe(int nIndex);

    QVector <QTreeWidgetItem *> vTreeLinkType;
    //+++++
    QTreeWidgetItem*  plcConnect;        //PLC连接
    QTreeWidgetItem*  sysSetting;     //系统设置---root----
    QTreeWidgetItem*  pcCtrl;         //主机管理----------
    QTreeWidgetItem*  pcChoice;       //机型选择
    QTreeWidgetItem*  displaySet;     //显示设置
    QTreeWidgetItem*  operateSet;     //操作设置
    QTreeWidgetItem*  dataCtrl;       //数据控制
    QTreeWidgetItem*  permissionSec;  //用户权限
    //QTreeWidgetItem*  timeArea;       //时间&区域
    QTreeWidgetItem*  hostPeri;       //主机外设----------
    QTreeWidgetItem*  printer;        //打印机
    //QTreeWidgetItem*  networkAd;      //网络适配器
    QTreeWidgetItem*  confiWorks;     //组态工程----------
    QTreeWidgetItem*  downloadSet;    //下载设置
    QTreeWidgetItem*  accessEncry;    //访问加密
    QTreeWidgetItem   *clock;         //时钟设置
    QTreeWidgetItem*  productLicen;   //产品授权
    QTreeWidgetItem*  lanSet;         //语言设置
    QTreeWidgetItem* chdItem;
    //QTreeWidgetItem*  datatransport;  //资料传输
    //old
    //XXXXX
    QTreeWidgetItem *link;          //连接
#ifdef AKPLC
    QTreeWidgetItem *PlcNode;//Plc编程
#endif
    //XXXXX
    void ShowComLink();//出现连接画面右键菜单
    void information(QString str, MSG_TYPE eType);
    int  DealWithDeleteScreen();//处理删除画面窗口自定义键盘的时候树形控件刷新问题
    QSizeF ScalePicture(QSizeF size1,QSizeF size2,QSizeF oldSize);
    //图片路径map
    //编译时候存需要下载的数据
    QString sFilePath;
    QMap<QString, QString> mPicPath;
    ST_LIBPATH mLibPathInfo;
    QStringList lLibPaths;
    QStringList lPicList;
    QString SavePicPath(QString path,QSizeF size);
    QString SaveLibPath(QString path,QSizeF size);
    QString SavePath(QString path,QSizeF size = QSizeF(800,600),bool bLib = false);

    void SaveLibraryFile();
    void saveItem(QGraphicsItem *pItem,QDataStream &stream);
    void GetItemText(QMultiMap<QString,QString> &FontMap,QGraphicsItem * pItem);
    QByteArray FileHeader();
    bool SaveMacro(QString sDir,QDataStream &stream);

    /**********************工具栏******************************/
    QLabel *lab_control_statusBar;
    QLineEdit *lab_up_space_statusBar;
    QLineEdit *lab_left_space_statusBar;
    QLineEdit *lab_width_space_statusBar;
    QLineEdit *lab_hidth_space_statusBar;
    QLabel *lab_Coordinate_statusBar;
    QLabel *lab_up_statusBar;
    QLabel *lab_left_statusBar;
    QLabel *lab_size_statusBar;
    QLabel *lab_hight_statusBar;
    QLabel *lab_samkoon_statusBar;
    QLabel *lab_width_statusBar;
    void modifyBitBtndlg(QGraphicsItem *item);//双击位按钮弹出对话框
    void modifyBitLampdlg(QGraphicsItem *item);//双击位按钮弹出对话框

    void modifyWeekdlg(QGraphicsItem *item);//双击的功能按钮弹出对话框
    void modifyDynCircledlg(QGraphicsItem *item);
    void modifyDynRectdlg(QGraphicsItem *item);

    void modifyTimeDisplaydlg(QGraphicsItem *item);//时间显示
    void modifyDateDisplaydlg(QGraphicsItem *item);//日期显示
    void modifyDynAlarmBardlg(QGraphicsItem *item);//动态报警条

    void modifyFlowBlock(QGraphicsItem *item);//流动块
    void modifyAlarmControldlg(QGraphicsItem *item);//报警控件
    void modifyHisAlarmdlg(QGraphicsItem *item);//历史报警显示器

    void OnModifyStaticPic(QGraphicsItem *item);//静态图片
    void OnModifyTextBoard(QGraphicsItem *item);//留言板
    void OnModifyComboBox(QGraphicsItem *item);//ComboBox
    void OnModifyLine(QGraphicsItem *item);//直线
    void OnModifyRect(QGraphicsItem *item);//矩形
    void OnModfyText(QGraphicsItem *item);//文本

    void OnModifyMsgDisplayDlg(QGraphicsItem *item);//消息显示
    void OnModifyTableDlg(QGraphicsItem *item);//表格
    void OnModifyScaleDlg(QGraphicsItem *item);//刻度
    void OnTrendChartDlg(QGraphicsItem * item);//趋势图
    void OnXYTrendChartDlg(QGraphicsItem *item);//XY趋势图
    void OnHISTrendChartDlg(QGraphicsItem *item);//历史趋势图

    void OnModfyComboBoxDlg(QGraphicsItem *item);//下拉框按钮
    void OnModfySliderDlg(QGraphicsItem *item); //滑块模拟量开关
    void OnModfyHisDataShowDlg(QGraphicsItem *item); //历史记录显示器
    void OnModfyAnimationDlg(QGraphicsItem *item); //动画

    void OnModfyRoundedRectDlg(QGraphicsItem *item); //圆角矩形
    void OnModfyArcDlg(QGraphicsItem *item); //基本扇形图形
    void OnModfyDataGroupDisplayDlg(QGraphicsItem *item); //数据群组显示
    void OnModfyTimerDlg(QGraphicsItem *item); //定时器
    void modifyKeyBoardASCII(QGraphicsItem *item);//ASCII字符输入键盘
    void modifyRecipeChoice(QGraphicsItem *item);//配方选择器
    void RefurbishConnect(SamDrawScene *pScene);//用户自定义键盘载入之后连接各种槽函数
    void modifyChartdlg(QGraphicsItem *item); //图表
    void modifyValuedlg(QGraphicsItem *item);
    void modifyImagedlg(QGraphicsItem *item);
    void modifyRecipeDisplay(QGraphicsItem *item);//配方显示器
    void modifyMFbtndlg(QGraphicsItem *item);//多功能按钮
    void deleteDirectory(QFileInfo fileList);
    void showMacroMenu();

signals:
    void InitScreenDlg();
    void InitScreenPropertyDlg();
    void newscreen_Assign();
    void newwindow_Assign();
    void screenProperty_assign();
    void windowProperty_assign();
    void InitWindowDlg();
    void InitWindowPropertyDlg();
    void copyScreen();
    void copyWindow();
    void deleteScreen();
    void deleteWindow();
    void SignalCompressProgress(int nProgress);
    void SignalGetvalue(int & nValue);
    void SignalInformation(QString str, MSG_TYPE eType);
    void upDate_treeScreenItem();
    void showNumDlg(QString str,QTreeWidgetItem *parentItem);//显示编号对话框
    void reTreeScreenAndWindow();//关闭和新建和打开的树控件画面和窗口的处理
    void openProreTreeCtl();//打开工程刷新树形控件
/*************************************************************************/
public:
    QStringList lsStr;//宏指令查找要用到

public:
    void handleWinTitle(QString &strTitle, QString str0);

private slots:
    void on_action_HMI_triggered();
    void on_action_upload_triggered();
    void on_actionCompress_triggered();
    void on_action_online_simulation_triggered();
    void on_action_macro_find_triggered();
    void on_action_macro_admin_triggered();
    void on_action_DatagroupDisplay_triggered();//数据群组
    //void on_action_open_mapstorage_triggered();
    void on_action_42_triggered();
    void on_action_41_triggered();
    void on_action_40_triggered();
    void on_action_39_triggered();
    void on_action_38_triggered();
    void on_action_37_triggered();
    void on_action_36_triggered();
    void on_action_quit_triggered();
    void on_action_save_as_triggered();
    void on_action_project_manager_triggered();
    void on_action_information_output_triggered();
    void on_action_sengtoback_triggered();
    void on_action_bringtop_triggered();
    void on_action_bringback_triggered();
    void on_action_bringforward_triggered();
    //void MarcoEdit(void);
    void StartDownload();
    void show_contextmenu(const QPoint& pos);
    void clearMessage();
    void ONRecipeChoice();//配方选择器
    void RunAboutDlg(); //关于对话框
    void MultiCopyDlg(); //多重复制
    void SlecetALL();//ctrl+A 全选
    void tree_newuserkeyboard();//添加用户自定义键盘
    void tree_deleteuserKeyboard();//删除用户自定义键盘
    void tree_UserKeyboardproperty();//用户自定义键盘属性界面
    //void OnCreatUploadDlg();//打开上载对话框
    //void on_action_triggered();
    void showDelMenu();
    void SlotItemClicked(QTreeWidgetItem *item, int column);
    void SlotItemClicked0(QTreeWidgetItem *item, int column);
    void treeItemLDclick(QTreeWidgetItem *item,int n);
    void treeItemLDclick0(QTreeWidgetItem *item,int n);
    void tree_addhisdatalogger();//树形控件历史数据信号 edit zhy
    //XXXXX
    void tree_deleteLink();//删除连接
    void tree_Linkproperty();//连接属性
    void createprodlg();//创建主界面新建工程对话框
    void clearTree();//清除原有树形控件
    //void createnewscreendlg();//创建新建画面
    void createsavedlg();//创建保存对话框
    void SaveProjectToFile(QString sFileName,int type);
    /**********物件工具栏的槽函数的添加***********************/
    void createrecipetable();//创建配方数据显示器
    void createbitbtndlg();//创建位按钮对话框
    void createMFbtndlg();//创建多功能按钮
    void createtimedisplaydlg();//创建时间显示对话框
    void createdatedisplaydlg();//创建日期显示对话框
    void createweekdisplaydlg();//创建星期显示对话框
    void createstaticpicturedlg();//创建静态图片显示对话框
    void createtrendchartdlg();//趋势图
    void createdyncricledlg();//创建动态圆显示对话框
    void createdynrentdlg();//创建动态圆矩形示对话框
    void createalarmcontroldlg();//创建报警控件对话框
    void createdynalarmbar();//创建动态报警条对话框
    void createhisalarm();//创建动态报警条对话框
    //void creategraphicsmove();//创建图形移动对话框
    //void createmeter();//创建仪表对话框
    void createchart();//穿件图表对话框
    void createvalue(); //创建数据显示对话框
    void createimage();//创建图片显示器对话框
    void createhisrecord();//创建历史数据显示器对话框
    void createmsgdisplay();//创建消息显示器
    void createflowblock();//创建流动块对话框
    void OnCreateTable();   //创建表格
    void OnCreateMessageBoard();//创建留言板
    void OnCreateComboBox();//创建ComboBox
    void OnCreateScales();   //创建刻度
    void OnCreateComboBoxDlg();//下拉框
    void OnCreateSliderDlg(); //滑块模拟量开关
    void OnCreateRoundedRect(); //圆角矩形
    void OnCreateArc(); //扇形
    //树形控件历史数据收集器相关信息 edit zhy
    void AddHisDataMenu();//历史数据收集器右键菜单
    void ShowSubHisdataMenu();//历史数据收集器0的右键菜单
    void tree_openhisdata();//打开历史数据收集器对话框函数
    void tree_deletehisdata();//删除历史数据收集器函数
    void tree_rename();//重命名数据收据器
    void CreateKeyboardASCII();//键盘组件
    //XXXXX
    void tree_newcom();//添加连接操作
    void tree_deleteAllLink();//删除连接操作
    void slotAddJML();//添加脚本库
    void slotAddJRL();//添加函数库
    void slotOpenMacro();//编辑脚本库

    void dockWidgetClose(int iData);//工程管理器、信息输出窗口关闭信号响应

    void on_action_tool_triggered();
public:
    void InitDateType(QComboBox *combobox);//初始化数据类别
    enum { MaxRecentFiles = 4 };//最多有4个最近打开的文档
    QAction *recentFileActs[MaxRecentFiles];
    void updateRecentFileActions();
    void setCurrentFile(const QString &fileName);
    bool is_Click_OpenrecentFile;//是否是点击的打开最近的文档
    bool is_OpenrecentFile;//是否是点击的打开最近的文档
    bool is_click_open;// 是否点击打开按钮
    QString  sOpenflieName;//点击的打开按钮的文件名字
    QString  sRecentflieName;//点击的最近打开的文件名字

public slots:
    void openRecentFile();//打开最近的文档
    void tree_newscreen();
    void newscreen_open();
    void newscreen_delete();
    void newscreen_property();
    void newscreen_copy();
    void tree_newWindow();
    void newswindow_open();
    void newswindow_delete();
    void newswindow_property();
    void newswindow_copy();
    void tree_recipe();
    void tree_openrecipe();
    void tree_deleterecipe();
    void tree_digitAlarm();//点击报警登陆的右键菜单上的数字报警登陆
    void digitAlarm_open();//点击数位报警登陆的右键菜单上的打开
    void digitAlarm_delete();//点击数位报警登陆的右键菜单上的删除
    void ChangetoChinese();//把工程翻译为中文
    void ChangetoEnglish();//把工程翻译为英文
    void createopenprodlg(QString path);//创建主界面打开工程对话框
    void createopenprodlg();//创建主界面打开工程对话框
    void reTree_ScreenAndWindow();
    void openPro_reTreeCtl();//打开工程刷新树形控件
    void SlotItemDBClick(QGraphicsItem *item);
    void openLink(QString name);//双击打开连接属性
    void openProtocol(QString parentName,QString name);//双击打开连接下的协议属性
    void addProtocol();//右键增加协议
    void delProtocol();//右键删除协议
    void openCurProtocol();

public:
    Ui::MainWindow *ui;
    void createActions();
    void createMenu();
    void createToolBars();
    void createStatusBar();
    //czq
    void initLeftDocking();
    void initRightDocking();
    void IintHisData();//初始化历史数据函数 zhy
    void deleteScreen_upDateIndex();//删除自定义键盘等更新所有画面按钮等空间
    int InitFontSize(QComboBox *fontsize);//字体大小初始化
    //czq
    //QTreeWidgetItem *hisdatalog_child;
    QVector<QTreeWidgetItem *> m_vecHisdatalogChild;
    QTreeWidgetItem *tree_hisdatalog;//数据采集
    void showMenu();//显示树控件上画面右键菜单
    void showScreenMenu();//显示树控件上画面第二级画面右键菜单
    void showAlarmMenu(); //显示树控件上报警登陆的右键菜单
    void showWindowMenu();//显示树控件上窗口右键菜单
    void showWindowSubMenu();//显示树控件上窗口右键菜单
    void showDigitalAlarmMenu();//数位报警登陆右键菜单
    void showRecipeMenu();//显示树控件配方右键菜单
    void showSubRecipeMenu();//显示树控件配方1右键菜单
    void reOpenPro();//重新打开工程或者新建时树控件的显示
    void initRecipeDlg();
    QString remove_leftZero(QString); //移除字符串左边的0
    QAction  *macroManagerAction;
    QAction  *multiKeyAction;
    QAction  *flowBlockAction;
    //QAction *pPieAction;
    QToolBar  *rightToolBar;
    myDockWidget *m_leftDock;
    myDockWidget *m_rightDock;

    myDockWidget *m_toolDock; //wxy 工具箱
    mytreeWidget *tree;
    //xiaoqiang
    mytreeWidget *tree0;
    QTreeWidgetItem *root0;
    QListWidget *listwidget;//预览列表
    QTreeWidgetItem *root;
    QTreeWidgetItem *copyScreen_Item;
    QTreeWidgetItem *copyWindow_Item;
    QTreeWidgetItem *copyUserKeyboard;//用户自定义键盘拷贝
    QComboBox  *statusButtoncmb;
    QLabel *qButtonLab;
    //QTextEdit   *textedit;
    //#include <QListView>
    QTableWidget *pMainList;

public: //edit by zqh
    //SamDrawScene pSceneSheet[MAX_SCRNCNT];
    QVector<SamDrawScene *> pSceneSheet;
    myGraphicsView *pView;
    QHBoxLayout *m_pLayout;
    SAM_DRAW_ACT_TYPE_E nControlType;
    int nActiveSheetIndex; //当前画面序号，从0开始
    int nActiveUserKeyboardIndex;//当前键盘
    //int nSheetTotalNumber; //当前工程建的画面总数
    bool bToolBarCMBInit;  //工具栏上的组合框初始化完成标示
    int nZoomNumber;       //一次缩放倍数
    bool bIfSceneShowGrid; //场景是否显示网格
    //bool bDrawAnimateFlag;  //画动画的标志
    //QList<QElipseItem *> pACircleList; //画动画位置圆的列表
    QComboBox  *qLanguagecmb; //工具栏上的语言选择框
    QLabel *qLanguageLab;
    int nLoadShapeType; //加载外形标示 0--一般外形，1--仪表外形
    int nLoadShapeFlag;//加载图表图形表示，1：图表类型，0：非图表类型，add for chart
    int nPcopyItenType; //记录图表保存的item是普通图形还是仪表图形。
public: //edit by zqh
    //void alterControlLanguage(QGraphicsItem *pItem,QStringList sList,int nID,
    //                          int nIndex); //chang the language by zqh

    //void changeItemLanguageAttr(QGraphicsItem *pItem);
    void AddCurrentItemStatusList(QGraphicsItem *pItem, int state);

    //void changeItemStatusAttr(QGraphicsItem *pItem);


    void compressFile(QString sFileName);
    void OnNewGraphicsScene(int nShowModel,int nWidth,int nHeight); //根据尺寸绘制画面大小新建场景
    //void OnNewGraphicsScene_Window(int nShowModel,int nWidth,int nHeight); //根据尺寸绘制画面大小新建场景
    void OnAddPattern(QComboBox *pComboBox);  //每个控件添加的样式
    QString ColorTOString(QColor color);
    void OnDoubleClikSpare(QGraphicsItem *item,QGraphicsItem *OldItem);
    void OnSingClikSpare(QGraphicsItem *oldItem);
    void OnDoubleClik(QGraphicsItem *item,QGraphicsItem *OldItem);
    QRectF GetItemRect(QGraphicsItem *item);
    void DrawScreenSize();
    void DrawWindowSize();
    void openInit_MenuAndTool();
    void OnSetMainSceneGrid();
    QString GetControlNO(QString sName);  //获得控件的编号
    void SetMultiStateText(QGraphicsItem *pItem,QStringList sList,int nID,
                           int nIndex,int nTotal);
    void OnFillAddressMsgClass(); //填充地址信息
    void fillTextMsgStruct(); //填充多语言文本信息，

    void OnFillVisiblePage(QStringList sList,QString sBtnName,int nSheetIndex);
    void OnFillAdvancedPage(QStringList sList,QString sBtnName,int nSheetIndex);
    bool CheckAddressInCompile();
    int IsAddressCheckRightInCompile(QString sAddr,int Type);
    void FillTreeAddress();
    //void OnDrawAnimate();
    QVector<QGraphicsItem *> child_userGroupItems;//用户自定义复制的情况
    void UserGroup(QGraphicsItem *pItem,int index );//打开的时候来熟悉编号（有自定义组合的空间）
    void IsDefineGroup(QGraphicsItem *);//是否是自定义组合
    bool USBCompile(QSqlDatabase &db,bool bsimulator = false);  //编译
    void setDefaultPlc(int nArray = -1);

public slots: //edit by zqh
    void OnDrawRect(); //画矩形
    void OnDrawLine(); //绘制直线
    void OnDrawEllipse(); //绘制圆
    void OnDrawPolygon(); //绘制多边形
    void OnDrawFoldLine();//绘制折线
    void OnDrawFreeLine();//绘制自由直线
    void onDrawBlightCircle(); //绘制曲线/圆弧
    void onDrawText();         //绘制Text文本
    void MessageOut(QString str, MSG_TYPE eType);
    void MessageOutEx(QString str, MSG_TYPE eType, MsgOutPut* pOutPut);
	void OnCopyItem();
	void OnPasteItem();
    void itemsMoved(SamDrawScene *scene,QList <QGraphicsItem *> movingItems,QList <QPointF >oldPoss);
    void itemResize(SamDrawScene *scene,QGraphicsItem *resizeItem,QSizeF size,QPointF oldPos);
    void lineItemchanged(SamDrawScene *scene,QGraphicsItem *item,
                         QPainterPath oldPath,QPainterPath newPath);
    void polygonchanged(SamDrawScene *scene,QGraphicsItem *item,
                        QPolygonF oldPolygon,QPolygonF newPolygon);
    void PreviewWindow();//预览窗口
    void OnSingleClickItem(); //QGraphicsItem *pItem
    void AddItemToScene();
    void updatePreviewWindow();//更新预览窗口
    void updateAllPreviewWindow();//更新预览窗口
    //void OnFinishDrawAnimate();
    void upDatetreeScreenItem();
    void OnSetZoomEnlarge();//放大
    void OnSetZoomFit();//复原
    void OnSetZoomSmall();//缩小
    void LoadProjectHelp();//加载帮助文档
private slots://edit by zqh
    void Reverse_selection();//反向选择
    void OnGroupItem();    //组合操作
    void OnDisGroupItem(); //取消组合
    void OnDeleteItem();   //删除图形
    void OnLockItem();     //锁定操作
    void OnUnLockItem();   //解锁操作
    void OnSetLeft();  //图形左对齐
    void OnSetRight(); //右对齐
    void OnSetTop();   //上对齐
    void OnSetButtom();//下对齐
    void OnSetHCenter(); //水平居中对齐
    void OnSetVCenter(); //垂直居中对齐
    void OnSetHSpacingAlign();//水平等间距对齐
    void OnSetVSpacingAlign();//垂直等间距
    void onWidthSame();       //设置等宽
    void onHeightSame();      //设置等高
    void onWidthHeightSame(); //设置等宽等高
    void onFrmLanguageChange(int nLanIndex);
    void OnAddNewScreen();      //新建画面
    void OnSetTheFrontScreen(); //上一幅画面
    void OnSetTheNextScreen();  //下一幅画面
    void listChange(int);//根据左边列表的改变来显示相应的列表
    void closeProject();//关闭工程
    void showNumDlg_ScreenAndWindow(QString,QTreeWidgetItem *);
    //void OnSetONState(); //设置为ON状态
    //void OnSetOFFState();//设置为OFF状态
    void onFrmStatecmbChange(int nIndex);//工具栏状态组合框发生改变
    void onScreenChange(int nStr);//
    void OnSetSceneGrid();//网格
    void OnSetDagViewModel();//设置视图模式
    void OnSetDagViewModelArrow();//鼠标是箭头
    void OnOpenPropertyDlg(); //打开属性对话框
    void OnFindAddressDlg();  //地址查找对话框
    void OnDisplayAddrUseDlg();//打开地址使用一览表对话框
    bool StartCompileThread();
    void USB_DownLoad(); //USB下载
    void MsgOutputListDoubleClicked(int nRow,int nClomn);//双击信息输出窗口
    void OnCreateAnimaDlg();
    void OnSetHMirror(); //水平镜像
    void OnSetVMirror(); //垂直镜像
    void OnCutItem(); //剪切
    void ExecuteOffLineMonitor(); //离线模拟
    void changeItem_x();
    void changeItem_y();
    void changeItem_w();
    void changeItem_h();
    void StartSimulator_on();
    void StartSimulator_off();

    void HandleRedoUndo();

    void SignalCompileEnd();//wxy
    void downFinished();
    void createXYtrend();
public:
    QUndoStack *undoStack;

public:
    QAction *undoAction;  /*撤销动作*/
    QAction *redoAction;  /*反撤销动作*/
    QAction *deleteAction;/*删除动作*/
    QUndoView *undoView;
    QMenu *editMenu;
    void createUndoView();
    //list_style
    QTabWidget*  dockTabWidget;
    QWidget*     subWidget1;//系统参数
    QWidget*     subWidget2;//画面
    QFrame*      widget;
    QVBoxLayout* dock_layout;
    QVBoxLayout* dock_layout1;
    QVBoxLayout* dock_layout2;
    //QComboBox* list_style;
    QStackedWidget  *stackeWidget;
    QTimer   *Ptimer;//预览窗口的定时器

public:    
    QGraphicsItem *pOldItem;
    void setActiveScreenIndex(QGraphicsScene *pScene);
    bool review_ScreenAndWindow_Name(QString);
    void OnCreateAnimation(); //动画
    void AndTreeSubItem(QGraphicsItem * newItem);//在画面或者窗口的树控件添加子项
    void ToSlectTreeItem(QStringList sList);// 单击场景上的Item是相应选择树形控件的项
    AddrMsg* pAddrMsg;  //存储地址信息类指针

    QVector<TEXTPRO> vTextMsg;//存储多语言文本信息，公查找替换使用

    QVector <AddrMsg*>vAddrMsg;//存储地址信息类动态数组
    MsgOutPut* pMsgOutPut;//信息输出窗口双击要处理的类

    QMap<int, MsgOutPut*>mapMsgOutPutItem;


    QGraphicsItem *pDrawToSceneItem;   //保存点击确定后控件Item
    //QVector <InitMaroClass *>vInitMaro;//保存初始化宏动态数组
    //QVector <GlobalMaroClass *>vGlobalMaro;//保存全局宏宏动态数组
    void PasteItemToScene();//粘贴ITEM到场景
    void deleteItem_upDateTreeContrl(QList<QGraphicsItem *> list);//删除场景的ITem时更新树形控件
     QString ControlNO(QString sName);  //获得控件的编号(在组合的时候用上面的GetControlNO不适用)
    bool eventFilter ( QObject * watched, QEvent * event )  ;
    void OnAddColorDlg(QPushButton *pbtn,ColorPickerPopup *colorPicker);  //每个控件添加颜色对话框
    QGraphicsItem * PasteItemToScence();//当粘贴Item到场景的时候
    void deleteItem_undefineGroup(QGraphicsItem *);//删除自定义的控件同时更新树形控件
    QGraphicsItem * IsHaveLibraryItem(QGraphicsItem *pItem); //判断是否含有图库item
    QGraphicsItem * OpenLibraryFile(QString str);
    QGraphicsItem * onGetItemFromFile(QString sPath);
    QList<QGraphicsItem *> SaveItemToLibList; //保存item到图库中的item

    void fillMarcoUseStruct(QString, QString, QStringList&);
    void findScreenAllMarco(QVector<MarcoString> &mStr);
    void fillMarcoName(int ifuse,int marcoindex,int nIndex,
                       QGraphicsItem *pItem,QString sCtrlName,QStringList sList);
    bool CheckMarcoIsNullInCompile(QString& strLibName);
    bool checkMacroName();
    void showCompileMsg(QString str,QGraphicsItem *pItem,int row,int index);
    //void compileLibrary(QSqlDatabase &db,int &count,int sceneId,int itemId);
    void compileVarTable(QSqlDatabase &db,int &count);
    void compileInitLibrary(QSqlDatabase &db,int &count);
    void compileGlobalLibrary(QSqlDatabase &db,int &count);
    QVector <SamDrawScene *> vBaseLibraryScene;  //存画面的容器
    void loadBaseLibAndUserDefineLib(); //加载基本图库和用户自定义图库
    void ResetPic(QGraphicsItem *pItem);
    void ResetItem(PicPosInfo posinfo,QGraphicsItem *pItem);
    bool FocusInStatusbar();
    QGraphicsItem * ReloadPic(QGraphicsItem *pItem,SamDrawScene *scene,int flag = 0);//打开组态的时候重新载入图片
    QGraphicsItem * ReloadItem(QGraphicsItem *pItem,bool btransparent,QString sColor,
                                           PicPosInfo posinfo,QString sPath);
    void SavePicToFile(QStringList pathList,QDataStream &stream);
    void LoadPicFromFile(QDataStream &stream);
    int IsCheckAddressRight(Keyboard &keyboard,QString WaringMsg,QLineEdit *pLineEdit,int Addr_Type,QString sAddr);
    void loadHelpHtm(int nKey); //加载帮助文档
    void uncompressFile(QString sSourceName,QString sSaveName);
    void SaveToStream(QString sSourceFile,QString sFileName,QDataStream &stream);
    void LoadFromStream(QString sFileName,QDataStream &stream);
    void SaveFontDir(QStringList list,QDataStream &stream);
    void deleteMacro(QString sMacroName);
private:
    void lockCurrentSheetItem(int nSheetIndex);//int nSelectLibType,
    void shareAddressCode(Keyboard &TreeAddr,QString sName, int recipeNum = 0);
    void compileArrangeAddr(QSqlDatabase &db,int nSceneId);
    stProtocol getPlcModel(QString name,int &connectType);
    std::vector<addrTargetProp> getArrangedAddrs(stProtocol cModel,
            std::vector<addrTargetProp> addrs);
    void complieArranged(QSqlDatabase &db,int nSceneId,int nConnectType,
            stProtocol cModel,std::vector<addrTargetProp>addrs);//新添加的数据,不需要保存
    void loadSysLibs();//载入脚本库

    void fillTreeTextMsg();
    void replaceTreeTextMsg(QString sOldMsg,QString sNewMsg);
public:
	QMultiMap<QString ,addrTargetProp> addrsInScene;//场景中用到的所有地址
	QMultiMap<QString ,addrTargetProp> addrsInSysPrarm;//系统参数中用到的所有地址
    void setStatusBarCtrlName(QGraphicsItem *pItem);
	QMap<QString,QString> getFontMap();
	QMap<QString,QString> m_LocalReg;

	QString GetFontFile(QString sFontType);
	void getAllFontNames(QSqlDatabase &db);
	void initFontMap();
	bool checkSysParam();
	inline int getProVersion()
	{
		return m_ProVersionNum;
	}
	inline void setProVersion(int versionNum)
	{
		m_ProVersionNum = versionNum;
	}
private:
    //设置工具箱中的按钮浮动效果
    void setToolBoxFloat();
    void setDynamicImage(QPushButton *button);
	QMap<QString,QString> m_fontMap;
	QMap<QString,QString> sysFontMap;
	int m_ProVersionNum;//打开组态的版本号
    QMap<QString, QString>m_factoryMap;

    //add by wxy
    QVector <VarPro> g_Vars; //全局变量组

    //新增变量表 13-10-17
    QTreeWidgetItem *tree_varRcd;

    void setWindowFirst();
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
public:
    QString findFactoryFullName(QString str);
    void savePicPath(QItemGroup *pItemGroup,QMap<QString, QString> &mPath);
    void loadPicPath(QItemGroup *pItemGroup,QMap<QString, QString> &mPath);

    QVector <VarPro> getGlobalVars();   //获取全局变量
    bool appendGlobalVar(VarPro variant);      //增加一个变量
    void setGlobalVar(QVector <VarPro> variants);

    void updateChScreen();   //wxy 更新屏幕下拉框的内容
    void savePlcPrj(QDataStream &stream);
    void loadPlcPrj(QString filename,QDataStream &stream);
    bool compilePlcPrj();

    SimulatorDlg *pSimDlg;
    QTabWidget*  ToolBarTabWidget;
    QScrollArea* scrollAreaBasic; //基本图形
    QScrollArea* scrollAreaCtl;   //控件

    //wxy增加MD5生成、检验函数，用于编译过程中资源的检测
    bool checkMD5(QByteArray md5, QString filePath);
    QByteArray getFileMd5(QString filePath);

    QMap<QString, QByteArray> mPicMd5;//wxy图片路径对应的MD5码
    QMap<QString, int>m_ChScreenMap;//wxy屏幕下拉框列表与画面存储顺序映射
    QVector<DBQuery > vAllDbQuery;
    void inSertDbQuery(QString tableName,QMap<QString,QVariant> mapDbquery);
    QList<int >m_Ids;
    int getNewId();
    bool insertId(int nId);

};



#endif // MAINWINDOW_H
