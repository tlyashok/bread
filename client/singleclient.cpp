#include "singleclient.h"

SingletonClient::~SingletonClient()
{
    socket->close();
}

SingletonClient::SingletonClient()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 33333);
    connect(socket, &QTcpSocket::readyRead, this, &SingletonClient::slot_readFromServer);
    qDebug() << "Клиент запущен";
}

void SingletonClient::slot_readFromServer()
{
    QString data;
    while(socket->bytesAvailable()>0) {
        data.append(socket->readAll());
    }
    qDebug() << data;
}

bool SingletonClient::sendToServer(QString answer)
{
    socket->write(answer.toUtf8());
    return 0;
}
