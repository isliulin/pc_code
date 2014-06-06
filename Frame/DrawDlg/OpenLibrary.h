#ifndef OPENLIBRARY_H
#define OPENLIBRARY_H

#include <QDialog>
#include "view/samdrawscene.h"
#include <QGraphicsItem>
#include <QHBoxLayout>
#include <QTreeWidgetItem>

namespace Ui {
    class OpenLibrary;
}

class OpenLibrary : public QDialog
{
    Q_OBJECT

public:
    explicit OpenLibrary(QWidget *parent = 0);
    ~OpenLibrary();

private:
    Ui::OpenLibrary *ui;
    int nActiveIndex;  //当前画面序号
    QGraphicsView *pView;
    QHBoxLayout *m_pLayout;
    int nSelectLibType;   //1表示选择的是基本图库，2表示用户自定义图库
    LibRaryScene *userScene;
public:
    QGraphicsItem *pCopyItem;
    QVector <SamDrawScene *> vUserScene;  //存用户自定义画面的容器
private:
    void loadUserDefineLib();
    bool getSaveItem();
    void lockCurrentSheetItem();
    void setCurrentLibSheet(int nSelectType,int nIndex);
  //  void loadBaseLibAndUserDefineLib(QRect rect);
private slots:
    void on_treeWidget_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
    void on_HelpButton_clicked();
    void onDoublClickLibraryItem(QGraphicsItem* pItem);
    void on_m_AlterItem_clicked();
    void on_m_Cancel_clicked();
    void on_m_OkBtn_clicked();
    void on_treeWidget_itemClicked(QTreeWidgetItem* item, int column);


//**********************自定义图库导入开发*********************
private slots:
    void on_treeWidget_itemPressed(QTreeWidgetItem* item, int column);
    void loadSelfDefImages();
    void createNewFolder();
    void delSelfDefImages();
private:
    const QString EXTERN_LIB_NODE;
    const QString SELF_DEF_NODE;
private:
    /*************************************************
    * 函数名称: loadImages2Extern
    * 功能描述: 将所选择目录的图片导入extern目录
    * 参数列表: srcFiles————目录路径
    *        　desPath ————目标目录路径
    * 返回结果: void
    *************************************************/
    void loadImages2Extern(const QStringList &srcFiles,const QString &desPath);
    /*************************************************
    * 函数名称: deleteDir
    * 功能描述: 删除目录
    * 参数列表: dirName————目录路径
    * 返回结果: bool   ————是否删除成功
    *************************************************/
    bool deleteDir(const QString &dirName);
    /*************************************************
    * 函数名称: drawNewScene
    * 功能描述: 绘制制定目录下的图片
    * 参数列表: dirPath————目录路径
    * 返回结果: void
    *************************************************/
    void drawNewScene(const QString &dirPath);
//*******************************************************END
};

#endif // OPENLIBRARY_H
