#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include "mytcpserver.h"
#include "database.h"
#include "dbrequests.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer *b = MyTcpServer::getInstance();

    DataBase::getInstance()->db_request("insert into Users values(1, 1, 'aaa', 'bbb', NULL)");

    qDebug() << DBRequests::getInstance()->auth("aaa", "bbb", 1);

    qDebug() << DBRequests::getInstance()->check_auth(1);


    return a.exec();
}
