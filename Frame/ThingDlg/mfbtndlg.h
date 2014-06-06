#ifndef MFBTNDLG_H
#define MFBTNDLG_H

#include <QDialog>
#include "view/mfbtnitem.h"

class QGraphicsItem;
class ExteriorWidget;
class SecurityWidget;
class Monitorwidget;
class QGraphicsScene;
namespace Ui {
    class MFBtnDlg;
}

class MFBtnDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MFBtnDlg(QGraphicsItem *pItem,QWidget *parent = 0);
    ~MFBtnDlg();
    void Init(QGraphicsItem *pItem);

private:
    Ui::MFBtnDlg *ui;
    bool                isUseScript;
    QString             macroName;
    QString             functionName;
    QVector<SwitchInfo> m_vecSwitchItem;//每个开关写入数据库的属性
    ExteriorWidget *exteriorwidget; //外观页面
    SecurityWidget *securitywidget; //权限页面
    Monitorwidget  *monitorwidget;
    QGraphicsScene scene;
    int oId;

private slots:
    void on_btn_new_clicked();
    void on_checkBox_clicked(bool checked);
    void on_comboBox_ScreenIndex_currentIndexChanged(int index);
    void on_comboBox_operType_currentIndexChanged(int index);
    void on_edit_value_editingFinished();
    void on_comboBox_operateType_2_currentIndexChanged(int index);
    void on_comboBox_dataType_currentIndexChanged(int index);
    void on_edit_operatingAddr_2_editingFinished();
    void on_comboBox_executeType_currentIndexChanged(int index);
    void on_comboBox_operateType_currentIndexChanged(int index);
    void on_edit_operatingAddr_editingFinished();
    void on_listWidget_currentRowChanged(int currentRow);
    void on_buttonBox_helpRequested();
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
    void on_group_macro_clicked(bool checked);
    void on_btn_wordAddr_clicked();
    void on_btn_bitAddr_clicked();
    void on_pushButton_del_clicked();
    void on_pushButton_pic_clicked();
    void on_pushButton_word_clicked();
    void on_pushButton_bit_clicked();
    //void libraryChanged(QString libname);
    void on_edit_const_editingFinished();
    void on_check_const_clicked(bool bChecked);
    void on_btn_wordAddr_const_clicked();
public:
    MfBtnItem* item;
};

#endif // MFBTNDLG_H
