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
    , Dimension(4)
{
    //
}

Game::~Game()
{

    for (auto w : AllWeapons)
        delete w;
    for (auto a : AllArmors)
        delete a;
    for (auto s : AllSpells)
        delete s;
    for (auto p : AllPotions)
        delete p;
    delete grid;
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

    std::cout << "\n";
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
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    clearscreen();
    MainMenu();
}

void Game::InitWeapons()
{
    std::ifstream inFile("weapons.txt");

    if (inFile.fail()) {
        std::cout << "Error Opening File 'weapons.txt'\n";
        exit(1);
    }

    std::string name;
    std::string price;
    std::string lvl;
    std::string dmg;
    char grip;

    while (!inFile.eof()) {
        getline(inFile, name, '\t');
        getline(inFile, price, '\t');
        getline(inFile, lvl, '\t');
        getline(inFile, dmg, '\t');
        inFile >> grip;

        if (inFile.eof())
            break;

        if (grip == '0')
            AllWeapons.push_back(new Weapon(name, std::stoi(price), std::stoi(lvl), std::stoi(dmg), false));
        else
            AllWeapons.push_back(new Weapon(name, std::stoi(price), std::stoi(lvl), std::stoi(dmg), true));
    }

    std::cout << "\tInitializing All Weapons... ";
    std::flush(std::cout);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Done\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

void Game::InitArmors()
{
    std::ifstream inFile("armors.txt");

    if (inFile.fail()) {
        std::cout << "Error Opening File 'armors.txt'\n";
        exit(1);
    }

    std::string name;
    std::string price;
    std::string lvl;
    std::string def;

    while (!inFile.eof()) {
        getline(inFile, name, '\t');
        getline(inFile, price, '\t');
        getline(inFile, lvl, '\t');
        inFile >> def;

        if (inFile.eof())
            break;

        AllArmors.push_back(new Armor(name, std::stoi(price), std::stoi(lvl), std::stoi(def)));
    }

    std::cout << "\tInitializing All Armors... ";
    std::flush(std::cout);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Done\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Game::InitPotions()
{
    std::ifstream inFile("potions.txt");

    if (inFile.fail()) {
        std::cout << "Error Opening File 'potions.txt'\n";
        exit(1);
    }

    std::string name;
    std::string price;
    std::string lvl;
    std::string type;

    while (!inFile.eof()) {
        getline(inFile, name, '\t');
        getline(inFile, price, '\t');
        getline(inFile, lvl, '\t');
        inFile >> type;

        if (inFile.eof())
            break;

        int type_num = std::stoi(type);
        switch (type_num) {
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
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Done\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Game::InitSpells()
{
    std::ifstream inFile("spells.txt");

    if (inFile.fail()) {
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

    while (!inFile.eof()) {
        getline(inFile, name, '\t');
        getline(inFile, price, '\t');
        getline(inFile, lvl, '\t');
        getline(inFile, mindmg, '\t');
        getline(inFile, maxdmg, '\t');
        getline(inFile, mp, '\t');
        getline(inFile, dur, '\t');
        inFile >> type;

        if (inFile.eof())
            break;

        int type_num = std::stoi(type);
        switch (type_num) {
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
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Done\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Game::InitGrid()
{

    std::cout << "\tInitializing Grid... ";
    grid = new Grid(); //draw map
    std::flush(std::cout);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Done\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Game::printWeap()
{
    clearscreen();
    std::cout << "\n\n";
    for (auto it = AllWeapons.begin(); it != AllWeapons.end(); ++it) {
        (*it)->print();
    }
    std::cout << "\n"
              << AllWeapons.size() << "\n"
              << AllArmors.size() << "\n";
    std::cout << AllPotions.size() << "\n"
              << AllSpells.size() << "\n";
    std::cout << "\n\n";
    std::cout << "Returning to Main Menu...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(60000));
    clearscreen();
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

    while (!(std::cin >> input) || input > 2) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 2)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input) {
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
    for (int i = 5; i >= 1; i--) {
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
    std::cout << "////////" << std::setw(28) << "[ 1 ]\tCreate New Hero" << std::setw(32) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    /* std::cout << "////////" << std::setw(27) << "[ 2 ]\tMarket Menu..." << std::setw(33) << "////////\n";*/
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(30) << "[ 2 ]\tPrint All Weapons" << std::setw(30) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(30) << "[ 3 ]\tDisplay Map" << std::setw(30) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(22) << "[ 0 ]\tQuit Game" << std::setw(38) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input > 4) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 1 - 4)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input) {
    case 1:
        clearbuffer();
        NewHeroMenu();
        break;
    /*case 2:
        clearbuffer();
        MarketMenu();
        break;*/
    case 3:
        clearbuffer();
        grid->displayMap();
        break;
    case 4:
        clearbuffer();
        printWeap();
        break;
    case 0:
        clearbuffer();
        ExitScreen();
        break;
    }
}

/*void Game::TravelMenu()
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

    while (!(std::cin >> input) || input > 4) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 4)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input) {
    case 1:
        clearbuffer();
        //if(Grid[ActiveBlock-Dimension] == inaccessible)
        //    std::cout << "cant\n";
        ActiveBlock -= Dimension;
        Grid[ActiveBlock]->move(MyHeroes);
        break;
    case 2:
        clearbuffer();
        //if(Grid[ActiveBlock-Dimension] == inaccessible)
        //    std::cout << "cant\n";
        ActiveBlock += Dimension;
        Grid[ActiveBlock]->move(MyHeroes);
        break;
    case 3:
        clearbuffer();
        PaladinInfo();
        break;
    case 0:
        clearbuffer();
        MainMenu();
        break;
    }
}
*/

void Game::NewHeroMenu()
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
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
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input > 3) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 3)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input) {
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
        MainMenu();
        break;
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
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 1 ]\tSelect" << std::setw(41) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 2 ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input > 2) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 2)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input) {
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
        MainMenu();
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
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 1 ]\tSelect" << std::setw(41) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 2 ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input > 2) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 2)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input) {
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
        MainMenu();
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
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 1 ]\tSelect" << std::setw(41) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 2 ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input > 2) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 2)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input) {
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
        MainMenu();
        break;
    }
}

void Game::CreateNewHero(heroType htype)
{
    clearscreen();
    std::cout << "\n\n\tLoading.." << std::endl;
    clearscreen();
    if (MyHeroes.size() >= 3) {
        std::cout << "\n\n";
        std::cout << "\tMaximum number of Heroes is reached!\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "\tYou cannot create more Heroes\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "\tReturning to Main Menu...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        clearscreen();
        MainMenu();
    }
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(38) << "=== Create New Hero ===" << std::setw(25) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    switch (htype) {
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
    while (std::cin.fail()) {
        std::cout << "\n"
                  << std::setw(47) << "Something went wrong\n";
        std::cout << std::setw(41) << "Try again\n\n";
        std::cout << std::setw(37) << "Hero Name: ";
        clearbuffer();
        std::cin >> input_name;
    }
    for (auto it = MyHeroes.begin(); it != MyHeroes.end(); ++it) {
        while (input_name == (*it)->get_name()) {
            std::cout << "\n"
                      << std::setw(50) << "This name is already taken!\n";
            std::cout << std::setw(50) << "Please type a different name\n";
            std::cout << "\n"
                      << std::setw(37) << "Hero Name: ";
            clearbuffer();
            std::cin >> input_name;
            while (std::cin.fail()) {
                std::cout << "\n"
                          << std::setw(47) << "Something went wrong\n";
                std::cout << std::setw(41) << "Try again\n\n";
                std::cout << std::setw(37) << "Hero Name: ";
                clearbuffer();
                std::cin >> input_name;
            }
        }
    }
    switch (htype) {
    case (heroType::WARRIOR):
        MyHeroes.push_back(new Warrior(input_name, AllWeapons[2], AllArmors[1], AllSpells[0]));
        break;
    case (heroType::SORCERER):
        MyHeroes.push_back(new Sorcerer(input_name, AllWeapons[0], AllArmors[1], AllSpells[2]));
        break;
    case (heroType::PALADIN):
        MyHeroes.push_back(new Paladin(input_name, AllWeapons[1], AllArmors[2], AllSpells[0]));
        break;
    }
    //MyHeroes[MyHeroes.size()-1]->addToInv(AllWeapons[0]);

    std::cout << "\n\n";
    std::cout << "\tCreated a New Hero successfully!\n\n";
    MyHeroes[MyHeroes.size() - 1]->checkInventory();
    //MyHeroes[MyHeroes.size()-1]->set_weapon(0);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "\tReturning to Main Menu...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearscreen();
}
/*
void market::menu()
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

    while (!(std::cin >> input) || input > 3) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 3)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input) {
    case 1:
        clearbuffer();
        buyMenu();
        break;
    case 2:
        clearbuffer();
        sellMenu() break;
    case 3:
        clearbuffer();
        DisplayMap();

        break;
    case 4:
        clearbuffer();
        TravelMenu();
    default:
        return;
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

    while (!(std::cin >> input) || input > 5) {
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
        MainMenu();
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
    std::vector<block*> Grid;
    Grid[ActiveBlock]->DisplayItems("Weapons");
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while (!(std::cin >> input) || input > Grid[ActiveBlock]->vector_count("Weapons")) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - " << Grid[ActiveBlock]->vector_count("Weapons") << ")\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }
    //MyHeroes[ActiveHero]->purchase(Grid[ActiveBlock], "Weapon", input);
    //Grid[ActiveBlock]->//sinartisi pol(input);
}

void Game::BuyArmors()
{
}

void Game::BuyPotions()
{
}

void Game::BuySpells()
{
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

    while (!(std::cin >> input) || input > 5) {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 5)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch (input) {
    case 1:
        clearbuffer();
        SellMenu();
        break;
    case 2:
        clearbuffer();
        SellMenu();
        break;
    case 3:
        clearbuffer();
        SellMenu();
        break;
    case 4:
        clearbuffer();
        SellMenu();
        break;
    case 5:
        clearbuffer();
        MarketMenu();
        break;
    case 0:
        clearbuffer();
        MainMenu();
        break;
    }
}
*/
void Game::clearbuffer()
{
    std::cin.clear(); //reset possible error flag
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