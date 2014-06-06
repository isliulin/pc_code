#ifndef SLIDER_H
#define SLIDER_H

#include <QDialog>
#include "SliderGeneralDlg.h"
#include "view/switchitem.h"

namespace Ui {
    class Slider;
}

class Slider : public QDialog
{
    Q_OBJECT

public:
    explicit Slider(QGraphicsItem *pItem,QWidget *parent = 0);
    ~Slider();
    QVBoxLayout *mainLayout;
    void InitAllProperty(SliderItem *pItem);
    SliderItem *pCopyItem;
    SliderInfo m_slider;

private:
    Ui::Slider *ui;
    int oId ;
signals:

public slots:
    void OnReDrawSlider();
public:
    SliderGeneralDlg *pGeneralDlg;
    SecurityWidget *pSecurityWight; //È¨ÏÞÒ³Ãæ
    securityPro sproperty;

private:
    QGraphicsScene *pScene;
    QGroupItem *pBaseItem;
    QTabWidget *tabWidget;

private slots:
    void on_help_clicked();
    void on_cancel_clicked();
    void on_accept_clicked();

};

#endif // SLIDER_H
