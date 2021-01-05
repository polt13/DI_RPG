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

void Monster::attack(Hero* MyHero)
{
    if(MyHero->get_hp() == 0)
        return;
    if( rand() % 100 > MyHero->get_agility() )
    {
        int DMGdealt = rand() % (maxDMG-minDMG + 1) + minDMG;   //Generate num from minDMG-maxDMG included
        cout << get_name() << " dealt " << DMGdealt << " DMG to " << MyHero->get_name() << "!" << endl;
        MyHero->decrease_hp(DMGdealt);
        if(MyHero->get_hp() <= 0)
        {
            MyHero->pass_out();
            return;
        }
    }
    else
        cout << MyHero->get_name() << " DODGED the Attack!" << endl;
    cout << MyHero->get_name() << " HP is: " << MyHero->get_hp() << endl;
}