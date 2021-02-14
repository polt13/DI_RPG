//  File Name:  hero.cpp

#include "rpg_lib.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <map>
#include <thread>

using std::string;

Hero::~Hero() { }

Hero::Hero(const string& MyName, int STR, int DEX, int AG, Weapon* MyWeapon, Armor* MyArmour, Spell* MySpell)
    : MaxMagicPower(150)
    , MaxStr(STR)
    , MaxDex(DEX)
    , MaxAgil(AG)
    , Money(100)
    , Experience(0)
    , XPmax(40)
    , RightHand(MyWeapon)
    , LeftHand(nullptr)
    , MyArmor(MyArmour)
    , Living(MyName, 50)
{
    SpellsInv.push_back(MySpell); //start with one spell
    MagicPower = MaxMagicPower;
    Agility = MaxAgil;
    Dexterity = MaxDex;
    Strength = MaxStr;
}

void Hero::set_xp(const int value)
{
    Experience += value;
    if (Experience > XPmax) {
        levelUp();
    }
}

int Hero::get_strength() const
{
    return Strength;
}

int Hero::get_dexterity() const
{
    return Dexterity;
}

int Hero::get_agility() const
{
    return Agility;
}

int Hero::getMoney() const
{
    return Money;
}

Weapon* Hero::get_righthand() const
{
    return RightHand;
}

Weapon* Hero::get_lefthand() const
{
    return LeftHand;
}

Armor* Hero::get_armor() const
{
    return MyArmor;
}

int Hero::get_max_xp() const
{
    return XPmax;
}

int Hero::inv_size(itemType itype) const
{
    if (itype == itemType::WEAPON)
        return WeaponsInv.size();
    else if (itype == itemType::ARMOR)
        return ArmorsInv.size();
    else if (itype == itemType::POTION)
        return PotionsInv.size();
    return SpellsInv.size();
}

int& Hero::getStat(potionType potion_t) //return stat by reference so that it can be increased
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
    default:
        return Agility;
    }
}

void Hero::moneyLoss()
{
    Money /= 2;
}

void Hero::revive()
{
    if (HealthPower == 0) {
        HealthPower = (MaxHealthPower / 5) + 1;
    }
}

void Hero::HPbuff(int hp)
{
    HealthPower += hp;
    if (HealthPower > MaxHealthPower) { //dont overheal
        HealthPower = MaxHealthPower;
    }
}

void Hero::MPbuff(int mp)
{
    MagicPower += mp;
    if (MagicPower > MaxMagicPower) {
        MagicPower = MaxMagicPower;
    }
}

void Hero::DEXbuff(int dex)
{
    Dexterity += dex;
    if (Dexterity > MaxDex) {
        Dexterity = MaxDex;
    }
}
void Hero::STRbuff(int str)
{
    Strength += str;
    if (Strength > MaxStr) {
        Strength = MaxStr;
    }
}

void Hero::AGILbuff(int agil)
{
    Agility += agil;
    if (Agility > MaxAgil) {
        Agility = MaxAgil;
    }
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
        std::cout << "No effect: monster has higher defense!\n";
        return;
    }
    if ((std::rand() % 100) > MyMonster->get_dodge()) {
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
    if (SpellsInv.size() == 0) {
        std::cout << "Spells inventory is empty!\n";
        return;
    }
    if (whichSpell > SpellsInv.size() - 1) {
        std::cout << "No such spell exists\n";
        return;
    }

    Spell* s = SpellsInv[whichSpell];
    int DMGdealt = s->getSpellDmg() + Dexterity - MyMonster->get_defense();
    if (DMGdealt < 0) {
        std::cout << "Higher defense than dmg\n";
        return;
    }
    if (MagicPower >= s->getMPcost()) {
        if ((std::rand() % 100) > MyMonster->get_dodge()) {
            MagicPower -= s->getMPcost();
            MyMonster->decrease_hp(DMGdealt);
            std::cout << get_name() << " dealt  " << DMGdealt << " magic damage to " << MyMonster->get_name() << '\n';
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
        MaxStr += str;
        MaxDex += dex;
        MaxAgil += ag;
        MaxHealthPower += 8;
        MaxMagicPower += 5;
    }
    std::cout << Name << " has leveled up to " << Level << "!\n";
    //refill every stat on levelup//
    HealthPower = MaxHealthPower;
    MagicPower = MaxMagicPower;
    Agility = MaxAgil;
    Dexterity = MaxDex;
    Strength = MaxStr;
}

void Hero::buy(Weapon* w)
{
    Money -= w->getPrice();
    WeaponsInv.push_back(w);
}

void Hero::buy(Armor* a)
{
    Money -= a->getPrice();
    ArmorsInv.push_back(a);
}

void Hero::buy(Potion* p)
{
    Money -= p->getPrice();
    PotionsInv.push_back(p);
}

void Hero::buy(Spell* s)
{
    Money -= s->getPrice();
    SpellsInv.push_back(s);
}

void Hero::sell(Market* MyMarket, itemType itype, int index)
{
    std::cout << "\n\n";
    if (itype == itemType::WEAPON) {
        if (WeaponsInv.size() == 0) {
            std::cout << "No available weapons to sell\n";
            return;
        }
        if (index < 0 || index > WeaponsInv.size() - 1) {
            std::cout << "BAD SELL INDEX\n";
            return;
        }
        std::cout << "\tSold " << Name << " '" << WeaponsInv[index]->get_name() << "' Weapon for " << WeaponsInv[index]->getPrice() / 2 << " Gold!\n";
        addMoney(WeaponsInv[index]->getPrice() / 2);
        MyMarket->acquire(WeaponsInv[index]);
        WeaponsInv.erase(WeaponsInv.begin() + index);
    } else if (itype == itemType::ARMOR) {
        if (ArmorsInv.size() == 0) {
            std::cout << "No available armors to sell\n";
            return;
        }
        if (index < 0 || index > ArmorsInv.size() - 1) {
            std::cout << "BAD SELL INDEX\n";
            return;
        }
        std::cout << "\tSold " << Name << " '" << ArmorsInv[index]->get_name() << "' Armor for " << ArmorsInv[index]->getPrice() / 2 << " Gold!\n";
        addMoney(ArmorsInv[index]->getPrice() / 2);
        MyMarket->acquire(ArmorsInv[index]);
        ArmorsInv.erase(ArmorsInv.begin() + index);
    } else if (itype == itemType::POTION) {
        if (PotionsInv.size() == 0) {
            std::cout << "No available potions to sell\n";
            return;
        }
        if (index < 0 || index > PotionsInv.size() - 1) {
            std::cout << "BAD SELL INDEX\n";
            return;
        }
        std::cout << "\tSold " << Name << " '" << PotionsInv[index]->get_name() << "' Potion for " << PotionsInv[index]->getPrice() / 2 << " Gold!\n";
        addMoney(PotionsInv[index]->getPrice() / 2);
        MyMarket->acquire(PotionsInv[index]);
        PotionsInv.erase(PotionsInv.begin() + index);
    } else {
        if (SpellsInv.size() == 0) {
            std::cout << "No available spells to sell\n";
            return;
        }
        if (index < 0 || index > SpellsInv.size() - 1) {
            std::cout << "BAD SELL INDEX\n";
            return;
        }
        std::cout << "\tSold " << Name << " '" << SpellsInv[index]->get_name() << "' Spell for " << SpellsInv[index]->getPrice() / 2 << " Gold!\n";
        addMoney(SpellsInv[index]->getPrice() / 2);
        MyMarket->acquire(SpellsInv[index]);
        SpellsInv.erase(SpellsInv.begin() + index);
    }
}

void Hero::addMoney(int m)
{
    Money += m;
}

void Hero::regenMP()
{
    if (HealthPower > 0) {
        std::cout << Name << " recovers " << MagicPower / 6 + 1 << " MP\n";
        MagicPower += (MagicPower / 10) + 1;
    }

    if (MagicPower > MaxMagicPower) {
        MagicPower = MaxMagicPower;
    }
}

void Hero::use(int whichPotion)
{

    if (PotionsInv.size() == 0) {
        std::cout << "Potions inv is empty\n";
        return;
    }
    if ((whichPotion < 0) || (whichPotion > (PotionsInv.size() - 1))) {
        std::cout << "Invalid position of Potion (Must be: 0 - " << PotionsInv.size() - 1 << ")\n ";
        return;
    }
    PotionsInv[whichPotion]->buff(this);
    PotionsInv.erase(PotionsInv.begin() + whichPotion);
}

void Hero::set_weapon(int whichWeapon, int hand)
{
    if (WeaponsInv.size() == 0) {
        std::cout << "No available weapons\n";
        return;
    }
    if (whichWeapon < 0 || (whichWeapon > WeaponsInv.size() - 1)) {
        std::cout << "Invalid position of Weapon (Must be: 0 - " << WeaponsInv.size() - 1 << ")\n ";
        std::cout << "Try again\n";
        return;
    }
    if ((hand != 1) && (hand != 2)) {
        std::cout << "Invalid number for Hand (Must be: 1 - Primary / 2 - Secondary / Empty - 1 by Default)\n";
        std::cout << "Try again\n";
        return;
    }
    Weapon* MyWeapon = WeaponsInv[whichWeapon];
    if (MyWeapon->get_minlvl() <= Level) {
        if (MyWeapon->isTwoHanded() == true) {
            if ((RightHand != nullptr) && (LeftHand == nullptr)) {
                std::cout << Name << " is already equipped with '" << RightHand->get_name() << "' Weapon\n";
                char input = proceed();
                if (input == 'n' || input == 'N')
                    return;
                unequip(gearType::RWEAPON);
            } else if ((RightHand != nullptr) && (LeftHand != nullptr)) {
                std::cout << Name << " is already equipped with '" << RightHand->get_name() << "' and '" << LeftHand->get_name() << "' Weapons\n";
                char input = proceed();
                if (input == 'n' || input == 'N')
                    return;
                unequip(gearType::RWEAPON);
                unequip(gearType::LWEAPON);
            }
            if (hand == 1)
                RightHand = MyWeapon;
            else
                LeftHand = MyWeapon;
            std::cout << "Equipped '" << MyWeapon->get_name() << "' Weapon!\n";
        } else {
            if ((RightHand == nullptr) && (LeftHand == nullptr)) {
                if (hand == 1)
                    RightHand = MyWeapon;
                else
                    LeftHand = MyWeapon;
                std::cout << "Equipped '" << MyWeapon->get_name() << "' Weapon!\n";
            } else if ((RightHand != nullptr) && (LeftHand == nullptr)) {
                if (hand == 1) {
                    std::cout << Name << " is already equipped with '" << RightHand->get_name() << "' Weapon\n";
                    char input = proceed();
                    if (input == 'n' || input == 'N')
                        return;
                    unequip(gearType::RWEAPON);
                } else {
                    if (RightHand->isTwoHanded() == true) {
                        std::cout << Name << " is already equipped with '" << RightHand->get_name() << "' Weapon\n";
                        char input = proceed();
                        if (input == 'n' || input == 'N')
                            return;
                        unequip(gearType::RWEAPON);
                    }
                    LeftHand = MyWeapon;
                }
                std::cout << "Equipped '" << MyWeapon->get_name() << "' Weapon!\n";
            } else if ((RightHand == nullptr) && (LeftHand != nullptr)) {
                if (hand == 1)
                    RightHand = MyWeapon;
                else {
                    std::cout << Name << " is already equipped with '" << LeftHand->get_name() << "' Weapon\n";
                    char input = proceed();
                    if (input == 'n' || input == 'N')
                        return;
                    unequip(gearType::LWEAPON);
                }
                std::cout << "Equipped '" << MyWeapon->get_name() << "' Weapon!\n";
            } else {
                if (hand == 1) {
                    std::cout << Name << " is already equipped with '" << RightHand->get_name() << "' Weapon\n";
                    char input = proceed();
                    if (input == 'n' || input == 'N')
                        return;
                    unequip(gearType::RWEAPON);
                    RightHand = MyWeapon;
                } else {
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
    } else
        std::cout << MyWeapon->get_name() << " can be equipped at Level " << MyWeapon->get_minlvl() << std::endl;
}

void Hero::equip(int whichArmor)
{
    if (ArmorsInv.size() == 0) {
        std::cout << "No available armors\n";
        return;
    }
    if (whichArmor < 0 || (whichArmor > (ArmorsInv.size() - 1))) {
        std::cout << "Invalid position of Armor (Must be: 0 - " << ArmorsInv.size() - 1 << ")\n ";
        std::cout << "Try again\n";
        return;
    }
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

void Hero::DisplayItems(itemType itype) const
{
    int index = 1;
    if (itype == itemType::WEAPON) {
        if (WeaponsInv.size() == 0)
            return;
        for (const auto w : WeaponsInv) {
            std::cout << "[ " << index++ << " ] ";
            std::cout << w->get_name() << " | Price: " << w->getPrice() / 2 << " | Damage: " << w->getDamage() << (w->get_grip() == "Two Handed" ? " | Two Handed" : " | One Handed") << " | Minimum level: " << w->get_minlvl() << '\n';
        }
    } else if (itype == itemType::ARMOR) {
        if (ArmorsInv.size() == 0)
            return;
        for (const auto a : ArmorsInv) {
            std::cout << "[ " << index++ << " ] ";
            std::cout << a->get_name() << " | Price: " << a->getPrice() / 2 << " | Defense: " << a->get_def() << " | Minimum level: " << a->get_minlvl() << '\n';
        }
    } else if (itype == itemType::POTION) {
        if (PotionsInv.size() == 0)
            return;
        for (const auto p : PotionsInv) {
            std::cout << "[ " << index++ << " ] ";
            std::cout << p->get_name() << " | Price: " << p->getPrice() / 2 << " | Buff: " << p->typeToString() << " | Buff Amount: " << p->get_buff_amount() << " | Minimum level: " << p->get_minlvl() << '\n';
        }
    } else {
        if (SpellsInv.size() == 0)
            return;
        for (const auto s : SpellsInv) {
            std::cout << "[ " << index++ << " ] ";
            std::cout << s->get_name() << " | Price: " << s->getPrice() / 2 << " Damage Range: " << s->get_mindmg() << " - " << s->get_maxdmg() << " | MP cost: " << s->getMPcost() << " | Duration: " << s->get_duration() << " | Minimum level: " << s->get_minlvl() << '\n';
        }
    }
}

void Hero::checkInventory() const
{
    std::cout << Name << "'s Inventory:\n\n\n";

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
    int itemCount = 0;
    //print weapons / armors / potions / spells
    std::cout << "Weapons:\n";
    for (const auto w : WeaponsInv) {
        std::cout << itemCount++ << ". ";
        w->print();
        std::cout << '\n';
    }
    itemCount = 0;
    std::cout << "\nArmors:\n";
    for (const auto a : ArmorsInv) {
        std::cout << itemCount++ << ". ";
        a->print();
        std::cout << '\n';
    }
    itemCount = 0;
    std::cout << "\nPotions:\n";
    for (const auto p : PotionsInv) {
        std::cout << itemCount++ << ". ";
        p->print();
        std::cout << '\n';
    }
    itemCount = 0;
    std::cout << "\nSpells:\n";
    for (const auto s : SpellsInv) {
        std::cout << itemCount++ << ". ";
        s->print();
        std::cout << '\n';
    }
}

void Hero::displayStats() const
{
    std::cout << Name << " | HP: " << HealthPower << " | MP: " << MagicPower << '\t';
}

char Hero::proceed() //make menu
{
    std::cout << "Do you want to proceed? (y/n)\n";
    char input;
    while (!(std::cin >> input) || (input != 'n' && input != 'N' && input != 'y' && input != 'Y')) {
        std::cout << "Wrong input, please type 'y' or 'n'\n";
        std::cin.clear(); //reset possible error flag
        std::cin.ignore(500, '\n'); //clear buffer
        std::cin >> input;
    }
    return input;
}