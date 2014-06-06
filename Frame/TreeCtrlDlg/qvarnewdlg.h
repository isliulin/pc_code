#ifndef QVARNEWDLG_H
#define QVARNEWDLG_H

#include <QDialog>
#include "qvardlg.h"
#include "Frame/qprogectmanager.h"
namespace Ui {
    class QVarNewdlg;
}

class QVarNewdlg : public QDialog
{
    Q_OBJECT

public:
    explicit QVarNewdlg(int index,int newModify,VarRecord *pRecord,QWidget *parent = 0);
    VarRecord *pRecordTemp;
    QVardlg *pVarDlgTemp;
    int indextmp;
    ~QVarNewdlg();

private:
    Ui::QVarNewdlg *ui;
    bool checkName(QString str);
private slots:
    void on_m_cancel_clicked();
    void on_m_ok_clicked();
    void on_m_addrinput_clicked();
};

#endif // QVARNEWDLG_H
