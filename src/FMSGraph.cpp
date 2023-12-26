//
// Created by jonas on 17/12/2023.
//

#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
#include "FMSGraph.h"


void FMSGraph::addAirline(Airline& airline)
{
    std::string code = airline.getCode();
    this->airlinesMap.insert(std::make_pair(code,airline));

}

void FMSGraph::removeAirline(Airline& airline)
{
    auto it = airlinesMap.find(airline.getCode());

    if (it != airlinesMap.end())
    {
        airlinesMap.erase(it);
    }
}

void FMSGraph::addAirport(Airport& airport)
{
    addVertex(airport);
}
void FMSGraph::removeAirport(const Airport& airport)
{
    removeVertex(airport);
}



void FMSGraph::addFlight(Flight& flight)
{
    addEdge(flight.getSource(),flight.getTarget(),flight.getAirline().getCode());
}


void FMSGraph::removeFlight(Flight& flight)
{
    removeEdge(flight.getSource(),flight.getTarget());
}

Airport FMSGraph::findAirport(std::string code)
{
    vector<Vertex<Airport> * > airports = getVertexSet();

    for (auto v : airports)
    {
        if (v->getInfo().getCode() == code)
        {
            return v->getInfo();
        }
    }
}

Airline FMSGraph::getAirline(std::string code)
{
    auto it = airlinesMap.find(code);
    if (it != airlinesMap.end()) {
        return it->second;
    }
}

void FMSGraph::airportFlightCount() {
    int airportCount = 0;
    int flightCount = 0;
    for (auto v : getVertexSet()){
        airportCount++;
        flightCount += v->getAdj().size();
    }
    std::cout << "Global number of airports: " << airportCount << std::endl;
    std::cout << "Global number of flights: " << flightCount << std::endl;
}

void FMSGraph::flightsPerAirport(std::string code) {
    Airport airport = findAirport(code);
    set<Airline> airlines;
    auto v = findVertex(airport);
    int flightCount = v->getAdj().size();
    for (auto e : v->getAdj()){
        airlines.insert(getAirline(e.getWeight()));
    }
    int airLineCount = airlines.size();
    std::cout << airport.getName() << " has " << flightCount << " outgoing flights from " << airLineCount
    << " different airlines." << std::endl;
}

vector<Vertex<Airport> * > FMSGraph::getAirports() const
{
    return getVertexSet();
}

void FMSGraph::flightsPerCity(std::string city)
{
    std::string city2 = city;
    std::transform(city2.begin(), city2.end(), city2.begin(), ::tolower);
    city2[0] = std::toupper(city2[0]);

    int numOfFlights = 0;


    for(auto airport : getAirports())
    {
        if(airport->getInfo().getCity() == city2)
        {
            numOfFlights += airport->getAdj().size();
        }
    }

    std::cout << "There are " << numOfFlights << " out of the city of " << city2 << std::endl;
}

void FMSGraph::flighsPerAirline(std::string airline)
{
    int numOfFlights = 0;

    for( auto airports : getAirports())
    {
        for(auto flight : airports->getAdj())
        {
            if(flight.getWeight() == airline)
            {
                numOfFlights += 1;
            }
        }
    }

    std::cout << "There are " << numOfFlights << " from " << airlinesMap.find(airline)->second.getName() << std::endl;
}

void FMSGraph::numOfDestinationsCity(std::string city)
{
    std::string city2 = city;
    std::transform(city2.begin(), city2.end(), city2.begin(), ::tolower);
    city2[0] = std::toupper(city2[0]);

    vector<std::string> difCountries;

    for(auto airport : getAirports())
    {
        if(airport->getInfo().getCity() == city2)
        {
            for(auto destinations : airport->getAdj())
            {
                auto it = std::find(difCountries.begin(), difCountries.end(),destinations.getDest()->getInfo().getCountry());

                if( it == difCountries.end())
                {
                    difCountries.push_back(destinations.getDest()->getInfo().getCountry());
                }
            }
        }
    }

    if(!difCountries.empty())
        std::cout << "The city of " << city2 << " has a number of " << difCountries.size() << " possible destinations." << std::endl;

    else
        std::cout << "The city of " << city2 << " was not found or it does not have an airport" << std::endl;
}

void FMSGraph::numOfDestinationsAirport(std::string code)
{
    std::string code2 = code;
    std::transform(code2.begin(), code2.end(), code2.begin(), ::toupper);


    vector<std::string> difCountries;


        for (auto airport: getAirports())
        {
            if (airport->getInfo().getCode() == code2)
            {
                for (auto destinations: airport->getAdj())
                {
                    auto it = std::find(difCountries.begin(), difCountries.end(),destinations.getDest()->getInfo().getCountry());
                    if (it == difCountries.end())
                    {
                        difCountries.push_back(destinations.getDest()->getInfo().getCountry());
                    }
                }
            }
        }


    if (difCountries.size() > 0)
    {
        std::cout << "The airport " << findAirport(code2).getName() << " has a number of " << difCountries.size() << " possible different countries as destination" << std::endl;
    }
    else
    {
        std::cout << "Airport not found" << std::endl;
    }

}
