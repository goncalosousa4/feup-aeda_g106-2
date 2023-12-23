#include "../header/Airport.h"

Airport::Airport(std::string code, std::string name, std::string city, double latitude, double longitude)
        : code(code), name(name), city(city), latitude(latitude), longitude(longitude) {}

std::string Airport::getCode() const {
    return code;
}

std::string Airport::getName() const {
    return name;
}

std::string Airport::getCity() const {
    return city;
}

double Airport::getLatitude() const {
    return latitude;
}

double Airport::getLongitude() const {
    return longitude;
}
