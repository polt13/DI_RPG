#include "rpg_lib.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <stdio.h>
//  Needed for sleep function
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

Game::Game() : playing(true)
{
    //
}

Game::~Game()
{
    for (auto it = MyHeroes.begin(); it != MyHeroes.end(); ++it)
        delete (*it);
}

void Game::StartScreen()
{
    system("clear");
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    std::cout << "\n\n";
    std::cout << "\tWelcome to DI_RPG\n\n";
    std::cout << "\tPress ENTER to continue..." << std::endl;
    std::cin.get();
    system("clear");
}

void Game::InitGame()
{
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");

    std::cout << "\n\n";

    InitWeapons();
    InitArmors();
    InitPotions();
    InitSpells();
    InitGrid();
    
    std::cout << "\n";
    std::cout << "\tOpening DI_RPG ";
    fflush(stdout);
    sleep(1);
    std::cout << ".";
    fflush(stdout);
    sleep(1);
    std::cout << ".";
    fflush(stdout);
    sleep(1);
    std::cout << ".";
    fflush(stdout);
    sleep(1);

    //sleep(2);

    system("clear");
    MainMenu();
}

void Game::InitWeapons()
{
    std::ifstream inFile;
    inFile.open("weapons.txt");

    if(inFile.fail())
    {
        std::cout << "Error Opening File 'weapons.txt'\n";
        exit(1);
    }

    std::string name;
    std::string price;
    std::string lvl;
    std::string dmg;
    char grip;

    while(!inFile.eof())
    {
        getline(inFile, name, '\t');
        getline(inFile, price, '\t');
        getline(inFile, lvl, '\t');
        getline(inFile, dmg, '\t');
        inFile >> grip;

        if(inFile.eof())
            break;

        if(grip == '0')
            AllWeapons.push_back(new Weapon(name, stoi(price), stoi(lvl), stoi(dmg), false));
        else
            AllWeapons.push_back(new Weapon(name, stoi(price), stoi(lvl), stoi(dmg), true));
    }
    inFile.close();

    std::cout << "\tInitializing All Weapons... ";
    fflush(stdout);
    sleep(1);
    std::cout << "Done\n";
}

void Game::InitArmors()
{
    std::ifstream inFile;
    inFile.open("armors.txt");

    if(inFile.fail())
    {
        std::cout << "Error Opening File 'armors.txt'\n";
        exit(1);
    }

    std::string name;
    std::string price;
    std::string lvl;
    std::string def;

    while(!inFile.eof())
    {
        getline(inFile, name, '\t');
        getline(inFile, price, '\t');
        getline(inFile, lvl, '\t');
        inFile >> def;

        if(inFile.eof())
            break;

        AllArmors.push_back(new Armor(name, stoi(price), stoi(lvl), stoi(def)));
    }
    inFile.close();

    std::cout << "\tInitializing All Armors... ";
    fflush(stdout);
    sleep(1);
    std::cout << "Done\n";
}

void Game::InitPotions()
{
    std::ifstream inFile;
    inFile.open("potions.txt");

    if(inFile.fail())
    {
        std::cout << "Error Opening File 'potions.txt'\n";
        exit(1);
    }

    std::string name;
    std::string price;
    std::string lvl;
    std::string type;

    while(!inFile.eof())
    {
        getline(inFile, name, '\t');
        getline(inFile, price, '\t');
        getline(inFile, lvl, '\t');
        inFile >> type;

        if(inFile.eof())
            break;

        int type_num = stoi(type);
        switch(type_num)
        {
            case 1:
                AllPotions.push_back(new Potion(name, stoi(price), stoi(lvl), potionType::DEX));
                break;
            case 2:
                AllPotions.push_back(new Potion(name, stoi(price), stoi(lvl), potionType::STR));
                break;
            case 3:
                AllPotions.push_back(new Potion(name, stoi(price), stoi(lvl), potionType::AGIL));
                break;
            case 4:
                AllPotions.push_back(new Potion(name, stoi(price), stoi(lvl), potionType::HP));
                break;
            case 5:
                AllPotions.push_back(new Potion(name, stoi(price), stoi(lvl), potionType::MP));
                break;
        }   
    }
    inFile.close();

    std::cout << "\tInitializing All Potions... ";
    fflush(stdout);
    sleep(1);
    std::cout << "Done\n";
}

void Game::InitSpells()
{
    std::ifstream inFile;
    inFile.open("spells.txt");

    if(inFile.fail())
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

    while(!inFile.eof())
    {
        getline(inFile, name, '\t');
        getline(inFile, price, '\t');
        getline(inFile, lvl, '\t');
        getline(inFile, mindmg, '\t');
        getline(inFile, maxdmg, '\t');
        getline(inFile, mp, '\t');
        getline(inFile, dur, '\t');
        inFile >> type;

        if(inFile.eof())
            break;

        int type_num = stoi(type);
        switch(type_num)
        {
            case 1:
                AllSpells.push_back(new IceSpell(name, stoi(price), stoi(lvl), stoi(mindmg), stoi(maxdmg), stoi(mp), stoi(dur)));
                break;
            case 2:
                AllSpells.push_back(new FireSpell(name, stoi(price), stoi(lvl), stoi(mindmg), stoi(maxdmg), stoi(mp), stoi(dur)));
                break;
            case 3:
                AllSpells.push_back(new LightningSpell(name, stoi(price), stoi(lvl), stoi(mindmg), stoi(maxdmg), stoi(mp), stoi(dur)));
                break;
        }
    }
    inFile.close();

    std::cout << "\tInitializing All Spells... ";
    fflush(stdout);
    sleep(1);
    std::cout << "Done\n";
}

void Game::InitGrid()
{
    std::cout << "\tInitializing Grid... ";
    fflush(stdout);
    sleep(1);
    std::cout << "Done\n";
}

/* void Game::printWeap()
{
    system("clear");
    std::cout << "\n\n";
    for (auto it = AllWeapons.begin(); it != AllWeapons.end(); ++it)
    {
        (*it)->print();
    }
    std::cout << "\n" << AllWeapons.size() << "\n" << AllArmors.size() << "\n";
    std::cout << AllPotions.size() << "\n" << AllSpells.size() << "\n";
    std::cout << "\n\n";
    std::cout << "Returning to Main Menu...\n";
    sleep(60);
    system("clear");
} */

void Game::DIRPG()
{
    system("clear");
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(34) << "=== DI_RPG ===" << std::setw(29) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(22) << "[ 1 ]\tPlay Game" << std::setw(38) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "[ 2 ]\tCredits" << std::setw(40) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(22) << "[ 0 ]\tQuit Game" << std::setw(38) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    
    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while(!(std::cin >> input) || input > 2)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 2)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch(input)
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
    system("clear");
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(35) << "=== Credits ===" << std::setw(28) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(36) << "Polydoros Tamtamis" << std::setw(27) << "////////\n";
    std::cout << "////////" << std::setw(32) << "sdi1900184" << std::setw(31) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(35) << "Christos Ioannou" << std::setw(28) << "////////\n";
    std::cout << "////////" << std::setw(32) << "sdi1900222" << std::setw(31) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << "\tReturning to DI_RPG in\n";
    sleep(1); 
    for(int i=5; i>=1; i--)
    {
        for(int y=5; y>=i; y--)
            std::cout << "\t";
        std::cout << i << "..\n";
        sleep(1);
    }
    system("clear");
    DIRPG();
}

void Game::ExitScreen()
{
    system("clear");
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    std::cout << "\n\n";
    std::cout << "\tThank you for playing DI_RPG\n\n";
    std::cout << "\tQuitting Game...\n\n";
    playing = false;
    sleep(2);
    system("clear");
}

void Game::MainMenu()
{
    system("clear");
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(36) << "=== Main Menu ===" << std::setw(27) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(28) << "[ 1 ]\tCreate New Hero" << std::setw(32) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(27) << "[ 2 ]\tDisplay Market" << std::setw(33) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
/*     std::cout << "////////" << std::setw(30) << "[ 3 ]\tPrint All Weapons" << std::setw(30) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n"; */
    std::cout << "////////" << std::setw(22) << "[ 0 ]\tQuit Game" << std::setw(38) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    
    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while(!(std::cin >> input) || input > 3)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 3)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch(input)
    {
        case 1:
            clearbuffer();
            NewHeroMenu();
            break;
        case 2:
            clearbuffer();
            DisplayMarket();
            break;
/*      case 3:
            clearbuffer();
            printWeap();
            break; */
        case 0:
            clearbuffer();
            ExitScreen();
            break;
    }
}

void Game::DisplayMap()
{
    system("clear");
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    int printed = 0;
    for (int i = 0; i < 16; i++)
    {
        std::cout << "|";
        //Grid[i]->print();
        printed++;
        if (printed == 4)
        {
            printed = 0;
            std::cout << "|";
            putchar('\n');
        }
    }
}

void Game::NewHeroMenu()
{
    system("clear");
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== New Hero Menu ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(25) << "[ 1 ]\tWarrior Info" << std::setw(35) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(26) << "[ 2 ]\tSorcerer Info" << std::setw(34) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(25) << "[ 3 ]\tPaladin Info" << std::setw(35) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while(!(std::cin >> input) || input > 3)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 3)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch(input)
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
            MainMenu();
            break;
    }
}

void Game::WarriorInfo()
{
    system("clear");
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    Warrior temp("");
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(36) << "=== Warrior Info ===" << std::setw(27) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Strength: " << temp.get_strength() << std::setw(31) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Dexterity: " << temp.get_dexterity() << std::setw(31) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(30) << "Agility: " << temp.get_agility() << std::setw(32) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 1 ]\tSelect" << std::setw(41) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 2 ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while(!(std::cin >> input) || input > 2)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 2)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch(input)
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
            MainMenu();
            break;
    }
}

void Game::SorcererInfo()
{
    system("clear");
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    Sorcerer temp("");
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== Sorcerer Info ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Strength: " << temp.get_strength() << std::setw(31) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Dexterity: " << temp.get_dexterity() << std::setw(31) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(30) << "Agility: " << temp.get_agility() << std::setw(32) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 1 ]\tSelect" << std::setw(41) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 2 ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while(!(std::cin >> input) || input > 2)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 2)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch(input)
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
            MainMenu();
            break;
    }
}

void Game::PaladinInfo()
{
    system("clear");
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    Paladin temp("");
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(36) << "=== Paladin Info ===" << std::setw(27) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Strength: " << temp.get_strength() << std::setw(31) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(31) << "Dexterity: " << temp.get_dexterity() << std::setw(31) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(30) << "Agility: " << temp.get_agility() << std::setw(32) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 1 ]\tSelect" << std::setw(41) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 2 ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while(!(std::cin >> input) || input > 2)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 2)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch(input)
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
            MainMenu();
            break;
    }
}

void Game::CreateNewHero(heroType htype)
{
    system("clear");
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    if(MyHeroes.size() >= 3)
    {
        std::cout << "\n\n";
        std::cout << "\tMaximum number of Heroes is reached!\n\n";
        sleep(1);
        std::cout << "\tYou cannot create more Heroes\n\n";
        sleep(1);
        std::cout << "\tReturning to Main Menu...\n";
        sleep(1);
        system("clear");
        MainMenu();
    }
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(38) << "=== Create New Hero ===" << std::setw(25) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    switch(htype)
    {
        case(heroType::WARRIOR):
            std::cout << "////////" << std::setw(32) << "[ Warrior ]" << std::setw(31) << "////////\n";
            break;
        case(heroType::SORCERER):
            std::cout << "////////" << std::setw(32) << "[ Sorcerer ]" << std::setw(31) << "////////\n";
            break;
        case(heroType::PALADIN):
            std::cout << "////////" << std::setw(32) << "[ Paladin ]" << std::setw(31) << "////////\n";
            break;
    }
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(49) << "--------------------------------------------" << std::setw(14) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::string input_name;
    std::cout << std::setw(37) << "Hero Name: ";
    std::cin >> input_name;
    while(std::cin.fail())
    {
        std::cout << "\n" << std::setw(47) << "Something went wrong\n";
        std::cout << std::setw(41) << "Try again\n\n";
        std::cout << std::setw(37) << "Hero Name: ";
        clearbuffer();
        std::cin >> input_name;
    }
    for (auto it = MyHeroes.begin(); it != MyHeroes.end(); ++it)
    {
        while(input_name == (*it)->get_name())
        {
            std::cout << "\n" << std::setw(50) << "This name is already taken!\n";
            std::cout << std::setw(50) << "Please type a different name\n";
            std::cout << "\n" << std::setw(37) << "Hero Name: ";
            clearbuffer();
            std::cin >> input_name;
            while(std::cin.fail())
            {
                std::cout << "\n" << std::setw(47) << "Something went wrong\n";
                std::cout << std::setw(41) << "Try again\n\n";
                std::cout << std::setw(37) << "Hero Name: ";
                clearbuffer();
                std::cin >> input_name;
            }
        }
    }
    switch(htype)
    {
        case(heroType::WARRIOR):
            MyHeroes.push_back(new Warrior(input_name));
            break;
        case(heroType::SORCERER):
            MyHeroes.push_back(new Sorcerer(input_name));
            break;
        case(heroType::PALADIN):
            MyHeroes.push_back(new Paladin(input_name));
            break;
    }

    std::cout << "\n\n";
    std::cout << "\tCreated a New Hero successfully!\n\n";
    sleep(1);
    std::cout << "\tReturning to Main Menu...\n";
    sleep(1);
    system("clear");
}

void Game::DisplayMarket()
{
    system("clear");
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(34) << "=== Market ===" << std::setw(29) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(16) << "[ 1 ]\tBuy" << std::setw(44) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 2 ]\tSell" << std::setw(43) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while(!(std::cin >> input) || input > 2)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 2)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch(input)
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
            MainMenu();
            break;
    }
}

void Game::BuyMenu()
{
    system("clear");
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(34) << "=== Buy Menu ===" << std::setw(29) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "[ 1 ]\tWeapons" << std::setw(40) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 2 ]\tArmors" << std::setw(41) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "[ 3 ]\tPotions" << std::setw(40) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 4 ]\tSpells" << std::setw(41) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 5 ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while(!(std::cin >> input) || input > 5)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 5)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch(input)
    {
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
            DisplayMarket();
            break;
        case 0:
            clearbuffer();
            MainMenu();
            break;
    }
}

void Game::BuyWeapons()
{
    system("clear");
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "=== Buy Weapons ===" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "[ 1 ]\tWeapons" << std::setw(40) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 2 ]\tArmors" << std::setw(41) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "[ 3 ]\tPotions" << std::setw(40) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 4 ]\tSpells" << std::setw(41) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 5 ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while(!(std::cin >> input) || input > 5)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 5)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch(input)
    {
        case 5:
            clearbuffer();
            BuyMenu();
            break;
        case 0:
            clearbuffer();
            MainMenu();
            break;
    }
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
    system("clear");
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(35) << "=== Sell Menu ===" << std::setw(28) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "[ 1 ]\tWeapons" << std::setw(40) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 2 ]\tArmors" << std::setw(41) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "[ 3 ]\tPotions" << std::setw(40) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(19) << "[ 4 ]\tSpells" << std::setw(41) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 5 ]\tBack" << std::setw(43) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(17) << "[ 0 ]\tExit" << std::setw(43) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while(!(std::cin >> input) || input > 5)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 5)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch(input)
    {
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
            DisplayMarket();
            break;
        case 0:
            clearbuffer();
            MainMenu();
            break;
    }
}

void Game::clearbuffer()
{
    std::cin.clear();               //reset possible error flag
    std::cin.ignore(500, '\n');     //clear buffer
}

bool Game::get_playing() const
{
    return playing;
}