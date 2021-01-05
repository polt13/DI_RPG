//  File Name:  main.cpp

#include <iostream>
#include "classes_constr.hpp"

using namespace std;

int main()
{
    //Hero* war1 = new Hero("Christos", 460, 100, 4, 2, 3);
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

    return 0;
}