#ifndef QUSERKEYBOARDPROPERTY_H
#define QUSERKEYBOARDPROPERTY_H
#include "ui_quserkeyboardproperty.h"

#include <QDialog>
#include "qpickercolor.h"
#include "qcolor.h"
#include "qfiledialog.h"
namespace Ui {
    class QUserKeyboardProperty;
}

class QUserKeyboardProperty : public QDialog
{
    Q_OBJECT

public:
    explicit QUserKeyboardProperty(QWidget *parent = 0);
    ~QUserKeyboardProperty();
    QButtonGroup *R_BackGaound_Group;
    void init();

private:
    Ui::QUserKeyboardProperty *ui;
    void DrowKeybaordsize();

private slots:
    void on_Cancel_clicked();
    void on_Accept_clicked();
    void on_newscreen_picture_radiobutton_clicked();
    void on_newscreen_silence_radiobutton_clicked();
    void on_newscreen_picture_pushButton_clicked();
    void on_newscreen_pushButton_frontcolor_clicked();
    void on_newscreen_pushButton_bk_clicked();
    void  setCurrentBKColor(const QColor &);
    void setCurrentFrontColor(const QColor &);
};

#endif // QUSERKEYBOARDPROPERTY_H
