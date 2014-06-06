#ifndef QMESSAGEBOARD_H
#define QMESSAGEBOARD_H

#include <QDialog>
#include "view/qmessageboradattr.h"

namespace Ui {
    class qMessageBoard;
}

class qMessageBoard : public QDialog
{
    Q_OBJECT

public:
    explicit qMessageBoard(qMessageBoradAttr* pItem, QWidget *parent = 0);
    ~qMessageBoard();

public:
    SecurityWidget      *pSecurityWight;//显现页面
    qMessageBoradAttr   *m_pCopyItem;
    QGraphicsScene      *pScene;        //场景
    qMessageBoradAttr   *pTempItem;

public:
    int  curLan;
    bool bInit;
    QVector<MmessageBoardLanguage> m_vecMessage;

private:
    Ui::qMessageBoard *ui;
    void drawTable();
    void drawSence();
    QVector<qreal> vVLine;              //用来存垂直线的数据
    QVector<qreal> vHLine;             //用来存水平线的数据
    int oId;

private slots:
    void on_spinBox_line_valueChanged(int );
    void on_accept_clicked();
    void on_cancel_clicked();
    void on_help_clicked();
    void on_comboBox_style_currentIndexChanged(int index);
    void on_comboBox_Tfonttype_currentIndexChanged(int index);
    void on_spinBox_Tfontsize_valueChanged(int );
    void on_spinBox_transparency_valueChanged(int );
    void on_checkBox_date_clicked();
    void on_checkBox_time_clicked();
    void on_checkBox_number_clicked();
    void on_lineEdit_message_editingFinished();
    void on_lineEdit_date_editingFinished();
    void on_lineEdit_time_editingFinished();
    void on_lineEdit_number_editingFinished();
    void on_comboBox_language_currentIndexChanged(int index);
    void on_pushButton_color_clicked();
    void set_pushButton_color(const QColor & mColor);
    void on_pushButton_frontcolor_clicked();
    void set_pushButton_frontcolor(const QColor & mColor);
    void on_pushButton_backcolor_clicked();
    void set_pushButton_backcolor(const QColor & mColor);
    void on_pushButton_framecolor_clicked();
    void set_pushButton_framecolor(const QColor & mColor);
    void on_pushButton_BKcolor_clicked();
    void set_pushButton_BKcolor(const QColor & mColor);
    void on_pushButton_Tfontcolor_clicked();
    void set_pushButton_Tfontcolor(const QColor & mColor);
};

#endif // QMESSAGEBOARD_H
