#ifndef TABLEITEM_H
#define TABLEITEM_H
#include "Frame/mainwindow.h"


class TableItem : public QVisableItem
{
public:
    TableItem();

      int GroupType() ;
     QGraphicsItem *Clone();//����item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

     void save(QDataStream &stream);//��item����������

     void load(QDataStream &stream);//������������item

     QString getItemName();
};

#endif // TABLEITEM_H
