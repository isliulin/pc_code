#ifndef PROTOCOLDLG_H
#define PROTOCOLDLG_H

#include <QDialog>

namespace Ui {
    class ProtocolDlg;
}
class ProtocolDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ProtocolDlg(stProtocol protocol,int index,bool bEthnet , int iProType, QWidget *parent = 0);
    ~ProtocolDlg();

public:
    stProtocol m_Protocol;
private:
    void setDefault();
    void updataUi();
    Ui::ProtocolDlg *ui;
    int m_Index;

private slots:

    void on_btn_help_clicked();
    void on_btn_default_clicked();
    void on_btn_accepted();
    void on_combo_manu_Changed(QString manuName);
    void on_combo_model_Changed(QString modelName);
private:
    int m_iType;
};

#endif // PROTOCOLDLG_H
