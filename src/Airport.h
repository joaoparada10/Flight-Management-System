//
// Created by jonas on 17/12/2023.
//

#ifndef AEDPROJECT2_AIRPORT_H
#define AEDPROJECT2_AIRPORT_H
#include <string>
#include <set>
#include <vector>

using namespace std;

class Airport {
private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    double latitude{};
    double longitude{};

public:
    Airport(std::string code, std::string name, std::string city, std::string country, double latitude, double longitude);
    Airport();
    std::string getCode();
    std::string getName();
    std::string getCity();
    std::string getCountry();
    double getLatitude();
    double getLongitude();
    bool operator==(const Airport& other) const;
    bool operator<(const Airport& other) const;
};


#endif //AEDPROJECT2_AIRPORT_H
