#include "mytcpserver.h"
#include "functions.h"
<<<<<<< HEAD


=======
///
/// \brief MyTcpServer::~MyTcpServer Деструктор, вызывающий функцию, закрывающую соединение
///
>>>>>>> 15297397c8fb95c9313160a48e57c353160982e4
MyTcpServer::~MyTcpServer()
{
    for (QTcpSocket* s : mTcpSocket)
            s->close();
    mTcpServer->close();
    serverStatus=0;
}
<<<<<<< HEAD

=======
///
/// \brief MyTcpServer::MyTcpServer Создание объекта класса
/// \param parent Подключение сигналов и слотов
///
>>>>>>> 15297397c8fb95c9313160a48e57c353160982e4
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        serverStatus=1;
        qDebug() << "server is started";
    }
}
///
/// \brief MyTcpServer::slotNewConnection Создание нового подключения (mTcpSocket)
///
void MyTcpServer::slotNewConnection(){
    QTcpSocket* socket = mTcpServer->nextPendingConnection();
    if(serverStatus==1){
        socket->write("Hello, World!!! I am echo server!\r\n");
        connect(socket, &QTcpSocket::readyRead,
                this,&MyTcpServer::slotServerRead);
        connect(socket,&QTcpSocket::disconnected,
                this,&MyTcpServer::slotClientDisconnected);
    }
    mTcpSocket.insert(socket->socketDescriptor(), socket);
}
///
/// \brief MyTcpServer::slotServerRead Копирование введённой строки(при подключении к серверу)
///
void MyTcpServer::slotServerRead(){
    QTcpSocket* socket = (QTcpSocket*)sender();
    QString data;
    while(socket->bytesAvailable()>0) {
        data.append(socket->readAll());
    }
    if (data.size() > 0 && data.back() == '\n') {
        socket->write(Functions::getInstance()->parse(data));
        data.clear();
    }
}
///
/// \brief MyTcpServer::slotClientDisconnected Закрытие соединения
///
void MyTcpServer::slotClientDisconnected(){
    QTcpSocket* socket = (QTcpSocket*)sender();
    socket->close();
}
