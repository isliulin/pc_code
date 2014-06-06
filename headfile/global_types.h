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
//һ�������


#if(CURRENT_PROJECT == AK_PROJECT)//AK ����
    #define SUFFIX              "*.ak"//��׺
    #define LOWER_CASE_PRO_NAME "ak" //Сд������
    #define CAPITAL_PRO_NAME    "AK" //��д������
    #define PRO_FULL_NAME       "AKWorkshop"//����ȫ��
    #define SAVE_FILE_STR       "AK Files (*.ak)"
    #define AK_FILE_END         ".ak"
    #define VERSION_NAME        "AKWorkShop"
    #define PRO_TYPE            "AK-070AS"
    #define AK_SAMKOON          "@@@SAMKOON###"//�Կ����б�ע
#elif(CURRENT_PROJECT == LA_PROJECT)//LA����
    #define SUFFIX              "*.la"//��׺
    #define LOWER_CASE_PRO_NAME "la"//Сд������
    #define CAPITAL_PRO_NAME    "LA"//��д������
    #define PRO_FULL_NAME       "LAWorkshop"//����ȫ��
    #define SAVE_FILE_STR       "LA Files (*.la)"
    #define AK_FILE_END         ".la"
    #define VERSION_NAME        "LAWorkShop"
    #define PRO_TYPE            "LA-1070BS"
    #define LA_DEBINUO          "@@@DEBINUO###"//�±�ŵ���б�ע
#elif(CURRENT_PROJECT == AKPLC_PROJECT)//AKP ����
    #define SUFFIX              "*.akp"//��׺
    #define LOWER_CASE_PRO_NAME "akp" //Сд������
    #define CAPITAL_PRO_NAME    "AKP" //��д������
    #define PRO_FULL_NAME       "AKWorkshop"//����ȫ��
    #define SAVE_FILE_STR       "AKP Files (*.akp)"
    #define AK_FILE_END         ".akp"
    #define VERSION_NAME        "AKWorkShop"
    #define PRO_TYPE            "AK-070AS"
    #define AK_SAMKOON          "@@@SAMKOON###"//�Կ����б�ע
    #define AKPLC               //һ���
#endif

/********************************************************************
  ���ã������
  ���ߣ�֣����
  ʱ�䣺2010-10-28
********************************************************************/
#define MAX_SCRNCNT 1000 //��������

/* QGraphicsItem::UserType */
#define Qt_USER_TYPE_BASE 65536
#define AK_CURRENT_VERSION 3457

#define VERSION_NUM         "-V1.0.2"//�˴���Ҫ�޸�

#define SWITCH_BACK_TYPE    1000   //�������ֿ�������backitem
#define MIN_ITEM_SIZE       1//item���õ���Сֵ

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
    SAM_DRAW_GROUP_SWITCH       = 10,//��������
    SAM_DRAW_GROUP_CHART        = 11,//ͼ��
    SAM_DRAW_GROUP_VALUE        = 12,//��ֵ��ʾ
    SAM_DRAW_GROUP_TREND        = 13,//����ͼ
    SAM_DRAW_GROUP_GROUPDATA    = 14,//����Ⱥ��
    SAM_DRAW_GROUP_IMAGE        = 15,//ͼƬ��ʾ
    SAM_DRAW_GROUP_ASCII        = 16,//ascii��ʾ
    SAM_DRAW_GROUP_TIME         = 17,//ʱ����ʾ
    SAM_DRAW_GROUP_ALARMITEM    = 18,//������ʾ�ؼ�
    SAM_DRAW_GROUP_ALARMBAR     = 19,//��̬������
    SAM_DRAW_GROUP_HISALARMITEM = 20,//��ʷ������ʾ�ؼ�
    SAM_DRAW_GROUP_FLOW         = 21,//������
    SAM_DRAW_GROUP_ANIMATION    = 22,//����
    SAM_DRAW_GROUP_KEY          = 23,//�������
    SAM_DRAW_GROUP_DYNRECT      = 24,//��̬����
    SAM_DRAW_GROUP_DYNCIRCLE    = 25,//��̬Բ
    SAM_DRAW_GROUP_DROPDOWN     = 27,//����ѡ��ť
    SAM_DRAW_GROUP_STATICTEXT   = 28,//��̬�ı�
    SAM_DRAW_GROUP_RECIPE       = 29,//�䷽ѡ����
    SAM_DRAW_GROUP_RECIPESHOW   = 30,//�䷽��ʾ��
    SAM_DRAW_GROUP_CALIBRATION  = 31,//�̶�
    SAM_DRAW_GROUP_HISTORYDATE  = 32,//��ʷ������ʾ��
    SAM_DRAW_GROUP_SLIDER       = 33,//������/������
    SAM_DRAW_GROUP_STATICPIC    = 34,//GIF��ʾ��
    SAM_DRAW_GROUP_MESSAGE      = 35,//��Ϣ��ʾ��
    SAM_DRAW_GROUP_TABLE        = 36,//���
    SAM_DRAW_GROUP_TEXTBOARD    = 37,//���԰�
    SAM_DRAW_GROUP_MFBTN        = 38,//�๦�ܰ�ť
    SAM_DRAW_GROUP_COMBOBOX     = 39,//������
    SAM_DRAW_GROUP_XYTREND      = 40,//XY����ͼ
    SAM_DRAW_GROUP_USER		= 100,//�Զ������

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
    PIC,          //ͼƬ
    LIBRARY,      //ͼ��
    USERDEFINE,   //�û��Զ���ͼ��
    NO_PIC,       //û��ͼƬ
};


struct TextProp
{
    QString sfont;//����
    QString text;//�ı�
    int size;//�����С
    QColor color;//�ı�ɫ
    int showProp;//��˸�����壬���壬�»��ߣ�����
};
typedef struct TextProp ST_TEXT_PROP;
typedef QVector<QVector<ST_TEXT_PROP > > textProList;
enum FLICK_TYPE
{
	NO_FLICK,          //����˸
	FLICK_TEXT,      //�ı���˸
	FLICK_SHOW,   //�ؼ�����
	FLICK_STATUS	//״̬�л�
};
struct PicProp
{
    EITEM_TYPE bLib;//��ͼ�⻹���ⲿͼƬ 0��ʾ���ⲿͼƬ 1��ʾ��ͼ��

    QString path;//·��
	FLICK_TYPE eFlick;//��˸����
    int nAlpha;//͸����
	QColor color;//����ɫ
};
typedef struct PicProp ST_PIC_PROP;
typedef QVector<ST_PIC_PROP > picProList;

typedef struct
{
    QMap<QString, QString> mLibPath;
    QMap<QString, QSizeF> mLibSize;
}ST_LIBPATH;

/*******************************************************************
Group�б���NAME���Ե�key
������GROUP ͨ��setData(GROUP_NAME_KEY,name)���������ϵ�����
*******************************************************************/
#define GROUP_NAME_KEY 66535

//��dataλ�ñ�����Ͽؼ���������������ͬ�ڻ���item���͵�type
//�� keyֵΪ66536 ��data��������Ͽؼ�����������
#define GROUP_TYPE_KEY 66536
//����datalist��data��keyֵ
#define GROUP_DATALIST_KEY 66537
//QPixmapItem ����ͼƬ��data����KEYֵ
#define PIC_SAVE_KEY 66538
//QPixmapItem ˢ�¼��������ڵ�data��
#define  PIC_COUNT_KEY 66539
//QPixmapItem ����boundrect���ڵ�data��
#define PIC_RECT_KEY 66540
#define ITEM_ID_KEY 66541     //�ؼ�ID��Key
#define GROUP_RECT_KEY 66542

// ���º궨������Ͽؼ�������ֵ

#define GROUP_TYPE_BITBTN 10 // ��λ��ť

#define GROUP_TYPE_BITLAMP 14//λָʾ��
#define GROUP_TYPE_WORDBTN 11//�Ӱ�ť
#define GROUP_TYPE_SCREENBTN 12//���水ť
#define GROUP_TYPE_FUNCTIONBTN 13//���ܰ�ť
#define GROUP_TYPE_WEEKBTN  24 //���ڰ�ť
#define GROUP_TYPE_DYNCIRCLE  30 //��̬Բ
#define GROUP_TYPE_DYNRECT  31 //��̬����
#define GROUP_TYPE_MFUNCTION  39 //�๦��
#define GROUP_TYPE_MULSTATELAMP 15//��״ָ̬ʾ��
#define GROUP_TYPE_MULSTATEBTN  16//��̬��ť
#define GROUP_TYPE_PICTUREDISPLAY 26//ͼƬ��ʾ��
#define GROUP_TYPE_PICTUREMOVE   35  //ͼƬ�ƶ�

#define GROUP_TYPE_NUMDISPLAY 17//��ֵ��ʾ
#define GROUP_TYPE_NUMENTRY 18//��ֵ����
#define GROUP_TYPE_ASCIIDISPLAY 19//ASCII����ʾ
#define GROUP_TYPE_ASCIIENTRY 20//ASCII������
#define GROUP_TYPE_BARGRAPH 21//��״ͼ
#define GROUP_TYPE_TIMEDISPLAY 22//ʱ����ʾ
#define GROUP_TYPE_DATEDISPLAY 23//������ʾ

#define GROUP_TYPE_ALARMCONTROL 32//������ʾ��
#define GROUP_TYPE_DYNALARMBAR 33//��̬������
#define GROUP_TYPE_HISALARM 34//��ʷ������ʾ��
#define GROUP_TYPE_METER 36//�Ǳ�
#define GROUP_TYPE_FLOWBLOCK 40//������

#define GROUP_TYPE_MSGDISPLAY 104//��Ϣ��ʾ
#define GROUP_TYPE_STATICPIC 100//��̬ͼƬ
#define GROUP_TYPE_GIFPIC 101//GIFͼƬ
#define GROUP_TYPE_PIE 102   //����ͼ
#define GROUP_TYPE_STEPING 103   //������ť

#define GROUP_TYPE_CHART  200    //ͼ��
#define GROUP_TYPE_VALUE  201    //������ʾ
#define GROUP_TYPE_TABLE 105   //���
#define GROUP_TYPE_SCALES 106   //�̶�
#define GROUP_TYPE_STATICTEXT 107  //��̬�ı�

#define GROUP_TYPE_TRENDCHART 108  //����ͼ
#define GROUP_TYPE_XYTRENDCHART 109  //XY����ͼ
#define GROUP_TYPE_HISTRENDCHART 110  //��ʷ����ͼ
#define GROUP_TYPE_HISDATAALARM 111  //��ʷ������ʾ��

#define GROUP_TYPE_SINGLESELECT 112  //��ѡ��ť
#define GROUP_TYPE_COMBOBOX 113  //������
#define GROUP_TYPE_SLIDER 114  //����ģ��������
#define GROUP_TYPE_ANIMATE 115  //����
#define GROUP_TYPE_MESSAGEBOARD 116  //���԰�

#define BASEITEM_TYPE_ROUNDEDRECT 117  //Բ�Ǿ���
#define BASEITEM_TYPE_ARC 118  //����
#define GROUP_TYPE_DATAGROUPDISPLAY 119  //����Ⱥ����ʾ
#define GROUP_TYPE_TIMER 120  //��ʱ��
#define GROUP_TYPE_ASCII_KEYBOARD 121  //ASCII����

#define GROUP_TYPE_RECIPE_CHOICE 150  //�䷽ѡ����
#define GROUP_TYPE_RECIPE_DISPLAY 151 //�䷽��ʾ��

#define GROUP_TYPE_OPERATE_RECORD 152 //������־��ʾ����edit by panfacheng
#define GROUP_TYPE_VARIBLE 153 //������edit by panfacheng

#define LIBRARY_LIB_GROUP 198  //ͼ�����
#define LIBRARY_PIXMAP_GROUP  200 //ͼƬͼ��
#define USER_DEFINE_GROUP 199  //�û��Զ������

#define DIGIT_ALARM_NUM 64  //��λ�����ĸ���
#define ANALOG_ALARM_NUM 64  //��ȱ����ĸ���

#define INITMARCO_NUM 16    //��ʼ�������
#define GLOBALMARCO_NUM 64  //ȫ�ֺ�����

//���̹�����
#define TREE_COM_LINK 122  //Com����
#define TREE_HMI_SETTING 123  //��������������
#define TREE_HMI_STATE 124  //HMI״̬
#define TREE_PLC_CONTROL 125  //PLC����
#define TREE_CLOCK 126  //ʱ��
#define TREE_FILE_PROTECT 127  //�ļ�����
#define TREE_HMI_PROTECT 128  //HMI����
#define TREE_DIGIT_ALARM 129  //��λ����
#define TREE_ANALOG_ALARM 130  //��ȱ���
#define TREE_RECIPE 131  //�䷽
#define TREE_DATA_TRANSFORM 132  //���ϴ���
#define TOOLBAR_OPENLIBRARY 133  //��ͼ��
#define TOOLBAR_SAVELIBRARY 134  //����ͼ��
#define TREE_HISDATA_RECORD 135 //��ʷ�����ռ���
#define GLOBAL_HELP_KEY 136 //�����ĵ�����ʼҳ��
#define TREE_LANGUAGE 137 //����
#define GLOBAL_MACRO_KEY 138 //ȫ�ֺ�
#define INIT_MACRO_KEY 139 //��ʼ����
#define MACRO_START_KEY 140 //������ָ��Ի���
#define MACRO_EDIT_KEY 141 //��ָ��༭
#define TABLE_ITEM_MOVE 142
//����
#define TREE_COM_DEAL 300  //ComЭ��
#define TREE_SHOWSET 301 //��ʾ����
#define TREE_IMPOWER 302 //��Ʒ��Ȩ
#define TREE_MODELCHOICE 303 //����ѡ��
#define TREE_DATACONTROL 304 //���ݿ���
#define TREE_USERPOWER 305 //�û�Ȩ��
#define TREE_DOWNSET 306 //��������
#define TREE_DOWNPOWER 307 //���籣��
#define TREE_ALARMLOGIN 308  //������¼

//���洰��
#define TREE_SCREENS 143 //����
#define TREE_WINDOWS 144 //����

#ifndef COMPRESSFILE_PATH
#define COMPRESSFILE_PATH "/samkoon/samhmi3.4/configuration/project.bin"
#define SIMFILE_PATH "/samkoon/samhmi3.4/configuration/prj.bin"
#define SHMFILE_PATH "/samkoon/samhmi3.4/configuration/samkoon.shm"
#define DRIVER_DIR "/samkoon/samhmi3.4/driver/"
#endif

#define PICTURE_PATH "Picture/"          //���ͼƬ����·��
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

        if (input.contains(' '))//�ո�
            return Invalid;

        if(0 == d)
        {
            if (input.contains('.'))//�ո�
                return Invalid;
        }
        if (b >= 0 && input.startsWith(QLatin1Char('-')))//���ڵ���0ʱ���븺��
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
