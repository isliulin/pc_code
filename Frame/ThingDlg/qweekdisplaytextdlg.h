#ifndef QWEEKDISPLAYTEXTDLG_H
#define QWEEKDISPLAYTEXTDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include "ui_qweekdisplaytextdlg.h"
#include <QGraphicsItem>
namespace Ui {
    class QWeekDisplaytextDlg;
}

class QWeekDisplaytextDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QWeekDisplaytextDlg(QWidget *parent = 0);
    ~QWeekDisplaytextDlg();
signals:
    void SetTextProperty();
    void ClickCell();
public:
    struct text
    {
        int nFontSize[5];   //�����С
        QString sColor;     //������ɫ
        int nWordInterval;  //�־�
        int nPosition;      //�ı�λ��
        QString sText[5];   //�ı�
        int bIfFlick;      //�Ƿ���˸
        QString sFont[5];   //����
    }TextProperty[7];

    int nCurrentIndex;      //��ǰ״̬
    QPickerColor *pTextColor;
    bool InitFlag;

public:
    void InitParament();
    void OnClickCell();
    void DoubleClickInit(QGraphicsItem *pItem);
    void SaveWeekdayTextPage(QStringList *datalist,int index);
public://private:
    Ui::QWeekDisplaytextDlg *ui;

private slots:
    void on_checkBox_clicked(bool checked);
    void on_Text_Color_clicked();
    void on_m_fontcmb_currentIndexChanged(QString sFont);
    void on_m_check_clicked(bool checked);
    void on_m_flickcheck_currentIndexChanged(int index);
    void on_m_radio9_clicked();
    void on_m_radio8_clicked();
    void on_m_radio7_clicked();
    void on_m_radio6_clicked();
    void on_m_radio5_clicked();
    void on_m_radio4_clicked();
    void on_m_radio3_clicked();
    void on_m_radio2_clicked();
    void on_m_radio1_clicked();
    void on_m_table_clicked(QModelIndex index);
    void on_m_textedit_textChanged();
    void on_m_wordintervalspin_valueChanged(int );
    void setTextColor(const QColor & mColor);       //�ı�ɫ

//    void OnSetTextColor();
    void on_m_fontsizecmb_currentIndexChanged(int index);
    void on_m_languagecmb_currentIndexChanged(int index);
};

#endif // QWEEKDISPLAYTEXTDLG_H
