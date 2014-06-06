#ifndef CONNECTTRD_H
#define CONNECTTRD_H
#include<QThread>

class QTcpSocket;
class ConnectTrd : public QThread
{
    Q_OBJECT
   public:
       ConnectTrd(QObject *parent = 0);
       ~ConnectTrd();
       virtual void run();
       void setIp(QString ip);
       //bool connected ;
       QString m_Ip;
       QVector<QTcpSocket *>sockets;
       void connectOne(QString ip);
signals:
       void ConnectTo(QString ip,QString name);
   public slots:
       void canRead();
 };
#endif // CONNECTTRD_H
