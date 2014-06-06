#ifndef HISALARMITEM_H
#define HISALARMITEM_H


#include "qvisableitem.h"
#include "alarmitem.h"

class HisAlarmItem : public QVisableItem
{
public:
    HisAlarmItem();

    int GroupType() ;
   QGraphicsItem *Clone();//����item

   void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�


   void save(QDataStream &stream);//��item����������

   void load(QDataStream &stream);//������������item
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
