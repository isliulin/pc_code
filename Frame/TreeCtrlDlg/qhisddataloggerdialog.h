#ifndef QHISDDATALOGGERDIALOG_H
#define QHISDDATALOGGERDIALOG_H
#include "Frame\addressinputdialog.h"
#include <QDialog>

namespace Ui {
    class QHisdDataLoggerDialog;
}
class QHisTableData
{
public:
    QVector<QVector<QString> > Name; 		//名称
    int datatype[32];		//数据类型
    int showtype[32];		//显示类型
    int TotalNum[32];		//总位数
    int PointNum[32];		//小数位数
    int ifZoom[32];			//是否缩放
    int plus_fr[32];		//增益整数
    int plus_bk[32];		//增益小数
    int offset_fr[32];		//偏移量整数
    int offset_bk[32];		//偏移量小数
};
class QHisdDataLoggerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QHisdDataLoggerDialog(QWidget *parent = 0);
    ~QHisdDataLoggerDialog();
HISTORY_LOG_PROP qhistabledata;//辅助变量，存储表格的数据
void ReHisTable(int nTablelength);//刷新历史数据表格的函数
void ReMemoryCount(int index);//计算内存所需数函数
void ReDataDisplaytype(int index);//根据数据类别刷新数据的显示类别

int tablerow;//存储当前选择的行
int tablecolumn;//存储当前选择的列
private:
    Ui::QHisdDataLoggerDialog *ui;
    bool bInitFinish;
private slots:
    void on_tabWidget_currentChanged(int index);
    void on_help_clicked();
    void on_Language_currentIndexChanged(int index);
    void on_cancel_clicked();
    void on_accept_clicked();
    void on_notiy_address_check_clicked();
    void on_triggeredbitchoice_clicked();
    void on_pushButton_readaddress_clicked();
    void on_offset_textEdited(QString );
    void on_gain_textEdited(QString );
    void on_data_item_fractionaldigits_valueChanged(int );
    void on_data_item_totaldigits_valueChanged(int );
    void on_data_item_displaytype_currentIndexChanged(int index);
    void on_data_item_datatype_currentIndexChanged(int index);
    void on_data_item_name_textChanged(QString );
    void on_hisdatatable_cellClicked(int row, int column);
    void on_number_sampling_valueChanged(int );
    void on_sample_length_valueChanged(int );
//    void on_buttonBox_accepted();
    void on_scaling_clicked(bool checked);
    void on_notiy_clicked(bool checked);
    void on_clocked_clicked(bool checked);
    void on_triggered_clicked(bool checked);
    void on_timed_clicked(bool checked);
private:
    void reDrawHisDataDisplay();
};

#endif // QHISDDATALOGGERDIALOG_H
