#ifndef QRECIPETABLE_H
#define QRECIPETABLE_H
#include "qrepicegenaral.h"
#include "view/QRecipetableItem.h"
#include "Frame/ThingDlg/switch/securitywidget.h"
#include <QDialog>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QGraphicsItem>
#include <QStandardItemModel>
class Qrecipetable : public QDialog
{
    Q_OBJECT
public:
    explicit Qrecipetable(QGraphicsItem *pItem,QWidget *parent = 0);
    ~Qrecipetable();
    void drawRecipeDisplay();
    QTabWidget *tabWidget;
    Qrepicegenaral  * ptab1;  //一般页面
    SecurityWidget *pSecurityWight;//显现页面
    QVBoxLayout *mainLayout;
    QDialogButtonBox *buttonBox;

     void InitAllProperty(QRecipeTableItem *pItem);
private:
     RECIPESHOW m_SaveInfo;
     QVector<qreal> vVLine;              //用来存垂直线的数据
     QVector<qreal> vHLine;             //用来存水平线的数据

private slots:
    void confyButton();
    void loadHelp();
public:
    QRecipeTableItem *pCopyItem;

};

#endif // QRECIPETABLE_H
