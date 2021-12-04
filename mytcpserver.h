#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
//#include <QTcpServer>
//#include <QTcpSocket>
//#include <QtNetwork>
#include <QList>

#include <socketthread.h>


class QTcpServer;
//class QTcpSocket;


class MyTcpServer : public QTcpServer
{
    Q_OBJECT

public:
    MyTcpServer(QObject *parent = 0);
    void incomingConnection(int socketDescriptor);

protected:
    QList<SocketThread*> listThread;

signals:
    void sendIP(QString, int);
    void startClient(int);
    //void sendData(int);
    void stopClient(int);
};

#endif // MYTCPSERVER_H
