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
    //矩形外观
    bool      m_bFillColor;
    QColor    m_nFillColor;
    bool      m_bFrameColor;
    QColor    m_nFrameColor;
    short     m_nFrameWidth;
    short     m_nAlpha;       //控件透明度
    //显示区域设置
    short     m_nBeginX;
    short     m_nBeginY;
    short     m_nWidth;
    short     m_nHeight;
    QColor    m_nBgColor;
    //位置控制
    bool      m_bPosCtrl;
    Keyboard  m_addrH;
    Keyboard  m_addrV;
    //大小控制
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
    virtual int GroupType();                //控件类型 位开关 字开关
    virtual DynCircleAttr* Clone();         //复制item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count, int index); //编译的时候保存item到数据库
    virtual void save(QDataStream &stream); //将item存入数据流
    virtual void load(QDataStream &stream); //从数据流导出item

    QString getItemName();
};

#endif // DYNCIRCLEATTR_H
