//  File Name:  hero.cpp

#include "rpg_lib.hpp"
#include <cmath>
#include <iostream>
#include <map>

using std::string;

Hero::~Hero()
{
    //std::cout << "A Hero to be destroyed!" <<'\n';
    std::cout << Name << '\n';
    std::cout << "Level: " << Level << '\n';
    std::cout << "HP: " << HealthPower << '\n';
    std::cout << "MP: " << MagicPower << '\n';
    std::cout << "STR: " << Strength << '\n';
    std::cout << "DEX: " << Dexterity << '\n';
    std::cout << "AG: " << Agility
              << "\n\n";
    std::cout << "Money: " << Money << '\n';
    std::cout << "XP: " << Experience << " / " << XPmax << '\n';
    std::cout << std::endl;
}

Hero::Hero(const string MyName, int STR, int DEX, int AG)
    : MagicPower(150)
    , Strength(STR)
    , Dexterity(DEX)
    , Agility(AG)
    , Money(0)
    , Experience(0)
    , XPmax(125)
    , RightHand(NULL)
    , LeftHand(NULL)
    , MyArmor(NULL)
    //do next ____ MyPotion(NULL)
    , Living(MyName, 50)
{
    //std::cout << "A New Hero has been created!" << endl <<'\n';
    std::cout << Name << '\n';
    std::cout << "Level: " << Level << '\n';
    std::cout << "HP: " << HealthPower << '\n';
    std::cout << "MP: " << MagicPower
              << '\n';
    std::cout << "STR: " << Strength << '\n';
    std::cout << "DEX: " << Dexterity << '\n';
    std::cout << "AG: " << Agility << "\n\n";
    std::cout << "Money: " << Money << '\n';
    std::cout << "XP: " << Experience << " / " << XPmax << '\n';
    std::cout << '\n';
}

void Hero::set_xp(const int value)
{
    Experience += value;
}

int Hero::get_agility() const
{
    return Agility;
}

int Hero::getMoney() const
{
    return Money;
}

Armor* Hero::get_armor() const
{
    return MyArmor;
}

int Hero::get_max_xp(){
    return XPmax;
}

int& Hero::getStat(cstats potion_t)
{
    switch (potion_t) {
    case (cstats::HP):
        return HealthPower;
    case (cstats::MP):
        return MagicPower;
    case (cstats::DEX):
        return Dexterity;
    case (cstats::STR):
        return Strength;
    }
    return Agility;
}

void Hero::attack(Monster* MyMonster)
{
    if (MyMonster->get_hp() == 0)
        return;
    int DMGdealt;
    if ((RightHand != NULL) && (LeftHand != NULL))
        DMGdealt = (Strength + RightHand->getDamage()) + (Strength + LeftHand->getDamage()) - MyMonster->get_defense();
    else if ((RightHand != NULL) && (LeftHand == NULL))
        DMGdealt = (Strength + RightHand->getDamage()) - MyMonster->get_defense();
    else if ((RightHand == NULL) && (LeftHand != NULL))
        DMGdealt = (Strength + LeftHand->getDamage()) - MyMonster->get_defense();
    else
        DMGdealt = Strength - MyMonster->get_defense();
    if (DMGdealt < 0) {
        std::cout << "Higher defense than dmg\n";
        return;
    }
    if ((rand() % 100) > MyMonster->get_dodge()) {
        std::cout << get_name() << " dealt " << DMGdealt << " DMG to " << MyMonster->get_name() << "!" << '\n';
        MyMonster->decrease_hp(DMGdealt);
    } else
        std::cout << MyMonster->get_name() << " DODGED the Attack!" << '\n';
    std::cout << MyMonster->get_name() << " HP is: " << MyMonster->get_hp() << '\n';
}

void Hero::castSpell(Monster* MyMonster, int whichSpell)
{
    if (MyMonster->get_hp() == 0)
        return;
    Spell* s = spells[whichSpell];
    int DMGdealt = s->getSpellDmg() + Dexterity - MyMonster->get_defense();
    if (DMGdealt < 0) {
        std::cout << "Higher defense than dmg\n";
        return;
    }
    if (MagicPower >= s->getMPcost()) {
        if ((rand() % 100) > MyMonster->get_dodge()) {
            MagicPower -= s->getMPcost();
            MyMonster->decrease_hp(DMGdealt);
            std::cout << get_name() << " dealt  " << DMGdealt << " to " << MyMonster->get_name() << '\n';
            s->apply_effect(MyMonster);
        } else
            std::cout << MyMonster->get_name() << " DODGED the Spell!" << '\n';
    } else
        std::cout << "Not enough MP\n";
    std::cout << MyMonster->get_name() << " HP is: " << MyMonster->get_hp() << '\n';
}

void Hero::levelUp(int str, int dex, int ag)
{
    while (Experience >= XPmax) //in case where XP from a battle is enough for more than 1 level up..
    {
        Experience -= XPmax;
        XPmax += round(XPmax * 0.25);
        Level++;
        Strength += str;
        Dexterity += dex;
        Agility += ag;
    }
}

void Hero::equip(Weapon* MyWeapon, int hand)
{
    if ((hand != 1) && (hand != 2)) {
        std::cout << "Please give a valid number for Hand (1 - Primary / 2 - Secondary / Empty - 1 by Default)\n";
        return;
    }
    if (MyWeapon->get_minlvl() <= Level) {
        if (MyWeapon->get_grip() == true) {
            if ((RightHand != NULL) && (LeftHand == NULL))
                unequip(2);
            else if ((RightHand != NULL) && (LeftHand != NULL)) {
                unequip(2);
                unequip(3);
            }
            RightHand = MyWeapon;
            std::cout << "Equipped '" << RightHand->get_name() << "' Weapon!\n";
            return;
        } else {
            if ((RightHand == NULL) && (LeftHand == NULL)) {
                RightHand = MyWeapon;
                std::cout << "Equipped '" << RightHand->get_name() << "' Weapon!\n";
                return;
            } else if ((RightHand != NULL) && (LeftHand == NULL)) {
                LeftHand = MyWeapon;
                std::cout << "Equipped '" << LeftHand->get_name() << "' Weapon!\n";
                return;
            } else {
                if (hand == 1) {
                    unequip(2);
                    RightHand = MyWeapon;
                    std::cout << "Equipped '" << RightHand->get_name() << "' Weapon!\n";
                    return;
                } else {
                    unequip(3);
                    LeftHand = MyWeapon;
                    std::cout << "Equipped '" << LeftHand->get_name() << "' Weapon!\n";
                    return;
                }
            }
        }
    } else
        std::cout << MyWeapon->get_name() << " can be equipped at Level " << MyWeapon->get_minlvl() << std::endl;
}

void Hero::equip(Armor* Armour)
{
    if (Armour->get_minlvl() <= Level) {
        if (MyArmor != NULL)
            unequip(1);
        MyArmor = Armour;
        std::cout << "Equipped '" << MyArmor->get_name() << "' Armor!\n";
    } else
        std::cout << Armour->get_name() << " can be equipped at Level " << Armour->get_minlvl() << std::endl;
}

void Hero::unequip(int ItemType)
{
    switch (ItemType) {
    case 1:
        std::cout << "Unequipped '" << MyArmor->get_name() << "' Armor!\n";
        MyArmor = NULL;
        return;
    case 2:
        std::cout << "Unequipped '" << RightHand->get_name() << "' Weapon!\n";
        RightHand = NULL;
        return;
    case 3:
        std::cout << "Unequipped '" << LeftHand->get_name() << "' Weapon!\n";
        LeftHand = NULL;
        return;
    }
}

void Hero::addToInv(Item* i)
{
    inv.push_back(i);
}

void Hero::print() const
{
    std::cout << Name << " HP: " << HealthPower << " MP:" << MagicPower << '\t';
}

