#include "procthread.h"

#include <QDebug>
#include <QDir>
#include <QDate>
#include <QTime>
//#include <QWaitCondition>
//#include <QMutex>
#include <QMessageBox>

//QMutex m_mutex;
//QWaitCondition threadCondition, threadCondition1;
//volatile int countWorkerThread=0;
//volatile int countWorkerSocket=0;
QMap <int,QByteArray> lineDelayMap;

ProcThread::ProcThread(/*bool id, bool id2, QString IP, int PORT*/)
{
    count=0;
    sizeArr=1440;

    countFr=0;
    minValueId_pr=0;
    minValueId_pr_ff=16777215;
    z=16; // заголовок
    arrIdx0.resize(0);
    idF_pr.resize(3);
    idF_pr.fill(0x00,3);
    countks_tmp=-1;

    countP=0;

    filePr.setFileName("data_"+QDate::currentDate().toString("yyyyMMdd_")+QTime::currentTime().toString("hh-mm-ss-zzz")+".bin");
    filePr.open(QIODevice::WriteOnly);
    streamOut.setDevice(&filePr);

    flag=true;

}

ProcThread::~ProcThread()
{
    filePr.close();    
    //socket->close();
}

void ProcThread::slotSock(bool IdNet, QString Ip, int Port) // Подключиться(на главной форме), передача объединенных данных по сети
{
    id_net=IdNet;
    qDebug()<<"id_net="<<id_net;
    if (id_net)
    {
        //if (socket->SocketState())
            //socket->close();
        socket=new QTcpSocket;
        socket->connectToHost(Ip, Port);
        connect(socket, SIGNAL(connected()), SLOT(slotConnected()));
        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),SLOT(slotError(QAbstractSocket::SocketError)));
    }
    else
    {
        socket->close();
    }
}

void ProcThread::slotConnected()
{
    qDebug()<<"Соединение сервером-2 через порт xxxx установлено!!!";
    emit connectServ2("Соединение установлено");
}

void ProcThread::slotError(QAbstractSocket::SocketError err)
{
    QString strError = (err == QAbstractSocket::HostNotFoundError ? // "Error: " +
    "Порт не найден" : err == QAbstractSocket::RemoteHostClosedError ? //The host was not found.
    "Удаленный порт закрыл соединение" : err == QAbstractSocket::ConnectionRefusedError ? // The remote host is closed.
    "Нет соединения" : QString(socket->errorString())); // The connection was refused.
    //m_ptxtInfo->append(strError);
    emit setMessage(strError);
}

void ProcThread::run()
{
    QTimer timer;
    timer.setInterval(100);
    timer.setSingleShot(false);
    connect(&timer, SIGNAL(timeout()), this, SLOT(processing()));
    timer.start();
    exec();
}

void ProcThread::processing()
{    

    do
    {
        arrIDX.resize(0);

        QMap<int, QByteArray>::iterator it = lineDelayMap.begin();
        for (;it != lineDelayMap.end(); it++)
        {
            if (lineDelayMap[it.key()].size()>5*25*128 && flag==true) // линия задержки, 5 фреймов
            {
                arrIDX.append(it.key());
                flag=false;
                //qDebug()<<flag<<"true";
            }
            else if (lineDelayMap[it.key()].size()>0 && flag==false)
            {
                arrIDX.append(it.key());
                //qDebug()<<flag<<lineDelayMap[it.key()].size();
            }

        }

        //ArrOut.fill(0x00,128);
        for (int i=0; i<arrIDX.size(); i++)
        {
//qDebug()<<1;

            ArrOut.append(lineDelayMap[arrIDX[i]].mid(0,5*25*128)); //id
            //qDebug()<<2;
            //ArrOut.append(lineDelayMap[arrIDX[i]].mid(3,125));

            //if (ArrOut.size()!=128)


            count+=ArrOut.size();
            streamOut.writeRawData(ArrOut,ArrOut.size());
            //streamOut.writeRawData(lineDelayMap[arrIDX[i]].mid(0,5*25*128),5*25*128);

            qDebug()<<ArrOut.size()<<count;
            lineDelayMap[arrIDX[i]].remove(0,5*25*128);
            ArrOut.resize(0);
            //qDebug()<<ArrOut.size()<<lineDelayMap[arrIDX[i]].size()<<count;

        }

        for (int i=0; i<arrIDX.size(); i++)
        {
            if (lineDelayMap[arrIDX[i]].size()==0)
            {
                arrIDX.remove(i,1);

            }
        }

        //streamOut.writeRawData(lineDelayMap[it.key()],lineDelayMap[it.key()].size());
        //lineDelayMap[it.key()].remove(0,lineDelayMap[it.key()].size());



    } while (arrIDX.size()>0);

    //qDebug()<<arrIDX.size()<<"arrIDX.size()";
}

