//  File Name:  dragon.cpp

#include "rpg_lib.hpp"

Dragon::Dragon(const std::string& MyName, int LvL)
    : Monster(MyName, LvL + 8, LvL + 10, LvL + 2, LvL + 2, LvL)
{
}