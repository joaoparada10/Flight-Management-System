//
// Created by jonas on 17/12/2023.
//

#include "Airline.h"

Airline::Airline(std::string code, std::string name, std::string callsign, std::string country)
{
    this->code = code;
    this->name = name;
    this->callsign = callsign;
    this->country = country;
    this->count = 0;
}

std::string Airline::getCode()
{
    return this->code;
}

std::string Airline::getName()
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

bool Airline::operator==(const Airline& other) const
{
    return this->code == other.code;
}

bool Airline::operator<(const Airline &other) const {
    if (this->count != other.count) return this->count < other.count;
    return this->code < other.code;
}

int Airline::getCount() {
    return this->count;
}

void Airline::setCount(int count) {
    this->count = count;
}
