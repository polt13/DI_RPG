//  File Name:  sorcerer_constr.cpp

#include "rpg_lib.hpp"
#include <iostream>

Sorcerer::~Sorcerer()
{
    //cout << "A Sorcerer to be destroyed!" << endl << endl;
}

Sorcerer::Sorcerer(const std::string MyName, Weapon* MyWeapon, Armor* MyArmour, Spell* MySpell)
    : Hero(MyName, 2, 4, 3, MyWeapon, MyArmour, MySpell)
{
    //cout << "A New Sorcerer has been created!" << endl << endl;
}

void Sorcerer::levelUp()
{
    Hero::levelUp(1, 3, 2);
}