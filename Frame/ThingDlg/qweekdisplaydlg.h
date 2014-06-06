#ifndef QWEEKDISPLAYDLG_H
#define QWEEKDISPLAYDLG_H

#include <QDialog>
#include"qweekdisplaygendlg.h"
#include"qweekdisplaytextdlg.h"
class QWeekDisplayDlg : public QDialog
{
    Q_OBJECT
public:
    explicit QWeekDisplayDlg(QGraphicsItem *pItem,QWidget *parent = 0);
    ~QWeekDisplayDlg();
    QVBoxLayout *mainLayout;
signals:

public slots:
    void OnSetTextProperty();
    void OnClickTextCell();
    void OnGeneralStateChange();
    void accept();
private slots:
   void loadHelp();
private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;


    QWeekDisplaytextDlg *pTextDlg;
    QStringList * datalist;

    void InitAllProperty(QGraphicsItem *pItem);
public:
    QWeekDisplayGenDlg *pGeneralDlg;
};

#endif // QWEEKDISPLAYDLG_H
