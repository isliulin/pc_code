#ifndef OPERATORSET_H
#define OPERATORSET_H

#include <QDialog>

namespace Ui {
    class operatorSet;
}

class operatorSet : public QDialog
{
    Q_OBJECT

public:
    explicit operatorSet(QWidget *parent = 0);
    ~operatorSet();

private:
    Ui::operatorSet *ui;

private slots:
    //void on_checkBox_clicked(bool checked);
    void on_check_autologin_clicked(bool checked);
    void on_pushButton_cancel_clicked();
    void on_pushButton_sure_clicked();
};

#endif // OPERATORSET_H
