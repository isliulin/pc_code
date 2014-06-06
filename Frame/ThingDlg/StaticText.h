#ifndef STATICTEXT_H
#define STATICTEXT_H

#include <QDialog>
#include "StaticTextDlg.h"
#include "view/switchitem.h"
class StaticText : public QDialog
{
    Q_OBJECT
public:
    explicit StaticText(QGraphicsItem *pItem,QWidget *parent = 0);
    ~StaticText();
    QVBoxLayout *mainLayout;
signals:

public slots:
    void accept();
private slots:
   void loadHelp();
private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
    //QStringList * datalist;
public:
    StaticTextDlg *pGeneralDlg;
    SecurityWidget *securitywidget; //È¨ÏÞÒ³Ãæ
    StaticTextItem *pCopyItem;
    SwitchItem *switchitem;
    TextInfos textInfo;
    securityPro sproperty;

};

#endif // STATICTEXT_H
