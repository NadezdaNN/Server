#-------------------------------------------------
#
# Project created by QtCreator 2021-09-21T09:36:39
#
#-------------------------------------------------

QT       += core gui
QT       += network

TARGET = ServerForm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mytcpserver.cpp \
    socketthread.cpp \
    procthread.cpp \
    myfunc.cpp

HEADERS  += mainwindow.h \
    mytcpserver.h \
    socketthread.h \
    procthread.h \
    myfunc.h

FORMS    += mainwindow.ui
