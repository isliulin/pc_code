/****************************************************************************************************
 ��̬ͼƬ

 **************************************************************************************************/

#ifndef QSTATICPICTUREITEM_H
#define QSTATICPICTUREITEM_H
#include "Frame/mainwindow.h"
#include "qvisableitem.h"

typedef struct
{
    int    nRCount;    //֡��ִ�д���
    short  nIsBitCtrl;  //0:����λ���ƣ�1��λ����
    short  nValidBit; //��Чλ
    QString sCtrlAddr; //���Ƶ�ַ
    Keyboard CtrlAddr; //���Ƶ�ַ
    QString sPicPath;  //ͼƬ·��
    bool   bIspic;     //ͼƬORͼ��
    short  nOrigWidth;
    short  nOrigHeight;//ͼƬԭʼ���
}STATIC_PIC;

class QStaticPictureItem : public QVisableItem
{
public:
    QStaticPictureItem(QGraphicsItem *parent = 0);

      int GroupType() ;
     QGraphicsItem *Clone();//����item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

     void save(QDataStream &stream);//��item����������

     void load(QDataStream &stream);//������������item

     QVector<ADDRPRO> getAllItemAddr();

     QString  getItemName();

     void redrawForChangeStatus(int index, int lan);

public:
     STATIC_PIC m_PicInfo;

public:
     QVector<ADDRPRO> lsX;
};

#endif
