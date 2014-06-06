#ifndef QDATEDISPLAYGENERALDLG_H
#define QDATEDISPLAYGENERALDLG_H

#include <QWidget>
#include <QGraphicsScene>
#include "qpickercolor.h"//ѡ����ɫ����
//#include "view/qrectitem.h"
#include "view/qsimpletextitem.h"//�ı���
#include <QGraphicsItemGroup>//�����
#include "view/qgroupitem.h"//�������Ĳ���


namespace Ui {
    class QDateDisplayGeneralDlg;
}

class QDateDisplayGeneralDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QDateDisplayGeneralDlg(QWidget *parent = 0);
    ~QDateDisplayGeneralDlg();
public://����
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
    void setFrameColor(const QColor & mColor);       //���ñ߿�ɫ
    void setFGColor(const QColor & mColor);       //ǰ��ɫ
    void setBGColor(const QColor & mColor);       //����ɫ
    void setTextColor(const QColor & mColor);       //�ı�ɫ
};

#endif // QDATEDISPLAYGENERALDLG_H
