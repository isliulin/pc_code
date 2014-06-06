#ifndef TABLEITEM_H
#define TABLEITEM_H
#include "Frame/mainwindow.h"


class TableItem : public QVisableItem
{
public:
    TableItem();

      int GroupType() ;
     QGraphicsItem *Clone();//复制item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库

     void save(QDataStream &stream);//将item存入数据流

     void load(QDataStream &stream);//从数据流导出item

     QString getItemName();
};

#endif // TABLEITEM_H
