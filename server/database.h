#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

#include "singleton.h"

class DataBase : public Singleton<DataBase>
{
    friend class Singleton<DataBase>;
private:
    ///
    /// \brief DataBase Конструктор, задаются имя БД и язык
    ///
    DataBase();
    DataBase(const DataBase& ) = delete;
    DataBase& operator = (DataBase &) = delete;
    ///
    /// \brief ~DataBase Деструктор, закрытие БД
    ///
    ~DataBase();
    QSqlDatabase db;
    ///
    /// \brief create_db Создание таблиц Users и Tasks
    ///
    bool db_created();
    void create_db();

public:
    ///
    /// \brief db_request Отправляет запрос в базу данных
    /// \param request
    /// \return Возвращает ответ в формате вектора записей запроса,
    /// \return где каждая запись представлена в виде QMap <название стобца : значение столбца>
    ///
    QVector<QMap<QString, QString>> db_request(QString request);
    ///
    /// \brief db_clear Очищает базу данных
    ///
    void db_clear();
    ///
    /// \brief printTable Возвращает в консоль таблицу, полученную через db_request
    /// \param table
    ///
    void printTable(const QVector<QMap<QString, QString>>& table);
};

#endif // DATABASE_H
