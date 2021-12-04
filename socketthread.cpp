#include "socketthread.h"

extern QMap <int,QByteArray> lineDelayMap;

SocketThread::SocketThread(int socketDescriptor, QObject *parent) : QThread(parent),
    m_socketDeckriptor(socketDescriptor), m_nNextBlockSize0(0)
{
    //count_arr=0;
    //m_nNextBlockSize0=0;
    startTh=false;
}

void SocketThread::run()
{
    m_client=new QTcpSocket();
    //qDebug()<<"run";
    if (!m_client->setSocketDescriptor(m_socketDeckriptor))
    {
        emit error(m_client->error());
        return;
    }

    //connect(m_client, SIGNAL(readyRead()), this, SLOT(slotReadyRead()), Qt::DirectConnection);
    //connect(m_client, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);
    emit sendIP((m_client->peerAddress()).toString(),m_socketDeckriptor);

    m_addr=m_client->peerAddress();
    qDebug()<<"New client..."<<m_addr;
    count_arr=0;

    QTimer *timer;
    timer = new QTimer();
    timer->setInterval(100);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotReadyRead()));
    //connect(&timer, SIGNAL(timeout()), this, SLOT(slotProc()));
    //QTimer *timer1;
    //timer1 = new QTimer();
    //timer1->setInterval(100);
    //timer1->setSingleShot(false);
    //connect(timer, SIGNAL(timeout()), this, SLOT(sendData(int m_socketDeckriptor)));
    timer->start();
    //timer1->start();
    //emit sendData(m_socketDeckriptor);

    exec();
}

void SocketThread::slotReadyRead()
{
    QDataStream in(m_client);
    //qDebug()<<"QDataStream in( m_client);";

    for (;;)
    {
        //qDebug()<<1; //qDebug()<<"m_nNextBlockSize0="<<m_nNextBlockSize0;
            if (!m_nNextBlockSize0) // m_nNextBlockSize0==0
            {
                //qDebug()<<2;
                if ( m_client->bytesAvailable() < sizeof(quint16))
                {
                    //qDebug()<<3<<sizeof(quint16);
                   /* if (startTh==false)
                    {
                        emit stopClient(m_socketDeckriptor);
                        startTh=true;
                        qDebug()<<"emit stopClient";
                    }*/
                    break;

                }
                in >> m_nNextBlockSize0;
                //qDebug()<<4<<m_nNextBlockSize0;
            }

            if ( m_client->bytesAvailable() < m_nNextBlockSize0)
            {
                //qDebug()<<5<<m_nNextBlockSize0;

                break;
            }

            QByteArray arr;
            in >> arr;
            count_arr+=arr.size();

             m_nNextBlockSize0 = 0;

            lineDelayMap[m_client->socketDescriptor()].append(arr);
            //qDebug()<<m_client->socketDescriptor()<<arr.size()<<"count_arr="<<count_arr<<m_nNextBlockSize0<<QTime::currentTime().toString("hh-mm-ss-zzz")<<arr.mid(0,10).toHex()<<lineDelayMap[m_client->socketDescriptor()].size();


            if (startTh==false)
            {
                emit startClient(m_socketDeckriptor);
                startTh=true;
                //qDebug()<<"emit startClient";
            }

            /*if (m_client->waitForReadyRead(1000)==false)
            {
                    emit stopClient(m_socketDeckriptor);
                    qDebug()<<"stopClient";
                    startTh=false;
            }*/
    }

}

void SocketThread::onDisconnect()
{
    //QTcpSocket *m_client=(QTcpSocket*)sender();
    m_client->deleteLater();
    qDebug()<<"stop Thread";
    quit();
}

void SocketThread::displayError(QAbstractSocket::SocketError error)
{
    if (error=QAbstractSocket::RemoteHostClosedError)
        qDebug()<<"client otkl";
    else
        qDebug()<<"error";
}
