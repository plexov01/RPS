#ifndef IPPORTCODER_H
#define IPPORTCODER_H

#include <QString>

class IPPortCoder {
public:
    // Кодирует IP-адрес и порт в строку символов
    static QString encodeIPPort(const QString ip, quint16 port);

    // Декодирует строку обратно в IP-адрес и порт
    static bool decodeIPPort(const QString &encoded, QString &ip, quint16 &port);
};

#endif // IPPORTCODER_H
