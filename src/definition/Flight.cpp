#include "Flight.h"

Flight::Flight(const std::string& source, const std::string& dest, const std::string& airline)
        : origin(source), destination(dest), airline(airline) {

}
const std::string& Flight::getSource() const {return origin;}

const std::string& Flight::getDest() const {return destination;}

const std::string& Flight::getAirline() const {return airline;}