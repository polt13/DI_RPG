//  File Name:  exoskeleton.cpp

#include "rpg_lib.hpp"
#include <iostream>

Exoskeleton::Exoskeleton(const std::string& MyName, int LvL)
    : Monster(MyName, LvL + 7, LvL + 9, LvL + 4, LvL + 2, LvL)
{
}