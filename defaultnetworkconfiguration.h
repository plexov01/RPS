#ifndef DEFAULTNETWORKCONFIGURATION_H
#define DEFAULTNETWORKCONFIGURATION_H

#include <QObject>

//Класс конфигурации сети по умолчанию
class DefaultNetworkConfiguration
{
public:

    QString getDefaultIp() const;
    int getDefaultPort() const;

private:
    int defaultPort = 50505;
};

#endif // DEFAULTNETWORKCONFIGURATION_H
