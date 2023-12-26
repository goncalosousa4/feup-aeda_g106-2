#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "Graph.h"

class Menu {
public:

    static void displayMenu(Graph ap);
    static void airportInfoMenu(Graph ap);
    static void statsMenu(Graph ap);

private:
    static void printAvailableAirports(Graph ap);
    static void printAvailableFlights(Graph ap);
    static void countFlightsOutOfAirport(Graph ap);
    static void flightsPerCityPerAirline(Graph ap);
    static void flightsPerAirline(Graph ap);
    static void countCountriesForAirport(Graph ap);
    static void countCountriesForCity(Graph ap);
    static void printNumDestinationsForAirport(Graph ap);

};

#endif