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

    qDebug() << TaskManager::getInstance()->create_task(1);

    qDebug() << TaskManager::getInstance()->check_task(1, 1, "12 13");
    return a.exec();
}
