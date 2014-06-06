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
    QTrendAppearance*   m_pTrendAppearDlg;//曲线外观设置对话框
    QTrendadisplay*     m_pTrendDisplay;//曲线显示区设置
    QTrendaTime*        m_pTrendTime;//曲线时间设置
    SecurityWidget *pSecurityWight;//显现页面

public:
    QTrendAttr* m_pCopyItem;

private slots:

    void on_help_clicked();
    void on_cancel_clicked();
    void on_accept_clicked();
};

#endif // QTREND_H
