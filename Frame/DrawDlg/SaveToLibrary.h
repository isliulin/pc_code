#ifndef SAVETOLIBRARY_H
#define SAVETOLIBRARY_H

#include <QDialog>
#include <QGraphicsItem>

namespace Ui {
    class SaveToLibrary;
}

class SaveToLibrary : public QDialog
{
    Q_OBJECT

public:
    explicit SaveToLibrary(QWidget *parent = 0);
    ~SaveToLibrary();

private:
    Ui::SaveToLibrary *ui;
    SamDrawScene *pScene;
    QButtonGroup  *Radio_Group ;
    QPixmap pPix;
public:
  //  QList<QGraphicsItem *> SaveItemList;
private slots:
    void on_HelpButton_clicked();
    void on_m_color_clicked();
    void on_m_transparentcheck_clicked(bool checked);
    void on_m_Cancel_clicked();
    void on_m_SaveTo_clicked();
    void selectFunction(int nCheckId);

    void setColor(const QColor &);

private:
    void selectAll(SamDrawScene *pScene);
    void reverseSelect(SamDrawScene *pScene);
};

#endif // SAVETOLIBRARY_H
