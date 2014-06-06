#ifndef QMESSAGEBORADATTR_H
#define QMESSAGEBORADATTR_H

#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"

typedef struct __MmessageBoardLanguage__
{
    int     m_nLanguage;    //����id
    QString m_sNumber;      //״̬��ʾ����
    QString m_sDateName;    //״̬��ʾ����
    QString m_sTimeName;    //״̬��ʾ����
    QString m_sMessageName; //״̬��ʾ����
}MmessageBoardLanguage;

class qMessageBoradAttr:public QVisableItem
{
public:
    //����
    bool    m_bShowId;      //�Ƿ���ʾ���
    bool    m_bShowTime;    //�Ƿ���ʾʱ��
    short   m_nTimeType;    //ʱ���ʽ��ö�٣�
    bool    m_bShowDate;    //�Ƿ���ʾ����
    short   m_nDateType;    //���ڸ�ʽ��ö�٣�
    short   m_nTFontSize;   //��ͷ�����С
    QString m_sTFontType;   //��ͷ��������
    QColor  m_nTFontColor;  //��ͷ������ɫ
    QColor  m_nTBackColor;  //��ͷ������ɫ
    //���
    short   m_nAlpha;       //�ؼ�͸����
    QColor  m_nLineColor;   //�߿���ɫ
    short   m_nFillCss;     //�����ʽ
    QColor  m_nBackColor;   //������ɫ
    QColor  m_nForeColor;   //ǰ��ɫ
    //����
    short   m_nFontSize;    //���������С
    QString m_sFontType;    //������������
    QColor  m_nFontColor;   //����������ɫ
    int     m_nRowNumber;   //��������
    //������
    QVector<MmessageBoardLanguage> m_vecMessage;

public:
    qMessageBoradAttr(QGraphicsItem *parent = 0);
    ~qMessageBoradAttr();

public:
    virtual int GroupType();                //�ؼ����� λ���� �ֿ���
    virtual qMessageBoradAttr* Clone();      //����item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count, int index); //�����ʱ�򱣴�item�����ݿ�
    virtual void save(QDataStream &stream); //��item����������
    virtual void load(QDataStream &stream); //������������item

    TEXTPRO getAllItemText();
    void replaceAllItemText(int iLan,int iSta,QString sNewText);
     TEXTPRO vText;

public:
    virtual void redrawForChangeLanguage(int index);
    virtual void changeItemLanguageAttr(int lanNum);
    virtual QStringList getAllFonts();
    QString  getItemName();
};

#endif // QMESSAGEBORADATTR_H
