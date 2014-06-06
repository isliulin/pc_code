#ifndef MARCOUSEDISPLAY_H
#define MARCOUSEDISPLAY_H

#include <QDialog>

typedef struct __MarcoString__{
    QString sScreenName;   //画面
    QString sItemName;     //控件名称
    QString sLibName;      //库名
    QString sFunName;      //函数名
}MarcoString;

namespace Ui {
    class MarcoUseDisplay;
}

class MarcoUseDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit MarcoUseDisplay(QWidget *parent = 0);
    ~MarcoUseDisplay();

private:
    Ui::MarcoUseDisplay *ui;

private:
    QVector<MarcoString> mVecStr;
    int nSelctType;  //选择类型
    void InitTable();

private slots:
    void on_m_table_cellDoubleClicked(int row, int column);
    void on_m_sheetcmb_currentIndexChanged(QString );
    void on_m_radio2_clicked();
    void on_m_radio1_clicked();
};

#endif // MARCOUSEDISPLAY_H
