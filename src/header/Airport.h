#ifndef AIRPORT_H_
#define AIRPORT_H_

#include <string>

class Airport {
private:
    std::string code;
    std::string name;
    std::string city;
    double latitude;
    double longitude;

public:
    Airport(std::string code, std::string name, std::string city, double latitude, double longitude);

    std::string getCode() const;
    std::string getName() const;
    std::string getCity() const;
    double getLatitude() const;
    double getLongitude() const;
};

#endif /* AIRPORT_H_ */
