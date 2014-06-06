#ifndef QHISTORYDATASHOWATTR_H
#define QHISTORYDATASHOWATTR_H

#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"
#include "Frame/qprogectmanager.h"

typedef struct __dataInfo__
{
    int      m_nSampNum;
    bool     m_bShow;
    QString  m_strName;
    Keyboard m_kb;
}dataInfo;

typedef struct __HistoryDataInfo__
{
    int                 m_nLanguage;
    QVector<dataInfo>   m_vecInfo;
}HistoryDataInfo;

typedef struct __HistoryTextInfo__
{
    short       m_nTitleFontSize;	//���������С��Ĭ��10
    int         m_nTitleLanguage;	//��������
    QString     m_sTitleFontType;	//�����������ͣ�Ĭ������
    QString     m_sTitleTimeName;	//������ʱ�䣬���ģ�ʱ�䣬Ӣ�ģ�Time
    QString     m_sTitleDateName;	//�����У�����
    QString     m_sTitleNumber;         //���
}HistoryTextInfo;

class QHistoryDataShowAttr:public QVisableItem//public QItemGroup
{
public:
    //һ��
    QColor  m_nForecolor;       //ǰ��ɫ
    QColor  m_nFrameColor;      //�߿�ɫ
    short   m_nAlpha;
    //---------------
    short   m_nTextFontSize;    //�ı������С��Ĭ��10
    short   m_nLine;            //��ʾ������Ĭ��5
    QColor  m_nTextFontColor;   //�ı�������ɫ��Ĭ�Ϻ�ɫ
    //---------------
    bool    m_bShowTime;	//�Ƿ���ʾʱ�䣬Ĭ����ʾ
    bool    m_bShowDate;	//�Ƿ���ʾ����,Ĭ����ʾ
    QColor  m_nTitleBackColor;	//���ⱳ����ɫ��Ĭ�ϻ�ɫ
    QColor  m_nTitleFontColor;	//����������ɫ��Ĭ�Ϻ�ɫ
    bool    m_bShowCode;        //�Ƿ���ʾ���
    TIME_FORMAT	m_eTimeFormat;  //(ͳһʱ���ʽö��)ʱ���ʽ HH:MM
    DATE_FORMAT	m_eDateFormat;  //(ͳһʱ���ʽö��)���ڸ�ʽ Ĭ�ϣ�DD/MM/YY
    bool    m_bAddr;            //�Ƿ���Ҫ���Ƶ�ַ
    Keyboard m_KeyAddr;         //���Ƶ�ַ
    //---------------
    QString     sGroupName;         //����
    //---------------
    QVector<HistoryTextInfo> m_vecHisText;//ÿ�����Զ�Ӧ�ı������ݵ���������

    //����
    QVector<HistoryDataInfo> m_vecHisData;

public:
    //QStringList sDataName;
    virtual void redrawForChangeLanguage(int index);
    virtual void changeItemLanguageAttr(int lanNum);
    virtual QStringList getAllFonts();

    TEXTPRO getAllItemText();
    void replaceAllItemText(int iLan,int iSta,QString sNewText);
     TEXTPRO vText;

public:
    QHistoryDataShowAttr(QGraphicsItem *parent = 0);
    ~QHistoryDataShowAttr();

public:
    virtual int GroupType();                //�ؼ����� λ���� �ֿ���
    virtual QHistoryDataShowAttr* Clone();            //����item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count, int index); //�����ʱ�򱣴�item�����ݿ�
    virtual void save(QDataStream &stream); //��item����������
    virtual void load(QDataStream &stream); //������������item
    QString  getItemName();
    void sampChanged(QString oldName,QString newName,int sampType);
};

#endif // QHISTORYDATASHOWATTR_H
