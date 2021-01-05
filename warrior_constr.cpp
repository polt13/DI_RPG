//  File Name:  warrior_constr.cpp

#include <iostream>
#include "classes_constr.hpp"

using namespace std;

Warrior::~Warrior()
{
    cout << "A Warrior to be destroyed!" << endl << endl;
}

Warrior::Warrior(const string MyName) : Hero(MyName, 4, 2, 3)
{
    cout << "A New Warrior has been created!" << endl << endl;
}

void Warrior::levelUp()
{
    Hero::levelUp(3, 1, 2);
}