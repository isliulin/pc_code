#ifndef LOADSHAPE_H
#define LOADSHAPE_H

#include <QDialog>
#include "view/samdrawscene.h"
#include <QGraphicsItem>
#include <QHBoxLayout>

namespace Ui {
    class LoadShape;
}

class LoadShape : public QDialog
{
    Q_OBJECT

public:
    explicit LoadShape(QWidget *parent = 0);
    ~LoadShape();

private:
    Ui::LoadShape *ui;
private:
    SamDrawScene *pScene;
    QVector <SamDrawScene *> vScene;  //�滭�������
    int nActiveIndex;  //��ǰ�������
    QGraphicsView *pView;
    QHBoxLayout *m_pLayout;
public:
    QGraphicsItem *pCopyItem;
private:
    void LoadScene(QString sPath);
private slots:
    void onSelectSingleItem();
};

#endif // LOADSHAPE_H
