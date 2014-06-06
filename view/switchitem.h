/****************************************************************************************************
  SwitchItem ����item�࣬�̳���QVisableItem
  ���п��ؿؼ�����SwitchItem �����

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
     QGraphicsItem *Clone();//����item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

     void InsertSwitchTable(QSqlDatabase &db,int type, int &count);
     void InsertStatusTable(QSqlDatabase &db,int itemId,int &count);
     void InsertTextTable(QSqlDatabase &db,int itemId,int index);
     void insertMacroTable(QSqlDatabase &db,int itemId,int &count,int sceneId,QString name);

     void save(QDataStream &stream);//��item����������

     void load(QDataStream &stream);//������������item

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
     //��������ҳ������
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

     //����ҳ������
     monitorPro mPro;

     //���ҳ������

     int statusIndex;
     int curSta;
     textProList statusText;//ÿ��״̬��Ӧһ��Vector

     picProList statusPic;//ÿ��״̬��Ӧ��ͼƬ����

public:
     QVector<ADDRPRO> kb;
     TEXTPRO vText;
};

#endif // SWITCHITEM_H
