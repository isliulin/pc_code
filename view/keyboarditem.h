/****************************************************************************************************
  键盘按钮——马文俊

 **************************************************************************************************/

#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "Frame/mainwindow.h"

enum KEY_OPERATION{
    ENTER=1,//确定
    BACKSPACE=2,//单个删除
    CLEAR=3,//清除全部
    ESC=4,//取消
    ASCII=5,//文本
    CAPSLOCK = 6//大小写切换
};
enum TextPositions//文本位置
{
    LStarts = 1,//靠左
    CStarts=2,//居中
    RStarts=3,//靠右
};
//键盘按钮成员变量
typedef struct DATAKEYBOARDINFO{

    //键盘按钮属性
    QString id;//编号
    short nStartX;//X轴
    short nStartY;//Y轴
    short nWidth;//宽
    short nHeight;//高
    QColor nUpFrameColor;//按下前边框色
    QColor nUpForeColor;//按下前前景色
    QColor nUpBackColor;//按下前背景色
    short eUpStyle;//按下前样式
    QColor nDownFrameColor;//按下后边框色
    QColor nDownForeColor;//按下后前景色
    QColor nDownBackColor;//按下后背景色
    short eDownStyle;//按下后样式
    KEY_OPERATION keyOperation;//操作
    QString ASCIIStr;//ascii码

    //文本页面变量
    short nLanguage;//语言ID
    QString sText;    //文本
    QString sFontFamily;//字体
    int nFontSize;    //字体大小
    QColor sColor;   //字体颜色
    short eFontCss;   //粗体、斜体、下划线
    short nPosition;    //位置

    short nPicChecked; //0 选中图库按钮， 1选中外部图片按钮
    //图片页面变量
    bool  bisPic;   //图片来源true 图片
    QString sPath;//图片路径
}KeyInfo;

class KeyBoardItem : public QVisableItem
{
public:
    KeyBoardItem();

      int GroupType() ;
     QGraphicsItem *Clone();//复制item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库

     void save(QDataStream &stream);//将item存入数据流

     void load(QDataStream &stream);//从数据流导出item

     QRectItem* getBackItem();

     QRectItem* getFarmItem();

     void onSaveKey(KeyInfo key_st);//保存键盘按钮属性

     void SetText(QString sText);
     void SetFontSize(int nFontSize);
     void SetFontName(QString sName); //设置字体名称
     void SetTextAlign(int nAlignType);
     void SetFontBold(bool nFlag); //true设置字体为粗体否则不设置
     void SetFontItalic(bool nFlag); //true设置字体为斜体否则不设置
     void SetFontUnderLine(bool nFlag); //true设置字体是否有下划线
     void SetFontColor(QColor color); //设置字体颜色
     void redrawForChangeStatus(int index, int lan);

     void SetBackColor(QColor mColor);
     void SetPattern(int nPATTERN);
     void SetFramColor(QColor mColor);
     void SetFrontColor(QColor mColor);

     QString  getItemName();
public:

     QRectItem * pBackRect;
     KeyInfo m_key;
};

#endif
