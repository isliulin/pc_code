/****************************************************************************************************
  SwitchItem 开关item类，继承与QVisableItem
  所有开关控件都是SwitchItem 类对象。

 **************************************************************************************************/

#ifndef SWITCHITEM_H
#define SWITCHITEM_H

#include "qvisableitem.h"
#include "qrectitem.h"
#include "qsimpletextitem.h"

class SwitchItem : public QVisableItem
{
public:
    SwitchItem();

     int GroupType() ;
     QGraphicsItem *Clone();//复制item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库

     void InsertSwitchTable(QSqlDatabase &db,int type, int &count);
     void InsertStatusTable(QSqlDatabase &db,int itemId,int &count);
     void InsertTextTable(QSqlDatabase &db,int itemId,int index);
     void insertMacroTable(QSqlDatabase &db,int itemId,int &count,int sceneId,QString name);

     void save(QDataStream &stream);//将item存入数据流

     void load(QDataStream &stream);//从数据流导出item

     //void SetText(QString text);

     void SetPicture(QString path,EITEM_TYPE blib,int alpha = 255,QColor color = QColor(0,0,0));
	 void resizeStatus(int statuCount,int lanCount);

     void redrawForChangeLanguage(int index);
     void redrawForChangeStatus(int index,int lan);
     int  getCurrentState();
     QString  getItemName();
     QStringList getItemStates();
	 QStringList getAllFonts();
         QVector<ADDRPRO> getAllItemAddr();

     TEXTPRO getAllItemText();
     void replaceAllItemText(int iLan,int iSta,QString sNewText);

     void SetDefault();

      QList<Keyboard> getAddress();
      void setAddress(QList<Keyboard> addr);


     void SavefunctionPage(
             SWITCH_TYPE Type,
             bitSwitchPro bitProperty,
             wordSwitchPro wordProperty,
             sceneSwitchPro sceneProperty,
             functionSwitchPro funProperty
             );
     void SaveBitPro(bitSwitchPro bitProperty);
     void SaveWordPro(wordSwitchPro wordProperty);
     void SaveScenePro(sceneSwitchPro sceneProperty);
     void SaveFunctionPro(functionSwitchPro funProperty);
	 void SaveIndicatorPro();

     void SaveMonitorPage(monitorPro mProperty);

     void SaveExteriorPage(int statusCount,textProList textpro,picProList picpro);

     int  checkMacroName(QString &msg);
public:
     //功能设置页面属性
     SWITCH_TYPE switchType;
     bitSwitchPro bitPro;
     wordSwitchPro wordPro;
     sceneSwitchPro scenePro;
     functionSwitchPro funPro;
     bool bMacro;
     bool bSlid;
     QString macroName;
	 QString functionName;
     bool bMacroUp;

     QString macroNameUp;

     //监视页面属性
     monitorPro mPro;

     //外观页面属性

     int statusIndex;
     int curSta;
     textProList statusText;//每个状态对应一个Vector

     picProList statusPic;//每个状态对应的图片属性

public:
     QVector<ADDRPRO> kb;
     TEXTPRO vText;
};

#endif // SWITCHITEM_H
