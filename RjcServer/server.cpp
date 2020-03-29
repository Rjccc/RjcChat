#include "server.h"

server::server(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer;
}

bool server::startServer(){

}
