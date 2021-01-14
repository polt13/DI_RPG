#include "rpg_lib.hpp"
#include <chrono>
#include <thread>
Grid::Grid()
{
    hero_pos = 0;

    for (auto row = 0; row < grid.size(); row++) {
        for (auto col = 0; col < grid[row].size(); col++) {
            if (row == (2 * col) + 1)
                grid[row][col] = new market;
            else if (row == col + 3)
                grid[row][col] = new inaccessible();
            else
                grid[row][col]
                    = new common();
        }
    }
}

void Grid::displayMap()
{
    Game::clearscreen();
    for (auto r = 0; r < grid.size(); ++r) {
        for (auto c = 0; c < grid[r].size(); ++c) {

            std::cout << "|";
            grid[r][c]->printBlock();
        }
    }
    std::cout << "|";
    std::cout << '\n';
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
    for (auto r = 0; r < grid.size(); r++) {
        for (auto c = 0; c < grid[r].size(); c++)
            delete grid[r][c];
    }
}