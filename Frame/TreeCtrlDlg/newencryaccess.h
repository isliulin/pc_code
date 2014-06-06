#ifndef NEWENCRYACCESS_H
#define NEWENCRYACCESS_H

#include <QDialog>

namespace Ui {
    class NewEncryAccess;
}

class NewEncryAccess : public QDialog
{
    Q_OBJECT

public:
    explicit NewEncryAccess(QWidget *parent = 0);
    ~NewEncryAccess();

private:
    Ui::NewEncryAccess *ui;

private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_sure_clicked();
};

#endif // NEWENCRYACCESS_H
