#pragma once
#include <QString>
#include <QByteArray>
#include <QByteArray>

#include "singleton.h"
#include "dbrequests.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class Functions : public Singleton<Functions>
{
    friend class Singleton<Functions>;
private:
    ///
    /// \brief wrong_user_message Вызывается при неверных сообщениях от пользователя
    /// \return Ответ для отправки клиенту
    ///
    QByteArray wrong_user_message();
    ///
    /// \brief auth Авторизует подключение пользователя
    /// \param login
    /// \param password
    /// \param userKey
    /// \return Возвращает ответ клиенту, об авторизации
    ///
    QByteArray auth(QString login, QString password, int userKey);
    ///
    /// \brief reg Регистрирует пользователя (добавляет информацию о нём в базу данных)
    /// \param login
    /// \param password
    /// \param userType
    /// \param loginTeacher
    /// \return Возвращает ответ клиенту, о регистрации
    ///
    QByteArray reg(QString login, QString password, int userType, QString loginTeacher);
    ///
    /// \brief check_auth Проверяет, авторизировано ли данное устройство
    /// \param userKey
    /// \return Возвращает ответ клиенту
    ///
    QByteArray check_auth(int userKey);
    ///
    /// \brief task_is_done Отдаёт задание на проверку и возвращает ответ
    /// \param userKey
    /// \param taskNumber
    /// \param taskKey
    /// \param isCorrect
    /// \return Вовзращает ответ клиенту
    ///
    QByteArray task_is_done(int userKey, int taskNumber, int taskKey, QString answer);
    ///
    /// \brief reset_connections Сбрасывает подключения для зарегистрированных пользователей
    /// \return
    ///
    QByteArray reset_connections();
    ///
    /// \brief get_task Генерирует задание, передаёт клиенту условие задания и его уникальный номер
    /// \param int task_number Номер задания 1-5
    /// \return QByteArray Ответ для отправки клиенту [taskKey] [taskText]
    ///
    QByteArray get_task(int taskNumber);
    ///
    /// \brief check_task Проверяет задание, генерируя условие задания по номеру задания и его уникальному ключу,
    /// \brief сопоставляет ответ, полученный сервером с ответом, данным клиентом.
    /// \param taskNumber Номер задания 1-5
    /// \param taskKey Уникальный ключ задания, используется как сид для функции random
    /// \param answer Ответ клиента
    /// \return true - задание решено верно, false - неверно
    ///
    bool check_task(int taskNumber, int taskKey, QString answer);
    ///
    /// \brief user_logout Удаляет подключения для пользователя с данными логином и паролем.
    /// \param login
    /// \param password
    /// \return 1 - успешно, 0 - пользователь не найден
    ///
    QByteArray user_logout(QString login, QString password);
public:
    ///
    /// \brief parse Принимает сообщение пользователя и возвращает ответ подходящей функции
    /// \param QString user_message "command arg1 arg2 arg3 ..."
    /// \return Возвращает, верно ли выполнено задание
    ///
    QByteArray parse(QString userMessage);
    ///
    /// \brief del_group Удаляет группу заданного преподавателя.
    /// \param loginTeacher
    /// \return 1 - успешно, 0 - группа не найдена
    ///
    QByteArray del_group(QString loginTeacher);
    ///
    /// \brief is_it_a_teacher Проверка на аккаунт преподавателя
    /// \return Возвращает true, если запрос идёт от преподавателя
    ///
    QByteArray is_it_a_teacher(int userKey);
    ///
    /// \brief get_students_list Если запрос идёт от преподавателя, вернуть список логинов его студентов
    /// \param userKey Дескриптор подключения
    /// \return
    ///
    QByteArray get_students_list(int userKey);
    ///
    /// \brief get_statistics Если запрос идёт от преподавателя группы в которой состоит ученик,
    /// возвращает статистику по заданию ученика
    /// \param studentLogin
    /// \param taskNumber
    /// \param userKey
    /// \return [количество верных попыток]$[количество неверных попыток]$[номера вариантов последних двадцати неверных попыток с разделителем $]
    ///
    QByteArray get_statistics(int userKey, QString studentLogin, int taskNumber);
};


#endif
// FUNCTIONS_H
