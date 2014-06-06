#ifndef QNEWWINDOWDLG_H
#define QNEWWINDOWDLG_H
#include "ui_qnewwindowdlg.h"
#include <QDialog>
#include "qpickercolor.h"
#include "Frame\mainwindow.h"
namespace Ui {
    class QNewWindowDlg;
}

class QNewWindowDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QNewWindowDlg(QWidget *parent = 0);
    ~QNewWindowDlg();
    bool review_Window_Name(QString str);

public:
    Ui::QNewWindowDlg *ui;
    void insertDataToTable(int iIndex);
    void alterDataToTable(int iIndex);

public:
    bool isNew;
    QList<SCRIPT_PROP> LocalListScript;//所有脚本

private slots:
    void on_check_title_clicked(bool checked);
    void on_radioButton_center_clicked();
    void on_radioButton_pos_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);//双击脚本库的一个单元
    void on_helpbtn_clicked();//脚本库帮助
    void on_pushButton_ch_clicked();//脚本库修改
    void on_pushButton_del_clicked();//脚本库删除
    void on_pushButton_new_clicked();//脚本库增加
    void on_newscreen_silence_radiobutton_clicked();    //默认
    void on_newscreen_picture_radiobutton_clicked();    //位图
    void on_newscreen_picture_pushButton_clicked();     //图片选择按钮
    void on_pushButton_ok_clicked();//确定
    void on_pushButton_cancel_clicked();//取消
    void on_newscreen_pushButton_frontcolor_clicked();//前景色按钮点击
    void on_BK_Color_clicked();//背景色按钮点击

public slots:
    void InitWindowDlg();                       //新建画面时调用到
    void InitWindowPropertyDlg();               //打开画面时用到
    void newwindow_Assign();                    //新建画面后保存画面的属性
    void windowProperty_assign();               //打开画面属性后的属性保存
    void copyWindow();                          //复制画面
    void deleteWindow();                        //删除画面
    void setCurrentBKColor(const QColor &);     //背景色信号槽
    void setCurrentFrontColor(const QColor &);  //前景色信号槽

private:
    //void deleteScreen_upDateIndex();
    bool is_property;//初始化标注
};

#endif // QNEWWINDOWDLG_H
