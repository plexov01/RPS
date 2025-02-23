#ifndef PLAYERMESSAGE_H
#define PLAYERMESSAGE_H


#include <QString>
#include <qtcpsocket.h>

class PlayerMessage {
public:
    PlayerMessage(const quint16 port, const QString message);

    quint16 getPort() const;
    QString getMessage() const;

    void setMessage(const QString message);

    // Оператор сравнения, чтобы можно было сравнивать объекты PlayerMessage
    bool operator==(const PlayerMessage& other) const;

private:
    quint16 port;
    QString message;
};

#endif // PLAYERMESSAGE_H
