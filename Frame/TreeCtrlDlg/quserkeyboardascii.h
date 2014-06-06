#ifndef QUSERKEYBOARDASCII_H
#define QUSERKEYBOARDASCII_H

#include <QWizardPage>
#include "ui_quserkeyboardascii.h"
#include "Frame\mainwindow.h"
#define ASCIISTART 9

namespace Ui {
    class QUserkeyboardASCII;
}

class QUserkeyboardASCII : public QWizardPage
{
    Q_OBJECT

public:
    explicit QUserkeyboardASCII(QWidget *parent = 0);
    ~QUserkeyboardASCII();

    Ui::QUserkeyboardASCII *ui;
    //QVector<ScreenAndWindow *>  userKeyboardwindow;
    QVector<SamDrawScene *> userKeyboardScene;
    //QVector<ScreenAndWindow *>  Tempwindow;//临时变量，存储选中的键盘组件
  //  QVector<SamDrawScene *> TempScene;
    bool ischecked[9];
    void ReView();

private slots:
    void on_ASCIIpattern9_clicked();
    void on_ASCIIpattern8_clicked();
    void on_ASCIIpattern7_clicked();
    void on_ASCIIpattern6_clicked();
    void on_ASCIIpattern5_clicked();
    void on_ASCIIpattern4_clicked();
    void on_ASCIIpattern3_clicked();
    void on_ASCIIpattern2_clicked();
    void on_ASCIIpattern1_clicked();
};

#endif // QUSERKEYBOARDASCII_H
