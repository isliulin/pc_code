#ifndef QRECIPEDATE_H
#define QRECIPEDATE_H

#include <QDialog>
#include <QGraphicsItem>
#include <QStandardItemModel>
namespace Ui {
    class Qrecipedate;
}

class Qrecipedate : public QDialog
{
    Q_OBJECT

public:
    explicit Qrecipedate(QWidget *parent = 0);
    ~Qrecipedate();
      void Init(QGraphicsItem *pItem);
      void GeneralSave(QStringList *datalist);

private:
    Ui::Qrecipedate *ui;
    bool bInitFlag;

private slots:


private slots:
    void on_m_language_currentIndexChanged(int index);
};

#endif // QRECIPEDATE_H
