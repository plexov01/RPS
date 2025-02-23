#ifndef SERVER_H
#define SERVER_H

#include "IPPortCoder.h"
#include "defaultnetworkconfiguration.h"
#include "game.h"
#include "playerMessage.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

class Server : public QObject {
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);

    bool startServer(quint16 port);

signals:
    void outputDebugText(QString debugText);
    void outputServerIdText(QString debugText);


private slots:
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();

private:

    Game game;

    DefaultNetworkConfiguration  defaultNetworkConfiguration;
    IPPortCoder ipPortCoder;

    QTcpServer *server;
    QList<QTcpSocket *> clients;
    QList<PlayerMessage> playerMessages;

    QTcpSocket* getFirstAnotherSocket(QTcpSocket* excludedClient);
    QString getMessageBySocket(QTcpSocket* socket);

    bool gameIsReady();
    void addPlayerMessage(const quint16 &port, const QString &messageText);
    void sendMessageToAllClients(const QString& messageText);
    void sendMessageToClient(QTcpSocket *socket, const QString& messageText);
};

#endif // SERVER_H
