#include "rpg_lib.hpp"
#include <iomanip>
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

/*void market::DisplayItems(std::string itype) const
{
    if (itype == "Weapons")
        for (const auto& w : weapons)
            w->print();
    else if (itype == "Armors")
        for (const auto& a : armors)
            a->print();
    else if (itype == "Potions")
        for (const auto& p : potions)
            p->print();
    else
        for (const auto& s : spells)
            s->print();
}

int market::vector_count(std::string num) const
{
    if (itype == "Weapons")
        return weapons.size();
    else if (itype == "Armors")
        return armors.size();
    else if (itype == "Potions")
        return potions.size();
    else
        return spells.size();
}

Weapon* market::purchase(Hero* MyHero, int num)
{
    Weapon* temp = weapons[num];
    weapons.erase(weapons.begin() + num);
    return temp;
}

Armor* market::purchase(Hero* MyHero, int num)
{
    Armor* temp = armors[num];
    armors.erase(armors.begin() + num);
    return temp;
}

Potion* market::purchase(Hero* MyHero, int num)
{
    Potion* temp = potions[num];
    potions.erase(potions.begin() + num);
    return temp;
}

Spell* market::purchase(Hero* MyHero, int num)
{
    Spell* temp = spells[num];
    spells.erase(spells.begin() + num);
    return temp;
}*/

void market::menu()
{
    Game::clearscreen();
    std::cout << "\n\n\tWelcome.." << std::endl;
    Game::clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(34) << "=== Market Menu ===" << std::setw(29) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(16) << "[ 1 ]\tBuy" << std::setw(44) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 2 ]\tSell" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 3 ]\tDisplay Map" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 4 ]\tTravel" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";
}

void market::visit(Hero& h)
{
    while (true) {
        menu();
        int input {};
        std::cin >> input;
        switch (input) {
        case 1:
            Game::clearbuffer();
            buyMenu(h);
            break;

        case 2:
            Game::clearbuffer();
            sellMenu(h);
            break;

        default:
            std::cout << "Exiting market..\n";
            return;
        }
    }
}

void market::buyMenu(Hero& h)
{

    int index {};
    std::string op;
    //format e.g. w2 -- Weapon 2
    std::cout << " Buy format is: {type}{index} where type: w,a,p,s\n";
    while (std::getline(std::cin, op)) {
        switch (op[0]) {
        case 'w':
            index = op[1] - '0';
            if (index < 0 || (index > weapons.size() - 1)) {
                std::cout << "No such weapon\n";
                return;
            }

            if (weapons[index]->getPrice() > h.getMoney()) {
                std::cout << "Not enough money\n";
                continue;
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

            if (armors[index]->getPrice() > h.getMoney()) {
                std::cout << "Not enough money\n";
                continue;
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
            if (spells[index]->getPrice() > h.getMoney()) {
                std::cout << "Not enough money\n";
                continue;
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
            if (potions[index]->getPrice() > h.getMoney()) {
                std::cout << "Not enough money\n";
                continue;
            }
            h.buy(potions[index]);
            potions.erase(potions.begin() + index);
            break;
        default:
            std::cout << "Goodbye!\n";
            return;
        }
    }
}

void market::sellMenu(Hero& h)
{
    h.checkInventory();
    h.sell(*this);
}

void market::move(std::vector<Hero*>& toMove)
{
    char option;
    squad.insert(squad.begin(), toMove.begin(), toMove.end()); //copy heroes to new location
    toMove.clear(); //empty previous block
    std::cout << "Visit market? y/n";
    if (std::cin >> option) {
        if (option == 'y') {
            Game::clearbuffer();
            visit(*squad[0]);
            return;
        }
    }
    Game::clearbuffer();
}

void market::displayStock()
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

void market::printBlock() const
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
    squad.insert(squad.begin(), toMove.begin(), toMove.end()); //copy heroes to new location
    toMove.clear(); //empty previous block
    if (std::rand() % 100 > 50) {
        std::cout << " Random encounter!\n";
        fight_start();
    }
}

void common::printBlock() const
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
    for (auto& e : Enemies) {
        delete e;
    }
}

void common::fight(std::vector<Monster*>& enemies)
{
    auto rounds = 0;
    while (end_fight(enemies) == false) {
        auto whoAttacks = 0;
        auto whichMonsterAttacks = 0;
        char option {};
        do {
            Game::clearbuffer();
            std::cout << "I for inventory, A for attack, D for stats display";
            std::cin >> option;

        } while (option != 'i' && option != 'I' && option != 'a' && option != 'A' && option != 'D' && option != 'd');
        int pick;
        if (option == 'D' || option == 'd') {
            displayStats(enemies);
            continue;
        } else if (option == 'i' || option == 'I') {

            std::cout << "Check inventory of character:\n";
            int HeroPick;
            while (!(std::cin >> HeroPick) || HeroPick > squad.size() - 1) {
                std::cout << "Not a valid pick\n";
                Game::clearbuffer();
            }
            squad[HeroPick]->checkInventory();
            std::cout << "1 for Potion, 2 for Spellcast, 3 to go back";
            while (!(std::cin >> pick) || option > 3 || option < 1) {
                std::cout << "Not a valid pick\n";
                Game::clearbuffer();
            }
            int whichItem;
            int who;
            switch (pick) {
            case 1:
                std::cout << "Use which potion?\n";
                while (!(std::cin >> whichItem)) {
                    std::cout << "Not a valid pick\n";
                    Game::clearbuffer();
                }
                squad[HeroPick]->use(whichItem); //use on the hero itself
                Game::clearbuffer();
                break;
            case 2:
                int enemyTarget;
                int whichSpell;
                std::cout << "Use which spell?\n";
                while (!(std::cin >> whichSpell)) {
                    std::cout << "Not a valid pick\n";
                    Game::clearbuffer();
                }
                std::cout << " Use spell on: \n";
                while (!(std::cin >> enemyTarget) || enemyTarget < 0 || (enemyTarget > enemies.size() - 1)) {
                    std::cout << "Not a valid pick\n";
                    Game::clearbuffer();
                }

                squad[HeroPick]->castSpell(enemies[enemyTarget], whichItem);
                Game::clearbuffer();
                break;
            case 3:
                Game::clearbuffer();
                std::cout << "Exiting..\n";
                return;
            }
            continue;
        } else {
            //circular rotation --- who attacks
            int enemy_at {};
            std::cout << squad[whoAttacks]->get_name() << " attacks: \n";
            while (!(std::cin >> enemy_at) || (enemy_at > enemies.size() - 1)) {
                std::cout << "Invalid index\n";
            }
            squad[whoAttacks++]->attack(enemies[enemy_at]); //attack and go to next person
            if (whoAttacks > squad.size() - 1)
                whoAttacks = 0;
            int heroTarget = std::rand() % squad.size();
            std::cout << enemies[whichMonsterAttacks]->get_name() << " attacks " << squad[heroTarget]->get_name() << '\n';
            enemies[whichMonsterAttacks]->attack(squad[heroTarget]);
        }

        for (auto& h : squad) {
            h->regenHP();
            h->regenMP();
        }
        for (auto& m : enemies) {
            m->regenHP();
        }
        end_round(enemies);
        ++rounds;
    }
    bool all_dead = true;
    for (const auto& h : squad) { //find if all heroes dead
        if (h->get_hp() != 0) {
            all_dead = false;
            for (auto& h : squad) {
                h->set_xp(enemies[0]->getLevel() * 5); //get xp based on level of enemy
                h->addMoney(enemies[0]->getLevel() * 3); //get money based on level of enemy
            }
        }
    }

    //if reached here -- all heroes are dead -- revive them with some HP and cost half the money
    for (auto& h : squad) {
        h->moneyLoss();
        //revive with some HP
        h->revive();
    }
    std::cout << "BATTLE LOST!\n";
    return;
}

void common::end_round(std::vector<Monster*>& enemies)
{
    for (auto m : enemies) {
        m->finish_round(); //checks when it's time to remove an effect
    }
}

void common::displayStats(const std::vector<Monster*>& enemies) const
{
    for (const auto& m : enemies) {
        m->displayStats();
    }
    std::cout << std::endl;
    for (const auto& h : squad) {
        h->displayStats();
    }
}

bool common::end_fight(const std::vector<Monster*>& enemies)
{
    //check if all heroes/monsters are dead
    bool heroes_dead = false, monsters_dead = false;
    for (const auto& monster : enemies) {
        if (monster->get_hp() != 0) {
            monsters_dead = false;
        }
    }

    for (const auto& h : squad) {
        if (h->get_hp() != 0) {
            heroes_dead = false;
        }
    }
    displayStats(enemies);
    if (heroes_dead == true && monsters_dead == false) {
        std::cout << "Game Over!\n";
        return true;
    } else if (heroes_dead == false && monsters_dead == true) {
        std::cout << "Heroes win!\n";
        return true;
    }

    return false; //none of the two sides are done
}

void inaccessible::printBlock() const
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

market::~market()
{
    for (auto& w : weapons)
        delete w;
    for (auto& p : potions)
        delete p;
    for (auto& s : spells)
        delete s;
    for (auto& a : armors)
        delete a;
}