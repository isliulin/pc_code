#ifndef QMESSAGESHOW_H
#define QMESSAGESHOW_H

#include <QDialog>
#include "view/qmessageshowattr.h"
#include "qmessageshowone.h"

namespace Ui {
    class qMessageShow;
}

class qMessageShow:public QDialog
{
    Q_OBJECT

public:
    explicit qMessageShow(QMessageShowAttr* pItem, QWidget *parent = 0);
    ~qMessageShow();

private:
    Ui::qMessageShow *ui;
    int oId;

public:
    void InitPropertys(QMessageShowAttr* pItem);

public:
    QMessageShowAttr* m_pCopyItem;

public:
    QGraphicsScene*     pScene; //≥°æ∞
    QGraphicsItem*      pOldItem;
    QGroupItem*         pBaseItem;
    QGroupItem*         pCopyBaseItem;
    //QMessageShowAttr*   itemTemp;
    QList<QGraphicsItem*> listItem;

public:
    qMessageShowOne* page1;
    SecurityWidget *pSecurityWight;//œ‘œ÷“≥√Ê

private slots:
    void on_help_clicked();
    void on_cancel_clicked();
    void on_accept_clicked();

public slots:
    void redraw();
};

#endif // QMESSAGESHOW_H
