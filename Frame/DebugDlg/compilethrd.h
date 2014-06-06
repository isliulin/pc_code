#ifndef COMPILETHRD_H
#define COMPILETHRD_H

#include <QThread>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "Frame/qprogectmanager.h"

typedef enum _compileType{         //编译类型
	COMPILE_ONLY = 1,            //编译
	DOWNLOAD,              //下载
	SIMULATOR_OFF,              //离线模拟
	SIMULATOR_ON,              //在线模拟
}COMPILE_TYPE;

class CompileThrd : public QThread
{
    Q_OBJECT
public:
    CompileThrd();
    void SetDownload(COMPILE_TYPE type);
    bool openDataBase(QSqlDatabase &dataBase);
    bool clearDataBaseData();
    bool createDataBase(QSqlDatabase &dataBase);
    bool ExecuteQuerys(QSqlDatabase &dataBase);
signals:
    void SignalStartDownload();
	void SignalStartsimulator();
    void message(QString msg, MSG_TYPE eType);
    void SignalCompileEnd();
public slots:
    void	threadfinished ();
protected:
    COMPILE_TYPE eType;
	
    void run();

private:
    bool removeDirectory(QString dirName);
public:
    bool bDatabaseClosed;
};

#endif // COMPILETHRD_H
