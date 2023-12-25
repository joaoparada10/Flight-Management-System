//
// Created by jonas on 17/12/2023.
//

#include "FMSGraph.h"

void FMSGraph::addAirline(Airline& airline)
{
    auto it = airlinesMap.find(airline.getCode());

    if( it == airlinesMap.end())
    {
        airlinesMap.insert(std::make_pair(airline.getCode(), airline)); // nao sei porque e que criar isto da maneira convencional nao estava a funcionar
    }
}

void FMSGraph::removeAirline(Airline& airline)
{
    auto it = airlinesMap.find(airline.getCode());

    if (it != airlinesMap.end())
    {
        airlinesMap.erase(it);
    }
}

void FMSGraph::addAirport(const Airport& airport)
{
    addVertex(airport);
}
void removeAirport(const Airport& airport);
void addFlight(const Flight& flight);
void removeFlight(const Flight& flight);