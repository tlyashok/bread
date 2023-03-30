#include "database.h"

bool DataBase::db_created()
{
    return this->db.tables() == QStringList{"Tasks", "Users"};
}

void DataBase::create_db()
{
    // типы пользователей: 0 - студент, 1 - преподаватель

    QSqlQuery query(this->db);
    query.exec("CREATE TABLE Users("
           "id INTEGER PRIMARY KEY, "
           "user_type INT8 NOT NULL, "
           "login VARCHAR(64) NOT NULL, "
           "password VARCHAR(64) NOT NULL, "
           "email VARCHAR(64) NOT NULL UNIQUE, "
           "connection INTEGER DEFAULT NULL "
           ")");
    query.exec("CREATE TABLE Tasks("
          "id INTEGER PRIMARY KEY, "
           "user_id INTEGER NOT NULL, "
           "task_id INTEGER NOT NULL, "
           "grade INT8 DEFAULT NULL"
           ")");
}

DataBase::DataBase()
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName("database.sqlite");
    if (!(this->db.open()))
        qDebug()<<db.lastError().text();
    if (!this->db_created())
        this->create_db();
}

DataBase::~DataBase()
{
    db.close();
}

QString DataBase::db_request(QString request)
{
    QSqlQuery query(this->db);
    query.exec(request);
    QSqlRecord record = query.record();
    QString result;
    while(query.next()) {
        for (int i = 0; i < record.count(); i++)
        {
            result.append(query.value(i));
            if (i != record.count()-1)
                result.append(", ");
        }
        if (!query.last())
            result.append("\n");
    }
    return result;
}

void DataBase::db_clear()
{
    QSqlQuery query(this->db);
    query.exec("DELETE FROM TABLE Users");
    query.exec("DELETE FROM TABLE Tasks");
}
