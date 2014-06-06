/****************************************************************************************************/


#ifndef ANIMATIONITEM_H
#define ANIMATIONITEM_H

#include "qvisableitem.h"
#include "Frame/qprogectmanager.h"
#include "Frame/mainwindow.h"
#include "ImageItem.h"

//typedef enum
//{
//    Pic,          //图片
//    Library,      //图库
//    Userdefine,   //用户自定义图库
//}PicType;

//轨迹点子表
typedef struct TRACK_POINT_INFO
{
    short nOrbitId;	//轨迹点序号
    short nXPos;	//轨迹点X坐标
    short nYPos;	//轨迹点Y坐标
}TrackPointInfo;

//监视条件子表
typedef struct
{
    short nStateNo;	//关联的状态序号
    short nSCmpFactor;	//上位预设值，用于比较

}StakeoutInfo;

//移动条件子表
typedef struct
{
    short nTrackPointNo;     //关联的轨迹点序号
    short nMCmpFactor;       //上位预设值，用于比较
}TPMoveInfo;

//图片路径子表
typedef struct
{
    QString   name;               //存储转换后的名称elment+X
    short     nStatusId;          //状态ID
    QString   sPath;		  //图片路径
    EITEM_TYPE    bIspic;//0:图片
    short int nCmpFactor;//预设固定值
}PictureInfo;

typedef enum //文本位置 靠左、居中、靠右
{
    Lpoint = 0,
    Cpoint,
    Rpoint,
}TEXT_PIC_ALIGN;

//文本属性子表
typedef struct
{
    bool    bValid;            //标记是否有效
    short   nStatusId;	 	//关联的状态ID
    QString sFontFamily;	//字体类型
    short   sFontIndex;         //字体下标
    short   nSize;		//大小
    QString nColor;		//文本颜色
    QString nBColor;		//文本背景色
    QString sText;		//文本内容
    short   nStyle;             //B0000 : 无效果,B0001 : 粗体,B0010 : 斜体,B0100 : 闪烁,B1000 :下划线
    TEXT_PIC_ALIGN eAlign;      //0：居中 ,1：靠右居中 ,2：靠左居中
    short   nSpace;             //字间距
}TextInfo;

typedef struct ANIMATONITEM
{
    short nLp;		    //控件左上角x坐标
    short nTp;		    //控件左上角y坐标
    short nWidth;	    //控件宽度
    short nHeight;	    //控件高度

    short nTrackType;       //0:散点轨迹,1:区域轨迹 index
    QString nBackColor;     //区域背景色
    short  nMoveCondition;  //0:按时间切换,1:按固定值切换 //index
    short nMoveType;        //0:循环移动,1:往返移动
    short nMoveTimeInterval;//移动间隔时间，单位为100毫秒
    short nStartTrackPoint; //初始轨迹点序号
    short nTrackPointTotal; //轨迹点总数
    QString sMoveCtrlAddr;      //
    Keyboard mMoveCtrlAddr;      //移动控制数据的字地址，通常为状态控制地址的下一个地址
    QVector <TPMoveInfo> stMoveInfo;//移动预设值列表


    Keyboard mXPosCtrlAddr;         //轨迹点X坐标
    Keyboard mYPosCtrlAddr;         //轨迹点Y坐标
    QString  sAddrX;
    QString  sAddrY;
    float    nXMoveStepScale; //X坐标移动比例,默认值必须为1
    float    nYMoveStepScale; //Y坐标移动比例，默认值必须为1
    short    nAreaOrigXPos;   //区域左上原点X坐标
    short    nAreaOrigYPos;   //区域左上原点Y坐标
    short    nAreaWidth;      //区域宽度
    short    nAreaHeight;     //区域高度

    //状态
    short    nStateTotal;     //状态总数
    short    nChangeCondition;//切换方式：0:Timeshorterval:时间切换 1:PreSetValue:预设值切换
    short    nChangeType;     //状态切换方式 1:ActionLoop: 状态循环 2:ActionTrip: 状态往复
    short    nChangeTimeinterval;//切换时间间隔
    short    nInitState;       //初始状态序号
    Keyboard mChangeCtrlAddr;    //状态控制地址，默认状态控制地址的下一地址为移动控制地址
    QString  sChangeCtrlAddr;
    QVector<StakeoutInfo> mSPreSetVList;//存放状态切换的预设值

    //文本
    bool    bEnableText;//是否启用文本
    QVector<TextInfo> Text;

    //图片
    bool    bEnablePic;//是否启用外形
    //QString sPicBackColor;//图片背景色
    QVector<PictureInfo> PicInfo;
}AnInfo;




class AnimationItem : public QVisableItem
{
public:
    AnimationItem();

     int GroupType();//控件类型 位开关 字开关


     QGraphicsItem *Clone();//复制item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库

     void save(QDataStream &stream);//将item存入数据流

     void load(QDataStream &stream);//从数据流导出item
public:

     void SetText(QString sText);
     void SetFontSize(int nFontSize);
     void SetFontName(QString sName); //设置字体名称
     void SetTextAlign(int nAlignType);

     void onSetCurrentNum(short int num);//保存当前显示图片下标
     int  onGetCurrentNum();
     void onSetTrackInfo(QVector<TrackPointInfo> &Tinfo);
     void onGetTrackInfo(QVector<TrackPointInfo> &Tinfo);
     void onSaveAnimatInfo(AnInfo &aninfo);
     void onGetAnimatInfo(AnInfo &aninfo);
     QStringList getAllFonts();

     QVector<ADDRPRO> getAllItemAddr();

     void onGetTrakpos();

     QString  getItemName();

     int getCurrentState();

     QStringList getItemStates();

     void redrawForChangeStatus(int index, int lan);
     //功能设置页面属性
     //struct CHART_INFORMATION *Datesave;
     AnInfo m_AnimatInfo;

private:
     short number;
     QVector<TrackPointInfo> TrackInfo;//轨迹点列表

public:
     QVector<ADDRPRO> lsX;
};
#endif
