#ifndef NEWPRORIGHT_H
#define NEWPRORIGHT_H

#include <QDialog>

namespace Ui {
    class NewProRight;
}

class NewProRight : public QDialog
{
    Q_OBJECT

public:
    explicit NewProRight(QWidget *parent = 0);
    ~NewProRight();

private:
    Ui::NewProRight *ui;

private:
    bool bFirst;

private slots:
    void on_checkBox_dateY5_clicked(bool checked);
    void on_checkBox_dateY4_clicked(bool checked);
    void on_checkBox_dateY3_clicked(bool checked);
    void on_checkBox_dateY2_clicked(bool checked);
    void on_checkBox_dateY1_clicked(bool checked);
    void on_checkBox_dayX5_clicked(bool checked);
    void on_checkBox_dayX4_clicked(bool checked);
    void on_checkBox_dayX3_clicked(bool checked);
    void on_checkBox_dayX2_clicked(bool checked);
    void on_checkBox_dayX1_clicked(bool checked);
    void on_helpbtn_clicked();
    void on_comboBox_aging_currentIndexChanged(int index);
    void on_comboBox_proRight_currentIndexChanged(int index);
    void on_pushButton_cancel_clicked();
    void on_pushButton_sure_clicked();
private:
    void setGroupBox2Enabled(bool bFlag = true);
    void setGroupBox3Enabled(bool bFlag = true);
    void setGroupBox2Checked(bool bChecked);
    void setGroupBox3Checked(bool bChecked);
};

#endif // NEWPRORIGHT_H
