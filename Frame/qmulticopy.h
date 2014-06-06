#ifndef QMULTICOPY_H
#define QMULTICOPY_H

#include <QDialog>
#include "QButtonGroup"
#include "qlibrary.h"
#include "Frame/qprogectmanager.h"
namespace Ui {
    class QMultiCopy;
}

class QMultiCopy : public QDialog
{
    Q_OBJECT

public:
    explicit QMultiCopy(QWidget *parent = 0);
    ~QMultiCopy();
    QButtonGroup *R_Alignment_Group;
    QStringList datalist;
    Keyboard TempKeyboard;
    QStringList GetNormKeyboard(QGraphicsItem &pItem);
    void MuCopyList(QGraphicsItem &pItem,int &CopyCount,QStringList NormKeyboardstr);
    QStringList GetKeyboardID(QGraphicsItem &pItem);
    QList<Keyboard > getItemAddrs(QGraphicsItem *pItem);
    void setItemsAddrs(QList<QGraphicsItem *>items,QList<QVector<Keyboard> >addrs);
    QList<QVector<Keyboard> >getMultiAddrs(QList<Keyboard> startAddrs,int nInterval,int count);
    void setMulitAddrs(QList<QGraphicsItem *>items,QGraphicsItem *item);

private:
    Ui::QMultiCopy *ui;

private slots:
    void on_cancel_clicked();
    void on_OK_clicked();
    void on_if_Increse_Address_clicked(bool checked);
};

#endif // QMULTICOPY_H
