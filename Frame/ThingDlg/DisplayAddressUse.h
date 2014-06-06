#ifndef DISPLAYADDRESSUSE_H
#define DISPLAYADDRESSUSE_H

#include <QDialog>
#include "Frame/mainwindow.h"

namespace Ui {
    class DisplayAddressUse;
}

class DisplayAddressUse : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayAddressUse(QWidget *parent = 0);
    ~DisplayAddressUse();

private:
    Ui::DisplayAddressUse *ui;

private slots:
    void on_m_table_cellDoubleClicked(int row, int column);
    void on_m_sheetcmb_currentIndexChanged(QString );
    void on_m_radio2_clicked();
    void on_m_radio1_clicked();

private:
    int  nSelctType;//—°‘Ò¿‡–Õ
    void InitTable();
    int  totalAddrCount();
};

#endif // DISPLAYADDRESSUSE_H
