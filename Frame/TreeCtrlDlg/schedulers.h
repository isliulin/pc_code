#ifndef SCHEDULERS_H
#define SCHEDULERS_H
#include <QList>
#include <QVariant>
#include <QVector>
#include <QTime>
#include "Frame/qprogectmanager.h"
enum E_WEEKDAY
{
    SUN = 0,     //周日
    MONDAY,        //
    TUESDAT,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    WEEKDAYERROR
};
enum E_ACTION_TYPE
{
    BITSET  ,     //设置位
    //BITRESET,     //复位
    BITXOR,       //交替
    SETWORD,      //设置字
    OTHER

};
class ScheItem
{
public:
    ScheItem();
    QVariant data(int col);
    QVariant timeData();
    QVariant cmdData();
    QVariant addrData();
public:
    int     id;
    int     timeType;//时间类型 0表示时间 1 表示从地址获取时间
    QTime     time;//计划执行时间
    Keyboard     kTimeAddr;//存执行时间的地址
    E_WEEKDAY eWeek;//在一周的哪天执行

    E_ACTION_TYPE eActionType;//操作类型
    Keyboard     kActionAddr;//操作地址
    int     eDataType;//字操作的数据类型
    int     valueType;//值的类型0表示常数，1表示从地址取值
    double  nValue;//字操作写入的数值
    Keyboard     kValueAddr;//字操作的值是地址

    bool    bControl;//受位控制
    Keyboard     kControlAddr;//控制地址
};
class Schedulers
{
public:
    Schedulers();
    QVector<QList<ScheItem> > getItems();
    QList<ScheItem> getWeekItems(E_WEEKDAY weekday);
    void insert(ScheItem item,E_WEEKDAY weekday);

    void editItem(QList<ScheItem> items,E_WEEKDAY weekday);
    ScheItem getItem(int row,E_WEEKDAY weekday);
    bool setItem(int row,E_WEEKDAY weekday,ScheItem item);
    bool removeItem(int row,E_WEEKDAY weekday);
    bool removeItems(QList<int >rows,E_WEEKDAY weekday);
    void setItems(QVector<QList<ScheItem> >items);
private:
    QVector<QList<ScheItem> > m_Items;
    //QList<ScheItem >m_Items;
};

#endif // SCHEDULERS_H
