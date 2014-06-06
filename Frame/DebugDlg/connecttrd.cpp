#include "connecttrd.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QTextCodec>
#define AKHMI_PORT 10101
ConnectTrd::ConnectTrd(QObject *parent) :
        QThread(parent)
{
    for(int i=0; i<255; i++)
    {
        sockets << NULL;
    }
}
ConnectTrd::~ConnectTrd()
{
    for(int i=0; i<255; i++)
    {
        if(sockets[i])
        {
            sockets[i]->disconnectFromHost();
            sockets[i]->deleteLater();
        }

    }
    sockets.clear();
}
void ConnectTrd::setIp(QString ip)
{
    m_Ip = ip;
}
void ConnectTrd::run()
{
    QString ip;
    QString ipHead = m_Ip.left(m_Ip.lastIndexOf(".")+1);

    for(int i=0; i<255; i++)
    {
        if(!sockets[i])
        {
            sockets[i] = new QTcpSocket();
            connect(sockets[i],SIGNAL(readyRead()),this,SLOT(canRead()));

        }
        else
        {
            sockets[i]->disconnectFromHost();
        }

        //msleep(1);
        ip = ipHead + QString::number(i+1);
        sockets[i]->connectToHost(ip,AKHMI_PORT);
        //sockets[i]->waitForConnected(1);
        //qDebug() << "connect to Host :"<< ip;
        //qDebug() << sockets[i]->errorString();
    }

    exec();
}
void ConnectTrd::canRead()
{
    qDebug() << "canRead";
    QTcpSocket* socket = qobject_cast<QTcpSocket *>(sender());
    if(socket)
    {

        QHostAddress hostIp = socket->peerAddress();
        QByteArray data = socket->readAll();
        QString hostName = QString::fromUtf8(data.data());
        qDebug() <<"read from hostIp "<<hostIp <<data.size();
        qDebug() << hostName;
        if(!hostIp.isNull())
        {
            emit ConnectTo(hostIp.toString(),hostName);
        }
    }
}
void ConnectTrd::connectOne(QString ip)
{
    QTcpSocket *socket = new QTcpSocket();

    connect(socket,SIGNAL(readyRead()),this,SLOT(canRead()));


    socket->connectToHost("192.168.1.240",AKHMI_PORT);

    socket->waitForConnected();

    qDebug()<< socket->waitForConnected()<< socket->errorString();
}
