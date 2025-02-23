#include "IPPortCoder.h"
#include <QStringList>

// Реализация encodeIPPort(Перевожу в ID из ip и port)
QString IPPortCoder::encodeIPPort(const QString ip, quint16 port) {
    QStringList ipParts = ip.split(".");
    QString encodedIP;
    for (const QString &part : std::as_const(ipParts)) {
        int num = part.toInt();
        encodedIP += QString::number(num, 36).toUpper().rightJustified(2, '0');
    }
    QString encodedPort = QString::number(port, 36).toUpper().rightJustified(4, '0');
    return encodedIP + encodedPort;
}

// Реализация decodeIPPort
bool IPPortCoder::decodeIPPort(const QString &encoded, QString &ip, quint16 &port) {

    if(encoded.length() < 1){
        return false;
    }

    QString encodedIP;
    QString encodedPort;
    bool ok;

    ///Если введённый ID меньше длины IP - считаем, что пользователь пытался ввести порт и берём последние символы (до 4-х)
    if (encoded.length() <= 8) {
        encodedPort = encoded.right(4);
        port = encodedPort.toInt(&ok, 36);
        return ok;
    }

    encodedIP = encoded.left(8);
    encodedPort = encoded.mid(8);

    QStringList ipParts;
    for (int i = 0; i < 4; ++i) {
        QString part = encodedIP.mid(i * 2, 2);
        int num = part.toInt(&ok, 36);
        if (!ok) {
            return ok;
        }
        ipParts.append(QString::number(num));
    }

    ip = ipParts.join(".");
    port = encodedPort.toInt(&ok, 36);

    return ok;
}
