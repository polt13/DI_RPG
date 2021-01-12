//  File Name:  main.cpp

#include "rpg_lib.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

//////ADD SEPARATE INVENTORY PUSH_BACK//
int main()
{
    std::srand(std::time(NULL));

    Game MyGame;

    MyGame.StartScreen();
    
    while(MyGame.get_playing())
        MyGame.MainMenu();


    std::srand(std::time(NULL));
    block* Grid[16];
    int MarketPos = 3;
    int commonBlocks[] = { 0, 1, 2, 7, 8, 9, 10, 11, 12 };
    int inaccessibleBlocks[] = { 4, 5, 6, 13, 14, 15 };
    Grid[MarketPos] = new market();
    for (int i = 0; i < 9; i++) {
        Grid[commonBlocks[i]] = new common();
    }
    for (int i = 0; i < 6; i++) {
        Grid[inaccessibleBlocks[i]] = new inaccessible();
    }
    int printed = 0;
    for (int i = 0; i < 16; i++) {
        std::cout << "|";
        Grid[i]->print();
        printed++;
        if (printed == 4) {
            printed = 0;
            std::cout << "|";
            putchar('\n');
        }
    }

    std::vector<Hero*> h { new Warrior("Liprandoglu") };
    Grid[3]->move(h);
}