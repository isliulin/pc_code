#ifndef NEWUSERRIGHT_H
#define NEWUSERRIGHT_H

#include <QDialog>

namespace Ui {
    class NewUserRight;
}

class NewUserRight : public QDialog
{
    Q_OBJECT

public:
    explicit NewUserRight(QWidget *parent = 0);
    ~NewUserRight();
    void init();

private:
    Ui::NewUserRight *ui;

private slots:
    void on_pushButton_help_clicked();
    void on_tableWidget_group_cellDoubleClicked(int row, int column);
    void on_tableWidget_user_cellDoubleClicked(int row, int column);
    void on_pushButton_delGroup_clicked();
    void on_pushButton_attrGroup_clicked();
    void on_pushButton_addGroup_clicked();
    void on_pushButton_delUser_clicked();
    void on_pushButton_attrUser_clicked();
    void on_pushButton_addUser_clicked();
    void on_pushButton_quit_clicked();
};

#endif // NEWUSERRIGHT_H
