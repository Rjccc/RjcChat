#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#define SERVER_IP   "localhost"
#define SERVER_PORT 4040

class server : public QObject
{
    Q_OBJECT
public:
    explicit server(QObject *parent = nullptr);

signals:

private:
    QTcpServer *tcpServer;

    bool startServer();
};

#endif // SERVER_H
