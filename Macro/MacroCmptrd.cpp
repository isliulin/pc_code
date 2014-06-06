#include "MacroCmptrd.h"
#include <QDir>
#include <QTextStream>
#include <QProcess>
#include <QCryptographicHash>
#include "macro.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

extern bool  is_tanslator;
MacroCmptrd::MacroCmptrd(void)
{
	setTypeMap();
    setStaticCode(loadStaticCode(),loadHeaderCode());
    bCompress = false;
    bSucess = false;
}

MacroCmptrd::~MacroCmptrd(void)
{
}
void MacroCmptrd::run()
{
    if(!bCompress)
    {
        copySysLib();
        while(!compileStack.isEmpty())
        {
            Macro *macro = compileStack.takeFirst();
            if(macro->type)
            {
                compileJML(*macro);
            }
            else
            {
                compileJRL(*macro);
            }
        }
    }
    else
    {
        qDebug() <<"compress JAR";
        bSucess = compressJar(m_librarys,m_strLibName);
        bCompress = false;
    }

}
void MacroCmptrd::startCompress(QVector<Macro > librarys)
{
    bCompress = true;
    bSucess = false;
    m_librarys = librarys;
    start();
}

void MacroCmptrd::setStaticCode(QString code,QString header)
{
    m_staticCode = code;
    m_HeadCode = header;
}
bool MacroCmptrd::startcompile(Macro &library)
{
    QString path ;
    QString cmd;
    QString log = "\\sdmacro\\log.txt";
    QString logpath = "sdmacro\\log.txt";
    QString xmlpath = "\\sdmacro\\build.xml";
    QString workDir = QDir::currentPath();//for test
    logpath = workDir+log;
    log ="> \""+ workDir+log;
    log+="\"";
    xmlpath = workDir+xmlpath;

	log.replace("/","\\");
    logpath.replace("/","\\");
    xmlpath.replace("/","\\");
    clearLog(logpath);

    QString slan = "CN";
    if(is_tanslator)
    {
        slan = "EN";
    }
    if (library.type)
    {
            cmd = QString("ant -quiet -f \"%1\" jmlc -Dml=%2 -Dulan=%3").arg(xmlpath).arg(library.libName).arg(slan)+log;
    }
    else
    {
            cmd = QString("ant -quiet -f \"%1\" jrlc -Dml=%2 -Dulan=%3").arg(xmlpath).arg(library.libName).arg(slan)+log;
    }

    path = workDir+"\\sdmacro\\bash.bat";
    path = path.replace("/","\\");

    QFile batFile(path);
    QTextStream stream(&batFile);


    if (batFile.open(QIODevice::WriteOnly))
    {
       stream << cmd;
       batFile.close();
    }


    QString classFile;
    if(library.type)
    {
        classFile = "sdmacro\\ml\\class\\jml\\";
    }
    else
    {
        classFile = "sdmacro\\ml\\class\\jrl\\";
    }
    classFile += library.libName;
    classFile += ".class";

    QFile::remove(classFile);
    makeJar(path);

    library.setMD5(getFileMd5(classFile));

    qDebug()<<library.libName<< ": MD5 = " << library.MD5();
    library.setCompipiled(!library.MD5().isEmpty());
    qDebug() << library.libName << ":compile result "<<library.isCompiled();
    QFile logfile(logpath);
    QTextStream logstream(&logfile);
    if (logfile.open(QIODevice::ReadOnly))
    {
        QString logStr;
        logStr = logstream.readAll();
        emit signalOutPut(library.libName,logStr);
        logfile.close();
    }
    return library.isCompiled();
}

bool MacroCmptrd::compressJar(QVector<Macro > librarys, QString& strLibName)
{
	QStringList filenames;
	QString classJml = "sdmacro\\ml\\\class\\jml";
	QString classJrl = "sdmacro\\ml\\\class\\jrl";
	foreach(Macro lib,librarys)
	{
		if(lib.isCompiled())
		{
			QString filename = lib.libName+".class";
			filenames << filename;
		}
	}

	QDir jmlDir(classJml);
	QFileInfoList lst = jmlDir.entryInfoList();
    QRegExp reg("\\$\\d*");
    reg.setMinimal(false);
	foreach(QFileInfo info,lst)
	{
        QString name = info.fileName();
        qDebug() <<"000000000000000000" << name.remove(reg);
        if (!filenames.contains(info.fileName(),Qt::CaseInsensitive)
            &&!filenames.contains(name.remove(reg)))
		{
			jmlDir.remove(info.absoluteFilePath());
		}
	}
	QDir jrlDir(classJrl);
	lst = jrlDir.entryInfoList();
	foreach(QFileInfo info,lst)
	{
        QString name = info.fileName();
        qDebug() <<"000000000000000000" << name.remove(reg);
        if (!filenames.contains(info.fileName(),Qt::CaseInsensitive)
            &&!filenames.contains(name.remove(reg)))
		{
			jrlDir.remove(info.absoluteFilePath());
		}
	}
    qDebug() << "compressJar copySysLib";
	copySysLib();
    qDebug() << "after copySysLib";
    QString workDir = QDir::currentPath();

    //wxy 必须优先编译函数库
    for(int i = 0; i < pwnd->macros.size(); i++)
    {
        if(!pwnd->macros[i].type) //函数库
        {
            if(pwnd->macros[i].isCompiled())
            {
                if (!pwnd->macros[i].checkMD5())
                {
                    qDebug()<< tr("重新编译了脚本 ") << pwnd->macros[i].libName;
                    if(!compileJRL(pwnd->macros[i]))
                    {
                        strLibName = pwnd->macros[i].libName;
                        return false;
                    }
                }
            }
        }
    }

    for(int i = 0; i< pwnd->macros.size(); i++)
    {
        if(pwnd->macros[i].type) //脚本
        {
            if(pwnd->macros[i].isCompiled())
            {
                if (!pwnd->macros[i].checkMD5())
                {
                    qDebug()<< tr("重新编译了函数库 ") << pwnd->macros[i].libName;
                    if(!compileJML(pwnd->macros[i]))
                    {
                        strLibName = pwnd->macros[i].libName;
                        return false;
                    }
                }
            }
        }
    }
    QString path;
    QString logPath = workDir+"\\sdmacro\\jarlog.txt";
    QString xmlPath = workDir+"\\sdmacro\\build.xml";
    path = workDir+"\\sdmacro\\bash.bat";
    path = path.replace("/","\\");
    QString cmd =QString("ant -quiet -f \"%1\" mldexjar > \"%2\"").arg(xmlPath).arg(logPath);
    QFile batFile(path);
    QTextStream stream(&batFile);


    if (batFile.open(QIODevice::WriteOnly))
	{
        //stream << "echo hello >comlog.txt\r\n";
        qDebug() <<"jar cmd :"<< cmd;
        stream << cmd;
        //stream << "\r\necho hello >comlog.txt\r\n";
        batFile.close();
	}
       // msleep(100);
        //QProcess process;
        makeJar(path);
        qDebug() << "after compressJar";
    return true;
}

void MacroCmptrd::makeJar(QString bat)
{
    QString path = bat;
    QProcess process;
    path = "\""+path;
    path+="\"";
    int result = process.execute(path);
    process.waitForFinished();
    qDebug() <<"compile :"<< process.readAllStandardOutput()<< process.readAllStandardError();
    qDebug() <<"path :"<< path;

}
void MacroCmptrd::clearLog(QString path)
{
    QFile::remove(path);
}

bool MacroCmptrd::Regexp(QString& strCode)
{
    bool bChanged = false;
    if(strCode == "")
    {
        return false;
    }
    QRegExp rxCodeErase("\\/\\*.*\\*\\/");
    rxCodeErase.setMinimal(true);
    strCode.replace(rxCodeErase, "");
    QString strA = "\\.\\s*[v]\\s*(\\[[^\\[\\]]*\\])?\\s*";
    QString strB1 = "((\\+\\+|\\-\\-)\\s*;?)";
    QString strCapture1 = "([^=\\\"][^\\\"]*)";
    QString strCapture2 = "((([^=\\\"]*\\\"[^\\\"]*){2})+)";
    QString strB2 = QString("([\\+|\\-|\\*|\\/]?[=]\\s*(%1|%2)\\s*;)").arg(strCapture1).arg(strCapture2);
    QString strB = QString("(%1|%2)").arg(strB1).arg(strB2);
    QString strRx = QString("%1%2").arg(strA).arg(strB);
    //最终正则表达式
    qDebug() << "regexp = "<< strRx;
    //\.\s*[v]\s*(\[[^\[\]]*\])?\s*(((\+\+|\-\-)\s*;?)|([\+|\-|\*|\/]?[=]\s*(([^=\"][^\"]*)|((([^=\"]*\"[^\"]*){2})+))\s*;))
    QRegExp rx(strRx);
    rx.setMinimal(true);

    int iPos = 0;
    while((iPos = rx.indexIn(strCode, iPos)) != -1)
    {
        bChanged = true;
        QString strInput = strCode.mid(iPos, rx.matchedLength());
        //strInput.replace(QRegExp("\\s*"), "");
        if(strInput.lastIndexOf("=") != -1)
        {
            int iLastIndex = strInput.indexOf("=");
            QString strValue = strInput.mid(iLastIndex+1, strInput.length()-iLastIndex-2);
            QString strOper = strInput.at(iLastIndex - 1);
            qDebug()<<"wxy_test$%"<<strInput<<strValue<<strOper;
            int iPosLeft = 0;
            QRegExp rxLeft("\\.\\s*[v]\\s*\\[.*\\]\\s*[\\+|\\-|\\*|\\/]?[=]");
            rxLeft.setMinimal(true);
            if((iPosLeft = rxLeft.indexIn(strInput, 0)) != -1)//判断是否有.v[]的情况
            {
                QString strLeft = strInput.mid(iPosLeft, rxLeft.matchedLength());
                int iIndex1 = strLeft.indexOf("[");
                int iIndex2 = strLeft.lastIndexOf("]");
                QString strIndex = strLeft.mid(iIndex1+1,iIndex2-iIndex1-1);
                qDebug()<<"wxy_test@#"<<strInput<<strLeft<<strIndex<<iIndex1<<iIndex2;
                if(strOper == "+")
                {
                    strCode.replace(iPos, rx.matchedLength(), QString(".add(%1,%2);").arg(strIndex).arg(strValue));
                    iPos += (strIndex.length() + strValue.length()+ 10);
                }
                else if(strOper == "-")
                {
                    strCode.replace(iPos, rx.matchedLength(), QString(".plus(%1,%2);").arg(strIndex).arg(strValue));
                    iPos += (strIndex.length() + strValue.length()+ 11);
                }
                else if(strOper == "*")
                {
                    strCode.replace(iPos, rx.matchedLength(), QString(".multiply(%1,%2);").arg(strIndex).arg(strValue));
                    iPos += (strIndex.length() + strValue.length()+ 15);
                }
                else if(strOper == "/")
                {
                    strCode.replace(iPos, rx.matchedLength(), QString(".divide(%1,%2);").arg(strIndex).arg(strValue));
                    iPos += (strIndex.length() + strValue.length()+ 13);
                }
                else
                {
                    //strIndex = strLeft.mid(3, strLeft.length()-5);
                    strCode.replace(iPos, rx.matchedLength(), QString(".setValue(%1,%2);").arg(strIndex).arg(strValue));
                    iPos += (strIndex.length() + strValue.length()+ 13);
                }
            }
            else
            {
                if(strOper == "+")
                {
                    strCode.replace(iPos, rx.matchedLength(), QString(".add(-1,%1);").arg(strValue));
                    iPos += (strValue.length()+10);
                }
                else if(strOper == "-")
                {
                    strCode.replace(iPos, rx.matchedLength(), QString(".plus(-1,%1);").arg(strValue));
                    iPos += (strValue.length()+11);
                }
                else if(strOper == "*")
                {
                    strCode.replace(iPos, rx.matchedLength(), QString(".multiply(-1,%1);").arg(strValue));
                    iPos += (strValue.length()+15);
                }
                else if(strOper == "/")
                {
                    strCode.replace(iPos, rx.matchedLength(), QString(".divide(-1,%1);").arg(strValue));
                    iPos += (strValue.length()+13);
                }
                else
                {
                    strCode.replace(iPos, rx.matchedLength(), QString(".setValue(-1,%1);").arg(strValue));
                    iPos += (strValue.length()+15);
                }

            }
        }
        else //++ --
        {
            int iIndexOf = -1;
            if((iIndexOf = strInput.lastIndexOf("++")) != -1)
            {
                int iPosLeft = 0;
                QRegExp rxLeft("\\.\\s*[v]\\s*\\[.*\\]");
                rxLeft.setMinimal(true);
                if((iPosLeft = rxLeft.indexIn(strInput, 0)) != -1)//.v[i+1]
                {
                    QString strLeft = strInput.mid(iPosLeft, rxLeft.matchedLength());
                    QString strIndex = strLeft.mid(3, strLeft.length()-4);
                    strCode.replace(iPos,rx.matchedLength(), QString(".increase(%1)").arg(strIndex));
                    iPos += (strIndex.length() + 9);
                    qDebug()<<"wxy_test++"<<strInput<<strLeft<<strIndex;
                }
                else//.v
                {
                    strCode.replace(iPos,rx.matchedLength(), QString(".increase(-1)"));
                    iPos += 11;
                }
            }
            else if((iIndexOf = strInput.lastIndexOf("--")) != -1)
            {
                int iPosLeft = 0;
                QRegExp rxLeft("\\.\\s*[v]\\s*\\[.*\\]");
                rxLeft.setMinimal(true);
                if((iPosLeft = rxLeft.indexIn(strInput, 0)) != -1)
                {
                    QString strLeft = strInput.mid(iPosLeft, rxLeft.matchedLength());
                    QString strIndex = strLeft.mid(3, strLeft.length()-4);
                    strCode.replace(iPos,rx.matchedLength(), QString(".decrease(%1)").arg(strIndex));
                    iPos += (strIndex.length() + 9);
                    qDebug()<<"wxy_test--"<<strInput<<strLeft<<strIndex;
                }
                else//.v
                {
                    strCode.replace(iPos,rx.matchedLength(), QString(".decrease(-1)"));
                    iPos += 11;
                }

            }
        }
    }
    //return strCode;
    return bChanged;
}

bool MacroCmptrd::compileJML(Macro &library)
{
	QString jmlPath = JMLPATH;
	QFile jml(jmlPath+"\\"+library.libName+".java");
    jml.remove();
	QTextStream stream(&jml); 
	if(jml.open( QIODevice::WriteOnly ))
	{
		//存文件头
        stream << m_HeadCode;
		QString classHeader;
		classHeader = QString("public class %1\r\n").arg(library.libName);
		stream << classHeader;
		stream << "{\r\n";
        //存代码
        //stream << library.code();
        QString strCode = library.code();
        while(Regexp(strCode))
        {
            ;
        }
        stream << /*Regexp(library.code())*/strCode;
		stream << "\r\n";
		//存变量声明
        for (int i=0; i<library.vars().size(); i++)
		{
            stream << "private " << typeMap.value(library.vars().at(i).dataType);
            stream << library.vars().at(i).varName << ";\r\n";
		}
        if(pwnd->getProVersion() >= 3125)
        {
            for(int i =0; i<pwnd->getGlobalVars().size(); i++)//全局变量
            {
                stream << "private " << typeMap.value(pwnd->getGlobalVars().at(i).dataType);
                stream << pwnd->getGlobalVars().at(i).varName << ";\r\n";
            }
        }

        //存SysInit函数
        stream << "public boolean SysInit(HashMap<String, PHolder> params){\r\n";
        stream <<"extFun(params);\r\n";
        stream <<"if(null == params){\r\n";
        stream <<"System.out.println(\"SysInit: Warning params is null!\");\r\n";
		stream <<"return false;\r\n";
		stream <<"}\r\n";
		stream <<"\r\n";

        for (int i=0; i<library.vars().size(); i++)
        {
            QString sVar = library.vars().at(i).varName;
            QString sTmp = QString("if(params.containsKey(\"%1\")){\r\n ").arg(sVar);
            stream << sTmp;
            sTmp = QString("%1 = (%2) params.get(\"%3\");\r\n").arg(sVar).arg(typeMap.value(library.vars().at(i).dataType)).arg(sVar);
            stream << sTmp;
            sTmp = QString("}else{\r\n");
            stream << sTmp;

            sTmp = QString("System.out.println(\"SysInit: %1 attach failed!\");\r\n").arg(sVar);
            stream << sTmp;
            stream <<"}\r\n";
        }
        if(pwnd->getProVersion() >= 3125)
        {
            for (int i=0; i<pwnd->getGlobalVars().size(); i++)
            {
                QString sVar = pwnd->getGlobalVars().at(i).varName;
                QString sTmp = QString("if(params.containsKey(\"%1\")){\r\n ").arg(sVar);
                stream << sTmp;
                sTmp = QString("%1 = (%2) params.get(\"%3\");\r\n").arg(sVar).arg(typeMap.value(pwnd->getGlobalVars().at(i).dataType)).arg(sVar);
                stream << sTmp;
                sTmp = QString("}else{\r\n");
                stream << sTmp;

                sTmp = QString("System.out.println(\"SysInit: %1 attach failed!\");\r\n").arg(sVar);
                stream << sTmp;
                stream <<"}\r\n";
            }
        }
		stream << "return true;\r\n}\r\n";
        stream << m_staticCode;
		stream << "}\r\n";
		jml.close();
	}
    else
    {

    }
    //compileFile_jml(library);
    return startcompile(library);
	return false;
}

bool MacroCmptrd::compileJRL(Macro &library)
{
	QString jrlPath = JRLPATH;
	QFile jrl(jrlPath+"\\"+library.libName+".java");
	QTextStream stream(&jrl); 
	if(jrl.open( QIODevice::WriteOnly ))
	{
		//存文件头
		stream << "package jrl;\r\n";
        stream << "import java.math.BigInteger;\r\n";
        stream << "import java.util.HashMap;\r\n";
        stream << "import com.android.Samkoonhmi.macro.corba.*;\r\n";
        stream << "import jrl.*;\r\n";
        stream << "import java.util.Vector;\r\n";
        stream << "import java.util.ArrayList;\r\n";
        stream << "import java.lang.*;\r\n";
        stream << "import java.io.*;\r\n";
		QString classHeader;
		classHeader = QString("public class %1\r\n").arg(library.libName);
		stream << classHeader;
		stream << "{\r\n";
		//存代码
        stream << library.code();
		stream << "}\r\n";
		stream << "\r\n";
		jrl.close();
	}
    //compileFile_jrl(library);
    return startcompile(library);
	return false;
}


void MacroCmptrd::setTypeMap()
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
void MacroCmptrd::copySysLib()
{
	QString destPath = FMATH_PATH;
	QString path = SYS_LIB_DIR;
	path += "FMath.class";
	QFile fmath_file(path);
	if (!QFile::exists(destPath))
	{
		fmath_file.copy(destPath);
	}
	destPath = MUTIL_PATH;
	path = SYS_LIB_DIR;
    path += "FString.class";
	QFile mutil_file(path);
	if (!QFile::exists(destPath))
	{
		mutil_file.copy(destPath);
	}
    destPath = FBASE_PATH;
    path = SYS_LIB_DIR;
    path += "FBase.class";
    QFile base_file(path);
    if (!QFile::exists(destPath))
    {
        base_file.copy(destPath);
    }

    destPath = CANBUS_PATH;
    path = SYS_LIB_DIR;
    path += "CANBus.class";
    QFile can_file(path);
    if (!QFile::exists(destPath))
    {
        can_file.copy(destPath);
    }

    destPath = TG_PATH;
    path = SYS_LIB_DIR;
    path += "TG.class";
    QFile tg_file(path);
    if (!QFile::exists(destPath))
    {
        tg_file.copy(destPath);
    }

    destPath = VIEW_PATH;
    path = SYS_LIB_DIR;
    path += "AKView.class";
    QFile view_file(path);
    if (!QFile::exists(destPath))
    {
        view_file.copy(destPath);
    }

    destPath = ITEM_PATH;
    path = SYS_LIB_DIR;
    path += "Item.class";
    QFile item_file(path);
    if (!QFile::exists(destPath))
    {
        item_file.copy(destPath);
    }

}
QString MacroCmptrd::loadStaticCode()
{
	QString code;
    QFile file("sdmacro/static.raw");
	if (file.open(QIODevice::ReadOnly|QIODevice::Text))
	{
		QTextStream stream(&file);
		code = stream.readAll();
		file.close();
	}
	return code;
}
QString MacroCmptrd::loadHeaderCode()
{
    QString code;
    QFile file("sdmacro/head.raw");
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream stream(&file);
        code = stream.readAll();
        file.close();
    }
    return code;
}
bool MacroCmptrd::checkCompiledResult(QString libName,QByteArray md5)
{
    qDebug() << "old md5 :" << md5;
    QByteArray nmd;
    QString filePath = "sdmacro\\ml\\class\\jml\\";
    filePath += libName;
    filePath += ".class";
    nmd = getFileMd5(filePath);
    qDebug() << "new md5 :" << nmd;
    if(nmd.isEmpty())
    {
        return false;
    }
    return (md5 == nmd);
}

void MacroCmptrd::pushMacro(Macro &macro)
{
    compileStack.push_back(&macro);
}
QByteArray MacroCmptrd::getFileMd5(QString filePath)
{
     QFile localFile(filePath);

     if (!localFile.open(QFile::ReadOnly))
     {
         qDebug() <<filePath <<"file open error.";
         return 0;
     }

     QCryptographicHash ch(QCryptographicHash::Md5);

     quint64 totalBytes = 0;
     quint64 bytesWritten = 0;
     quint64 bytesToWrite = 0;
     quint64 loadSize = 1024 * 4;
     QByteArray buf;

     totalBytes = localFile.size();
     bytesToWrite = totalBytes;

     while (1)
     {
         if(bytesToWrite > 0)
         {
             buf = localFile.read(qMin(bytesToWrite, loadSize));
             ch.addData(buf);
             bytesWritten += buf.length();
             bytesToWrite -= buf.length();
             buf.resize(0);
         }
         else
         {
             break;
         }

         if(bytesWritten == totalBytes)
         {
             break;
         }
     }

     localFile.close();
     QByteArray md5 = ch.result();
     return md5;
}
