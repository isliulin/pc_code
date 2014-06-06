/****************************************************************************************************/


#ifndef ANIMATIONITEM_H
#define ANIMATIONITEM_H

#include "qvisableitem.h"
#include "Frame/qprogectmanager.h"
#include "Frame/mainwindow.h"
#include "ImageItem.h"

//typedef enum
//{
//    Pic,          //ͼƬ
//    Library,      //ͼ��
//    Userdefine,   //�û��Զ���ͼ��
//}PicType;

//�켣���ӱ�
typedef struct TRACK_POINT_INFO
{
    short nOrbitId;	//�켣�����
    short nXPos;	//�켣��X����
    short nYPos;	//�켣��Y����
}TrackPointInfo;

//���������ӱ�
typedef struct
{
    short nStateNo;	//������״̬���
    short nSCmpFactor;	//��λԤ��ֵ�����ڱȽ�

}StakeoutInfo;

//�ƶ������ӱ�
typedef struct
{
    short nTrackPointNo;     //�����Ĺ켣�����
    short nMCmpFactor;       //��λԤ��ֵ�����ڱȽ�
}TPMoveInfo;

//ͼƬ·���ӱ�
typedef struct
{
    QString   name;               //�洢ת���������elment+X
    short     nStatusId;          //״̬ID
    QString   sPath;		  //ͼƬ·��
    EITEM_TYPE    bIspic;//0:ͼƬ
    short int nCmpFactor;//Ԥ��̶�ֵ
}PictureInfo;

typedef enum //�ı�λ�� ���󡢾��С�����
{
    Lpoint = 0,
    Cpoint,
    Rpoint,
}TEXT_PIC_ALIGN;

//�ı������ӱ�
typedef struct
{
    bool    bValid;            //����Ƿ���Ч
    short   nStatusId;	 	//������״̬ID
    QString sFontFamily;	//��������
    short   sFontIndex;         //�����±�
    short   nSize;		//��С
    QString nColor;		//�ı���ɫ
    QString nBColor;		//�ı�����ɫ
    QString sText;		//�ı�����
    short   nStyle;             //B0000 : ��Ч��,B0001 : ����,B0010 : б��,B0100 : ��˸,B1000 :�»���
    TEXT_PIC_ALIGN eAlign;      //0������ ,1�����Ҿ��� ,2���������
    short   nSpace;             //�ּ��
}TextInfo;

typedef struct ANIMATONITEM
{
    short nLp;		    //�ؼ����Ͻ�x����
    short nTp;		    //�ؼ����Ͻ�y����
    short nWidth;	    //�ؼ����
    short nHeight;	    //�ؼ��߶�

    short nTrackType;       //0:ɢ��켣,1:����켣 index
    QString nBackColor;     //���򱳾�ɫ
    short  nMoveCondition;  //0:��ʱ���л�,1:���̶�ֵ�л� //index
    short nMoveType;        //0:ѭ���ƶ�,1:�����ƶ�
    short nMoveTimeInterval;//�ƶ����ʱ�䣬��λΪ100����
    short nStartTrackPoint; //��ʼ�켣�����
    short nTrackPointTotal; //�켣������
    QString sMoveCtrlAddr;      //
    Keyboard mMoveCtrlAddr;      //�ƶ��������ݵ��ֵ�ַ��ͨ��Ϊ״̬���Ƶ�ַ����һ����ַ
    QVector <TPMoveInfo> stMoveInfo;//�ƶ�Ԥ��ֵ�б�


    Keyboard mXPosCtrlAddr;         //�켣��X����
    Keyboard mYPosCtrlAddr;         //�켣��Y����
    QString  sAddrX;
    QString  sAddrY;
    float    nXMoveStepScale; //X�����ƶ�����,Ĭ��ֵ����Ϊ1
    float    nYMoveStepScale; //Y�����ƶ�������Ĭ��ֵ����Ϊ1
    short    nAreaOrigXPos;   //��������ԭ��X����
    short    nAreaOrigYPos;   //��������ԭ��Y����
    short    nAreaWidth;      //������
    short    nAreaHeight;     //����߶�

    //״̬
    short    nStateTotal;     //״̬����
    short    nChangeCondition;//�л���ʽ��0:Timeshorterval:ʱ���л� 1:PreSetValue:Ԥ��ֵ�л�
    short    nChangeType;     //״̬�л���ʽ 1:ActionLoop: ״̬ѭ�� 2:ActionTrip: ״̬����
    short    nChangeTimeinterval;//�л�ʱ����
    short    nInitState;       //��ʼ״̬���
    Keyboard mChangeCtrlAddr;    //״̬���Ƶ�ַ��Ĭ��״̬���Ƶ�ַ����һ��ַΪ�ƶ����Ƶ�ַ
    QString  sChangeCtrlAddr;
    QVector<StakeoutInfo> mSPreSetVList;//���״̬�л���Ԥ��ֵ

    //�ı�
    bool    bEnableText;//�Ƿ������ı�
    QVector<TextInfo> Text;

    //ͼƬ
    bool    bEnablePic;//�Ƿ���������
    //QString sPicBackColor;//ͼƬ����ɫ
    QVector<PictureInfo> PicInfo;
}AnInfo;




class AnimationItem : public QVisableItem
{
public:
    AnimationItem();

     int GroupType();//�ؼ����� λ���� �ֿ���


     QGraphicsItem *Clone();//����item

     void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

     void save(QDataStream &stream);//��item����������

     void load(QDataStream &stream);//������������item
public:

     void SetText(QString sText);
     void SetFontSize(int nFontSize);
     void SetFontName(QString sName); //������������
     void SetTextAlign(int nAlignType);

     void onSetCurrentNum(short int num);//���浱ǰ��ʾͼƬ�±�
     int  onGetCurrentNum();
     void onSetTrackInfo(QVector<TrackPointInfo> &Tinfo);
     void onGetTrackInfo(QVector<TrackPointInfo> &Tinfo);
     void onSaveAnimatInfo(AnInfo &aninfo);
     void onGetAnimatInfo(AnInfo &aninfo);
     QStringList getAllFonts();

     QVector<ADDRPRO> getAllItemAddr();

     void onGetTrakpos();

     QString  getItemName();

     int getCurrentState();

     QStringList getItemStates();

     void redrawForChangeStatus(int index, int lan);
     //��������ҳ������
     //struct CHART_INFORMATION *Datesave;
     AnInfo m_AnimatInfo;

private:
     short number;
     QVector<TrackPointInfo> TrackInfo;//�켣���б�

public:
     QVector<ADDRPRO> lsX;
};
#endif
