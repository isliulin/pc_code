#ifndef QHISTRENDDISPLAYPENDLG_H
#define QHISTRENDDISPLAYPENDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include "ui_qhistrenddisplaypendlg.h"
#include "qgraphicsitem.h"

namespace Ui {
    class QHisTrendDisplayPenDlg;
}

class QHisTrendDisplayPenDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QHisTrendDisplayPenDlg(QWidget *parent = 0);
    ~QHisTrendDisplayPenDlg();
    Ui::QHisTrendDisplayPenDlg *ui;
    void InitDataSource();//��ʼ��������Դ
    void InitPXData(QComboBox *PComBox);//����InitDataSource������ʼ��������Դ
    int  TrendCheckMinMax(int DataType);
    void Init(QGraphicsItem *pItem);
    void InitPenType( QComboBox * pComboBox) ;      //�ʵ�������ʽ
    QIntValidator *intValidator;
    void InitValidator();

public:
    void SetPenHide(int nIndex);
    void SavePenPage(QStringList *datalist, int index);

private slots:
    void on_P8_Color_clicked();
    void on_P7_Color_clicked();
    void on_P6_Color_clicked();
    void on_P5_Color_clicked();
    void on_P4_Color_clicked();
    void on_P3_Color_clicked();
    void on_P2_Color_clicked();
    void on_P1_Color_clicked();
    void setColorP1(const QColor & mColor);       //�ı�ɫ
    void setColorP2(const QColor & mColor);       //�ı�ɫ
    void setColorP3(const QColor & mColor);       //�ı�ɫ
    void setColorP4(const QColor & mColor);       //�ı�ɫ
    void setColorP5(const QColor & mColor);       //�ı�ɫ
    void setColorP6(const QColor & mColor);       //�ı�ɫ
    void setColorP7(const QColor & mColor);       //�ı�ɫ
    void setColorP8(const QColor & mColor);       //�ı�ɫ
};

#endif // QHISTRENDDISPLAYPENDLG_H
