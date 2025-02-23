#include "applicationView.h"
#include "ui_applicationView.h"
#include <qregularexpression.h>
#include <qvalidator.h>
#include "server.h"
#include "client.h"

#include <QNetworkInterface>

ApplicationView::ApplicationView(QWidget *parent) : QWidget(parent), ui(new Ui::ApplicationView)
{
    ui->setupUi(this);

    //Подключаю кнопки
    connect(ui->createGame, &QPushButton::clicked, this, &ApplicationView::createGame_released);
    connect(ui->joinGame, &QPushButton::clicked, this, &ApplicationView::joinGame_released);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &ApplicationView::lineEditTextChanged);

    connect(ui->rock, &QPushButton::released, this, &ApplicationView::rock_released);
    connect(ui->paper, &QPushButton::released, this, &ApplicationView::paper_released);
    connect(ui->scissors, &QPushButton::released, this, &ApplicationView::scissors_released);

    // Создание регулярного выражения для допустимых символов
    QRegularExpression regex("^[A-Za-z0-9]{1,12}$");

    // Создание валидатора на основе регулярного выражения
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, this);

    // Установка валидатора
    ui->lineEdit->setValidator(validator);

    ui->lineEdit->setText("");

}

ApplicationView::~ApplicationView()
{
    delete ui;
}

void ApplicationView::switchToWindowByName(const QString &windowName) {
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        QWidget *widget = ui->stackedWidget->widget(i);
        if (widget->objectName() == windowName) {
            ui->stackedWidget->setCurrentIndex(i);
            return;
        }
    }
    qDebug() << "Window not found: " << windowName;  // Вывод в отладку, если окно не найдено
}

void ApplicationView::createGame_released()
{
    Server *server = new Server();
    quint16 port;
    QString ip;
    QString textLineEdit = ui->lineEdit->text();

    // получаем ip и port из введённого ID (все символы, которые введены после 8-го символа в ID)
    ipPortCoder.decodeIPPort(textLineEdit, ip, port);

    connect(server, &Server::outputDebugText, this, &ApplicationView::setDebugText);
    connect(server, &Server::outputServerIdText, this, &ApplicationView::setServerIdText);

    if(server->startServer(port)){
        switchToWindowByName("server");

    }

}


void ApplicationView::joinGame_released()
{

    quint16 port;
    QString ip;
    QString textLineEdit = ui->lineEdit->text();

    // Получаем ip и port из введённого ID (все символы, которые введены после 8-го символа в ID)
    ipPortCoder.decodeIPPort(textLineEdit, ip, port);

    QHostAddress address;
    address.setAddress(ip);

    Client *client = new Client();
    // client->setView(this);
    connect(this, &ApplicationView::buttonPressed, client, &Client::sendMessage);

    connect(client, &Client::outputDebugText, this, &ApplicationView::setDebugText);
    connect(client, &Client::outputMainText, this, &ApplicationView::setMainText);



    if(client->tryConnectToServer(address, port)){
        switchToWindowByName("game");
    }

}

void ApplicationView::lineEditTextChanged(const QString &arg1)
{
    ui->lineEdit->setText(arg1.toUpper());
}


void ApplicationView::setMainText(QString string)
{
    ui->label->setText(string);
}

void ApplicationView::setDebugText(QString string)
{
    ui->debugLabel->setText(string);
}

void ApplicationView::setServerIdText(QString string)
{
    ui->textServerID->setText(string);
}


void ApplicationView::rock_released()
{
    emit buttonPressed("Rock");
}


void ApplicationView::paper_released()
{
    emit buttonPressed("Paper");
}


void ApplicationView::scissors_released()
{
    emit buttonPressed("Scissors");
}


