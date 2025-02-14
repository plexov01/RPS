#include "client.h"
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this)) {
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

void Client::connectToServer(const QString &host, quint16 port) {
    socket->connectToHost(host, port);
}

void Client::sendData(const QByteArray &data) {
    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->write(data);
    }
}

void Client::onConnected() {
    qDebug() << "Connected to server!";
    sendData("Hello from client");
}

void Client::onDisconnected() {
    qDebug() << "Disconnected from server!";
}

void Client::onReadyRead() {
    QByteArray data = socket->readAll();
    qDebug() << "Received from server:" << data;
}
