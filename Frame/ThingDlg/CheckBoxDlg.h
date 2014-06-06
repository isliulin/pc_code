#ifndef CHECKBOXDLG_H
#define CHECKBOXDLG_H

#include <QDialog>
#include "view/CheckBoxItem.h"

namespace Ui {
    class CheckBoxDlg;
}

class CheckBoxDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CheckBoxDlg(QWidget *parent = 0);
    ~CheckBoxDlg();

private:
    void initUiDlg();

public:
    CheckBoxItem *pCopyItem;

private:
    Ui::CheckBoxDlg *ui;
};

#endif // CHECKBOXDLG_H
