//  File Name:  warrior_constr.cpp

#include "rpg_lib.hpp"
#include <iostream>

Warrior::~Warrior()
{
    //cout << "A Warrior to be destroyed!" << endl << endl;
}

Warrior::Warrior(const std::string MyName, Weapon* MyWeapon, Armor* MyArmour, Spell* MySpell)
    : Hero(MyName, 4, 2, 3, MyWeapon, MyArmour, MySpell)
{
    //cout << "A New Warrior has been created!" << endl << endl;
}

void Warrior::levelUp()
{
    Hero::levelUp(3, 1, 2);
}