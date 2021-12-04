#ifndef PROCTHREAD_H
#define PROCTHREAD_H

#include <QThread>
#include <QThreadStorage>
#include <QMap>

#include "myfunc.h"
#include "mainwindow.h"

class ProcThread : public QThread
{
    Q_OBJECT

    public:
        ProcThread();
        ~ProcThread();
        void run();

    private:
        QVector<int> arrIDX, arrIdx0;
        QMap<int,int> countKS, countKS2, arrCountFr, arrCountFrTrue;
        MyFunc func;
        QMap<int,QByteArray> idF;
        QMap<int,QByteArray> ks1, ks2, kb1, kb2, ks_tmp, ks1_sf, ks2_sf;
        int idx, count, sizeArr;
        QByteArray id_f, id_f_pr;
        int minValueId_pr, minValueId_pr_ff;
        int z, countFr; // заголовок, общее количество фреймов
        QByteArray idF2, idF3;
        QMap<int,QByteArray> lineDelayInf, lineDelayInf_tmp;
        QMap<QPair<int,int>, QVector <int> > pos, pos_tmp;
        QByteArray idF_pr;
        int countks_tmp, countks_tmp2;
        QFile filePr;
        QDataStream streamOut;
        QTextStream strTxt;
        QFile fileOut;
        //int count;
        //void processing(int);
        int countP;
        QMap<int,int> countks_kadr;
        QByteArray arrBlock, arrBlock1;
        QByteArray ArrOut;
        QTcpSocket *socket;
        bool id_saveHD;
        bool id_net;
        bool flag;
public slots:
void processing();
    private slots:
        void slotError(QAbstractSocket::SocketError);
        void slotConnected();
        void slotSock(bool,QString,int);
        //void slotSaveHD(bool);


    signals:
        void connectServ2(QString);
        void setMessage(QString);
};


#endif // PROCTHREAD_H
