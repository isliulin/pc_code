#ifndef XYTRENDDLG_H
#define XYTRENDDLG_H

#include <QDialog>
#include "view/xytrend.h"
#include <qgraphicsitem.h>
class QTrendadisplay;
class XYTrendGenDlg;
class SecurityWidget;

namespace Ui {
    class XYTrendDlg;
}

class XYTrendDlg : public QDialog
{
    Q_OBJECT

public:
    explicit XYTrendDlg(XYtrend *pItem,QWidget *parent = 0);
    ~XYTrendDlg();
    void InitAllProperty(XYtrend *pItem);
    XYtrend *m_pCopyItem;
private:
    Ui::XYTrendDlg *ui;
    QTrendadisplay* m_pTrendDisplay;//显示设置
    XYTrendGenDlg* m_pGenDlg;//一般页面
    SecurityWidget *pSecurityWight;//显现页面
    QGraphicsScene scene;
    int oId;

private slots:

    void on_help_clicked();
    void on_cancel_clicked();
    void on_accept_clicked();
};

#endif // XYTRENDDLG_H
