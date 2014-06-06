#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>
#include "Frame/qprogectmanager.h"

namespace Ui {
    class Monitorwidget;
}

class Monitorwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Monitorwidget(QWidget *parent = 0);
    ~Monitorwidget();
    QVector <double > values;

    Keyboard monitorAddr;
    monitorPro mProperty;

	void setAddrType(int type);
    void changeAddr(QString string);
    void SetCheckDisabled(bool checked);//启用，禁用“与操作地址相同”选项

    bool Save();


    void setFuncType(int type);
    
    void setSlid(bool checked);

    void init(QItemGroup *pItem);

    void setItemIndex(int iIndex);

    void setCheckSameVisiable(bool bVisiable);
private:
    Ui::Monitorwidget *ui;
    int functionType;
    QItemGroup *item;
    bool bMonitor;
public slots:

signals:
    void signalSetCheckSame(int index);
    void StatusCountChanged(int count);
	void signalBitLamp();
	

private slots:
    void on_groupBox_clicked(bool checked);
    void on_btn_wordAddr_clicked();
    void on_btn_bitAddr_clicked();
    void on_comboBox_bitAddr_currentIndexChanged(int index);
    void on_check_sameWord_stateChanged(int );
    void on_check_sameBit_stateChanged(int );
    void on_spin_statusCount_valueChanged(int );
    void on_combo_condition_currentIndexChanged(int index);
    void on_btn_customValue_clicked();
    void on_group_word_clicked(bool checked);
    void on_group_bit_clicked(bool checked);
};

#endif // MONITORWIDGET_H
