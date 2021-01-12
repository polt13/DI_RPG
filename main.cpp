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


    // Warrior* warrior1 = new Warrior("MPAMPAS");
    // Weapon* weapon1 = new Weapon("KAVLI", 100, 1, 40, false);
    // Weapon* weapon2 = new Weapon("KALAMARI", 100, 1, 60, true);
    // Armor* armor1 = new Armor("POUTANA_SOU", 100, 1, 20);
    // Armor* armor2 = new Armor("MUCH_WOW", 100, 1, 20);

    // Armor* bigmmr = new Armor("KAVLI", 100, 1, 40);
    // warrior1->addToInv(bigmmr);

    // //warrior1->addToWeapons(weapon1);
    // //warrior1->addToArmors(armor1);
    // //warrior1->addToArmors(armor2);
    // //warrior1->addToWeapons(weapon2);
    // // warrior1->equip(weapon1);
    // // warrior1->equip(armor1);
    // // warrior1->equip(weapon2, 1);
    // // warrior1->addToInv(armor2);

    // warrior1->checkInventory();

    // //system("clear");

    // std::cout << "\n\n";

    
    // block* Grid[16];
    // int MarketPos = 3;
    // int commonBlocks[] = { 0, 1, 2, 7, 8, 9, 10, 11, 12 };
    // int inaccessibleBlocks[] = { 4, 5, 6, 13, 14, 15 };
    // Grid[MarketPos] = new market();
    // for (int i = 0; i < 9; i++) {
    //     Grid[commonBlocks[i]] = new common();
    // }
    // for (int i = 0; i < 6; i++) {
    //     Grid[inaccessibleBlocks[i]] = new inaccessible();
    // }
    // int printed = 0;
    // for (int i = 0; i < 16; i++) {
    //     std::cout << "|";
    //     Grid[i]->print();
    //     printed++;
    //     if (printed == 4) {
    //         printed = 0;
    //         std::cout << "|";
    //         putchar('\n');
    //     }
    // }
}