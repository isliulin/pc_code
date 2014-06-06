#ifndef QMESSAGESHOWATTR_H
#define QMESSAGESHOWATTR_H

#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"
#include "Frame/qprogectmanager.h"

typedef struct __LanDiff__
{
    short   m_nStatusIndex; //״̬id
    QString m_sStateMessage;//״̬��ʾ����
    int     m_nLanguage;    //����id
    QString m_sFontType;    //��������
    short   m_nFontSize;    //�����С
    QColor  m_nFontColor;   //������ɫ
}LanDiff;

typedef struct __MsgProp__
{
    //��һҳ����
    QColor  m_nFrameColor;  //�߿�ɫ
    QColor  m_nForecolor;   //ǰ��ɫ
    QColor  m_nBackcolor;   //����ɫ
    int     m_nStyle;       //��ʽ

    //�ڶ�ҳ����,�������ԵĲ�ͬ����ͬ
    QVector<LanDiff> m_nVecPage2;
}MsgProp;

class QMessageShowAttr:public QVisableItem//public QItemGroup
{
public:
    QString     m_sShape;           //����
    bool        m_bDataType;        //16λ������Ϊ0,32λ������λ1,�������ݿ�ʱ�ָ���ö��
    Keyboard    m_keyAddress;       //���ӵ�ַ
    short       m_nStateCount;      //��״̬��
    bool        m_bFirstLanguage;   //�������Զ���ʹ�õ�һ�����Ե��ı�
    bool        m_bStateZero;       //����״̬���Զ���״̬0��ͬ
    short       m_eRemove;          //�ƶ����򱣴����ݿ�ʱ�ָ���ö��
    short       m_nSpeed;           //�ƶ��ٶ�
    short       m_nAlpha;
    QVector<MsgProp> m_vecMsg;      //����״̬����

public:
    QMessageShowAttr(QGraphicsItem *parent = 0);
    ~QMessageShowAttr();

public:
    //QGroupItem* pBaseItem;
    //void resetMsg(int curSta, QColor frame, QColor front, QColor back, int style);
    int curSta;
    virtual void redrawForChangeLanguage(int index);
    virtual void changeItemLanguageAttr(int lanNum);
    virtual void redrawForChangeStatus(int index, int lan);
    virtual int  getCurrentState();
    virtual QStringList getItemStates();
    QList<Keyboard> getAddress();
    void setAddress(QList<Keyboard> addr);
    virtual QVector<ADDRPRO> getAllItemAddr();
    virtual QStringList getAllFonts();

    TEXTPRO getAllItemText();
    void replaceAllItemText(int iLan,int iSta,QString sNewText);
     TEXTPRO vText;

public:
    virtual int GroupType();                //�ؼ����� λ���� �ֿ���
    virtual QMessageShowAttr* Clone();      //����item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count, int index); //�����ʱ�򱣴�item�����ݿ�
    virtual void save(QDataStream &stream); //��item����������
    virtual void load(QDataStream &stream); //������������item
    QString  getItemName();

public:
    QVector<ADDRPRO> addrs;
};

#endif // QMESSAGESHOWATTR_H
