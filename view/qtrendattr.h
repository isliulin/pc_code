#ifndef QTRENDATTR_H
#define QTRENDATTR_H

#include <vector>
#include <qcolor.h>
#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"

using namespace std;

//////////////////�����������////////////////////
typedef enum _CurveType{    //ͼ������
    TypeRealTime = 1,       //ʵʱ
    TypeHistory,            //��ʷ
    TypeDataGroup,          //����Ⱥ������(��Ϊ��2�ֽṹ�幫�����ݿ�����Լ����)
}CurveType;

typedef enum _CurveDataType{  //������������
    Curve16Bin = 1,     //16λBin
    Curve32Bin,     //32λBin
    Curve16BCD,     //16λBCD
    Curve32BCD,     //32λBCD
    Curve32Float,   //32λ����
}CurveDataType;


///////////////////////////////////////////

//////////////////��ɫ����////////////////////
typedef enum _LineStyleType{  //����
    LineSolid = 1,      //ʵ��
    LineDash,       //�̻���
    LineDotted,     //����    
    LinePoint,      //�㻮��
    Line2Point,     //2�㻮��
}LineStyleType;

typedef struct __ColorGroupInfo__
{
    LineStyleType   eLineType;      //����
    short           nChannelNum;    //ͨ����
    short           nLineThickness; //�������
    QColor          nDisplayColor;  //��ʾ��ɫ
}ColorGroupInfo;
////////////////////////////////////////////

//////////////////��ʾ����/////////////////////
typedef enum _DisplayConditionType{  //��ʾ����
    DisplayKeep = 1,    //������ʾ
	DisplayOn,      //λONʱ��ʾ
    DisplayOff,     //λOFFʱ��ʾ

}DisConType;

typedef struct __DisplayGroupInfo__
{
    DisConType   eDisplayCondition; //��ʾ����
    short        nDisplayNum;       //��ʾͨ����
    Keyboard     KeyAddr;           //��ʾON/OFF��ַ
}DisplayGroupInfo;

typedef struct __ChannelGroupInfo__
{
	CurveDataType   m_eDataType;	//��������
	short           m_nNumOfChannel;	//ͨ����
    QString         m_sGroupName;//�ɼ������ƣ���������Ⱥ���ʱ��ʹ��
	double          m_nSourceMin;	//���뷶Χ��Сֵ
	double          m_nSourceMax;	//���뷶Χ���ֵ
	double          m_nDisplayMin;	//��ʾ������Сֵ
	double          m_nDisplayMax;	//��ʾ�������ֵ

	short           nLineThickness; //�������
	QColor          nDisplayColor;  //��ʾ��ɫ
	LineStyleType   eLineType;      //����
	DisConType   eDisplayCondition; //��ʾ����
	Keyboard     KeyAddr;           //��ʾON/OFF��ַ
}ChannelGroupInfo;
///////////////////////////////////////////

////////////////////ʱ������//////////////////////
typedef enum _DateType  //���ڸ�ʽ
{
    YMD_ONE = 1,        //YYYY/MM/DD
    YMD_TWO,        //YYYY.MM.DD
    YMD_THREE,      //YYYY-MM-DD
    MDY_ONE,        //MM/DD/YYYY
    MDY_TWO,        //MM.DD.YYYY
    MDY_THREE,      //MM-DD-YYYY
    DMY_ONE,        //DD/MM/YYYY
    DMY_TWO,        //DD.MM.YYYY
    DMY_THREE,      //DD-MM-YYYY
}DateType;

typedef enum _Time_Type //ʱ���ʽ
{
    TIME_HM1 = 1,   //hh:MM
    TIME_HMS1,  //hh:mm:ss
    TIME_HM2,   //HH-MM
    TIME_HMS2,  //HH-MM-SS
}TimeType;

typedef enum _TimeUnitType //X��ʱ�䵥λ
{
    //UNIT_SECOND,  //��
    UNIT_MINUTE = 1,    //��
    UNIT_HOUR,      //ʱ
    UNIT_DAY,       //��
    UNIT_MONTH,     //��
    UNIT_YEAR,      //��
}TimeUnitType;

typedef enum _FontType //��������
{
    FONT_SONGTI = 1,    //����
    FONT_SHILIANG,  //ʸ������
}FontType;

typedef enum _TxtAttrType //�ı�����
{
    TXT_CUTI = 1,   //����
    TXT_XIETI,  //б��
}TxtAttrType;

typedef enum _CurveStartType //�ɼ�ʱ��
{
    START_NEAR = 1,    //���
    START_FROMTO,       //��...��...
    START_DISKBEGIN,      //�Ӵ������ݿ�ʼ
    START_ADDR,        //ѡ���ַ
}CurveStartType;
/////////////////////////////////////////

class QTrendAttr:public QVisableItem//public QItemGroup//
{  
public://�������,ע�������saveʱ�������ȱ��棬��Ϊm_nCurChnnelNum������ݵ�������
    bool        m_bIsAll;           //����ȫ��
    CurveType   m_eTableType;       //ͼ������
    QString     m_sGroupNum;        //��ǰ����
    short       m_nCurChnnelNum;    //��ǰͨ����
    short       m_nChnnelBegin;     //��ʼͨ����
    int         m_nTotalTrendNumber;//������ͨ����
	QList<int> m_Channels; //����ѡ�е�ͨ����

	double          m_nDisplayMin;	//��ʾ��Сֵ
	double          m_nDisplayMax;	//��ʾ���ֵ
    QVector<ChannelGroupInfo> m_vecChannelGroups;//����ͨ�������������

public://��ʾ������
    bool    m_bSelectVertMinor;	//�Ƿ���ʾ��ֱ�α��
    bool    m_bSelectHorMinor;	//�Ƿ���ʾˮƽ�α��
    bool    m_bMainVer;         //�Ƿ���ʾ��ֱ�����
    bool    m_bMainHor;         //�Ƿ���ʾˮƽ�����
    short   m_nDataSample;	//����������
    short   m_nScrollSample;	//����������
    short   m_nVertMajorScale;	//��ֱ�����
    short   m_nVertMinorScale;	//��ֱ�α��
    short   m_nHorMajorScale;	//ˮƽ�����
    short   m_nHorMinorScale;	//ˮƽ�α��
    vector<DisplayGroupInfo> m_vecDisplayGroups;//����ͨ�������������

public://��ɫ�Ի���Ҫ�洢������
    bool   m_bGrade;            //�Ƿ���Ҫ����
    QColor m_nVerColor;         //ˮƽ������ɫ
    QColor m_nHorColor;         //��ֱ������ɫ
    QColor m_nBoradColor;	//�߿���ɫ
    QColor m_nScaleColor;	//�����ɫ
    QColor m_nGraphColor;	//ͼ������ɫ
    int m_alpha;//ͼ����͸����
    vector<ColorGroupInfo> m_vecGroupColor;//����ͨ����ɫ����

public://ʱ����ʾ
    //TimeUnitType    m_eTimeUnit;    //X��ʱ�䵥λ
    TimeType        m_eTimeFormat;  //ʱ���ʽ
    DateType        m_eDateFormat;  //���ڸ�ʽ
    FontType        m_eFontType;    //��������
    TxtAttrType     m_eTxtAttr;     //�ı�����
    CurveStartType  m_eStart;       //����ʱ��ɼ���ʽ
    bool            m_bXMarked;     //�Ƿ�X���ע
    short           m_nFontSize;    //�����С
    QColor          m_nMarkedColor; //��ע��ɫ
    int             m_nTimeLen;     //���ʱ��
    TimeUnitType    m_eTimeUnitNear;//���ʱ�䵥λ
    QDate           m_dFromDate;    //��ʼ����
    QTime           m_tFromTime;    //��ʼʱ��
    QDate           m_dToDate;      //��ֹ����
    QTime           m_tToTime;      //��ֹʱ��
    Keyboard        m_kbFrom;       //��ʼʱ���ַ
    Keyboard        m_kbTo;         //��ֹʱ���ַ
    bool            m_bDateFormat;  //�Ƿ���ʾ���ڸ�ʽ
    bool            m_bTimeFormat;  //�Ƿ���ʾʱ���ʽ

public:
    QTrendAttr(QGraphicsItem *parent = 0);
    ~QTrendAttr();
    QString  getItemName();

public:
    virtual int GroupType();                //�ؼ����� λ���� �ֿ���
    virtual QTrendAttr *Clone();            //����item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count,int index); //�����ʱ�򱣴�item�����ݿ�
    virtual void save(QDataStream &stream); //��item����������
    virtual void load(QDataStream &stream); //������������item
	QVector<ADDRPRO> getAllItemAddr();
	void sampChanged(QString oldName,QString newName,int sampType);

public:
    QVector<ADDRPRO> kb;
};

#endif // QTRENDATTR_H
