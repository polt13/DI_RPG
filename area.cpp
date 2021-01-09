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
    std::vector<Monster*> Enemies(3);
    for (auto i = 1; i <= 3; i++) {
        auto whichMonster = std::rand() % 60;
        if (whichMonster > 50) {
            Enemies.push_back(new Dragon("Vaggelis"));
        } else if (whichMonster > 25) {
            Enemies.push_back(new Exoskeleton("Iakovos"));
        } else
            Enemies.push_back(new Spirit("Kekw"));
    }

    fight(Enemies);
}

void common::fight(std::vector<Monster*>& enemies)
{
    auto rounds = 0;
    while (end_fight(enemies) == false) {
        char option {};
        do {
            std::cin.clear();
            std::cin.ignore(500, '\n');
            std::cout << "I for inventory, A for attack";
            std::cin >> option;

        } while (option != 'i' && option != 'I' && option != 'a' && option != 'A');
    }
}

void common::displayStatus(const std::vector<Monster*>& enemies) const
{
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        (*it)->print();
    }
    std::cout << std::endl;
    for (auto it = squad.begin(); it != squad.end(); ++it) {
        (*it)->print();
    }
}

bool common::end_fight(const std::vector<Monster*>& enemies)
{
    //check if all heroes/monsters are dead
    bool heroes_dead = false, monsters_dead = false;
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        if ((*it)->get_hp() != 0) {
            monsters_dead = false;
        }
    }

    for (auto it = squad.begin(); it != squad.end(); ++it) {
        if ((*it)->get_hp() != 0) {
            heroes_dead = false;
        }
    }
    displayStatus(enemies);
    if (heroes_dead == true && monsters_dead == false) {
        std::cout << "Game Over!\n";
        return true;
    } else if (heroes_dead == false && monsters_dead == true) {
        std::cout << "Heroes win!\n";
        for (auto it = squad.begin(); it != squad.end(); ++it) {
            //?(*it)->get_xp()
        }
        return true;
    }

    return false; //none of the two sides are done
}

void inaccessible::print() const
{
    std::cout << " # ";
}

void inaccessible::move(std::vector<Hero*>& squad)
{
    std::cout << "inaccessible block: can't move here.\n";
}
