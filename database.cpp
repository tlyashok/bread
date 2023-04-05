#include "database.h"

bool DataBase::db_created()
{
    return this->db.tables() == QStringList{"Tasks", "Users"};
}

void DataBase::create_db()
{
    QSqlQuery query(this->db);
    /* Создаёт две таблицы:
     *
     * Users
     * --------------------------------------------------
     * id | user_type | login | password | connection_id
     * --------------------------------------------------
     *    |           |       |          |       |
     *    |           |       |          |       |
     *    |           |       |          |       |
     * --------------------------------------------------
     *
     * user_type: 0 - студент, 1 - преподаватель
     *
     *
    * Tasks
    * ----------------------------------------------------
    * id | user_id   | task_id | task_number | is_correct
    * ----------------------------------------------------
    *    |           |         |             |
    *    |           |         |             |
    *    |           |         |             |
    * ----------------------------------------------------
     *
     * Tasks.user_id <-> Users.id
     */
    query.exec("CREATE TABLE Users("
           "id INTEGER PRIMARY KEY, "
           "user_type INT8 NOT NULL, "
           "login VARCHAR(64) NOT NULL, "
           "password VARCHAR(64) NOT NULL, "
           "connection_id INTEGER DEFAULT NULL "
           ")");
    query.exec("CREATE TABLE Tasks("
          "id INTEGER PRIMARY KEY, "
           "user_id INTEGER NOT NULL, "
           "task_id INTEGER NOT NULL, "
           "task_number INTEGER NOT NULL, "
           "is_correct BOOLEAN DEFAULT NULL"
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

QVector<QMap<QString, QString>> DataBase::db_request(QString request)
{
    QSqlQuery query(this->db);
    query.exec(request);
    QSqlRecord record = query.record();
    QVector<QString> columns;
    for (int i = 0; i < record.count(); i++) {
        QString columnName = record.fieldName(i);
        columns.append(columnName);
    }
    QVector<QMap<QString, QString>> result;
    if (query.lastError().isValid()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
    } else {
        while (query.next()) {
            QMap<QString, QString> row;
            for (int i = 0; i < columns.count(); i++) {
                QString columnName = query.record().fieldName(i);
                QString value = query.value(i).toString();
                row.insert(columnName, value);
            }
            result.append(row);
        }
    }
    return result;
}

void DataBase::printTable(const QList<QMap<QString, QString>>& table)
{
    const int columnWidth = 15;

    // выводим горизонтальную линию таблицы
    qDebug().noquote() << QString("-").repeated(columnWidth * table.first().size() + table.first().size() + 1);

    // выводим заголовки столбцов
    QString header;
    for (auto& column : table.first().keys()) {
        header += QString("| %1 ").arg(column.leftJustified(columnWidth, ' '), Qt::AlignHCenter);
    }
    qDebug().noquote() << header << "|";

    // выводим горизонтальную линию таблицы
    qDebug().noquote() << QString("-").repeated(columnWidth * table.first().size() + table.first().size() + 1);

    // выводим строки таблицы
    for (auto& row : table) {
        QString rowStr;
        for (auto& value : row.values()) {
            rowStr += QString("| %1 ").arg(value.leftJustified(columnWidth, ' '), Qt::AlignHCenter);
        }
        qDebug().noquote() << rowStr << "|";
    }

    // выводим горизонтальную линию таблицы
    qDebug().noquote() << QString("-").repeated(columnWidth * table.first().size() + table.first().size() + 1);
}

void DataBase::db_clear()
{
    QSqlQuery query(this->db);
    query.exec("DELETE FROM TABLE Users");
    query.exec("DELETE FROM TABLE Tasks");
}
