//  File Name:  hero_constr.cpp

#include <iostream>
#include <cmath>
#include "classes_constr.hpp"

using namespace std;

Hero::~Hero()
{
    //cout << "A Hero to be destroyed!" << endl;
    cout << Name << endl;
    cout << "Level: " << Level << endl;
    cout << "HP: " << HealthPower << endl;
    cout << "MP: " << MagicPower << endl << endl;
    cout << "STR: " << Strenght << endl;
    cout << "DEX: " << Dexterity << endl;
    cout << "AG: " << Agility << endl << endl;
    cout << "Money: " << Money << endl;
    cout << "XP: " << Experience << " / " << XPmax << endl;
    cout << endl;
}

Hero::Hero(const string MyName, int STR, int DEX, int AG) : MagicPower(150), Strenght(STR), Dexterity(DEX), Agility(AG), Money(0), Experience(0), XPmax(125), Living(MyName, 400)
{
    //cout << "A New Hero has been created!" << endl << endl;
    cout << Name << endl;
    cout << "Level: " << Level << endl;
    cout << "HP: " << HealthPower << endl;
    cout << "MP: " << MagicPower << endl << endl;
    cout << "STR: " << Strenght << endl;
    cout << "DEX: " << Dexterity << endl;
    cout << "AG: " << Agility << endl << endl;
    cout << "Money: " << Money << endl;
    cout << "XP: " << Experience << " / " << XPmax << endl;
    cout << endl;
}

void Hero::set_xp(const int value)
{
    Experience = value;
}

void Hero::levelUp(int str, int dex, int ag)
{
    while(Experience >= XPmax)
    {
        Experience -= XPmax;
        XPmax += round(XPmax*0.25);
        Level++;
        Strenght += str;
        Dexterity += dex;
        Agility += ag;
    }
}