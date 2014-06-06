/*********************************************************************************/
//filename  DataDisPlayItem.h
/*********************************************************************************/

#ifndef DATADISPLAY_H
#define DATADISPLAY_H

#include "qvisableitem.h"
#include "Frame/qprogectmanager.h"
#include "Frame/ThingDlg/expression.h"

enum VALUESHOWTYPE   //��ǰtabҳ��
{
    DATAINPUTSHOW,    //��������
    ASCIIINPUTSHOW,   //ascii����
    DATETIMEINPUT,    //����ʱ����ʾ
};

enum TextPosition//�ı�λ�� ���󡢾��С�����
{
    LStart = 1,
    CStart,
    RStart,
};
enum InputMode //���뷽ʽ ����/λ
{
    Touch = 1,
    Bit,
};


typedef struct DATADISPLAYINFO
{
    VALUESHOWTYPE etabPag;            //��ǰ�� ��ֵ���롢ʱ����ʾ��ASCLL������ʾ��
    short int nStartX;                //�ؼ����������
    short int nStartY;                //�ؼ����������
    short int nWidth;                 //�ؼ����
    short int nHeight;                //�ؼ��߶�
    short int nTextStartX;	      //�ı�������������
    short int nTextStartY;	      //�ı��������������
    short int nTextWidth;	      //�ı�������
    short int nTextHeight;	      //�ı�����߶�
    QString   nShapId;                //��״
    QString   nAddress;               //����ӵ�ַ
    bool      bIsInput;               //��������
    bool      bIsScale;               //��������
    short int eNumberType;            //�������� index
    short int nByteLength;            //Դ��Χ  index
    QString   sSourceMax;             //Դ��Χ���ֵ
    QString   sSourceMin;             //Դ��Χ��Сֵ
    short int sShow;                  //��ʾָ��  index
    bool      bRound;                 //��ʾ����������
    QString   sShowMax;               //��ʾ���ֵ
    QString   sShowMin;               //��ʾ��Сֵ
    short int nFontType;              //�������� index
    QString   sFontType;
    short int nFontSize;              //�����С index
    short int eFontCss;               //�ı�����
    short int nAllbytelength;         //����ʾλ��
    short int sDecimalType;           //С��ָ��λ�� ����/��ַ  index
    short int sDecimalLength;         //С��λ��
    QString   sDecimalAddress;        //С��λ����ַ
    TextPosition eShowStyle;          //�ı���ʾλ��
    QString   nFontColor;             //������ɫ
    QString   nBackColor;             //���屳����ɫ
    QString   nHightColor;            //��λ������ɫ
    QString   nLowerColor;            //��λ������ɫ
    InputMode eInputTypeId;           //���뷽ʽ ������λ
    bool      nKeyMark;               //�Ƿ����ü���
    short int nKeyId;                 //���̱��
    QString   sKeyname;
    QString   nPreView;               //Ԥ����ʾ
    int       nTouchPropId;	      //��������ID��
    int       nShowPropId;	      //��������ID��
    Keyboard  addr;                   //����ӵ�ַ
    Keyboard  addrSourceMax;          //Դ����ַ
    Keyboard  addrSourceMin;          //Դ��С��ַ
    Keyboard  addrShowMin;            //��ʾ��С��ַ
    Keyboard  addrShowMax;            //��ʾ����ַ
    QString   sAddrBit;               //λ�����ַ
    Keyboard  addrBit;                //λ�����ַ
    Keyboard  addrDicmal;             //С��λ����ַ

    QString    nHightNumber;            //����ֵ
    QString    nLowerNumber;            //����ֵ
    bool       bUseMacro;          //�Ƿ�ʹ�ú�ָ��
    QString   macroName;           //��ָ��ID��
    QString   functionName;        //�ű�����ID
    short     nTransparent;      //�Ƿ�͸��
    short     eInputAreaType;       //���뷶Χ����
    Keyboard  addrInputMax;            //�������ֵ����
    Keyboard  addrInputMin;            //������Сֵ
    QString   sInputMax;
    QString   sInputMin;
    bool      bInputSign;           //������ʾ��
    int       nBoardX;              //�Զ���������X
    int       nBoardY;              //�Զ���������Y
    bool      bAutoChangeBit;       //�Ƿ��Զ���λ

    bool      bOffset;              //�Ƿ�ƫ��
    Keyboard  addrOffset;           //ƫ�Ƶ�ַ

    bool      bInputIsShow;         //ͬ��ص�ַ
    Keyboard  addrInputSame;

    bool      bOutExpression;          //�Ƿ�ʹ��������ʽ
    bool      bInExpression;          //�Ƿ�ʹ��������ʽ
    Expression m_outputExp;//���ӱ��ʽ
    Expression m_inputExp;//������ʽ
}DataInfo;

typedef struct ASCIIINPUTINFO
{
    VALUESHOWTYPE etabPag;            //��ǰ�� ��ֵ���롢ʱ����ʾ��ASCLL������ʾ��
    short int nStartX;                //�ؼ����������
    short int nStartY;                //�ؼ����������
    short int nWidth;                 //�ؼ����
    short int nHeight;                //�ؼ��߶�
    short int     nTextStartX;	      //�ı�������������
    short int     nTextStartY;	      //�ı��������������
    short int     nTextWidth;	      //�ı�������
    short int     nTextHeight;	      //�ı�����߶�
    QString   nShapId;                //��״
    QString   sAddress;               //����ӵ�ַ
    short int eNumberType;            //��������
    bool      bIsinput;               //��������
    short int nFontStyle;             //�������� index
    QString   sFontType;
    short int nFontsize;              //�����С  index
    short int nLanguageTypeId;        //��ʾ���� index
    short int eFontCss;               //�ı�����
    short int nShowCharNumber;        //��ʾ�ַ�����
    TextPosition nShowStyle;          //�ı���ʾλ��
    short int  nCode;                 //�ַ�����
    QString   nFontColor;             //������ɫ
    QString   nBackColor;             //���屳����ɫ
    InputMode eInputTypeId;           //���뷽ʽ ������λ
    short int nTouchPropId;           //��������ID��
    short int nShowPropId;            //��������ID��
    short int nKeyId;                 //���̱��
    QString   sKeyname;               //��������
    bool      nKeyMark;               //�Ƿ����ü���
    Keyboard  addr;                   //����ֵ�ַ
    QString   sAddrBit;               //λ�����ַ
    Keyboard  addrBit;                //λ�����ַ
    bool      bUseMacro;        //�Ƿ�ʹ�ú�ָ��
    QString   macroName;         //��ָ��ID��
    QString   functionName;    //�ű�����ID
    short        nTransparent;      //�Ƿ�͸��
    bool      bInputSign;           //������ʾ��
    int       nBoardX;              //�Զ���������X
    int       nBoardY;              //�Զ���������Y
    bool      bAutoChangeBit;       //�Ƿ��Զ���λ

    bool      bOffset;              //�Ƿ�ƫ��
    Keyboard  addrOffset;           //ƫ�Ƶ�ַ

    bool      bInputIsShow;         //ͬ��ص�ַ
    Keyboard  addrInputSame;
}ASCIIINFO;

typedef struct DATETIMEINFO
{
    VALUESHOWTYPE etabPag;            //��ǰ�� ��ֵ���롢ʱ����ʾ��ASCLL������ʾ��
    short int     nStartX;	      //�ؼ����������
    short int     nStartY;	      //�ؼ����������
    short int     nWidth;	      //�ؼ����
    short int     nHeight;	      //�ؼ��߶�
    short int     nTextStartX;	      //�ı�������������
    short int     nTextStartY;	      //�ı��������������
    short int     nTextWidth;	      //�ı�������
    short int     nTextHeight;	      //�ı�����߶�
    QString     nShapId;	      //����id
    short int     nFontStyle;	      //�������� index
    QString       sFontType;
    short int     nFontSize;	      //�����С  index
    short int     eFontCss;	      //�������� ��ѡ����׼��б�壬���壬�»��ߣ� index
    short int     eShowDate;	      //���� index
    short int     eShowTime;	      //ʱ��  index
    QString       nFontColor;	      //������ɫ
    QString       nBackground;	      //���屳����ɫ
    bool          bDateMark;          //����ѡ��
    bool          bTimeMark;          //ʱ��ѡ��
    bool          bWeekMark;          //����ѡ��
    TextPosition nShowStyle;          //�ı���ʾλ��
    QString       nPreView;           //Ԥ����ʾ
    short int     nLanguageTypeId;    //��ʾ���� index
    short          nTransparent;      //�Ƿ�͸��
    //Keyboard  addr;                   //����ֵ�ַ
}TIMEINFO;



class DataDisplayItem : public QVisableItem
{
public:
    DataDisplayItem();

    int GroupType();//�ؼ����� λ���� �ֿ���


    QGraphicsItem *Clone();//����item

    void compile(QSqlDatabase &db,int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

    void save(QDataStream &stream);//��item����������

    void load(QDataStream &stream);//������������item

    void onSaveDataInfo(DataInfo data_st);        //������ֵ��ʾ��Ϣ

    void onSaveAsciiInfo(ASCIIINFO ascii_st);        //����ASCII������Ϣ

    void onSaveTimeInfo(TIMEINFO time_st);        //����ʱ����ʾ��Ϣ

    void onGetPosition();

    void SetTextAlign(int nAlignType);

    int GetTextAlign(); //����ı��Ķ��뷽ʽ

    void SetRectBackColor(QColor color); //���ñ������ο�ı���ɫ

    void SetFontColor(QColor color); //����������ɫ

    void SetText(QString sText); //�����ı�

    void SetPattern(int nType);

    int GetPattern(); //�����ʽ

    void SetAlpha(int nType);

    QGraphicsItem* GetBackItem();

    QString GetKeyboardName();

    void SetKeyBoardInfo(QString sName, int index);

    void insertMacroTable(QSqlDatabase &db,int itemId,int &count,int sceneId,QString macroName,QString functionName);

    QList<Keyboard> getAddress();

    void setAddress(QList<Keyboard> addr);

    QStringList getAllFonts();

    QVector<ADDRPRO> getAllItemAddr();

    QString  getItemName();

    void redrawForChangeStatus(int index, int lan);

    int getCurrentState();

    void UpdateKeyboardInfo();

    void insertExpressTable(QSqlDatabase &db,Expression exp,int &count,int addLength,int itemId);

    int checkMacroName(QString &msg);
public:
    QVector<ADDRPRO> lsX;

public:

    VALUESHOWTYPE m_etabPag;            //��ǵ�ǰ�� ��ֵ���롢ʱ����ʾ��ASCLL������ʾ��

    //TextPosition m_TextAligent;         //���ֶ��뷽ʽ

    DataInfo m_data;

    ASCIIINFO m_ascii;

    TIMEINFO m_time;

    EITEM_TYPE m_eIspic;


};

#endif
