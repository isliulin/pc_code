#ifndef SUBDATACONTROL_H
#define SUBDATACONTROL_H

#include <QDialog>
#include "Frame/qprogectmanager.h"
#include <QButtonGroup>
#include "ui_subdatacontrol.h"

namespace Ui {
    class subDataControl;
}

class subDataControl:public QDialog
{
    Q_OBJECT
public:
    explicit subDataControl(QWidget *parent = 0);
    ~subDataControl();

public:
    Ui::subDataControl *ui;

public:
    QButtonGroup * sel_group;
    Keyboard kaddress;

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_comboBox_currentIndexChanged(int);
    void on_checkBox_close_stateChanged(int);
    void on_checkBox_stateChanged(int);
};

#endif // SUBDATACONTROL_H
