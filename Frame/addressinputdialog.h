#ifndef ADDRESSINPUTDIALOG_H
#define ADDRESSINPUTDIALOG_H
#include "ui_addressinputdialog.h"
#include <QLineEdit>

#include <QDialog>
#include "Frame/qprogectmanager.h"
namespace Ui {
    class AddressInputDialog;
}

class AddressInputDialog : public QDialog
{
    Q_OBJECT

public:
    AddressInputDialog(QWidget *parent = 0,int addrType = 0);
    AddressInputDialog(Keyboard &address,QString sAddr,int addrType = 0,QWidget *parent = 0);
    AddressInputDialog(Keyboard &address,QWidget *parent = 0,int addrType = 0);
    void init();
    int IsCorrect();
	int checkAddrFromLib(int connectIndex,int protocolIndex,int registerIndex);

    void setAllparam(QString sAddr,int addrType);

    ~AddressInputDialog();
    Keyboard *temp_address,*localkeyboard;
    QLineEdit  *gl_lineeditintput;//��ַ����Ի����ϵĵ�ַlineedit��ֵ
    QString temp_Com;//��ʱ�洢COM����Ϣ
    QString temp_PLC_Station;//��ʱ���PLCվ����Ϣ
public:
    Ui::AddressInputDialog *ui;

public:
    int m_type;//��ַ���� 0: λ��ַ 1:�ֵ�ַ ����ֵ�������Ƶ�ַ����
    QString GetHMIModel();
    bool NumIsDigit2(QString str);//�޷���10����
	int findConnect(int index);

private slots:

    void on_comboBox_protocol_currentIndexChanged(QString name);
    void on_comboBox_register_currentIndexChanged(int index);
    void on_addressinputdialog_address_lineedit_textChanged(QString );
    void on_plc_station_currentIndexChanged(int index);
    void on_comboBox_storage_currentIndexChanged(int index);
    void on_pushbtncolon_clicked();
    void on_pushbtnslash_clicked();
    void on_pushbtndot_clicked();
    void on_pushbtnf_clicked();
    void on_pushbtne_clicked();
    void on_pushbtnd_clicked();
    void on_pushbtnc_clicked();
    void on_pushbtnb_clicked();
    void on_pushbtna_clicked();
    void on_pushbtnintput_clicked();
    void on_pushbtnquit_clicked();
    void on_pushbtnback_clicked();
    void on_pushbtnclear_clicked();
    void on_pushButton0_clicked();
    void on_pushButton9_clicked();
    void on_pushButton8_clicked();
    void on_pushButton7_clicked();
    void on_pushbtn6_clicked();
    void on_pushbtn5_clicked();
    void on_pushbtn4_clicked();
    void on_pushbtn3_clicked();
    void on_pushbtn2_clicked();
    void on_pushbtn1_clicked();
};

#endif // ADDRESSINPUTDIALOG_H
