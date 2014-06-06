#ifndef QDATATRANSPORTDLG_H
#define QDATATRANSPORTDLG_H

#include <QDialog>

namespace Ui {
    class QDataTransportDlg;
}

class QDataTransportDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDataTransportDlg(QWidget *parent = 0);
    ~QDataTransportDlg();
    QString CheckToStr(int iDataIndex);

private:
    Ui::QDataTransportDlg *ui;
private slots:
    void on_HelpButton_clicked();
    void on_Close_clicked();
    void on_listWidget_doubleClicked(QModelIndex index);
    void on_Alter_clicked();
    void on_Delete_clicked();
    void on_New_clicked();
};

#endif // QDATATRANSPORTDLG_H
