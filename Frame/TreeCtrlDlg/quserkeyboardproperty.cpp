#include "quserkeyboardproperty.h"
#include  "Frame\mainwindow.h"
#include <QString>
extern  MainWindow *pwnd;

QUserKeyboardProperty::QUserKeyboardProperty(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::QUserKeyboardProperty)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
    pwnd->OnAddPattern(ui->newscreen_style_combobox);
    ui->newscreen_silence_radiobutton->setChecked(true);
    ui->newscreen_pushButton_bk->setVisible(true);
    ui->newscreen_pushButton_frontcolor->setVisible(true);
    ui->newscreen_style_combobox->setVisible(true);
    ui->newscreen_style_combobox->setCurrentIndex(1);
    ui->newscreen_picture_lineedit->setVisible(false);
    ui->newscreen_picture_lineedit->setText("");
    ui->newscreen_picture_pushButton->setVisible(false);
    R_BackGaound_Group = new QButtonGroup(this);
    R_BackGaound_Group->addButton(ui->newscreen_silence_radiobutton,0);
    R_BackGaound_Group->addButton(ui->newscreen_picture_radiobutton,1);
    ui->Width->setRange(100,pwnd->m_pSamSysParame->m_projectProp.nSceneWidth);
    ui->high->setRange(100,pwnd->m_pSamSysParame->m_projectProp.nSceneHeight);
    QRegExp regExp("[^:]{0,50}");
    QValidator *validator = new QRegExpValidator(regExp,this);
    ui->sUserKeyboardName->setValidator(validator);
    init();
    this->setWindowTitle(tr("�Զ������"));
}

QUserKeyboardProperty::~QUserKeyboardProperty()
{
    delete ui;
}
void QUserKeyboardProperty::init()
{
    ui->Width->setValue(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->width());//���
    ui->high->setValue(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->height());//�߶�
    ui->sUserKeyboardName->setText(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName);//�Զ����������
    R_BackGaound_Group->button(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSelectType)->setChecked(true);
    ui->newscreen_picture_lineedit->setText(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_picturePath);
    ui->newscreen_pushButton_bk->setStyleSheet( QString("background:%1").arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneBackColor.name()));
    ui->newscreen_pushButton_frontcolor->setStyleSheet(QString("background:%1").arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneStyleColor.name()));
    ui->newscreen_style_combobox->setCurrentIndex(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nPattern);
    on_newscreen_picture_radiobutton_clicked();
    on_newscreen_silence_radiobutton_clicked();
}
void QUserKeyboardProperty::on_newscreen_pushButton_bk_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->newscreen_pushButton_bk,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setCurrentBKColor(const QColor &)));
}

void QUserKeyboardProperty::on_newscreen_pushButton_frontcolor_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->newscreen_pushButton_frontcolor ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setCurrentFrontColor(const QColor &)));
}

void  QUserKeyboardProperty::setCurrentBKColor(const QColor & currentColor)
{
    ui->newscreen_pushButton_bk->setStyleSheet(QString("background:%1").arg(currentColor.name()));
}
void  QUserKeyboardProperty::setCurrentFrontColor(const QColor & currentColor)
{
    ui->newscreen_pushButton_frontcolor->setStyleSheet(QString("background:%1").arg(currentColor.name()));
}

void QUserKeyboardProperty::on_newscreen_picture_pushButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, tr("Open File"),"/home",
                                                  tr("Images (*.png *.jpeg *.jpg *.bmp)"));
    ui->newscreen_picture_lineedit->setText(filename);
}

void QUserKeyboardProperty::on_newscreen_silence_radiobutton_clicked()
{
    if(ui->newscreen_silence_radiobutton->isChecked())
    {
        ui->label_bk->setVisible(true);
        ui->label_frontcolor->setVisible(true);
        ui->label_style->setVisible(true);

        ui->newscreen_pushButton_bk->setVisible(true);
        ui->newscreen_pushButton_frontcolor->setVisible(true);
        ui->newscreen_style_combobox->setVisible(true);

        ui->newscreen_picture_lineedit->setVisible(false);
        ui->newscreen_picture_pushButton->setVisible(false);
    }
}

void QUserKeyboardProperty::on_newscreen_picture_radiobutton_clicked()
{
    if(ui->newscreen_picture_radiobutton->isChecked())
    {
        ui->label_bk->setVisible(false);
        ui->label_frontcolor->setVisible(false);
        ui->label_style->setVisible(false);

        ui->newscreen_pushButton_bk->setVisible(false);
        ui->newscreen_pushButton_frontcolor->setVisible(false);
        ui->newscreen_style_combobox->setVisible(false);

        ui->newscreen_picture_lineedit->setVisible(true);
        ui->newscreen_picture_pushButton->setVisible(true);
    }
}
void QUserKeyboardProperty::on_Accept_clicked()
{
    QMessageBox box(QMessageBox::Warning,PRO_FULL_NAME,tr("�Զ�����̲���Ϊ�գ�"),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
    if(ui->sUserKeyboardName->text()=="")
    {
        box.exec();
        ui->sUserKeyboardName->setFocus(Qt::ActiveWindowFocusReason);
        return;
    }

    if(ui->newscreen_picture_radiobutton->isChecked())
    {
        if(ui->newscreen_picture_lineedit->text() == "")
        {
            QMessageBox::about(this, tr("����"), tr("û��ѡ��ͼƬ��"));
            return;
        }
    }
    QStringList list;//��������
    for(int i=0;i<pwnd->pSceneSheet.size();i++)
    {
        if(pwnd->nActiveSheetIndex == i)
        {
            continue;
        }
        if(pwnd->pSceneSheet.at(i)->sNewScreenName == ui->sUserKeyboardName->text())
        {
            box.setText(tr("�����Ѿ����ڣ�������������"));
            box.exec();
            ui->sUserKeyboardName->setFocus();
            return;
        }
    }
    if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName!=ui->sUserKeyboardName->text())
    {
        pwnd->reUserkeyboardname(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName,ui->sUserKeyboardName->text());
    }
    DrowKeybaordsize();
    //��ͼ��ʽ��ɫ��������ɫ�õ�
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneStyleColor=ui->newscreen_pushButton_frontcolor ->palette().background().color();
    //ѡ�񱳾���ʽ������ɫ����ͼƬ
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSelectType=R_BackGaound_Group->checkedId();
    //������ʽ
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nPattern=ui->newscreen_style_combobox->currentIndex();
    //ͼƬ·��
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_picturePath=ui->newscreen_picture_lineedit->text();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_bChangePicPath = true;
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->setSceneRect(0,0,ui->Width->value(),ui->high->value());
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneBackColor = ui->newscreen_pushButton_bk->palette().background().color(); //����ɫ
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName=ui->sUserKeyboardName->text();//�Զ����������
    QString sTemp=pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0);
    list=sTemp.split(":");
    pwnd->newScreen[pwnd->nActiveSheetIndex]->setText(0,list.at(0)+":"+ui->sUserKeyboardName->text());
    pwnd->upDatetreeScreenItem();//���»�������
    accept();
}


void QUserKeyboardProperty::on_Cancel_clicked()
{
    reject();
}
void QUserKeyboardProperty::DrowKeybaordsize()
{
    qreal qPointx = 0; //������
    qreal qPointy = 0; //������
    qreal qVal = 0; //��ʱ����
    QGraphicsItem *item;

    int nWidth = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->width();   //���
    int nHeight = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->height(); //�߶�

    double iScalex;//X��������ű���
    double iScaley;//Y��������ű���

    //����ˮƽģʽ�µ����ű���
    iScalex=(double)nWidth/ui->Width->value();//X��������ű���
    iScaley=(double)nHeight/ui->high->value();//Y��������ű���

    QList <QGraphicsItem *> selList;
    QGroupItem * group;
    QPainterPath path;
    path.addRect(0,0,pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->width(),pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->height());
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->setSelectionArea(path);
    selList=pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->selectedItems();
    foreach(QGraphicsItem *pitem,selList)
        pitem->setSelected(false);
    for(int i = 0; i <selList.size(); i++)  //�������ű������µ����ؼ���λ�úʹ�С
    {
        item = selList.at(i);
        qPointx=item->boundingRect().left()+item->scenePos().x();//�õ���ǰX����
        qPointx=qPointx/iScalex;//�����ű������õ��µ�λ��
        qVal = qPointx - item->boundingRect().x();
        selList.at(i)->setX(qVal);

        qPointy=item->boundingRect().top()+item->scenePos().y();//�õ���ǰy����
        qPointy=qPointy/iScaley;//�����ű������õ��µ�λ��
        qVal = qPointy - item->boundingRect().y();
        selList.at(i)->setY(qVal);
        foreach(QGraphicsItem *pItem,selList.at(i)->childItems())
        {
            if (pItem->type() == SAM_DRAW_OBJECT_PIXMAP)
            {
                QPixmapItem *pTmp = NULL;
                pTmp = dynamic_cast<QPixmapItem *> (pItem);
                pTmp->boundRect = pTmp->sceneBoundingRect();
            }

        }
        group=new QGroupItem(selList.at(i));
        group->SetWidth(item->sceneBoundingRect().width()/iScalex);
        group->SetHeigth(item->sceneBoundingRect().height()/iScaley);
    }
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->reBondingTrackers();
}
