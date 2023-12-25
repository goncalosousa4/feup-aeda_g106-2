#ifndef AIRLINE_H
#define AIRLINE_H

#include <string>

class Airline {
public:
    Airline();
    Airline(const std::string& code, const std::string& name, const std::string& callsign, const std::string& country);


    const std::string& getCode() const;
    const std::string& getName() const;
    const std::string& getCallsign() const;
    const std::string& getCountry() const;

private:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;
};

#endif // AIRLINE_H
