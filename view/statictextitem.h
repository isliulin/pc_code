#ifndef STATICTEXTITEM_H
#define STATICTEXTITEM_H
#include "Frame/mainwindow.h"
typedef struct Texts
{
    QString texts;
    int fontSizes;
    int fontSizeIndexs;
    QString fonts;
    int fontIndexs;
    int TextAlignIndexs;//文本对齐方式
    QString nFontColors;
    bool adapts;//字适应
    bool bolds;
    bool italics;
    bool underlines;
    QString newColor;
}TextItemLists;
typedef struct TEXTINFO{
    QString sStextStr;//文本
    short nFontFamly;//字体的类型
    QString sFontFamly;
    short nFontSize;//文本大小index
    short sFontSize;
    bool bFristLanguage;//是否显示第一种语言
    short nLanguageId;//语言序号
    short eTextPro;//文本属性—(粗/斜/下)
    bool mbolds;
    bool mitalics;
    bool munderlines;
    short sFontSpace;//字距
    short eTextAlign;//文本对齐方式
    QString nFontColor;//字体颜色
    short nStylePadding;//填充的样式
    int nAlphaPadding;//填充的透明度
    QString nBackColorPadding;//填充的背景色
    QString nForeColorPadding;//填充的前景色
    short nStartX;//开始x
    short nStartY;//开始y
    short nWidth;//文本框宽
    short nHeight;//文本框高
    short nLineWidth;//线条的宽度
    QString nLineColor;//线条的颜色
    int nZvalue;//层ID
    int nCollidindId;//组合ID
    int nShowPropId;//显现
    bool adaptTexts;//字适应
    QVector<TextItemLists> textList;
    bool isText;
    bool isKeyDown;
}TextInfos;



class StaticTextItem : public QVisableItem
{
public:
    StaticTextItem();

      int GroupType() ;
     QGraphicsItem *Clone();//复制item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库

     void save(QDataStream &stream);//将item存入数据流

     void load(QDataStream &stream);//从数据流导出item

     void onSaveText(TextInfos text);//保存流动块属性

     void onSecurityPro(securityPro sproperty);//保存权限页面属性

     void redrawForChangeLanguage(int index);//重画文本

     void changeItemLanguageAttr(int lanNum);

     TEXTPRO getAllItemText();
     void replaceAllItemText(int iLan,int iSta,QString sNewText);

      TEXTPRO vText;

	 QStringList getAllFonts();

         QString bitShot(int id);

     QString  getItemName();

     QSimpleTextItem *pTEXT;

     TextInfos m_text;

     securityPro m_sproperty;
};

#endif // STATICTEXTITEM_H
