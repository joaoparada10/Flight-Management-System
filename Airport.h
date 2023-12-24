//
// Created by jonas on 17/12/2023.
//

#ifndef AEDPROJECT2_AIRPORT_H
#define AEDPROJECT2_AIRPORT_H
#include <string>


class Airport {
private:
    string code;
    string name;
    string city;
    string country;
    double latitude;
    double longitude;

public:
    Airport(string code, string name, string city, string country, double latitude, double longitude);
    double getLatitude();
    double getLongitude();
    double calculateDistance(const Airport& otherAirport);
};


#endif //AEDPROJECT2_AIRPORT_H
