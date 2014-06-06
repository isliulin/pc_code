#ifndef QRECIPECHOICEGENDLG_H
#define QRECIPECHOICEGENDLG_H

#include <QDialog>
#include "qpickercolor.h"//ѡ����ɫ����
#include "QGraphicsItem"
namespace Ui {
    class QRecipeChoiceGenDlg;
}

class QRecipeChoiceGenDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QRecipeChoiceGenDlg(QWidget *parent = 0);
    ~QRecipeChoiceGenDlg();
    QButtonGroup *R_Lyaout_Group;
    void Init(QGraphicsItem *pItem);
    QGraphicsItem * pCopyItem;
    void GeneralSave(QStringList *datalist, int index);

private:
    Ui::QRecipeChoiceGenDlg *ui;

private slots:
    void on_Ifuse_Macro_clicked(bool checked);
    void on_BG_Color_clicked();
    void on_Text_Color_clicked();
    void setBGColor(const QColor & mColor);       //����ɫ
    void setTextColor(const QColor & mColor);       //�ı�ɫ
    void typeSelect(int nCheckId);

};

#endif // QRECIPECHOICEGENDLG_H
