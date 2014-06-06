#ifndef QDROPDOWNFONT_H
#define QDROPDOWNFONT_H

#include <QWidget>
#include "view/qdropdownattr.h"

namespace Ui {
    class qDropDownFont;
}

class qDropDownFont:public QWidget
{
    Q_OBJECT

public:
    explicit qDropDownFont(QWidget *parent = 0);
    ~qDropDownFont();

private:
    Ui::qDropDownFont *ui;

public:
    void Init(QDropdownAttr *pItem);

public:
    QString     m_strFontName;          //字体类型的名字
    short       m_nFontSize;            //字体大小
    short       m_nLanType;             //语言种类
    short       m_nFontStyle;           //文字样式（标准，粗体，斜体）
    QColor      m_nFontColor;           //字体颜色
    QColor      m_nBackColor;           //背景颜色
    short       m_nAlpha;

private slots:
    void on_spinBox_tran_valueChanged(int );
    void on_spinBox_valueChanged(int );
    void on_comboBox_fontLan_currentIndexChanged(int index);
    void on_comboBox_fontType_currentIndexChanged(int index);
    void on_checkBox_4_clicked(bool checked);
    void on_checkBox_3_clicked(bool checked);
    void on_checkBox_2_clicked(bool checked);
    void on_checkBox_1_clicked(bool checked);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void set_pushButton_showColor(const QColor & mColor);
    void set_pushButton_2_showColor(const QColor & mColor);

signals:
    void alphaCh(short alpha);
};

#endif // QDROPDOWNFONT_H
