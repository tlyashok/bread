#ifndef DATABASE_H
#define DATABASE_H

#include <QString>

#include "singleton.h"

class DataBase : public Singleton<DataBase>
{
    friend class Singleton<DataBase>;
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
