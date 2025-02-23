#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>

class Client : public QObject {
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    bool tryConnectToServer(QHostAddress &hostAdress, quint16 port);

signals:
    void outputDebugText(QString debugText);
    void outputMainText(QString debugText);

public slots:
    void sendMessage(const QString &message);

private slots:
    void onConnected();
    void onReadyRead();

private:
    QTcpSocket *socket;
};

#endif // CLIENT_H
