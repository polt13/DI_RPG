//  File Name:  paladin_constr.cpp

#include <iostream>
#include "classes_constr.hpp"

using namespace std;

Paladin::~Paladin()
{
    cout << "A Paladin to be destroyed!" << endl << endl;
}

Paladin::Paladin(const string MyName) : Hero(MyName, 4, 3, 2)
{
    cout << "A New Paladin has been created!" << endl << endl;
}

void Paladin::levelUp()
{
    Hero::levelUp(3, 2, 1);
}