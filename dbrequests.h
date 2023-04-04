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
    /// \return Проверяет, существует ли такой пользователь
    ///
    bool reg(QString login, QString password);
    ///
    /// \brief reset_connections Очищает связь между пользователями и аккаунтами в бд
    ///
    void reset_connections();
    ///
    /// \brief correct_answer Отмечает верное выполнение задания пользователем в бд
    /// \param userData Логин + пароль
    /// \param numberTask Номер задания
    ///
    void correct_answer(QString userData, int numberTask);
    ///
    /// \brief correct_answer Отмечает неверное выполнение задания пользователем в бд
    /// \param userData Логин + пароль
    /// \param numberTask Номер задания
    ///
    void incorrect_answer(QString userData, int numberTask);
};

#endif // DBREQUESTS_H
