#ifndef SWITCHDLG_H
#define SWITCHDLG_H

#include <QDialog>
#include "bitwidget.h"
#include "wordwidget.h"
#include "screenwidget.h"
#include "exteriorwidget.h"
#include "securitywidget.h"
#include "monitorwidget.h"
#include "functionwdiget.h"

#include <QGraphicsItem>

namespace Ui {
    class SwitchDlg;
}

class SwitchDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SwitchDlg(QGraphicsItem *pItem,QWidget *parent = 0);
    ~SwitchDlg();
    void init();//��ʼ����������
    void setBtnGroup();//��4��radiobutton �ӵ�group
    void accept();

    void InitUi();
private:
    Ui::SwitchDlg *ui;
    int oId;

    QGraphicsScene scene;

private slots:

    //void on_radio_function_clicked();
    //void on_radio_scene_clicked();
    //void on_radio_bit_clicked();
    //void on_radio_word_clicked();

        void on_check_macro_up_clicked(bool checked);
        void on_check_macro_down_clicked(bool checked);
        void on_btn_new_up_clicked();
        void on_check_slid_clicked(bool checked);
        void on_add_macro();
        void on_buttonBox_helpRequested();
    void functionChanged(int type);
    void changeAddr(QString string);
    void setMonitorAddr(int );
public:    
    QGraphicsItem *item;

    QString sSwitchAddr;//������ַ

    QWidget * cWidget;//��ǰ��ʾ������ҳ
    BitWidget *bitwidget;//λ���ص�ʱ����ʾ������ҳ
    WordWidget *wordwidget;//�ֿ��ص�ʱ����ʾ������ҳ
    ScreenWidget *screenwidget;//���濪�ص�ʱ����ʾ������ҳ
    FunctionWdiget *funwidget;//���ܿ��ص�ʱ����ʾ������ҳ

    ExteriorWidget *exteriorwidget; //���ҳ��
    SecurityWidget *securitywidget; //Ȩ��ҳ��
    Monitorwidget  *monitorwidget; //����ҳ��
};

#endif // SWITCHDLG_H
