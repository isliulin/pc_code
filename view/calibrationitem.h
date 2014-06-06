#ifndef CalibrationItem_H
#define CalibrationItem_H
#include "qvisableitem.h"
#include <QDialog>
#include "Frame/mainwindow.h"

//刻度结构体
typedef struct DATACALIBRATIONINFO{
    int id;//编号
    QString nLineColor;//线条颜色
    QString nTextColor;//字体颜色
    short nCalibrationDirection;//刻度方向
    short nNumberIncreaseDirection;//刻度大小递增方向
    QString direction;
    short nMainNumberCount;//主刻度数目
    short nNextNumberCount;//次刻度数目
    bool bShowText;//是否显示文本
    QString nMaxNumber;//刻度值最大值
    QString nMinNumber;//刻度值最小值
    short nDecimalCount;//刻度值小数位数
    short nTextSize;//字体大小
    QString stextsize;
    int nStartX;//开始x
    int nStartY;//开始y
    int nCalibrationWidth;//刻度的宽
    int nCalibrationHeight;//刻度的高
    int nZvalue;//层ID
    int nCollidindId;//组合ID
} Calibration;



class CalibrationItem : public QVisableItem
{
public:
    CalibrationItem(QGraphicsItem *parent = 0);
    int GroupType() ;
   QGraphicsItem *Clone();//复制item

   void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库

   void save(QDataStream &stream);//将item存入数据流

   void load(QDataStream &stream);//从数据流导出item

   void onSaveCalibration(Calibration cali_st);//保存刻度属性

   QString getItemName();

   Calibration m_calibrations;

};
#endif // CalibrationItem_H
