#include "rpg_lib.hpp"
#include <chrono>
#include <iomanip>
#include <thread>

static bool spawned = false; //keep track of whether or not heroes spawned, to avoid immediately entering battle

Market::Market(const std::vector<Weapon*>& AllWeapons, const std::vector<Armor*>& AllArmors, const std::vector<Potion*>& AllPotions, const std::vector<Spell*>& AllSpells)
    : size(5)
    , Block(blockType::MARKET)

{
    //from universal item pool make market
    for (int i = 1; i <= size; i++) {
        int index = (std::rand() % AllWeapons.size());
        weapons.push_back(AllWeapons[index]);
        index = (std::rand() % AllArmors.size());
        armors.push_back(AllArmors[index]);
        index = (std::rand() % AllPotions.size());
        potions.push_back(AllPotions[index]);
        index = (std::rand() % AllSpells.size());
        spells.push_back(AllSpells[index]);
    }
}

void Market::DisplayItems(itemType itype) const
{
    int index = 1;
    if (itype == itemType::WEAPON) {
        for (const auto w : weapons) {
            std::cout << "[ " << index++ << " ] ";
            w->print();
        }
    } else if (itype == itemType::ARMOR) {
        for (const auto a : armors) {
            std::cout << "[ " << index++ << " ] ";
            a->print();
        }
    } else if (itype == itemType::POTION) {
        for (const auto p : potions) {
            std::cout << "[ " << index++ << " ] ";
            p->print();
        }
    } else
        for (const auto s : spells) {
            std::cout << "[ " << index++ << " ] ";
            s->print();
        }
}

void Market::buy(Hero* MyHero, itemType itype, int index)
{
    if (itype == itemType::WEAPON) {
        if (weapons[index]->getPrice() <= MyHero->getMoney()) {
            std::cout << "\n\n";
            std::cout << "\tPurchased " << weapons[index]->get_name() << " Weapon for " << MyHero->get_name() << "\n";
            MyHero->buy(weapons[index]);
            weapons.erase(weapons.begin() + index);
            return;
        } else {
            std::cout << "\n\n";
            std::cout << "\tNot enough money\n";
        }
    } else if (itype == itemType::ARMOR) {
        if (armors[index]->getPrice() <= MyHero->getMoney()) {
            std::cout << "\n\n";
            std::cout << "\tPurchased " << armors[index]->get_name() << " Armor for " << MyHero->get_name() << "\n";
            MyHero->buy(armors[index]);
            armors.erase(armors.begin() + index);
            return;
        } else {
            std::cout << "\n\n";
            std::cout << "\tNot enough money\n";
        }
    } else if (itype == itemType::POTION) {
        if (potions[index]->getPrice() <= MyHero->getMoney()) {
            std::cout << "\n\n";
            std::cout << "\tPurchased " << potions[index]->get_name() << " Potion for " << MyHero->get_name() << "\n";
            MyHero->buy(potions[index]);
            potions.erase(potions.begin() + index);
            return;
        } else {
            std::cout << "\n\n";
            std::cout << "\tNot enough money\n";
        }
    } else {
        if (spells[index]->getPrice() <= MyHero->getMoney()) {
            std::cout << "\n\n";
            std::cout << "\tPurchased " << spells[index]->get_name() << " Spell for " << MyHero->get_name() << "\n";
            MyHero->buy(spells[index]);
            spells.erase(spells.begin() + index);
            return;
        } else {
            std::cout << "\n\n";
            std::cout << "\tNot enough money\n";
        }
    }
}

void Market::acquire(Weapon* MyWeapon)
{
    weapons.push_back(MyWeapon);
}

void Market::acquire(Armor* MyArmor)
{
    armors.push_back(MyArmor);
}

void Market::acquire(Potion* MyPotion)
{
    potions.push_back(MyPotion);
}

void Market::acquire(Spell* MySpell)
{
    spells.push_back(MySpell);
}

Block::Block(blockType btype)
    : Btype(btype)

{
}

std::vector<Hero*>& Block::getSquad()
{
    return Squad; //get heroes from current block, so that they can move to next
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
    if (spawned == true) { //dont attempt to put in battle immediately after spawning
        if (std::rand() % 100 > 80) {
            std::cout << "\n\n";
            std::cout << "\t\t\tRandom encounter!\n\n";
            interact_with();
        }
    } else {
        spawned = true;
    }
}

void Common::print() const
{
    if (Squad.empty())

        std::cout << "     ";
    else
        std::cout << "  H  "; //heroes at this block
}

void Common::interact_with()
{
    //generate enemy monsters
    std::vector<Monster*> Enemies;
    std::string name;
    int dragon_count = 0, skel_count = 0, spirit_count = 0;
    int enemy_count = (std::rand() % 3) + 1;
    for (auto i = 1; i <= enemy_count; i++) {
        auto whichMonster = std::rand() % 60;
        if (whichMonster > 50) {
            name = "Dragon " + std::to_string(dragon_count++);
            Enemies.push_back(new Dragon(name));
        } else if (whichMonster > 25) {
            name = "Skeleton " + std::to_string(skel_count++);
            Enemies.push_back(new Exoskeleton(name));
        } else {
            name = "Spirit " + std::to_string(spirit_count++);
            Enemies.push_back(new Spirit(name));
        }
    }
    battle_status(Enemies);
    fight(Enemies);

    //after battle is done cleanup remaining monsters (if they won)//
    for (auto e : Enemies)
        delete e;
}

void Common::fight(std::vector<Monster*>& enemies)
{
    auto atk_hero = 0;
    auto enemy_lvl = enemies[0]->getLevel();

    while (end_fight(enemies) == false) { //checks if condition to finish battle are met
        //round starts here
        int option;
        do {

            std::cout << "\n\n1 to view battle status, 2 to view inventory, 3 to attack, 4 to escape\n\n";
            std::cin >> option;
            Game::clearbuffer();

        } while (option != 1 && option != 2 && option != 3 && option != 4);
        int pick;
        if (option == 1) {
            battle_status(enemies);
            continue;
        } else if (option == 2) {

            std::cout << "Check inventory of character? [ 0 to " << Squad.size() - 1 << "]\n";
            int HeroPick;
            while (!(std::cin >> HeroPick) || HeroPick > Squad.size() - 1) {
                std::cout << "Not a valid pick\n";
                Game::clearbuffer();
            }
            Squad[HeroPick]->checkInventory();
            std::cout << "1 for Potion, 2 for Spellcast, 3 to go back\n";
            while (!(std::cin >> pick) || option > 3 || option < 1) {
                std::cout << "Not a valid pick\n";
                Game::clearbuffer();
            }
            switch (pick) {
            case 1:
                int whichPotion;
                Squad[HeroPick]->DisplayItems(itemType::POTION);
                std::cout << "\nUse which potion?\n";
                while (!(std::cin >> whichPotion)) {
                    std::cout << "Not a valid pick\n";
                    Game::clearbuffer();
                }
                Squad[HeroPick]->use(whichPotion - 1); //use on the hero itself
                continue;
            case 2:
                int enemyTarget;
                int whichSpell;
                Squad[HeroPick]->DisplayItems(itemType::SPELL);
                std::cout << "\nUse which spell?\n";
                while (!(std::cin >> whichSpell)) {
                    std::cout << "Not a valid pick\n";
                }
                battle_status(enemies);
                std::cout << " Use spell on: [0 to "
                          << enemies.size() - 1 << "]\n";
                while (!(std::cin >> enemyTarget) || enemyTarget < 0 || (enemyTarget > enemies.size() - 1)) {
                    std::cout << "Not a valid pick\n";
                }
                Squad[HeroPick]->castSpell(enemies[enemyTarget], whichSpell - 1);
                if (enemies[enemyTarget]->get_hp() == 0) {
                    delete enemies[enemyTarget]; //if monster dead after attack remove it
                    enemies.erase(enemies.begin() + enemyTarget);
                }
                break;
            default:
                continue;
            }
        } else if (option == 3) {
            // init  combat
            //circular rotation --- who attacks
            int enemy_at;
            battle_status(enemies);
            std::cout << Squad[atk_hero]->get_name() << " attacks: [0 to " << enemies.size() - 1 << "]\n";
            while (!(std::cin >> enemy_at) || (enemy_at > enemies.size() - 1)) {
                std::cout << "No such enemy\n";
            }
            Squad[atk_hero++]->attack(enemies[enemy_at]); //attack and go to next hero
            if (enemies[enemy_at]->get_hp() == 0) {
                delete enemies[enemy_at]; //if monster dead after attack remove it from battle
                enemies.erase(enemies.begin() + enemy_at);
                if (enemies.size() == 0)
                    continue; //fight needs to end
            }
            if (atk_hero > Squad.size() - 1) //circle around players
                atk_hero = 0;
            auto atk_monster = std::rand() % enemies.size();
            auto heroTarget = std::rand() % Squad.size(); //randomly pick hero target for monster AI
            std::cout << enemies[atk_monster]->get_name() << " attacks " << Squad[heroTarget]->get_name() << '\n';
            enemies[atk_monster]->attack(Squad[heroTarget]);
        } else {
            std::cout << " Leave battle? [0 for No, 1 for Yes]\n";
            int escape;
            while (!(std::cin >> escape) || (escape != 0 && escape != 1)) {
                std::cout << "BAD ESCAPE!\n";
            }
            if (escape == 1)
                return;
            else
                continue;
        }

        for (auto h : Squad) {
            h->regenHP();
            h->regenMP();
        }
        for (auto e : enemies) {
            e->regenHP();
        }
        end_round(enemies);
        //round ends here
    }
    //after either monsters or heroes have died
    bool all_dead = true;
    for (auto h : Squad) { //find if all heroes dead
        if (h->get_hp() != 0) {
            all_dead = false;
            h->set_xp(enemy_lvl * 50); //get xp based on level of enemy
            h->addMoney(enemy_lvl * 30); //get money based on level of enemy
            std::cout << h->get_name() << " got " << enemy_lvl * 50 << "XP, " << enemy_lvl * 30 << " in gold!\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        } else {
            h->revive();
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        }
    }

    if (all_dead == false)
        return; //not all heroes dead
    else {
        //if reached here -- all heroes are dead -- reduce moneycount
        for (auto h : Squad)
            h->moneyLoss();
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }

    std::cout << "BATTLE LOST!\n";
}

void Common::end_round(std::vector<Monster*>& enemies)
{
    std::cout << "Round ends\n";
    for (auto e : enemies)
        e->finish_round(); //checks when it's time to remove an effect
}

void Common::battle_status(const std::vector<Monster*>& enemies) const
{
    for (const auto m : enemies) {
        m->displayStats();
        std::cout << "-- ";
    }
    std::cout << "\n\n";
    for (const auto h : Squad) {
        h->displayStats();
        std::cout << "-- ";
    }
    std::cout << std::endl;
}

bool Common::end_fight(const std::vector<Monster*>& enemies)
{
    //check if all heroes/monsters are dead
    bool heroes_dead = true, monsters_dead = false;
    if (enemies.size() == 0)
        monsters_dead = true;

    for (const auto h : Squad) {
        if (h->get_hp() != 0)
            heroes_dead = false; //at least one alive
    }

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
    std::cout << "  #  ";
}

void Market::move(std::vector<Hero*>& toMove)
{
    Squad.insert(Squad.begin(), toMove.begin(), toMove.end()); //copy heroes to new location (this common block)
    toMove.clear();
    //interact_with();
}

void Market::print() const
{

    if (Squad.empty())

        std::cout << "  M  "; //heroes at market block
    else
        std::cout << " H-M ";
}

void Market::interact_with()
{
    std::cout << "\tView market with Hero: [ 1 to " << Squad.size() << " ]\n";
    int hero;
    while (!(std::cin >> hero) || hero >= Squad.size() + 1 || hero <= 0) {
        std::cout << "\n";
        std::cout << "BAD INPUT\n";
        Game::clearbuffer();
        std::cout << "\tView market with Hero: [ 1 to " << Squad.size() << " ]\n";
    }
    Menu(Squad[hero - 1]);
}

void Market::Menu(Hero* h)
{
    int input;
    bool flag;
    do {
        Game::clearscreen();
        flag = false;

        std::cout << "\n\n\tWelcome.." << std::endl;
        std::cout << "\n\n\tYou've got " << h->getMoney() << " gold.\n\n";
        std::cout << "\n--------------------------------------------------\n";

        std::cout << "\n\n";
        std::cout << "\t=== Market Menu ===\n\n";
        std::cout << "\n--------------------------------------------------\n\n";
        std::cout << "\t[ 1 ]\tBuy\n";
        std::cout << "\n";
        std::cout << "\t[ 2 ]\tSell\n";
        std::cout << "\n";
        std::cout << "\t[ 0 ]\tExit\n";
        std::cout << "\n";
        std::cout << "--------------------------------------------------\n\n\n";
        std::cout << std::setw(37) << "Input: ";

        while (!(std::cin >> input) || input < 0 || input > 2) {
            std::cout << "\n";
            std::cout << std::setw(50) << "Invalid input (Must be: 1 - 2)\n";
            Game::clearbuffer();
            std::cout << std::setw(37) << "Input: ";
        }
        Game::clearbuffer();
        switch (input) {
        case 1:
            flag = BuyMenu(h);
            break;
        case 2:
            flag = SellMenu(h);
            break;
        case 0:
            flag = true;
            std::cout << "Exiting Market..\n";
            break;
        }
    } while (flag == false);
}

bool Market::BuyMenu(Hero* h)
{
    int input;
    int index;
    Game::clearscreen();

    std::cout << "\n\n";
    std::cout << "\t=== Buy Menu ===\n\n";
    std::cout << "\n--------------------------------------------------\n\n";
    std::cout << "\tWeapons:\n";
    DisplayItems(itemType::WEAPON);
    std::cout << "\n";
    std::cout << "\tArmors:\n";
    DisplayItems(itemType::ARMOR);
    std::cout << "\n";
    std::cout << "\tPotions:\n";
    DisplayItems(itemType::POTION);
    std::cout << "\n";
    std::cout << "\tSpells:\n";
    DisplayItems(itemType::SPELL);
    std::cout << "\n--------------------------------------------------\n\n";
    std::cout << "\t[ 1 ]\tWeapons\n";
    std::cout << "\n";
    std::cout << "\t[ 2 ]\tArmors\n";
    std::cout << "\n";
    std::cout << "\t[ 3 ]\tPotions\n";
    std::cout << "\n";
    std::cout << "\t[ 4 ]\tSpells\n";
    std::cout << "\n";
    std::cout << "\t[ 0 ]\tExit\n";
    std::cout << "\n";
    std::cout << "--------------------------------------------------\n\n\n";

    std::cout << std::setw(37) << "Pick category: ";

    while (!(std::cin >> input) || input < 0 || input > 4) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 4)\n";
        Game::clearbuffer();
        std::cout << std::setw(37) << "Pick category: ";
    }
    Game::clearbuffer();

    if (input == 0)
        return true;
    else {
        std::cout << "Select an Item: ";

        switch (input) {
        case 1:
            while (!(std::cin >> index) || index <= 0 || index >= weapons.size() + 1) {
                std::cout << "\n";
                std::cout << std::setw(50) << "Invalid input (Must be: 1 - " << weapons.size() << ")\n";
                Game::clearbuffer();
                std::cout << std::setw(37) << "What to buy: ";
            }
            buy(h, itemType::WEAPON, index - 1);
            break;
        case 2:
            while (!(std::cin >> index) || index <= 0 || index >= armors.size() + 1) {
                std::cout << "\n";
                std::cout << std::setw(50) << "Invalid input (Must be: 1 - " << armors.size() << ")\n";
                Game::clearbuffer();
                std::cout << std::setw(37) << "What to buy: ";
            }
            buy(h, itemType::ARMOR, index - 1);
            break;
        case 3:
            while (!(std::cin >> index) || index <= 0 || index >= potions.size() + 1) {
                std::cout << "\n";
                std::cout << std::setw(50) << "Invalid input (Must be: 1 - " << potions.size() << ")\n";
                Game::clearbuffer();
                std::cout << std::setw(37) << "What to buy: ";
            }
            buy(h, itemType::POTION, index - 1);
            break;
        case 4:
            while (!(std::cin >> index) || index <= 0 || index >= spells.size() + 1) {
                std::cout << "\n";
                std::cout << std::setw(50) << "Invalid input (Must be: 1 - " << spells.size() << ")\n";
                Game::clearbuffer();
                std::cout << std::setw(37) << "What to buy: ";
            }
            buy(h, itemType::SPELL, index - 1);
            break;
        }
    }
    return false;
}

bool Market::SellMenu(Hero* h)
{
    int input;
    int index;
    Game::clearscreen();

    std::cout << "\n\n";
    std::cout << "\t=== Sell Menu ===\n\n";
    std::cout << "\n--------------------------------------------------\n\n";
    std::cout << "\tWeapons:\n";
    h->DisplayItems(itemType::WEAPON);
    std::cout << "\n";
    std::cout << "\tArmors:\n";
    h->DisplayItems(itemType::ARMOR);
    std::cout << "\n";
    std::cout << "\tPotions:\n";
    h->DisplayItems(itemType::POTION);
    std::cout << "\n";
    std::cout << "\tSpells:\n";
    h->DisplayItems(itemType::SPELL);
    std::cout << "\n--------------------------------------------------\n\n";
    std::cout << "\t[ 1 ]\tWeapons\n";
    std::cout << "\n";
    std::cout << "\t[ 2 ]\tArmors\n";
    std::cout << "\n";
    std::cout << "\t[ 3 ]\tPotions\n";
    std::cout << "\n";
    std::cout << "\t[ 4 ]\tSpells\n";
    std::cout << "\n";
    std::cout << "\t[ 0 ]\tExit\n";
    std::cout << "\n";
    std::cout << "--------------------------------------------------\n\n\n";

    std::cout << std::setw(37) << "Pick category: ";

    while (!(std::cin >> input) || input < 0 || input > 4) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 4)\n";
        Game::clearbuffer();
        std::cout << std::setw(37) << "Pick category: ";
    }
    Game::clearbuffer();

    if (input == 0)
        return true;
    else {
        std::cout << "Sell which item? (index from 1)\n";

        switch (input) {
        case 1:
            if (h->inv_size(itemType::WEAPON) == 0) {
                std::cout << "There is nothing to sell\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                break;
            }
            while (!(std::cin >> index) || index <= 0 || index >= h->inv_size(itemType::WEAPON) + 1) {
                std::cout << "\n";
                std::cout << std::setw(50) << "Invalid input (Must be: 1 - " << h->inv_size(itemType::WEAPON) << ")\n";
                Game::clearbuffer();
                std::cout << std::setw(37) << "Sell which item? (index from 1)\n";
            }
            index--;
            h->sell(this, itemType::WEAPON, index); //sell to this(market)
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        case 2:
            if (h->inv_size(itemType::ARMOR) == 0) {
                std::cout << "There is nothing to sell\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                break;
            }
            while (!(std::cin >> index) || index <= 0 || index >= h->inv_size(itemType::ARMOR) + 1) {
                std::cout << "\n";
                std::cout << std::setw(50) << "Invalid input (Must be: 1 - " << h->inv_size(itemType::ARMOR) << ")\n";
                Game::clearbuffer();
                std::cout << std::setw(37) << "Sell which item? (index from 1)\n";
            }
            index--;
            h->sell(this, itemType::ARMOR, index);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        case 3:
            if (h->inv_size(itemType::POTION) == 0) {
                std::cout << "There is nothing to sell\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                break;
            }
            while (!(std::cin >> index) || index <= 0 || index >= h->inv_size(itemType::POTION) + 1) {
                std::cout << "\n";
                std::cout << std::setw(50) << "Invalid input (Must be: 1 - " << h->inv_size(itemType::POTION) << ")\n";
                Game::clearbuffer();
                std::cout << std::setw(37) << "Sell which item? (index from 1)\n";
            }
            index--;
            h->sell(this, itemType::POTION, index);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        case 4:
            if (h->inv_size(itemType::SPELL) == 0) {
                std::cout << "There is nothing to sell\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                break;
            }
            while (!(std::cin >> index) || index <= 0 || index >= h->inv_size(itemType::SPELL) + 1) {
                std::cout << "\n";
                std::cout << std::setw(50) << "Invalid input (Must be: 1 - " << h->inv_size(itemType::SPELL) << ")\n";
                Game::clearbuffer();
                std::cout << std::setw(37) << "Sell which item? (index from 1)\n";
            }
            index--;
            h->sell(this, itemType::SPELL, index);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        }
    }
    return false;
}