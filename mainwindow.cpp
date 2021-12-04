#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "procthread.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ServerForm");
    myLayout=new QGridLayout;

    for (int i=0; i<2; ++i)
    {       
        myLabel[i]=new QLabel;        
        myLayout->addWidget(myLabel[i],i,0,Qt::AlignLeft);
        myLabel[i]->setDisabled(true);
        myLabel[i]->setText("Нет соединения");

        myLabel_1[i]=new QLabel;
        myLayout->addWidget(myLabel_1.value(i),i,1,Qt::AlignCenter);
        myLabel_1.value(i)->setDisabled(true);
        myLabel_1.value(i)->setText("Нет данных");
    }
    myWidget = new QWidget;
    myWidget->setLayout(myLayout);
    ui->scrollArea->setWidget(myWidget);    

    ProcThread *myProc=new ProcThread(); // поток-объединение
    myProc->start();

    serv=new MyTcpServer();
    connect(serv, SIGNAL(sendIP(QString,int)), this, SLOT(slotSendIP(QString,int))/*, Qt::DirectConnection*/);
    connect(serv, SIGNAL(startClient(int)), this, SLOT(slotStart(int))/*, Qt::DirectConnection*/);
    connect(serv, SIGNAL(stopClient(int)), this, SLOT(slotStop(int))/*, Qt::DirectConnection*/); // НЕ РАБОТАЕТ
    //connect(serv, SIGNAL(startClient(int)), this, SLOT(slotStart(int))/*, Qt::DirectConnection*/);

}

void MainWindow::slotSendIP(QString strIP,int idSock)
{   
    VecSockDescr.append(idSock);

    if (VecSockDescr.size()>2)
    {
        myLabel[VecSockDescr.size()-1]=new QLabel;
        myLayout->addWidget(myLabel.value(VecSockDescr.indexOf(idSock)),VecSockDescr.indexOf(idSock),0);
        myLabel_1[VecSockDescr.indexOf(idSock)]=new QLabel;
        myLayout->addWidget(myLabel_1.value(VecSockDescr.indexOf(idSock)),VecSockDescr.indexOf(idSock),1,Qt::AlignCenter);

        myLabel.value(VecSockDescr.indexOf(idSock))->setDisabled(false);
        myLabel.value(VecSockDescr.indexOf(idSock))->setText(" Подключение с адреса "+strIP);
        myLabel_1.value(VecSockDescr.indexOf(idSock))->setDisabled(true);
        myLabel_1.value(VecSockDescr.indexOf(idSock))->setText("Нет данных");
    }
    else
    {        
        myLabel.value(VecSockDescr.indexOf(idSock))->setDisabled(false);
        myLabel.value(VecSockDescr.indexOf(idSock))->setText(" Подключение с адреса "+strIP);
    }
}
void MainWindow::slotStart(int idSock)
{
    myLabel_1.value(VecSockDescr.indexOf(idSock))->setDisabled(false);
    myLabel_1.value(VecSockDescr.indexOf(idSock))->setText("Поступление данных ");
}

void MainWindow::slotStop(int idSock)
{   
    myLabel_1.value(VecSockDescr.indexOf(idSock))->setDisabled(true);
    myLabel_1.value(VecSockDescr.indexOf(idSock))->setText("Остановка потока ");
}

/*virtual*/ /*void MainWindow::slotNewConnection()
{
    QTcpSocket *pClientSocket = m_server->nextPendingConnection();
    sockDescrList.append(pClientSocket->socketDescriptor());

    thread = new SocketThread(pClientSocket->socketDescriptor(),this);
    //connect(thread, SIGNAL(finished()), this, SLOT(removeThread()), Qt::DirectConnection);
    //connect(thread, SIGNAL(sendIP(QString,int)), this, SIGNAL(sendIP(QString,int)), Qt::DirectConnection);
    //connect(thread, SIGNAL(startClient(int)), this, SIGNAL(startClient(int)), Qt::DirectConnection);
    //connect(thread, SIGNAL(stopClient(int)), this, SIGNAL(stopClient(int)), Qt::DirectConnection);
    //m_threads.append(thread);
    //thread->start();


    if (sockDescrList.size()>2)
    {
        myLabel[sockDescrList.size()-1]=new QLabel;
        ui->gridLayout->addWidget(myLabel.value(sockDescrList.size()-1),sockDescrList.size()-1,0,Qt::AlignLeft);

        myLabel_1[sockDescrList.size()-1]=new QLabel;
        ui->gridLayout->addWidget(myLabel_1.value(sockDescrList.size()-1),sockDescrList.size()-1,1,Qt::AlignCenter);
        myLabel_1.value(sockDescrList.size()-1)->setDisabled(true);
        myLabel_1.value(sockDescrList.size()-1)->setText("Нет данных");
    }
    myLabel.value(sockDescrList.size()-1)->setDisabled(false);
    myLabel.value(sockDescrList.size()-1)->setText("Подключение с адреса "+(pClientSocket->peerAddress()).toString());
}*/

MainWindow::~MainWindow()
{
    delete ui;
}
