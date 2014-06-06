#ifndef QVALUESCALEDLG_H
#define QVALUESCALEDLG_H

#include <QWidget>
#include "view/DataDisplayItem.h"

namespace Ui {
    class QValueScaleDlg;
}

class QValueScaleDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QValueScaleDlg(QWidget *parent = 0);
    ~QValueScaleDlg();

public:
    Ui::QValueScaleDlg *ui;
private:
    Keyboard Monitor_Address_Keyboard;
private slots:
    void on_m_ShowcbBox_currentIndexChanged(int index);
    void on_m_SourcecbBox_currentIndexChanged(int index);

    void onSetRange(double dMax, double dMin, int type,int base);

    void on_m_sMaxAddress_EntryBtn_clicked();
    void on_m_sMinAddress_EntryBtn_clicked();
};

#endif // QVALUESCALEDLG_H
