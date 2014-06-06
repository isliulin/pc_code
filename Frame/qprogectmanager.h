/**************************************************************
 *                        SAMKOON TECHNOLOGY CORP.
 *                          COPYRIGHT (C) 2011
 *
 * Description: QSamSysParame class implementation.for samkoon system parame
 *
 * Functions: None.
 *
 * Modification Log:
 * Date             Name             Description Of Change
 * 2011-6-29        Tang             Creation.
 *************************************************************/

#ifndef QPROGECTMANAGER_H
#define QPROGECTMANAGER_H
#include <QColor>
#include <QDate>
#include <QVector>
#include <QGraphicsItem>
//#include "view/samdrawscene.h"
#include <QSqlDatabase>
#include "structHead.h"

/*enum _ARRAY_ORDER
{
    LEFT_TO_RIGHT       = 0x01, //从左到右
    UP_TO_DOWN,                 //从上到下
    RIGHT_TO_LEFT,              //从右到左
    DOWN_TO_UP,                 //从下到上
    CLOCK_WISE,                 //顺时针
    COUNTER_CLOCK_WISE,         //逆时针
    NOT_MOVE ,                  //不移动
    OTHER_MOVE_DERECT
}ARRAY_ORDER_A;*/

enum MSG_TYPE
{
    MSG_NORMAL = 0,     //正常
    MSG_WARNING,        //警告
    MSG_ERROR           //错误
};

enum DATA_TYPE
{
    BIT_1            = 0x01,        // 位
    POSITIVE_INT_16 ,//= 0x02,         // 16位整数
    POSITIVE_INT_32 ,//= 0x03,         // 32位整数
    INT_16 ,         //= 0x04,         // 16位正整数
    INT_32 ,         //= 0x05,         // 32位正整数
    BCD_16,          // = 0x06,        // 16位BCD码
    BCD_32,          // = 0x07,        // 32位BCD码
    FLOAT_32 ,       // = 0x08,        // 32位浮点数
    ASCII_STRING ,   //= 0x09,         // ASCII码
    OTHER_DATA_TYPE  = 0x0a,
    UNICODE_STRING   = 0x0F,           // unicode字符串
};

typedef enum _TIME_FORMAT
{
    HHMM_COLON      = 0x01,     //HH:MM
    HHMMSS_COLON,               //HH:MM:SS
    HHMM_ACROSS,                //HH-MM
    HHMMSS_ACROSS,              //HH-MM-SS
    TIME_TYPE_COUNT,
}TIME_FORMAT;

typedef enum _DATE_FORMAT
{
    YYYYMMDD_SLASH  = 0x01,	//YYYY/MM/DD
    YYYYMMDD_POINT,		//YYYY.MM.DD
    YYYYMMDD_ACROSS,		//YYYY-MM-DD
    MMDDYYYY_SLASH,		//MM/DD/YYYY
    MMDDYYYY_POINT,		//MM.DD.YYYY
    MMDDYYYY_ACROSS,		//MM-DD-YYYY
    DDMMYYYY_SLASH,		//DD/MM/YYYY
    DDMMYYYY_POINT,		//DD.MM.YYYY
    DDMMYYYY_ACROSS,		//DD-MM-YYYY
    DATE_TYPE_COUNT,
}DATE_FORMAT;

typedef enum objType
{
        OBJ_ITEM = 1,//item类型
	OBJ_HISTORYDATA,//历史数据
	OBJ_ALARM,// 报警
	OBJ_MACRO,//宏
	OBJ_RECIPE,//配方
	OBJ_SYSPRARM,//系统参数
    OBJ_REALTIME_DATA,//实时数据采集
	OBJ_OTHER//其他
}E_OBJ_TYPE;

/*串口信息列表*/
typedef struct serialPort{
    int BAUD_RATE ;                // 波特率
    int PARITY_TYPE ;              // 1:NONE(无), 2:EVEN(偶校验), 3:ODD(奇校验)
    int DATA_BIT ;                 // 数据位
    int STOP_BIT ;                 // 停止位
}SERIAL_PORT_PROP;

typedef enum PORT_TYPE
{
    PORT_SERIAL = 1,
    PORT_ETHNET,
    PORT_SERIAL_ETHNET,
//    PORT_CAN,
//    PORT_ZIGBEE,
//    PORT_OTHER
}E_PORT_TYPE;

typedef enum _protocol_type
{
    PRO_SERIAL = 1,
    PRO_ETHNET,
    PRO_CAN
}PROTOCOL_TYPE;

typedef struct _PlcModel{
	QString sModelName;  //协议的名称
	QStringList regs;  //地址
        QStringList sBitregs;//位地址
        QStringList sWorldregs;//字地址
        QStringList sDworldregs;//双字地址
	//默认值
	int	nPlcNo;	//Plc站号
	int	nReceiveTimeout;	//接收超时（ms）
	int	nMaxRWLen;	//最大读写长度
	int	nRetryTime;	//重试次数
    int	nIntervalTime;//帧间隔时间
    int nCycleTime;//最小通信周期
    SERIAL_PORT_PROP mPort;//串口信息
    E_PORT_TYPE ePorttype;//该协议支持的接口类型

}PLC_MODEL;

typedef struct _factory{
	QString sFactoryName;  //厂家名称
	QVector<PLC_MODEL> models;//所支持的该厂家PLC
}PLC_FACTORY;

//协议属性
typedef struct _stProtocol
{
    QString	sName;	//用户设定的名称 用户可以重命名
    QString sFactoryName; //协议所属的厂家名称 不可变，从文件取得
    QString sProtocolName;//协议名称。不可变，从文件取得
    int	nPlcNo;	//Plc站号
    int	nReceiveTimeout;	//接收超时（ms）
    int	nMaxRWLen;	//最大读写长度
    int	nRetryTime;	//重试次数
    int	nIntervalTime;//帧间隔时间
    int nCycleTime;//最小通信周期
    PLC_MODEL mPlc;  //从文件取得的PLC属性
    QString ip;
    int port;
    bool bIsTcpProtocol;//是否TCP协议
}stProtocol;

//连接属性
typedef struct _connect
{
	int	id; //连接编号
	QString sConnectName;//连接名称
	int	eConnectPort;//连接端口
	bool bUseRelationPort;//是否转发
	int	eRelationPort;//转发到的端口
        int     bMasterScreen;	   //为1：表示是主屏，为0：表示是从屏
        int     bConnectScreenPort;//1：连接从屏口   0：连接PLC口
        int     nSlaveScreenNum;   //穿透从屏的数量1-20
	int	nScreenNo;//本机编号，供屏做从站时使用
	int	nBaudRate;//波特率
	int	nDataBits;//数据位数
	int	nCheckType;//校验类型0:NONE, 1:EVEN, 2:ODD
	int	nStopBit;//停止位
	QString sIpAddr;//IP地址
	int	nNetPortNum;//网络端口号

	QVector<stProtocol> vProtocols;//协议
}stConnect;

typedef struct _stAddrCompileParaments
{
    E_OBJ_TYPE eType;//地址类型
    int itemId;//所属item的id 或者所在组的序号
    int addrNum;//该地址在组中的序号
    int id;//分配给地址表的id
    READ_WRITE_COM_TYPE eRWtype; //读写属性
}ADDR_PARAMENTS;

typedef struct  MemberFun
{
    QString funName;
    QString importCode;
    QString daemon;
    QString demoEn;
}stMemberFun;

typedef struct  ScriptLib
{
    QString LibName;
    QVector <stMemberFun> functions;
}stScriptLib;


class Keyboard
{
public:
    Keyboard();
    Keyboard& operator=(const Keyboard &souceObj);
    Keyboard& operator =(const int n);
    void compile(QSqlDatabase &db,ADDR_PARAMENTS paraments);
    int getAddrValue(stProtocol model,int &index);
	bool getCurrentModel(stProtocol &cModel,stConnect &cConnect);
	QVector <ADDR_CHECK_SOURCE_PROP> getMultiAddrs(int nInterval,int count);
	void refreshShowAddr();
    QVector <Keyboard> copyAddrs(int nIntervl,int count);

    quint8  nConnectType;         //连接型号如内部存储区、com1等
    quint8  nPlcRegTypeIndex;     //PLC寄存器X、Y、T、C等的索引
    quint8  nPlcStationIndex;     //PLC站号
    quint8  nAddrType;            //地址类型 0: bit, 1:word
    QString sShowAddr;            //地址输入字符串如“X123”
    QString sPlcAddrValue;        //plc寄存器地址值如“123”等
    QString sPlcRegTypeStr;       //plc寄存器“X”、“Y”等
    QString sPlcName;             //地址使用的协议名称
    int     Length;               //连续地址的长度

    friend QDataStream &operator<<(QDataStream &stream, Keyboard &keyBoard);
    friend QDataStream &operator>>(QDataStream &stream, Keyboard &keyBoard);
};

typedef struct __ADDRPRO__{
    Keyboard* pAddr;
    QString   str;
    short     type;//地址类型，位地址为0，字地址为1
    short     nRecipe;//配方号，用于连续的配方地址，0为不是配方，大于0为配方号
}ADDRPRO;

typedef struct __TEXTPRO__{
    QString sCtrlName; //控件名称
    QVector <int>iLanguage;//多语言

    QVector<int>vStatus;//值为状态值
    QVector<QString> vMsg;
    QVector<QString>vText;//值为文本内容
  //  QMap<int,QString>mText;//第一个值为状态值，第二个值为文本内容
}TEXTPRO;

typedef enum addrCheckErrorInfo{
	ADDR_CORRECT = 0x01,               //地址正确
	IS_BIT_ADDR = 0x02,                //是位地址
	IS_WORD_ADDR = 0x03,               //是字地址
	ADDR_FORMAT_ERROR = 0x04,          //地址格式错误，主要是没有按照寄存器的格式来，参照寄存器的名称
	ADDR_OUT_BOUND = 0x05,             //地址越界
	ILLEGAL_REG = 0x06,                //非法寄存器名字
	ILLEGAL_VALUE = 0x07,              //非法地址值，主要指值转换成int不正确
	ADDR_STRING_NULL = 0x08,			//地址为空
	INVALID_CONNECT = 0x09,				//无连接
	ADDR_OTHER_ERROR                   //未知错误
}ADDR_CHECK_ERROR_INFO;
enum eSwitchType
{
    BIT_SWITCH,      //位开关
    WORD_SWITCH,     //字开关
    SCENE_SWITCH,    //画面开关
    PECULIAR_SWITCH,  //特殊开关
	INDICATOR_SWITCH  //指示灯

};
typedef enum eSwitchType SWITCH_TYPE;

enum eMonitorType
{
    NONE,     //不监视
    BIT_MONITOR,   //双态
    POLY      //多态
};
typedef enum eMonitorType MONITOR_TYPE;

enum eBitOperType
{
    SET_BIT, //置位
    RESET,   //复位
    JOG,     //点动
    REPLACE, //交替
};
typedef enum eBitOperType BIT_OPER_TYPE;

enum eWordOperType
{
    INPUT_VALUE,  //输入数值
    ADD,          //加
    MINUS,        //减
    ADD_LOOPER,   //连续加
    MINUS_LOOPER, //连续减
};
typedef enum eWordOperType WORD_OPER_TYPE;



enum eSceneType
{
    OPEN,       //打开画面
    BACK,       //打开前一画面
    CLOSE,       //关闭窗口
    CLOSE_OPEN,       //关闭当前窗口并打开画面
    RETURN,           //返回前一画面
};
typedef enum eSceneType SCENE_OPER_TYPE;


enum ePeculiarType
{
    BACKLIGHT,       //背景灯开关
    RESET_HMI,           //系统重启
    SET_SCENE_TIME,  //设置屏保时间
    SET_SYSTEM_TIME, //设置系统时间
    CHANGE_USER,     //切换当前用户
    USER_MANAGE,     //用户管理
    TOUCH_SOUND,     //触摸声音开关
    COPYRIGHT,       //产品授权
    CHANGE_LANGUAGE, //语言切换
    SCREENSHOT,      //屏幕截图
    OPER_WINDOW,     //窗口操作
    FORMULA,         //采样数据操作
    SAMPLING,        //配方操作
    ALARM ,           //报警操作
    EDIT_PASSWORD , //修改当前密码
    CLOSE_HMI ,      //关机
};
typedef enum ePeculiarType PECULIAR_TYPE;

//开关部分属性类型
struct bitSwitchPro
{
    Keyboard addr;//位地址
    BIT_OPER_TYPE operType;//操作类型
    bool  bDown;//执行方式
	bool  bConfirm;//是否需要操作者确认
	int   nTimeout;// 最长等待时间
};
struct wordSwitchPro
{
    Keyboard addr;//字地址
    WORD_OPER_TYPE operType;//操作类型
    DATA_TYPE dataType;//数据类型
    double value;//常数
	bool bCycle;//绕回
	double nMax;//最大值
	double nMin;//最小值
    bool bDynamicControl; //wxy 常量数值动态控制
    Keyboard addrConst; //常量数值地址
};
struct sceneSwitchPro
{
    SCENE_OPER_TYPE operType;//操作类型
    int     nSlideStyle;     //---切换效果
    QString sceneName;//画面名称
    bool bLogout;// 切换画面是否注销
};
struct functionSwitchPro
{
    PECULIAR_TYPE operType;//操作类型
    int functionIndex;//具体功能
    QString windowName;//窗口名称
    bool IsCheckX;//是否选择X轴放大缩小
    bool IsCheckY;//是否选择Y轴放大缩小
};
struct monitorPro
{
    MONITOR_TYPE monitorType;//监视类型
    bool bBitAddr; //地址类型，是否是位地址
    int bitIndex; //字的位号
    bool bSameAddr; //监视地址是否和操作地址相同
    Keyboard addr;  //监视地址
    DATA_TYPE dataType;//数据类型
    int count;     //总状态数
    int valueType; //状态切换条件
    QVector <double > values;//自定义状态值

};

//权限页面属性
struct securityPro
{
    bool enableTouch;//启用触控权限
    bool enableVisable;//启用显现权限

    bool byGroups_T;//触控权限 1-受用户组控制 0-受位控制
    bool byGroups_V;//显现权限 1-受用户组控制 0-受位控制

    QStringList groups_T;//触控受用户组控制 具有控制权限的组
    QStringList groups_V;//显现受用户组控制 具有控制权限的组

    int addrType_T;//触控受位控制 地址类型 0-位地址 1-字地址
    int addrType_V;//显现受位控制 地址类型

    int bitIndex_T;//触控受位控制 字地址的位
    int bitIndex_V;//显现受位控制 字地址的位

    int condition_T;//触控权限 解锁条件
    int condition_V;//显现权限 解锁条件

    Keyboard address_T;//触控权限 控制地址
    Keyboard address_V;//显现权限 控制地址

    bool bNotice;//操作是否通知
    Keyboard addrNotice; //通知地址
    int datatype;//如果选择字地址的话，数据类型
    //int noticeAddrType; //通知值的地址类型
    double noticeValue;//通知值

    bool bDelay;//是否延时触控
    int time;//按压时间
};

typedef struct userLevelProp{
    bool bSelect;       //是否选择这用户
    QString sUserName;  //用户的名称
    QString sUserPWD;   //用户的秘密
    bool bUserLevelList[8];  //用户等级
}USER_LEVEL_PROP;

typedef struct HMIPrinterProp{
    bool   bUsePrinter;     //是否开启打印
    bool   bPrintNo;        //是否打印序号
    bool   bPrintTime;      //是否打印时间
    bool   bPrintTimeEx;    //是否打印扩展时间
    bool   bPrintStandTime; //是否打印标准时间
    bool   bPrintPricesTime;//是否打印精确时间
    bool   bPrintDate;      //是否打印日期
    bool   bPrintDateEx;    //是否打印扩展日期
    bool   bPrintCheckError; //是否打印窗口错误
    bool   bPrintCharModel;  //是否字符模式打印
    quint8 nPrinterType;    //打印机型号
    quint8 nDataBit;        //数据位
    quint8 nStopBit;        //停止位
    quint8 nCheckOe;        //奇偶校验
    int    nPrintPort;      //打印机端口
    int    nPrintBaud;      //波特率
    QStringList sBackupForNewVer;    //为以后的业务留的备份数据
}HMI_PRINTER_PROP;

typedef struct projectProp{
    quint8 nDisplayMode;                   //0:代表水平排列，1：代表垂直排列
    quint8 nStartScreenIndex;              //启动画面ID  上位用
    quint8 nScreensaverTimer;              //屏保时间，从0分钟到60分钟
    quint8 nFlickerFqc;                    //控件闪烁频率
    bool   bHaveAlarmVoice;                //是否有报警声音
    bool   bHaveTouchVoice;                //是否有触摸声音
    bool   bScreensaver;                   //是否屏保
    bool   bLoadInitScene;                 //是否加载初始化页面
    quint8 nScreensaverIndex;              //屏保画面
    quint8 nLoadSceneIndex;                //初始化页面的ID号
    quint8 nLoadSceneTime;                 //载入画面的时间 1s - 10s
    quint8 nDefautUserId;                  //默认用户的ID号
    quint8 nSetFloatProp;                  //设置浮点数 0:是标准，1:是自定义
    quint8 nSetFloatType;                  //浮点数的类型，0：是低字在前，1是高字在前
    quint8 nNoDataValueFlag;               //通信失败时数值物件的标志
    quint8 nNoDataCharFlag;                //通信失败时字符物件的标志
    quint8 nPicFilePathIndex;              //触控无效时是否显示自定义图片的ID号
    bool   bHideMouse;                     //是否隐藏鼠标光标
    bool   bTouchInvalidPic;               //触控无效时是否显示自定义图片
    bool   bTIPicTransparent;              //触控无效时自定义图片是否需要透明
    bool   bUseHighLevelPWD;               //是否使用最高权限密码
    bool   bNeedUpLoad;                    //最高权限密码是否支持上载组态
    bool   bAccessOperate;                 //是否需要权限操作
    bool   bNeedUploadCom;                 //是否需要上载组态
    bool   bUploadComNeedPWD;              //上载组态时是否需要密码
    bool   bAlarmCoruscate;                //报警产生时是否闪烁画面
    //add by Dylan 2011-10-18
    bool   bClearHisAlarm;                 //是否清除历史报警记录
    bool   bStratScreen;                   //是否下载完成后启动画面
    bool   bClearHisData;                  //是否清除历史数据
    bool   bDownLoadRecipe;                //是否下载配方
    //add by Dylan 2011.11.4
    quint8 nHisdataSave;                   //历史数据存储位置
    quint8 nHisAlarmSave;                  //历史报警存储位置
    quint8 nScreenPictureSave;             //屏幕截图存储位置
    //add by Dylan 2011.11.7
    quint8 nDownLoadPicCheck;              //是否转换图片格式
    int nSceneWidth;                       //屏幕的宽度
    int nSceneHeight;                      //屏幕的高度
    int nDownLoadType;                     //下载方式 0-USB 1-以太网口
    //add by Dylan 2011.11.4
    QString sHisdataPath;                  //历史数据存放地址
    QString sHisAlarmPath;                 //历史报警存放地址
    QString sScreenPicturePath;            //屏幕截图存放地址

    QString sPjtFilePath;                  //工程的路径
    QString sPjtModel;                     //工程的型号
    QString sHighLevelPWD;                 //最高权限操作的密码
    QString sUploadComPWD;                 //上载组态时的密码
    QString sDowndloadIP;                  //ip地址 类似于 “192.168.1.10”
    QString sPortNO;                       //端口号如：“8000”
    QStringList sTIPicPathList;            //触控无效时自定义图片的路径列表
    QColor  mTIPicColor;                   //触控无效时自定义图片的透明色
    QColor cAlarmBackColor;                //报警产生时闪烁画面背景色
    USER_LEVEL_PROP mUserLevelList[8];     //8个用户的属性
    HMI_PRINTER_PROP mPrinterProp;         //打印机相关的属性
    QStringList sBackupForNewVer;    //为以后的业务留的备份数据
    //at(0)---"0"表示默认采用触摸屏操作，“1”标示采用鼠标操作 add by Dylan 2011-12-12
    //at(1)---系统报警条颜色 add by Dylan 2011-12-19
    //at(2)---系统报警文本颜色 add by Dylan 2011-12-19
    //at(3)---系统报警字体 add by Dylan 2011-12-19
    //at(4)---系统报警字体大小add by Dylan 2011-12-19
    //at(5)---系统报警显示方式 0-始终显示 1-周期显示 add by Dylan 2011-12-19
    //at(6)---系统报警条出现位置 0-顶端  1-底部 add by Dylan 2011-12-19
    //at(7)---是否使用系统报警 add by Dylan 2011-12-19
}PROJECT_PROP;
//+++++
//代替上面的结构体的,整个系统的变量
typedef enum _ScrDirctionType{  //屏幕方向
    scrHorizontal = 1,          //水平
    scrVertical,                //垂直
}ScrDirType;

//改成bool类型,去掉这个定义
/*typedef enum _StandbyMode{      //待机模式
    modeScreen = 1,             //画面待机
    modeLight,                  //亮度变化待机
}StandbyMode;*/

typedef enum _LightMode{        //亮度设置模式
    LightNull = 1,              //没有亮度
    LightMin,                   //最小亮度
    //LightHalfCur,               //当前亮度的一半
}LightMode;

typedef enum _DownloadMode{     //下载模式
    UsbDownload = 1,            //Usb下载
    NetDownload,                //网络下载
}DownloadMode;

typedef enum _PicSaveMode{      //图片保存格式
    SavePicJPEG = 1,            //JPEG
    SavePicBMP,                 //BMP
}PicSaveMode;

typedef enum _AuthorizeMode{    //授权方式
    AuthForever = 1,            //永久授权
    AuthTime,                   //时间授权
}AuthorizeMode;

typedef enum _AuthTimeSet{      //时效授权设置
    AUseTime = 1,               //按使用时间计算时
    ATimeOut,                   //按截止日期计算
}AuthTimeSet;

typedef enum _PrinterType{      //支持的打印机型号
    Type_1 = 1,                 //1   WH-E19(炜煌)
    Type_2,                     //2   WH-A5(炜煌)
}PrinterType;

typedef enum _HMIPosType{       //HMI位置
    HMIHost = 1,                //本机
    HMIRemote,                  //远端
}HMIPosType;

typedef enum _LinkPortType{     //连接接口类型
    LinkCom1 = 1,               //Com1
    LinkCom2,                   //Com2
    LinkEthernet,               //以太网
}LinkPortType;

typedef enum _LinkType{         //连接类型
    LinkTSerial = 1,            //串口
    LinkTEthernet,              //以太网
}LinkType;

typedef struct __UserPermiss__
{
    QString m_strName;          //用户的名称
    QString m_strDescrip;       //用户的描述
    QString m_strPassword;      //用户密码
}UserPermiss;

typedef struct __Administrator__
{
    QString m_strUser;
    bool    m_bIsAdmin;
}Admin;

typedef struct __GroupPermiss__
{
    QString m_strName;          //组的名称
    QString m_strDescrip;       //组的描述
    bool    m_bNeedAdmin;       //是否需要管理员
    QVector<Admin> m_vecMember;  //该组的用户的成员
}GroupPermiss;

typedef struct __BitSenceItem__{
    bool     bReset;             //自动复位
    quint8   nCtlStatus;         //控制画面切换的状态
    QString  sCtlSceneId;        //要更改的画面名字
    Keyboard mCtlSceneAddr;      //控制更改画面的地址
    bool     bClose;             //wxy自动关闭，仅窗口有效
}BitSenceItem;

typedef struct __GlobalVariable__
{
    //--------机型选择
    QString         m_strModelName;     //机型名称
    ScrDirType      m_eScreenDir;       //屏幕方向
    QString         m_strModelSize;     //屏幕尺寸
    QString         m_strResolution;    //分辨率
    QString         m_strColor;         //色彩
    QString         m_strUsermemory;    //用户内存
    QString         m_strNandFlash;     //存储空间容量
    QString         m_strPowersupply;   //供电电源
    QString         m_strCom1;          //com口个数
    QString         m_strCom2;          //CAN总线
    QString         m_strUsb;           //USB
    QString         m_strMaxscreennumber;//以太网
    int             m_nScreenWidth;     //分辨率宽
    int             m_nScreenHeight;    //分辨率高
    //int             model;              //水平垂直模式
    //其他（USB，COM，网络信息）待定
    QString         m_strHmiName;       //HMI别名

    //--------显示设置---------------------------------------
    bool            m_bUseLogo;         //是否使用启动Logo画面     
    QString         m_sLogoNum;         //设置启动Logo画面号
    QString         m_strLogoNum;       //Logo画面号对应图形的路径
    bool            m_bStandby;         //是否启用待机模式
    bool            m_bStandbyMode;     //待机方式
    QString         m_sStandbyNum;      //当前待机画面号
    QString         m_strStandbyNum;    //待机画面号对应图形的路径
    LightMode       m_eStandbyLight;    //待机亮度
    int             m_nScreenTime;      //待机保护时间(秒)
    bool            m_bStandbyLogin;    //待机注销登录
    QString         m_sInitNum;         //初始画面设置（画面号）
    int             m_nRecipeIndex;     //当前配方组
    int             m_nRecipeNum;       //当前配方号
    int             m_nFlickRate;       //闪烁频率
    bool            m_bLockIcon;        //是否需要锁图标

    //--------操作设置---------------------------------------
    bool            m_bTouchVoice;      //是否开启触摸声音
    bool            m_autoLogin;        //是否启用网络监控
    bool            m_bMultiVisitor;    //是否允许多人访问远程监控
    QString         m_strMonitor;       //监控密码
    int             m_nMonitorPort;     //远程监控端口

    //--------数据控制---------------------------------------
    bool            m_bCurScreenNum;        //是否当前画面编号
    bool            m_bCurFormulaNum;       //是否当前配方编号
    bool            m_bCurLanguageNum;      //是否当前语言编号
    bool            m_bWordAddrScreenNum;   //是否字地址控制画面切换编号
    Keyboard        m_keyCurScreen;         //当前画面地址编号
    Keyboard        m_keyCurFormula;        //当前配方地址编号
    Keyboard        m_keyCurLanguage;       //当前语言地址编号
    Keyboard        m_keyWordAddrScreen;    //字地址控制画面切换编号
    bool            m_bBitSenceExch;        //位地址控制画面切换
    QVector<BitSenceItem> m_vecBitSence;    //位地址控制画面切换结构体

    //--------用户权限
    QVector<UserPermiss>    m_vecUser;      //用户信息
    QVector<GroupPermiss>   m_vecGroup;     //组信息

    //--------打印机---------------------------------------
    PrinterType     m_ePrinter;             //打印机支持型号

    //--------上下载设置-----------------------------------
    DownloadMode    m_eDownload;            //下载方式
    short           m_nIp1;                 //IP地址
    short           m_nIp2;                 //
    short           m_nIp3;                 //
    short           m_nIp4;                 //
    int             m_nPort;                //端口号
    PicSaveMode     m_ePicMode;             //图片保存格式
    bool            m_bStartHMI;            //下载后启动HMI
    bool            m_bClearData;           //下载时清除历史数据
    bool            m_bClearAlarm;          //下载时清除历史报警数据
    bool            m_bWriteFormula;        //下载时写入配方
    bool            m_bUpLoad;              //是否允许上载
    bool            m_bUploadPassword;      //上载需要密码
    QString         m_strUploadPassword;    //上载密码

    //--------访问加密---------------------------------
    bool            m_bEncryAccess;         //是否启用访问加密
    QString         m_strAccessPassword;    //访问密码

    //--------产品授权---------------------------------
    AuthorizeMode   m_eAuthMode;            //产品授权方式
    AuthTimeSet     m_eTimeStyle;           //授权时间方式
    QString         m_strTimeout;
    //ProRightDay     m_vecDayRight[5];       //时间授权
    //ProRightDate    m_vecDateRight[5];       //日期授权
    /*typedef struct __ProRightDay__
    {
        bool      m_bIsUse;          //是否启用
        QString   m_strTimeout;      //超时提醒字符串
        int       m_nUseDay;         //使用天数
        QString   m_sUseDayPassword; //使用天数密码
    }ProRightDay;
    typedef struct __ProRightDate__
    {
        bool      m_bIsUse;          //是否启用
        QString   m_strTimeout;      //超时提醒字符串
        QDateTime m_gDateTime;       //日期时间数组
        QString   m_strDate;         //日期时间数组密码
    }ProRightDate;*/
    bool      m_bIsUseDay[5];       //是否启用
    QString   m_strTimeoutDay[5];   //超时提醒字符串
    int       m_nUseDay[5];         //使用天数
    QString   m_sUseDayPassword[5]; //使用天数密码
    /////////////////////////////////////////////
    bool      m_bIsUseDate[5];      //是否启用
    QString   m_strTimeoutDate[5];  //超时提醒字符串
    QDateTime m_gDateTime[5];       //日期时间数组
    QString   m_strDate[5];         //日期时间数组密码

    //-------------------语言设置--------------------
    short            m_nLanNum;             //语言总数
    short            m_nCurLan;             //当前语言号
    QVector<QString> m_vecLanguageNameList; //语言名称列表

}GlobalVariable;
////////////////////end//////////////////////

typedef struct plcCommunicateProp{
    quint8  nHmiLocation;     //HMI位置 0-本机 1-远端
    quint8  nConnectNum;      //连接编号 com1 or com2
    quint8  nConnectType;     //连接类型 0:串口，1：以太网口
    quint8  nConnectPort;     //连接接口-通过该变量标示连接类型 0：com1   1：com2   2：以太网
    quint8  nPlcAddrInterval; //plc连续地址间隔
    quint8  nDataBits;        //数据位数
    quint8  nCheckType;       //校验方式 0:NONE, 1:EVEN, 2:ODD
    quint8  nStopBit;         //停止位 1-2
    quint8  nRetryTime;       //重试次数
    quint8  nAddrType;        //地址模式 0：标准模式，1：扩展模式
    quint8  nFwConnectType;    //穿透应用中的连接方式 0为直连串口 1为以太网 其他备用
    quint8  nFwFromStationId;  //穿透应用中的从站ID
    quint16 nTouchScreenAddr; //触摸屏地址 0-255
    quint16 nPlcAddr;         //plc地址 0-255
    quint16 nCommunicateTime; //通信时间 0-1024
    quint16 nTimeout1; //超时时间1 200-65535
    quint16 nTimeout2; //超时时间2 1-1024
    int     nBandRade;        //波特率
    QString sConnectName;     //连接名称
    QString sDiviceType;      //属于哪个厂家的设备
    QString sDiviceModel;     //设备型号
    QString sInternetIpAddr;   //选择用以太网连接时候的IP地址
    QString sInternetPort;     //选择用以太网连接时候的端口号
    QString sFwIpAddr;         //穿透应用中用以太网连接时候的IP地址
    QString sFwPort;           //穿透应用中用以太网连接时候的端口号
    QStringList sDataBakeup;//备用参数4个
    QStringList sBackupForNewVer;    //为以后的业务留的备份数据
}PLC_COMMUNICATE_PROP;

typedef struct _VarPro
{
    QString varName;//变量名称
    Keyboard addr;   //对应的地址
    int dataType;//数据类型
    int RWPerm;//读写属性
    int count; //批量类型的个数
    bool bOffset; //是否存在偏移地址
    Keyboard offsetAddr; //对应的偏移地址
    _VarPro()
    {
        varName = "";
        addr = Keyboard();
        dataType = 0;
        RWPerm = 2;
        count = 1;
        offsetAddr = Keyboard();
        bOffset =false;
    }
}VarPro;

typedef struct _MacroLibrary
{
    QString libName;
    QString code;
    QStringList functions;
    bool isCompiled;
    QByteArray md5;
    bool type;
    QVector<VarPro> variants;
}MacroLibrary;

typedef struct initMaroProp//edit by zqh
{
    QString sLibName;     //脚本库名称
    QString sFucName;    //脚本函数名称
}INIT_MARO_PROP;       //初始化脚本结构体

typedef struct globalMaroProp //edit by zqh
{
    QString sLibName;    //脚本库名称
    QString sFucName;    //脚本函数名称
    int     iRunRate;          //执行频率
    bool  bIfCtrl;               //是否受控触发
    int     iCtrlType;           //受控类型，0-位控件，1-字控件
    Keyboard mCtlAddr;   //控制地址
    int    iValue;                 //执行条件
    int    iScriptCount;        //执行次数wxy
}GLOBAL_MARO_PROP; //全局脚本结构体

typedef struct dataTransferProp{
    quint8 nTriggerType;       //触发方式 1:计时，2：触发
    quint8 nTriggerSpace;      //触发间隔 0-20
    quint8 nAddrType;          //0:bit , 1: word, 2:double word
    quint8 nWordBitPos;        //字的哪一位来控制
    bool bAutomatismOff;    //自动复位
    Keyboard  mTriggerAddr;    //触发地址
    Keyboard  mSourceAddr;     //源地址
    Keyboard  mTargetAddr;     //目标地址
    bool bDynLength;        //是否动态长度
    Keyboard  mLengthAddr;     //长度地址
    QStringList sBackupForNewVer;    //为以后的业务留的备份数据
}DATA_TRANSFER_PROP;

typedef struct historyDataItem{
    quint8 nDataType;             //0-7
    quint8 nDataShowType;         //0:十进制数，1：十六进制数， 2:8进制数
    quint8 nDataLen;              //总位数，0-10
    quint8 nDataPointLen;         //小数位数
    bool   bZoom;                 //是否缩放
    QString  sAddrName;           //地址名称
    QString  sZoomStr;            //增益字符串值
    QString  sOffsetStr;          //偏移字符串值
    QVector<QString > sNameList;  //名字列表，同时存多种语言的名字,语言作索引
    QStringList sBackupForNewVer;    //为以后的业务留的备份数据
}HISTORY_DATA_ITEM;

typedef struct historyLogProp{
    bool  bHistoryDataExist;       //历史数据是否存在
    bool  bFullStop;               //取满是否停止取样
    bool  bFullNotic;              //取满是否通知
    bool  bAutoOff;                //自动复位
    quint8  nSampleType;           //取样方式,计时，触发，整点
    quint8  nFullNoticPercent;     //取满通知的百分比 0-100，代表百分之nFullNoticPercent
    quint16  nSampleLen;           //取样长度 0-32
    int     nTimeInterval;         //计时间隔  秒为单位
    int     nTriggerTime;          //整点触发时间 于多少分钟触发
    int     nSampleSize;           //取样大小
    QString sHistoryDataName;      //历史数据名称
    Keyboard mReadAddr;            //读取地址
    Keyboard mTriggerAddr;         //触发地址
    Keyboard mFullNoticAddr;       //取满通知地址
    QVector<HISTORY_DATA_ITEM > mSampleList;     //取样数据的列表，总大小为nSampleLen
    QStringList sBackupForNewVer;    //为以后的业务留的备份数据
    //at(0)---内存所需数 add by Dylan 2011-12-12
}HISTORY_LOG_PROP;

typedef enum _AddrConnectType{  //地址连接方式
    addrInside,   //内部的
    addrCom,      //com口
    addrNet       //net
}AddrConnectType;

typedef enum _PlcProType{  //协议枚举
    plcOne,      //协议1
    plcTwo,      //协议2
    plcThree     //协议3
}PlcProType;

 typedef struct dataAddressItem{
//     AddrConnectType eConnectType;     //地址连接方式
//     PlcProType      ePlcProType;      //协议枚举
//     quint16         nPlcRegIndex;     //PLC寄存器的索引
     quint16         nAddrNumber;      //每条地址的编号,针对随机地址
//     int             nPlcStationIndex; //PLC的站号
//     int             nPlcStartAddr;    //PLC的起始地址值
//     int             nAddrLen;         //地址的长度
     bool            bZoom;             //是否数据处理
     double             inputMax;         //采集范围高限
     double             inputMin;         //采集范围低限
     double             outputMax;         //工程范围高限
     double             outputMin;         //工程范围低限
     int                decLen;             //小数位数
     bool               bRound;             //是否四舍五入
     QString         name;
	 DATA_TYPE dataType;//数据类型
    Keyboard        keyAddress;       //编号对应的地址,针对随机地址
}DATA_ADDRESS_ITEM;

typedef enum _SampType{  //采样方式
    SampTime = 1,       //固定时间采样
    SampCycle,      //恒定周期采样
    SampControl     //位ON控制采样
}SampType;

typedef enum _SampFullType{  //采样取满处理
    SFReplace = 1,     //替换老数据
    SFClear,      //清除数据重新采样   
    SFStop,       //停止采样
}SampFullType;

typedef enum _SaveMidType{  //保存的媒介
    SM_Udisk = 1,     //媒介一
    SM_CFcard,    //媒介二
    SM_SDcard     //媒介三
}SaveMidType;

typedef enum _SaveDateType{  //保存的日期格式
    DateYMD = 1,       //年月日
    DateMDY,       //月日年
    DateDMY,       //日月年
    DateMD         //月日
}SaveDateType;

typedef enum _DataType{  //保存的数据类型
    DataInt = 1,        //符号整形
    DataUint,       //无符号整形
    DataHex,        //16进制
    DataBCD,        //BCD码
    DataFloat       //浮点型
}DataType;

typedef enum _AlarmCondtion{  //报警条件
    ALARM_ON = 1,     //ON报警
    ALARM_OFF,       //OFF报警
    ALARM_VALUE,      //固定值报警
    ALARM_RANGE,        //范围内报警
    ALARM_RANGE_OUT     //超出范围报警
}E_ALARM_CONDTION;

typedef struct dataSampling{
    bool         bContiguousAddr;    //是否是连续的地址
    bool         bFullNotic;         //是否取满通知
    bool         bAutoReset;         //是否自动复位
    bool         bSaveToFile;        //是否保存文件
    bool         bAutoSave;          //是否自动保存
    
    int          nSaveHour;          //自动保存时间间隔
    bool         bAddrCtlSamp;       //位地址控制是否采样
    //bool         bSampTime;          //是否采样频率时间间隔为1秒
    quint8       nDataLen;           //数据位数
    quint8       nDecimalLen;        //小数长度
    quint8       nStartHour;         //开始的时（0-23）
    quint8       nStartMinute;       //开始的分（0-60）
    quint8       nEndHour;           //结束的时（0-23）
    quint8       nEndMinute;         //结束的分（0-60）
    //quint8       nSampAddrLen;       //字地址采样长度
    quint8       nDigitLen;          //位长
    SampType     eSampType;          //采样方式
    SampFullType eDealSampFull;      //取满处理方式
    SaveMidType  eSaveMedium;        //保存的媒介
    SaveDateType eDateShowType;      //日期格式
    
    //int          nTotalSampNum;      //采样最大总数
    int          nSampTime;          //采样时间
    int          nSampUnit;          //采样单位
    int          nDataSampType;      //实时,1。历史,2
    int          nSampRate;          //采样的频率
    int          nSampRateUnit;      //频率单位
    int          nSampTimes;         //采样次数
    int          nSampCountUnit;     //采样次数频率

	bool          bDynTimeRange;     //是否动态时间范围
	bool          bDynSampleRate;     //是否动态采样频率
	Keyboard     startTimeAddr;     //开始采样时间（地址）
	Keyboard     endTimeAddr;     //结束采样时间（地址）
	Keyboard     dynRateAddr;     //采样频率（地址）
    
    Keyboard     strNoticAddrId;     //地址通知字符串
    Keyboard     strCtlSampAddrId;   //控制采样的地址字符串
    
    Keyboard     keyCtlSaveAddr;     //保存文件的控制地址
    bool         bPrint;                //是否打印
    bool         bPrintDate;            //是否打印日期
    bool         bPrintTime;            //是否打印时间

    QVector<DATA_ADDRESS_ITEM>  m_dataTable;  //数据表格
}DATA_SAMPLING;

typedef struct wHMIinfoToPlc{
    bool bWCurrSceneId;          //是否写当前画面号到plc
    bool bWCurrRecipeId;         //是否写当前配方号到plc
    bool bWCurrUserId;           //是否写当前用户号到plc
    bool bWCurrLangageId;        //是否写当前语言索引到plc
    Keyboard mSceneIdAddr;       //写当前画面的地址
    Keyboard mRecipeIdAddr;      //写当前配方号的地址
    Keyboard mUserIdAddr;        //写当前用户号的地址
    Keyboard mLangageIdAddr;     //写当前语言索引的地址
    QStringList sBackupForNewVer;    //为以后的业务留的备份数据
}WRITE_HMIINFO_TO_PLC;

typedef struct sceneCtlByBitProp{
    bool   bReset;                   //自动复位
    quint8 nCtlStatus;           //控制画面切换的状态
    quint8 nCtlSceneId;          //要更改的画面号
    Keyboard mCtlSceneAddr;      //控制更改画面的地址
    QStringList sBackupForNewVer;    //为以后的业务留的备份数据
}SCENE_CTL_BY_BIT;

typedef struct ctlByPlcProp{
    bool  bCtlRecipeChange;      //控制更改配方
    bool  bCtlWriteRecipe;       //控制写入配方
    bool  bCtlCurrUserId;        //控制更改当前用户
    bool  bWordCtlSceneSwitch;   //字控制画面切换
    bool  bBitCtlSceneSwitch;    //位控制画面切换
    Keyboard mChangeRecipeAddr;  //控制更改配方的地址
    Keyboard mWriteRecipeAddr;   //控制写入配方的地址
    Keyboard mCtlUserIdAddr;     //控制更改当前用户的地址
    Keyboard mSceneCtlByWAddr;   //字控制画面切换的地址
    QVector<SCENE_CTL_BY_BIT> mSceneCtlByBitList;   //位控制画面切换的地址
    QStringList sBackupForNewVer;    //为以后的业务留的备份数据
}CTL_BY_PLC;

typedef struct clockProp{
    bool    bReset;              //是否自动复位
    quint8  nDataType;           //数据类型
    quint8  nAddrLen;            //地址长度
    quint8  nStartType;          //启动方式 0:计时 1：触发
    quint16 nTimeInterval;       //时间间隔 1-255
    Keyboard mCtlAddr;           //控制地址
    Keyboard mTriggerAddr;       //触发地址
}CLOCK_PROP;

typedef struct treeClockProp{
    bool bDownLoadTime;          //是否下载系统时间到PLC
    bool bWTimeToPlc;            //是否写时间到PLC
    bool bRTimeFromPlc;          //与PLC时间相同
    CLOCK_PROP mWTimeToPlc;      //写时间到PLC
    CLOCK_PROP mRTimeFromPlc;    //与PLC时间同步
    QStringList sBackupForNewVer;    //为以后的业务留的备份数据
}TREE_CLOCK_PROP;

typedef struct fileProtectProp{
    bool bNeedFileProtect;       //是否需要文件保护
    QString sProtectPWD;         //文件保护的密码
}FILE_PROTECT_PROP;

typedef struct HMIProtectSet{
    quint8   nProtectSceneId;    //保护画面的ID
    QString  sUnlockPWD;         //解锁密码
    QDate    mProtectDate;       //期限日期
    QTime    mProtectTime;       //期限时间
    QStringList sBackupForNewVer;    //为以后的业务留的备份数据
}HMI_PROTECT_SET;

typedef struct HMIProtectProp{
    bool  bSelectHMIProtect;     //是否选择HMI保护
    quint8 nTotalProtectNum;     //保护总数
    quint8 nCurrentLevel;        //当前选择的保护等级
    QVector<HMI_PROTECT_SET > mProtectList;   //保护属性列表
    QStringList sBackupForNewVer;    //为以后的业务留的备份数据
}HMI_PROTECT_PROP;

typedef struct recipeProp{
    bool     bRecipeExist;       //是否存在配方
    bool     bWRecipeToPlc;      //是否写配方到PLC
    bool     bRRecipeFromPlc;    //是否从PLC中读配方
    bool     bRaddrSameWaddr;    //读取地址是否与写地址相同
    quint8   nDataType;          //数据类型
    quint16  nRecipeTotalNum;    //配方总数 0-255
    int      nRecipeLen;         //配方长度
    int      nLanIndex;        //语言的索引
    QString  sRecipeName;        //配方名称
    QString  sDescription;       //描述
    QString  sRecMemAddrRange;   //配方记忆地址范围
    QString  sCurrRecAddrRange;  //当前配方地址范围
    QString  sRecipeRegNum;      //配方编号寄存器
    Keyboard mWRecipeAddr;       //写配方的地址
    Keyboard mRRecipeAddr;       //读配方的地址
    QVector<quint8 >  nSourceIdList;      //源配方编号
    QVector<quint8 >  nTargetIdList;      //目标配方编号
    QVector<QString > sRecipeData;        //数据列表
    QVector<QVector<QString > > sRowHeadName;       //配方数据列头名称
    QStringList sBackupForNewVer;    //为以后的业务留的备份数据
}RECIPE_PROP;

//配方数据 begin
typedef struct
{
    QString sName;//元素名称
    QString sAddr;//元素地址
    Keyboard  addr;
    QString sAddrType; //地址类型
    QString  sText;     //元素值
}ELMENT;

//配方多语言表
typedef struct
{
   QString sRecipeName;//配方名称
   short   nLanguageId;//语言ID
   QString sRecipeDescri;//配方描述
   short   nRecipeId;    //配方ID
}RECIPELANGUAGE;

typedef struct
{
    short nLanguageId;	        //语言id号
    short nRecipeGroupId;	//配方组id
    short nElemIndex;	        //配方元素的ID
    QString sElemName;	        //元素的名称
}RECIPEElEMENT;

typedef struct
{
    QVector <RECIPELANGUAGE> RecipeInfo;//配方名称信息
    QString sFormulaName;//配方名称
    QVector<ELMENT> elment;
    int nColum;          //列下标
}FORMULA_ST;

typedef struct
{
    QVector<FORMULA_ST> formula;
    QString   sName;              //配方组名称
    QString   sRecipeGDescri;     //配方数组的描述
    int       nRecipeNum;         //一组配方的数量
    int       nRecipeLen;         //一个配方的长度
    short     eDataType;          //配方的数据类型
    short     nLanguageId;        //语言下标
    bool      bCtlAddr;           //是否需要控制地址
    QString   sCtlAddrId;         //控制地址
    Keyboard  addrCtl;            //控制地址
    //bool      bTransRecipe;       //是否传输配方
    short     eRecipeTransType;   //配方传输方式 1：可读写 2：从PLC读 3：写到PLC
    bool      bCompleteNotic;     //是否需要完成通知
    QString   sComNoticAddrId;    //完成通知地址
    Keyboard  addrNotic;          //位完成通知地址
    short     eSaveMedia;         //存储路径 1：内部存储区 2：U盘 3:SD卡
    bool      bContniu;            //true连续 false随即
    QString   sContniuAddr;        //连续地址
    QVector  < QVector<RECIPEElEMENT> > ElmentName;//元素多语言信息

    short int nKeyId;                 //键盘编号
    QString   sKeyname;               //键盘名称
    bool      nKeyMark;               //是否启用键盘
    int       nBoardX;              //自定义键盘起点X
    int       nBoardY;              //自定义键盘起点Y
}FORMULA_PROP;

//配方数据 end
typedef struct languageProp{
    quint8 nTotalNum;                      //语言总数
    QVector<QString > sLanguageNameList;   //语言名称列表
}LANGUAGE_PROP;



typedef struct digitalAlarmProp{
    quint8  nTypeIndex;         //类型的索引
    quint8  nLanguageId;        //报警的索引
    quint8  nScanInterval;      //扫描时间间隔 0-99
    quint16 nAddrLen;           //地址长度 0-512
    quint16 nCurrRowIndex;      //当前行
    QString sAlarmName;         //报警名称
    Keyboard mReadAddr;         //读取地址
    QVector<bool >    bSelect;      //是否选择
    QVector<bool >    bOFFSelect;      //是否选择
    QVector<QVector<QString > > sMsgList;     //消息列表
    QStringList sBackupForNewVer;    //为以后的业务留的备份数据
}DIGITAL_ALARM_PROP;
//单条报警
typedef struct _stAlarm
{
    int index;
    Keyboard addr;
    int symb;//符合 = > <
    double value;
    QStringList messages;
    DATA_TYPE dataType;//数据类型
    double rangeHigh;
    double rangeLow;
    E_ALARM_CONDTION eCondtion;//报警条件 ：ON 报警，OFF报警 ，固定值报警，范围内报警，超出范围报警
    bool bOpenScene;//报警是否打开窗口
    QString sceneName; //窗口名称
    bool bSeneMsg; //报警是否发送短信息
    QStringList sPhoneNums; //报警发送短信息目标电话号码
    bool bAddtoDB;//报警是否添加到数据库
    bool bPrint;                //是否打印
    bool bPrintDate;            //是否打印日期
    bool bPrintTime;            //是否打印时间
}stAlarm;
typedef struct AlarmGroup
{
    QString alarmName;
    int addrType;
    DATA_TYPE dataType;//数据类型
    QVector<stAlarm >alarms;
}ALARM_GROUP;

typedef struct analogAlarmProp{
    quint8  nCurrRowIndex;      //当前行
    quint8  nLanguageId;        //报警的索引
    quint8  nScanInterval;      //扫描时间间隔 0-99
    quint16 nAddrLen;           //地址长度 0-32
    QString sAlarmName;         //报警名称
    Keyboard mReadAddr;         //读取地址
    QVector<bool >    bSelect;      //是否选择
    QVector<quint8 >  nDataType;    //数据类别列表
    QVector<double >     nBoundary;    //界限列表
    QVector<QVector<QString > > sMsgList;     //消息列表
    QStringList sBackupForNewVer;    //为以后的业务留的备份数据
}ANALOG_ALARM_PROP;


typedef struct _stAddrPrarm{
	QString    sName;   //设备名称
	int        regIndex;//寄存器序号
	int		   addrValue;//地址值
	int        length;   //地址长度
	READ_WRITE_COM_TYPE rwPrarm;//读写属性
}stAddrPrarm;
//掉电存储区
typedef struct _stPowerProtect{
    int        startLB;   //起始地址值
    int        lengthLB;//地址长度
    int		   startLW;//起始地址值
    int        lengthLW;   //地址长度
}stPowerProtect;

typedef struct __MACRO_LIB__{
    QString libName;
    QStringList funcNames;
}MacroLib;

/**********************************************************
  变量表结构体
**********************************************************/
typedef struct globalOperateRecord{
    QString    SVarName;   //变量名字
    int        ibitWord;
    Keyboard   mCtlAddr;   //地址
}GLOBAL_VAR_RECORD;

//新增变量表 13-10-17
typedef struct _VarRecord{
    QString    sVarName;   //变量名字
    DATA_TYPE mType;//数据类型
    Keyboard   mAddr;   //地址
}VarRecord;

class Schedulers;
class QSamSysParame
{
public:
    QSamSysParame();
    ~QSamSysParame();

public:
    void globalCompile(QSqlDatabase &db,int &count);//全局宏
    void initCompile(QSqlDatabase &db,int &count);//初始化宏
    void dataSamplingCompile(QSqlDatabase &db,int &count);//数据采集数据库
    void insertSampleAddr(QSqlDatabase &db,int &count,QVector<DATA_ADDRESS_ITEM> m_dataTable,int nGroupId,int sampleType);
    void SystemProcCompile(QSqlDatabase &db,int &count,bool bSimulator);//系统参数设置
    void PasswordCompile(QSqlDatabase &db,int &count);//密码表
    void LanguageCompile(QSqlDatabase &db,int &count);//语言表
    void UserRightCompile(QSqlDatabase &db,int &count);//用户组权限表
    void alarmCompile(QSqlDatabase &db,int &count);//报警登录部分
    void alarmMessagesCompile(QSqlDatabase &db,QStringList msgs,int GroupId,int AlarmIndex);//报警消息表
    void connectCompile(QSqlDatabase &db,int &count);//连接设置部分
    void protoclCompile(QSqlDatabase &db,QVector<stProtocol> protocols,int nConnectId,int nUserPlcIndex);//连接协议部分
    void recipeCompile(QSqlDatabase &db,int &count);
    void datatransferCompile(QSqlDatabase &db,int &count);
    void timesettingCompile(QSqlDatabase &db,int &count);
    void schedulerCompile(QSqlDatabase &db,int &count);
    void compile(QSqlDatabase &db,int &count,bool bSimulator);

private:
    friend QDataStream &operator<<(QDataStream &stream, QSamSysParame *pSamSysParame);
    friend QDataStream &operator>>(QDataStream &stream, QSamSysParame *pSamSysParame);

public:
    quint8 nUserDefKeyboardCount; //0-31
    /*file proptect ,but not use by lower*/
    FILE_PROTECT_PROP m_fileProtect;

    //+++++
    PROJECT_PROP m_projectProp;
    GlobalVariable m_mixGlobalVar;

    /*setting */
    WRITE_HMIINFO_TO_PLC m_wHmiInfoToPlc;
    CTL_BY_PLC m_ctlByPlc;
    TREE_CLOCK_PROP m_clockProp;
    HMI_PROTECT_PROP m_hmiProtectProp;
    //LANGUAGE_PROP m_languageProp;

    /*history*/
    //HISTORY_LOG_PROP    m_historyLogData;      //旧的变量，以后不要的
    QVector<DATA_SAMPLING> m_loadDataSampling;   //新的数据采集变量
    QVector<QString>    m_vecDataSamplingStr;    //每个数据采集变量的命名

    //alarm
    QVector<ALARM_GROUP > m_qvcAlarm;

    //connect info
    QVector<stConnect > m_qvcConnect;

    /*recipe*/
    RECIPE_PROP m_recipeProp;
    QVector<FORMULA_PROP> m_qvcRecipe;
    FORMULA_PROP m_qRecipe;
    /*plc Communicate connect */
    QVector<PLC_COMMUNICATE_PROP > m_qvcPlcCommunicate;
    QVector<INIT_MARO_PROP > m_qvcInitMaroProp;
    QVector<GLOBAL_MARO_PROP > m_qvcGlobalMaroProp;
    QVector<DATA_TRANSFER_PROP > m_qvcdataTransProp;

    QVector<GLOBAL_VAR_RECORD > m_qvcVarRecord;   //变量表容器
    //新增变量表 13-10-17
    QVector<VarRecord> m_VarRecord;

    stPowerProtect m_PowerProtect;

    Schedulers *schedulers;
    //QVector<SamDrawScene *> pUserKeyboard_vector;//用户自定义键盘容器
};


class MsgOutPut //信息输出窗口的item和画面序号
{
public:
    QGraphicsItem *pItem; //扫描的item
    int nSheetIndex;      //画面序号
};

class AddrMsg //存地址信息,用于地址查找，地址一览表和编译地址错误检查使用
{
public:
    QGraphicsItem *pItem; //扫描的item
    int nSheetIndex;      //画面序号
    QVector<ADDRPRO> Address;
};

/********************新建工程的数据封装**************************/
class QNewPro
{
public:
    /************新建工程里面的新建工程向导页面的数据*************/
    QString newprowizard_path;//新建项目的路径
    QString newprowizard_name;//新建项目的名字
    QString newprowizard_model;//新建项目的型号选择
    QString HMI_Name;
    QString newprowizard_showmodel;//新建项目的显示型号
    QString     newprowizard_showmodel_maxscreennum;//新建项目的最大画面数
    /********************************************************/

    /************新建工程里面的连接向导页面的数据*************/
    QString  newlinkwizard_connection;//连接向导的连接编号
    QString  newlinkwizard_linkname;//连接名称
    QString  newlinkwizard_linktype;//连接种类
    QString  newlinkwizard_linkdevice;//连接设备
    QString  newlinkwizard_linkserver;//连接服务
    QString  newlinkwizard_plcaddress;//PLC的连续地址间隔

    QString sName;	//用户设定的名称 用户可以重命名
    QString sFactoryName; //协议所属的厂家名称 不可变，从文件取得
    QString sProtocolName;//协议名称。不可变，从文件取得
    QString proFlag;//协议是在连接0，连接1，还是以太网
    /******************************************************/

    /************新建工程里面的新建画面页面的数据*************/
    QString  newscreenwizard_name;//新建画面的名字
    QColor  newscreenwizard_bk;//背景色
    QColor  newscreenwizard_frontcolor;//前景色
    int  newscreenwizard_style;//样式
    QString  newscreenwizard_picturepath;//画面路径
    bool  ischeck_slience;//默认的选择状态
    bool  ischeck_picture;//图片的选择状态
    int   nSeleteType;//默认选择
    // nNewscreenwizard_style
    /******************************************************/
private:
    friend QDataStream &operator<<(QDataStream &stream, QNewPro *pNewPro);
    friend QDataStream &operator>>(QDataStream &stream, QNewPro *pNewPro);

};//

//wxy 离线模拟状态
typedef enum _state{         //当前模拟运行的状态
    START_VBOX = 1,            //启动虚拟机
    VBOX_READY,              //虚拟机已就绪，
    CONNECT_ADB,              //通过IP建立连接
    DOWLOAD_FILE,              //连接成功，开始传输文件
    RUNNING						//模拟运行中
}SIMULAT_STATE;

#endif // QPROGECTMANAGER_H


