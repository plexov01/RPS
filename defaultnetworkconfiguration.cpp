#include "defaultnetworkconfiguration.h"
#include <QObject>
#include <QNetworkInterface>

// Получить Ip по умолчанию(Ip адресс в локальной сети)
QString DefaultNetworkConfiguration::getDefaultIp() const {
    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    for (const QHostAddress &address : std::as_const(addresses)) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback()) {
            return address.toString();
        }
    }
    return "127.0.0.1"; // Если ничего не нашли, возвращаем localhost
}

//Получить Port по умолчанию
int DefaultNetworkConfiguration::getDefaultPort() const {

    return defaultPort;
}
