//  File Name:  living_constr.cpp

#include "classes_constr.hpp"
#include <iostream>

using namespace std;

Living::~Living()
{
    //cout << "A Living to be destroyed!" << endl;
    //cout << endl;
}

Living::Living(const string MyName, const int HP)
    : Name(MyName)
    , Level(1)
    , HealthPower(HP)
    , Faint(false)
{
    //cout << "A New Living has been created!" << endl;
    //cout << endl;
}

void Living::decrease_hp(int dealt)
{
    HealthPower -= dealt;
    if (HealthPower <= 0) {
        HealthPower = 0;
        pass_out();
    }
}

string Living::get_name()
{
    return Name;
}

int Living::get_hp()
{
    return HealthPower;
}

void Living::pass_out()
{
    cout << Name << " passed out!" << endl;
    cout << "HP: " << HealthPower << endl;
    Faint = true;
}