/****************************************************************************************************
  �䷽ѡ��item�࣬�̳���QVisableItem
 **************************************************************************************************/

#ifndef QRECIPEITEM_H
#define QRECIPEITEM_H

#include "QDataStream"
#include  "Frame/mainwindow.h"

typedef struct
{
    short   eShowType;        //�䷽��ʾ����ʽ���������б�1:���� 2���б�
    short   sShowRecipeId;    //�䷽��ı��
    QString sFontFamily;      //������ʽ
    short   nFontSize;        //�����С
    QColor  nTextColor;       //������ɫ
    QColor  nBackColor;       //������ɫ
    short   nCurrShowRow;     //��ǰ��ʾ������
    bool    bUseMacro;        //�Ƿ�ʹ�ú�ָ��
    QString   macroName;         //��ָ��ID��
    QString   functionName;    //�ű�����ID
    short   nTransparent;        //͸����
}RCIPEINFO;

class QRcipeItem : public QVisableItem
{
public:
    QRcipeItem();

     int GroupType();//�ؼ����� λ���� �ֿ���


     QGraphicsItem *Clone();//����item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

     void save(QDataStream &stream);//��item����������

     void load(QDataStream &stream);//������������item

     void onSaveInfo(RCIPEINFO &Rcipe);

     void insertMacroTable(QSqlDatabase &db,int itemId,int &count,int sceneId);

     QStringList getAllFonts();

     QString  getItemName();

     int GetRicipeGroupId(int index);//�����䷽��Id��

     void setInvalid();

     int getInvalid();
     int checkMacroName(QString &msg);

public:
     RCIPEINFO m_Rcipe;
private:

};

#endif
