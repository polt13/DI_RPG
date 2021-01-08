//  File Name:  main.cpp

#include "rpg_lib.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
    srand((unsigned int)time(NULL));

    Hero* war1 = new Warrior("Christos");
    //war1->set_xp(200);
    //war1->levelUp();

    Weapon* wea1 = new Weapon("BIG GUN", 100, 1, 60, false);
    Weapon* wea2 = new Weapon("small GUN", 100, 1, 60, false);
    Weapon* wea3 = new Weapon("VERY GUN", 100, 1, 60, false);
    

    war1->equip(wea1, 1);
    war1->equip(wea2, 1);
    war1->equip(wea3, 3);

    Armor* arm1 = new Armor("THORMAIL", 100, 1, 60);
    Armor* arm2 = new Armor("TURBO", 100, 2, 60);

    
    Dragon* dra1 = new Dragon("Ehlonna");
    dra1->attack(war1);
    //war1->attack(dra1);

/*
    Hero* sor1 = new Sorcerer("PEPEGA");
    sor1->set_xp(200);
    sor1->levelUp();
    Potion* p = new Potion("P", 5, 3, cstats::HP);
    delete sor1;
    delete war1;
    Monster* m = new Dragon("Coco");
    war1->attack(m);
*/
    /*
    Warrior* war1 = new Warrior("Abbathor");
    cout << endl;
    Sorcerer* sor1 = new Sorcerer("Bahamut");
    cout << endl;
    Paladin* pal1 = new Paladin("Eadro");

    cout << endl << endl << endl;

    Dragon* dra1= new Dragon("Ehlonna");
    cout << endl;
    Exoskeleton* exo1 = new Exoskeleton("Gadhelyn");
    cout << endl;
    Spirit* spi1 = new Spirit("Moradin");
    */

    //Hero* war1 = new Warrior("Christos");
    //Monster* dra1 = new Dragon("Ehlonna");
    //dra1->attack(war1);

    return 0;
}