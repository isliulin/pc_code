#ifndef QTREND_H
#define QTREND_H

#include <QDialog>
#include <qgraphicsitem.h>
#include <qtablewidget.h>
#include <qdialogbuttonbox.h>
#include <QVBoxLayout>
#include "qtrendappearance.h"
#include "qtrendadisplay.h"
#include "qtrendatime.h"
#include "view/qtrendattr.h"
//#include "view/qdrawgraphics.h"

class QGraphicsScene;
namespace Ui {
    class QTrend;
}

class QTrend : public QDialog
{
    Q_OBJECT

public:
    explicit QTrend(QTrendAttr *pItem, QWidget *parent = 0);
    ~QTrend();

private:
    Ui::QTrend *ui;
    QGraphicsScene scene;
    int oId;

public:
    void InitAllProperty(QTrendAttr *pItem);

public:
    QTrendAppearance*   m_pTrendAppearDlg;//����������öԻ���
    QTrendadisplay*     m_pTrendDisplay;//������ʾ������
    QTrendaTime*        m_pTrendTime;//����ʱ������
    SecurityWidget *pSecurityWight;//����ҳ��

public:
    QTrendAttr* m_pCopyItem;

private slots:

    void on_help_clicked();
    void on_cancel_clicked();
    void on_accept_clicked();
};

#endif // QTREND_H
