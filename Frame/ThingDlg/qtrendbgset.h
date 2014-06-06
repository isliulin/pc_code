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
    int m_nGroupNum;    //总组数
    int m_nGroupBegin;  //起始组号
    int m_nMaxNum;      //最大组数

private:
    Ui::QTrendbgSet *ui;

private:

private slots:
    void groupSelected(int row,int col);
    void on_pushButton_cancel_clicked();
    void on_pushButton_sure_clicked();
};

#endif // QTRENDBGSET_H
