#ifndef QMESSAGESHOWATTR_H
#define QMESSAGESHOWATTR_H

#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"
#include "Frame/qprogectmanager.h"

typedef struct __LanDiff__
{
    short   m_nStatusIndex; //状态id
    QString m_sStateMessage;//状态显示内容
    int     m_nLanguage;    //语言id
    QString m_sFontType;    //字体类型
    short   m_nFontSize;    //字体大小
    QColor  m_nFontColor;   //字体颜色
}LanDiff;

typedef struct __MsgProp__
{
    //第一页属性
    QColor  m_nFrameColor;  //边框色
    QColor  m_nForecolor;   //前景色
    QColor  m_nBackcolor;   //背景色
    int     m_nStyle;       //样式

    //第二页属性,根据语言的不同而不同
    QVector<LanDiff> m_nVecPage2;
}MsgProp;

class QMessageShowAttr:public QVisableItem//public QItemGroup
{
public:
    QString     m_sShape;           //外形
    bool        m_bDataType;        //16位正整数为0,32位正整数位1,保存数据库时恢复成枚举
    Keyboard    m_keyAddress;       //监视地址
    short       m_nStateCount;      //总状态数
    bool        m_bFirstLanguage;   //所有语言都是使用第一种语言的文本
    bool        m_bStateZero;       //所有状态属性都和状态0相同
    short       m_eRemove;          //移动方向保存数据库时恢复成枚举
    short       m_nSpeed;           //移动速度
    short       m_nAlpha;
    QVector<MsgProp> m_vecMsg;      //各个状态属性

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
    virtual int GroupType();                //控件类型 位开关 字开关
    virtual QMessageShowAttr* Clone();      //复制item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count, int index); //编译的时候保存item到数据库
    virtual void save(QDataStream &stream); //将item存入数据流
    virtual void load(QDataStream &stream); //从数据流导出item
    QString  getItemName();

public:
    QVector<ADDRPRO> addrs;
};

#endif // QMESSAGESHOWATTR_H
