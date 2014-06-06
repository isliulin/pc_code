/****************************************************************************************************
  ͼ��item�࣬�̳���QVisableItem
 **************************************************************************************************/

#ifndef CHARTTIEM_H
#define CHARTTIEM_H

#include "qvisableitem.h"
#include "Frame/qprogectmanager.h"

//Բ�Ͱ�Բ�ĽǶȿ�ȵ���Ϣ�ṹ��
struct CIRCLE_TYPE
{
    QPoint FirstPos;       //��һ��Բ�Ķ�������
    QPoint SecondPos;      //�ڶ���Բ�Ķ�������
    int num;                //Բ�ĸ���
    int nRadiu;             //Բ�뾶
    QString FirstColor;     //��һ��Բ�ı���ɫ
    QString SecondColor;    //�ڶ���Բ�ı���ɫ
    QString ScaleColor;    //�̶���ɫ
    int nstartAngle;        //Բ��ʼ�Ƕ�
    int nSpanAngle;         //Բ��Ƕ�
    int nScaleStartAngle;   //�̶ȿ�ʼ�Ƕ�
    int nScaleSpanAngle;     //�̶ȿ�Ƕ�
    int nMainScal;           //���̶���
    int nSubScal;            //�ο̶���
    bool bPoint;             //�Ƿ�ָ��

    short nTransparent;      //�Ƿ�͸��
    bool  bShowFrame;        //��ʾ�߿�
};

//�Ǳ���Ϣ�Ƕȿ����Ϣ�ṹ��
typedef struct METER_STRU
{
    int nMeterType;         //�Ǳ�����
    int nPointType;         //�Ǳ�ָ������ ����
    int nDirection;         //����  0�����ң�1������
    int nMainScal;          //���̶���
    int nSubScal;           //�ο̶���
    int nstartAngle;         //Բ��ʼ�Ƕ�
    int nSpanAngle;          //Բ���ÿ�Ƕ�
    int nPointStartAngle;    //�̶ȿ�ʼ�Ƕ�
    int nPointSpanAngel;     //�̶ȿ�Ƕ�
    double dMax;            //���ֵ
    double dMin;            //��Сֵ
    QString sPointColor;    //�Ǳ�ָ����ɫ
    QString sBackColor;     //�Ǳ�����ɫ
    QString sCaleColor;     //�Ǳ�̶���ɫ
    QString shapeName;      //�Ǳ�����
}*PMETER_ST;

enum DIRECTION
{
    TOWARD_LEFT = 3,      //����
    TOWARD_RIGHT,     //����
    TOWARD_TOP,       //����
    TOWARD_BOTTOM,    //����
    TO_LEFT_ROTATE,   //������ת
    TO_RIGHT_ROTATE   //������ת
};

enum  SHAPE_TYPE
{
    PILLA,      //����
    CIRCLE,     //Բ
    SECTOR,     //��Բ
    GROOVE      //��
};

enum GRAPH_TYPE
{
    ENCOMMON_TYPE,      //��ͨͼ��
    ENSTATISTICS_TYPE,  //ͳ��ͼ��
    ENMETER_TYPE        //�Ǳ�ͼ��
};

enum GRAPH_SHAPE {

        //��״ͼ
        BG_PL001,
        BG_PL002,
        BG_PL003,
        BG_PL004,
        BG_PL005,
        BG_PL006,

        BG_3D002,
        BG_3D004,
        BG_3D005,
        BG_3D006,

        BG_SC001,
        BG_SC002,
        BG_SC003,

        //Բ��
        CG_3D001,
        CG_3D002,
        CG_3D005,
        CG_3D006,

        CG_PL001,
        CG_PL002,
        CG_PL003,
        CG_PL004,
        CG_PL005,
        CG_PL006,

        //��Բͼ
        HG_PL001,
        HG_PL002,
        HG_PL003,
        HG_PL004,
        HG_PL005,
        HG_PL006,

        HG_3D001,
        HG_3D002,

        //��״ͼ
        GR_PL001M,
        GR_PL002M,
        GR_PL003M,
        GR_PL004M,
        GR_PL005M,
        GR_PL006M,
        GR_PL007M,
        GR_PL008M,
        GR_PL009M,
        GR_PL0010M,
        GR_PL0011M,
        GR_PL0012M,
        GR_PL0013M,
        GR_PL0014M,
        GR_PL0015M,
        GR_PL0016M,
        GR_PL0017M,
        GR_PL0018M,
        GR_PL0019M,
        GR_PL0020M,
        GR_PL0021M,

        GR_PL001,
        GR_PL002,
        GR_PL003,
        GR_PL004,
        GR_PL005,
        GR_PL006,
        GR_PL007,
        GR_PL008,
        GR_PL009,
        GR_PL0010,
        GR_PL0011,
        GR_PL0012,
        GR_PL0013,
        GR_PL0014,
        GR_PL0015,
        GR_PL0016,
        GR_PL0017,
        GR_PL0018,
        GR_PL0019,
        GR_PL0020,
        GR_PL0021,

        GR_3D001M,
        GR_3D002M,
        GR_3D003M,
        GR_3D004M,
        GR_3D005M,
        GR_3D006M,
        GR_3D007M,
        GR_3D008M,
        GR_3D009M,
        GR_3D0010M,
        GR_3D0011M,
        GR_3D0012M,
        GR_3D0013M,
        GR_3D0014M,
        GR_3D0015M,
        GR_3D0016M,
        GR_3D0017M,
        GR_3D0018M,
        GR_3D0019M,
        GR_3D0020M,
        GR_3D0021M,

        GR_3D001,
        GR_3D002,
        GR_3D003,
        GR_3D004,
        GR_3D005,
        GR_3D006,
        GR_3D007,
        GR_3D008,
        GR_3D009,
        GR_3D0010,
        GR_3D0011,
        GR_3D0012,
        GR_3D0013,
        GR_3D0014,
        GR_3D0015,
        GR_3D0016,
        GR_3D0017,
        GR_3D0018,
        GR_3D0019,
        GR_3D0020,
        GR_3D0021,

        //�Ǳ�
        MT_PL001,
        MT_PL002,
        MT_PL003,
        MT_PL004,
        MT_PL005,
        MT_PL006,
        MT_PL007,
        MT_PL008,
        MT_PL009,
        MT_PL0010,
        MT_PL0011,
        MT_PL0012,
        MT_PL0013,
        MT_PL0014,
        MT_PL0015,
        MT_PL0016,
        MT_PL0017,
        MT_PL0018,
        MT_PL0019,
        MT_PL0020,

        MT_3D001,
        MT_3D002,
        MT_3D003,
        MT_3D004,
        MT_3D005,
        MT_3D006,
        MT_3D007,
        MT_3D008,
        MT_3D009,
        MT_3D0010,
        MT_3D0011,
        MT_3D0012,
        MT_3D0013,
        MT_3D0014,
        MT_3D0015,
        MT_3D0016,
        MT_3D0017,
        MT_3D0018,
        MT_3D0019,
        MT_3D0020,

};

typedef struct ALARM_SET
{
    bool        bAlarm;            //�������� Ĭ��false
    short int   nType;
    QString     nMin;             //������Сֵ
    QString     nMax;             //�������ֵ
    Keyboard    nMinaddr;
    Keyboard    nMaxaddr;
    QString     nTextColor;       //������ʾ��ɫ
    QString     nDesignColor;     //����ͼ����ɫ
}ALARM_ST;

struct COMMON_INFORMATION
{
    GRAPH_TYPE eGraphType;        //ͼ������
    GRAPH_SHAPE eShapeId;         //ͼ��ID����
    QString     mAddress;         //����ֵ�ַ
    short int   eDataType;        //�������͵�index
    short int   nSourceRang;      //ָ��Դ��Χ index
    DIRECTION   eDirection;       //��ʾ����
    QString     nTextColor;       //��ʾ��ɫ
    QString     nBackcolor;       //������ɫ
    short int   nLeftTopX;        //�ؼ����Ͻ�����
    short int   nLeftTopY;        //�ؼ����Ͻ�Y����
    short int   nWidth;           //�ؼ����
    short int   nHeight;          //�ؼ��߶�
    short int   nShowLeftTopX;	  //�ڲ���̬��ʾͼ����X����
    short int   nShowLeftTopY;	  //�ڲ���̬��ʾͼ����Y����
    short int   nShowWidth;	  //�ڲ���̬��ʾͼ��
    short int   nShowHigth;	  //�ڲ���̬��ʾͼ��
    short int   nRulerLeftTopX;	  //�����ʾ����X����
    short int   nRulerLeftTopY;	  //�����ʾ����Y����
    short int   nRulerWidth;	  //�����ʾ��
    short int   nRulerHigth;	  //�����ʾ��

    short int   nMainRuling;      //����߿̶� Ĭ��2
    bool        bShowRuling;      //�α����ʾ Ĭ��false
    bool        bShowRuleValue;   //�Ƿ���ʾ���̶�ֵ
    short int   nRuling;          //�α�߿̶� Ĭ��5
    QString     nRulingColor;     //�����ɫ Ĭ�Ϸۺ�
    DIRECTION   eRulerDirectio;   //�����ʾ����
    double      nScaleLength;      //��߳���
    int         nPointType;        //ָ������
    short int   bSourceMark;      //Դ����+/-Ĭ����
    QString     eSourceMin;       //Դ��С Ĭ��0
    QString     eSourceMax;       //Դ��� Ĭ��100
    bool        bShowMark;        //��ʾ����+/- Ĭ��false
    double         eShowMin;         //��ʾ��С Ĭ��0
    double         eShowMax;         //��ʾ���Ĭ��100
    SHAPE_TYPE  eShapeType;       //��ͨͼ������ ��Բ�� �۵�
    bool        bFill;            //��ʾ��� Ĭ��false
    bool        bHole;            //��
    short int   nRadius;          //�װ뾶
    bool        bStart;           //��ʾ��ʼ��
    short int   nDesign;          //��ʾͼ��
    QString     nDesignColor;     //ͼ����ɫ
    QString     nFrameColor;      //�߿���ɫ
    bool        nScaleMark;       //ѡ�дο̶�
    short int   nMainScale;       //���̶Ȕ�
    short int   nSubScale;        //�ο̶Ȕ�
    CIRCLE_TYPE nCircle;          //Բ�Ͱ�Բ��Ϣ�ṹ��
    ALARM_ST       sAlarm;        //��������
    Keyboard    addr;
    Keyboard  addrSourceMax;          //Դ����ַ
    Keyboard  addrSourceMin;          //Դ��С��ַ
    short     nStartAngle;         //��ʼ��ĽǶ�
    short     nSpanAngle;          //Բ�Ŀ�Ƕ�

    short        nTransparent;    //�Ƿ�͸��
    bool         bShowFrame;      //��ʾ�߿�
};
struct METER_INFORMATION
{
    GRAPH_SHAPE eShapeId;         //�D�ξ�̖
    DIRECTION   eDirection;       //��ʾ����
    QString     mAddress;         //����ֵ�ַ
    short int   eDataType;        //�������͵�index
    short int   nSourceMark;      //Դ��̖
    short int   nSourceRang;      //ָ��Դ��Χ
    QString     eSourceMin;       //Դ��С
    QString     eSourceMax;       //Դ���
    bool        bShowMark;        //�@ʾ��̖
    double         eShowMin;         //�@ʾ��С
    double         eShowMax;         //�@ʾ���
    bool        bAlarm;           //���O�� Ĭ�Jfalse
    QString     nTextColor;       //�@ʾ�ɫ
    QString     nDesignColor;     //�D���ɫ,������ɫ
    QString     nScaleColor;      //�̶���ɫ
    short int   nMainScale;       //���̶Ȕ�
    short int   nSubScale;        //�ο̶Ȕ�
    double      nScaleLength;      //�̶ȳ���
    bool        nScaleMark;       //ѡ�дο̶�
    bool        bShowRuleValue;   //�Ƿ���ʾ���̶�ֵ
    short        nTransparent;      //�Ƿ�͸��
    int         nPointType;        //ָ������
    short int   nstartAngle;      //Բ��ʼ�Ƕ�
    short int   nSpanAngle;       //Բ���ÿ�Ƕ�
    short int   nPointStartAngle; //�̶ȿ�ʼ�Ƕ�
    short int   nPointSpanAngel;  //�̶ȿ�Ƕ�
    short int   nLeftTopX;        //�ؼ����Ͻ�����
    short int   nLeftTopY;        //�ؼ����Ͻ�Y����
    short int   nWidth;           //�ؼ����
    short int   nHeight;          //�ؼ��߶�
    short int   nShowLeftTopX;	  //�ڲ���̬��ʾͼ����X����
    short int   nShowLeftTopY;	  //�ڲ���̬��ʾͼ����Y����
    short int   nShowWidth;	  //�ڲ���̬��ʾͼ��
    short int   nShowHigth;	  //�ڲ���̬��ʾͼ��
    ALARM_ST    sAlarm;        //��������
    Keyboard    addr;
    Keyboard  addrSourceMax;          //Դ����ַ
    Keyboard  addrSourceMin;          //Դ��С��ַ

    bool         bShowFrame;         //��ʾ�߿�
};

class ChartItem : public QVisableItem
{
public:
    ChartItem();

     int GroupType();//�ؼ����� λ���� �ֿ���


     QGraphicsItem *Clone();//����item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

     void save(QDataStream &stream);//��item����������

     void load(QDataStream &stream);//������������item
public:

     GRAPH_TYPE  m_eGraphType;       //��ͨͼ������ ��Բ�� �۵�

     struct COMMON_INFORMATION common_st;

     struct METER_INFORMATION meter_st;

     void onSaveMeter(struct METER_INFORMATION meter);

     void onSaveCommon(struct COMMON_INFORMATION common);

     void onGetPosition();

     QString GetPicPath(ChartItem *libItem,SHAPE_TYPE nType,int nkey,DIRECTION derection);

     QString SaveLibPath(QGraphicsItem *pItem,QString path,QSizeF size);

     QVector<ADDRPRO> getAllItemAddr();

     void setAddress(QList<Keyboard> addr);

     QList<Keyboard> getAddress();

     QString  getItemName();

     //��������ҳ������
     //struct CHART_INFORMATION *Datesave;
public:
     QVector<ADDRPRO> lsX;
};

#endif // CHARTTIEM_H
