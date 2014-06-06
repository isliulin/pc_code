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
    int nActiveIndex;  //��ǰ�������
    QGraphicsView *pView;
    QHBoxLayout *m_pLayout;
    int nSelectLibType;   //1��ʾѡ����ǻ���ͼ�⣬2��ʾ�û��Զ���ͼ��
    LibRaryScene *userScene;
public:
    QGraphicsItem *pCopyItem;
    QVector <SamDrawScene *> vUserScene;  //���û��Զ��廭�������
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


//**********************�Զ���ͼ�⵼�뿪��*********************
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
    * ��������: loadImages2Extern
    * ��������: ����ѡ��Ŀ¼��ͼƬ����externĿ¼
    * �����б�: srcFiles��������Ŀ¼·��
    *        ��desPath ��������Ŀ��Ŀ¼·��
    * ���ؽ��: void
    *************************************************/
    void loadImages2Extern(const QStringList &srcFiles,const QString &desPath);
    /*************************************************
    * ��������: deleteDir
    * ��������: ɾ��Ŀ¼
    * �����б�: dirName��������Ŀ¼·��
    * ���ؽ��: bool   ���������Ƿ�ɾ���ɹ�
    *************************************************/
    bool deleteDir(const QString &dirName);
    /*************************************************
    * ��������: drawNewScene
    * ��������: �����ƶ�Ŀ¼�µ�ͼƬ
    * �����б�: dirPath��������Ŀ¼·��
    * ���ؽ��: void
    *************************************************/
    void drawNewScene(const QString &dirPath);
//*******************************************************END
};

#endif // OPENLIBRARY_H
