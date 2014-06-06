#include "qprotocoltool.h"
#include <QDir>
#include <QFileInfo>
#include <QLibrary>
#include <string>
#include <vector>
#define DRIVER_PATH "drivers/qtdll"
using namespace std;
QProtocolTool::QProtocolTool()
{
}
//获取驱动文件夹下的所有驱动文件
QVector<PLC_FACTORY> QProtocolTool::getAllProtocols()
{
    QVector<PLC_FACTORY> protocols;
    QDir drvdir(DRIVER_PATH);
    QFileInfoList infolist;
    infolist = drvdir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    PLC_FACTORY factory;
    foreach(QFileInfo path,infolist)
    {
        factory.sFactoryName = path.fileName();
        qDebug() <<"factory" <<factory.sFactoryName;
        factory.models = getProtocols(path.filePath());
        if(!factory.models.isEmpty())
            protocols << factory;
    }
    return protocols;
}

//获取单个驱动文件夹下的所有协议
QVector<PLC_MODEL> QProtocolTool::getProtocols(QString absPath)
{
    QVector<PLC_MODEL> models;
    PLC_MODEL model;

    QDir dir(absPath);
    QFileInfoList infolist;
    QStringList filters;
    filters << "*.dll";
    infolist = dir.entryInfoList(filters,QDir::Files);
    QStringList registers;
    foreach(QFileInfo path,infolist)
    {
        if(getAllProperty(path.filePath(),model))
        {
            model.sModelName = path.baseName();
            qDebug() <<"model"<< model.sModelName;
            //if (!model.regs.isEmpty())
            {
                models << model;
            }
            //else
            //qDebug() << "error: register is empty!";
        }
    }
    return models;
}

bool QProtocolTool::getAllProperty(QString absPath,PLC_MODEL &model)
{
    vector<string> stdLst;
    vector<string> stdBitLst;
    vector<string> stdWordLst;
    vector<string> stdDWordLst;
    QVector<QString> qVcStr;
    QStringList registers;
    QLibrary lib(absPath);
	int nInterval = 0;
	int	nPlcNo = 0;
	int	nReceiveTimeout = 0;
	int	nMaxRWLen = 0;
	int	nRetryTime = 0;
	int nCycleTime = 0;
    SERIAL_PORT_PROP PlcPort;
    E_PORT_TYPE ePortType;

    stdLst.clear();
    stdWordLst.clear();
    stdBitLst.clear();
    stdDWordLst.clear();
    typedef void (*ADDPROC)( vector<string> &);
	typedef int (*GETPRO)( );
    typedef void (*getRegProc)( vector<string> &,ADDR_REG_TYPE);
    typedef E_PORT_TYPE (*GETPortType)();

    typedef SERIAL_PORT_PROP (*GetPortProc)();
    QString qStr;

    if(lib.load())
    {
        getRegProc getRegs= (getRegProc)lib.resolve("getAllRegNames");
        if(getRegs)
        {
           getRegs(stdLst,ALL_ADDR_REG);
           getRegs(stdBitLst,BIT_ADDR_REG);
           getRegs(stdWordLst,WORT_ADDR_REG);
           getRegs(stdDWordLst,DWORT_ADDR_REG);
        }
        GETPRO getStationIndex = (GETPRO)lib.resolve("getDefaultStation");
		if(getStationIndex)
		{
			nPlcNo = getStationIndex();
		}
		GETPRO getTimeoutValue = (GETPRO)lib.resolve("getDefaultTimeout");
		if(getTimeoutValue)
		{
			nReceiveTimeout = getTimeoutValue();
		}
		GETPRO getReadLength = (GETPRO)lib.resolve("getDefaultMaxRwLen");
		if(getReadLength)
		{
			nMaxRWLen = getReadLength();
		}
		GETPRO getRetryTimes = (GETPRO)lib.resolve("getDefaultRetryTimes");
		if(getRetryTimes)
		{
			nRetryTime = getRetryTimes();
		}
		GETPRO getIntervalTime = (GETPRO)lib.resolve("getDefaultIntervalTime");
		if(getIntervalTime)
		{
			nInterval = getIntervalTime();
		}
		GETPRO getCycleTime = (GETPRO)lib.resolve("getDefaultCollectRate");
		if(getCycleTime)
		{
			nCycleTime = getCycleTime();
		}

        GetPortProc getPortInfo =  (GetPortProc)lib.resolve("getDefaultSerialInfo");
        if(getPortInfo)
        {
             PlcPort = getPortInfo();
        }

        GETPortType getPortType = (GETPortType)lib.resolve("getProType");
        if(getPortType)
        {
            ePortType = getPortType();
        }
		lib.unload();
    }
    else
	{
		return false;
		qDebug() << "getRegStrs -- load "<< absPath << " fiald" ;
	}
        
    
    foreach(string stdstring,stdLst)
    {
       registers << qStr.fromStdString(stdstring);
    }

	model.nIntervalTime = nInterval;
	model.nMaxRWLen = nMaxRWLen;
	model.nPlcNo = nPlcNo;
	model.nRetryTime = nRetryTime;
	model.nReceiveTimeout = nReceiveTimeout;
	model.regs = registers;
	model.nCycleTime = nCycleTime;
        model.mPort = PlcPort;
    model.ePorttype = /*ePortType*/PORT_SERIAL_ETHNET;//wxy add 先屏蔽掉这功能

        registers.clear();
        foreach(string stdstring,stdBitLst)
        {
           registers << qStr.fromStdString(stdstring);
        }
        model.sBitregs = registers;

        registers.clear();
        foreach(string stdstring,stdWordLst)
        {
           registers << qStr.fromStdString(stdstring);
        }
        model.sWorldregs = registers;

        registers.clear();
        foreach(string stdstring,stdDWordLst)
        {
           registers << qStr.fromStdString(stdstring);
        }
        model.sDworldregs = registers;
    return true;
}

QMap<QString, QString> QProtocolTool::getDriversConfig()
{
    QMap<QString, QString> map;
    QString strPath = QString("%1/drivers.dat").arg(DRIVER_PATH);
    if(QFile::exists(strPath))
    {
        QFile file(strPath);
        if (file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QString line;//临时变量，存储从文件取出的一行数据
            QString sModel;//文件变量
            QTextStream stream(&file);//定义操作文件的变量
            line=stream.readLine();//文件第一行存储的是型号的个数
            int iDriverCount=line.toInt();//把得到的QString类型的数据转换为整型该行存储的是所有型号的个数
            for(int temp=0;temp<iDriverCount;temp++)
            {
                sModel=stream.readLine();
                line=sModel.split("(").at(0);
                map.insert(line, sModel);
            }
        }
    }
    return map;
}
