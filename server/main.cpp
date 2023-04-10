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


    return a.exec();
}
