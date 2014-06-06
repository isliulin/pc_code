#ifndef STATICTEXTDLG_H
#define STATICTEXTDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include <QGraphicsItem>
#include "ui_StaticTextDlg.h"
#include "view/statictextitem.h"

namespace Ui {
    class StaticTextDlg;
}

class StaticTextDlg : public QWidget
{
    Q_OBJECT

public:
    explicit StaticTextDlg(QWidget *parent = 0);
    ~StaticTextDlg();

    QPickerColor *pFontColor;
    QPickerColor *pBackColor;
    QPickerColor *pFrontColor;
    QGroupItem *pBaseItem;
    QGraphicsScene *pScene;
    StaticTextItem *textItem;
public:
    Ui::StaticTextDlg *ui;
public:

    bool isFlag;
    struct Text
    {
        QString sText;
        int nFontSize;
        int nfontsizeindex;
        QString sFont;
        int nfont;
        int TextAlignIndex;
        QString nFontColor;
        bool adapt;//◊÷  ”¶
        bool bold;
        bool italic;
        bool underline;
        QString newColors;
    }TxtProperty[5];
public:
    void InitParament();
    void OnDoubleClickInit(StaticTextItem *item);
    void SaveText(TextInfos &m_text);

signals:
    void DrawTextView();

private slots:
    //void on_adaptText_clicked(bool checked);
    void on_WordInterval_valueChanged(int );
    void on_Alpha_valueChanged(int );
    void on_Pattern_currentIndexChanged(int index);
    void on_m_underlinecheck_clicked(bool checked);
    void on_IfItalic_clicked(bool checked);
    void on_IfBold_clicked(bool checked);
    void on_combo_Alignment_currentIndexChanged(int index);
    void on_adaptText_clicked(bool checked);
    void on_FrontColor_clicked();
    void on_BackColor_clicked();
    void on_FontColor_clicked();
    void on_m_check_clicked(bool checked);
    void on_font_currentIndexChanged(QString sFont);
    void on_FontSize_currentIndexChanged(QString sFontSize);
    void on_plainTextEdit_textChanged();
    void on_m_languagecmb_currentIndexChanged(int index);

    void setCurrentFontColor(const QColor &);
    void setCurrentBKColor(const QColor &);
    void setCurrentFrontColor(const QColor &);
};

#endif // STATICTEXTDLG_H
