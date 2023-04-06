#include <QString>
#include <QStringList>
#include <QByteArray>
#include "functions.h"

QByteArray Functions::wrong_user_message(QStringList data) {
    QString s("Переданы неверные аргументы для комманды "+data[0]+": ");
    for (int i = 1; i < data.size(); i++)
        s.append(data[i]+", ");
    s.chop(3);
    s.append("\r\n");
    return QByteArray(s.toUtf8());
}

QByteArray Functions::func_login(QString username, QString password) {
    return QByteArray("Тут должна быть авторизация\r\n");
}

QByteArray Functions::func_register(QString username, QString email, QString password) {
    return QByteArray("Тут должна быть регистрация\r\n");
}

QByteArray Functions::parse(QString userMessage) {
    QStringList data = userMessage.split(' ');
    if (data[0] == "register")
        if (data.size() == 4)
            return func_register(data[1], data[2], data[3]);
        else
            return wrong_user_message(data);
    else if (data[0] == "login")
        if ( data.size() == 3)
            return func_login(data[1], data[2]);
        else
            return wrong_user_message(data);
    else {
        return QByteArray(userMessage.toUtf8());
    }
}

QByteArray Functions::get_task(int taskNumber)
{
    switch (taskNumber)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    }
}

QByteArray Functions::check_task(int taskNumber, int taskKey, QString answer)
{
    switch (taskNumber)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    }
}
