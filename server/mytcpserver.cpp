#include "mytcpserver.h"
#include "functions.h"


MyTcpServer::~MyTcpServer()
{
    for (QTcpSocket* s : mTcpSocket)
            s->close();
    mTcpServer->close();
    serverStatus=0;
}


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

void MyTcpServer::slotNewConnection(){
    QTcpSocket* socket = mTcpServer->nextPendingConnection();
    if(serverStatus==1){
        socket->write("Сервер запущен.\r\n");
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
    QByteArray response;
    while(socket->bytesAvailable()>0) {
        data.append(socket->readLine());
    }
    if (data.size() > 0 && data.back() == '\n') {
        QStringList datas = data.split("\n");
        for (int i = 0; i < datas.size(); i++) {
            data = QString::number(socket->socketDescriptor()) + " " + datas[i];
            qDebug() << "data: " << data << '\n';
            response = Functions::getInstance()->parse(data);
            qDebug() << "response: "<< response << '\n';
            socket->write(response+"\n");
            data.clear();
        }
    }
}

void MyTcpServer::slotClientDisconnected(){
    QTcpSocket* socket = (QTcpSocket*)sender();
    socket->close();
}
