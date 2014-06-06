#ifndef QTRENDDATAGROUPATTR_H
#define QTRENDDATAGROUPATTR_H

#include <vector>
#include <qcolor.h>
#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"
#include "view/qtrendattr.h"      //要借用其中的枚举

using namespace std;

class QTrendDataGroupAttr:public QVisableItem
{
public:
    QTrendDataGroupAttr(QGraphicsItem *parent = 0);
    ~QTrendDataGroupAttr();

public://曲线外观,
    bool        m_bIsAll;                       //个别，全部
    QString     m_sCurChnnel;                //当前组名
    QString     m_sChnnelBegin;                 //起始组号,在vecGroupNum中的
    int         m_nTotalTrendNumber;            //曲线总组数
    QVector<DisplayGroupInfo> m_vecDisplayGroups;//各个通道控制字地址设置
    QVector<ChannelGroupInfo> m_vecChannelGroups;//各个通道曲线外观设置
    QVector<QString>m_selGroups;//所有选中的组名
    double      m_nDisplayMax;//显示最大值
    double      m_nDisplayMin;//显示最小值

public://显示区设置
    bool    m_bSelectVertMinor;	//是否显示垂直次标尺
    bool    m_bSelectHorMinor;	//是否显示水平次标尺
    bool    m_bMainVer;         //是否显示垂直主标尺
    bool    m_bMainHor;         //是否显示水平主标尺
    short   m_nDataSample;	//数据样本数
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
    QColor m_nMarkedColor; //标注颜色
    int    m_alpha;        //图表区透明度
    short   m_nFontSize;    //字体大小
    vector<ColorGroupInfo> m_vecGroupColor;//各个通道颜色设置

public:
    virtual int GroupType();                //控件类型 位开关 字开关
    virtual QTrendDataGroupAttr *Clone();         //复制item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count, int index); //编译的时候保存item到数据库
    virtual void save(QDataStream &stream); //将item存入数据流
    virtual void load(QDataStream &stream); //从数据流导出item
	QVector<ADDRPRO> getAllItemAddr();
    QString  getItemName();
	void sampChanged(QString oldName,QString newName,int sampType);

public:
    QVector<ADDRPRO> kb;
};

#endif // QTRENDDATAGROUPATTR_H
