#ifndef HISALARMITEM_H
#define HISALARMITEM_H


#include "qvisableitem.h"
#include "alarmitem.h"

class HisAlarmItem : public QVisableItem
{
public:
    HisAlarmItem();

    int GroupType() ;
   QGraphicsItem *Clone();//复制item

   void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库


   void save(QDataStream &stream);//将item存入数据流

   void load(QDataStream &stream);//从数据流导出item
   void redrawForChangeLanguage(int index);

   TEXTPRO getAllItemText();
   void replaceAllItemText(int iLan,int iSta,QString sNewText);
    TEXTPRO vText;

   QStringList getAllFonts();
   QVector<ADDRPRO> getAllItemAddr();

   void setAddress(QList<Keyboard> addr);

   QList<Keyboard> getAddress();
   QString  getItemName();
public:
    stAlarmItemPro alarmPro;
public:
    QVector<ADDRPRO> kb;
};

#endif // HISALARMITEM_H
