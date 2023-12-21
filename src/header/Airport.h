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
    Airport(const std::string& code, const std::string& name, const std::string& city,
            double latitude, double longitude);

    const std::string& getCode() const;
    const std::string& getName() const;
    const std::string& getCity() const;
    double getLatitude() const;
    double getLongitude() const;
};

#endif /* AIRPORT_H_ */
