#ifndef QDROPDOWNBOX_H
#define QDROPDOWNBOX_H

#include <QDialog>
#include <qgraphicsitem.h>
#include <qtablewidget.h>
#include "view/qdropdownattr.h"
#include "Frame/ThingDlg/switch/securitywidget.h"
#include "qdropdownfont.h"
#include "qdropdownlist.h"

class ComboPicture;
namespace Ui {
    class qDropDownBox;
}

class qDropDownBox : public QDialog
{
    Q_OBJECT

public:
    explicit qDropDownBox(QDropdownAttr* pItem, QWidget *parent = 0);
    ~qDropDownBox();

private:
    Ui::qDropDownBox *ui;
    int oId;

public:
    void InitProperty(QDropdownAttr* pItem);

public:
    qDropDownList *m_pDropDownList;//下拉框列表
    qDropDownFont *m_pDropDownFont;//下拉框字体
    SecurityWidget *pSecurityWight;//显现页面
    ComboPicture *m_pPictureList;//图片列表

public:
    QDropdownAttr *m_pCopyItem;

private slots:
    void redraw(short );
    void on_help_clicked();
    void on_cancel_clicked();
    void on_accept_clicked();
    void on_checked_picture(bool checked);
    void on_rowChanged(int row );

public:
    QGraphicsScene* pScene;//场景
    QDropdownAttr*  pTempItem;
    QRectItem       *pRect;
    QRectItem       *pBackRect;
    QFoldLineItem   *pLine;
};

#endif // QDROPDOWNBOX_H
