#ifndef QFLOWBLOCK_H
#define QFLOWBLOCK_H

#include <QDialog>
#include "qflowblockgendlg.h"
#include "view/FlowBlockItem.h"
#include "Frame/ThingDlg/switch/securitywidget.h"

namespace Ui {
    class qFlowBlock;
}

class qFlowBlock : public QDialog
{
    Q_OBJECT

public:
    explicit qFlowBlock(QGraphicsItem *pItem,QWidget *parent = 0);
    ~qFlowBlock();

public:
    QFlowBlockGenDlg *pQFlowBlockGen;
    FlowInfo m_flow;
    FlowBlockItem *pCopyItem;
    securityPro sproperty;
    SecurityWidget *securitywidgets; //È¨ÏÞÒ³Ãæ
    void InitAllProperty(FlowBlockItem *pItem);
    QGraphicsScene *pScene;
private:
    Ui::qFlowBlock *ui;
    int nDirection;
    int nFlowCount;
    QList<QRectItem *> pRectList;
    int oId;
public slots:
    void onDrawFlow();
private slots:
    void on_help_clicked();
    void on_cancel_clicked();
    void on_accept_clicked();
};

#endif // QFLOWBLOCK_H
