#pragma once

#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

#include <QCoreApplication>
#include <QString>

#include "singleton.h"


///
/// \brief The MyTcpServer class Класс для сервера
///
class MyTcpServer : public QObject, public Singleton <MyTcpServer>
{
    Q_OBJECT
    friend class Singleton<MyTcpServer>;
public slots:
    void slotNewConnection();
    void slotClientDisconnected();

    void slotServerRead();
    //void slotReadClient();
private:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
    QTcpServer * mTcpServer;
    QMap<int, QTcpSocket*> mTcpSocket;
    int serverStatus;
};


#endif // MYTCPSERVER_H







