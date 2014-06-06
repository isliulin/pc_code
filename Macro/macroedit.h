#ifndef MACROEDIT_H
#define MACROEDIT_H
#include <QtGui>
#include <QDialog>
#include "varSettingWidget.h"
#include "MacroCmptrd.h"
#include "Frame/qprogectmanager.h"
#include "macro.h"
class QsciScintillaEx;


#define  JMLPATH "sdmacro\\jsrc\\jml"
#define  JRLPATH "sdmacro\\jsrc\\jrl"

 

class AddLib : public QDialog
{
    Q_OBJECT

public:
    AddLib(QVector<Macro> libs,QWidget *parent = 0);
    ~AddLib();

    QString libName;
    QLabel *label;
    QLabel *msg;
    QLineEdit *edit;
    QDialogButtonBox *btnBox;
    QVector<Macro > librarys;
	QStringList reWords;
    void setEditString(QString str);
private slots:
    void accepted();
    void onTextChanged(QString text);

};


//add by wuxiyang
//默认是循环查找
class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = 0);

signals:
    void findFirst(const QString &expr, bool re, bool cs, bool wo, bool wrap, bool forward);
    void findNext();
    void replace(const QString &text);
    void setCursorPosition();
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void findClicked();   //查找
    void enableFindButton(const QString &text);
    void replaceClicked();   //替换
    void onCheckBoxChanged(bool); //复选框改变，重新开始查找
    void ReplaceButton(const QString &text);
private:
    QLabel *label;
    QLineEdit *lineEdit;

    QCheckBox *caseCheckBox;     //大小写敏感
    QCheckBox *backwardCheckBox; //向后
    QCheckBox *worldMatchCheckBox; //全词匹配
    QCheckBox *rExpCheckBox; //正则表达式
    QPushButton *findButton;
    QPushButton *closeButton;

    QLabel *labelReplace;
    QLineEdit *editReplace;
    QPushButton *replaceButton;
private:
    bool is_firstFind;
    bool m_bFindText;
public:
    void setFindTextResult(bool bFind);
    void setIsFindFirst(bool bFirst);
};


class MacroEdit : public QDialog
{    
    Q_OBJECT

public:
    MacroEdit(QString currentName,QWidget *parent = 0);
    ~MacroEdit();
    void creatToolBar();
    void initLibTree();
    void initTabWidget();
    void initVarTable(QTableWidget* pVartable, int iIndex);
    void initHighlighter();
    void initSysLib();
    void funlibChanged(QString libName);


    void updataTree(QStringList functions);

    void setCurrentFile(const QString &fileName);

    bool saveCode(QTreeWidgetItem *pItem);
    void loadCode(QString libName);
    void setRow(VarPro cVar,int row, QTableWidget* pVartable);
    void reloadVars(QString libraryName, QTableWidget* pVartable,int iIndex = 0);

    void setTypeMap();
    bool compileJML(MacroLibrary &library);
    bool compileJRL(MacroLibrary &library);
    void closeEvent(QCloseEvent *event);
    void menuOnFunction(QTreeWidgetItem *item);
    Macro * getLibrarys(QString libName);
    void reject();
    
public:
    QLabel *labelLst;
    QLabel *labelnothing;
    QPushButton *addLibBtn;
    QPushButton *addMacroBtn;
    QTreeWidget *tree;//树形：脚本库
    QTreeWidgetItem *rootJRL;
    QTreeWidgetItem *rootJML;

    QToolBar *toolbar;//编辑工具条
    QsciScintillaEx *textEdit; //编辑窗口
    varSettingWidget *pvarSettingWidget;//变量设定中的属性编辑窗口

    QTabWidget *table;//信息输出窗口+变量设定窗口 的tabWidget
    QPlainTextEdit *msgOutput;//信息输出窗口
    QTableWidget *vartable;//变量设定窗口
    QTableWidget *gvartable;//全局变量设定窗口
    QAction *newVarAction;
    QAction *editVarAction;
    QAction *delVarAction;
    QAction *batVarAction;

    QLabel *labelLib;
    QLineEdit *libNameEdit;
    QLabel *labelMacro;
    QLineEdit *marcoNameEdit;

    QPushButton *insertFuncBtn;

    QAction *undoAction;
    QAction *saveAction;
    QAction *compileAction;
    QAction *redoAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *copyAction;
    QAction *compileAllAction;
    QAction *hideMsgAction;
    QAction *loadAction;
    QAction *savetoAction;
    //QAction *compileAllAction;
    QAction *findAction;

    QComboBox *comboSysLib;
    QComboBox *comboLibFun;
    QPlainTextEdit * sysLibTips;
    QGroupBox *groupSysLib;
    QLabel *labelSlecetLib;
    QLabel *labelSlecetFun;

    QVector<MacroLibrary > librarys;
private slots:
    void onModified();
    void save();
    bool compile();
    bool insertFunction();
    void treeItemChanged(QTreeWidgetItem* cItem,int coulum);
    void showMacroMenu();
    void pressTree(QTreeWidgetItem*item,int col);

    void onNewVar();

    void onEditVar();

    void onDelVar();

    void onSaveCode();

    void onLoadCode();

    void onCompileAll();

    //add by wuxiyang
    void onFind();

    void onNewMulti();
    void hideMsgWindow();

    void libChanged(QString libName);
    void funcChanged(QString funcName);

    void addMacro();

    //void editCursorPosChanged(int line,int index);
private slots:
    void showErrorLog(QString libName,QString log);
    QByteArray getCompileRestlt(QString libName,bool libType);
    void disableUi();
    void enableUi();
    void slotAddJML();
    void insertFuncCode();
    void newFuncCode();

    void toolbarInsertFunc();
    void slotAddJRL();
    void slotDelete();
    void slotEdit();
    void findFirst(const QString &expr, bool re, bool cs, bool wo, bool wrap, bool forward);
    void findNext();
    void replace(const QString &test);

    void rename();//wxy add
private:
    QString lName;
    QString insertCode;
    VarPro defaultVar;
    QMap<int,QString> typeMap;
    MacroCmptrd *cmpTrd;
    bool bReload;
    bool bCompile;
    QTreeWidgetItem* currentItem;//当前的函数库对应的树形item

    FindDialog *findDlg;

    //wxy全局变量改动时，更新脚本库编译状态，以及脚本库节点图标状态
    void refreshJML();
};

#endif // MACROEDIT_H
