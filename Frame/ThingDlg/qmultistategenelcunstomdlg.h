#ifndef QMULTISTATEGENELCUNSTOMDLG_H
#define QMULTISTATEGENELCUNSTOMDLG_H
#include "ui_qmultistategenelcunstomdlg.h"
#include <QDialog>

namespace Ui {
    class QMultiStateGenelCunstomDlg;
}

class QMultiStateGenelCunstomDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QMultiStateGenelCunstomDlg(QWidget *parent = 0);
    ~QMultiStateGenelCunstomDlg();

    void setAllData(QVector<double > values,bool bInit);
    void setAllData(QVector<int > values,bool bInit);
    int nCurrentRow;
    QVector<int >allValues;
    QVector<double > getValues();
    void setRange(int type);
public:
    Ui::QMultiStateGenelCunstomDlg *ui;
private slots:
    void on_sData_textChanged(QString );
    void on_pushButton_down_clicked();
    void on_pushButton_up_clicked();
    void on_pushButton_cancle_clicked();
    void on_pushButton_ok_clicked();
    void setBtn(int,int);

};

#endif // QMULTISTATEGENELCUNSTOMDLG_H
