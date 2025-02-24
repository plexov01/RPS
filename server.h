#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "IPPortCoder.h"
#include "defaultnetworkconfiguration.h"
#include "game.h"
#include "playerMessage.h"

//Класс сервера
class Server : public QObject {
    Q_OBJECT
signals:
    void outputDebugText(QString debugText);
    void outputServerIdText(QString debugText);

public:
    explicit Server(QObject *parent = nullptr);

    bool startServer(quint16 port);


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

    void UpdatePlayerMessage(const quint16 &port, const QString &messageText);

    bool gameIsReady();

    QTcpSocket* getFirstAnotherSocket(QTcpSocket* excludedClient);
    QString getMessageBySocket(QTcpSocket* socket);

    void sendMessageToAllClients(const QString& messageText);
    void sendMessageToClient(QTcpSocket *socket, const QString& messageText);
};

#endif // SERVER_H
