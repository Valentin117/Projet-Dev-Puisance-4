#include "mainwindow.h"
#include "gameplay.h"

#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QPalette>
#include <QObject>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Gameplay gameplay(Gameplay::nombredIA());

    gameplay.setLayout(&gameplay.layout);
    gameplay.show();

    return a.exec();
}
