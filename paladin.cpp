//  File Name:  paladin_constr.cpp

#include "rpg_lib.hpp"
#include <iostream>

using namespace std;

Paladin::~Paladin()
{
    //cout << "A Paladin to be destroyed!" << endl << endl;
}

Paladin::Paladin(const string MyName, Weapon* MyWeapon, Armor* MyArmour, Spell* MySpell)
    : Hero(MyName, 4, 3, 2, MyWeapon, MyArmour, MySpell)
{
    //cout << "A New Paladin has been created!" << endl << endl;
}

void Paladin::levelUp()
{
    Hero::levelUp(3, 2, 1);
}