#include "singleclient.h"

SingletonClient::~SingletonClient()
{
    socket->close();
}

SingletonClient::SingletonClient()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("172.23.48.246", 33333);
    connect(socket, &QTcpSocket::readyRead, this, &SingletonClient::slot_readFromServer);
    qDebug() << "Клиент запущен";
}

void SingletonClient::slot_readFromServer()
{
    QString data;
    QStringList datas;
    while(socket->bytesAvailable()>0) {
        data.append(socket->readAll());
    }
    if (data.size() > 0) {
        qDebug() << "data: " << data << "\n";
        datas = data.split("\n");
        for (int i = 0; i < datas.size(); i++) {
            qDebug() << "datas["<<i<<"]: " << datas[i] << "\n";
            emit this->serverAnswer(datas[i]);
        }
    }
}

bool SingletonClient::sendToServer(QString answer)
{
    socket->write((answer+QString("\n")).toUtf8());
    return 0;
}
