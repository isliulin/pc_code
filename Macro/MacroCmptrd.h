#ifndef MACROCMPTRD_H
#define MACROCMPTRD_H
#include <QThread>
#include <QStack>
#include "Frame/qprogectmanager.h"

#define  JMLPATH "sdmacro\\jsrc\\jml"
#define  JRLPATH "sdmacro\\jsrc\\jrl"
#define  FMATH_PATH "sdmacro\\ml\\class\\jrl\\FMath.class"
#define  MUTIL_PATH "sdmacro\\ml\\class\\jrl\\FString.class"
#define  FBASE_PATH "sdmacro\\ml\\class\\jrl\\FBase.class"
#define  CANBUS_PATH "sdmacro\\ml\\class\\jrl\\CANBus.class"
#define  TG_PATH "sdmacro\\ml\\class\\jrl\\TG.class"
#define  VIEW_PATH "sdmacro\\ml\\class\\jrl\\AKView.class"
#define  ITEM_PATH "sdmacro\\ml\\class\\jrl\\Item.class"
#define  SYS_LIB_DIR "sdmacro\\"

class Macro;
class MacroCmptrd :
	public QThread
{
	Q_OBJECT
public:
	MacroCmptrd(void);
    ~MacroCmptrd(void);
    bool startcompile(Macro &library);
    void clearLog(QString path);
    bool compressJar(QVector<Macro > librarys, QString& strLibName);
    void makeJar(QString bat);
    bool compileJML(Macro &library);
    bool compileJRL(Macro &library);
	void setTypeMap();
	void copySysLib();
    void setStaticCode(QString code,QString header);
	QString loadStaticCode();
    QString loadHeaderCode();
    static bool checkCompiledResult(QString libName,QByteArray md5);
    static QByteArray getFileMd5(QString filePath);
    void pushMacro(Macro &macro);
    void run();
    void startCompress(QVector<Macro > librarys);
signals:
    void signalOutPut(QString libName,QString msg);
private:
	bool type;
	QMap<int,QString> typeMap;
    QList<Macro*> compileStack;
	QString m_name;
    QString m_staticCode;
    QString m_HeadCode;
    bool bCompress;//是否进行打包
    QVector<Macro > m_librarys;//要打包的脚本

    bool Regexp(QString& strCode);
public:
    QString m_strLibName;//打包返回的脚本名称
    bool bSucess;

};
#endif  //MACROCMPTRD_H
