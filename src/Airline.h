//
// Created by jonas on 17/12/2023.
//

#ifndef AEDPROJECT2_AIRLINE_H
#define AEDPROJECT2_AIRLINE_H

#include <string>

class Airline {
private:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;

public:
    Airline(std::string code, std::string name, std::string callsign, std::string country)
    std::string getCode();
    std::string geName();
    std::string getCallsign();
    std::string getCountry();
};


#endif //AEDPROJECT2_AIRLINE_H
