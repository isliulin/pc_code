#ifndef STATICTEXTS_H
#define STATICTEXTS_H

#include <QDialog>
#include "StaticTextDlg.h"
#include "ui_statictexts.h"
#include "view/switchitem.h"
namespace Ui {
    class StaticTexts;
}
class StaticTexts : public QDialog
{
    Q_OBJECT
public:
    explicit StaticTexts(QGraphicsItem *pItem,QWidget *parent = 0);
    ~StaticTexts();
signals:

public slots:
    void DrawStaticTexts();
private slots:
   void on_help_clicked();
   void on_cancel_clicked();
   void on_accept_clicked();

private:
    QGroupItem *pBaseItem;
    QTabWidget *tabWidget;
    QGraphicsScene *pScene;
    Ui::StaticTexts *ui;
    QString sText;//保存键盘上文本标记
    int oId;
public:
    StaticTextDlg *pGeneralDlg;
    SecurityWidget *securitywidget; //权限页面
    StaticTextItem *pCopyItem;
    SwitchItem *switchitem;
    TextInfos textInfo;
    securityPro sproperty;

};

#endif // STATICTEXTS_H
