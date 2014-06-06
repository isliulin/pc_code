#ifndef QUPLOADDLG_H
#define QUPLOADDLG_H

#include <QDialog>
#include "qfiledialog.h"
#include "qmessagebox.h"
namespace Ui {
    class QUploadDlg;
}

class QUploadDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QUploadDlg(QWidget *parent = 0);
    ~QUploadDlg();
    void uploadfile(QFile &file);

private:
    Ui::QUploadDlg *ui;

private slots:
    void on_UploadStart_clicked();
    void on_UploadCancel_clicked();
    void on_pushButton_clicked();
};

#endif // QUPLOADDLG_H
