//
// Created by jonas on 17/12/2023.
//

#ifndef AEDPROJECT2_AIRPORT_H
#define AEDPROJECT2_AIRPORT_H
#include <string>

using namespace std;

class Airport {
private:
    string code;
    string name;
    string city;
    string country;
    double latitude;
    double longitude;

public:
    Airport(std::string code, std::string name, std::string city, std::string country, double latitude, double longitude);
    std::string getCode();
    std::string getName();
    std::string getCity();
    std::string geTCountry();
    double getLatitude();
    double getLongitude();
    double calculateDistance(const Airport& otherAirport);
};


#endif //AEDPROJECT2_AIRPORT_H