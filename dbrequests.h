#ifndef DBREQUESTS_H
#define DBREQUESTS_H

#include <QString>

#include "singleton.h"

class DBRequests : public Singleton<DBRequests>
{
    friend class Singleton<DBRequests>;
public:
    ///
    /// \brief check_auth
    /// \param login
    /// \param password
    ///
    bool check_auth(QString login, QString password);
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
