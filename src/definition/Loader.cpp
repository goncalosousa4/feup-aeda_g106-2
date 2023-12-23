#include "../header/Airport.h"
#include "../header/Loader.h"
#include "../header/Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void Loader::loadAirports(Graph& graph, std::string filename) {
    std::ifstream file("../dataset/airports.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file airports.csv " << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // ignore the 1st line
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 6) {
            std::string code = tokens[0];
            std::string name = tokens[1];
            std::string city = tokens[2];
            double latitude = std::stod(tokens[4]);
            double longitude = std::stod(tokens[5]);
            if (graph.addVertex(code)) {
                auto vertex = graph.findVertex(code);
                vertex->setAirport(Airport(code, name, city, latitude, longitude));
            } else {
                std::cerr << "Error: Airport with code " << code << " already exists in the graph." << std::endl;
            }
        } else {
            std::cerr << "Error: Invalid line in file dataset/airports.csv"<< std::endl;
        }
    }

    file.close();
}
