#ifndef DYNRECTATTR_H
#define DYNRECTATTR_H

#include <qcolor.h>
#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"

class DynRectAttr:public QVisableItem//public QItemGroup
{
public:
    DynRectAttr(QGraphicsItem *parent = 0);
    ~DynRectAttr();

public:
    //�������
    bool      m_bFillColor;
    QColor    m_nFillColor;
    bool      m_bFrameColor;
    QColor    m_nFrameColor;
    short     m_nFrameWidth;
    short     m_nAlpha;
    //��ʾ��������
    short     m_nBeginX;
    short     m_nBeginY;
    short     m_nWidth;
    short     m_nHeight;
    QColor    m_nBgColor;
    //λ�ÿ���
    bool      m_bPosCtrl;
    Keyboard  m_addrH;
    Keyboard  m_addrV;
    //��С����
    bool      m_bSizeCtrl;
    short     m_nRefType;//�̶���
    Keyboard  m_addrWidth;
    Keyboard  m_addrHeight;

public:
    //void resetRect(QColor mBkColor, QColor mFrmColor);
    void resetRect(short alpha, QColor mBkColor, QColor mFrmColor, bool bBack, bool bFrame);
    QList<Keyboard> getAddress();
    void setAddress(QList<Keyboard> addr);
    virtual QVector<ADDRPRO> getAllItemAddr();
    virtual QStringList getAllFonts();

public:
    QVector<ADDRPRO> addrs;

public:
    virtual int GroupType();                //�ؼ����� λ���� �ֿ���
    virtual DynRectAttr* Clone();           //����item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count, int index); //�����ʱ�򱣴�item�����ݿ�
    virtual void save(QDataStream &stream); //��item����������
    virtual void load(QDataStream &stream); //������������item
    QString getItemName();
};

#endif // DYNRECTATTR_H
