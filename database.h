#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>

#include "singleton.h"

class DataBase : public Singleton<DataBase>
{
    friend class Singleton<DataBase>;
private:
    DataBase();
    DataBase(const DataBase& ) = delete;
    DataBase& operator = (DataBase &) = delete;
    ~DataBase();
    QSqlDatabase db;
    bool db_created();
    void create_db();

public:
    ///
    /// \brief db_request Отправляет запрос в базу данных
    /// \param request
    /// \return Возвращает ответ
    ///
    QString db_request(QString request);
    ///
    /// \brief db_clear Очищает базу данных
    ///
    void db_clear();
};

#endif // DATABASE_H
