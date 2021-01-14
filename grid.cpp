#include "rpg_lib.hpp"
#include <chrono>
#include <thread>
Grid::Grid()
{
    std::cout << "CONSTRUCTOR!!\n";
    std::cout << grid.size() << '\n';
    int marketcount {};
    int blockcount {};
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

Grid::~Grid()
{
    for (auto p : grid) {
        delete p;
    }
}