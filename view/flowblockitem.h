/****************************************************************************************************
  Flowblock流动块——马文俊

 **************************************************************************************************/

#ifndef FLOWBLOCK_H
#define FLOWBLOCK_H
#include <QDialog>
#include "Frame/mainwindow.h"
//方向枚举
enum DIRECTIONS{
    LEVEL=1,      //水平
    VERTICAL=2,   //垂直
    LEFT,       //向左
    RIGHT       //向右
};
//速度枚举
enum SPEED{
    FIXEDFLOWSPEED=1,//固定流动速度
    TRENDFLOWSPEED=2,//动态流动速度
    LOW=3,		//低
    MIDDLE=4,		//中
    HIGH=5		//高
};

#include "qvisableitem.h"
//流动块成员变量
typedef struct DATAFLOWBLOCKINFO{
QString id;//编号
short nStartX ;//横坐标
short nStartY ;//纵坐标
short nRectWidth ;//宽
short nRectHeight ;//高
QString nFForeColor ;//流动块前景色
QString nFBackColor ;//流动块背景色
QString nDForeColor ;//管道前景色
QString nDBackColor ;//管道背景色
QString nFrameColor ;//边框色
short eStyle ;//样式
QString nTriggerAddress ;//触发地址
DIRECTIONS eShowWay ;//显示方式
DIRECTIONS eFlowDirection ;//流动方向
QString sflowdirection;
bool bTouchAddress ;//是否使用地址改变流动方向
QString eTouchAddress ;//触控地址
short nValidState;//有效状态
short nFlowNum ;//流动块数目
bool bSideLine ;//有无边线
SPEED eFlowSpeedType ;//选择流动速度类型
SPEED eFixedFlowSpeed ;//固定流动速度
QString nTrendFlowSpeed ;//动态流动速度
short nZvalue ;
short nCollidindId ;

Keyboard trendSpeed;//动态流动速度触发键盘
Keyboard triggerAdd;//触发地址键盘
Keyboard touchAdd;//触控地址键盘

}FlowInfo;

class FlowBlockItem : public QVisableItem
{
public:
    FlowBlockItem();
    int GroupType() ;
    QGraphicsItem *Clone();//复制item
    void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库
    void save(QDataStream &stream);//将item存入数据流
    void load(QDataStream &stream);//从数据流导出item
    void onSaveFlow(FlowInfo flow_st);//保存流动块属性
    void onSecurityPro(securityPro sproperty);//权限
    QList<Keyboard> getAddress();//多重复制获得地址
    void setAddress(QList<Keyboard> addr);//多重复制设置地址
    virtual QVector<ADDRPRO> getAllItemAddr();//查找地址虚函数
    QString getItemName();
    FlowInfo m_flow;
    securityPro m_sproperty;

public:
     QVector<ADDRPRO> addrs;
};

#endif // FLOWBLOCK_H
