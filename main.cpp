//  File Name:  main.cpp

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "classes_constr.hpp"

using namespace std;

int main()
{
    srand((unsigned int)time(NULL));

    //Hero* war1 = new Hero("Christos", 460, 100, 4, 2, 3);
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

   Hero* war1 = new Warrior("Christos");
   Monster* dra1 = new Dragon("Ehlonna");
   dra1->attack(war1);
   dra1->attack(war1);
   dra1->attack(war1);
   dra1->attack(war1);
   dra1->attack(war1);
   dra1->attack(war1);

    return 0;
}