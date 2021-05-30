#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <iostream>

enum Typejoueur{
    Humain,
    Machine,
    Null
};

class Player
{
private:
    QString name;
    QString color;
    Typejoueur type;
    int score;
    int brain;

public:
    Player();
    ~Player();
    Player(const QString &color, Typejoueur type);
    QString getName();
    QString getColor();
    Typejoueur getType();
    int getScore();
    int getBrain();

    void setScore(int scorePlayer);
    void setBrain(int qi);
    void setType(Typejoueur type);
    void setColor(QString color);
    void setName(QString name);
};

#endif // PLAYER_H
