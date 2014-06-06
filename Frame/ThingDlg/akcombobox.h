#ifndef AKCOMBOBOX_H
#define AKCOMBOBOX_H

#include <QDialog>
#include "view/akcomboitem.h"
#include "view/qmessageboradattr.h"
namespace Ui {
    class AkComboBox;
}

class AkComboBox : public QDialog
{
    Q_OBJECT

public:
    //explicit AkComboBox(AkComboItem* pItem, QWidget *parent = 0);
    explicit AkComboBox(AkComboItem* pItem, QWidget *parent = 0);
    ~AkComboBox();

private:
    Ui::AkComboBox *ui;
    //增加编辑框
    QLineEdit* pEdit;
    QString    m_str;//存放编辑框内容
    int        m_nEditRow;//编辑框所在的行
    int        m_nEditCol;//编辑框所在的列

private:
    //void InitProperty(AkComboItem* pItem);
    void InitProperty(AkComboItem* pItem);

private slots:
    void on_m_DataTypefontCmbBox_currentIndexChanged(int index);
    void on_spin_Trans_valueChanged(int );
    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void on_checkBox_3_clicked(bool checked);
    void on_checkBox_2_clicked(bool checked);
    void on_checkBox_clicked(bool checked);
    void on_spinBox_2_valueChanged(int );
    void on_comboBox_fontType_currentIndexChanged(QString );
    void on_combo_Alignment_activated(int index);
    void on_combo_Language_currentIndexChanged(int index);
    void on_btn_backcolor_2_clicked();
    void on_help_clicked();
    void on_cancel_clicked();
    void on_accept_clicked();
    void on_btn_backcolor_clicked();
    void on_btn_picture_clicked();
    void on_btn_no_clicked();
    void on_btn_lib_clicked();
    void on_checkBox_lanFirst_clicked(bool checked);
    void on_spinBox_valueChanged(int );
    void on_pushButton_timeAddr_clicked();
    void on_btn_new_2_clicked();

public://临时变量
    int           curLan; //当前语言,从0开始
    bool          bInit;//是否初始化完成

    QGroupItem    *pBaseItem;//Scene
    //QGraphicsItem *pCopyItem;//Scene

    Keyboard      key;//控制地址
    EITEM_TYPE 	  eLibType;//图库类型
    QString       path;//路径
    QColor        BkColor;//背景色
    QColor        TextColor;//文本颜色

    QVector<ComboStatu>     m_vecStatus;    //多状态
    QVector<ComboLanguage>  m_vecLanguage;  //多语言
    int oId;

public://
    AkComboItem   *m_pCopyItem;
    //qMessageBoradAttr *m_pCopyItem;

public:
    SecurityWidget *pSecurityWight;//显现页面
    void draw();

public:
    QGraphicsScene* pScene;//场景
    AkComboItem*    pTempItem;
    QRectItem       *pRect;
    QRectItem       *pBackRect;
    QFoldLineItem   *pLine;
    void drawScene();

    AkComboItem     *pSceneItem;

private slots:
    void set_pushButton_fill(const QColor & mColor);//背景色
    void set_text_color(const QColor & mColor);//文本色
    void shit();
};

#endif // AKCOMBOBOX_H
