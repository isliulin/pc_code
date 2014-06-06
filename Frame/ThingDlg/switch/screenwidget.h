#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#include <QWidget>
#include "Frame/qprogectmanager.h"

namespace Ui {
    class ScreenWidget;
}

class ScreenWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenWidget(QWidget *parent = 0);
    ~ScreenWidget();
    bool Save();
    void InitUi(sceneSwitchPro property);

    sceneSwitchPro sceneproperty;
private:
    Ui::ScreenWidget *ui;

private slots:
    void on_comboBox_operType_currentIndexChanged(int index);
};

#endif // SCREENWIDGET_H
