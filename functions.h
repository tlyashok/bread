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
QByteArray wrong_user_message(QStringList data);
///
/// \brief func_login Авторизует пользователя
/// \param QString username
/// \param QString password
/// \return QByteArray response
///
QByteArray func_login(QString username, QString password);
///
/// \brief func_register Регистрирует пользователя
/// \param QString username
/// \param QString email
/// \param QString password
/// \return QByteArray response
///
QByteArray func_register(QString username, QString email, QString password);
///
/// \brief parse Принимает сообщение пользователя и возвращает ответ подходящей функции
/// \param QString user_message "command arg1 arg2 arg3 ..."
/// \return QByteArray response command(arg1, arg2, arg3, ...)
///
QByteArray parse(QString user_message);
#endif
// FUNCTIONS_H
