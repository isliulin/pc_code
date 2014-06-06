#ifndef QKEYBOARDASCIIGEN_H
#define QKEYBOARDASCIIGEN_H

#include <QDialog>
#include "qpickercolor.h"
#include "Frame/qprogectmanager.h"
#include <QGraphicsScene>
#include "view/qsimpletextitem.h"//文本类
#include <QGraphicsItemGroup>//组合类
#include "view/qgroupitem.h"//对组合类的操作
#include "view/keyboarditem.h"
#include "Frame/ThingDlg/qkeybutton.h"

namespace Ui {
    class QKeyboardASCIIGen;
}

class QKeyboardASCIIGen : public QDialog
{
    Q_OBJECT

public:
    explicit QKeyboardASCIIGen(QWidget *parent = 0);
    ~QKeyboardASCIIGen();
    QButtonGroup *TypeCheck;
    KeyBoardItem *pCopyItem;
    void ASCIIEntryGenSave(KeyInfo &keyInfo);
    void Init(KeyBoardItem *pItem);
    void onGetinfo(KeyInfo &keyInfo);
    QButtonGroup  *RadioButton_screen_pos_Group ;
    QButtonGroup  *RadioButton_screen_Group;
    QPixmap newimage;
    QString onGetText();
    Ui::QKeyboardASCIIGen *ui;
    QString EditText;
    QGroupItem *pBaseItem;
    //QGraphicsScene *pScene;
    QGraphicsItem *pOldItem;
    QString sFrameColorBefore;
    QString sFGColorBefore;
    QString sBGColorBefore;
    QString sFrameColorAfter;
    QString sBGColorAfter;
    QString sFGColorAfter;
    int nPatternBefore;
    int nPatternAfter;
    QGraphicsItem *pItem;
    KeyInfo key;

    bool bState;//false: before    true: after
    //文本页面变量
    QString sText;    //文本
    QString sFont;    //字体
    int nFontSize;    //字体大小
    int fontsizecurrindex;
    QString sColor;   //字体颜色
    //bool Flick;       //闪烁
    bool Bold;        //粗体
    bool Italic;      //斜体
    bool UnderLine;   //下划线
    int nWordInterval;//字距
    int nPosition;    //位置
    //图片页面变量
    int nPicSource;   //图片来源
    bool ifFit;       //是否配合物大小
    int nPicBorder;   //图片边距
    int nPicPosition; //图片位置
    bool ifDeletePic; //是否删除图片
    QString sPath;

private:
    QGraphicsItem *pLibItem;
    void isPixOrItem(QGraphicsItem* pItem);
    bool nInitFlag;
    bool isflag;

signals:
    void onKeypress(int iFlag);
    void txtChange();
    void onDrawSence();
    void onStyle(QString str);
    void picChange(QGraphicsItem* pItem,QPixmap *pixmap);
    void addPicture(QGraphicsItem* pItem,QPixmap* picture);

private slots:
    void on_CAPSLOCK_clicked(bool checked);
    void on_m_deletepicbtn_clicked();
    void PicPosChanged(int nCheckId);
    void on_m_slectpicbtn_clicked();
    void on_Pattern_currentIndexChanged(int index);
    void on_combo_Alignment_currentIndexChanged(int index);
    void on_comboBox_font_currentIndexChanged(QString );
    void OnSetTextColor(const QColor &);
    void on_m_textbtn_clicked();
    void on_m_fontsizecmb_currentIndexChanged(int index);
    void on_m_underlinecheck_clicked(bool checked);
    void on_m_italiccheck_clicked(bool checked);
    void on_m_boldcheck_clicked(bool checked);
    void on_m_text_textChanged();
    void on_State1_clicked();
    void on_State0_clicked();
//    void on_nStateChange_currentIndexChanged(int index);
    //void on_LoadShape_clicked();
    void on_ASCII_clicked(bool checked);
    void on_ESC_clicked(bool checked);
    void on_CLEAR_clicked(bool checked);
    void on_BACKSPACE_clicked(bool checked);
    void on_ENTER_clicked(bool checked);
   // void on_Text_Color_clicked();
    void on_BG_Color_clicked();
    void on_FG_Color_clicked();
    void on_Frame_Color_clicked();
    void on_ASCIIText_textChanged(QString );
    void on_Pattern_activated(int index);
    void setFrameColor(const QColor & mColor);       //设置边框色
    void setFGColor(const QColor & mColor);       //前景色
    void setBGColor(const QColor & mColor);       //背景色
   // void setTextColor(const QColor & mColor);       //文本色
};

#endif // QKEYBOARDASCIIGEN_H
