#pragma once
#include <QString>
#include <QByteArray>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
///
/// \brief wrong_user_message Вызывается при неверных сообщениях от пользователя
/// \param QStringList data
/// \return QByteArray response
///
QByteArray wrong_user_message(QStringList data) {
//    return QByteArray("Произошла ошибка!");
    QString s("Переданы неверные аргументы для комманды "+data[0]+": ");
    for (int i = 1; i < data.size(); i++)
        s.append(data[i]+", ");
    s.chop(3);
    s.append("\r\n");
    return QByteArray(s.toUtf8());
}
///
/// \brief func_login Авторизует пользователя
/// \param QString username
/// \param QString password
/// \return QByteArray response
///
QByteArray func_login(QString username, QString password) {
    return QByteArray("Тут должна быть авторизация\r\n");
}
///
/// \brief func_register Регистрирует пользователя
/// \param QString username
/// \param QString email
/// \param QString password
/// \return QByteArray response
///
QByteArray func_register(QString username, QString email, QString password) {
    return QByteArray("Тут должна быть регистрация\n");
}
///
/// \brief parse Принимает сообщение пользователя и возвращает ответ подходящей функции
/// \param QString user_message "command arg1 arg2 arg3 ..."
/// \return QByteArray response command(arg1, arg2, arg3, ...)
///
QByteArray parse(QString user_message) {
    QStringList data = user_message.split(' ');
    if (data[0] == "register" && data.size() == 4)
        return func_register(data[1], data[2], data[3]);
    else if (data[0] == "login" && data.size() == 3)
        return func_login(data[1], data[2]);
    return wrong_user_message(data);
}
#endif
// FUNCTIONS_H
