#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QString>
#include <QVector>
#include <QSet>
#include <QDebug>

#include <cstdlib>
#include <ctime>

#include "singleton.h"

class TaskManager : public Singleton<TaskManager>
{
    friend class Singleton<TaskManager>;
public:
    ///
    /// \brief create_task Генерирует одно из пяти заданий
    /// \param task_number Номер задания 1-5
    /// \return Возвращает условие задания и его уникальный ключ
    ///
    QString create_task(int taskNumber);
    ///
    /// \brief check_task Проверяет задание
    /// \param taskNumber Номер задания 1-5
    /// \param taskKey Уникальный ключ задания
    /// \param answer Ответ пользователя
    /// \return Верное или неверное выполнение задания true/false
    ///
    bool check_task(int taskNumber, int taskKey, QString answer);
private:
    ///
    /// \brief check_task1 Проверяет первое задание
    /// \param taskKey Уникальный ключ задания
    /// \param answer Ответ пользователя
    /// \return Верное или неверное выполнение задания true/false
    ///
    bool check_task1(int taskKey, QString answer);
    ///
    /// \brief check_task2
    /// \param taskKey
    /// \param answer
    /// \return
    ///
    bool check_task2(int taskKey, QString answer);
    ///
    /// \brief check_task3
    /// \param taskKey
    /// \param answer
    /// \return
    ///
    bool check_task3(int taskKey, QString answer);
    ///
    /// \brief check_task4
    /// \param taskKey
    /// \param answer
    /// \return
    ///
    bool check_task4(int taskKey, QString answer);
    ///
    /// \brief check_task5
    /// \param taskKey
    /// \param answer
    /// \return
    ///
    bool check_task5(int taskKey, QString answer);
    ///
    /// \brief create_task1 Генерирует задание по уникальному ключу
    /// \param taskKey Ключ задания
    /// \return Возвращает условие задания и ключ (если использовалось значение по умолчанию, то новый ключ)
    ///
    QString create_task1(int taskKey = 0);
    ///
    /// \brief create_task2
    /// \param taskKey
    /// \return
    ///
    QString create_task2(int taskKey = 0);
    ///
    /// \brief create_task3
    /// \param taskKey
    /// \return
    ///
    QString create_task3(int taskKey = 0);
    ///
    /// \brief create_task4
    /// \param taskKey
    /// \return
    ///
    QString create_task4(int taskKey = 0);
    ///
    /// \brief create_task5
    /// \param taskKey
    /// \return
    ///
    QString create_task5(int taskKey = 0);
};

#endif // TASKMANAGER_H
