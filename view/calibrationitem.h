#ifndef CalibrationItem_H
#define CalibrationItem_H
#include "qvisableitem.h"
#include <QDialog>
#include "Frame/mainwindow.h"

//�̶Ƚṹ��
typedef struct DATACALIBRATIONINFO{
    int id;//���
    QString nLineColor;//������ɫ
    QString nTextColor;//������ɫ
    short nCalibrationDirection;//�̶ȷ���
    short nNumberIncreaseDirection;//�̶ȴ�С��������
    QString direction;
    short nMainNumberCount;//���̶���Ŀ
    short nNextNumberCount;//�ο̶���Ŀ
    bool bShowText;//�Ƿ���ʾ�ı�
    QString nMaxNumber;//�̶�ֵ���ֵ
    QString nMinNumber;//�̶�ֵ��Сֵ
    short nDecimalCount;//�̶�ֵС��λ��
    short nTextSize;//�����С
    QString stextsize;
    int nStartX;//��ʼx
    int nStartY;//��ʼy
    int nCalibrationWidth;//�̶ȵĿ�
    int nCalibrationHeight;//�̶ȵĸ�
    int nZvalue;//��ID
    int nCollidindId;//���ID
} Calibration;



class CalibrationItem : public QVisableItem
{
public:
    CalibrationItem(QGraphicsItem *parent = 0);
    int GroupType() ;
   QGraphicsItem *Clone();//����item

   void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

   void save(QDataStream &stream);//��item����������

   void load(QDataStream &stream);//������������item

   void onSaveCalibration(Calibration cali_st);//����̶�����

   QString getItemName();

   Calibration m_calibrations;

};
#endif // CalibrationItem_H
