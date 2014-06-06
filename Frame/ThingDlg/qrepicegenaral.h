#ifndef QREPICEGENARAL_H
#define QREPICEGENARAL_H

#include <QWidget>
#include  <QGraphicsItem>
#include "view/QRecipetableItem.h"
#include <QVector>

namespace Ui {
    class Qrepicegenaral;
}

class Qrepicegenaral : public QWidget
{
    Q_OBJECT

public:
    explicit Qrepicegenaral(QWidget *parent = 0);
    ~Qrepicegenaral();
    void Init(QRecipeTableItem *pItem);
    QGraphicsItem * pCopyItem;

   bool  GeneralSave(RECIPESHOW &Info);
   int GetRecipeIndex();//获取当前显示的配方组ID
   int GetAligentType();//获取文本对齐方式
   QColor GetBackColor();//获取文本框背景色
   int GetLangIndex();

   QColor GetTitleBackColor();
   QColor GetTitleTextColor();//获取标题列文本色
   int GetRowCount();//获取行数
   int GetColoumCount();//获取列数
   QString GetTitletextFont();//获取标题列字体
   int GetTitletextSize();     //获取标题列字体大小


   //获取标题行信息
   QString GetRowText();      //获取列标题名称，有多语言
   QString GetRowtextFont();//获取标题列字体
   int GetRowtextSize();     //获取标题列字体大小
   QColor GetRowBackColor();
   QColor GetRowTextColor();//获取标题列文本色

   QColor GetLineColor();   //获取表格线颜色

   bool showDeschecked();//是否显示配方描述

   bool showIDChecked();//是否显示配方ID


   int getId();
   int GetTransparentValue();

   QString sRecipeName[5];
   QString sFont[5];
   int nFontSize[5];
   QVector <QString> m_sRecipeName;//表列标题多语言信息
  // QVector<QString> vector_lan;
private:
     bool bInitFlag;
     int oId;

private slots:
    void on_comboBox_lan_currentIndexChanged(int index);
    void on_m_RecipeNamelineEdit_textChanged(QString );
    void on_btn_Linecolor_clicked();
    void on_m_GroupRecipecmBox_currentIndexChanged(int index);
    void on_m_RowTextcolorBtn_clicked();
    void on_m_RowBackColorBtn_clicked();
    void on_comboBox_title_font_activated(QString sfont);
    void on_comboBox_title_fontsize_activated(QString sFont);
    void on_recipename_textChanged(QString sName);

    void on_comboBox_lan_activated(int index);
    void on_btn_title_color_clicked();
    void on_btn_title_bk_clicked();
    void on_btn_textcolor_clicked();
    void on_btn_board_clicked();
    void on_btn_bk_clicked();
    void setBKColor(const QColor &);
    void setTextColor(const QColor &);
    void setRowBackColor(const QColor &);
    void setRowTextColor(const QColor &);
    void settitle_BKColor(const QColor &);
    void setTitleColor(const QColor &);
    void setLineBtnColor(const QColor &);

private:
    Ui::Qrepicegenaral *ui;
};

#endif // QREPICEGENARAL_H
