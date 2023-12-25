#include "src/header/Graph.h"
#include "src/header/Loader.h"
#include "src/header/Menu.h"
#include <iostream>


int main() {
    Graph Airport;
    Loader::loadAirports(Airport, "airports.csv");
    Loader::loadFlights(Airport, "flights.csv");
    std::cout << " ___________________________________________________\n";
    std::cout << "| --> Welcome to Flight Management Services AED <-- |\n";
    std::cout << "|            Press 0 + ENTER to continue            | \n";
    std::cout << "|___________________________________________________|\n";
    int space;
    std::cin >> space;
    if (space == 0){

        std::cout<<"          \\    "<<std::endl;
        std::cout<<"          \\ \\"<<std::endl;
        std::cout<<"           \\  \\"<<std::endl;
        std::cout<<"    |\\      \\   \\"<<std::endl;
        std::cout<<"... >}==|||A E D|||[  ) .....................    "<<std::endl;
        std::cout<<"    |/      /   /"<<std::endl;
        std::cout<<"           /  /"<<std::endl;
        std::cout<<"          / /"<<std::endl;
        std::cout<<"          /"<<std::endl;

        std::cout<<"                   \\    "<<std::endl;
        std::cout<<"                   \\ \\"<<std::endl;
        std::cout<<"                    \\  \\"<<std::endl;
        std::cout<<"             |\\      \\   \\"<<std::endl;
        std::cout<<"............ >}==|||A E D|||[  ) ............    "<<std::endl;
        std::cout<<"             |/      /   /"<<std::endl;
        std::cout<<"                    /  /"<<std::endl;
        std::cout<<"                   / /"<<std::endl;
        std::cout<<"                   /"<<std::endl;

        std::cout<<"                            \\    "<<std::endl;
        std::cout<<"                            \\ \\"<<std::endl;
        std::cout<<"                             \\  \\"<<std::endl;
        std::cout<<"                      |\\      \\   \\"<<std::endl;
        std::cout<<"..................... >}==|||A E D|||[  ) ...    "<<std::endl;
        std::cout<<"                      |/      /   /"<<std::endl;
        std::cout<<"                             /  /"<<std::endl;
        std::cout<<"                            / /"<<std::endl;
        std::cout<<"                            /"<<std::endl;

        Menu::displayMenu(Airport);
    } else {std::cout<< "Enter a valid key!";}


}

//          \
//          \ \
//           \  \
//    |\      \   \
//    > }==|||||||||||[  )
//    |/      /   /
//           /  /
//          / /
//          /