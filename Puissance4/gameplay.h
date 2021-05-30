#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "player.h"

#include <QMessageBox>
#include <QPushButton>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QPalette>
#include <QObject>

class Gameplay : public QWidget
{
    Q_OBJECT

public:
    Gameplay( );
    Gameplay(int nbderobot);
    ~Gameplay();

    int select;

    const int x=8;
    const int y=7;
    QPushButton bouton[8][7];
    int gameState[6][7];

    int playerTurn;
    Player *player;
    int nbPlayer;
    int Rand(int a, int b);

    QGridLayout layout ;
    bool replay=false;

    static int nombredIA();
    void putBlock();
    void putBlock(int &select);
    void iaTurn(int qi);

    void moveSwitch(int newselect);

    bool verif_verti(int val);
    bool verif_horiz(int val);
    bool verif_diag_g(int val);
    bool verif_diag_d(int val);
    bool verif_full(int val);

    void restartGame(QPushButton bouton[8][7], int gameState[6][7] , QGridLayout &layout , int &select , int player);
    bool getReplay();
    bool end_Game(int player);

    static int PlayerName();
    void playerPseudo();
    void updateScore();

public slots:
    void playerSwitch();
    void moverightSlot();
    void moveleftSlot();
};

#endif // GAMEPLAY_H
