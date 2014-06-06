#ifndef QTRENDBGSET_H
#define QTRENDBGSET_H

#include <QDialog>

namespace Ui {
    class QTrendbgSet;
}

class QTrendbgSet : public QDialog
{
    Q_OBJECT

public:
    explicit QTrendbgSet(QVector<QString > groups, QWidget *parent = 0);
    ~QTrendbgSet();

public:
    QVector<QString > vecGroup;
    int m_nGroupNum;    //������
    int m_nGroupBegin;  //��ʼ���
    int m_nMaxNum;      //�������

private:
    Ui::QTrendbgSet *ui;

private:

private slots:
    void groupSelected(int row,int col);
    void on_pushButton_cancel_clicked();
    void on_pushButton_sure_clicked();
};

#endif // QTRENDBGSET_H
