//  File Name:  exoskeleton.cpp

#include <iostream>
#include "rpg_lib.hpp"

using namespace std;

Exoskeleton::~Exoskeleton()
{
    cout << "An Exoskeleton to be destroyed!" << endl << endl;
}

Exoskeleton::Exoskeleton(const string MyName, int LvL)
        : Monster(MyName, LvL*3, LvL*5, LvL*4, LvL*2, LvL)
{
    cout << "A New Exoskeleton has been created!" << endl << endl;
}