#ifndef AIRPORTLOADER_H_
#define AIRPORTLOADER_H_

#include "Graph.h"
#include "Airport.h"
#include <string>

class Loader {
public:
    static void loadAirports(Graph& graph, std::string filename);
    static void loadFlights(Graph& graph, const std::string& flightFilename);
};

#endif /* AIRPORTLOADER_H_ */
