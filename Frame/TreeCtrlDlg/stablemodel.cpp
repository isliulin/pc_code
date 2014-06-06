#include "stablemodel.h"
#include "schedulers.h"
StableModel::StableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_weekday = SUN;
    m_schedulers = NULL;
}

StableModel::StableModel(Schedulers *schedulers,QObject *parent) :
    QAbstractTableModel(parent)
{
    //m_weekday = SUN;
    m_schedulers = schedulers;
}

void StableModel::setSchedulers(Schedulers *schedulers)
{
    m_schedulers = schedulers;
    reset();
}
int StableModel::rowCount(const QModelIndex &parent) const
{
    int count = 0;
    if(m_schedulers)
    {
        count = m_schedulers->getItems().at(m_weekday).size();
    }
    return count;
}
int StableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}
int StableModel::count() const
{
    return count(m_weekday);
}
int StableModel::count(E_WEEKDAY weekday) const
{
    int count = 0;
    if(m_schedulers)
    {
        count = m_schedulers->getItems().at(weekday).size();
    }
    return count;
}

QVariant StableModel::data(const QModelIndex &index, int role) const
{
    if (role!=Qt::DisplayRole)

      return QVariant();


    QVariant var;
    int row = index.row();
    int col = index.column();

    QList<ScheItem> items = m_schedulers->getWeekItems(m_weekday);
    if(items.size() > row)
    {
        ScheItem item = items.at(row);
        var = item.data(col);
    }
    return var;

}
void StableModel::setWeekday(E_WEEKDAY weekday)
{
    m_weekday = weekday;
    reset();
}
void StableModel::insert(ScheItem item)
{
    m_schedulers->insert(item,item.eWeek);
    reset();
    //emit dataChanged(createIndex(0,0),createIndex(m_schedulers->getWeekItems(weekday).size(),3));
}
ScheItem StableModel::itemAt(int row,E_WEEKDAY weekday)
{
    return m_schedulers->getItem(row, weekday);
    reset();
}
bool StableModel::setItem(int row,E_WEEKDAY weekday,ScheItem item)
{
    bool result = m_schedulers->setItem(row,weekday,item);
    reset();
    return result;
}
bool StableModel::removeItem(int row,E_WEEKDAY weekday)
{
    bool result =  m_schedulers->removeItem(row,weekday);
    reset();
    return result;
}
bool StableModel::removeitems(QList<int >rows,E_WEEKDAY weekday)
{
    bool result =  m_schedulers->removeItems(rows,weekday);
    reset();
    return result;
}
QVariant StableModel::headerData(int section, Qt::Orientation orientation,
                                 int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0:
                return tr("时间");
            case 1:
                return tr("操作");
            case 2:
                return tr("地址");
            default:
                return QVariant();
        }
    }
    if (orientation == Qt::Vertical && role == Qt::DisplayRole) {

       return QVariant(section);

    }
    return QVariant();
}
