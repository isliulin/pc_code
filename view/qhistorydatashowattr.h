#ifndef QHISTORYDATASHOWATTR_H
#define QHISTORYDATASHOWATTR_H

#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"
#include "Frame/qprogectmanager.h"

typedef struct __dataInfo__
{
    int      m_nSampNum;
    bool     m_bShow;
    QString  m_strName;
    Keyboard m_kb;
}dataInfo;

typedef struct __HistoryDataInfo__
{
    int                 m_nLanguage;
    QVector<dataInfo>   m_vecInfo;
}HistoryDataInfo;

typedef struct __HistoryTextInfo__
{
    short       m_nTitleFontSize;	//标题字体大小，默认10
    int         m_nTitleLanguage;	//标题语言
    QString     m_sTitleFontType;	//标题字体类型，默认宋体
    QString     m_sTitleTimeName;	//标题列时间，中文：时间，英文：Time
    QString     m_sTitleDateName;	//标题列，日期
    QString     m_sTitleNumber;         //序号
}HistoryTextInfo;

class QHistoryDataShowAttr:public QVisableItem//public QItemGroup
{
public:
    //一般
    QColor  m_nForecolor;       //前景色
    QColor  m_nFrameColor;      //边框色
    short   m_nAlpha;
    //---------------
    short   m_nTextFontSize;    //文本字体大小，默认10
    short   m_nLine;            //显示行数，默认5
    QColor  m_nTextFontColor;   //文本字体颜色，默认黑色
    //---------------
    bool    m_bShowTime;	//是否显示时间，默认显示
    bool    m_bShowDate;	//是否显示日期,默认显示
    QColor  m_nTitleBackColor;	//标题背景颜色，默认黄色
    QColor  m_nTitleFontColor;	//标题字体颜色，默认黑色
    bool    m_bShowCode;        //是否显示编号
    TIME_FORMAT	m_eTimeFormat;  //(统一时间格式枚举)时间格式 HH:MM
    DATE_FORMAT	m_eDateFormat;  //(统一时间格式枚举)日期格式 默认：DD/MM/YY
    bool    m_bAddr;            //是否需要控制地址
    Keyboard m_KeyAddr;         //控制地址
    //---------------
    QString     sGroupName;         //组名
    //---------------
    QVector<HistoryTextInfo> m_vecHisText;//每种语言对应的表里内容的字体属性

    //数据
    QVector<HistoryDataInfo> m_vecHisData;

public:
    //QStringList sDataName;
    virtual void redrawForChangeLanguage(int index);
    virtual void changeItemLanguageAttr(int lanNum);
    virtual QStringList getAllFonts();

    TEXTPRO getAllItemText();
    void replaceAllItemText(int iLan,int iSta,QString sNewText);
     TEXTPRO vText;

public:
    QHistoryDataShowAttr(QGraphicsItem *parent = 0);
    ~QHistoryDataShowAttr();

public:
    virtual int GroupType();                //控件类型 位开关 字开关
    virtual QHistoryDataShowAttr* Clone();            //复制item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count, int index); //编译的时候保存item到数据库
    virtual void save(QDataStream &stream); //将item存入数据流
    virtual void load(QDataStream &stream); //从数据流导出item
    QString  getItemName();
    void sampChanged(QString oldName,QString newName,int sampType);
};

#endif // QHISTORYDATASHOWATTR_H
