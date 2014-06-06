#ifndef BITWIDGET_H
#define BITWIDGET_H

#include <QWidget>
#include <Frame/qprogectmanager.h>
namespace Ui {
    class BitWidget;
}

class BitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BitWidget(QWidget *parent = 0);
    ~BitWidget();

    QString getAddr();
    Keyboard bitAddr;

    bitSwitchPro bitproperty;
    bool Save();
    void InitUi(bitSwitchPro property);

private:
    Ui::BitWidget *ui;

signals:
    void AddrChanged(QString string);




private slots:
    void on_btn_bitAddr_clicked();
    void on_edit_operatingAddr_textChanged(QString );
    void on_comboBox_operateType_currentIndexChanged(int index);
};

#endif // BITWIDGET_H
