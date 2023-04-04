#include "dbrequests.h"


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
        if (answer[0]["connection"] != "NULL" and answer[0]["connection"] == QString::number(userKey)) {
            return true;
        } else if (answer[0]["connection"] != "NULL" and answer[0]["connection"] != QString::number(userKey)) {
            return false;
        } else if (answer[0]["connection"] == "NULL") {
            DataBase::getInstance()->db_request(
                            QString("UPDATE Users"
                                    "SET connection = %1"
                                    "WHERE login = '%2' and password = '%3'").arg(QString::number(userKey), login, password));
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
                        "where connection = %1").arg(userKey));
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

/*
bool DBRequests::reg(QString login, QString password, int UserKey)
{
    QVector<QMap<QString, QString>> answer = DataBase::getInstance()->db_request(
                QString("select * from Users where login = '%1'").arg(login));

}
*/
