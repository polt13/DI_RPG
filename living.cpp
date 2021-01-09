//  File Name:  living_constr.cpp

#include "rpg_lib.hpp"
#include <iostream>

using std::string;

Living::~Living()
{
    //std::cout << "A Living to be destroyed!" << std::endl;
    //std::cout << std::endl;
}

Living::Living(const string MyName, const int HP, int LvL)
    : Name(MyName)
    , Level(LvL)
    , HealthPower(HP)
    , Faint(false)
{
    //std::cout << "A New Living has been created!" << std::endl;
    //std::cout << std::endl;
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