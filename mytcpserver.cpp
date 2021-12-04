#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent) : QTcpServer(parent)
{
    QHostAddress addr;
       if (!listen(QHostAddress::Any,2323))
       {
           qDebug()<<"Not Server";
           close();
       }
       else
           qDebug()<<"Server start";
}

void MyTcpServer::incomingConnection(int socketDescriptor)
{    
    //qDebug()<<"incomingConnection start"<<socketDescriptor;
    SocketThread *thread = new SocketThread(socketDescriptor,this);
    //connect(thread, SIGNAL(finished()), this, SLOT(removeThread()), Qt::DirectConnection);
    connect(thread, SIGNAL(sendIP(QString,int)), this, SIGNAL(sendIP(QString,int)), Qt::DirectConnection);
    connect(thread, SIGNAL(startClient(int)), this, SIGNAL(startClient(int))); //, Qt::DirectConnection
    connect(thread, SIGNAL(stopClient(int)), this, SIGNAL(stopClient(int)), Qt::DirectConnection);
    //connect(thread, SIGNAL(stopClient(int)), this, SIGNAL(stopClient(int)), Qt::DirectConnection);
    listThread.append(thread);
    thread->start();
    //qDebug()<<"incomingConnection start end"<<socketDescriptor;
}
