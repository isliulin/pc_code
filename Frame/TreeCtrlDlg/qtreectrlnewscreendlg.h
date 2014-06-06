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
    bool is_property;//��ʼ����ע
    //void deleteScreen_upDateIndex();
    void insertDataToTable(int iIndex);
    void alterDataToTable(int iIndex);

public:
    bool isNew;
    QList<SCRIPT_PROP> LocalListScript;//���нű�

private slots:
    void on_checkBox_right_clicked(bool checked);
    void on_checkBox_left_clicked(bool checked);
    void on_tableWidget_cellDoubleClicked(int row, int column);//˫���ű����һ����Ԫ
    void on_pushButton_help_clicked();                  //�ű������
    void on_pushButton_ch_clicked();                    //�ű����޸�
    void on_pushButton_del_clicked();                   //�ű���ɾ��
    void on_pushButton_new_clicked();                   //�ű�������
    void on_pushButton_cancel_clicked();                //ȷ��
    void on_pushButton_sure_clicked();                  //ȡ��
    void on_newscreen_silence_radiobutton_clicked();    //Ĭ��
    void on_newscreen_picture_radiobutton_clicked();    //λͼ
    void on_newscreen_picture_pushButton_clicked();     //ͼƬѡ��ť
    void on_newscreen_pushButton_bk_clicked();          //����ɫ��ť���
    void on_newscreen_pushButton_frontcolor_clicked();  //ǰ��ɫ��ť���

public slots:
    void InitScreenDlg();                       //�½�����ʱ���õ�
    void InitScreenPropertyDlg();               //�򿪻���ʱ�õ�
    void newscreen_Assign();                    //�½�����󱣴滭�������
    void screenProperty_assign();               //�򿪻������Ժ�����Ա���
    void copyScreen();                          //���ƻ���
    void deleteScreen();                        //ɾ������
    void setCurrentBKColor(const QColor &);     //����ɫ�źŲ�
    void setCurrentFrontColor(const QColor &);  //ǰ��ɫ�źŲ�
};

#endif // QTREECTRLNEWSCREENDLG_H
