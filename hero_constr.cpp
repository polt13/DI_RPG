//  File Name:  hero_constr.cpp
#include "classes_constr.hpp"
#include <cmath>
#include <iostream>

using namespace std;

Hero::~Hero()
{
    //cout << "A Hero to be destroyed!" << endl;
    cout << Name << endl;
    cout << "Level: " << Level << endl;
    cout << "HP: " << HealthPower << endl;
    cout << "MP: " << MagicPower << endl
         << endl;
    cout << "STR: " << Strength << endl;
    cout << "DEX: " << Dexterity << endl;
    cout << "AG: " << Agility << endl
         << endl;
    cout << "Money: " << Money << endl;
    cout << "XP: " << Experience << " / " << XPmax << endl;
    cout << endl;
}

Hero::Hero(const string MyName, int STR, int DEX, int AG)
    : MagicPower(150)
    , Strength(STR)
    , Dexterity(DEX)
    , Agility(AG)
    , Money(0)
    , Experience(0)
    , XPmax(125)
    ,
    //do next ____ MyWeapon(NULL), MyArmor(NULL), MyPotion(NULL)
    Living(MyName, 400)
{
    //cout << "A New Hero has been created!" << endl << endl;
    cout << Name << endl;
    cout << "Level: " << Level << endl;
    cout << "HP: " << HealthPower << endl;
    cout << "MP: " << MagicPower << endl
         << endl;
    cout << "STR: " << Strength << endl;
    cout << "DEX: " << Dexterity << endl;
    cout << "AG: " << Agility << endl
         << endl;
    cout << "Money: " << Money << endl;
    cout << "XP: " << Experience << " / " << XPmax << endl;
    cout << endl;
}

int Hero::get_agility() const
{
    return Agility;
}

int& Hero::getStat(cstats potion_t)
{
    if (potion_t == cstats::HP)
        return HealthPower;
    else if (potion_t == cstats::MP)
        return MagicPower;
    else if (potion_t == cstats::DEX)
        return Dexterity;
    else if (potion_t == cstats::STR)
        return Strength;
    else
        return Agility;
}

/*
int Hero::get_weap_dmg() const
{
    return MyWeapon->get_dmg();
}

int Hero::get_armor_def() const
{
    return MyArmor->get_defense();
}
*/

void Hero::set_xp(const int value)
{
    Experience = value;
}

void Hero::attack(Monster* MyMonster)
{
    if (MyMonster->get_hp() == 0)
        return;
    if ((rand() % 100) > MyMonster->get_dodge()) {
        int DMGdealt = Strength - MyMonster->get_defense() + 0; //DO NEXT -- ADD WEAPON DAMAGE!!!!!!!!!
        std::cout
            << get_name() << " dealt " << DMGdealt << " DMG to " << MyMonster->get_name() << "!" << endl;
        MyMonster->decrease_hp(DMGdealt);
    } else
        cout << MyMonster->get_name() << " DODGED the Attack!" << endl;
    cout << MyMonster->get_name() << " HP is: " << MyMonster->get_hp() << endl;
}

void Hero::castSpell(Monster* m, int whichSpell)
{
    Spell* s = spells[whichSpell];
    int final_damage = s->getSpellDmg() + Dexterity - m->get_defense();
    if (final_damage < 0) {
        std::cout << "Higher defense than dmg\n";
        return;
    }
    if (MagicPower >= s->getMPcost()) {
        MagicPower -= s->getMPcost();
        m->decrease_hp(final_damage);
        std::cout << " Dealt  " << final_damage << " to " << m->get_name() << '\n';
    } else {
        std::cout << "Not enough mana\n";
        return;
    }
}

void Hero::levelUp(int str, int dex, int ag)
{
    while (Experience >= XPmax) {
        Experience -= XPmax;
        XPmax += round(XPmax * 0.25);
        Level++;
        Strength += str;
        Dexterity += dex;
        Agility += ag;
    }
}
