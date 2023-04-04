#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include "mytcpserver.h"
#include "database.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer *b = MyTcpServer::getInstance();



    DataBase::getInstance()->db_request("insert into Users values(1, 1, 'aaa', 'bbb', 123)");

    DataBase::getInstance()->db_request("insert into Users values(2, 1, 'aaa', 'bbb', 123)");


    DataBase::getInstance()->printTable(DataBase::getInstance()->db_request("select * from Users"));


    return a.exec();
}
