#ifndef SCRIPTLIB_H
#define SCRIPTLIB_H
#include "scriptLib_global.h"
#include <QVector>
#include <QString>
typedef struct  MemberFun
{
    QString funName;
    QString importCode;
    QString daemon;
}stMemberFun;
typedef struct  ScriptLib
{
    QString LibName;
    QVector <stMemberFun> functions;
}stScriptLib;

extern "C" QVector<stScriptLib> SCRIPTLIBSHARED_EXPORT getSysLibs();
#endif // SCRIPTLIB_H
