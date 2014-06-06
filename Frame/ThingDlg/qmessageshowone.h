#ifndef QMESSAGESHOWONE_H
#define QMESSAGESHOWONE_H

#include <QWidget>
#include "Frame/qprogectmanager.h"
#include "view/qmessageshowattr.h"
#include "ui_qmessageshowone.h"

namespace Ui {
    class qMessageShowOne;
}

class qMessageShowOne : public QWidget
{
    Q_OBJECT

public:
    explicit qMessageShowOne(QWidget *parent = 0);
    ~qMessageShowOne();

public:
    Ui::qMessageShowOne *ui;

/////////////////////////////////////////////////////////
public://ԭpage2�ı���
    int     m_curLan;//��ǰ����
    bool    m_bFirstLanguage;   //�������Զ���ʹ�õ�һ�����Ե��ı�
    bool    m_bStateZero;       //����״̬���Զ���״̬0��ͬ
/////////////////////////////////////////////////////////

public:
    int curSta;//��ǰ״̬(��ǰ������ǵڼ���״̬)

public:
    QString     m_sShape;           //����
    bool        m_bDataType;        //16λ������Ϊ0,32λ������λ1,�������ݿ�ʱ�ָ���ö��
    Keyboard    m_keyAddress;       //���ӵ�ַ
    short       m_nStateCount;      //��״̬��
    short       m_eRemove;          //�ƶ�����(�����)
    short       m_nSpeed;           //�ƶ��ٶ�(�����)
    short       m_nAlpha;

    QVector<MsgProp> m_vecMsg;      //����״̬����

public:
    bool bInit;
    void Init(QMessageShowAttr* pItem);

private slots:
    void on_spinBox_tran_valueChanged(int );
    void on_comboBox_style_currentIndexChanged(int index);
    void set_pushButton_bkColor(const QColor & mColor);
    void on_pushButton_bkColor_clicked();
    void set_pushButton_foreColor(const QColor & mColor);
    void on_pushButton_foreColor_clicked();
    void on_pushButton_frameColor_clicked();
    void set_pushButton_frameColor(const QColor & mColor);
    void on_spinBox_curNum_valueChanged(int );
    void on_pushButton_addr_clicked();
    void on_lineEdit_addr_editingFinished();
    void on_comboBox_dataType_currentIndexChanged(int index);
    void on_spinBox_total_valueChanged(int );
    void on_pushButton_waixing_clicked();
    void on_comboBox_move_currentIndexChanged(int index);
    void on_spinBox_valueChanged(int value);
    void on_pushButton_fontColor_clicked();
    void set_pushButton_fontColor(const QColor & mColor);
    void on_spinBox_fontSize_valueChanged(int );
    void on_comboBox_fontNmae_currentIndexChanged(int index);
    void on_comboBox_lan_currentIndexChanged(int index);
    void on_checkBox_lanFirst_clicked(bool checked);//�Ƿ�ȫʹ�õ�һ������
    void on_checkBox_state_clicked(bool checked);
    void on_tableWidget_cellClicked(int row, int column);
    void on_plainTextEdit_textChanged();//�޸ĵ�ǰ״̬�ı�����

signals:
    void changeCondition();
};

#endif // QMESSAGESHOWONE_H
