#ifndef QTIMEDISPLAYGENERALDLG_H
#define QTIMEDISPLAYGENERALDLG_H

#include <QWidget>
#include <QGraphicsScene>

#include "view/qrectitem.h"
#include "view/qsimpletextitem.h"
#include <QGraphicsItemGroup>
#include "view/qgroupitem.h"
#include "qpickercolor.h"

namespace Ui {
    class QTimeDisplayGeneralDLg;
}

class QTimeDisplayGeneralDLg : public QWidget
{
    Q_OBJECT

public:
    explicit QTimeDisplayGeneralDLg(QWidget *parent = 0);
    ~QTimeDisplayGeneralDLg();
    void TimeDisplayGenSave(QStringList *datalist, int index);
    void Init(QGraphicsItem *pItem);
    QGraphicsItem * pCopyItem;
    QButtonGroup *RadioButton_direction_Group;

private:
    Ui::QTimeDisplayGeneralDLg *ui;
private:
    QGraphicsScene *pScene;
    QString sHour;
    QString sMinute;
    QString sTime;
    QString sSecond;
    QTime time;      //��õ�ǰʱ��

    QRectItem *pFramRect;
    QRectItem *pBackRect;
    QSimpleTextItem *pText;
private:
   QGroupItem *pBaseItem;
   int nAlignment;
   bool nInitFlag;

   QPickerColor *pFrontColor;
   QPickerColor *pFramColor;
   QPickerColor *pBackColor ;
   QPickerColor *pTextColor;

private slots:

    void on_m_fontcmb_currentIndexChanged(QString );
    void on_Text_Color_clicked();
    void on_BG_Color_clicked();
    void on_FG_Color_clicked();
    void on_Frame_Color_clicked();
    void on_LoadShape_clicked();
    void on_m_patterncmb_currentIndexChanged(int index);
    void on_m_formatcmb_currentIndexChanged(int index);
    void on_m_rightradio_clicked();
    void on_m_middleradio_clicked();
    void on_m_leftradio_clicked();
    void on_m_fontsizecmb_currentIndexChanged(int );

    void setFrameColor(const QColor & mColor);       //���ñ߿�ɫ
    void setFGColor(const QColor & mColor);       //ǰ��ɫ
    void setBGColor(const QColor & mColor);       //����ɫ
    void setTextColor(const QColor & mColor);       //�ı�ɫ
};

#endif // QTIMEDISPLAYGENERALDLG_H
