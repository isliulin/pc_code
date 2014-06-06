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
    label = new QLabel(tr("�����������"),this);
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
	edit->setToolTip(tr("��Ч�ַ�:A-Z,a-z,0-9,_"));
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
        msg->setText(tr("������ֻ��Ϊ��Ӣ���ַ������֡��»���"));
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
            msg->setText(libName+tr(" �Ѵ���"));
            return ;
        }

    }
    if(reWords.contains(libName))
    {
        bExist = true;
        msg->setText(libName+tr(" �Ǳ����ؼ���"));
        return ;
    }

    if(!libName.isEmpty())
    {

        QRegExp regExp("^[A-Za-z_][0-9a-zA-Z_]{0,20}$");
        if(libName.indexOf(regExp) <0)
        {
            msg->setText(tr("������ֻ��Ϊ��Ӣ���ַ������֡��»���"));
            return ;
        }
        QDialog::accept();
    }
    else
        msg->setText(tr("�����Ʋ���Ϊ�գ�"));
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
    label = new QLabel(tr("��������:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    labelReplace = new QLabel(tr("�滻Ϊ:"));
    editReplace = new QLineEdit;
    labelReplace->setBuddy(editReplace);

    caseCheckBox = new QCheckBox(tr("ƥ���Сд(&M)"));
    backwardCheckBox = new QCheckBox(tr("��ǰ����(&S)"));
    worldMatchCheckBox = new QCheckBox(tr("����ƥ��(&O)"));
    rExpCheckBox = new QCheckBox(tr("������ʽ(&E)"));

    findButton = new QPushButton(tr("����(&F)"));
    findButton->setDefault(true);
    findButton->setEnabled(false);

    closeButton = new QPushButton(tr("�ر�(&C)"));

    replaceButton = new QPushButton(tr("�滻(&R)"));

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


    setWindowTitle(tr("����"));
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
    this->setWindowTitle(tr("�ű������"));
    qDebug() << "MacroEdit::MacroEdit";
    lName = currentName;
    labelnothing = new QLabel(tr(""),this);
    labelLst = new QLabel(tr("�ű�"),this);
    addMacroBtn = new QPushButton(tr(""),this);
    addMacroBtn->setFlat(true);
    addMacroBtn->setIcon(QIcon(":/standardtool/images/standardtool/newscreen.ico"));
    addMacroBtn->setToolTip(tr("��ӽű�"));

    QHBoxLayout *firstlayout = new QHBoxLayout();
    firstlayout->addWidget(labelLst);
    firstlayout->addWidget(addMacroBtn);
    firstlayout->setStretch(0,3);
    firstlayout->setStretch(1,1);
    tree = new QTreeWidget(this);

    //



	groupSysLib = new QGroupBox(tr("���ϵͳ����"),this);
	QVBoxLayout *glayout = new QVBoxLayout(groupSysLib);

	labelSlecetLib = new QLabel(tr("������"),this);
	labelSlecetFun = new QLabel(tr("��������"),this);
	comboSysLib = new QComboBox(this);
	comboLibFun = new QComboBox(this);
	insertFuncBtn = new QPushButton(tr(""),this);
	insertFuncBtn->setFlat(true);
	insertFuncBtn->setIcon(QIcon(":/debug/images/debug/macro.ico"));
    insertFuncBtn->setToolTip(tr("���ú���"));
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



    labelLib = new QLabel(tr("������"),this);
    libNameEdit = new QLineEdit(this);
    libNameEdit->setEnabled(false);
    labelLib->setBuddy(libNameEdit);



    table = new QTabWidget(this);
    textEdit = new QsciScintillaEx(this);

    QVBoxLayout *editLayout = new QVBoxLayout();

    //����������
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

	//���ñ༭�������
	initHighlighter();



    setLayout(mainLayout);

    //resize(800,600);

    //��ʼ�����νṹ���� �ű���
    initLibTree();

    //��ʼ�������趨����Ϣ�������
    initTabWidget();

    

	//�������Ͷ�Ӧ�������ַ���
	setTypeMap();

    initSysLib();
    /*add by wuxiyang��ʼ�������ŵ����캯������ȥ��
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

//��ʼ�����νṹ���� �ű���
void MacroEdit::initLibTree()
{
    qDebug() << "MacroEdit::initLibTree";
    rootJML = new QTreeWidgetItem(tree, QStringList(tr("�ű�")));
    rootJRL = new QTreeWidgetItem(tree, QStringList(tr("������")));

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
        //��ӿ����Ƶ����νṹ����
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

        //��Ӻ�������Ϊ����������
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

//��ʼ����Ϣ������� �� �����趨����
void MacroEdit::initTabWidget()
{
    msgOutput = new QPlainTextEdit(this);
    QVBoxLayout *msglayout = new QVBoxLayout;
    msglayout->addWidget(msgOutput);
    vartable = new QTableWidget(this);
    initVarTable(vartable,LOCAL_VARTABLE);
    gvartable = new QTableWidget(this);
    initVarTable(gvartable,GLOBAL_VARTABLE);

    table->addTab(msgOutput,tr("��Ϣ���"));
    table->addTab(vartable,tr("�����趨"));
    table->addTab(gvartable,tr("ȫ�ֱ����趨"));
    table->setCurrentWidget(vartable);

}
void MacroEdit::initVarTable(QTableWidget *pVartable, int iIndex)
{
    //pVartable = new QTableWidget(this);

    newVarAction = new QAction(tr("�½�����"),pVartable);
    batVarAction = new QAction(tr("�����½�"),pVartable);
    editVarAction = new QAction(tr("�༭����"),pVartable);
    delVarAction = new QAction(tr("ɾ������"),pVartable);


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

    /*�����趨����������ã�����Ϊ����ѡ������,���ɱ༭ ����ѡ�����*/
    pVartable->setSelectionBehavior(QAbstractItemView::SelectRows);
    pVartable->setSelectionMode(QAbstractItemView::ContiguousSelection);
    pVartable->setEditTriggers(QAbstractItemView::NoEditTriggers);


    /*��˫�������趨���ʱ,���������༭�Ի���*/
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
	
    pVartable->setItem(0, 0, new QTableWidgetItem(tr("�½�")));


	/*���ñ��������ı�*/
	QStringList Labels;
	Labels<<tr("������")<<tr("�������")<<tr("��ַ����")<<tr("��д����")
                <<tr("��ַ����")<<tr("��ַ")<<tr("ƫ�Ƶ�ַ");
    pVartable->setHorizontalHeaderLabels(Labels);

	/*���ñ���п��С*/
    pVartable->setColumnWidth(0,100);//������
    pVartable->setColumnWidth(1,100);//�������
    //wxy��ʵ�������С�޸ı���п�
    pVartable->setColumnWidth(2,60);//��ַ����
    pVartable->setColumnWidth(3,60);//��д����
    pVartable->setColumnWidth(4,75);//��ַ����
    pVartable->setColumnWidth(5,200);//��ַ
    pVartable->setColumnWidth(6,200);//ƫ�Ƶ�ַ

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
        pVartable->setItem(pVartable->rowCount()-1, 0, new QTableWidgetItem(tr("�½�(�����Ҽ�)")));

	}
}
//���ø����༭�������
void MacroEdit::initHighlighter()
{
    //����������
    textEdit->setMarginLineNumbers(1,true);

    textEdit->setMarginsBackgroundColor(QColor(210,210,200,255));
    textEdit->setMarginsForegroundColor(QColor(0x8B,0x96,0xAB,255));
    textEdit->setMarginWidth(1,"99999");
    textEdit->setMarginsFont(QFont(QString(QFont::Courier),-1,-1,false));
    textEdit->setMarginSensitivity(1,true);


    //������۵�
    textEdit->setFoldMarginColors(QColor(230,230,230,255),QColor(230,230,230,255));
    textEdit->setFolding(QsciScintilla::BoxedFoldStyle);

    //�Զ�����
    textEdit->setAutoIndent(true);
    textEdit->setIndentationGuides(true);
    textEdit->setIndentationsUseTabs(true);
    textEdit->setIndentationGuidesBackgroundColor(QColor(230,230,230,255));
    textEdit->setIndentationGuidesForegroundColor(QColor(230,230,230,255));



    //java�﷨����
    QsciLexerJava *jlexer = new QsciLexerJava;
    textEdit->setLexer(jlexer);

    //���õ�ǰ�и���
    textEdit->setCaretLineVisible(true);
    textEdit->setCaretLineBackgroundColor(QColor(230,230,230,255));


    //ʹ��utf8
    textEdit->setUtf8(true);


    //�Զ���ʾ

    //connect(textEdit, SIGNAL(marginClicked(int, int, Qt::KeyboardModifiers)),this, SLOT(onMarginClicked()));


    connect(textEdit, SIGNAL(textChanged()),this, SLOT(onModified()));
    connect(textEdit, SIGNAL(findAction()), this, SLOT(onFind()));
    //connect(textEdit, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(editCursorPosChanged(int,int)));

    setCurrentFile("");
}

//��Ӧ�ı��ĸı�
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
	//ɾ�����νṹ�оɵĺ����б�
	for(int i=0;i<childcount;i++)
	{
		funcItem->removeChild(funcItem->child(0));
	}

    //���º������еĺ������б�
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
                pwnd->macros[i].setCompipiled(false); //wxyͼ��ı䣬������Ӧ�öԸýű�����д���
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

    //ȥ������ע��
    for(int i=0; i< textEdit->lines(); i++)
    {
        QString line = textEdit->text(i);
        line.remove(QRegExp("//."));
        code.append(line);
    }
    //ȥ������ע��

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

	
        //��ʾ���к��������νṹ����
        foreach(QString name,funcNames)
        {
            item = new QTreeWidgetItem(funcItem, QStringList(name));
            funcItem->addChild(item);
            item->setIcon(0,QIcon(":/standardtool/images/standardtool/copy.ico"));
			funcItem->setExpanded(true);
        }

        code = textEdit->text();
   
}
//���νṹ ˫���ı䵱ǰitem
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
    //�ж��Ƿ����ѡ��
    if(currentItem && currentItem != preItem)
    {
        //����ǰһ��������

        if (saveCode(preItem))
        {
			//������ǰ������Ĵ���
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

//���溯����Ĵ���
bool MacroEdit::saveCode(QTreeWidgetItem* pItem)
{
	if (!pItem)
	{
		return true;
	}
    QString code = textEdit->text();
    if(textEdit->isModified())
    {
        //ѯ���Ƿ񱣴�
        QString msg ;
        msg = tr("�Ƿ񱣴���뵽�����⣺")+pItem->text(0);
        QMessageBox box(QMessageBox::Information,tr("δ����"),msg,QMessageBox::Ok|QMessageBox::Close|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

        box.button(QMessageBox::Ok)->setText(tr("��"));
		box.button(QMessageBox::Close)->setText(tr("��"));
        box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));

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

//�������������
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
//ˢ�����νṹ����ʾ
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
    toolbar->setStyleSheet("font: 9pt '����';\n"
                            "color: rgb(8, 45, 105);");
    toolbar->setMinimumSize(1,85);

    saveAction = new QAction(tr("����"),this);
    saveAction->setIcon(QIcon(":/standardtool/images/Msave.ico"));
    saveAction->setToolTip(tr("����"));
    saveAction->setIconText(tr("\n����"));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(save()));

    compileAction = new QAction(tr("����"),this);
    compileAction->setIcon(QIcon(":/debug/images/debug/compile.ico"));
    compileAction->setToolTip(tr("���沢����"));
    compileAction->setIconText(tr("\n����"));
    connect(compileAction,SIGNAL(triggered()),this,SLOT(compile()));

    //compileAllAction = new QAction(tr("���뺯��"),this);
    //saveAction->setIcon(QIcon(":/Marco/images/standardtool/filesave.png"));
    //compileAllAction->setToolTip(tr("����ͨ������ĺ���"));
    //connect(compileAllAction,SIGNAL(triggered()),this,SLOT(toolbarInsertFunc()));

    undoAction = new QAction(tr("����"), this);
    undoAction->setIcon(QIcon(":/standardtool/images/standardtool/undo.ico"));
    undoAction->setToolTip(tr("����"));
    undoAction->setIconText(tr("\n����"));
    connect(undoAction,SIGNAL(triggered()),textEdit,SLOT(undo()));

    redoAction = new QAction(tr("������"), this);
    redoAction->setIcon(QIcon(":/standardtool/images/standardtool/redo.ico"));
    redoAction->setToolTip(tr("�ָ�"));
    redoAction->setIconText(tr("\n�ָ�"));
    connect(redoAction,SIGNAL(triggered()),textEdit,SLOT(redo()));

    cutAction = new QAction(tr("����"), this);
    cutAction->setIcon(QIcon(":/standardtool/images/Mcut.ico"));
    cutAction->setToolTip(tr("����"));
    cutAction->setIconText(tr("\n����"));
    connect(cutAction,SIGNAL(triggered()),textEdit,SLOT(cut()));

    pasteAction = new QAction(tr("ճ��"), this);
    pasteAction->setIcon(QIcon(":/standardtool/images/Mpaste.ico"));
    pasteAction->setToolTip(tr("ճ��"));
    pasteAction->setIconText(tr("\nճ��"));
    connect(pasteAction,SIGNAL(triggered()),textEdit,SLOT(paste()));

    copyAction = new QAction(tr("����"), this);
    copyAction->setIcon(QIcon(":/standardtool/images/Mcopy.ico"));
    copyAction->setToolTip(tr("����"));
    copyAction->setIconText(tr("\n����"));
    connect(copyAction,SIGNAL(triggered()),textEdit,SLOT(copy()));

	hideMsgAction = new QAction(tr("��Ϣ/��������"), this);
    hideMsgAction->setIcon(QIcon(":/standardtool/images/Mhide.ico"));
	hideMsgAction->setToolTip(tr("������Ϣ�������"));
    hideMsgAction->setIconText(tr("\nչ��/����"));
	connect(hideMsgAction,SIGNAL(triggered()),this,SLOT(hideMsgWindow()));

    loadAction = new QAction(tr("����"), this);
    loadAction->setIcon(QIcon(":/standardtool/images/Mopen.ico"));
    loadAction->setToolTip(tr("���ļ�����"));
    loadAction->setIconText(tr("\n����"));
	connect(loadAction,SIGNAL(triggered()),this,SLOT(onLoadCode()));

    savetoAction = new QAction(tr("����"), this);
    savetoAction->setIcon(QIcon(":/standardtool/images/Mtofile.ico"));
    savetoAction->setToolTip(tr("�������ļ�"));
    savetoAction->setIconText(tr("\n����"));
	connect(savetoAction,SIGNAL(triggered()),this,SLOT(onSaveCode()));

	
	compileAllAction= new QAction(tr("ȫ������"), this);
    compileAllAction->setIcon(QIcon(":/standardtool/images/Hammer.ico"));
    compileAllAction->setToolTip(tr("ȫ�����±���"));
    compileAllAction->setIconText(tr("\nȫ������"));
	connect(compileAllAction,SIGNAL(triggered()),this,SLOT(onCompileAll()));
    //connect(hideMsgAction,SIGNAL(triggered()),this,SLOT(hideMsgWindow()));

    findAction = new QAction(tr("����"), this);
    findAction->setIcon(QIcon(":/standardtool/images/find.ico"));
    findAction->setToolTip(tr("�����ı�"));
    findAction->setIconText(tr("\n����"));
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

    QTreeWidgetItem* cParent = NULL;//��ǰ�ĺ������Ӧ������item
    QTreeWidgetItem *curItem = tree->currentItem();
    QList<QTreeWidgetItem* > topItems;
    for(int i=0;i<tree->topLevelItemCount();i++)
    {
        topItems << tree->topLevelItem(i);
    }

    textEdit->setModified(false);

    //������뵽������
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

void MacroEdit::showMacroMenu()//�ű��˵�
{

}

//���뵥�������
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
//����ϵͳ����
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


//�����������뺯��������Ӧ
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
//�½�����
void MacroEdit::onNewVar()
{
    int rowIndex = -1;
    if(1 == table->currentIndex())//�ֲ������趨
    {
        //wxy �޽ű���ʾ��Ӧ����ʾ��Ϣ
        QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr(""),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        if(!currentItem)
        {
            msg.setText(tr("���������Ӧ�Ŀ⣡"));
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
                    vartable->setItem(vartable->rowCount()-1, 0, new QTableWidgetItem(tr("�½�(�����Ҽ�)")));
                }
                return;
            }
        }
    }
    else if(2 == table->currentIndex())//ȫ�ֱ����趨
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
            gvartable->setItem(gvartable->rowCount()-1, 0, new QTableWidgetItem(tr("�½�(�����Ҽ�)")));
        }
        return;
    }
}

//�༭����
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
                                          new QTableWidgetItem(tr("�½�(�����Ҽ�)")));
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
                                  new QTableWidgetItem(tr("�½�(�����Ҽ�)")));
            }
            refreshJML();
        }
    }
}
//ɾ������
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
    msg = tr("�Ƿ�ɾ��������");
    QMessageBox box(QMessageBox::Information,tr("ȷ��"),msg,QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    box.button(QMessageBox::Ok)->setText(tr("ɾ��"));
    box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));

    box.exec();
    if(box.clickedButton() == box.button(QMessageBox::Cancel))
    {
        return;
    }

    //wxy list����Ŀֻ����1
    QList<QTableWidgetSelectionRange> list = pVartable->selectedRanges();
    int iTopRow = list.at(0).topRow();
    int iBottomRow = list.at(0).bottomRow();
    for(int i = iBottomRow; i >= iTopRow; i--)//wxy ����ɾ������֤ɾ��Ԫ�ص���ȷ��
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

//�ж�һ���ű��Ƿ����ɹ�
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
	typeStr << tr("boolֵ")<<tr("16λ����")<<tr("16λ������")<<tr("32λ����")<<tr("32λ������")
		<< tr("bool����")<<tr("16λ��������")<<tr("16λ����������")<<tr("32λ��������")
        <<tr("32λ����������")<<tr("32λ������")<<tr("32λ����������")<<tr("16λBCD��")
        <<tr("16λBCD������")<<tr("32λBCD��")<<tr("32λBCD������")<< tr("ASCII�ַ���")
        << tr("Unicode�ַ���");

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
	StrRW << tr("��")<<tr("д")<<tr("��д");

	QString sRW = "";

	if (cVar.RWPerm <StrRW.size() && cVar.RWPerm >= 0)
	{
		sRW = StrRW.at(cVar.RWPerm);
	}
    pVartable->setItem(row, 0, new QTableWidgetItem(cVar.varName));
    pVartable->setItem(row, 1, new QTableWidgetItem(sType));
    pVartable->setItem(row, 2, new QTableWidgetItem(sLen));
    pVartable->setItem(row, 3, new QTableWidgetItem(sRW));

	QString sAddrType = tr("�ڲ���ַ");
	if (cVar.addr.nConnectType != 0)
	{
		sAddrType = tr("�ⲿ��ַ");
	}
    pVartable->setItem(row, 4, new QTableWidgetItem(sAddrType));
    pVartable->setItem(row, 5, new QTableWidgetItem(cVar.addr.sShowAddr));
    if(cVar.bOffset)
    {
        pVartable->setItem(row, 6, new QTableWidgetItem(cVar.offsetAddr.sShowAddr));
    }
    else
    {
        pVartable->setItem(row, 6, new QTableWidgetItem(tr("��")));
    }
}

void MacroEdit::setTypeMap()
{
	typeMap.clear();
	typeMap.insert(0,"BoolHolder ");//boolֵ
	typeMap.insert(1,"ShortHolder ");//16λ����
	typeMap.insert(2,"UShortHolder ");//16λ������
	typeMap.insert(3,"IntHolder ");//32λ����
	typeMap.insert(4,"UIntHolder ");//32λ������
    typeMap.insert(5,"BoolSeqHolder ");//bool����
    typeMap.insert(6,"ShortSeqHolder ");//16λ��������
	typeMap.insert(7,"UShortSeqHolder ");//16λ����������
    typeMap.insert(8,"IntSeqHolder ");//32λ��������
	typeMap.insert(9,"UIntSeqHolder ");//32λ����������
    typeMap.insert(10,"FloatHolder ");//32λ������
	typeMap.insert(11,"FloatSeqHolder ");//32λ����������
    typeMap.insert(12,"Bcd16Holder ");//16λBCD��
    typeMap.insert(13,"Bcd16SeqHolder ");//16λBCD������
    typeMap.insert(14,"Bcd32Holder ");//32λBCD��
    typeMap.insert(15,"Bcd32SeqHolder ");//32λBCD������
    typeMap.insert(16,"StringHolder ");//�ַ���
    typeMap.insert(17,"StringHolder ");//�ַ���
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
                msgOutput->appendPlainText(tr("[%1]����ű� %2 �ɹ�").arg(cTime).arg(libName));
            }
            else
            {
                cItem->setIcon(0,QIcon(":/standardtool/images/standardtool/delete.ico"));
                msgOutput->appendPlainText(tr("[%1]����ű� %2 ʧ��").arg(cTime).arg(libName));
            }
        }

    }
}
//�Ҽ� �ű������
void MacroEdit::pressTree(QTreeWidgetItem*item,int col)
{
    if (qApp->mouseButtons() != Qt::RightButton)
    {
        return;
    }
    QMenu menu(tree);
    if(item == rootJRL || item == rootJML)
    {

        QAction *openJML= menu.addAction(tr("��ӽű���"));
        QAction *openJRL= menu.addAction(tr("��Ӻ�����"));

        connect(openJML,SIGNAL(triggered()),this,SLOT(slotAddJML()));
        connect(openJRL,SIGNAL(triggered()),this,SLOT(slotAddJRL()));
        menu.exec(QCursor::pos());
    }
    else if(item->parent() == rootJRL || item->parent() == rootJML)
    {
        QAction *openJML= menu.addAction(tr("�༭"));
        QAction *openJRL= menu.addAction(tr("ɾ��"));

        connect(openJML,SIGNAL(triggered()),this,SLOT(slotEdit()));
        connect(openJRL,SIGNAL(triggered()),this,SLOT(slotDelete()));
        if(item->parent() == rootJML)
        {
            QAction *rename = menu.addAction(tr("������"));
            connect(rename, SIGNAL(triggered()), this, SLOT(rename()));
        }
        menu.exec(QCursor::pos());
    }
	else
	{
		menuOnFunction(item);
	}

}

//�Ҽ���������ʱ����Ӳ˵�
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

    //QAction *newFunction= menu.addAction(tr("�½�����"));
	QAction *insertFunction= menu.addAction(tr("���ú���"));

	insertCode = item->text(0)+"( )";
	insertCode = item->parent()->text(0)+"."+insertCode;

    //connect(newFunction,SIGNAL(triggered()),this,SLOT(newFuncCode()));
	connect(insertFunction,SIGNAL(triggered()),this,SLOT(insertFuncCode()));
	if (JML_items.contains(item->parent()))
	{
		//�Ҽ� �ű�����
		insertFunction->setEnabled(false);
		menu.exec(QCursor::pos());
	}
	else if (JRL_items.contains(item->parent()))
	{
		//�Ҽ�  �����⺯��
		
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
//��ӽű���
void MacroEdit::slotAddJML()
{
    QTreeWidgetItem *item = NULL;
    Macro lib;
    AddLib addWzrd(pwnd->macros,this);
    addWzrd.setWindowTitle(tr("��ӽű���"));
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

//��Ӻ�����
void MacroEdit::slotAddJRL()
{
    QTreeWidgetItem *item = NULL;
    Macro lib;
    AddLib addWzrd(pwnd->macros,this);
    addWzrd.setWindowTitle(tr("��Ӻ�����"));
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
    msg = tr("�Ƿ�ɾ����%1��").arg(item->text(0));
    QMessageBox box(QMessageBox::Information,tr("ȷ��"),msg,QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    box.button(QMessageBox::Ok)->setText(tr("ɾ��"));
    box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));

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
                        //wxy�ű��ⱻɾ���������±���ű�
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
//����ϵͳ�����⵽UI
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
		//ѯ���Ƿ񱣴�
		QString msg ;
		msg = tr("�Ƿ񱣴���뵽�����⣺")+currentItem->text(0);
		QMessageBox box(QMessageBox::Information,tr("δ����"),msg,QMessageBox::Ok|QMessageBox::Cancel|QMessageBox::Close,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

		box.button(QMessageBox::Ok)->setText(tr("����"));
		box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));
		box.button(QMessageBox::Close)->setText(tr("������"));

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
//���� �⺯��
void MacroEdit::insertFuncCode()
{
	textEdit->insert(insertCode);
}

//�½�����
void MacroEdit::newFuncCode()
{}

//������ı�֮�����øÿ�Ľű��ⶼҪ��Ϊδ����
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
		//ȥ������ע��
        for(int j=0; j< lines.size(); j++)
		{
            QString line = lines[j];
			line.remove(QRegExp("//."));
			code.append(line);
		}
		//ȥ������ע��

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


//���ļ�����
void MacroEdit::onLoadCode()
{
	if(!currentItem)
		return;
	QString filename = QFileDialog::getOpenFileName(this,tr("ѡ��Ҫ������ļ�"),
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

//����Ϊ�ļ�
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
		tr("ѡ��Ҫ�洢��λ��"),
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

    //wxy �������ȱ��뺯����
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
    QAction *openJML= menu.addAction(tr("��ӽű���"));
    QAction *openJRL= menu.addAction(tr("��Ӻ�����"));

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
        msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        QString strMsg = QString(tr("�Ҳ���\"%1\"")).arg(expr);
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
    //wxy���ȫ�ֱ��������нű�����Ϊδ����
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
        addWzrd.setWindowTitle(tr("�޸Ŀ�����"));
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
