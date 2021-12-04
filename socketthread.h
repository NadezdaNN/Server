#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>

class SocketThread : public QThread

{
    Q_OBJECT
public:
    SocketThread(int socketDescriptor, QObject *parent = 0);
        //~SocketThread();
        void run();
        bool startTh;
private:
    int m_socketDeckriptor;
    QTcpSocket *m_client;
    QHostAddress m_addr;
    int count_arr;
    quint16 m_nNextBlockSize0;

public slots:
    //void slotProc();
    void slotReadyRead();
    void onDisconnect();
    void displayError(QAbstractSocket::SocketError error);
    //void sendData(int);

signals:
    void error(QAbstractSocket::SocketError);
    void sendIP(QString, int);
    void startClient(int);
    void stopClient(int);
    //void sendData(int);

};

#endif // SOCKETTHREAD_H
