#ifndef QKEYBUTTON_H
#define QKEYBUTTON_H

#include <QDialog>
#include "qkeyboardasciigen.h"
#include "Frame/ThingDlg/switch/securitywidget.h"
namespace Ui {
    class qkeybutton;
}

class qkeybutton : public QDialog
{
    Q_OBJECT

public:
    explicit qkeybutton(QGraphicsItem *pItem,QWidget *parent = 0);
    ~qkeybutton();
    void InitAllProperty(KeyBoardItem *pItem);
    void onDownkeyKeypress(KeyInfo key);//���º� ��ť����
    void onUpkeyKeypress(KeyInfo key);//����ǰ ��ť����

public:
    KeyInfo m_key;
    KeyBoardItem *pCopyItem;
    QGraphicsItem *pOldItem;
    QKeyboardASCIIGen *pASCIIInputgen;
    QTabWidget *tabWidget;

private:   
    Ui::qkeybutton *ui;
    QGraphicsScene *pScene;
    QGroupItem *pBaseItem;
    bool bInitFlag;
    SecurityWidget *pSecurityWight;
    int oId;

public slots:
    void onKeypress(int iFlag);//0:����ǰ��1�����º�
    void onTextChange();

private slots:
    void onAddPicture(QGraphicsItem* pItem,QPixmap* pPix);
    void on_help_clicked();
    void on_cancel_clicked();
    void on_accept_clicked();
};

#endif // QKEYBUTTON_H
