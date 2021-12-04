#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QtNetwork>
#include <QMap>
#include <QLabel>
#include <QHash>
#include <QGridLayout>
#include <QWidget>

#include "mytcpserver.h"

class QTcpServer;
class QTextEdit;
class QTcpSocket;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow//, public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    QTcpServer *m_server;

    QMap<int,QLabel*> myLabel, myLabel_1;
    QMap<int,QLabel*>::iterator imap;
    QList<int> VecSockDescr;
    QWidget *myWidget;
    QGridLayout* myLayout;

protected:
    MyTcpServer *serv;


public slots:
    //virtual void slotNewConnection();
    void slotSendIP(QString,int);
    void slotStart(int);
    void slotStop(int);

};

#endif // MAINWINDOW_H
