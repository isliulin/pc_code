#ifndef NEWDYNRECTDLG_H
#define NEWDYNRECTDLG_H

#include <QDialog>
#include <qgraphicsitem.h>
#include <color.h>
#include "Frame/mainwindow.h"
#include "view/dynrectattr.h"

namespace Ui {
    class newDynRectDlg;
}

class newDynRectDlg : public QDialog
{
    Q_OBJECT

public:
    explicit newDynRectDlg(DynRectAttr* pItem, QWidget *parent = 0);
    ~newDynRectDlg();

private:
    Ui::newDynRectDlg *ui;
    int oId;

public:
    SecurityWidget *pSecurityWight;//显现页面

    //矩形外观
    bool      m_bFillColor;
    QColor    m_nFillColor;
    bool      m_bFrameColor;
    QColor    m_nFrameColor;
    short     m_nFrameWidth;
    short     m_nAlpha;
    //显示区域设置
    short     m_nBeginX;
    short     m_nBeginY;
    short     m_nWidth;
    short     m_nHeight;
    QColor    m_nBgColor;
    //位置控制
    bool      m_bPosCtrl;
    Keyboard  m_addrH;
    Keyboard  m_addrV;
    //大小控制
    bool      m_bSizeCtrl;
    short     m_nRefType;//固定点
    Keyboard  m_addrWidth;
    Keyboard  m_addrHeight;

public:
    void Init(DynRectAttr *pItem);

public:
    DynRectAttr *m_pCopyItem;

public:
    QGraphicsScene scene;
    DynRectAttr *itemTemp;

private slots:
    void on_spinBox_valueChanged(int );
    void on_groupBox_4_clicked(bool checked);
    void on_groupBox_5_clicked(bool checked);
    void on_pushButton_AddrHeight_clicked();
    void on_pushButton_AddrWidth_clicked();
    void on_pushButton_AddrV_clicked();
    void on_pushButton_AddrH_clicked();
    void on_pushButton_bgColor_clicked();
    void set_pushButton_bgColor(const QColor & mColor);
    void on_pushButton_frame_clicked();
    void set_pushButton_frame(const QColor & mColor);
    void on_pushButton_fill_clicked();
    void set_pushButton_fill(const QColor & mColor);
    void on_checkBox_frame_clicked(bool checked);
    void on_checkBox_fill_clicked(bool checked);
    void on_help_clicked();
    void on_cancel_clicked();
    void on_accept_clicked();
};

#endif // NEWDYNRECTDLG_H
