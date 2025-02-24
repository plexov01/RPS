#include "client.h"
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

//Пытаемся подключиться к серверу
bool Client::tryConnectToServer(QHostAddress &hostAdress, quint16 port) {
    socket->connectToHost(hostAdress, port);

    if (socket->waitForConnected(1000)) {  // Ждем 1 секунду
        return true;
    } else {
        emit outputDebugText("Connection error: " + socket->errorString());
        return false;
    }
}

void Client::sendMessage(const QString &message) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(message.toUtf8());
    }
}

void Client::onReadyRead() {
    QByteArray data = socket->readAll();
    if(data != "Server is full!"){
        emit outputMainText(data);
        emit canSwitchToGameView();
        emit outputDebugText("Connected to server!");
    }else{
        emit outputDebugText("Error: Server already full!");
    }

}
