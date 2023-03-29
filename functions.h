#pragma once
#include <QString>
#include <QByteArray>

#include "singleton.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class Functions : public Singleton<Functions>
{
    friend class Singleton<Functions>;
private:
    ///
    /// \brief wrong_user_message Вызывается при неверных сообщениях от пользователя
    /// \param QStringList data
    /// \return QByteArray Ответ для отправки клиенту
    ///
    QByteArray wrong_user_message(QStringList data);
    ///
    /// \brief func_login Авторизует пользователя
    /// \param QString username
    /// \param QString password
    /// \return QByteArray Ответ для отправки клиенту
    ///
    QByteArray func_login(QString username, QString password);
    ///
    /// \brief func_register Регистрирует пользователя
    /// \param QString username
    /// \param QString email
    /// \param QString password
    /// \return QByteArray Ответ для отправки клиенту
    ///
    QByteArray func_register(QString username, QString email, QString password);
    ///
    /// \brief get_task Генерирует задание, передаёт клиенту условие задания и его уникальный номер
    /// \param int task_number Номер задания 1-5
    /// \return QByteArray Ответ для отправки клиенту
    ///
    QByteArray get_task(int taskNumber);
    ///
    /// \brief check_task Проверяет задание, генерируя условие задания по номеру задания и его уникальному ключу,
    /// \brief сопоставляет ответ, полученный сервер с ответом, данным клиентом.
    /// \param task_number Номер задания 1-5
    /// \param task_key Уникальный ключ задания, используется как сид для функции random
    /// \param answer Ответ для отправки клиенту
    /// \return
    ///
    QByteArray check_task(int taskNumber, int taskKey, QString answer);
public:
    ///
    /// \brief parse Принимает сообщение пользователя и возвращает ответ подходящей функции
    /// \param QString user_message "command arg1 arg2 arg3 ..."
    /// \return QByteArray Ответ для отправки клиенту
    ///
    QByteArray parse(QString userMessage);
};


#endif
// FUNCTIONS_H
