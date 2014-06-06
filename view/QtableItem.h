#ifndef QTABLEITEM_H
#define QTABLEITEM_H

#include "qitemgroup.h"
#include "../Frame/qprogectmanager.h"

typedef struct
{
    short nOrientationCount;      //�������
    short nPortraitCount;         //�������
    bool  bShowFrameLine;         //�Ƿ���ʾ�߿�����
    bool  bShowOrientationLine;   //�Ƿ���ʾˮƽ����
    bool  bShowPortraitCount;     //�Ƿ���ʾ��ֱ����
    QColor  nBackColor;           //��񱳾���ɫ
    QColor  nFramecolor;         //���߿���ɫ
    QColor nWShowColor;           //�����߿�������ɫ
    short  eNLineType;	          //����ڱ߿�����
    short   nTransparent;        //͸����
    bool bHDynamicControl;          //���������̬����
    Keyboard   addrHDynamic;        //���������̬���Ƶ�ַ
    bool bVDynamicControl;          //���������̬����
    Keyboard   addrVDynamic;        //���������̬���Ƶ�ַ

}TABLEINFO;
class QTableItem : public QVisableItem
{
public:
    QTableItem(QGraphicsItem *parent = 0);

    int GroupType();//�ؼ����� λ���� �ֿ���


    QGraphicsItem *Clone();//����item

    void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

    void save(QDataStream &stream);//��item����������

    void load(QDataStream &stream);//������������item

    QString getItemName();

    TABLEINFO m_Table;
};
#endif
