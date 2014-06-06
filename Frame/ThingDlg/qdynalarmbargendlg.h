#ifndef QDYNALARMBARGENDLG_H
#define QDYNALARMBARGENDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include "Frame/qprogectmanager.h"
#include <QGraphicsScene>
#include "view/qsimpletextitem.h"//文本类
#include <QGraphicsItemGroup>//组合类
#include "view/qgroupitem.h"//对组合类的操作
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
    ///颜色
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
    void setFrameColor(const QColor & mColor);       //设置边框色
    void setFGColor(const QColor & mColor);       //前景色
    void setBGColor(const QColor & mColor);       //背景色
    void setTextColor(const QColor & mColor);       //文本色
};

#endif // QDYNALARMBARGENDLG_H
