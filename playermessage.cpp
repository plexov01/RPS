#include "playerMessage.h"

PlayerMessage::PlayerMessage(const quint16 port, const QString message): port(port), message(message) {}

quint16 PlayerMessage::getPort() const {
    return port;
}

QString PlayerMessage::getMessage() const {
    return message;
}

void PlayerMessage::setMessage(const QString newMessage) {
    message = newMessage;
}

// Реализация оператора сравнения
bool PlayerMessage::operator==(const PlayerMessage& other) const {
    return this->port == other.port;
}
