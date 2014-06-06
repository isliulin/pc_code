#ifndef QTREECTRLNEWSCREENDLG_H
#define QTREECTRLNEWSCREENDLG_H
#include "ui_qtreectrlnewscreendlg.h"
#include <QDialog>
#include "qpickercolor.h"
#include "Frame\mainwindow.h"

namespace Ui
{
    class QTreeCtrlNewScreenDlg;
}

class QTreeCtrlNewScreenDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QTreeCtrlNewScreenDlg(QWidget *parent = 0);
    ~QTreeCtrlNewScreenDlg();

public:
    Ui::QTreeCtrlNewScreenDlg *ui;
    bool review_Screen_Name(QString str);

private:
    bool is_property;//初始化标注
    //void deleteScreen_upDateIndex();
    void insertDataToTable(int iIndex);
    void alterDataToTable(int iIndex);

public:
    bool isNew;
    QList<SCRIPT_PROP> LocalListScript;//所有脚本

private slots:
    void on_checkBox_right_clicked(bool checked);
    void on_checkBox_left_clicked(bool checked);
    void on_tableWidget_cellDoubleClicked(int row, int column);//双击脚本库的一个单元
    void on_pushButton_help_clicked();                  //脚本库帮助
    void on_pushButton_ch_clicked();                    //脚本库修改
    void on_pushButton_del_clicked();                   //脚本库删除
    void on_pushButton_new_clicked();                   //脚本库增加
    void on_pushButton_cancel_clicked();                //确定
    void on_pushButton_sure_clicked();                  //取消
    void on_newscreen_silence_radiobutton_clicked();    //默认
    void on_newscreen_picture_radiobutton_clicked();    //位图
    void on_newscreen_picture_pushButton_clicked();     //图片选择按钮
    void on_newscreen_pushButton_bk_clicked();          //背景色按钮点击
    void on_newscreen_pushButton_frontcolor_clicked();  //前景色按钮点击

public slots:
    void InitScreenDlg();                       //新建画面时调用到
    void InitScreenPropertyDlg();               //打开画面时用到
    void newscreen_Assign();                    //新建画面后保存画面的属性
    void screenProperty_assign();               //打开画面属性后的属性保存
    void copyScreen();                          //复制画面
    void deleteScreen();                        //删除画面
    void setCurrentBKColor(const QColor &);     //背景色信号槽
    void setCurrentFrontColor(const QColor &);  //前景色信号槽
};

#endif // QTREECTRLNEWSCREENDLG_H
