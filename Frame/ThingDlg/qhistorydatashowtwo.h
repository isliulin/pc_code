#ifndef QHISTORYDATASHOWTWO_H
#define QHISTORYDATASHOWTWO_H

#include <QWidget>
#include "view/qhistorydatashowattr.h"

namespace Ui {
    class QHistoryDataShowTwo;
}

class QHistoryDataShowTwo : public QWidget
{
    Q_OBJECT

public:
    explicit QHistoryDataShowTwo(QWidget *parent = 0);
    ~QHistoryDataShowTwo();

private:
    Ui::QHistoryDataShowTwo *ui;

public:
    QLineEdit* pEdit;
    QString m_str;

public:
    void Init(QHistoryDataShowAttr* pItem);

public:
    int curSamp;//当前在m_loadDataSampling中的第几个数据采集是被选中的数据采集

public:
    int m_nCurLanNum;   //当前语言号
    int m_nCurRow;      //当前链接的第几行
    bool bInit;         //初始化标注

public:
    void sortHisData();

public:
    QString                  sGroupName;//组名
    QVector<HistoryDataInfo> m_vecHisData;

private slots:
    void on_checkBox_all_clicked(bool checked);
    void on_tableWidget_cellClicked(int row, int column);
    void on_comboBox_currentIndexChanged(int index);
    void on_comboBox_2_currentIndexChanged(int index);
    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

public slots:
    void shit();
    void slotLan(int lan);

signals:
    void redrawSence();
    void sigLanguageCh(int);
    void groupCh();
};

#endif // QHISTORYDATASHOWTWO_H
