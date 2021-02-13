//  File Name:  living_constr.cpp

#include "rpg_lib.hpp"
#include <iostream>

using std::string;

Living::Living(const string& MyName, const int HP, int LvL)
    : Name(MyName)
    , Level(LvL)
    , MaxHealthPower(HP)
    , HealthPower(HP)
    , Faint(false)

{
}

void Living::regenHP()
{
    if (HealthPower > 0) {
        std::cout << Name << " recovers " << (HealthPower / 8) + 1 << " HP\n";
        HealthPower += (HealthPower / 8) + 1; //if HP = 0 don't regen
    }
    if (HealthPower > MaxHealthPower) { //dont overheal
        HealthPower = MaxHealthPower;
    }
}

void Living::decrease_hp(int dealt)
{
    HealthPower -= dealt;
    if (HealthPower <= 0) {
        HealthPower = 0;
        pass_out();
    }
}

string Living::get_name() const
{
    return Name;
}

int Living::get_hp() const
{
    return HealthPower;
}

void Living::pass_out()
{
    std::cout << Name << " passed out!" << std::endl;
    std::cout << "HP: " << HealthPower << std::endl;
    Faint = true;
}

int Living::getLevel()
{
    return Level;
}