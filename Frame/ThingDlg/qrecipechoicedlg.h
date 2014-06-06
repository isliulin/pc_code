#ifndef QRECIPECHOICEDLG_H
#define QRECIPECHOICEDLG_H

#include <QDialog>
#include <QGraphicsItem>
#include "view/QRecipeItem.h"
#include "Frame/ThingDlg/switch/securitywidget.h"

namespace Ui {
    class QRecipeChoiceDlg;
}

class QRecipeChoiceDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QRecipeChoiceDlg(QGraphicsItem *pItem,QWidget *parent = 0);
    void Init(QRcipeItem *pItem);
    void drawRecipeSelect();
    void onSaveInfo();
    ~QRecipeChoiceDlg();
    QRcipeItem *pCopyItem;

private:
    Ui::QRecipeChoiceDlg *ui;
    SecurityWidget *pSecurityWight;
    RCIPEINFO m_Rcipe;
    int oId;

public slots:
    void confyButton();
    void loadHelp();
    void onSetTextColor(const QColor &mColor);
    void onSetBackColor(const QColor &mColor);
    //void libraryChanged(QString libName);

private slots:
    void on_btn_new_clicked();
    void on_m_ComboradioBtn_clicked(bool checked);
    void on_m_TableradioBtn_clicked(bool checked);
    void on_m_BackColorpushBtn_clicked();
    void on_m_TextColorpushBtn_clicked();
};

#endif // QRECIPECHOICEDLG_H
