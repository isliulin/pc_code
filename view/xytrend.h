#ifndef XYTREND_H
#define XYTREND_H

#include "qtrendattr.h"
typedef struct _ChannelInfo
{
    short           m_nNumOfChannel;	//通道号
    Keyboard        m_AddrX;//X轴首地址
    Keyboard        m_AddrY;//Y轴首地址

    short           nLineThickness; //线条宽度
    QColor          nDisplayColor;  //显示颜色
    LineStyleType   eLineType;      //线型
    DisConType   eDisplayCondition; //显示条件
    Keyboard     KeyAddr;           //显示ON/OFF地址
}ChannelInfo;

class XYtrend:public QVisableItem//public QItemGroup//
{
public://
    bool        m_bIsAll;           //个别，全部
    int chlCount;//通道总数
    int addrLength;//地址长度，相当于采样点数

    DATA_TYPE m_dataType;//数据类型
    Keyboard    m_TriggerAddr;//触发地址
    bool        m_bReset;//是否自动复位
    bool        m_bScale;//是否缩放

    bool m_bDisplayConst;//显示范围是否常量
    Keyboard    m_DisplayMaxAddrX;//显示范围最大值 地址
    Keyboard    m_DisplayMinAddrX;//显示范围最小值 地址

    double          m_nDisplayMinX;	//显示最小值
    double          m_nDisplayMaxX;	//显示最大值
    bool        m_bConstX;//是否常量范围
    Keyboard    m_SourceMaxAddrX;//源范围最大值 地址
    Keyboard    m_SourceMinAddrX;//源范围最小值 地址
    double      m_nSourceMaxX;	//源范围最大值
    double      m_nSourceMinX;	//源范围最小值

    bool m_bDisplayConstY;//Y显示范围是否常量
    Keyboard    m_DisplayMaxAddrY;//Y显示范围最大值 地址
    Keyboard    m_DisplayMinAddrY;//Y显示范围最小值 地址
    double          m_nDisplayMinY;	//Y显示最小值
    double          m_nDisplayMaxY;	//Y显示最大值
    bool        m_bConstY;//是否常量范围
    Keyboard    m_SourceMaxAddrY;//源范围最大值 地址
    Keyboard    m_SourceMinAddrY;//源范围最小值 地址
    double      m_nSourceMaxY;	//源范围最大值
    double      m_nSourceMinY;	//源范围最小值


    QVector<ChannelInfo> m_vecChannels;//各个通道曲线外观设置

public://显示区设置
    bool    m_bSelectVertMinor;	//是否显示垂直次标尺
    bool    m_bSelectHorMinor;	//是否显示水平次标尺
    bool    m_bMainVer;         //是否显示垂直主标尺
    bool    m_bMainHor;         //是否显示水平主标尺
    //short   m_nDataSample;	//数据样本数
    //short   m_nScrollSample;	//滚动样本数
    short   m_nVertMajorScale;	//垂直主标尺
    short   m_nVertMinorScale;	//垂直次标尺
    short   m_nHorMajorScale;	//水平主标尺
    short   m_nHorMinorScale;	//水平次标尺

public://颜色对话框要存储的数据
    bool   m_bGrade;            //是否需要网格
    QColor m_nVerColor;         //水平网格颜色
    QColor m_nHorColor;         //垂直网格颜色
    QColor m_nBoradColor;	//边框颜色
    QColor m_nScaleColor;	//标尺颜色
    QColor m_nGraphColor;	//图表区颜色
    int m_alpha;//图表区透明度
    QColor m_TextColor;//刻度文本色
    int m_textSize;//刻度文本大小


public:
    XYtrend(QGraphicsItem *parent = 0);
    ~XYtrend();
    QString  getItemName();

public:
    virtual int GroupType();                //控件类型 位开关 字开关
    virtual XYtrend *Clone();            //复制item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count,int index); //编译的时候保存item到数据库
    virtual void save(QDataStream &stream); //将item存入数据流
    virtual void load(QDataStream &stream); //从数据流导出item
    QVector<ADDRPRO> getAllItemAddr();

public:
    QVector<ADDRPRO> kb;
};

#endif // XYTREND_H
