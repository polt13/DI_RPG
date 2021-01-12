#include "rpg_lib.hpp"
#include <iomanip>
//  Needed for sleep function
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <cstdlib>

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
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    std::cout << "\n\n";
    std::cout << "\tWelcome to DI_RPG\n\n";
    std::cout << "\tPress ENTER to continue..." << std::endl;
    std::cin.get();
    system("clear");
}

void Game::CreditsScreen()
{
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(36) << "=== Credits ===" << std::setw(27) << "////////\n";
    std::cout << "////////" << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(37) << "Polydoros Tamtamis" << std::setw(26) << "////////\n";
    std::cout << "////////" << std::setw(33) << "sdi1900184" << std::setw(30) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(36) << "Christos Ioannou" << std::setw(27) << "////////\n";
    std::cout << "////////" << std::setw(33) << "sdi1900222" << std::setw(30) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::cout << "\n";

    std::cout << "\tReturning to Main Menu in\n";
    sleep(1); 
    for(int i=5; i>=1; i--)
    {
        for(int y=5; y>=i; y--)
            std::cout << "\t";
        std::cout << i << "..\n";
        sleep(1);
    }
    system("clear");
    MainMenu();
}

void Game::ExitScreen()
{
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    std::cout << "\n\n";
    std::cout << "\tThank you for playing DI_RPG\n\n";
    std::cout << "\tQuitting Game...\n\n";
    playing = false;
    sleep(2);
}

void Game::MainMenu()
{
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
    std::cout << "////////" << std::setw(22) << "[ 1 ]\tPlay Game" << std::setw(38) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(20) << "[ 2 ]\tCredits" << std::setw(40) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(28) << "[ 3 ]\tCreate New Hero" << std::setw(32) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(27) << "[ 4 ]\tDisplay Market" << std::setw(33) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////" << std::setw(22) << "[ 0 ]\tQuit Game" << std::setw(38) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "////////"                                << std::setw(63) << "////////\n";
    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    
    std::cout << "\n";

    std::cout << std::setw(37) << "Input: ";

    while(!(std::cin >> input) || input > 9)
    {
        std::cout << "\n";
        std::cout << std::setw(50) << "Invalid input (Must be: 0 - 9)\n";
        clearbuffer();
        std::cout << std::setw(37) << "Input: ";
    }

    switch(input)
    {
        case 1:
            break;
        case 2:
            clearbuffer();
            CreditsScreen();
            break;
        case 3:
            clearbuffer();
            CreateNewHero();
            break;
        case 4:
            clearbuffer();
            DisplayMarket();
        case 0:
            clearbuffer();
            ExitScreen();
            break;
    }
}

void Game::CreateNewHero()
{
    std::cout << "\n\n\tLoading.." << std::endl;
    system("clear");
    if(MyHeroes.size() >= 3)
    {
        std::cout << "\n\n\tMaximum number of Heroes is reached!\n";
        sleep(1);
        std::cout << "\n\tYou cannot create more Heroes\n";
        sleep(1);
        std::cout << "\n\tReturning to Main Menu...\n";
        sleep(1);
        system("clear");
        return;
    }
    std::string input_name;
    std::cout << "Hero Name: ";
    std::cin >> input_name;
    while(std::cin.fail())
    {
        std::cout << "Something went wrong\n";
        std::cout << "Try again\n";
        std::cout << "Hero Name: ";
        clearbuffer();
        std::cin >> input_name;
    }
    for (auto it = MyHeroes.begin(); it != MyHeroes.end(); ++it)
    {
        while(input_name == (*it)->get_name())
        {
            std::cout << "This name is already taken!\n";
            std::cout << "Please type a different name\n";
            std::cout << "Hero Name: ";
            clearbuffer();
            std::cin >> input_name;
            while(std::cin.fail())
            {
                std::cout << "Something went wrong\n";
                std::cout << "Try again\n";
                std::cout << "Hero Name: ";
                clearbuffer();
                std::cin >> input_name;
            }
        }
    }
    std::string input_htype;
    std::cout << "Hero Types [Warrior] | [Sorcerer] | [Paladin]\n";
    std::cout << "Hero Type: ";
    while(!(std::cin >> input_htype) || (input_htype != "Warrior" && input_htype != "Sorcerer" && input_htype != "Paladin"))
    {
        std::cout << "Invalid Type of Hero (Must be: 'Warrior' / 'Sorcerer' / 'Paladin)\n";
        std::cout << "Hero Type: ";
        clearbuffer();
    }
    if(input_htype == "Warrior")
    {
        MyHeroes.push_back(new Warrior(input_name));
    }
    else if(input_htype == "Sorcerer")
    {
        MyHeroes.push_back(new Sorcerer(input_name));
    }
    else
    {
        MyHeroes.push_back(new Paladin(input_name));
    }
    std::cout << "Created a New Hero successfully!\n";
    sleep(1);
    std::cout << "Returning to Main Menu...\n";
    sleep(1);
    system("clear");
}

void Game::DisplayMarket()
{
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

void Game::SellMenu()
{
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