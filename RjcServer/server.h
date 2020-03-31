#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QTime>
#include <QTimer>

#define SERVER_IP   "localhost"
#define SERVER_PORT 4040

class server : public QObject
{
    Q_OBJECT
public:
    explicit server(QObject *parent = nullptr);

    bool startServer();
    bool closeServer();

    QString server_ip;
    quint16 server_port;
    QList<QString> clientsNames;
signals:
    void signalNewClient(QString);
    void signalNewChatMsg(QString,QString);
private:
    QMap<QTimer*,QTcpSocket*> forAuth;
    QMap<QTcpSocket*,QString> clients;
    QTcpServer *tcpServer;
    quint16 nextBlockSize;

private slots:
    void slotNewConnection();
    void slotAuthFailed();
    void slotReadClient();
};

#endif // SERVER_H
