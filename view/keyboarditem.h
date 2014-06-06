/****************************************************************************************************
  ���̰�ť�������Ŀ�

 **************************************************************************************************/

#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "Frame/mainwindow.h"

enum KEY_OPERATION{
    ENTER=1,//ȷ��
    BACKSPACE=2,//����ɾ��
    CLEAR=3,//���ȫ��
    ESC=4,//ȡ��
    ASCII=5,//�ı�
    CAPSLOCK = 6//��Сд�л�
};
enum TextPositions//�ı�λ��
{
    LStarts = 1,//����
    CStarts=2,//����
    RStarts=3,//����
};
//���̰�ť��Ա����
typedef struct DATAKEYBOARDINFO{

    //���̰�ť����
    QString id;//���
    short nStartX;//X��
    short nStartY;//Y��
    short nWidth;//��
    short nHeight;//��
    QColor nUpFrameColor;//����ǰ�߿�ɫ
    QColor nUpForeColor;//����ǰǰ��ɫ
    QColor nUpBackColor;//����ǰ����ɫ
    short eUpStyle;//����ǰ��ʽ
    QColor nDownFrameColor;//���º�߿�ɫ
    QColor nDownForeColor;//���º�ǰ��ɫ
    QColor nDownBackColor;//���º󱳾�ɫ
    short eDownStyle;//���º���ʽ
    KEY_OPERATION keyOperation;//����
    QString ASCIIStr;//ascii��

    //�ı�ҳ�����
    short nLanguage;//����ID
    QString sText;    //�ı�
    QString sFontFamily;//����
    int nFontSize;    //�����С
    QColor sColor;   //������ɫ
    short eFontCss;   //���塢б�塢�»���
    short nPosition;    //λ��

    short nPicChecked; //0 ѡ��ͼ�ⰴť�� 1ѡ���ⲿͼƬ��ť
    //ͼƬҳ�����
    bool  bisPic;   //ͼƬ��Դtrue ͼƬ
    QString sPath;//ͼƬ·��
}KeyInfo;

class KeyBoardItem : public QVisableItem
{
public:
    KeyBoardItem();

      int GroupType() ;
     QGraphicsItem *Clone();//����item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

     void save(QDataStream &stream);//��item����������

     void load(QDataStream &stream);//������������item

     QRectItem* getBackItem();

     QRectItem* getFarmItem();

     void onSaveKey(KeyInfo key_st);//������̰�ť����

     void SetText(QString sText);
     void SetFontSize(int nFontSize);
     void SetFontName(QString sName); //������������
     void SetTextAlign(int nAlignType);
     void SetFontBold(bool nFlag); //true��������Ϊ�����������
     void SetFontItalic(bool nFlag); //true��������Ϊб���������
     void SetFontUnderLine(bool nFlag); //true���������Ƿ����»���
     void SetFontColor(QColor color); //����������ɫ
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
