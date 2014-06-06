#ifndef MARCOUSEDISPLAY_H
#define MARCOUSEDISPLAY_H

#include <QDialog>

typedef struct __MarcoString__{
    QString sScreenName;   //����
    QString sItemName;     //�ؼ�����
    QString sLibName;      //����
    QString sFunName;      //������
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
    int nSelctType;  //ѡ������
    void InitTable();

private slots:
    void on_m_table_cellDoubleClicked(int row, int column);
    void on_m_sheetcmb_currentIndexChanged(QString );
    void on_m_radio2_clicked();
    void on_m_radio1_clicked();
};

#endif // MARCOUSEDISPLAY_H
