#ifndef SECURITYWIDGET_H
#define SECURITYWIDGET_H

#include <QWidget>
#include <QGraphicsItem>
#include <QListWidgetItem>
#include <Frame/qprogectmanager.h>
#include "ui_securitywidget.h"

namespace Ui {
    class SecurityWidget;
}

class SecurityWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SecurityWidget(QWidget *parent = 0);
    void setTouchGroupEnabled(bool value);
    ~SecurityWidget();

    bool Save();
    void setTouchDisable(bool checked);

    void init(QItemGroup *pItem);

    void init(securityPro sproperty);//wxy 权限界面初始化
public:
    Keyboard AddrT;//触控解锁地址
    Keyboard AddrV;//显示解锁地址
    Keyboard noticeAddr;//通知地址

    securityPro sproperty;
public:
    Ui::SecurityWidget *ui;
    QItemGroup *item;

    void setGroupVVisible(bool bShow);
private slots:

    void on_combo_NoticeType_currentIndexChanged(int index);
    void on_combo_addrTypeT_currentIndexChanged(int index);
    void on_combo_addrTypeV_currentIndexChanged(int index);
    void OnListTChanged(QListWidgetItem* listItem);
    void OnListVChanged(QListWidgetItem* listItem);
    void on_combo_NoticceAddrType_currentIndexChanged(int index);
    void on_btn_ctlAddrV_clicked();
    void on_btn_noticeAddr_clicked();
    void on_btn_ctlAddrT_clicked();
    void on_groupBox_ShowByGroup_clicked(bool value);
    void on_groupBox_ShowByBit_clicked(bool value);
    void on_groupBox_TouchByBit_clicked(bool value);
    void on_groupBox_TouchByGroup_clicked(bool value);
};

#endif // SECURITYWIDGET_H
