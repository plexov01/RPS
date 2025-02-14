#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

    void startServer(quint16 port);

private slots:
    void newConnection();
    void readData();
    void clientDisconnected();

private:
    QTcpServer *tcpServer;
    QList<QTcpSocket*> clients;  // Список подключенных клиентов
};

#endif // SERVER_H
