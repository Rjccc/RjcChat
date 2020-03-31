#include "server.h"

server::server(QObject *parent) : QObject(parent)
{
    server_ip = "";
    server_port = 0;
    nextBlockSize = 0;

    tcpServer = new QTcpServer;

    connect(tcpServer,SIGNAL(newConnection()),SLOT(slotNewConnection()));
}

bool server::startServer(){
    tcpServer->listen(QHostAddress::LocalHost,SERVER_PORT);
    if(tcpServer->isListening()){
        server_ip = tcpServer->serverAddress().toString();
        server_port = tcpServer->serverPort();
        return true;
    }   else {
        return false;
    }
}

bool server::closeServer(){
    tcpServer->close();
    if(tcpServer->isListening()){
        return false;
    }
    else{
        server_ip = "";
        server_port = 0;
        return true;
    }
}

void server::slotNewConnection(){
    QTcpSocket *clientSock = tcpServer->nextPendingConnection();
    qDebug() << "TYEST";
    connect(clientSock,SIGNAL(readyRead()),SLOT(slotReadClient()));
    QTimer *timerForAuth = new QTimer;
    timerForAuth->setInterval(5000);//5sec. change later
    forAuth[timerForAuth] = clientSock;
    connect(timerForAuth,SIGNAL(timeout()),SLOT(slotAuthFailed()));
    timerForAuth->start();
}

void server::slotAuthFailed(){
    QTimer *timer = (QTimer*)sender();
    if(clients[forAuth[timer]].isEmpty())
        forAuth[timer]->disconnectFromHost();
    delete timer;
}

void server::slotReadClient(){
    QTcpSocket* clientSock = (QTcpSocket*)sender();
    QDataStream in(clientSock);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;) {
            if (!nextBlockSize) {
                if (clientSock->bytesAvailable() < sizeof(quint16)) {
                    break;
                }
                in >> nextBlockSize;
            }

            if (clientSock->bytesAvailable() < nextBlockSize) {
                break;
            }
            int typeOfMsg;
            in >> typeOfMsg;
            if(typeOfMsg == 1){//Auth
                QString nameOfClient;
                in >> nameOfClient;
                if(clientsNames.contains(nameOfClient)){//i can do it better
                     nameOfClient.append("[1]");
                }
                clients[clientSock] = nameOfClient;
                emit signalNewClient(nameOfClient);
            }
            if(typeOfMsg == 2){//Chat msg
                QString nameOfClient;
                QString msg;
                in >> nameOfClient >> msg;
                emit signalNewChatMsg(nameOfClient,msg);
            }

            nextBlockSize = 0;
        }
}
