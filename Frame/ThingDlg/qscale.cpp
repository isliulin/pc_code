#include "qscale.h"
#include "ui_qscale.h"
#include "ui_scalesdlg.h"
#include "view/calibrationitem.h"
#include "Frame/ThingDlg/scalesdlg.h"
#include "Frame\MainWindow.h"

extern MainWindow *pwnd;
qScale::qScale(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qScale)
{
    ui->setupUi(this);
    oId = -1;
    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    pScene = new QGraphicsScene(this);
    ui->MainView->setScene(pScene);
    ui->MainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QGraphicsItem *Item;
    pGeneralDlg = new ScalesDlg;
    ui->tabWidget->addTab(pGeneralDlg, tr("�������"));
    pSecurity = new SecurityWidget(this);
    ui->tabWidget->addTab(pSecurity, tr("Ȩ������"));
    pSecurity->setGroupVVisible(false);
    pSecurity->setTouchGroupEnabled(false);

    connect(pGeneralDlg, SIGNAL(DrawScales()),this, SLOT(onDrawScales()));
    if(pItem)
    {
        Item = dynamic_cast<CalibrationItem *> (pItem)->Clone();
        pGeneralDlg->DoubleClickInit(dynamic_cast<CalibrationItem *> (Item));//���
        CalibrationItem* pCalibration = dynamic_cast<CalibrationItem*>(pItem);
        if(pCalibration)
        {
            pSecurity->init(pCalibration);
        }
        pScene->clear();
        onDrawScales();
        oId = dynamic_cast<CalibrationItem *> (Item)->id();
        ui->spinBox->setValue(oId);
    }
    else
    {
        pGeneralDlg->InitParament();
        pSecurity->init(0);
        pScene->clear();
        onDrawScales();
        ui->spinBox->setValue(pwnd->getNewId());
    }
    this->setWindowTitle(tr("�̶�"));
}

qScale::~qScale()
{
    if(pGeneralDlg)
    {
        delete pGeneralDlg;
        pGeneralDlg=NULL;
    }
    delete ui;
}

bool qScale::on_accept_clicked()
{
    //��Сֵ���ܴ������ֵ
    if(pGeneralDlg->ui->m_minedit->text().toDouble()>pGeneralDlg->ui->m_maxedit->text().toDouble()){
        QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("��Сֵ���ܴ������ֵ"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
        box.exec();
        pGeneralDlg->ui->m_minedit->setFocus();
        pGeneralDlg->ui->m_minedit->selectAll();
        return false;
    }
    onDrawScales();
    pGeneralDlg->SaveGeneralPage(caliInfo);
    this->pCopyItem->onSaveCalibration(caliInfo);
    if(pSecurity->Save())
    {
        //pGeneralDlg->pCopyItem->SaveSecurityPro(&(pSecurity->sproperty));
        this->pCopyItem->SaveSecurityPro(&(pSecurity->sproperty));
    }
    else
    {
        return false;
    }
    pCopyItem->setId(ui->spinBox->value());

    if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID�ظ������޸�ID��"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox->setFocus();
        return false;
    }

    accept();
}

void qScale::on_cancel_clicked()
{
    this->close();
}

void qScale::on_help_clicked()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_CALIBRATION);
}

void qScale::onDrawScales()
{
    pScene->clear();
    QColor mLineColor =  pGeneralDlg->ui->m_linecolorbtn->palette().background().color();           //������ɫ
    int nDirection = pGeneralDlg->pDirection->checkedId();               //����
    int nMain = pGeneralDlg->ui->m_mainspin->value();                     //���̶�
    int nSub = pGeneralDlg->ui->m_subspin->value();                       //�ο̶�
    bool bShowText = pGeneralDlg->ui->m_showtextcheck->isChecked();       //�Ƿ������ı�
    QPainterPath mPath;               //�����ߵ�path
    double mMoveX = 0;                //���̶�X��ʼ��
    double mMoveY = 0;                //���̶�Y��ʼ��
    //double  = 0;                //���̶�X��ʼ��
    double mLineY = 0;                //���̶�Y��ʼ��
    double mLineX = 0;
    CalibrationItem *pGroup = new CalibrationItem;
    QLineItem *pLine;
    //int WH = 160;
    int i = 0;
    double MainSpace = 100.0/(nMain-1);               //���̶ȼ��
    double SubSpace = 100.0/((nSub+1)*(nMain-1)); //�ο̶ȼ��
    double ML = 25;                                  //���̶��ߵĳ���int
    int nVal = (nSub+1)*(nMain-1);
    QSimpleTextItem *pText;
    QString sText = "";
    QRectF rect(QPointF(0,0), QSize(30,30));
    int nH = 0;
    double nL = 50; //int

    /**********************************************************************
     *�����ǻ�����
     *********************************************************************/
    if(nDirection == 1 || nDirection == 2) //���������������
    {
        mMoveX = nL;
        mMoveY = 0;
        mLineX = nL;
        mLineY = 100;
    }
    else if(nDirection == 3 || nDirection == 4) //�������ϻ�������
    {
        mMoveX = 0;
        mMoveY = nL;
        mLineX = 100;
        mLineY = nL;
    }
    mPath.moveTo(mMoveX,mMoveY);
    mPath.lineTo(mLineX,mLineY);
    pLine = new QLineItem(mPath);
    pLine->setLineColor(mLineColor); //������ɫ
    pLine->SetName(tr("MainLine"));
    pGroup->addToGroup(pLine);

    /**********************************************************************
     *�����ǻ����̶ȡ��ο̶�
     *********************************************************************/

        switch(nDirection)
        {
        case 1://��������
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mMoveX = -ML+nL;
                mMoveY = i*MainSpace;
                mLineX = +nL;
                mLineY = i*MainSpace;
                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mLineColor); //������ɫ
                pLine->SetName(QString("MLine%1").arg(i));
                pGroup->addToGroup(pLine);

                if(bShowText)
                {
                    sText = GetText(i);
                    pText = new QSimpleTextItem(rect,sText);
                    nH = GetTextLength(sText,pText);
                    if(pGeneralDlg->ui->m_fontsizecmb->currentIndex()>10)
                        pText = DrawText(pText,i,mMoveX-nH-4-7,mLineY-9,sText);
                    else
                        pText = DrawText(pText,i,mMoveX-nH-4-7,mLineY-8,sText);
                    pGroup->addToGroup(pText);
                }
            }

            for(i = 1; i < nVal;i++) //���ο̶�
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mMoveX = -ML/2+nL;
                    mMoveY = i*SubSpace;
                    mLineX = nL;
                    mLineY = i*SubSpace;
                    mPath.moveTo(mMoveX,mMoveY);
                    mPath.lineTo(mLineX,mLineY);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mLineColor); //������ɫ
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
        case 2://��������
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mMoveX = nL;
                mMoveY = i*MainSpace;
                mLineX = ML+nL;
                mLineY = i*MainSpace;
                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mLineColor); //������ɫ
                pLine->SetName(QString("SubLine%1").arg(i));
                pGroup->addToGroup(pLine);

                if(bShowText)
                {
                    sText = GetText(i);
                    pText = new QSimpleTextItem(rect,sText);
                    if(pGeneralDlg->ui->m_fontsizecmb->currentIndex()>10)
                        pText = DrawText(pText,i,mLineX+2+7,mLineY-9,sText);
                    else
                        pText = DrawText(pText,i,mLineX+2+7,mLineY-8,sText);
                    pGroup->addToGroup(pText);
                }
            }
            for(i = 1; i < nVal;i++) //���ο̶�
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mMoveX = nL;
                    mMoveY = i*SubSpace;
                    mLineX = ML/2+nL;
                    mLineY = i*SubSpace;
                    mPath.moveTo(mMoveX,mMoveY);
                    mPath.lineTo(mLineX,mLineY);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mLineColor); //������ɫ
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
        case 3://��������
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mMoveX = i*MainSpace;
                mMoveY = -ML+nL;
                mLineX = i*MainSpace;
                mLineY = nL;
                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mLineColor); //������ɫ
                pLine->SetName(QString("SubLine%1").arg(i));
                pGroup->addToGroup(pLine);

                if(bShowText)
                {
                    sText = GetText(i);
                    pText = new QSimpleTextItem(rect,sText);
                    nH = GetTextLength(sText,pText);
                    pText = DrawText(pText,i,mMoveX-nH/2-2,mMoveY-16,sText);
                    pGroup->addToGroup(pText);
                }
            }
            for(i = 1; i < nVal;i++) //���ο̶�
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mMoveX = i*SubSpace;
                    mMoveY = -ML/2+nL;
                    mLineX = i*SubSpace;
                    mLineY = nL;
                    mPath.moveTo(mMoveX,mMoveY);
                    mPath.lineTo(mLineX,mLineY);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mLineColor); //������ɫ
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
        case 4://��������
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mMoveX = i*MainSpace;
                mMoveY = nL;
                mLineX = i*MainSpace;
                mLineY = ML+nL;
                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mLineColor); //������ɫ
                pLine->SetName(QString("SubLine%1").arg(i));
                pGroup->addToGroup(pLine);

                if(bShowText)
                {
                    sText = GetText(i);
                    pText = new QSimpleTextItem(rect,sText);
                    nH = GetTextLength(sText,pText);
                    pText = DrawText(pText,i,mLineX-nH/2-2,mLineY+4,sText);
                    pGroup->addToGroup(pText);
                }
            }
            for(i = 1; i < nVal;i++) //���ο̶�
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mMoveX = i*SubSpace;
                    mMoveY = nL;
                    mLineX = i*SubSpace;
                    mLineY = ML/2+nL;
                    mPath.moveTo(mMoveX,mMoveY);
                    mPath.lineTo(mLineX,mLineY);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mLineColor); //������ɫ
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
         default:
                break;

        } //end switch
    //end if
        pCopyItem=pGroup;

        pScene->addItem(pCopyItem);        //��ӵ�����
        pCopyItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pCopyItem->setFlag(QGraphicsItem::ItemIsMovable, false);

}

QSimpleTextItem* qScale::DrawText(QSimpleTextItem *pText, int nIndex,
                                     double LineX, double LineY,QString sText)
{
    int nFontSize = pGeneralDlg->ui->m_fontsizecmb->currentText().toInt();//�����С
    QColor mTextColor = pGeneralDlg->ui->m_textcolorbtn ->palette().background().color();             //�ı���ɫ
    QString sName = "";

    pText->SetFontSize(nFontSize);
    QFont nfont = pText->GetTextFont(); //�����ı����Ĵ�С
    nfont.setPointSize(nFontSize);
    QFontMetrics fontM(nfont);
    QRect rc = fontM.boundingRect(sText);

    QRectF rect(QPointF(0,0), QSize(50,50));
    rect.setSize(QSize(rc.width()+5,rc.height()));
    pText->setRect(rect);

   int nDirection = pGeneralDlg->pDirection->checkedId();                //����
    if(nDirection == 1)
    {
        pText->SetTextAlign(6);
    }
    else if(nDirection == 2)
    {
        pText->SetTextAlign(4);
    }
    else
    {
        pText->SetTextAlign(5);
    }

    pText->setPos(LineX,LineY);

    pText->SetFontColor(mTextColor);
    sName = QString("%1").arg(nIndex);
    sName = "Txt"+sName;
    pText->SetName(sName);
    pText->SetRectOutLine(false);
    return pText;
}

QString qScale::GetText(int nIndex)
{
    double Min = pGeneralDlg->ui->m_minedit->text().toDouble();           //��Сֵ
    double Max = pGeneralDlg->ui->m_maxedit->text().toDouble();           //���ֵ
    int nMain = pGeneralDlg->ui->m_mainspin->value();                     //���̶�
    int nTextDirection = pGeneralDlg->ui->m_textdirectioncmb->currentIndex();//�ı�����
    int nPointNum = pGeneralDlg->ui->m_pointnumcmb->currentText().toInt();//С��λ��

    double mValue = (Max - Min) / (nMain - 1);
    double dVal = 0;
    QString sText = "";

    if(nTextDirection == 0) //�ı�����
    {
        dVal = Max - mValue*nIndex;
        if(nIndex == nMain-1)
            dVal = Min;
    }
    else                   //�ı�����
    {
        dVal = Min + mValue*nIndex;
        if(nIndex == nMain-1)
            dVal = Max;
    }

    if(dVal == -0)
        dVal = 0;
    sText.sprintf("%.0f", dVal);
    QString sTemp = "";
    if(nPointNum != 0)
    {
        sTemp = sText.left(1);
        if(sTemp == "-") //�Ǹ�����ʱ��
        {
            sTemp = sText.right(sText.length()-1); //ȡ��ȥ���ŵ�����
            while(sTemp.length()-nPointNum <= 0)
                  sTemp = "0"+sTemp;
              sTemp = sTemp.insert(sTemp.length()-nPointNum,".");
              sText = "-"+sTemp;
        }
        else
        {
               while(sText.length()-nPointNum <= 0)
                     sText = "0"+sText;
                 sText = sText.insert(sText.length()-nPointNum,".");
        }
    }
    bool ok = false;
    float temp = sText.toFloat(&ok);
    if(ok)
    {
        if(temp < 0.001 && temp > -0.001)
            sText = "0";
    }
    return sText;
}

int qScale::GetTextLength(QString sText,QSimpleTextItem* pText)
{
    int nFontSize = pGeneralDlg->ui->m_fontsizecmb->currentText().toInt();//�����С
    QFont nfont = pText->GetTextFont(); //�����ı����Ĵ�С
    nfont.setPointSize(nFontSize);
    QFontMetrics fontM(nfont);
    QRect rc = fontM.boundingRect(sText);
    return rc.width();
}
