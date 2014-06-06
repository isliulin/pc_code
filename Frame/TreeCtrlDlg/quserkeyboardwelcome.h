#ifndef QUSERKEYBOARDWELCOME_H
#define QUSERKEYBOARDWELCOME_H

#include <QWizardPage>

namespace Ui {
    class QUserkeyboardwelcome;
}

class QUserkeyboardwelcome : public QWizardPage
{
    Q_OBJECT

public:
    explicit QUserkeyboardwelcome(QWidget *parent = 0);
    ~QUserkeyboardwelcome();

private:
    Ui::QUserkeyboardwelcome *ui;
};

#endif // QUSERKEYBOARDWELCOME_H
