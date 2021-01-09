//  File Name:  main.cpp

#include "rpg_lib.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
<<<<<<< HEAD
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
=======
>>>>>>> origin/chris
}