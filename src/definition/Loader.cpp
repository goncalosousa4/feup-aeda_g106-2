#include "../header/Airport.h"
#include "../header/Loader.h"
#include "Airline.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>


void Loader::loadAirports(Graph& graph, std::string filename) {
    std::ifstream file(filename);
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
            std::string country = tokens[3];
            double latitude = std::stod(tokens[4]);
            double longitude = std::stod(tokens[5]);

            if (graph.addVertex(code)) {
                auto vertex = graph.findVertex(code);
                vertex->setAirport(Airport(code, name, city,country, latitude, longitude));
            } else {
                std::cerr << "Error: Airport with code " << code << " already exists in the graph." << std::endl;
            }
        } else {
            std::cerr << "Error: Invalid line in file" << filename << std::endl;
        }
    }

    file.close();
}
void Loader::loadFlights(Graph& graph, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file flights.csv " << std::endl;
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

        if (tokens.size() == 3) {
            std::string origin = tokens[0];
            std::string destination = tokens[1];
            std::string airline = tokens[2];

            Vertex* source = graph.findVertex(origin);
            Airport src=source->getAirport();


            Vertex* dest = graph.findVertex(destination);
            Airport des = dest->getAirport();


            if (graph.findVertex(origin) && graph.findVertex(origin) ) {

                // Haversine Distance Function implementation, i guess

                double lat1 = src.getLatitude();
                double lon1 = src.getLongitude();
                double lat2 = des.getLatitude();
                double lon2 = des.getLongitude();

                lat1 = lat1 * M_PI / 180.0;
                lon1 = lon1 * M_PI / 180.0;
                lat2 = lat2 * M_PI / 180.0;
                lon2 = lon2 * M_PI / 180.0;


                double dlat = lat2 - lat1;
                double dlon = lon2 - lon1;
                double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
                double c = 2 * atan2(sqrt(a), sqrt(1 - a));


                const double radius = 6371.0;


                double w = radius * c;


                graph.addEdge(origin, destination, airline, w);
            } else {
                std::cerr << "Error: One or both airports not found for flight from "
                          << origin << " to " << destination << std::endl;
            }
        } else {
            std::cerr << "Error: Invalid line in file " << filename << std::endl;
        }
    }

    file.close();
}
