/****************************************************************************************************
  配方选择item类，继承于QVisableItem
 **************************************************************************************************/

#ifndef QRECIPEITEM_H
#define QRECIPEITEM_H

#include "QDataStream"
#include  "Frame/mainwindow.h"

typedef struct
{
    short   eShowType;        //配方显示的样式（下拉或列表）1:下拉 2：列表
    short   sShowRecipeId;    //配方组的编号
    QString sFontFamily;      //字体样式
    short   nFontSize;        //字体大小
    QColor  nTextColor;       //字体颜色
    QColor  nBackColor;       //背景颜色
    short   nCurrShowRow;     //当前显示的行数
    bool    bUseMacro;        //是否使用宏指令
    QString   macroName;         //宏指令ID号
    QString   functionName;    //脚本函数ID
    short   nTransparent;        //透明度
}RCIPEINFO;

class QRcipeItem : public QVisableItem
{
public:
    QRcipeItem();

     int GroupType();//控件类型 位开关 字开关


     QGraphicsItem *Clone();//复制item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库

     void save(QDataStream &stream);//将item存入数据流

     void load(QDataStream &stream);//从数据流导出item

     void onSaveInfo(RCIPEINFO &Rcipe);

     void insertMacroTable(QSqlDatabase &db,int itemId,int &count,int sceneId);

     QStringList getAllFonts();

     QString  getItemName();

     int GetRicipeGroupId(int index);//返回配方组Id号

     void setInvalid();

     int getInvalid();
     int checkMacroName(QString &msg);

public:
     RCIPEINFO m_Rcipe;
private:

};

#endif
