#ifndef INFODLG_H
#define INFODLG_H

#include <QDialog>
class downloadTrd ;
namespace Ui {
    class InfoDlg;
}

class InfoDlg : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDlg(QWidget *parent = 0);
    ~InfoDlg();


private:
    downloadTrd *thread;
    Ui::InfoDlg *ui;

private slots:
    void on_pushButton_clicked();
    void Serial(QString sNumber,int type);
};

#endif // INFODLG_H
