#include <QCoreApplication>
#include "server.h"
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Создаем сервер
    Server server;
    server.startServer(12345);  // Порт, на котором сервер будет слушать подключения

    // Создаем клиента
    Client client;
    client.connectToServer("127.0.0.1", 12345);  // Подключаемся к серверу на localhost

    return a.exec();
}
