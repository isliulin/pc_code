#ifndef QSTATICPICTUREGENDLG_H
#define QSTATICPICTUREGENDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include <QGraphicsScene>
#include "view/qpixmapitem.h"

namespace Ui {
    class QStaticPictureGenDlg;
}

class QStaticPictureGenDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QStaticPictureGenDlg(QWidget *parent = 0);
    ~QStaticPictureGenDlg();

private:
    Ui::QStaticPictureGenDlg *ui;

private slots:
    void on_m_transparantbtn_clicked();
    void setAlphaColor(const QColor & mColor);       //…Ë÷√±ﬂøÚ…´
    void on_m_fileradio_clicked();
    void on_m_sysradio_clicked();
    void on_m_pathbtn_clicked();
    void on_m_trasparantcheck_clicked();
 //   void OnTransparantColor();
private:
    //QPickerColor *pTransparantColor;
public:
    QString sPath;
    int nSelectType;
    QGraphicsScene *pScene; //≥°æ∞
    QPixmapItem *pPixmap;
    QStringList sDataList;
    QGraphicsItem *pOldItem;
public:
    void InitParament();
    QString GetPicName(QString sPath);
    QPixmap TransparentPic(QPixmap pPic);
    void OnDoubleClickOpenInit(QGraphicsItem *pItem);
    void OnSaveProperty();
    QString GetLibItemName(QString str);
};

#endif // QSTATICPICTUREGENDLG_H
