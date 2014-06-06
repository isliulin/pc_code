#ifndef QPROTOCOLTOOL_H
#define QPROTOCOLTOOL_H
#include "qprogectmanager.h"

class QProtocolTool
{
public:
    QProtocolTool();
    static QVector <PLC_FACTORY> getAllProtocols();
    static QVector <PLC_MODEL> getProtocols(QString absPath);
    static bool getAllProperty(QString absPath,PLC_MODEL &model);
    static QMap<QString, QString> getDriversConfig();
};

#endif // QPROTOCOLTOOL_H
