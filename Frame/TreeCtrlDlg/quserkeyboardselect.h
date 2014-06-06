#ifndef QUSERKEYBOARDSELECT_H
#define QUSERKEYBOARDSELECT_H
#include "ui_quserkeyboardselect.h"

#include <QWizardPage>

namespace Ui {
    class QUserkeyboardselect;
}

class QUserkeyboardselect : public QWizardPage
{
    Q_OBJECT

public:
    explicit QUserkeyboardselect(QWidget *parent = 0);
    ~QUserkeyboardselect();

    Ui::QUserkeyboardselect *ui;

private slots:
    void on_CASCIIKeyboard_clicked(bool checked);
    void on_CNumberKeyboard_clicked();
};

#endif // QUSERKEYBOARDSELECT_H
