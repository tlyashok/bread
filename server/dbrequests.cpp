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
        qDebug() << "Ошибка. Пользователей с данным логином и паролем больше одного." << '\n';
        return false;
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
    qDebug() << "Что-то пошло не так." << '\n';
    return false;
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
        qDebug() << "Ошибка. Пользователей с данным подключением больше одного." << '\n';
        return false;
    // Если такой пользователь один, то авторизация успешна.
    } else {
        return true;
    }
    qDebug() << "Что-то пошло не так." << '\n';
    return false;
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
        qDebug() << "Пользователь не найден." << '\n';
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
        qDebug() << "Группа не найдена." << '\n';
        return false;
    } else if (teacher.size() > 1) {
        qDebug() << "Ошибка. Несколько преподавателей с одинаковым логином." << '\n';
        return false;
    } else {
        DataBase::getInstance()->db_request(QString("delete from Users "
                                                    "where id = %1").arg(teacher[0]["id"]));
        return true;
    }
}

bool DBRequests::is_it_a_teacher(int userKey)
{
    QVector<QMap<QString, QString>> current_user =
            DataBase::getInstance()->db_request(
                QString("select user_type from Users "
                        "where connection_id = %1").arg(QString::number(userKey)));
    if (current_user.size() == 0) {
        qDebug() << "Данный пользователь не найден." << '\n';
        return false;
    } else if (current_user[0]["user_type"] == "0") {
        return false;
    } else {
        return true;
    }
}

QStringList DBRequests::get_students_list(int userKey)
{
   QVector<QMap<QString, QString>> studentList =
           DataBase::getInstance()->db_request(
               QString("select login from "
                       "Users as s1 "
                       "left join "
                       "UserGroups as s2 "
                       "on s1.id = s2.user_id "
                       "where s2.id = "
                       "(select id from Users where connection_id = %1)").arg(QString::number(userKey)));
   QStringList answer;
   for (int i = 0; i < studentList.size();i++) {
       answer.push_back(studentList[i]["login"]);
   }
   return answer;
}

QString DBRequests::get_statistics(int userKey, QString studentLogin, int taskNumber)
{
    QVector<QMap<QString, QString>> checkAccess =
            DataBase::getInstance()->db_request(
                QString("select connection_id from Users "
                        "where id = "
                        "(select s2.id from "
                        "Users as s1 "
                        "left join "
                        "UserGroups as s2 "
                        "on s1.id = s2.user_id "
                        "where login = '%1') limit 1").arg(studentLogin));
    if (checkAccess.size()==0) {
        qDebug() << "Что-то пошло не так." << '\n';
        return "";
    } else if (checkAccess[0]["connection_id"] == QString::number(userKey)) {
        QVector<QMap<QString, QString>> studentTasks =
                DataBase::getInstance()->db_request(
                    QString("select s1.task_id, s1.is_correct from "
                            "Tasks as s1 "
                            "left join "
                            "Users as s2 "
                            "on s1.user_id = s2.id "
                            "where s2.login = '%1' and "
                            "s1.task_number = %2").arg(studentLogin, QString::number(taskNumber)));
        int correctAnswers = 0;
        int wrongAnswers = 0;
        QStringList wrongAnswerTasks;
        for (int i = 0; i < studentTasks.size(); i++) {
            if (studentTasks[i]["is_correct"] == "1") {
                correctAnswers++;
            } else {
                wrongAnswers++;
            }
        }
        for (int i = 0; i < studentTasks.size(); i++) {
            if (studentTasks[i]["is_correct"] == "0") {
                wrongAnswerTasks.push_back(studentTasks[i]["task_id"]);
            }
        }
        QString answer;
        answer = QString::number(correctAnswers) + "$" + QString::number(wrongAnswers);
        for (int i = 0; i < wrongAnswerTasks.size(); i++) {
            answer += "$";
            answer += wrongAnswerTasks[i];
        }
        return answer;
    } else {
        qDebug() << "Доступ запрещён." << '\n';
        return "";
    }



}

