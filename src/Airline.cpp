//
// Created by jonas on 17/12/2023.
//

#include "Airline.h"

Airline::Airline(int code, int name, int callsign, int country)
{
    this->code = code;
    this->name = name;
    this->callsign = callsign;
    this->country = country;
}

std::string Airline::getCode()
{
    return this->code;
}

std::string Airline::geName()
{
    return this->name;
}

std::string Airline::getCallsign()
{
    return this->callsign;
}

std::string Airline::getCountry()
{
    return this->country;
}