#include "src/header/Graph.h"
#include "src/header/Loader.h"
#include "src/header/Menu.h"
#include <iostream>
#include <chrono>
#include <thread>


int main() {
    Graph Airport;

    std::cout << "\nPLEASE WAIT WHILE WE TAKE OFF...\n";
    std::cout << "IT SHOULDN'T TAKE MUCH LONGER\n\n\n";

    Loader::loadAirports(Airport, "../dataset/airports.csv");


    Loader::loadFlights(Airport, "../dataset/flights.csv");

    std::cout << "FASTEN YOUR SEATBELTS, HERE WE GO!\n\n\n";



    std::cout << " ___________________________________________________\n";
    std::cout << "| --> Welcome to Flight Management Services AED <-- |\n";
    std::cout << "|            Enter your name to continue            | \n";
    std::cout << "|___________________________________________________|\n";
    std::string name;
    std::cin >> name;
    std::cout << std::endl;

    std::cout<<"          \\    "<<std::endl;
    std::cout<<"          \\ \\"<<std::endl;
    std::cout<<"           \\  \\"<<std::endl;
    std::cout<<"    |\\      \\   \\"<<std::endl;
    std::cout<<"--  >}(|||||A E D|||[  )  ---------------------    "<<std::endl;
    std::cout<<"    |/      /   /"<<std::endl;
    std::cout<<"           /  /     Hello! Welcome "<< name << "!" << std::endl;
    std::cout<<"          / /        " << std::endl;
    std::cout<<"          /"<<std::endl;

    Menu::displayMenu(Airport);



}

//          \
//          \ \
//           \  \
//    |\      \   \
//    >}(|||||A E D|||[  )
//    |/      /   /
//           /  /
//          / /
//          /