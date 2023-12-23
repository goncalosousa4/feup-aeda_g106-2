#include "src/header/Graph.h"
#include "src/header/Airport.h"
#include "src/header/Loader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main() {
    Graph Airport;
    Loader::loadAirports(Airport);
    return 0;
}
