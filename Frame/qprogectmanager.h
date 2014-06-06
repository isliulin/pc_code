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
    LEFT_TO_RIGHT       = 0x01, //������
    UP_TO_DOWN,                 //���ϵ���
    RIGHT_TO_LEFT,              //���ҵ���
    DOWN_TO_UP,                 //���µ���
    CLOCK_WISE,                 //˳ʱ��
    COUNTER_CLOCK_WISE,         //��ʱ��
    NOT_MOVE ,                  //���ƶ�
    OTHER_MOVE_DERECT
}ARRAY_ORDER_A;*/

enum MSG_TYPE
{
    MSG_NORMAL = 0,     //����
    MSG_WARNING,        //����
    MSG_ERROR           //����
};

enum DATA_TYPE
{
    BIT_1            = 0x01,        // λ
    POSITIVE_INT_16 ,//= 0x02,         // 16λ����
    POSITIVE_INT_32 ,//= 0x03,         // 32λ����
    INT_16 ,         //= 0x04,         // 16λ������
    INT_32 ,         //= 0x05,         // 32λ������
    BCD_16,          // = 0x06,        // 16λBCD��
    BCD_32,          // = 0x07,        // 32λBCD��
    FLOAT_32 ,       // = 0x08,        // 32λ������
    ASCII_STRING ,   //= 0x09,         // ASCII��
    OTHER_DATA_TYPE  = 0x0a,
    UNICODE_STRING   = 0x0F,           // unicode�ַ���
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
        OBJ_ITEM = 1,//item����
	OBJ_HISTORYDATA,//��ʷ����
	OBJ_ALARM,// ����
	OBJ_MACRO,//��
	OBJ_RECIPE,//�䷽
	OBJ_SYSPRARM,//ϵͳ����
    OBJ_REALTIME_DATA,//ʵʱ���ݲɼ�
	OBJ_OTHER//����
}E_OBJ_TYPE;

/*������Ϣ�б�*/
typedef struct serialPort{
    int BAUD_RATE ;                // ������
    int PARITY_TYPE ;              // 1:NONE(��), 2:EVEN(żУ��), 3:ODD(��У��)
    int DATA_BIT ;                 // ����λ
    int STOP_BIT ;                 // ֹͣλ
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
	QString sModelName;  //Э�������
	QStringList regs;  //��ַ
        QStringList sBitregs;//λ��ַ
        QStringList sWorldregs;//�ֵ�ַ
        QStringList sDworldregs;//˫�ֵ�ַ
	//Ĭ��ֵ
	int	nPlcNo;	//Plcվ��
	int	nReceiveTimeout;	//���ճ�ʱ��ms��
	int	nMaxRWLen;	//����д����
	int	nRetryTime;	//���Դ���
    int	nIntervalTime;//֡���ʱ��
    int nCycleTime;//��Сͨ������
    SERIAL_PORT_PROP mPort;//������Ϣ
    E_PORT_TYPE ePorttype;//��Э��֧�ֵĽӿ�����

}PLC_MODEL;

typedef struct _factory{
	QString sFactoryName;  //��������
	QVector<PLC_MODEL> models;//��֧�ֵĸó���PLC
}PLC_FACTORY;

//Э������
typedef struct _stProtocol
{
    QString	sName;	//�û��趨������ �û�����������
    QString sFactoryName; //Э�������ĳ������� ���ɱ䣬���ļ�ȡ��
    QString sProtocolName;//Э�����ơ����ɱ䣬���ļ�ȡ��
    int	nPlcNo;	//Plcվ��
    int	nReceiveTimeout;	//���ճ�ʱ��ms��
    int	nMaxRWLen;	//����д����
    int	nRetryTime;	//���Դ���
    int	nIntervalTime;//֡���ʱ��
    int nCycleTime;//��Сͨ������
    PLC_MODEL mPlc;  //���ļ�ȡ�õ�PLC����
    QString ip;
    int port;
    bool bIsTcpProtocol;//�Ƿ�TCPЭ��
}stProtocol;

//��������
typedef struct _connect
{
	int	id; //���ӱ��
	QString sConnectName;//��������
	int	eConnectPort;//���Ӷ˿�
	bool bUseRelationPort;//�Ƿ�ת��
	int	eRelationPort;//ת�����Ķ˿�
        int     bMasterScreen;	   //Ϊ1����ʾ��������Ϊ0����ʾ�Ǵ���
        int     bConnectScreenPort;//1�����Ӵ�����   0������PLC��
        int     nSlaveScreenNum;   //��͸����������1-20
	int	nScreenNo;//������ţ���������վʱʹ��
	int	nBaudRate;//������
	int	nDataBits;//����λ��
	int	nCheckType;//У������0:NONE, 1:EVEN, 2:ODD
	int	nStopBit;//ֹͣλ
	QString sIpAddr;//IP��ַ
	int	nNetPortNum;//����˿ں�

	QVector<stProtocol> vProtocols;//Э��
}stConnect;

typedef struct _stAddrCompileParaments
{
    E_OBJ_TYPE eType;//��ַ����
    int itemId;//����item��id ��������������
    int addrNum;//�õ�ַ�����е����
    int id;//�������ַ���id
    READ_WRITE_COM_TYPE eRWtype; //��д����
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

    quint8  nConnectType;         //�����ͺ����ڲ��洢����com1��
    quint8  nPlcRegTypeIndex;     //PLC�Ĵ���X��Y��T��C�ȵ�����
    quint8  nPlcStationIndex;     //PLCվ��
    quint8  nAddrType;            //��ַ���� 0: bit, 1:word
    QString sShowAddr;            //��ַ�����ַ����硰X123��
    QString sPlcAddrValue;        //plc�Ĵ�����ֵַ�硰123����
    QString sPlcRegTypeStr;       //plc�Ĵ�����X������Y����
    QString sPlcName;             //��ַʹ�õ�Э������
    int     Length;               //������ַ�ĳ���

    friend QDataStream &operator<<(QDataStream &stream, Keyboard &keyBoard);
    friend QDataStream &operator>>(QDataStream &stream, Keyboard &keyBoard);
};

typedef struct __ADDRPRO__{
    Keyboard* pAddr;
    QString   str;
    short     type;//��ַ���ͣ�λ��ַΪ0���ֵ�ַΪ1
    short     nRecipe;//�䷽�ţ������������䷽��ַ��0Ϊ�����䷽������0Ϊ�䷽��
}ADDRPRO;

typedef struct __TEXTPRO__{
    QString sCtrlName; //�ؼ�����
    QVector <int>iLanguage;//������

    QVector<int>vStatus;//ֵΪ״ֵ̬
    QVector<QString> vMsg;
    QVector<QString>vText;//ֵΪ�ı�����
  //  QMap<int,QString>mText;//��һ��ֵΪ״ֵ̬���ڶ���ֵΪ�ı�����
}TEXTPRO;

typedef enum addrCheckErrorInfo{
	ADDR_CORRECT = 0x01,               //��ַ��ȷ
	IS_BIT_ADDR = 0x02,                //��λ��ַ
	IS_WORD_ADDR = 0x03,               //���ֵ�ַ
	ADDR_FORMAT_ERROR = 0x04,          //��ַ��ʽ������Ҫ��û�а��ռĴ����ĸ�ʽ�������ռĴ���������
	ADDR_OUT_BOUND = 0x05,             //��ַԽ��
	ILLEGAL_REG = 0x06,                //�Ƿ��Ĵ�������
	ILLEGAL_VALUE = 0x07,              //�Ƿ���ֵַ����Ҫֵָת����int����ȷ
	ADDR_STRING_NULL = 0x08,			//��ַΪ��
	INVALID_CONNECT = 0x09,				//������
	ADDR_OTHER_ERROR                   //δ֪����
}ADDR_CHECK_ERROR_INFO;
enum eSwitchType
{
    BIT_SWITCH,      //λ����
    WORD_SWITCH,     //�ֿ���
    SCENE_SWITCH,    //���濪��
    PECULIAR_SWITCH,  //���⿪��
	INDICATOR_SWITCH  //ָʾ��

};
typedef enum eSwitchType SWITCH_TYPE;

enum eMonitorType
{
    NONE,     //������
    BIT_MONITOR,   //˫̬
    POLY      //��̬
};
typedef enum eMonitorType MONITOR_TYPE;

enum eBitOperType
{
    SET_BIT, //��λ
    RESET,   //��λ
    JOG,     //�㶯
    REPLACE, //����
};
typedef enum eBitOperType BIT_OPER_TYPE;

enum eWordOperType
{
    INPUT_VALUE,  //������ֵ
    ADD,          //��
    MINUS,        //��
    ADD_LOOPER,   //������
    MINUS_LOOPER, //������
};
typedef enum eWordOperType WORD_OPER_TYPE;



enum eSceneType
{
    OPEN,       //�򿪻���
    BACK,       //��ǰһ����
    CLOSE,       //�رմ���
    CLOSE_OPEN,       //�رյ�ǰ���ڲ��򿪻���
    RETURN,           //����ǰһ����
};
typedef enum eSceneType SCENE_OPER_TYPE;


enum ePeculiarType
{
    BACKLIGHT,       //�����ƿ���
    RESET_HMI,           //ϵͳ����
    SET_SCENE_TIME,  //��������ʱ��
    SET_SYSTEM_TIME, //����ϵͳʱ��
    CHANGE_USER,     //�л���ǰ�û�
    USER_MANAGE,     //�û�����
    TOUCH_SOUND,     //������������
    COPYRIGHT,       //��Ʒ��Ȩ
    CHANGE_LANGUAGE, //�����л�
    SCREENSHOT,      //��Ļ��ͼ
    OPER_WINDOW,     //���ڲ���
    FORMULA,         //�������ݲ���
    SAMPLING,        //�䷽����
    ALARM ,           //��������
    EDIT_PASSWORD , //�޸ĵ�ǰ����
    CLOSE_HMI ,      //�ػ�
};
typedef enum ePeculiarType PECULIAR_TYPE;

//���ز�����������
struct bitSwitchPro
{
    Keyboard addr;//λ��ַ
    BIT_OPER_TYPE operType;//��������
    bool  bDown;//ִ�з�ʽ
	bool  bConfirm;//�Ƿ���Ҫ������ȷ��
	int   nTimeout;// ��ȴ�ʱ��
};
struct wordSwitchPro
{
    Keyboard addr;//�ֵ�ַ
    WORD_OPER_TYPE operType;//��������
    DATA_TYPE dataType;//��������
    double value;//����
	bool bCycle;//�ƻ�
	double nMax;//���ֵ
	double nMin;//��Сֵ
    bool bDynamicControl; //wxy ������ֵ��̬����
    Keyboard addrConst; //������ֵ��ַ
};
struct sceneSwitchPro
{
    SCENE_OPER_TYPE operType;//��������
    int     nSlideStyle;     //---�л�Ч��
    QString sceneName;//��������
    bool bLogout;// �л������Ƿ�ע��
};
struct functionSwitchPro
{
    PECULIAR_TYPE operType;//��������
    int functionIndex;//���幦��
    QString windowName;//��������
    bool IsCheckX;//�Ƿ�ѡ��X��Ŵ���С
    bool IsCheckY;//�Ƿ�ѡ��Y��Ŵ���С
};
struct monitorPro
{
    MONITOR_TYPE monitorType;//��������
    bool bBitAddr; //��ַ���ͣ��Ƿ���λ��ַ
    int bitIndex; //�ֵ�λ��
    bool bSameAddr; //���ӵ�ַ�Ƿ�Ͳ�����ַ��ͬ
    Keyboard addr;  //���ӵ�ַ
    DATA_TYPE dataType;//��������
    int count;     //��״̬��
    int valueType; //״̬�л�����
    QVector <double > values;//�Զ���״ֵ̬

};

//Ȩ��ҳ������
struct securityPro
{
    bool enableTouch;//���ô���Ȩ��
    bool enableVisable;//��������Ȩ��

    bool byGroups_T;//����Ȩ�� 1-���û������ 0-��λ����
    bool byGroups_V;//����Ȩ�� 1-���û������ 0-��λ����

    QStringList groups_T;//�������û������ ���п���Ȩ�޵���
    QStringList groups_V;//�������û������ ���п���Ȩ�޵���

    int addrType_T;//������λ���� ��ַ���� 0-λ��ַ 1-�ֵ�ַ
    int addrType_V;//������λ���� ��ַ����

    int bitIndex_T;//������λ���� �ֵ�ַ��λ
    int bitIndex_V;//������λ���� �ֵ�ַ��λ

    int condition_T;//����Ȩ�� ��������
    int condition_V;//����Ȩ�� ��������

    Keyboard address_T;//����Ȩ�� ���Ƶ�ַ
    Keyboard address_V;//����Ȩ�� ���Ƶ�ַ

    bool bNotice;//�����Ƿ�֪ͨ
    Keyboard addrNotice; //֪ͨ��ַ
    int datatype;//���ѡ���ֵ�ַ�Ļ�����������
    //int noticeAddrType; //ֵ֪ͨ�ĵ�ַ����
    double noticeValue;//ֵ֪ͨ

    bool bDelay;//�Ƿ���ʱ����
    int time;//��ѹʱ��
};

typedef struct userLevelProp{
    bool bSelect;       //�Ƿ�ѡ�����û�
    QString sUserName;  //�û�������
    QString sUserPWD;   //�û�������
    bool bUserLevelList[8];  //�û��ȼ�
}USER_LEVEL_PROP;

typedef struct HMIPrinterProp{
    bool   bUsePrinter;     //�Ƿ�����ӡ
    bool   bPrintNo;        //�Ƿ��ӡ���
    bool   bPrintTime;      //�Ƿ��ӡʱ��
    bool   bPrintTimeEx;    //�Ƿ��ӡ��չʱ��
    bool   bPrintStandTime; //�Ƿ��ӡ��׼ʱ��
    bool   bPrintPricesTime;//�Ƿ��ӡ��ȷʱ��
    bool   bPrintDate;      //�Ƿ��ӡ����
    bool   bPrintDateEx;    //�Ƿ��ӡ��չ����
    bool   bPrintCheckError; //�Ƿ��ӡ���ڴ���
    bool   bPrintCharModel;  //�Ƿ��ַ�ģʽ��ӡ
    quint8 nPrinterType;    //��ӡ���ͺ�
    quint8 nDataBit;        //����λ
    quint8 nStopBit;        //ֹͣλ
    quint8 nCheckOe;        //��żУ��
    int    nPrintPort;      //��ӡ���˿�
    int    nPrintBaud;      //������
    QStringList sBackupForNewVer;    //Ϊ�Ժ��ҵ�����ı�������
}HMI_PRINTER_PROP;

typedef struct projectProp{
    quint8 nDisplayMode;                   //0:����ˮƽ���У�1������ֱ����
    quint8 nStartScreenIndex;              //��������ID  ��λ��
    quint8 nScreensaverTimer;              //����ʱ�䣬��0���ӵ�60����
    quint8 nFlickerFqc;                    //�ؼ���˸Ƶ��
    bool   bHaveAlarmVoice;                //�Ƿ��б�������
    bool   bHaveTouchVoice;                //�Ƿ��д�������
    bool   bScreensaver;                   //�Ƿ�����
    bool   bLoadInitScene;                 //�Ƿ���س�ʼ��ҳ��
    quint8 nScreensaverIndex;              //��������
    quint8 nLoadSceneIndex;                //��ʼ��ҳ���ID��
    quint8 nLoadSceneTime;                 //���뻭���ʱ�� 1s - 10s
    quint8 nDefautUserId;                  //Ĭ���û���ID��
    quint8 nSetFloatProp;                  //���ø����� 0:�Ǳ�׼��1:���Զ���
    quint8 nSetFloatType;                  //�����������ͣ�0���ǵ�����ǰ��1�Ǹ�����ǰ
    quint8 nNoDataValueFlag;               //ͨ��ʧ��ʱ��ֵ����ı�־
    quint8 nNoDataCharFlag;                //ͨ��ʧ��ʱ�ַ�����ı�־
    quint8 nPicFilePathIndex;              //������Чʱ�Ƿ���ʾ�Զ���ͼƬ��ID��
    bool   bHideMouse;                     //�Ƿ����������
    bool   bTouchInvalidPic;               //������Чʱ�Ƿ���ʾ�Զ���ͼƬ
    bool   bTIPicTransparent;              //������Чʱ�Զ���ͼƬ�Ƿ���Ҫ͸��
    bool   bUseHighLevelPWD;               //�Ƿ�ʹ�����Ȩ������
    bool   bNeedUpLoad;                    //���Ȩ�������Ƿ�֧��������̬
    bool   bAccessOperate;                 //�Ƿ���ҪȨ�޲���
    bool   bNeedUploadCom;                 //�Ƿ���Ҫ������̬
    bool   bUploadComNeedPWD;              //������̬ʱ�Ƿ���Ҫ����
    bool   bAlarmCoruscate;                //��������ʱ�Ƿ���˸����
    //add by Dylan 2011-10-18
    bool   bClearHisAlarm;                 //�Ƿ������ʷ������¼
    bool   bStratScreen;                   //�Ƿ�������ɺ���������
    bool   bClearHisData;                  //�Ƿ������ʷ����
    bool   bDownLoadRecipe;                //�Ƿ������䷽
    //add by Dylan 2011.11.4
    quint8 nHisdataSave;                   //��ʷ���ݴ洢λ��
    quint8 nHisAlarmSave;                  //��ʷ�����洢λ��
    quint8 nScreenPictureSave;             //��Ļ��ͼ�洢λ��
    //add by Dylan 2011.11.7
    quint8 nDownLoadPicCheck;              //�Ƿ�ת��ͼƬ��ʽ
    int nSceneWidth;                       //��Ļ�Ŀ��
    int nSceneHeight;                      //��Ļ�ĸ߶�
    int nDownLoadType;                     //���ط�ʽ 0-USB 1-��̫����
    //add by Dylan 2011.11.4
    QString sHisdataPath;                  //��ʷ���ݴ�ŵ�ַ
    QString sHisAlarmPath;                 //��ʷ������ŵ�ַ
    QString sScreenPicturePath;            //��Ļ��ͼ��ŵ�ַ

    QString sPjtFilePath;                  //���̵�·��
    QString sPjtModel;                     //���̵��ͺ�
    QString sHighLevelPWD;                 //���Ȩ�޲���������
    QString sUploadComPWD;                 //������̬ʱ������
    QString sDowndloadIP;                  //ip��ַ ������ ��192.168.1.10��
    QString sPortNO;                       //�˿ں��磺��8000��
    QStringList sTIPicPathList;            //������Чʱ�Զ���ͼƬ��·���б�
    QColor  mTIPicColor;                   //������Чʱ�Զ���ͼƬ��͸��ɫ
    QColor cAlarmBackColor;                //��������ʱ��˸���汳��ɫ
    USER_LEVEL_PROP mUserLevelList[8];     //8���û�������
    HMI_PRINTER_PROP mPrinterProp;         //��ӡ����ص�����
    QStringList sBackupForNewVer;    //Ϊ�Ժ��ҵ�����ı�������
    //at(0)---"0"��ʾĬ�ϲ��ô�������������1����ʾ���������� add by Dylan 2011-12-12
    //at(1)---ϵͳ��������ɫ add by Dylan 2011-12-19
    //at(2)---ϵͳ�����ı���ɫ add by Dylan 2011-12-19
    //at(3)---ϵͳ�������� add by Dylan 2011-12-19
    //at(4)---ϵͳ���������Сadd by Dylan 2011-12-19
    //at(5)---ϵͳ������ʾ��ʽ 0-ʼ����ʾ 1-������ʾ add by Dylan 2011-12-19
    //at(6)---ϵͳ����������λ�� 0-����  1-�ײ� add by Dylan 2011-12-19
    //at(7)---�Ƿ�ʹ��ϵͳ���� add by Dylan 2011-12-19
}PROJECT_PROP;
//+++++
//��������Ľṹ���,����ϵͳ�ı���
typedef enum _ScrDirctionType{  //��Ļ����
    scrHorizontal = 1,          //ˮƽ
    scrVertical,                //��ֱ
}ScrDirType;

//�ĳ�bool����,ȥ���������
/*typedef enum _StandbyMode{      //����ģʽ
    modeScreen = 1,             //�������
    modeLight,                  //���ȱ仯����
}StandbyMode;*/

typedef enum _LightMode{        //��������ģʽ
    LightNull = 1,              //û������
    LightMin,                   //��С����
    //LightHalfCur,               //��ǰ���ȵ�һ��
}LightMode;

typedef enum _DownloadMode{     //����ģʽ
    UsbDownload = 1,            //Usb����
    NetDownload,                //��������
}DownloadMode;

typedef enum _PicSaveMode{      //ͼƬ�����ʽ
    SavePicJPEG = 1,            //JPEG
    SavePicBMP,                 //BMP
}PicSaveMode;

typedef enum _AuthorizeMode{    //��Ȩ��ʽ
    AuthForever = 1,            //������Ȩ
    AuthTime,                   //ʱ����Ȩ
}AuthorizeMode;

typedef enum _AuthTimeSet{      //ʱЧ��Ȩ����
    AUseTime = 1,               //��ʹ��ʱ�����ʱ
    ATimeOut,                   //����ֹ���ڼ���
}AuthTimeSet;

typedef enum _PrinterType{      //֧�ֵĴ�ӡ���ͺ�
    Type_1 = 1,                 //1   WH-E19(쿻�)
    Type_2,                     //2   WH-A5(쿻�)
}PrinterType;

typedef enum _HMIPosType{       //HMIλ��
    HMIHost = 1,                //����
    HMIRemote,                  //Զ��
}HMIPosType;

typedef enum _LinkPortType{     //���ӽӿ�����
    LinkCom1 = 1,               //Com1
    LinkCom2,                   //Com2
    LinkEthernet,               //��̫��
}LinkPortType;

typedef enum _LinkType{         //��������
    LinkTSerial = 1,            //����
    LinkTEthernet,              //��̫��
}LinkType;

typedef struct __UserPermiss__
{
    QString m_strName;          //�û�������
    QString m_strDescrip;       //�û�������
    QString m_strPassword;      //�û�����
}UserPermiss;

typedef struct __Administrator__
{
    QString m_strUser;
    bool    m_bIsAdmin;
}Admin;

typedef struct __GroupPermiss__
{
    QString m_strName;          //�������
    QString m_strDescrip;       //�������
    bool    m_bNeedAdmin;       //�Ƿ���Ҫ����Ա
    QVector<Admin> m_vecMember;  //������û��ĳ�Ա
}GroupPermiss;

typedef struct __BitSenceItem__{
    bool     bReset;             //�Զ���λ
    quint8   nCtlStatus;         //���ƻ����л���״̬
    QString  sCtlSceneId;        //Ҫ���ĵĻ�������
    Keyboard mCtlSceneAddr;      //���Ƹ��Ļ���ĵ�ַ
    bool     bClose;             //wxy�Զ��رգ���������Ч
}BitSenceItem;

typedef struct __GlobalVariable__
{
    //--------����ѡ��
    QString         m_strModelName;     //��������
    ScrDirType      m_eScreenDir;       //��Ļ����
    QString         m_strModelSize;     //��Ļ�ߴ�
    QString         m_strResolution;    //�ֱ���
    QString         m_strColor;         //ɫ��
    QString         m_strUsermemory;    //�û��ڴ�
    QString         m_strNandFlash;     //�洢�ռ�����
    QString         m_strPowersupply;   //�����Դ
    QString         m_strCom1;          //com�ڸ���
    QString         m_strCom2;          //CAN����
    QString         m_strUsb;           //USB
    QString         m_strMaxscreennumber;//��̫��
    int             m_nScreenWidth;     //�ֱ��ʿ�
    int             m_nScreenHeight;    //�ֱ��ʸ�
    //int             model;              //ˮƽ��ֱģʽ
    //������USB��COM��������Ϣ������
    QString         m_strHmiName;       //HMI����

    //--------��ʾ����---------------------------------------
    bool            m_bUseLogo;         //�Ƿ�ʹ������Logo����     
    QString         m_sLogoNum;         //��������Logo�����
    QString         m_strLogoNum;       //Logo����Ŷ�Ӧͼ�ε�·��
    bool            m_bStandby;         //�Ƿ����ô���ģʽ
    bool            m_bStandbyMode;     //������ʽ
    QString         m_sStandbyNum;      //��ǰ���������
    QString         m_strStandbyNum;    //��������Ŷ�Ӧͼ�ε�·��
    LightMode       m_eStandbyLight;    //��������
    int             m_nScreenTime;      //��������ʱ��(��)
    bool            m_bStandbyLogin;    //����ע����¼
    QString         m_sInitNum;         //��ʼ�������ã�����ţ�
    int             m_nRecipeIndex;     //��ǰ�䷽��
    int             m_nRecipeNum;       //��ǰ�䷽��
    int             m_nFlickRate;       //��˸Ƶ��
    bool            m_bLockIcon;        //�Ƿ���Ҫ��ͼ��

    //--------��������---------------------------------------
    bool            m_bTouchVoice;      //�Ƿ�����������
    bool            m_autoLogin;        //�Ƿ�����������
    bool            m_bMultiVisitor;    //�Ƿ�������˷���Զ�̼��
    QString         m_strMonitor;       //�������
    int             m_nMonitorPort;     //Զ�̼�ض˿�

    //--------���ݿ���---------------------------------------
    bool            m_bCurScreenNum;        //�Ƿ�ǰ������
    bool            m_bCurFormulaNum;       //�Ƿ�ǰ�䷽���
    bool            m_bCurLanguageNum;      //�Ƿ�ǰ���Ա��
    bool            m_bWordAddrScreenNum;   //�Ƿ��ֵ�ַ���ƻ����л����
    Keyboard        m_keyCurScreen;         //��ǰ�����ַ���
    Keyboard        m_keyCurFormula;        //��ǰ�䷽��ַ���
    Keyboard        m_keyCurLanguage;       //��ǰ���Ե�ַ���
    Keyboard        m_keyWordAddrScreen;    //�ֵ�ַ���ƻ����л����
    bool            m_bBitSenceExch;        //λ��ַ���ƻ����л�
    QVector<BitSenceItem> m_vecBitSence;    //λ��ַ���ƻ����л��ṹ��

    //--------�û�Ȩ��
    QVector<UserPermiss>    m_vecUser;      //�û���Ϣ
    QVector<GroupPermiss>   m_vecGroup;     //����Ϣ

    //--------��ӡ��---------------------------------------
    PrinterType     m_ePrinter;             //��ӡ��֧���ͺ�

    //--------����������-----------------------------------
    DownloadMode    m_eDownload;            //���ط�ʽ
    short           m_nIp1;                 //IP��ַ
    short           m_nIp2;                 //
    short           m_nIp3;                 //
    short           m_nIp4;                 //
    int             m_nPort;                //�˿ں�
    PicSaveMode     m_ePicMode;             //ͼƬ�����ʽ
    bool            m_bStartHMI;            //���غ�����HMI
    bool            m_bClearData;           //����ʱ�����ʷ����
    bool            m_bClearAlarm;          //����ʱ�����ʷ��������
    bool            m_bWriteFormula;        //����ʱд���䷽
    bool            m_bUpLoad;              //�Ƿ���������
    bool            m_bUploadPassword;      //������Ҫ����
    QString         m_strUploadPassword;    //��������

    //--------���ʼ���---------------------------------
    bool            m_bEncryAccess;         //�Ƿ����÷��ʼ���
    QString         m_strAccessPassword;    //��������

    //--------��Ʒ��Ȩ---------------------------------
    AuthorizeMode   m_eAuthMode;            //��Ʒ��Ȩ��ʽ
    AuthTimeSet     m_eTimeStyle;           //��Ȩʱ�䷽ʽ
    QString         m_strTimeout;
    //ProRightDay     m_vecDayRight[5];       //ʱ����Ȩ
    //ProRightDate    m_vecDateRight[5];       //������Ȩ
    /*typedef struct __ProRightDay__
    {
        bool      m_bIsUse;          //�Ƿ�����
        QString   m_strTimeout;      //��ʱ�����ַ���
        int       m_nUseDay;         //ʹ������
        QString   m_sUseDayPassword; //ʹ����������
    }ProRightDay;
    typedef struct __ProRightDate__
    {
        bool      m_bIsUse;          //�Ƿ�����
        QString   m_strTimeout;      //��ʱ�����ַ���
        QDateTime m_gDateTime;       //����ʱ������
        QString   m_strDate;         //����ʱ����������
    }ProRightDate;*/
    bool      m_bIsUseDay[5];       //�Ƿ�����
    QString   m_strTimeoutDay[5];   //��ʱ�����ַ���
    int       m_nUseDay[5];         //ʹ������
    QString   m_sUseDayPassword[5]; //ʹ����������
    /////////////////////////////////////////////
    bool      m_bIsUseDate[5];      //�Ƿ�����
    QString   m_strTimeoutDate[5];  //��ʱ�����ַ���
    QDateTime m_gDateTime[5];       //����ʱ������
    QString   m_strDate[5];         //����ʱ����������

    //-------------------��������--------------------
    short            m_nLanNum;             //��������
    short            m_nCurLan;             //��ǰ���Ժ�
    QVector<QString> m_vecLanguageNameList; //���������б�

}GlobalVariable;
////////////////////end//////////////////////

typedef struct plcCommunicateProp{
    quint8  nHmiLocation;     //HMIλ�� 0-���� 1-Զ��
    quint8  nConnectNum;      //���ӱ�� com1 or com2
    quint8  nConnectType;     //�������� 0:���ڣ�1����̫����
    quint8  nConnectPort;     //���ӽӿ�-ͨ���ñ�����ʾ�������� 0��com1   1��com2   2����̫��
    quint8  nPlcAddrInterval; //plc������ַ���
    quint8  nDataBits;        //����λ��
    quint8  nCheckType;       //У�鷽ʽ 0:NONE, 1:EVEN, 2:ODD
    quint8  nStopBit;         //ֹͣλ 1-2
    quint8  nRetryTime;       //���Դ���
    quint8  nAddrType;        //��ַģʽ 0����׼ģʽ��1����չģʽ
    quint8  nFwConnectType;    //��͸Ӧ���е����ӷ�ʽ 0Ϊֱ������ 1Ϊ��̫�� ��������
    quint8  nFwFromStationId;  //��͸Ӧ���еĴ�վID
    quint16 nTouchScreenAddr; //��������ַ 0-255
    quint16 nPlcAddr;         //plc��ַ 0-255
    quint16 nCommunicateTime; //ͨ��ʱ�� 0-1024
    quint16 nTimeout1; //��ʱʱ��1 200-65535
    quint16 nTimeout2; //��ʱʱ��2 1-1024
    int     nBandRade;        //������
    QString sConnectName;     //��������
    QString sDiviceType;      //�����ĸ����ҵ��豸
    QString sDiviceModel;     //�豸�ͺ�
    QString sInternetIpAddr;   //ѡ������̫������ʱ���IP��ַ
    QString sInternetPort;     //ѡ������̫������ʱ��Ķ˿ں�
    QString sFwIpAddr;         //��͸Ӧ��������̫������ʱ���IP��ַ
    QString sFwPort;           //��͸Ӧ��������̫������ʱ��Ķ˿ں�
    QStringList sDataBakeup;//���ò���4��
    QStringList sBackupForNewVer;    //Ϊ�Ժ��ҵ�����ı�������
}PLC_COMMUNICATE_PROP;

typedef struct _VarPro
{
    QString varName;//��������
    Keyboard addr;   //��Ӧ�ĵ�ַ
    int dataType;//��������
    int RWPerm;//��д����
    int count; //�������͵ĸ���
    bool bOffset; //�Ƿ����ƫ�Ƶ�ַ
    Keyboard offsetAddr; //��Ӧ��ƫ�Ƶ�ַ
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
    QString sLibName;     //�ű�������
    QString sFucName;    //�ű���������
}INIT_MARO_PROP;       //��ʼ���ű��ṹ��

typedef struct globalMaroProp //edit by zqh
{
    QString sLibName;    //�ű�������
    QString sFucName;    //�ű���������
    int     iRunRate;          //ִ��Ƶ��
    bool  bIfCtrl;               //�Ƿ��ܿش���
    int     iCtrlType;           //�ܿ����ͣ�0-λ�ؼ���1-�ֿؼ�
    Keyboard mCtlAddr;   //���Ƶ�ַ
    int    iValue;                 //ִ������
    int    iScriptCount;        //ִ�д���wxy
}GLOBAL_MARO_PROP; //ȫ�ֽű��ṹ��

typedef struct dataTransferProp{
    quint8 nTriggerType;       //������ʽ 1:��ʱ��2������
    quint8 nTriggerSpace;      //������� 0-20
    quint8 nAddrType;          //0:bit , 1: word, 2:double word
    quint8 nWordBitPos;        //�ֵ���һλ������
    bool bAutomatismOff;    //�Զ���λ
    Keyboard  mTriggerAddr;    //������ַ
    Keyboard  mSourceAddr;     //Դ��ַ
    Keyboard  mTargetAddr;     //Ŀ���ַ
    bool bDynLength;        //�Ƿ�̬����
    Keyboard  mLengthAddr;     //���ȵ�ַ
    QStringList sBackupForNewVer;    //Ϊ�Ժ��ҵ�����ı�������
}DATA_TRANSFER_PROP;

typedef struct historyDataItem{
    quint8 nDataType;             //0-7
    quint8 nDataShowType;         //0:ʮ��������1��ʮ���������� 2:8������
    quint8 nDataLen;              //��λ����0-10
    quint8 nDataPointLen;         //С��λ��
    bool   bZoom;                 //�Ƿ�����
    QString  sAddrName;           //��ַ����
    QString  sZoomStr;            //�����ַ���ֵ
    QString  sOffsetStr;          //ƫ���ַ���ֵ
    QVector<QString > sNameList;  //�����б�ͬʱ��������Ե�����,����������
    QStringList sBackupForNewVer;    //Ϊ�Ժ��ҵ�����ı�������
}HISTORY_DATA_ITEM;

typedef struct historyLogProp{
    bool  bHistoryDataExist;       //��ʷ�����Ƿ����
    bool  bFullStop;               //ȡ���Ƿ�ֹͣȡ��
    bool  bFullNotic;              //ȡ���Ƿ�֪ͨ
    bool  bAutoOff;                //�Զ���λ
    quint8  nSampleType;           //ȡ����ʽ,��ʱ������������
    quint8  nFullNoticPercent;     //ȡ��֪ͨ�İٷֱ� 0-100������ٷ�֮nFullNoticPercent
    quint16  nSampleLen;           //ȡ������ 0-32
    int     nTimeInterval;         //��ʱ���  ��Ϊ��λ
    int     nTriggerTime;          //���㴥��ʱ�� �ڶ��ٷ��Ӵ���
    int     nSampleSize;           //ȡ����С
    QString sHistoryDataName;      //��ʷ��������
    Keyboard mReadAddr;            //��ȡ��ַ
    Keyboard mTriggerAddr;         //������ַ
    Keyboard mFullNoticAddr;       //ȡ��֪ͨ��ַ
    QVector<HISTORY_DATA_ITEM > mSampleList;     //ȡ�����ݵ��б��ܴ�СΪnSampleLen
    QStringList sBackupForNewVer;    //Ϊ�Ժ��ҵ�����ı�������
    //at(0)---�ڴ������� add by Dylan 2011-12-12
}HISTORY_LOG_PROP;

typedef enum _AddrConnectType{  //��ַ���ӷ�ʽ
    addrInside,   //�ڲ���
    addrCom,      //com��
    addrNet       //net
}AddrConnectType;

typedef enum _PlcProType{  //Э��ö��
    plcOne,      //Э��1
    plcTwo,      //Э��2
    plcThree     //Э��3
}PlcProType;

 typedef struct dataAddressItem{
//     AddrConnectType eConnectType;     //��ַ���ӷ�ʽ
//     PlcProType      ePlcProType;      //Э��ö��
//     quint16         nPlcRegIndex;     //PLC�Ĵ���������
     quint16         nAddrNumber;      //ÿ����ַ�ı��,��������ַ
//     int             nPlcStationIndex; //PLC��վ��
//     int             nPlcStartAddr;    //PLC����ʼ��ֵַ
//     int             nAddrLen;         //��ַ�ĳ���
     bool            bZoom;             //�Ƿ����ݴ���
     double             inputMax;         //�ɼ���Χ����
     double             inputMin;         //�ɼ���Χ����
     double             outputMax;         //���̷�Χ����
     double             outputMin;         //���̷�Χ����
     int                decLen;             //С��λ��
     bool               bRound;             //�Ƿ���������
     QString         name;
	 DATA_TYPE dataType;//��������
    Keyboard        keyAddress;       //��Ŷ�Ӧ�ĵ�ַ,��������ַ
}DATA_ADDRESS_ITEM;

typedef enum _SampType{  //������ʽ
    SampTime = 1,       //�̶�ʱ�����
    SampCycle,      //�㶨���ڲ���
    SampControl     //λON���Ʋ���
}SampType;

typedef enum _SampFullType{  //����ȡ������
    SFReplace = 1,     //�滻������
    SFClear,      //����������²���   
    SFStop,       //ֹͣ����
}SampFullType;

typedef enum _SaveMidType{  //�����ý��
    SM_Udisk = 1,     //ý��һ
    SM_CFcard,    //ý���
    SM_SDcard     //ý����
}SaveMidType;

typedef enum _SaveDateType{  //��������ڸ�ʽ
    DateYMD = 1,       //������
    DateMDY,       //������
    DateDMY,       //������
    DateMD         //����
}SaveDateType;

typedef enum _DataType{  //�������������
    DataInt = 1,        //��������
    DataUint,       //�޷�������
    DataHex,        //16����
    DataBCD,        //BCD��
    DataFloat       //������
}DataType;

typedef enum _AlarmCondtion{  //��������
    ALARM_ON = 1,     //ON����
    ALARM_OFF,       //OFF����
    ALARM_VALUE,      //�̶�ֵ����
    ALARM_RANGE,        //��Χ�ڱ���
    ALARM_RANGE_OUT     //������Χ����
}E_ALARM_CONDTION;

typedef struct dataSampling{
    bool         bContiguousAddr;    //�Ƿ��������ĵ�ַ
    bool         bFullNotic;         //�Ƿ�ȡ��֪ͨ
    bool         bAutoReset;         //�Ƿ��Զ���λ
    bool         bSaveToFile;        //�Ƿ񱣴��ļ�
    bool         bAutoSave;          //�Ƿ��Զ�����
    
    int          nSaveHour;          //�Զ�����ʱ����
    bool         bAddrCtlSamp;       //λ��ַ�����Ƿ����
    //bool         bSampTime;          //�Ƿ����Ƶ��ʱ����Ϊ1��
    quint8       nDataLen;           //����λ��
    quint8       nDecimalLen;        //С������
    quint8       nStartHour;         //��ʼ��ʱ��0-23��
    quint8       nStartMinute;       //��ʼ�ķ֣�0-60��
    quint8       nEndHour;           //������ʱ��0-23��
    quint8       nEndMinute;         //�����ķ֣�0-60��
    //quint8       nSampAddrLen;       //�ֵ�ַ��������
    quint8       nDigitLen;          //λ��
    SampType     eSampType;          //������ʽ
    SampFullType eDealSampFull;      //ȡ������ʽ
    SaveMidType  eSaveMedium;        //�����ý��
    SaveDateType eDateShowType;      //���ڸ�ʽ
    
    //int          nTotalSampNum;      //�����������
    int          nSampTime;          //����ʱ��
    int          nSampUnit;          //������λ
    int          nDataSampType;      //ʵʱ,1����ʷ,2
    int          nSampRate;          //������Ƶ��
    int          nSampRateUnit;      //Ƶ�ʵ�λ
    int          nSampTimes;         //��������
    int          nSampCountUnit;     //��������Ƶ��

	bool          bDynTimeRange;     //�Ƿ�̬ʱ�䷶Χ
	bool          bDynSampleRate;     //�Ƿ�̬����Ƶ��
	Keyboard     startTimeAddr;     //��ʼ����ʱ�䣨��ַ��
	Keyboard     endTimeAddr;     //��������ʱ�䣨��ַ��
	Keyboard     dynRateAddr;     //����Ƶ�ʣ���ַ��
    
    Keyboard     strNoticAddrId;     //��ַ֪ͨ�ַ���
    Keyboard     strCtlSampAddrId;   //���Ʋ����ĵ�ַ�ַ���
    
    Keyboard     keyCtlSaveAddr;     //�����ļ��Ŀ��Ƶ�ַ
    bool         bPrint;                //�Ƿ��ӡ
    bool         bPrintDate;            //�Ƿ��ӡ����
    bool         bPrintTime;            //�Ƿ��ӡʱ��

    QVector<DATA_ADDRESS_ITEM>  m_dataTable;  //���ݱ��
}DATA_SAMPLING;

typedef struct wHMIinfoToPlc{
    bool bWCurrSceneId;          //�Ƿ�д��ǰ����ŵ�plc
    bool bWCurrRecipeId;         //�Ƿ�д��ǰ�䷽�ŵ�plc
    bool bWCurrUserId;           //�Ƿ�д��ǰ�û��ŵ�plc
    bool bWCurrLangageId;        //�Ƿ�д��ǰ����������plc
    Keyboard mSceneIdAddr;       //д��ǰ����ĵ�ַ
    Keyboard mRecipeIdAddr;      //д��ǰ�䷽�ŵĵ�ַ
    Keyboard mUserIdAddr;        //д��ǰ�û��ŵĵ�ַ
    Keyboard mLangageIdAddr;     //д��ǰ���������ĵ�ַ
    QStringList sBackupForNewVer;    //Ϊ�Ժ��ҵ�����ı�������
}WRITE_HMIINFO_TO_PLC;

typedef struct sceneCtlByBitProp{
    bool   bReset;                   //�Զ���λ
    quint8 nCtlStatus;           //���ƻ����л���״̬
    quint8 nCtlSceneId;          //Ҫ���ĵĻ����
    Keyboard mCtlSceneAddr;      //���Ƹ��Ļ���ĵ�ַ
    QStringList sBackupForNewVer;    //Ϊ�Ժ��ҵ�����ı�������
}SCENE_CTL_BY_BIT;

typedef struct ctlByPlcProp{
    bool  bCtlRecipeChange;      //���Ƹ����䷽
    bool  bCtlWriteRecipe;       //����д���䷽
    bool  bCtlCurrUserId;        //���Ƹ��ĵ�ǰ�û�
    bool  bWordCtlSceneSwitch;   //�ֿ��ƻ����л�
    bool  bBitCtlSceneSwitch;    //λ���ƻ����л�
    Keyboard mChangeRecipeAddr;  //���Ƹ����䷽�ĵ�ַ
    Keyboard mWriteRecipeAddr;   //����д���䷽�ĵ�ַ
    Keyboard mCtlUserIdAddr;     //���Ƹ��ĵ�ǰ�û��ĵ�ַ
    Keyboard mSceneCtlByWAddr;   //�ֿ��ƻ����л��ĵ�ַ
    QVector<SCENE_CTL_BY_BIT> mSceneCtlByBitList;   //λ���ƻ����л��ĵ�ַ
    QStringList sBackupForNewVer;    //Ϊ�Ժ��ҵ�����ı�������
}CTL_BY_PLC;

typedef struct clockProp{
    bool    bReset;              //�Ƿ��Զ���λ
    quint8  nDataType;           //��������
    quint8  nAddrLen;            //��ַ����
    quint8  nStartType;          //������ʽ 0:��ʱ 1������
    quint16 nTimeInterval;       //ʱ���� 1-255
    Keyboard mCtlAddr;           //���Ƶ�ַ
    Keyboard mTriggerAddr;       //������ַ
}CLOCK_PROP;

typedef struct treeClockProp{
    bool bDownLoadTime;          //�Ƿ�����ϵͳʱ�䵽PLC
    bool bWTimeToPlc;            //�Ƿ�дʱ�䵽PLC
    bool bRTimeFromPlc;          //��PLCʱ����ͬ
    CLOCK_PROP mWTimeToPlc;      //дʱ�䵽PLC
    CLOCK_PROP mRTimeFromPlc;    //��PLCʱ��ͬ��
    QStringList sBackupForNewVer;    //Ϊ�Ժ��ҵ�����ı�������
}TREE_CLOCK_PROP;

typedef struct fileProtectProp{
    bool bNeedFileProtect;       //�Ƿ���Ҫ�ļ�����
    QString sProtectPWD;         //�ļ�����������
}FILE_PROTECT_PROP;

typedef struct HMIProtectSet{
    quint8   nProtectSceneId;    //���������ID
    QString  sUnlockPWD;         //��������
    QDate    mProtectDate;       //��������
    QTime    mProtectTime;       //����ʱ��
    QStringList sBackupForNewVer;    //Ϊ�Ժ��ҵ�����ı�������
}HMI_PROTECT_SET;

typedef struct HMIProtectProp{
    bool  bSelectHMIProtect;     //�Ƿ�ѡ��HMI����
    quint8 nTotalProtectNum;     //��������
    quint8 nCurrentLevel;        //��ǰѡ��ı����ȼ�
    QVector<HMI_PROTECT_SET > mProtectList;   //���������б�
    QStringList sBackupForNewVer;    //Ϊ�Ժ��ҵ�����ı�������
}HMI_PROTECT_PROP;

typedef struct recipeProp{
    bool     bRecipeExist;       //�Ƿ�����䷽
    bool     bWRecipeToPlc;      //�Ƿ�д�䷽��PLC
    bool     bRRecipeFromPlc;    //�Ƿ��PLC�ж��䷽
    bool     bRaddrSameWaddr;    //��ȡ��ַ�Ƿ���д��ַ��ͬ
    quint8   nDataType;          //��������
    quint16  nRecipeTotalNum;    //�䷽���� 0-255
    int      nRecipeLen;         //�䷽����
    int      nLanIndex;        //���Ե�����
    QString  sRecipeName;        //�䷽����
    QString  sDescription;       //����
    QString  sRecMemAddrRange;   //�䷽�����ַ��Χ
    QString  sCurrRecAddrRange;  //��ǰ�䷽��ַ��Χ
    QString  sRecipeRegNum;      //�䷽��żĴ���
    Keyboard mWRecipeAddr;       //д�䷽�ĵ�ַ
    Keyboard mRRecipeAddr;       //���䷽�ĵ�ַ
    QVector<quint8 >  nSourceIdList;      //Դ�䷽���
    QVector<quint8 >  nTargetIdList;      //Ŀ���䷽���
    QVector<QString > sRecipeData;        //�����б�
    QVector<QVector<QString > > sRowHeadName;       //�䷽������ͷ����
    QStringList sBackupForNewVer;    //Ϊ�Ժ��ҵ�����ı�������
}RECIPE_PROP;

//�䷽���� begin
typedef struct
{
    QString sName;//Ԫ������
    QString sAddr;//Ԫ�ص�ַ
    Keyboard  addr;
    QString sAddrType; //��ַ����
    QString  sText;     //Ԫ��ֵ
}ELMENT;

//�䷽�����Ա�
typedef struct
{
   QString sRecipeName;//�䷽����
   short   nLanguageId;//����ID
   QString sRecipeDescri;//�䷽����
   short   nRecipeId;    //�䷽ID
}RECIPELANGUAGE;

typedef struct
{
    short nLanguageId;	        //����id��
    short nRecipeGroupId;	//�䷽��id
    short nElemIndex;	        //�䷽Ԫ�ص�ID
    QString sElemName;	        //Ԫ�ص�����
}RECIPEElEMENT;

typedef struct
{
    QVector <RECIPELANGUAGE> RecipeInfo;//�䷽������Ϣ
    QString sFormulaName;//�䷽����
    QVector<ELMENT> elment;
    int nColum;          //���±�
}FORMULA_ST;

typedef struct
{
    QVector<FORMULA_ST> formula;
    QString   sName;              //�䷽������
    QString   sRecipeGDescri;     //�䷽���������
    int       nRecipeNum;         //һ���䷽������
    int       nRecipeLen;         //һ���䷽�ĳ���
    short     eDataType;          //�䷽����������
    short     nLanguageId;        //�����±�
    bool      bCtlAddr;           //�Ƿ���Ҫ���Ƶ�ַ
    QString   sCtlAddrId;         //���Ƶ�ַ
    Keyboard  addrCtl;            //���Ƶ�ַ
    //bool      bTransRecipe;       //�Ƿ����䷽
    short     eRecipeTransType;   //�䷽���䷽ʽ 1���ɶ�д 2����PLC�� 3��д��PLC
    bool      bCompleteNotic;     //�Ƿ���Ҫ���֪ͨ
    QString   sComNoticAddrId;    //���֪ͨ��ַ
    Keyboard  addrNotic;          //λ���֪ͨ��ַ
    short     eSaveMedia;         //�洢·�� 1���ڲ��洢�� 2��U�� 3:SD��
    bool      bContniu;            //true���� false�漴
    QString   sContniuAddr;        //������ַ
    QVector  < QVector<RECIPEElEMENT> > ElmentName;//Ԫ�ض�������Ϣ

    short int nKeyId;                 //���̱��
    QString   sKeyname;               //��������
    bool      nKeyMark;               //�Ƿ����ü���
    int       nBoardX;              //�Զ���������X
    int       nBoardY;              //�Զ���������Y
}FORMULA_PROP;

//�䷽���� end
typedef struct languageProp{
    quint8 nTotalNum;                      //��������
    QVector<QString > sLanguageNameList;   //���������б�
}LANGUAGE_PROP;



typedef struct digitalAlarmProp{
    quint8  nTypeIndex;         //���͵�����
    quint8  nLanguageId;        //����������
    quint8  nScanInterval;      //ɨ��ʱ���� 0-99
    quint16 nAddrLen;           //��ַ���� 0-512
    quint16 nCurrRowIndex;      //��ǰ��
    QString sAlarmName;         //��������
    Keyboard mReadAddr;         //��ȡ��ַ
    QVector<bool >    bSelect;      //�Ƿ�ѡ��
    QVector<bool >    bOFFSelect;      //�Ƿ�ѡ��
    QVector<QVector<QString > > sMsgList;     //��Ϣ�б�
    QStringList sBackupForNewVer;    //Ϊ�Ժ��ҵ�����ı�������
}DIGITAL_ALARM_PROP;
//��������
typedef struct _stAlarm
{
    int index;
    Keyboard addr;
    int symb;//���� = > <
    double value;
    QStringList messages;
    DATA_TYPE dataType;//��������
    double rangeHigh;
    double rangeLow;
    E_ALARM_CONDTION eCondtion;//�������� ��ON ������OFF���� ���̶�ֵ��������Χ�ڱ�����������Χ����
    bool bOpenScene;//�����Ƿ�򿪴���
    QString sceneName; //��������
    bool bSeneMsg; //�����Ƿ��Ͷ���Ϣ
    QStringList sPhoneNums; //�������Ͷ���ϢĿ��绰����
    bool bAddtoDB;//�����Ƿ���ӵ����ݿ�
    bool bPrint;                //�Ƿ��ӡ
    bool bPrintDate;            //�Ƿ��ӡ����
    bool bPrintTime;            //�Ƿ��ӡʱ��
}stAlarm;
typedef struct AlarmGroup
{
    QString alarmName;
    int addrType;
    DATA_TYPE dataType;//��������
    QVector<stAlarm >alarms;
}ALARM_GROUP;

typedef struct analogAlarmProp{
    quint8  nCurrRowIndex;      //��ǰ��
    quint8  nLanguageId;        //����������
    quint8  nScanInterval;      //ɨ��ʱ���� 0-99
    quint16 nAddrLen;           //��ַ���� 0-32
    QString sAlarmName;         //��������
    Keyboard mReadAddr;         //��ȡ��ַ
    QVector<bool >    bSelect;      //�Ƿ�ѡ��
    QVector<quint8 >  nDataType;    //��������б�
    QVector<double >     nBoundary;    //�����б�
    QVector<QVector<QString > > sMsgList;     //��Ϣ�б�
    QStringList sBackupForNewVer;    //Ϊ�Ժ��ҵ�����ı�������
}ANALOG_ALARM_PROP;


typedef struct _stAddrPrarm{
	QString    sName;   //�豸����
	int        regIndex;//�Ĵ������
	int		   addrValue;//��ֵַ
	int        length;   //��ַ����
	READ_WRITE_COM_TYPE rwPrarm;//��д����
}stAddrPrarm;
//����洢��
typedef struct _stPowerProtect{
    int        startLB;   //��ʼ��ֵַ
    int        lengthLB;//��ַ����
    int		   startLW;//��ʼ��ֵַ
    int        lengthLW;   //��ַ����
}stPowerProtect;

typedef struct __MACRO_LIB__{
    QString libName;
    QStringList funcNames;
}MacroLib;

/**********************************************************
  ������ṹ��
**********************************************************/
typedef struct globalOperateRecord{
    QString    SVarName;   //��������
    int        ibitWord;
    Keyboard   mCtlAddr;   //��ַ
}GLOBAL_VAR_RECORD;

//���������� 13-10-17
typedef struct _VarRecord{
    QString    sVarName;   //��������
    DATA_TYPE mType;//��������
    Keyboard   mAddr;   //��ַ
}VarRecord;

class Schedulers;
class QSamSysParame
{
public:
    QSamSysParame();
    ~QSamSysParame();

public:
    void globalCompile(QSqlDatabase &db,int &count);//ȫ�ֺ�
    void initCompile(QSqlDatabase &db,int &count);//��ʼ����
    void dataSamplingCompile(QSqlDatabase &db,int &count);//���ݲɼ����ݿ�
    void insertSampleAddr(QSqlDatabase &db,int &count,QVector<DATA_ADDRESS_ITEM> m_dataTable,int nGroupId,int sampleType);
    void SystemProcCompile(QSqlDatabase &db,int &count,bool bSimulator);//ϵͳ��������
    void PasswordCompile(QSqlDatabase &db,int &count);//�����
    void LanguageCompile(QSqlDatabase &db,int &count);//���Ա�
    void UserRightCompile(QSqlDatabase &db,int &count);//�û���Ȩ�ޱ�
    void alarmCompile(QSqlDatabase &db,int &count);//������¼����
    void alarmMessagesCompile(QSqlDatabase &db,QStringList msgs,int GroupId,int AlarmIndex);//������Ϣ��
    void connectCompile(QSqlDatabase &db,int &count);//�������ò���
    void protoclCompile(QSqlDatabase &db,QVector<stProtocol> protocols,int nConnectId,int nUserPlcIndex);//����Э�鲿��
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
    //HISTORY_LOG_PROP    m_historyLogData;      //�ɵı������Ժ�Ҫ��
    QVector<DATA_SAMPLING> m_loadDataSampling;   //�µ����ݲɼ�����
    QVector<QString>    m_vecDataSamplingStr;    //ÿ�����ݲɼ�����������

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

    QVector<GLOBAL_VAR_RECORD > m_qvcVarRecord;   //����������
    //���������� 13-10-17
    QVector<VarRecord> m_VarRecord;

    stPowerProtect m_PowerProtect;

    Schedulers *schedulers;
    //QVector<SamDrawScene *> pUserKeyboard_vector;//�û��Զ����������
};


class MsgOutPut //��Ϣ������ڵ�item�ͻ������
{
public:
    QGraphicsItem *pItem; //ɨ���item
    int nSheetIndex;      //�������
};

class AddrMsg //���ַ��Ϣ,���ڵ�ַ���ң���ַһ����ͱ����ַ������ʹ��
{
public:
    QGraphicsItem *pItem; //ɨ���item
    int nSheetIndex;      //�������
    QVector<ADDRPRO> Address;
};

/********************�½����̵����ݷ�װ**************************/
class QNewPro
{
public:
    /************�½�����������½�������ҳ�������*************/
    QString newprowizard_path;//�½���Ŀ��·��
    QString newprowizard_name;//�½���Ŀ������
    QString newprowizard_model;//�½���Ŀ���ͺ�ѡ��
    QString HMI_Name;
    QString newprowizard_showmodel;//�½���Ŀ����ʾ�ͺ�
    QString     newprowizard_showmodel_maxscreennum;//�½���Ŀ���������
    /********************************************************/

    /************�½����������������ҳ�������*************/
    QString  newlinkwizard_connection;//�����򵼵����ӱ��
    QString  newlinkwizard_linkname;//��������
    QString  newlinkwizard_linktype;//��������
    QString  newlinkwizard_linkdevice;//�����豸
    QString  newlinkwizard_linkserver;//���ӷ���
    QString  newlinkwizard_plcaddress;//PLC��������ַ���

    QString sName;	//�û��趨������ �û�����������
    QString sFactoryName; //Э�������ĳ������� ���ɱ䣬���ļ�ȡ��
    QString sProtocolName;//Э�����ơ����ɱ䣬���ļ�ȡ��
    QString proFlag;//Э����������0������1��������̫��
    /******************************************************/

    /************�½�����������½�����ҳ�������*************/
    QString  newscreenwizard_name;//�½����������
    QColor  newscreenwizard_bk;//����ɫ
    QColor  newscreenwizard_frontcolor;//ǰ��ɫ
    int  newscreenwizard_style;//��ʽ
    QString  newscreenwizard_picturepath;//����·��
    bool  ischeck_slience;//Ĭ�ϵ�ѡ��״̬
    bool  ischeck_picture;//ͼƬ��ѡ��״̬
    int   nSeleteType;//Ĭ��ѡ��
    // nNewscreenwizard_style
    /******************************************************/
private:
    friend QDataStream &operator<<(QDataStream &stream, QNewPro *pNewPro);
    friend QDataStream &operator>>(QDataStream &stream, QNewPro *pNewPro);

};//

//wxy ����ģ��״̬
typedef enum _state{         //��ǰģ�����е�״̬
    START_VBOX = 1,            //���������
    VBOX_READY,              //������Ѿ�����
    CONNECT_ADB,              //ͨ��IP��������
    DOWLOAD_FILE,              //���ӳɹ�����ʼ�����ļ�
    RUNNING						//ģ��������
}SIMULAT_STATE;

#endif // QPROGECTMANAGER_H


