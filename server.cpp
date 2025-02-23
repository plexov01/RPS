#include "server.h"
#include <QDebug>


Server::Server(QObject *parent) : QObject(parent) {
    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection, this, &Server::onNewConnection);
}

bool Server::startServer(quint16 port) {

    if (server->listen(QHostAddress::Any, port)) {

        QString currentIp = defaultNetworkConfiguration.getDefaultIp();
        quint16 currentPort = server->serverPort();

        emit outputServerIdText(ipPortCoder.encodeIPPort(currentIp, currentPort));
        emit outputDebugText("Server started! Use Server ID to connect!");

        return true;
    } else {
        emit outputDebugText("Failed to start server!");
        return false;
    }
}

void Server::onNewConnection() {
    QTcpSocket *clientSocket = server->nextPendingConnection();

    if(clients.size() < 2){
        clients.append(clientSocket);
    } else{
        return;
    }

    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::onClientDisconnected);

    qDebug() << "New client connected!";

    if(gameIsReady()){
        sendMessageToAllClients("Game started!\n Do your choice! \n");
    }else{
        sendMessageToAllClients("There are not enough players to play! \n  Wait ...");
    }


}

void Server::onReadyRead() {
    QTcpSocket *thisSocket = qobject_cast<QTcpSocket *>(sender());
    if (!thisSocket) return;
    QTcpSocket *anotherSocket;

    QString serverResponseToThisSocket;
    QString serverResponseToAnotherSocket;


    QByteArray message = thisSocket->readAll();
    QString messageString = QString::fromUtf8(message);

    quint16 socketPort = thisSocket->peerPort();

    if(!gameIsReady()){
        serverResponseToThisSocket = "Please, wait for another player!";
    }else{
        anotherSocket = getFirstAnotherSocket(thisSocket);

        serverResponseToThisSocket = "Selected: "+ message + "\n\nWait for choice another player!";
        serverResponseToAnotherSocket = "Another player already made choice!\n Do your choice!";

    }


    addPlayerMessage(socketPort, messageString);

    if(playerMessages.size() == clients.size() && gameIsReady()){
        Game::Choice thisSocketChoice = Game::stringToChoice(message);
        Game::Choice anotherSocketChoice = Game::stringToChoice(getMessageBySocket(anotherSocket));
        Game::Choice winnerChoice = Game::getWinner(thisSocketChoice, anotherSocketChoice);

        qDebug() <<thisSocketChoice<<anotherSocketChoice<<winnerChoice;

        if(winnerChoice == Game::Choice::Invalid){
            serverResponseToThisSocket = "Draw! ";
            serverResponseToAnotherSocket = "Draw!";
            playerMessages.clear();
        }else if(winnerChoice == thisSocketChoice){
            serverResponseToThisSocket = "Win!\n Your choice: " + getMessageBySocket(thisSocket) +
                                         "\nChoice another player: " + getMessageBySocket(anotherSocket);
            serverResponseToAnotherSocket = "Defeat!\n Your choice: " + getMessageBySocket(anotherSocket) +
                                            "\nChoice another player: " + getMessageBySocket(thisSocket);
            playerMessages.clear();

        }else{
            serverResponseToThisSocket = "Defeat!\n Your choice: " + getMessageBySocket(thisSocket) +
                                         "\nChoice another player: " + getMessageBySocket(anotherSocket);
            serverResponseToAnotherSocket = "Win!\n Your choice: " + getMessageBySocket(anotherSocket) +
                                            "\nChoice another player: " + getMessageBySocket(thisSocket);
            playerMessages.clear();

        }
    }


    sendMessageToClient(thisSocket, serverResponseToThisSocket);

    if(anotherSocket){
        sendMessageToClient(anotherSocket, serverResponseToAnotherSocket);
    }


}


void Server::addPlayerMessage(const quint16 &port, const QString &messageText) {
    // Ищем существующее сообщение этого клиента
    bool messageFound = false;
    for (PlayerMessage playerMessage : playerMessages) {
        if (playerMessage.getPort() == port) {
            // Если сообщение найдено, обновляем его
            playerMessage.setMessage(messageText);
            messageFound = true;
            qDebug() << "Message updated for client:" << port<<playerMessage.getMessage() ;

        }

    }

    // Если сообщение не найдено, создаем новое сообщение и добавляем в список
    if (!messageFound) {
        // PlayerMessage newPlayerMessage(port, messageText);
        playerMessages.append(PlayerMessage(port, messageText));
        qDebug() << "New message added for client:" << port;
    }
}


void Server::onClientDisconnected() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket) return;

    clients.removeAll(clientSocket);
    clientSocket->deleteLater();
    qDebug() << "Client disconnected!";

    // Ищем сообщение этого клиента в списке playerMessages
    for (PlayerMessage playerMessage : playerMessages) {
        if (playerMessage.getPort() == clientSocket->peerPort()) {
            // Если нашли сообщение от этого клиента, удаляем его из списка
            playerMessages.removeOne(playerMessage);
            qDebug() << "Removed message for disconnected client.";
            break;  // Прерываем цикл, так как мы нашли и удалили нужное сообщение
        }
    }


    sendMessageToAllClients("Another player leaved game!\n There are not enough players to play! \n  Wait ...");
}

QTcpSocket* Server::getFirstAnotherSocket(QTcpSocket* excludedClient) {
    // Проходим по всем клиентам
    for (QTcpSocket* client : std::as_const(clients)) {
        // Проверяем, не является ли этот клиент исключенным
        if (client != excludedClient) {
            return client;  // Возвращаем первого подходящего клиента
        }
    }
    return nullptr;  // Если все клиенты исключены, возвращаем nullptr
}

QString Server::getMessageBySocket(QTcpSocket* socket) {
    for (PlayerMessage playerMessage : playerMessages) {
        if (playerMessage.getPort() == socket->peerPort()) {
            return playerMessage.getMessage();
        }
    }
    return ""; // Если не нашли, возвращаем пустую строку
}

bool Server::gameIsReady(){
    return clients.size() == 2;
}

// Отправляем сообщение всем клиентам
void Server::sendMessageToAllClients(const QString& messageText){
    Q_FOREACH (QTcpSocket* client ,clients) {
        if (client->state() == QAbstractSocket::ConnectedState) {
            client->write(messageText.toUtf8());
        }
    }

}
//Отправляем сообщение клиенту
void Server::sendMessageToClient(QTcpSocket *socket, const QString& messageText){
    if (socket && socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(messageText.toUtf8());
    }
}
