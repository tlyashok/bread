#ifndef SINGLECLIENT_H
#define SINGLECLIENT_H

#include <QString>
#include <QTcpSocket>
#include <QVariant>
#include <QDebug>
#include <QObject>

#include "singleton.h"

class SingletonClient : public QObject, public Singleton<SingletonClient>
{
    friend class Singleton<SingletonClient>;
    Q_OBJECT
private:
    QTcpSocket* socket;
    ///
    /// \brief SingletonClient Конструктор по умолчанию
    ///
    SingletonClient();
    ///
    /// \brief ~SingletonClient Деструктор
    ///
    SingletonClient(SingletonClient&) = delete;
    SingletonClient& operator=(SingletonClient&) = delete;

public:
    ///
    /// \brief sendToServer Отправка сообщения серверу
    /// \return
    ///
    bool sendToServer(QString);
    ~SingletonClient();

private slots:
    ///
    /// \brief slot_readFromServer Принятие сообщение с сервера
    ///
    void slot_readFromServer();

signals:
    ///
    /// \brief taskArrived Сигнал о прибытии задания
    ///
    void serverAnswer(QString);

};

#endif // SINGLECLIENT_H
