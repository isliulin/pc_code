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
    int curSamp;//��ǰ��m_loadDataSampling�еĵڼ������ݲɼ��Ǳ�ѡ�е����ݲɼ�

public:
    int m_nCurLanNum;   //��ǰ���Ժ�
    int m_nCurRow;      //��ǰ���ӵĵڼ���
    bool bInit;         //��ʼ����ע

public:
    void sortHisData();

public:
    QString                  sGroupName;//����
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
