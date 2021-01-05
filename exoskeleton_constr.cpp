//  File Name:  exoskeleton_constr.cpp

#include <iostream>
#include "rpg_lib.hpp"

using namespace std;

Exoskeleton::~Exoskeleton()
{
    cout << "An Exoskeleton to be destroyed!" << endl << endl;
}

Exoskeleton::Exoskeleton(const string MyName)
        : Monster(MyName, 50, 70, 50, 5)
{
    cout << "A New Exoskeleton has been created!" << endl << endl;
}