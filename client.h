#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QTcpSocket>
#include <QVariant>
#include <QDebug>

#include "singleton.h"

class SingletonClient : public Singleton<SingletonClient>
{
    friend class Singleton<SingletonClient>;
    Q_OBJECT;
private:
    QTcpSocket* socket;
    ///
    /// \brief SingletonClient Конструктор по умолчанию
    ///
    SingletonClient();
    ///
    /// \brief ~SingletonClient Деструктор
    ///
    ~SingletonClient();
    SingletonClient(SingletonClient&) = delete;
    SingletonClient& operator=(SingletonClient&) = delete;

public:
    ///
    /// \brief sendToServer Отправка сообщения серверу
    /// \return
    ///
    bool sendToServer(QString);

private slots:
    void slot_readFromServer();

};

#endif // CLIENT_H

