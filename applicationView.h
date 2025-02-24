#ifndef APPLICATIONVIEW_H
#define APPLICATIONVIEW_H

#include <QWidget>
#include "ipPortCoder.h"

class Client;
class Server;

namespace Ui {
class ApplicationView;
}
///Ui приложения
class ApplicationView : public QWidget
{
    Q_OBJECT
signals:
    void buttonPressed(QString nameButton);

public:
    explicit ApplicationView(QWidget *parent = nullptr);
    ~ApplicationView();

    void switchToWindowByName(const QString &windowName);

public slots:
    void setMainText(QString string);
    void setDebugText(QString string);
    void setServerIdText(QString string);
    void switchToGameView();

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
