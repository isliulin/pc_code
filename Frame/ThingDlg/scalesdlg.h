#ifndef SCALESDLG_H
#define SCALESDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include <QGraphicsScene>
#include "view/qgroupitem.h"
#include "ui_scalesdlg.h"
#include "view/calibrationitem.h"

namespace Ui {
    class ScalesDlg;
}

class ScalesDlg : public QWidget
{
    Q_OBJECT

public:
    explicit ScalesDlg(QWidget *parent = 0);
    ~ScalesDlg();

public:
    Ui::ScalesDlg *ui;

private slots:
    void on_m_showtextcheck_clicked();
    void on_m_textcolorbtn_clicked();
    void on_m_linecolorbtn_clicked();
    void on_m_showtextcheck_clicked(bool checked);
    void on_m_pointnumcmb_currentIndexChanged(int index);
    void on_m_fontsizecmb_currentIndexChanged(int index);
    void on_m_maxedit_textChanged(QString );
    void on_m_minedit_textChanged(QString );
    void on_m_pointnumcmb_highlighted(int index);
    void on_m_subspin_valueChanged(int );
    void on_m_mainspin_valueChanged(int );
    void on_m_textdirectioncmb_currentIndexChanged(int index);
    void on_m_showscalecheck_clicked(bool checked);
    void OnSetLineColor(const QColor &);
    void OnSetTextColor(const QColor &);
    void OnScaleDirectionChange(int nIndex);
public:
    bool bInitFlag;
    QButtonGroup *pDirection;
    QGraphicsScene *pScene;
public:
    QGraphicsItem *pOldItem;
    CalibrationItem *pCopyItem;
public:
    void InitParament();
    void SaveGeneralPage(Calibration &m_calibration);
    void DoubleClickInit(CalibrationItem *pItem);

signals:
    void DrawScales();
};

#endif // SCALESDLG_H
