#ifndef QMESSAGEBORADATTR_H
#define QMESSAGEBORADATTR_H

#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"

typedef struct __MmessageBoardLanguage__
{
    int     m_nLanguage;    //语言id
    QString m_sNumber;      //状态显示内容
    QString m_sDateName;    //状态显示内容
    QString m_sTimeName;    //状态显示内容
    QString m_sMessageName; //状态显示内容
}MmessageBoardLanguage;

class qMessageBoradAttr:public QVisableItem
{
public:
    //标题
    bool    m_bShowId;      //是否显示编号
    bool    m_bShowTime;    //是否显示时间
    short   m_nTimeType;    //时间格式（枚举）
    bool    m_bShowDate;    //是否显示日期
    short   m_nDateType;    //日期格式（枚举）
    short   m_nTFontSize;   //表头字体大小
    QString m_sTFontType;   //表头字体类型
    QColor  m_nTFontColor;  //表头字体颜色
    QColor  m_nTBackColor;  //表头背景颜色
    //填充
    short   m_nAlpha;       //控件透明度
    QColor  m_nLineColor;   //边框颜色
    short   m_nFillCss;     //填充样式
    QColor  m_nBackColor;   //背景颜色
    QColor  m_nForeColor;   //前景色
    //字体
    short   m_nFontSize;    //内容字体大小
    QString m_sFontType;    //内容字体类型
    QColor  m_nFontColor;   //内容字体颜色
    int     m_nRowNumber;   //内容行数
    //多语言
    QVector<MmessageBoardLanguage> m_vecMessage;

public:
    qMessageBoradAttr(QGraphicsItem *parent = 0);
    ~qMessageBoradAttr();

public:
    virtual int GroupType();                //控件类型 位开关 字开关
    virtual qMessageBoradAttr* Clone();      //复制item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count, int index); //编译的时候保存item到数据库
    virtual void save(QDataStream &stream); //将item存入数据流
    virtual void load(QDataStream &stream); //从数据流导出item

    TEXTPRO getAllItemText();
    void replaceAllItemText(int iLan,int iSta,QString sNewText);
     TEXTPRO vText;

public:
    virtual void redrawForChangeLanguage(int index);
    virtual void changeItemLanguageAttr(int lanNum);
    virtual QStringList getAllFonts();
    QString  getItemName();
};

#endif // QMESSAGEBORADATTR_H
