//  File Name:  sorcerer_constr.cpp

#include "rpg_lib.hpp"

Sorcerer::~Sorcerer()
{
}

Sorcerer::Sorcerer(const std::string& MyName, Weapon* MyWeapon, Armor* MyArmour, Spell* MySpell)
    : Hero(MyName, 2, 4, 3, MyWeapon, MyArmour, MySpell)
{
}

void Sorcerer::levelUp()
{
    Hero::levelUp(1, 3, 2);
}