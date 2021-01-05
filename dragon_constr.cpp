//  File Name:  dragon_constr.cpp

#include <iostream>
#include "classes_constr.hpp"

using namespace std;

Dragon::~Dragon()
{
    cout << "A Dragon to be destroyed!" << endl << endl;
}

Dragon::Dragon(const string MyName)
        : Monster(MyName, 80, 100, 20, 5)
{
    cout << "A New Dragon has been created!" << endl << endl;
}