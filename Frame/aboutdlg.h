#ifndef ABOUTDLG_H
#define ABOUTDLG_H

#include <QDialog>

namespace Ui {
    class AboutDlg;
}

class AboutDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDlg(QWidget *parent = 0);
    ~AboutDlg();

private:
    Ui::AboutDlg *ui;

private slots:
    void on_OKBtn_clicked();
};

#endif // ABOUTDLG_H
