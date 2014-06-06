#ifndef SAVEUSERDEFINELIB_H
#define SAVEUSERDEFINELIB_H
#include "view/samdrawscene.h"
#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
    class SaveUserDefineLib;
}

class SaveUserDefineLib : public QDialog
{
    Q_OBJECT

public:
    explicit SaveUserDefineLib(QWidget *parent = 0);
    ~SaveUserDefineLib();

private:
    Ui::SaveUserDefineLib *ui;

    QVector <SamDrawScene *> vUserScene;  //存用户自定义画面的容器
    int nActiveIndex;  //当前画面序号
    QHBoxLayout *m_pLayout;
private:
    void loadUserDefineLib(QString sPath);
    QGraphicsItem * CreateGroupItem();
    void SaveDefineLib(QString sPath);

    void SetItemPath(QGraphicsItem *pItem);
    QStringList sPath;

    void lockCurrentSheetItem();
    QPointF getMaxPoint();



private slots:
    void on_m_Cancel_clicked();
    void on_m_SaveItem_clicked();
    void on_m_DeleteItem_clicked();
    void on_treeWidget_itemClicked(QTreeWidgetItem* item, int column);
   // void onSelectSingleItem();
};

#endif // SAVEUSERDEFINELIB_H
