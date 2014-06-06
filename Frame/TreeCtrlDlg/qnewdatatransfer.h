#ifndef QNEWDATATRANSFER_H
#define QNEWDATATRANSFER_H

#include <QDialog>
#include "qbuttongroup.h"
#include "Frame/qprogectmanager.h"
namespace Ui {
    class QNewDataTransfer;
}

class QNewDataTransfer : public QDialog
{
    Q_OBJECT

public:
    explicit QNewDataTransfer(QWidget *parent = 0);
    QNewDataTransfer(int CheckRow,QWidget *parent);
    ~QNewDataTransfer();
    QButtonGroup *R_Group;
    Keyboard kTriggerBit;
    Keyboard kSourceAddress;
    Keyboard kDestinationAdderss;
    Keyboard kLengthAddress;
    int iFlg;//��־���޸����ݻ�����������
    int iCurrentRow;//��־��ǰѡ�е���
    void DataSive(int index);
private:
    Ui::QNewDataTransfer *ui;

private slots:
    void on_btn_length_clicked();
    void on_check_length_clicked(bool checked);
    void on_cancel_clicked();
    void on_Accept_clicked();
    void on_Destination_Address_Keyboard_clicked();
    void on_Source_Address_Keyboard_clicked();
    void on_Trigger_Bit_Keyboard_clicked();
    void on_Triggered_clicked(bool checked);
    void on_Timed_clicked(bool checked);
};

#endif // QNEWDATATRANSFER_H
