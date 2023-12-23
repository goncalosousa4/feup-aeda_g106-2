// Menu.h

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "Graph.h"

class Menu {
public:

    static void displayMenu(Graph ap);

private:
    static void printAvailableAirports(Graph ap);
    static void printAvailableFlights(Graph ap);


};

#endif // MENU_H
