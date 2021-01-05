//  File Name:  spirit_constr.cpp

#include <iostream>
#include "classes_constr.hpp"

using namespace std;

Spirit::~Spirit()
{
    cout << "A Spirit to be destroyed!" << endl << endl;
}

Spirit::Spirit(const string MyName)
        : Monster(MyName, 50, 70, 20, 25)
{
    cout << "A New Spirit has been created!" << endl << endl;
}