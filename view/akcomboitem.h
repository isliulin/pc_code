#ifndef AKCOMBOITEM_H
#define AKCOMBOITEM_H

#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"

typedef struct __Combo_Statu__
{
    QVector<QString> m_vecText;	//一个状态的各个文本
    double           m_value;
}ComboStatu;

typedef struct __Combo_Language__
{
    short   m_nAlign;       //对齐，居中0，左对齐1，右对齐2
    short   m_nFontSize;    //字体大小
    QString m_strFontName;  //字体名字
    QColor  m_nTextColor;   //文本色

    bool    m_bCuTi;        //粗体
    bool    m_bXieTi;       //斜体
    bool    m_bXiaHuaXian;  //下划线
}ComboLanguage;

typedef struct __Data_Combobox__
{
    int		m_nStatuNum; 	//总状态数
    DATA_TYPE 	m_eDataType;	//数据类型
    Keyboard 	m_keyCtrlAddr;	//控制地址

    short       m_nAlpha;	//透明度
    QColor      m_nBKColor;	//背景色
    EITEM_TYPE 	m_eLibType;	//0标示是外部图片 1表示是图库
    QString 	m_strPath;	//路径

    bool        m_bUseMacro;	//是否使用脚本
    QString     m_strMacroName;	//脚本

    bool        m_bFirstLan;	//是否使用第一种语言

    QVector<ComboStatu>     m_vecStatus;    //多状态

    QVector<ComboLanguage>  m_vecLanguage;  //多语言
}DataCombobox;

class AkComboItem:public QVisableItem
{
public:
    AkComboItem(QGraphicsItem *parent = 0);
    ~AkComboItem();

public:
    DataCombobox     dataCombo;
    QVector<ADDRPRO> addrs;

public:
    virtual int GroupType();                //控件类型 位开关 字开关
    virtual AkComboItem* Clone();      //复制item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count, int index); //编译的时候保存item到数据库
    virtual void save(QDataStream &stream); //将item存入数据流
    virtual void load(QDataStream &stream); //从数据流导出item

public:
    virtual void redrawForChangeLanguage(int index);
    virtual void redrawForChangeStatus(int index, int lan);
    virtual void changeItemLanguageAttr(int lanNum);
    virtual QStringList getAllFonts();
    QString getItemName();
    int checkMacroName(QString &msg);

    TEXTPRO getAllItemText();
    void replaceAllItemText(int iLan,int iSta,QString sNewText);
     TEXTPRO vText;

    virtual QVector<ADDRPRO> getAllItemAddr();
    virtual QStringList getItemStates();

    QList<Keyboard> getAddress();
    void setAddress(QList<Keyboard> addr);
};

#endif // AKCOMBOITEM_H
