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

    // Значения для проверки работоспособности
    DBRequests::getInstance()->reg("vasya", "123", 0);
    DBRequests::getInstance()->auth("vasya", "123", 123);
    DBRequests::getInstance()->task_is_done(123,1,123,true);

    return a.exec();
}
