#ifndef QRECTDLG_H
#define QRECTDLG_H

#include <QDialog>
#include "qpickercolor.h"
#include "qgraphicsitem.h"
//#include "view/qrectitem.h"
#include "QDialogButtonBox"
//#include "view/qpolygonitem.h"
//#include "view/qelipseitem.h"
#include "view/qrectbasicitem.h"
#include "view/qelipsebasicitem.h"
#include "view/qpolygonbasicitem.h"
namespace Ui {
    class QRectDlg;
}

class QRectDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QRectDlg(QGraphicsItem *item,QWidget *parent = 0);
    ~QRectDlg();

    void RectInit(QGraphicsItem *item);
    QGraphicsItem *pTempRectItem;
    QRectBasicItem *pRectItem;
    QElipseBasicItem *pElipseItem;
    QPolygonBasicItem *pPolygonItem;

    QRectItem *pRectItemOld;
    QElipseItem *pElipseItemOld;
    QPolygonItem *pPolygonItemOld;

    QVBoxLayout *mainLayout ;
    ColorPickerPopup *colorPicker;
    ColorPickerPopup *colorPicker2;
    ColorPickerPopup *colorPicker3;
    SecurityWidget* pSecurity;
public slots:
    void confyButton();
private slots:
   void loadHelp();
private:
    QDialogButtonBox *buttonBox;
    Ui::QRectDlg *ui;

private slots:
    void on_Fore_Color_clicked();
    void on_Back_Color_clicked();
    void on_Line_Color_clicked();

    void setCurrentLineColor(const QColor &);
    void setCurrentBKColor(const QColor &);
    void setCurrentFrontColor(const QColor &);

};

#endif // QRECTDLG_H
