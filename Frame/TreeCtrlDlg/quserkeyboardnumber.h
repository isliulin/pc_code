#ifndef QUSERKEYBOARDNUMBER_H
#define QUSERKEYBOARDNUMBER_H

#include <QWizardPage>
#include "Frame\mainwindow.h"
#include "ui_quserkeyboardnumber.h"

namespace Ui {
    class QUserkeyboardnumber;
}

class QUserkeyboardnumber : public QWizardPage
{
    Q_OBJECT

public:
    explicit QUserkeyboardnumber(QWidget *parent = 0);
    ~QUserkeyboardnumber();
    //QVector<ScreenAndWindow *>  userKeyboardwindow;
    QVector<SamDrawScene *> userKeyboardScene;
    //QVector<ScreenAndWindow *>  Tempwindow;//临时变量，存储选中的键盘组件
    QVector<SamDrawScene *> TempScene;
    Ui::QUserkeyboardnumber *ui;
    bool ischecked[9];
    void ReView();

private slots:
    void on_NOpattern9_clicked();
    void on_NOpattern8_clicked();
    void on_NOpattern7_clicked();
    void on_NOpattern6_clicked();
    void on_NOpattern5_clicked();
    void on_NOpattern4_clicked();
    void on_NOpattern3_clicked();
    void on_NOpattern2_clicked();
    void on_NOpattern1_clicked();
};

#endif // QUSERKEYBOARDNUMBER_H
