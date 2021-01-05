//  File Name:  monster_constr.cpp

#include <iostream>
#include "classes_constr.hpp"

using namespace std;

Monster::~Monster()
{
    //cout << "A Monster to be destroyed!" << endl;
    cout << Name << endl;
    cout << "Level: " << Level << endl;
    cout << "HP: " << HealthPower << endl << endl;
    cout << "DMG: " << minDMG << " - " << maxDMG << endl;
    cout << "DEF: " << Defense << endl;
    cout << "DODGE: " << Dodge << "%" << endl;
    cout << endl;
}

Monster::Monster(const string MyName, int LowDMG, int HighDMG, int DEF, int MissChance) : minDMG(LowDMG), maxDMG(HighDMG), Defense(DEF), Dodge(MissChance), Living(MyName, 250)
{
    //cout << "A New Monster has been created!" << endl;
    cout << Name << endl;
    cout << "Level: " << Level << endl;
    cout << "HP: " << HealthPower << endl << endl;
    cout << "DMG: " << minDMG << " - " << maxDMG << endl;
    cout << "DEF: " << Defense << endl;
    cout << "DODGE: " << Dodge << "%" << endl;
    cout << endl;
}