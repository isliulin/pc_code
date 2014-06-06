#ifndef QVALUEDATEINPUTDLG_H
#define QVALUEDATEINPUTDLG_H

#include <QWidget>
#include <QGraphicsItem>
#include "view/DataDisplayItem.h"
//#include "qvaluedlg.h"

namespace Ui {
    class QValueDateInputDlg;
}

class QValueDateInputDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QValueDateInputDlg(QWidget *parent = 0);
    ~QValueDateInputDlg();
    void Init(DataDisplayItem *pItem = NULL);
    bool onDataGenSave(DataInfo &data_st);//保存数值显示信息
    bool onAsciiGenSave(ASCIIINFO &ascii_st);  //保存ascii显示信息
    bool IsHaveKeyboard();

private:
    Ui::QValueDateInputDlg *ui;
    bool bInitFlag;
    Keyboard Monitor_Address_Keyboard;

private slots:
    void on_m_keyspBox_currentIndexChanged(int index);
    void on_m_PouupckBox_clicked(bool checked);
    void on_Monitor_Address_EntryBtn_clicked();
    void on_m_BitradioBtn_clicked();
    void on_m_touchradioBtn_clicked();
};

#endif // QVALUEDATEINPUTDLG_H
