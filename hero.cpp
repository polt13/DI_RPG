//  File Name:  hero_constr.cpp
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
    ,
    //do next ____ MyWeapon(NULL), MyArmor(NULL), MyPotion(NULL)
    Living(MyName, 400)
{
    //std::cout << "A New Hero has been created!" << endl <<'\n';
    std::cout << Name <<'\n';
    std::cout << "Level: " << Level <<'\n';
    std::cout << "HP: " << HealthPower <<'\n';
    std::cout << "MP: " << MagicPower 
         <<'\n';
    std::cout << "STR: " << Strength <<'\n';
    std::cout << "DEX: " << Dexterity <<'\n';
    std::cout << "AG: " << Agility << "\n\n";
    std::cout << "Money: " << Money <<'\n';
    std::cout << "XP: " << Experience << " / " << XPmax <<'\n';
    std::cout <<'\n';
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
        std::cout << get_name() << " dealt " << DMGdealt << " DMG to " << MyMonster->get_name() << "!" <<'\n';
        MyMonster->decrease_hp(DMGdealt);
    } else
        std::cout << MyMonster->get_name() << " DODGED the Attack!" <<'\n';
    std::cout << MyMonster->get_name() << " HP is: " << MyMonster->get_hp() <<'\n';
}

int Hero::getMoney() const{
    return Money;
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
        s->apply_effect(m);
    } else {
        std::cout << "Not enough MP\n";
        return;
    }
}

void Hero::levelUp(int str, int dex, int ag)
{
    while (Experience >= XPmax) { //in case where XP from a battle is enough for more than 1 level up..
        Experience -= XPmax;
        XPmax += round(XPmax * 0.25);
        Level++;
        Strength += str;
        Dexterity += dex;
        Agility += ag;
    }
}

void Hero::addToInv(Item* i){
    inv.push_back(i);
}
