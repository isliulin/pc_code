#ifndef COMBOPICTURE_H
#define COMBOPICTURE_H

#include <QWidget>
#include "headfile/global_types.h"
#include "view/qdropdownattr.h"

class QDropdownAttr;
class QGraphicsScene;
namespace Ui {
    class ComboPicture;
}


class ComboPicture : public QWidget
{
    Q_OBJECT

public:
    explicit ComboPicture(QWidget *parent = 0);
    ~ComboPicture();

private:
    Ui::ComboPicture *ui;
    QGraphicsScene *pScene;
    QDropdownAttr *m_Item;
    QVector<QPair<QString,QString> > mpaths;

public:
    void refreshTab(int index);
    void Init(QVector<SwitchInfo> m_vecSwitchItem);
    QString GetPicName(QString sPath);
    QGraphicsItem *onGetItemFromFile(QString sPath,EITEM_TYPE eType);
    void showRowPic(EITEM_TYPE libtype,QString path);
signals:
    void picChanged(int index,EITEM_TYPE bLib,QString path);
    void rowChanged(int row);

private slots:
    void on_m_SelectPicpushBtn_clicked();
    void on_m_deletepicbtn_clicked();
    void on_m_SelectLibpushBtn_clicked();
    void on_Add(QString funcName,QString path);
    void on_Delete(QString funcName,QString path);

    void on_cellChanged();
};

#endif // COMBOPICTURE_H
