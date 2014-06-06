//#include "qkeyboardascii.h"
//#include "Frame/mainwindow.h"
//extern MainWindow *pwnd;
//QKeyboardASCII::QKeyboardASCII(QGraphicsItem *pItem,QWidget *parent) :
//    QDialog(parent)
//{
//    tabWidget = new QTabWidget();
//    pASCIIInputgen=new QKeyboardASCIIGen();
//    pLabel = new QWordBtnLabelDlg();
//    tabWidget->addTab(pASCIIInputgen, tr(""));
//    //tabWidget->addTab(pLabel, tr("标示"));
//    //tabWidget->addTab(pASCIIInputAdv, tr("高级"));
//    //tabWidget->addTab(pASCIIInputVis, tr("显现"));

//    //datalist = new QStringList();
//    //int i = 0;
////    for (i=0; i<200; i++)
////    {
////            datalist->append("");
////    }
//    connect(pLabel, SIGNAL(SetTextProperty()),this, SLOT(SetTxtProperty()));
//    connect(pLabel, SIGNAL(addPicture(QGraphicsItem*,QPixmap*)),this, SLOT(onAddPicture(QGraphicsItem*,QPixmap*)));
//    connect(pASCIIInputgen, SIGNAL(txtChange()),this, SLOT(SetTxtProperty()));
//    connect(pASCIIInputgen, SIGNAL(picChange(QGraphicsItem*,QPixmap*)),this, SLOT(onAddPicture(QGraphicsItem*,QPixmap*)));

////    buttonBox = new QDialogButtonBox();
////    buttonBox->addButton(tr("确定"),QDialogButtonBox::AcceptRole);
////    buttonBox->addButton(tr("取消"),QDialogButtonBox::RejectRole);
////    buttonBox->addButton(tr("帮助"),QDialogButtonBox::HelpRole);
////    connect(buttonBox, SIGNAL(accepted()), this, SLOT(confyButton()));
////    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
////    connect(buttonBox, SIGNAL(helpRequested ()), this, SLOT(loadHelp()));

////    pLabel->ui->label->setHidden(true);
////    pLabel->ui->m_languagecmb->setHidden(true);
////    pLabel->ui->m_check->setHidden(true);

////    pLabel->ui->tabWidget_2->move(10,10);
////    pLabel->ui->label->setHidden(true);
//    mainLayout = new QVBoxLayout;
//    mainLayout->addWidget(tabWidget);
//    mainLayout->addWidget(buttonBox);
//    setLayout(mainLayout);
//    InitAllProperty(pItem);
//    this->setWindowTitle(tr("键盘组件"));
//    this->resize(800,400);
//}
//QKeyboardASCII::~QKeyboardASCII()
//{

//     if(mainLayout)
//      {
//          delete mainLayout;
//          mainLayout=NULL;
//      }
//     if(pLabel)
//     {
//         delete pLabel;
//         pLabel = NULL;
//     }

//     if(buttonBox)
//        {
//            delete buttonBox;
//            buttonBox=NULL;
//        }
//     if(pASCIIInputgen)
//        {
//            delete pASCIIInputgen;
//            pASCIIInputgen=NULL;
//        }
//     if(pASCIIInputAdv)
//        {
//            delete pASCIIInputAdv;
//            pASCIIInputAdv=NULL;
//        }
//     if(pASCIIInputVis)
//        {
//            delete pASCIIInputVis;
//            pASCIIInputVis=NULL;
//        }
//   if(tabWidget)
//   {
//       delete tabWidget;
//       tabWidget=NULL;
//   }
////   datalist->clear();
////   delete datalist;
//}
//void QKeyboardASCII::SetTxtProperty()        //改变一般页面文本的基本属性
//{
//    pASCIIInputgen->pBaseItem->SetPropertyValue("mText.Text",QVariant(pLabel->sText));                //设置文本
//    pASCIIInputgen->pBaseItem->SetPropertyValue("mText.Font",QVariant(pLabel->sFont));                  //设置字体
//    pASCIIInputgen->pBaseItem->SetPropertyValue("mText.FontSize",QVariant(pLabel->nFontSize));        //设置字体大小

//    pASCIIInputgen->pBaseItem->SetPropertyValue("mText.FontItalic",QVariant(pLabel->Italic));         //斜体
//    pASCIIInputgen->pBaseItem->SetPropertyValue("mText.FontBold",QVariant(pLabel->Bold));             //粗体
//    pASCIIInputgen->pBaseItem->SetPropertyValue("mText.UnderLine",QVariant(pLabel->UnderLine));       //下划线
//    pASCIIInputgen->pBaseItem->SetPropertyValue("mText.WordInterval",QVariant(pLabel->nWordInterval));//字距
//    pASCIIInputgen->pBaseItem->SetPropertyValue("mText.Alignment",QVariant(pLabel->nPosition));       //对齐方式
//    pASCIIInputgen->pBaseItem->SetPropertyValue("mText.FontColor",QVariant(pLabel->sColor));          //字体颜色
//}

//void QKeyboardASCII::onAddPicture(QGraphicsItem *pItem,QPixmap* pPix)
//{
//    QGraphicsItem * newItem;
//    QDrawGraphics *pDraw = new QDrawGraphics;

//    newItem = pDraw->AlterGraphics(pASCIIInputgen->pOldItem,pPix,pItem,pLabel->nPicPosition,
//                                   pLabel->nPicBorder,pLabel->ifFit); //,pTab->ifDeletePic

//    pASCIIInputgen->pScene->removeItem(pASCIIInputgen->pOldItem);
//    pASCIIInputgen->pScene->addItem(newItem);
//    pASCIIInputgen->pOldItem = newItem;
//    pASCIIInputgen->pBaseItem = new QGroupItem(newItem);
//    if(pDraw)
//    {
//        delete pDraw;
//        pDraw = NULL;
//    }
//}
//void QKeyboardASCII::confyButton()
//{
//      //pLabel->GeneralSave(datalist,140);
//      //pASCIIInputgen->pBaseItem->SetPropertyValue("mText.Text",QVariant(datalist->at(154)));                //设置文本
//      int iLan = pwnd->qLanguagecmb->currentIndex();
//      if(iLan < 0)
//          iLan = 0;
//      pLabel->ui->m_languagecmb->setCurrentIndex(iLan);  //设置默认是语言1

////      pASCIIInputgen->ASCIIEntryGenSave(datalist,40);
////    if(!pASCIIInputAdv->advancedSave(datalist,20))
////     {
////        return;
////    }
////    if(!pASCIIInputVis->visibleSave(datalist,0))
////    {
////        return;
////    }


//    //pASCIIInputgen->pOldItem->setData(GROUP_DATALIST_KEY,*datalist);
//    pASCIIInputgen->pOldItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_ASCII_KEYBOARD));
//    accept();
//}//
//void QKeyboardASCII::InitAllProperty(KeyBoardItem *pItem)
//{
//    if (pItem)//打开一个已有的位按钮
//    {
//       // *datalist = qVariantValue<QStringList>(pItem->data(GROUP_DATALIST_KEY));
//        pASCIIInputgen->Init(pItem);//初始化一般页面
//        //pASCIIInputAdv->Init(pItem);//初始化高级页面
//        //pLabel->Init(pItem);//初始化标示页面
//        pASCIIInputVis->Init(pItem);//初始化标示页面
//    }
//    else//新建
//    {
//        pASCIIInputgen->Init(NULL);//初始化一般页面
//        //pASCIIInputAdv->Init(NULL);//初始化高级页面
//        //pASCIIInputVis->Init(NULL);//初始化标示页面
//        pLabel->Init(NULL);//初始化标示页面
//    }
//}
//void QKeyboardASCII::loadHelp()
//{
//    pwnd->loadHelpHtm(GROUP_TYPE_ASCII_KEYBOARD);
//}
