//
// Created by jonas on 17/12/2023.
//

#include "Flight.h"
#include <string>

Flight::Flight(std::string Source, std::string Target , std::string Airline)
{
    this->source = Source;
    this->target = Target;
    this->airLine = Airline;
}

std::string Flight::getAirline() {
    return this->airLine;
}
std::string Flight::getSource() {
    return this->source;
}
std::string Flight::getTarget() {
    return this->target;
}
