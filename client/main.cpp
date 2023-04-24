#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client w(nullptr);

    //SingletonClient::getInstance()->sendToServer("auth 123 start");
    //SingletonClient::getInstance()->sendToServer("reg 123 start asd");

    w.show();
    return a.exec();
}
