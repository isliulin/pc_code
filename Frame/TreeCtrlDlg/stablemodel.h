#ifndef STABLEMODEL_H
#define STABLEMODEL_H
#include "schedulers.h"
#include <QAbstractTableModel>
//class Schedulers;
class StableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit StableModel(QObject *parent = 0);

     StableModel(Schedulers *schedulers,QObject *parent = 0);

     int count() const;
     int count(E_WEEKDAY weekday) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;

    void setWeekday(E_WEEKDAY weekday);
    void setSchedulers(Schedulers *schedulers);
    void insert(ScheItem item);
    ScheItem itemAt(int row,E_WEEKDAY weekday);
    bool setItem(int row,E_WEEKDAY weekday,ScheItem item);
    bool removeItem(int row,E_WEEKDAY weekday);
    bool removeitems(QList<int >rows,E_WEEKDAY weekday);
private:
    Schedulers *m_schedulers;
    E_WEEKDAY m_weekday;
signals:

public slots:

};

#endif // STABLEMODEL_H
