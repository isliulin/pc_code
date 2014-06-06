/*********************************************************************************/
//filename  DataDisPlayItem.h
/*********************************************************************************/

#ifndef DATADISPLAY_H
#define DATADISPLAY_H

#include "qvisableitem.h"
#include "Frame/qprogectmanager.h"
#include "Frame/ThingDlg/expression.h"

enum VALUESHOWTYPE   //当前tab页面
{
    DATAINPUTSHOW,    //数据输入
    ASCIIINPUTSHOW,   //ascii输入
    DATETIMEINPUT,    //日期时间显示
};

enum TextPosition//文本位置 靠左、居中、靠右
{
    LStart = 1,
    CStart,
    RStart,
};
enum InputMode //输入方式 触摸/位
{
    Touch = 1,
    Bit,
};


typedef struct DATADISPLAYINFO
{
    VALUESHOWTYPE etabPag;            //当前是 数值输入、时间显示、ASCLL输入显示？
    short int nStartX;                //控件横坐标起点
    short int nStartY;                //控件纵坐标起点
    short int nWidth;                 //控件宽度
    short int nHeight;                //控件高度
    short int nTextStartX;	      //文本区域起点横坐标
    short int nTextStartY;	      //文本区域起点纵坐标
    short int nTextWidth;	      //文本区域宽度
    short int nTextHeight;	      //文本区域高度
    QString   nShapId;                //形状
    QString   nAddress;               //监控子地址
    bool      bIsInput;               //允许输入
    bool      bIsScale;               //允许缩放
    short int eNumberType;            //数据类型 index
    short int nByteLength;            //源范围  index
    QString   sSourceMax;             //源范围最大值
    QString   sSourceMin;             //源范围最小值
    short int sShow;                  //显示指定  index
    bool      bRound;                 //显示：四舍五入
    QString   sShowMax;               //显示最大值
    QString   sShowMin;               //显示最小值
    short int nFontType;              //字体类型 index
    QString   sFontType;
    short int nFontSize;              //字体大小 index
    short int eFontCss;               //文本属性
    short int nAllbytelength;         //总显示位数
    short int sDecimalType;           //小数指定位数 常量/地址  index
    short int sDecimalLength;         //小数位数
    QString   sDecimalAddress;        //小数位数地址
    TextPosition eShowStyle;          //文本显示位置
    QString   nFontColor;             //字体颜色
    QString   nBackColor;             //字体背景颜色
    QString   nHightColor;            //高位背景颜色
    QString   nLowerColor;            //低位背景颜色
    InputMode eInputTypeId;           //输入方式 触摸、位
    bool      nKeyMark;               //是否启用键盘
    short int nKeyId;                 //键盘编号
    QString   sKeyname;
    QString   nPreView;               //预览显示
    int       nTouchPropId;	      //触控属性ID号
    int       nShowPropId;	      //显隐属性ID号
    Keyboard  addr;                   //监控子地址
    Keyboard  addrSourceMax;          //源最大地址
    Keyboard  addrSourceMin;          //源最小地址
    Keyboard  addrShowMin;            //显示最小地址
    Keyboard  addrShowMax;            //显示最大地址
    QString   sAddrBit;               //位输入地址
    Keyboard  addrBit;                //位输入地址
    Keyboard  addrDicmal;             //小数位数地址

    QString    nHightNumber;            //高限值
    QString    nLowerNumber;            //低限值
    bool       bUseMacro;          //是否使用宏指令
    QString   macroName;           //宏指令ID号
    QString   functionName;        //脚本函数ID
    short     nTransparent;      //是否透明
    short     eInputAreaType;       //输入范围类型
    Keyboard  addrInputMax;            //输入最大值限制
    Keyboard  addrInputMin;            //输入最小值
    QString   sInputMax;
    QString   sInputMin;
    bool      bInputSign;           //输入提示框
    int       nBoardX;              //自定义键盘起点X
    int       nBoardY;              //自定义键盘起点Y
    bool      bAutoChangeBit;       //是否自动复位

    bool      bOffset;              //是否偏移
    Keyboard  addrOffset;           //偏移地址

    bool      bInputIsShow;         //同监控地址
    Keyboard  addrInputSame;

    bool      bOutExpression;          //是否使用输出表达式
    bool      bInExpression;          //是否使用输入表达式
    Expression m_outputExp;//监视表达式
    Expression m_inputExp;//输入表达式
}DataInfo;

typedef struct ASCIIINPUTINFO
{
    VALUESHOWTYPE etabPag;            //当前是 数值输入、时间显示、ASCLL输入显示？
    short int nStartX;                //控件横坐标起点
    short int nStartY;                //控件纵坐标起点
    short int nWidth;                 //控件宽度
    short int nHeight;                //控件高度
    short int     nTextStartX;	      //文本区域起点横坐标
    short int     nTextStartY;	      //文本区域起点纵坐标
    short int     nTextWidth;	      //文本区域宽度
    short int     nTextHeight;	      //文本区域高度
    QString   nShapId;                //形状
    QString   sAddress;               //监控子地址
    short int eNumberType;            //数据类型
    bool      bIsinput;               //允许输入
    short int nFontStyle;             //字体类型 index
    QString   sFontType;
    short int nFontsize;              //字体大小  index
    short int nLanguageTypeId;        //显示语言 index
    short int eFontCss;               //文本属性
    short int nShowCharNumber;        //显示字符数量
    TextPosition nShowStyle;          //文本显示位置
    short int  nCode;                 //字符编码
    QString   nFontColor;             //字体颜色
    QString   nBackColor;             //字体背景颜色
    InputMode eInputTypeId;           //输入方式 触摸、位
    short int nTouchPropId;           //触控属性ID号
    short int nShowPropId;            //显隐属性ID号
    short int nKeyId;                 //键盘编号
    QString   sKeyname;               //键盘名称
    bool      nKeyMark;               //是否启用键盘
    Keyboard  addr;                   //监控字地址
    QString   sAddrBit;               //位输入地址
    Keyboard  addrBit;                //位输入地址
    bool      bUseMacro;        //是否使用宏指令
    QString   macroName;         //宏指令ID号
    QString   functionName;    //脚本函数ID
    short        nTransparent;      //是否透明
    bool      bInputSign;           //输入提示框
    int       nBoardX;              //自定义键盘起点X
    int       nBoardY;              //自定义键盘起点Y
    bool      bAutoChangeBit;       //是否自动复位

    bool      bOffset;              //是否偏移
    Keyboard  addrOffset;           //偏移地址

    bool      bInputIsShow;         //同监控地址
    Keyboard  addrInputSame;
}ASCIIINFO;

typedef struct DATETIMEINFO
{
    VALUESHOWTYPE etabPag;            //当前是 数值输入、时间显示、ASCLL输入显示？
    short int     nStartX;	      //控件横坐标起点
    short int     nStartY;	      //控件纵坐标起点
    short int     nWidth;	      //控件宽度
    short int     nHeight;	      //控件高度
    short int     nTextStartX;	      //文本区域起点横坐标
    short int     nTextStartY;	      //文本区域起点纵坐标
    short int     nTextWidth;	      //文本区域宽度
    short int     nTextHeight;	      //文本区域高度
    QString     nShapId;	      //外形id
    short int     nFontStyle;	      //字体类型 index
    QString       sFontType;
    short int     nFontSize;	      //字体大小  index
    short int     eFontCss;	      //字体属性 多选（标准，斜体，粗体，下划线） index
    short int     eShowDate;	      //日期 index
    short int     eShowTime;	      //时间  index
    QString       nFontColor;	      //字体颜色
    QString       nBackground;	      //字体背景颜色
    bool          bDateMark;          //日期选中
    bool          bTimeMark;          //时间选中
    bool          bWeekMark;          //星期选中
    TextPosition nShowStyle;          //文本显示位置
    QString       nPreView;           //预览显示
    short int     nLanguageTypeId;    //显示语言 index
    short          nTransparent;      //是否透明
    //Keyboard  addr;                   //监控字地址
}TIMEINFO;



class DataDisplayItem : public QVisableItem
{
public:
    DataDisplayItem();

    int GroupType();//控件类型 位开关 字开关


    QGraphicsItem *Clone();//复制item

    void compile(QSqlDatabase &db,int nSceneId,int &count,int index);//编译的时候保存item到数据库

    void save(QDataStream &stream);//将item存入数据流

    void load(QDataStream &stream);//从数据流导出item

    void onSaveDataInfo(DataInfo data_st);        //保存数值显示信息

    void onSaveAsciiInfo(ASCIIINFO ascii_st);        //保存ASCII输入信息

    void onSaveTimeInfo(TIMEINFO time_st);        //保存时间显示信息

    void onGetPosition();

    void SetTextAlign(int nAlignType);

    int GetTextAlign(); //获得文本的对齐方式

    void SetRectBackColor(QColor color); //设置背景矩形框的背景色

    void SetFontColor(QColor color); //设置字体颜色

    void SetText(QString sText); //设置文本

    void SetPattern(int nType);

    int GetPattern(); //获得样式

    void SetAlpha(int nType);

    QGraphicsItem* GetBackItem();

    QString GetKeyboardName();

    void SetKeyBoardInfo(QString sName, int index);

    void insertMacroTable(QSqlDatabase &db,int itemId,int &count,int sceneId,QString macroName,QString functionName);

    QList<Keyboard> getAddress();

    void setAddress(QList<Keyboard> addr);

    QStringList getAllFonts();

    QVector<ADDRPRO> getAllItemAddr();

    QString  getItemName();

    void redrawForChangeStatus(int index, int lan);

    int getCurrentState();

    void UpdateKeyboardInfo();

    void insertExpressTable(QSqlDatabase &db,Expression exp,int &count,int addLength,int itemId);

    int checkMacroName(QString &msg);
public:
    QVector<ADDRPRO> lsX;

public:

    VALUESHOWTYPE m_etabPag;            //标记当前是 数值输入、时间显示、ASCLL输入显示？

    //TextPosition m_TextAligent;         //文字对齐方式

    DataInfo m_data;

    ASCIIINFO m_ascii;

    TIMEINFO m_time;

    EITEM_TYPE m_eIspic;


};

#endif
