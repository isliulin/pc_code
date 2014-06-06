#ifndef NEWINITSET_H
#define NEWINITSET_H

#include <QDialog>

namespace Ui {
    class NewInitSet;
}

class NewInitSet : public QDialog
{
    Q_OBJECT

public:
    explicit NewInitSet(QWidget *parent = 0);
    ~NewInitSet();

private:
    Ui::NewInitSet *ui;

private slots:
    void on_helpbtn_clicked();
    void on_comboBox_peifang_currentIndexChanged(int index);
    void on_comboBox_peifang_2_currentIndexChanged(int index);
    void on_comboBox_standbyModel_currentIndexChanged(int index);
    void on_groupBox_3_clicked(bool checked);
    void on_groupBox_clicked(bool checked);
    void on_pushButton_cancel_clicked();
    void on_pushButton_sure_clicked();
};

#endif // NEWINITSET_H
