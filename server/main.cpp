#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include "mytcpserver.h"
#include "database.h"
#include "dbrequests.h"
#include "taskmanager.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer *b = MyTcpServer::getInstance();

    qDebug() << TaskManager::getInstance()->create_task(4);

    qDebug() << TaskManager::getInstance()->check_task(4, 1097571711, "12,23,34,45,56,67,78,81");
    return a.exec();
}
