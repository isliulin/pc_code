/****************************************************************************************************
  图表item类，继承与QVisableItem
 **************************************************************************************************/

#ifndef CHARTTIEM_H
#define CHARTTIEM_H

#include "qvisableitem.h"
#include "Frame/qprogectmanager.h"

//圆和半圆的角度跨度等信息结构体
struct CIRCLE_TYPE
{
    QPoint FirstPos;       //第一个圆的顶点坐标
    QPoint SecondPos;      //第二个圆的顶点坐标
    int num;                //圆的个数
    int nRadiu;             //圆半径
    QString FirstColor;     //第一个圆的背景色
    QString SecondColor;    //第二个圆的背景色
    QString ScaleColor;    //刻度颜色
    int nstartAngle;        //圆开始角度
    int nSpanAngle;         //圆跨角度
    int nScaleStartAngle;   //刻度开始角度
    int nScaleSpanAngle;     //刻度跨角度
    int nMainScal;           //主刻度数
    int nSubScal;            //次刻度数
    bool bPoint;             //是否画指针

    short nTransparent;      //是否透明
    bool  bShowFrame;        //显示边框
};

//仪表信息角度跨度信息结构体
typedef struct METER_STRU
{
    int nMeterType;         //仪表类型
    int nPointType;         //仪表指针类型 保留
    int nDirection;         //方向  0：向右，1：向左
    int nMainScal;          //主刻度数
    int nSubScal;           //次刻度数
    int nstartAngle;         //圆开始角度
    int nSpanAngle;          //圆设置跨角度
    int nPointStartAngle;    //刻度开始角度
    int nPointSpanAngel;     //刻度跨角度
    double dMax;            //最大值
    double dMin;            //最小值
    QString sPointColor;    //仪表指针颜色
    QString sBackColor;     //仪表背景颜色
    QString sCaleColor;     //仪表刻度颜色
    QString shapeName;      //仪表名称
}*PMETER_ST;

enum DIRECTION
{
    TOWARD_LEFT = 3,      //向左
    TOWARD_RIGHT,     //向右
    TOWARD_TOP,       //向上
    TOWARD_BOTTOM,    //向下
    TO_LEFT_ROTATE,   //向左旋转
    TO_RIGHT_ROTATE   //向右旋转
};

enum  SHAPE_TYPE
{
    PILLA,      //柱形
    CIRCLE,     //圆
    SECTOR,     //半圆
    GROOVE      //槽
};

enum GRAPH_TYPE
{
    ENCOMMON_TYPE,      //普通图形
    ENSTATISTICS_TYPE,  //统计图形
    ENMETER_TYPE        //仪表图形
};

enum GRAPH_SHAPE {

        //柱状图
        BG_PL001,
        BG_PL002,
        BG_PL003,
        BG_PL004,
        BG_PL005,
        BG_PL006,

        BG_3D002,
        BG_3D004,
        BG_3D005,
        BG_3D006,

        BG_SC001,
        BG_SC002,
        BG_SC003,

        //圆形
        CG_3D001,
        CG_3D002,
        CG_3D005,
        CG_3D006,

        CG_PL001,
        CG_PL002,
        CG_PL003,
        CG_PL004,
        CG_PL005,
        CG_PL006,

        //半圆图
        HG_PL001,
        HG_PL002,
        HG_PL003,
        HG_PL004,
        HG_PL005,
        HG_PL006,

        HG_3D001,
        HG_3D002,

        //槽状图
        GR_PL001M,
        GR_PL002M,
        GR_PL003M,
        GR_PL004M,
        GR_PL005M,
        GR_PL006M,
        GR_PL007M,
        GR_PL008M,
        GR_PL009M,
        GR_PL0010M,
        GR_PL0011M,
        GR_PL0012M,
        GR_PL0013M,
        GR_PL0014M,
        GR_PL0015M,
        GR_PL0016M,
        GR_PL0017M,
        GR_PL0018M,
        GR_PL0019M,
        GR_PL0020M,
        GR_PL0021M,

        GR_PL001,
        GR_PL002,
        GR_PL003,
        GR_PL004,
        GR_PL005,
        GR_PL006,
        GR_PL007,
        GR_PL008,
        GR_PL009,
        GR_PL0010,
        GR_PL0011,
        GR_PL0012,
        GR_PL0013,
        GR_PL0014,
        GR_PL0015,
        GR_PL0016,
        GR_PL0017,
        GR_PL0018,
        GR_PL0019,
        GR_PL0020,
        GR_PL0021,

        GR_3D001M,
        GR_3D002M,
        GR_3D003M,
        GR_3D004M,
        GR_3D005M,
        GR_3D006M,
        GR_3D007M,
        GR_3D008M,
        GR_3D009M,
        GR_3D0010M,
        GR_3D0011M,
        GR_3D0012M,
        GR_3D0013M,
        GR_3D0014M,
        GR_3D0015M,
        GR_3D0016M,
        GR_3D0017M,
        GR_3D0018M,
        GR_3D0019M,
        GR_3D0020M,
        GR_3D0021M,

        GR_3D001,
        GR_3D002,
        GR_3D003,
        GR_3D004,
        GR_3D005,
        GR_3D006,
        GR_3D007,
        GR_3D008,
        GR_3D009,
        GR_3D0010,
        GR_3D0011,
        GR_3D0012,
        GR_3D0013,
        GR_3D0014,
        GR_3D0015,
        GR_3D0016,
        GR_3D0017,
        GR_3D0018,
        GR_3D0019,
        GR_3D0020,
        GR_3D0021,

        //仪表
        MT_PL001,
        MT_PL002,
        MT_PL003,
        MT_PL004,
        MT_PL005,
        MT_PL006,
        MT_PL007,
        MT_PL008,
        MT_PL009,
        MT_PL0010,
        MT_PL0011,
        MT_PL0012,
        MT_PL0013,
        MT_PL0014,
        MT_PL0015,
        MT_PL0016,
        MT_PL0017,
        MT_PL0018,
        MT_PL0019,
        MT_PL0020,

        MT_3D001,
        MT_3D002,
        MT_3D003,
        MT_3D004,
        MT_3D005,
        MT_3D006,
        MT_3D007,
        MT_3D008,
        MT_3D009,
        MT_3D0010,
        MT_3D0011,
        MT_3D0012,
        MT_3D0013,
        MT_3D0014,
        MT_3D0015,
        MT_3D0016,
        MT_3D0017,
        MT_3D0018,
        MT_3D0019,
        MT_3D0020,

};

typedef struct ALARM_SET
{
    bool        bAlarm;            //报警设置 默认false
    short int   nType;
    QString     nMin;             //报警最小值
    QString     nMax;             //报警最大值
    Keyboard    nMinaddr;
    Keyboard    nMaxaddr;
    QString     nTextColor;       //报警显示颜色
    QString     nDesignColor;     //报警图案颜色
}ALARM_ST;

struct COMMON_INFORMATION
{
    GRAPH_TYPE eGraphType;        //图表类型
    GRAPH_SHAPE eShapeId;         //图形ID名称
    QString     mAddress;         //监控字地址
    short int   eDataType;        //数据类型的index
    short int   nSourceRang;      //指定源范围 index
    DIRECTION   eDirection;       //显示方向
    QString     nTextColor;       //显示颜色
    QString     nBackcolor;       //背景颜色
    short int   nLeftTopX;        //控件左上角坐标
    short int   nLeftTopY;        //控件左上角Y坐标
    short int   nWidth;           //控件宽度
    short int   nHeight;          //控件高度
    short int   nShowLeftTopX;	  //内部动态显示图顶点X坐标
    short int   nShowLeftTopY;	  //内部动态显示图顶点Y坐标
    short int   nShowWidth;	  //内部动态显示图宽
    short int   nShowHigth;	  //内部动态显示图高
    short int   nRulerLeftTopX;	  //标尺显示顶点X坐标
    short int   nRulerLeftTopY;	  //标尺显示顶点Y坐标
    short int   nRulerWidth;	  //标尺显示宽
    short int   nRulerHigth;	  //标尺显示高

    short int   nMainRuling;      //主标尺刻度 默认2
    bool        bShowRuling;      //次标尺显示 默认false
    bool        bShowRuleValue;   //是否显示主刻度值
    short int   nRuling;          //次标尺刻度 默认5
    QString     nRulingColor;     //标尺颜色 默认粉红
    DIRECTION   eRulerDirectio;   //标尺显示方向
    double      nScaleLength;      //标尺长度
    int         nPointType;        //指针类型
    short int   bSourceMark;      //源符号+/-默认无
    QString     eSourceMin;       //源最小 默认0
    QString     eSourceMax;       //源最大 默认100
    bool        bShowMark;        //显示符号+/- 默认false
    double         eShowMin;         //显示最小 默认0
    double         eShowMax;         //显示最大默认100
    SHAPE_TYPE  eShapeType;       //普通图形类型 如圆柱 槽等
    bool        bFill;            //显示填充 默认false
    bool        bHole;            //孔
    short int   nRadius;          //孔半径
    bool        bStart;           //显示开始点
    short int   nDesign;          //显示图案
    QString     nDesignColor;     //图案颜色
    QString     nFrameColor;      //边框颜色
    bool        nScaleMark;       //选中次刻度
    short int   nMainScale;       //主刻度數
    short int   nSubScale;        //次刻度數
    CIRCLE_TYPE nCircle;          //圆和半圆信息结构体
    ALARM_ST       sAlarm;        //报警设置
    Keyboard    addr;
    Keyboard  addrSourceMax;          //源最大地址
    Keyboard  addrSourceMin;          //源最小地址
    short     nStartAngle;         //开始点的角度
    short     nSpanAngle;          //圆的跨角度

    short        nTransparent;    //是否透明
    bool         bShowFrame;      //显示边框
};
struct METER_INFORMATION
{
    GRAPH_SHAPE eShapeId;         //圖形編號
    DIRECTION   eDirection;       //显示方向
    QString     mAddress;         //监控字地址
    short int   eDataType;        //数据类型的index
    short int   nSourceMark;      //源符號
    short int   nSourceRang;      //指定源范围
    QString     eSourceMin;       //源最小
    QString     eSourceMax;       //源最大
    bool        bShowMark;        //顯示符號
    double         eShowMin;         //顯示最小
    double         eShowMax;         //顯示最大
    bool        bAlarm;           //報警設置 默認false
    QString     nTextColor;       //顯示顏色
    QString     nDesignColor;     //圖案顏色,背景颜色
    QString     nScaleColor;      //刻度颜色
    short int   nMainScale;       //主刻度數
    short int   nSubScale;        //次刻度數
    double      nScaleLength;      //刻度长度
    bool        nScaleMark;       //选中次刻度
    bool        bShowRuleValue;   //是否显示主刻度值
    short        nTransparent;      //是否透明
    int         nPointType;        //指针类型
    short int   nstartAngle;      //圆开始角度
    short int   nSpanAngle;       //圆设置跨角度
    short int   nPointStartAngle; //刻度开始角度
    short int   nPointSpanAngel;  //刻度跨角度
    short int   nLeftTopX;        //控件左上角坐标
    short int   nLeftTopY;        //控件左上角Y坐标
    short int   nWidth;           //控件宽度
    short int   nHeight;          //控件高度
    short int   nShowLeftTopX;	  //内部动态显示图顶点X坐标
    short int   nShowLeftTopY;	  //内部动态显示图顶点Y坐标
    short int   nShowWidth;	  //内部动态显示图宽
    short int   nShowHigth;	  //内部动态显示图高
    ALARM_ST    sAlarm;        //报警设置
    Keyboard    addr;
    Keyboard  addrSourceMax;          //源最大地址
    Keyboard  addrSourceMin;          //源最小地址

    bool         bShowFrame;         //显示边框
};

class ChartItem : public QVisableItem
{
public:
    ChartItem();

     int GroupType();//控件类型 位开关 字开关


     QGraphicsItem *Clone();//复制item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库

     void save(QDataStream &stream);//将item存入数据流

     void load(QDataStream &stream);//从数据流导出item
public:

     GRAPH_TYPE  m_eGraphType;       //普通图形类型 如圆柱 槽等

     struct COMMON_INFORMATION common_st;

     struct METER_INFORMATION meter_st;

     void onSaveMeter(struct METER_INFORMATION meter);

     void onSaveCommon(struct COMMON_INFORMATION common);

     void onGetPosition();

     QString GetPicPath(ChartItem *libItem,SHAPE_TYPE nType,int nkey,DIRECTION derection);

     QString SaveLibPath(QGraphicsItem *pItem,QString path,QSizeF size);

     QVector<ADDRPRO> getAllItemAddr();

     void setAddress(QList<Keyboard> addr);

     QList<Keyboard> getAddress();

     QString  getItemName();

     //功能设置页面属性
     //struct CHART_INFORMATION *Datesave;
public:
     QVector<ADDRPRO> lsX;
};

#endif // CHARTTIEM_H
