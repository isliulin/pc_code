/****************************************************************************************************
 静态图片

 **************************************************************************************************/

#ifndef QSTATICPICTUREITEM_H
#define QSTATICPICTUREITEM_H
#include "Frame/mainwindow.h"
#include "qvisableitem.h"

typedef struct
{
    int    nRCount;    //帧组执行次数
    short  nIsBitCtrl;  //0:不受位控制，1受位控制
    short  nValidBit; //有效位
    QString sCtrlAddr; //控制地址
    Keyboard CtrlAddr; //控制地址
    QString sPicPath;  //图片路径
    bool   bIspic;     //图片OR图库
    short  nOrigWidth;
    short  nOrigHeight;//图片原始宽高
}STATIC_PIC;

class QStaticPictureItem : public QVisableItem
{
public:
    QStaticPictureItem(QGraphicsItem *parent = 0);

      int GroupType() ;
     QGraphicsItem *Clone();//复制item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库

     void save(QDataStream &stream);//将item存入数据流

     void load(QDataStream &stream);//从数据流导出item

     QVector<ADDRPRO> getAllItemAddr();

     QString  getItemName();

     void redrawForChangeStatus(int index, int lan);

public:
     STATIC_PIC m_PicInfo;

public:
     QVector<ADDRPRO> lsX;
};

#endif
