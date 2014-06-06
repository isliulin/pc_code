#ifndef QTIMERGENDLG_H
#define QTIMERGENDLG_H

#include <QWidget>
#include "ui_qtimergendlg.h"

namespace Ui {
    class QTimerGenDlg;
}

class QTimerGenDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QTimerGenDlg(QWidget *parent = 0);
    ~QTimerGenDlg();

public:
    Ui::QTimerGenDlg *ui;
private:
    QStringList sMarcoName;

    void LoadTimerShape();
public:
    Keyboard BitAddr;
    QGraphicsScene *pScene;
    QGraphicsItem * pCopyItem;
public:
    void InitParament();
    void GeneralSave(QStringList *datalist);
    void DoubleClickInit(QGraphicsItem *pItem);

private slots:
    void on_comboBox_2_currentIndexChanged(int index);
    void on_m_addrbtn_clicked();
    void on_comboBox_currentIndexChanged(int index);
};

#endif // QTIMERGENDLG_H
