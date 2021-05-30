#include "gameplay.h"

#include <QLineEdit>
#include <iostream>

int Gameplay::nombredIA(){
    QMessageBox msgBox;
    msgBox.setText("Jouer contre une IA ?");

    QPushButton *IA1 = new QPushButton("Contre un Joueur");
    QPushButton *IA2 = new QPushButton("Contre l'IA");
    QPushButton *Leave = new QPushButton("Fermer l'application");

    msgBox.addButton(IA1 , QMessageBox::RejectRole);
    msgBox.addButton(IA2 , QMessageBox::RejectRole);
    msgBox.addButton(Leave, QMessageBox::RejectRole);

    int ret=msgBox.exec();
    if(ret != 1 && ret !=  2)
        QApplication::quit();

    return (ret);
}

Gameplay::Gameplay(){
    select=3;
    nbPlayer=2;
    playerTurn=1;

    player=new Player[2];
    player[0]= Player("blue", Typejoueur::Humain);
    player[1]= Player("red", Typejoueur::Humain);
    restartGame(bouton, gameState, layout, select, playerTurn);

    QObject::connect(&bouton[7][7-5], SIGNAL(clicked()),this, SLOT(moveleftSlot()));
    QObject::connect(&bouton[7][7-6], SIGNAL(clicked()),this, SLOT(moveleftSlot()));
    QObject::connect(&bouton[7][7-2], SIGNAL(clicked()),this, SLOT(moverightSlot()));
    QObject::connect(&bouton[7][7-3], SIGNAL(clicked()),this, SLOT(moverightSlot()));
    QObject::connect(&bouton[7][7-4], SIGNAL(clicked()),this, SLOT(playerSwitch()));
}

Gameplay::Gameplay(int nbIA){
    select=3;
    nbPlayer=2;
    playerTurn=1;
    player=new Player[2];

    switch (nbIA) {
    case 0 :{
        player[0]= Player("blue", Typejoueur::Humain);
        player[1]= Player("red", Typejoueur::Humain);
        break;
    }
    case 1:{
        player[0]= Player("blue", Typejoueur::Humain);
        player[1]= Player("red", Typejoueur::Machine);
        break;
    }
    default:
        QApplication::quit();
    }

    restartGame(bouton, gameState, layout, select, playerTurn);

    if(player[playerTurn].getType()==Typejoueur::Machine){
        iaTurn(player[playerTurn].getBrain());
    }

    QObject::connect(&bouton[7][7-5], SIGNAL(clicked()),this, SLOT(moveleftSlot()));
    QObject::connect(&bouton[7][7-6], SIGNAL(clicked()),this, SLOT(moveleftSlot()));
    QObject::connect(&bouton[7][7-2], SIGNAL(clicked()),this, SLOT(moverightSlot()));
    QObject::connect(&bouton[7][7-3], SIGNAL(clicked()),this, SLOT(moverightSlot()));
    QObject::connect(&bouton[7][7-4], SIGNAL(clicked()),this, SLOT(playerSwitch()));
}

Gameplay::~Gameplay()
{
    delete [] player;
}

int Gameplay::Rand( int a, int b)
{
    int nRand ;
    nRand= a + (int)((float)rand() * (b-a+1) / (RAND_MAX-1)) ;
    return nRand;
}

void Gameplay::putBlock(){
    putBlock(select);
}

void Gameplay::putBlock(int &select){
    QString colorbg= "background-color:" + player[playerTurn].getColor() +";"  ;
    bool full=true;

    for (int i=5; i>=0;i--){
        if(gameState[i][select]==0){
            bouton[i+1][select].setStyleSheet(colorbg);
            gameState[i][select]=(playerTurn+1);

            if(end_Game(playerTurn+1)){
                QMessageBox msgBox;
                msgBox.setText("Partie terminé, le joueur " + player[playerTurn].getColor() + " a gagné !");
                msgBox.setInformativeText("Voulez-vous rejouer ?");
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::Yes);
                int ret=msgBox.exec();

                switch (ret) {
                case QMessageBox::Yes:
                    restartGame(bouton, gameState, layout, select, playerTurn);
                    replay=true;
                break;
                case  QMessageBox::No:
                    QApplication::quit();
                break;
                default:
                    break;
                }
            }
            i=-1;
            full=false;
        }
    }

    if(!full){
        playerTurn=(playerTurn+1)%nbPlayer;
        bouton[0][select].setStyleSheet("background-color: grey;");
        bouton[0][select].setText("\n\n        \n\n");

        select=3;

        bouton[0][select].setStyleSheet("background-color:" + player[playerTurn].getColor() +";");
        bouton[0][select].setText("\n\nJoueur "+QString::number((playerTurn+1))+"\n\n");
    }
}

void Gameplay::playerSwitch(){
    if(player[playerTurn].getType()==Typejoueur::Humain)
    putBlock();

    if(player[playerTurn].getType()==Typejoueur::Machine){
        iaTurn( player[playerTurn].getBrain());
    }
}

void Gameplay::iaTurn(int qi){
    switch (qi) {
        case 0:{
            int a=Rand(0,6);
            putBlock(a);
        break;
        }
        default:{
            QApplication::quit();
        }
    }
}

void Gameplay::moveSwitch(int newselect){
    bouton[0][select].setText("\n\n        \n\n");
    bouton[0][select].setStyleSheet("background-color: grey;");
    bouton[0][newselect].setStyleSheet("background-color:" + player[playerTurn].getColor() +";");
    bouton[0][newselect].setText("\n\nJoueur "+QString::number((playerTurn+1))+"\n\n");
}

void Gameplay::moverightSlot(){
    int newselect=(select+1)%7;
    moveSwitch(newselect);
    select=newselect;
}

void Gameplay::moveleftSlot(){
    int newselect=(select-1)%7;
    if(newselect<0){
        newselect = 6;
    }
    moveSwitch(newselect);
    select=newselect;
}

bool Gameplay::verif_verti(int val){
    bool end_vert=false;
    for(int columns=0; columns<7;columns++){
        for(int lines=5;lines>=0;lines--){
            if(lines>2){
                if(gameState[lines][columns]==val && gameState[lines-1][columns]==val && gameState[lines-2][columns]==val && gameState[lines-3][columns]==val){
                    end_vert=true;
                }
            }
        }
    }
    return end_vert;
}

bool Gameplay::verif_horiz(int val){
    bool end_hor=false;
    for(int lines=5;lines>=0;lines--){
        for(int columns=0; columns<7;columns++){
            if(columns<4){
                if(gameState[lines][columns]==val && gameState[lines][columns+1]==val && gameState[lines][columns+2]==val && gameState[lines][columns+3]==val){
                    end_hor=true;
                }
            }
        }
    }
    return end_hor;
}

bool Gameplay::verif_diag_g(int val){
    bool end_diag_g=false;
    for(int lines=2;lines>=0;lines--){
        for(int columns=0; columns<4;columns++){
            if(gameState[lines][columns]==val && gameState[lines+1][columns+1]==val && gameState[lines+2][columns+2]==val && gameState[lines+3][columns+3]==val){
                end_diag_g=true;
            }
        }
    }
    return end_diag_g;
}

bool Gameplay::verif_diag_d(int val){
    bool end_diag_d=false;
    for(int lines=5;lines>=3;lines--){
        for(int columns=0; columns<4;columns++){
            if(gameState[lines][columns]==val && gameState[lines-1][columns+1]==val && gameState[lines-2][columns+2]==val && gameState[lines-3][columns+3]==val){
                end_diag_d=true;
            }
        }
    }
    return end_diag_d;
}

bool Gameplay::verif_full(int val){
    bool end_full=false;
    for(int lines=2;lines>6;lines--){
        for(int columns=0; columns>7;columns++){
            if(gameState[lines][columns]==val){
                    end_full=true;
            }
        }
    }
    return end_full;
}

void Gameplay::restartGame(QPushButton bouton[8][7], int gameState[6][7], QGridLayout &layout, int &select, int playerTurn){
    for (int x=0 ; x<6;x++){
        for (int y=0 ; y<7;y++){
            gameState[x][y]=0;
        }
    }

    for (int i=0 ; i<8;i++){
        for(int h=0;h<7;h++){
            bouton[i][h].setText("\n\n        \n\n");
            bouton[i][h].setStyleSheet("background-color: solid gray;");

            layout.addWidget(&bouton[i][h], i, h);

            bouton[0][h].setStyleSheet("background-color: grey;");
            bouton[7][h].setStyleSheet("background-color: grey;");
        }
    }
    bouton[7][7-4].setText("\n\n PLACER \n\n");
    bouton[7][7-2].setText("\n\n   >>   \n\n");
    bouton[7][7-3].setText("\n\n   >>   \n\n");
    bouton[7][7-5].setText("\n\n   <<   \n\n");
    bouton[7][7-6].setText("\n\n   <<   \n\n");

    bouton[0][select].setStyleSheet("background-color:" + player[playerTurn].getColor() +";");
    bouton[0][select].setText("\n\nJoueur "+QString::number((playerTurn+1))+"\n\n");
}

bool Gameplay::getReplay(){
    return replay;
}

bool Gameplay::end_Game(int value){
    bool end=false;
        if(verif_horiz(value) || verif_verti(value)|| verif_diag_d(value)|| verif_diag_g(value) || verif_full(value))
            end=true;
    return end;
}

void Gameplay::updateScore()
{

}
