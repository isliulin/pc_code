#ifndef MFBTNITEM_H
#define MFBTNITEM_H

#include "qvisableitem.h"
#include "qdropdownattr.h"
class MfBtnItem : public QVisableItem
{
public:
    MfBtnItem();
    ~MfBtnItem();
    void SetDefault();

public:
    bool                isUseScript;
    QString             macroName;
    QString             functionName;
    QVector<SwitchInfo> m_vecSwitchItem;//ÿ������д�����ݿ������

    //QVector<ST_TEXT_PROP > textPros;//�ı�����
    //ST_PIC_PROP picPro;//ͼƬ����

    int statusIndex;
    int curSta;
    textProList statusText;
    picProList statusPic;
public:

    QList<Keyboard> getAddress();//��ȡ������ַ
    void setAddress(QList<Keyboard> addr);//���ò�����ַ
    QVector<ADDRPRO> getAllItemAddr();//��ȡ�����õ��ĵ�ַ
    void changeItemLanguageAttr(int lanNum);//�ı�����
    QStringList getAllFonts();//��ȡ��������
	void SetPicture(QString path,EITEM_TYPE blib,int alpha = 255,QColor color = QColor(0,0,0));
    //void InsertTextTable(QSqlDatabase &db,int itemId);
    //void resizeLan(int count);
    QString  getItemName();


    int GroupType();                //�ؼ�����
    MfBtnItem * Clone();         //����item
    void compile(QSqlDatabase &db, int nSceneId, int &count,int index); //�����ʱ�򱣴�item�����ݿ�
    void insertMacroTable(QSqlDatabase &db,int itemId,int &count,int sceneId);
    void InsertSwitchTable(QSqlDatabase &db,int type, int &count,SwitchInfo info);
    void getRange(int dataType,double &nMax,double &nMin);
    //void redrawForChangeStatus(int index, int lan);

    void save(QDataStream &stream); //��item����������
    void load(QDataStream &stream); //������������item

    void SaveMonitorPage(monitorPro mProperty);
    monitorPro mPro;

    void InsertStatusTable(QSqlDatabase &db,int itemId,int &count);
    void InsertTextTable(QSqlDatabase &db,int itemId,int index);

    void redrawForChangeLanguage(int index);
    void redrawForChangeStatus(int index, int lan);
    QStringList getItemStates();
    void resizeStatus(int statuCount,int lanCount);

    int getCurrentState();
    int checkMacroName(QString &msg);

    TEXTPRO getAllItemText();
    void replaceAllItemText(int iLan,int iSta,QString sNewText);
     TEXTPRO vText;

public:
    QVector<ADDRPRO> addrs;
};

#endif // MFBTNITEM_H
