#ifndef POWERPROTECTDLG_H
#define POWERPROTECTDLG_H

#include <QDialog>

namespace Ui {
    class PowerProtectDlg;
}

class PowerProtectDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PowerProtectDlg(QWidget *parent = 0);
    ~PowerProtectDlg();

private:
    Ui::PowerProtectDlg *ui;

private slots:
    void on_btn_help_clicked();
    void on_btn_cancel_clicked();
    void on_btn_ok_clicked();
};

#endif // POWERPROTECTDLG_H
