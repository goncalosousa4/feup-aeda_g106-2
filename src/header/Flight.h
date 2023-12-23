#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>

class Flight {
public:
    Flight(const std::string& source, const std::string& dest, const std::string& airline);
    const std::string& getSource() const;
    const std::string& getDest() const;
    const std::string& getAirline() const;

private:
    std::string origin;
    std::string destination;
    const std::string& airline;
};

#endif //FLIGHT_H
