//
// Created by jonas on 17/12/2023.
//

#ifndef AEDPROJECT2_FLIGHT_H
#define AEDPROJECT2_FLIGHT_H
#include <string>

class Flight {
private:
    std::string source;
    std::string target;
    std::string airLine;
public:
    Flight(std::string Source, std::string Target , std::string Airline);
    std::string getSource();
    std::string getTarget();
    std::string getAirline();
};


#endif //AEDPROJECT2_FLIGHT_H
