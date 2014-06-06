#ifndef QTRENDDATAGROUPATTR_H
#define QTRENDDATAGROUPATTR_H

#include <vector>
#include <qcolor.h>
#include "view/qvisableitem.h"
#include "Frame/mainwindow.h"
#include "view/qtrendattr.h"      //Ҫ�������е�ö��

using namespace std;

class QTrendDataGroupAttr:public QVisableItem
{
public:
    QTrendDataGroupAttr(QGraphicsItem *parent = 0);
    ~QTrendDataGroupAttr();

public://�������,
    bool        m_bIsAll;                       //����ȫ��
    QString     m_sCurChnnel;                //��ǰ����
    QString     m_sChnnelBegin;                 //��ʼ���,��vecGroupNum�е�
    int         m_nTotalTrendNumber;            //����������
    QVector<DisplayGroupInfo> m_vecDisplayGroups;//����ͨ�������ֵ�ַ����
    QVector<ChannelGroupInfo> m_vecChannelGroups;//����ͨ�������������
    QVector<QString>m_selGroups;//����ѡ�е�����
    double      m_nDisplayMax;//��ʾ���ֵ
    double      m_nDisplayMin;//��ʾ��Сֵ

public://��ʾ������
    bool    m_bSelectVertMinor;	//�Ƿ���ʾ��ֱ�α��
    bool    m_bSelectHorMinor;	//�Ƿ���ʾˮƽ�α��
    bool    m_bMainVer;         //�Ƿ���ʾ��ֱ�����
    bool    m_bMainHor;         //�Ƿ���ʾˮƽ�����
    short   m_nDataSample;	//����������
    short   m_nVertMajorScale;	//��ֱ�����
    short   m_nVertMinorScale;	//��ֱ�α��
    short   m_nHorMajorScale;	//ˮƽ�����
    short   m_nHorMinorScale;	//ˮƽ�α��

public://��ɫ�Ի���Ҫ�洢������
    bool   m_bGrade;            //�Ƿ���Ҫ����
    QColor m_nVerColor;         //ˮƽ������ɫ
    QColor m_nHorColor;         //��ֱ������ɫ
    QColor m_nBoradColor;	//�߿���ɫ
    QColor m_nScaleColor;	//�����ɫ
    QColor m_nGraphColor;	//ͼ������ɫ
    QColor m_nMarkedColor; //��ע��ɫ
    int    m_alpha;        //ͼ����͸����
    short   m_nFontSize;    //�����С
    vector<ColorGroupInfo> m_vecGroupColor;//����ͨ����ɫ����

public:
    virtual int GroupType();                //�ؼ����� λ���� �ֿ���
    virtual QTrendDataGroupAttr *Clone();         //����item
    virtual void compile(QSqlDatabase &db, int nSceneId, int &count, int index); //�����ʱ�򱣴�item�����ݿ�
    virtual void save(QDataStream &stream); //��item����������
    virtual void load(QDataStream &stream); //������������item
	QVector<ADDRPRO> getAllItemAddr();
    QString  getItemName();
	void sampChanged(QString oldName,QString newName,int sampType);

public:
    QVector<ADDRPRO> kb;
};

#endif // QTRENDDATAGROUPATTR_H
