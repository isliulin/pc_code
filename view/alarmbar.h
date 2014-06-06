#ifndef ALARMBAR_H
#define ALARMBAR_H

#include "qvisableitem.h"


typedef struct _stAlarmBarPro
{
	int appearIndex;//外形
	QColor frameColor;//边框色
	QColor backColor;//背景色
	QColor frColor;//前景色
	QColor textColor;//文本色
        int nPattern;//样式
	int fontSize;//字体大小
	bool bSelectall;//是否显示所有报警
	int nRangLow; //显示报警范围下限
	int nRangHigh; //显示报警范围上限
	int speed; //报警条移动速度
	int direction;//报警条移动方向
	int sort;//报警排序方式

    QStringList groupName;//报警组名称

}stAlarmBarPro;
class AlarmBar : public QVisableItem
{
public:
    AlarmBar();

    int GroupType() ;
   QGraphicsItem *Clone();//复制item

   int SetDefault();//设置默认外观
   void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库
   QVector<ADDRPRO> getAllItemAddr();
   void save(QDataStream &stream);//将item存入数据流
   void load(QDataStream &stream);//从数据流导出item
   QString getItemName();

public:
    stAlarmBarPro stPro;

public:
    QVector<ADDRPRO> kb;
};
#endif // ALARMBAR_H
