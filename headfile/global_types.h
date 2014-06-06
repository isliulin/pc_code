#ifndef DEFINEMACRO_H
#define DEFINEMACRO_H

#include <QString>
#include <QColor>
#include <QDoubleValidator>
#include <QSizeF>

#define AK_PROJECT 0
#define LA_PROJECT 1
#define AKPLC_PROJECT 2
#define CURRENT_PROJECT AK_PROJECT
//一体机代码


#if(CURRENT_PROJECT == AK_PROJECT)//AK 工程
    #define SUFFIX              "*.ak"//后缀
    #define LOWER_CASE_PRO_NAME "ak" //小写工程名
    #define CAPITAL_PRO_NAME    "AK" //大写工程名
    #define PRO_FULL_NAME       "AKWorkshop"//工程全称
    #define SAVE_FILE_STR       "AK Files (*.ak)"
    #define AK_FILE_END         ".ak"
    #define VERSION_NAME        "AKWorkShop"
    #define PRO_TYPE            "AK-070AS"
    #define AK_SAMKOON          "@@@SAMKOON###"//显控特有标注
#elif(CURRENT_PROJECT == LA_PROJECT)//LA工程
    #define SUFFIX              "*.la"//后缀
    #define LOWER_CASE_PRO_NAME "la"//小写工程名
    #define CAPITAL_PRO_NAME    "LA"//大写工程名
    #define PRO_FULL_NAME       "LAWorkshop"//工程全称
    #define SAVE_FILE_STR       "LA Files (*.la)"
    #define AK_FILE_END         ".la"
    #define VERSION_NAME        "LAWorkShop"
    #define PRO_TYPE            "LA-1070BS"
    #define LA_DEBINUO          "@@@DEBINUO###"//德比诺特有标注
#elif(CURRENT_PROJECT == AKPLC_PROJECT)//AKP 工程
    #define SUFFIX              "*.akp"//后缀
    #define LOWER_CASE_PRO_NAME "akp" //小写工程名
    #define CAPITAL_PRO_NAME    "AKP" //大写工程名
    #define PRO_FULL_NAME       "AKWorkshop"//工程全称
    #define SAVE_FILE_STR       "AKP Files (*.akp)"
    #define AK_FILE_END         ".akp"
    #define VERSION_NAME        "AKWorkShop"
    #define PRO_TYPE            "AK-070AS"
    #define AK_SAMKOON          "@@@SAMKOON###"//显控特有标注
    #define AKPLC               //一体机
#endif

/********************************************************************
  作用：定义宏
  作者：郑启红
  时间：2010-10-28
********************************************************************/
#define MAX_SCRNCNT 1000 //画面总数

/* QGraphicsItem::UserType */
#define Qt_USER_TYPE_BASE 65536
#define AK_CURRENT_VERSION 3457

#define VERSION_NUM         "-V1.0.2"//此处不要修改

#define SWITCH_BACK_TYPE    1000   //用来区分开关类型backitem
#define MIN_ITEM_SIZE       1//item设置的最小值

#define DRIVERS_MODLE       "Drivers/qtdll/drivers.dat"
/* Sam draw 3.4 item object type define.
 * Note: this enum value must be the same
 * with the Type(type()) in class defination
 */
enum eSamDrawObjQtType
{
    SAM_DRAW_OBJECT_RECT        = Qt_USER_TYPE_BASE + 15,
    SAM_DRAW_OBJECT_ELIPSE      = Qt_USER_TYPE_BASE + 16,
    SAM_DRAW_OBJECT_LINE        = Qt_USER_TYPE_BASE + 17,
    SAM_DRAW_OBJECT_POLYGON     = Qt_USER_TYPE_BASE + 18,
    SAM_DRAW_OBJECT_FOLDLINE    = Qt_USER_TYPE_BASE + 19,
    SAM_DRAW_OBJECT_FREELINE    = Qt_USER_TYPE_BASE + 20,
    SAM_DRAW_OBJECT_ARCLINE     = Qt_USER_TYPE_BASE + 21,
    SAM_DRAW_OBJECT_TEXT        = Qt_USER_TYPE_BASE + 22,
    SAM_DRAW_OBJECT_GROUP       = Qt_USER_TYPE_BASE + 23,
    SAM_DRAW_OBJECT_PIXMAP      = Qt_USER_TYPE_BASE + 24,
    SAM_DRAW_OBJECT_LINECIRCLE  = Qt_USER_TYPE_BASE + 25,

    SAM_DRAW_OBJECT_ROUNDEDRECT = Qt_USER_TYPE_BASE + 26,
    SAM_DRAW_OBJECT_ARC         = Qt_USER_TYPE_BASE + 27,

    SAM_DRAW_OBJECT_RECT_NEW        = Qt_USER_TYPE_BASE + 35,
    SAM_DRAW_OBJECT_ELIPSE_NEW      = Qt_USER_TYPE_BASE + 36,
    SAM_DRAW_OBJECT_LINE_NEW        = Qt_USER_TYPE_BASE + 37,
    SAM_DRAW_OBJECT_POLYGON_NEW     = Qt_USER_TYPE_BASE + 38,
    SAM_DRAW_OBJECT_FOLDLINE_NEW    = Qt_USER_TYPE_BASE + 39,
    SAM_DRAW_OBJECT_FREELINE_NEW    = Qt_USER_TYPE_BASE + 40,
    SAM_DRAW_OBJECT_ARCLINE_NEW     = Qt_USER_TYPE_BASE + 41,
    SAM_DRAW_OBJECT_LINECIRCLE_NEW  = Qt_USER_TYPE_BASE + 42,
    SAM_DRAW_OBJECT_ROUNDEDRECT_NEW = Qt_USER_TYPE_BASE + 43,
    SAM_DRAW_OBJECT_ARC_NEW         = Qt_USER_TYPE_BASE + 44,

    SAM_DRAW_OBJECT_LINETRACKER = Qt_USER_TYPE_BASE + 997,
    SAM_DRAW_OBJECT_LINEEX      = Qt_USER_TYPE_BASE + 998,
    SAM_DRAW_OBJECT_TRACKER     = Qt_USER_TYPE_BASE + 999,
    SAM_DRAW_OBJECT_LOCK        = Qt_USER_TYPE_BASE + 1000,
    SAM_DRAW_OBJECT_QT_TYPE_BUTT
};
typedef enum eSamDrawObjQtType SAM_DRAW_OBJECT_TYPE_E;


enum eGroupType
{
    SAM_DRAW_GROUP_SWITCH       = 10,//开关类型
    SAM_DRAW_GROUP_CHART        = 11,//图表
    SAM_DRAW_GROUP_VALUE        = 12,//数值显示
    SAM_DRAW_GROUP_TREND        = 13,//趋势图
    SAM_DRAW_GROUP_GROUPDATA    = 14,//数据群组
    SAM_DRAW_GROUP_IMAGE        = 15,//图片显示
    SAM_DRAW_GROUP_ASCII        = 16,//ascii显示
    SAM_DRAW_GROUP_TIME         = 17,//时间显示
    SAM_DRAW_GROUP_ALARMITEM    = 18,//报警显示控件
    SAM_DRAW_GROUP_ALARMBAR     = 19,//动态报警条
    SAM_DRAW_GROUP_HISALARMITEM = 20,//历史报警显示控件
    SAM_DRAW_GROUP_FLOW         = 21,//流动块
    SAM_DRAW_GROUP_ANIMATION    = 22,//动画
    SAM_DRAW_GROUP_KEY          = 23,//键盘组件
    SAM_DRAW_GROUP_DYNRECT      = 24,//动态矩形
    SAM_DRAW_GROUP_DYNCIRCLE    = 25,//动态圆
    SAM_DRAW_GROUP_DROPDOWN     = 27,//功能选择按钮
    SAM_DRAW_GROUP_STATICTEXT   = 28,//静态文本
    SAM_DRAW_GROUP_RECIPE       = 29,//配方选择器
    SAM_DRAW_GROUP_RECIPESHOW   = 30,//配方显示器
    SAM_DRAW_GROUP_CALIBRATION  = 31,//刻度
    SAM_DRAW_GROUP_HISTORYDATE  = 32,//历史数据显示器
    SAM_DRAW_GROUP_SLIDER       = 33,//滑动块/进度条
    SAM_DRAW_GROUP_STATICPIC    = 34,//GIF显示器
    SAM_DRAW_GROUP_MESSAGE      = 35,//消息显示器
    SAM_DRAW_GROUP_TABLE        = 36,//表格
    SAM_DRAW_GROUP_TEXTBOARD    = 37,//留言板
    SAM_DRAW_GROUP_MFBTN        = 38,//多功能按钮
    SAM_DRAW_GROUP_COMBOBOX     = 39,//下拉框
    SAM_DRAW_GROUP_XYTREND      = 40,//XY趋势图
    SAM_DRAW_GROUP_USER		= 100,//自定义组合

    SAM_DRAW_GROUP_QT_TYPE_BUTT
};
typedef enum eGroupType ENUM_GROUP_TYPE;



struct PicPosInfo{
	bool fixrect;
	int  space;
	int  btnIndex;
};

enum EITEM_TYPE
{
    PIC,          //图片
    LIBRARY,      //图库
    USERDEFINE,   //用户自定义图库
    NO_PIC,       //没有图片
};


struct TextProp
{
    QString sfont;//字体
    QString text;//文本
    int size;//字体大小
    QColor color;//文本色
    int showProp;//闪烁，粗体，黑体，下划线，对齐
};
typedef struct TextProp ST_TEXT_PROP;
typedef QVector<QVector<ST_TEXT_PROP > > textProList;
enum FLICK_TYPE
{
	NO_FLICK,          //不闪烁
	FLICK_TEXT,      //文本闪烁
	FLICK_SHOW,   //控件显隐
	FLICK_STATUS	//状态切换
};
struct PicProp
{
    EITEM_TYPE bLib;//是图库还是外部图片 0标示是外部图片 1表示是图库

    QString path;//路径
	FLICK_TYPE eFlick;//闪烁属性
    int nAlpha;//透明度
	QColor color;//背景色
};
typedef struct PicProp ST_PIC_PROP;
typedef QVector<ST_PIC_PROP > picProList;

typedef struct
{
    QMap<QString, QString> mLibPath;
    QMap<QString, QSizeF> mLibSize;
}ST_LIBPATH;

/*******************************************************************
Group中保存NAME属性的key
即对于GROUP 通过setData(GROUP_NAME_KEY,name)来保存该组合的名字
*******************************************************************/
#define GROUP_NAME_KEY 66535

//该data位置保存组合控件的类型描述，不同于基本item类型的type
//即 key值为66536 的data区保存组合控件的类型描述
#define GROUP_TYPE_KEY 66536
//保存datalist的data区key值
#define GROUP_DATALIST_KEY 66537
//QPixmapItem 保存图片的data区的KEY值
#define PIC_SAVE_KEY 66538
//QPixmapItem 刷新计数器所在的data区
#define  PIC_COUNT_KEY 66539
//QPixmapItem 保存boundrect所在的data区
#define PIC_RECT_KEY 66540
#define ITEM_ID_KEY 66541     //控件ID的Key
#define GROUP_RECT_KEY 66542

// 以下宏定义了组合控件的类型值

#define GROUP_TYPE_BITBTN 10 // 是位按钮

#define GROUP_TYPE_BITLAMP 14//位指示灯
#define GROUP_TYPE_WORDBTN 11//子按钮
#define GROUP_TYPE_SCREENBTN 12//画面按钮
#define GROUP_TYPE_FUNCTIONBTN 13//功能按钮
#define GROUP_TYPE_WEEKBTN  24 //星期按钮
#define GROUP_TYPE_DYNCIRCLE  30 //动态圆
#define GROUP_TYPE_DYNRECT  31 //动态矩形
#define GROUP_TYPE_MFUNCTION  39 //多功能
#define GROUP_TYPE_MULSTATELAMP 15//多状态指示灯
#define GROUP_TYPE_MULSTATEBTN  16//多态按钮
#define GROUP_TYPE_PICTUREDISPLAY 26//图片显示器
#define GROUP_TYPE_PICTUREMOVE   35  //图片移动

#define GROUP_TYPE_NUMDISPLAY 17//数值显示
#define GROUP_TYPE_NUMENTRY 18//数值输入
#define GROUP_TYPE_ASCIIDISPLAY 19//ASCII码显示
#define GROUP_TYPE_ASCIIENTRY 20//ASCII码输入
#define GROUP_TYPE_BARGRAPH 21//柱状图
#define GROUP_TYPE_TIMEDISPLAY 22//时间显示
#define GROUP_TYPE_DATEDISPLAY 23//日期显示

#define GROUP_TYPE_ALARMCONTROL 32//报警显示器
#define GROUP_TYPE_DYNALARMBAR 33//动态报警条
#define GROUP_TYPE_HISALARM 34//历史报警显示器
#define GROUP_TYPE_METER 36//仪表
#define GROUP_TYPE_FLOWBLOCK 40//流动条

#define GROUP_TYPE_MSGDISPLAY 104//消息显示
#define GROUP_TYPE_STATICPIC 100//静态图片
#define GROUP_TYPE_GIFPIC 101//GIF图片
#define GROUP_TYPE_PIE 102   //扇形图
#define GROUP_TYPE_STEPING 103   //步进按钮

#define GROUP_TYPE_CHART  200    //图表
#define GROUP_TYPE_VALUE  201    //数据显示
#define GROUP_TYPE_TABLE 105   //表格
#define GROUP_TYPE_SCALES 106   //刻度
#define GROUP_TYPE_STATICTEXT 107  //静态文本

#define GROUP_TYPE_TRENDCHART 108  //趋势图
#define GROUP_TYPE_XYTRENDCHART 109  //XY趋势图
#define GROUP_TYPE_HISTRENDCHART 110  //历史趋势图
#define GROUP_TYPE_HISDATAALARM 111  //历史数据显示器

#define GROUP_TYPE_SINGLESELECT 112  //单选按钮
#define GROUP_TYPE_COMBOBOX 113  //下拉框
#define GROUP_TYPE_SLIDER 114  //滑块模拟量开关
#define GROUP_TYPE_ANIMATE 115  //动画
#define GROUP_TYPE_MESSAGEBOARD 116  //留言板

#define BASEITEM_TYPE_ROUNDEDRECT 117  //圆角矩形
#define BASEITEM_TYPE_ARC 118  //扇形
#define GROUP_TYPE_DATAGROUPDISPLAY 119  //数据群组显示
#define GROUP_TYPE_TIMER 120  //定时器
#define GROUP_TYPE_ASCII_KEYBOARD 121  //ASCII键盘

#define GROUP_TYPE_RECIPE_CHOICE 150  //配方选择器
#define GROUP_TYPE_RECIPE_DISPLAY 151 //配方显示器

#define GROUP_TYPE_OPERATE_RECORD 152 //操作日志显示器。edit by panfacheng
#define GROUP_TYPE_VARIBLE 153 //变量表。edit by panfacheng

#define LIBRARY_LIB_GROUP 198  //图库组合
#define LIBRARY_PIXMAP_GROUP  200 //图片图库
#define USER_DEFINE_GROUP 199  //用户自定义组合

#define DIGIT_ALARM_NUM 64  //数位报警的个数
#define ANALOG_ALARM_NUM 64  //类比报警的个数

#define INITMARCO_NUM 16    //初始化宏个数
#define GLOBALMARCO_NUM 64  //全局宏宏个数

//工程管理器
#define TREE_COM_LINK 122  //Com连接
#define TREE_HMI_SETTING 123  //触摸屏参数设置
#define TREE_HMI_STATE 124  //HMI状态
#define TREE_PLC_CONTROL 125  //PLC控制
#define TREE_CLOCK 126  //时钟
#define TREE_FILE_PROTECT 127  //文件保护
#define TREE_HMI_PROTECT 128  //HMI保护
#define TREE_DIGIT_ALARM 129  //数位报警
#define TREE_ANALOG_ALARM 130  //类比报警
#define TREE_RECIPE 131  //配方
#define TREE_DATA_TRANSFORM 132  //资料传输
#define TOOLBAR_OPENLIBRARY 133  //打开图库
#define TOOLBAR_SAVELIBRARY 134  //保存图库
#define TREE_HISDATA_RECORD 135 //历史数据收集器
#define GLOBAL_HELP_KEY 136 //帮助文档的起始页面
#define TREE_LANGUAGE 137 //语言
#define GLOBAL_MACRO_KEY 138 //全局宏
#define INIT_MACRO_KEY 139 //初始化宏
#define MACRO_START_KEY 140 //启动宏指令对话框
#define MACRO_EDIT_KEY 141 //宏指令编辑
#define TABLE_ITEM_MOVE 142
//新增
#define TREE_COM_DEAL 300  //Com协议
#define TREE_SHOWSET 301 //显示设置
#define TREE_IMPOWER 302 //产品授权
#define TREE_MODELCHOICE 303 //机型选择
#define TREE_DATACONTROL 304 //数据控制
#define TREE_USERPOWER 305 //用户权限
#define TREE_DOWNSET 306 //下载设置
#define TREE_DOWNPOWER 307 //掉电保存
#define TREE_ALARMLOGIN 308  //报警登录

//画面窗口
#define TREE_SCREENS 143 //画面
#define TREE_WINDOWS 144 //窗口

#ifndef COMPRESSFILE_PATH
#define COMPRESSFILE_PATH "/samkoon/samhmi3.4/configuration/project.bin"
#define SIMFILE_PATH "/samkoon/samhmi3.4/configuration/prj.bin"
#define SHMFILE_PATH "/samkoon/samhmi3.4/configuration/samkoon.shm"
#define DRIVER_DIR "/samkoon/samhmi3.4/driver/"
#endif

#define PICTURE_PATH "Picture/"          //打包图片保存路径
#define SCRIPT_HEADER "/*********************Please don't delete******************************/\r\n\
public void MACRO_MAIN(HashMap<String, PHolder> params){\r\n\
    SysInit(params);\r\n\
    \/\/TODO\r\n\
}\r\n"
#define SYS_FUNCTION_HEADER "/*********************Please don't delete******************************\r\n\
public static int fun(){\r\n\
	return 0;\r\n\
}\r\n\
****************************************************************/\r\n"
static int ColorToInt(QColor color)
{
    int value = (((0xFF << 24)) | ((color.red() << 16)) | ((color.green() << 8)) | color.blue());
    return value;
}

class DoubleValidator : public QDoubleValidator
{
public:
    DoubleValidator(QObject * parent = 0,int base = 10)
        : QDoubleValidator(parent)
    {
        nBase = base;
    }

    DoubleValidator( double bottom, double top, int decimals, QObject* parent = 0)
        : QDoubleValidator( bottom, top, decimals, parent)
    {}

    QValidator::State validate(QString & input, int &) const
    {
        const double b = bottom();
        const double t = top();
        const int d = decimals();

        QRegExp empty(QString::fromLatin1("-?\\.?"));

        if (input.contains(' '))//空格
            return Invalid;

        if(0 == d)
        {
            if (input.contains('.'))//空格
                return Invalid;
        }
        if (b >= 0 && input.startsWith(QLatin1Char('-')))//大于等于0时输入负号
            return Invalid;

        if (empty.exactMatch(input))
            return Intermediate;
        bool ok = false;
        double entered = input.toDouble(&ok);

        if(16 == nBase)
        {
            entered = input.toInt(&ok,16);
        }
        else if(10 == nBase)
        {
            entered = input.toDouble(&ok);
        }
        else if(8 == nBase)
        {
            entered = input.toInt(&ok,8);
        }
        if (!ok) return Invalid;

        int nume = input.count('e', Qt::CaseInsensitive);
        int i;
        if (input.contains(','))
            i = input.indexOf(',');
        else
            i = input.indexOf('.');
        if (i >= 0 && nume == 0)
        {
            // has decimal point (but no e), now count digits after that
            i++;
            int j = i;
            while(input[j].isDigit())
                j++;
            if (j - i > d)
                return Invalid;
        }
        if( entered < b )
        {
            return Invalid;
        }
        else if( entered > t )
        {
            return Invalid;
        }

        return Acceptable;
    }
public:
    int nBase;
};

#endif // DEFINEMACRO_H
