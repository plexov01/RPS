#include "server.h"
#include <QDebug>

Server::Server(QObject *parent) : QObject(parent), tcpServer(new QTcpServer(this))
{
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);
}

Server::~Server() {
    qDeleteAll(clients);
}

void Server::startServer(quint16 port) {
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        qCritical() << "Failed to start server:" << tcpServer->errorString();
        return;
    }
    qDebug() << "Server started on port" << port;
}

void Server::newConnection() {
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readData);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::clientDisconnected);

    clients.append(clientSocket);
    qDebug() << "New client connected:" << clientSocket->peerAddress().toString();

    // Информируем сервер, сколько клиентов подключено
    qDebug() << "Number of clients:" << clients.size();
}

void Server::readData() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    QByteArray data = clientSocket->readAll();
    qDebug() << "Received from client:" << data;
}

void Server::clientDisconnected() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    clients.removeAll(clientSocket);
    clientSocket->deleteLater();

    qDebug() << "Client disconnected. Number of clients:" << clients.size();
}
