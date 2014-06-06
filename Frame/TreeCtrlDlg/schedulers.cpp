#include "schedulers.h"

ScheItem::ScheItem()
{
    eWeek = WEEKDAYERROR;
}
QVariant ScheItem::data(int col)
{
    QVariant var;
    switch(col)
    {
    case 0:// ±º‰
        var = timeData();
        break;
    case 1://√¸¡Ó
        var = cmdData();
        break;
    case 2://µÿ÷∑
        var = addrData();
        break;
    default://√Ë ˆ
        break;
    }
    return var;
}
QVariant ScheItem::timeData()
{
    QVariant var;
    if(timeType == 0)
    {
        var = QVariant(time.toString());
    }
    else
    {
        var = QVariant(kTimeAddr.sShowAddr);
    }
    return var;
}
QVariant ScheItem::cmdData()
{
    QVariant var;
    switch(eActionType)
    {
    case BITSET:
        var = QVariant(QObject::tr("BITSET"));
        break;
//    case BITRESET:
//        var = QVariant(QObject::tr("BITRESET"));
//        break;
    case BITXOR:
        var = QVariant(QObject::tr("BITXOR"));
        break;
    case SETWORD:
        var = QVariant(QObject::tr("SETWORD"));
        break;
    default:
        break;
    }
    return var;
}
QVariant ScheItem::addrData()
{
    QVariant var;
    var = QVariant(kActionAddr.sShowAddr);
    return var;
}
Schedulers::Schedulers()
{
    m_Items.resize(7);
}

QVector<QList<ScheItem> > Schedulers::getItems()
{
    return m_Items;
}
void Schedulers::setItems(QVector<QList<ScheItem> >items)
{
    m_Items = items;
    m_Items.resize(7);
}
ScheItem Schedulers::getItem(int row,E_WEEKDAY weekday)
{
    if(row >= m_Items[weekday].size())
    {
        return ScheItem();
    }
    return m_Items[weekday][row];
}
bool Schedulers::setItem(int row,E_WEEKDAY weekday,ScheItem item)
{
    if(row >= m_Items[weekday].size())
    {
        return false;
    }
    m_Items[weekday][row] = item;
    return true;
}
bool Schedulers::removeItem(int row,E_WEEKDAY weekday)
{
    if(row >= m_Items[weekday].size())
    {
        return false;
    }
    m_Items[weekday].removeAt(row);
    return true;
}
QList<ScheItem> Schedulers::getWeekItems(E_WEEKDAY weekday)
{
    QList<ScheItem> items;

    items = m_Items[weekday];
    return items;
}

void Schedulers::insert(ScheItem item,E_WEEKDAY weekday)
{
    m_Items[weekday].append(item);
}

bool Schedulers::removeItems(QList<int >rows,E_WEEKDAY weekday)
{
    QList<ScheItem> items;
    for(int i=0; i<m_Items[weekday].size(); i++)
    {
        if(!rows.contains(i))
        {
            items << m_Items[weekday][i];
        }
    }
    m_Items[weekday].clear();
    m_Items[weekday] = items;
}
void Schedulers::editItem(QList<ScheItem> items,E_WEEKDAY weekday)
{
    m_Items[weekday] = items;
}
