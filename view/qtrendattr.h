#ifndef QTRENDATTR_H
#define QTRENDATTR_H

#include <vector>
#include <qcolor.h>
#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"

using namespace std;

//////////////////曲线外观设置////////////////////
typedef enum _CurveType{    //图表类型
    TypeRealTime = 1,       //实时
    TypeHistory,            //历史
    TypeDataGroup,          //数据群组曲线(因为这2种结构体公用数据库表，所以加这个)
}CurveType;

typedef enum _CurveDataType{  //曲线数据类型
    Curve16Bin = 1,     //16位Bin
    Curve32Bin,     //32位Bin
    Curve16BCD,     //16位BCD
    Curve32BCD,     //32位BCD
    Curve32Float,   //32位浮点
}CurveDataType;


///////////////////////////////////////////

//////////////////颜色设置////////////////////
typedef enum _LineStyleType{  //线型
    LineSolid = 1,      //实线
    LineDash,       //短划线
    LineDotted,     //虚线    
    LinePoint,      //点划线
    Line2Point,     //2点划线
}LineStyleType;

typedef struct __ColorGroupInfo__
{
    LineStyleType   eLineType;      //线型
    short           nChannelNum;    //通道号
    short           nLineThickness; //线条宽度
    QColor          nDisplayColor;  //显示颜色
}ColorGroupInfo;
////////////////////////////////////////////

//////////////////显示设置/////////////////////
typedef enum _DisplayConditionType{  //显示条件
    DisplayKeep = 1,    //保持显示
	DisplayOn,      //位ON时显示
    DisplayOff,     //位OFF时显示

}DisConType;

typedef struct __DisplayGroupInfo__
{
    DisConType   eDisplayCondition; //显示条件
    short        nDisplayNum;       //显示通道号
    Keyboard     KeyAddr;           //显示ON/OFF地址
}DisplayGroupInfo;

typedef struct __ChannelGroupInfo__
{
	CurveDataType   m_eDataType;	//数据类型
	short           m_nNumOfChannel;	//通道号
    QString         m_sGroupName;//采集组名称，仅在数据群组的时候使用
	double          m_nSourceMin;	//输入范围最小值
	double          m_nSourceMax;	//输入范围最大值
	double          m_nDisplayMin;	//显示符号最小值
	double          m_nDisplayMax;	//显示符号最大值

	short           nLineThickness; //线条宽度
	QColor          nDisplayColor;  //显示颜色
	LineStyleType   eLineType;      //线型
	DisConType   eDisplayCondition; //显示条件
	Keyboard     KeyAddr;           //显示ON/OFF地址
}ChannelGroupInfo;
///////////////////////////////////////////

////////////////////时间设置//////////////////////
typedef enum _DateType  //日期格式
{
    YMD_ONE = 1,        //YYYY/MM/DD
    YMD_TWO,        //YYYY.MM.DD
    YMD_THREE,      //YYYY-MM-DD
    MDY_ONE,        //MM/DD/YYYY
    MDY_TWO,        //MM.DD.YYYY
    MDY_THREE,      //MM-DD-YYYY
    DMY_ONE,        //DD/MM/YYYY
    DMY_TWO,        //DD.MM.YYYY
    DMY_THREE,      //DD-MM-YYYY
}DateType;

typedef enum _Time_Type //时间格式
{
    TIME_HM1 = 1,   //hh:MM
    TIME_HMS1,  //hh:mm:ss
    TIME_HM2,   //HH-MM
    TIME_HMS2,  //HH-MM-SS
}TimeType;

typedef enum _TimeUnitType //X轴时间单位
{
    //UNIT_SECOND,  //秒
    UNIT_MINUTE = 1,    //分
    UNIT_HOUR,      //时
    UNIT_DAY,       //日
    UNIT_MONTH,     //月
    UNIT_YEAR,      //年
}TimeUnitType;

typedef enum _FontType //字体类型
{
    FONT_SONGTI = 1,    //宋体
    FONT_SHILIANG,  //矢量字体
}FontType;

typedef enum _TxtAttrType //文本属性
{
    TXT_CUTI = 1,   //粗体
    TXT_XIETI,  //斜体
}TxtAttrType;

typedef enum _CurveStartType //采集时间
{
    START_NEAR = 1,    //最近
    START_FROMTO,       //从...到...
    START_DISKBEGIN,      //从存盘数据开始
    START_ADDR,        //选择地址
}CurveStartType;
/////////////////////////////////////////

class QTrendAttr:public QVisableItem//public QItemGroup//
{  
public://曲线外观,注意这个在save时必须最先保存，因为m_nCurChnnelNum这个数据的特殊性
    bool        m_bIsAll;           //个别，全部
    CurveType   m_eTableType;       //图表类型
    QString     m_sGroupNum;        //当前组名
    short       m_nCurChnnelNum;    //当前通道号
    short       m_nChnnelBegin;     //起始通道号
    int         m_nTotalTrendNumber;//曲线总通道数
	QList<int> m_Channels; //所有选中的通道号

	double          m_nDisplayMin;	//显示最小值
	double          m_nDisplayMax;	//显示最大值
    QVector<ChannelGroupInfo> m_vecChannelGroups;//各个通道曲线外观设置

public://显示区设置
    bool    m_bSelectVertMinor;	//是否显示垂直次标尺
    bool    m_bSelectHorMinor;	//是否显示水平次标尺
    bool    m_bMainVer;         //是否显示垂直主标尺
    bool    m_bMainHor;         //是否显示水平主标尺
    short   m_nDataSample;	//数据样本数
    short   m_nScrollSample;	//滚动样本数
    short   m_nVertMajorScale;	//垂直主标尺
    short   m_nVertMinorScale;	//垂直次标尺
    short   m_nHorMajorScale;	//水平主标尺
    short   m_nHorMinorScale;	//水平次标尺
    vector<DisplayGroupInfo> m_vecDisplayGroups;//各个通道曲线外观设置

public://颜色对话框要存储的数据
    bool   m_bGrade;            //是否需要网格
    QColor m_nVerColor;         //水平网格颜色
    QColor m_nHorColor;         //垂直网格颜色
    QColor m_nBoradColor;	//边框颜色
    QColor m_nScaleColor;	//标尺颜色
    QColor m_nGraphColor;	//图表区颜色
    int m_alpha;//图表区透明度
    vector<ColorGroupInfo> m_vecGroupColor;//各个通道颜色设置

public://时间显示
    //TimeUnitType    m_eTimeUnit;    //X轴时间单位
    TimeType        m_eTimeFormat;  //时间格式
    DateType        m_eDateFormat;  //日期格式
    FontType        m_eFontType;    //字体类型
    TxtAttrType     m_eTxtAttr;     //文本属性
    CurveStartType  m_eStart;       //那种时间采集方式
    bool            m_bXMarked;     //是否X轴标注
    short           m_nFontSize;    //字体大小
    QColor          m_nMarkedColor; //标注颜色
    int             m_nTimeLen;     //最近时间
    TimeUnitType    m_eTimeUnitNear;//最近时间单位
    QDate           m_dFromDate;    //起始日期
    QTime           m_tFromTime;    //起始时间
    QDate           m_dToDate;      //终止日期
    QTime           m_tToTime;      //终止时间
    Keyboard        m_kbFrom;       //起始时间地址
    Keyboard        m_kbTo;         //终止时间地址
    bool            m_bDateFormat;  //是否显示日期格式
    bool            m_bTimeFormat;  //是否显示时间格式

public:
    QTrendAttr(QGraphicsItem *parent = 0);
    ~QTrendAttr();
    QString  getItemName();

public:
    virtual int GroupType();                //控件类型 位开关 字开关
    virtual QTrendAttr *Clone();            //复制item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count,int index); //编译的时候保存item到数据库
    virtual void save(QDataStream &stream); //将item存入数据流
    virtual void load(QDataStream &stream); //从数据流导出item
	QVector<ADDRPRO> getAllItemAddr();
	void sampChanged(QString oldName,QString newName,int sampType);

public:
    QVector<ADDRPRO> kb;
};

#endif // QTRENDATTR_H
