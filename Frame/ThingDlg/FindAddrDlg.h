#ifndef FINDADDRDLG_H
#define FINDADDRDLG_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
    class FindAddrDlg;
}

class FindAddrDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FindAddrDlg(QWidget *parent = 0);
    ~FindAddrDlg();

private:
    Ui::FindAddrDlg *ui;

    QButtonGroup * Type_Group;
public:
    QString sAddress;
    bool bIfCase;//�Ƿ�ѡ���Сд
    bool bIfSame;//�Ƿ�ѡ����ȫƥ��
    int iSelctType;//ѡ�����ͣ�0Ϊ��ַ���ң�1Ϊ�ı�����
    QString sReplaceMsg; //�滻����

private slots:
    void on_m_cancel_clicked();
    void on_m_ok_clicked();
    void selectType(int iCheckId);
};

#endif // FINDADDRDLG_H
