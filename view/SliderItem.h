#ifndef SLIDERITEM_H
#define SLIDERITEM_H

#include <QDialog>
#include "Frame/mainwindow.h"
typedef struct SLIDERINFO{
    int startX;// X
    int startY;// Y
    int mWidth;// 矩形宽
    int mHeight;// 矩形高
    QString rectColor;// 矩形背景色
    QString slideBarColor;// 滑轨的颜色
    QString fingerBackColor;// 指标背景颜色
    QString fingerLineColor;// 指标边框颜色
    short direction;// 滑块的方向，向上1，向下2，向左3，向右4
    QString sPosition;
    short nPosition;// 刻度文字的方向
    short dataType;// 数据类别
    QString writeAddress;// 写入地址
    bool isTrend;// 是否显示动态范围
    QString maxTrend;// 动态范围最大值
    QString minTrend;// 动态范围最小值

    bool isShowCalibration;// 是否显示刻度
    QString nCalibrationColor;//刻度颜色
    int nMaxNumber;//  主刻度数目
    int nMinNumber;//  次刻度数目
    bool bShowShaft;// 是否显示轴
    bool bShowText;// 是否显示文字
    short nTotalCount;// 刻度小数位数总位数
    short nDecimalCount;// smallint 刻度值小数位数
    short nTextSize;// smallint 字体大小index
    QString sTextSize;
    QString nCalibrationMax;// 刻度最大值
    QString nCalibrationMin;// 刻度最小值
    int nZvalue;
    int nCollidindId;

    Keyboard keyWriteAddress;//字地址
    Keyboard MaxAddress;//触发地址键盘
    Keyboard MinAddress;//触控地址键盘
}SliderInfo;

class SliderItem : public QVisableItem
{
public:
    SliderItem();

    int GroupType() ;
   QGraphicsItem *Clone();//复制item

   void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库

   void save(QDataStream &stream);//将item存入数据流

   void load(QDataStream &stream);//从数据流导出item

   void onSaveSlider(SliderInfo slider);//保存流动块属性

   void onSecurityPro(securityPro sproperty);//保存权限页面属性

   QList<Keyboard> getAddress();

   void setAddress(QList<Keyboard> addr);

   virtual QVector<ADDRPRO> getAllItemAddr();//查找地址虚函数

   QString getItemName();

   SliderInfo m_slider;

   securityPro m_sproperty;
public:
   QVector<ADDRPRO> addrs;
};

#endif // SLIDERITEM_H
