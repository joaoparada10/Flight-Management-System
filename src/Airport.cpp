//
// Created by jonas on 17/12/2023.
//

#include "Airport.h"
#include <string>
#include <complex>

Airport::Airport(std::string code, std::string name, std::string city, std::string country, double latitude, double longitude)
{
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}

std::string Airport::getCode()
{
    return this->code;
}

std::string Airport::getName()
{
    return this->name;
}

std::string Airport::getCity()
{
    return this->city;
}

std::string Airport::getCountry()
{
    return this->country;
}

double Airport::getLatitude()
{
    return this->latitude;
}

double Airport::getLongitude()
{
    return this->longitude;
}

double toRadians(double degree) // funçao auxiliar para a funçao de cima
{
    return degree * (M_PI / 180.0);
}

// Inside the Airport class definition
bool Airport::operator==(const Airport& other) const {
    return this->code == other.code;
}

bool Airport::operator<(const Airport &other) const {
    return this->code < other.code;
}

Airport::Airport() = default;

