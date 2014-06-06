/****************************************************************************************************/


#ifndef QRECIPETABLEITEM_H
#define QRECIPETABLEITEM_H

#include <QDataStream>
#include "qvisableitem.h"

typedef struct
{
   int   nRecipeGroupId;   //�䷽ID
   bool  bShowRecipeID;	   //�Ƿ���ʾ�䷽ID
   bool  bShowDescrip;	   //�Ƿ���ʾ�䷽����
   short eTextAlignType;   //���ֵĶ��뷽ʽ
   short nLanguaId;	   //���Ե�ID��
   short nRowShowNum;	   //��ʾ������
   short nColumShowNum;	   //Ҫ��ʾ������
   QColor nHHeadTextColor; //��head������ɫ
   QColor nHHeadBackColor; //��head������ɫ
   short  nHHeadFontSize;  //��head�����С
   QString sHHeadFontFamily;	//��head��������
   QColor  nVHeadTextColor;	//��head������ɫ
   QColor  nVHeadBackColor;	//��head������ɫ
   short   nVHeadFontSize;	//��head�����С
   QString  sVHeadFontFamily;	//��head��������
   QColor  nDataTextColor;	//��������������ɫ
   QColor  nDataBackColor;	//�������ı�����ɫ
   short   nDataFontSize;	//�������������С
   QColor  nLineColor;          //�������ɫ
   short   nTransparent;        //͸����
   QVector <QString> sRecipeName;//���б����������Ϣ
}RECIPESHOW;

class QRecipeTableItem : public QVisableItem
{
public:
    QRecipeTableItem();

     int GroupType();//�ؼ����� λ���� �ֿ���


     QGraphicsItem *Clone();//����item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

     void save(QDataStream &stream);//��item����������

     void load(QDataStream &stream);//������������item
public:

     void SetText(QString sText);
     void SetFontSize(int nFontSize);
     void SetFontName(QString sName); //������������
     void SetTextAlign(int nAlignType);

     void SaveInfo(RECIPESHOW info);
     void GetInfo(RECIPESHOW &info);

     QStringList getAllFonts();

     QString  getItemName();

     void changeItemLanguageAttr(int lanNum);

     void RefreshItem(int index);//˫�����䷽���ݲɼ��޸�ȷ�������item

     int GetRicipeGroupId(int index);//�����䷽��Id��

     int getInvalid();

     void setInvalid();

     //��������ҳ������
     //struct CHART_INFORMATION *Datesave;
private:
     RECIPESHOW m_SaveInfo;

private:

};

#endif
