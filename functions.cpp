#include <QString>
#include <QStringList>
#include <QByteArray>
#include "functions.h"

QByteArray wrong_user_message(QStringList data) {
//    return QByteArray("Произошла ошибка!");
    QString s("Переданы неверные аргументы для комманды "+data[0]+": ");
    for (int i = 1; i < data.size(); i++)
        s.append(data[i]+", ");
    s.chop(3);
    s.append("\r\n");
    return QByteArray(s.toUtf8());
}

QByteArray func_login(QString username, QString password) {
    return QByteArray("Тут должна быть авторизация\r\n");
}

QByteArray func_register(QString username, QString email, QString password) {
    return QByteArray("Тут должна быть регистрация\n");
}

QByteArray parse(QString user_message) {
    QStringList data = user_message.split(' ');
    if (data[0] == "register" && data.size() == 4)
        return func_register(data[1], data[2], data[3]);
    else if (data[0] == "login" && data.size() == 3)
        return func_login(data[1], data[2]);
    return wrong_user_message(data);
}
