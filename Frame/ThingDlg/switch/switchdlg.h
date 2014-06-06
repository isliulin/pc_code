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
    void init();//初始化所有属性
    void setBtnGroup();//将4个radiobutton 加到group
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

    QString sSwitchAddr;//操作地址

    QWidget * cWidget;//当前显示的属性页
    BitWidget *bitwidget;//位开关的时候显示的属性页
    WordWidget *wordwidget;//字开关的时候显示的属性页
    ScreenWidget *screenwidget;//画面开关的时候显示的属性页
    FunctionWdiget *funwidget;//功能开关的时候显示的属性页

    ExteriorWidget *exteriorwidget; //外观页面
    SecurityWidget *securitywidget; //权限页面
    Monitorwidget  *monitorwidget; //监视页面
};

#endif // SWITCHDLG_H
