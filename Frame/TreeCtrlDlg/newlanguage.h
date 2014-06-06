#ifndef NEWLANGUAGE_H
#define NEWLANGUAGE_H

#include <QDialog>

namespace Ui {
    class NewLanguage;
}

class NewLanguage : public QDialog
{
    Q_OBJECT

public:
    explicit NewLanguage(QWidget *parent = 0);
    ~NewLanguage();

private:
    Ui::NewLanguage *ui;
    bool bInitFlag;
private slots:
    void on_spinBox_valueChanged(int value);
    void on_comboBox_X_currentIndexChanged(int index);
    void on_HelpButton_clicked();
    void on_pushButton_cancle_clicked();
    void on_pushButton_ok_clicked();
};

#endif // NEWLANGUAGE_H
