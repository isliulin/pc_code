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
public://原page2的变量
    int     m_curLan;//当前语言
    bool    m_bFirstLanguage;   //所有语言都是使用第一种语言的文本
    bool    m_bStateZero;       //所有状态属性都和状态0相同
/////////////////////////////////////////////////////////

public:
    int curSta;//当前状态(当前点击的是第几个状态)

public:
    QString     m_sShape;           //外形
    bool        m_bDataType;        //16位正整数为0,32位正整数位1,保存数据库时恢复成枚举
    Keyboard    m_keyAddress;       //监视地址
    short       m_nStateCount;      //总状态数
    short       m_eRemove;          //移动方向(走马灯)
    short       m_nSpeed;           //移动速度(走马灯)
    short       m_nAlpha;

    QVector<MsgProp> m_vecMsg;      //各个状态属性

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
    void on_checkBox_lanFirst_clicked(bool checked);//是否全使用第一种语言
    void on_checkBox_state_clicked(bool checked);
    void on_tableWidget_cellClicked(int row, int column);
    void on_plainTextEdit_textChanged();//修改当前状态文本内容

signals:
    void changeCondition();
};

#endif // QMESSAGESHOWONE_H
