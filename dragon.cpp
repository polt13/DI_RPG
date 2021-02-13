//  File Name:  dragon.cpp

#include "rpg_lib.hpp"

Dragon::Dragon(const std::string& MyName, int LvL)
    : Monster(MyName, LvL + 5, LvL + 7, LvL + 2, LvL + 2, LvL)
{
}