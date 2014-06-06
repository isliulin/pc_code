#ifndef TABLE_H
#define TABLE_H

#include <QDialog>
#include "tabledlg.h"
class Table : public QDialog
{
    Q_OBJECT
public:
    explicit Table(QGraphicsItem *pItem,QWidget *parent = 0);
    ~Table();
    QVBoxLayout *mainLayout;

signals:

public slots:
    void accept();
private slots:
   void loadHelp();
private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
    QStringList * datalist;
    SecurityWidget* pSecurity;
public:
    TableDlg *pGeneralDlg;

};

#endif // TABLE_H
