//  File Name:  spirit.cpp

#include "rpg_lib.hpp"

Spirit::Spirit(const std::string& MyName, int LvL)
    : Monster(MyName, LvL + 5, LvL + 6, LvL + 2, LvL + 4, LvL)
{
}