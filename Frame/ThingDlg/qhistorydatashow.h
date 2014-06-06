#ifndef QHISTORYDATASHOW_H
#define QHISTORYDATASHOW_H

#include <QDialog>
#include "qhistorydatashowone.h"
#include "qhistorydatashowtwo.h"
#include "view/qhistorydatashowattr.h"

namespace Ui {
    class QHistoryDataShow;
}

class QHistoryDataShow:public QDialog
{
    Q_OBJECT

public:
    explicit QHistoryDataShow(QHistoryDataShowAttr* pItem, QWidget *parent = 0);
    ~QHistoryDataShow();

private:
    Ui::QHistoryDataShow *ui;
    QVector<qreal> vVLine;              //�����洹ֱ�ߵ�����
    QVector<qreal> vHLine;             //������ˮƽ�ߵ�����
    int oId;

public:
    void InitPropertys(QHistoryDataShowAttr* pItem);

public:
    QHistoryDataShowAttr* m_pCopyItem;

public:
    QHistoryDataShowOne* page1;
    QHistoryDataShowTwo* page2;
    SecurityWidget *pSecurityWight;//����ҳ��

public:
    //QStringList sDataName;
    void DrawTable();

private slots:
    void on_help_clicked();
    void on_cancel_clicked();
    void on_accept_clicked();

public slots:
    void drawSence();

public:
    QGraphicsScene*         pScene;//����
    QHistoryDataShowAttr*   pTempItem;
};

#endif // QHISTORYDATASHOW_H
