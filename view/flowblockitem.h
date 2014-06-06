/****************************************************************************************************
  Flowblock�����顪�����Ŀ�

 **************************************************************************************************/

#ifndef FLOWBLOCK_H
#define FLOWBLOCK_H
#include <QDialog>
#include "Frame/mainwindow.h"
//����ö��
enum DIRECTIONS{
    LEVEL=1,      //ˮƽ
    VERTICAL=2,   //��ֱ
    LEFT,       //����
    RIGHT       //����
};
//�ٶ�ö��
enum SPEED{
    FIXEDFLOWSPEED=1,//�̶������ٶ�
    TRENDFLOWSPEED=2,//��̬�����ٶ�
    LOW=3,		//��
    MIDDLE=4,		//��
    HIGH=5		//��
};

#include "qvisableitem.h"
//�������Ա����
typedef struct DATAFLOWBLOCKINFO{
QString id;//���
short nStartX ;//������
short nStartY ;//������
short nRectWidth ;//��
short nRectHeight ;//��
QString nFForeColor ;//������ǰ��ɫ
QString nFBackColor ;//�����鱳��ɫ
QString nDForeColor ;//�ܵ�ǰ��ɫ
QString nDBackColor ;//�ܵ�����ɫ
QString nFrameColor ;//�߿�ɫ
short eStyle ;//��ʽ
QString nTriggerAddress ;//������ַ
DIRECTIONS eShowWay ;//��ʾ��ʽ
DIRECTIONS eFlowDirection ;//��������
QString sflowdirection;
bool bTouchAddress ;//�Ƿ�ʹ�õ�ַ�ı���������
QString eTouchAddress ;//���ص�ַ
short nValidState;//��Ч״̬
short nFlowNum ;//��������Ŀ
bool bSideLine ;//���ޱ���
SPEED eFlowSpeedType ;//ѡ�������ٶ�����
SPEED eFixedFlowSpeed ;//�̶������ٶ�
QString nTrendFlowSpeed ;//��̬�����ٶ�
short nZvalue ;
short nCollidindId ;

Keyboard trendSpeed;//��̬�����ٶȴ�������
Keyboard triggerAdd;//������ַ����
Keyboard touchAdd;//���ص�ַ����

}FlowInfo;

class FlowBlockItem : public QVisableItem
{
public:
    FlowBlockItem();
    int GroupType() ;
    QGraphicsItem *Clone();//����item
    void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�
    void save(QDataStream &stream);//��item����������
    void load(QDataStream &stream);//������������item
    void onSaveFlow(FlowInfo flow_st);//��������������
    void onSecurityPro(securityPro sproperty);//Ȩ��
    QList<Keyboard> getAddress();//���ظ��ƻ�õ�ַ
    void setAddress(QList<Keyboard> addr);//���ظ������õ�ַ
    virtual QVector<ADDRPRO> getAllItemAddr();//���ҵ�ַ�麯��
    QString getItemName();
    FlowInfo m_flow;
    securityPro m_sproperty;

public:
     QVector<ADDRPRO> addrs;
};

#endif // FLOWBLOCK_H
