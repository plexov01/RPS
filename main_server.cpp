#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    Server server;
    server.startServer(12345);

    return a.exec();
}
