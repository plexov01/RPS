#ifndef GAME_H
#define GAME_H

#include <QString>
#include <QHostAddress>

//Класс игры
class Game
{
public:
    enum Choice {
        Rock,
        Paper,
        Scissors,
        Invalid
    };

    Game();
    static QString choiceToString(Choice choice);
    static Choice stringToChoice(const QString &str);
    static Choice getWinner(Choice player1, Choice player2);
};

#endif // GAME_H
