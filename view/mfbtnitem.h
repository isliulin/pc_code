#ifndef MFBTNITEM_H
#define MFBTNITEM_H

#include "qvisableitem.h"
#include "qdropdownattr.h"
class MfBtnItem : public QVisableItem
{
public:
    MfBtnItem();
    ~MfBtnItem();
    void SetDefault();

public:
    bool                isUseScript;
    QString             macroName;
    QString             functionName;
    QVector<SwitchInfo> m_vecSwitchItem;//每个开关写入数据库的属性

    //QVector<ST_TEXT_PROP > textPros;//文本属性
    //ST_PIC_PROP picPro;//图片属性

    int statusIndex;
    int curSta;
    textProList statusText;
    picProList statusPic;
public:

    QList<Keyboard> getAddress();//获取操作地址
    void setAddress(QList<Keyboard> addr);//设置操作地址
    QVector<ADDRPRO> getAllItemAddr();//获取所有用到的地址
    void changeItemLanguageAttr(int lanNum);//改变语言
    QStringList getAllFonts();//获取所有字体
	void SetPicture(QString path,EITEM_TYPE blib,int alpha = 255,QColor color = QColor(0,0,0));
    //void InsertTextTable(QSqlDatabase &db,int itemId);
    //void resizeLan(int count);
    QString  getItemName();


    int GroupType();                //控件类型
    MfBtnItem * Clone();         //复制item
    void compile(QSqlDatabase &db, int nSceneId, int &count,int index); //编译的时候保存item到数据库
    void insertMacroTable(QSqlDatabase &db,int itemId,int &count,int sceneId);
    void InsertSwitchTable(QSqlDatabase &db,int type, int &count,SwitchInfo info);
    void getRange(int dataType,double &nMax,double &nMin);
    //void redrawForChangeStatus(int index, int lan);

    void save(QDataStream &stream); //将item存入数据流
    void load(QDataStream &stream); //从数据流导出item

    void SaveMonitorPage(monitorPro mProperty);
    monitorPro mPro;

    void InsertStatusTable(QSqlDatabase &db,int itemId,int &count);
    void InsertTextTable(QSqlDatabase &db,int itemId,int index);

    void redrawForChangeLanguage(int index);
    void redrawForChangeStatus(int index, int lan);
    QStringList getItemStates();
    void resizeStatus(int statuCount,int lanCount);

    int getCurrentState();
    int checkMacroName(QString &msg);

    TEXTPRO getAllItemText();
    void replaceAllItemText(int iLan,int iSta,QString sNewText);
     TEXTPRO vText;

public:
    QVector<ADDRPRO> addrs;
};

#endif // MFBTNITEM_H
