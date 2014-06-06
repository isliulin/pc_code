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
#include "headfile/global_types.h"  //�궨��ͷ�ļ�
#include "Frame\TreeCtrlDlg\qtreectrlnewscreendlg.h"
#include "NewProjectWizard\qnewprodlg.h"//�½����̶Ի���ͷ�ļ�
#include "qprogectmanager.h"
#include "Frame\TreeCtrlDlg\qtreectrltimedlg.h"
#include "Frame\TreeCtrlDlg\qtreectrlrecipedlg.h"//�䷽
#include "Frame/TreeCtrlDlg/qdatatransportdlg.h"//���ϴ���
/**********�����������������Ի���*************/
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
/**********��ͼ���������Ի���*************/
#include "Frame/DrawDlg/qlinedlg.h"
#include "Frame/DrawDlg/qrectdlg.h"
//#include "Frame/DrawDlg/qtextdlg.h"
#include "Frame/aboutdlg.h"//���ڶԻ���
#include "Frame/qmulticopy.h"//���ظ�ֵ
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
/*******�������θ������ڵĳ�ʼ��С**************/
class mytreeWidget : public QTreeWidget
{
public:
    QSize sizeHint() const
    {
        return QSize(200, 900); /* �����ﶨ��dock�ĳ�ʼ��С */
    }
};

//add by wuxiyang
//����tab������ת��
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
//���ӹر��ź�
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
    QStringList sLibraryPath;//����ͼ�⵱ǰ�򿪵�·�����´δ�ͼ��ѡ������ǰ·��
    /*add by tang haiguo */
    QSamSysParame *m_pSamSysParame;
    QVector<MacroLibrary > librarys; //�ű��� Ҳ���Ǻ�ָ��
    QVector<Macro> macros; //�ű��� Ҳ���Ǻ�ָ��
    void saveLibrary(QDataStream &stream);//����ű�
    void loadLibrary(QDataStream &stream);//��ȡ�ű�
    void init();
    //czq
    //unsigned int m_curDataLog;//��ǰ�������ǵڼ������ݲɼ�����,0����ǰû�����ݲɼ�

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

    QComboBox* pChScreen;        //��Ļ�б�������

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
    bool is_haveScreen;//�Ƿ���ڳ���
    bool is_SaveAS;//�Ƿ����Ϊ
    bool is_Save;//�Ƿ񱣴�
    bool is_NeedCompiled;//wxy ������ʶ�Ƿ���Ҫ���±���
    QString sOpenFileVersion;
    bool bCpyAndPaste;
    QString saveAs_Name;//���Ϊ����
    bool   isHave;//������½����̵�ȷ����ťʱ���ؼ����������Ч
    bool    is_Is;
    bool  isCompiled;
    CompileThrd *thread;
    downloadTrd *threadDownload;
    QColor StringTOColor(QString sColor);
    //int  nScreen_Width;//��Ļ �Ŀ��
    //int  nScreen_Height;//��Ļ�ĸ߶�
    bool isCheck_ScreenProperty;//�Ƿ�ѡ��������Բ˵�
    bool isCheck_WindowProperty;//�Ƿ�ѡ�񴰿ڵ����Բ˵�
    bool is_ScreenProperty_Name;//�����������ʱ���ж�����
    bool is_WindowProperty_Name;//�����������ʱ���ж�����
    QTreeWidgetItem *screen;//���ؼ���һ������
    QTreeWidgetItem *window;////���ؼ���һ������
    QTreeWidgetItem *tree_macro;////���ؼ���һ����ָ��
    QTreeWidgetItem *global_macro;
    QTreeWidgetItem *init_macro;
    QNewWindowDlg  *newWindowDlg;//�Ҽ�������ؼ��ϵ�һ������˵����ɵ��½����ڶԻ���
    QTreeCtrlNewScreenDlg  *newScreenDlg;//�Ҽ�������ؼ��ϵ�һ������˵����ɵ��½�����Ի���
    QCopyScreenDlg           *newCopyScreen;//�Ҽ�������ؼ��ϵ�2������˵����ɵ��½����ƻ���Ի���
    QCopyWindowDlg             *newCopyWindow;//�Ҽ�������ؼ��ϵ�2������˵����ɵ��½����ƻ���Ի���
    QTreeWidgetItem *newScreen[MAX_SCRNCNT]; //���ؼ��ϵ�2������˵��ĵĸ���
    QTreeWidgetItem *TreeuserKeyboard[30];//���οؼ��û��Զ������
    //QVector<SamDrawScene *> pUserKeyboard_vector;//�û��Զ����������

    QVector<QTreeWidgetItem *>screenSubItem_vector;

    QTreeWidgetItem *alarmlog;//��һ��������½
    QVector<QString> alarm_name;//���汨���ĸ�������
    QVector<int> alarm_style;//���汨��style 0-digital
    QTreeWidgetItem *recipe;//���ؼ���һ���䷽
    QTreeWidgetItem *datatransport;//���ϴ���
    QTreeWidgetItem *treeScheduler;
    QTreeWidgetItem *sub_Recipe;//���ؼ���2���䷽"�䷽1"
    int nscreen;//�����Ӽ��ĸ���
    //bool isHave_Recipe;//�Ƿ�����䷽
    //int ifhisdataexist;//��ʷ�����Ƿ����
    bool bSimulator;
    QUserKeyboard *userkeyboarddlg;//�û��Զ�����̶Ի���
    QTreeWidgetItem *TreeKeyboard;//�Զ������
    QUserKeyboardProperty *userkeyboardproperty;//�û��Զ���������ԶԻ���
    void showUserKeyboard();//�û��Զ�������Ҽ����Բ˵�
    void showUserKeyboardAddnew();//�û��Զ�������Ҽ��½��˵�
    bool OnCheckUserkeyboard();//����ʱ����û��Զ�����̺���
    void checkUserKeyboard();//�����ʱ�����Ƿ��õ��û��Զ������

    int nFindActiveSheetIndex(QString stemp);//���Һ������ڲ��ҵ�ǰѡ�е�ҳ���������еľ���λ��
    void fillUserKeyboard(QStringList &sList);//�������Ϻ������е�ַ����
    void deletehisdata();//ɾ����ʷ���ݵ�ʱ�������ʷ��������
    QString GetHMIConnectInformation(QString sHMIModle);//����HMI�ͺ�ȷ�����ӿ�
    //XXXXX

    int                   nCurrentDigitalAlarmIndex;//��ǰ�����ݱ���
    int                   nCurrentAnalog_alarmIndex;
    int                   m_digitalAlarm;    //���ؼ�����λ������½�ұߵ�β��
    //int                   nanalogAlarm;       //��ȱ�����½�ĸ���
    int                   m_analogAlarm;       //���ؼ�����ȱ�����½�ұߵ�β��
    QTreeWidgetItem *digital_treeItem[DIGIT_ALARM_NUM];//�����λ������½
    QTreeWidgetItem *analog_treeItem[ANALOG_ALARM_NUM];//�����ȱ�����½
    QVector<QTreeWidgetItem *> digital_alarmlogItem_Vector;//
    QVector<QTreeWidgetItem *> analog_alarmlogItem_Vector;
    /******************���ݵķ�װ******************************************/
    QNewPro  *newpro;
    //edit zhy
    int  GetFristScreenID(int nIncludeWindow);//�õ���һ�������������е�λ��
    void reUserkeyboardname(QString sOldName,QString sNewName);//�����Զ���������Ƶ�ʱ��ˢ���õ����Զ�����̵Ŀؼ�
    void Rename(QString sOldName,QString sNewName,QStringList &sList);//�����Ǹ������ĸ�������
    bool bCheckFount(QComboBox &fontcombobox);
    //XXXXX
    void ShowlinkProperty();//�����Ҽ��˵�
    QString  GetSCreenName(int nScreenId);//ͨ�� �߼������ҵ���Ӧ��ʵ������
    int GetSCreenID(int nScreenId);//ͨ���߼������ҵ���Ӧ�����ʵ������
    QVector<int> nSimulatorport;//�洢ģ��ʱ���ѡ�еĵ�ǰ�����ӿ�
    void  reScreenorwindowName(QString sOldname,QString sNewname);//���ָ���֮��ˢ�¿ؼ��е�����
    QString KeyboardToString(Keyboard keyboard);//��ַת��Ϊ�ַ�������
    void StringToKeyboard(Keyboard &keyboard,QString sKeyboard);//�ַ���ת��Ϊ��ַ����
    void GroupTypeKey(QGraphicsItem *item);//˫���򿪶Ի������е��ж����ͼ�εĺ���
    void BasicGraphicsItem(QGraphicsItem *item);//����ͼ�εĺ���
    int Addr_Type;//��ʾ���ֻ���λ
    int DataType;//�洢�������
    int CheckMinMax(QString Min, QString Max, int DataType,int CheckType);
    int IsAddressCheckRight(Keyboard &keyboard,QString WaringMsg,QLineEdit *pLineEdit,int Addr_Type);
    int IsMyAddressCheckRight(Keyboard &keyboard,QString WaringMsg,QLineEdit *pLineEdit,int Addr_Type, QSpinBox *pSpinBox);
    int CheckString(Keyboard &keyboard,QString sourceStr,int Addr_Type);
    int CheckExternAddr(Keyboard &keyboard,QString sourceStr,int Addr_Type);
        int getCurrentSamp();
        void languageChangeForRecipe(int nIndex);

    QVector <QTreeWidgetItem *> vTreeLinkType;
    //+++++
    QTreeWidgetItem*  plcConnect;        //PLC����
    QTreeWidgetItem*  sysSetting;     //ϵͳ����---root----
    QTreeWidgetItem*  pcCtrl;         //��������----------
    QTreeWidgetItem*  pcChoice;       //����ѡ��
    QTreeWidgetItem*  displaySet;     //��ʾ����
    QTreeWidgetItem*  operateSet;     //��������
    QTreeWidgetItem*  dataCtrl;       //���ݿ���
    QTreeWidgetItem*  permissionSec;  //�û�Ȩ��
    //QTreeWidgetItem*  timeArea;       //ʱ��&����
    QTreeWidgetItem*  hostPeri;       //��������----------
    QTreeWidgetItem*  printer;        //��ӡ��
    //QTreeWidgetItem*  networkAd;      //����������
    QTreeWidgetItem*  confiWorks;     //��̬����----------
    QTreeWidgetItem*  downloadSet;    //��������
    QTreeWidgetItem*  accessEncry;    //���ʼ���
    QTreeWidgetItem   *clock;         //ʱ������
    QTreeWidgetItem*  productLicen;   //��Ʒ��Ȩ
    QTreeWidgetItem*  lanSet;         //��������
    QTreeWidgetItem* chdItem;
    //QTreeWidgetItem*  datatransport;  //���ϴ���
    //old
    //XXXXX
    QTreeWidgetItem *link;          //����
#ifdef AKPLC
    QTreeWidgetItem *PlcNode;//Plc���
#endif
    //XXXXX
    void ShowComLink();//�������ӻ����Ҽ��˵�
    void information(QString str, MSG_TYPE eType);
    int  DealWithDeleteScreen();//����ɾ�����洰���Զ�����̵�ʱ�����οؼ�ˢ������
    QSizeF ScalePicture(QSizeF size1,QSizeF size2,QSizeF oldSize);
    //ͼƬ·��map
    //����ʱ�����Ҫ���ص�����
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

    /**********************������******************************/
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
    void modifyBitBtndlg(QGraphicsItem *item);//˫��λ��ť�����Ի���
    void modifyBitLampdlg(QGraphicsItem *item);//˫��λ��ť�����Ի���

    void modifyWeekdlg(QGraphicsItem *item);//˫���Ĺ��ܰ�ť�����Ի���
    void modifyDynCircledlg(QGraphicsItem *item);
    void modifyDynRectdlg(QGraphicsItem *item);

    void modifyTimeDisplaydlg(QGraphicsItem *item);//ʱ����ʾ
    void modifyDateDisplaydlg(QGraphicsItem *item);//������ʾ
    void modifyDynAlarmBardlg(QGraphicsItem *item);//��̬������

    void modifyFlowBlock(QGraphicsItem *item);//������
    void modifyAlarmControldlg(QGraphicsItem *item);//�����ؼ�
    void modifyHisAlarmdlg(QGraphicsItem *item);//��ʷ������ʾ��

    void OnModifyStaticPic(QGraphicsItem *item);//��̬ͼƬ
    void OnModifyTextBoard(QGraphicsItem *item);//���԰�
    void OnModifyComboBox(QGraphicsItem *item);//ComboBox
    void OnModifyLine(QGraphicsItem *item);//ֱ��
    void OnModifyRect(QGraphicsItem *item);//����
    void OnModfyText(QGraphicsItem *item);//�ı�

    void OnModifyMsgDisplayDlg(QGraphicsItem *item);//��Ϣ��ʾ
    void OnModifyTableDlg(QGraphicsItem *item);//���
    void OnModifyScaleDlg(QGraphicsItem *item);//�̶�
    void OnTrendChartDlg(QGraphicsItem * item);//����ͼ
    void OnXYTrendChartDlg(QGraphicsItem *item);//XY����ͼ
    void OnHISTrendChartDlg(QGraphicsItem *item);//��ʷ����ͼ

    void OnModfyComboBoxDlg(QGraphicsItem *item);//������ť
    void OnModfySliderDlg(QGraphicsItem *item); //����ģ��������
    void OnModfyHisDataShowDlg(QGraphicsItem *item); //��ʷ��¼��ʾ��
    void OnModfyAnimationDlg(QGraphicsItem *item); //����

    void OnModfyRoundedRectDlg(QGraphicsItem *item); //Բ�Ǿ���
    void OnModfyArcDlg(QGraphicsItem *item); //��������ͼ��
    void OnModfyDataGroupDisplayDlg(QGraphicsItem *item); //����Ⱥ����ʾ
    void OnModfyTimerDlg(QGraphicsItem *item); //��ʱ��
    void modifyKeyBoardASCII(QGraphicsItem *item);//ASCII�ַ��������
    void modifyRecipeChoice(QGraphicsItem *item);//�䷽ѡ����
    void RefurbishConnect(SamDrawScene *pScene);//�û��Զ����������֮�����Ӹ��ֲۺ���
    void modifyChartdlg(QGraphicsItem *item); //ͼ��
    void modifyValuedlg(QGraphicsItem *item);
    void modifyImagedlg(QGraphicsItem *item);
    void modifyRecipeDisplay(QGraphicsItem *item);//�䷽��ʾ��
    void modifyMFbtndlg(QGraphicsItem *item);//�๦�ܰ�ť
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
    void showNumDlg(QString str,QTreeWidgetItem *parentItem);//��ʾ��ŶԻ���
    void reTreeScreenAndWindow();//�رպ��½��ʹ򿪵����ؼ�����ʹ��ڵĴ���
    void openProreTreeCtl();//�򿪹���ˢ�����οؼ�
/*************************************************************************/
public:
    QStringList lsStr;//��ָ�����Ҫ�õ�

public:
    void handleWinTitle(QString &strTitle, QString str0);

private slots:
    void on_action_HMI_triggered();
    void on_action_upload_triggered();
    void on_actionCompress_triggered();
    void on_action_online_simulation_triggered();
    void on_action_macro_find_triggered();
    void on_action_macro_admin_triggered();
    void on_action_DatagroupDisplay_triggered();//����Ⱥ��
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
    void ONRecipeChoice();//�䷽ѡ����
    void RunAboutDlg(); //���ڶԻ���
    void MultiCopyDlg(); //���ظ���
    void SlecetALL();//ctrl+A ȫѡ
    void tree_newuserkeyboard();//����û��Զ������
    void tree_deleteuserKeyboard();//ɾ���û��Զ������
    void tree_UserKeyboardproperty();//�û��Զ���������Խ���
    //void OnCreatUploadDlg();//�����ضԻ���
    //void on_action_triggered();
    void showDelMenu();
    void SlotItemClicked(QTreeWidgetItem *item, int column);
    void SlotItemClicked0(QTreeWidgetItem *item, int column);
    void treeItemLDclick(QTreeWidgetItem *item,int n);
    void treeItemLDclick0(QTreeWidgetItem *item,int n);
    void tree_addhisdatalogger();//���οؼ���ʷ�����ź� edit zhy
    //XXXXX
    void tree_deleteLink();//ɾ������
    void tree_Linkproperty();//��������
    void createprodlg();//�����������½����̶Ի���
    void clearTree();//���ԭ�����οؼ�
    //void createnewscreendlg();//�����½�����
    void createsavedlg();//��������Ի���
    void SaveProjectToFile(QString sFileName,int type);
    /**********����������Ĳۺ��������***********************/
    void createrecipetable();//�����䷽������ʾ��
    void createbitbtndlg();//����λ��ť�Ի���
    void createMFbtndlg();//�����๦�ܰ�ť
    void createtimedisplaydlg();//����ʱ����ʾ�Ի���
    void createdatedisplaydlg();//����������ʾ�Ի���
    void createweekdisplaydlg();//����������ʾ�Ի���
    void createstaticpicturedlg();//������̬ͼƬ��ʾ�Ի���
    void createtrendchartdlg();//����ͼ
    void createdyncricledlg();//������̬Բ��ʾ�Ի���
    void createdynrentdlg();//������̬Բ����ʾ�Ի���
    void createalarmcontroldlg();//���������ؼ��Ի���
    void createdynalarmbar();//������̬�������Ի���
    void createhisalarm();//������̬�������Ի���
    //void creategraphicsmove();//����ͼ���ƶ��Ի���
    //void createmeter();//�����Ǳ�Ի���
    void createchart();//����ͼ��Ի���
    void createvalue(); //����������ʾ�Ի���
    void createimage();//����ͼƬ��ʾ���Ի���
    void createhisrecord();//������ʷ������ʾ���Ի���
    void createmsgdisplay();//������Ϣ��ʾ��
    void createflowblock();//����������Ի���
    void OnCreateTable();   //�������
    void OnCreateMessageBoard();//�������԰�
    void OnCreateComboBox();//����ComboBox
    void OnCreateScales();   //�����̶�
    void OnCreateComboBoxDlg();//������
    void OnCreateSliderDlg(); //����ģ��������
    void OnCreateRoundedRect(); //Բ�Ǿ���
    void OnCreateArc(); //����
    //���οؼ���ʷ�����ռ��������Ϣ edit zhy
    void AddHisDataMenu();//��ʷ�����ռ����Ҽ��˵�
    void ShowSubHisdataMenu();//��ʷ�����ռ���0���Ҽ��˵�
    void tree_openhisdata();//����ʷ�����ռ����Ի�����
    void tree_deletehisdata();//ɾ����ʷ�����ռ�������
    void tree_rename();//�����������վ���
    void CreateKeyboardASCII();//�������
    //XXXXX
    void tree_newcom();//������Ӳ���
    void tree_deleteAllLink();//ɾ�����Ӳ���
    void slotAddJML();//��ӽű���
    void slotAddJRL();//��Ӻ�����
    void slotOpenMacro();//�༭�ű���

    void dockWidgetClose(int iData);//���̹���������Ϣ������ڹر��ź���Ӧ

    void on_action_tool_triggered();
public:
    void InitDateType(QComboBox *combobox);//��ʼ���������
    enum { MaxRecentFiles = 4 };//�����4������򿪵��ĵ�
    QAction *recentFileActs[MaxRecentFiles];
    void updateRecentFileActions();
    void setCurrentFile(const QString &fileName);
    bool is_Click_OpenrecentFile;//�Ƿ��ǵ���Ĵ�������ĵ�
    bool is_OpenrecentFile;//�Ƿ��ǵ���Ĵ�������ĵ�
    bool is_click_open;// �Ƿ����򿪰�ť
    QString  sOpenflieName;//����Ĵ򿪰�ť���ļ�����
    QString  sRecentflieName;//���������򿪵��ļ�����

public slots:
    void openRecentFile();//��������ĵ�
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
    void tree_digitAlarm();//���������½���Ҽ��˵��ϵ����ֱ�����½
    void digitAlarm_open();//�����λ������½���Ҽ��˵��ϵĴ�
    void digitAlarm_delete();//�����λ������½���Ҽ��˵��ϵ�ɾ��
    void ChangetoChinese();//�ѹ��̷���Ϊ����
    void ChangetoEnglish();//�ѹ��̷���ΪӢ��
    void createopenprodlg(QString path);//����������򿪹��̶Ի���
    void createopenprodlg();//����������򿪹��̶Ի���
    void reTree_ScreenAndWindow();
    void openPro_reTreeCtl();//�򿪹���ˢ�����οؼ�
    void SlotItemDBClick(QGraphicsItem *item);
    void openLink(QString name);//˫������������
    void openProtocol(QString parentName,QString name);//˫���������µ�Э������
    void addProtocol();//�Ҽ�����Э��
    void delProtocol();//�Ҽ�ɾ��Э��
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
    void IintHisData();//��ʼ����ʷ���ݺ��� zhy
    void deleteScreen_upDateIndex();//ɾ���Զ�����̵ȸ������л��水ť�ȿռ�
    int InitFontSize(QComboBox *fontsize);//�����С��ʼ��
    //czq
    //QTreeWidgetItem *hisdatalog_child;
    QVector<QTreeWidgetItem *> m_vecHisdatalogChild;
    QTreeWidgetItem *tree_hisdatalog;//���ݲɼ�
    void showMenu();//��ʾ���ؼ��ϻ����Ҽ��˵�
    void showScreenMenu();//��ʾ���ؼ��ϻ���ڶ��������Ҽ��˵�
    void showAlarmMenu(); //��ʾ���ؼ��ϱ�����½���Ҽ��˵�
    void showWindowMenu();//��ʾ���ؼ��ϴ����Ҽ��˵�
    void showWindowSubMenu();//��ʾ���ؼ��ϴ����Ҽ��˵�
    void showDigitalAlarmMenu();//��λ������½�Ҽ��˵�
    void showRecipeMenu();//��ʾ���ؼ��䷽�Ҽ��˵�
    void showSubRecipeMenu();//��ʾ���ؼ��䷽1�Ҽ��˵�
    void reOpenPro();//���´򿪹��̻����½�ʱ���ؼ�����ʾ
    void initRecipeDlg();
    QString remove_leftZero(QString); //�Ƴ��ַ�����ߵ�0
    QAction  *macroManagerAction;
    QAction  *multiKeyAction;
    QAction  *flowBlockAction;
    //QAction *pPieAction;
    QToolBar  *rightToolBar;
    myDockWidget *m_leftDock;
    myDockWidget *m_rightDock;

    myDockWidget *m_toolDock; //wxy ������
    mytreeWidget *tree;
    //xiaoqiang
    mytreeWidget *tree0;
    QTreeWidgetItem *root0;
    QListWidget *listwidget;//Ԥ���б�
    QTreeWidgetItem *root;
    QTreeWidgetItem *copyScreen_Item;
    QTreeWidgetItem *copyWindow_Item;
    QTreeWidgetItem *copyUserKeyboard;//�û��Զ�����̿���
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
    int nActiveSheetIndex; //��ǰ������ţ���0��ʼ
    int nActiveUserKeyboardIndex;//��ǰ����
    //int nSheetTotalNumber; //��ǰ���̽��Ļ�������
    bool bToolBarCMBInit;  //�������ϵ���Ͽ��ʼ����ɱ�ʾ
    int nZoomNumber;       //һ�����ű���
    bool bIfSceneShowGrid; //�����Ƿ���ʾ����
    //bool bDrawAnimateFlag;  //�������ı�־
    //QList<QElipseItem *> pACircleList; //������λ��Բ���б�
    QComboBox  *qLanguagecmb; //�������ϵ�����ѡ���
    QLabel *qLanguageLab;
    int nLoadShapeType; //�������α�ʾ 0--һ�����Σ�1--�Ǳ�����
    int nLoadShapeFlag;//����ͼ��ͼ�α�ʾ��1��ͼ�����ͣ�0����ͼ�����ͣ�add for chart
    int nPcopyItenType; //��¼ͼ�����item����ͨͼ�λ����Ǳ�ͼ�Ρ�
public: //edit by zqh
    //void alterControlLanguage(QGraphicsItem *pItem,QStringList sList,int nID,
    //                          int nIndex); //chang the language by zqh

    //void changeItemLanguageAttr(QGraphicsItem *pItem);
    void AddCurrentItemStatusList(QGraphicsItem *pItem, int state);

    //void changeItemStatusAttr(QGraphicsItem *pItem);


    void compressFile(QString sFileName);
    void OnNewGraphicsScene(int nShowModel,int nWidth,int nHeight); //���ݳߴ���ƻ����С�½�����
    //void OnNewGraphicsScene_Window(int nShowModel,int nWidth,int nHeight); //���ݳߴ���ƻ����С�½�����
    void OnAddPattern(QComboBox *pComboBox);  //ÿ���ؼ���ӵ���ʽ
    QString ColorTOString(QColor color);
    void OnDoubleClikSpare(QGraphicsItem *item,QGraphicsItem *OldItem);
    void OnSingClikSpare(QGraphicsItem *oldItem);
    void OnDoubleClik(QGraphicsItem *item,QGraphicsItem *OldItem);
    QRectF GetItemRect(QGraphicsItem *item);
    void DrawScreenSize();
    void DrawWindowSize();
    void openInit_MenuAndTool();
    void OnSetMainSceneGrid();
    QString GetControlNO(QString sName);  //��ÿؼ��ı��
    void SetMultiStateText(QGraphicsItem *pItem,QStringList sList,int nID,
                           int nIndex,int nTotal);
    void OnFillAddressMsgClass(); //����ַ��Ϣ
    void fillTextMsgStruct(); //���������ı���Ϣ��

    void OnFillVisiblePage(QStringList sList,QString sBtnName,int nSheetIndex);
    void OnFillAdvancedPage(QStringList sList,QString sBtnName,int nSheetIndex);
    bool CheckAddressInCompile();
    int IsAddressCheckRightInCompile(QString sAddr,int Type);
    void FillTreeAddress();
    //void OnDrawAnimate();
    QVector<QGraphicsItem *> child_userGroupItems;//�û��Զ��帴�Ƶ����
    void UserGroup(QGraphicsItem *pItem,int index );//�򿪵�ʱ������Ϥ��ţ����Զ�����ϵĿռ䣩
    void IsDefineGroup(QGraphicsItem *);//�Ƿ����Զ������
    bool USBCompile(QSqlDatabase &db,bool bsimulator = false);  //����
    void setDefaultPlc(int nArray = -1);

public slots: //edit by zqh
    void OnDrawRect(); //������
    void OnDrawLine(); //����ֱ��
    void OnDrawEllipse(); //����Բ
    void OnDrawPolygon(); //���ƶ����
    void OnDrawFoldLine();//��������
    void OnDrawFreeLine();//��������ֱ��
    void onDrawBlightCircle(); //��������/Բ��
    void onDrawText();         //����Text�ı�
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
    void PreviewWindow();//Ԥ������
    void OnSingleClickItem(); //QGraphicsItem *pItem
    void AddItemToScene();
    void updatePreviewWindow();//����Ԥ������
    void updateAllPreviewWindow();//����Ԥ������
    //void OnFinishDrawAnimate();
    void upDatetreeScreenItem();
    void OnSetZoomEnlarge();//�Ŵ�
    void OnSetZoomFit();//��ԭ
    void OnSetZoomSmall();//��С
    void LoadProjectHelp();//���ذ����ĵ�
private slots://edit by zqh
    void Reverse_selection();//����ѡ��
    void OnGroupItem();    //��ϲ���
    void OnDisGroupItem(); //ȡ�����
    void OnDeleteItem();   //ɾ��ͼ��
    void OnLockItem();     //��������
    void OnUnLockItem();   //��������
    void OnSetLeft();  //ͼ�������
    void OnSetRight(); //�Ҷ���
    void OnSetTop();   //�϶���
    void OnSetButtom();//�¶���
    void OnSetHCenter(); //ˮƽ���ж���
    void OnSetVCenter(); //��ֱ���ж���
    void OnSetHSpacingAlign();//ˮƽ�ȼ�����
    void OnSetVSpacingAlign();//��ֱ�ȼ��
    void onWidthSame();       //���õȿ�
    void onHeightSame();      //���õȸ�
    void onWidthHeightSame(); //���õȿ�ȸ�
    void onFrmLanguageChange(int nLanIndex);
    void OnAddNewScreen();      //�½�����
    void OnSetTheFrontScreen(); //��һ������
    void OnSetTheNextScreen();  //��һ������
    void listChange(int);//��������б�ĸı�����ʾ��Ӧ���б�
    void closeProject();//�رչ���
    void showNumDlg_ScreenAndWindow(QString,QTreeWidgetItem *);
    //void OnSetONState(); //����ΪON״̬
    //void OnSetOFFState();//����ΪOFF״̬
    void onFrmStatecmbChange(int nIndex);//������״̬��Ͽ����ı�
    void onScreenChange(int nStr);//
    void OnSetSceneGrid();//����
    void OnSetDagViewModel();//������ͼģʽ
    void OnSetDagViewModelArrow();//����Ǽ�ͷ
    void OnOpenPropertyDlg(); //�����ԶԻ���
    void OnFindAddressDlg();  //��ַ���ҶԻ���
    void OnDisplayAddrUseDlg();//�򿪵�ַʹ��һ����Ի���
    bool StartCompileThread();
    void USB_DownLoad(); //USB����
    void MsgOutputListDoubleClicked(int nRow,int nClomn);//˫����Ϣ�������
    void OnCreateAnimaDlg();
    void OnSetHMirror(); //ˮƽ����
    void OnSetVMirror(); //��ֱ����
    void OnCutItem(); //����
    void ExecuteOffLineMonitor(); //����ģ��
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
    QAction *undoAction;  /*��������*/
    QAction *redoAction;  /*����������*/
    QAction *deleteAction;/*ɾ������*/
    QUndoView *undoView;
    QMenu *editMenu;
    void createUndoView();
    //list_style
    QTabWidget*  dockTabWidget;
    QWidget*     subWidget1;//ϵͳ����
    QWidget*     subWidget2;//����
    QFrame*      widget;
    QVBoxLayout* dock_layout;
    QVBoxLayout* dock_layout1;
    QVBoxLayout* dock_layout2;
    //QComboBox* list_style;
    QStackedWidget  *stackeWidget;
    QTimer   *Ptimer;//Ԥ�����ڵĶ�ʱ��

public:    
    QGraphicsItem *pOldItem;
    void setActiveScreenIndex(QGraphicsScene *pScene);
    bool review_ScreenAndWindow_Name(QString);
    void OnCreateAnimation(); //����
    void AndTreeSubItem(QGraphicsItem * newItem);//�ڻ�����ߴ��ڵ����ؼ��������
    void ToSlectTreeItem(QStringList sList);// ���������ϵ�Item����Ӧѡ�����οؼ�����
    AddrMsg* pAddrMsg;  //�洢��ַ��Ϣ��ָ��

    QVector<TEXTPRO> vTextMsg;//�洢�������ı���Ϣ���������滻ʹ��

    QVector <AddrMsg*>vAddrMsg;//�洢��ַ��Ϣ�ද̬����
    MsgOutPut* pMsgOutPut;//��Ϣ�������˫��Ҫ�������

    QMap<int, MsgOutPut*>mapMsgOutPutItem;


    QGraphicsItem *pDrawToSceneItem;   //������ȷ����ؼ�Item
    //QVector <InitMaroClass *>vInitMaro;//�����ʼ���궯̬����
    //QVector <GlobalMaroClass *>vGlobalMaro;//����ȫ�ֺ�궯̬����
    void PasteItemToScene();//ճ��ITEM������
    void deleteItem_upDateTreeContrl(QList<QGraphicsItem *> list);//ɾ��������ITemʱ�������οؼ�
     QString ControlNO(QString sName);  //��ÿؼ��ı��(����ϵ�ʱ���������GetControlNO������)
    bool eventFilter ( QObject * watched, QEvent * event )  ;
    void OnAddColorDlg(QPushButton *pbtn,ColorPickerPopup *colorPicker);  //ÿ���ؼ������ɫ�Ի���
    QGraphicsItem * PasteItemToScence();//��ճ��Item��������ʱ��
    void deleteItem_undefineGroup(QGraphicsItem *);//ɾ���Զ���Ŀؼ�ͬʱ�������οؼ�
    QGraphicsItem * IsHaveLibraryItem(QGraphicsItem *pItem); //�ж��Ƿ���ͼ��item
    QGraphicsItem * OpenLibraryFile(QString str);
    QGraphicsItem * onGetItemFromFile(QString sPath);
    QList<QGraphicsItem *> SaveItemToLibList; //����item��ͼ���е�item

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
    QVector <SamDrawScene *> vBaseLibraryScene;  //�滭�������
    void loadBaseLibAndUserDefineLib(); //���ػ���ͼ����û��Զ���ͼ��
    void ResetPic(QGraphicsItem *pItem);
    void ResetItem(PicPosInfo posinfo,QGraphicsItem *pItem);
    bool FocusInStatusbar();
    QGraphicsItem * ReloadPic(QGraphicsItem *pItem,SamDrawScene *scene,int flag = 0);//����̬��ʱ����������ͼƬ
    QGraphicsItem * ReloadItem(QGraphicsItem *pItem,bool btransparent,QString sColor,
                                           PicPosInfo posinfo,QString sPath);
    void SavePicToFile(QStringList pathList,QDataStream &stream);
    void LoadPicFromFile(QDataStream &stream);
    int IsCheckAddressRight(Keyboard &keyboard,QString WaringMsg,QLineEdit *pLineEdit,int Addr_Type,QString sAddr);
    void loadHelpHtm(int nKey); //���ذ����ĵ�
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
            stProtocol cModel,std::vector<addrTargetProp>addrs);//����ӵ�����,����Ҫ����
    void loadSysLibs();//����ű���

    void fillTreeTextMsg();
    void replaceTreeTextMsg(QString sOldMsg,QString sNewMsg);
public:
	QMultiMap<QString ,addrTargetProp> addrsInScene;//�������õ������е�ַ
	QMultiMap<QString ,addrTargetProp> addrsInSysPrarm;//ϵͳ�������õ������е�ַ
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
    //���ù������еİ�ť����Ч��
    void setToolBoxFloat();
    void setDynamicImage(QPushButton *button);
	QMap<QString,QString> m_fontMap;
	QMap<QString,QString> sysFontMap;
	int m_ProVersionNum;//����̬�İ汾��
    QMap<QString, QString>m_factoryMap;

    //add by wxy
    QVector <VarPro> g_Vars; //ȫ�ֱ�����

    //���������� 13-10-17
    QTreeWidgetItem *tree_varRcd;

    void setWindowFirst();
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
public:
    QString findFactoryFullName(QString str);
    void savePicPath(QItemGroup *pItemGroup,QMap<QString, QString> &mPath);
    void loadPicPath(QItemGroup *pItemGroup,QMap<QString, QString> &mPath);

    QVector <VarPro> getGlobalVars();   //��ȡȫ�ֱ���
    bool appendGlobalVar(VarPro variant);      //����һ������
    void setGlobalVar(QVector <VarPro> variants);

    void updateChScreen();   //wxy ������Ļ�����������
    void savePlcPrj(QDataStream &stream);
    void loadPlcPrj(QString filename,QDataStream &stream);
    bool compilePlcPrj();

    SimulatorDlg *pSimDlg;
    QTabWidget*  ToolBarTabWidget;
    QScrollArea* scrollAreaBasic; //����ͼ��
    QScrollArea* scrollAreaCtl;   //�ؼ�

    //wxy����MD5���ɡ����麯�������ڱ����������Դ�ļ��
    bool checkMD5(QByteArray md5, QString filePath);
    QByteArray getFileMd5(QString filePath);

    QMap<QString, QByteArray> mPicMd5;//wxyͼƬ·����Ӧ��MD5��
    QMap<QString, int>m_ChScreenMap;//wxy��Ļ�������б��뻭��洢˳��ӳ��
    QVector<DBQuery > vAllDbQuery;
    void inSertDbQuery(QString tableName,QMap<QString,QVariant> mapDbquery);
    QList<int >m_Ids;
    int getNewId();
    bool insertId(int nId);

};



#endif // MAINWINDOW_H
