#ifndef AIRPORTLOADER_H_
#define AIRPORTLOADER_H_

#include "Graph.h"
#include "Airport.h"
#include "Airline.h"
#include <string>

class Loader {
public:
    static void loadAirports(Graph& graph, std::string filename);
    static void loadFlights(Graph& graph, const std::string& Filename);


    static Airline findAirlineByCode(const std::string &code, std::string filename); // finds airlines without loading the entire file
};

#endif
