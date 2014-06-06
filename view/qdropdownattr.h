#ifndef QDROPDOWNATTR_H
#define QDROPDOWNATTR_H

#include "view/switchitem.h"
#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"

//const int NoEffect  = 0x0000;//无效果
//const int Bold      = 0x0001;//粗体
//const int Italic    = 0x0010;//斜体
//const int UnderLine = 0x1000;//下划线

typedef struct __SwitchInfo__
{
    short   switchType;     //1功能类型（1字开关，2位开关，3画面开关）
    //int     switchCount;    //编号
    //int     switchItemId;   //控件Id，属于哪个下拉框控件
    //int     switchFunId;    //功能Id（功能按钮Id）
    QVector<QString> vecSwitchFunName;  //功能名字,每种语言对应一个名字，
    //QString switchFunName;  //功能名字,每种语言对应一个名字，

    //位开关属性
    Keyboard        addrBit;        //1位地址
    BIT_OPER_TYPE   operTypeB;      //1操作类型
    bool            bDown;          //执行方式

    //字开关属性
    Keyboard        addrWord;       //1字地址
    WORD_OPER_TYPE  operTypeW;      //1操作类型
    DATA_TYPE       dataType;       //1数据类型
    double          value;          //1
    bool            bDynamicControl; //1wxy 常量数值动态控制
    Keyboard        addrConst;       //1常量数值地址


    //画面切换属性
    SCENE_OPER_TYPE operType;       //1操作类型
    //int             nSceneType;     //当前画面号，以后转成画面0，窗口1
    QString         sceneName;      //1画面名称
    bool            bLogout;        //1切换画面是否注销

    EITEM_TYPE      bLib;//是否是图片
    QString         sPath;//功能对应的图片路径
}SwitchInfo;

class QDropdownAttr:public QVisableItem
{
public://选择列表
    short               m_nShowNumber;  //下拉显示数量
    //QList<SwitchItem> m_listSwitchItem;//每个开关的实际属性
    //int                 totalItem;      //保存输入输出的时候用
    int                 totalScreen;    //保存当前情况下多少个画面，以区别窗口，但是为了防止保存的时候窗口或画面数改变
    bool                isUseScript;
    QString             macroName;
    QString             functionName;
    QVector<SwitchInfo> m_vecSwitchItem;//每个开关写入数据库的属性

public://字体设置
    QString     m_strFontName;          //字体类型的名字
    short       m_nFontSize;            //字体大小
    short       m_nLanType;             //语言种类
    short       m_nFontStyle;           //文字样式（标准，粗体，斜体）
    QColor      m_nFontColor;           //字体颜色
    QColor      m_nBackColor;           //背景颜色
    short       m_nAlpha;               //透明度
    bool        m_bUsePic;              //是否使用图片切换

public:
    QRectItem       *pRect;
    QRectItem       *pBackRect;
    QFoldLineItem   *pLine;

public:
    void resetDropDown(QColor mColor, short alpha);
    void getRange(int dataType,double &nMax,double &nMin);

    TEXTPRO getAllItemText();
    void replaceAllItemText(int iLan,int iSta,QString sNewText);
     TEXTPRO vText;

public:
    QDropdownAttr(QGraphicsItem *parent = 0);
    ~QDropdownAttr();
    QList<Keyboard> getAddress();
    void setAddress(QList<Keyboard> addr);
    virtual QVector<ADDRPRO> getAllItemAddr();
    virtual void changeItemLanguageAttr(int lanNum);
    virtual QStringList getAllFonts();

public:
    virtual int GroupType();                //控件类型 位开关 字开关
    virtual QDropdownAttr * Clone();         //复制item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count,int index); //编译的时候保存item到数据库
    virtual void save(QDataStream &stream); //将item存入数据流
    virtual void load(QDataStream &stream); //从数据流导出item
    QString getItemName();
    int checkMacroName(QString &msg);

public:
    QVector<ADDRPRO> addrs;
};

#endif // QDROPDOWNATTR_H
