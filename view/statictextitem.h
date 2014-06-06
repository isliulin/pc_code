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
    int TextAlignIndexs;//�ı����뷽ʽ
    QString nFontColors;
    bool adapts;//����Ӧ
    bool bolds;
    bool italics;
    bool underlines;
    QString newColor;
}TextItemLists;
typedef struct TEXTINFO{
    QString sStextStr;//�ı�
    short nFontFamly;//���������
    QString sFontFamly;
    short nFontSize;//�ı���Сindex
    short sFontSize;
    bool bFristLanguage;//�Ƿ���ʾ��һ������
    short nLanguageId;//�������
    short eTextPro;//�ı����ԡ�(��/б/��)
    bool mbolds;
    bool mitalics;
    bool munderlines;
    short sFontSpace;//�־�
    short eTextAlign;//�ı����뷽ʽ
    QString nFontColor;//������ɫ
    short nStylePadding;//������ʽ
    int nAlphaPadding;//����͸����
    QString nBackColorPadding;//���ı���ɫ
    QString nForeColorPadding;//����ǰ��ɫ
    short nStartX;//��ʼx
    short nStartY;//��ʼy
    short nWidth;//�ı����
    short nHeight;//�ı����
    short nLineWidth;//�����Ŀ��
    QString nLineColor;//��������ɫ
    int nZvalue;//��ID
    int nCollidindId;//���ID
    int nShowPropId;//����
    bool adaptTexts;//����Ӧ
    QVector<TextItemLists> textList;
    bool isText;
    bool isKeyDown;
}TextInfos;



class StaticTextItem : public QVisableItem
{
public:
    StaticTextItem();

      int GroupType() ;
     QGraphicsItem *Clone();//����item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

     void save(QDataStream &stream);//��item����������

     void load(QDataStream &stream);//������������item

     void onSaveText(TextInfos text);//��������������

     void onSecurityPro(securityPro sproperty);//����Ȩ��ҳ������

     void redrawForChangeLanguage(int index);//�ػ��ı�

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
