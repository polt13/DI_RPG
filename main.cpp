//  File Name:  main.cpp

#include "classes_constr.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
    srand((unsigned int)time(NULL));

    Hero* war1 = new Warrior("Christos");
    war1->set_xp(200);
    war1->levelUp();

    Hero* sor1 = new Sorcerer("PEPEGA");
    sor1->set_xp(200);
    sor1->levelUp();
    Potion* p = new Potion("P", 5, 3, cstats::HP);
    delete sor1;
    delete war1;
    Monster* m = new Dragon("Coco");
    war1->attack(m);
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