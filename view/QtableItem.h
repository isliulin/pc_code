#ifndef QTABLEITEM_H
#define QTABLEITEM_H

#include "qitemgroup.h"
#include "../Frame/qprogectmanager.h"

typedef struct
{
    short nOrientationCount;      //横向个数
    short nPortraitCount;         //纵向个数
    bool  bShowFrameLine;         //是否显示边框线条
    bool  bShowOrientationLine;   //是否显示水平线条
    bool  bShowPortraitCount;     //是否显示垂直线条
    QColor  nBackColor;           //表格背景颜色
    QColor  nFramecolor;         //表格边框颜色
    QColor nWShowColor;           //表格外边框：线条颜色
    short  eNLineType;	          //表格内边框：线型
    short   nTransparent;        //透明度
    bool bHDynamicControl;          //横向个数动态控制
    Keyboard   addrHDynamic;        //横向个数动态控制地址
    bool bVDynamicControl;          //纵向个数动态控制
    Keyboard   addrVDynamic;        //纵向个数动态控制地址

}TABLEINFO;
class QTableItem : public QVisableItem
{
public:
    QTableItem(QGraphicsItem *parent = 0);

    int GroupType();//控件类型 位开关 字开关


    QGraphicsItem *Clone();//复制item

    void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库

    void save(QDataStream &stream);//将item存入数据流

    void load(QDataStream &stream);//从数据流导出item

    QString getItemName();

    TABLEINFO m_Table;
};
#endif
