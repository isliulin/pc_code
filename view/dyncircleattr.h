#ifndef DYNCIRCLEATTR_H
#define DYNCIRCLEATTR_H

#include <qcolor.h>
#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"

class DynCircleAttr:public QVisableItem//public QItemGroup
{
public:
    DynCircleAttr(QGraphicsItem *parent = 0);
    ~DynCircleAttr();

public:
    //�������
    bool      m_bFillColor;
    QColor    m_nFillColor;
    bool      m_bFrameColor;
    QColor    m_nFrameColor;
    short     m_nFrameWidth;
    short     m_nAlpha;       //�ؼ�͸����
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
    Keyboard  m_addrCircle;

public:
    QElipseItem *pCircle;

public:
    //void resetCircle(short alpha);
    void resetCircle(short alpha, bool fill, bool frame, QColor cFill, QColor cFrame);
    QList<Keyboard> getAddress();
    void setAddress(QList<Keyboard> addr);
    virtual QVector<ADDRPRO> getAllItemAddr();
    virtual QStringList getAllFonts();
    //virtual void setAllItemAddr(QString oldKey, QString newKey);

public:
    QVector<ADDRPRO> kb;

public:
    virtual int GroupType();                //�ؼ����� λ���� �ֿ���
    virtual DynCircleAttr* Clone();         //����item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count, int index); //�����ʱ�򱣴�item�����ݿ�
    virtual void save(QDataStream &stream); //��item����������
    virtual void load(QDataStream &stream); //������������item

    QString getItemName();
};

#endif // DYNCIRCLEATTR_H
