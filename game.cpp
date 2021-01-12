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
    //
}

void Game::StartScreen()
{
    system("clear");
    std::cout << "\n\n";
    std::cout << "\tWelcome to DI_RPG\n\n";
    std::cout << "\tPress ENTER to continue..." << std::endl;
    std::cin.get();
    system("clear");
}

void Game::CreditsScreen()
{
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
        case 0:
            clearbuffer();
            ExitScreen();
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