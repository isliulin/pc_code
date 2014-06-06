#ifndef XYTREND_H
#define XYTREND_H

#include "qtrendattr.h"
typedef struct _ChannelInfo
{
    short           m_nNumOfChannel;	//ͨ����
    Keyboard        m_AddrX;//X���׵�ַ
    Keyboard        m_AddrY;//Y���׵�ַ

    short           nLineThickness; //�������
    QColor          nDisplayColor;  //��ʾ��ɫ
    LineStyleType   eLineType;      //����
    DisConType   eDisplayCondition; //��ʾ����
    Keyboard     KeyAddr;           //��ʾON/OFF��ַ
}ChannelInfo;

class XYtrend:public QVisableItem//public QItemGroup//
{
public://
    bool        m_bIsAll;           //����ȫ��
    int chlCount;//ͨ������
    int addrLength;//��ַ���ȣ��൱�ڲ�������

    DATA_TYPE m_dataType;//��������
    Keyboard    m_TriggerAddr;//������ַ
    bool        m_bReset;//�Ƿ��Զ���λ
    bool        m_bScale;//�Ƿ�����

    bool m_bDisplayConst;//��ʾ��Χ�Ƿ���
    Keyboard    m_DisplayMaxAddrX;//��ʾ��Χ���ֵ ��ַ
    Keyboard    m_DisplayMinAddrX;//��ʾ��Χ��Сֵ ��ַ

    double          m_nDisplayMinX;	//��ʾ��Сֵ
    double          m_nDisplayMaxX;	//��ʾ���ֵ
    bool        m_bConstX;//�Ƿ�����Χ
    Keyboard    m_SourceMaxAddrX;//Դ��Χ���ֵ ��ַ
    Keyboard    m_SourceMinAddrX;//Դ��Χ��Сֵ ��ַ
    double      m_nSourceMaxX;	//Դ��Χ���ֵ
    double      m_nSourceMinX;	//Դ��Χ��Сֵ

    bool m_bDisplayConstY;//Y��ʾ��Χ�Ƿ���
    Keyboard    m_DisplayMaxAddrY;//Y��ʾ��Χ���ֵ ��ַ
    Keyboard    m_DisplayMinAddrY;//Y��ʾ��Χ��Сֵ ��ַ
    double          m_nDisplayMinY;	//Y��ʾ��Сֵ
    double          m_nDisplayMaxY;	//Y��ʾ���ֵ
    bool        m_bConstY;//�Ƿ�����Χ
    Keyboard    m_SourceMaxAddrY;//Դ��Χ���ֵ ��ַ
    Keyboard    m_SourceMinAddrY;//Դ��Χ��Сֵ ��ַ
    double      m_nSourceMaxY;	//Դ��Χ���ֵ
    double      m_nSourceMinY;	//Դ��Χ��Сֵ


    QVector<ChannelInfo> m_vecChannels;//����ͨ�������������

public://��ʾ������
    bool    m_bSelectVertMinor;	//�Ƿ���ʾ��ֱ�α��
    bool    m_bSelectHorMinor;	//�Ƿ���ʾˮƽ�α��
    bool    m_bMainVer;         //�Ƿ���ʾ��ֱ�����
    bool    m_bMainHor;         //�Ƿ���ʾˮƽ�����
    //short   m_nDataSample;	//����������
    //short   m_nScrollSample;	//����������
    short   m_nVertMajorScale;	//��ֱ�����
    short   m_nVertMinorScale;	//��ֱ�α��
    short   m_nHorMajorScale;	//ˮƽ�����
    short   m_nHorMinorScale;	//ˮƽ�α��

public://��ɫ�Ի���Ҫ�洢������
    bool   m_bGrade;            //�Ƿ���Ҫ����
    QColor m_nVerColor;         //ˮƽ������ɫ
    QColor m_nHorColor;         //��ֱ������ɫ
    QColor m_nBoradColor;	//�߿���ɫ
    QColor m_nScaleColor;	//�����ɫ
    QColor m_nGraphColor;	//ͼ������ɫ
    int m_alpha;//ͼ����͸����
    QColor m_TextColor;//�̶��ı�ɫ
    int m_textSize;//�̶��ı���С


public:
    XYtrend(QGraphicsItem *parent = 0);
    ~XYtrend();
    QString  getItemName();

public:
    virtual int GroupType();                //�ؼ����� λ���� �ֿ���
    virtual XYtrend *Clone();            //����item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count,int index); //�����ʱ�򱣴�item�����ݿ�
    virtual void save(QDataStream &stream); //��item����������
    virtual void load(QDataStream &stream); //������������item
    QVector<ADDRPRO> getAllItemAddr();

public:
    QVector<ADDRPRO> kb;
};

#endif // XYTREND_H
