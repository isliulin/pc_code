#ifndef SCHEDULERS_H
#define SCHEDULERS_H
#include <QList>
#include <QVariant>
#include <QVector>
#include <QTime>
#include "Frame/qprogectmanager.h"
enum E_WEEKDAY
{
    SUN = 0,     //����
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
    BITSET  ,     //����λ
    //BITRESET,     //��λ
    BITXOR,       //����
    SETWORD,      //������
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
    int     timeType;//ʱ������ 0��ʾʱ�� 1 ��ʾ�ӵ�ַ��ȡʱ��
    QTime     time;//�ƻ�ִ��ʱ��
    Keyboard     kTimeAddr;//��ִ��ʱ��ĵ�ַ
    E_WEEKDAY eWeek;//��һ�ܵ�����ִ��

    E_ACTION_TYPE eActionType;//��������
    Keyboard     kActionAddr;//������ַ
    int     eDataType;//�ֲ�������������
    int     valueType;//ֵ������0��ʾ������1��ʾ�ӵ�ַȡֵ
    double  nValue;//�ֲ���д�����ֵ
    Keyboard     kValueAddr;//�ֲ�����ֵ�ǵ�ַ

    bool    bControl;//��λ����
    Keyboard     kControlAddr;//���Ƶ�ַ
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
