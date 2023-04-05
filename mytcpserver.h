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
    ///
    /// \brief MyTcpServer::slotNewConnection Создание нового подключения (mTcpSocket)
    ///
    void slotNewConnection();
    ///
    /// \brief MyTcpServer::slotClientDisconnected Закрытие соединения
    ///
    void slotClientDisconnected();
    ///
    /// \brief MyTcpServer::slotServerRead Копирование введённой строки(при подключении к серверу)
    ///
    void slotServerRead();
    //void slotReadClient();
private:
    ///
    /// \brief MyTcpServer::MyTcpServer Создание объекта класса
    /// \param parent Подключение сигналов и слотов
    ///
    ///
    explicit MyTcpServer(QObject *parent = nullptr);
    ///
    /// \brief MyTcpServer::~MyTcpServer Деструктор, вызывающий функцию, закрывающую соединение
    ///
    ///
    ~MyTcpServer();
    QTcpServer * mTcpServer;
    QMap<int, QTcpSocket*> mTcpSocket;
    int serverStatus;
};


#endif // MYTCPSERVER_H







