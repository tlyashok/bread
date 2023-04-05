#ifndef DBREQUESTS_H
#define DBREQUESTS_H

#include <QString>
#include <QDebug>

#include "singleton.h"
#include "database.h"

class DBRequests : public Singleton<DBRequests>
{
    friend class Singleton<DBRequests>;
public:
    ///
    /// \brief auth Находит пользователя в базе данных и присваивает ему уникальный дексриптор подключения
    /// \param login
    /// \param password
    /// \param userKey Дескриптор подключения
    /// \return Проверяет, получилось ли авторизироваться
    ///
    bool auth(QString login, QString password, int userKey);
    ///
    /// \brief check_auth Проверяет, существует ли пользователь с данным дескриптором в базе данных.
    /// \param userKey Дескриптор подключения
    /// \return Проверяет, получилось ли найти ровно одного такого пользователя
    ///
    bool check_auth(int userKey);
    ///
    /// \brief reg Регистрация пользователя по логину и паролю
    /// \param login
    /// \param password
    /// \param userType
    /// \return Проверяет, успешна ли выполнена регистрация
    ///
    bool reg(QString login, QString password, int userType);
    ///
    /// \brief reset_connections Очищает связь между пользователями и аккаунтами в бд
    ///
    void reset_connections();
    ///
    /// \brief correct_answer Отмечает верное выполнение задания пользователем в бд
    /// \param taskNumber Номер задания
    /// \param userKey Дескриптор подключения
    /// \param taskKey Дескриптор уникального варианта задания
    /// \param isCorrect Указывает, нужно ли пометить выполнение задания как верное или нет
    ///
    void task_is_done(int userKey, int taskNumber, int taskKey, bool isCorrect);

};

#endif // DBREQUESTS_H
