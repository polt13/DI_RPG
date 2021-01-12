set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g3 -fsanitize=address")
project(DI_RPG)
add_executable(DI_RPG dragon.cpp exoskeleton.cpp hero.cpp item.cpp game.cpp living.cpp main.cpp monster.cpp paladin.cpp area.cpp sorcerer.cpp spirit.cpp warrior.cpp rpg_lib.hpp)
target_compile_options (DI_RPG PRIVATE -g3 -fsanitize=address -std=c++11)
