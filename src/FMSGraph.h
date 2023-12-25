//
// Created by jonas on 17/12/2023.
//
// Podemos dar extend do Graph.h e fazer as funções que precisamos para o projeto aqui (Airport = Vertex; Flight = Edge) OU implementar do 0 um custom graph
#ifndef AEDPROJECT2_FMSGRAPH_H
#define AEDPROJECT2_FMSGRAPH_H

#include "Graph.h"
#include "Airport.h"
#include "Airline.h"
#include "Flight.h"
#include <unordered_map>

class FMSGraph : public Graph<Airport> { // entao este aqui e so uma adaptaçao do graph com nomes chiques

private:
    std::unordered_map<std::string, Airline> airlinesMap; // isto e para termos as nossas airlines todas guardadas num sitio caso seja necessario

public:
    void addAirline(Airline& airline);
    void removeAirline(Airline& airline);
    void addAirport(const Airport& airport);
    void removeAirport(const Airport& airport);
    void addFlight(const Flight& flight);
    void removeFlight(const Flight& flight);
};


#endif //AEDPROJECT2_FMSGRAPH_H
