#ifndef QRECIPECHOICE_H
#define QRECIPECHOICE_H

#include <QDialog>
#include "qrecipechoicegendlg.h"
#include "qdialogbuttonbox.h"
//#include "qvisibilitydlg.h"
#include <QGraphicsItem>
class QRecipeChoice : public QDialog
{
    Q_OBJECT
public:
    explicit QRecipeChoice(QGraphicsItem *pItem,QWidget *parent = 0);
    ~QRecipeChoice();
    QVBoxLayout *mainLayout;
    QStringList * datalist;
    QRecipeChoiceGenDlg*pRecipeChoiceGen;
    //QAdvancedDlg  * Advancedlg;     //¸ß¼¶Ò³Ãæ
signals:

public slots:
    void confyButton();
    void loadHelp();
private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
    void InitAllProperty(QGraphicsItem *pItem);
public:
    QGraphicsItem *pCopyItem;

};

#endif // QRECIPECHOICE_H
