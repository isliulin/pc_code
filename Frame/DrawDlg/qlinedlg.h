#ifndef QLINEDLG_H
#define QLINEDLG_H

#include <QDialog>
#include "qgraphicsitem.h"
#include "QDialogButtonBox"
#include "qpickercolor.h"
#include "color.h"
//#include "view/qpolygonitem.h"
//#include "view/qlineitem.h"
#include "view/qlinebasicitem.h"
#include "view/qfoldlinebasicitem.h"
#include "view/qlinecirclebasicitem.h"
#include "view/qfreelinebasicitem.h"
namespace Ui {
    class QLineDlg;
}

class QLineDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QLineDlg(QGraphicsItem *item,QWidget *parent = 0);
    ~QLineDlg();
    QLineBasicItem *pLineItem;
    QFoldLineBasicItem *pFoldLineItem;
    QFreeLineBasicItem *pFreeLineItem;
    QLineCircleBasicItem *pLineCircleItem;

    QLineItem *pLineItemOld;
    QFoldLineItem *pFoldLineItemOld;
    QFreeLineItem *pFreeLineItemOld;
    QLineCircleItem *pLineCircleItemOld;

    void LineInit(QGraphicsItem *item);
    QGraphicsItem *pTempItem;
    QVBoxLayout *mainLayout;
    ColorPickerPopup *colorPicker;
public slots:
    void confyButton();
private slots:
   void loadHelp();
private:
    Ui::QLineDlg *ui;
    QDialogButtonBox *buttonBox;
    SecurityWidget* pSecurity;
    int oId;
private slots:
    void on_Line_Color_clicked();
    void setCurrentLineColor(const QColor &);
};

#endif // QLINEDLG_H
