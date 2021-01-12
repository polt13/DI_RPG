#include "rpg_lib.hpp"
market::market()
{
    int itemcount = std::rand() % 4 + 1;
    for (int i = 1; i <= itemcount; ++i) { //ADD RANDOM ITEMS
        potions.push_back(new Potion("Item", std::rand() % 10, 5, potionType::HP));
        spells.push_back(new FireSpell("Potion", std::rand() % 10, 1, 2, 3, 4, 5));
        weapons.push_back(new Weapon("Weapon", std::rand() % 10, 1, 2, false));
        armors.push_back(new Armor("Armor", 1, 2, 3));
    }
}

void market::interact(Hero& h)
{
    std::string op;
    std::cout << "Welcome. B to buy, S to sell, E to exit";
    std::getline(std::cin, op);
    if (op.size() < 1) {
        std::cout << "BAD_IN";
        Menu::BUFFERCLR();
        return;
    }
    if (op.size() == 1) { //regardless of input, if its length is one,
        // exit
        if (op[0] != 'S' && op[0] != 'B') {
            std::cout << "Goodbye!\n";
            return;
        }
    }

    if (op[0] == 'B') {
        int index {};
        std::cout << "Format is: {type}{item_index}";
        while (std::getline(std::cin, op)) {
            switch (op[0]) {
            case 'w':
                index = op[1] - '0';
                if (index < 0 || (index > weapons.size() - 1)) {
                    std::cout << "No such weapon\n";
                    return;
                }
                h.buy(weapons[index]);
                weapons.erase(weapons.begin() + index);
                break;
            case 'a':
                index = op[1] - '0';
                if (index < 0 || (index > armors.size() - 1)) {
                    std::cout << "No such armor\n";
                    return;
                }
                h.buy(armors[index]);
                armors.erase(armors.begin() + index);
                break;
            case 's':
                index = op[1] - '0';
                if (index < 0 || (index > spells.size() - 1)) {
                    std::cout << "No such spell\n";
                    return;
                }
                h.buy(spells[index]);
                spells.erase(spells.begin() + index);
                break;
            case 'p':
                index = op[1] - '0';
                if (index < 0 || (index > potions.size() - 1)) {
                    std::cout << "No such potion\n";
                    return;
                }
                h.buy(potions[index]);
                potions.erase(potions.begin() + index);
                break;
            default:
                std::cout << "Goodbye!\n";
                return;
            }
        }
    } else if (op[0] == 'S') {
        h.checkInventory();
        h.sell(*this);
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
    Menu::BUFFERCLR();
}

void market::display()
{
    std::cout << "Welcome!\n";
    unsigned int itemCount = 0;
    std::cout << "\nWeapons:\n";
    for (const auto& w : weapons) {
        std::cout << itemCount++ << ". ";
        w->print();
        std::cout << '\n';
    }
    itemCount = 0;
    std::cout << "\nArmors:\n";
    for (const auto& a : armors) {
        std::cout << itemCount++ << ". ";
        a->print();
        std::cout << '\n';
    }
    itemCount = 0;
    std::cout << "\nSpells:\n";
    for (const auto& s : spells) {
        std::cout << itemCount++ << ". ";
        s->print();
        std::cout << '\n';
    }
    itemCount = 0;
    std::cout << "\nPotions:\n";
    for (const auto& p : potions) {
        std::cout << itemCount++ << ". ";
        p->print();
        std::cout << '\n';
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

//////////add to inv of market sold item from hero //////////////////
void market::acquire(Potion* p)
{
    potions.push_back(p);
}
void market::acquire(Armor* a)
{
    armors.push_back(a);
}
void market::acquire(Weapon* w)
{
    weapons.push_back(w);
}
void market::acquire(Spell* s)
{
    spells.push_back(s);
}