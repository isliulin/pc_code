#ifndef QTRENDDATAGROUP_H
#define QTRENDDATAGROUP_H

#include <QDialog>
#include <qgraphicsitem.h>
#include <qtablewidget.h>
#include <qdialogbuttonbox.h>
#include <QVBoxLayout>
#include "qtrendbtable.h"
#include "qtrendbdisparea.h"
#include "view/qtrendattr.h"
#include "view/qtrenddatagroupattr.h"

namespace Ui {
    class QTrendDataGroup;
}
class QGraphicsScene;
class QTrendDataGroup : public QDialog
{
    Q_OBJECT

public:
    explicit QTrendDataGroup(QTrendDataGroupAttr *pItem, QWidget *parent = 0);
    ~QTrendDataGroup();

private:
    Ui::QTrendDataGroup *ui;
    QGraphicsScene scene;
    int oId;

public:
    QTrendDataGroupAttr*      m_pCopyItem;//拷贝存储

public:
    void InitAllProperty(QTrendDataGroupAttr *pItem);

public:
    QTrendbTable*       m_pTrendTableDlg;   //数据群组外观设置对话框
    QTrendbDispArea*    m_pTrendDispAreaDlg;//数据群组显示设置对话框
    //QTrendbColor*       m_pTrendColor;      //数据群组颜色设置对话框
    SecurityWidget *pSecurityWight;//显现页面

private slots:

    void on_help_clicked();
    void on_cancel_clicked();
    void on_accept_clicked();
};

#endif // QTRENDDATAGROUP_H
