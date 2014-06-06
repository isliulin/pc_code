#ifndef AKCOMBOITEM_H
#define AKCOMBOITEM_H

#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"

typedef struct __Combo_Statu__
{
    QVector<QString> m_vecText;	//һ��״̬�ĸ����ı�
    double           m_value;
}ComboStatu;

typedef struct __Combo_Language__
{
    short   m_nAlign;       //���룬����0�������1���Ҷ���2
    short   m_nFontSize;    //�����С
    QString m_strFontName;  //��������
    QColor  m_nTextColor;   //�ı�ɫ

    bool    m_bCuTi;        //����
    bool    m_bXieTi;       //б��
    bool    m_bXiaHuaXian;  //�»���
}ComboLanguage;

typedef struct __Data_Combobox__
{
    int		m_nStatuNum; 	//��״̬��
    DATA_TYPE 	m_eDataType;	//��������
    Keyboard 	m_keyCtrlAddr;	//���Ƶ�ַ

    short       m_nAlpha;	//͸����
    QColor      m_nBKColor;	//����ɫ
    EITEM_TYPE 	m_eLibType;	//0��ʾ���ⲿͼƬ 1��ʾ��ͼ��
    QString 	m_strPath;	//·��

    bool        m_bUseMacro;	//�Ƿ�ʹ�ýű�
    QString     m_strMacroName;	//�ű�

    bool        m_bFirstLan;	//�Ƿ�ʹ�õ�һ������

    QVector<ComboStatu>     m_vecStatus;    //��״̬

    QVector<ComboLanguage>  m_vecLanguage;  //������
}DataCombobox;

class AkComboItem:public QVisableItem
{
public:
    AkComboItem(QGraphicsItem *parent = 0);
    ~AkComboItem();

public:
    DataCombobox     dataCombo;
    QVector<ADDRPRO> addrs;

public:
    virtual int GroupType();                //�ؼ����� λ���� �ֿ���
    virtual AkComboItem* Clone();      //����item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count, int index); //�����ʱ�򱣴�item�����ݿ�
    virtual void save(QDataStream &stream); //��item����������
    virtual void load(QDataStream &stream); //������������item

public:
    virtual void redrawForChangeLanguage(int index);
    virtual void redrawForChangeStatus(int index, int lan);
    virtual void changeItemLanguageAttr(int lanNum);
    virtual QStringList getAllFonts();
    QString getItemName();
    int checkMacroName(QString &msg);

    TEXTPRO getAllItemText();
    void replaceAllItemText(int iLan,int iSta,QString sNewText);
     TEXTPRO vText;

    virtual QVector<ADDRPRO> getAllItemAddr();
    virtual QStringList getItemStates();

    QList<Keyboard> getAddress();
    void setAddress(QList<Keyboard> addr);
};

#endif // AKCOMBOITEM_H
