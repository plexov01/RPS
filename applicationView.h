#ifndef APPLICATIONVIEW_H
#define APPLICATIONVIEW_H

class Client;
class Server;
#include "ipPortCoder.h"
#include <QWidget>

namespace Ui {
class ApplicationView;
}

class ApplicationView : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicationView(QWidget *parent = nullptr);
    ~ApplicationView();

    void switchToWindowByName(const QString &windowName);

    void setServer(Server server);
    void setClient(Client client);

signals:
    void buttonPressed(QString nameButton);

public slots:
    void setMainText(QString string);
    void setDebugText(QString string);
    void setServerIdText(QString string);

private slots:
    void createGame_released();

    void joinGame_released();

    void lineEditTextChanged(const QString &arg1);

    void rock_released();

    void paper_released();

    void scissors_released();

private:

    Ui::ApplicationView *ui;
    Server *server;
    Client *client;
    IPPortCoder ipPortCoder;
};

#endif // APPLICATIONVIEW_H
