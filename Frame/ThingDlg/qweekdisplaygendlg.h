#ifndef QWEEKDISPLAYGENDLG_H
#define QWEEKDISPLAYGENDLG_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "view/qgroupitem.h"
#include "qpickercolor.h"
#include "ui_qweekdisplaygendlg.h"
namespace Ui {
    class QWeekDisplayGenDlg;
}

class QWeekDisplayGenDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QWeekDisplayGenDlg(QWidget *parent = 0);
    ~QWeekDisplayGenDlg();

public://private:
    Ui::QWeekDisplayGenDlg *ui;
signals:
    void GeneralStateChange();   //״̬�ı䷢�����ź�
    void txtChange();
private slots:
    void on_BG_Color_clicked();
    void on_FG_Color_clicked();
    void on_Frame_Color_clicked();
    void on_LoadShape_clicked();
    void on_m_patterncmb_currentIndexChanged(int index);
    void on_m_statespin_valueChanged(int );
    void setFrameColor(const QColor & mColor);       //���ñ߿�ɫ
    void setFGColor(const QColor & mColor);       //ǰ��ɫ
    void setBGColor(const QColor & mColor);       //����ɫ


//    void OnSetBorderColor();
//    void OnSetFrontColor();
//    void OnSetBackColor();

public:
    QGraphicsScene *pScene; //����
    QGraphicsItem *pOldItem;
    QGroupItem *pBaseItem;

//    QPickerColor *pBorderColor;
//    QPickerColor *pFrontColor;
//    QPickerColor *pBackColor ;
    bool InitFlag;

    struct Week
    {
        QString sBorderColor;      //�߿�ɫ
        QString sFrontColor;       //ǰ��ɫ
        QString sBackColor;        //����ɫ
        int nPattern;              //��ʽ
    }WeekDay[7];

public:
    void InitParament();
    void SaveWeekGeneralPage(QStringList *datalist, int index);
    void DoubleClickInit(QGraphicsItem *pItem);
};

#endif // QWEEKDISPLAYGENDLG_H
