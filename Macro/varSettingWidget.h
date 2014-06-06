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
Labels<<tr("������")<<tr("�������")<<tr("�ֳ�")<<tr("��д����")
      <<tr("��ַ����")<<tr("��ַ")<<tr("��������")<<tr("PLCվ��");
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

    void offsetInput(void); //ƫ�Ƶ�ַ������Ӧ
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
     QLabel *offsetAddrLabel; //ƫ�Ƶ�ַ

     QLineEdit *nameLineEdit;
     QLineEdit *lengthLineEdit;
     QLineEdit *addressLineEdit;
     QLineEdit *offsetAddrEdit;//ƫ�Ƶ�ַ�༭��

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
