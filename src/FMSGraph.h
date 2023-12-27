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
#include <set>

class FMSGraph : public Graph<Airport> { // entao este aqui e so uma adaptaçao do graph com nomes chiques

private:
    std::unordered_map<std::string, Airline> airlinesMap; // isto e para termos as nossas airlines todas guardadas num sitio caso seja necessario

public:
    void addAirline(Airline& airline);
    void removeAirline(Airline& airline);
    void addAirport(Airport& airport);
    void removeAirport(const Airport& airport);
    void addFlight(Flight& flight);
    void removeFlight( Flight& flight);
    Airport findAirport(std::string code);
    Airline getAirline(std::string code);
    void airportFlightCount();      //i.
    void flightsPerAirport(std::string code);       //ii.
    vector<Vertex<Airport> * > getAirports() const;
    Airport getAirport(std::string code);
    void flightsPerCity(std::string city);          //iii.
    void flighsPerAirline(std::string airline);     //iii.
    void airportDestinations(std::string code);     //v.
    void reachableDestinationsInXStops(std::string code,int n); //vi.
    void numOfDestinationsCity(std::string city);       //iv.
    void numOfDestinationsAirport(std::string code);    //iv.
    void maxTrip();         //vii.
    void topAirports(int numOfAirports);        //viii.
    void articulationDfs(Vertex<Airport>* v, set<Airport> & articulationAirports, stack<Airport> &s, int index);
    void essentialAirports();
    int connectedComponents();
    void connectedComponentsDfsVisit(Vertex<Airport>* v, set<std::string> & airportCount);
    int lowestNumberOfStops(Vertex<Airport>* source, Vertex<Airport>* destination);
    set<vector<Vertex<Airport>*>> findAllShortestPathsBetweenAirports(Vertex<Airport>* source, Vertex<Airport>* destination);
    void bestFlightOption();
    vector<Airport> cityAirports(std::string city);
    Vertex<Airport>* cityOption();
    Vertex<Airport>* airportOption();
    Vertex<Airport>* coordinatesOption();
};


#endif //AEDPROJECT2_FMSGRAPH_H

