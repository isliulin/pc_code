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
    void initTreeHMIstateDlg(); //初始化树控件上的HMI状态对话框
    void initTreeHMIProtectDlg();//初始化HMI保护对话框
    void initHMIPrinter();//初始化HMI打印机数据
    void initTreeHMIUserPage();
    void initTreeFileProtectDlg();//初始化文件保护对话框

signals:
private slots:
   void setSubTitle(int);

public: //edit by zqh
    void DrawScreenSize(); //绘制画面

};

#endif // QNEWPRODLG_H
