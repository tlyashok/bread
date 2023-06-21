#include <QString>
#include <QStringList>
#include <QByteArray>
#include "functions.h"

QByteArray Functions::wrong_user_message() {
    return QByteArray(QString("invalid_arguments").toUtf8());
}

QByteArray Functions::auth(QString login, QString password, int userKey)
{
    bool authSuccess = DBRequests::getInstance()->auth(login, password, userKey);
    return QByteArray((QString("auth$")+QString::number(authSuccess)).toUtf8());
}

QByteArray Functions::reg(QString login, QString password, int userType, QString loginTeacher)
{
    bool regSuccess = DBRequests::getInstance()->reg(login, password, userType, loginTeacher);
    return QByteArray((QString("reg$")+QString::number(regSuccess)).toUtf8());
}

QByteArray Functions::check_auth(int userKey)
{
    bool checkAuthSucces = DBRequests::getInstance()->check_auth(userKey);
    return QByteArray((QString("check_auth$")+QString::number(checkAuthSucces)).toUtf8());
}

QByteArray Functions::task_is_done(int userKey, int taskNumber, int taskKey, QString answer)
{
    bool isAnswerCorrect = check_task(taskNumber, taskKey, answer);
    DBRequests::getInstance()->task_is_done(userKey, taskNumber, taskKey, isAnswerCorrect,answer);
    return QByteArray((QString("task_is_done$")+QString::number(isAnswerCorrect)).toUtf8());
}

QByteArray Functions::reset_connections()
{
    DBRequests::getInstance()->reset_connections();
    return QByteArray(QString(QString::number(true)).toUtf8());
}

QByteArray Functions::user_logout(QString login, QString password)
{
    bool checkLogoutSuccess = DBRequests::getInstance()->user_logout(login, password);
    return QByteArray(QString(QString::number(checkLogoutSuccess)).toUtf8());
}

QByteArray Functions::del_group(QString loginTeacher)
{
    bool checkDelGroup = DBRequests::getInstance()->del_group(loginTeacher);
    return QByteArray(QString(QString::number(checkDelGroup)).toUtf8());
}

QByteArray Functions::is_it_a_teacher(int userKey)
{
    bool checkTeacher = DBRequests::getInstance()->is_it_a_teacher(userKey);
    return QByteArray(QString(QString::number(checkTeacher)).toUtf8());
}

QByteArray Functions::get_students_list(int userKey)
{
    bool checkTeacher = DBRequests::getInstance()->is_it_a_teacher(userKey);
    QString answer;
    if (checkTeacher == false) {
        qDebug() << "Данный пользователь не является преподавателем." << '\n';
        return QByteArray(answer.toUtf8());
    } else {
        QStringList studentList = DBRequests::getInstance()->get_students_list(userKey);
        for (int i = 0; i < studentList.size(); i++) {
            answer += studentList[i];
            if (i != studentList.size()-1) {
                answer += "$";
            }
        }
        return QByteArray(answer.toUtf8());
    }
}

QByteArray Functions::get_task(int taskNumber)
{
    return QByteArray(TaskManager::getInstance()->create_task(taskNumber).toUtf8());
}

bool Functions::check_task(int taskNumber, int taskKey, QString answer)
{
    return TaskManager::getInstance()->check_task(taskNumber, taskKey, answer);
}


QByteArray Functions::get_statistics(int userKey, QString studentLogin, int taskNumber)
{
    return QByteArray(DBRequests::getInstance()->get_statistics(userKey,studentLogin,taskNumber).toUtf8());
}

/*
 * Формат команды
 *
 * [Дескриптор подключения] [Команда] [arg1] [arg2]...
 *
 *
 */

QByteArray Functions::parse(QString userMessage) {
    QStringList data = userMessage.split(' ');
    int descriptor = data[0].toInt();
    for (int i = 0; i < data.size(); i++) {
        qDebug() << data[i] << " ";
    }
    if (data.size() < 2) {
        qDebug() << "Неверная команда от сервера.";
        return QByteArray(QString("invalid_command").toUtf8());
    }
    qDebug() << '\n';
    if (data[1] == "reg") {
        return reg(data[2], data[3], data[4].toInt(), data[5]);
    } else if (data[1] == "auth") {
        return auth(data[2], data[3], descriptor);
    } else if (data[1] ==  "check_auth") {
        return check_auth(descriptor);
    } else if (data[1] == "reset_connections") {
        return reset_connections();
    } else if (data[1] ==  "task") {
        return task_is_done(descriptor, data[2].toInt(), data[3].toInt(), data[4]);
    } else if (data[1] ==  "user_logout") {
        return user_logout(data[2], data[3]);
    } else if (data[1] == "get_task") {
        return get_task(data[2].toInt());
    } else if (data[1] == "del_group") {
        return del_group(data[2]);
    } else if (data[1] == "is_it_a_teacher") {
        return is_it_a_teacher(descriptor);
    } else if (data[1] == "get_students_list") {
        return get_students_list(descriptor);
    } else if (data[1] == "get_statistics") {
        return get_statistics(descriptor,data[2],data[3].toInt());
    } else {
        return wrong_user_message();
    }
}
