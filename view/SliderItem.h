#ifndef SLIDERITEM_H
#define SLIDERITEM_H

#include <QDialog>
#include "Frame/mainwindow.h"
typedef struct SLIDERINFO{
    int startX;// X
    int startY;// Y
    int mWidth;// ���ο�
    int mHeight;// ���θ�
    QString rectColor;// ���α���ɫ
    QString slideBarColor;// �������ɫ
    QString fingerBackColor;// ָ�걳����ɫ
    QString fingerLineColor;// ָ��߿���ɫ
    short direction;// ����ķ�������1������2������3������4
    QString sPosition;
    short nPosition;// �̶����ֵķ���
    short dataType;// �������
    QString writeAddress;// д���ַ
    bool isTrend;// �Ƿ���ʾ��̬��Χ
    QString maxTrend;// ��̬��Χ���ֵ
    QString minTrend;// ��̬��Χ��Сֵ

    bool isShowCalibration;// �Ƿ���ʾ�̶�
    QString nCalibrationColor;//�̶���ɫ
    int nMaxNumber;//  ���̶���Ŀ
    int nMinNumber;//  �ο̶���Ŀ
    bool bShowShaft;// �Ƿ���ʾ��
    bool bShowText;// �Ƿ���ʾ����
    short nTotalCount;// �̶�С��λ����λ��
    short nDecimalCount;// smallint �̶�ֵС��λ��
    short nTextSize;// smallint �����Сindex
    QString sTextSize;
    QString nCalibrationMax;// �̶����ֵ
    QString nCalibrationMin;// �̶���Сֵ
    int nZvalue;
    int nCollidindId;

    Keyboard keyWriteAddress;//�ֵ�ַ
    Keyboard MaxAddress;//������ַ����
    Keyboard MinAddress;//���ص�ַ����
}SliderInfo;

class SliderItem : public QVisableItem
{
public:
    SliderItem();

    int GroupType() ;
   QGraphicsItem *Clone();//����item

   void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

   void save(QDataStream &stream);//��item����������

   void load(QDataStream &stream);//������������item

   void onSaveSlider(SliderInfo slider);//��������������

   void onSecurityPro(securityPro sproperty);//����Ȩ��ҳ������

   QList<Keyboard> getAddress();

   void setAddress(QList<Keyboard> addr);

   virtual QVector<ADDRPRO> getAllItemAddr();//���ҵ�ַ�麯��

   QString getItemName();

   SliderInfo m_slider;

   securityPro m_sproperty;
public:
   QVector<ADDRPRO> addrs;
};

#endif // SLIDERITEM_H
