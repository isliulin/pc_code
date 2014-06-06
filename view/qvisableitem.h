#ifndef QVISABLEITEM_H
#define QVISABLEITEM_H

#include "qitemgroup.h"



class QVisableItem : public QItemGroup
{
public:
    QVisableItem(QGraphicsItem *parent);

    virtual int GroupType();//�ؼ����� λ���� �ֿ���


    virtual QGraphicsItem *Clone();//����item

    virtual void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

    virtual void save(QDataStream &stream);//��item����������

    virtual void load(QDataStream &stream);//������������item

    virtual void SetText(QString text);

    virtual void SetPicture(QString path,EITEM_TYPE blib,int alpha = 255,QColor color = QColor(0,0,0));

    virtual void redrawForChangeLanguage(int index);
    virtual void changeItemLanguageAttr(int lanNum);
    virtual void redrawForChangeStatus(int index, int lan);
    virtual int  getCurrentState();
    virtual QStringList getItemStates();
    virtual QVector<ADDRPRO> getAllItemAddr();

    virtual QString  getItemName();

    void SaveSecurityPro(securityPro *pro);

    qint64 GetUserGroupT();//ȡ�ô���Ȩ������ѡ�е��û���

    qint64 GetUserGroupV();//ȡ������Ȩ������ѡ�е��û���
public:
    securityPro sPro;
    //Ȩ��ҳ������
    /*
    bool enableTouch;//���ô���Ȩ��
    bool enableVisable;//��������Ȩ��

    bool byGroups_T;//����Ȩ�� 1-���û������ 0-��λ����
    bool byGroups_V;//����Ȩ�� 1-���û������ 0-��λ����

    QList <int >groups_T;//�������û������ ���п���Ȩ�޵���
    QList <int >groups_V;//�������û������ ���п���Ȩ�޵���

    int addrType_T;//������λ���� ��ַ���� 0-λ��ַ 1-�ֵ�ַ
    int addrType_V;//������λ���� ��ַ����

    int bitIndex_T;//������λ���� �ֵ�ַ��λ
    int bitIndex_V;//������λ���� �ֵ�ַ��λ

    bool condition_T;//����Ȩ�� ��������
    bool condition_V;//����Ȩ�� ��������

    Keyboard address_T;//����Ȩ�� ���Ƶ�ַ
    Keyboard address_V;//����Ȩ�� ���Ƶ�ַ

    bool bNotice;//�Ƿ����֪ͨ
    Keyboard addrNotice; //֪ͨ��ַ
    int datatype;//���ѡ���ֵ�ַ�Ļ�����������
    //int noticeAddrType; //ֵ֪ͨ�ĵ�ַ����
    int noticeValue;//ֵ֪ͨ

    bool bDelay;//�Ƿ���ʱ����
    int time;//��ѹʱ��
    */
public:
    QVector<ADDRPRO> kb;
};

#endif // QVISABLEITEM_H
