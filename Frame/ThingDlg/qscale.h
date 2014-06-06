#ifndef QSCALE_H
#define QSCALE_H

#include <QDialog>
#include <QGraphicsItem>
#include "Frame/ThingDlg/scalesdlg.h"
#include "ui_scalesdlg.h"
namespace Ui {
    class qScale;
}

class qScale : public QDialog
{
    Q_OBJECT

public:
    explicit qScale(QGraphicsItem *pItem,QWidget *parent = 0);
    ~qScale();

public:
    ScalesDlg *pGeneralDlg;
    Calibration caliInfo;
    CalibrationItem *pCopyItem;
private:
    Ui::qScale *ui;
    QGroupItem *pBaseItem;
    QGraphicsScene *pScene;
    SecurityWidget* pSecurity;
    int oId;
private:
    QSimpleTextItem* DrawText(QSimpleTextItem* pText,int nIndex,double LineX,
                              double LineY,QString sText);
    QString GetText(int nIndex);
    int GetTextLength(QString sText,QSimpleTextItem* pText);
public slots:
    void onDrawScales();

private slots:
    void on_help_clicked();
    void on_cancel_clicked();
    bool on_accept_clicked();
};

#endif // QSCALE_H
