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
    QVector<QVector<QString> > Name; 		//����
    int datatype[32];		//��������
    int showtype[32];		//��ʾ����
    int TotalNum[32];		//��λ��
    int PointNum[32];		//С��λ��
    int ifZoom[32];			//�Ƿ�����
    int plus_fr[32];		//��������
    int plus_bk[32];		//����С��
    int offset_fr[32];		//ƫ��������
    int offset_bk[32];		//ƫ����С��
};
class QHisdDataLoggerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QHisdDataLoggerDialog(QWidget *parent = 0);
    ~QHisdDataLoggerDialog();
HISTORY_LOG_PROP qhistabledata;//�����������洢��������
void ReHisTable(int nTablelength);//ˢ����ʷ���ݱ��ĺ���
void ReMemoryCount(int index);//�����ڴ�����������
void ReDataDisplaytype(int index);//�����������ˢ�����ݵ���ʾ���

int tablerow;//�洢��ǰѡ�����
int tablecolumn;//�洢��ǰѡ�����
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
