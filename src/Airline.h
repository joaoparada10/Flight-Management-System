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
    int count;  //auxiliary; number of airline flights per travel

public:
    Airline(std::string code, std::string name, std::string callsign, std::string country);
    std::string getCode();
    std::string getName();
    std::string getCallsign();
    std::string getCountry();
    int getCount();
    void setCount(int count);
    bool operator==(const Airline& other) const;
    bool operator<(const Airline& other) const;
};


#endif //AEDPROJECT2_AIRLINE_H
