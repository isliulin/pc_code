#ifndef ALARMBAR_H
#define ALARMBAR_H

#include "qvisableitem.h"


typedef struct _stAlarmBarPro
{
	int appearIndex;//����
	QColor frameColor;//�߿�ɫ
	QColor backColor;//����ɫ
	QColor frColor;//ǰ��ɫ
	QColor textColor;//�ı�ɫ
        int nPattern;//��ʽ
	int fontSize;//�����С
	bool bSelectall;//�Ƿ���ʾ���б���
	int nRangLow; //��ʾ������Χ����
	int nRangHigh; //��ʾ������Χ����
	int speed; //�������ƶ��ٶ�
	int direction;//�������ƶ�����
	int sort;//��������ʽ

    QStringList groupName;//����������

}stAlarmBarPro;
class AlarmBar : public QVisableItem
{
public:
    AlarmBar();

    int GroupType() ;
   QGraphicsItem *Clone();//����item

   int SetDefault();//����Ĭ�����
   void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�
   QVector<ADDRPRO> getAllItemAddr();
   void save(QDataStream &stream);//��item����������
   void load(QDataStream &stream);//������������item
   QString getItemName();

public:
    stAlarmBarPro stPro;

public:
    QVector<ADDRPRO> kb;
};
#endif // ALARMBAR_H
