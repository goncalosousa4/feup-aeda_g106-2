#include "../header/Airline.h"

Airline::Airline() {}

Airline::Airline(const std::string& code, const std::string& name, const std::string& callsign, const std::string& country)
        : code(code), name(name), callsign(callsign), country(country) {}

std::string Airline::getCode() const {
    return code;
}

std::string Airline::getName() const {
    return name;
}

std::string Airline::getCallsign() const {
    return callsign;
}

std::string Airline::getCountry() const {
    return country;
}
