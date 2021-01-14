#include "rpg_lib.hpp"

class Grid {
private:
    //5x5 grid
    std::array<std::array<block*, 5>, 5> grid;

public:
    Grid();
};