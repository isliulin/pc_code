#ifndef VARSETTINGWIDGET_H
#define VARSETTINGWIDGET_H
#include <QDialog>
#include <QComboBox>
#include <QTableWidget>
#include "Frame/qprogectmanager.h"


class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;
class QTableWidget;
class QSpinBox;
class QGroupBox;

enum Command_t{NEW,EDIT,DEL};
/*
Labels<<tr("变量名")<<tr("数据类别")<<tr("字长")<<tr("读写属性")
      <<tr("地址类型")<<tr("地址")<<tr("连接类型")<<tr("PLC站号");
 */
typedef struct varSettingRecord
{

    QString strVarName;
    QString strDataType;
    QString strDataLength;
    QString strRW;

    QString strAddressType;
    QString strAddress;
    QString strConType;
    QString strPLCStation;

}varSettingRecord_t;


class varSettingWidget : public QDialog
{
    Q_OBJECT

public:
    varSettingWidget(QTableWidget *parent = 0,bool bMulti = false, bool bGlobal = false);
public:
    void setDefault(QVector<VarPro> vars,VarPro var);
    QVector <Keyboard> getAddrs(Keyboard kb);
    QString appendNumTail(QString varName,int index);

private slots:

    void addrInput(void);
    void setDataTypeIndex(int index);
    void setRWIndex(int index);

    void noSaveRecord(void);

    void offsetInput(void); //偏移地址输入响应
    void groupBoxOffsetChanged(bool);
public slots:

     void saveVarInfo(void);
     static int updateVarSettingConTable(int index, QString strConName);
     static QString GetPLCStation(int index);
public:
     QLabel *varNameLabel;
     QLabel *dataTypeLabel;
     QLabel *lengthLabel;
     QLabel *rwLabel;
     QLabel *addressLabel;
     QLabel *countLabel;
     QLabel *offsetAddrLabel; //偏移地址

     QLineEdit *nameLineEdit;
     QLineEdit *lengthLineEdit;
     QLineEdit *addressLineEdit;
     QLineEdit *offsetAddrEdit;//偏移地址编辑框

     QSpinBox *countSpin;

     QComboBox *dataTypeLineEdit;
     QComboBox *rwLineEdit;

     QPushButton *addressButton;
     QPushButton *okButton;
     QPushButton *cancelButton;

     QTableWidget *pTableWidget;
     bool quit;

     QPushButton *offsetButton;
     QGroupBox   *groupBoxOffset;
public:
     QString strVarName;
     QString strDataType;
     QString strDataLength;
     QString strRW;
     QString strAddress;

     VarPro saveVar;
     VarPro initVar;

     QVector <VarPro> saveVars;
     int iDataTypeIndex;
     int iRWIndex;
     int iLength;
     Keyboard addr;
     Keyboard offsetAddr;
private:
     void initMem();

public:
     int icellDoubleClickedRow;
     int icellDoubleClickedColumn;
     int icurrentRowIndex;
     int BOOL;

public :
     Command_t command;
     bool isMulti;
     QVector<QString> varNames;
private:
     bool m_bGlobal;
};

#endif // VARSETTINGWIDGET_H
