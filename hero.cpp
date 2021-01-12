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
    Spell* s = SpellsInv[whichSpell];
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

void Hero::use(int whichPotion)
{
    if (whichPotion < 0 || (whichPotion > PotionsInv.size() - 1)) {
        std::cout << "Invalid position of Potion (Must be: 0 - " << PotionsInv.size() - 1 << ")\n ";
        std::cout << "Try again\n";
        return;
    }
    PotionsInv[whichPotion]->buff(*this);
    PotionsInv.erase(PotionsInv.begin() + whichPotion);
}

void Hero::equip(int whichWeapon, int hand)
{
    if (whichWeapon < 0 || (whichWeapon > WeaponsInv.size() - 1))
    {
        std::cout << "Invalid position of Weapon (Must be: 0 - " << WeaponsInv.size() - 1 << ")\n ";
        std::cout << "Try again\n";
        return;
    }
    if ((hand != 1) && (hand != 2))
    {
        std::cout << "Invalid number for Hand (Must be: 1 - Primary / 2 - Secondary / Empty - 1 by Default)\n";
        std::cout << "Try again\n";
        return;
    }
    Weapon* MyWeapon = WeaponsInv[whichWeapon];
    if (MyWeapon->get_minlvl() <= Level)
    {
        if (MyWeapon->isTwoHanded() == true)
        {
            if ((RightHand != nullptr) && (LeftHand == nullptr))
            {
                std::cout << Name << " is already equipped with '" << RightHand->get_name() << "' Weapon\n";
                char input = proceed();
                if (input == 'n' || input == 'N')
                    return;
                unequip(gearType::RWEAPON);
            }
            else if ((RightHand != nullptr) && (LeftHand != nullptr))
            {
                std::cout << Name << " is already equipped with '" << RightHand->get_name() << "' and '" << LeftHand->get_name() << "' Weapons\n";
                char input = proceed();
                if (input == 'n' || input == 'N')
                    return;
                unequip(gearType::RWEAPON);
                unequip(gearType::LWEAPON);
            }
            if(hand == 1)
                RightHand = MyWeapon;
            else
                LeftHand = MyWeapon;
            std::cout << "Equipped '" << MyWeapon->get_name() << "' Weapon!\n";
        }
        else
        {
            if ((RightHand == nullptr) && (LeftHand == nullptr))
            {
                if(hand == 1)
                    RightHand = MyWeapon;
                else
                    LeftHand = MyWeapon;
                std::cout << "Equipped '" << MyWeapon->get_name() << "' Weapon!\n";
            }
            else if ((RightHand != nullptr) && (LeftHand == nullptr))
            {
                if(hand == 1)
                {
                    std::cout << Name << " is already equipped with '" << RightHand->get_name() << "' Weapon\n";
                    char input = proceed();
                    if (input == 'n' || input == 'N')
                        return;
                    unequip(gearType::RWEAPON);
                }
                else
                {
                    if(RightHand->isTwoHanded() == true)
                    {
                        std::cout << Name << " is already equipped with '" << RightHand->get_name() << "' Weapon\n";
                        char input = proceed();
                        if (input == 'n' || input == 'N')
                            return;
                        unequip(gearType::RWEAPON);
                    }
                    LeftHand = MyWeapon;
                }
                std::cout << "Equipped '" << MyWeapon->get_name() << "' Weapon!\n";
            }
            else if((RightHand == nullptr) && (LeftHand != nullptr))
            {
                if(hand == 1)
                    RightHand = MyWeapon;
                else
                {
                    std::cout << Name << " is already equipped with '" << LeftHand->get_name() << "' Weapon\n";
                    char input = proceed();
                    if (input == 'n' || input == 'N')
                        return;
                    unequip(gearType::LWEAPON);
                }
                std::cout << "Equipped '" << MyWeapon->get_name() << "' Weapon!\n";
            }
            else
            {
                if (hand == 1)
                {
                    std::cout << Name << " is already equipped with '" << RightHand->get_name() << "' Weapon\n";
                    char input = proceed();
                    if (input == 'n' || input == 'N')
                        return;
                    unequip(gearType::RWEAPON);
                    RightHand = MyWeapon;
                }
                else
                {
                    std::cout << Name << " is already equipped with '" << LeftHand->get_name() << "' Weapon\n";
                    char input = proceed();
                    if (input == 'n' || input == 'N')
                        return;
                    unequip(gearType::LWEAPON);
                    LeftHand = MyWeapon;
                }
                std::cout << "Equipped '" << MyWeapon->get_name() << "' Weapon!\n";
            }
        }
        WeaponsInv.erase(WeaponsInv.begin() + whichWeapon);
    }
    else
        std::cout << MyWeapon->get_name() << " can be equipped at Level " << MyWeapon->get_minlvl() << std::endl;
}

void Hero::equip(int whichArmor)
{
    if (whichArmor < 0 || (whichArmor > (ArmorsInv.size() - 1))) {
        std::cout << "Invalid position of Armor (Must be: 0 - " << ArmorsInv.size() - 1 << ")\n ";
        std::cout << "Try again\n";
        return;
    }
    // --> error // Armor* Armour = Inventory[whichArmor];
    Armor* Armour = ArmorsInv[whichArmor];
    if (Armour->get_minlvl() <= Level) {
        if (MyArmor != nullptr) {
            std::cout << Name << " is already equipped with '" << MyArmor->get_name() << "' Armor\n";
            char input = proceed();
            if (input == 'n' || input == 'N')
                return;
            unequip(gearType::ARMOR);
        }
        MyArmor = Armour;
        ArmorsInv.erase(ArmorsInv.begin() + whichArmor);
        std::cout << "Equipped '" << MyArmor->get_name() << "' Armor!\n";
    } else
        std::cout << Armour->get_name() << " can be equipped at Level " << Armour->get_minlvl() << std::endl;
}

void Hero::unequip(gearType equipT)
{
    switch (equipT) {
    case (gearType::ARMOR):
        std::cout << "Unequipped '" << MyArmor->get_name() << "' Armor!\n";
        ArmorsInv.push_back(MyArmor);
        MyArmor = nullptr;
        return;
    case (gearType::RWEAPON):
        std::cout << "Unequipped '" << RightHand->get_name() << "' Weapon!\n";
        WeaponsInv.push_back(RightHand);
        RightHand = nullptr;
        return;
    case (gearType::LWEAPON):
        std::cout << "Unequipped '" << LeftHand->get_name() << "' Weapon!\n";
        WeaponsInv.push_back(LeftHand);
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
    //print weapons / armors / potions / spells
    int index = 0;
    std::cout << "Weapons:\n";
    for (auto it = WeaponsInv.begin(); it != WeaponsInv.end(); ++it)
    {
        std::cout << index++ << ". ";
        (*it)->print();
        std::cout << "\n";
    }
    std::cout << "\nArmors:\n";
    for (auto it = ArmorsInv.begin(); it != ArmorsInv.end(); ++it)
    {
        std::cout << index++ << ". ";
        (*it)->print();
        std::cout << "\n";
    }
        std::cout << "\nPotions:\n";
    for (auto it = PotionsInv.begin(); it != PotionsInv.end(); ++it)
    {
        std::cout << index++ << ". ";
        (*it)->print();
        std::cout << "\n";
    }
        std::cout << "\nSpells:\n";
    for (auto it = SpellsInv.begin(); it != SpellsInv.end(); ++it)
    {
        std::cout << index++ << ". ";
        (*it)->print();
        std::cout << "\n";
    }
}

void Hero::addToInv(Weapon* ToAdd)
{
    WeaponsInv.push_back(ToAdd);
}

void Hero::addToInv(Armor* ToAdd)
{
    ArmorsInv.push_back(ToAdd);
}

void Hero::addToInv(Potion* ToAdd)
{
    PotionsInv.push_back(ToAdd);
}
void Hero::addToInv(Spell* ToAdd)
{
    SpellsInv.push_back(ToAdd);
}

void Hero::displayStats() const
{
    std::cout << Name << " | HP: " << HealthPower << " | MP:" << MagicPower << '\t';
}

char Hero::proceed()
{
    std::cout << "Do you want to proceed? (y/n)\n";
    char input;
    while (!(std::cin >> input) || (input != 'n' && input != 'N' && input != 'y' && input != 'Y')) {
        std::cout << "Invalid input, please type 'y' or 'n'\n";
        std::cin.clear(); //reset possible error flag
        std::cin.ignore(500, '\n'); //clear buffer
        //std::cin >> input;
    }
    return input;
}