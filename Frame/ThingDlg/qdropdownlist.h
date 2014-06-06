#ifndef QDROPDOWNLIST_H
#define QDROPDOWNLIST_H

#include <QWidget>
#include "view/qdropdownattr.h"

namespace Ui {
    class qDropDownList;
}

class qDropDownList:public QWidget
{
    Q_OBJECT

public:
    short               m_nShowNumber;  //下拉显示数量
    int                 screenNum;
    //QList<SwitchItem> m_listSwitchItem;//每个开关的实际属性
    bool                isUseScript;
    QString             macroName;
    QString             functionName;
    QVector<SwitchInfo> m_vecSwitchItem;//每个开关写入数据库的属性

public:
    explicit qDropDownList(QWidget *parent = 0);
    ~qDropDownList();

private:
    bool isInit;
    Ui::qDropDownList *ui;

public:
    void Init(QDropdownAttr *pItem);
    bool getPicCheck();

signals:
    void addFun(QString funcName,QString path);
    void deleteFun(QString funcName,QString path);
private slots:
    void on_check_pic_clicked(bool checked);
    void on_btn_new_clicked();
    void on_edit_value_editingFinished();
    void on_comboBox_curLan_currentIndexChanged(int index);
    void on_comboBox_script_currentIndexChanged(int index);
    void on_groupBox_4_clicked(bool checked);
    void on_edit_operatingAddr_2_editingFinished();
    void on_edit_operatingAddr_editingFinished();
    void on_checkBox_clicked(bool checked);
    void on_comboBox_ScreenIndex_currentIndexChanged(int index);
    void on_comboBox_operType_currentIndexChanged(int index);
    void on_spin_Value_valueChanged(int );
    void on_comboBox_operateType_2_currentIndexChanged(int index);
    void on_comboBox_dataType_currentIndexChanged(int index);
    void on_comboBox_operateType_currentIndexChanged(int index);
    void on_lineEdit_name_editingFinished();
    void on_listWidget_currentRowChanged(int currentRow);
    void on_btn_wordAddr_clicked();
    void on_btn_bitAddr_clicked();
    void on_pushButton_del_clicked();
    void on_pushButton_pic_clicked();
    void on_pushButton_word_clicked();
    void on_pushButton_bit_clicked();
    void on_spinBox_valueChanged(int );
    //add by wxy
    void on_edit_const_editingFinished();
    void on_check_const_clicked(bool bChecked);
    void on_btn_wordAddr_const_clicked();

    void on_sel_pic(int index,EITEM_TYPE bLib,QString path);
    signals:
    void picturechecked(bool checked);
};

#endif // QDROPDOWNLIST_H
