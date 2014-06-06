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

    virtual void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库

    virtual void save(QDataStream &stream);//将item存入数据流

    virtual void load(QDataStream &stream);//从数据流导出item

    qint64 GetUserGroupT();//取得触控权限所有选中的用户组

    qint64 GetUserGroupV();//取得显现权限所有选中的用户组
public:
    securityPro sPro;

};

#endif // QBASICGRAPHICSITEM_H
