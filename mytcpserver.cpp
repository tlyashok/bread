#include "mytcpserver.h"
#include "functions.h"
///
/// \brief MyTcpServer::~MyTcpServer Деструктор, вызывающий функцию, закрывающую соединение
///
MyTcpServer::~MyTcpServer()
{
    //mTcpSocket->close();
    mTcpServer->close();
    server_status=0;
}
///
/// \brief MyTcpServer::MyTcpServer Создание объекта класса
/// \param parent Подключение сигналов и слотов
///
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        server_status=1;
        qDebug() << "server is started";
    }
}
///
/// \brief MyTcpServer::slotNewConnection Создание нового подключения (mTcpSocket)
///
void MyTcpServer::slotNewConnection(){
    if(server_status==1){
        mTcpSocket = mTcpServer->nextPendingConnection();
        mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
        connect(mTcpSocket, &QTcpSocket::readyRead,
                this,&MyTcpServer::slotServerRead);
        connect(mTcpSocket,&QTcpSocket::disconnected,
                this,&MyTcpServer::slotClientDisconnected);
    }
}
///
/// \brief MyTcpServer::slotServerRead Копирование введённой строки(при подключении к серверу)
///
void MyTcpServer::slotServerRead(){
    QString data;
    while(mTcpSocket->bytesAvailable()>0) {
        data.append(mTcpSocket->readAll());
    }
    if (data.size() > 0 && data.back() == '\n') {
        mTcpSocket->write(parse(data));
        data.clear();
    }
}
///
/// \brief MyTcpServer::slotClientDisconnected Закрытие соединения
///
void MyTcpServer::slotClientDisconnected(){
    mTcpSocket->close();
}
