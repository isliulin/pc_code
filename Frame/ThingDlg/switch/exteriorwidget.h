#ifndef EXTERIORWIDGET_H
#define EXTERIORWIDGET_H

//外观页面
#include <QWidget>

namespace Ui {
    class ExteriorWidget;
}

class ExteriorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExteriorWidget(QWidget *parent = 0);
    ~ExteriorWidget();

    void resizeStatus(int count);//更新属性vector

    inline int getStatusCount()
    {
        return statusCount;
    }

    void UpdateText(int statusIndex,int languageIndex);
    void UpdatePic(int statusIndex);
    void ShowPropChanged();

    void init(QItemGroup *pItem,bool bInit = false);

    bool Save();
	int currentState();


public:
    //外观页面所有属性
    int statusIndex;
    //QVector<ST_TEXT_PROP > textList;//每种语言对应一个ST_TEXT_PROP

    QVector<QVector<ST_TEXT_PROP > > statusText;//每个状态对应一个Vector

    QVector<ST_PIC_PROP > statusPic;//每个状态对应的图片属性

    ST_TEXT_PROP defaultText;

    ST_PIC_PROP defaultPic;

    int languageCount;
    QGraphicsScene scene;
    QGraphicsItem *pCopyItem;
private:
    bool initflg;
    int statusCount;
    Ui::ExteriorWidget *ui;

    QItemGroup *item;
    QGroupItem *pBaseItem;
private slots:
    void on_spin_Trans_valueChanged(int alpha);
    void on_btn_backcolor_clicked();
    void on_btn_no_clicked();
    void on_combo_flick_currentIndexChanged(int index);
    void on_btn_copyText_2_clicked();
    void on_btn_lib_clicked();
    void textSizeChange(int size);
    void on_btn_copyText_clicked();
    void on_btn_copyPic_clicked();
    void pictureChanged();
    void on_textChanged();
    void on_btn_picture_clicked();
    void on_check_Flick_clicked(bool checked);
    void on_btn_underline_clicked(bool checked);
    void on_btn_Italic_clicked(bool checked);
    void on_btn_bold_clicked(bool checked);
    void setTextColor(const QColor &color);
    void setBackColor(const QColor &color);
    void on_btn_color_clicked();
    void on_combo_Alignment_currentIndexChanged(int index);
    void on_combo_Font_currentIndexChanged(QString );
    void on_combo_Language_currentIndexChanged(int index);
    void on_spin_StatusIndex_valueChanged(int );
    void slotStatusCountChanged(int count);
	void slotBitLamp();

};

#endif // EXTERIORWIDGET_H
