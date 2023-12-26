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

double Airport::calculateDistance(const Airport& otherAirport)
{
    constexpr double earthRadius = 6371.0;

    double lat1 = toRadians(latitude);
    double lon1 = toRadians(longitude);
    double lat2 = toRadians(otherAirport.latitude);
    double lon2 = toRadians(otherAirport.longitude);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = std::sin(dlat / 2) * std::sin(dlat / 2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dlon / 2) * std::sin(dlon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    // Distance in kilometers
    double distance = earthRadius * c;

    return distance;
}

// Inside the Airport class definition
bool Airport::operator==(const Airport& other) const {
    return this->code == other.code;
}

