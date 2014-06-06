#ifndef QNEWLINKWIZARD_H
#define QNEWLINKWIZARD_H

#include <QWizardPage>
#include "ui_qnewlinkwizard.h"

namespace Ui {
    class QNewLinkWizard;
}

class QNewLinkWizard : public QWizardPage
{
    Q_OBJECT
public:
    explicit QNewLinkWizard(QWidget *parent = 0);
    ~QNewLinkWizard();
public:
    Ui::QNewLinkWizard *ui;
private slots:
    void on_newlinkwizard_linkport_combobox_3_currentIndexChanged(QString );
    void on_newlinkwizard_linkport_combobox_2_currentIndexChanged(QString );
    void on_newlinkwizard_server_combobox_currentIndexChanged(QString );
    void on_newlinkwizard_device_combobox_currentIndexChanged(int index);
    void on_newlinkwizard_linkport_combobox_currentIndexChanged(QString);
private:
    int getProtocolType();
};

#endif // QNEWLINKWIZARD_H
