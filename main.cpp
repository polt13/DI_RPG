//  File Name:  main.cpp

#include "rpg_lib.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
    std::srand(std::time(NULL));

    Game MyGame;

    MyGame.StartScreen();

    while (MyGame.get_playing())
        MyGame.MainMenu();
}