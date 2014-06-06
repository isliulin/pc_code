#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include "qvisableitem.h"
#include "view/qpixmapitem.h"
#include "Frame/qprogectmanager.h"
class ImageItem;

typedef struct IMAGE_INFO_SAVE
{
    short int nLp;//控件左上角x坐标
    short int nTp;//控件左上角y坐标
    short int nWidth;//控件宽度
    short int nHeight;//控件高度
    short int nFunType;//0::单幅固定  1:多幅切换
    bool      bUseFlicker;//闪烁
    //QString   nBackColor;//背景颜色
    short int nChangeCondition;//0时间间隔切换 1位值切换2:固定值切换
    QString   mWatchAddr;//监视地址
    Keyboard    addr;
    short int nStatusTotal;//记录状态总数
    short int nTimeInterval;//切换时间间隔，单位为100毫秒
    short int nPicType;//0：系统图库 1：文件图库
    bool      bIsLoopType;//当nChangeCondition为按时间间隔切换时有效,true：按状态号循环切换(默认),false: 按状态号往返切换
    short int nCmpFactor;//预设固定值
    //QColor    nBackColor;//背景颜色
}INTOSAVE;

typedef struct IMAGE_INFO_STRUCT//图片信息结构体，下标，名称，路径
{
    //int num;
    QString name;//存储转换后的名称elment+X
    QString path;//如果是图片则存储路径，如果是图库则存储GROUP_NAME_KEY 页-ID格式
    EITEM_TYPE    bIspic;//0:图片
    short int nCmpFactor;//预设固定值
    //QPixmapItem *PicItem;
    //ImageItem *pItem;
}IMAGEINFO;

class ImageItem : public QVisableItem
{
public:
    ImageItem();

     int GroupType();//控件类型 位开关 字开关


     QGraphicsItem *Clone();//复制item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库

     void save(QDataStream &stream);//将item存入数据流

     void load(QDataStream &stream);//从数据流导出item

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
     //功能设置页面属性
     //struct CHART_INFORMATION *Datesave;
private:
     short int number;//记录当前选中图片的数组下标

};
#endif
