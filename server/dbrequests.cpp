#include "dbrequests.h"


/*
* Users
* --------------------------------------------------
* id | user_type | login | password | connection_id
* --------------------------------------------------
*    |           |       |          |
*    |           |       |          |
*    |           |       |          |
* --------------------------------------------------
*
* user_type: 0 - студент, 1 - преподаватель
* если нет соединения, то connection_id = Null
*
* Tasks
* ----------------------------------------------------
* id | user_id   | task_id | task_number | is_correct
* ----------------------------------------------------
*    |           |         |             |
*    |           |         |             |
*    |           |         |             |
* ----------------------------------------------------
*/

bool DBRequests::auth(QString login, QString password, int userKey)
{
    // Сперва находим в базе данных пользователя с соответствующим логином и паролем.
    QVector<QMap<QString, QString>> answer = DataBase::getInstance()->db_request(
                QString("select * from Users "
                        "where login = '%1' and password = '%2'").arg(login, password));
    // Если таких пользователей нет, то подключение не удалось.
    if (answer.size() == 0) {
        return false;
    // Если таких пользователей (строк в базе данных) больше одного, то что-то пошло не так.
    } else if (answer.size() > 1) {
        qDebug() << "Ошибка. Пользователей с данным логином и паролем больше одного.";
        throw;
    /* Проверяем присвоен ли текущему пользователю дескриптор,
     * если да и он совпадает с нашим, то авторизация успешна,
     * если да и он не совпадает с нашим, то авторизация не успешна,
     * если нет, то присваиваем ему userKey и сообщаем, что авторизация успешна. */
    } else {
        if (answer[0]["connection_id"] != "" and answer[0]["connection_id"] == QString::number(userKey)) {
            return true;
        } else if (answer[0]["connection_id"] != "" and answer[0]["connection_id"] != QString::number(userKey)) {
            return false;
        } else if (answer[0]["connection_id"] == "") {
            DataBase::getInstance()->db_request(
                            QString("update Users "
                                    "set connection_id = %1 "
                                    "where login = '%2' and password = '%3'").arg(QString::number(userKey), login, password));
            return true;
        }
    }
    qDebug() << "Что-то пошло не так.";
    throw;
}

bool DBRequests::check_auth(int userKey)
{
    // Ищем авторизированных пользователей с данным подключением.
    QVector<QMap<QString, QString>> answer = DataBase::getInstance()->db_request(
                QString("select * from Users "
                        "where connection_id = %1").arg(QString::number(userKey)));
    // Если таких пользователей нет, то авторизация не пройдена.
    if (answer.size() == 0) {
        return false;
    // Если таких пользователей (строк в базе данных) больше одного, то что-то пошло не так.
    } else if (answer.size() > 1) {
        qDebug() << "Ошибка. Пользователей с данным подключением больше одного.";
        throw;
    // Если такой пользователь один, то авторизация успешна.
    } else {
        return true;
    }
    qDebug() << "Что-то пошло не так.";
    throw;
}


bool DBRequests::reg(QString login, QString password, int userType)
{
    QVector<QMap<QString, QString>> answer = DataBase::getInstance()->db_request(
                QString("select * from Users "
                        "where login = '%1'").arg(login));
    // Если данный логин найден в базе данных, значит он занят.
    if (answer.size() != 0) {
        return false;
    // Добавляем нового пользователя в базу данных.
    } else {
        DataBase::getInstance()->db_request(QString("insert into Users(user_type,login, password) "
                                                    "values (%1, '%2', '%3')").arg(QString::number(userType), login, password));
        return true;
    }

}

void DBRequests::reset_connections()
{
    // Удаляет дескрипторы соединений для всех пользователей.
    DataBase::getInstance()->db_request(QString("update Users "
                                                "set connection_id = null"));
}

void DBRequests::task_is_done(int userKey, int taskNumber, int taskKey, bool isCorrect)
{
    QVector<QMap<QString, QString>> answer = DataBase::getInstance()->db_request(
                QString("select id from Users where connection_id = %1").arg(QString::number(userKey)));
    QString userId = answer[0]["id"];
    DataBase::getInstance()->db_request(QString("insert into Tasks(user_id, task_id, task_number, is_correct) "
                                                "values(%1, %2, %3, %4)").arg
                                        (userId, QString::number(taskKey),
                                         QString::number(taskNumber), QString::number(isCorrect)));
}

