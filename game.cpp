#include "rpg_lib.hpp"
#include <chrono> //
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <thread> //  for sleep
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

Game::Game()
    : playing(true)
    , Dimension(8)
    , ActiveHero(0)
    , ActiveBlock_x(2)
    , ActiveBlock_y(2)
{
    //
}

Game::~Game()
{
    for (auto h : MyHeroes)
        delete h;
    for (auto w : AllWeapons)
        delete w;
    for (auto a : AllArmors)
        delete a;
    for (auto s : AllSpells)
        delete s;
    for (auto p : AllPotions)
        delete p;

    for(auto i = 0; i < Grid.size(); i++)
    {
        for (auto j = 0; j < Grid[i].size(); ++j)
        {
            delete Grid[i][j];
        }
    }
}

void Game::StartScreen()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "\n\n";
    std::cout << "\tWelcome to DI_RPG\n\n";
    std::cout << "\tPress ENTER to continue..." << std::endl;
    std::cin.get();
    clearscreen();
}

void Game::InitGame()
{
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();

    std::cout << "\n\n";

    InitWeapons();
    InitArmors();
    InitPotions();
    InitSpells();
    InitGrid();

    /* std::cout << "\n";
    std::cout << "\tOpening DI_RPG ";
    std::flush(std::cout);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << ".";
    std::flush(std::cout);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << ".";
    std::flush(std::cout);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << ".";
    std::flush(std::cout);
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); */

    clearscreen();
    NewHeroMenu();
}

void Game::InitWeapons()
{
    std::ifstream inFile("weapons.txt");

    if (inFile.fail())
    {
        std::cout << "Error Opening File 'weapons.txt'\n";
        exit(1);
    }

    std::string name;
    std::string price;
    std::string lvl;
    std::string dmg;
    std::string grip;

    while (!inFile.eof())
    {
        getline(inFile, name, '\t');
        getline(inFile, price, '\t');
        getline(inFile, lvl, '\t');
        getline(inFile, dmg, '\t');
        getline(inFile, grip, '\n');

        if (inFile.eof())
            break;

        if (grip == "0")
            AllWeapons.push_back(new Weapon(name, std::stoi(price), std::stoi(lvl), std::stoi(dmg), false));
        else
            AllWeapons.push_back(new Weapon(name, std::stoi(price), std::stoi(lvl), std::stoi(dmg), true));
    }

    std::cout << "\tInitializing All Weapons... ";
    std::flush(std::cout);
    /* std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Done\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(200)); */
}

void Game::InitArmors()
{
    std::ifstream inFile("armors.txt");

    if (inFile.fail())
    {
        std::cout << "Error Opening File 'armors.txt'\n";
        exit(1);
    }

    std::string name;
    std::string price;
    std::string lvl;
    std::string def;

    while (!inFile.eof())
    {
        getline(inFile, name, '\t');
        getline(inFile, price, '\t');
        getline(inFile, lvl, '\t');
        getline(inFile, def, '\n');

        if (inFile.eof())
            break;

        AllArmors.push_back(new Armor(name, std::stoi(price), std::stoi(lvl), std::stoi(def)));
    }

    std::cout << "\tInitializing All Armors... ";
    std::flush(std::cout);
    /* std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Done\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); */
}

void Game::InitPotions()
{
    std::ifstream inFile("potions.txt");

    if (inFile.fail())
    {
        std::cout << "Error Opening File 'potions.txt'\n";
        exit(1);
    }

    std::string name;
    std::string price;
    std::string lvl;
    std::string type;

    while (!inFile.eof())
    {
        getline(inFile, name, '\t');
        getline(inFile, price, '\t');
        getline(inFile, lvl, '\t');
        getline(inFile, type, '\n');

        if (inFile.eof())
            break;

        int type_num = std::stoi(type);
        switch (type_num)
        {
        case 1:
            AllPotions.push_back(new Potion(name, std::stoi(price), std::stoi(lvl), potionType::DEX));
            break;
        case 2:
            AllPotions.push_back(new Potion(name, std::stoi(price), std::stoi(lvl), potionType::STR));
            break;
        case 3:
            AllPotions.push_back(new Potion(name, std::stoi(price), std::stoi(lvl), potionType::AGIL));
            break;
        case 4:
            AllPotions.push_back(new Potion(name, std::stoi(price), std::stoi(lvl), potionType::HP));
            break;
        case 5:
            AllPotions.push_back(new Potion(name, std::stoi(price), std::stoi(lvl), potionType::MP));
            break;
        }
    }

    std::cout << "\tInitializing All Potions... ";
    std::flush(std::cout);
    /* std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Done\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); */
}

void Game::InitSpells()
{
    std::ifstream inFile("spells.txt");

    if (inFile.fail())
    {
        std::cout << "Error Opening File 'spells.txt'\n";
        exit(1);
    }

    std::string name;
    std::string price;
    std::string lvl;
    std::string mindmg;
    std::string maxdmg;
    std::string mp;
    std::string dur;
    std::string type;

    while (!inFile.eof())
    {
        getline(inFile, name, '\t');
        getline(inFile, price, '\t');
        getline(inFile, lvl, '\t');
        getline(inFile, mindmg, '\t');
        getline(inFile, maxdmg, '\t');
        getline(inFile, mp, '\t');
        getline(inFile, dur, '\t');
        getline(inFile, type, '\n');

        if (inFile.eof())
            break;

        int type_num = std::stoi(type);
        switch (type_num)
        {
        case 1:
            AllSpells.push_back(new IceSpell(name, std::stoi(price), std::stoi(lvl), std::stoi(mindmg), std::stoi(maxdmg), std::stoi(mp), std::stoi(dur)));
            break;
        case 2:
            AllSpells.push_back(new FireSpell(name, std::stoi(price), std::stoi(lvl), std::stoi(mindmg), std::stoi(maxdmg), std::stoi(mp), std::stoi(dur)));
            break;
        case 3:
            AllSpells.push_back(new LightningSpell(name, std::stoi(price), std::stoi(lvl), std::stoi(mindmg), std::stoi(maxdmg), std::stoi(mp), std::stoi(dur)));
            break;
        }
    }

    std::cout << "\tInitializing All Spells... ";
    std::flush(std::cout);
    /* std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Done\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); */
}

void Game::InitGrid()
{

    std::cout << "\tInitializing Grid... ";
    for(auto i = 0; i < Grid.size(); i++)
    {
        for (auto j = 0; j < Grid[i].size(); ++j)
        {
            Grid[i][j] = new Common(blockType::COMMON, AllWeapons, AllArmors, AllPotions, AllSpells);
        }
    }
    std::flush(std::cout);
    /* std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Done\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); */
}

void Game::DIRPG()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(34) << "=== DI_RPG ===" << std::setw(29) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(22) << "[ 1 ]\tPlay Game" << std::setw(38) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "[ 2 ]\tCredits" << std::setw(40) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(22) << "[ 0 ]\tQuit Game" << std::setw(38) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > 2)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 2)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input)
    {
    case 1:
        clearbuffer();
        InitGame();
        break;
    case 2:
        clearbuffer();
        CreditsScreen();
        break;
    case 0:
        clearbuffer();
        ExitScreen();
        break;
    }
}

void Game::CreditsScreen()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(35) << "=== Credits ===" << std::setw(28) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(36) << "Polydoros Tamtamis" << std::setw(27) << "////////\n";
    std::cout << "////////" << std::setw(32) << "sdi1900184" << std::setw(31) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(35) << "Christos Ioannou" << std::setw(28) << "////////\n";
    std::cout << "////////" << std::setw(32) << "sdi1900222" << std::setw(31) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << "\tReturning to DI_RPG in\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    for (int i = 5; i >= 1; i--)
    {
        for (int y = 5; y >= i; y--)
            std::cout << "\t";
        std::cout << i << "..\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    clearscreen();
    DIRPG();
}

void Game::ExitScreen()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "\n\n";
    std::cout << "\tThank you for playing DI_RPG\n\n";
    std::cout << "\tQuitting Game...\n\n";
    playing = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    clearscreen();
}

void Game::MainMenu()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(36) << "=== Main Menu ===" << std::setw(27) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(28) << "[ 1 ]\tResume Game" << std::setw(32) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(28) << "[ 2 ]\tHeroes Info" << std::setw(32) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(28) << "[ 3 ]\tChange Active Hero" << std::setw(32) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(27) << "[ 4 ]\tDisplay Map" << std::setw(33) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(22) << "[ 0 ]\tQuit Game" << std::setw(38) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > 3)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 3)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input)
    {
        case 1:
            clearbuffer();
            CommonBlockMenu();
            break;
        case 2:
            clearbuffer();
            //HeroesInfo();
            break;
        case 3:
            clearbuffer();
            //ChangeActiveHero();
            break;
        case 4:
            clearbuffer();
            //DisplayMap();
            break;
        case 0:
            clearbuffer();
            ExitScreen();
            break;
    }
}

void Game::TravelMenu()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== Travel Menu ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(25) << "[ 1 ]\tUp" << std::setw(35) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(26) << "[ 2 ]\tDown" << std::setw(34) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(25) << "[ 3 ]\tLeft" << std::setw(35) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(25) << "[ 4 ]\tRight" << std::setw(35) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > 4) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 4)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input)
    {
        case 1:
            clearbuffer();
            //
            break;
        case 2:
            clearbuffer();
            //
            break;
        case 3:
            clearbuffer();
            //
            break;
        case 4:
            clearbuffer();
            //
            break;
        case 0:
            clearbuffer();
            CommonBlockMenu();
            break;
    }
}

void Game::NewHeroMenu()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    if (MyHeroes.size() >= 3)
    {
        clearscreen();
        CommonBlockMenu();
    }
    if(MyHeroes.size() <= 2)
    {
        std::cout << "//////////////////////////////////////////////////////////////////////\n";
        std::cout << "////////" << std::setw(63) << "////////\n";
        std::cout << "////////" << std::setw(37) << "=== New Hero Menu ===" << std::setw(26) << "////////\n";
        std::cout << "////////" << std::setw(63) << "////////\n";
        std::cout << "//////////////////////////////////////////////////////////////////////\n";
        std::cout << "//////////////////////////////////////////////////////////////////////\n";
        std::cout << "////////" << std::setw(63) << "////////\n";
        std::cout << "////////" << std::setw(63) << "////////\n";
        std::cout << "////////" << std::setw(25) << "[ 1 ]\tWarrior Info" << std::setw(35) << "////////\n";
        std::cout << "////////" << std::setw(63) << "////////\n";
        std::cout << "////////" << std::setw(26) << "[ 2 ]\tSorcerer Info" << std::setw(34) << "////////\n";
        std::cout << "////////" << std::setw(63) << "////////\n";
        std::cout << "////////" << std::setw(25) << "[ 3 ]\tPaladin Info" << std::setw(35) << "////////\n";
        if (MyHeroes.size() != 0)
        {
            std::cout << "////////" << std::setw(63) << "////////\n";
            std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
        }
        std::cout << "////////" << std::setw(63) << "////////\n";
        std::cout << "////////" << std::setw(63) << "////////\n";
        std::cout << "//////////////////////////////////////////////////////////////////////\n";

        std::cout << "\n";

        std::cout << std::setw(37) << "Input: ";

        if (MyHeroes.size() != 0)
        {
            while (!(std::cin >> input) || input < 0 || input > 3)
            {
                std::cout << "\n";
                std::cout << std::setw(50) << "Invalid input (Must be: 0 - 3)\n";
                clearbuffer();
                std::cout << std::setw(37) << "Input: ";
            }
        }
        else
        {
            while (!(std::cin >> input) || input <= 0 || input > 3)
            {
                std::cout << "\n";
                std::cout << std::setw(50) << "Invalid input (Must be: 1 - 3)\n";
                clearbuffer();
                std::cout << std::setw(37) << "Input: ";
            }
        }

        switch (input)
        {
            case 1:
                clearbuffer();
                WarriorInfo();
                break;
            case 2:
                clearbuffer();
                SorcererInfo();
                break;
            case 3:
                clearbuffer();
                PaladinInfo();
                break;
            case 0:
                clearbuffer();
                std::cout << "\n\n";
                if(MyHeroes.size() == 1)
                    std::cout << "\t" << MyHeroes.size() << " Hero created!\n\n";
                else
                    std::cout << "\t" << MyHeroes.size() << " Heroes created!\n\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::cout << "\tYou cannot create more Heroes\n\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::cout << "\tSpawning...\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                CommonBlockMenu();
                break;
        }
    }
}

void Game::WarriorInfo()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    Warrior temp("temp", AllWeapons[2], AllArmors[1], AllSpells[0]);
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(36) << "=== Warrior Info ===" << std::setw(27) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Strength: " << temp.get_strength() << std::setw(31) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Dexterity: " << temp.get_dexterity() << std::setw(31) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(30) << "Agility: " << temp.get_agility() << std::setw(32) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(27) << "Start Weapon: " << AllWeapons[2]->get_name() << std::setw(23) << "////////\n";
    std::cout << "////////" << std::setw(24) << "Damage: " << AllWeapons[2]->getDamage() << " | " << AllWeapons[2]->get_grip() << std::setw(25) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(27) << "Start Armor: " << AllArmors[1]->get_name() << std::setw(24) << "////////\n";
    std::cout << "////////" << std::setw(30) << "Defense: " << AllArmors[1]->get_def() << std::setw(32) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Start Spell: " << AllSpells[0]->get_name() << std::setw(27) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Damage Range: " << AllSpells[0]->get_mindmg() << " - " << AllSpells[0]->get_maxdmg() << std::setw(27) << "////////\n";
    std::cout << "////////" << std::setw(25) << "Magic Power: " << AllSpells[0]->getMPcost() << " | Duration: " << AllSpells[0]->get_duration() << std::setw(22) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 1 ]\tSelect" << std::setw(41) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 2 ]\tBack" << std::setw(43) << "////////\n";
    if (MyHeroes.size() != 0)
    {
        std::cout << "////////" << std::setw(63) << "////////\n";
        std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    }
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    if (MyHeroes.size() != 0)
    {
        while (!(std::cin >> input) || input < 0 || input > 2)
        {
            std::cout << "\n";
            std::cout << std::setw(50) << "Invalid input (Must be: 0 - 2)\n";
            clearbuffer();
            std::cout << std::setw(37) << "Input: ";
        }
    }
    else
    {
        while (!(std::cin >> input) || input <= 0 || input > 2)
        {
            std::cout << "\n";
            std::cout << std::setw(50) << "Invalid input (Must be: 1 - 2)\n";
            clearbuffer();
            std::cout << std::setw(37) << "Input: ";
        }
    }

    switch (input)
    {
        case 1:
            clearbuffer();
            CreateNewHero(heroType::WARRIOR);
            break;
        case 2:
            clearbuffer();
            NewHeroMenu();
            break;
        case 0:
            clearbuffer();
            if(MyHeroes.size() == 1)
                std::cout << "\t" << MyHeroes.size() << " Hero created!\n\n";
            else
                std::cout << "\t" << MyHeroes.size() << " Heroes created!\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "\tYou cannot create more Heroes\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "\tSpawning...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            CommonBlockMenu();
            break;
    } 
}

void Game::SorcererInfo()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    Sorcerer temp("temp", AllWeapons[0], AllArmors[1], AllSpells[2]);
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== Sorcerer Info ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Strength: " << temp.get_strength() << std::setw(31) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Dexterity: " << temp.get_dexterity() << std::setw(31) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(30) << "Agility: " << temp.get_agility() << std::setw(32) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
        std::cout << "////////" << std::setw(29) << "Start Weapon: " << AllWeapons[0]->get_name() << std::setw(25) << "////////\n";
    std::cout << "////////" << std::setw(24) << "Damage: " << AllWeapons[0]->getDamage() << " | " << AllWeapons[0]->get_grip() << std::setw(25) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(27) << "Start Armor: " << AllArmors[1]->get_name() << std::setw(24) << "////////\n";
    std::cout << "////////" << std::setw(30) << "Defense: " << AllArmors[1]->get_def() << std::setw(32) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(29) << "Start Spell: " << AllSpells[2]->get_name() << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(30) << "Damage Range: " << AllSpells[2]->get_mindmg() << " - " << AllSpells[2]->get_maxdmg() << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(25) << "Magic Power: " << AllSpells[2]->getMPcost() << " | Duration: " << AllSpells[2]->get_duration() << std::setw(22) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 1 ]\tSelect" << std::setw(41) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 2 ]\tBack" << std::setw(43) << "////////\n";
    if (MyHeroes.size() != 0)
    {
        std::cout << "////////" << std::setw(63) << "////////\n";
        std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    }
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    if(MyHeroes.size() != 0)
    {
        while (!(std::cin >> input) || input < 0 || input > 2)
        {
            std::cout << "\n";
            std::cout << std::setw(50) << "Invalid input (Must be: 0 - 2)\n";
            clearbuffer();
            std::cout << std::setw(37) << "Input: ";
        }
    }
    else
    {
        while (!(std::cin >> input) || input <= 0 || input > 2)
        {
            std::cout << "\n";
            std::cout << std::setw(50) << "Invalid input (Must be: 1 - 2)\n";
            clearbuffer();
            std::cout << std::setw(37) << "Input: ";
        }
    }

    switch (input)
    {
        case 1:
            clearbuffer();
            CreateNewHero(heroType::SORCERER);
            break;
        case 2:
            clearbuffer();
            NewHeroMenu();
            break;
        case 0:
            clearbuffer();
            if(MyHeroes.size() == 1)
                std::cout << "\t" << MyHeroes.size() << " Hero created!\n\n";
            else
                std::cout << "\t" << MyHeroes.size() << " Heroes created!\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "\tYou cannot create more Heroes\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "\tSpawning...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            CommonBlockMenu();
            break;
    }
}

void Game::PaladinInfo()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    Paladin temp("temp", AllWeapons[1], AllArmors[2], AllSpells[0]);
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(36) << "=== Paladin Info ===" << std::setw(27) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Strength: " << temp.get_strength() << std::setw(31) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Dexterity: " << temp.get_dexterity() << std::setw(31) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(30) << "Agility: " << temp.get_agility() << std::setw(32) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(28) << "Start Weapon: " << AllWeapons[1]->get_name() << std::setw(23) << "////////\n";
    std::cout << "////////" << std::setw(24) << "Damage: " << AllWeapons[1]->getDamage() << " | " << AllWeapons[1]->get_grip() << std::setw(25) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(30) << "Start Armor: " << AllArmors[2]->get_name() << std::setw(27) << "////////\n";
    std::cout << "////////" << std::setw(30) << "Defense: " << AllArmors[2]->get_def() << std::setw(32) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Start Spell: " << AllSpells[0]->get_name() << std::setw(27) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Damage Range: " << AllSpells[0]->get_mindmg() << " - " << AllSpells[0]->get_maxdmg() << std::setw(27) << "////////\n";
    std::cout << "////////" << std::setw(25) << "Magic Power: " << AllSpells[0]->getMPcost() << " | Duration: " << AllSpells[2]->get_duration() << std::setw(22) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 1 ]\tSelect" << std::setw(41) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 2 ]\tBack" << std::setw(43) << "////////\n";
    if(MyHeroes.size() != 0)
    {
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    }
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    if(MyHeroes.size() != 0)
    {
        while (!(std::cin >> input) || input < 0 || input > 2)
        {
            std::cout << "\n";
            std::cout << std::setw(50) << "Invalid input (Must be: 0 - 2)\n";
            clearbuffer();
            std::cout << std::setw(37) << "Input: ";
        }
    }
    else
    {
        while (!(std::cin >> input) || input <= 0 || input > 2)
        {
            std::cout << "\n";
            std::cout << std::setw(50) << "Invalid input (Must be: 1 - 2)\n";
            clearbuffer();
            std::cout << std::setw(37) << "Input: ";
        }
    }
    
    switch (input)
    {
        case 1:
            clearbuffer();
            CreateNewHero(heroType::PALADIN);
            break;
        case 2:
            clearbuffer();
            NewHeroMenu();
            break;
        case 0:
            clearbuffer();
            if(MyHeroes.size() == 1)
                std::cout << "\t" << MyHeroes.size() << " Hero created!\n\n";
            else
                std::cout << "\t" << MyHeroes.size() << " Heroes created!\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "\tYou cannot create more Heroes\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "\tSpawning...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            CommonBlockMenu();
            break;
    }
}

void Game::CreateNewHero(heroType htype)
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(38) << "=== Create New Hero ===" << std::setw(25) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    switch (htype)
    {
    case (heroType::WARRIOR):
        std::cout << "////////" << std::setw(32) << "[ Warrior ]" << std::setw(31) << "////////\n";
        break;
    case (heroType::SORCERER):
        std::cout << "////////" << std::setw(32) << "[ Sorcerer ]" << std::setw(31) << "////////\n";
        break;
    case (heroType::PALADIN):
        std::cout << "////////" << std::setw(32) << "[ Paladin ]" << std::setw(31) << "////////\n";
        break;
    }
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::string input_name;
    std::cout << std::setw(37) << "Hero Name: ";
    std::cin >> input_name;
    while (std::cin.fail())
    {
        std::cout << "\n"
                  << std::setw(47) << "Something went wrong\n";
        std::cout << std::setw(41) << "Try again\n\n";
        std::cout << std::setw(37) << "Hero Name: ";
        clearbuffer();
        std::cin >> input_name;
    }
    for (auto it = MyHeroes.begin(); it != MyHeroes.end(); ++it)
    {
        while (input_name == (*it)->get_name())
        {
            std::cout << "\n"
                      << std::setw(50) << "This name is already taken!\n";
            std::cout << std::setw(50) << "Please type a different name\n";
            std::cout << "\n"
                      << std::setw(37) << "Hero Name: ";
            clearbuffer();
            std::cin >> input_name;
            while (std::cin.fail())
            {
                std::cout << "\n"
                          << std::setw(47) << "Something went wrong\n";
                std::cout << std::setw(41) << "Try again\n\n";
                std::cout << std::setw(37) << "Hero Name: ";
                clearbuffer();
                std::cin >> input_name;
            }
        }
    }
    switch (htype)
    {
    case (heroType::WARRIOR):
        MyHeroes.push_back(new Warrior(input_name, AllWeapons[2], AllArmors[1], AllSpells[0]));
        ActiveHero = MyHeroes.size()-1;
        break;
    case (heroType::SORCERER):
        MyHeroes.push_back(new Sorcerer(input_name, AllWeapons[0], AllArmors[1], AllSpells[2]));
        ActiveHero = MyHeroes.size()-1;
        break;
    case (heroType::PALADIN):
        MyHeroes.push_back(new Paladin(input_name, AllWeapons[1], AllArmors[2], AllSpells[0]));
        ActiveHero = MyHeroes.size()-1;
        break;
    }

    std::cout << "\n\n";
    std::cout << "\tCreated a New Hero successfully!\n\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    int left_count;
    left_count = 3 - MyHeroes.size();
    if(left_count == 1)
        std::cout << "\tYou can create " << left_count << " more hero...\n";
    else if(left_count == 0)
    {
        std::cout << "\tMaximum number of Heroes is reached!\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "\tYou cannot create more Heroes\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "\tSpawning...\n";
    }
    else
        std::cout << "\tYou can create " << left_count << " more heroes...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearscreen();
    NewHeroMenu();
}

void Game::CommonBlockMenu()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(39) << "=== Common Block Menu ===" << std::setw(24) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(28) << "[ 1 ]\tCheck Inventory" << std::setw(32) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(27) << "[ 2 ]\tTravel" << std::setw(33) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    if(Grid[ActiveBlock_x][ActiveBlock_y]->get_market() != nullptr)
    {
        std::cout << "////////" << std::setw(28) << "[ 3 ]\tDisplay Market" << std::setw(32) << "////////\n";
        std::cout << "////////" << std::setw(63) << "////////\n";
    }
    std::cout << "////////" << std::setw(30) << "[ 0 ]\tMain Menu" << std::setw(30) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > 3)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 3)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input)
    {
    case 1:
        clearbuffer();
        InventoryMenu();
        break;
    case 2:
        clearbuffer();
        TravelMenu();
        break;
    case 3:
        clearbuffer();
        MarketMenu();
        break;
    case 0:
        clearbuffer();
        MainMenu();
        break;
    }
}

void Game::InventoryMenu()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(39) << "=== Inventory Menu ===" << std::setw(24) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    MyHeroes[ActiveHero]->checkInventory();
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(28) << "[ 1 ]\tChange Weapon" << std::setw(32) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(27) << "[ 2 ]\tChange Armor" << std::setw(33) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(28) << "[ 3 ]\tUse Potion" << std::setw(32) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(30) << "[ 0 ]\tExit" << std::setw(30) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > 3)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 3)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input)
    {
    case 1:
        clearbuffer();
        ChangeWeapon();
        break;
    case 2:
        clearbuffer();
        ChangeArmor();
        break;
    case 3:
        clearbuffer();
        UsePotion();
        break;
    case 0:
        clearbuffer();
        CommonBlockMenu();
        break;
    }
}

void Game::ChangeWeapon()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== Change Weapon ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    MyHeroes[ActiveHero]->DisplayItems("Weapons");
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(9) << "[ " << MyHeroes[ActiveHero]->get_vector_size("Weapon")+1 << " ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "Hero Selected: " << MyHeroes[ActiveHero]->get_name() << std::setw(20) << "////////\n";
    std::cout << "////////" << std::setw(20) << "Right Hand: ";
    if(MyHeroes[ActiveHero]->get_righthand() != nullptr)
        std::cout << MyHeroes[ActiveHero]->get_righthand()->get_name() << std::setw(30) << "////////\n";
    else
        std::cout << "-" << std::setw(30) << "////////\n";
    std::cout << "////////" << std::setw(20) << "Left Hand: ";
    if(MyHeroes[ActiveHero]->get_lefthand() != nullptr)
        std::cout << MyHeroes[ActiveHero]->get_lefthand()->get_name() << std::setw(30) << "////////\n";
    else
        std::cout << "-" << std::setw(30) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > MyHeroes[ActiveHero]->get_vector_size("Weapon")+1)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - " << MyHeroes[ActiveHero]->get_vector_size("Weapon")+1 << ")\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    if(input == MyHeroes[ActiveHero]->get_vector_size("Weapon")+1)
    {
        clearbuffer();
        InventoryMenu();
    }
    else if(input == 0)
    {
        clearbuffer();
        CommonBlockMenu();
    }
    int index = input-1;

    std::cout << "\n";

    std::cout << std::setw(37) << "Select Hand: ";

    while (!(std::cin >> input) || input < 1 || input > 2)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 1 - 2)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Select Hand: ";
    }
    MyHeroes[ActiveHero]->set_weapon(index, input);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearbuffer();
    CommonBlockMenu();
}

void Game::ChangeArmor()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== Change Armor ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    MyHeroes[ActiveHero]->DisplayItems("Armors");
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(9) << "[ " << MyHeroes[ActiveHero]->get_vector_size("Armor")+1 << " ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "Hero Selected: " << MyHeroes[ActiveHero]->get_name() << std::setw(20) << "////////\n";
    std::cout << "////////" << std::setw(20) << "Armor: ";
    if(MyHeroes[ActiveHero]->get_armor() != nullptr)
        std::cout << MyHeroes[ActiveHero]->get_armor()->get_name() << std::setw(30) << "////////\n";
    else
        std::cout << "-" << std::setw(30) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > MyHeroes[ActiveHero]->get_vector_size("Armor")+1)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - " << MyHeroes[ActiveHero]->get_vector_size("Armor")+1 << ")\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    if(input == MyHeroes[ActiveHero]->get_vector_size("Armor")+1)
    {
        clearbuffer();
        InventoryMenu();
    }
    else if(input == 0)
    {
        clearbuffer();
        CommonBlockMenu();
    }
    MyHeroes[ActiveHero]->equip(input-1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearbuffer();
    CommonBlockMenu();
}

void Game::UsePotion()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== Use Potion ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    MyHeroes[ActiveHero]->DisplayItems("Potions");
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(9) << "[ " << MyHeroes[ActiveHero]->get_vector_size("Potion")+1 << " ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "Hero Selected: " << MyHeroes[ActiveHero]->get_name() << std::setw(20) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > MyHeroes[ActiveHero]->get_vector_size("Potion")+1)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - " << MyHeroes[ActiveHero]->get_vector_size("Potion")+1 << ")\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    if(input == MyHeroes[ActiveHero]->get_vector_size("Potion")+1)
    {
        clearbuffer();
        InventoryMenu();
    }
    else if(input == 0)
    {
        clearbuffer();
        CommonBlockMenu();
    }
    MyHeroes[ActiveHero]->use(input-1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearbuffer();
    CommonBlockMenu();
}

void Game::MarketMenu()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
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

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > 2) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 2)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input)
    {
        case 1:
            clearbuffer();
            BuyMenu();
            break;
        case 2:
            clearbuffer();
            SellMenu();
            break;
        case 0:
            clearbuffer();
            CommonBlockMenu();
            break;
    }
}

void Game::BuyMenu()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
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
    std::cout << "////////" << std::setw(17) << "[ 5 ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > 5) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 5)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input) {
    case 1:
        clearbuffer();
        BuyWeapons();
        break;
    case 2:
        clearbuffer();
        BuyArmors();
        break;
    case 3:
        clearbuffer();
        BuyPotions();
        break;
    case 4:
        clearbuffer();
        BuySpells();
        break;
    case 5:
        clearbuffer();
        MarketMenu();
        break;
    case 0:
        clearbuffer();
        CommonBlockMenu();
        break;
    }
}

void Game::BuyWeapons()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== Buy Weapons ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->DisplayItems("Weapons");
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(9) << "[ " << Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Weapon")+1 << " ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "Hero Selected: " << MyHeroes[ActiveHero]->get_name() << " | Money: " << MyHeroes[ActiveHero]->getMoney() << std::setw(20) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Weapon")+1)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - " << Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Weapon")+1 << ")\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    if(input == Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Weapon")+1)
    {
        clearbuffer();
        BuyMenu();
    }
    else if(input == 0)
    {
        clearbuffer();
        CommonBlockMenu();
    }
    Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->buy(MyHeroes[ActiveHero], "Weapon", input-1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearbuffer();
    CommonBlockMenu();
}

void Game::BuyArmors()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== Buy Armors ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->DisplayItems("Armors");
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(9) << "[ " << Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Armor")+1 << " ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "Hero Selected: " << MyHeroes[ActiveHero]->get_name() << " | Money: " << MyHeroes[ActiveHero]->getMoney() << std::setw(20) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Armor")+1)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - " << Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Armor")+1 << ")\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    if(input == Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Armor")+1)
    {
        clearbuffer();
        BuyMenu();
    }
    else if(input == 0)
    {
        clearbuffer();
        CommonBlockMenu();
    }
    Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->buy(MyHeroes[ActiveHero], "Armor", input-1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearbuffer();
    CommonBlockMenu();
}

void Game::BuyPotions()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== Buy Potions ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->DisplayItems("Potions");
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(9) << "[ " << Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Potion")+1 << " ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "Hero Selected: " << MyHeroes[ActiveHero]->get_name() << " | Money: " << MyHeroes[ActiveHero]->getMoney() << std::setw(20) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Potion")+1)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - " << Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Potion")+1 << ")\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    if(input == Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Potion")+1)
    {
        clearbuffer();
        BuyMenu();
    }
    else if(input == 0)
    {
        clearbuffer();
        CommonBlockMenu();
    }
    Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->buy(MyHeroes[ActiveHero], "Potion", input-1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearbuffer();
    CommonBlockMenu();
}

void Game::BuySpells()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== Buy Spells ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->DisplayItems("Spells");
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(9) << "[ " << Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Spell")+1 << " ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "Hero Selected: " << MyHeroes[ActiveHero]->get_name() << " | Money: " << MyHeroes[ActiveHero]->getMoney() << std::setw(20) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Spell")+1)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - " << Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Spell")+1 << ")\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    if(input == Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->get_vector_size("Spell")+1)
    {
        clearbuffer();
        BuyMenu();
    }
    else if(input == 0)
    {
        clearbuffer();
        CommonBlockMenu();
    }
    Grid[ActiveBlock_x][ActiveBlock_y]->get_market()->buy(MyHeroes[ActiveHero], "Spell", input-1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearbuffer();
    CommonBlockMenu();
}

void Game::SellMenu()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
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
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > 5) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 5)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input) {
        case 1:
            clearbuffer();
            SellWeapons();
            break;
        case 2:
            clearbuffer();
            SellArmors();
            break;
        case 3:
            clearbuffer();
            SellPotions();
            break;
        case 4:
            clearbuffer();
            SellSpells();
            break;
        case 5:
            clearbuffer();
            MarketMenu();
            break;
        case 0:
            clearbuffer();
            CommonBlockMenu();
            break;
    }
}

void Game::SellWeapons()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== Sell Weapons ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    MyHeroes[ActiveHero]->DisplayItems("Weapons");
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(9) << "[ " << MyHeroes[ActiveHero]->get_vector_size("Weapon")+1 << " ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "Hero Selected: " << MyHeroes[ActiveHero]->get_name() << " | Money: " << MyHeroes[ActiveHero]->getMoney() << std::setw(20) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > MyHeroes[ActiveHero]->get_vector_size("Weapon")+1)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - " << MyHeroes[ActiveHero]->get_vector_size("Weapon")+1 << ")\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    if(input == MyHeroes[ActiveHero]->get_vector_size("Weapon")+1)
    {
        clearbuffer();
        SellMenu();
    }
    else if(input == 0)
    {
        clearbuffer();
        CommonBlockMenu();
    }
    MyHeroes[ActiveHero]->sell(Grid[ActiveBlock_x][ActiveBlock_y]->get_market(), "Weapon", input-1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearbuffer();
    CommonBlockMenu();
}

void Game::SellArmors()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== Sell Armors ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    MyHeroes[ActiveHero]->DisplayItems("Armors");
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(9) << "[ " << MyHeroes[ActiveHero]->get_vector_size("Armor")+1 << " ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "Hero Selected: " << MyHeroes[ActiveHero]->get_name() << " | Money: " << MyHeroes[ActiveHero]->getMoney() << std::setw(20) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > MyHeroes[ActiveHero]->get_vector_size("Armor")+1)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - " << MyHeroes[ActiveHero]->get_vector_size("Armor")+1 << ")\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    if(input == MyHeroes[ActiveHero]->get_vector_size("Armor")+1)
    {
        clearbuffer();
        SellMenu();
    }
    else if(input == 0)
    {
        clearbuffer();
        CommonBlockMenu();
    }
    MyHeroes[ActiveHero]->sell(Grid[ActiveBlock_x][ActiveBlock_y]->get_market(), "Armor", input-1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearbuffer();
    CommonBlockMenu();
}

void Game::SellPotions()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== Sell Potions ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    MyHeroes[ActiveHero]->DisplayItems("Potions");
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(9) << "[ " << MyHeroes[ActiveHero]->get_vector_size("Potion")+1 << " ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "Hero Selected: " << MyHeroes[ActiveHero]->get_name() << " | Money: " << MyHeroes[ActiveHero]->getMoney() << std::setw(20) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > MyHeroes[ActiveHero]->get_vector_size("Potion")+1)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - " << MyHeroes[ActiveHero]->get_vector_size("Potion")+1 << ")\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    if(input == MyHeroes[ActiveHero]->get_vector_size("Potion")+1)
    {
        clearbuffer();
        SellMenu();
    }
    else if(input == 0)
    {
        clearbuffer();
        CommonBlockMenu();
    }
    MyHeroes[ActiveHero]->sell(Grid[ActiveBlock_x][ActiveBlock_y]->get_market(), "Potion", input-1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearbuffer();
    CommonBlockMenu();
}

void Game::SellSpells()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== Sell Spells ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    MyHeroes[ActiveHero]->DisplayItems("Spells");
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(9) << "[ " << MyHeroes[ActiveHero]->get_vector_size("Spell")+1 << " ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "Hero Selected: " << MyHeroes[ActiveHero]->get_name() << " | Money: " << MyHeroes[ActiveHero]->getMoney() << std::setw(20) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input < 0 || input > MyHeroes[ActiveHero]->get_vector_size("Spell")+1)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - " << MyHeroes[ActiveHero]->get_vector_size("Spell")+1 << ")\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    if(input == MyHeroes[ActiveHero]->get_vector_size("Spell")+1)
    {
        clearbuffer();
        SellMenu();
    }
    else if(input == 0)
    {
        clearbuffer();
        CommonBlockMenu();
    }
    MyHeroes[ActiveHero]->sell(Grid[ActiveBlock_x][ActiveBlock_y]->get_market(), "Spell", input-1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearbuffer();
    CommonBlockMenu();
}

void Game::clearbuffer()
{
    std::cin.clear();           //reset possible error flag
    std::cin.ignore(500, '\n'); //clear buffer
}

void Game::clearscreen()
{
    std::cout << "\033c";
}

bool Game::get_playing() const
{
    return playing;
}