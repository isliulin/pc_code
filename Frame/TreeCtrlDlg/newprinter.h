#ifndef NEWPRINTER_H
#define NEWPRINTER_H

#include <QDialog>

namespace Ui {
    class NewPrinter;
}

class NewPrinter : public QDialog
{
    Q_OBJECT

public:
    explicit NewPrinter(QWidget *parent = 0);
    ~NewPrinter();

private:
    Ui::NewPrinter *ui;

private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_sure_clicked();
};

#endif // NEWPRINTER_H
