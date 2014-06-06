#ifndef QHISTORYDATASHOWONE_H
#define QHISTORYDATASHOWONE_H

#include <QWidget>
#include "view/qhistorydatashowattr.h"
#include "ui_qhistorydatashowone.h"

namespace Ui {
    class QHistoryDataShowOne;
}

class QHistoryDataShowOne : public QWidget
{
    Q_OBJECT

public:
    explicit QHistoryDataShowOne(QWidget *parent = 0);
    ~QHistoryDataShowOne();

//private:
    Ui::QHistoryDataShowOne *ui;

public:
    void Init(QHistoryDataShowAttr* pItem);

public:
    int m_nCurLanNum;//��ǰ���Ժ�
    bool bInit;

public:
    //һ��
    QColor  m_nForecolor;       //ǰ��ɫ
    QColor  m_nFrameColor;      //�߿�ɫ
    short   m_nAlpha;
    //---------------
    short   m_nTextFontSize;    //�ı������С��Ĭ��10
    short   m_nLine;            //��ʾ������Ĭ��5
    QColor  m_nTextFontColor;   //�ı�������ɫ��Ĭ�Ϻ�ɫ
    //---------------
    bool    m_bShowTime;	//�Ƿ���ʾʱ�䣬Ĭ����ʾ
    bool    m_bShowDate;	//�Ƿ���ʾ����,Ĭ����ʾ
    QColor  m_nTitleBackColor;	//���ⱳ����ɫ��Ĭ�ϻ�ɫ
    QColor  m_nTitleFontColor;	//����������ɫ��Ĭ�Ϻ�ɫ
    bool    m_bShowCode;        //�Ƿ���ʾ���
    TIME_FORMAT	m_eTimeFormat;  //(ͳһʱ���ʽö��)ʱ���ʽ HH:MM
    DATE_FORMAT	m_eDateFormat;  //(ͳһʱ���ʽö��)���ڸ�ʽ Ĭ�ϣ�DD/MM/YY
    bool    m_bAddr;            //�Ƿ���Ҫ���Ƶ�ַ
    Keyboard m_KeyAddr;         //���Ƶ�ַ
    //---------------
    QVector<HistoryTextInfo> m_vecHisText;//ÿ�����Զ�Ӧ�ı������ݵ���������

private slots:
    //����
    void on_pushButton_Ctrl_clicked();
    void on_checkBox_Ctrl_clicked(bool checked);
    void on_spinBox_valueChanged(int );
    void on_lineEdit_number_editingFinished();
    void on_spinBox_dataLine_valueChanged(int value);
    void on_spinBox_dataFontSize_valueChanged(int value);
    void on_pushButton_dataColor_clicked();
    void set_pushButton_dataColor(const QColor & mColor);

    //��
    void on_pushButton_frameColor_clicked();
    void set_pushButton_frameColor(const QColor & mColor);
    void on_pushButton_frontColor_clicked();
    void set_pushButton_frontColor(const QColor & mColor);

    //�ı���
    void on_comboBox_textDateType_currentIndexChanged(int index);
    void on_checkBox_textDateb_clicked(bool checked);
    void on_comboBox_textTimeType_currentIndexChanged(int index);
    void on_checkBox_textTimeb_clicked(bool checked);
    void on_pushButton_textWordColor_clicked();
    void set_pushButton_textWordColor(const QColor & mColor);
    void on_pushButton_textBk_clicked();
    void set_pushButton_textBk(const QColor & mColor);
    void on_checkBox_textNum_clicked(bool checked);

    //������
    void on_lineEdit_titleDate_editingFinished();
    void on_lineEdit_titleTime_editingFinished();
    void on_comboBox_titleFontType_currentIndexChanged(int index);
    void on_spinBox_titleFontSize_valueChanged(int );
    void on_comboBox_titleLan_currentIndexChanged(int index);

signals:
    void redrawSence();
    void sigLanguageCh(int);

public slots:
    void groupCh();
    void slotLan(int lan);
};

#endif // QHISTORYDATASHOWONE_H
