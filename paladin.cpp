//  File Name:  paladin_constr.cpp

#include "rpg_lib.hpp"
#include <iostream>

Paladin::~Paladin()
{
}

Paladin::Paladin(const std::string& MyName, Weapon* MyWeapon, Armor* MyArmour, Spell* MySpell)
    : Hero(MyName, 4, 3, 2, MyWeapon, MyArmour, MySpell)
{
}

void Paladin::levelUp()
{
    Hero::levelUp(3, 2, 1);
}