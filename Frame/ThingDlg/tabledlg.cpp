#include "tabledlg.h"
#include "ui_tabledlg.h"
#include "view/qrectitem.h"
#include "view/qlineitem.h"

#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

TableDlg::TableDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableDlg)
{
    vVLine.clear();
    vHLine.clear();
    ui->setupUi(this);
    oId = -1;
    pScene = new QGraphicsScene(this);
    ui->MainView->setScene(pScene);

}

TableDlg::~TableDlg()
{
    if(pScene)
    {
        delete pScene;
        pScene=NULL;
    }
    delete ui;
}

void TableDlg::InitParament()
{
    bInitFlag = false;

    ui->m_backcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(224,224,224).name()));
    ui->m_bordercolorbtn->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    ui->m_linecolorbtn->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    ui->m_bordercheck->setChecked(true);
    ui->m_borderlable->setVisible(true);
    ui->m_bordercolorbtn->setVisible(true);
    ui->m_linetypecmb->setCurrentIndex(1);
    ui->m_hcheck->setChecked(true);
    ui->m_vcheck->setChecked(true);

    ui->lineEdit_H->setText("LW0");
    ui->lineEdit_H->setVisible(false);
    ui->check_const_H->setCheckState(Qt::Unchecked);
    ui->check_const_H->setVisible(true);
    ui->btnAddr_const_H->setVisible(false);

    ui->lineEdit_V->setText("LW0");
    ui->lineEdit_V->setVisible(false);
    ui->check_const_V->setCheckState(Qt::Unchecked);
    ui->check_const_V->setVisible(true);
    ui->btnAddr_const_V->setVisible(false);
    ui->spinBox->setValue(pwnd->getNewId());

    DrawTable();
    bInitFlag = true;
}

void TableDlg::OnSetBackColor(const QColor & mBkColor)   //����ɫ
{
    ui-> m_backcolorbtn->setStyleSheet( QString("background:%1").arg(mBkColor.name()));        //������ɫ
    QString sColor = pwnd->ColorTOString(mBkColor);
    pBaseItem->SetPropertyValue("mRect.BackColor",QVariant(sColor));
    pBaseItem->SetPropertyValue("mRect.Alpha",QVariant(ui->m_TransparentspBox->value()));
}

void TableDlg::OnSetBorderColor(const QColor & mBorderColor) //�߿�ɫ
{
    ui->m_bordercolorbtn->setStyleSheet( QString("background:%1").arg(mBorderColor.name())); //�߿���ɫ
    QString sColor = pwnd->ColorTOString(mBorderColor);
    pBaseItem->SetPropertyValue("mRect.LineColor",QVariant(sColor));
}

void TableDlg::OnSetLineColor(const QColor & mColor)  //������ɫ
{
     ui->m_linecolorbtn->setStyleSheet( QString("background:%1").arg(mColor.name())); //�߿���ɫ
    if(!bInitFlag)
        return;
    pScene->clear();
    DrawTable();
}

void TableDlg::on_m_bordercheck_clicked() //���
{
    bool nCheck = ui->m_bordercheck->checkState();
    if(nCheck)
    {
        ui->m_borderlable->setVisible(true);
        ui->m_bordercolorbtn->setVisible(true);
        pBaseItem->SetPropertyValue("mRect.LineType",QVariant(1));
        QColor mColor = ui->m_bordercolorbtn->palette().background().color();;   //�߿���ɫ
        QString sColor = pwnd->ColorTOString(mColor);
        pBaseItem->SetPropertyValue("mRect.LineColor",QVariant(sColor));
    }
    else
    {
        ui->m_borderlable->setVisible(false);
        ui->m_bordercolorbtn->setVisible(false);
        pBaseItem->SetPropertyValue("mRect.LineType",QVariant(0));
    }
}

void TableDlg::DrawTable()
{
    QColor mBkColor = ui->m_backcolorbtn->palette().background().color();         //������ɫ
    QColor mBorderColor = ui->m_bordercolorbtn->palette().background().color();   //�߿���ɫ
    QColor mLineColor =ui->m_linecolorbtn->palette().background().color();      //������ɫ
    int nHNum = ui->m_hnumberspin->value();           //�������
    if(ui->check_const_H->isChecked())
    {
        nHNum = 4;
    }
    int nVNum = ui->m_Vnumberspin->value();           //�������
    if(ui->check_const_V->isChecked())
    {
        nVNum = 4;
    }
    bool bBorder = ui->m_bordercheck->checkState();   //�Ƿ����
    bool bHShow = ui->m_hcheck->checkState();         //�Ƿ�ˮƽ����
    bool bVShow = ui->m_vcheck->checkState();         //�Ƿ�ֱ��ʾ
    int nLineType = ui->m_linetypecmb->currentIndex();//��������
    short nTransparent = ui->m_TransparentspBox->value();

    QPainterPath mPath;               //�����ߵ�path
    double mMoveX = 0;                //���̶�X��ʼ��
    double mMoveY = 0;                //���̶�Y��ʼ��
    double mLineX = 0;                //���̶�X��ʼ��
    double mLineY = 0;                //���̶�Y��ʼ��
    QTableItem *pGroup = new QTableItem;
    QLineItem *pLine;
    int WH = 160;
    double HVal = 160.0/nHNum;
    double VVal = 160.0/nVNum;
    QString str = "";

    QRectF rect(QPointF(0,0), QSize(WH,WH));        //���Ʊ߿�ɫ���ο�
    QRectItem *pRect = new QRectItem(rect);
    pRect->SetBackColor(mBkColor);                    //���ñ���ɫ
    pRect->SetName(tr("mRect"));
    pRect->SetAlpha(nTransparent);
    pGroup->addToGroup(pRect);
    bool bDoubclick = false;
    if(bBorder)                                       //ѡ�����
    {
        pRect->SetLineType(1);
        pRect->SetLineColor(mBorderColor);              //���ñ߿�ɫ
    }
    else
    {
        pRect->SetLineType(0);
    }

    if(nVNum == (vVLine.size() - 1) && nHNum == (vHLine.size() - 1))
    {
        bDoubclick = true;
        qreal Width = vVLine.at(vVLine.size()-1) - vVLine.at(0);
        qreal Hight = vHLine.at(vHLine.size()-1) - vHLine.at(0);

        qreal n = vVLine.at(0);
        for(int i = 0; i < vVLine.size(); i++ )
        {
            vVLine[i] = vVLine[i] - n;
            vVLine[i] = vVLine[i] * 160.0/Width;
        }

        n = vHLine.at(0);
        for(int i = 0; i < vHLine.size(); i++ )
        {
            vHLine[i] = vHLine[i] - n;
            vHLine[i] = vHLine[i] * 160.0/Hight;
        }
    }

    /*********************************************************************
     *�����ǻ�ˮƽ����
     ********************************************************************/
    if(bHShow)
    {
        for(int i = 1; i < nHNum; i++)
        {
            QPainterPath mPath;
            mMoveX = 0;
            mMoveY = i*HVal;
            mLineX = WH;
            mLineY = i*HVal;
            if(bDoubclick)
            {
                mMoveY = vHLine.at(i);
                mLineY = vHLine.at(i);
            }
            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);
            pLine = new QLineItem(mPath);
            pLine->setLineColor(mLineColor);
            pLine->setLineType(nLineType);
            str = QString("%1").arg(i);
            str = tr("HLine")+str;
            pLine->SetName(str);
            pGroup->addToGroup(pLine);
        }
    }
    /*********************************************************************
     *�����ǻ���ֱ����
     ********************************************************************/
    if(bVShow)
    {
        for(int i = 1; i < nVNum; i++)
        {
            QPainterPath mPath;
            mMoveX = i*VVal;
            mMoveY = 0;
            mLineX = i*VVal;
            mLineY = WH;
            if(bDoubclick)
            {
                mMoveX = vVLine.at(i);
                mLineX = vVLine.at(i);
            }
            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);
            pLine = new QLineItem(mPath);
            pLine->setLineColor(mLineColor);
            pLine->setLineType(nLineType);
            str = QString("%1").arg(i);
            str = tr("VLine")+str;
            pLine->SetName(str);
            pGroup->addToGroup(pLine);
        }
    }
    pScene->addItem(pGroup);        //��ӵ�����
    pGroup->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->setFlag(QGraphicsItem::ItemIsMovable, false);

    this->pOldItem = pGroup;
    this->pBaseItem = new QGroupItem(pOldItem);
}

void TableDlg::on_m_hnumberspin_valueChanged(int )//�������
{
    if(!bInitFlag)
        return;
    pScene->clear();
    DrawTable();
}

void TableDlg::on_m_Vnumberspin_valueChanged(int )//�������
{
    if(!bInitFlag)
        return;
    pScene->clear();
    DrawTable();
}

void TableDlg::on_m_hcheck_clicked(bool checked)//ˮƽ��ʾ
{
    if(!bInitFlag)
        return;
    pScene->clear();
    DrawTable();
}

void TableDlg::on_m_vcheck_clicked(bool checked)//��ֱ��ʾ
{
     if(!bInitFlag)
        return;
     pScene->clear();
     DrawTable();
}

void TableDlg::on_m_linetypecmb_currentIndexChanged(int index)//��������
{
    if(!bInitFlag)
        return;
    int i = 0;
    QString str = "";
    int nHNum = ui->m_hnumberspin->value();           //�������
    int nVNum = ui->m_Vnumberspin->value();           //�������
    for(i = 1; i < nHNum; i++)
    {
        str = QString("%1").arg(i);
        str = tr("HLine")+str;
        str = str + tr(".LineType");
        pBaseItem->SetPropertyValue(str,QVariant(index));
    }
    for( i = 1; i < nVNum; i++)
    {
        str = QString("%1").arg(i);
        str = tr("VLine")+str;
        str = str + tr(".LineType");
        pBaseItem->SetPropertyValue(str,QVariant(index));
    }
}

bool TableDlg::SaveGeneralPage(QStringList *datalist, int index)
{
    TABLEINFO Table;
    int nTemp = 0;
    QColor mColor = ui-> m_backcolorbtn ->palette().background().color();;         //������ɫ20
    Table.nBackColor = mColor;

    mColor = ui->m_bordercolorbtn->palette().background().color();  //�߿���ɫ21
    Table.nFramecolor = mColor;

    mColor = ui->m_linecolorbtn->palette().background().color();       //������ɫ22
    Table.nWShowColor = mColor;

    Table.bShowFrameLine = ui->m_bordercheck->isChecked();//�Ƿ����23

    nTemp = ui->m_hnumberspin->value();//�������24
    Table.nOrientationCount = nTemp;

    nTemp = ui->m_Vnumberspin->value();//�������25
    Table.nPortraitCount = nTemp;

    Table.bShowOrientationLine = ui->m_hcheck->isChecked();//�Ƿ�ˮƽ26

    Table.bShowPortraitCount = ui->m_vcheck->isChecked();//�Ƿ�ֱ27

    nTemp = ui->m_linetypecmb->currentIndex();//������
    Table.eNLineType = nTemp;

    Table.nTransparent = ui->m_TransparentspBox->value();

    Table.bHDynamicControl = ui->check_const_H->isChecked();
    if(Table.bHDynamicControl)
    {
        if(! pwnd->IsAddressCheckRight(Table.addrHDynamic,tr("д���ַ"),ui->lineEdit_H,1))
        {
            ui->lineEdit_H->setFocus();
            return false;
        }
    }
    else
    {
        Table.addrHDynamic.sShowAddr = "LW0";
    }

    Table.bVDynamicControl = ui->check_const_V->isChecked();
    if(Table.bVDynamicControl)
    {
        if(! pwnd->IsAddressCheckRight(Table.addrVDynamic,tr("д���ַ"),ui->lineEdit_V,1))
        {
            ui->lineEdit_V->setFocus();
            return false;
        }
    }
    else
    {
        Table.addrVDynamic.sShowAddr = "LW0";
    }
    pOldItem->m_Table = Table;
    pOldItem->setId(ui->spinBox->value());

    if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID�ظ������޸�ID��"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox->setFocus();
        return false;
    }

    return true;
}

void TableDlg::DoubleClickInit(QGraphicsItem *pItem)
{
    bInitFlag = false;
    QColor mColor;
    if(pItem)   //��Data �� stringList�л�ȡ���Բ�����
    {

        if(pItem)
        {
            QGraphicsItem *Item = dynamic_cast<QTableItem *> (pItem)->Clone();
            pOldItem = dynamic_cast<QTableItem *> (Item);
        }
        if(!pOldItem)
        {
            return;
        }

        QList<QGraphicsItem *> list = pItem->childItems();
        QRectF rect = pItem->sceneBoundingRect();
        QString sName = "";
        vVLine.clear();
        vHLine.clear();
        vVLine.append(rect.x());
        vHLine.append(rect.y());
        foreach(QGraphicsItem *pItem,list)
        {
            QPointF pos = pItem->boundingRect().topLeft()+pItem->scenePos();
            sName = pItem->data(GROUP_NAME_KEY).toString();
            if(sName.contains("VLine")) //��ֱ��
            {
                vVLine.append(pos.x());
            }
            if(sName.contains("HLine")) //ˮƽ��
            {
                vHLine.append(pos.y());
            }
        }

        for(int i = 0; i < vVLine.size(); i++)
        {
            for(int j = i + 1; j < vVLine.size(); j++)
            {
                if(vVLine.at(i) > vVLine.at(j))
                {
                    qreal odata;
                    odata = vVLine.at(i);
                    vVLine.replace(i,vVLine.at(j));
                    vVLine.replace(j,odata);
                }
            }
        }
        vVLine.append(rect.x() + rect.width());

        //��ֱ��
        for(int i = 0; i < vHLine.size(); i++)
        {
            for(int j = i + 1; j < vHLine.size(); j++)
            {
                if(vHLine.at(i) > vHLine.at(j))
                {
                    qreal odata;
                    odata = vHLine.at(i);
                    vHLine.replace(i,vHLine.at(j));
                    vHLine.replace(j,odata);
                }
            }
        }
        vHLine.append(rect.y() + rect.height());

        mColor = pOldItem->m_Table.nBackColor;
        ui->m_backcolorbtn ->setStyleSheet( QString("background:%1").arg(mColor.name()));

        mColor = pOldItem->m_Table.nFramecolor;
        ui->m_bordercolorbtn->setStyleSheet( QString("background:%1").arg(mColor.name()));

        mColor = pOldItem->m_Table.nWShowColor;
        ui->m_linecolorbtn ->setStyleSheet( QString("background:%1").arg(mColor.name()));

        ui->m_bordercheck->setChecked(pOldItem->m_Table.bShowFrameLine);

        ui->m_hnumberspin->setValue(pOldItem->m_Table.nOrientationCount);

        ui->m_Vnumberspin->setValue(pOldItem->m_Table.nPortraitCount);

        ui->m_hcheck->setChecked(pOldItem->m_Table.bShowOrientationLine);

        ui->m_vcheck->setChecked(pOldItem->m_Table.bShowPortraitCount);

        ui->m_linetypecmb->setCurrentIndex(pOldItem->m_Table.eNLineType);

        ui->m_TransparentspBox->setValue(pOldItem->m_Table.nTransparent);

        oId = pOldItem->id();
        ui->spinBox->setValue(pOldItem->id());
        if(pOldItem->m_Table.bHDynamicControl)
        {
            ui->m_hnumberspin->setVisible(false);

            ui->lineEdit_H->setText(pOldItem->m_Table.addrHDynamic.sShowAddr);
            ui->lineEdit_H->setVisible(true);
            ui->check_const_H->setCheckState(Qt::Checked);
            ui->btnAddr_const_H->setVisible(true);
        }
        else
        {
            ui->m_hnumberspin->setVisible(true);

            ui->lineEdit_H->setText(pOldItem->m_Table.addrHDynamic.sShowAddr);
            ui->lineEdit_H->setVisible(false);
            ui->check_const_H->setCheckState(Qt::Unchecked);
            ui->btnAddr_const_H->setVisible(false);
        }
        if(pOldItem->m_Table.bVDynamicControl)
        {
            ui->m_Vnumberspin->setVisible(false);

            ui->lineEdit_V->setText(pOldItem->m_Table.addrVDynamic.sShowAddr);
            ui->lineEdit_V->setVisible(true);
            ui->check_const_V->setCheckState(Qt::Checked);
            ui->btnAddr_const_V->setVisible(true);
        }
        else
        {
            ui->m_Vnumberspin->setVisible(true);

            ui->lineEdit_V->setText(pOldItem->m_Table.addrVDynamic.sShowAddr);
            ui->lineEdit_V->setVisible(false);
            ui->check_const_V->setCheckState(Qt::Unchecked);
            ui->btnAddr_const_V->setVisible(false);
        }
        DrawTable();
        on_m_bordercheck_clicked();
    }
    bInitFlag = true;
}

void TableDlg::on_m_backcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_backcolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetBackColor(const QColor &)));
}

void TableDlg::on_m_bordercolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_bordercolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetBorderColor(const QColor &)));
}

void TableDlg::on_m_linecolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_linecolorbtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetLineColor(const QColor &)));
}

void TableDlg::on_m_TransparentspBox_valueChanged(int )
{
    if(!bInitFlag)
        return;
    pScene->clear();
    DrawTable();
}

void TableDlg::on_btnAddr_const_H_clicked()
{
    if(pOldItem == NULL)
    {
        return;
    }
    QString str = ui->lineEdit_H->text();
    AddressInputDialog dlg_readaddress(pOldItem->m_Table.addrHDynamic,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_H->setText(pOldItem->m_Table.addrHDynamic.sShowAddr);
    }
}

void TableDlg::on_btnAddr_const_V_clicked()
{
    if(pOldItem == NULL)
    {
        return;
    }
    QString str = ui->lineEdit_V->text();
    AddressInputDialog dlg_readaddress(pOldItem->m_Table.addrVDynamic,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_V->setText(pOldItem->m_Table.addrVDynamic.sShowAddr);
    }
}

void TableDlg::on_check_const_H_clicked()
{
    if(ui->check_const_H->isChecked())
    {
        ui->m_hnumberspin->setVisible(false);
        ui->btnAddr_const_H->setVisible(true);
        ui->lineEdit_H->setVisible(true);
//        if(pOldItem)
//        {
//            ui->lineEdit_H->setText(pOldItem->m_Table.addrHDynamic.sShowAddr);
//        }
    }
    else
    {
        ui->m_hnumberspin->setVisible(true);
        ui->btnAddr_const_H->setVisible(false);
        ui->lineEdit_H->setVisible(false);
    }
    pScene->clear();
    DrawTable();
}

void TableDlg::on_check_const_V_clicked()
{
    if(ui->check_const_V->isChecked())
    {
        ui->m_Vnumberspin->setVisible(false);
        ui->btnAddr_const_V->setVisible(true);
        ui->lineEdit_V->setVisible(true);
//        if(pOldItem)
//        {
//            ui->lineEdit_V->setText(pOldItem->m_Table.addrVDynamic.sShowAddr);
//        }
    }
    else
    {
        ui->m_Vnumberspin->setVisible(true);
        ui->btnAddr_const_V->setVisible(false);
        ui->lineEdit_V->setVisible(false);
    }
    pScene->clear();
    DrawTable();
}
