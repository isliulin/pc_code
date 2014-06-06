#ifndef QNEWPRODLGEX_H
#define QNEWPRODLGEX_H

#include <QDialog>

#include "qnewprojectwizard.h"
#include "qnewlinkwizard.h"

namespace Ui {
    class qNewProDlgEx;
}

class qNewProDlgEx : public QDialog
{
    Q_OBJECT

public:
    explicit qNewProDlgEx(QWidget *parent = 0);
    ~qNewProDlgEx();

    QNewProjectWizard  *newprowizard;
    QNewLinkWizard  *newlinkwizard;
private:
    Ui::qNewProDlgEx *ui;
private slots:
    void on_pushButton_Next_clicked();
    void on_pushButton_Pre_clicked();
    void on_pushButton_Done_clicked();
    void on_pushButton_Cancel_clicked();
private:
    void initTreeHMIUserPage();
    void initHMIPrinter();
    void initTreeFileProtectDlg();
    void initTreeLanguageDlg();
    void initCom();
protected:
    void closeEvent(QCloseEvent * event);
};

#endif // QNEWPRODLGEX_H
