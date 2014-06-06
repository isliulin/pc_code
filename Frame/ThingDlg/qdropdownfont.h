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
    QString     m_strFontName;          //�������͵�����
    short       m_nFontSize;            //�����С
    short       m_nLanType;             //��������
    short       m_nFontStyle;           //������ʽ����׼�����壬б�壩
    QColor      m_nFontColor;           //������ɫ
    QColor      m_nBackColor;           //������ɫ
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
