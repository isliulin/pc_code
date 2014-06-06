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
    bool bIfCase;//是否选择大小写
    bool bIfSame;//是否选择完全匹配
    int iSelctType;//选择类型，0为地址查找，1为文本查找
    QString sReplaceMsg; //替换内容

private slots:
    void on_m_cancel_clicked();
    void on_m_ok_clicked();
    void selectType(int iCheckId);
};

#endif // FINDADDRDLG_H
