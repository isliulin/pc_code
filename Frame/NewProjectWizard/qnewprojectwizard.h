#ifndef QNEWPROJECTWIZARD_H
#define QNEWPROJECTWIZARD_H

#include <QWizardPage>
#include "ui_qnewprojectwizard.h"

namespace Ui {
    class QNewProjectWizard;
};

class QNewProjectWizard : public QWizardPage
{
    Q_OBJECT

public:
    explicit QNewProjectWizard(QWidget *parent = 0);
    ~QNewProjectWizard();

public:
    Ui::QNewProjectWizard *ui;

private slots:
     void on_showmodel_2_currentIndexChanged(QString );
     void on_showmodel_currentIndexChanged(int index);
     void on_HMImodel_currentIndexChanged(QString index);
     void on_newpro_pushButton_clicked();
     void DrawScreenSize();
private:
     void initHIMSetting();
};

#endif // QNEWPROJECTWIZARD_H
