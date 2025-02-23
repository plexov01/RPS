#include "game.h"

Game::Game() {}

QString Game::choiceToString(Choice choice) {
    switch (choice) {
    case Rock: return "Rock";
    case Paper: return "Paper";
    case Scissors: return "Scissors";
    default: return "Invalid";
    }
}

Game::Choice Game::stringToChoice(const QString &str) {
    if (str == "Rock") return Rock;
    if (str == "Paper") return Paper;
    if (str == "Scissors") return Scissors;
    return Invalid;
}

Game::Choice Game::getWinner(Choice player1Choice, Choice player2Choice) {
    if (player1Choice == player2Choice) return Choice::Invalid;
    if ((player1Choice == Rock && player2Choice == Scissors) ||
        (player1Choice == Paper && player2Choice == Rock) ||
        (player1Choice == Scissors && player2Choice == Paper)) {
        return player1Choice;
    } else {
        return player2Choice;
    }
}
