# include "client.h"

SingletonClient::~SingletonClient()
{
    socket->close();
}

