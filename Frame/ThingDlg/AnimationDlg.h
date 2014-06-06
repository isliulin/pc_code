#ifndef ANIMATIONDLG_H
#define ANIMATIONDLG_H

#include <QDialog>
#include <QGraphicsItem>
#include "view/animationitem.h"
#include "Frame/ThingDlg/switch/areawidget.h"
#include "Frame/ThingDlg/switch/scatterwidget.h"
#include "Frame/ThingDlg/switch/securitywidget.h"

namespace Ui {
    class AnimationDlg;
}

class AnimationDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AnimationDlg(QGraphicsItem *pItem,QWidget *parent = 0);
    void InitAllProperty(AnimationItem *pItem);
    AnimationItem *onCopyItem(QGraphicsItem *pItem);
    QString GetPicName(QString sPath);
    bool onAnimatInfosave(AnInfo &aninfo);
    void onSetStatus(int maxnum);
    void onSaveTextInfo();//保存文本属性
    void onInitText();
    void onItemchange(int nCurrentRow);
    AnimationItem *onGetItemFromFile(QString sPath,EITEM_TYPE eType);
    void onTableNumChange(int nTotalRow);
    void onAddText(int nRow);
    void OnSetTextProperty();
    void onReplaceItem();//替换掉矩形框Item
    void onSelectpicbtn(int nType);
    ~AnimationDlg();

public:
    AreaWidget *pAreaWidget;
    ScatterWidget *pScatWidget;
    QWidget * cWidget;//当前显示的属性页
    SecurityWidget *pSecurityWight;//显现页面
    AnimationItem *pCopyItem;
    QGraphicsItem *pOldItem;
    AnimationItem *pStatusItem;
    QGraphicsScene *pScene;
    QGroupItem *pBaseItem;
    QVector<PictureInfo> PicInfo;//图片属性
    QVector<TextInfo> m_Text;      //文本属性
    AnInfo m_AnimatInfo;

private:
    Ui::AnimationDlg *ui;
    QVector<int> values;
    bool bInitflag;
    Keyboard Monitor_Address_Keyboard;
    bool bSave;
    int oId;

signals:

public slots:
    void onResetpoint(int index,QPointF pos);//重新设置轨迹点坐标
    void confyButton();
    void loadHelp();
private slots:
    void on_m_SelectPicpushBtn_2_clicked();
    void on_m_SelectLibpushBtn_2_clicked();
    void on_m_TextlineEdit_textChanged();
    void on_m_TextlineEdit_textChanged(QString );
    void on_Monitor_Address_EntryBtn_clicked();
    void on_btn_customValue_clicked();
    void on_m_ConditionCmBox_currentIndexChanged(int index);
    void on_m_EnableTextCkBox_clicked(bool checked);
    void on_m_TextlineEdit_lostFocus();
    void on_m_tableWidget_clicked(QModelIndex index);
    void on_m_SaveTextpushBtn_clicked();
    void on_edit_text_textChanged();
    void on_m_StatusTextCmBox_currentIndexChanged(int index);
    void on_m_TextColorpushBtn_clicked();
    void on_m_fontCbBox_currentIndexChanged(int index);
    void on_m_AligmentCbBox_currentIndexChanged(int index);
    void on_m_fontSizecbBox_currentIndexChanged(int index);
    void on_m_UnderlineckBox_clicked(bool checked);
    void on_m_ItalicckBox_clicked(bool checked);
    void on_m_BoldckBox_clicked(bool checked);
    void on_m_OrdinaryckBox_clicked(bool checked);
    void on_m_StatusTotalSpBox_valueChanged(int );
    void on_comboBox_5_currentIndexChanged(int index);
    void on_m_DrawpushBtn_clicked();
    void on_checkBox_clicked();
    void on_checkBox_2_clicked(bool checked);
    void on_m_deletepicbtn_clicked();
    void on_m_BackColorBtn_clicked();
    void on_m_LocusTypecmBox_currentIndexChanged(int index);

public slots:
   void onSetTextColor(const QColor &mColor);
   void onPicBackColor(const QColor &mColor);
};

#endif // ANIMATIONDLG_H
