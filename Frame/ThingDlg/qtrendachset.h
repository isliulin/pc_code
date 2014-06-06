#ifndef QTRENDACHSET_H
#define QTRENDACHSET_H

#include <QDialog>
#include <qcombobox.h>
#include <qtablewidget.h>
#include "Frame/ThingDlg/qtrendappearance.h"

namespace Ui {
    class QTrendaChSet;
}

class QTrendaChSet:public QDialog
{
    Q_OBJECT

public:
    explicit QTrendaChSet(QList<int >channels, int curGroup = 0, QWidget *parent = 0);
    ~QTrendaChSet();

private:
    Ui::QTrendaChSet *ui;

public:
    int m_nChNum;   //总通道数
    int m_nChBegin; //起始通道号

    int m_nMaxNum;  //最大通道数
    int m_nCurGroup;//当前所在组
	QList<int> m_Channels;

private:
	QMap<int,DATA_ADDRESS_ITEM >mapChls;
    //QComboBox*          m_pComboBox;
    //QTableWidgetItem*   m_pCellItem;
    //QComboBox           m_comboBox;
    //QTableWidgetItem    m_cellItem;
    //bool                m_bFirst;

private:
    void refrushTable(int);

private slots:
	void chlSelected(int row,int col);
    void on_spinBox_beginCh_valueChanged(int value);
    void on_spinBox_chNum_valueChanged(int value);
    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void on_pushButton_cancel_clicked();
    void on_pushButton_sure_clicked();
};

#endif //QTRENDACHSET_H
