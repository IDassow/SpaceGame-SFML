// Game2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <time.h>
#include "Game.h"

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    Game game;
    game.run();

    std::cout << "Game Exited!\n";
}

