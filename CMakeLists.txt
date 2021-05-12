set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
project(DI_RPG)
add_executable(DI_RPG dragon.cpp exoskeleton.cpp hero.cpp item.cpp game.cpp living.cpp main.cpp monster.cpp paladin.cpp area.cpp sorcerer.cpp spirit.cpp warrior.cpp rpg_lib.hpp)

