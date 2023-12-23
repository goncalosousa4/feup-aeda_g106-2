#include "../header/Airport.h"

Airport::Airport(const std::string& code, const std::string& name, const std::string& city, double latitude, double longitude)
        : code(code), name(name), city(city), latitude(latitude), longitude(longitude) {}

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
