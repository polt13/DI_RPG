//  File Name:  living_constr.cpp

#include <iostream>
#include <string>
#include "classes_constr.hpp"

using namespace std;

Living::~Living()
{
    //cout << "A Living to be destroyed!" << endl;
    //cout << endl;
}

Living::Living(const string MyName, const int HP) : Name(MyName), Level(1), HealthPower(HP)
{
    //cout << "A New Living has been created!" << endl;
    //cout << endl;
}