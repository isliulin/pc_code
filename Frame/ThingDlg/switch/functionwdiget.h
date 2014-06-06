#ifndef FUNCTIONWDIGET_H
#define FUNCTIONWDIGET_H

#include <QWidget>
#include "Frame/qprogectmanager.h"

namespace Ui {
    class FunctionWdiget;
}

class FunctionWdiget : public QWidget
{
    Q_OBJECT

public:
    explicit FunctionWdiget(QWidget *parent = 0);
    ~FunctionWdiget();
    bool Save();
    void InitUi(functionSwitchPro property);

    functionSwitchPro funproperty;
private:
    Ui::FunctionWdiget *ui;
    bool bX;
    bool bY;
    void FunTranslation(int index);

private slots:
    void on_checkBox_Y_clicked(bool checked);
    void on_checkBox_X_clicked(bool checked);
    void on_combo_Funciton_currentIndexChanged(int index);
};

#endif // FUNCTIONWDIGET_H
