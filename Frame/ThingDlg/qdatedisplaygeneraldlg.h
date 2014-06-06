#ifndef QDATEDISPLAYGENERALDLG_H
#define QDATEDISPLAYGENERALDLG_H

#include <QWidget>
#include <QGraphicsScene>
#include "qpickercolor.h"//选择颜色的类
//#include "view/qrectitem.h"
#include "view/qsimpletextitem.h"//文本类
#include <QGraphicsItemGroup>//组合类
#include "view/qgroupitem.h"//对组合类的操作


namespace Ui {
    class QDateDisplayGeneralDlg;
}

class QDateDisplayGeneralDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QDateDisplayGeneralDlg(QWidget *parent = 0);
    ~QDateDisplayGeneralDlg();
public://日期
    QString sDate;
    QString sMonth;
    QString sYear;
    void TimeDisplayGenSave(QStringList *datalist, int index);
    void Init(QGraphicsItem *pItem);
    QDate date;
    QGraphicsItem * pCopyItem;
    QButtonGroup *RadioButton_direction_Group;

private:
    Ui::QDateDisplayGeneralDlg *ui;
private:
    QGraphicsScene *pScene;
    QGroupItem *pBaseItem;
    bool nInitFlag;

private slots:
    void on_Font_currentIndexChanged(QString );
    void on_Text_Color_clicked();
    void on_BG_Color_clicked();
    void on_FG_Color_clicked();
    void on_Frame_Color_clicked();
    void on_LoadShape_clicked();
    void on_FontSize_currentIndexChanged(QString );
    void on_Alignment_Right_clicked(bool checked);
    void on_Alignment_Center_clicked(bool checked);
    void on_Alignment_Left_clicked(bool checked);
    void on_Pattern_currentIndexChanged(int index);
    void on_Separative_Sign_currentIndexChanged(QString );
    void on_Format_currentIndexChanged(int index);
    void setFrameColor(const QColor & mColor);       //设置边框色
    void setFGColor(const QColor & mColor);       //前景色
    void setBGColor(const QColor & mColor);       //背景色
    void setTextColor(const QColor & mColor);       //文本色
};

#endif // QDATEDISPLAYGENERALDLG_H
