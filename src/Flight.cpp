//
// Created by jonas on 29/12/2023.
//

#include "Flight.h"
#include "Airport.h"

Flight::Flight(Airport Source, Airport Target, Airline airline)
        : source(Source), target(Target), airLine(airline) {}


Airline Flight::getAirline()
{
    return this->airLine;
}

Airport Flight::getSource()
{
    return this->source;
}

Airport Flight::getTarget()
{
    return this->target;
}

