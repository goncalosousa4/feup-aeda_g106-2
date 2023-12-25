#ifndef AIRLINE_H
#define AIRLINE_H

#include <string>

class Airline {
public:
    Airline();
    Airline(const std::string& code, const std::string& name, const std::string& callsign, const std::string& country);

    // Getter methods (you can add more if needed)
    std::string getCode() const;
    std::string getName() const;
    std::string getCallsign() const;
    std::string getCountry() const;

private:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;
};

#endif // AIRLINE_H
