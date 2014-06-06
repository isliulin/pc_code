#include "qmessageshowone.h"

#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

qMessageShowOne::qMessageShowOne(QWidget *parent):QWidget(parent),ui(new Ui::qMessageShowOne)
{
    bInit = false;
    ui->setupUi(this);

    pwnd->OnAddPattern(ui->comboBox_style);

    ui->comboBox_dataType->addItem(tr("16λ������"));
    ui->comboBox_dataType->addItem(tr("32λ������"));

    ui->pushButton_waixing->hide();

    //stateCount  = 0;//��ǰ��״̬����
    m_curLan    = 0;//��ǰ����
    //curSta    = 0;//��ǰ��

    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//���һ������

    ui->comboBox_fontNmae->addItems(QFontDatabase().families(QFontDatabase::Any));

    ui->comboBox_move->addItem(tr("���ƶ�"));
    ui->comboBox_move->addItem(tr("�����ƶ�"));
    ui->comboBox_move->addItem(tr("�����ƶ�"));

    //��ʼ����������
    int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    QString str;
    if(ui->comboBox_lan->count() != 0)
    {
        ui->comboBox_lan->clear();
    }
    for(int i = 0; i < lanNum; i++)
    {
        str = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList[i];
        ui->comboBox_lan->addItem(str);
    }

    //bInit = true;
}

qMessageShowOne::~qMessageShowOne()
{
    delete ui;
}

void qMessageShowOne::Init(QMessageShowAttr* pItem)
{
    int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    m_vecMsg.clear();

    if(pItem)
    {
        curSta          = pItem->curSta;
        m_sShape        = pItem->m_sShape;
        m_bDataType     = pItem->m_bDataType;
        m_keyAddress    = pItem->m_keyAddress;
        m_nStateCount   = pItem->m_nStateCount;
        m_eRemove       = pItem->m_eRemove;          //�����
        m_nSpeed        = pItem->m_nSpeed;           //�ƶ��ٶ�
        m_nAlpha        = pItem->m_nAlpha;

        m_bFirstLanguage= pItem->m_bFirstLanguage;
        m_bStateZero    = pItem->m_bStateZero;

        m_vecMsg        = pItem->m_vecMsg;

        if(m_nStateCount != m_vecMsg.size())
        {
            m_nStateCount = m_vecMsg.size();
        }

        if(m_vecMsg[0].m_nVecPage2.size() != lanNum)//�����������ı䣬�������е�vector
        {
            if(m_vecMsg[0].m_nVecPage2.size() > lanNum)//��Ҫȥ��
            {
                int delNum = m_vecMsg[0].m_nVecPage2.size() - lanNum;
                int vecSize = m_vecMsg.size();
                for(int i = 0; i < vecSize; i++)
                {
                    for(int j = 0 ; j < delNum; j++)
                    {
                        m_vecMsg[i].m_nVecPage2.pop_back();
                    }
                }
            }
            else//��Ҫ����
            {
                int addNum = lanNum - m_vecMsg[0].m_nVecPage2.size();
                //int temp = m_vecMsg[0].m_nVecPage2.size();
                int vecSize = m_vecMsg.size();
                for(int i = 0; i < vecSize; i++)
                {
                    LanDiff lanItem;
                    for(int j = 0 ; j < addNum; j++)
                    {
                        lanItem.m_nStatusIndex  = i;
                        lanItem.m_nLanguage     = j;
                        lanItem.m_nFontColor    = QColor(0, 0, 0);
                        lanItem.m_nFontSize     = 10;
                        //lanItem.m_nSpeed        = 0;
                        lanItem.m_sStateMessage = QString::number(i);
                        //lanItem.m_eRemove       = 0;//���ƶ�
                        lanItem.m_sFontType     = tr("Droid Sans Fallback");//ui->comboBox_fontNmae->itemText(0);

                        m_vecMsg[i].m_nVecPage2.push_back(lanItem);
                    }
                }
            }
        }
    }
    else
    {
        curSta          = 0;
        m_sShape        = "";
        m_bDataType     = false;
        m_nStateCount   = 2;
        m_eRemove       = 0;          //�����
        m_nSpeed        = 5;          //�ƶ��ٶ�
        m_nAlpha        = 255;
        m_keyAddress.sPlcRegTypeStr = tr("LW");
        m_keyAddress.sShowAddr      = tr("LW0");
        m_keyAddress.nPlcRegTypeIndex = 1;
        m_keyAddress.sPlcAddrValue = "0";
        m_keyAddress.nConnectType = 0;

        m_bFirstLanguage= false;
        m_bStateZero    = false;

        QVector<LanDiff> vecLan;
        LanDiff lanItem;
        MsgProp msg;
        for(int i = 0; i < m_nStateCount; i++)
        {
            msg.m_nFrameColor   = QColor(224, 224, 224);
            msg.m_nForecolor    = QColor(0, 0, 0);
            msg.m_nBackcolor    = QColor(192, 192, 192);
            msg.m_nStyle        = 1;

            for(int j = 0; j < lanNum; j++)
            {
                lanItem.m_nStatusIndex  = i;
                lanItem.m_nLanguage     = j;
                lanItem.m_nFontColor    = QColor(0, 0, 0);
                lanItem.m_nFontSize     = 10;
                lanItem.m_sStateMessage = QString::number(i);
                lanItem.m_sFontType     = tr("Droid Sans Fallback");

                vecLan.push_back(lanItem);
            }

            msg.m_nVecPage2 = vecLan;
            vecLan.clear();
            m_vecMsg.push_back(msg);
            msg.m_nVecPage2.clear();
        }
    }

    //----------------------------����------------------------------
    ui->spinBox_total->setValue(m_nStateCount);//��״̬��
    if(m_bDataType)//�������
    {
        ui->comboBox_dataType->setCurrentIndex(1);
    }
    else
    {
        ui->comboBox_dataType->setCurrentIndex(0);
    }
    ui->lineEdit_addr->setText(m_keyAddress.sShowAddr);//���ӵ�ַ
    ui->comboBox_move->setCurrentIndex(m_eRemove);//�����
    if(0 == m_eRemove)
    {
        ui->label_9->hide();
        ui->spinBox->hide();
    }
    else
    {
        ui->label_9->show();
        ui->spinBox->show();
        ui->spinBox->setValue(m_nSpeed);//�ƶ��ٶ�
    }
    ui->spinBox_tran->setValue(m_nAlpha);

    //--------------------------״̬����-------------------------------
    ui->checkBox_state->setChecked(m_bStateZero);
    ui->spinBox_curNum->setMaximum(m_nStateCount - 1);
    ui->checkBox_lanFirst->setChecked(m_bFirstLanguage);
    if(m_bStateZero)//����״̬��0״̬��ͬ
    {
        curSta = 0;
        ui->spinBox_curNum->setValue(curSta);//��ǰ״̬
        ui->spinBox_curNum->setEnabled(false);//����0״̬��ͬ�������ֻ����0״̬

        ui->pushButton_frameColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[curSta].m_nFrameColor.name()));//�߿�ɫ
        ui->pushButton_foreColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[curSta].m_nForecolor.name()));//ǰ��ɫ
        ui->pushButton_bkColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[curSta].m_nBackcolor.name()));//����ɫ
        ui->comboBox_style->setCurrentIndex(m_vecMsg[curSta].m_nStyle);//��ʽ

        //--------------------------ԭ�ڶ�ҳ(��������)---------------------------
        if(m_bFirstLanguage)
        {
            m_curLan = 0;
            ui->comboBox_lan->setCurrentIndex(m_curLan);
            ui->comboBox_lan->setEnabled(false);

            ui->comboBox_lan->setCurrentIndex(m_curLan);
            ui->spinBox_fontSize->setValue(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontSize);
            ui->pushButton_fontColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontColor.name()));
            int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
            for(int i = 0; i < fontNum; i++)
            {
                if(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_sFontType == QFontDatabase().families(QFontDatabase::Any).at(i))
                {
                    ui->comboBox_fontNmae->setCurrentIndex(i);
                    break;
                }
            }
        }
        else
        {
            ui->comboBox_lan->setCurrentIndex(m_curLan);
            ui->comboBox_lan->setEnabled(true);

            ui->comboBox_lan->setCurrentIndex(m_curLan);
            ui->spinBox_fontSize->setValue(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontSize);
            ui->pushButton_fontColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontColor.name()));
            int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
            for(int i = 0; i < fontNum; i++)
            {
                if(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_sFontType == QFontDatabase().families(QFontDatabase::Any).at(i))
                {
                    ui->comboBox_fontNmae->setCurrentIndex(i);
                    break;
                }
            }
        }

        ui->comboBox_lan->setCurrentIndex(m_curLan);
        ui->spinBox_fontSize->setValue(m_vecMsg[0].m_nVecPage2[m_curLan].m_nFontSize);
        ui->pushButton_fontColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[0].m_nVecPage2[m_curLan].m_nFontColor.name()));
        int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
        for(int i = 0; i < fontNum; i++)
        {
            if(m_vecMsg[0].m_nVecPage2[m_curLan].m_sFontType == QFontDatabase().families(QFontDatabase::Any).at(i))
            {
                ui->comboBox_fontNmae->setCurrentIndex(i);
                break;
            }
        }
    }
    else
    {
        ui->spinBox_curNum->setValue(curSta);//��ǰ״̬
        ui->spinBox_curNum->setEnabled(true);//

        ui->pushButton_frameColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[curSta].m_nFrameColor.name()));//�߿�ɫ
        ui->pushButton_foreColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[curSta].m_nForecolor.name()));//ǰ��ɫ
        ui->pushButton_bkColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[curSta].m_nBackcolor.name()));//����ɫ
        ui->comboBox_style->setCurrentIndex(m_vecMsg[curSta].m_nStyle);//��ʽ

        //--------------------------ԭ�ڶ�ҳ(��������)---------------------------
        //ui->checkBox_lanFirst->setChecked(m_bFirstLanguage);
        if(m_bFirstLanguage)
        {
            m_curLan = 0;
            ui->comboBox_lan->setCurrentIndex(m_curLan);
            ui->comboBox_lan->setEnabled(false);

            ui->comboBox_lan->setCurrentIndex(m_curLan);
            ui->spinBox_fontSize->setValue(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontSize);
            ui->pushButton_fontColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontColor.name()));
            int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
            for(int i = 0; i < fontNum; i++)
            {
                if(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_sFontType == QFontDatabase().families(QFontDatabase::Any).at(i))
                {
                    ui->comboBox_fontNmae->setCurrentIndex(i);
                    break;
                }
            }
        }
        else
        {
            ui->comboBox_lan->setCurrentIndex(m_curLan);
            ui->comboBox_lan->setEnabled(true);

            ui->comboBox_lan->setCurrentIndex(m_curLan);
            ui->spinBox_fontSize->setValue(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontSize);
            ui->pushButton_fontColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontColor.name()));
            int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
            for(int i = 0; i < fontNum; i++)
            {
                if(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_sFontType == QFontDatabase().families(QFontDatabase::Any).at(i))
                {
                    ui->comboBox_fontNmae->setCurrentIndex(i);
                    break;
                }
            }
        }
    }

    //////////////////////////////////////��ʼ��״̬��////////////////////////////////////
    int num = m_vecMsg.size();
    ui->tableWidget->setRowCount(num);
    for(int i = 0; i < num; i++)
    {
        //�����
        QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::number(m_vecMsg[i].m_nVecPage2[m_curLan].m_nStatusIndex));
        ui->tableWidget->setItem(i, 0, newItem1);

        //����ı�
        QTableWidgetItem *newItem2 = new QTableWidgetItem(m_vecMsg[i].m_nVecPage2[m_curLan].m_sStateMessage);
        ui->tableWidget->setItem(i, 1, newItem2);
    }
    ui->plainTextEdit->setPlainText(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_sStateMessage);

    //emit changeCondition();
    bInit = true;
}

//-------------------------�����źŲ۴���-------------------------------
void qMessageShowOne::on_spinBox_total_valueChanged(int value)//��״̬��
{
    if(bInit == false)
    {
        return;
    }
    ui->tableWidget->setRowCount(value);

    if(m_nStateCount != value)
    {
        m_nStateCount = value;//�ı�״̬����

        if(ui->spinBox_curNum->value() >= m_nStateCount - 1)//�����ǰ��״̬����Ҫ��ɾ���Ļ�
        {
            curSta = m_nStateCount - 1;
            ui->spinBox_curNum->setValue(m_nStateCount - 1);
            ui->pushButton_frameColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[m_nStateCount - 1].m_nFrameColor.name()));
            ui->pushButton_foreColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[m_nStateCount - 1].m_nForecolor.name()));
            ui->pushButton_bkColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[m_nStateCount - 1].m_nBackcolor.name()));
            ui->comboBox_style->setCurrentIndex(m_vecMsg[m_nStateCount - 1].m_nStyle);

            //ԭ���ڶ�ҳ
            curSta = m_nStateCount - 1;
            ui->spinBox_fontSize->setValue(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontSize);
            ui->pushButton_fontColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontColor.name()));
            int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
            for(int i = 0; i < fontNum; i++)
            {
                if(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_sFontType == QFontDatabase().families(QFontDatabase::Any).at(i))
                {
                    ui->comboBox_fontNmae->setCurrentIndex(i);
                    break;
                }
            }
            ui->tableWidget->setCurrentItem(ui->tableWidget->item(curSta, 0));
            ui->plainTextEdit->setPlainText(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_sStateMessage);
        }

        int vecNum = m_vecMsg.size();
        int temp   = 0;
        if(vecNum > m_nStateCount)//��ǰVector�еı�����С��ɾ��һЩ
        {
            temp = vecNum - m_nStateCount;
            for(int i = 0; i < temp; i++)
            {
                m_vecMsg.pop_back();
                ui->tableWidget->removeRow(vecNum - 1 - i);
            }
        }
        else if(vecNum < m_nStateCount)
        {
            temp = m_nStateCount - vecNum;
            QVector<LanDiff> vecLan;
            LanDiff lanItem;
            MsgProp msg;
            if(m_bStateZero)//����״̬��0״̬
            {
                for(int i = 0; i < temp; i++)
                {
                    msg.m_nFrameColor   = m_vecMsg[0].m_nFrameColor;
                    msg.m_nForecolor    = m_vecMsg[0].m_nForecolor;
                    msg.m_nBackcolor    = m_vecMsg[0].m_nBackcolor;
                    msg.m_nStyle        = m_vecMsg[0].m_nStyle;

                    int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
                    if(m_bFirstLanguage)
                    {
                        for(int j = 0; j < lanNum; j++)
                        {
                            lanItem.m_nStatusIndex  = vecNum + i;
                            lanItem.m_nLanguage     = j;
                            lanItem.m_nFontColor    = m_vecMsg[0].m_nVecPage2[0].m_nFontColor;
                            lanItem.m_nFontSize     = m_vecMsg[0].m_nVecPage2[0].m_nFontSize;
                            lanItem.m_sStateMessage = QString::number(vecNum + i);
                            lanItem.m_sFontType     = m_vecMsg[0].m_nVecPage2[0].m_sFontType;
                            vecLan.push_back(lanItem);
                        }
                    }
                    else
                    {
                        for(int j = 0; j < lanNum; j++)
                        {
                            lanItem.m_nStatusIndex  = vecNum + i;
                            lanItem.m_nLanguage     = j;
                            lanItem.m_nFontColor    = QColor(0, 0, 0);
                            lanItem.m_nFontSize     = 10;
                            lanItem.m_sStateMessage = QString::number(vecNum + i);
                            lanItem.m_sFontType     = tr("Droid Sans Fallback");
                            vecLan.push_back(lanItem);
                        }
                    }
                    msg.m_nVecPage2 = vecLan;
                    vecLan.clear();
                    m_vecMsg.push_back(msg);
                    msg.m_nVecPage2.clear();

                    //�ӱ���//�����//����ı�
                    QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::number(m_vecMsg[vecNum + i].m_nVecPage2[m_curLan].m_nStatusIndex));
                    ui->tableWidget->setItem(vecNum + i, 0, newItem1);
                    QTableWidgetItem *newItem2 = new QTableWidgetItem(m_vecMsg[vecNum + i].m_nVecPage2[m_curLan].m_sStateMessage);
                    ui->tableWidget->setItem(vecNum + i, 1, newItem2);
                }
            }
            else
            {
                for(int i = 0; i < temp; i++)
                {
                    msg.m_nFrameColor   = QColor(224, 224, 224);
                    msg.m_nForecolor    = QColor(0, 0, 0);
                    msg.m_nBackcolor    = QColor(192, 192, 192);
                    msg.m_nStyle        = 1;

                    int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
                    if(m_bFirstLanguage)
                    {
                        for(int j = 0; j < lanNum; j++)
                        {
                            lanItem.m_nStatusIndex  = vecNum + i;
                            lanItem.m_nLanguage     = j;
                            lanItem.m_nFontColor    = m_vecMsg[0].m_nVecPage2[0].m_nFontColor;
                            lanItem.m_nFontSize     = m_vecMsg[0].m_nVecPage2[0].m_nFontSize;
                            lanItem.m_sStateMessage = QString::number(vecNum + i);
                            lanItem.m_sFontType     = m_vecMsg[0].m_nVecPage2[0].m_sFontType;
                            vecLan.push_back(lanItem);
                        }
                    }
                    else
                    {
                        for(int j = 0; j < lanNum; j++)
                        {
                            lanItem.m_nStatusIndex  = vecNum + i;
                            lanItem.m_nLanguage     = j;
                            lanItem.m_nFontColor    = QColor(0, 0, 0);
                            lanItem.m_nFontSize     = 10;
                            lanItem.m_sStateMessage = QString::number(vecNum + i);
                            lanItem.m_sFontType     = tr("Droid Sans Fallback");
                            vecLan.push_back(lanItem);
                        }
                    }
                    msg.m_nVecPage2 = vecLan;
                    vecLan.clear();
                    m_vecMsg.push_back(msg);
                    msg.m_nVecPage2.clear();

                    //�ӱ���//�����//����ı�
                    QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::number(m_vecMsg[vecNum + i].m_nVecPage2[m_curLan].m_nStatusIndex));
                    ui->tableWidget->setItem(vecNum + i, 0, newItem1);
                    QTableWidgetItem *newItem2 = new QTableWidgetItem(m_vecMsg[vecNum + i].m_nVecPage2[m_curLan].m_sStateMessage);
                    ui->tableWidget->setItem(vecNum + i, 1, newItem2);
                }
            }
        }

        ui->spinBox_curNum->setMaximum(m_nStateCount - 1);//����״̬����
    }

    emit changeCondition();
}

void qMessageShowOne::on_comboBox_dataType_currentIndexChanged(int index)//�������
{
    if(0 == index)
    {
        m_bDataType = false;
    }
    else
    {
        m_bDataType = true;
    }
}

void qMessageShowOne::on_lineEdit_addr_editingFinished()//���ӵ�ַ
{
//    if(bInit == false)
//    {
//        return;
//    }
//    if(!pwnd->IsAddressCheckRight(m_keyAddress, tr("���ӵ�ַ"), ui->lineEdit_addr, 1))
//    {
//        ui->lineEdit_addr->setText(m_keyAddress.sShowAddr);
//    }
}

void qMessageShowOne::on_pushButton_addr_clicked()//���ӵ�ַ��ť
{
    if(bInit == false)
    {
        return;
    }

    Keyboard key;
    QString str = ui->lineEdit_addr->text();
    AddressInputDialog dlg_readaddress(key,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_addr->setText(key.sShowAddr);
    }
    //AddressInputDialog dlg_readaddress(key,this);
    //dlg_readaddress.exec();
    //ui->lineEdit_addr->setText(key.sShowAddr);
    m_keyAddress = key;
}

void qMessageShowOne::on_comboBox_move_currentIndexChanged(int index)//�����
{
    if(bInit == false)
    {
        return;
    }

    m_eRemove = index;

    if(0 == index)
    {
        ui->label_9->hide();
        ui->spinBox->hide();
    }
    else
    {
        ui->label_9->show();
        ui->spinBox->show();
        ui->spinBox->setValue(m_nSpeed);
    }
}

void qMessageShowOne::on_spinBox_valueChanged(int value)//�ƶ��ٶ�
{
    if(bInit == false)
    {
        return;
    }

    m_nSpeed = value;
}

//------------------------------״̬���������źŲ۴���------------------------------------
void qMessageShowOne::on_spinBox_curNum_valueChanged(int value)//��ǰ״̬,��ʹ�þ�˵����������״̬����0״̬��ͬ
{
    if(bInit == false)
    {
        return;
    }

    curSta = value;

    ui->pushButton_frameColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[value].m_nFrameColor.name()));
    ui->pushButton_foreColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[value].m_nForecolor.name()));
    ui->pushButton_bkColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[value].m_nBackcolor.name()));
    ui->comboBox_style->setCurrentIndex(m_vecMsg[value].m_nStyle);

    if(m_bFirstLanguage)
    {
        m_curLan = 0;
        ui->comboBox_lan->setCurrentIndex(m_curLan);
        ui->comboBox_lan->setEnabled(false);

        ui->comboBox_lan->setCurrentIndex(m_curLan);
        ui->spinBox_fontSize->setValue(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontSize);
        ui->pushButton_fontColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontColor.name()));
        int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
        for(int i = 0; i < fontNum; i++)
        {
            if(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_sFontType == QFontDatabase().families(QFontDatabase::Any).at(i))
            {
                ui->comboBox_fontNmae->setCurrentIndex(i);
                break;
            }
        }
    }
    else
    {
        ui->comboBox_lan->setCurrentIndex(m_curLan);
        ui->comboBox_lan->setEnabled(true);

        ui->comboBox_lan->setCurrentIndex(m_curLan);
        ui->spinBox_fontSize->setValue(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontSize);
        ui->pushButton_fontColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontColor.name()));
        int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
        for(int i = 0; i < fontNum; i++)
        {
            if(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_sFontType == QFontDatabase().families(QFontDatabase::Any).at(i))
            {
                ui->comboBox_fontNmae->setCurrentIndex(i);
                break;
            }
        }
    }

    ui->tableWidget->setCurrentItem(ui->tableWidget->item(curSta, 1));
    ui->plainTextEdit->setPlainText(m_vecMsg[curSta].m_nVecPage2[m_curLan].m_sStateMessage);
    ui->plainTextEdit->selectAll();
    ui->plainTextEdit->setFocus();

    emit changeCondition();
}

void qMessageShowOne::on_pushButton_frameColor_clicked()//�߿�ɫ
{
    if(bInit == false)
    {
        return;
    }
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_frameColor ,colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_frameColor(const QColor &)));
}

void qMessageShowOne::set_pushButton_frameColor(const QColor & mColor)//�߿�ɫ�źŲ�
{
    if(bInit == false)
    {
        return;
    }
    ui->pushButton_frameColor->setStyleSheet(QString("background:%1").arg(mColor.name()));

    if(m_bStateZero)
    {
        for(int i = 0; i < m_nStateCount; i++)
        {
            m_vecMsg[i].m_nFrameColor = mColor;
        }
    }
    else
    {
        m_vecMsg[ui->spinBox_curNum->value()].m_nFrameColor = mColor;
    }

    emit changeCondition();
}

void qMessageShowOne::on_pushButton_foreColor_clicked()//ǰ��ɫ
{
    if(bInit == false)
    {
        return;
    }
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_foreColor ,colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_foreColor(const QColor &)));
}

void qMessageShowOne::set_pushButton_foreColor(const QColor & mColor)//ǰ��ɫ�źŲ�
{
    if(bInit == false)
    {
        return;
    }
    ui->pushButton_foreColor->setStyleSheet(QString("background:%1").arg(mColor.name()));

    if(m_bStateZero)
    {
        for(int i = 0; i < m_nStateCount; i++)
        {
            m_vecMsg[i].m_nForecolor = mColor;
        }
    }
    else
    {
        m_vecMsg[ui->spinBox_curNum->value()].m_nForecolor = mColor;
    }

    emit changeCondition();
}

void qMessageShowOne::on_pushButton_bkColor_clicked()//����ɫ
{
    if(bInit == false)
    {
        return;
    }
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_bkColor ,colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_bkColor(const QColor &)));
}

void qMessageShowOne::set_pushButton_bkColor(const QColor & mColor)//����ɫ�źŲ�
{
    if(bInit == false)
    {
        return;
    }
    ui->pushButton_bkColor->setStyleSheet(QString("background:%1").arg(mColor.name()));

    if(m_bStateZero)
    {
        for(int i = 0; i < m_nStateCount; i++)
        {
            m_vecMsg[i].m_nForecolor = mColor;
        }
    }
    else
    {
        m_vecMsg[ui->spinBox_curNum->value()].m_nBackcolor = mColor;
    }

    emit changeCondition();
}

void qMessageShowOne::on_comboBox_style_currentIndexChanged(int index)//��ʽ
{
    if(bInit == false)
    {
        return;
    }

    if(m_bStateZero)
    {
        for(int i = 0; i < m_nStateCount; i++)
        {
            m_vecMsg[i].m_nStyle = index;
        }
    }
    else
    {
        m_vecMsg[ui->spinBox_curNum->value()].m_nStyle = index;
    }

    emit changeCondition();
}

//����״̬ʹ�õ�һ�����ܵ����//��������ʹ�õ�һ�ֲ��ܵ��
void qMessageShowOne::on_comboBox_lan_currentIndexChanged(int index)//��ǰ����
{
    if(bInit == false)
    {
        return;
    }

    m_curLan = index;

    ui->spinBox_fontSize->setValue(m_vecMsg[curSta].m_nVecPage2[index].m_nFontSize);
    ui->pushButton_fontColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[curSta].m_nVecPage2[index].m_nFontColor.name()));
    int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
    for(int i = 0; i < fontNum; i++)
    {
        if(m_vecMsg[curSta].m_nVecPage2[index].m_sFontType == QFontDatabase().families(QFontDatabase::Any).at(i))
        {
            ui->comboBox_fontNmae->setCurrentIndex(i);
            break;
        }
    }

    int k  = ui->tableWidget->rowCount();
    for(int i = 0; i < k; i++)
    {
        ui->tableWidget->item(i, 1)->setText(m_vecMsg[i].m_nVecPage2[index].m_sStateMessage);
    }

    ui->plainTextEdit->setPlainText(m_vecMsg[curSta].m_nVecPage2[index].m_sStateMessage);

    emit changeCondition();
}

void qMessageShowOne::on_comboBox_fontNmae_currentIndexChanged(int index)//��������
{
    if(bInit == false)
    {
        return;
    }

    QString str = ui->comboBox_fontNmae->currentText();

    if(m_bStateZero)
    {
        for(int i = 0; i < m_nStateCount; i++)
        {
            if(m_bFirstLanguage)//�������������ʱ��m_curLan�϶�Ϊ0
            {
                int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
                for(int j = 0; j < lanNum; j++)
                {
                    m_vecMsg[curSta].m_nVecPage2[j].m_sFontType = str;
                }
            }
            else
            {
                m_vecMsg[curSta].m_nVecPage2[m_curLan].m_sFontType = str;
            }
        }
    }
    else
    {
        if(m_bFirstLanguage)//�������������ʱ��m_curLan�϶�Ϊ0
        {
            int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
            for(int j = 0; j < lanNum; j++)
            {
                m_vecMsg[curSta].m_nVecPage2[j].m_sFontType = str;
            }
        }
        else
        {
            m_vecMsg[curSta].m_nVecPage2[m_curLan].m_sFontType = str;
        }
    }

    emit changeCondition();
}

void qMessageShowOne::on_spinBox_fontSize_valueChanged(int value)//�����С
{
    if(bInit == false)
    {
        return;
    }

    if(m_bStateZero)
    {
        for(int i = 0; i < m_nStateCount; i++)
        {
            if(m_bFirstLanguage)//�������������ʱ��m_curLan�϶�Ϊ0
            {
                int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
                for(int j = 0; j < lanNum; j++)
                {
                    m_vecMsg[curSta].m_nVecPage2[j].m_nFontSize = value;
                }
            }
            else
            {
                m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontSize = value;
            }
        }
    }
    else
    {
        if(m_bFirstLanguage)//�������������ʱ��m_curLan�϶�Ϊ0
        {
            int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
            for(int j = 0; j < lanNum; j++)
            {
                m_vecMsg[curSta].m_nVecPage2[j].m_nFontSize = value;
            }
        }
        else
        {
            m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontSize = value;
        }
    }

    emit changeCondition();
}

void qMessageShowOne::on_pushButton_fontColor_clicked()//������ɫ
{
    if(bInit == false)
    {
        return;
    }

    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_fontColor ,colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_fontColor(const QColor &)));
}

void qMessageShowOne::set_pushButton_fontColor(const QColor & mColor)//������ɫ�źŲ�
{
    ui->pushButton_fontColor->setStyleSheet(QString("background:%1").arg(mColor.name()));

    if(m_bStateZero)
    {
        for(int i = 0; i < m_nStateCount; i++)
        {
            if(m_bFirstLanguage)//�������������ʱ��m_curLan�϶�Ϊ0
            {
                int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
                for(int j = 0; j < lanNum; j++)
                {
                    m_vecMsg[curSta].m_nVecPage2[j].m_nFontColor = mColor;
                }
            }
            else
            {
                m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontColor = mColor;
            }
        }
    }
    else
    {
        if(m_bFirstLanguage)//�������������ʱ��m_curLan�϶�Ϊ0
        {
            int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
            for(int j = 0; j < lanNum; j++)
            {
                m_vecMsg[curSta].m_nVecPage2[j].m_nFontColor = mColor;
            }
        }
        else
        {
            m_vecMsg[curSta].m_nVecPage2[m_curLan].m_nFontColor = mColor;
        }
    }

    emit changeCondition();
}

//--------------------�������ԣ�״̬��ʹ�õ�һ�֣����Σ�����״̬��---------------------
void qMessageShowOne::on_pushButton_waixing_clicked()//����
{
    //��ʱ����
}

void qMessageShowOne::on_checkBox_lanFirst_clicked(bool checked)//�Ƿ�ȫʹ�õ�һ������
{
    if(bInit == false)
    {
        return;
    }

    m_bFirstLanguage = checked;

    if(checked)
    {
        m_curLan = 0;

        //�޸�����
        int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
        for(int i = 0; i < m_nStateCount; i++)
        {
            for(int j = 1; j < lanNum; j++)
            {
                m_vecMsg[i].m_nVecPage2[j].m_sFontType  = m_vecMsg[i].m_nVecPage2[0].m_sFontType;
                m_vecMsg[i].m_nVecPage2[j].m_nFontSize  = m_vecMsg[i].m_nVecPage2[0].m_nFontSize;
                //m_vecMsg[i].m_nVecPage2[j].m_eRemove    = m_vecMsg[i].m_nVecPage2[0].m_eRemove;
                m_vecMsg[i].m_nVecPage2[j].m_nFontColor = m_vecMsg[i].m_nVecPage2[0].m_nFontColor;
            }
        }

        //�޸�UI
        ui->comboBox_lan->setCurrentIndex(m_curLan);
        ui->spinBox_fontSize->setValue(m_vecMsg[curSta].m_nVecPage2[0].m_nFontSize);
        ui->pushButton_fontColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[curSta].m_nVecPage2[0].m_nFontColor.name()));
        int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
        for(int i = 0; i < fontNum; i++)
        {
            if(m_vecMsg[curSta].m_nVecPage2[0].m_sFontType == QFontDatabase().families(QFontDatabase::Any).at(i))
            {
                ui->comboBox_fontNmae->setCurrentIndex(i);
                break;
            }
        }
        ui->plainTextEdit->setPlainText(m_vecMsg[curSta].m_nVecPage2[0].m_sStateMessage);
        ui->comboBox_lan->setEnabled(false);
    }
    else
    {
        ui->comboBox_lan->setEnabled(true);
    }

    emit changeCondition();
}

void qMessageShowOne::on_checkBox_state_clicked(bool checked)//�Ƿ�ȫʹ�õ�һ��״̬
{
    if(bInit == false)
    {
        return;
    }

    m_bStateZero = checked;

    if(checked)
    {
        //���ݵĸı�
        int totalStatus = m_vecMsg.size();
        for(int i = 0; i < totalStatus; i++)
        {
            m_vecMsg[i].m_nBackcolor  = ui->pushButton_bkColor->palette().background().color();
            m_vecMsg[i].m_nForecolor  = ui->pushButton_foreColor->palette().background().color();
            m_vecMsg[i].m_nFrameColor = ui->pushButton_frameColor->palette().background().color();
            m_vecMsg[i].m_nStyle      = ui->comboBox_style->currentIndex();

            int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
            for(int j = 0; j < lanNum; j++)
            {
                m_vecMsg[i].m_nVecPage2[j].m_sFontType  = m_vecMsg[0].m_nVecPage2[j].m_sFontType;
                m_vecMsg[i].m_nVecPage2[j].m_nFontSize  = m_vecMsg[0].m_nVecPage2[j].m_nFontSize;
                m_vecMsg[i].m_nVecPage2[j].m_nFontColor = m_vecMsg[0].m_nVecPage2[j].m_nFontColor;
            }
        }

        //UI�ĸı�
        ui->spinBox_fontSize->setValue(m_vecMsg[0].m_nVecPage2[m_curLan].m_nFontSize);
        ui->pushButton_fontColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[0].m_nVecPage2[m_curLan].m_nFontColor.name()));
        int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
        for(int i = 0; i < fontNum; i++)
        {
            if(m_vecMsg[0].m_nVecPage2[m_curLan].m_sFontType == QFontDatabase().families(QFontDatabase::Any).at(i))
            {
                ui->comboBox_fontNmae->setCurrentIndex(i);
                break;
            }
        }

        ui->spinBox_curNum->setEnabled(false);
        ui->spinBox_curNum->setValue(0);
    }
    else
    {
        ui->spinBox_curNum->setEnabled(true);
        //int k = ui->tableWidget->currentRow();
        ui->spinBox_curNum->setValue(ui->tableWidget->currentRow());
    }

    emit changeCondition();
}

void qMessageShowOne::on_tableWidget_cellClicked(int row, int column)//����ѡ��ĳ��״̬
{
    if(bInit == false)
    {
        return;
    }

    curSta = row;

    if(m_bStateZero)
    {
        ui->spinBox_curNum->setValue(0);
    }
    else
    {
        ui->spinBox_curNum->setValue(row);
    }

    ui->pushButton_frameColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[row].m_nFrameColor.name()));
    ui->pushButton_foreColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[row].m_nForecolor.name()));
    ui->pushButton_bkColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[row].m_nBackcolor.name()));
    ui->comboBox_style->setCurrentIndex(m_vecMsg[row].m_nStyle);

    ui->spinBox_fontSize->setValue(m_vecMsg[row].m_nVecPage2[m_curLan].m_nFontSize);
    ui->pushButton_fontColor->setStyleSheet(QString("background:%1").arg(m_vecMsg[row].m_nVecPage2[m_curLan].m_nFontColor.name()));
    int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
    for(int i = 0; i < fontNum; i++)
    {
        if(m_vecMsg[row].m_nVecPage2[m_curLan].m_sFontType == QFontDatabase().families(QFontDatabase::Any).at(i))
        {
            ui->comboBox_fontNmae->setCurrentIndex(i);
            break;
        }
    }

    ui->plainTextEdit->setPlainText(m_vecMsg[row].m_nVecPage2[m_curLan].m_sStateMessage);
    ui->plainTextEdit->selectAll();
    ui->plainTextEdit->setFocus();

    emit changeCondition();
}

void qMessageShowOne::on_plainTextEdit_textChanged()//�޸ĵ�ǰ״̬�ı�����
{
    if(bInit == false)
    {
        return;
    }

    QString str = ui->plainTextEdit->toPlainText();
    m_vecMsg[curSta].m_nVecPage2[m_curLan].m_sStateMessage = str;
    ui->tableWidget->item(curSta, 1)->setText(str);

    emit changeCondition();
}

void qMessageShowOne::on_spinBox_tran_valueChanged(int value)
{
    if(bInit == false)
    {
        return;
    }

    this->m_nAlpha = value;
    emit changeCondition();
}
