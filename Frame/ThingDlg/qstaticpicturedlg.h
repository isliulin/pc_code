#ifndef QSTATICPICTUREDLG_H
#define QSTATICPICTUREDLG_H

#include <QDialog>
#include <QGraphicsItem>
#include <view/QStaticPictureItem.h>
#include "Frame/ThingDlg/switch/securitywidget.h"

namespace Ui {
    class QStaticPictureDlg;
}

class QStaticPictureDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QStaticPictureDlg(QGraphicsItem *pItem,QWidget *parent = 0);
    ~QStaticPictureDlg();
    void Init(QStaticPictureItem *pItem);
    void OnAddMovie();
    SecurityWidget *pSecurityWight;//����ҳ��

private:
    Ui::QStaticPictureDlg *ui;
    QGraphicsScene *pScene;
    QGraphicsPixmapItem *pPic;
    QPixmapItem *pPixmap;
    QTimer *PTimer;
    int nFramCount;   //֡������
    int nCurrentFram; //��ǰ֡
    QMovie *mMove;
    Keyboard CtrlAddr; //���Ƶ�ַ
    int oId;

public:
    QStaticPictureItem *pCopyItem;

private slots:
    void on_IfBitControl_clicked(bool checked);
    void on_pushButton_clicked();
    void on_m_cancelBtn_clicked();
    void on_m_BackColorpushBtn_clicked();
    void on_m_pathbtn_clicked();
    void on_m_runstopbtn_clicked(); //���в���
public slots:
    void confyButton();
    void loadHelp();
    void onSetBackColor(const QColor &mColor);
    void OnGifRun();
};

#endif // QSTATICPICTUREDLG_H
