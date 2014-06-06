#ifndef SKDRAWTOOL_H
#define SKDRAWTOOL_H

#include <QDialog>
#include <QToolBar>
#include "view/samdrawscene.h"
#include <QDockWidget>
#include <QTableWidget>
#include "view/samdrawscene.h"
namespace Ui {
    class SKDrawTool;
}

class SKDrawTool : public QDialog
{
    Q_OBJECT

public:
    explicit SKDrawTool(QWidget *parent = 0);
    ~SKDrawTool();

private:
    Ui::SKDrawTool *ui;
    QToolBar *pToolbar;
    SamDrawScene *pScene;
    bool nSelectClickFlag;
    QString sWidgtContent;   //控件中输入的内容
private:

private:
    void loadTableWidget();
    void setItemProperty(int nMark);
private slots:
    void on_action_moveback_triggered();
    void on_action_movefore_triggered();
    void on_action_movedownlest_triggered();
    void on_action_movetoplest_triggered();
    void on_action_DrawText_triggered();
    void on_m_Cancel_clicked();
    void on_m_SaveItemBtn_clicked();
    void on_action_DeleteItem_triggered();
    void on_action_Arc_triggered();
    void on_action_PoloyRect_triggered();
    void on_action_Circle_triggered();
    void on_action_DrawRoundRect_triggered();
    void on_action_DrawRect_triggered();
    void on_action_DrawFreeLine_triggered();
    void on_action_DrawCircleLine_triggered();
    void on_action_DrawFoldLine_triggered();
    void on_action_DrawLine_triggered();
    void on_action_HMirror_triggered();
    void on_action_VMirror_triggered();
    void on_action_SameWidthHeight_triggered();
    void on_action_SameHeight_triggered();
    void on_action_SameWidth_triggered();
    void on_action_HCenter_triggered();
    void on_action_ButtomAlign_triggered();
    void on_action_TopAlign_triggered();
    void on_action_VCenter_triggered();
    void on_action_RightAlign_triggered();
    void on_action_LeftAlign_triggered();
    void on_m_table_itemChanged(QTableWidgetItem* item);
    void on_m_alpha_valueChanged(int );
    void on_m_linestyle_currentIndexChanged(int index);
    void on_m_linewidth_currentIndexChanged(int index);
    void on_m_pattern_currentIndexChanged(int index);
    void on_LineColor_clicked();
    void on_FrontColor_clicked();
    void on_BackColor_clicked();
    void on_action_Disgroup_triggered();
    void on_action_Group_triggered();

    void setBackColor(const QColor &);
    void setFrontColor(const QColor &);
    void setLineColor(const QColor &);
    void onSelectSingleItem();
};

#endif // SKDRAWTOOL_H
