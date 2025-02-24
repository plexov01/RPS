#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>

//Класс клиента
class Client : public QObject {
    Q_OBJECT

signals:
    void outputDebugText(QString debugText);
    void outputMainText(QString debugText);
    void canSwitchToGameView();

public:
    explicit Client(QObject *parent = nullptr);
    bool tryConnectToServer(QHostAddress &hostAdress, quint16 port);

public slots:
    void sendMessage(const QString &message);

private slots:
    void onReadyRead();

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
