#ifndef QIMAGESHOWDLG_H
#define QIMAGESHOWDLG_H

#include <QDialog>
#include <QGraphicsItem>
#include "Frame/DrawDlg/OpenLibrary.h"
#include "view/ImageItem.h"
#include "Frame/ThingDlg/switch/securitywidget.h"

namespace Ui {
    class QImageShowDlg;
}

class QImageShowDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QImageShowDlg(QGraphicsItem *pItem,QWidget *parent = 0);
    void Init(ImageItem *pItem);
    void onSingleInit();
    void onMultInit();
    void onTableNumChange(int nTotalRow);//改变列表框的行数
    void onItemchange(int nCurrentRow);
    bool onSavePicInfo(INTOSAVE &picInfo);
    void onSetStatus(int maxnum);
    ImageItem *onCopyItem(QGraphicsItem *pItem);
    ImageItem *onGetItemFromFile(QString sPath,EITEM_TYPE eType);
    QString GetPicName(QString sPath);
    void onSelectpicbtn(int nType);
    ~QImageShowDlg();

public:
    ImageItem *pCopyItem;
private:
    Ui::QImageShowDlg *ui;
    SecurityWidget *pSecurityWight;
    QGraphicsScene *pScene;
    QGroupItem *pBaseItem;
    QVector<IMAGEINFO> PicInfo;
    INTOSAVE m_SaveInfo;
    Keyboard World_Address_Keyboard;
    Keyboard Bit_Address_Keyboard;
    QString  sBitAddress;
    QString sWorldAddress;
    bool bInitFlag;
    QVector <int> values;
    int oId;

public slots:
    void confyButton();
    void loadHelp();
    void onSetBackColor(const QColor &mColor);

private slots:
    void on_m_SelectPicpushBtn_clicked();
    void on_m_SelectLibpushBtn_clicked();
    void on_m_MonitorAddress_editingFinished();
    void on_btn_customValue_clicked();
    void on_m_CmpspBox_valueChanged(int );
    void on_m_StatuscmbBox_currentIndexChanged(int index);
    void on_m_BackColorBtn_clicked();
    void on_groupBox_3_clicked();
    void on_Monitor_Address_EntryBtn_clicked();
    void on_m_deletepicbtn_clicked();
    void on_m_tableWidget_clicked(QModelIndex index);
    void on_m_StatuspBox_valueChanged(int );
    void on_m_BitradioBtn_clicked(bool checked);
    void on_m_FixedradioBtn_clicked(bool checked);
    void on_m_TimeradioBtn_clicked();
    void on_m_MutilradioBtn_clicked(bool checked);
    void on_m_SingleradioBtn_clicked(bool checked);
};

#endif // QIMAGESHOWDLG_H
