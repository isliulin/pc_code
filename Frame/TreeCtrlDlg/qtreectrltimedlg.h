#ifndef QTREECTRLTIMEDLG_H
#define QTREECTRLTIMEDLG_H

#include <QDialog>
#include <Frame/qprogectmanager.h>
namespace Ui {
    class QTreeCtrlTimeDlg;
}

class QTreeCtrlTimeDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QTreeCtrlTimeDlg(QWidget *parent = 0);
    ~QTreeCtrlTimeDlg();

     void initDlg();

     QDialogButtonBox  *buttonbox;
     Keyboard kWriteTimeToPLC;
     Keyboard kWriteTriggered;
     Keyboard kReadAddress;
     Keyboard kReadTriggered;
private:
    Ui::QTreeCtrlTimeDlg *ui;

private slots:

    void on_treectrltimedlg_sametimewithPLC_groupbox_toggled(bool );
    void on_treectrltimedlg_timetoHMI_groupbox_toggled(bool );

    void on_sametimewithPLC_trigered_pushButton_clicked();
    void on_sametimewithPLC_readaddress_pushButton_clicked();
    void on_timetoplc_trigered_pushButton_clicked();
    void on_timetoplc_writeaddress_pushButton_clicked();

    void on_sametimewithPLC_trigered_radioButton_clicked();
    void on_sametimewithPLC_timed_radioButton_clicked();

    void on_timetoplc_trigerred_radiobutton_clicked();
    void on_timetoplc_timed_radiobutton_clicked();

public slots:
    void confyButton();
    void helpButton();
};

#endif // QTREECTRLTIMEDLG_H
