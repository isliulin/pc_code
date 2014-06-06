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
    QList<SCRIPT_PROP> LocalListScript;//���нű�

private slots:
    void on_check_title_clicked(bool checked);
    void on_radioButton_center_clicked();
    void on_radioButton_pos_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);//˫���ű����һ����Ԫ
    void on_helpbtn_clicked();//�ű������
    void on_pushButton_ch_clicked();//�ű����޸�
    void on_pushButton_del_clicked();//�ű���ɾ��
    void on_pushButton_new_clicked();//�ű�������
    void on_newscreen_silence_radiobutton_clicked();    //Ĭ��
    void on_newscreen_picture_radiobutton_clicked();    //λͼ
    void on_newscreen_picture_pushButton_clicked();     //ͼƬѡ��ť
    void on_pushButton_ok_clicked();//ȷ��
    void on_pushButton_cancel_clicked();//ȡ��
    void on_newscreen_pushButton_frontcolor_clicked();//ǰ��ɫ��ť���
    void on_BK_Color_clicked();//����ɫ��ť���

public slots:
    void InitWindowDlg();                       //�½�����ʱ���õ�
    void InitWindowPropertyDlg();               //�򿪻���ʱ�õ�
    void newwindow_Assign();                    //�½�����󱣴滭�������
    void windowProperty_assign();               //�򿪻������Ժ�����Ա���
    void copyWindow();                          //���ƻ���
    void deleteWindow();                        //ɾ������
    void setCurrentBKColor(const QColor &);     //����ɫ�źŲ�
    void setCurrentFrontColor(const QColor &);  //ǰ��ɫ�źŲ�

private:
    //void deleteScreen_upDateIndex();
    bool is_property;//��ʼ����ע
};

#endif // QNEWWINDOWDLG_H
