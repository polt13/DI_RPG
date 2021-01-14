#include "rpg_lib.hpp"
#include <chrono>
#include <thread>
Grid::Grid()
{
    hero_pos = 0;

    for (auto block = 0; block < grid.size(); block++) {
        if (block == 11) {
            grid[block] = new market();
        } else
            grid[block] = new common();
    }
}

void Grid::displayMap()
{
    Game::clearscreen();
    auto printed = 0;
    for (auto r = 0; r < grid.size(); ++r) {
        std::cout << "|";
        grid[r]->printBlock();
        if (++printed == 5) {
            std::cout << "|";
            printed = 0;
            std::cout << '\n';
        }
    }
}

void Grid::move(std::string m)
{
    std::string dir;
    while (std::getline(std::cin, dir)) {
        if (dir == "up") {

        } else if (dir == "down") {

        } else if (dir == "left") {

        } else if (dir == "right") {
        }
    }
}

Grid::~Grid()
{
    for (auto p : grid) {
        delete p;
    }
}