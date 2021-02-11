#include "rpg_lib.hpp"
#include <iomanip>

Market::Market(const std::vector<Weapon*>& AllWeapons, const std::vector<Armor*>& AllArmors, const std::vector<Potion*>& AllPotions, const std::vector<Spell*>& AllSpells)
    : size(5)
    , Block(blockType::MARKET)

{
    std::cout << (int)Btype << '\n';
    //from universal item pool make market
    for (int i = 1; i <= size; i++) {
        int index;
        index = (std::rand() % AllWeapons.size());
        weapons.push_back(AllWeapons[index]);
        index = (std::rand() % AllArmors.size());
        armors.push_back(AllArmors[index]);
        index = (std::rand() % AllPotions.size());
        potions.push_back(AllPotions[index]);
        index = (std::rand() % AllSpells.size());
        spells.push_back(AllSpells[index]);
    }
}

void Market::DisplayItems(std::string itype) const
{
    int index = 1;
    if (itype == "Weapons")
        for (const auto& w : weapons) {
            std::cout << "[ " << index++ << " ] ";
            w->print();
        }
    else if (itype == "Armors")
        for (const auto& a : armors) {
            std::cout << "[ " << index++ << " ] ";
            a->print();
        }
    else if (itype == "Potions")
        for (const auto& p : potions) {
            std::cout << "[ " << index++ << " ] ";
            p->print();
        }
    else
        for (const auto& s : spells) {
            std::cout << "[ " << index++ << " ] ";
            s->print();
        }
}

void Market::buy(Hero* MyHero, std::string type, int index)
{
    if (type == "Weapon") {
        if (weapons[index]->getPrice() <= MyHero->getMoney()) {
            std::cout << "\n\n";
            std::cout << "\tPurchased '" << weapons[index]->get_name() << "' Weapon for " << MyHero->get_name() << "\n";
            MyHero->buy(weapons[index]);
            weapons.erase(weapons.begin() + index);
            return;
        }
        std::cout << "\n\n";
        std::cout << "\tNot enough money\n";
    } else if (type == "Armor") {
        if (armors[index]->getPrice() <= MyHero->getMoney()) {
            std::cout << "\n\n";
            std::cout << "\tPurchased '" << armors[index]->get_name() << "' Armor for " << MyHero->get_name() << "\n";
            MyHero->buy(armors[index]);
            armors.erase(armors.begin() + index);
            return;
        }
        std::cout << "\n\n";
        std::cout << "\tNot enough money\n";
    } else if (type == "Potion") {
        if (potions[index]->getPrice() <= MyHero->getMoney()) {
            std::cout << "\n\n";
            std::cout << "\tPurchased '" << potions[index]->get_name() << "' Potion for " << MyHero->get_name() << "\n";
            MyHero->buy(potions[index]);
            potions.erase(potions.begin() + index);
            return;
        }
        std::cout << "\n\n";
        std::cout << "\tNot enough money\n";
    } else {
        if (spells[index]->getPrice() <= MyHero->getMoney()) {
            std::cout << "\n\n";
            std::cout << "\tPurchased '" << spells[index]->get_name() << "' Spell for " << MyHero->get_name() << "\n";
            MyHero->buy(spells[index]);
            spells.erase(spells.begin() + index);
            return;
        }
        std::cout << "\n\n";
        std::cout << "\tNot enough money\n";
    }
}

void Market::sell(Weapon* MyWeapon)
{
    weapons.push_back(MyWeapon);
}

void Market::sell(Armor* MyArmor)
{
    armors.push_back(MyArmor);
}

void Market::sell(Potion* MyPotion)
{
    potions.push_back(MyPotion);
}

void Market::sell(Spell* MySpell)
{
    spells.push_back(MySpell);
}

Block::Block(blockType btype)
    : Btype(btype)

{
}

blockType Block::get_type() const
{
    return Btype;
}

//no market in common
Common::Common()
    : Block(blockType::COMMON)
{
}

void Common::move(std::vector<Hero*>& toMove)
{
    Squad.insert(Squad.begin(), toMove.begin(), toMove.end()); //copy heroes to new location (this common block)
    toMove.clear(); //empty previous block
    if (std::rand() % 100 > 50) {
        std::cout << "\n\n";
        std::cout << "\tRandom encounter!\n";
        interact_with();
    }
}
void Common::print() const
{
    if (Squad.empty())

        std::cout << " H "; //heroes at this block
    else
        std::cout << " ";
}

void Common::interact_with()
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

    //after battle is done cleanup remaining monsters (if they won)//
    for (auto e : Enemies)
        delete e;
}

void Common::fight(std::vector<Monster*>& enemies)
{

    while (end_fight(enemies) == false) { //checks if condition to finish battle are met
        //round starts here
        auto whoAttacks = 0;
        auto whichMonsterAttacks = 0;
        char option = 0;
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
            while (!(std::cin >> HeroPick) || HeroPick > Squad.size() - 1) {
                std::cout << "Not a valid pick\n";
                Game::clearbuffer();
            }
            Squad[HeroPick]->checkInventory();
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
                Squad[HeroPick]->use(whichItem); //use on the hero itself
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

                Squad[HeroPick]->castSpell(enemies[enemyTarget], whichItem);
                if (enemies[enemyTarget]->get_hp() == 0) {
                    delete enemies[enemyTarget]; //if monster dead after attack remove it
                    enemies.erase(enemies.begin() + enemyTarget);
                }
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
            std::cout << Squad[whoAttacks]->get_name() << " attacks: \n";
            while (!(std::cin >> enemy_at) || (enemy_at > enemies.size() - 1)) {
                std::cout << "Invalid index\n";
            }
            Squad[whoAttacks++]->attack(enemies[enemy_at]); //attack and go to next person
            if (enemies[enemy_at]->get_hp() == 0) {
                delete enemies[enemy_at]; //if monster dead after attack remove it
                enemies.erase(enemies.begin() + enemy_at);
            }
            if (whoAttacks > Squad.size() - 1) //circle around players
                whoAttacks = 0;
            int heroTarget = std::rand() % Squad.size(); //randomly pick hero target for monster AI
            std::cout << enemies[whichMonsterAttacks]->get_name() << " attacks " << Squad[heroTarget]->get_name() << '\n';
            enemies[whichMonsterAttacks]->attack(Squad[heroTarget]);
        }

        for (auto h : Squad) {
            h->regenHP();
            h->regenMP();
        }
        for (auto m : enemies) {
            m->regenHP();
        }
        end_round(enemies);
        //round ends here
    }
    bool all_dead = true;
    for (auto h : Squad) { //find if all heroes dead
        if (h->get_hp() != 0) {
            all_dead = false;
            h->set_xp(enemies[0]->getLevel() * 5); //get xp based on level of enemy
            h->addMoney(enemies[0]->getLevel() * 3); //get money based on level of enemy
        }
    }
    if (all_dead == false)
        return; //not all heroes dead

    //if reached here -- all heroes are dead -- revive them with some HP and cost half the money
    for (auto h : Squad) {
        h->moneyLoss();
        //revive with some HP
        h->revive();
    }
    std::cout << "BATTLE LOST!\n";
    return;
}

void Common::end_round(std::vector<Monster*>& enemies)
{
    for (auto m : enemies)
        m->finish_round(); //checks when it's time to remove an effect
}

void Common::displayStats(const std::vector<Monster*>& enemies) const
{
    for (const auto m : enemies) {
        m->displayStats();
    }
    std::cout << std::endl;
    for (const auto h : Squad) {
        h->displayStats();
    }
}

bool Common::end_fight(const std::vector<Monster*>& enemies)
{
    //check if all heroes/monsters are dead
    bool heroes_dead = false, monsters_dead = false;
    for (const auto monster : enemies) {
        if (monster->get_hp() != 0)
            monsters_dead = false;
    }

    for (const auto h : Squad) {
        if (h->get_hp() != 0)
            heroes_dead = false;
    }
    displayStats(enemies);
    if (heroes_dead == true && monsters_dead == false) {
        std::cout << " All heroes have fainted\n";
        return true;
    } else if (heroes_dead == false && monsters_dead == true) {
        std::cout << " Heroes win! \n";
        return true;
    }

    return false; //none of the two sides are done
}

Inaccessible::Inaccessible()
    : Block(blockType::INACCESSIBLE)
{
    //
}

void Inaccessible::move(std::vector<Hero*>& toMove)
{
    interact_with();
}

void Inaccessible::interact_with()
{
    std::cout << "\n\n"
              << " This block is inaccessible\n";
}

void Inaccessible::print() const
{
    std::cout << " # ";
}

void Market::move(std::vector<Hero*>& toMove)
{
    Squad.insert(Squad.begin(), toMove.begin(), toMove.end()); //copy heroes to new location (this common block)
    toMove.clear();
    interact_with();
}

void Market::print() const
{

    if (Squad.empty())

        std::cout << " H-M "; //heroes at market block
    else
        std::cout << " M ";
}

void Market::interact_with()
{
    std::cout << " View market with Hero:\n";
    int hero;
    while (!(std::cin >> hero) || hero > Squad.size() - 1) {
        std::cout << "BAD INPUT\n";
    }
    Menu(Squad[hero]);
}

void Market::Menu(Hero* h)
{
    int input;
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
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << std::endl;

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > 2) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 2)\n";
        Game::clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }
    Game::clearbuffer();
    while (input != 0) {
        switch (input) {
        case 1:
            BuyMenu(h);
            break;
        case 2:
            SellMenu(h);
            break;
        }
    }
    std::cout << "Exiting Market..\n";
}

void Market::BuyMenu(Hero* h)
{
    int input;
    int index;
    Game::clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    Game::clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(34) << "=== Buy Menu ===" << std::setw(29) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "[ 1 ]\tWeapons" << std::setw(40) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 2 ]\tArmors" << std::setw(41) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "[ 3 ]\tPotions" << std::setw(40) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 4 ]\tSpells" << std::setw(41) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    //std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    do {
        while (!(std::cin >> input) || input < 0 || input > 4) {
            std::cout << "\n";
            std::cout << std::setw(50) << "Invalid input (Must be: 0 - 4)\n";
            Game::clearbuffer();
            std::cout << std::setw(37) << "Input: ";
        }
        Game::clearbuffer();
        std::cout << " Which item would you like?\n";
        while (!(std::cin >> index) || index < 0) {
            std::cout << "Bad index\n";
        }
        switch (input) {
        case 1:
            if (index > weapons.size() - 1) {
                std::cout << " There is no such weapon\n";
            } else {
                buy(h, "Weapons", index);
            }
            break;
        case 2:
            if (index > armors.size() - 1) {
                std::cout << " There is no such armor\n";
            } else {
                buy(h, "Armors", index);
            }
            break;
        case 3:
            if (index > potions.size() - 1) {
                std::cout << "There is no such potion\n";
            } else {
                buy(h, "Potions", index);
            }
            break;
        case 4:
            if (index > spells.size() - 1) {
                std::cout << "There is no such spell\n";
            } else {
                buy(h, "Spells", index);
            }
            break;
        }
    } while (input != 0);
}

void Market::SellMenu(Hero* h)
{
    int input;
    Game::clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    Game::clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(35) << "=== Sell Menu ===" << std::setw(28) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "[ 1 ]\tWeapons" << std::setw(40) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 2 ]\tArmors" << std::setw(41) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "[ 3 ]\tPotions" << std::setw(40) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 4 ]\tSpells" << std::setw(41) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 5 ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    //std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";
    do {
        while (!(std::cin >> input) || input < 0 || input > 5) {
            std::cout << "\n";
            std::cout << std::setw(50) << "Invalid input (Must be: 0 - 5)\n";
            Game::clearbuffer();
            std::cout << std::setw(37) << "Input: ";
        }
        int index;
        std::cout << " Sell which item? (index from 0)\n";
        while (!(std::cin >> index)) {
            std::cout << "BAD INPUT\n";
        }
        Game::clearbuffer();
        h->checkInventory();

        switch (input) {
        case 1:
            h->sell(this, "Weapon", index);
            break;
        case 2:

            h->sell(this, "Armor", index);
            break;
        case 3:

            h->sell(this, "Potion", index);
            break;
        case 4:

            h->sell(this, "Potion", index);
            break;
        }
    } while (input != 5);
}