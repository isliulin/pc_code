#ifndef QDROPDOWNATTR_H
#define QDROPDOWNATTR_H

#include "view/switchitem.h"
#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"

//const int NoEffect  = 0x0000;//��Ч��
//const int Bold      = 0x0001;//����
//const int Italic    = 0x0010;//б��
//const int UnderLine = 0x1000;//�»���

typedef struct __SwitchInfo__
{
    short   switchType;     //1�������ͣ�1�ֿ��أ�2λ���أ�3���濪�أ�
    //int     switchCount;    //���
    //int     switchItemId;   //�ؼ�Id�������ĸ�������ؼ�
    //int     switchFunId;    //����Id�����ܰ�ťId��
    QVector<QString> vecSwitchFunName;  //��������,ÿ�����Զ�Ӧһ�����֣�
    //QString switchFunName;  //��������,ÿ�����Զ�Ӧһ�����֣�

    //λ��������
    Keyboard        addrBit;        //1λ��ַ
    BIT_OPER_TYPE   operTypeB;      //1��������
    bool            bDown;          //ִ�з�ʽ

    //�ֿ�������
    Keyboard        addrWord;       //1�ֵ�ַ
    WORD_OPER_TYPE  operTypeW;      //1��������
    DATA_TYPE       dataType;       //1��������
    double          value;          //1
    bool            bDynamicControl; //1wxy ������ֵ��̬����
    Keyboard        addrConst;       //1������ֵ��ַ


    //�����л�����
    SCENE_OPER_TYPE operType;       //1��������
    //int             nSceneType;     //��ǰ����ţ��Ժ�ת�ɻ���0������1
    QString         sceneName;      //1��������
    bool            bLogout;        //1�л������Ƿ�ע��

    EITEM_TYPE      bLib;//�Ƿ���ͼƬ
    QString         sPath;//���ܶ�Ӧ��ͼƬ·��
}SwitchInfo;

class QDropdownAttr:public QVisableItem
{
public://ѡ���б�
    short               m_nShowNumber;  //������ʾ����
    //QList<SwitchItem> m_listSwitchItem;//ÿ�����ص�ʵ������
    //int                 totalItem;      //�������������ʱ����
    int                 totalScreen;    //���浱ǰ����¶��ٸ����棬�����𴰿ڣ�����Ϊ�˷�ֹ�����ʱ�򴰿ڻ������ı�
    bool                isUseScript;
    QString             macroName;
    QString             functionName;
    QVector<SwitchInfo> m_vecSwitchItem;//ÿ������д�����ݿ������

public://��������
    QString     m_strFontName;          //�������͵�����
    short       m_nFontSize;            //�����С
    short       m_nLanType;             //��������
    short       m_nFontStyle;           //������ʽ����׼�����壬б�壩
    QColor      m_nFontColor;           //������ɫ
    QColor      m_nBackColor;           //������ɫ
    short       m_nAlpha;               //͸����
    bool        m_bUsePic;              //�Ƿ�ʹ��ͼƬ�л�

public:
    QRectItem       *pRect;
    QRectItem       *pBackRect;
    QFoldLineItem   *pLine;

public:
    void resetDropDown(QColor mColor, short alpha);
    void getRange(int dataType,double &nMax,double &nMin);

    TEXTPRO getAllItemText();
    void replaceAllItemText(int iLan,int iSta,QString sNewText);
     TEXTPRO vText;

public:
    QDropdownAttr(QGraphicsItem *parent = 0);
    ~QDropdownAttr();
    QList<Keyboard> getAddress();
    void setAddress(QList<Keyboard> addr);
    virtual QVector<ADDRPRO> getAllItemAddr();
    virtual void changeItemLanguageAttr(int lanNum);
    virtual QStringList getAllFonts();

public:
    virtual int GroupType();                //�ؼ����� λ���� �ֿ���
    virtual QDropdownAttr * Clone();         //����item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count,int index); //�����ʱ�򱣴�item�����ݿ�
    virtual void save(QDataStream &stream); //��item����������
    virtual void load(QDataStream &stream); //������������item
    QString getItemName();
    int checkMacroName(QString &msg);

public:
    QVector<ADDRPRO> addrs;
};

#endif // QDROPDOWNATTR_H
