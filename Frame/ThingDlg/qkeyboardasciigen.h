#ifndef QKEYBOARDASCIIGEN_H
#define QKEYBOARDASCIIGEN_H

#include <QDialog>
#include "qpickercolor.h"
#include "Frame/qprogectmanager.h"
#include <QGraphicsScene>
#include "view/qsimpletextitem.h"//�ı���
#include <QGraphicsItemGroup>//�����
#include "view/qgroupitem.h"//�������Ĳ���
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
    //�ı�ҳ�����
    QString sText;    //�ı�
    QString sFont;    //����
    int nFontSize;    //�����С
    int fontsizecurrindex;
    QString sColor;   //������ɫ
    //bool Flick;       //��˸
    bool Bold;        //����
    bool Italic;      //б��
    bool UnderLine;   //�»���
    int nWordInterval;//�־�
    int nPosition;    //λ��
    //ͼƬҳ�����
    int nPicSource;   //ͼƬ��Դ
    bool ifFit;       //�Ƿ�������С
    int nPicBorder;   //ͼƬ�߾�
    int nPicPosition; //ͼƬλ��
    bool ifDeletePic; //�Ƿ�ɾ��ͼƬ
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
    void setFrameColor(const QColor & mColor);       //���ñ߿�ɫ
    void setFGColor(const QColor & mColor);       //ǰ��ɫ
    void setBGColor(const QColor & mColor);       //����ɫ
   // void setTextColor(const QColor & mColor);       //�ı�ɫ
};

#endif // QKEYBOARDASCIIGEN_H
