#include "macroedit.h"
#include "QsciScintillaEx.h"
#include <Qsci/qscilexerjava.h>
#include "Frame/mainwindow.h"
#include <QDir>

extern MainWindow *pwnd;
#define COLUMNCOUNT 7
#define LOCAL_VARTABLE 0
#define GLOBAL_VARTABLE 1

AddLib::AddLib(QVector<Macro > libs,QWidget *parent)
        : QDialog(parent)
{
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    librarys = libs;
    label = new QLabel(tr("请输入库名称"),this);
    msg = new QLabel(this);
    edit = new QLineEdit(this);

    label->setBuddy(edit);
    btnBox = new QDialogButtonBox(QDialogButtonBox::Ok |QDialogButtonBox::Cancel,Qt::Horizontal,this);
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(label,0,0,1,1);
    layout->addWidget(edit,0,1,1,1);
    layout->addWidget(msg,1,1,1,1);
    layout->addWidget(btnBox,0,2,1,2);

    this->setLayout(layout);
    connect(edit,SIGNAL(textChanged(QString)),this,SLOT(onTextChanged(QString )));
    connect(btnBox,SIGNAL(accepted()),this,SLOT(accepted()));
    connect(btnBox,SIGNAL(rejected()),this,SLOT(reject()));

	QRegExp regExp("[A-Za-z_][0-9a-zA-Z_]{0,20}");
	QValidator *validator = new QRegExpValidator(regExp,this);
	edit->setValidator(validator);
	edit->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));
	reWords <<"null"<<"int"<<"short"<<"long"<<"float"<<"double"<<"byte"<<"char"
		<<"String"<<"const"<<"true"<<"false"<<"public"<<"static"<<"private"<<"protected"
		<<"default"<<"continue"<<"while"<<"goto"<<"return"<<"volatile"<<"void"<<"for"
		<<"class"<<"if"<<"else"<<"switch"<<"case"<<"break"
		<<"do"<<"catch"<<"throw"<<"throws"<<"try"<<"finall"<<"finally"<<"new"<<"this"
        <<"package"<<"SysInit"<<"import"<<"implements"<<"extends"<<"abstract"<<"super"<<"strictfp"<<"interface"
		<<"transient"<<"synchronized"<<"instanceof"<<"native";

}
AddLib::~AddLib()
{}
void AddLib::onTextChanged(QString text)
{
    msg->setText("");
    QRegExp regExp("^[A-Za-z_][0-9a-zA-Z_]{0,20}$");
	
    if(text.indexOf(regExp) <0)
    {
        msg->setText(tr("库名称只能为中英文字符、数字、下划线"));
    }
}
void AddLib::accepted()
{
    bool bExist = false;
    libName = edit->text();
    foreach(Macro library,librarys)
    {
		if(libName.compare(library.libName,Qt::CaseInsensitive)== 0)
        {
            bExist = true;
            msg->setText(libName+tr(" 已存在"));
            return ;
        }

    }
    if(reWords.contains(libName))
    {
        bExist = true;
        msg->setText(libName+tr(" 是保留关键字"));
        return ;
    }

    if(!libName.isEmpty())
    {

        QRegExp regExp("^[A-Za-z_][0-9a-zA-Z_]{0,20}$");
        if(libName.indexOf(regExp) <0)
        {
            msg->setText(tr("库名称只能为中英文字符、数字、下划线"));
            return ;
        }
        QDialog::accept();
    }
    else
        msg->setText(tr("库名称不能为空！"));
}

void AddLib::setEditString(QString str)
{
    edit->setText(str);
}

//add by wuxiyang
FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    is_firstFind = true;
    m_bFindText = false;
    label = new QLabel(tr("查找内容:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    labelReplace = new QLabel(tr("替换为:"));
    editReplace = new QLineEdit;
    labelReplace->setBuddy(editReplace);

    caseCheckBox = new QCheckBox(tr("匹配大小写(&M)"));
    backwardCheckBox = new QCheckBox(tr("向前查找(&S)"));
    worldMatchCheckBox = new QCheckBox(tr("整字匹配(&O)"));
    rExpCheckBox = new QCheckBox(tr("正则表达式(&E)"));

    findButton = new QPushButton(tr("查找(&F)"));
    findButton->setDefault(true);
    findButton->setEnabled(false);

    closeButton = new QPushButton(tr("关闭(&C)"));

    replaceButton = new QPushButton(tr("替换(&R)"));

    connect(lineEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(enableFindButton(const QString &)));

    connect(editReplace, SIGNAL(textChanged(const QString &)),
            this, SLOT(ReplaceButton(const QString &)));

    connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(replaceButton, SIGNAL(clicked()), this, SLOT(replaceClicked()));

    connect(caseCheckBox, SIGNAL(toggled(bool)), this, SLOT(onCheckBoxChanged(bool)));
    connect(backwardCheckBox, SIGNAL(toggled(bool)), this, SLOT(onCheckBoxChanged(bool)));
    connect(worldMatchCheckBox, SIGNAL(toggled(bool)), this, SLOT(onCheckBoxChanged(bool)));
    connect(rExpCheckBox, SIGNAL(toggled(bool)), this, SLOT(onCheckBoxChanged(bool)));

    QHBoxLayout *LeftLayout1 = new QHBoxLayout;
    LeftLayout1->addWidget(label);
    LeftLayout1->addWidget(lineEdit);

    QHBoxLayout *LeftLayout2 = new QHBoxLayout;
    LeftLayout2->addWidget(labelReplace);
    LeftLayout2->addWidget(editReplace);

    QVBoxLayout *LeftLeftLayout = new QVBoxLayout;
    LeftLeftLayout->addWidget(caseCheckBox);
    LeftLeftLayout->addWidget(worldMatchCheckBox);

    QVBoxLayout *leftRightLayout = new QVBoxLayout;
    leftRightLayout->addWidget(backwardCheckBox);
    leftRightLayout->addWidget(rExpCheckBox);

    QHBoxLayout *LeftLayout3 = new QHBoxLayout;
    LeftLayout3->addLayout(LeftLeftLayout);
    LeftLayout3->addLayout(leftRightLayout);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(LeftLayout1);
    leftLayout->addLayout(LeftLayout2);
    leftLayout->addLayout(LeftLayout3);


    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(replaceButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);


    setWindowTitle(tr("查找"));
    setFixedHeight(sizeHint().height());
}

void FindDialog::findClicked()
{
    QString text = lineEdit->text();
    if(true == is_firstFind)
    {
        emit findFirst(text, rExpCheckBox->isChecked(),
                             caseCheckBox->isChecked(),
                             worldMatchCheckBox->isChecked(),
                             true,
                             !backwardCheckBox->isChecked());
        //is_firstFind = false;
        //m_bFindText = true;
    }
    else
    {
        emit findNext();
    }
}

void FindDialog::enableFindButton(const QString &text)
{
    findButton->setEnabled(!text.isEmpty());
    is_firstFind = true;
    m_bFindText = false;
}

void FindDialog::ReplaceButton(const QString &text)
{
    m_bFindText = false;
}

void FindDialog::replaceClicked()
{
     QString text = editReplace->text();
     if(m_bFindText)
     {
         emit replace(text);
     }
     else
     {
         emit findFirst(lineEdit->text(), rExpCheckBox->isChecked(),
                              caseCheckBox->isChecked(),
                              worldMatchCheckBox->isChecked(),
                              true,
                              !backwardCheckBox->isChecked());
         //is_firstFind = false;
         //m_bFindText = true;
     }
}

void FindDialog::onCheckBoxChanged(bool)
{
     is_firstFind = true;
     m_bFindText = false;
}

void FindDialog::closeEvent(QCloseEvent *event)
{
    lineEdit->clear();
    editReplace->clear();
    lineEdit->setFocus();
    rExpCheckBox->setChecked(false);
    caseCheckBox->setChecked(false);
    worldMatchCheckBox->setChecked(false);
    backwardCheckBox->setChecked(false);
}

void FindDialog::setFindTextResult(bool bFind)
{
    m_bFindText = bFind;
}

void FindDialog::setIsFindFirst(bool bFirst)
{
    is_firstFind = bFirst;
}

MacroEdit::MacroEdit(QString currentName,QWidget *parent)
    : QDialog(parent)
{
    vartable = NULL;
    gvartable = NULL;
    setWindowFlags(Qt::Window);
    this->setWindowTitle(tr("脚本浏览器"));
    qDebug() << "MacroEdit::MacroEdit";
    lName = currentName;
    labelnothing = new QLabel(tr(""),this);
    labelLst = new QLabel(tr("脚本"),this);
    addMacroBtn = new QPushButton(tr(""),this);
    addMacroBtn->setFlat(true);
    addMacroBtn->setIcon(QIcon(":/standardtool/images/standardtool/newscreen.ico"));
    addMacroBtn->setToolTip(tr("添加脚本"));

    QHBoxLayout *firstlayout = new QHBoxLayout();
    firstlayout->addWidget(labelLst);
    firstlayout->addWidget(addMacroBtn);
    firstlayout->setStretch(0,3);
    firstlayout->setStretch(1,1);
    tree = new QTreeWidget(this);

    //



	groupSysLib = new QGroupBox(tr("添加系统函数"),this);
	QVBoxLayout *glayout = new QVBoxLayout(groupSysLib);

	labelSlecetLib = new QLabel(tr("库名称"),this);
	labelSlecetFun = new QLabel(tr("函数名称"),this);
	comboSysLib = new QComboBox(this);
	comboLibFun = new QComboBox(this);
	insertFuncBtn = new QPushButton(tr(""),this);
	insertFuncBtn->setFlat(true);
	insertFuncBtn->setIcon(QIcon(":/debug/images/debug/macro.ico"));
    insertFuncBtn->setToolTip(tr("引用函数"));
	sysLibTips = new QPlainTextEdit(this);
	//labelSlecetLib->setBuddy(comboSysLib);
	//labelSlecetFun->setBuddy(comboLibFun);

	QGridLayout *hlayout_lib = new QGridLayout();
	hlayout_lib->addWidget(labelSlecetLib,0,0,1,2);
	hlayout_lib->addWidget(comboSysLib,0,2,1,4);

	//QHBoxLayout *hlayout_fun = new QHBoxLayout();
	hlayout_lib->addWidget(labelSlecetFun,1,0,1,2);
	hlayout_lib->addWidget(comboLibFun,1,2,1,4);
	hlayout_lib->addWidget(insertFuncBtn,1,6,1,1);

	

	glayout->addLayout(hlayout_lib);
	//glayout->addLayout(hlayout_fun);
	glayout->addWidget(sysLibTips);

    QVBoxLayout *vlayout = new QVBoxLayout();
	
    labelnothing->setMaximumWidth(300);
    tree->setMaximumWidth(300);
    groupSysLib->setMaximumWidth(300);


    vlayout->addWidget(labelnothing);
    vlayout->addLayout(firstlayout);
    vlayout->addWidget(tree);
	vlayout->addWidget(groupSysLib);
    vlayout->setStretch(1,30);
	vlayout->setStretch(2,30);



    labelLib = new QLabel(tr("库名称"),this);
    libNameEdit = new QLineEdit(this);
    libNameEdit->setEnabled(false);
    labelLib->setBuddy(libNameEdit);



    table = new QTabWidget(this);
    textEdit = new QsciScintillaEx(this);

    QVBoxLayout *editLayout = new QVBoxLayout();

    //创建工具条
    creatToolBar();


    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(labelLib);
    hlayout->addWidget(libNameEdit);

//     hlayout->addWidget(labelMacro);
//     hlayout->addWidget(marcoNameEdit);
//     hlayout->addWidget(insertFuncBtn);



    editLayout->addLayout(hlayout);
    editLayout->addWidget(toolbar);

    editLayout->addWidget(textEdit,2);

    editLayout->addWidget(table,1);

    QHBoxLayout *mainLayout = new QHBoxLayout();


    //QSizePolicy policy = tree->sizePolicy();

    //policy.setHorizontalPolicy(QSizePolicy::Maximum);
    //tree->setSizePolicy(policy);

    mainLayout->addLayout(vlayout,1);
    mainLayout->addLayout(editLayout,5);

    

    //mainLayout->setRowStretch(0,20);
    //mainLayout->setRowStretch(1,40);
    
    //mainLayout->setColumnStretch(1, 30);
    //mainLayout->setColumnStretch(0, 5);

	//设置编辑框的属性
	initHighlighter();



    setLayout(mainLayout);

    //resize(800,600);

    //初始化树形结构部分 脚本库
    initLibTree();

    //初始化变量设定和信息输出窗口
    initTabWidget();

    

	//设置类型对应的声明字符串
	setTypeMap();

    initSysLib();
    /*add by wuxiyang初始化操作放到构造函数里面去做
    defaultVar.addr = Keyboard();
    defaultVar.dataType = 0;
    defaultVar.RWPerm = 2;
	defaultVar.count = 1;
    */
	cmpTrd = new MacroCmptrd();
    connect(cmpTrd,SIGNAL(signalOutPut(QString,QString)),this,SLOT(showErrorLog(QString,QString)));
    connect(cmpTrd,SIGNAL(started()),this,SLOT(disableUi()));
    connect(cmpTrd,SIGNAL(finished()),this,SLOT(enableUi()));
    connect(addMacroBtn,SIGNAL(clicked()),this,SLOT(addMacro()));

	setWindowState(Qt::WindowMaximized);
	bReload = true;
	bCompile = false;
    textEdit->setFocus();
    findDlg = 0;
}

MacroEdit::~MacroEdit()
{
    if (cmpTrd)
    {
            cmpTrd->deleteLater();
            cmpTrd = NULL;
    }
}

//初始化树形结构部分 脚本库
void MacroEdit::initLibTree()
{
    qDebug() << "MacroEdit::initLibTree";
    rootJML = new QTreeWidgetItem(tree, QStringList(tr("脚本")));
    rootJRL = new QTreeWidgetItem(tree, QStringList(tr("函数库")));

    QTreeWidgetItem *item = NULL;
    QTreeWidgetItem *childItem = NULL;

    currentItem = NULL;
    QString iconPath;

    qDebug() << "MacroEdit::initLibTree-235";
    if(lName.isEmpty() && !pwnd->macros.isEmpty())
    {
        lName = pwnd->macros[0].libName;
    }
    qDebug() << "MacroEdit::initLibTree-240";
    foreach(Macro lib,pwnd->macros)
    {
        //添加库名称到树形结构部分
        if(!lib.type)
            item = new QTreeWidgetItem(rootJRL, QStringList(lib.libName));
        else
            item = new QTreeWidgetItem(rootJML, QStringList(lib.libName));
        //rootJRL->addChild(item);
        if(lib.isCompiled())
        {
            iconPath = QString(":/standardtool/images/standardtool/copy.ico");
        }
        else
            iconPath = QString(":/standardtool/images/standardtool/delete.ico");
        item->setIcon(0,QIcon(iconPath));

        //添加函数名作为函数的子项
        foreach(QString funcName,lib.functions)
        {
            childItem = new QTreeWidgetItem(item,QStringList(funcName));
            //item->addChild(childItem);
            childItem->setIcon(0,QIcon(":/standardtool/images/standardtool/copy.ico"));
        }
        if(lName == lib.libName)
        {
            textEdit->setText(lib.code());
            textEdit->setModified(false);
        }
    }
    tree->expandAll();
    if(rootJRL->childCount() >0)
    {
        currentItem = rootJRL->child(0);
    }
    for(int i=0; i<rootJRL->childCount();i++)
    {
        if(rootJRL->child(i)->text(0) == lName)
        {
            currentItem = rootJRL->child(i);
        }
    }
    for(int i=0; i<rootJML->childCount();i++)
    {
        if(rootJML->child(i)->text(0) == lName)
        {
            currentItem = rootJML->child(i);
        }
    }
	if(currentItem)
	{
		libNameEdit->setText(currentItem->text(0));
		treeItemChanged(currentItem,0);
	}
	else
	{
		textEdit->setReadOnly(true);
	}
        
    connect(tree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this,SLOT(treeItemChanged(QTreeWidgetItem*,int)));

    connect(tree,SIGNAL(itemPressed(QTreeWidgetItem*,int)),
            this,SLOT(pressTree(QTreeWidgetItem*,int)));
}

//初始化信息输出窗口 和 变量设定窗口
void MacroEdit::initTabWidget()
{
    msgOutput = new QPlainTextEdit(this);
    QVBoxLayout *msglayout = new QVBoxLayout;
    msglayout->addWidget(msgOutput);
    vartable = new QTableWidget(this);
    initVarTable(vartable,LOCAL_VARTABLE);
    gvartable = new QTableWidget(this);
    initVarTable(gvartable,GLOBAL_VARTABLE);

    table->addTab(msgOutput,tr("信息输出"));
    table->addTab(vartable,tr("变量设定"));
    table->addTab(gvartable,tr("全局变量设定"));
    table->setCurrentWidget(vartable);

}
void MacroEdit::initVarTable(QTableWidget *pVartable, int iIndex)
{
    //pVartable = new QTableWidget(this);

    newVarAction = new QAction(tr("新建变量"),pVartable);
    batVarAction = new QAction(tr("批量新建"),pVartable);
    editVarAction = new QAction(tr("编辑变量"),pVartable);
    delVarAction = new QAction(tr("删除变量"),pVartable);


    connect(newVarAction,SIGNAL(triggered()),this,SLOT(onNewVar()));
    connect(editVarAction,SIGNAL(triggered()),this,SLOT(onEditVar()));
    connect(delVarAction,SIGNAL(triggered()),this,SLOT(onDelVar()));
    connect(batVarAction,SIGNAL(triggered()),this,SLOT(onNewMulti()));

    pVartable->addAction(newVarAction);
    pVartable->addAction(batVarAction);
    pVartable->addAction(editVarAction);
    pVartable->addAction(delVarAction);

    pVartable->setContextMenuPolicy(Qt::ActionsContextMenu);



    reloadVars(lName,pVartable,iIndex);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(pVartable);

    /*变量设定类表属性设置：设置为单击选择整行,不可编辑 允许选择多行*/
    pVartable->setSelectionBehavior(QAbstractItemView::SelectRows);
    pVartable->setSelectionMode(QAbstractItemView::ContiguousSelection);
    pVartable->setEditTriggers(QAbstractItemView::NoEditTriggers);


    /*当双击变量设定表格时,弹出变量编辑对话框*/
    connect(pVartable,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(onEditVar()));


}

void MacroEdit::reloadVars(QString libraryName, QTableWidget* pVartable,int iIndex/* = 0*/)
{
    foreach(Macro library,pwnd->macros)
	{
		if(library.libName == libraryName)
		{
			if (!library.type)
			{
                pVartable->setDisabled(true);
                if(gvartable)
                {
                    gvartable->setDisabled(true);
                }
			}
            else
            {
                pVartable->setDisabled(false);
                if(gvartable)//wxy
                {
                    gvartable->setDisabled(false);
                }
			}
			break;
		}

	}

	QString vName = lName;
	
    pVartable->clear();
    pVartable->setRowCount(1);
    pVartable->setColumnCount(COLUMNCOUNT);
	
    pVartable->setItem(0, 0, new QTableWidgetItem(tr("新建")));


	/*设置表格标题栏文本*/
	QStringList Labels;
	Labels<<tr("变量名")<<tr("数据类别")<<tr("地址长度")<<tr("读写属性")
                <<tr("地址类型")<<tr("地址")<<tr("偏移地址");
    pVartable->setHorizontalHeaderLabels(Labels);

	/*设置表格列宽大小*/
    pVartable->setColumnWidth(0,100);//变量名
    pVartable->setColumnWidth(1,100);//数据类别
    //wxy按实际需求大小修改表格列宽
    pVartable->setColumnWidth(2,60);//地址长度
    pVartable->setColumnWidth(3,60);//读写属性
    pVartable->setColumnWidth(4,75);//地址类型
    pVartable->setColumnWidth(5,200);//地址
    pVartable->setColumnWidth(6,200);//偏移地址

	QVector<VarPro >vars;
    if(LOCAL_VARTABLE == iIndex)
    {
        foreach(Macro lib,pwnd->macros)
        {
            if (lib.libName == libraryName)
            {
                vars = lib.vars();
                break;
            }
        }
    }
    else if(GLOBAL_VARTABLE == iIndex)
    {
        vars = pwnd->getGlobalVars();
    }

	int rowIndex = -1;
	foreach(VarPro var,vars)
	{
        rowIndex = pVartable->rowCount()-1;
        setRow(var,rowIndex,pVartable);
        pVartable->setRowCount(pVartable->rowCount()+1);
        pVartable->setItem(pVartable->rowCount()-1, 0, new QTableWidgetItem(tr("新建(单击右键)")));

	}
}
//设置高亮编辑框的属性
void MacroEdit::initHighlighter()
{
    //左侧边栏设置
    textEdit->setMarginLineNumbers(1,true);

    textEdit->setMarginsBackgroundColor(QColor(210,210,200,255));
    textEdit->setMarginsForegroundColor(QColor(0x8B,0x96,0xAB,255));
    textEdit->setMarginWidth(1,"99999");
    textEdit->setMarginsFont(QFont(QString(QFont::Courier),-1,-1,false));
    textEdit->setMarginSensitivity(1,true);


    //代码块折叠
    textEdit->setFoldMarginColors(QColor(230,230,230,255),QColor(230,230,230,255));
    textEdit->setFolding(QsciScintilla::BoxedFoldStyle);

    //自动缩进
    textEdit->setAutoIndent(true);
    textEdit->setIndentationGuides(true);
    textEdit->setIndentationsUseTabs(true);
    textEdit->setIndentationGuidesBackgroundColor(QColor(230,230,230,255));
    textEdit->setIndentationGuidesForegroundColor(QColor(230,230,230,255));



    //java语法高亮
    QsciLexerJava *jlexer = new QsciLexerJava;
    textEdit->setLexer(jlexer);

    //设置当前行高亮
    textEdit->setCaretLineVisible(true);
    textEdit->setCaretLineBackgroundColor(QColor(230,230,230,255));


    //使用utf8
    textEdit->setUtf8(true);


    //自动提示

    //connect(textEdit, SIGNAL(marginClicked(int, int, Qt::KeyboardModifiers)),this, SLOT(onMarginClicked()));


    connect(textEdit, SIGNAL(textChanged()),this, SLOT(onModified()));
    connect(textEdit, SIGNAL(findAction()), this, SLOT(onFind()));
    //connect(textEdit, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(editCursorPosChanged(int,int)));

    setCurrentFile("");
}

//响应文本的改变
void MacroEdit::onModified()
{
    if(!currentItem || !rootJRL)
    {
        qDebug() << "no library selected,return";
        return;
    }
	QTreeWidgetItem *item = NULL;
	QTreeWidgetItem *funcItem = currentItem;

	bool libType = true;
	int childcount = funcItem->childCount();
	//删除树形结构中旧的函数列表
	for(int i=0;i<childcount;i++)
	{
		funcItem->removeChild(funcItem->child(0));
	}

    //更新函数库中的函数名列表
    for(int i =0; i<pwnd->macros.size(); i++)
    {
        if(pwnd->macros[i].libName == funcItem->text(0))
        {
			if (bReload)
			{
                bCompile = false;
			}
			QString iconPath;
			if(bCompile)
			{
				iconPath = QString(":/standardtool/images/standardtool/copy.ico");
			}
			else
            {
                iconPath = QString(":/standardtool/images/standardtool/delete.ico");
                pwnd->macros[i].setCompipiled(false); //wxy图标改变，按流程应该对该脚本库进行处理
            }
			funcItem->setIcon(0,QIcon(iconPath));
            libType = pwnd->macros[i].type;
            if (!libType && bReload)
            {
                funlibChanged(pwnd->macros[i].libName);
			}
			break;
		}
	}

    QStringList funcNames;    
	
	//regExp= QRegExp("public\\ {1,}void\\ {1,}[A-z_]{1,32}[a-z0-9_-]{0,32}\\(.{0,256}\\)");
	QRegExp regExp;
	QRegExp regMax;
//	if (libType)
//	{
//		regExp= QRegExp("public\\ {1,}[A-z_]{1,32}[A-z0-9_-]{0,32}\\ {1,}[A-z_]{1,32}[A-z0-9_-]{0,32}\\ {0,}\\(.{0,256}\\)");
//		regMax = QRegExp("public.[^\\ ]{0,}\\ {0,}");
//	}
//	else
//	{
		regExp = QRegExp("public\\ {1,}static\\ {1,}[A-z_]{1,32}[A-z0-9_-]{0,32}\\ {1,}[A-z_]{1,32}[A-z0-9_-]{0,32}\\ {0,}\\(.{0,256}\\)");
		regMax = QRegExp("public\\ {0,}static.[^\\ ]{0,}\\ {0,}");
//	}
	QRegExp reganno = QRegExp("/\\*.{0,}\\*/");
	
	//QRegExp regEOF = QRegExp("public\\ {1,}[A-z_]{1,32}[a-z0-9_-]{0,32}\\ {1,}[A-z_]{1,32}[a-z0-9_-]{0,32}\\(.{0,256}\\)\\s{0,}\\{$");
	regMax.setMinimal(false);
    reganno.setMinimal(true);

    regExp.setMinimal(true);

	//regEOF.setMinimal(true);

    QString code;

    //去掉单行注释
    for(int i=0; i< textEdit->lines(); i++)
    {
        QString line = textEdit->text(i);
        line.remove(QRegExp("//."));
        code.append(line);
    }
    //去掉多行注释

    code.remove(reganno);

    int count = code.count(regExp);
    QString cap;
    int index;
    int matchLen;

    while(!libType && count > 0)
    {
        index = code.indexOf(regExp);
        matchLen = regExp.matchedLength();
        cap = regExp.cap(0);

        code = code.right(code.length() - index-cap.length());
        count = code.count(regExp);
		cap.remove(QRegExp("\\(.{0,256}\\)"));
        cap.remove(regMax);
        //cap.remove("void");
        
        cap.remove("\ ");
		if (!funcNames.contains(cap))
		{
			funcNames << cap;
		}
        
    }

	
        //显示所有函数到树形结构下面
        foreach(QString name,funcNames)
        {
            item = new QTreeWidgetItem(funcItem, QStringList(name));
            funcItem->addChild(item);
            item->setIcon(0,QIcon(":/standardtool/images/standardtool/copy.ico"));
			funcItem->setExpanded(true);
        }

        code = textEdit->text();
   
}
//树形结构 双击改变当前item
void MacroEdit::treeItemChanged(QTreeWidgetItem* cItem,int coulum)
{
    qDebug() << "MacroEdit::treeItemChanged";
    QTreeWidgetItem *preItem = currentItem;
    QList<QTreeWidgetItem* > topItems;
    for(int i=0;i<rootJRL->childCount();i++)
    {
        topItems << rootJRL->child(i);
    }
    for(int i=0;i<rootJML->childCount();i++)
    {
        topItems << rootJML->child(i);
    }

    if(topItems.contains(cItem))
    {
        currentItem = cItem;
    }
    else if(cItem && topItems.contains(cItem->parent()))
    {
        currentItem = cItem->parent();
    }



    QString preLib;
    //判断是否更改选中
    if(currentItem && currentItem != preItem)
    {
        //保存前一个函数库

        if (saveCode(preItem))
        {
			//调出当前函数库的代码
			textEdit->setReadOnly(false);
			loadCode(currentItem->text(0));
			tree->setCurrentItem(currentItem);
			textEdit->setFocus();
			libNameEdit->setText(currentItem->text(0));
			qDebug() << "reload code from library";
            reloadVars(currentItem->text(0), vartable);
        }
		else
		{
			currentItem = preItem;
		}
    }   
}

//保存函数库的代码
bool MacroEdit::saveCode(QTreeWidgetItem* pItem)
{
	if (!pItem)
	{
		return true;
	}
    QString code = textEdit->text();
    if(textEdit->isModified())
    {
        //询问是否保存
        QString msg ;
        msg = tr("是否保存代码到函数库：")+pItem->text(0);
        QMessageBox box(QMessageBox::Information,tr("未保存"),msg,QMessageBox::Ok|QMessageBox::Close|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

        box.button(QMessageBox::Ok)->setText(tr("是"));
		box.button(QMessageBox::Close)->setText(tr("否"));
        box.button(QMessageBox::Cancel)->setText(tr("取消"));

        box.exec();
        if(box.clickedButton() == box.button(QMessageBox::Ok))
        {
            for(int i=0;i<pwnd->macros.size();i++)
            {
                if( pwnd->macros[i].libName == pItem->text(0))
                {
                    pwnd->macros[i].setCode(code);
					pwnd->macros[i].setCompipiled(false);
                }

            }
			
        }
		else if (box.clickedButton() == box.button(QMessageBox::Cancel))
		{
			return false;
		}
    }
	return true;
}

//调出函数库代码
void MacroEdit::loadCode(QString libName)
{
    foreach(Macro library,pwnd->macros)
    {
        if(library.libName == libName)
        {
			bReload = false;
            bCompile = library.isCompiled();
            textEdit->setText(library.code());
            textEdit->setModified(false);
			bReload = true;
        }

    }
}
//刷新树形结构的显示
void MacroEdit::updataTree(QStringList functions)
{}


void MacroEdit::setCurrentFile(const QString &fileName)
{
}

void MacroEdit::creatToolBar()
{
    toolbar = new QToolBar(this);
    toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolbar->setIconSize(QSize(32,32));
    toolbar->setStyleSheet("font: 9pt '宋体';\n"
                            "color: rgb(8, 45, 105);");
    toolbar->setMinimumSize(1,85);

    saveAction = new QAction(tr("保存"),this);
    saveAction->setIcon(QIcon(":/standardtool/images/Msave.ico"));
    saveAction->setToolTip(tr("保存"));
    saveAction->setIconText(tr("\n保存"));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(save()));

    compileAction = new QAction(tr("编译"),this);
    compileAction->setIcon(QIcon(":/debug/images/debug/compile.ico"));
    compileAction->setToolTip(tr("保存并编译"));
    compileAction->setIconText(tr("\n编译"));
    connect(compileAction,SIGNAL(triggered()),this,SLOT(compile()));

    //compileAllAction = new QAction(tr("插入函数"),this);
    //saveAction->setIcon(QIcon(":/Marco/images/standardtool/filesave.png"));
    //compileAllAction->setToolTip(tr("插入通过编译的函数"));
    //connect(compileAllAction,SIGNAL(triggered()),this,SLOT(toolbarInsertFunc()));

    undoAction = new QAction(tr("撤销"), this);
    undoAction->setIcon(QIcon(":/standardtool/images/standardtool/undo.ico"));
    undoAction->setToolTip(tr("撤销"));
    undoAction->setIconText(tr("\n撤销"));
    connect(undoAction,SIGNAL(triggered()),textEdit,SLOT(undo()));

    redoAction = new QAction(tr("反撤销"), this);
    redoAction->setIcon(QIcon(":/standardtool/images/standardtool/redo.ico"));
    redoAction->setToolTip(tr("恢复"));
    redoAction->setIconText(tr("\n恢复"));
    connect(redoAction,SIGNAL(triggered()),textEdit,SLOT(redo()));

    cutAction = new QAction(tr("剪切"), this);
    cutAction->setIcon(QIcon(":/standardtool/images/Mcut.ico"));
    cutAction->setToolTip(tr("剪切"));
    cutAction->setIconText(tr("\n剪切"));
    connect(cutAction,SIGNAL(triggered()),textEdit,SLOT(cut()));

    pasteAction = new QAction(tr("粘贴"), this);
    pasteAction->setIcon(QIcon(":/standardtool/images/Mpaste.ico"));
    pasteAction->setToolTip(tr("粘贴"));
    pasteAction->setIconText(tr("\n粘贴"));
    connect(pasteAction,SIGNAL(triggered()),textEdit,SLOT(paste()));

    copyAction = new QAction(tr("复制"), this);
    copyAction->setIcon(QIcon(":/standardtool/images/Mcopy.ico"));
    copyAction->setToolTip(tr("复制"));
    copyAction->setIconText(tr("\n复制"));
    connect(copyAction,SIGNAL(triggered()),textEdit,SLOT(copy()));

	hideMsgAction = new QAction(tr("信息/变量窗口"), this);
    hideMsgAction->setIcon(QIcon(":/standardtool/images/Mhide.ico"));
	hideMsgAction->setToolTip(tr("收起信息输出窗口"));
    hideMsgAction->setIconText(tr("\n展开/收起"));
	connect(hideMsgAction,SIGNAL(triggered()),this,SLOT(hideMsgWindow()));

    loadAction = new QAction(tr("导入"), this);
    loadAction->setIcon(QIcon(":/standardtool/images/Mopen.ico"));
    loadAction->setToolTip(tr("从文件载入"));
    loadAction->setIconText(tr("\n导入"));
	connect(loadAction,SIGNAL(triggered()),this,SLOT(onLoadCode()));

    savetoAction = new QAction(tr("导出"), this);
    savetoAction->setIcon(QIcon(":/standardtool/images/Mtofile.ico"));
    savetoAction->setToolTip(tr("导出到文件"));
    savetoAction->setIconText(tr("\n导出"));
	connect(savetoAction,SIGNAL(triggered()),this,SLOT(onSaveCode()));

	
	compileAllAction= new QAction(tr("全部编译"), this);
    compileAllAction->setIcon(QIcon(":/standardtool/images/Hammer.ico"));
    compileAllAction->setToolTip(tr("全部重新编译"));
    compileAllAction->setIconText(tr("\n全部编译"));
	connect(compileAllAction,SIGNAL(triggered()),this,SLOT(onCompileAll()));
    //connect(hideMsgAction,SIGNAL(triggered()),this,SLOT(hideMsgWindow()));

    findAction = new QAction(tr("查找"), this);
    findAction->setIcon(QIcon(":/standardtool/images/find.ico"));
    findAction->setToolTip(tr("查找文本"));
    findAction->setIconText(tr("\n查找"));
    findAction->setShortcut(QKeySequence::Find);
    connect(findAction, SIGNAL(triggered()), this, SLOT(onFind()));


    //toolbar->addSeparator();
    toolbar->addAction(undoAction);
    toolbar->addAction(redoAction);
    //toolbar->addSeparator();
    toolbar->addAction(cutAction);
    toolbar->addAction(pasteAction);
    toolbar->addAction(copyAction);
    //toolbar->addSeparator();
    toolbar->addAction(saveAction);
    toolbar->addAction(loadAction);
    toolbar->addAction(savetoAction);
    //toolbar->addSeparator();
    toolbar->addAction(compileAction);
	toolbar->addAction(compileAllAction);
    toolbar->addAction(hideMsgAction);
    toolbar->addAction(findAction);

}
void MacroEdit::save()
{

    QTreeWidgetItem* cParent = NULL;//当前的函数库对应的树形item
    QTreeWidgetItem *curItem = tree->currentItem();
    QList<QTreeWidgetItem* > topItems;
    for(int i=0;i<tree->topLevelItemCount();i++)
    {
        topItems << tree->topLevelItem(i);
    }

    textEdit->setModified(false);

    //保存代码到函数库
    //foreach(MacroLibrary library,pwnd->librarys)
    for(int i=0;i<pwnd->macros.size();i++)
    {
        if(currentItem && pwnd->macros[i].libName == currentItem->text(0))
        {
			QStringList names;
			for(int j=0; j<currentItem->childCount(); j++)
			{
				names << currentItem->child(j)->text(0);
			}
            pwnd->macros[i].setCode(textEdit->text());
			
            pwnd->macros[i].functions = names;
            //pwnd->macros[i].setCompipiled(bCompile);
			break;
        }

    }
}

void MacroEdit::showMacroMenu()//脚本菜单
{

}

//编译单个库代码
bool MacroEdit::compile()
{
	if (cmpTrd->isRunning())
	{
		return false;
	}
    msgOutput->clear();
	if (!table->isVisible())
	{
		table->setVisible(true);
	}
    save();

	QDir MacroDir = QDir("sdmacro\\jsrc\\jml");
	if(!MacroDir.exists())
	{
		MacroDir.mkpath(MacroDir.absolutePath());
	}
	MacroDir = QDir("sdmacro\\jsrc\\jrl");
	if(!MacroDir.exists())
	{
		MacroDir.mkpath(MacroDir.absolutePath());
	}

	if (!currentItem)
	{
		return false;
	}
    for(int i=0;i<pwnd->macros.size();i++)
    {
        if (!pwnd->macros[i].type)//JRL
        {
            cmpTrd->pushMacro(pwnd->macros[i]);
            //pwnd->macros[i].compile(cmpTrd);
            //cmpTrd->compileJRL(pwnd->macros[i]);
        }
    }
    for(int i=0;i<pwnd->macros.size();i++)
    {
        if(pwnd->macros[i].libName == currentItem->text(0))
        {
            cmpTrd->pushMacro(pwnd->macros[i]);
            //pwnd->macros[i].compile(cmpTrd);

            break;
        }
        /*
            if ()
			{
                bCompile = true;
				msgOutput->clear();
                QString date = QDateTime::currentDateTime().toString("hh:mm:ss");
                msgOutput->insertItem(0,date+":compile sucess!");

            }

        if(pwnd->macros[i].isCompiled())
        {
            currentItem->setIcon(0,QIcon(":/standardtool/images/standardtool/copy.ico"));
        }
        else
        {
            currentItem->setIcon(0,QIcon(":/standardtool/images/standardtool/delete.ico"));
        }
        */
	}
    if(cmpTrd)
        cmpTrd->start();
    return false;
}
bool MacroEdit::compileJML(MacroLibrary &library)
{

	return false;
}

bool MacroEdit::compileJRL(MacroLibrary &library)
{

	return false;
}
//插入系统函数
bool MacroEdit::insertFunction()
{	
	QString sLibName = comboSysLib->currentText();
	QString sFuncName = comboLibFun->currentText();
    QString code;
    if(sLibName.compare("FBase",Qt::CaseInsensitive) == 0)
    {
        //code = sFuncName;
    }
    //else
    {
        code = sLibName + "."+sFuncName;
    }
    if(currentItem && !textEdit->isReadOnly() && code != ".")
    {
        textEdit->insert(code);
		textEdit->setFocus();
    }
	return false;
}


//工具栏“插入函数”的响应
void MacroEdit::toolbarInsertFunc()
{	
	
}
void MacroEdit::hideMsgWindow()
{	
	if (table->isVisible())
	{
		table->setVisible(false);
	}
	else
		table->setVisible(true);

}
//新建变量
void MacroEdit::onNewVar()
{
    int rowIndex = -1;
    if(1 == table->currentIndex())//局部变量设定
    {
        //wxy 无脚本提示相应的提示信息
        QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr(""),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        msg.addButton(tr("确定"),QMessageBox::AcceptRole);
        if(!currentItem)
        {
            msg.setText(tr("请先添加相应的库！"));
            msg.exec();
            return;
        }

        for(int i=0;i<pwnd->macros.size();i++)
        {
            if( pwnd->macros[i].libName == currentItem->text(0))
            {
                pvarSettingWidget = new varSettingWidget(vartable);
                pvarSettingWidget->setDefault(pwnd->macros[i].vars(),defaultVar);
                if(pvarSettingWidget->exec() == QDialog::Accepted)
                {
                    pwnd->macros[i].appendVar( pvarSettingWidget->saveVar);
                    pwnd->macros[i].setCompipiled(false);
                    currentItem->setIcon(0,QIcon(":/standardtool/images/standardtool/delete.ico"));
                    rowIndex = vartable->rowCount()-1;
                    setRow(pvarSettingWidget->saveVar,rowIndex,vartable);
                    vartable->setRowCount(vartable->rowCount()+1);
                    vartable->setItem(vartable->rowCount()-1, 0, new QTableWidgetItem(tr("新建(单击右键)")));
                }
                return;
            }
        }
    }
    else if(2 == table->currentIndex())//全局变量设定
    {
        pvarSettingWidget = new varSettingWidget(gvartable,false,true);
        pvarSettingWidget->setDefault(pwnd->getGlobalVars(),defaultVar);
        if(pvarSettingWidget->exec() == QDialog::Accepted)
        {
            pwnd->appendGlobalVar(pvarSettingWidget->saveVar);
            refreshJML();
            //pwnd->macros[i].appendVar( pvarSettingWidget->saveVar);
            //pwnd->macros[i].setCompipiled(false);
            //currentItem->setIcon(0,QIcon(":/standardtool/images/standardtool/delete.ico"));

            rowIndex = gvartable->rowCount()-1;
            setRow(pvarSettingWidget->saveVar,rowIndex,gvartable);
            gvartable->setRowCount(gvartable->rowCount()+1);
            gvartable->setItem(gvartable->rowCount()-1, 0, new QTableWidgetItem(tr("新建(单击右键)")));
        }
        return;
    }
}

//编辑变量
void MacroEdit::onEditVar()
{
    QTableWidget* pVartable = NULL;
    if(1 == table->currentIndex())
    {
        pVartable = vartable;
    }
    else if(2 == table->currentIndex())
    {
        pVartable = gvartable;
    }
    int row = pVartable->currentRow();

    if(row > pVartable->rowCount()-1 || !currentItem)
    {
        return;
    }
    else if(row == pVartable->rowCount()-1)
    {
        onNewVar();
        return;
    }

    QString vName = pVartable->item(row,0)->text();
    int i =0;
    int j =0;
    bool bExist = false;
    if(1 == table->currentIndex())
    {
        for(;i<pwnd->macros.size();i++)
        {
            if( pwnd->macros[i].libName == currentItem->text(0))
            {
                bExist = true;
                break;
            }

        }
        if (!bExist)
        {
            return ;
        }
        for (bExist = false; j<pwnd->macros[i].vars().size(); j++)
        {
            if (pwnd->macros[i].vars().at(j).varName == vName)
            {
                bExist = true;
                break;
            }
        }


        if (bExist)
        {
            pvarSettingWidget = new varSettingWidget(pVartable);
            pvarSettingWidget->setDefault(pwnd->macros[i].vars(),pwnd->macros[i].vars().at(j));
            if (pvarSettingWidget->exec() == QDialog::Accepted)
            {
                QVector <VarPro> vars = pwnd->macros[i].vars();
                vars.replace(j,pvarSettingWidget->saveVar);
                pwnd->macros[i].setVar(vars);
                pwnd->macros[i].setCompipiled(false);
                currentItem->setIcon(0,QIcon(":/standardtool/images/standardtool/delete.ico"));
                setRow(pvarSettingWidget->saveVar,row,pVartable);
            }
        }
    }
    else if(2 == table->currentIndex())
    {
        for (bExist = false; j<pwnd->getGlobalVars().size(); j++)
        {
            if (pwnd->getGlobalVars().at(j).varName == vName)
            {
                bExist = true;
                break;
            }
        }


        if (bExist)
        {
            pvarSettingWidget = new varSettingWidget(pVartable,false,true);
            pvarSettingWidget->setDefault(pwnd->getGlobalVars(),pwnd->getGlobalVars().at(j));
            if (pvarSettingWidget->exec() == QDialog::Accepted)
            {
                QVector <VarPro> vars = pwnd->getGlobalVars();
                vars.replace(j,pvarSettingWidget->saveVar);
                pwnd->setGlobalVar(vars);
                refreshJML();
                setRow(pvarSettingWidget->saveVar,row,pVartable);
            }
        }
    }
}

void MacroEdit::onNewMulti()
{
    int rowIndex = -1;
    if(1 == table->currentIndex())
    {
        if(!currentItem)
            return;
        for(int i=0;i<pwnd->macros.size();i++)
        {
            if( pwnd->macros[i].libName == currentItem->text(0))
            {
                pvarSettingWidget = new varSettingWidget(vartable,true);
                pvarSettingWidget->setDefault(pwnd->macros[i].vars(),defaultVar);

                if(pvarSettingWidget->exec() == QDialog::Accepted)
                {
                    pwnd->macros[i].setCompipiled(false);
                    currentItem->setIcon(0,QIcon(":/standardtool/images/standardtool/delete.ico"));

                    foreach(VarPro cVar,pvarSettingWidget->saveVars)
                    {
                        pwnd->macros[i].appendVar(cVar);

                        rowIndex = vartable->rowCount()-1;
                        setRow(cVar,rowIndex,vartable);

                        vartable->setRowCount(vartable->rowCount()+1);

                        vartable->setItem(vartable->rowCount()-1, 0,
                                          new QTableWidgetItem(tr("新建(单击右键)")));
                    }
                }
                break;
            }

        }
    }
    else if(2 == table->currentIndex())
    {
        pvarSettingWidget = new varSettingWidget(gvartable,true,true);
        pvarSettingWidget->setDefault(pwnd->getGlobalVars(),defaultVar);
        if(pvarSettingWidget->exec() == QDialog::Accepted)
        {
            foreach(VarPro cVar,pvarSettingWidget->saveVars)
            {
                pwnd->appendGlobalVar(cVar);
                rowIndex = gvartable->rowCount()-1;
                setRow(cVar,rowIndex,gvartable);
                gvartable->setRowCount(gvartable->rowCount()+1);
                gvartable->setItem(gvartable->rowCount()-1, 0,
                                  new QTableWidgetItem(tr("新建(单击右键)")));
            }
            refreshJML();
        }
    }
}
//删除变量
void MacroEdit::onDelVar()
{
    QTableWidget* pVartable = NULL;
    if(1 == table->currentIndex())
    {
        pVartable = vartable;
    }
    else if(2 == table->currentIndex())
    {
        pVartable = gvartable;
    }
    QString msg ;
    msg = tr("是否删除变量？");
    QMessageBox box(QMessageBox::Information,tr("确认"),msg,QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    box.button(QMessageBox::Ok)->setText(tr("删除"));
    box.button(QMessageBox::Cancel)->setText(tr("取消"));

    box.exec();
    if(box.clickedButton() == box.button(QMessageBox::Cancel))
    {
        return;
    }

    //wxy list的数目只会是1
    QList<QTableWidgetSelectionRange> list = pVartable->selectedRanges();
    int iTopRow = list.at(0).topRow();
    int iBottomRow = list.at(0).bottomRow();
    for(int i = iBottomRow; i >= iTopRow; i--)//wxy 逆序删除，保证删除元素的正确性
    {
        int row = /*pVartable->currentRow()*/i;

        if(row >= pVartable->rowCount()-1 || !currentItem)
        {
            return;
        }

        QString vName = pVartable->item(row,0)->text();
        int i =0;
        int j =0;
        bool bExist = false;
        if(1 == table->currentIndex())
        {
            for(;i<pwnd->macros.size();i++)
            {
                if( pwnd->macros[i].libName == currentItem->text(0))
                {
                    bExist = true;
                    break;
                }

            }
            if (!bExist)
            {
                return ;
            }
            for (bExist = false; j<pwnd->macros[i].vars().size(); j++)
            {
                if (pwnd->macros[i].vars().at(j).varName == vName)
                {
                    bExist = true;
                    break;
                }
            }

            if (bExist)
            {
                QVector <VarPro> vars = pwnd->macros[i].vars();
                vars.remove(j);
                pwnd->macros[i].setVar(vars);
                pwnd->macros[i].setCompipiled(false);
                currentItem->setIcon(0,QIcon(":/standardtool/images/standardtool/delete.ico"));
                pVartable->removeRow(row);
            }
        }
        else if(2 == table->currentIndex())
        {
            for (bExist = false; j<pwnd->getGlobalVars().size(); j++)
            {
                if (pwnd->getGlobalVars().at(j).varName == vName)
                {
                    bExist = true;
                    break;
                }
            }

            if (bExist)
            {
                QVector <VarPro> vars = pwnd->getGlobalVars();
                vars.remove(j);
                pwnd->setGlobalVar(vars);
                refreshJML();
                pVartable->removeRow(row);
            }
        }
    }
}

//判断一条脚本是否编译成功
QByteArray MacroEdit::getCompileRestlt(QString libName,bool libType)
{
	QString path;
    QByteArray md5;
	if (libType)
	{
        path = QDir::currentPath()+"\\sdmacro\\ml\\class\\jml\\"+libName;
	}
	else
	{
        path = QDir::currentPath()+"\\sdmacro\\ml\\class\\jrl\\"+libName;
	}
	path +=".class";
        path.replace("/","\\");

	QFileInfo file(path);
    if (!file.exists())
	{
        return md5;
    }
    return MacroCmptrd::getFileMd5(path);
}

void MacroEdit::setRow(VarPro cVar,int row, QTableWidget* pVartable)
{
	QStringList typeStr;
	typeStr << tr("bool值")<<tr("16位整数")<<tr("16位正整数")<<tr("32位整数")<<tr("32位正整数")
		<< tr("bool数组")<<tr("16位整数数组")<<tr("16位正整数数组")<<tr("32位整数数组")
        <<tr("32位正整数数组")<<tr("32位浮点数")<<tr("32位浮点数数组")<<tr("16位BCD码")
        <<tr("16位BCD码数组")<<tr("32位BCD码")<<tr("32位BCD码数组")<< tr("ASCII字符串")
        << tr("Unicode字符串");

	QString sType = "";

	if (cVar.dataType <typeStr.size() && cVar.dataType >= 0)
	{
		sType = typeStr.at(cVar.dataType);
	}

	int len = 1;
    QString sLen = "1";
	switch (cVar.dataType)
	{
	case 0:
	case 1:
	case 2:
	case 5:
    case 6:
    case 7:
    case 12:
    case 13:
    case 16:
		len = 1;
		break;
	default:
		len = 2;
		break;
	}
	sLen = QString::number(len*cVar.count);
	QStringList StrRW;
	StrRW << tr("读")<<tr("写")<<tr("读写");

	QString sRW = "";

	if (cVar.RWPerm <StrRW.size() && cVar.RWPerm >= 0)
	{
		sRW = StrRW.at(cVar.RWPerm);
	}
    pVartable->setItem(row, 0, new QTableWidgetItem(cVar.varName));
    pVartable->setItem(row, 1, new QTableWidgetItem(sType));
    pVartable->setItem(row, 2, new QTableWidgetItem(sLen));
    pVartable->setItem(row, 3, new QTableWidgetItem(sRW));

	QString sAddrType = tr("内部地址");
	if (cVar.addr.nConnectType != 0)
	{
		sAddrType = tr("外部地址");
	}
    pVartable->setItem(row, 4, new QTableWidgetItem(sAddrType));
    pVartable->setItem(row, 5, new QTableWidgetItem(cVar.addr.sShowAddr));
    if(cVar.bOffset)
    {
        pVartable->setItem(row, 6, new QTableWidgetItem(cVar.offsetAddr.sShowAddr));
    }
    else
    {
        pVartable->setItem(row, 6, new QTableWidgetItem(tr("无")));
    }
}

void MacroEdit::setTypeMap()
{
	typeMap.clear();
	typeMap.insert(0,"BoolHolder ");//bool值
	typeMap.insert(1,"ShortHolder ");//16位整数
	typeMap.insert(2,"UShortHolder ");//16位正整数
	typeMap.insert(3,"IntHolder ");//32位整数
	typeMap.insert(4,"UIntHolder ");//32位正整数
    typeMap.insert(5,"BoolSeqHolder ");//bool数组
    typeMap.insert(6,"ShortSeqHolder ");//16位整数数组
	typeMap.insert(7,"UShortSeqHolder ");//16位正整数数组
    typeMap.insert(8,"IntSeqHolder ");//32位整数数组
	typeMap.insert(9,"UIntSeqHolder ");//32位正整数数组
    typeMap.insert(10,"FloatHolder ");//32位浮点数
	typeMap.insert(11,"FloatSeqHolder ");//32位浮点数数组
    typeMap.insert(12,"Bcd16Holder ");//16位BCD码
    typeMap.insert(13,"Bcd16SeqHolder ");//16位BCD码数组
    typeMap.insert(14,"Bcd32Holder ");//32位BCD码
    typeMap.insert(15,"Bcd32SeqHolder ");//32位BCD码数组
    typeMap.insert(16,"StringHolder ");//字符串
    typeMap.insert(17,"StringHolder ");//字符串
}

void MacroEdit::showErrorLog(QString libName,QString log)
{
    table->setCurrentWidget(msgOutput);
    //msgOutput->clear();
    //msgOutput->setAutoScroll(true);
    QStringList lst = log.split("\r\n");
    qDebug()<<"log line count "<< lst.size();
    for(int i=0; i<lst.size();i++)
    {
        msgOutput->appendPlainText(lst.at(i)+"\r\n");
    }
    QTreeWidgetItem * cItem = NULL;
    for(int i=0; i<rootJRL->childCount();i++)
    {
        qDebug() << rootJRL->child(i)->text(0) << libName;
        if(rootJRL->child(i)->text(0) == libName)
        {
            cItem = rootJRL->child(i);
            break;
        }
    }
    for(int i=0; i<rootJML->childCount();i++)
    {
        qDebug() << rootJML->child(i)->text(0) << libName;
        if(rootJML->child(i)->text(0) == libName)
        {
            cItem = rootJML->child(i);
            break;
        }
    }

    for(int i=0;i<pwnd->macros.size();i++)
    {
        qDebug()<<pwnd->macros[i].libName<< ": MD5 = " << pwnd->macros[i].MD5();
        qDebug() << pwnd->macros[i].libName << ":compile result "<<pwnd->macros[i].isCompiled();

        if((pwnd->macros[i].libName == libName) && cItem)
        {
			QString cTime = QTime::currentTime().toString();
            if(pwnd->macros[i].isCompiled())
            {
				
                cItem->setIcon(0,QIcon(":/standardtool/images/standardtool/copy.ico"));
                msgOutput->appendPlainText(tr("[%1]编译脚本 %2 成功").arg(cTime).arg(libName));
            }
            else
            {
                cItem->setIcon(0,QIcon(":/standardtool/images/standardtool/delete.ico"));
                msgOutput->appendPlainText(tr("[%1]编译脚本 %2 失败").arg(cTime).arg(libName));
            }
        }

    }
}
//右键 脚本浏览器
void MacroEdit::pressTree(QTreeWidgetItem*item,int col)
{
    if (qApp->mouseButtons() != Qt::RightButton)
    {
        return;
    }
    QMenu menu(tree);
    if(item == rootJRL || item == rootJML)
    {

        QAction *openJML= menu.addAction(tr("添加脚本库"));
        QAction *openJRL= menu.addAction(tr("添加函数库"));

        connect(openJML,SIGNAL(triggered()),this,SLOT(slotAddJML()));
        connect(openJRL,SIGNAL(triggered()),this,SLOT(slotAddJRL()));
        menu.exec(QCursor::pos());
    }
    else if(item->parent() == rootJRL || item->parent() == rootJML)
    {
        QAction *openJML= menu.addAction(tr("编辑"));
        QAction *openJRL= menu.addAction(tr("删除"));

        connect(openJML,SIGNAL(triggered()),this,SLOT(slotEdit()));
        connect(openJRL,SIGNAL(triggered()),this,SLOT(slotDelete()));
        if(item->parent() == rootJML)
        {
            QAction *rename = menu.addAction(tr("重命名"));
            connect(rename, SIGNAL(triggered()), this, SLOT(rename()));
        }
        menu.exec(QCursor::pos());
    }
	else
	{
		menuOnFunction(item);
	}

}

//右键函数名的时候，添加菜单
void MacroEdit::menuOnFunction(QTreeWidgetItem *item)
{
	if (!item)
	{
		return;
	}
	QMenu menu(tree);
	QList<QTreeWidgetItem* > JML_items;
	QList<QTreeWidgetItem* > JRL_items;
	for(int i=0;i<rootJRL->childCount();i++)
	{
		JRL_items << rootJRL->child(i);
	}
	for(int i=0;i<rootJML->childCount();i++)
	{
		JML_items << rootJML->child(i);
	}

    //QAction *newFunction= menu.addAction(tr("新建函数"));
	QAction *insertFunction= menu.addAction(tr("引用函数"));

	insertCode = item->text(0)+"( )";
	insertCode = item->parent()->text(0)+"."+insertCode;

    //connect(newFunction,SIGNAL(triggered()),this,SLOT(newFuncCode()));
	connect(insertFunction,SIGNAL(triggered()),this,SLOT(insertFuncCode()));
	if (JML_items.contains(item->parent()))
	{
		//右键 脚本函数
		insertFunction->setEnabled(false);
		menu.exec(QCursor::pos());
	}
	else if (JRL_items.contains(item->parent()))
	{
		//右键  函数库函数
		
		bool bCmp = false;

        Macro *curLibrary = getLibrarys(item->parent()->text(0));
        if (curLibrary && curLibrary->isCompiled())
		{
			bCmp = true;
		}
		if (textEdit->isReadOnly() || !bCmp)
		{
			insertFunction->setEnabled(false);
		}

		menu.exec(QCursor::pos());
	}
	
}
//添加脚本库
void MacroEdit::slotAddJML()
{
    QTreeWidgetItem *item = NULL;
    Macro lib;
    AddLib addWzrd(pwnd->macros,this);
    addWzrd.setWindowTitle(tr("添加脚本库"));
    if(addWzrd.exec() == QDialog::Accepted)
    {
        lib.libName = addWzrd.libName;
        lib.type = true;
        lib.setCompipiled(false);
        lib.setCode(SCRIPT_HEADER);
        pwnd->macros.append(lib);
        item = new QTreeWidgetItem(rootJML, QStringList(lib.libName));
		//tree->setCurrentItem(item);
		treeItemChanged(item,0);
    }
}

//添加函数库
void MacroEdit::slotAddJRL()
{
    QTreeWidgetItem *item = NULL;
    Macro lib;
    AddLib addWzrd(pwnd->macros,this);
    addWzrd.setWindowTitle(tr("添加函数库"));
    if(addWzrd.exec() == QDialog::Accepted)
    {
        lib.libName = addWzrd.libName;
        lib.type = false;
        lib.setCompipiled(false);
        lib.setCode(SYS_FUNCTION_HEADER);
        pwnd->macros.append(lib);
        item = new QTreeWidgetItem(rootJRL, QStringList(lib.libName));
		//tree->setCurrentItem(item);
		treeItemChanged(item,0);
    }
}

void MacroEdit::slotDelete()
{
    QTreeWidgetItem *item = tree->currentItem();
    QString msg ;
    msg = tr("是否删除：%1？").arg(item->text(0));
    QMessageBox box(QMessageBox::Information,tr("确认"),msg,QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    box.button(QMessageBox::Ok)->setText(tr("删除"));
    box.button(QMessageBox::Cancel)->setText(tr("取消"));

    box.exec();
    if(box.clickedButton() == box.button(QMessageBox::Cancel))
    {
        return;
    }


    if(item->parent() == rootJML || item->parent() == rootJRL)
    {
        item->parent()->removeChild(item);
        for(int i =0;i<pwnd->macros.size();i++)
        {
                if( pwnd->macros[i].libName == item->text(0))
                {
                        pwnd->macros.remove(i);
                        //wxy脚本库被删除必须重新编译脚本
                        QFile::remove("sdmacro\\ml\\ml.jar");
                        break;
                }

        }
    }
    if (item == currentItem)
    {
		textEdit->clear();
		textEdit->setModified(false);
		if (rootJML->childCount()>0)
		{
			currentItem = 0;
			treeItemChanged(rootJML->child(0),0);
		}
		else if (rootJRL->childCount()>0)
		{
			currentItem = 0;
			treeItemChanged(rootJRL->child(0),0);
		}
		else
		{
			textEdit->setReadOnly(true);
			libNameEdit->setText("");
            reloadVars("",vartable);
        }
    }
	
}
void MacroEdit::slotEdit()
{
    
    QTreeWidgetItem *item = tree->currentItem();
    //currentItem = item;
    treeItemChanged(item,0);
    
}
void MacroEdit::libChanged(QString libName)
{
    comboLibFun->clear();
    sysLibTips->clear();
    foreach(stScriptLib syslib,pwnd->sysLibs)
    {
        if(syslib.LibName == libName)
        {
            foreach(stMemberFun function,syslib.functions)
            {
                comboLibFun->addItem(function.funName);

            }
            if(syslib.functions.size()>0)
            {
                sysLibTips->setPlainText(syslib.functions.first().daemon);
            }
        }
    }
}

void MacroEdit::funcChanged(QString funcName)
{

    QString libName = comboSysLib->currentText();

    qDebug() << "funcChanged" << libName;
    sysLibTips->clear();
    foreach(stScriptLib syslib,pwnd->sysLibs)
    {
        if(syslib.LibName == libName)
        {
            qDebug() << "syslib.LibName == libName";
            foreach(stMemberFun function,syslib.functions)
            {
                if(function.funName == funcName)
                {
                    sysLibTips->setPlainText(function.daemon);
                    break;
                }

            }
            break;
        }
    }

}
//加载系统函数库到UI
void MacroEdit::initSysLib()
{

    sysLibTips->setReadOnly(true);
    foreach(stScriptLib syslib,pwnd->sysLibs)
    {
        comboSysLib->addItem(syslib.LibName);
    }
    if(pwnd->sysLibs.size()>0)
    {
        stScriptLib currentlib = pwnd->sysLibs.first();
        foreach(stMemberFun function,currentlib.functions)
        {
            comboLibFun->addItem(function.funName);            
        }
        if(currentlib.functions.size()>0)
        {
            sysLibTips->setPlainText(currentlib.functions.first().daemon);
        }
    }
    connect(comboSysLib,SIGNAL(currentIndexChanged(QString)),this,SLOT(libChanged(QString)));
    connect(comboLibFun,SIGNAL(currentIndexChanged(QString)),this,SLOT(funcChanged(QString)));

    connect(insertFuncBtn,SIGNAL(clicked()),this,SLOT(insertFunction()));

}

void MacroEdit::closeEvent(QCloseEvent *event)
{
    if(cmpTrd && cmpTrd->isRunning())
    {
        cmpTrd->terminate();
        //event->ignore();
        //return;
    }
	QString code = textEdit->text();
	if(textEdit->isModified() && currentItem)
	{
		//询问是否保存
		QString msg ;
		msg = tr("是否保存代码到函数库：")+currentItem->text(0);
		QMessageBox box(QMessageBox::Information,tr("未保存"),msg,QMessageBox::Ok|QMessageBox::Cancel|QMessageBox::Close,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

		box.button(QMessageBox::Ok)->setText(tr("保存"));
		box.button(QMessageBox::Cancel)->setText(tr("取消"));
		box.button(QMessageBox::Close)->setText(tr("不保存"));

		box.exec();
		if(box.clickedButton() == box.button(QMessageBox::Ok))
		{
			save();
		}
		else if (box.clickedButton() == box.button(QMessageBox::Cancel))
		{
			event->ignore();
			return;
		}
	}
}
Macro * MacroEdit::getLibrarys(QString libName)
{
    Macro * retLibrary = NULL;
    foreach(Macro library,pwnd->macros)
	{
		if(library.libName == libName)
		{
			retLibrary = &library;
			break;
		}

	}
	return retLibrary;
}
//引用 库函数
void MacroEdit::insertFuncCode()
{
	textEdit->insert(insertCode);
}

//新建函数
void MacroEdit::newFuncCode()
{}

//函数库改变之后，引用该库的脚本库都要设为未编译
void MacroEdit::funlibChanged(QString libName)
{
    qDebug() << "funlibChanged "<<libName;
	QRegExp reganno = QRegExp("/\\*.{0,}\\*/");
	reganno.setMinimal(true);

	QString nstr = "\\b"+libName+".";
	QRegExp regcalled = QRegExp(nstr);
    for (int i=0; i<pwnd->macros.size(); i++)
	{
        QString code;
        QStringList lines = pwnd->macros[i].code().split("\r\n");
		//去掉单行注释
        for(int j=0; j< lines.size(); j++)
		{
            QString line = lines[j];
			line.remove(QRegExp("//."));
			code.append(line);
		}
		//去掉多行注释

		code.remove(reganno);

		int count = code.count(regcalled);
        qDebug() << "count :" <<count;
        qDebug() << "code :" <<code;
        qDebug() << "regcalled :" <<nstr;
        if (count > 0)
		{
            pwnd->macros[i].setCompipiled(false);
			for(int j=0; j<rootJML->childCount();j++)
			{
                if(rootJML->child(j)->text(0) == pwnd->macros[i].libName)
				{
                    rootJML->child(j)->setIcon(0,QIcon(":/standardtool/images/standardtool/delete.ico"));
				}
			}
		}
	}
}


//从文件载入
void MacroEdit::onLoadCode()
{
	if(!currentItem)
		return;
	QString filename = QFileDialog::getOpenFileName(this,tr("选择要载入的文件"),
		pwnd->sFilePath,
		tr("TEXT Files (*.java *.txt)"));
	QFile fp(filename);
	QTextStream stream(&fp);
	if (fp.open(QIODevice::ReadOnly))
	{
		QString code;
		code = stream.readAll();
		textEdit->setText(code);
		textEdit->setModified(false);
	}
}

//导出为文件
void MacroEdit::onSaveCode()
{
	QString code = textEdit->text();
	if (code.isEmpty())
	{
		return ;
	}
	QFileDialog::Options options;
	QString selectedFilter;
	QString dir = QFileDialog::getSaveFileName(this,
		tr("选择要存储的位置"),
		pwnd->sFilePath,
		tr("TEXT Files (*.txt)"),
		&selectedFilter,
		options);

	if (!dir.isEmpty())
	{
		if (dir.endsWith(".txt"),false)
		{
			dir.append(".txt");
		}
		QFile fp(dir);
		QTextStream stream(&fp);
		
		if (fp.open(QIODevice::WriteOnly))
		{
			stream << code;
			fp.close();
		}
		
	}
}
void MacroEdit::onCompileAll()
{
	if (cmpTrd->isRunning())
	{
		return;
	}
	if (!table->isVisible())
	{
		table->setVisible(true);
	}
	save();

	QDir MacroDir = QDir("sdmacro\\jsrc\\jml");
	if(!MacroDir.exists())
	{
		MacroDir.mkpath(MacroDir.absolutePath());
	}
	MacroDir = QDir("sdmacro\\jsrc\\jrl");
	if(!MacroDir.exists())
	{
		MacroDir.mkpath(MacroDir.absolutePath());
	}

    //wxy 必须优先编译函数库
	for(int i=0;i<pwnd->macros.size();i++)
	{
        if (!pwnd->macros[i].type)//JRL
		{
			cmpTrd->pushMacro(pwnd->macros[i]);
		}
	}
	for(int i=0;i<pwnd->macros.size();i++)
	{
        if(pwnd->macros[i].type)//JML
        {
            cmpTrd->pushMacro(pwnd->macros[i]);
        }
	}
	if(cmpTrd)
		cmpTrd->start();
	
}

void MacroEdit::disableUi()
{
    tree->setEnabled(false);
    toolbar->setEnabled(false);
    insertFuncBtn->setEnabled(false);
    textEdit->setReadOnly(true);
}

void MacroEdit::enableUi()
{
    tree->setEnabled(true);
    toolbar->setEnabled(true);
    insertFuncBtn->setEnabled(true);
    textEdit->setReadOnly(false);
}
void MacroEdit::reject()
{
    close();
}

void MacroEdit::addMacro()
{
    QMenu menu(this);
    QAction *openJML= menu.addAction(tr("添加脚本库"));
    QAction *openJRL= menu.addAction(tr("添加函数库"));

    connect(openJML,SIGNAL(triggered()),this,SLOT(slotAddJML()));
    connect(openJRL,SIGNAL(triggered()),this,SLOT(slotAddJRL()));
    menu.exec(QCursor::pos());
}

void MacroEdit::onFind()
{
    if(!findDlg)
    {
        findDlg = new FindDialog(this);
        connect(findDlg, SIGNAL(findFirst(QString,bool,bool,bool,bool,bool)), this,
                         SLOT(findFirst(QString,bool,bool,bool,bool,bool)));
        connect(findDlg, SIGNAL(findNext()), this, SLOT(findNext()));
        connect(findDlg, SIGNAL(replace(const QString&)), this, SLOT(replace(const QString&)));
    }
    findDlg->show();
    findDlg->activateWindow();
}

void MacroEdit::findFirst(const QString &expr, bool re, bool cs, bool wo, bool wrap, bool forward)
{
    bool bFind = textEdit->findFirst(expr, re, cs, wo, wrap, forward);
    findDlg->setFindTextResult(bFind);
    findDlg->setIsFindFirst(!bFind);
    if(false == bFind)
    {
        QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr(""),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        msg.addButton(tr("确定"),QMessageBox::AcceptRole);
        QString strMsg = QString(tr("找不到\"%1\"")).arg(expr);
        msg.setText(strMsg);
        msg.exec();
    }
}

void MacroEdit::findNext()
{
   bool bFind = textEdit->findNext();
   findDlg->setFindTextResult(bFind);
}

void MacroEdit::replace(const QString &test)
{
  textEdit->replace(test);
  findDlg->setFindTextResult(false);
}

void MacroEdit::refreshJML()
{
    //wxy添加全局变量将所有脚本库置为未编译
    for(int j = 0; j < pwnd->macros.size(); j++)
    {
        if(pwnd->macros[j].type)
        {
            pwnd->macros[j].setCompipiled(false);
        }
    }
    for(int k=0; k<rootJML->childCount();k++)
    {
        QTreeWidgetItem* treeItem= rootJML->child(k);
        if(treeItem)
        {
            treeItem->setIcon(0,QIcon(":/standardtool/images/standardtool/delete.ico"));
        }
    }
}

void MacroEdit::rename()
{
    QTreeWidgetItem *item = tree->currentItem();
    if(item)
    {
        QString strPreLibName = item->text(0);
        AddLib addWzrd(pwnd->macros,this);
        addWzrd.setWindowTitle(tr("修改库名称"));
        addWzrd.setEditString(strPreLibName);
        if(addWzrd.exec() == QDialog::Accepted)
        {
            QString strNewLibName = addWzrd.libName;
            for(int i=0;i<pwnd->macros.size();i++)
            {
                if( pwnd->macros[i].libName == strPreLibName)
                {
                    pwnd->macros[i].libName = strNewLibName;
                    pwnd->macros[i].setCompipiled(false);
                    item->setText(0, strNewLibName);
                    item->setIcon(0,QIcon(":/standardtool/images/standardtool/delete.ico"));
                    break;
                }
            }
        }
    }
}
