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
    //���ӱ༭��
    QLineEdit* pEdit;
    QString    m_str;//��ű༭������
    int        m_nEditRow;//�༭�����ڵ���
    int        m_nEditCol;//�༭�����ڵ���

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

public://��ʱ����
    int           curLan; //��ǰ����,��0��ʼ
    bool          bInit;//�Ƿ��ʼ�����

    QGroupItem    *pBaseItem;//Scene
    //QGraphicsItem *pCopyItem;//Scene

    Keyboard      key;//���Ƶ�ַ
    EITEM_TYPE 	  eLibType;//ͼ������
    QString       path;//·��
    QColor        BkColor;//����ɫ
    QColor        TextColor;//�ı���ɫ

    QVector<ComboStatu>     m_vecStatus;    //��״̬
    QVector<ComboLanguage>  m_vecLanguage;  //������
    int oId;

public://
    AkComboItem   *m_pCopyItem;
    //qMessageBoradAttr *m_pCopyItem;

public:
    SecurityWidget *pSecurityWight;//����ҳ��
    void draw();

public:
    QGraphicsScene* pScene;//����
    AkComboItem*    pTempItem;
    QRectItem       *pRect;
    QRectItem       *pBackRect;
    QFoldLineItem   *pLine;
    void drawScene();

    AkComboItem     *pSceneItem;

private slots:
    void set_pushButton_fill(const QColor & mColor);//����ɫ
    void set_text_color(const QColor & mColor);//�ı�ɫ
    void shit();
};

#endif // AKCOMBOBOX_H
