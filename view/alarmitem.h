#ifndef ALARMITEM_H
#define ALARMITEM_H
#include "Frame/qprogectmanager.h"


#include "qvisableitem.h"
typedef struct _stAlarmTitles
{
	//int languageIndex;//���Ժ�
	int nFontSize;//�������ִ�С
	QString sFont;//��������
	QString sTime;//��ʱ�䡱
	QString sDate;//"����"
	QString sMessage;//"��Ϣ"
	QString sClearTime;//"���ʱ��"
	QString sClearDate;//"�������"
}stAlarmTitles;
typedef struct _stAlarmItemPro
{
	QColor frameColor;//��ı߿�ɫ
	QColor tableColor;//��ı���ɫ
	bool bControl; //�Ƿ�ʹ�ÿ��Ƶ�ַ
	Keyboard controlAddr;//���Ƶ�ַ
	int nFontSize;//�����С
	QString sFont;//����
	QColor textColor;//�ı�ɫ
	int rowCount;//����
	QColor titleBackcolor;//����������ɫ
	QColor titleColor;//����������ɫ
	bool bShowTime;//�Ƿ���ʾʱ��
	//QString sTimeStr;
	int eTimeFormat;//ʱ���ʽ

	bool bShowDate;//�Ƿ���ʾ����
	//QString sDateStr;
	int eDateFormat;//���ڸ�ʽ
	bool bShowNumber;//�Ƿ���ʾ���

	bool bSelectAll; //��ʾ���б���
	int nRangeLow;//��ʾ��Χ����
	int nRangeHigh;//��ʾ��Χ����

	bool bClearTime;//�Ƿ���ʾ��������ʱ��
	int eClearTimeFormat;//����ʱ���ʽ
	bool bClearDate;//�Ƿ���ʾ������������
	int eClearDateFormat;//�����������ڸ�ʽ
	QColor clearedColor;//��������������ɫ
	QColor confirmColor;//�Ѿ�ȷ�ϱ�������ɫ
	QVector<stAlarmTitles> titles;//�������������ı�
    QStringList groupName;//������
}stAlarmItemPro;
   //������ʾ��
class AlarmItem : public QVisableItem
{
public:
    AlarmItem();

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
   QString  getItemName();
   //������ʾ������
public:
   stAlarmItemPro alarmPro;
public:
   QVector<ADDRPRO> kb;
};

#endif // ALARMITEM_H
