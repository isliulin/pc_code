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
    setWindowTitle(tr("动态报警条"));
    oId = -1;

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    QSize sz = size();
    setFixedSize(sz);//禁止拖放窗口大小

    ui->View->setScene(&scene);

    if(pItem && (pItem->type() == SAM_DRAW_OBJECT_GROUP))
    {
        item = dynamic_cast<QItemGroup *> (pItem)->Clone();
    }
    else
        item = NULL;

    QPushButton *btn = ui->buttonBox->button(QDialogButtonBox::Ok);
    btn->setText(tr("确定"));

    btn = ui->buttonBox->button(QDialogButtonBox::Cancel);
    btn->setText(tr("取消"));

    btn = ui->buttonBox->button(QDialogButtonBox::Help);
    btn->setText(tr("帮助"));

    pDynAlarmBarGen=new QDynAlarmBarGenDlg();
    pSecurityWight=new SecurityWidget(this);
    ui->tabWidget->addTab(pDynAlarmBarGen, tr("基本设置"));

    ui->tabWidget->addTab(pSecurityWight, tr("权限设置"));
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
    if (item)//打开一个已有的位按钮
    {
        QGroupItem groupfunction(item);
        groupfunction.SetWidth(100);
        groupfunction.SetHeigth(100);

        scene.addItem(item);

        AlarmBar *alarmbar = dynamic_cast<AlarmBar *> (item);
        //InitUi();
        oId = alarmbar->id();
        ui->spinBox_3->setValue(oId);

        pDynAlarmBarGen->Init(alarmbar);//初始化一般页面
        pSecurityWight->init(alarmbar);//初始化标示页面
    }
    else//新建
    {
        pDynAlarmBarGen->Init(NULL);//初始化一般页面
        pSecurityWight->init(NULL);//初始化权限页面
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
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                            0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("确定"),QMessageBox::AcceptRole);
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
