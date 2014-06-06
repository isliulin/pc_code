#ifndef INSERTDATASAMPLE_H
#define INSERTDATASAMPLE_H

#include <QDialog>
#include "Frame/qprogectmanager.h"

namespace Ui {
    class InsertDataSample;
}

class InsertDataSample : public QDialog
{
    Q_OBJECT

public:
    explicit InsertDataSample(DATA_ADDRESS_ITEM item,QWidget *parent = 0);
    ~InsertDataSample();
	QString getDatatypeStr();
	int sampleCount();
	QVector <Keyboard> getAddrs();

public:
    DATA_ADDRESS_ITEM m_Item;
private:
    Ui::InsertDataSample *ui;
	int row;

private slots:
    void on_combo_datatype_currentIndexChanged(int index);
    void on_groupBox_clicked(bool checked);
    void on_btn_addr_clicked();
    void on_btn_cancel_clicked();
    void on_btn_ok_clicked();
};

#endif // INSERTDATASAMPLE_H
