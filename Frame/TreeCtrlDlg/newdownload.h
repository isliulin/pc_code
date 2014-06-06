#ifndef NEWDOWNLOAD_H
#define NEWDOWNLOAD_H

#include <QDialog>
#include <QButtonGroup>
class IpAddressWidget;
namespace Ui {
    class NewDownload;
}

class NewDownload : public QDialog
{
    Q_OBJECT

public:
    explicit NewDownload(QWidget *parent = 0);
    ~NewDownload();

private:
    Ui::NewDownload *ui;
    QButtonGroup *pType;
    IpAddressWidget *ipEdit;

private slots:
    void on_pushButton_help_clicked();
    void on_checkBox_5_clicked(bool checked);
    void on_groupBox_2_clicked(bool checked);
    void on_pushButton_cancel_clicked();
    void on_pushButton_sure_clicked();

    void downTypeSelect(int iCheckId);
};

#endif // NEWDOWNLOAD_H
