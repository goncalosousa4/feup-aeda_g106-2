#include "src/header/Graph.h"
#include "src/header/Loader.h"
#include "src/header/Airport.h"

#include <iostream>

int main(){
    Graph Airports;
    Loader::loadAirports(Airports);

    std::cout << "Number of airports loaded: " << Airports.getNumVertex() << std::endl;

    return 0;
}
