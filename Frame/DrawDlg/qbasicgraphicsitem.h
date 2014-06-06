#ifndef QBASICGRAPHICSITEM_H
#define QBASICGRAPHICSITEM_H

#include "Frame/qprogectmanager.h"

class QBasicGraphicsItem
{
public:
    QBasicGraphicsItem();
public:
    virtual void SaveSecurityPro(securityPro *pro);

    virtual securityPro GetSecurityPro();

    virtual void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

    virtual void save(QDataStream &stream);//��item����������

    virtual void load(QDataStream &stream);//������������item

    qint64 GetUserGroupT();//ȡ�ô���Ȩ������ѡ�е��û���

    qint64 GetUserGroupV();//ȡ������Ȩ������ѡ�е��û���
public:
    securityPro sPro;

};

#endif // QBASICGRAPHICSITEM_H
