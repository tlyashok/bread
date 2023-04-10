#include "dbrequests.h"


/* Создаёт две таблицы:
 *
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
 *
 * Tasks
 * -------------------------------------------------------------
 * id | user_id   | task_id | task_number | answer | is_correct
 * -------------------------------------------------------------
 *    |           |         |             |        |
 *    |           |         |             |        |
 *    |           |         |             |        |
 * -------------------------------------------------------------
 *
 * Tasks.user_id <-> Users.id
 *
 * UserGroups
 * ---------------
 * id | user_id
 * ---------------
 *    |
 *    |
 *    |
 * ---------------
 *
 * UserGroups.student_id <-> Users.id
 *
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


bool DBRequests::reg(QString login, QString password, int userType, QString loginTeacher)
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
        QVector<QMap<QString, QString>> current_user =
                DataBase::getInstance()->db_request(QString("select * from Users "
                                                            "where login = '%1' and password = '%2'").arg(login, password));
        if (userType == 1) {
            QVector<QMap<QString, QString>> teacher =
                    DataBase::getInstance()->db_request(QString("select * from Users "
                                                                "where login = '%1' and password = '%2'").arg(login, password));
            DataBase::getInstance()->db_request(QString("insert into UserGroups "
                                                        "values(%1, %2)").arg(teacher[0]["id"],current_user[0]["id"]));
        } else {
            QVector<QMap<QString, QString>> teacher =
                    DataBase::getInstance()->db_request(QString("select * from Users "
                                                                "where login = '%1'").arg(loginTeacher));
            DataBase::getInstance()->db_request(QString("insert into UserGroups "
                                                        "values(%1, %2)").arg(teacher[0]["id"], current_user[0]["id"]));
        }

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

bool DBRequests::user_logout(QString login, QString password)
{
    QVector<QMap<QString, QString>> answer = DataBase::getInstance()->db_request(
                QString("select * "
                        "from Users "
                        "where login = '%1' and password = '%2'").arg(login, password));

    if (answer.size() == 0) {
        qDebug() << "Пользователь не найден.";
        return false;
    } else {
        DataBase::getInstance()->db_request(
                 QString("update Users "
                         "set connection_id = null"
                         "where login = '%1' and password = '%2'").arg(login, password));
        return true;
    }
}

bool DBRequests::del_group(QString loginTeacher)
{
    QVector<QMap<QString, QString>> teacher =
            DataBase::getInstance()->db_request(QString("select * from Users "
                                                        "where login = '%1'").arg(loginTeacher));
    if (teacher.size() == 0) {
        qDebug() << "Группа не найдена.";
        return false;
    } else if (teacher.size() > 1) {
        qDebug() << "Ошибка. Несколько преподавателей с одинаковым логином.";
        return false;
    } else {
        DataBase::getInstance()->db_request(QString("delete from Users "
                                                    "where id = %1").arg(teacher[0]["id"]));
        return true;
    }
}

