#include "rpg_lib.hpp"
market::market()
{
    long int item_count = std::rand() % 6 + 5;
    for (int i = 1; i <= item_count; ++i) {
        items.push_back(new Potion("Item", rand() % 10, 5, cstats::HP));
    }
}

void market::purchase(Hero& h, int whichItemToBuy)
{
    if (whichItemToBuy < 0 || whichItemToBuy > (items.size() - 1))
        return;
    if (items[whichItemToBuy]->getPrice() <= h.getMoney()) {
        h.addToInv(items[whichItemToBuy]);
        items.erase(items.begin() + whichItemToBuy); //remove from shop
    } else {
        std::cout << "not enough money\n";
        return;
    }
}

void market::move(std::vector<Hero*>& toMove)
{
    char option;
    std::copy(toMove.begin(), toMove.end(), squad.begin()); //copy heroes to new location
    toMove.clear(); //empty previous block
    std::cout << "display market? y/n";
    if (std::cin >> option) {
        if (option == 'y') {
            display();
        }
    }
    std::cin.clear(); //reset possible error flag
    std::cin.ignore(500, '\n'); //clear buffer
}

void market::display()
{
    for (auto it = items.begin(); it != items.end(); ++it) {
        (*it)->print();
    }
}

void market::print() const
{
    //heroes at the market block
    if (squad.empty() == false) {
        std::cout << " H -- M ";
        return;
    }
    std::cout << " M ";
}

void common::move(std::vector<Hero*>& toMove)
{
    std::copy(toMove.begin(), toMove.end(), squad.begin());
    toMove.clear();
    if (std::rand() % 100 > 50) {
        std::cout << " Random encounter!\n";
        fight_start();
    }
}

void common::print() const
{
    if (squad.empty() == false) {
        std::cout << " H ";
        return;
    }
    std::cout << "   ";
}

void common::fight_start()
{
    //generate enemy monsters
}

void inaccessible::print() const
{
    std::cout << " # ";
}

void inaccessible::move(std::vector<Hero*>& squad)
{
    std::cout << "inaccessible block: can't move here.\n";
}