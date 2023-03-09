#include "mytcpserver.h"
#include "functions.h"

MyTcpServer::~MyTcpServer()
{
    for (QTcpSocket* s : mTcpSocket)
            s->close();
    mTcpServer->close();
    server_status=0;
}
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

void MyTcpServer::slotNewConnection(){
    QTcpSocket* socket = mTcpServer->nextPendingConnection();
    if(server_status==1){
        socket->write("Hello, World!!! I am echo server!\r\n");
        connect(socket, &QTcpSocket::readyRead,
                this,&MyTcpServer::slotServerRead);
        connect(socket,&QTcpSocket::disconnected,
                this,&MyTcpServer::slotClientDisconnected);
    }
    mTcpSocket.insert(socket->socketDescriptor(), socket);
}

void MyTcpServer::slotServerRead(){
    QTcpSocket* socket = (QTcpSocket*)sender();
    QString data;
    while(socket->bytesAvailable()>0) {
        data.append(socket->readAll());
    }
    if (data.size() > 0 && data.back() == '\n') {
        socket->write(parse(data));
        data.clear();
    }
}

void MyTcpServer::slotClientDisconnected(){
    QTcpSocket* socket = (QTcpSocket*)sender();
    socket->close();
}
