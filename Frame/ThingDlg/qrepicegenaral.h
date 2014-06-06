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
   int GetRecipeIndex();//��ȡ��ǰ��ʾ���䷽��ID
   int GetAligentType();//��ȡ�ı����뷽ʽ
   QColor GetBackColor();//��ȡ�ı��򱳾�ɫ
   int GetLangIndex();

   QColor GetTitleBackColor();
   QColor GetTitleTextColor();//��ȡ�������ı�ɫ
   int GetRowCount();//��ȡ����
   int GetColoumCount();//��ȡ����
   QString GetTitletextFont();//��ȡ����������
   int GetTitletextSize();     //��ȡ�����������С


   //��ȡ��������Ϣ
   QString GetRowText();      //��ȡ�б������ƣ��ж�����
   QString GetRowtextFont();//��ȡ����������
   int GetRowtextSize();     //��ȡ�����������С
   QColor GetRowBackColor();
   QColor GetRowTextColor();//��ȡ�������ı�ɫ

   QColor GetLineColor();   //��ȡ�������ɫ

   bool showDeschecked();//�Ƿ���ʾ�䷽����

   bool showIDChecked();//�Ƿ���ʾ�䷽ID


   int getId();
   int GetTransparentValue();

   QString sRecipeName[5];
   QString sFont[5];
   int nFontSize[5];
   QVector <QString> m_sRecipeName;//���б����������Ϣ
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
