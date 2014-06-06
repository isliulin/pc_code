/****************************************************************************************************/


#ifndef QRECIPETABLEITEM_H
#define QRECIPETABLEITEM_H

#include <QDataStream>
#include "qvisableitem.h"

typedef struct
{
   int   nRecipeGroupId;   //配方ID
   bool  bShowRecipeID;	   //是否显示配方ID
   bool  bShowDescrip;	   //是否显示配方描述
   short eTextAlignType;   //文字的对齐方式
   short nLanguaId;	   //语言的ID号
   short nRowShowNum;	   //显示的行数
   short nColumShowNum;	   //要显示的列数
   QColor nHHeadTextColor; //横head文字颜色
   QColor nHHeadBackColor; //横head背景颜色
   short  nHHeadFontSize;  //横head字体大小
   QString sHHeadFontFamily;	//横head字体类型
   QColor  nVHeadTextColor;	//竖head文字颜色
   QColor  nVHeadBackColor;	//竖head背景颜色
   short   nVHeadFontSize;	//竖head字体大小
   QString  sVHeadFontFamily;	//竖head字体类型
   QColor  nDataTextColor;	//数据区的文字颜色
   QColor  nDataBackColor;	//数据区的背景颜色
   short   nDataFontSize;	//数据区的字体大小
   QColor  nLineColor;          //表格线颜色
   short   nTransparent;        //透明度
   QVector <QString> sRecipeName;//表列标题多语言信息
}RECIPESHOW;

class QRecipeTableItem : public QVisableItem
{
public:
    QRecipeTableItem();

     int GroupType();//控件类型 位开关 字开关


     QGraphicsItem *Clone();//复制item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库

     void save(QDataStream &stream);//将item存入数据流

     void load(QDataStream &stream);//从数据流导出item
public:

     void SetText(QString sText);
     void SetFontSize(int nFontSize);
     void SetFontName(QString sName); //设置字体名称
     void SetTextAlign(int nAlignType);

     void SaveInfo(RECIPESHOW info);
     void GetInfo(RECIPESHOW &info);

     QStringList getAllFonts();

     QString  getItemName();

     void changeItemLanguageAttr(int lanNum);

     void RefreshItem(int index);//双击打开配方数据采集修改确定后更新item

     int GetRicipeGroupId(int index);//返回配方组Id号

     int getInvalid();

     void setInvalid();

     //功能设置页面属性
     //struct CHART_INFORMATION *Datesave;
private:
     RECIPESHOW m_SaveInfo;

private:

};

#endif
