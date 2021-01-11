#include "rpg_lib.hpp"
market::market()
{
    long int item_count = std::rand() % 4 + 1;
    for (int i = 1; i <= item_count; ++i) { //ADD RANDOM ITEMS
        potionStock.push_back(new Potion("Item", std::rand() % 10, 5, potionType::HP));
        spellStock.push_back(new FireSpell("Potion", std::rand() % 10, 1, 2, 3, 4, 5));
        weaponStock.push_back(new Weapon("Weapon", std::rand() % 10, 1, 2, false));
        armorStock.push_back(new Armor("Armor", 1, 2, 3));
    }
}

void market::purchase(Hero& h)
{

    std::string option;
    std::cout << "W for Weapon, A for Armor, P for Potion, S for Spells";
    while (!(std::cin >> option) || (option != "A" && option != "W" && option != "S" && option != "P")) {
        std::cout << "BAD_INPUT\n";
        std::cin.clear();
        std::cin.ignore(500, '\n');
        std::cout << "W for Weapon, A for Armor, P for Potion, S for Spells";
    }

    std::cin.clear();
    std::cin.ignore(500, '\n');
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
    std::cout << " Potions ";
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
            std::cout << "I for inventory, A for attack, D";
            std::cin >> option;

        } while (option != 'i' && option != 'I' && option != 'a' && option != 'A');
    }
}

void common::displayStats(const std::vector<Monster*>& enemies) const
{
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        (*it)->displayStats();
    }
    std::cout << std::endl;
    for (auto it = squad.begin(); it != squad.end(); ++it) {
        (*it)->displayStats();
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
    displayStats(enemies);
    if (heroes_dead == true && monsters_dead == false) {
        std::cout << "Game Over!\n";
        return true;
    } else if (heroes_dead == false && monsters_dead == true) {
        std::cout << "Heroes win!\n";
        for (auto it = squad.begin(); it != squad.end(); ++it) {
            (*it)->set_xp((*it)->get_max_xp() / 4); //get 1/4th of XPmax
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
