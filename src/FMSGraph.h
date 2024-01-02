//
// Created by jonas on 17/12/2023.
//

/**
 * @file FMSGraph.h
 * @brief Header file for the FMSGraph class and an extention of graph.h
 */

#ifndef AEDPROJECT2_FMSGRAPH_H
#define AEDPROJECT2_FMSGRAPH_H

#include "Graph.h"
#include "Flight.h"
#include <unordered_map>
#include <set>

class FMSGraph : public Graph<Airport> {

private:
    std::unordered_map<std::string, Airline> airlinesMap;

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
    vector<vector<Flight>> allPossibleFlightsPerTravel(vector<Vertex<Airport>*> path);
    int filterPerMinNumberOfAirlines(vector<vector<Flight>>& allPossibleFlights);
    void bestFlightOptions(Vertex<Airport>* source , Vertex<Airport>* destination);
    void bestFlightOptionsWithFilter(Vertex<Airport> *source, Vertex<Airport> *destination);
    vector<Airport> cityAirports(std::string city);
    Vertex<Airport>* cityOption();
    Vertex<Airport>* airportOption();
    Vertex<Airport>* coordinatesOption();
    void addAirlinesToFilter(vector<Airline>& airlines);
    void removeAirlinesFromFilter(vector<Airline>& airlines);
    FMSGraph applyAirlineFilter(vector<Airline> selectedAirlines);
};


#endif //AEDPROJECT2_FMSGRAPH_H

