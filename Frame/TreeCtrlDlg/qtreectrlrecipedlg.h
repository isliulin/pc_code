#ifndef QTREECTRLRECIPEDLG_H
#define QTREECTRLRECIPEDLG_H
#include "ui_qtreectrlrecipedlg.h"
#include "Frame\addressinputdialog.h"
#include "Frame/qprogectmanager.h"
#include <QDialog>
#include <QTableView>
#include <QStandardItemModel>
#include <QItemDelegate>



namespace Ui {
    class QTreeCtrlRecipeDlg;
}

class QTreeCtrlRecipeDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QTreeCtrlRecipeDlg(QWidget *parent = 0,int index = -1);
    ~QTreeCtrlRecipeDlg();
    void CellChanged_Bit(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void CellChanged_Word(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void onSetIaddr(Keyboard addr);
    bool onSaveInfo();
    void onLimitDataInput(int type,int row, int column);
    bool onSetAddress();
    void on_recipesize_spinBox_valueChanged(int );
    void refreshTableItem();
    void Init();

private:
    void mousePressEvent ( QMouseEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void tableFocusOut();
    bool eventFilter(QObject * o,QEvent *event);
    QVector <Keyboard> getAddrs(Keyboard addr,int nIntervl);
    Keyboard Address_Keyboard;
    Keyboard Bit_Address_Keyboard;
    Keyboard I_Address_Keyboard;
    int nIndex;
    bool bInitflag;
public:
    Ui::QTreeCtrlRecipeDlg *ui;
    FORMULA_PROP Pro;
    QVector<FORMULA_ST> formula;//Åä·½Êý×é
public slots:
    void confyButton();
    void loadHelp();

private slots:
    void on_m_keyspBox_currentIndexChanged(int index);
    void on_m_PouupckBox_clicked(bool checked);
    void on_recipe_spinBox_editingFinished();
    void on_m_helpBtn_clicked();
    void on_recipesize_spinBox_editingFinished();
    void on_m_IAddrlineEdit_editingFinished();
    void on_m_tableWidget_itemChanged(QTableWidgetItem* item);
    void on_m_LanguageCmBox_currentIndexChanged(int index);
    void on_m_BitaddresspushBtn_clicked();
    void on_m_writeaddresspushBtn_clicked();
    void on_m_namelineEdit_2_textChanged(QString );
    void on_recipeintput_pushButton_clicked();
    void on_recipeoutput_pushButton_clicked();
    void on_m_tabWidget_currentChanged(int index);
    void on_m_writeaddressCkBox_clicked(bool checked);
    void on_m_tableWidget_itemDoubleClicked(QTableWidgetItem* item);
    void on_datestyle_comboBox_currentIndexChanged(int index);
    void on_m_IaddrpushBtn_clicked();
    void on_M_CradioBtn_clicked(bool checked);
    void on_m_IradioBtn_clicked(bool checked);
    void on_m_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void on_m_tableWidget_cellDoubleClicked(int row, int column);
    void on_m_DeletePripushBtn_clicked();
    void on_m_AddPripushBtn_clicked();
    void on_m_TransRecipeCkBox_clicked(bool checked);
};

#endif // QTREECTRLRECIPEDLG_H
