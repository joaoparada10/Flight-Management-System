//
// Created by jonas on 26/12/2023.
//
#include "FileReader.h"
#include <iostream>

int main(){
    std::cout << "Hello World :D" << std::endl;
    FMSGraph testGraph;
    FileReader::airlineMap("data/airlines.csv",testGraph);
    FileReader::addAirports("data/airports.csv", testGraph);
    FileReader::addFlights("data/flights.csv",testGraph);
    //testGraph.airportFlightCount();                                 //i.
    //testGraph.flightsPerAirport("OPO");                     //ii.
    /*testGraph.flightsPerCity("lisbon");                     //iii.
    testGraph.flighsPerAirline("IBE");                      //iii.
    testGraph.numOfDestinationsCity("HORTA");               //iv.
    testGraph.numOfDestinationsAirport("FAO");              //iv.
    testGraph.airportDestinations("OPO");                    //v
    testGraph.reachableDestinationsInXStops("OPO",7);   //vi.
    testGraph.maxTrip();                                        //vii
    testGraph.topAirports(9);                       //viii */
    //testGraph.essentialAirports();
    set<vector<Vertex<Airport>*>> test = testGraph.findAllShortestPathsBetweenAirports(testGraph.findVertex(testGraph.findAirport("OPO")),testGraph.findVertex(testGraph.findAirport("SUJ")));

    for (auto path : test){
        for (auto v : path){
            std::cout << v->getInfo().getName() << " - ";
        }
        std::cout << std::endl;
    }

    testGraph.bestFlightOption();
    return 0;
}