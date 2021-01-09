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
    , RightHand(nullptr)
    , LeftHand(nullptr)
    , MyArmor(nullptr)
    //do next ____ MyPotion(nullptr)
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

int Hero::get_max_xp()
{
    return XPmax;
}

int& Hero::getStat(potionType potion_t)
{
    switch (potion_t) {
    case (potionType::HP):
        return HealthPower;
    case (potionType::MP):
        return MagicPower;
    case (potionType::DEX):
        return Dexterity;
    case (potionType::STR):
        return Strength;
    }
    return Agility;
}

void Hero::attack(Monster* MyMonster)
{
    if (MyMonster->get_hp() == 0)
        return;
    int DMGdealt;
    if ((RightHand != nullptr) && (LeftHand != nullptr))
        DMGdealt = (Strength + RightHand->getDamage()) + (Strength + LeftHand->getDamage()) - MyMonster->get_defense();
    else if ((RightHand != nullptr) && (LeftHand == nullptr))
        DMGdealt = (Strength + RightHand->getDamage()) - MyMonster->get_defense();
    else if ((RightHand == nullptr) && (LeftHand != nullptr))
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
        if (MyWeapon->isTwoHanded() == true) {
            if ((RightHand != nullptr) && (LeftHand == nullptr))
                unequip(itemType::RWEAPON);
            else if ((RightHand != nullptr) && (LeftHand != nullptr)) {
                unequip(itemType::RWEAPON);
                unequip(itemType::LWEAPON);
            }
            RightHand = MyWeapon;
            std::cout << "Equipped '" << RightHand->get_name() << "' Weapon!\n";
            return;
        } else {
            if ((RightHand == nullptr) && (LeftHand == nullptr)) {
                RightHand = MyWeapon;
                std::cout << "Equipped '" << RightHand->get_name() << "' Weapon!\n";
                return;
            } else if ((RightHand != nullptr) && (LeftHand == nullptr)) {
                LeftHand = MyWeapon;
                std::cout << "Equipped '" << LeftHand->get_name() << "' Weapon!\n";
                return;
            } else {
                if (hand == 1) {
                    unequip(itemType::RWEAPON);
                    RightHand = MyWeapon;
                    std::cout << "Equipped '" << RightHand->get_name() << "' Weapon!\n";
                    return;
                } else {
                    unequip(itemType::LWEAPON);
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
        if (MyArmor != nullptr)
            unequip(itemType::ARMOR);
        MyArmor = Armour;
        std::cout << "Equipped '" << MyArmor->get_name() << "' Armor!\n";
    } else
        std::cout << Armour->get_name() << " can be equipped at Level " << Armour->get_minlvl() << std::endl;
}

void Hero::unequip(itemType equipT)
{
    switch (equipT) {
    case (itemType::ARMOR):
        std::cout << "Unequipped '" << MyArmor->get_name() << "' Armor!\n";
        inv.push_back(MyArmor);
        MyArmor = nullptr;
        return;
    case (itemType::RWEAPON):
        std::cout << "Unequipped '" << RightHand->get_name() << "' Weapon!\n";
        inv.push_back(RightHand);
        RightHand = nullptr;
        return;
    case (itemType::LWEAPON):
        std::cout << "Unequipped '" << LeftHand->get_name() << "' Weapon!\n";
        inv.push_back(LeftHand);
        LeftHand = nullptr;
        return;
    }
}

void Hero::checkInventory() const
{
    std::cout << Name << "'s Inventory:\n\n";

    if (RightHand != nullptr) {
        RightHand->print();
        std::cout << "\t[EQUIPPED]\n";
    }
    if (LeftHand != nullptr) {
        LeftHand->print();
        std::cout << "\t[EQUIPPED]\n";
    }
    if (MyArmor != nullptr) {
        MyArmor->print();
        std::cout << "\t[EQUIPPED]\n";
    }
    for (auto it = inv.begin(); it != inv.end(); ++it) {
        (*it)->print();
        std::cout << "\n";
    }
}

void Hero::addToInv(Item* i)
{
    inv.push_back(i);
}

void Hero::displayStats() const
{
    std::cout << Name << " | HP: " << HealthPower << " | MP:" << MagicPower << '\t';
}
