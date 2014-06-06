#ifndef WORDWIDGET_H
#define WORDWIDGET_H

#include <QWidget>
#include <Frame/qprogectmanager.h>
namespace Ui {
    class WordWidget;
}

class WordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WordWidget(QWidget *parent = 0);
    ~WordWidget();

    QString getAddr();

    bool Save();
    void InitUi(wordSwitchPro property);

    Keyboard wordAddr;
    Keyboard wordAddrConst;//wxy

    wordSwitchPro wordproperty;
private:
    Ui::WordWidget *ui;

signals:
    void AddrChanged(QString string);

private slots:
    void on_comboBox_operateType_currentIndexChanged(int index);
    void on_comboBox_dataType_currentIndexChanged(int index);
    void on_btn_wordAddr_clicked();
    void on_edit_operatingAddr_textChanged(QString );
    void on_check_const_clicked(bool);
    void on_btn_wordAddr_const_clicked();
};

#endif // WORDWIDGET_H
