#include "player.h"

Player::Player()
{
    QString name="";
    QString color="";

    type=Null;
    score=0;
    brain=0;
}
Player::~Player(){

}

Player::Player(const QString &color, Typejoueur type){
score=0;
brain=0;
    this->color=color;
    this->type=type;
}

QString Player::getName(){
    return name;
}

QString Player::getColor(){
    return color;
}

Typejoueur Player::getType(){
    return type;
}

int Player::getScore(){
    return score;
}

int Player::getBrain(){
    return brain;
}


void Player::setScore(int scorePlayer){
    score = scorePlayer;
}

void Player::setBrain(int qi){
     brain = qi;
}

void Player::setType(Typejoueur type){
    this->type=type;
}

void Player::setColor(QString color){
    this->color=color;
}

void Player::setName(QString name){
    this->name=name;
}
