#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include "qvisableitem.h"
#include "view/qpixmapitem.h"
#include "Frame/qprogectmanager.h"
class ImageItem;

typedef struct IMAGE_INFO_SAVE
{
    short int nLp;//�ؼ����Ͻ�x����
    short int nTp;//�ؼ����Ͻ�y����
    short int nWidth;//�ؼ����
    short int nHeight;//�ؼ��߶�
    short int nFunType;//0::�����̶�  1:����л�
    bool      bUseFlicker;//��˸
    //QString   nBackColor;//������ɫ
    short int nChangeCondition;//0ʱ�����л� 1λֵ�л�2:�̶�ֵ�л�
    QString   mWatchAddr;//���ӵ�ַ
    Keyboard    addr;
    short int nStatusTotal;//��¼״̬����
    short int nTimeInterval;//�л�ʱ��������λΪ100����
    short int nPicType;//0��ϵͳͼ�� 1���ļ�ͼ��
    bool      bIsLoopType;//��nChangeConditionΪ��ʱ�����л�ʱ��Ч,true����״̬��ѭ���л�(Ĭ��),false: ��״̬�������л�
    short int nCmpFactor;//Ԥ��̶�ֵ
    //QColor    nBackColor;//������ɫ
}INTOSAVE;

typedef struct IMAGE_INFO_STRUCT//ͼƬ��Ϣ�ṹ�壬�±꣬���ƣ�·��
{
    //int num;
    QString name;//�洢ת���������elment+X
    QString path;//�����ͼƬ��洢·���������ͼ����洢GROUP_NAME_KEY ҳ-ID��ʽ
    EITEM_TYPE    bIspic;//0:ͼƬ
    short int nCmpFactor;//Ԥ��̶�ֵ
    //QPixmapItem *PicItem;
    //ImageItem *pItem;
}IMAGEINFO;

class ImageItem : public QVisableItem
{
public:
    ImageItem();

     int GroupType();//�ؼ����� λ���� �ֿ���


     QGraphicsItem *Clone();//����item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

     void save(QDataStream &stream);//��item����������

     void load(QDataStream &stream);//������������item

     int onGetCurrentNum();

     void onSetCurrentNum(short int num);

     void onSavePicInfo(INTOSAVE picInfo);

     void onGetPosition();

     void redrawForChangeStatus(int index, int lan);

     int getCurrentState();

     QStringList getItemStates();

     QVector<ADDRPRO> getAllItemAddr();

     QString  getItemName();

     QList<Keyboard> getAddress();

     void setAddress(QList<Keyboard> addr);

public:
     QVector<ADDRPRO> lsX;

public:
     QVector<IMAGEINFO> m_PicInfo;

     INTOSAVE m_SaveInfo;
     //��������ҳ������
     //struct CHART_INFORMATION *Datesave;
private:
     short int number;//��¼��ǰѡ��ͼƬ�������±�

};
#endif
