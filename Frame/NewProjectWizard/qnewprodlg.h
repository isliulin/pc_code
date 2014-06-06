#ifndef QNEWPRODLG_H
#define QNEWPRODLG_H

#include <QWizard>

#include "qnewprojectwizard.h"
#include "qnewlinkwizard.h"

class QNewProDlg : public QWizard
{
    Q_OBJECT
public:
    explicit QNewProDlg(QWidget *parent = 0);

    QNewProjectWizard  *newprowizard;
    QNewLinkWizard  *newlinkwizard;

    enum{Page_NewProWizard,
          Page_NewLinkWizard,
          Page_NewScreenWizard};

    void initCom();
    bool validateCurrentPage();
    virtual void cleanupPage(int id);
    void  initTreeLanguageDlg();
    void initTreeHMIstateDlg(); //��ʼ�����ؼ��ϵ�HMI״̬�Ի���
    void initTreeHMIProtectDlg();//��ʼ��HMI�����Ի���
    void initHMIPrinter();//��ʼ��HMI��ӡ������
    void initTreeHMIUserPage();
    void initTreeFileProtectDlg();//��ʼ���ļ������Ի���

signals:
private slots:
   void setSubTitle(int);

public: //edit by zqh
    void DrawScreenSize(); //���ƻ���

};

#endif // QNEWPRODLG_H
