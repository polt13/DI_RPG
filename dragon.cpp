//  File Name:  dragon.cpp

#include "rpg_lib.hpp"
#include <iostream>

using namespace std;

Dragon::~Dragon()
{
    cout << "A Dragon to be destroyed!" << endl
         << endl;
}

Dragon::Dragon(const string MyName, int LvL)
    : Monster(MyName, LvL*5, LvL*7, LvL*2, LvL*2, LvL)
{
    cout << "A New Dragon has been created!" << endl
         << endl;
}