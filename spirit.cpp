//  File Name:  spirit.cpp

#include <iostream>
#include "rpg_lib.hpp"

using namespace std;

Spirit::~Spirit()
{
    cout << "A Spirit to be destroyed!" << endl << endl;
}

Spirit::Spirit(const string MyName, int LvL)
        : Monster(MyName, LvL*3, LvL*5, LvL*2, LvL*4, LvL)
{
    cout << "A New Spirit has been created!" << endl << endl;
}