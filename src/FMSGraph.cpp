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