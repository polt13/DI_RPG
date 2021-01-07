//  File Name:  sorcerer_constr.cpp

#include <iostream>
#include "rpg_lib.hpp"

using namespace std;

Sorcerer::~Sorcerer()
{
    cout << "A Sorcerer to be destroyed!" << endl << endl;
}

Sorcerer::Sorcerer(const string MyName)
        : Hero(MyName, 2, 4, 3)
{
    cout << "A New Sorcerer has been created!" << endl << endl;
}

void Sorcerer::levelUp()
{
    Hero::levelUp(1, 3, 2);
}