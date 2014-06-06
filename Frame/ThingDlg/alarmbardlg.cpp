#include "alarmbardlg.h"
#include "ui_alarmbardlg.h"
#include "view/alarmbar.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

AlarmbarDlg::AlarmbarDlg(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlarmbarDlg)
{
    ui->setupUi(this);
    setWindowTitle(tr("��̬������"));
    oId = -1;

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    QSize sz = size();
    setFixedSize(sz);//��ֹ�ϷŴ��ڴ�С

    ui->View->setScene(&scene);

    if(pItem && (pItem->type() == SAM_DRAW_OBJECT_GROUP))
    {
        item = dynamic_cast<QItemGroup *> (pItem)->Clone();
    }
    else
        item = NULL;

    QPushButton *btn = ui->buttonBox->button(QDialogButtonBox::Ok);
    btn->setText(tr("ȷ��"));

    btn = ui->buttonBox->button(QDialogButtonBox::Cancel);
    btn->setText(tr("ȡ��"));

    btn = ui->buttonBox->button(QDialogButtonBox::Help);
    btn->setText(tr("����"));

    pDynAlarmBarGen=new QDynAlarmBarGenDlg();
    pSecurityWight=new SecurityWidget(this);
    ui->tabWidget->addTab(pDynAlarmBarGen, tr("��������"));

    ui->tabWidget->addTab(pSecurityWight, tr("Ȩ������"));
    pSecurityWight->ui->groupBox_Touch->setEnabled(false);
    pSecurityWight->ui->group_press->setEnabled(false);
    pSecurityWight->ui->groupBox_Notice->setEnabled(false);
    pSecurityWight->setTouchGroupEnabled(false);
    InitAllProperty();
}


AlarmbarDlg::~AlarmbarDlg()
{
    if(pDynAlarmBarGen)
    {
        delete pDynAlarmBarGen;
        pDynAlarmBarGen = NULL;
    }
    if(pSecurityWight)
    {
        delete pSecurityWight;
        pSecurityWight = NULL;
    }

}
void AlarmbarDlg::InitAllProperty()
{
    if (item)//��һ�����е�λ��ť
    {
        QGroupItem groupfunction(item);
        groupfunction.SetWidth(100);
        groupfunction.SetHeigth(100);

        scene.addItem(item);

        AlarmBar *alarmbar = dynamic_cast<AlarmBar *> (item);
        //InitUi();
        oId = alarmbar->id();
        ui->spinBox_3->setValue(oId);

        pDynAlarmBarGen->Init(alarmbar);//��ʼ��һ��ҳ��
        pSecurityWight->init(alarmbar);//��ʼ����ʾҳ��
    }
    else//�½�
    {
        pDynAlarmBarGen->Init(NULL);//��ʼ��һ��ҳ��
        pSecurityWight->init(NULL);//��ʼ��Ȩ��ҳ��
        ui->spinBox_3->setValue(pwnd->getNewId());
    }
    pSecurityWight->setTouchDisable(true);
    scene.addItem(pDynAlarmBarGen->pCopyItem);
}
void AlarmbarDlg::accept()
{
    if(pSecurityWight->Save())
    {
        pDynAlarmBarGen->DynAlarmBarGenSave(pSecurityWight->sproperty);

        pDynAlarmBarGen->setid(ui->spinBox_3->value());

        if(ui->spinBox_3->value() != oId && !pwnd->insertId(ui->spinBox_3->value()))
        {
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID�ظ������޸�ID��"),
                            0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
            box.exec();
            ui->spinBox_3->setFocus();
            return ;
        }

        QDialog::accept();
    }
}
void AlarmbarDlg::on_buttonBox_accepted()
{

}

void AlarmbarDlg::on_buttonBox_helpRequested()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_ALARMBAR);
}
