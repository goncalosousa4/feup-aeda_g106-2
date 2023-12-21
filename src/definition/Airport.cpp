#include "../header/Airport.h"
#include "../header/Loader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Airport::Airport(const std::string& code, const std::string& name, const std::string& city, double latitude, double longitude):
            code(code), name(name), city(city), latitude(latitude), longitude(longitude) {}

const std::string& Airport::getCode() const {
    return code;
}

const std::string& Airport::getName() const {
    return name;
}

const std::string& Airport::getCity() const {
    return city;
}

double Airport::getLatitude() const {
    return latitude;
}

double Airport::getLongitude() const {
    return longitude;
}

void Loader::loadAirports(Graph& graph) {
    std::string filename = "dataset/airports.csv";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
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
            std::cout << token << std::endl;
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
            std::cerr << "Error: Invalid line in file " << filename << std::endl;
        }
    }

    file.close();
}