#ifndef MODELSEL_H
#define MODELSEL_H

#include <QDialog>

namespace Ui {
    class ModelSel;
}

class ModelSel : public QDialog
{
    Q_OBJECT

public:
    explicit ModelSel(QWidget *parent = 0);
    ~ModelSel();

    void reBondingTrackers(QGraphicsItem *pselItem,QGraphicsScene *pScene);

private:
    Ui::ModelSel *ui;
    void DrawScreenSize();

private slots:
     void on_HMImodel_2_currentIndexChanged(QString );
     void on_pushButton_help_clicked();
     void on_pushButton_quit_clicked();
     void on_showmodel_currentIndexChanged(int index);
     void on_HMImodel_currentIndexChanged(QString index);

private:
     //void initHIMSetting();
};

#endif // MODELSEL_H

