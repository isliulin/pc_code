#ifndef QDATALOGGERDLG_H
#define QDATALOGGERDLG_H
#include "Frame\addressinputdialog.h"
#include <QDialog>
#include <qtablewidget.h>
#include <QHBoxLayout>
#include <QStandardItemModel.h>

namespace Ui
{
    class qdataloggerdlg;
}

class QMyWidget : public QWidget
{
    Q_OBJECT

//private:
public:
    QLineEdit   *pEdit;
    QPushButton *pBtn;
    static Keyboard    curAddr;
    bool        bUpdate; //是否要刷新老的表项

public:
    QMyWidget(int width = 100, int height = 30, QWidget* parent = 0);
    ~QMyWidget();

private slots:
    void getBtnAddress();
    void getEditAddress();
};

class qdataloggerdlg : public QDialog
{
    Q_OBJECT

public:
    explicit qdataloggerdlg(int index,QWidget *parent = 0);
    ~qdataloggerdlg();

private:
    Ui::qdataloggerdlg *ui;
    bool              bInitFinish;        //初始化完成标志
    bool              bFlush;             //当前传值是否正常，小插曲
    QMyWidget*        m_pMyWidgetCur;
    //QMyWidget*        m_pMyWidgetOld;
    QStandardItemModel model;
	int m_curSamp;
    DATA_SAMPLING     m_dataSampling;     //数据采样表格数据的全局条件限制

    void temp_storage_addr();           //重新计算地址并存储在m_dataSampling
    void show_table_continous_addr();   //连续地址的刷新
    void show_table_srand_addr();       //随机地址的刷新
	

private:
    void RedrawAllScene();//扫描所有场景，

private slots:
    void on_check_Print_clicked(bool checked);
    void on_check_autosave_clicked(bool checked);
    void on_btn_deleteall_clicked();
    void on_comboBox_ctlCountUnit_currentIndexChanged(int index);
    void on_comboBox_cycCountUnit_currentIndexChanged(int index);
    void on_comboBox_cycFreqUnit_currentIndexChanged(int index);
    void on_comboBox_timeFreqUint_currentIndexChanged(int index);
    void on_radioButton_2_clicked();
    void on_radioButton_clicked();
    void on_comboBox_maxNum_currentIndexChanged(int index);
    void on_pushButton_ctlWordAddr_clicked();
    void on_lineEdit_ctlWordAddr_editingFinished();
    void on_doubleSpinBox_desMax_valueChanged(double );
    void on_doubleSpinBox_desMin_valueChanged(double );
    void on_doubleSpinBox_srcMax_valueChanged(double );
    void on_doubleSpinBox_srcMin_valueChanged(double );
    void on_checkBox_rounding_clicked(bool checked);
    void on_comboBox_dateFormat_currentIndexChanged(int index);
    void on_comboBox_dataFormat_currentIndexChanged(int index);
    void on_spinBox_decimalDigit_valueChanged(int );
    void on_spinBox_totalDigit_valueChanged(int );
    void on_checkBox_suppression_clicked(bool checked);
    void on_checkBox_zoom_clicked(bool checked);
    void on_radioButton_SDcard_clicked();
    void on_radioButton_CFcard_clicked();
    void on_radioButton_Udisk_clicked();
    void on_checkBox_saveFile_clicked(bool checked);
    void on_pushButton_notify_clicked();
    void on_lineEdit_notify_editingFinished();
    void on_spinBox_maxNum_valueChanged(int );
    void on_radioButton_replace_clicked(bool checked);
    void on_radioButton_begin_clicked(bool checked);
    void on_radioButton_stop_clicked(bool checked);
    void on_checkBox_ctlReset_clicked(bool checked);
    void on_pushButton_ctlAddr_clicked();
    void on_lineEdit_ctlAddr_editingFinished();
    void on_spinBox_ctlCount_valueChanged(int );
    void on_checkBox_cycReset_clicked(bool checked);
    void on_spinBox_cycCount_valueChanged(int );
    void on_pushButton_cycAddr_clicked();
    void on_lineEdit_cycAddr_editingFinished();
    //void on_radioButton_milsecond_clicked();
    //void on_radioButton_second_clicked();
    void on_spinBox_cycFreq_valueChanged(int );
    void on_lineEdit_timeAddr_editingFinished();
    void on_pushButton_timeAddr_clicked();
    void on_spinBox_timeFreq_valueChanged(int );
    void on_spinBox_endMinute_valueChanged(int );
    void on_spinBox_endHour_valueChanged(int );
    void on_spinBox_beginMinute_valueChanged(int );
    void on_spinBox_beginHour_valueChanged(int );
    void on_TableDClick(int row,int colum);
    void on_pushButton_addrBegin_clicked();
    //void on_lineEdit_addrBegin_editingFinished();
    void on_spinBox_allWords_valueChanged(int num);
    void on_radioButton_32bit_clicked(bool checked);
    void on_radioButton_16bit_clicked(bool checked);
    void on_radioButton_addrRand_clicked(bool checked);
    void on_radioButton_addrConti_clicked(bool checked);
    void on_checkBox_notify_clicked(bool checked);
    void on_checkBox_cycAddrCtl_clicked(bool checked);
    void on_checkBox_timeAddrCtl_clicked(bool checked);
    void on_radioButton_styControl_clicked(bool checked);
    void on_radioButton_styCycle_clicked(bool checked);
    void on_radioButton_styTime_clicked(bool checked);
    void on_accept_clicked();
    void on_help_clicked();
    void on_cancel_clicked();
	void on_add();
	void on_delete();

	void on_btn_startAddr();
	
	void on_btn_endAddr();
	
	void on_btn_rateAddr();
	
	void on_btn_rateAddr_2();

	void setDynTimeUi(bool checked);
	void setDynRateUi(bool checked);
	void setDynRateUi_cycle(bool checked);
};

#endif //QDATALOGGERDLG_H
