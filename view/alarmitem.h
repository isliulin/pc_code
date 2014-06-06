#ifndef ALARMITEM_H
#define ALARMITEM_H
#include "Frame/qprogectmanager.h"


#include "qvisableitem.h"
typedef struct _stAlarmTitles
{
	//int languageIndex;//语言号
	int nFontSize;//标题文字大小
	QString sFont;//标题字体
	QString sTime;//“时间”
	QString sDate;//"日期"
	QString sMessage;//"消息"
	QString sClearTime;//"清除时间"
	QString sClearDate;//"清除日期"
}stAlarmTitles;
typedef struct _stAlarmItemPro
{
	QColor frameColor;//表的边框色
	QColor tableColor;//表的背景色
	bool bControl; //是否使用控制地址
	Keyboard controlAddr;//控制地址
	int nFontSize;//字体大小
	QString sFont;//字体
	QColor textColor;//文本色
	int rowCount;//行数
	QColor titleBackcolor;//标题栏背景色
	QColor titleColor;//标题文字颜色
	bool bShowTime;//是否显示时间
	//QString sTimeStr;
	int eTimeFormat;//时间格式

	bool bShowDate;//是否显示日期
	//QString sDateStr;
	int eDateFormat;//日期格式
	bool bShowNumber;//是否显示编号

	bool bSelectAll; //显示所有报警
	int nRangeLow;//显示范围下限
	int nRangeHigh;//显示范围上限

	bool bClearTime;//是否显示消除报警时间
	int eClearTimeFormat;//消除时间格式
	bool bClearDate;//是否显示消除报警日期
	int eClearDateFormat;//消除报警日期格式
	QColor clearedColor;//已消除报警的颜色
	QColor confirmColor;//已经确认报警的颜色
	QVector<stAlarmTitles> titles;//标题栏的所有文本
    QStringList groupName;//组名称
}stAlarmItemPro;
   //报警显示器
class AlarmItem : public QVisableItem
{
public:
    AlarmItem();

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
   QString  getItemName();
   //报警显示器属性
public:
   stAlarmItemPro alarmPro;
public:
   QVector<ADDRPRO> kb;
};

#endif // ALARMITEM_H
