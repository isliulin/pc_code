#ifndef QDYNALARMBARGENDLG_H
#define QDYNALARMBARGENDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include "Frame/qprogectmanager.h"
#include <QGraphicsScene>
#include "view/qsimpletextitem.h"//�ı���
#include <QGraphicsItemGroup>//�����
#include "view/qgroupitem.h"//�������Ĳ���
#include "view/alarmbar.h"

namespace Ui {
    class QDynAlarmBarGenDlg;
}

class QDynAlarmBarGenDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QDynAlarmBarGenDlg(QWidget *parent = 0);
    ~QDynAlarmBarGenDlg();
    void Init(QGraphicsItem *pItem);
    void DynAlarmBarGenSave(securityPro sproperty);
    QGraphicsItem * pCopyItem;
    void setid(int id);

private:
    Ui::QDynAlarmBarGenDlg *ui;
    QButtonGroup *RadioButton_direction_Group;
    QButtonGroup *RadioButton_AlarmSort_Group;
    ///��ɫ
//    QPickerColor *pFramColor;
//    QPickerColor *pFrontColor;
//    QPickerColor *pBackColor ;
//    QPickerColor *pTextColor;
    QGraphicsScene *pScene;
    QGroupItem *pBaseItem;
    bool nInitFlag;
    stAlarmBarPro alarmPro;
    bool bAll;
    QStringList groupNames;

private slots:
    void on_btn_groupset_clicked();
    void on_Shape_clicked();
    void on_Text_Color_clicked();
    void on_BG_Color_clicked();
    void on_FG_Color_clicked();
    void on_Frame_Color_clicked();
    void on_FontSize_currentIndexChanged(QString );
    void on_Pattern_currentIndexChanged(int index);
    void setFrameColor(const QColor & mColor);       //���ñ߿�ɫ
    void setFGColor(const QColor & mColor);       //ǰ��ɫ
    void setBGColor(const QColor & mColor);       //����ɫ
    void setTextColor(const QColor & mColor);       //�ı�ɫ
};

#endif // QDYNALARMBARGENDLG_H
