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
    Qrepicegenaral  * ptab1;  //һ��ҳ��
    SecurityWidget *pSecurityWight;//����ҳ��
    QVBoxLayout *mainLayout;
    QDialogButtonBox *buttonBox;

     void InitAllProperty(QRecipeTableItem *pItem);
private:
     RECIPESHOW m_SaveInfo;
     QVector<qreal> vVLine;              //�����洹ֱ�ߵ�����
     QVector<qreal> vHLine;             //������ˮƽ�ߵ�����

private slots:
    void confyButton();
    void loadHelp();
public:
    QRecipeTableItem *pCopyItem;

};

#endif // QRECIPETABLE_H
