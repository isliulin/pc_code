#ifndef QVISABLEITEM_H
#define QVISABLEITEM_H

#include "qitemgroup.h"



class QVisableItem : public QItemGroup
{
public:
    QVisableItem(QGraphicsItem *parent);

    virtual int GroupType();//控件类型 位开关 字开关


    virtual QGraphicsItem *Clone();//复制item

    virtual void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//编译的时候保存item到数据库

    virtual void save(QDataStream &stream);//将item存入数据流

    virtual void load(QDataStream &stream);//从数据流导出item

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

    qint64 GetUserGroupT();//取得触控权限所有选中的用户组

    qint64 GetUserGroupV();//取得显现权限所有选中的用户组
public:
    securityPro sPro;
    //权限页面属性
    /*
    bool enableTouch;//启用触控权限
    bool enableVisable;//启用显现权限

    bool byGroups_T;//触控权限 1-受用户组控制 0-受位控制
    bool byGroups_V;//显现权限 1-受用户组控制 0-受位控制

    QList <int >groups_T;//触控受用户组控制 具有控制权限的组
    QList <int >groups_V;//显现受用户组控制 具有控制权限的组

    int addrType_T;//触控受位控制 地址类型 0-位地址 1-字地址
    int addrType_V;//显现受位控制 地址类型

    int bitIndex_T;//触控受位控制 字地址的位
    int bitIndex_V;//显现受位控制 字地址的位

    bool condition_T;//触控权限 解锁条件
    bool condition_V;//显现权限 解锁条件

    Keyboard address_T;//触控权限 控制地址
    Keyboard address_V;//显现权限 控制地址

    bool bNotice;//是否解锁通知
    Keyboard addrNotice; //通知地址
    int datatype;//如果选择字地址的话，数据类型
    //int noticeAddrType; //通知值的地址类型
    int noticeValue;//通知值

    bool bDelay;//是否延时触控
    int time;//按压时间
    */
public:
    QVector<ADDRPRO> kb;
};

#endif // QVISABLEITEM_H
