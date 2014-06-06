#ifndef MACRO_H
#define MACRO_H
#include<QString>
#include<QVector>
#include "Frame/qprogectmanager.h"

class MacroCmptrd ;
class Macro
{
public:
    Macro();
    Macro(QString code,QString name);
    //fuction
    bool compile(MacroCmptrd thread);//���뵱ǰ����
    bool setCode(QString code);//�޸ĺ�������
    QString code(); //���ص�ǰ�����Ĵ���
    void setVar(QVector <VarPro> variants);//�������ñ���
    bool appendVar(VarPro variant);
    QVector <VarPro> vars();
    bool isCompiled();
    void setModified();
    void setCompipiled(bool iscompiled);
    QByteArray MD5();
    bool checkMD5();
    void save(QDataStream &stream);
    void load(QDataStream &stream);
    void setMD5(QByteArray md);
public:
    QString libName; //��������
    bool type; //�����ͣ��ű��������Զ����
    QStringList functions;//�Զ�����ж������
    QVector <VarPro> m_Vars; //������
private:
    //Enum MACRO_TYPE m_type;//���ͣ�ȫ�ֽű�������ű�����ʼ���ű����ؼ��ű�

    QString m_code; //��������

    QByteArray md5; //������class�ļ�У����
    bool m_Compiled; //�Ƿ�ͨ������




};

#endif // MACRO_H
