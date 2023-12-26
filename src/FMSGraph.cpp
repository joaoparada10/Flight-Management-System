//
// Created by jonas on 17/12/2023.
//

#include <iostream>
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

